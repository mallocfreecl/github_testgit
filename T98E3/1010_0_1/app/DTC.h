/*BEGIN_FILE_HDR
**************************************************************************
* NOTICE
* This software is the property of XiangBin Electric. Any information contained in this
* doc should not be reproduced, or used, or disclosed without the written authorization from
* XiangBin Electric.
**************************************************************************
* File Name:DTC.h
********************************************************************
* Project/Product:LXT9818
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
*     1.0       2021-07-23      yhd            Original
*
*
********************************************************************
*END_FILE_HDR*/
#ifndef DTC_H
#define DTC_H

/* Includes*/
/******************************************************************/
#include "AppTypes.h"

/* Defines*/
/******************************************************************/
typedef enum{
  eDTCIdxBatHigh,
  eDTCIdxBatLow,

  eDTCIdxChipTHigh,/* 2 */
  eDTCIdxChipTLow,

  eDTCIdxMotorShort,
  eDTCIdxMotorOpen,/* 5 */
  eDTCIdxMotorLock,
  /*增加干运行故障,2023-05-12-by zjj*/
	eDTCIdxMotorDryRunning,
			
	eDTCIdxECUFaultSysOT,
	eDTCIdxECUFaultPMU_5V_OV,
	eDTCIdxECUFaultPMU_1V5_OV,/* 10 */
	eDTCIdxECUFaultSuppShort,
	eDTCIdxECUFaultSuppTimeOut,
	eDTCIdxECUFaultVDDEXT_OverLoad,/* 13 */
	eDTCIdxECUFaultVDDEXT_OverVoltage,
	eDTCIdxECUFaultVDDEXT_Short,
	eDTCIdxECUFaultRef5VOverLoad,/* 16 */
	eDTCIdxECUFaultRef5VOverVoltage,
	eDTCIdxECUFaultRef5VUnderVoltage,
	eDTCIdxECUFaultVBGError,/* 19 */
	eDTCIdxECUFaultRef5VError,
	eDTCIdxECUFaultVSDHigh,
	eDTCIdxECUFaultVSDLow,/* 22 */
	eDTCIdxECUFaultVCPHigh,
	eDTCIdxECUFaultVCPLow1,
	eDTCIdxECUFaultVCPLow2,/* 25 */
	
	eDTCIdxNVMECCFault,
	eDTCIdxRAMFault,
	eDTCIdxFlashCheckSumError,/* 28 */
	
	/*增加故障划分,2023-05-21-by zjj*/
	eDTCIdxMotorOnShortGNDOL,/* 29 */
	eDTCIdxMotorOnShortGNDCL,
	eDTCIdxMotorOnShortBATOL,/* 31 */
	eDTCIdxMotorOnShortBATCL,
	
	eDTCIdxMotorMotorOnOverCurrent,
	eDTCIdxMotorOnSpeedOutRange,/* 34 */
	eDTCIdxMotorOnSpeedOutRange_OverSpeed,
	eDTCIdxMotorOnSpeedOutRange_UnderSpeed,
	eDTCIdxMotorOnSpeedOutRange_DryRunning,/* 37 */
	eDTCIdxMotorOnSpeedOutRange_ReverseSpeed,
	eDTCIdxMotorOnSpeedOutRange_DiffSpeedAndCurrent,
	
	/*增加电流零点相关标志位,2023-08-10-by zjj*/
	eDTCIdxCSAZeroCalibrationFault,/* 40 */
	eDTCIdxCSAZeroAdcBusyError,
	eDTCIdxCSAZeroHigh,/* 42 */
	eDTCIdxCSAZeroLow,
	eDTCIdxCSAZeroSampleCntErrorr,
	eDTCIdxCSAZeroVoltError,/* 45 */
	eDTCIdxCSAZeroTempError,
	
  eDTCRecordsNum,
}DTCRecordIdx_t;
/*polyspace-begin  MISRA2012:6.1*/
typedef union{
  u16 reg;

	struct
	{
		struct{
			u8 RePowerCnt:7;
			u8 IsFault:1;
		}FaultRePowerInfo;

		u8 FaultTotalCnt;
	}bit;
}DTCRecord_t;
/*polyspace-end  MISRA2012:6.1*/
typedef struct{
  u16 Dummy;
  u16 PowerUpCnt;
	/*记录电流零点,2022-03-09-by zyg*/
	u16 IShuntZero;

  DTCRecord_t Records[eDTCRecordsNum];

  u16 CheckSum;
}DTC_t;

/* Variables */
/******************************************************************/
extern DTC_t DTCVar;
extern u16 DTCVarBytesLen;
extern u8 DtcIShuntWriteEn;
extern u8 DtcDataSwRstEn;
/* Function declaration */
/******************************************************************/
extern void DTC_Init(void);
extern void DTC_PeriodTask(void);
extern DTCRecord_t DTC_GetRecord(DTCRecordIdx_t Idx);
/*DTC数据存储函数 24-8-26 by CL*/
extern void DTC_DataSave(void);
#endif
