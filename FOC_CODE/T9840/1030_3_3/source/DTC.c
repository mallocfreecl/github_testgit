#include "DTC.h"
#include "ADCSample.h"
#include "debug.h"
#include "driver_generic.h"
#include "flash_ctrl.h"
#include "saradc_tables.h"

#pragma data_alignment = 2

DTC_t DTCVar;
/* 清除DataFlash内容标志，22.01.10 by yhd */
u8 DTC_ClrDFlashEn = 0u;
static u16 DTCDataStartAddr;
static u16 DTCVarBytesLen;
static u16 DTCVarWordsLen;
bool IsDTCUpdated = false;

static u16 DTC_CaculateCheckSum(void);

void DTC_Init(void)
{
  DTCDataStartAddr = flash_get_page_base_addr(FLASH_CTRL, 0, true);

  DTCVarBytesLen = sizeof(DTCVar);
  /*  消除polyspace警告 2023.10.29 by lxs */
  DTCVarWordsLen = (((DTCVarBytesLen & 0x1u) != 0) ? (DTCVarBytesLen + 1) : DTCVarBytesLen) >> 1;/* polyspace DEFECT:DEAD_CODE  */

  /*
  Read DTCVar From Info Flash Page0
  */
 /* polyspace +1 MISRA-C3:11.3 */
  uintptr_t *pDes = (uintptr_t *)(&DTCVar);

  for (u16 i = 0; i < DTCVarWordsLen; i++)
  {
    u16 tmp = flash_read_info_word(FLASH_CTRL, (uintptr_t)DTCDataStartAddr + (i << 1));
    /* 去除死代码 23.10.17 by lxs */
    *(pDes + i) = tmp;
  }

  if ((DTCVar.Dummy != 0x55AA) || (DTCVar.CheckSum != DTC_CaculateCheckSum()))
  {
    /* polyspace +1 MISRA-C3:11.3 */
    u16 *p = (u16 *)&DTCVar;
    for (u8 i = 0; i < DTCVarWordsLen; i++)
    {
      *(p + i) = 0;
    }

    DTCVar.Dummy = 0x55AA;
  }

  if (DTCVar.PowerUpCnt < 0xFFFFu)
  {
    DTCVar.PowerUpCnt++;
  }

  for (u8 i = 0; i < eDTCRecordsNum; i++)
  {
    /* 消除polyspace警告 23.10.17 by lxs */
    if (DTCVar.Records[i].IsFault != 0u)
    {
      if (DTCVar.Records[i].RePowerCnt < 0x7F)
      {
        DTCVar.Records[i].RePowerCnt++;
      }
      else
      {
        DTCVar.Records[i].IsFault = 0;
        DTCVar.Records[i].RePowerCnt = 0;
      }
    }
  }

  IsDTCUpdated = true;
}

static u16 DTC_CaculateCheckSum(void)
{
  u16 Sum = 0;
  /* polyspace +1 MISRA-C3:11.3 */
  u16 *p = (u16 *)&DTCVar;

  for (u8 i = 0; i < DTCVarWordsLen - 1; i++)
  {
    Sum += *(p + i);
  }

  return Sum;
}

/*
Duration: 20ms
*/
void DTC_RAM2Flash(void)
{
  if (!IsDTCUpdated)
  {
    return;
  }

  IsDTCUpdated = false;

  DTCVar.CheckSum = DTC_CaculateCheckSum();

  SDK_InterruptDisable();

  /* Pagse erase time: 20ms */
  /* 该函数有返回值，消除polyspace警告 23.10.29 by lxs */
  (void)flash_erase_pages(FLASH_CTRL, (uintptr_t *)DTCDataStartAddr, 1, true);
  /* polyspace +1 MISRA-C3:11.3 */
  uintptr_t *pSrc = (uintptr_t *)&DTCVar;
  uintptr_t *pDes = (uintptr_t *)DTCDataStartAddr;

  u16 Words = DTCVarWordsLen;
  /* 消除polyspace警告 23.10.29 by lxs */
  while (Words != 0u)
  {
    if (Words >= (FLASH_ROW_SIZE / 2))
    {
      /* 该函数有返回值，消除polyspace警告 23.10.29 by lxs */
      (void)flash_program_rows(FLASH_CTRL, pSrc, pDes, (FLASH_ROW_SIZE / 2), true);

      pSrc += (FLASH_ROW_SIZE / 2);
      pDes += (FLASH_ROW_SIZE / 2);
      Words -= (FLASH_ROW_SIZE / 2);
    }
    else
    {
      /* 该函数有返回值，消除polyspace警告 23.10.29 by lxs */
      (void)flash_program_rows(FLASH_CTRL, pSrc, pDes, Words, true);

      Words = 0;
    }
  }
  /* polyspace +1 MISRA-C3:11.8 */
  saradc_apply_list((saradc_table_list_entry *)list_windmill, true);

  SDK_InterruptEnable();
}

void DTC_UpdateRecord(DTCRecordIdx_t Idx, u8 IsFault)
{
  if (IsFault == 0u)
  {
    return;
  }
  
  if(DTCVar.Records[Idx].IsFault == 0)
  {
    DTCVar.Records[Idx].IsFault = 1;
    IsDTCUpdated = true;
  }
  
  if(DTCVar.Records[Idx].RePowerCnt != 0)
  {
    DTCVar.Records[Idx].RePowerCnt = 0;
    IsDTCUpdated = true;
  }
}

DTCRecord_t DTC_GetRecord(DTCRecordIdx_t Idx)
{
  return DTCVar.Records[Idx];
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:DTC_ClrDFlash
* Description:
* 清除DataFlash中的数据
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
void DTC_ClrDFlash(void)
{
  u16 i = 0u;

  if (DTC_ClrDFlashEn != 0u)
  {
    DTC_ClrDFlashEn = 0;
    for (i = 0u; i < eDTCRecordsNum; i++)
    {
      DTCVar.Records[i].IsFault = 0u;
      DTCVar.Records[i].RePowerCnt = 0u;
      DTCVar.FaultTotalCnt[i] = 0u;
    }
    IsDTCUpdated = true;
  }
}
