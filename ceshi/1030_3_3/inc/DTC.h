#ifndef DTC_H
#define DTC_H

#include "SDKTypes.h"

/* Defines*/
/******************************************************************/

/* 增加故障类型，22.01.10 by yhd */
/* 增加BemfOutRange故障，22.03.06 by yhd */
typedef enum
{
  eDTCIdxBatHigh,
  eDTCIdxBatLow,
  eDTCIdxChipTHigh,
  eDTCIdxChipTLow,
  eDTCIdxMotorShort,
  eDTCIdxMotorOpen,
  eDTCIdxMotorLock,
  eDTCIdxMotorShortBAT,
  eDTCIdxMotorShortGND,
  eDTCIdxMotorMotorDryRunning,
  /* 细化失步故障 23.08.28 by lxs */
  eDTCIdxMotorSpeedOutRange,
  eDTCIdxMotorSpeedOutRange_Inc,
  eDTCIdxMotorSpeedTooLow,
  eDTCIdxMotorSpeedTooHigh,
  eDTCIdxMotorCurrentOutRange,
  eDTCIdxMotorDrvErr,
  eDTCIdxMotorBemfOutRange,
  eDTCIdxMotorDrvOverCurrent,
  eDTCIdxMotorDrvOverTemp,
  eDTCIdxMotorDrvVCCLow,
  eDTCIdxMotorDrvVGLow,
  eDTCIdxChipFaut,
/* 空间不够，屏蔽细化的芯片故障，使用总的代替 23.12.15 by lxs */
#if 0 
  eDTCIdxSysClkFail,

  eDTCIdxWDogRst,
  eDTCIdxCPUParityRst,
  eDTCIdxSRAMParity,
  eDTCIdxFlashBitErr1,
  eDTCIdxFlashBitErr2,
  eDTCIdxsram_wr_prot,
  eDTCIdxstack_prot,
  eDTCIdxexec_prot,

  eDTCIdxbad_access,
  eDTCIdxSCI_FE,
  eDTCIdxSCI_OV,
  eDTCIdxdma_read_err,
  eDTCIdxdma_write_err,
  eDTCIdxreload_error_evt,
#endif

  eDTCRecordsNum,
} DTCRecordIdx_t;
/* 故障标志，22.01.10 by yhd */
/* 增加BemfOutRange故障，22.03.06 by yhd */
typedef union {
  u32 R;

  struct
  {
    u32 BatHigh : 1;
    u32 BatLow : 1;
    u32 ChipTHigh : 1;
    u32 ChipTLow : 1;
    u32 MotorShort : 1;
    u32 MotorOpen : 1;
    u32 MotorLock : 1;
	
	  u32 MotorShortBAT : 1;
    u32 MotorShortGND : 1;
    /* 增加干运行故障 23.10.30 by lxs */
    u32 MotorDryRunning : 1;
    /* 细化失步故障 23.08.28 by lxs */
    u32 MotorSpeedOutRange : 1;
    u32 MotorSpeedOutRange_Inc : 1;
    u32 MotorSpeedTooLow : 1;
    u32 MotorSpeedTooHigh : 1;
    u32 MotorCurrentOutRange : 1;
    u32 MotorDrvErr : 1;
    u32 MotorBemfOutRange : 1;
    u32 MotorDrvOverCurrent : 1;
    u32 MotorDrvOverTemp : 1;
    u32 MotorDrvVCCLow : 1;
    u32 MotorDrvVGLow : 1;
    u32 ChipFault : 1;
/* 空间不够，屏蔽细化的芯片故障，使用总的代替 23.12.11 by lxs */
#if 0
    u32 SysClkFail : 1;

    u32 WDogRst : 1;
    u32 CPUParityRst : 1;
    u32 SRAMParity : 1;
    u32 FlashBitErr1 : 1;
    u32 FlashBitErr2 : 1;
    u32 sram_wr_prot : 1;
    u32 stack_prot : 1;
    u32 exec_prot : 1;

    u32 bad_access : 1;
    u32 SCI_FE : 1;
    u32 SCI_OV : 1;
    u32 dma_read_err : 1;
    u32 dma_write_err : 1;
    u32 reload_error_evt : 1;
#endif
  } B;
} FaultFlags_t;

typedef struct
{
  u8 RePowerCnt : 7;
  u8 IsFault : 1;
} DTCRecord_t;

typedef struct
{
  u16 Dummy;
  u16 PowerUpCnt;

  DTCRecord_t Records[eDTCRecordsNum];
  /* 增加故障总计数功能，22.01.10 by yhd */
  u8 FaultTotalCnt[eDTCRecordsNum];

  u16 CheckSum;
} DTC_t;

/* Variables */
/******************************************************************/
extern DTC_t DTCVar;
/* 清除DataFlash中的数据标志, 22.01.10 by yhd */
extern u8 DTC_ClrDFlashEn;

extern bool IsDTCUpdated;

/* Function declaration */
/******************************************************************/
extern void DTC_Init(void);
extern void DTC_RAM2Flash(void);
extern void DTC_UpdateRecord(DTCRecordIdx_t Idx, u8 IsFault);
extern DTCRecord_t DTC_GetRecord(DTCRecordIdx_t Idx);
/* 清除DataFlash中的数据, 22.01.10 by yhd */
extern void DTC_ClrDFlash(void);

#endif
