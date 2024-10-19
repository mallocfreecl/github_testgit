#include "PwmIn.h"
#include "debug.h"

/*
Hardware relay
*/
#include "api.h"
#include "commons.h"

/* Defines*/
/******************************************************************/
/* 对计算定时器时钟进行补偿，22.03.03 by yhd */
#define PWMIN_CAPTURE_TIMER_CLK (505100uL) // Hz
#define PWMIN_PERIOD_TASK_TIME_BASE 5      // ms
/* 增加检测信号先延时时间，减少对低频信号的干扰，22.03.06 by yhd */
#define PWMIN_SIGNAL_IDLE_STATE_DELAY_TIME (90u)
/* 修改宏定义，防止polyspace报警告 23.10.29 by lxs */
#define divider_udiv_sw(x, y) (((u32)(x)) / ((u32)(y))) /* polyspace MISRA-C3:7.2 */

/* Variables */
/******************************************************************/
static struct
{
  u16 LowPulseOverFlowCnt;
  u16 PeriodPulseOverFlowCnt;
  u32 LowPulseCnt;
  u32 PeriodPulseCnt;
  bool Update;
  /* 捕获定时器输入切换标志， 22.01.10 by yhd */
  bool IsTmrInputChg;
} PwmInVar = {
  .IsTmrInputChg = true,
};

PwmInAPI_t PwmInAPI = {
  0,     // Freq
  0,     // Duty
  0,     // Idle time
  true,  // Bus state
  false, // Update
};

/* Function declaration */
/******************************************************************/
static u32 PwmIn_LowPulseCntTrim(void);
static u32 PwmIn_PeriodPulseCntTrim(void);
static void PwmIn_ScaleLowPulseCnt(u32 *pLowPulseCnt);
static u8 PwmIn_ScalePeriodPulseCnt(u32 *pPeriodPulseCnt);
static void PwmIn_BusStateConfirm(void);

void PwmIn_LowPulseHigh2LowHandler(void)
{
  PwmInVar.LowPulseOverFlowCnt = 0;
  PwmInAPI.BusState = 0;
}

void PwmIn_LowPulseCaptureTimerOverFlowHandler(void)
{
  if (PwmInVar.LowPulseOverFlowCnt < 0xFFFFu)
  {
    PwmInVar.LowPulseOverFlowCnt++;
  }
}

void PwmIn_LowPulseLow2HighCaptureHandler(void)
{
  /* polyspace-begin MISRA-C3:10.8 */
  PwmInVar.LowPulseCnt =
    ((u32)PwmInVar.LowPulseOverFlowCnt << 16) - (u32)((PwmInVar.LowPulseOverFlowCnt != 0) ? 32768 : 0) +
    (u32)((s16)READ_REG_U16(AADDR_CCTIMER_2_CAPCMP_A) + ((PwmInVar.LowPulseOverFlowCnt != 0) ? 32768 : 0));
  /* polyspace-end MISRA-C3:10.8 */
  PwmInAPI.BusState = 1;

  /* Pwm输入Pin功能切换时特殊处理，22.01.10 by yhd */
  if (PwmInVar.IsTmrInputChg == false)
  {
    PwmInAPI.BusIdleTime = 0u;
  }
  PwmInVar.IsTmrInputChg = false;
}

void PwmIn_PeriodPulseCaptureTimerOverFlowHandler(void)
{
  if (PwmInVar.PeriodPulseOverFlowCnt < 0xFFFFu)
  {
    PwmInVar.PeriodPulseOverFlowCnt++;
  }
}

void PwmIn_PeriodPulseCaptureAndRestartHandler(void)
{
  /* 捕获定时器输入切换时会触发捕获中断，这时不进行处理，22.01.10 by yhd */
  if (PwmInVar.IsTmrInputChg == false)
  {
    /* polyspace-begin MISRA2012:10.8 */
    PwmInVar.PeriodPulseCnt =
      ((u32)PwmInVar.PeriodPulseOverFlowCnt << 16) - (u32)((PwmInVar.PeriodPulseOverFlowCnt != 0) ? 32768 : 0) +
      (u32)((s16)READ_REG_U16(AADDR_CCTIMER_2_CAPCMP_B) + ((PwmInVar.PeriodPulseOverFlowCnt != 0) ? 32768 : 0));
    /* polyspace-start MISRA2012:10.8 */
    PwmInVar.PeriodPulseOverFlowCnt = 0;
    PwmInVar.Update = true;
  }
}

/*
Call this function periodly
*/
void PwmIn_PeriodTask(void)
{
  u32 LowPulseCnt;
  u32 PeriodPulseCnt;
  u8 ShiftBits;

  if (PwmInVar.Update)
  {
    PwmInVar.Update = false;

    PwmInAPI.BusIdleTime = 0;

    LowPulseCnt = PwmIn_LowPulseCntTrim();
    PeriodPulseCnt = PwmIn_PeriodPulseCntTrim();

    if (LowPulseCnt > PeriodPulseCnt)
    {
      if (PwmInVar.LowPulseCnt < PwmInVar.PeriodPulseCnt)
      {
        LowPulseCnt = PeriodPulseCnt;
      }
      else
      {
        LowPulseCnt = 0;
      }
    }

    PwmIn_ScaleLowPulseCnt(&LowPulseCnt);
    ShiftBits = PwmIn_ScalePeriodPulseCnt(&PeriodPulseCnt);

    PwmInAPI.LowDuty = divider_udiv_sw(((u32)LowPulseCnt * (u32)1000) >> ShiftBits, PeriodPulseCnt);
    PwmInAPI.Freq = divider_udiv_sw(((u32)PWMIN_CAPTURE_TIMER_CLK * 10) >> ShiftBits, PeriodPulseCnt);
  }
  else
  {
    if (PwmInAPI.BusIdleTime < (0xFFFFu - PWMIN_PERIOD_TASK_TIME_BASE))
    {
      PwmInAPI.BusIdleTime += PWMIN_PERIOD_TASK_TIME_BASE;
    }
    else
    {
      PwmInAPI.BusIdleTime = 0xFFFFu;
    }

    /*
    Pwm输入固定电平时确认电平状态，23.02.22 by jxj。

    由于PwmInAPI.BusIdleTime是以PWMIN_PERIOD_TASK_TIME_BASE为单位进行变化的，所以对该值取
    PWMIN_PERIOD_TASK_TIME_BASE的整数倍后再判断是否相等，23.02.22 by jxj。
    */
    if (PwmInAPI.BusIdleTime ==
        PWMIN_SIGNAL_IDLE_STATE_DELAY_TIME / PWMIN_PERIOD_TASK_TIME_BASE * PWMIN_PERIOD_TASK_TIME_BASE)
    {
      PwmIn_BusStateConfirm();
    }
    else if (PwmInAPI.BusIdleTime ==
             ((PWMIN_SIGNAL_IDLE_STATE_DELAY_TIME / PWMIN_PERIOD_TASK_TIME_BASE + 1u) * PWMIN_PERIOD_TASK_TIME_BASE))
    {
      PwmInAPI.BusState = (PwmInVar.IsTmrInputChg == false);
      PwmInVar.IsTmrInputChg = false;
    }
    else
    {
    }
  }
}

static u32 PwmIn_LowPulseCntTrim(void)
{
  u32 LowPulseCnt = PwmInVar.LowPulseCnt;

  return LowPulseCnt;
}

static u32 PwmIn_PeriodPulseCntTrim(void)
{
  u32 PeriodPulseCnt = PwmInVar.PeriodPulseCnt;

  return PeriodPulseCnt;
}

static void PwmIn_ScaleLowPulseCnt(u32 *pLowPulseCnt)
{
  if (*pLowPulseCnt > divider_udiv_sw(0xFFFFFFFF, 10))
  {
    *pLowPulseCnt = divider_udiv_sw(*pLowPulseCnt, 1000) * 1000;
  }
  else if (*pLowPulseCnt > divider_udiv_sw(0xFFFFFFFF, 100))
  {
    *pLowPulseCnt = divider_udiv_sw(*pLowPulseCnt, 100) * 100;
  }
  else if (*pLowPulseCnt > divider_udiv_sw(0xFFFFFFFF, 1000))
  {
    *pLowPulseCnt = divider_udiv_sw(*pLowPulseCnt, 10) * 10;
  }
  else
  {
  }
}

static u8 PwmIn_ScalePeriodPulseCnt(u32 *pPeriodPulseCnt)
{
  u8 ShiftBits = 0;

  while (*pPeriodPulseCnt > 0xFFFFu)
  {
    *pPeriodPulseCnt >>= 1;
    ShiftBits++;
  }

  return ShiftBits;
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:PwmIn_BusStateConfirm
* Description:
* 将Pwm输入Pin在捕获和GPIO功能间切换。Pin设为GPIO时，Tmr捕获默认输入为0。
* 如果Pin状态为高，则Pin切换为GPIO时会触发Tmr下降沿中断。Pin切换为捕获时
* 会触发上升沿中断。
* 如果Pin状态为低，则不会触发中断。
* Pin功能切换后触发中断的延时不确定
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
static void PwmIn_BusStateConfirm(void)
{
  PwmInVar.IsTmrInputChg = true;
  iomux_ctrl_select_c(IOMUX_CTRL_PORT_NO_2, IOMUX_CTRL_FUNC_C_GPIO);

  PwmInVar.IsTmrInputChg = true;
  iomux_ctrl_select_c(IOMUX_CTRL_PORT_NO_2, IOMUX_CTRL_FUNC_C_CCTIMER_2_MEAS);
}
