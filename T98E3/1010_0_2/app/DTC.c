/*BEGIN_FILE_HDR
**************************************************************************
* NOTICE
* This software is the property of XiangBin Electric. Any information contained in this
* doc should not be reproduced, or used, or disclosed without the written authorization from
* XiangBin Electric.
**************************************************************************
* File Name:DTC.c
********************************************************************
* Project/Product:LXT9816_PMP
* Title:
* Author:yhd
*********************************************************************
* Description:
*
* (Requirements, pseudo code and etc.)
*********************************************************************
* Limitations:
*
* (limitations)
*********************************************************************
*********************************************************************
* Revision History：
*
* Version       Date         	  Author         Descriptions
* ----------    --------------  ------------   ----------------------------------------
* 1.0           2021-08-20      zyg            Original
* 
*
********************************************************************
*END_FILE_HDR*/

/* Includes*/
/******************************************************************/
#include "DTC.h"
#include "SDK.h"
#include "ADCSample.h"
#include "MotorAPI.h"
#include "GlobalVars.h"

#include "AppMain.h"                   /* Model's header file */
#include "rtwtypes.h"
#include "LINDataPro.h"

/* Defines*/
/******************************************************************/
#define DTC_START_ADDR (DataFlashStart)
/*增加EEPROM数据备份区地址,2022-04-21-by zyg*/
#define DTC_BACK_UP_ADDR (DataFlashStart + (DataFlashSize >> 1u))

#define DTC_WRITE_VOLTAGE (60u)	/* Unit:0.1V */

#define DTC_DUMMY_DATA (0x55AAu)
#define POWER_UP_CNT_MAX (0xFFFFu)
#define REPOWER_UP_CNT_MAX (0x7Fu)
#define FAULT_CNT_MAX (0xFFu)

#define DTC_DFLASH_WRITE_VOLTAGE_MIN (65u)
#define DTC_DFLASH_WRITE_VOLTAGE_MAX (270u)/*EEPROM存储电压阈值修改 23.10.10 by lpy*/
#define DTC_DFLASH_WRITE_CHIP_T_MIN (-35)
#define DTC_DFLASH_WRITE_CHIP_T_MAX (150)


DTC_t DTCVar;
u8 DtcDataSwRstEn = 0u;
u8 DtcIShuntWriteEn = 0u;

static Addr_t DTCDataStartAddr;
/*增加EEPROM数据备份区域,2022-04-21-by zyg*/
static Addr_t DFlashBackUpAddr;
u16 DTCVarBytesLen; /* Debug varible */
static u8 IsDTCUpdated = 0u;
/*消除polyspace警告,2021-09-22-by zyg*/
/*polyspace-begin  MISRA2012:6.1*/
static struct{
  u16 FlagNew:1;
  u16 FlagOld:1;
  u16 CntNew:7;
  u16 CntOld:7;
} FaultFlagAndCnt[eDTCRecordsNum] = {0 };
/*polyspace-end  MISRA2012:6.1*/
/* Function declaration */
/******************************************************************/
static u8 DTC_isDtcDataValid(void);
static u16 DTC_CaculateCheckSum(void);
static void DTCVarReset(void);
static void DTCPowerCntUpdate(void);
/*根据规则修改,2021-09-18-by zyg*/
static void DTC_UpdateFaultTotalCnt(DTCRecordIdx_t Idx, u8 FaultCntOrFlag, u8 FaultCntFlagOld);
static void DTC_UpdateFaultRePowerInfo(DTCRecordIdx_t Idx, u8 IsFault);
static void DTC_RAM2Flash(void);

/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name: DTC_PeriodTask
* Description:
* 1.Update fault flags
* 2.Record fault counts
* 3.Write DTC data to EEPROM before power down
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
void DTC_PeriodTask(void)
{
	u8 i = 0u;
	
  FaultFlagAndCnt[eDTCIdxBatHigh].FlagNew = Y.VoltageStatus > 0;
  FaultFlagAndCnt[eDTCIdxBatLow].FlagNew = Y.VoltageStatus < 0;

  FaultFlagAndCnt[eDTCIdxChipTHigh].FlagNew = Y.AmbTStatus > 0;
  FaultFlagAndCnt[eDTCIdxChipTLow].FlagNew = Y.AmbTStatus < 0;

  FaultFlagAndCnt[eDTCIdxMotorShort].FlagNew = MotorAPIVar.Faults.bit.Short;
  FaultFlagAndCnt[eDTCIdxMotorOpen].FlagNew = MotorAPIVar.Faults.bit.Open;
  FaultFlagAndCnt[eDTCIdxMotorLock].FlagNew = MotorAPIVar.Faults.bit.Lock;
  FaultFlagAndCnt[eDTCIdxMotorDryRunning].FlagNew = MotorAPIVar.IsDryRunning;/*增加干运行故障存储 23.05.21 by zjj*/
  FaultFlagAndCnt[eDTCIdxMotorShort].CntNew = Y.ShortCnt;
  FaultFlagAndCnt[eDTCIdxMotorOpen].CntNew = Y.OpenCnt;
  FaultFlagAndCnt[eDTCIdxMotorLock].CntNew = Y.LockCnt;

  FaultFlagAndCnt[eDTCIdxECUFaultSysOT].FlagNew = ECUFaults.bit.SysOT;
  FaultFlagAndCnt[eDTCIdxECUFaultPMU_5V_OV].FlagNew = ECUFaults.bit.PMU_5V_OV;
  FaultFlagAndCnt[eDTCIdxECUFaultPMU_1V5_OV].FlagNew = ECUFaults.bit.PMU_1V5_OV;
  FaultFlagAndCnt[eDTCIdxECUFaultSuppShort].FlagNew = ECUFaults.bit.SuppShort;
  FaultFlagAndCnt[eDTCIdxECUFaultSuppTimeOut].FlagNew = ECUFaults.bit.SuppTimeOut;
  FaultFlagAndCnt[eDTCIdxECUFaultVDDEXT_OverLoad].FlagNew = ECUFaults.bit.VDDEXT_OverLoad;
  FaultFlagAndCnt[eDTCIdxECUFaultVDDEXT_OverVoltage].FlagNew = ECUFaults.bit.VDDEXT_OverVoltage;
  FaultFlagAndCnt[eDTCIdxECUFaultVDDEXT_Short].FlagNew = ECUFaults.bit.VDDEXT_Short;
  FaultFlagAndCnt[eDTCIdxECUFaultRef5VOverLoad].FlagNew = ECUFaults.bit.Ref5VOverLoad;
  FaultFlagAndCnt[eDTCIdxECUFaultRef5VOverVoltage].FlagNew = ECUFaults.bit.Ref5VOverVoltage;
  FaultFlagAndCnt[eDTCIdxECUFaultRef5VUnderVoltage].FlagNew = ECUFaults.bit.Ref5VUnderVoltage;
  FaultFlagAndCnt[eDTCIdxECUFaultVBGError].FlagNew = ECUFaults.bit.VBGError;
  if(PowerUpTimeMs > 1000u)
  {
    FaultFlagAndCnt[eDTCIdxECUFaultVSDHigh].FlagNew = ECUFaults.bit.VSDHigh;
    FaultFlagAndCnt[eDTCIdxECUFaultVSDLow].FlagNew = ECUFaults.bit.VSDLow;
    FaultFlagAndCnt[eDTCIdxECUFaultVCPHigh].FlagNew = ECUFaults.bit.VCPHigh;
    FaultFlagAndCnt[eDTCIdxECUFaultVCPLow1].FlagNew = ECUFaults.bit.VCPLow1;
    FaultFlagAndCnt[eDTCIdxECUFaultVCPLow2].FlagNew = ECUFaults.bit.VCPLow2;
  }
  else
  {

  }

  FaultFlagAndCnt[eDTCIdxNVMECCFault].FlagNew = ECUFaults.bit.DFlash;
  FaultFlagAndCnt[eDTCIdxRAMFault].FlagNew = ECUFaults.bit.Ram;
  FaultFlagAndCnt[eDTCIdxFlashCheckSumError].FlagNew = ECUFaults.bit.CFlash;
  /*增加故障划分 23.05.21 by zjj*/
  FaultFlagAndCnt[eDTCIdxCSAZeroCalibrationFault].FlagNew = CSAZeroFault.bit.CSAZeroCalibrationFault;
  FaultFlagAndCnt[eDTCIdxCSAZeroAdcBusyError].FlagNew = CSAZeroFault.bit.CSAZeroAdcBusyError;
  FaultFlagAndCnt[eDTCIdxCSAZeroHigh].FlagNew = CSAZeroFault.bit.CSAZeroHigh;
  FaultFlagAndCnt[eDTCIdxCSAZeroLow].FlagNew = CSAZeroFault.bit.CSAZeroLow;
  FaultFlagAndCnt[eDTCIdxCSAZeroSampleCntErrorr].FlagNew = CSAZeroFault.bit.CSAZeroSampleCntErrorr;
  FaultFlagAndCnt[eDTCIdxCSAZeroVoltError].FlagNew = CSAZeroFault.bit.CSAZeroVoltError;
  FaultFlagAndCnt[eDTCIdxCSAZeroTempError].FlagNew = CSAZeroFault.bit.CSAZeroTempError;
  
  FaultFlagAndCnt[eDTCIdxMotorOnShortGNDOL].FlagNew = MotorAPIVar.DetailFaults.bit.MotorOnShortGNDOL;
  FaultFlagAndCnt[eDTCIdxMotorOnShortGNDCL].FlagNew = MotorAPIVar.DetailFaults.bit.MotorOnShortGNDCL;
  FaultFlagAndCnt[eDTCIdxMotorOnShortBATOL].FlagNew = MotorAPIVar.DetailFaults.bit.MotorOnShortBATOL;
  FaultFlagAndCnt[eDTCIdxMotorOnShortBATCL].FlagNew = MotorAPIVar.DetailFaults.bit.MotorOnShortBATCL;
	
  FaultFlagAndCnt[eDTCIdxMotorMotorOnOverCurrent].FlagNew = MotorAPIVar.DetailFaults.bit.MotorOnOverCurrent;
  FaultFlagAndCnt[eDTCIdxMotorOnSpeedOutRange].FlagNew = MotorAPIVar.DetailFaults.bit.MotorOnSpeedOutRange;
	
  FaultFlagAndCnt[eDTCIdxMotorOnSpeedOutRange_OverSpeed].FlagNew = MotorAPIVar.DetailFaults.bit.MotorOnSpeedOutRange_OverSpeed;
  FaultFlagAndCnt[eDTCIdxMotorOnSpeedOutRange_UnderSpeed].FlagNew = MotorAPIVar.DetailFaults.bit.MotorOnSpeedOutRange_UnderSpeed;
  FaultFlagAndCnt[eDTCIdxMotorOnSpeedOutRange_DryRunning].FlagNew = MotorAPIVar.DetailFaults.bit.MotorOnSpeedOutRange_DryRunning;
  FaultFlagAndCnt[eDTCIdxMotorOnSpeedOutRange_ReverseSpeed].FlagNew = MotorAPIVar.DetailFaults.bit.MotorOnSpeedOutRange_ReverseSpeed;
  FaultFlagAndCnt[eDTCIdxMotorOnSpeedOutRange_DiffSpeedAndCurrent].FlagNew = MotorAPIVar.DetailFaults.bit.MotorOnSpeedOutRange_DiffSpeedAndCurrent;

  for( i = 0u; i < eDTCRecordsNum; i++)/* Define variables at the beginning of the function - 2021-07-31-by zyg  */
  {
    DTC_UpdateFaultRePowerInfo((DTCRecordIdx_t)i, FaultFlagAndCnt[i].FlagNew);

    if((i == eDTCIdxMotorShort) || (i == eDTCIdxMotorOpen) || (i == eDTCIdxMotorLock))
    {
      DTC_UpdateFaultTotalCnt((DTCRecordIdx_t)i, FaultFlagAndCnt[i].CntNew, FaultFlagAndCnt[i].CntOld);
      FaultFlagAndCnt[i].CntOld = FaultFlagAndCnt[i].CntNew;
    }
    else
    {
      DTC_UpdateFaultTotalCnt((DTCRecordIdx_t)i, FaultFlagAndCnt[i].FlagNew, FaultFlagAndCnt[i].FlagOld);
    }
		
		FaultFlagAndCnt[i].FlagOld = FaultFlagAndCnt[i].FlagNew;
    /*在DTC存储更新存储标志后清除短电短地故障记录 24-8-26 by CLong*/
		MotorAPIVar.DetailFaults.bit.MotorOnShortGNDOL=0;
		MotorAPIVar.DetailFaults.bit.MotorOnShortGNDCL=0;
		MotorAPIVar.DetailFaults.bit.MotorOnShortBATOL=0;
		MotorAPIVar.DetailFaults.bit.MotorOnShortBATCL=0;
  }
	/*增加DTC软件复位,2022-03-10-by zyg*/
	if (DtcDataSwRstEn != 0u)
  {
		/* 不擦除电流零点，23.10.10 by lpy  */
		u16 IShuntZero = DTCVar.IShuntZero;
    DtcDataSwRstEn = 0u;

    DTCVarReset();
		DTCVar.IShuntZero = IShuntZero;
		IsDTCUpdated = 1u;
  }
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:DTC_DataSave
* Description:
* 
* 
* 
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
void DTC_DataSave(void)
{	
	/* 在DTC数据变化并且电机停止、低压时或休眠前将数据写入Data Flash
     电流零点更新后直接写入DFlash */
  /*增加EEROM写入判断条件 22.10.10 by lpy*/	
  /*增加lin通信存储条件 24-8-26 by CL*/
	if (((IsDTCUpdated != 0u) && (ADCResults.Voltage.Bat > DTC_DFLASH_WRITE_VOLTAGE_MIN) &&
      (ADCResults.Voltage.Bat < DTC_DFLASH_WRITE_VOLTAGE_MAX) &&
      (ADCResults.Temperature.Chip > DTC_DFLASH_WRITE_CHIP_T_MIN) &&
      (ADCResults.Temperature.Chip < DTC_DFLASH_WRITE_CHIP_T_MAX) && (MotorAPIVar.ActSpeed == 0) &&
      ((Y.VoltageStatus == -1) || (ECUFaults.bit.VSDLow != 0u) ||  
	    (DTCSave_ENABLE != 0) || (Y.ChipReset != 0u) || (LinRx.IsSleep != 0u))) || (DtcIShuntWriteEn != 0u))
	{
		if (ECUFaults.bit.DFlash != 0u)
    {
      SDK_clrDFlashError(DTC_START_ADDR, DTCVarBytesLen);
    }

    if (ECUFaults.bit.DFlash == 0u)
    {
		DTC_RAM2Flash();
    }
	}
  else
  {

  }
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:DTC_Init
* Description:
* 1.If DTC data in EEPROM is valid, read this data and update repower
* count.
* 2.If DTC data in EEPROM is invalid, reset DTC data to default value.
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
void DTC_Init(void)
{
	u8 Valid = 0;
  DTCDataStartAddr = (Addr_t)(DTC_START_ADDR);
	/*增加EEPROM数据备份区地址,2022-04-21-by zyg*/
	DFlashBackUpAddr = (Addr_t)(DTC_BACK_UP_ADDR);
	
  DTCVarBytesLen = sizeof(DTCVar);
  SDK_EEPROM_Read(DTCDataStartAddr, (u8 *)(&DTCVar), DTCVarBytesLen);

	Valid = DTC_isDtcDataValid();
  if (Valid == 0u)
  {
    SDK_EEPROM_Read(DFlashBackUpAddr, (u8 *)(&DTCVar), DTCVarBytesLen);
    Valid = DTC_isDtcDataValid();
  }

  if (Valid == 0u)
  {
    DTCVarReset();
  }
	else
	{
		DTCPowerCntUpdate();
	}

  IsDTCUpdated = 1u;
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:DTC_IsDTCDataValid
* Description:
*   Caulate checksum and compare with checksum which is read from
* EEPROM.
*
* Inputs:
*
*
* Outputs:true or false
*
*
* Limitations:
********************************************************************
END_FUNCTION_HDR*/
static u8 DTC_isDtcDataValid(void)
{
  u16 ChkSum = 0u;
  ChkSum = DTC_CaculateCheckSum();
  return ((DTCVar.Dummy == DTC_DUMMY_DATA) && (DTCVar.CheckSum == ChkSum)) ? 1u : 0u;
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:DTC_CaculateCheckSum
* Description:
*   sum all data expected CheckSum.
*
* Inputs:
*
*
* Outputs:CheckSum
*
*
* Limitations:
********************************************************************
END_FUNCTION_HDR*/
static u16 DTC_CaculateCheckSum(void)
{
  u16 Sum = 0u;
	u16 i = 0u;
	
	Sum += DTCVar.Dummy;
	Sum += DTCVar.PowerUpCnt;
	/*增加电流零点,2022-03-09-by zyg*/
	Sum += DTCVar.IShuntZero;
	
  for( i = 0u; i < eDTCRecordsNum; i++)/* Define variables at the beginning of the function - 2021-07-31-by zyg  */
  {
    Sum += DTCVar.Records[i].reg;
  }

  return Sum;
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:DTCVarReset
* Description:
*   Set Dummy = 0x55AA, PowerUpCnt = 1, Records = 0.
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
static void DTCVarReset(void)
{
	u16 i = 0u;
	
	DTCVar.Dummy = DTC_DUMMY_DATA;
	DTCVar.PowerUpCnt = 1u;
	/*DTC软件复位时零点清零，需要重新标一次零点 2023-08-15-by zjj*/
	DTCVar.IShuntZero = 0u;
	
	for( i = 0u; i < eDTCRecordsNum; i++)
	{
		DTCVar.Records[i].reg = 0u;
	}
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:DTCPowerCntUpdate
* Description:
* 1.PowerUpCnt: PowerUp count from first flashed
* 2.IsFault: 1:falut occord, 0:falut not occord
* 2.RePowerCnt:repower count after last fault occord
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
static void DTCPowerCntUpdate(void)
{
	u16 i = 0u;
	
	if(DTCVar.PowerUpCnt < (U16_MAX))
	{
		DTCVar.PowerUpCnt++;
	}
  else
  {

  }

	for( i = 0u; i < eDTCRecordsNum; i++)/* Define variables at the beginning of the function - 2021-07-31-by zyg  */
	{
		if((DTCVar.Records[i].bit.FaultRePowerInfo.IsFault) != 0u)/*消除polyspace警告,2021-09-22-by zyg*/
		{
			if(DTCVar.Records[i].bit.FaultRePowerInfo.RePowerCnt < (REPOWER_UP_CNT_MAX))
			{
				DTCVar.Records[i].bit.FaultRePowerInfo.RePowerCnt++;
			}
			else
			{
				DTCVar.Records[i].bit.FaultRePowerInfo.IsFault = 0u;
				DTCVar.Records[i].bit.FaultRePowerInfo.RePowerCnt = 0u;
			}
		}
    else
    {

    }
	}
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:DTC_UpdateFaultTotalCnt
* Description:
*
*
* Inputs:
* 1.Idx:fault type index
* 2.FaultCntOrFlag:Current fault count or falut flag
* 3.FaultCntFlagOld:Last fault count or fault flag
*
* Outputs:
*
*
* Limitations:
********************************************************************
END_FUNCTION_HDR*/
static void DTC_UpdateFaultTotalCnt(DTCRecordIdx_t Idx, u8 FaultCntOrFlag, u8 FaultCntFlagOld)
{
	/*优化代码结构,22.06.01 by zyg*/
	if((FaultCntOrFlag > (FaultCntFlagOld))&&(Idx < eDTCRecordsNum))
	{
      if(DTCVar.Records[Idx].bit.FaultTotalCnt < (FAULT_CNT_MAX))
      {
        DTCVar.Records[Idx].bit.FaultTotalCnt++;
        
        IsDTCUpdated = 1u;
      }
	}
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:DTC_UpdateFaultRePowerInfo
* Description:
*   Update fault flag and falut repower count.
*
* Inputs:
* 1.Idx:fault type index
* 2.IsFault:true or false
* Outputs:
*
*
* Limitations:
********************************************************************
END_FUNCTION_HDR*/
static void DTC_UpdateFaultRePowerInfo(DTCRecordIdx_t Idx, u8 IsFault)
{
	/*增加故障判断,防止低压下一直写EEPROM,22.06.01 by zyg*/
  if((IsFault != 0u)&&(Idx < eDTCRecordsNum))
  {
    if(DTCVar.Records[Idx].bit.FaultRePowerInfo.IsFault != 1u)
    {
      DTCVar.Records[Idx].bit.FaultRePowerInfo.IsFault = 1u;
      DTCVar.Records[Idx].bit.FaultRePowerInfo.RePowerCnt = 0u;

      IsDTCUpdated = 1u;
    }
    else
    {
			if(DTCVar.Records[Idx].bit.FaultRePowerInfo.RePowerCnt != 0u)
      {
        DTCVar.Records[Idx].bit.FaultRePowerInfo.RePowerCnt = 0u;

        IsDTCUpdated = 1u;
      }
    }
	}
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:DTC_GetRecord
* Description:
*   Read fault information by fault index
*
* Inputs:
* 1.Idx:fault type index
*
* Outputs:
* Fault record type
*
* Limitations:
********************************************************************
END_FUNCTION_HDR*/
DTCRecord_t DTC_GetRecord(DTCRecordIdx_t Idx)
{
  return (Idx < eDTCRecordsNum) ? (DTCVar.Records[Idx]) : ((DTCRecord_t){0u,});
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:DTC_RAM2Flash
* Description:
*   Write DTC data to EEPROM
*   Write DTC will pause flash code executing about 7ms.
* Inputs:
*
*
* Outputs:
*
*
* Limitations:
********************************************************************
END_FUNCTION_HDR*/
static void DTC_RAM2Flash(void)
{
/* DFLASH写入时零点存储标志复位，防止写入出错 23.08.15 by zjj */
	DtcIShuntWriteEn = 0u;
  IsDTCUpdated = 0u;
  DTCVar.CheckSum = DTC_CaculateCheckSum();
	SDK_writeDFlash(DTC_START_ADDR, (u8 *)(&DTCVar), DTCVarBytesLen);
  SDK_writeDFlash(DTC_BACK_UP_ADDR, (u8 *)(&DTCVar), DTCVarBytesLen);
}
