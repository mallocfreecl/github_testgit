#include "main.h"
#include "ADCSample.h"
#include "DTC.h"
#include "IsrHandler.h"
#include "MotorAPI.h"
#include "PwmIn.h"
#include "VBatMonitor.h"
#include "testmode.h"

#include "AppMain.h"
#include "rtwtypes.h"

#include "debug.h"
#include "freemaster.h"

/* 写DFlash后执行休眠、复位的最短延时时间，没有延时可能会写入出错，23.02.21 by jxj */
#define MAIN_DELAY_AFTER_DFLASH_WRITE (1u)

/* 在固定地址写入常量 */
/* 无符号类型后缀加u 2023.10.29 by lxs */
__root static const uint16_t cookie @0x8000u = 0xaa55u;
__root static const uint16_t cookie2 @0xFFF2u = 0x0000u;

static void Task_5ms(void);
static void Task_10ms(void);
static void Task_50ms(void);
static void Task_100ms(void);

static void AppMainInputUpdate(void);
/* 屏蔽休眠相关函数 23.01.05 by lxs */
//static bool IsSleepSignalValid(void);
static void UpdateDTCRecords(void);
static void SCIEnMonitor(void);
/* 关闭LIN收发器函数 24.01.05 by lxs */
static void TurnOffLinTransceiver(void);

int main(void)
{
  SDK_HardWareInit();
  DTC_Init();
  ADC_VarInit();
  Motor_Init();
  AppMain_initialize();
  SDK_InterruptEnable();
  /* 关闭LIN收发器 24.01.05 by lxs */
  TurnOffLinTransceiver();
  
  while (1)
  {
    static u16 LastTimeMs = 0;

    if (Time.Ms != LastTimeMs)
    {
      Task_5ms();
      Task_10ms();
      Task_50ms();
      Task_100ms();

      LastTimeMs = Time.Ms;
    }
  }
}

static void Task_5ms(void)
{
  if ((Time.Ms % 5) != 0)
  {
    return;
  }

  ADC_PeriodTask();
  PwmIn_PeriodTask();

  AppMainInputUpdate();

  /* fct test, 21.07.30 by yhd */
  if (fcttest_JumpInFlag == 0u)
  {
    AppMain_step();
  }
  else
  {
    TestModePwmOutSelect();
    PwmOut100Hz_50Duty();
  }
  /* 反电势抑制电压监控函数 23.08.30 by lxs */
  BatMonitor();
}

static void AppMainInputUpdate(void)
{
  U.SupVoltage = ADCResults.Voltage.Bat;
  U.FilteredVoltage = ADCResults.Voltage.BatFiltered;
  U.AmbTemperature = ADCResults.Temperature.Chip;
  U.ChipFault = SDK_IsChipFault();

#if DEBUG_SCI_SPEED_EN
  if (!DebugVar.PwmInSpeedCtrlEn)
  {
    U.PwmInFreq = 1000;
    /* U.PwmInHighDuty will be updated by freemaster */
    U.PwmInIdleTime = 0;
    U.PwmInPinSts = 0;
  }
  else
#endif
  {
    U.PwmInFreq = PwmInAPI.Freq;
    /* 对占空比进行四舍五入 24.03.24 by lxs */
    U.PwmInHighDuty = ((1000 - PwmInAPI.LowDuty)+5)/10*10;
    U.PwmInIdleTime = PwmInAPI.BusIdleTime;
    U.PwmInPinSts = PwmInAPI.BusState;
  }
  /* 水泵无休眠功能 24.01.05 by lxs */
  U.SleepValid = 0;
  /*给出停止信号后，清除故障状态，使故障重启和故障反馈重新开始 23.08.03 by mxd*/
  if(Y.PwmInTargetSpeed == 0)
  {
    MotorVar.Fault.bits.Short = 0; 
    MotorVar.Fault.bits.Lock = 0;
    MotorVar.Fault.bits.OpenLoad = 0;
    MotorVar.Fault.bits.OverCurrent = 0;
    MotorVar.Fault.bits.DryRunning = 0;
  }
  U.IsMotorShort = MotorVar.Fault.bits.Short;
  U.IsMotorLock = MotorVar.Fault.bits.Lock;
  U.IsMotorOpenLoad = MotorVar.Fault.bits.OpenLoad;
  U.IsMotorDryRunning = MotorVar.Fault.bits.DryRunning;
  U.RestartComplete = MotorVar.RestartCompeleted;
  /* RestartCompeleted should be cleared immediately */
  MotorVar.RestartCompeleted = false;
}
/* 注释休眠相关代码 23.12.20 by lxs */
#if 0
static bool IsSleepSignalValid(void)
{
  bool Valid = false;

  /*
  PwmIn bus floating state is false
  n/fpwm ,fpwm = 50Hz, n = 6, n/fpwm = 120ms
  Measured time is 100ms
  */
  if ((U.PwmInIdleTime > 100) && (U.PwmInPinSts == false))
  {
    Valid = true;
  }

  return Valid;
}
#endif

static void Task_10ms(void)
{
  if ((Time.Ms % 10) != 0)
  {
    return;
  }
/* 注释复位相关代码 24.03.26 by lxs */
#if 0
  static u8 ResetDelayCnt = 0u;
  /* 修改复位存储逻辑顺序 23.08.30 by lxs */
  if (Y.ChipReset == true)
  {
    if (ResetDelayCnt >= MAIN_DELAY_AFTER_DFLASH_WRITE)
    {
      SDK_ChipReset();
    }
    else
    {
      DTC_RAM2Flash();
    }
    ResetDelayCnt++;
  }
  else
  {
    ResetDelayCnt = 0;
  }
#endif

/* 注释休眠相关代码 23.12.20 by lxs */
#if 0
  /* fct test, 21.07.30 by yhd */
  /* 消除polyspace警告 23.10.29 by lxs */
  if (fcttest_JumpInFlag != 0u)
  {
    if ((IsSleepSignalValid() != 0u) && (testmode_GoToSleep != 0u))
    {
      Y.ChipSleep = true;
    }
    else
    {
      Y.ChipSleep = false;
    }
  }
   /* 修改休眠存储逻辑顺序 23.08.30 by lxs */
  static u8 SleepDelayCnt = 0u;
  if (Y.ChipSleep == true)
  {
    if (SleepDelayCnt >= MAIN_DELAY_AFTER_DFLASH_WRITE)
    {
      SDK_ChipSleep();
    }
    else
    {
      DTC_RAM2Flash();
    }
    SleepDelayCnt++;
  }
  else
  {
    SleepDelayCnt = 0;
  }
#endif

  PowerUpTimeCnt();
  /* 实际转速为0时，存储故障 24.03.27 by lxs */
  if (MotorVar.CurrentSpeed == 0)
  {
    DTC_RAM2Flash();
  }
#if 0
  if (IsVBatLoss())
  {
    if (MotorVar.CurrentSpeed == 0)
    {
      DTC_RAM2Flash();
    }
  }
#endif
  
  /* fct test, 21.07.30 by yhd */
  /* 消除polyspace警告 23.10.29 by lxs */
  if (testmode_JumpInFlag != 0u)
  {
    PwmOut50Hz_50Duty();
  }
  else
  {
#if !DEBUG_DIAG_OUT
    if (Y.FeedBackBusStatus == true)
    {
      SDK_MCUDiagOut(ePinOutHigh);
    }
    else
    {
      SDK_MCUDiagOut(ePinOutLow);
    }
#endif

    MotorVar.RestartEnable = Y.MotorRestartEnable;

    Motor_PeriodTask();
    /* 检测到掉电时，将目标转速设为0 23.08.28 by lxs */
    if (IsVBatLoss())
    {
      Y.TargetSpeedLimited = 0;
    }

    Motor_SetSpeed(Y.TargetSpeedLimited);
  }
}

/* fct test, 21.07.30 by yhd */
static void Task_50ms(void)
{
  if ((Time.Ms % 50) != 0)
  {
    return;
  }

  SelfSignalHandle();
  TestMode();
}

static void Task_100ms(void)
{
  if ((Time.Ms % 100) != 0)
  {
    return;
  }

  /*修改结束*/
  SDK_FeedWDOG();
  UpdateDTCRecords();

#if DEBUG_USE_SCI
  SCIEnMonitor();
#endif
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:UpdateDTCRecords
* Description:
* 1.更新故障标志
* 2.记录故障的重新上电次数，故障标志
* 3.记录故障总次数
* 4.通过串口命令清除DFlash数据
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
static void UpdateDTCRecords(void)
{
  static u8 LastMShortCnt = 0u;
  static u8 LastMOpenCnt = 0u;
  static u8 LastMLockCnt = 0u;
  static FaultFlags_t LastFaultFlag = {.R = 0uL};
  FaultFlags_t FaultFlag = {.R = 0uL};
  u8 i = 0u;
  /* 获取故障标志，22.01.10 by yhd */
  FaultFlag.B.BatHigh = (Y.VoltageStatus > 0);
  FaultFlag.B.BatLow = (Y.VoltageStatus < 0);
  FaultFlag.B.ChipTHigh = (Y.AmbTStatus > 0);
  FaultFlag.B.ChipTLow = (Y.AmbTStatus < 0);
  FaultFlag.B.MotorShort = (MotorVar.Fault.bits.Short);
  FaultFlag.B.MotorOpen = (MotorVar.Fault.bits.OpenLoad);
  FaultFlag.B.MotorLock = (MotorVar.Fault.bits.Lock);
  /* 增加干运行故障 23.10.30 by lxs */
  FaultFlag.B.MotorDryRunning = (MotorVar.Fault.bits.DryRunning);
  FaultFlag.B.MotorShortBAT =
    ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_SHORT_BAT_HEX) >> MOTOR_API_FAULT_RECORD_MSK_SHORT_BAT_CNT);
  FaultFlag.B.MotorShortGND =
    ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_SHORT_GND_HEX) >> MOTOR_API_FAULT_RECORD_MSK_SHORT_GND_CNT);
  FaultFlag.B.MotorSpeedOutRange = ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_SPEED_OUT_RANGE_HEX) >>
                                    MOTOR_API_FAULT_RECORD_MSK_SPEED_OUT_RANGE_CNT);
  FaultFlag.B.MotorSpeedOutRange_Inc = ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_SPEED_OUT_RANGE_INC_HEX) >>
                                        MOTOR_API_FAULT_RECORD_MSK_SPEED_OUT_RANGE_INC_CNT);
  FaultFlag.B.MotorSpeedTooLow = ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_SPEED_TOO_LOW_HEX) >>
                                  MOTOR_API_FAULT_RECORD_MSK_SPEED_TOO_LOW_CNT);
  FaultFlag.B.MotorSpeedTooHigh = ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_SPEED_TOO_HIGH_HEX) >>
                                   MOTOR_API_FAULT_RECORD_MSK_SPEED_TOO_HIGH_CNT);
  FaultFlag.B.MotorCurrentOutRange = ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_OVER_CURRENT_HEX) >>
                                      MOTOR_API_FAULT_RECORD_MSK_OVER_CURRENT_CNT);
  FaultFlag.B.MotorDrvErr =
    ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_DRV_ERR_HEX) >> MOTOR_API_FAULT_RECORD_MSK_DRV_ERR_CNT);
  FaultFlag.B.MotorBemfOutRange = ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_BEMF_OUT_RANGE_HEX) >>
                                   MOTOR_API_FAULT_RECORD_MSK_BEMF_OUT_RANGE_CNT);
  FaultFlag.B.MotorDrvOverCurrent =
    ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_DRV_OC_HEX) >> MOTOR_API_FAULT_RECORD_MSK_DRV_OC_CNT);
  FaultFlag.B.MotorDrvOverTemp =
    ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_DRV_OT_HEX) >> MOTOR_API_FAULT_RECORD_MSK_DRV_OT_CNT);
  FaultFlag.B.MotorDrvVCCLow =
    ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_DRV_VCC_LOW_HEX) >> MOTOR_API_FAULT_RECORD_MSK_DRV_VCC_LOW_CNT);
  FaultFlag.B.MotorDrvVGLow =
    ((MotorVar.FaultRecord & MOTOR_API_FAULT_RECORD_MSK_DRV_VG_LOW_HEX) >> MOTOR_API_FAULT_RECORD_MSK_DRV_VG_LOW_CNT);
  /*芯片故障记录总故障, 2023.12.11 by lxs */ 
  FaultFlag.B.ChipFault = (ChipFaults.reg != 0u);
#if 0
  FaultFlag.B.SysClkFail = ChipFaults.bit.SysClkFail;

  FaultFlag.B.WDogRst = ChipFaults.bit.WDogRst;
  FaultFlag.B.CPUParityRst = ChipFaults.bit.CPUParityRst;
  FaultFlag.B.SRAMParity = ChipFaults.bit.SRAMParity;
  FaultFlag.B.FlashBitErr1 = ChipFaults.bit.FlashBitErr1;
  FaultFlag.B.FlashBitErr2 = ChipFaults.bit.FlashBitErr2;
  FaultFlag.B.sram_wr_prot = ChipFaults.bit.sram_wr_prot;
  FaultFlag.B.stack_prot = ChipFaults.bit.stack_prot;
  FaultFlag.B.exec_prot = ChipFaults.bit.exec_prot;

  FaultFlag.B.bad_access = ChipFaults.bit.bad_access;
  FaultFlag.B.SCI_FE = ChipFaults.bit.SCI_FE;
  FaultFlag.B.SCI_OV = ChipFaults.bit.SCI_OV;
  FaultFlag.B.dma_read_err = ChipFaults.bit.dma_read_err;
  FaultFlag.B.dma_write_err = ChipFaults.bit.dma_write_err;
  FaultFlag.B.reload_error_evt = ChipFaults.bit.reload_error_evt;
#endif
  DTC_UpdateRecord(eDTCIdxBatHigh, FaultFlag.B.BatHigh);
  DTC_UpdateRecord(eDTCIdxBatLow, FaultFlag.B.BatLow);
  DTC_UpdateRecord(eDTCIdxChipTHigh, FaultFlag.B.ChipTHigh);
  DTC_UpdateRecord(eDTCIdxChipTLow, FaultFlag.B.ChipTLow);
  DTC_UpdateRecord(eDTCIdxMotorShort, FaultFlag.B.MotorShort);
  DTC_UpdateRecord(eDTCIdxMotorOpen, FaultFlag.B.MotorOpen);
  DTC_UpdateRecord(eDTCIdxMotorLock, FaultFlag.B.MotorLock);
  /* 增加干运行故障 23.10.30 by lxs */
  DTC_UpdateRecord(eDTCIdxMotorMotorDryRunning, FaultFlag.B.MotorDryRunning);
  DTC_UpdateRecord(eDTCIdxMotorShortBAT, FaultFlag.B.MotorShortBAT);
  DTC_UpdateRecord(eDTCIdxMotorShortGND, FaultFlag.B.MotorShortGND);
  DTC_UpdateRecord(eDTCIdxMotorSpeedOutRange, FaultFlag.B.MotorSpeedOutRange);
  DTC_UpdateRecord(eDTCIdxMotorSpeedOutRange_Inc, FaultFlag.B.MotorSpeedOutRange_Inc);
  DTC_UpdateRecord(eDTCIdxMotorSpeedTooLow, FaultFlag.B.MotorSpeedTooLow);
  DTC_UpdateRecord(eDTCIdxMotorSpeedTooHigh, FaultFlag.B.MotorSpeedTooHigh);
  DTC_UpdateRecord(eDTCIdxMotorCurrentOutRange, FaultFlag.B.MotorCurrentOutRange);

  DTC_UpdateRecord(eDTCIdxMotorDrvErr, FaultFlag.B.MotorDrvErr);
  DTC_UpdateRecord(eDTCIdxMotorBemfOutRange, FaultFlag.B.MotorBemfOutRange);
  DTC_UpdateRecord(eDTCIdxMotorDrvOverCurrent, FaultFlag.B.MotorDrvOverCurrent);
  DTC_UpdateRecord(eDTCIdxMotorDrvOverTemp, FaultFlag.B.MotorDrvOverTemp);
  DTC_UpdateRecord(eDTCIdxMotorDrvVCCLow, FaultFlag.B.MotorDrvVCCLow);
  DTC_UpdateRecord(eDTCIdxMotorDrvVGLow, FaultFlag.B.MotorDrvVGLow);
  DTC_UpdateRecord(eDTCIdxChipFaut, FaultFlag.B.ChipFault);
#if 0
  DTC_UpdateRecord(eDTCIdxSysClkFail, FaultFlag.B.SysClkFail);

  DTC_UpdateRecord(eDTCIdxWDogRst, FaultFlag.B.WDogRst);
  DTC_UpdateRecord(eDTCIdxCPUParityRst, FaultFlag.B.CPUParityRst);
  DTC_UpdateRecord(eDTCIdxSRAMParity, FaultFlag.B.SRAMParity);
  DTC_UpdateRecord(eDTCIdxFlashBitErr1, FaultFlag.B.FlashBitErr1);
  DTC_UpdateRecord(eDTCIdxFlashBitErr2, FaultFlag.B.FlashBitErr2);
  DTC_UpdateRecord(eDTCIdxsram_wr_prot, FaultFlag.B.sram_wr_prot);
  DTC_UpdateRecord(eDTCIdxstack_prot, FaultFlag.B.stack_prot);
  DTC_UpdateRecord(eDTCIdxexec_prot, FaultFlag.B.exec_prot);
  DTC_UpdateRecord(eDTCIdxbad_access, FaultFlag.B.bad_access);

  DTC_UpdateRecord(eDTCIdxSCI_FE, FaultFlag.B.SCI_FE);
  DTC_UpdateRecord(eDTCIdxSCI_OV, FaultFlag.B.SCI_OV);
  DTC_UpdateRecord(eDTCIdxdma_read_err, FaultFlag.B.dma_read_err);
  DTC_UpdateRecord(eDTCIdxdma_write_err, FaultFlag.B.dma_write_err);
  DTC_UpdateRecord(eDTCIdxreload_error_evt, FaultFlag.B.reload_error_evt);
#endif

  /* 计算故障总计数，22.01.10 by yhd */
  for (i = 0u; i < eDTCRecordsNum; i++)
  {
    if (((((FaultFlag.R >> i) & 0x1u) > ((LastFaultFlag.R >> i) & 0x1u)) && (DTCVar.FaultTotalCnt[i] < 0xFFu))\
    && (i != eDTCIdxMotorShort) && (i != eDTCIdxMotorOpen) && (i != eDTCIdxMotorLock))
    {
      DTCVar.FaultTotalCnt[i]++;
      IsDTCUpdated = true;
    }
  }

  if ((FaultFlag.B.MotorShort != 0u) && (DW.MotorRestartAndFaultCnt_bnwn.ShortCntLast_PreviousInput > LastMShortCnt) &&
      (DTCVar.FaultTotalCnt[eDTCIdxMotorShort] < 0xFFu))
  {
    DTCVar.FaultTotalCnt[eDTCIdxMotorShort]++;
    IsDTCUpdated = true;
  }
  LastMShortCnt = DW.MotorRestartAndFaultCnt_bnwn.ShortCntLast_PreviousInput;

  if ((FaultFlag.B.MotorOpen != 0u) && (DW.MotorRestartAndFaultCnt_bnwn.OpenCntLast_PreviousInput > LastMOpenCnt) &&
      (DTCVar.FaultTotalCnt[eDTCIdxMotorOpen] < 0xFFu))
  {
    DTCVar.FaultTotalCnt[eDTCIdxMotorOpen]++;
    IsDTCUpdated = true;
  }
  LastMOpenCnt = DW.MotorRestartAndFaultCnt_bnwn.OpenCntLast_PreviousInput;

  if ((FaultFlag.B.MotorLock != 0u) && (DW.MotorRestartAndFaultCnt_bnwn.LockCntLast_PreviousInput > LastMLockCnt) &&
      (DTCVar.FaultTotalCnt[eDTCIdxMotorLock] < 0xFFu))
  {
    DTCVar.FaultTotalCnt[eDTCIdxMotorLock]++;
    IsDTCUpdated = true;
  }
  LastMLockCnt = DW.MotorRestartAndFaultCnt_bnwn.LockCntLast_PreviousInput;

  LastFaultFlag = FaultFlag;

  /* 清除DataFlash, 22.01.10 by yhd */
  DTC_ClrDFlash();
}

static void SCIEnMonitor(void)
{
  static bool SCIEn = false;

  if (SCIEn)
  {
    return;
  }

  if (DebugVar.SCIEn && !SCIEn)
  {
    SCIEn = true;

    SDK_SCIInitLater();
  }
}
/* 关闭LIN收发器函数 24.01.05 by lxs */
static void TurnOffLinTransceiver(void)
{
  gpio_set_data_out(GPIO_C, GPIO_IO_7,true);
}
