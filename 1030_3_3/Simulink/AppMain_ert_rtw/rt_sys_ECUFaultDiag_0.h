/*
 * File: rt_sys_ECUFaultDiag_0.h
 *
 * Code generated for Simulink model 'AppMain'.
 *
 * Model version                  : 5.31
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Mar 12 13:36:25 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->MSP430
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_rt_sys_ECUFaultDiag_0_h_
#define RTW_HEADER_rt_sys_ECUFaultDiag_0_h_
#ifndef AppMain_COMMON_INCLUDES_
#define AppMain_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* AppMain_COMMON_INCLUDES_ */

#include "AppMain_types.h"

/* Block states (default storage) for system 'TemperatureState' (':3100') */
typedef struct
{
  uint16_T LowCnt;                     /* 'TemperatureState' (':3100') */
  uint16_T HighCnt;                    /* 'TemperatureState' (':3100') */
  uint16_T NormalCnt;                  /* 'TemperatureState' (':3100') */
  int8_T DefaultStatus;                /* 'TemperatureState' (':3100') */
  uint8_T is_active_c1_lib1;           /* 'TemperatureState' (':3100') */
  uint8_T is_c1_lib1;                  /* 'TemperatureState' (':3100') */
  boolean_T IsInited;                  /* 'TemperatureState' (':3100') */
}
DW_TemperatureState_T;

extern void TemperatureState_Init(int8_T *rty_Status, DW_TemperatureState_T
  *localDW);
extern void TemperatureState(int16_T rtu_Input, int8_T *rty_Status, uint16_T
  rtp_DelayCntTHR, int16_T rtp_HighEntryTHR, int16_T rtp_HighExitTHR, uint16_T
  rtp_LongDelayCntTHR, int16_T rtp_LowEntryTHR, int16_T rtp_LowExitTHR,
  DW_TemperatureState_T *localDW);

#endif                                 /* RTW_HEADER_rt_sys_ECUFaultDiag_0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
