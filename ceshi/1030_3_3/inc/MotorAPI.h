#ifndef MOTOR_API_H
#define MOTOR_API_H

#include "SDKTypes.h"

/* Defines*/
/******************************************************************/
/* 加长停止后的重启最小间隔时间，防止启动失败，23.02.23 by jxj */
#define MOTOR_RESTART_TIME_MIN 500      // ms
/*重新整理全部故障，包括故障细化 2023.12.15 by lxs */ 
#define MOTOR_API_FAULT_RECORD_MSK_SHORT_GND_HEX (0x0001u)//0  短地
#define MOTOR_API_FAULT_RECORD_MSK_SHORT_GND_CNT (0u)
#define MOTOR_API_FAULT_RECORD_MSK_SHORT_BAT_HEX (0x0002u)//1  短电
#define MOTOR_API_FAULT_RECORD_MSK_SHORT_BAT_CNT (1u)
#define MOTOR_API_FAULT_RECORD_MSK_DRV_ERR_HEX (0x0004u)//2   驱动器故障  导致重启
#define MOTOR_API_FAULT_RECORD_MSK_DRV_ERR_CNT (2u)
#define MOTOR_API_FAULT_RECORD_MSK_SPEED_OUT_RANGE_HEX (0x0008u)//3  超速
#define MOTOR_API_FAULT_RECORD_MSK_SPEED_OUT_RANGE_CNT (3u)
#define MOTOR_API_FAULT_RECORD_MSK_DRV_OC_HEX (0x0010u)//4
#define MOTOR_API_FAULT_RECORD_MSK_DRV_OC_CNT (4u)
#define MOTOR_API_FAULT_RECORD_MSK_DRV_OT_HEX (0x0020u)//5
#define MOTOR_API_FAULT_RECORD_MSK_DRV_OT_CNT (5u)
#define MOTOR_API_FAULT_RECORD_MSK_DRV_VCC_LOW_HEX (0x0040u)//6
#define MOTOR_API_FAULT_RECORD_MSK_DRV_VCC_LOW_CNT (6u)
#define MOTOR_API_FAULT_RECORD_MSK_DRV_VG_LOW_HEX (0x0080u)//7
#define MOTOR_API_FAULT_RECORD_MSK_DRV_VG_LOW_CNT (7u)
#define MOTOR_API_FAULT_RECORD_MSK_SPEED_OUT_RANGE_INC_HEX (0x0100u) //8  失步
#define MOTOR_API_FAULT_RECORD_MSK_SPEED_OUT_RANGE_INC_CNT (8u)
#define MOTOR_API_FAULT_RECORD_MSK_SPEED_TOO_LOW_HEX (0x0200u)//9  //转速过低
#define MOTOR_API_FAULT_RECORD_MSK_SPEED_TOO_LOW_CNT (9u)
#define MOTOR_API_FAULT_RECORD_MSK_SPEED_TOO_HIGH_HEX (0x0400u)//10  //转速过高
#define MOTOR_API_FAULT_RECORD_MSK_SPEED_TOO_HIGH_CNT (10u)
#define MOTOR_API_FAULT_RECORD_MSK_OVER_CURRENT_HEX (0x0800u)//11  //过流
#define MOTOR_API_FAULT_RECORD_MSK_OVER_CURRENT_CNT (11u)
#define MOTOR_API_FAULT_RECORD_MSK_BEMF_OUT_RANGE_HEX (0x1000u) //12 //反电势异常
#define MOTOR_API_FAULT_RECORD_MSK_BEMF_OUT_RANGE_CNT (12u)
#define MOTOR_API_OVER_MODULATION (1250)
struct windmill_t
{

  //*******raw data
  /** three voltage samples of phase u*/ s16 u_in[3];
  /** three voltage samples of phase v*/ s16 v_in[3];
  /** three voltage samples of phase w*/ s16 w_in[3];

  //*******filtered data
  /** averaged voltage of phase u*/ s16 u;
  /** averaged voltage of phase v*/ s16 v;
  /** averaged voltage of phase w*/ s16 w;

  //*******clarke
  /** phasor in direction of coil u.*/ s16 a;
  /** phasor in direction of coil u.+90°*/ s16 b;
  /** ABS(a) + ABS(b)*/ u16 manhattan;

  //*******angle, velocity, direction
  /**angle of phasors*/ u16 theta;
  /**last angle of phasors*/ u16 last_theta;
  /**diffence to the last angle*/ s16 theta_diff;
  /**diffence to the last angle tp filtered*/ s16 theta_diff_tp;
  /**velocity of the bemf in unit INC*/ s16 velocity;
  /**direction of the rotation*/ s16 direction;

  /* 修改为无符号  2023.10.29 by lxs */
  /**samples done for windmill detection*/ u16 samples;

  //*******sync pre-pwm
  /** bp of measurement*/ u16 bp;
  /***/ s16 bp_error;
  /***/ s16 last_bp_error;
};

typedef enum
{
  eMotorIdle,
  eMotorOpenLoop,
  eMotorCloseLoop,
  eMotorFault,
} MotorState_t;

/* 新增Bemf错误标志，22.03.06 by yhd */
typedef union {
  u16 reg;

  struct
  {
    u16 Short : 1;
    u16 Lock : 1;
    u16 OpenLoad : 1;
    u16 OverCurrent: 1;
    u16 SpeedOutRange : 1;
    u16 SpeedOutRangeInc : 1;
    u16 SpeedTooLow : 1;
    u16 SpeedTooHigh : 1;
    u16 BemfOutRange : 1;
	/* 增加干运行故障标志 24.01.05 by lxs */
    u16 DryRunning : 1;
  } bits;
} MotorFault_t;

typedef struct
{
  s16 CurrentSpeed;
  s16 TargetSpeed;
  s16 WindMillingSpeed;

  MotorState_t CurrentMode;
  MotorFault_t Fault;

  bool RestartEnable;
  bool ReverseRotation;
  bool RestartCompeleted;
  s16 AngleShift;

  s16 NewInc;
  s16 PwmMult;
  s16 PwmMultComp;
  /* 根据转速计算的Mult最小值，22.03.06 by yhd */
  s16 PwmMultMin;
  u16 Voltage;
  s16 PhaseDiff;

  u16 StopTime;
  u16 CloseLoopTime;
  /* 增加开环时间标志 23.08.28 by lxs */
  u16 OpenLoopTime;
  u16 SpeedTooLowTime;
  u16 SpeedTooHighTime;
  u16 SpeedLoseStepTime;
  u16 CurrentTooHighTime;
  u16 DriverErrorTime;
  /* Bemf诊断计时，22.03.06 by yhd */
  u16 BemfOutRangeTime;

  u8 StartToClose;
  /* 反转500rpm以上定位标志,生命周期为满足条件直到开环结束 23.08.24 by lxs */
  u8 ReversalToOpen; 
  u8 VoltageCompensationEn;

  s16 OverModulateK;

  u8 CloseLoopEn;
  u8 ParamTuneEn;
  u8 VolatgeCompEn;

  u16 FaultRecord;
  /* 转速限电流标志 23.08.28 by lxs */
  u8 ShuntCurrentLimitFlag;
  /* 干运行高低计数以及进入干运行标志 24.01.05 by lxs */
  u32 DryRunningCurrentHighTime;
  u32 DryRunningCurrentLowTime;
  u8 EnterDryRunningFlag;
} MotorVar_t;

typedef enum
{
  sinus_no_float,
  sinus_stallcheck, // not further supported
  sinus_float,      // not further supported
  trapez_no_float,
  trapez_float,
} bldc_mode_t;

typedef u16 driver_error_t;

extern MotorVar_t MotorVar;
extern struct windmill_t wm;
extern volatile driver_error_t last_driver_error;
extern volatile driver_error_t driver_status;
extern s16 driver_maximal_multiplier;
extern bldc_mode_t bldc_mode;

extern void Motor_DrvErrHandler(void);

extern void Motor_Init(void);
extern void Motor_SetSpeed(s16 SpeedRpm);
extern void Motor_PeriodTask(void);
extern void Motor_CaculateWindmillPosition(void);

#endif
