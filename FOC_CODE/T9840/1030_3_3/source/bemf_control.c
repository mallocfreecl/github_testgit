#include "bemf_control.h"
#include "ADCSample.h"
#include "MotorAPI.h"
#include "commons.h"
#include "divider.h"
#include "driver_generic.h"
#include "irq.h"
#include "main.h"
#include "motor.h"
#include "pi_controller.h"
#include "pre_pwm_helper_addon.h"
#include "pre_pwm_module.h"
#include "pwm_module.h"
#include "saradc_module.h"
#include "testmode.h"
#include "u_f_table.h"
#include "IsrHandler.h"

#include "debug.h"

/* Defines*/
/******************************************************************/
/* 根据转速计算反电势幅值的系数，23.07.18 by lxs */
#define BEMF_CONTROL_BEMF_COEF1 (113)
#define BEMF_CONTROL_BEMF_COEF2 (340640)

/* 执行速度PI需要满足的最小Sector个数，22.03.06 by yhd */
#define BEMF_CONTROL_SECTOR_CNT_MIN (3u)

#define BEMF_CONTROL_VBAT_COMP_MIN (850) // AD:850->15V
/* 额定工作电压为27V 23.11.7 by lxs */
static u16 MOTOR_REF_VOLTAGE = 1536;//270*4096/720
/* 反转有转速启动定位转速 24.01.05 by lxs */
#define BEMF_CONTROL_REVERSAL_TO_ALIAN_SPEED (-500)
/* 开路诊断阈值 23.12.15 by lxs */
#define OPEN_LOAD_DIAG_VOLTAGE_DIFF_MAX (10u << 4)
/* 短路诊断阈值 23.12.15 by lxs */
#define BEMF_CONTROL_DIFF_SHORT (10u)
/* demo自带相移函数，程序使用自己算的相移，不使用demo，为节省空间，屏蔽掉 2023.12.15 by lxs */
#define BEMF_CONTROL_EN_DEMO_SHIFT_WAVE (0u)
/* 使能有转速启停切闭环相关代码标志，水泵无需有转速启停 */
#define BEMF_CONTROL_START_TO_CLOSE_EN (0u)
/* 计算相偏移的系数 24.03.25 by lxs */
#define BEMF_CONTROL_PHASEDIFFOFFSET_COFE1 (49)
#define BEMF_CONTROL_PHASEDIFFOFFSET_COFE2 (8)

u16 FilteredBat = 0;

bemf_control_target_state_t target;
bemf_control_current_state_t current;

pi_ctrl_data_t inc_controller;
pi_ctrl_data_t mult_controller;

s16 shift_wave = 0;
/* 修改为静态变量 2023.10.29 by lxs */
#if BEMF_CONTROL_EN_DEMO_SHIFT_WAVE
static s16 shift_wave_last_val = 0;
#endif
/* 修改为静态变量 2023.10.29 by lxs */
static u16 filter_bits = FILTER_BITS_SETTING;

// In standstill position is determined with test pulses
/* 修改为静态变量 2023.10.29 by lxs */
static bool enable_startup_current = true;
/*duration of every of the four test-pulses*/
static u16 voltage_devider_time = STARTUP_DURATION;

/* 闭环后的Sector计数，22.03.06 by yhd */
static u8 SectorCnt = 0u;
/* 修改为静态变量 2023.10.29 by lxs */
static s16 waiting_for_controller = 0;
/* 暂时屏蔽开路相关代码 24,。03.14 by lxs */
// static OpenLoadDiagVoltage_t OpenLoadDiagVoltage = {0};

static void Motor_WindmillInit(void);
static u16 Motor_EstimateStartAngle(void);
/* 声明函数 23.12.15 by lxs */
static void Motor_StartRoutine(void);
static void BemfComtrol_store(s16 *correction, s16 *data, s32 *correct, u16 *bv);
static void Motor_GenerateAndMeasureEstimatePulse(u16 half_duty, volatile u16 *first, volatile u16 *second,
                                                  volatile u16 *floating, u16 table);
#if BEMF_CONTROL_EN_DEMO_SHIFT_WAVE
static void demo_motor_shift_wave(void);
#endif
bool Motor_IsSpeedUp(void)
{
  /* polyspace-begin MISRA-C3:10.1 */
  /* polyspace-begin MISRA-C3:7.2 */
  return ((ABS(target.speed) > ABS(current.speed)) &&
          ((bool)(target.speed & 0x8000) == (bool)(current.speed & 0x8000)));
  /* polyspace-end MISRA-C3:7.2 */
  /* polyspace-end MISRA-C3:10.1 */
}

void Motor_SpeedRamp(u16 Acc)
{
  if (target.speed == current.speed)
  {
    return;
  }

  /********** SPEED_CONTROLLER **********/
  /* polyspace +2 MISRA-C3:10.1 */
  s32 add = (s32)Acc << (SCALE_INC - ACCELERATION_NGAIN);
  s32 target_speed_shifted = (s32)target.speed << SCALE_INC;

  bool smaler = (bool)(target_speed_shifted < current.speed_shifted);
  if (smaler)
  {
    add = -add;
  }
  current.speed_shifted += add;
  bool still_smaler = (bool)(target_speed_shifted < current.speed_shifted);

  // wait for controller to go into open loop
  /* polyspace +1 MISRA-C3:10.1 */
  s32 wait_here = ((s32)m.stop_control) << (SCALE_INC);

  if ((current.mode == mode_closed) &&
      ((target.speed < 0) && (current.speed_shifted > 0) && (current.speed_shifted < wait_here)))
  {
    current.speed_shifted = wait_here;
    current.speed = m.stop_control;
    waiting_for_controller++;
  }
  else if ((current.mode == mode_closed) &&
           ((target.speed > 0) && (current.speed_shifted < 0) && (current.speed_shifted > -wait_here)))
  {
    current.speed_shifted = -wait_here;
    current.speed = -(s16)m.stop_control;
    waiting_for_controller++;
  }
  // case target over-jumped = target reached
  else if (smaler != still_smaler)
  {
    current.speed_shifted = target_speed_shifted;
    current.speed = target.speed;
    waiting_for_controller = 0;
  }
  else
  {
    // case on acceleration
    /* polyspace +1 MISRA-C3:10.1 */
    current.speed = current.speed_shifted >> SCALE_INC;
    waiting_for_controller = 0;
  }

  // limit the target rotation rate to 112% to have faster response for deceleration
  if (current.mode == mode_closed)
  {
    /* polyspace +1 MISRA-C3:10.1 */
    current.speed = current.speed_shifted >> SCALE_INC;
  }

  if (current.speed == 0)
  {
    current.speed = 1;
  }
}

static void Motor_StartRoutine(void)
{
  // get position and config pre_pwm
  s16 StartAngle;
  s16 speed = DEFAULT_INC;
  s16 mult = U_F_Kennlinie(0, 0, true, true);

  enable_pwm(0x0); // to be shure to have not output yet
  SDK_MotorDrvOn();

  bool IsWindmillPresent = Motor_IsWindmillPresent();
/* demo自带相移函数，静止到开环使用，使用一次 2023.12.11 by lxs */
#if BEMF_CONTROL_EN_DEMO_SHIFT_WAVE
  s16 backup_shift_wave = shift_wave;
  shift_wave = 0;
  demo_motor_shift_wave();
#endif
   /* 提高直接进入闭环转速 23.02.23 by jxj */
   /* polyspace-begin MISRA-C3:10.1 */
   /* polyspace-begin MISRA-C3:7.2 */
/* 屏蔽正向有转速启动 23.12.29 by lxs */
#if BEMF_CONTROL_START_TO_CLOSE_EN
  if (((wm.velocity & 0x8000) ^ (target.speed & 0x8000)) || (ABS(wm.velocity) < 868 /*m.start_control*/))
  {
    MotorVar.StartToClose = 0;
  }
  else
  {
    MotorVar.StartToClose = 1;
  }
#endif
  /* polyspace-end MISRA-C3:7.2 */
  /* polyspace-end MISRA-C3:10.1 */
  /* 在定位启动中，将反转定位和静止定位分开，23.08.24 by lxs */
  if((MotorVar.StartToClose == 0)&&(MotorVar.WindMillingSpeed < BEMF_CONTROL_REVERSAL_TO_ALIAN_SPEED))
  {
    MotorVar.ReversalToOpen = 1;
  }
  else
  {
    MotorVar.ReversalToOpen = 0;
  }

  if (IsWindmillPresent && (MotorVar.StartToClose != 0u))
  {
    // stop list
    saradc_apply_list((saradc_table_list_entry *)NULL, true);
    ADCListDoneHandler2();

    // the values are calculated by the interrupt routine of the windmilling table
    // If this angle area is not detected and the windmill is gone the motor goes into standstill start
    // Note: If the uf curve is not well configured the motor will break or accelerate for the controller
    /* polyspace +1 DEFECT:SIGN_CHANGE  */ /* polyspace +1 MISRA-C3:10.1 */
    StartAngle = (s16)wm.theta + (wm.theta_diff_tp << 1u); // interpolate to the present
    if (wm.velocity > 0)
    {
      StartAngle -= DEG_TO_BP(WINDMILL_START_WITH_PHASE_RESERVE);
    }
    else
    {
      StartAngle += DEG_TO_BP(WINDMILL_START_WITH_PHASE_RESERVE);
    }

    StartAngle = Motor_BasePhaseLimit(StartAngle);
    speed = wm.velocity;

    /* 根据自转转速计算mult, 23.07.18 by lxs */
    s32 mult1 = ((s32)ABS((s32)speed) * BEMF_CONTROL_BEMF_COEF1 + BEMF_CONTROL_BEMF_COEF2) / GPIO_ADC_VBAT;
    
    if (speed < 0)
    {
      mult1 = -mult1;
    }

    if (ABS(mult1) > ABS((s32)mult))
    {
      mult = mult1;
    }

    if (MotorVar.ParamTuneEn == 0u)
    {
      m.pKi = 256;
      m.pKp = 3000;
      m.iKi = 3000;
      m.iKp = 500;
    }
  }
  else
  {
    if (MotorVar.ParamTuneEn == 0u)
    {
      m.pKi = 256;
      m.pKp = 3000;
      m.iKi = 2000;
      m.iKp = 200;
    }
    /* 反转定位时使用定角度定位，不使用估算角度 23.08.24 by lxs */
    if(MotorVar.ReversalToOpen == 1)
    {
      enable_startup_current = false;
    }
    else
    {
      enable_startup_current = true;
    }

    if (enable_startup_current == true)
    {
      StartAngle = Motor_EstimateStartAngle() + DEG_TO_BP(270);
      StartAngle = Motor_BasePhaseLimit(StartAngle);
    }
    else
    {
       StartAngle = DEG_TO_BP(80);
    }

    if (target.speed < 0)
    {
      speed = -speed;
      mult = -mult;
    }
  }

  inc_controller.param.Kp = m.pKp;
  inc_controller.param.Ki = m.pKi;
  mult_controller.param.Kp = m.iKp;
  mult_controller.param.Ki = m.iKi;

  pre_pwm_enable_inc(false);
  PRE_PWM_SET_BP(StartAngle);
  pre_pwm_set_sinc_smult_init(speed, mult, true, false);

  current.speed = speed;
  /* polyspace +1 MISRA-C3:10.1 */
  current.speed_shifted = (s32)current.speed << SCALE_INC;

  if (IsWindmillPresent)
  {
    wm.theta = StartAngle;
  }
/* demo自带相移函数，静止到开环使用，使用一次 2023.12.15  by lxs */
#if BEMF_CONTROL_EN_DEMO_SHIFT_WAVE
  // misalign the bp pointer
  shift_wave = backup_shift_wave;
  demo_motor_shift_wave();
#endif
  s8 start_window = divider_sdiv(PRE_PWM_GET_BP + DEG_TO_BP(30), DEG_TO_BP(60));
  start_window = start_window + 1;
  if (start_window < 0)
  {
    start_window += 6;
  }

  if (start_window > 5)
  {
    start_window -= 6;
  }
  /* polyspace+1 DEFECT:SIGN_CHANGE */
  saradc_window_control_V2_patch(start_window, 0);
  saradc_apply_list((saradc_table_list_entry *)list_bemf_start, true);
}

void Motor_ModeStateMachine(void)
{
  CLI();

  bemf_control_mode_t next_mode = current.mode;
  /* polyspace +1 MISRA-C3:10.1 */
  s16 inc_of_controller = (s16)(inc_controller.state.sum_error >> SCALE_INC);

  /*
  switch to openloop while ABS(inc_of_controller) <= 600rpm
  */
  bool for_to_rev =
    (bool)((inc_of_controller > 0) && (inc_of_controller <= 860) && (target.speed <= (s16)m.stop_control));
  bool rev_to_for =
    (bool)((inc_of_controller < 0) && (inc_of_controller >= (-860)) && (target.speed >= (-(s16)m.stop_control)));

  if (target.mode == mode_closed)
  {
    if ((current.mode == mode_idle) && (target.speed != 0))
    {
      next_mode = mode_open;
    }
	/* 消除polyspace警告 23.08.28 by lxs */
  /* 消除ployspace警告 2023.10.29 by lxs */
    else if ((current.mode == mode_open) && (MotorVar.CloseLoopEn != 0) &&
             (((target.speed >= 0) && (current.speed >= (s16)m.start_control)) ||
              ((target.speed <= 0) && (current.speed <= (-(s16)(m.start_control))))))
    {
      next_mode = mode_closed;
    }
    else if ((current.mode == mode_closed) && (for_to_rev || rev_to_for))
    {
      next_mode = mode_open; // closed -> open only on direction change
    }
    else if ((target.speed == 0) && (current.speed <= DEFAULT_INC) && (current.mode != mode_idle))
    {
      target.mode = mode_idle;
      next_mode = mode_idle;
    }
    /* 消除polyspace警告 2023.10.17 by lxs */
    else
    {
    }
  }
  else
  {
    next_mode = target.mode;
  }

  if ((current.mode == mode_idle) && (target.speed == 0))
  {
    next_mode = mode_idle;
    target.mode = mode_idle;
  }

  if (current.mode != next_mode)
  {
    Motor_ChangeModeTo(next_mode);
  }
  SEI();
}

void Motor_ChangeModeTo(bemf_control_mode_t next_mode)
{
  if (next_mode != mode_idle)
  {
    last_driver_error = DRIVER_OK;
  }
  /* polyspace-begin MISRA-C3:16.1 */
  switch (next_mode)
  {
  case mode_idle: {
    for (u16 *p = bemf_voltage[0]; p < &(bemf_voltage[1][BEMF_DATA_COUNT]); p++)
    {
      *p = 0xFFFFu;
    }

    pre_pwm_irq_handler_bp_0_enable(false);

    current.speed = DEFAULT_INC;
    /* 加强制类型转换，消除polyspace警告 2023.10.23 by lxs */
    /* polyspace +1 MISRA-C3:10.1 */
    current.speed_shifted = (s32)current.speed << SCALE_INC;
    pre_pwm_set_sinc_smult_init(DEFAULT_INC, DEFAULT_MULT, true, true);

    pre_pwm_control_on_duty(false, true);
    pre_pwm_set_smult(0);
    // switch all gates to high impedanz/floating
    REG_PWMN_IRQ_STATUS = BIT_PWMN_IRQ_STATUS_START_EVT;
    enable_pwm(0x00);
    wait_next_cycle();
    //@ 52&05 on for windmill detection
    SDK_MotorDrvLowPower();

    // reload to zero
    REG_PWMN_PWM0_C0_RELOAD = 0;
    REG_PWMN_PWM1_C0_RELOAD = 0;
    REG_PWMN_PWM2_C0_RELOAD = 0;

    bemf_control_reset(DEFAULT_INC, DEFAULT_MULT);

    /* 关闭相输出后再初始化自转检测，22.03.06 by yhd */
    Motor_WindmillInit();
/* 屏蔽demo自带的相移函数 23.12.15 by lxs */
#if BEMF_CONTROL_EN_DEMO_SHIFT_WAVE
    {
      MotorVar.AngleShift = 0;
      shift_wave = 0;
      demo_motor_shift_wave();
    }
#endif
  }
  break;
  /* polyspace-begin MISRA-C3:16.3 */
  case mode_open: {
    if (current.mode == mode_idle)
    {
      Motor_StartRoutine();
      pre_pwm_control(true); // Enable pwmn load on&duty from prepwm
      enable_pwm(0x3);       // HS&LS pwm signal enable
    }
    // back to open loop
    else if (current.mode == mode_closed)
    {
      s16 StartAngle = 0;
      s16 speed = DEFAULT_INC;
      s16 mult = U_F_Kennlinie(0, 0, true, true);

      MotorVar.StartToClose = 0;

      if (target.speed < 0)
      {
        speed = -speed;
        mult = -mult;
      }

      m.pKi = 256;
      m.pKp = 3000;
      m.iKi = 5000;
      m.iKp = 200;
      inc_controller.param.Kp = m.pKp;
      inc_controller.param.Ki = m.pKi;
      mult_controller.param.Kp = m.iKp;
      mult_controller.param.Ki = m.iKi;

      pre_pwm_enable_inc(false);
      PRE_PWM_SET_BP(StartAngle);
      pre_pwm_set_sinc_smult_init(speed, mult, true, false);

      current.speed = speed;
      /* polyspace +1 MISRA-C3:10.1 */
      current.speed_shifted = (s32)current.speed << SCALE_INC;

      s8 start_window = divider_sdiv(PRE_PWM_GET_BP + DEG_TO_BP(30), DEG_TO_BP(60));
      start_window = start_window + 1;
      if (start_window < 0)
      {
        start_window += 6;
      }

      if (start_window > 5)
      {
        start_window -= 6;
      }
      /* polyspace+1 DEFECT:SIGN_CHANGE */
      saradc_window_control_V2_patch(start_window, 0);
      saradc_apply_list((saradc_table_list_entry *)list_bemf_start, true);
    }
    else
    {
    }

    pre_pwm_enable_inc(true);
    waiting_for_controller = 0;
  }
    if (MotorVar.StartToClose == 0u)
    {
      break;
    }
    next_mode = mode_closed;
  /* polyspace-end MISRA-C3:16.3 */
  case mode_closed: {
    s16 smult;

    MotorVar.CloseLoopTime = 0;

    MotorVar.Voltage = GPIO_ADC_VBAT;

    if (MotorVar.StartToClose == 1)
    {
      MotorVar.VoltageCompensationEn = 0;

      bemf_control_reset(pre_pwm_get_sinc(), pre_pwm_get_smult()); // reset controller
      pi_controller_sum_init(&inc_controller, pre_pwm_get_sinc());
      pi_controller_sum_init(&mult_controller, pre_pwm_get_smult());
    }
    else
    {
      MotorVar.VoltageCompensationEn = 1;
      /* 开环切闭环时将过调制和电压补偿除回去，防止输出过大 23.12.15 by lxs */
      smult = (s16)((s32)(pre_pwm_get_smult()) * 1000 / MOTOR_API_OVER_MODULATION * (s32)MotorVar.Voltage / (s32)MOTOR_REF_VOLTAGE) ;
      
      bemf_control_reset(pre_pwm_get_sinc(), smult); // reset controller
      pi_controller_sum_init(&inc_controller, pre_pwm_get_sinc());
      pi_controller_sum_init(&mult_controller, smult);
    }

    /* 进入闭环时清零SectorCnt，22.03.06 by yhd */
    SectorCnt = 0u;
  }
  break;
  default:/* 消除polyspace警告 2023.10.29 by lxs */
    break;
  }
  /* polyspace-end MISRA-C3:16.1 */

  current.mode = next_mode;
}

s16 inc_controller_fun(s16 phase_diff)
{

  s16 new_inc;

  /********** PHASE_CONTROLLER **********/

  u16 divider = PRE_PWM_GET_ABS_INC;
  /* 消除polyspace警告 23.10.29 by lxs */
  /* polyspace +1 DEFECT:USELESS_IF */ /* polyspace +1 MISRA-C3:14.3 */
  if ((filter_bits & INC_CONTROLLER_DISABLE_TIME_BIT) != 0u)
  {
    divider = 0;
  }
  /* polyspace-begin DEFECT:DEAD_CODE */
  /* polyspace +1 MISRA-C3:2.1 */ /* polyspace +1 MISRA-C3:14.3 */
  if ((filter_bits & INC_CONTROLLER_MULTIPLY_TIME_BIT) != 0u)
  {
    divider = 0xFFFFu;
  }
  /* polyspace-end DEFECT:DEAD_CODE */
  /* polyspace +1 MISRA-C3:10.1 */
  new_inc = (pi_controller_call(&inc_controller, -phase_diff, divider)) >> SCALE_INC;
  // Attention no interrupts for bemf detection if inc = 0, because the waveform stops
  if (new_inc == 0)
  {
    new_inc = 1;
  }
  return new_inc;
}

/* 消除polyspace警告，修改形参名字 2023.10.29 by lxs */
s16 mult_controller_fun(u16 index_number, s16 new_inc, s16 phase_diff)
{
  static s32 diff_torque_rest = 0;
  s16 new_mult;

  /********** TORQUE_CONTROLLER **********/

  // percentage of speed error as input
  u16 divider = ABS(current.speed);

  // s32 diff_torque = (current.speed_shifted) - inc_controller.state.sum_error;
  s32 diff_torque = (current.speed_shifted) - (inc_controller.state.sum_error);
  /* polyspace-begin DEFECT:DEAD_CODE */
  /* polyspace +1 MISRA-C3:2.1 */ /* polyspace +1 MISRA-C3:14.3 */
  if ((filter_bits & MULT_CONTROLLER_DISABLE_PERCENT) != 0u)
  {
  }
  else
  {
    diff_torque = divider_sdiv(diff_torque + diff_torque_rest, divider);
    diff_torque_rest = divider_get_sdiv_remainder();
  }
  /* polyspace-end DEFECT:DEAD_CODE */

  if (diff_torque > INT16_MAX)
  {
    diff_torque = INT16_MAX;
  }
  if (diff_torque < INT16_MIN)
  {
    diff_torque = INT16_MIN;
  }
  /* 消除polyspace警告 23.10.29 by lxs */
  /* polyspace-begin DEFECT:DEAD_CODE */
  /* polyspace +1 MISRA-C3:2.1 */ /* polyspace +1 MISRA-C3:14.3 */
  if ((filter_bits & MULT_CONTROLLER_DISABLE_TIME_BIT) != 0u)
  {
    divider = 0;
  }
  else
  {
    divider = PRE_PWM_GET_ABS_INC;
  }
  /* polyspace-end DEFECT:DEAD_CODE */
  /* polyspace +1 MISRA-C3:10.1 */
  new_mult = ((pi_controller_call(&mult_controller, diff_torque, divider)) >> SCALE_MULT);

  if (mult_controller.param.Ki == 0 && mult_controller.param.Kp == 0)
  {
  }
  else
  {

    bool reinit = false;

    // operation only as motor
    s16 used_min_mult = m.uf_offset;
    /* 消除polyspace警告 23.10.17 by lxs */
    if (m.uf_min != 0u)
    {
      used_min_mult = m.uf_min;
    }

    // Handles bad configuration or additional wind
    /* 消除polyspace警告 23.10.17 by lxs */
    if (waiting_for_controller != 0u)
    {
      if (waiting_for_controller > used_min_mult)
      {
        used_min_mult = 0;
        waiting_for_controller = used_min_mult;
      }
      else
      {
        used_min_mult = used_min_mult - waiting_for_controller;
      }
    }

    s16 vbat_maximal_multiplier = get_vbat_maximal_multiplier();

    // maximal
    if (new_mult > vbat_maximal_multiplier)
    {
      new_mult = vbat_maximal_multiplier;
      reinit = true;
    }
    if (new_mult < -vbat_maximal_multiplier)
    {
      new_mult = -vbat_maximal_multiplier;
      reinit = true;
    }

    // minimal
    if (new_inc > 0)
    {
      if (new_mult < used_min_mult)
      {
        new_mult = used_min_mult;
        reinit = true;
      }
    }
    else
    {
      if (new_mult > -used_min_mult)
      {
        new_mult = -used_min_mult;
        reinit = true;
      }
    }

    if (reinit == true)
    {
      pi_controller_sum_init(&mult_controller, new_mult);
    }
  }
  return new_mult;
}

/* 消除polyspace警告，修改形参名字 2023.10.29  by lxs*/
void bemf_control_call(s16 phase_diff, u8 index_number)
{
  MotorVar.Voltage = GPIO_ADC_VBAT;
  if (MotorVar.Voltage < BEMF_CONTROL_VBAT_COMP_MIN)
  {
    MotorVar.Voltage = BEMF_CONTROL_VBAT_COMP_MIN;
  }
  MotorVar.PhaseDiff = phase_diff;
/* 24V风扇在特定转速或时间切相位环kpki。暂时保留，后续无用可删除 24.01.05 by lxs */
# if 0
  if ((MotorVar.CloseLoopTime > 5000) || (ABS(MotorVar.CurrentSpeed) > 2300))
  {
    if (!MotorVar.ParamTuneEn)
    {
      inc_controller.param.Kp = 3000;
      inc_controller.param.Ki = 200;
    }
  }
#endif

  if (MotorVar.StartToClose != 0u)
  {
    if ((MotorVar.CloseLoopTime >= 3000) || (ABS(MotorVar.CurrentSpeed) > 2000))
    {
      if (MotorVar.VoltageCompensationEn == 0u)
      {
        if (MotorVar.VolatgeCompEn != 0u)
        {
          MotorVar.VoltageCompensationEn = 1;
        }
        MOTOR_REF_VOLTAGE = MotorVar.Voltage;
      }
    }
    else
    {
      MotorVar.VoltageCompensationEn = 0;
    }
  }

  FilteredBat = MotorVar.Voltage;

  if (MotorVar.VoltageCompensationEn != 0u)
  {
    /* polyspace-begin MISRA-C3:10.1 */
    mult_controller.param.max =
      (((s32)PI_CONTROLLER_MAX_MULT * (s32)FilteredBat / (s32)MOTOR_REF_VOLTAGE) << SCALE_MULT);
    /* polyspace-end MISRA-C3:10.1 */ 
    mult_controller.param.min = -mult_controller.param.max;
    driver_maximal_multiplier = (s32)PI_CONTROLLER_MAX_MULT * (s32)FilteredBat / (s32)MOTOR_REF_VOLTAGE;
  }

  #if 0
  /* 消除polyspace警告 2023.10.18 by lxs */
  if (MotorVar.ParamTuneEn == 0u)
  {
    static bool flag = 0;

    if (ADCResults.Voltage.Bat > 260)
    {
      flag = 1;
    }
    else if (ADCResults.Voltage.Bat < 250)
    {
      flag = 0;
    }
    else
    {
    }

    DebugVar.PhaseDiffOffset = (ABS(ADCResults.Current.DC) * 32) / (flag ? 6 : 9);
    /* 刘贺刘工关于解决水泵不同负载失步的临时参考代码，暂时保留 24.01.05 by lxs  */
    // dcvoltagttmp = ADCResults.Voltage.Bat;
    // dcvoltagttmp = dcvoltagttmp < 200? 200: dcvoltagttmp;
    // dcvoltagttmp = dcvoltagttmp > 400? 400: dcvoltagttmp;
    // DebugVar.PhaseDiffOffset = DebugVar.PhaseDiffOffset * ADCResults.Voltage.Bat/240;
  }
  #else
    /* 修改超前角参数 24.03.12 by lxs */
    DebugVar.PhaseDiffOffset = (ABS(ADCResults.Current.DC) * BEMF_CONTROL_PHASEDIFFOFFSET_COFE1) / BEMF_CONTROL_PHASEDIFFOFFSET_COFE2;
    DebugVar.PhaseDiffOffset = (s16)((s32)DebugVar.PhaseDiffOffset * (s32)FilteredBat / (s32)MOTOR_REF_VOLTAGE);
  #endif

  /* 不使用前BEMF_CONTROL_SECTOR_CNT_MIN个sector计算的diff，避免刚切入闭环时不稳定，22.03.06 by yhd */
  if (SectorCnt < BEMF_CONTROL_SECTOR_CNT_MIN)
  {
    SectorCnt++;

    phase_diff = 0;
    DebugVar.PhaseDiffOffset = 0;
  }

  s16 new_inc = inc_controller_fun(phase_diff + DebugVar.PhaseDiffOffset);
  /* 修改polyspace警告，修改形参名字 23.10.29 by lxs */
  s16 new_mult = mult_controller_fun(index_number, new_inc, phase_diff);

  MotorVar.PwmMult = new_mult;

  if (MotorVar.VoltageCompensationEn != 0u)
  {
    new_mult = (s16)((s32)new_mult * (s32)MOTOR_REF_VOLTAGE / (s32)FilteredBat);

    /* Max over modulation limit */
	  /* 减小输出限制,防止电压跳变时电流过大 23.12.16 by lxs */
    static s16 mult_max = 1200;

    if (new_mult > mult_max)
    {
      new_mult = mult_max;
    }
    else if (new_mult < -mult_max)
    {
      new_mult = -mult_max;
    }
    else
    {
    }
  }

  MotorVar.PwmMultComp = new_mult;

  MotorVar.NewInc = new_inc;

  s16 stop_rotrate_max = m.max_rot;
  /* polyspace +1 MISRA-C3:10.1 */
  stop_rotrate_max = stop_rotrate_max + (stop_rotrate_max >> 1u);

  if (new_inc < -stop_rotrate_max || new_inc > stop_rotrate_max)
  {
    // speed out of bounds
    MotorVar.Fault.bits.SpeedOutRangeInc = true;
  }
  else
  {
    if (bemf_control_get_mode() == mode_closed)
    {
      SCIDebug.Motor.OverModulateK = MotorVar.OverModulateK;
    }
    else
    {
      SCIDebug.Motor.OverModulateK = 1000;
    }

    pre_pwm_set_sinc_smult_init(new_inc, new_mult, false, false);
/* 屏蔽demo自带的相移函数 23.12.15 by lxs */
#if BEMF_CONTROL_EN_DEMO_SHIFT_WAVE
    shift_wave = MotorVar.AngleShift;
    demo_motor_shift_wave();
#endif
  }

  Motor_ModeStateMachine();
}

void bemf_control_reset(s16 inc, s16 mult)
{
  pi_controller_reset(&inc_controller);
  pi_controller_reset(&mult_controller);
}

void Motor_SetTargetMode(bemf_control_mode_t new_mode)
{
  target.mode = new_mode;
  Motor_ModeStateMachine();
}

bemf_control_mode_t bemf_control_get_mode(void)
{
  return current.mode;
}

void Motor_BreakEnable(bool enable)
{
  if (enable)
  {
    u16 half_duty = REG_PWMN_CNT_MAX_RELOAD >> 1;
    REG_PWMN_PWM0_C0_RELOAD = half_duty;
    REG_PWMN_PWM1_C0_RELOAD = half_duty;
    REG_PWMN_PWM2_C0_RELOAD = half_duty;
    wait_next_cycle();
    SDK_MotorDrvOn(); // driver on
    wait_next_cycle();
    enable_pwm(0x03); // output pwm on
  }
  else
  {
    SDK_MotorDrvOff(); // driver off
    enable_pwm(0x00);  // output pwm off
  }
}
/* 屏蔽demo自带的相移函数 23.12.15 by lxs */
#if BEMF_CONTROL_EN_DEMO_SHIFT_WAVE
// only for tuning and should be replaced if MOTCUV2
// this is hacked don't use this in runtime
static void demo_motor_shift_wave(void)
{
  if (shift_wave_last_val == shift_wave)
  {
    return;
  }

  CLI();
  pre_pwm_enable_inc(false);
  u16 bp = PRE_PWM_GET_BP;
  PRE_PWM_SET_BP(Motor_BasePhaseLimit(bp + shift_wave - shift_wave_last_val));
  pre_pwm_enable_inc(true);
  shift_wave_last_val = shift_wave;
  SEI();
}
#endif
static void Motor_GenerateAndMeasureEstimatePulse(u16 half_duty, volatile u16 *first, volatile u16 *second,
                                           volatile u16 *floating, u16 table)
{
  u8 cnt = 0;

  wait_next_cycle();
  /* polyspace +1 MISRA-C3:11.6 */
  if ((void *)table != NULL)
  {
    REG_SARADC_CTRL_SADR_NEW = table;
  };

  *first = 0xFFFFu;
  *second = 0;
  *floating = 0;
  wait_next_cycle();

  /*
    STARTUP_SAMPLES_1 = 1
  */
  for (cnt = 0; cnt < STARTUP_SAMPLES_1; ++cnt)
  {
    *first = 0;
    *second = 0xFFFFu;
    wait_next_cycle();
    wait_next_cycle();
    *first = 0xFFFFu;
    *second = 0x0;
    wait_next_cycle();
    wait_next_cycle();
  }

  *first = 0;
  *second = 0xFFFFu;
  wait_next_cycle();

  *first = half_duty;
  *second = half_duty;
  *floating = 3;
  wait_next_cycle();
}

static void BemfComtrol_store(s16 *correction, s16 *data, s32 *correct, u16 *bv)
{
  for (u8 i = STARTUP_DATA_START; i < STARTUP_SAMPLES_1; ++i)
  {
    correction[0] += +(s16)bv[(4 * i) + 1] - (s16)bv[(4 * i) + 0] + (s16)bv[(4 * i) + 3] - (s16)bv[(4 * i) + 2];

    correct[0] += (s32)bv[(4 * i) + 2] + (s32)bv[(4 * i) + 3];
    correct[1] += (s32)bv[(4 * i) + 0] + (s32)bv[(4 * i) + 1];
  }
}

bool Motor_StillStateDiag(void)
{
  bool IsOpenLoad = false;
  bool IsShort = false;
  bool IsShortGND = false;
  bool IsShortBAT = false;
  /*
  Short Diag
  */
  /*短地*/
  if ((ADCResults.Voltage.PhaseU < BEMF_CONTROL_DIFF_SHORT) || (ADCResults.Voltage.PhaseV < BEMF_CONTROL_DIFF_SHORT) ||
      (ADCResults.Voltage.PhaseW < BEMF_CONTROL_DIFF_SHORT))
  {
    IsShortGND = true;
    MotorVar.FaultRecord |= MOTOR_API_FAULT_RECORD_MSK_SHORT_GND_HEX;
  }
  else if ((ADCResults.Voltage.PhaseU > ADCResults.Voltage.Bat - BEMF_CONTROL_DIFF_SHORT) ||
           (ADCResults.Voltage.PhaseV > ADCResults.Voltage.Bat - BEMF_CONTROL_DIFF_SHORT) ||
           (ADCResults.Voltage.PhaseW > ADCResults.Voltage.Bat - BEMF_CONTROL_DIFF_SHORT))
  {
    IsShortBAT = true;
    MotorVar.FaultRecord |= MOTOR_API_FAULT_RECORD_MSK_SHORT_BAT_HEX;
  }
  else
  {
  }
  if (IsShortGND || IsShortBAT)
  {
    IsShort = true;
  }
/* 屏蔽开路诊断相关代码 24.03.14 by lxs */
#if 0
  /*
  OpenLoad Diag
  */
  if (!IsShort)
  {
    u16 count_max_backup = READ_REG_U16(AADDR_PWMN_CNT_MAX_RELOAD);
    s16 old_inc = pre_pwm_get_sinc();
    s16 old_mult = pre_pwm_get_smult();
	  /* 开路诊断使用软件除法器 23.12.11 by lxs */
    /* polyspace +2 MISRA-C3:10.8 */
    s16 set_inc_as_timer = divider_udiv_soft(
      ((u32)STARTUP_BOOTSTRAP_LOAD * (u32)PRE_PWM_GET_ABS_INC) + (u32)(count_max_backup >> 1), count_max_backup);
    if (old_inc < 0)
    {
      set_inc_as_timer = -set_inc_as_timer;
    }

    // safe init process
    pre_pwm_control(false); // pre_pwm off
    pre_pwm_enable_dma(false);
    pre_pwm_enable_inc(false);
    Motor_BreakEnable(true);

    saradc_apply_list((saradc_table_list_entry *)NULL, true);

    // dont change direction to save time, from mult is only the sign important
    // the pre_pwm is used as timer after each pwm a new hbridge state is set
    pre_pwm_set_sinc_smult_init(set_inc_as_timer, set_inc_as_timer, false, true); // default

    WRITE_REG_16(AADDR_PWMN_CNT_MAX_RELOAD, C_PWM_CNT_MAX);
    /* 三相开启下mos，输出低电平给自举电容充电 24.03.13 by lxs */
    REG_PWMN_PWM0_C0_RELOAD = 0x0;
    REG_PWMN_PWM1_C0_RELOAD = 0x0;
    REG_PWMN_PWM2_C0_RELOAD = 0x0;
    WRITE_REG_16(AADDR_PWMN_PWM0_ON_RELOAD, 3);
    WRITE_REG_16(AADDR_PWMN_PWM1_ON_RELOAD, 3);
    WRITE_REG_16(AADDR_PWMN_PWM2_ON_RELOAD, 3);

    Time.PwmOutLowFlag = 1;
    while(Time.PwmOutLowCnt < 10)
    {

    }
    Time.PwmOutLowFlag = 0;
    /* 关闭三相输出 24.03.13 by lxs*/
    WRITE_REG_16(AADDR_PWMN_PWM0_ON_RELOAD, 0);
    WRITE_REG_16(AADDR_PWMN_PWM1_ON_RELOAD, 0);
    WRITE_REG_16(AADDR_PWMN_PWM2_ON_RELOAD, 0);

    WRITE_REG_16(AADDR_PWMN_CNT_MAX_RELOAD, C_PWM_CNT_MAX);

    REG_PWMN_PWM0_C0_RELOAD = C_PWM_CNT_MAX >> 1;
    REG_PWMN_PWM1_C0_RELOAD = C_PWM_CNT_MAX >> 1;
    REG_PWMN_PWM2_C0_RELOAD = C_PWM_CNT_MAX >> 1;

    WRITE_REG_16(AADDR_PWMN_PWM0_ON_RELOAD, 3);
    WRITE_REG_16(AADDR_PWMN_PWM1_ON_RELOAD, 0);
    WRITE_REG_16(AADDR_PWMN_PWM2_ON_RELOAD, 0);
    Time.PwmOutLowFlag1 = 1;
    while(Time.PwmOutLowCnt1 < 2)
    {

    }
    Time.PwmOutLowFlag1 = 0;
    wait_next_cycle();

    // safe measurement process
    CLI();

    // REG_PWMN_IRQ_STATUS = BIT_PWMN_IRQ_STATUS_START_EVT;
    // wait_next_cycle();
    REG_SARADC_CTRL_SADR_NEW = (u16)ListOpenLaodDiag | 0x0001u;
    /* polyspace +1 MISRA-C3:11.6 */
    while ((ListOpenLaodDiag != (void *)READ_REG_U16(AADDR_SARADC_CTRL_SADR_DONE)))
    {
    };

    OpenLoadDiagVoltage.Sup = GPIO_ADC_VBAT_IDLE;
    OpenLoadDiagVoltage.U_H = GPIO_WINDMILL_U;
    OpenLoadDiagVoltage.U_L = GPIO_WINDMILL_U2;
    OpenLoadDiagVoltage.V = GPIO_WINDMILL_V;
    OpenLoadDiagVoltage.W = GPIO_WINDMILL_W;

    SEI();

    // End
    WRITE_REG_16(AADDR_PWMN_CNT_MAX_RELOAD, count_max_backup);
    REG_PWMN_PWM0_C0_RELOAD = 0x0;
    REG_PWMN_PWM1_C0_RELOAD = 0x0;
    REG_PWMN_PWM2_C0_RELOAD = 0x0;

    pre_pwm_set_sinc_smult_init(DEFAULT_INC, DEFAULT_MULT, true, true);

    pre_pwm_control_on_duty(false, true);
    pre_pwm_set_smult(0);
    // switch all gates to high impedanz/floating
    REG_PWMN_IRQ_STATUS = BIT_PWMN_IRQ_STATUS_START_EVT;
    enable_pwm(0x00);
    wait_next_cycle();
#if 1 /* 该部分偶发过误报短路，第一次上电时，诊断使用的电压全部采错 23.11.09 by lxs */
    if ((OpenLoadDiagVoltage.U_H + OPEN_LOAD_DIAG_VOLTAGE_DIFF_MAX < OpenLoadDiagVoltage.Sup) ||
        (OpenLoadDiagVoltage.U_L > OPEN_LOAD_DIAG_VOLTAGE_DIFF_MAX))
    {
      IsShort = true;
    }
    else
    {
      if ((OpenLoadDiagVoltage.V + OPEN_LOAD_DIAG_VOLTAGE_DIFF_MAX < OpenLoadDiagVoltage.U_H) ||
          (OpenLoadDiagVoltage.U_H + OPEN_LOAD_DIAG_VOLTAGE_DIFF_MAX < OpenLoadDiagVoltage.V))
      {
        IsOpenLoad = true;
      }

      if ((OpenLoadDiagVoltage.W + OPEN_LOAD_DIAG_VOLTAGE_DIFF_MAX < OpenLoadDiagVoltage.U_H) ||
          (OpenLoadDiagVoltage.U_H + OPEN_LOAD_DIAG_VOLTAGE_DIFF_MAX < OpenLoadDiagVoltage.W))
      {
        IsOpenLoad = true;
      }
    }
#else
    if ((OpenLoadDiagVoltage.V + OPEN_LOAD_DIAG_VOLTAGE_DIFF_MAX < OpenLoadDiagVoltage.U_H) ||
    (OpenLoadDiagVoltage.U_H + OPEN_LOAD_DIAG_VOLTAGE_DIFF_MAX < OpenLoadDiagVoltage.V))
    {
      IsOpenLoad = true;
    }

    if ((OpenLoadDiagVoltage.W + OPEN_LOAD_DIAG_VOLTAGE_DIFF_MAX < OpenLoadDiagVoltage.U_H) ||
    (OpenLoadDiagVoltage.U_H + OPEN_LOAD_DIAG_VOLTAGE_DIFF_MAX < OpenLoadDiagVoltage.W))
    {
      IsOpenLoad = true;
    }
#endif

    MotorVar.Fault.bits.OpenLoad = IsOpenLoad;

    if (MotorVar.Fault.bits.OpenLoad != 0u)
    {
      for (u16 *p = bemf_voltage[0]; p < &(bemf_voltage[1][BEMF_DATA_COUNT]); p++)
      {
        *p = 0xFFFFu;
      }

      Motor_WindmillInit();
    }
  }
#endif

  MotorVar.Fault.bits.Short = IsShort;

  return (IsOpenLoad || IsShort);
}

static u16 Motor_EstimateStartAngle(void)
{
  s16 correction[3];
  s16 data[6];
  s32 correct[6];
  s32 overflow_decision = 0;
  u16 theta_reactance_corrected;
  s32 d_new[3];

  u16 count_max_backup = READ_REG_U16(AADDR_PWMN_CNT_MAX_RELOAD);
  s16 old_inc = pre_pwm_get_sinc();
  s16 old_mult = pre_pwm_get_smult();

  /*
  set_inc_as_timer = (2400*inc + cnt_max/2)/cnt_max
  */
  /* polyspace-begin MISRA-C3:10.8 */
  s16 set_inc_as_timer = divider_udiv(
    ((u32)STARTUP_BOOTSTRAP_LOAD * (u32)PRE_PWM_GET_ABS_INC) + (u32)(count_max_backup >> 1), count_max_backup);
  /* polyspace-end MISRA-C3:10.8 */
  if (old_inc < 0)
  {
    set_inc_as_timer = -set_inc_as_timer;
  }

  // safe init process
  pre_pwm_control(false); // pre_pwm off
  pre_pwm_enable_dma(false);
  pre_pwm_enable_inc(false);
  Motor_BreakEnable(true);

  saradc_apply_list((saradc_table_list_entry *)NULL, true);

  // dont change direction to save time, from mult is only the sign important
  // the pre_pwm is used as timer after each pwm a new hbridge state is set
  pre_pwm_set_sinc_smult_init(set_inc_as_timer, set_inc_as_timer, false, true); // default

  for (u8 i = 0; i < 3; ++i)
  {
    correction[i] = 0;
    correct[i * 2] = 0;
    correct[i * 2 + 1] = 0;
  }

  /*
   voltage_devider_time = STARTUP_DURATION = 1920,  Period = 80us
   30*STARTUP_EXTEND_BOOTSTRAP = 30
   Break duration = 30 * 80 us = 2400us
  */
  WRITE_REG_16(AADDR_PWMN_CNT_MAX_RELOAD, voltage_devider_time);
  REG_PWMN_PWM0_C0_RELOAD = voltage_devider_time >> 1;
  REG_PWMN_PWM1_C0_RELOAD = voltage_devider_time >> 1;
  REG_PWMN_PWM2_C0_RELOAD = voltage_devider_time >> 1;

  for (u32 var = 0; var < (30 * STARTUP_EXTEND_BOOTSTRAP) && enable_startup_current; ++var)
  {
    wait_next_cycle();
  }

  // safe measurement process
  CLI();
  // A-B
  REG_PWMN_IRQ_STATUS = BIT_PWMN_IRQ_STATUS_START_EVT;
  wait_next_cycle();
  REG_PWMN_IRQ_STATUS = BIT_PWMN_IRQ_STATUS_START_EVT;
  // REG_SARADC_CTRL_TADR = ESTIMATION_ADDRESS_0; Dont do this
  Motor_GenerateAndMeasureEstimatePulse(voltage_devider_time >> 1, (u16 *)AADDR_PWMN_PWM0_C0_RELOAD,
                                        (u16 *)AADDR_PWMN_PWM1_C0_RELOAD, (u16 *)AADDR_PWMN_PWM2_ON_RELOAD,
                                        (u16)list_estimation_1 | 0x0001u);
  /* polyspace +1 MISRA-C3:11.6 */                                       
  while ((list_estimation_1_2 != (void *)READ_REG_U16(AADDR_SARADC_CTRL_SADR_DONE)))
  {
  };

  // B-C
  Motor_GenerateAndMeasureEstimatePulse(voltage_devider_time >> 1, (u16 *)AADDR_PWMN_PWM1_C0_RELOAD,
                                        (u16 *)AADDR_PWMN_PWM2_C0_RELOAD, (u16 *)AADDR_PWMN_PWM0_ON_RELOAD,
                                        (u16)list_estimation_2 | 0x0001u);
  /* polyspace +1 MISRA-C3:11.6 */                                        
  while ((list_estimation_2_2 != (void *)READ_REG_U16(AADDR_SARADC_CTRL_SADR_DONE)))
  {
  };

  // C-A
  Motor_GenerateAndMeasureEstimatePulse(voltage_devider_time >> 1, (u16 *)AADDR_PWMN_PWM2_C0_RELOAD,
                                        (u16 *)AADDR_PWMN_PWM0_C0_RELOAD, (u16 *)AADDR_PWMN_PWM1_ON_RELOAD,
                                        (u16)list_estimation_3 | 0x0001u);
  /* polyspace +1 MISRA-C3:11.6 */
  while ((list_estimation_3_2 != (void *)READ_REG_U16(AADDR_SARADC_CTRL_SADR_DONE)))
  {
  };

  SEI();

  // skip tadr base phase dataset
  BemfComtrol_store(&correction[0], &data[0], &correct[0], (u16 *)(ESTIMATION_ADDRESS_0 + 2));
  BemfComtrol_store(&correction[1], &data[2], &correct[2], (u16 *)(ESTIMATION_ADDRESS_1 + 2));
  BemfComtrol_store(&correction[2], &data[4], &correct[4], (u16 *)(ESTIMATION_ADDRESS_2 + 2));

  // End
  WRITE_REG_16(AADDR_PWMN_CNT_MAX_RELOAD, count_max_backup);
  REG_PWMN_PWM0_C0_RELOAD = 0x0;
  REG_PWMN_PWM1_C0_RELOAD = 0x0;
  REG_PWMN_PWM2_C0_RELOAD = 0x0;

  pre_pwm_enable_inc(true);
  pre_pwm_enable_dma(true);

  // calc
  d_new[0] = correct[0] + correct[5] - correct[1] - correct[4];
  d_new[1] = correct[2] + correct[1] - correct[3] - correct[0];
  d_new[2] = correct[4] + correct[3] - correct[5] - correct[2];

  theta_reactance_corrected = ABS((s16)(Motor_BasePhaseLimit(BP_MAX - (s16)(uvw_theta(d_new[2], d_new[0], d_new[1])))));

  if (theta_reactance_corrected < DEG_TO_BP(90))
  {
    overflow_decision += (s32)correction[0];
  }
  else
  {
    overflow_decision -= (s32)correction[0];
  }

  if (theta_reactance_corrected < DEG_TO_BP(210))
  {
    overflow_decision -= (s32)correction[1];
  }
  else
  {
    overflow_decision += (s32)correction[1];
  }

  if (theta_reactance_corrected < DEG_TO_BP(330))
  {
    overflow_decision += (s32)correction[2];
  }
  else
  {
    overflow_decision -= (s32)correction[2];
  }

  // if sync decision is inverted
  if (overflow_decision > 0)
  {
    theta_reactance_corrected += BP_MAX;
  }
  theta_reactance_corrected = theta_reactance_corrected >> 1;

  return theta_reactance_corrected;
}

static void Motor_WindmillInit(void)
{
  if (pre_pwm_get_sinc() < 0)
  {
    /* polyspace +1 MISRA-C3:10.1 */
    wm.direction = INT16_MIN >> 1u;
  }
  else
  {
    /* polyspace +1 MISRA-C3:10.1 */
    wm.direction = INT16_MAX >> 1u;
  }

  wm.velocity = pre_pwm_get_sinc();
  wm.theta_diff_tp = INC_PER_20PWMS_TO_DBP(wm.velocity);
  wm.samples = 0;

  /* Reset last theta */
  wm.theta = INVALID;
  wm.last_theta = INVALID;
  wm.theta_diff = INVALID;
  wm.last_bp_error = INVALID;
  /* polyspace +1 MISRA-C3:11.8 */
  saradc_apply_list((saradc_table_list_entry *)list_windmill, true);
}

bool Motor_IsWindmillPresent(void)
{
  /* polyspace +1 MISRA-C3:10.1 */
  return (bool)((ABS(wm.direction)) > (BP_MAX << 2u));
}
