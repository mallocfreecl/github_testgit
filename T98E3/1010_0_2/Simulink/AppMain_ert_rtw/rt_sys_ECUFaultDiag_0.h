/*
 * File: rt_sys_ECUFaultDiag_0.h
 *
 * Code generated for Simulink model 'AppMain'.
 *
 * Model version                  : 9.0
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Wed Oct 30 10:43:57 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_rt_sys_ECUFaultDiag_0_h_
#define RTW_HEADER_rt_sys_ECUFaultDiag_0_h_
#ifndef AppMain_COMMON_INCLUDES_
#define AppMain_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* AppMain_COMMON_INCLUDES_ */

/* Block states (default storage) for system 'AmbTOverDiag' (':1621') */
typedef struct
{
  uint16_T LowCnt;                     /* 'AmbTOverDiag' (':1621') */
  uint16_T HighCnt;                    /* 'AmbTOverDiag' (':1621') */
  uint16_T NormalCnt;                  /* 'AmbTOverDiag' (':1621') */
  int8_T DefaultStatus;                /* 'AmbTOverDiag' (':1621') */
  uint8_T is_active_c2_lib1;           /* 'AmbTOverDiag' (':1621') */
  uint8_T is_c2_lib1;                  /* 'AmbTOverDiag' (':1621') */
  boolean_T IsInited;                  /* 'AmbTOverDiag' (':1621') */
}
DW_AmbTOverDiag_T;

extern void AmbTOverDiag_Init(int8_T *rty_Status, DW_AmbTOverDiag_T *localDW);
extern void AmbTOverDiag(int16_T rtu_Input, int8_T *rty_Status, uint16_T
  rtp_DelayCntTHR, int16_T rtp_HighEntryTHR, int16_T rtp_HighExitTHR, int16_T
  rtp_LowEntryTHR, int16_T rtp_LowExitTHR, DW_AmbTOverDiag_T *localDW);

#endif                                 /* RTW_HEADER_rt_sys_ECUFaultDiag_0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
