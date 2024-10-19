#include "IsrHandler.h"
#include "MotorAPI.h"
#include "PwmIn.h"
#include "debug.h"
#include "driver_52350.h"
#include "driver_generic.h"
#include "freemaster.h"
#include "main.h"
#include "saradc_module.h"
#include "testmode.h"
#include "uartdebug.h"

Time_t Time = {0};

/*
Isr function prototype:
void f(int sno)
{

}
*/

void MotorDrv_IO_Err_Handler(int sno)
{
  Motor_DrvErrHandler();
}

void SCIRxHandler(int sno)
{
    UART2_Rx_Handle();
}

void SCITxHandler(int sno)
{
    UART2_Tx_Handle();
}

void CCTimer0_A_RestartHandler(int sno)
{
  Time.Ms++;
  /* 屏蔽开路诊断相关代码 24.03.14 by lxs */
  #if 0
  /* 开路诊断输出低电平延时计数 23.03.13 by lxs */
  if(Time.PwmOutLowFlag != 0)
  {
    Time.PwmOutLowCnt++;
  }
  else
  {
    Time.PwmOutLowCnt = 0;
  }

  if(Time.PwmOutLowFlag1 != 0)
  {
    Time.PwmOutLowCnt1++;
  }
  else
  {
    Time.PwmOutLowCnt1 = 0;
  }
  #endif

  if (Time.Ms >= 1000)
  {
    Time.Ms = 0;
    /* 分钟和小时计数无用 23.12.11 by lxs */
#if 0
    Time.Second++;
    if (Time.Second >= 60)
    {
      Time.Second = 0;

      Time.Min++;
      if (Time.Min >= 60)
      {
        Time.Min = 0;

        Time.Hour++;
      }
    }
#endif
  }
}

void CCTimer0_B_RestartHandler(int sno)
{
}

void CCTimer2_A_RestartHandler(int sno)
{
  PwmIn_LowPulseHigh2LowHandler();
}

void CCTimer2_A_CaptureHandler(int sno)
{
  PwmIn_LowPulseLow2HighCaptureHandler();
}

void CCTimer2_A_OverflowHandler(int sno)
{
  PwmIn_LowPulseCaptureTimerOverFlowHandler();
}

void CCTimer2_B_RestartHandler(int sno)
{
}

void CCTimer2_B_CaptureHandler(int sno)
{
  PwmIn_PeriodPulseCaptureAndRestartHandler();
}

void CCTimer2_B_OverflowHandler(int sno)
{
  PwmIn_PeriodPulseCaptureTimerOverFlowHandler();
}

void ADCListDoneHandler(int sno)
{
  ADCListDoneHandler2();
}

void ADCDMAErrorHandler(int sno)
{
  static u8 Cnt = 0;

  Cnt++;
}
