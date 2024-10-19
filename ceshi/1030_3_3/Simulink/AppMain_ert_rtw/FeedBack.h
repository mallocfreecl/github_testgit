/*
 * File: FeedBack.h
 *
 * Code generated for Simulink model 'AppMain'.
 *
 * Model version                  : 5.32
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Wed Sep 18 17:44:48 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->MSP430
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FeedBack_h_
#define RTW_HEADER_FeedBack_h_
#ifndef AppMain_COMMON_INCLUDES_
#define AppMain_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* AppMain_COMMON_INCLUDES_ */

/* Block states (default storage) for system 'DelayOut' (':2346:23') */
typedef struct
{
  int16_T DelayInput1_DSTATE;          /* 'Delay Input1' (':2346:23:13:2') */
  uint16_T DelayInput1_DSTATE_px1k;    /* 'Delay Input1' (':2346:23:12:2') */
  int16_T OutLast_PreviousInput;       /* 'OutLast' (':2346:23:15') */
  uint16_T DelayCnt;                   /* 'DelayOut' (':2346:23:11') */
  uint8_T is_active_c3_lib1;           /* 'DelayOut' (':2346:23:11') */
  uint8_T is_c3_lib1;                  /* 'DelayOut' (':2346:23:11') */
}
DW_DelayOut_T;

/* Block signals for system 'FeedBackDelay4' (':2346') */
typedef struct
{
  int16_T Out;                         /* 'DelayOut' (':2346:23:11') */
}
B_FeedBackDelay_T;

/* Block states (default storage) for system 'FeedBackDelay4' (':2346') */
typedef struct
{
  uint16_T Memory_PreviousInput;       /* 'Memory' (':2346:26') */
  boolean_T DelayInput1_DSTATE;        /* 'Delay Input1' (':2346:25:2') */
  boolean_T DelayInput1_DSTATE_aiff;   /* 'Delay Input1' (':2346:24:2') */
  DW_DelayOut_T DelayOut_orxz;         /* 'DelayOut' (':2346:23') */
}
DW_FeedBackDelay_T;

extern void DelayOut_Init(int16_T *rty_Out, DW_DelayOut_T *localDW);
extern void DelayOut(int16_T rtu_In, uint16_T rtu_DelayTime, int16_T *rty_Out,
                     DW_DelayOut_T *localDW);
extern void FeedBackDelay_Init(B_FeedBackDelay_T *localB, DW_FeedBackDelay_T
  *localDW);
extern boolean_T FeedBackDelay(uint16_T rtu_FeedBackStartDelayTime, boolean_T
  rtu_IsFault, uint16_T rtu_FeedBackEndDelayTime, B_FeedBackDelay_T *localB,
  DW_FeedBackDelay_T *localDW);
extern void FeedBack_Init(void);
extern void FeedBack(void);

#endif                                 /* RTW_HEADER_FeedBack_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
