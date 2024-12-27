#ifndef DEBUG_H
#define DEBUG_H

#include "main.h"

#define DEBUG_DIAG_OUT 0

#if DEBUG_DIAG_OUT
#define DEBUG_TIME_MEASURE_TB_5MS 0
#define DEBUG_TIME_MEASURE_TB_10MS 0
#define DEBUG_TIME_MEASURE_TB_100MS 0

#define DEBUG_PWMN_START_TOGGLE 0

#define DEBUG_DIAG_OUT_FREE_MASTER_RECERIVE 0

#define DEBUG_DIAG_ADCListDone 0

#define DEBUG_DIAG_PwmInDelay 0

#define DEBUG_DIAG_InitTime 0

#define DEBUG_DIAG_PwmInInt_LowPulse 0
#define DEBUG_DIAG_PwmInInt_Period 0

#define DEBUG_DIAG_OUT_Sector0 0
#define DEBUG_DIAG_OUT_Sector1 0
#define DEBUG_DIAG_OUT_Sector2 0

#define DEBUG_DIAG_OUT_OpenLoop 0

#endif

#define DEBUG_USE_SCI 1
#if DEBUG_USE_SCI
#define DEBUG_USE_FREE_MASTER 0 /*  disable freemaster, 21.07.30 by yhd */
#define DEBUG_USE_FAN_COM_TOOL 1
#endif

#if DEBUG_USE_FREE_MASTER
#define DEBUG_SCI_SPEED_EN 1
#else
#define DEBUG_SCI_SPEED_EN 0
#endif

#define DEBUG_TUNE_EN DEBUG_USE_FREE_MASTER

#if DEBUG_TUNE_EN == 1

#endif

typedef struct
{
  u16 ProductVersion;
  union {
    u16 reg;

    struct
    {
      u16 MinorHardVersion : 4;
      u16 InnerVersion : 4;
      u16 SoftVersion : 8;
    } bits;
  } InnerVersion;
  /* 增加FCT版本号 24.03.12 by lxs */
  u8 FctVersion;
  u8 DebugVersion;
  
} Version_t;

extern const Version_t Version;
typedef struct
{
  bool PwmInSpeedCtrlEn;
  s16 PhaseDiffOffset;
  bool SCIEn;
  bool DirectSpeedCtrlEn;
  s16 DirectSpeed;
  bool FreeMasterEn;
} Debug_t;

extern Debug_t DebugVar;

/* 21.07.30 by yhd */
extern const u32 FlashCheckSum;
extern const u8 FlashECUInfo[12];

#endif // !DEBUG_H
