#include "MotorAPI.h"
#include "VBatMonitor.h"
#include "bemf_control.h"
#include "commons.h"
#include "debug.h"
#include "main.h"
#include "motor.h"
#include "testmode.h"
/* 改变电机转动方向 23.12.15 by lxs */
#define MOTOR_POS_ROTATION_DIRECTION 1 //-1 ro 1

#define PWM_CNT_MODE_SAWTOOTH 0
#define PWM_CNT_MODE_INV_SAWTOOTH 1
#define PWM_CNT_MODE_TRIANGLE 2
#define PWM_CNT_MODE_INV_TRIANGLE 3

#define DT_MODE_RISING_ONLY 0
#define DT_MODE_RISING_AND_FALING 1

#define TALBLE_SELECT 0
#define START_POSITION_U 0

#define WM_APM_MIN 100

/* 顺风启动最小转速差,22.03.06 by yhd*/
#define MOTOR_API_REF_ACT_SPEED_DIFF_MIN (50)

#define MOTOR_API_LOCK_WM_SPEED_TH (800)

/* BEMF诊断宏定义,22.03.06 by yhd*/
#define MOTOR_API_TIME_BASE (10u) // Unit:ms
#define MOTOR_API_DIAG_BEMF_COEF1 (354)
#define MOTOR_API_DIAG_BEMF_COEF2 (9041)
#define MOTOR_API_DIAG_BEMF_COEF3 1 / 2
#define MOTOR_API_DIAG_BEMF_TIME_TH (3000u) // Unit:ms

/* 软件上的112代表实际的116 23.12.21 by lxs */
#define MOTOR_API_MAX_CURRENT_0P1_A (112) // Unit:0.1A
#define MOTOR_API_CURRENT_LIMIT_START_TH ((MOTOR_API_MAX_CURRENT_0P1_A)-30)
/*此处修改限流的kpki，上下限用于快速反应变化。 23.06.28 by lxs */
#define MOTOR_API_OC_SPD_I_OUT_MAX (60)
#define MOTOR_API_OC_SPD_KP (2)
#define MOTOR_API_OC_SPD_KI (10)

#define MOTOR_API_OC_SPD_I_OUT_MAX_MAX (1200)
#define MOTOR_API_LIMIT_CURRENT_ERROR (10)
/* 转速限电流延时 23.08.28 by lxs */
#define MOTOR_API_OC_RECOVER_DELAY_TH (10u)
/* 根据电流限转速最大转速阈值 23.12.15 by lxs */
#define MOTOR_API_MAX_SPEED_RPM (5000)
/* 过流阈值 23.08.28 by lxs */
#define MOTOR_API_SHUNT_CURRENT_OC_TH (300)
/* 过流诊断时间 1s*/
#define MOTOR_API_OVER_CURRENT_DIAGNOSE_TIME (100)
/* 桥区故障诊断次数阈值 23.08.28 by lxs */
#define MOTOR_API_DRV_ERR_CNT_TH (3)
/* 堵转恢复停止时间 23.08.28 by lxs */
#define MOTOR_API_LOCK_FAST_RECOVER_TIME_TH (5000)
/* 定位时间为1s 24.01.05 by lxs*/
#define MOTOR_API_ALIAN_TIME (1000U)
#define MOTOR_API_OPENLOOP_SWITCH_ACC_SPEED (20) // 开环内切换加速度的转速
/* 开环内20rpm以内使用的加速度 24.01.05 by lxs */
#define MOTOR_API_OPENLOOP_ACC_MIN (70)
/* 干运行诊断电流阈值 23.09.08 by lxs */
#define MOTOR_API_DRY_RUNNING_CURRENT_TH (15)
/* 干运行诊断时间相关参数 24.01.05 by lxs */
#define MOTOR_API_DRY_RUNNNG_HIGH_FILTER_TIME (4000)
#define MOTOR_API_DRY_RUNNNG_LOW_FILTER_TIME (4000)
#define MOTOR_API_DRY_RUNNNG_TEST_TIME ((u32)15*(u32)60*(u32)1000)
/*ms失步诊断阈值*/
#define MOTOR_API_LOSE_STEP_TIME_THR (20000u)
/*rpm转速过高*/
#define MOTOR_API_SPEED_TOO_HIGH_THR (6000u)
/*ms超速或低速诊断阈值*/
#define MOTOR_API_SPEED_TOO_LOW_OR_HIGH_TIME_THR (10000u)
/*ms堵转诊断结束时间*/
#define MOTOR_API_DIAG_LOCK_CLOSE_LOOP_TIME_THR (60000u)
/*将所有结构体变量初始化 2023.10.29 by lxs */
MotorVar_t MotorVar = {0};

struct windmill_t wm;

volatile driver_error_t driver_status = DRIVER_OK;
volatile driver_error_t last_driver_error = DRIVER_OK;
bldc_mode_t bldc_mode = sinus_no_float;
s16 driver_maximal_multiplier = PI_CONTROLLER_MAX_MULT;

static void Motor_HardWareInit(void);
static void Motor_SoftWareInit(void);
static void Motor_BLDCModeInit(void);
static s16 Motor_TargetSpeedTrimedByWindMilling(s16 WindMillingSpeed, s16 TargetSpeed);
/* 添加限制最大母线电流功能，23.06.28 by lxs */
static s16 Motor_TargetSpeedTrimedByShuntCurrent(s16 ShuntCurrent, s16 TargetSpeed, s16 CurrentSpeed);
static s16 Motor_Rpm2Inc(s16 Rpm);
static u16 Motor_CaculateSpeedRampAcc(void);
static void Motor_StopStateDiag(void);
static void Motor_UpdateSpeed(void);
static s16 Motor_Inc2Rpm(s16 Inc);
static void Motor_OverModulate(void);
static void Motor_LockMonitor(void);
static void Motor_ModeTimeCnt(void);
static void Motor_StopHook(void);
static void Motor_CloseLoopHook(void);
static void Motor_diagBemf(void);
static void Motor_SpeedMonitor(void);
static void Motor_CurrentMonitor(void);
/* 干运行状态监控函数声明 23.09.11 by lxs */
static void MotorAPI_MotorDryRunningMonitor(void);

void Motor_Init(void)
{
  Motor_HardWareInit();
  Motor_SoftWareInit();
}

static void Motor_HardWareInit(void)
{
  bool swap_uv = true;
  u16 wave_offset_0 = 0;
  u16 wave_offset_1 = 0;
  pre_pwm_bp_max_t bp_max = 0; // automatic set
  pre_pwm_table_entry *table_entry_array;

  pwm_init(PWM_CNT_MODE_INV_TRIANGLE, DT_MODE_RISING_ONLY, DRIVER_PWM_DEADTIME);
  pre_pwm_init();
  pre_pwm_config_offline(true, &bp_max, &wave_offset_0, &wave_offset_1, DRIVER_PWM_DEADTIME, TALBLE_SELECT,
                         &table_entry_array, START_POSITION_U, swap_uv);
  pre_pwm_config_online(bp_max, wave_offset_0, wave_offset_1);
  pre_pwm_config_online_inc(DEFAULT_INC);
  pre_pwm_config_online_scale(DEFAULT_MULT, DEFAULT_MULT_SHIFT);
  pre_pwm_set_sinc_smult_init(DEFAULT_INC, DEFAULT_MULT, true, true);
}

static void Motor_SoftWareInit(void)
{
  MotorVar.OverModulateK = 1000;

  MotorVar.RestartEnable = false;

  MotorVar.CloseLoopEn = 1;
  MotorVar.ParamTuneEn = 0;
  /* 水泵使用电压补偿 24.01.05 by lxs */
  MotorVar.VolatgeCompEn = 1;

  current.mode = mode_invalid;
  current.speed = DEFAULT_INC;
  /* 加强制类型转换防溢出，消除polyspace警告 2023.10.29 by lxs */
  /* polyspace +1 MISRA-C3:10.1 */
  current.speed_shifted = (s32)current.speed << SCALE_INC;

  MotorVar.CurrentMode = (MotorState_t)current.mode;

  Motor_SetSpeed(0);

  bemf_control_reset(DEFAULT_INC, DEFAULT_MULT); // reset all PI-controller
  /* polyspace +1 MISRA-C3:10.1 */
  s32 stop_barrier_200 = ((s32)m.max_rot) << (SCALE_INC + 1); // OV

  /* eliminate warning, 21.07.30 by yhd */
  u16 pKp, pKi, iKp, iKi;
  pKp = m.pKp;
  pKi = m.pKi;
  iKp = m.iKp;
  iKi = m.iKi;
  pi_controller_init(&inc_controller, pKp, pKi, -stop_barrier_200, stop_barrier_200, SCALE_INC, 0); // PHASE_CONTROLLER
  /* polyspace +2 MISRA-C3:10.1 */
  pi_controller_init(&mult_controller, iKp, iKi, -(((s32)PI_CONTROLLER_MAX_MULT) << SCALE_MULT),
                     (((s32)PI_CONTROLLER_MAX_MULT) << SCALE_MULT), SCALE_MULT, 0); // INC_CONTROLLER

  Motor_BLDCModeInit();
}

static void Motor_BLDCModeInit(void)
{
  if (bldc_mode == sinus_no_float || bldc_mode == sinus_float || bldc_mode == sinus_stallcheck)
  {
    WRITE_REG_16(AADDR_PRE_PWM_ADDR_BASE, (u16)table_entry_svm);
  }
  else
  {
    WRITE_REG_16(AADDR_PRE_PWM_ADDR_BASE, (u16)table_entry_trapez);
  }

  // modes with always on float mode
  bool floating = (bool)(bldc_mode == trapez_float) || (bool)(bldc_mode == sinus_float);
  pre_pwm_enable_float(floating);

  saradc_swap_vw(pre_pwm_is_reverse());

  if (bldc_mode == sinus_stallcheck)
  {
    activate_pre_pwm_float_control(0, true);
    activate_pre_pwm_float_control(1, false);
    activate_pre_pwm_float_control(2, false);
    enable_pwm(0x03); // output pwm on
  }
  else
  {
    activate_pre_pwm_float_control(0, true);
    activate_pre_pwm_float_control(1, true);
    activate_pre_pwm_float_control(2, true);
  }
}
void Motor_SetSpeed(s16 SpeedRpm)
{
  s16 SpeedInc;
  bemf_control_mode_t CurrentMode = bemf_control_get_mode();
  /* 进入干运行状态标志为1且未诊断出干运行时，水泵全速 24.01.05 by lxs */
  if((MotorVar.EnterDryRunningFlag != 0u)&& (MotorVar.Fault.bits.DryRunning == 0u)
  &&(SpeedRpm != 0u))
  {
    SpeedRpm = MOTOR_API_MAX_SPEED_RPM;
  }
  else
  {

  }
  /* 在电机停止状态才使用自转转速限制目标转速，22.03.10 by yhd */
  if (CurrentMode == mode_idle)
  {
    SpeedRpm = Motor_TargetSpeedTrimedByWindMilling(MotorVar.WindMillingSpeed, SpeedRpm);
  }
  /* 添加限制最大母线电流功能，23.06.28 by lxs */
  if (CurrentMode == mode_closed)
  {
    /* 将电流改为滤波后的值 23.07.18 by lxs */
    SpeedRpm = Motor_TargetSpeedTrimedByShuntCurrent(ADCResults.Current.DCFlt, SpeedRpm, MotorVar.CurrentSpeed);
  }
  else
  {
    SpeedRpm = Motor_TargetSpeedTrimedByShuntCurrent(0, SpeedRpm, MotorVar.CurrentSpeed);
  }
  /* 限制根据母线电流限制转速的最大值 23.12.15 by lxs */
  if (SpeedRpm >= (s16)MOTOR_API_MAX_SPEED_RPM)
  {
    SpeedRpm = (s16)MOTOR_API_MAX_SPEED_RPM;
  }
  else if (SpeedRpm <= -(s16)(MOTOR_API_MAX_SPEED_RPM))
  {
    SpeedRpm = -(s16)(MOTOR_API_MAX_SPEED_RPM);
  }
  else
  {
  }

  SpeedInc = Motor_Rpm2Inc((s16)SpeedRpm);

  target.speed = SpeedInc * MOTOR_POS_ROTATION_DIRECTION;

  /* 当自转转速大于MOTOR_API_LOCK_WM_SPEED_TH时，认为堵转恢复成功。22.03.08 by yhd */
  if ((MotorVar.Fault.bits.Lock != 0u) && (ABS(wm.velocity) > MOTOR_API_LOCK_WM_SPEED_TH) &&
      ((wm.samples & 0xFFF0u) != 0) && (MotorVar.StopTime >= MOTOR_API_LOCK_FAST_RECOVER_TIME_TH))
  {
    MotorVar.Fault.bits.Lock = 0u;
  }

  if ((SpeedInc == 0) || ((wm.samples & 0xFFF0u) == 0))
  {
    Motor_SetTargetMode(mode_idle);
  }
  else
  {

    if ((CurrentMode != mode_open) && (CurrentMode != mode_closed))
    {
      if (MotorVar.StopTime >= MOTOR_RESTART_TIME_MIN)
      {
        if ((MotorVar.Fault.reg == 0u) || ((MotorVar.Fault.reg != 0u) && (MotorVar.RestartEnable != 0u)))
        {
          Motor_StopStateDiag();
        }

        if (MotorVar.Fault.reg == 0u)
        {
          Motor_SetTargetMode(mode_closed);
        }
        else
        {
          if (MotorVar.RestartEnable && (!MotorVar.RestartCompeleted))
          {
            Motor_SetTargetMode(mode_closed);
          }
        }
      }
    }
    else
    {
      Motor_SetTargetMode(mode_closed);
    }
  }
}

static s16 Motor_TargetSpeedTrimedByWindMilling(s16 WindMillingSpeed, s16 TargetSpeed)
{
  if (ABS(WindMillingSpeed) > 2000)
  {
    /* Homodromous rotation Speed too high  */
    TargetSpeed = 0;
  }
  /* 自转转速和目标转速同向且自转转速大于目标转速50转时不启动，22.03.06 by yhd */
  else if (((s32)WindMillingSpeed * TargetSpeed > 0) &&
           (ABS(WindMillingSpeed) > (ABS(TargetSpeed) + MOTOR_API_REF_ACT_SPEED_DIFF_MIN)))
  {
    /* Homodromous rotation Speed large than target speed  */
    TargetSpeed = 0;
  }
  else
  {
  }
  return TargetSpeed;
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:Motor_TargetSpeedTrimedByShuntCurrent
* Description:
* 通过调节目标转速来限制最大母线电流
*
* Inputs:
* ShuntCurrent：母线电流，单位0.1A
* TargetSpeed：目标转速，单位：rpm
* CurrentSpeed:当前转速，单位：rpm
*
* Outputs:
* TargetSpeed：新的目标转速，单位：rpm
*
* Limitations:
********************************************************************
END_FUNCTION_HDR*/
static s16 Motor_TargetSpeedTrimedByShuntCurrent(s16 ShuntCurrent, s16 TargetSpeed, s16 CurrentSpeed)
{
/*转速限电流1010.0暂时不考虑 22.11.09 by mxd*/
/*1020版本增加过流诊断 23.02.23 by mxd*/
#if 1
  s16 ShuntCurrentError = 0;
  static s16 ShuntCurrentErrorLast = 0;
  static s16 SpdIOut = 0;
  static u8 OCRecoverDelayCnt = 0u;
  static s16 SpdIOutChange = 0u;

  if (ShuntCurrent > MOTOR_API_CURRENT_LIMIT_START_TH)
  {
    ShuntCurrentError = MOTOR_API_MAX_CURRENT_0P1_A - ShuntCurrent;
    SpdIOut = SpdIOut + ShuntCurrentError / MOTOR_API_OC_SPD_KP +
              (ShuntCurrentError - ShuntCurrentErrorLast) * MOTOR_API_OC_SPD_KI;
    ShuntCurrentErrorLast = ShuntCurrentError;
    /* 电流超过限流1A，增大限流的转速幅度 24.01.05 by lxs */
    if((ShuntCurrent - MOTOR_API_MAX_CURRENT_0P1_A) > MOTOR_API_LIMIT_CURRENT_ERROR)
    {
      SpdIOutChange = MOTOR_API_OC_SPD_I_OUT_MAX_MAX;
    }
    else
    {
      SpdIOutChange = MOTOR_API_OC_SPD_I_OUT_MAX;
    }

    if (SpdIOut > SpdIOutChange)
    {
      SpdIOut = SpdIOutChange;
    }
    else if (SpdIOut < (-SpdIOutChange))
    {
      SpdIOut = (-SpdIOutChange);
    }
    else
    {
    }

    MotorVar.ShuntCurrentLimitFlag = 1u;
    OCRecoverDelayCnt = MOTOR_API_OC_RECOVER_DELAY_TH;
  }
  else
  {
    if (MotorVar.ShuntCurrentLimitFlag != 0u)
    {
      if (OCRecoverDelayCnt > 0u)
      {
        OCRecoverDelayCnt--;
      }
      else
      {
        MotorVar.ShuntCurrentLimitFlag = 0u;
      }
    }
    else
    {
      OCRecoverDelayCnt = 0u;
      SpdIOut = 0;
      ShuntCurrentErrorLast = 0;
    }
  }

  if (MotorVar.ShuntCurrentLimitFlag != 0u)
  {
    if (CurrentSpeed + SpdIOut < TargetSpeed)
    {
      TargetSpeed = CurrentSpeed + SpdIOut;
    }
    else
    {
    }
  }
#endif
  return TargetSpeed;
}

static s16 Motor_Rpm2Inc(s16 Rpm)
{
  return ERPM_TO_INC(Rpm * m.pole_pairs);
}

static void Motor_StopStateDiag(void)
{
  if (Motor_IsWindmillPresent())
  {
    MotorVar.Fault.bits.Short = false;
    MotorVar.Fault.bits.OpenLoad = false;
  }
  else
  {
    if (Motor_StillStateDiag())
    {
      MotorVar.RestartCompeleted = true;
    }
    MotorVar.StopTime = 0;
  }
}

void Motor_PeriodTask(void)
{
  MotorVar.CurrentMode = (MotorState_t)bemf_control_get_mode();

  Motor_UpdateSpeed();

  switch (MotorVar.CurrentMode)
  {
  case mode_open: {
    u16 boost = 0;

    if (Motor_IsSpeedUp())
    {
      boost = m.uf_boost;
    }

    u16 accel;
    /* 反转进入开环，则先进行定位 24.01.05 by lxs */
    if ((MotorVar.ReversalToOpen == 1) && (MotorVar.OpenLoopTime < MOTOR_API_ALIAN_TIME))
    {
      accel = 0;
    }
    else
    {
      if (ABS(MotorVar.CurrentSpeed) < MOTOR_API_OPENLOOP_SWITCH_ACC_SPEED)
      {
        accel = MOTOR_API_OPENLOOP_ACC_MIN;
      }
      else
      {
        accel = MOTOR_OPEN_VF_ACCEL;
      }
    }

    s16 smult = U_F_Kennlinie(current.speed, boost, true, false);
    DebugVar.PhaseDiffOffset = 0;
    SCIDebug.Motor.OverModulateK = 1000;
    pre_pwm_set_sinc_smult_init(current.speed, smult, false, false);
    pre_pwm_enable_inc(true);

    Motor_SpeedRamp(accel);
    Motor_ModeStateMachine();
  }
  break;
  case mode_closed: {
    Motor_SpeedRamp(Motor_CaculateSpeedRampAcc());
    Motor_ModeStateMachine();

    Motor_OverModulate();
    }
  break;
  default:/*  消除polyspace警告 2023.10.17 by lxs */
    break;
  }

  if ((MotorVar.CurrentMode == (MotorState_t)mode_open) || (MotorVar.CurrentMode == (MotorState_t)mode_closed))
  {
    /* 诊断Bemf是否正常，22.03.06 by yhd */
    Motor_diagBemf();
    Motor_SpeedMonitor();
    Motor_CurrentMonitor();

    Motor_LockMonitor();

    if(MotorVar.CurrentMode == (MotorState_t)mode_closed)
    {
      /* 干运行监控函数 23.09.11 by lxs */
      MotorAPI_MotorDryRunningMonitor();
    }
  }

  Motor_ModeTimeCnt();
}

static void Motor_UpdateSpeed(void)
{
  MotorVar.TargetSpeed = Motor_Inc2Rpm(target.speed);
  /* 给自转转速赋值，22.03.06 by yhd */
  if (MotorVar.CurrentMode == (MotorState_t)mode_open)
  {
    MotorVar.CurrentSpeed = Motor_Inc2Rpm(current.speed);
    MotorVar.WindMillingSpeed = MotorVar.CurrentSpeed;
  }
  else if (MotorVar.CurrentMode == (MotorState_t)mode_closed)
  {
    MotorVar.CurrentSpeed = Motor_Inc2Rpm(MotorVar.NewInc);
    MotorVar.WindMillingSpeed = MotorVar.CurrentSpeed;
  }
  else
  {
    if ((wm.samples & 0xFFF0u) != 0)
    {
      MotorVar.WindMillingSpeed = Motor_Inc2Rpm(wm.velocity);
    }
    else
    {
      if (MotorVar.CurrentSpeed != 0)
      {
        MotorVar.WindMillingSpeed = MotorVar.CurrentSpeed;
      }
    }
    MotorVar.CurrentSpeed = 0;
  }

  #if (MOTOR_POS_ROTATION_DIRECTION == -1)
    MotorVar.TargetSpeed = -MotorVar.TargetSpeed;
    MotorVar.CurrentSpeed = -MotorVar.CurrentSpeed;
    MotorVar.WindMillingSpeed = -MotorVar.WindMillingSpeed;
  #endif
}

static u16 Motor_CaculateSpeedRampAcc(void)
{
  u16 Acc;

  if (Motor_IsSpeedUp())
  {
    Acc = m.accel_closed_up;
  }
  else
  {
    Acc = m.accel_closed_down;
  }

  return Acc;
}

static s16 Motor_Inc2Rpm(s16 Inc)
{
  return (INC_TO_ERPM(Inc) / m.pole_pairs);
}

static void Motor_ModeTimeCnt(void)
{
  static bemf_control_mode_t LastMode = mode_invalid;

  if (MotorVar.CurrentMode != (MotorState_t)LastMode)
  {
    if ((MotorVar.CurrentMode == (MotorState_t)mode_idle) && (LastMode != mode_idle))
    {
      Motor_StopHook();
    }
	  /* 进入闭环后，对定位相关参数进行处理 23.08.24 by lxs */
    if ((MotorVar.CurrentMode == (MotorState_t)mode_closed) && (LastMode != mode_closed))
    {
      Motor_CloseLoopHook();
    }
    LastMode = (bemf_control_mode_t)MotorVar.CurrentMode;
  }

  switch (MotorVar.CurrentMode)
  {
  case mode_idle:
    if (MotorVar.StopTime < (0xFFFFu - MOTOR_API_TIME_BASE)) // 时间都是u16类型
    {
      MotorVar.StopTime += MOTOR_API_TIME_BASE;
    }
    break;
  case mode_closed:
    if (MotorVar.CloseLoopTime < (0xFFFFu - MOTOR_API_TIME_BASE))
    {
      MotorVar.CloseLoopTime += MOTOR_API_TIME_BASE;
    }
    break;
	  /* 开环时间计数 23.08.24 by lxs */
    case mode_open:
    if (MotorVar.OpenLoopTime < (0xFFFFu - MOTOR_API_TIME_BASE))
    {
      MotorVar.OpenLoopTime += MOTOR_API_TIME_BASE;
    }
    break; 
  default:/*  消除polyspace警告 2023.10.17 by lxs */
    break;
  }
}

static void Motor_StopHook(void)
{
  MotorVar.StopTime = 0;
  MotorVar.CloseLoopTime = 0;
  MotorVar.StartToClose = 0;
  MotorVar.VoltageCompensationEn = 0;
  MotorVar.CurrentTooHighTime = 0;
  MotorVar.SpeedTooLowTime = 0;
  MotorVar.SpeedTooHighTime = 0;
  MotorVar.SpeedLoseStepTime = 0;
  MotorVar.DriverErrorTime = 0;
  /* 清零Bemf异常计数，22.03.06 by yhd */
  MotorVar.BemfOutRangeTime = 0;
  /*反转定位状态标志和开环时间计数清零 23.08.24 by lxs*/
  MotorVar.ReversalToOpen = 0;
  MotorVar.OpenLoopTime = 0;
  MotorVar.ShuntCurrentLimitFlag = 0u;
  /* 停止时清除该值,避免开环切闭环电流偶尔出现过大情况  23.08.28 by lxs */
  MotorVar.NewInc = 0;
  /* 清除干运行诊断相关计数 23.12.26 by lxs */
  MotorVar.DryRunningCurrentHighTime = 0;
  MotorVar.DryRunningCurrentLowTime = 0;
  MotorVar.EnterDryRunningFlag = 0u;
}

static void Motor_CloseLoopHook(void)
{
  /* 清除开环时间计数和反转进闭环标志 23.08.24 by lxs */
  MotorVar.OpenLoopTime = 0;
  MotorVar.ReversalToOpen = 0;
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:Motor_diagBemf
* Description:
* 根据当前转速计算最小mult输出，比较
*
* Inputs:
*
*
* Outputs:
*
*
* Limitations:
********************************************************************
END_FUNCTION_HDR*/
static void Motor_diagBemf(void)
{
  if (MotorVar.CurrentMode == (MotorState_t)mode_open)
  {
    MotorVar.PwmMultMin = 0;
  }
  else
  {
    MotorVar.PwmMultMin =
      (((s32)ABS(MotorVar.NewInc) * MOTOR_API_DIAG_BEMF_COEF1 - MOTOR_API_DIAG_BEMF_COEF2) / GPIO_ADC_VBAT) *
      MOTOR_API_DIAG_BEMF_COEF3;
  }

  if (ABS(MotorVar.PwmMultMin) > ABS(MotorVar.PwmMultComp))
  {
    if (MotorVar.BemfOutRangeTime < MOTOR_API_DIAG_BEMF_TIME_TH)
    {
      MotorVar.BemfOutRangeTime += MOTOR_API_TIME_BASE;
    }
    else
    {
      MotorVar.Fault.bits.BemfOutRange = 1u;
    }
  }
  else
  {
    if (MotorVar.BemfOutRangeTime >= MOTOR_API_TIME_BASE)
    {
      MotorVar.BemfOutRangeTime -= MOTOR_API_TIME_BASE;
    }
  }
}


static void Motor_SpeedMonitor(void)
{
  // static s16 TargetSpeedLast = 0;
  static bool InverseLast = false;
  if (ABS(MotorVar.CurrentSpeed) < m.start_control)
  {
    if (MotorVar.SpeedTooLowTime < (0xFFFFu - MOTOR_API_TIME_BASE))
    {
      MotorVar.SpeedTooLowTime += MOTOR_API_TIME_BASE;
    }
  }
  else
  {
    MotorVar.SpeedTooLowTime = 0;
  }

  if (ABS(MotorVar.CurrentSpeed) > MOTOR_API_SPEED_TOO_HIGH_THR)
  {
    if (MotorVar.SpeedTooHighTime < (0xFFFFu - MOTOR_API_TIME_BASE))
    {
      MotorVar.SpeedTooHighTime += MOTOR_API_TIME_BASE;
    }
  }
  else
  {
    MotorVar.SpeedTooHighTime = 0;
  }
  /* 去掉实际转速比期望转速大50转的诊断 24.03.11 by lxs */
#if 0
  if ((MotorVar.CurrentSpeed < MotorVar.TargetSpeed) || (MotorVar.TargetSpeed != TargetSpeedLast))
  {
    MotorVar.SpeedLoseStepTime = 0;
  }
  else if ((ABS(MotorVar.CurrentSpeed) > ABS(MotorVar.TargetSpeed) + 50))
  {
    if (MotorVar.SpeedLoseStepTime < (0xFFFFu - MOTOR_API_TIME_BASE))
    {
      MotorVar.SpeedLoseStepTime += MOTOR_API_TIME_BASE;
    }
  }
  else
  {
  }

  TargetSpeedLast = MotorVar.TargetSpeed;
#endif
  /* polyspace +1 MISRA-C3:10.1 */
  if (((MotorVar.CurrentSpeed & 0x8000u) ^ (MotorVar.TargetSpeed & 0x8000u)) != 0)
  {
    InverseLast = true;
  }
  else
  {
    if (InverseLast)
    {
      MotorVar.SpeedTooLowTime = 0;
      MotorVar.SpeedTooHighTime = 0;
      MotorVar.SpeedLoseStepTime = 0;
    }

    InverseLast = false;
  }

  if (MotorVar.CurrentMode == (MotorState_t)mode_open)
  {
    MotorVar.SpeedTooLowTime = 0;
    MotorVar.SpeedTooHighTime = 0;
    MotorVar.SpeedLoseStepTime = 0;
  }
}

static void Motor_CurrentMonitor(void)
{
  if (ADCResults.Current.DC > MOTOR_API_SHUNT_CURRENT_OC_TH)
  {
    if (MotorVar.CurrentTooHighTime < (0xFFFFu - MOTOR_API_TIME_BASE))
    {
      MotorVar.CurrentTooHighTime += MOTOR_API_TIME_BASE;
    }
  }
  else
  {
    MotorVar.CurrentTooHighTime = 0;
  }

  static bool InverseLast = false;
  /* polyspace +1 MISRA-C3:10.1 */
  if (((MotorVar.CurrentSpeed & 0x8000u) ^ (MotorVar.TargetSpeed & 0x8000u)) != 0)
  {
    InverseLast = true;
  }
  else
  {
    if (InverseLast)
    {
      MotorVar.CurrentTooHighTime = 0;
    }

    InverseLast = false;
  }

  if (MotorVar.CurrentMode == (MotorState_t)mode_open)
  {
    MotorVar.CurrentTooHighTime = 0;
  }
}

void Motor_DrvErrHandler(void)
{
  static driver_error_t last_error_code = DRIVER_OK;
  driver_error_t this_error_code = SDK_MotorDrvGetStatus();

  if (this_error_code != DRIVER_OK || last_error_code != DRIVER_OK)
  {
    driver_status = this_error_code;

    switch (driver_status)
    {
    case DRIVER_OK:
      break;
    case DRIVER_OVERCURRENT:
      if (PowerUpBlank(200))
      {
        /*
        Driver Switching on will cause over current.
        */
        /*使用宏定义记录故障，增加上电后的桥区故障技术 2023.12.15 by lxs */
        MotorVar.FaultRecord |= MOTOR_API_FAULT_RECORD_MSK_DRV_OC_HEX;
        MotorVar.DriverErrorTime++;
      }
      break;
    case DRIVER_OVERTEMP:
      MotorVar.FaultRecord |= MOTOR_API_FAULT_RECORD_MSK_DRV_OT_HEX;
      break;
    case DRIVER_VCC_UNDERVOLTAGE:
      MotorVar.FaultRecord |= MOTOR_API_FAULT_RECORD_MSK_DRV_VCC_LOW_HEX;
      break;
    case DRIVER_VG_UNDERVOLTAGE:
      MotorVar.FaultRecord |= MOTOR_API_FAULT_RECORD_MSK_DRV_VG_LOW_HEX;
      break;
    default:/*  消除polyspace警告 2023.10.17 by lxs */
      break;
    }

    if (this_error_code != DRIVER_OK)
    {
      last_driver_error = this_error_code;
    }
    last_error_code = this_error_code;
  }

  if (MotorVar.DriverErrorTime > MOTOR_API_DRV_ERR_CNT_TH)
  {
    MotorVar.FaultRecord |= MOTOR_API_FAULT_RECORD_MSK_DRV_ERR_HEX;
    /* 电压跳变会误报驱动器故障，现将该部分屏蔽，让电压跳变时进行有转速启动 23.07.17 by lxs */
    #if 0
    MotorVar.Fault.bits.Lock = true;

    if (MotorVar.RestartEnable)
    {
      MotorVar.RestartCompeleted = true;
    }
   #endif
    /* 驱动故障次数处理后清0 23.08.28 by lxs */
    MotorVar.DriverErrorTime = 0u;
    Motor_SetTargetMode(mode_idle);
    Motor_ModeStateMachine();
    
  }

  SDK_MotorDrvClearError(driver_status);
}

void Motor_CaculateWindmillPosition(void)
{
  // average them
  wm.u_in[0] = (GPIO_WINDMILL_U >> 4);
  wm.u_in[0] += (GPIO_WINDMILL_U2 >> 4);
  wm.v_in[0] = (GPIO_WINDMILL_V >> 4);
  wm.v_in[0] += (GPIO_WINDMILL_V2 >> 4);
  wm.w_in[0] = (GPIO_WINDMILL_W >> 4);
  wm.w_in[0] += (GPIO_WINDMILL_W2 >> 4);

  // we have all data start again
  if (bemf_control_get_mode() == mode_idle)
  {
    /* polyspace +1 MISRA-C3:11.8 */
    saradc_apply_list((saradc_table_list_entry *)list_windmill, true);
  }

  // filter input with previous and next data
  // machine is one step ahead take the bp of wm.u_in[1]
  /* polyspace-begin MISRA-C3:10.1 */
  wm.u = (wm.u_in[0] + (wm.u_in[1] << 1) + wm.u_in[2]) >> 2;
  wm.v = (wm.v_in[0] + (wm.v_in[1] << 1) + wm.v_in[2]) >> 2;
  wm.w = (wm.w_in[0] + (wm.w_in[1] << 1) + wm.w_in[2]) >> 2;
  /* polyspace-end MISRA-C3:10.1 */
  wm.u_in[1] = wm.u_in[0];
  wm.v_in[1] = wm.v_in[0];
  wm.w_in[1] = wm.w_in[0];
  wm.u_in[2] = wm.u_in[1];
  wm.v_in[2] = wm.v_in[1];
  wm.w_in[2] = wm.w_in[1];

  // calculate clarke a,b, theta, mannhattan
  wm.a = (2 * wm.u - wm.v - wm.w);
  wm.b = divider_sdiv((((s32)wm.v - (s32)wm.w)) * 13775, 7953);
  wm.theta = atan2Lerp_BP(wm.a, wm.b);
  wm.manhattan = ABS(wm.a) + ABS(wm.b);

  if (wm.manhattan > WM_APM_MIN)
  {
    // two samples in order
    if (wm.last_theta != INVALID)
    {
      // velocity filter
      wm.theta_diff = take_nearest_bp(wm.theta, wm.last_theta);
      /* polyspace +1 MISRA-C3:10.1  */
      wm.theta_diff_tp = (wm.theta_diff_tp * 15 + wm.theta_diff) >> 4;
      wm.velocity = DBP_PER_20PWMS_TO_INC(wm.theta_diff_tp);

      // rotation direction
      wm.direction += wm.theta_diff;
      if (wm.direction > (INT16_MAX - BP_MAX))
      {
        wm.direction = (INT16_MAX - BP_MAX);
      }
      if (wm.direction < (INT16_MIN + BP_MAX))
      {
        wm.direction = (INT16_MIN + BP_MAX);
      }
    }

    wm.last_theta = wm.theta;
  }
  else
  {
    wm.theta = INVALID;
    wm.last_theta = INVALID;
    wm.theta_diff = INVALID;
    wm.last_bp_error = INVALID;

    if (wm.direction > BP_MAX)
    {
      wm.direction -= BP_MAX;
    }
    else if (wm.direction < -BP_MAX)
    {
      wm.direction += BP_MAX;
    }
    else
    {
      wm.direction = 0;
      wm.velocity = 0;
    }
  }

  if (wm.samples != 0xFFFFu)
  {
    wm.samples++;
  }
}
static void Motor_OverModulate(void)
{
  MotorVar.OverModulateK = MOTOR_API_OVER_MODULATION;
}

static void Motor_LockMonitor(void)
{

  if (MotorVar.CloseLoopTime < MOTOR_API_DIAG_LOCK_CLOSE_LOOP_TIME_THR)
  {
    /*转速低于开环切闭环转速10s 2023.11.03  by mxd */
    if (MotorVar.SpeedTooLowTime > MOTOR_API_SPEED_TOO_LOW_OR_HIGH_TIME_THR)
    {
      MotorVar.Fault.bits.SpeedTooLow = 1u;
    }
    else
    {
    }
    /*当前转速大于目标转速50rpm，持续20s 2023.11.03  by mxd */
    if (MotorVar.SpeedLoseStepTime > MOTOR_API_LOSE_STEP_TIME_THR)
    {
      MotorVar.Fault.bits.SpeedOutRange = 1u;
    }
    else
    {
    }
    /*转速高于6000rpm，持续10s 2023.11.03  by mxd */
    if (MotorVar.SpeedTooHighTime > MOTOR_API_SPEED_TOO_LOW_OR_HIGH_TIME_THR)
    {
      MotorVar.Fault.bits.SpeedTooHigh = 1u;
    }
    else
    {
    }
  }
  
  if (MotorVar.CurrentTooHighTime > MOTOR_API_OVER_CURRENT_DIAGNOSE_TIME)
  {
    MotorVar.Fault.bits.OverCurrent = 1u;
  }
  else
  {
    MotorVar.Fault.bits.OverCurrent = 0u;
  }

  /* 使用Bemf诊断堵转故障，22.03.09 by yhd */
  /* 增加过流诊断，归为堵转故障 23.07.04 by lxs */
  if ((MotorVar.Fault.bits.SpeedOutRange != 0u) || (MotorVar.Fault.bits.BemfOutRange != 0u) ||
      (MotorVar.Fault.bits.SpeedTooHigh != 0u) || (MotorVar.Fault.bits.SpeedTooLow != 0u) ||
      (MotorVar.Fault.bits.SpeedOutRangeInc != 0u) || (MotorVar.Fault.bits.OverCurrent != 0u))
  {
    MotorVar.FaultRecord |= ((u16)MotorVar.Fault.bits.OverCurrent << MOTOR_API_FAULT_RECORD_MSK_OVER_CURRENT_CNT);
    MotorVar.FaultRecord |=
      ((u16)MotorVar.Fault.bits.SpeedOutRangeInc << MOTOR_API_FAULT_RECORD_MSK_SPEED_OUT_RANGE_INC_CNT);
    MotorVar.FaultRecord |= ((u16)MotorVar.Fault.bits.SpeedTooLow << MOTOR_API_FAULT_RECORD_MSK_SPEED_TOO_LOW_CNT);
    MotorVar.FaultRecord |= ((u16)MotorVar.Fault.bits.SpeedOutRange << MOTOR_API_FAULT_RECORD_MSK_SPEED_OUT_RANGE_CNT);
    MotorVar.FaultRecord |= ((u16)MotorVar.Fault.bits.SpeedTooHigh << MOTOR_API_FAULT_RECORD_MSK_SPEED_TOO_HIGH_CNT);
    MotorVar.FaultRecord |= ((u16)MotorVar.Fault.bits.BemfOutRange << MOTOR_API_FAULT_RECORD_MSK_BEMF_OUT_RANGE_CNT);

    MotorVar.Fault.bits.OverCurrent = false;
    MotorVar.Fault.bits.BemfOutRange = false;
    MotorVar.Fault.bits.SpeedOutRange = false;
    MotorVar.Fault.bits.SpeedOutRangeInc = false;
    MotorVar.Fault.bits.SpeedTooHigh = false;
    MotorVar.Fault.bits.SpeedTooLow = false;

    MotorVar.Fault.bits.Lock = true;

    if (MotorVar.RestartEnable)
    {
      MotorVar.RestartCompeleted = true;
    }

    Motor_SetTargetMode(mode_idle);
  }
  else
  {
    if ((MotorVar.CloseLoopTime > 5000) && (MotorVar.DriverErrorTime == 0) && (MotorVar.SpeedTooLowTime == 0) &&
        (MotorVar.SpeedTooHighTime == 0) && (MotorVar.SpeedLoseStepTime == 0) && (ABS(MotorVar.CurrentSpeed) < 5000))
    {
      /* 故障恢复后清除故障记录标志，22.01.10 by yhd */
      MotorVar.FaultRecord = 0u;

      MotorVar.RestartCompeleted = true;
      MotorVar.Fault.bits.Lock = false;
    }
  }
}
/* 干运行诊断函数 23.09.08 by lxs */
static void MotorAPI_MotorDryRunningMonitor(void)
{
  /* 获取当前滤波电流值 24.03.27 by lxs */
  s16 DryRunningCurrent = ABS(ADCResults.Current.DCFlt);

  if(DryRunningCurrent < MOTOR_API_DRY_RUNNING_CURRENT_TH)
	{
		MotorVar.DryRunningCurrentHighTime = 0u;
		if(MotorVar.DryRunningCurrentLowTime <= 0xFFFFFFFFu - (MOTOR_API_TIME_BASE))
		{
			MotorVar.DryRunningCurrentLowTime += (MOTOR_API_TIME_BASE);
		}
		else
		{
			MotorVar.DryRunningCurrentLowTime = 0xFFFFFFFFu;
		}
	}
	else
	{
		MotorVar.DryRunningCurrentLowTime = 0u;
		if(MotorVar.DryRunningCurrentHighTime <= 0xFFFFFFFFu - (MOTOR_API_TIME_BASE))
		{
			MotorVar.DryRunningCurrentHighTime += (MOTOR_API_TIME_BASE);
		}
		else
		{
			MotorVar.DryRunningCurrentHighTime = 0xFFFFFFFFu;
		}
	}

  if(MotorVar.DryRunningCurrentLowTime >= MOTOR_API_DRY_RUNNNG_LOW_FILTER_TIME)
  {
    MotorVar.EnterDryRunningFlag = 1u;
    /* 干运行时间超过15分钟 干运行标志置1 24.01.05 by lxs */
    if(MotorVar.DryRunningCurrentLowTime > (MOTOR_API_DRY_RUNNNG_TEST_TIME))
    {
      MotorVar.Fault.bits.DryRunning = 1u;
    }
    else
    {

    }
  }

  /* 正常运行时间超过4s 干运行标志清0 24.01.05 by lxs */
  if(MotorVar.DryRunningCurrentHighTime > (MOTOR_API_DRY_RUNNNG_HIGH_FILTER_TIME))
  {
    MotorVar.Fault.bits.DryRunning = 0u;
    MotorVar.EnterDryRunningFlag = 0u;
  }
  else
  {

  }
}
