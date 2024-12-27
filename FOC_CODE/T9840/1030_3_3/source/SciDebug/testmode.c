#ifndef TESTMODE_C
#define TESTMODE_C

#include "testmode.h"
#include "ADCSample.h"
#include "AppMain.h"
#include "DTC.h"
#include "IsrHandler.h"
#include "MotorAPI.h"
#include "PwmIn.h"
#include "VBatMonitor.h"
#include "bemf_control.h"
#include "commons.h"
#include "debug.h"
#include "freemaster.h"
#include "main.h"
#include "rtwtypes.h"
#include "uartdebug.h"

#define CurrentADToAmp(AD) ((u16)((u32)(AD)*125u >> 12))

SCIDebug_t SCIDebug = {
  {
    0,
    0,
    1000,
  },
};

/* Define test mode defines and variables, 21.07.30 by yhd */
// Terminal Test
#define TerminalTestPwmInFreqMin 380u // Hz
#define TerminalTestPwmInFreqMax 420u // Hz
#define TerminalTestPwmInPeriodMax (Mcr_PwmInCLK / TerminalTestPwmInFreqMin)
#define TerminalTestPwmInPeriodMin (Mcr_PwmInCLK / TerminalTestPwmInFreqMax)

#define TerminalTestDutyCycleMaxError 20 //*0.1%

#define TerminalTestEnteyDutyCycle 300 //*0.1%
#define TerminalTestEnteyDutyCycleMin (TerminalTestEnteyDutyCycle - TerminalTestDutyCycleMaxError)
#define TerminalTestEnteyDutyCycleMax (TerminalTestEnteyDutyCycle + TerminalTestDutyCycleMaxError)
#define TerminalTestStep1DutyCycle 400 //*0.1%
#define TerminalTestStep1DutyCycleMin (TerminalTestStep1DutyCycle - TerminalTestDutyCycleMaxError)
#define TerminalTestStep1DutyCycleMax (TerminalTestStep1DutyCycle + TerminalTestDutyCycleMaxError)
#define TerminalTestStep2DutyCycle 500 //*0.1%
#define TerminalTestStep2DutyCycleMin (500 - TerminalTestDutyCycleMaxError)
#define TerminalTestStep2DutyCycleMax (800 + TerminalTestDutyCycleMaxError)
#define TerminalTestStep3DutyCycle 900 //*0.1%
#define TerminalTestStep3DutyCycleMin (TerminalTestStep3DutyCycle - TerminalTestDutyCycleMaxError)
#define TerminalTestStep3DutyCycleMax (TerminalTestStep3DutyCycle + TerminalTestDutyCycleMaxError)

#define TerminalTestTemperatureUpLimit 140
#define TerminalTestTemperatureBelowLimit 0

#define TerminalTestVSUpLimit 170
#define TerminalTestVSBelowLimit 150
#define TerminalTestVDHUpLimit 0
#define TerminalTestVDHBelowLimit 0
#define TerminalTestMONUpLimit 120
#define TerminalTestMONBelowLimit 110
#define TerminalTestVSDUpLimit 125
#define TerminalTestVSDBelowLimit 105
#define TerminalTestVCPUpLimit 145
#define TerminalTestVCPBelowLimit 125
#define TerminalTestVDDPUpLimit 178
#define TerminalTestVDDPBelowLimit 168
#define TerminalTestVBGUpLimit 175
#define TerminalTestVBGBelowLimit 165
#define TerminalTestVAREFUpLimit 235
#define TerminalTestVAREFBelowLimit 225
#define TerminalTestVDDCUpLimit 240
#define TerminalTestVDDCBelowLimit 230

u8 testmode_JumpInFlag = FALSE;
u8 fcttest_JumpInFlag = FALSE;
u8 terminaltest_JumpInFlag = FALSE;

u8 testmode_debug_cmd = 1;
u8 testmode_BrigeOutEn = 0;
u8 testmode_PWMOut50HzEn = 0;
u8 testmode_PWMOut100HzEn = 0;
u8 testmode_PWMOut100HzEnTmp = 0;
u8 testmode_GoToSleep = 0;

s16 TestModeCmdSpeed = 0;

bool TestMOSRunning = false;

bool IsPhaseVoltageAbnormal = false;

u8 sample_done = 0;

u16 PhaseVoltageUSum = 0;
u16 PhaseVoltageVSum = 0;
u16 PhaseVoltageWSum = 0;
u8 PhaseVoltageUCnt = 0;
u8 PhaseVoltageVCnt = 0;
u8 PhaseVoltageWCnt = 0;

u8 testmode_Command = 0;

void SelfSignalHandle(void);
void FctTestMode(void);
void TerminalTestMode(void);
void TestMode(void);

/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:Test_MOS
* Description:
*   Fct mos test
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
u16 debug_pwmout = 10000;
void Test_MOS(void)
{
  u16 pwmout;
  static u8 state = 0;
  static u16 pwmout_ramp = 0;
  static u8 exit_flag = 1;
  static u8 exited_flag = 1;

  // static u16 count_max_backup;
  // static s16 old_inc;
  // static s16 old_mult;

  if ((testmode_BrigeOutEn == 0) && (exit_flag == 1))
  {
    if (exited_flag == 0)
    {
      Motor_ChangeModeTo(mode_idle);

      state = 0;
      pwmout_ramp = 0;
      exited_flag = 1;
    }
    return;
  }

  exited_flag = 0;

  if (testmode_BrigeOutEn == 1)
  {
    if (pwmout_ramp < debug_pwmout)
    {
      pwmout_ramp += 100;
      if (pwmout_ramp > debug_pwmout)
      {
        pwmout_ramp = debug_pwmout;
      }
    }
    exit_flag = 0;
  }
  else
  {
    if (pwmout_ramp > 100)
    {
      pwmout_ramp -= 100;
      exit_flag = 0;
    }
    else
    {
      exit_flag = 1;
    }
  }

  pwmout = (u32)2400 * (u32)pwmout_ramp / 10000;

  switch (state)
  {
  case 0:
    // count_max_backup = READ_REG_U16(AADDR_PWMN_CNT_MAX_RELOAD);
    // old_inc = pre_pwm_get_sinc();
    // old_mult = pre_pwm_get_smult();

    pre_pwm_control(false); // pre_pwm off
    pre_pwm_enable_dma(false);
    pre_pwm_enable_inc(false);

    WRITE_REG_16(AADDR_PWMN_CNT_MAX_RELOAD, 2400);
  case 1:
    REG_PWMN_PWM0_C0_RELOAD = pwmout;
    REG_PWMN_PWM1_C0_RELOAD = 0;
    REG_PWMN_PWM2_C0_RELOAD = pwmout;
    REG_PWMN_PWM0_ON_RELOAD = 3;
    REG_PWMN_PWM1_ON_RELOAD = 3;
    REG_PWMN_PWM2_ON_RELOAD = 0;

    state = 2;
    break;
  case 2:
    REG_PWMN_PWM0_C0_RELOAD = pwmout;
    REG_PWMN_PWM1_C0_RELOAD = pwmout;
    REG_PWMN_PWM2_C0_RELOAD = 0;
    REG_PWMN_PWM0_ON_RELOAD = 0;
    REG_PWMN_PWM1_ON_RELOAD = 3;
    REG_PWMN_PWM2_ON_RELOAD = 3;

    state = 3;
    break;
  case 3:
    REG_PWMN_PWM0_C0_RELOAD = 0;
    REG_PWMN_PWM1_C0_RELOAD = pwmout;
    REG_PWMN_PWM2_C0_RELOAD = pwmout;
    REG_PWMN_PWM0_ON_RELOAD = 3;
    REG_PWMN_PWM1_ON_RELOAD = 0;
    REG_PWMN_PWM2_ON_RELOAD = 3;

    state = 1;
    break;
  default:
    break;
  }
}
/****************************************************************
 * FUNCTION :
 * DESCRIPTION :
 * INPUTS :
 * OUTPUTS :
 *****************************************************************/

/* Add new debug cmd, 21.07.30 by yhd */
union {
  u16 Val;
  struct
  {
    u8 L;
    u8 H;
  } Byte;
} Val1, Val2, Val3, Val4;

void SelfSignalHandle(void)
{
  /* 修改串口调试命令，22.01.10 by yhd */
  u8 UartFrameID = 0u;
  u8 MainCmd = 0u;
  u8 SubCmd = 0u;
  u8 Tmp1 = 0u;
  u8 Tmp2 = 0u;

  u8 TxBuf[8] = {0};
  u8 i;
  u8 TxEn = 1;

  UartFrameID = Rd_Sig_Id();
  if (UartFrameID == RX_ID0)
  {
    MainCmd = Rd_Sig_U8(0);
    switch (MainCmd)
    {
    case 0xF8u:
      SubCmd = Rd_Sig_U8(1u);

      TxBuf[0u] = SubCmd;
      switch (SubCmd)
      {
      case 0u: {
        TxBuf[0u] = (ADCResults.Current.DCFlt + 32768u) >> 8u;
        TxBuf[1u] = (ADCResults.Current.DCFlt + 32768u) & 0xFFu;
        TxBuf[2u] = (ADCResults.Current.DC + 32768u) >> 8u;
        TxBuf[3u] = (ADCResults.Current.DC + 32768u) & 0xFFu;
        TxBuf[4u] = (PwmInAPI.Freq + 32768u) >> 8u;
        TxBuf[5u] = (PwmInAPI.Freq + 32768u) & 0xFFu;
        TxBuf[6u] = ((1000u - PwmInAPI.LowDuty) + 32768u) >> 8u;
        TxBuf[7u] = ((1000u - PwmInAPI.LowDuty) + 32768u) & 0xFFu;
      }
      break;
      case 1u:
        TxBuf[1u] = Rd_Sig_U8(6u);
        for (i = 0u; i < 6u; i++)
        {
          Tmp1 = Rd_Sig_U8(6u) + i;
          if (Tmp1 < eDTCRecordsNum)
          {
            TxBuf[2u + i] = DTCVar.FaultTotalCnt[Tmp1];
          }
          else
          {
            TxBuf[2u + i] = 0u;
          }
        }
        break;
      case 2u: {
        TxBuf[1u] = Version.ProductVersion >> 8u;
        TxBuf[2u] = Version.ProductVersion & 0xFFu;
        TxBuf[3u] = Version.InnerVersion.reg >> 8u;
        TxBuf[4u] = Version.InnerVersion.reg & 0xFFu;
        TxBuf[5u] = Version.FctVersion;
        TxBuf[6u] = Version.DebugVersion;
      }
      break;
        case 3u: {
        TxBuf[0u] = (Y.TargetSpeedLimited + 32768u) >> 8;
        TxBuf[1u] = (Y.TargetSpeedLimited + 32768u) & 0xFFu;
        TxBuf[2u] = (Y.TargetSpeed + 32768u) >> 8;
        TxBuf[3u] = (Y.TargetSpeed + 32768u) & 0xFFu;
        TxBuf[4u] = (MotorVar.TargetSpeed + 32768u) >> 8u;
        TxBuf[5u] = (MotorVar.TargetSpeed + 32768u) & 0xFFu;
        TxBuf[6u] = (MotorVar.CurrentSpeed + 32768u) >> 8u;
        TxBuf[7u] = (MotorVar.CurrentSpeed + 32768u) & 0xFFu;
      }
      break;

      case 4u: {
        if (Y.VoltageStatus < 0)
        {
          Tmp1 = 0;
        }
        else if (Y.VoltageStatus > 0)
        {
          Tmp1 = 2u;
        }
        else
        {
          Tmp1 = 1u;
        }

        if (Y.AmbTStatus < 0)
        {
          Tmp2 = 0u;
        }
        else if (Y.AmbTStatus > 0)
        {
          Tmp2 = 2u;
        }
        else
        {
          Tmp2 = 1u;
        }
        /* 当前故障增加干运行 24.03.26 by lxs */
        TxBuf[1u] = (MotorVar.Fault.bits.Short << 0u) | (MotorVar.Fault.bits.Short << 1u) |
                    (MotorVar.Fault.bits.OpenLoad << 2u) | (MotorVar.Fault.bits.Lock << 3) | (Tmp1 << 4u) |
                    (Tmp2 << 6u) | (MotorVar.Fault.bits.DryRunning << 7u);
        TxBuf[2u] = (0u << 0u) | ((u8)((PwmInAPI.BusIdleTime > 1000u) && (PwmInAPI.BusState == 0u)) << 1u) |
                    ((u8)((PwmInAPI.BusIdleTime > 1000u) && (PwmInAPI.BusState != 0u)) << 2u);
        TxBuf[3u] = (MotorVar.FaultRecord >> 8) & 0xFFu;
        TxBuf[4u] = MotorVar.FaultRecord & 0xFFu;
        TxBuf[5u] = DW.MotorRestartAndFaultCnt_bnwn.ShortCntLast_PreviousInput;
        TxBuf[6u] = DW.MotorRestartAndFaultCnt_bnwn.OpenCntLast_PreviousInput;
        TxBuf[7u] = DW.MotorRestartAndFaultCnt_bnwn.LockCntLast_PreviousInput;
      }
      break;
      case 5u: {
        TxBuf[2u] = (ADCResults.Temperature.Ambient + 32768u) >> 8u;
        TxBuf[3u] = (ADCResults.Temperature.Ambient + 32768u) & 0xFFu;
        // TxBuf[4u] = (ADCResults.Temperature.Chip + 32768u) >> 8u;
        // TxBuf[5u] = (ADCResults.Temperature.Chip + 32768u) & 0xFFu;
        TxBuf[6u] = ((ADCResults.Voltage.Bat * 11) + 32768u) >> 8u;
        TxBuf[7u] = ((ADCResults.Voltage.Bat * 11) + 32768u) & 0xFFu;
      }
      break;
      case 6u:
        TxBuf[2u] = (MotorVar.WindMillingSpeed + 32768u) >> 8;
        TxBuf[3u] = (MotorVar.WindMillingSpeed + 32768u) & 0xFFu;
        break;
      case 7u:
        TxBuf[1u] = Rd_Sig_U8(6u);
        for (i = 0u; i < 6u; i++)
        {
          Tmp1 = Rd_Sig_U8(6u) + i;
          if (Tmp1 < eDTCRecordsNum)
          {
            TxBuf[2u + i] = DTCVar.Records[Tmp1].RePowerCnt;
          }
          else
          {
            TxBuf[2u + i] = 0u;
          }
        }
        break;
      case 8u:
        DTC_ClrDFlashEn = 1u;
        Rst_Sig_U8(1);
        break;
      default: /* 不做任何处理 */

        break;
      }
      break;
    default:
      TxEn = 0;
      break;
    }

    if (TxEn == 1)
    {
      for (i = 0; i < 8; i++)
      {
        Wr_Sig_U8(i, TxBuf[i]);
      }
      UartSendFrameStart(0x20);
    }
  }
}

/****************************************************************
 * FUNCTION :
 * DESCRIPTION :
 * INPUTS :
 * OUTPUTS :
 *****************************************************************/
/* impelement fct test, 21.07.30 by yhd*/
void FctTestMode(void)
{
  static u8 testmode_counter = 100;
  static u8 testmode_Command_Last = 0;
  static u8 testmode_TxEn = 0;
  static u8 testmode_TxId = 0;
  u8 testmodebuffer[8];
  u8 i = 0;

  // after power up,there is 5S get shakehand command from  Super_Computer
  if ((fcttest_JumpInFlag == FALSE) && (testmode_counter > 0))
  {
    /*5S cnt time up then stop get shakehand command from  Super_Computer*/
    testmode_counter--;
    testmode_Command = Rd_Sig_Id();
    /*get shakehand command then jump into test mode*/
    if ((testmode_Command == RX_ID2) && (Rd_Sig_U8(0) == 0x01) && (Rd_Sig_U8(4) == 0x05) && (Rd_Sig_U8(7) == 0x08))
    {
      fcttest_JumpInFlag = TRUE;
      testmode_counter = 0;
      Motor_SetSpeed(0);
    }
  }
  else
  {
    testmode_counter = 0;
  }

  // jump into test mode if ture
  if (fcttest_JumpInFlag == TRUE)
  {
    testmode_Command = Rd_Sig_Id();

    if (testmode_Command != RX_ID3)
    {
      testmode_BrigeOutEn = 0;
      // TestMOSRunning = true;
      // Test_MOS();
      // TestMOSRunning = false;
    }

    if (testmode_Command != RX_ID4)
    {
      testmode_PWMOut50HzEn = 0;
      testmode_PWMOut100HzEn = 0;
      testmode_PWMOut100HzEnTmp = 0;
      sample_done = 0;
    }

    if ((testmode_Command == RX_ID4) && (testmode_Command_Last != RX_ID4))
    {
      PhaseVoltageUSum = 0;
      PhaseVoltageVSum = 0;
      PhaseVoltageWSum = 0;
      PhaseVoltageUCnt = 0;
      PhaseVoltageVCnt = 0;
      PhaseVoltageWCnt = 0;
    }

    if (testmode_Command != RX_ID5)
    {
      testmode_GoToSleep = 0;
    }

    switch (testmode_Command)
    {
    case RX_ID2: {
      u16 ADVal = 0;
      testmode_TxEn = 1;
      testmode_TxId = 0x02;
      testmodebuffer[0] = 0x01;
      testmodebuffer[1] = 0x02;
      testmodebuffer[2] = 0x03;
      testmodebuffer[3] = 0x04;
      testmodebuffer[4] = 0x05;
      testmodebuffer[5] = 0x06;
      testmodebuffer[6] = 0x07;
      testmodebuffer[7] = 0x08;

      if (PhaseVoltageUCnt < 8)
      {
        ADVal = ADCResults.Voltage.PhaseU;
        if (ADVal != 0xFFFFu)
        {
          PhaseVoltageUSum += ADVal;
          PhaseVoltageUCnt++;
        }
      }
      if (PhaseVoltageVCnt < 8)
      {
        ADVal = ADCResults.Voltage.PhaseV;
        if (ADVal != 0xFFFFu)
        {
          PhaseVoltageVSum += ADVal;
          PhaseVoltageVCnt++;
        }
      }
      if (PhaseVoltageWCnt < 8)
      {
        ADVal = ADCResults.Voltage.PhaseW;
        if (ADVal != 0xFFFFu)
        {
          PhaseVoltageWSum += ADVal;
          PhaseVoltageWCnt++;
        }
      }

      break;
    }
    case RX_ID3: {
      static u8 delaycnt = 0, delaycnt2 = 0;
      static u8 framecnt = 0;

      if (testmode_Command_Last != RX_ID3)
      {
        delaycnt = 0;
        delaycnt2 = 0;
        framecnt = 0;

        {

          if (((PhaseVoltageUCnt != 0) && ((PhaseVoltageUSum / PhaseVoltageUCnt + 10 > ADCResults.Voltage.Bat) ||
                                           (PhaseVoltageUSum / PhaseVoltageUCnt < 10))) ||
              ((PhaseVoltageVCnt != 0) && ((PhaseVoltageVSum / PhaseVoltageVCnt + 10 > ADCResults.Voltage.Bat) ||
                                           (PhaseVoltageVSum / PhaseVoltageVCnt < 10))) ||
              ((PhaseVoltageWCnt != 0) && ((PhaseVoltageWSum / PhaseVoltageWCnt + 10 > ADCResults.Voltage.Bat) ||
                                           (PhaseVoltageWSum / PhaseVoltageWCnt < 10))))
          {
            IsPhaseVoltageAbnormal = true;
          }
          else
          {
            IsPhaseVoltageAbnormal = false;
          }
        }

        if (IsPhaseVoltageAbnormal == false)
        {
          testmode_BrigeOutEn = 1;
        }
      }

      if (delaycnt < 100)
      {
        delaycnt++;
      }
      else
      {
      }

      if (delaycnt > 4) // delay 200ms to samp
      {
        testmode_TxEn = 1;
        testmode_TxId = 0x04;

        if (framecnt == 0)
        {
          framecnt = 1;
          testmodebuffer[0] = 0x00; // subid
          testmodebuffer[1] = (FlashECUInfo[0] & 0xF0) | ((Version.ProductVersion >> 4) & 0x0F);
          testmodebuffer[2] = (FlashECUInfo[1] & 0x0f) | ((Version.ProductVersion & 0x0F) << 4);
          testmodebuffer[3] = FlashECUInfo[2];
          testmodebuffer[4] = FlashECUInfo[3];
          testmodebuffer[5] = FlashECUInfo[4];
          testmodebuffer[6] = FlashECUInfo[5];
          testmodebuffer[7] = FlashECUInfo[6];
        }
        else if (framecnt == 1)
        {
          framecnt = 2;
          testmodebuffer[0] = 0x01; // subid
          testmodebuffer[1] = FlashECUInfo[7];
          testmodebuffer[2] = FlashECUInfo[8];
          testmodebuffer[3] = FlashECUInfo[9];
          testmodebuffer[4] = FlashECUInfo[10];
          testmodebuffer[5] = FlashECUInfo[11];
          testmodebuffer[6] = (ADCResults.Voltage.Bat >> 8) & 0xFF;
          testmodebuffer[7] = ADCResults.Voltage.Bat & 0xFF;
        }
        else if (framecnt == 2)
        {
          framecnt = 3;
          testmodebuffer[0] = 0x02; // subid
          testmodebuffer[1] = (ADCResults.Temperature.Chip >> 8) & 0xFF;
          testmodebuffer[2] = ADCResults.Temperature.Chip & 0xFF;
          testmodebuffer[3] = (ADCResults.Current.DC >> 8) & 0xFF;
          testmodebuffer[4] = ADCResults.Current.DC & 0xFF;
          testmodebuffer[5] = ((1000 - PwmInAPI.LowDuty) >> 8) & 0xFF;
          testmodebuffer[6] = (1000 - PwmInAPI.LowDuty) & 0xFF;
          testmodebuffer[7] = 0;
        }
        else if (framecnt == 3)
        {
          if (delaycnt2 == 0)
          {
            testmodebuffer[0] = 0x03; // subid
            /* 将原内部版本号替换为FCT版本号 24.03.27 by lxs */
            testmodebuffer[1] = 0;
            testmodebuffer[2] = Version.FctVersion & 0xFF;
            /*
            Bit0:SysClkFail
            Bit1:WDogRst
            Bit2:CPUParityRst
            Bit3:SRAMParity
            Bit4:FlashBitErr1
            Bit5:FlashBitErr2
            Bit6:sram_wr_prot
            Bit7:stack_prot
            */
            testmodebuffer[3] = ChipFaults.reg & 0xFF;
            /*
            Bit0:exec_prot
            Bit1:bad access
            Bit2:SCI_FE
            Bit3:SCI_OV
            Bit4:dma_read_err
            Bit5:dma_write_err
            Bit6:reload_error_evt
            Bit7:overcurrent
            */
            testmodebuffer[4] = (ChipFaults.reg >> 8) & 0xFF;
            /*
            Bit0:DrvOc
            Bit1:DrvOT
            Bit2:VCC_UV
            Bit3:VG_UV
            Bit4:0
            Bit5:0
            Bit6:0
            Bit7:0
            */
            testmodebuffer[5] = (ChipFaults.reg >> 16) & 0xFF;
            testmodebuffer[6] = 0;
            testmodebuffer[7] = 0;
            delaycnt2++;
          }
          else
          {
            testmode_TxEn = 0;
            if (delaycnt2 < 1)
            {
              delaycnt2++;
            }
            else
            {
              delaycnt2 = 0;
              framecnt = 0;
            }
          }
        }

        if (IsPhaseVoltageAbnormal == true)
        {
          testmodebuffer[1] = 0;
          testmodebuffer[2] = 0;
          testmodebuffer[3] = 0;
          testmodebuffer[4] = 0;
          testmodebuffer[5] = 0;
          testmodebuffer[6] = 0;
          testmodebuffer[7] = 0;
        }

#if 0
                    u16 tmp = (u16)ADCResults.Current.DC + 32768;
                    testmodebuffer[0] = (tmp>>8) & 0xFF;
                    testmodebuffer[1] = tmp & 0xFF;
#endif
      }
    }
    break;
    case RX_ID4:
      testmode_TxEn = 0;
      if (testmode_PWMOut100HzEn == 0)
      {
        testmode_PWMOut50HzEn = 1;
      }
      break;
    case RX_ID5:
      testmode_TxEn = 0;
      testmode_GoToSleep = 1;
      break;
    default:
      testmode_TxEn = 0;
      break;
    }
  }

  if (testmode_TxEn == 1)
  {
    testmode_TxEn = 0;
    for (i = 0; i < 8; i++)
    {
      Wr_Sig_U8(i, testmodebuffer[i]);
    }
    UartSendFrameStart(testmode_TxId);
  }

  testmode_Command_Last = testmode_Command;
}
/****************************************************************
* FUNCTION    : TerminalTestMode
* DESCRIPTION : the function is used for terminal test of product,include
       signal judge,calibrate current zero and闁跨喓绂坢ple resistor coefficient,
       test static current
* INPUTS      :
* OUTPUTS     :
*****************************************************************/
void TerminalTestMode(void)
{
#if 0
  static u8 testmode_counter = 40; //50ms*40=2000ms

  if((terminaltest_JumpInFlag == FALSE)&&(testmode_counter > 0))
  {
    static u8 signal_counter = 20;//50ms*20 = 1000ms

    testmode_counter--;

    if((glIsPwmInShortGND == 0)
    && (glIsPwmInShortVBat == 0)
    && (glCalPeriodPulseWidth > TerminalTestPwmInPeriodMin)
    && (glCalPeriodPulseWidth < TerminalTestPwmInPeriodMax)
    && (glCalHighLevelDutyCycle < TerminalTestEnteyDutyCycleMax)
    && (glCalHighLevelDutyCycle > TerminalTestEnteyDutyCycleMin))
    {
        if(signal_counter > 0)
        {
            signal_counter--;
        }
        else
        {
            //Jump into testmode and stop motor
            terminaltest_JumpInFlag = TRUE;
            TestModeCmdSpeed = 0;
        }
    }
    else
    {
        signal_counter = 10;
    }
  }
  else
  {
    testmode_counter = 0;
  }

  if(terminaltest_JumpInFlag == TRUE)
  {
    static u8 state = 0;
    static u8 feedbacken = 0;
    static u8 lastfeedbacken = 0;
    static u16 low_time = 0;
    static u16 high_time = 0;
    static u8 feedpulsecnt = 0;

    if((glIsPwmInShortGND == 0)
    && (glIsPwmInShortVBat == 0)
    && (glCalPeriodPulseWidth > TerminalTestPwmInPeriodMin)
    && (glCalPeriodPulseWidth < TerminalTestPwmInPeriodMax))
    {
        if((glCalHighLevelDutyCycle < TerminalTestEnteyDutyCycleMax)
                && (glCalHighLevelDutyCycle > TerminalTestEnteyDutyCycleMin))
        {
            if(state != 0)
            {
                feedpulsecnt = 0;
                feedbacken = 0;
            }
            state = 0;
        }
        else if((glCalHighLevelDutyCycle < TerminalTestStep1DutyCycleMax)
        && (glCalHighLevelDutyCycle > TerminalTestStep1DutyCycleMin))
        {
            if(state != 1)
            {
                feedpulsecnt = 0;
                feedbacken = 0;
            }
            state = 1;
        }
        else if((glCalHighLevelDutyCycle < TerminalTestStep2DutyCycleMax)
                && (glCalHighLevelDutyCycle > TerminalTestStep2DutyCycleMin))
        {
            if(state != 2)
            {
                feedpulsecnt = 0;
                feedbacken = 0;
            }
            state = 2;
        }
        else if((glCalHighLevelDutyCycle < TerminalTestStep3DutyCycleMax)
                && (glCalHighLevelDutyCycle > TerminalTestStep3DutyCycleMin))
        {
            if(state != 3)
            {
                feedpulsecnt = 0;
                feedbacken = 0;
            }
            state = 3;
        }
        else
        {

        }
    }


    //Fault Jundge
    if(FastFaultJudge_DW.motorocfault == 1)
    {
        low_time  = 13;
        high_time = 1;
    }
    else if(FastFaultJudge_DW.motoropfault == 1)
    {
        low_time  = 11;
        high_time = 1;
    }
    else if((FastFaultJudge_DW.motorshortfault == 1)
            ||(FastFaultJudge_DW.motorvbatfault == 1))
    {
        low_time  = 9;
        high_time = 1;
    }
    else if((glTempOffChip > TerminalTestTemperatureUpLimit)
            ||(glTempOffChip < TerminalTestTemperatureBelowLimit)
            ||(glTempOnChip > TerminalTestTemperatureUpLimit)
            ||(glTempOnChip < TerminalTestTemperatureBelowLimit)
            //||(glTempSampleFault != 0)
            //||(glVtempAdErrFlag != 0)
            ||(glSysOverTempFault != 0)
           )
    {
        low_time  = 7;
        high_time = 1;
    }
    else if(((MotorCtrl_Par.targetspeed == 0)
             && ((ADCResults.CH_VS > TerminalTestVSUpLimit)
               ||(ADCResults.CH_VS < TerminalTestVSBelowLimit)
               //||(ADCResults.CH_MON > TerminalTestMONUpLimit)
               //||(ADCResults.CH_MON < TerminalTestMONBelowLimit)
               ||(ADCResults.CH_VSD > TerminalTestVSDUpLimit)
               ||(ADCResults.CH_VSD < TerminalTestVSDBelowLimit)
               ||(ADCResults.CH_VCP > TerminalTestVCPUpLimit)
               ||(ADCResults.CH_VCP < TerminalTestVCPBelowLimit)
               ||(ADCResults.CH_VDDP > TerminalTestVDDPUpLimit)
               ||(ADCResults.CH_VDDP < TerminalTestVDDPBelowLimit)
               ||(ADCResults.CH_VBG > TerminalTestVBGUpLimit)
               ||(ADCResults.CH_VBG < TerminalTestVBGBelowLimit)
               ||(ADCResults.CH_VAREF > TerminalTestVAREFUpLimit)
               ||(ADCResults.CH_VAREF < TerminalTestVAREFBelowLimit)
               ||(ADCResults.CH_VDDC > TerminalTestVDDCUpLimit)
               ||(ADCResults.CH_VDDC < TerminalTestVDDCBelowLimit)
              )
            )
            ||(glVDDPOverLoadFault != 0)||(glVDDCOverLoadFault != 0)
            ||(glSupplyShortFault != 0)||(glSupplyTimeOutFault != 0)
            ||(glVDDEXTOverLoadFault != 0)||(glVDDEXTOverVolFault != 0)
            ||(glVDDEXTShortFault != 0)||(glADC1VREFFault != 0)
            //||(glADC2VBGFault != 0)
            ||(glAdFault != 0)
            ||(glBrdvVSDHighVolFault != 0)||(glBrdvVSDLowVolFault != 0)
            ||(glBrdvVCPHighVolFault != 0)||(glBrdvVCPLowVol1Fault != 0)
            ||(glBrdvVCPLowVol2Fault != 0))
    {
        low_time  = 5;
        high_time = 1;
    }
    else
    {
        low_time  = 0;
        high_time = 0;
    }


    switch(state)
    {
      case 0x00:
          if(feedbacken == 0)
          {
              if(feedpulsecnt > 1)
              {
                  feedbacken = 0;
              }
              else
              {
                  feedpulsecnt++;

                  feedbacken = 1;
                  low_time  = 1;
                  high_time = 1;
              }
          }
          TestModeCmdSpeed = 0;
        break;
      case 0x01:
          if(feedbacken == 0)
          {
              if(feedpulsecnt > 1)
              {
                  feedbacken = 0;
              }
              else
              {
                  feedpulsecnt++;

                  feedbacken = 1;
                  if((high_time == 0) && (low_time == 0))
                  {
                      low_time  = 3;
                      high_time = 1;
                  }
              }
          }
         TestModeCmdSpeed = 0;
        break;
      case 0x02:
          if(feedbacken == 0)
          {
              if(feedpulsecnt > 1)
              {
                  feedbacken = 0;
              }
              else
              {
                  if((high_time == 0) && (low_time == 0))
                  {
                      feedbacken = 0;
                  }
                  else
                  {
                      feedpulsecnt++;
                      feedbacken = 1;
                  }
              }
          }
          if(glCalHighLevelDutyCycle < 500)
          {
            TestModeCmdSpeed = 1700;
          }
          else if(glCalHighLevelDutyCycle > 800)
          {
            TestModeCmdSpeed = Mcr_MotorSpeedMax;
          }
          else
          {
              TestModeCmdSpeed = 1700 + (glCalHighLevelDutyCycle - 500)*(Mcr_MotorSpeedMax - 1700)/(800 - 500);
          }
        break;
      case 0x03:
          if(feedbacken == 0)
          {
              if(feedpulsecnt > 1)
              {
                  feedbacken = 0;
              }
              else
              {
                  if((high_time == 0) && (low_time == 0))
                  {
                      feedbacken = 0;
                  }
                  else
                  {
                      feedpulsecnt++;
                      feedbacken = 1;
                  }
              }
          }

        TestModeCmdSpeed = 800;
        break;
      default:
        TestModeCmdSpeed = 0;
        break;
    }

    if(feedbacken == 1)
    {
      static u8 pulsecnt = 0;
      static u8 pulsestatus = 0;
      static u16 lowtimetemp = 0;
      static u16 hightimetemp = 0;

      if((feedbacken == 1)&&(lastfeedbacken == 0))
      {
        pulsecnt = 0;
        pulsestatus = 0;
        lowtimetemp = low_time;
        hightimetemp = high_time;
      }

      if(pulsestatus == 0)
      {
        //Pull down pwm line
        PwmOutHigh();
        glCapDutyForbid = 1;
        if(lowtimetemp > 0)
        {
          lowtimetemp--;
        }
        else
        {
          pulsestatus = 1;
          lowtimetemp = low_time;
        }
      }
      else
      {
        //Pull up pwm line
        PwmOutLow();
        glCapDutyForbid = 0;
        if(hightimetemp > 0)
        {
          hightimetemp--;
        }
        else
        {
          pulsestatus = 0;
          if(pulsecnt >= 0)
          {
            feedbacken = 0;
          }
          else
          {
            pulsecnt++;
            hightimetemp = high_time;
          }
        }
      }
    }
    lastfeedbacken = feedbacken;
  }
#endif
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
void TestMode(void)
{
  FctTestMode();
  TerminalTestMode();

  testmode_JumpInFlag = fcttest_JumpInFlag || terminaltest_JumpInFlag;
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
void PwmOut50Hz_50Duty(void)
{
  if (testmode_PWMOut50HzEn == 1)
  {
    static u8 bus_flag = 1;
    if (bus_flag)
    {
      bus_flag = 0;
      SDK_MCUDiagOut(ePinOutHigh);
    }
    else
    {
      bus_flag = 1;
      SDK_MCUDiagOut(ePinOutLow);

      if (testmode_PWMOut100HzEnTmp == 1)
      {
        testmode_PWMOut50HzEn = 0;
        testmode_PWMOut100HzEn = 1;
      }
    }
  }
  else if (testmode_PWMOut100HzEn == 0)
  {
    SDK_MCUDiagOut(ePinOutLow);
  }
  else
  {
  }
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
void PwmOut100Hz_50Duty(void)
{
  if (testmode_PWMOut100HzEn == 1)
  {
    static u8 bus_flag = 1;
    if (bus_flag)
    {
      bus_flag = 0;
      SDK_MCUDiagOut(ePinOutHigh);
    }
    else
    {
      bus_flag = 1;
      SDK_MCUDiagOut(ePinOutLow);
    }
  }
  else if (testmode_PWMOut50HzEn == 0)
  {
    SDK_MCUDiagOut(ePinOutLow);
  }
  else
  {
  }
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
void TestModePwmOutSelect(void)
{
  if ((testmode_Command == RX_ID4) && (sample_done == 0))
  {
    u16 ADVal = 0;
    u8 fault = 0;

    if (PhaseVoltageUCnt < 4)
    {
      ADVal = ADCResults.Voltage.PhaseU;

      if (ADVal != 0xFFFFu)
      {
        PhaseVoltageUSum += ADVal;
        PhaseVoltageUCnt++;
      }
    }
    else
    {
      sample_done = 1;

      if ((PhaseVoltageUSum / 4) < 10)
      {
        fault = 1;
      }
    }

    if (PhaseVoltageVCnt < 4)
    {
      ADVal = ADCResults.Voltage.PhaseV;
      if (ADVal != 0xFFFFu)
      {
        PhaseVoltageVSum += ADVal;
        PhaseVoltageVCnt++;
      }
    }
    else
    {
      sample_done = 1;

      if ((PhaseVoltageVSum / 4) > 10)
      {
        fault = 1;
      }
    }

    if (PhaseVoltageWCnt < 4)
    {
      ADVal = ADCResults.Voltage.PhaseW;
      if (ADVal != 0xFFFFu)
      {
        PhaseVoltageWSum += ADVal;
        PhaseVoltageWCnt++;
      }
    }
    else
    {
      sample_done = 1;

      if ((PhaseVoltageWSum / 4) > 10)
      {
        fault = 1;
      }
    }

    if (sample_done == 1)
    {
      if (fault == 1)
      {
        // testmode_PWMOut100HzEnTmp = 1;
      }
    }
  }
}
#endif
