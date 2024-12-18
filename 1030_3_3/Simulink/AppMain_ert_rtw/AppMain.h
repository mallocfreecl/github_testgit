/*
 * File: AppMain.h
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

#ifndef RTW_HEADER_AppMain_h_
#define RTW_HEADER_AppMain_h_
#include <string.h>
#ifndef AppMain_COMMON_INCLUDES_
#define AppMain_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* AppMain_COMMON_INCLUDES_ */

#include "AppMain_types.h"

/* Child system includes */
#include "ECUFaultDiag.h"
#include "FeedBack.h"
#include "MotorRestartAndFaultCnt.h"
#include "MotorTargetSpeedMux.h"
#include "PwmInParamEval.h"
#include "PwmInTargetSpeedEval.h"
#include "rt_sys_ECUFaultDiag_0.h"

/* Macros for accessing real-time model data structure */

/* Block signals (default storage) */
typedef struct
{
  uint16_T DutyLast;                   /* 'DutyLast' (':1800') */
  uint16_T Duty;                       /* 'Merge2' (':1760') */
  uint16_T Switch;                     /* 'Switch' (':3091') */
  uint16_T Freq;
  /* 'TmpSignal ConversionAtBusConversion_InsertedFor_PwmInStatus_at_inport_0_BusSelector1Outport3' (':0') */
  uint16_T HighDuty;
  /* 'TmpSignal ConversionAtBusConversion_InsertedFor_PwmInStatus_at_inport_0_BusSelector1Outport4' (':0') */
  int16_T PwmInTargetSpeed;            /* 'Merge1' (':1668') */
  int16_T Out;                         /* 'DelayOut' (':1398') */
  int8_T Status;                       /* 'TemperatureState' (':3099') */
  boolean_T Compare;                   /* 'Compare' (':2309:2') */
  boolean_T PwmInError;                /* 'Merge2' (':1669') */
  boolean_T Err;                       /* 'Merge' (':1748') */
  boolean_T PwmInErr;                  /* 'Data Type Conversion1' (':1791') */
  boolean_T Merge1;                    /* 'Merge1' (':1759') */
  boolean_T DutyValid;                 /* 'Logical Operator' (':2298') */
  boolean_T Switch_kva1;               /* 'Switch' (':3124') */
  B_DutyFilter_T DutyFilter_h2ru;      /* 'DutyFilter' (':1703') */
  B_FeedBackDelay_T FeedBackDelay5;    /* 'FeedBackDelay4' (':2346') */
  B_FeedBackDelay_T FeedBackDelay4;    /* 'FeedBackDelay4' (':2346') */
}
B_T;

/* Block states (default storage) for system 'AppMain' */
typedef struct
{
  int16_T FltVoltageLast_PreviousInput;/* 'FltVoltageLast' (':2261') */
  int16_T LastSpeed_PreviousInput;     /* 'LastSpeed' (':1772') */
  uint16_T PowerOnBlankTimeCnt_PreviousInp;/* 'PowerOnBlankTimeCnt' (':967') */
  uint16_T DutyLast_PreviousInput;     /* 'DutyLast' (':1800') */
  uint16_T LastDelay_PreviousInput;    /* 'LastDelay' (':1773') */
  uint16_T LastState_PreviousInput;    /* 'LastState' (':1608') */
  boolean_T DelayInput1_DSTATE;        /* 'Delay Input1' (':2453:2') */
  boolean_T DelayInput1_DSTATE_gs5l;   /* 'Delay Input1' (':3092:2') */
  boolean_T DelayInput1_DSTATE_mx1q;   /* 'Delay Input1' (':1686:2') */
  boolean_T DelayInput1_DSTATE_h0ze;   /* 'Delay Input1' (':1687:2') */
  boolean_T Delay_DSTATE[2];           /* 'Delay' (':3094') */
  int8_T If_ActiveSubsystem;           /* 'If' (':1650') */
  int8_T If_ActiveSubsystem_aekd;      /* 'If' (':1676') */
  int8_T If1_ActiveSubsystem;          /* 'If1' (':1743') */
  boolean_T FeedBackEnLast_PreviousInput;/* 'FeedBackEnLast' (':3064') */
  boolean_T FeedBackEnLast_PreviousInp_nnxg;/* 'FeedBackEnLast' (':3074') */
  boolean_T FeedBackEnLast_PreviousInp_by2c;/* 'FeedBackEnLast' (':3043') */
  DW_TemperatureState_T sf_TemperatureState;/* 'TemperatureState' (':3100') */
  DW_SpeedDelayOut_T SpeedDelayOut_awf2;/* 'SpeedDelayOut' (':1394') */
  DW_FreqValidJudge_T FreqValidJudge_llbg;/* 'FreqValidJudge' (':1734') */
  DW_DutyFilter_T DutyFilter_h2ru;     /* 'DutyFilter' (':1703') */
  DW_MotorRestartAndFaultCnt_T MotorRestartAndFaultCnt_bnwn;/* 'MotorRestartAndFaultCnt' (':815') */
  DW_FeedBackDelay_T FeedBackDelay5;   /* 'FeedBackDelay4' (':2346') */
  DW_FeedBackDelay_T FeedBackDelay4;   /* 'FeedBackDelay4' (':2346') */
  DW_ECUFaultDiag_T ECUFaultDiag_ima5; /* 'ECUFaultDiag' (':769') */
}
DW_T;

/* Constant parameters (default storage) */
typedef struct
{
  /* Pooled Parameter (Expression: int16([163 256 256]))
   * Referenced by:
   *   '1-D Lookup Table' (':3175')
   *   '1-D Lookup Table' (':2249')
   */
  int16_T pooled6[3];

  /* Pooled Parameter (Expression: int16([170 230 320]))
   * Referenced by:
   *   '1-D Lookup Table' (':3175')
   *   '1-D Lookup Table' (':2249')
   */
  int16_T pooled7[3];
}
ConstP_T;

/* External inputs (root inport signals with default storage) */
typedef struct
{
  int16_T SupVoltage;                  /* 'SupVoltage' (':766') */
  int16_T AmbTemperature;              /* 'AmbTemperature' (':767') */
  boolean_T ChipFault;                 /* 'ChipFault' (':768') */
  boolean_T PwmInPinSts;               /* 'PwmInPinSts' (':1038') */
  boolean_T SleepValid;                /* 'SleepValid' (':1566') */
  uint16_T PwmInFreq;                  /* 'PwmInFreq' (':1627') */
  uint16_T PwmInHighDuty;              /* 'PwmInHighDuty' (':1628') */
  uint16_T PwmInIdleTime;              /* 'PwmInIdleTime' (':1629') */
  boolean_T IsMotorShort;              /* 'IsMotorShort' (':1826') */
  boolean_T IsMotorLock;               /* 'IsMotorLock' (':1827') */
  boolean_T IsMotorOpenLoad;           /* 'IsMotorOpenLoad' (':1828') */
  boolean_T RestartComplete;           /* 'RestartComplete' (':1882') */
  int16_T FilteredVoltage;             /* 'FilteredVoltage' (':2253') */
  boolean_T IsMotorDryRunning;         /* 'IsMotorDryRunning' (':2342') */
  boolean_T TestModeSpeedCtrlEnable;   /* 'TestModeSpeedCtrlEnable' (':2915') */
  int16_T TestModeSpeed;               /* 'TestModeSpeed' (':2916') */
}
ExtU_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct
{
  boolean_T MotorRestartEnable;        /* 'MotorRestartEnable' (':1616') */
  boolean_T ChipSleep;                 /* 'ChipSleep' (':1625') */
  boolean_T ChipReset;                 /* 'ChipReset' (':1626') */
  boolean_T FeedBackBusStatus;         /* 'FeedBackBusStatus' (':2164') */
  int16_T TargetSpeedLimited;          /* 'TargetSpeedLimited' (':2216') */
  int8_T VoltageStatus;                /* 'VoltageStatus' (':2265') */
  int8_T AmbTStatus;                   /* 'AmbTStatus' (':2266') */
  uint8_T ShortCnt;                    /* 'ShortCnt' (':2584') */
  uint8_T OpenCnt;                     /* 'OpenCnt' (':2585') */
  uint8_T LockCnt;                     /* 'LockCnt' (':2586') */
  boolean_T PwmInError;                /* 'PwmInError' (':3085') */
  boolean_T PwmInShortGND;             /* 'PwmInShortGND' (':3087') */
  boolean_T PwmInShortBat;             /* 'PwmInShortBat' (':3089') */
  int16_T PwmInTargetSpeed;            /* 'PwmInTargetSpeed' (':3130') */
  int16_T TargetSpeed;                 /* 'TargetSpeed' (':3131') */
}
ExtY_T;

/* Real-time Model Data Structure */
struct tag_RTM_T
{
  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct
  {
    struct
    {
      uint8_T TID[2];
    }
    TaskCounters;
  }
  Timing;
};

/* Block signals (default storage) */
extern B_T B;

/* Block states (default storage) */
extern DW_T DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_T U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_T Y;

/* Constant parameters (default storage) */
extern const ConstP_T ConstP;

/* Model entry point functions */
extern void AppMain_initialize(void);
extern void AppMain_step(void);

/* Real-time Model object */
extern RT_MODEL_T *const M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block 'FaultDetectedLast' (':2015') : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block 'Bias' (':2600') : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block 'Constant' (':2601:3') : Unused code path elimination
 * Block 'Constant5' (':2594') : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block 'Memory' (':2603') : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Eliminate redundant data type conversion
 * Block 'Constant' (':1570') : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is 'block_name' ('SID'), where block_name is the name of the block
 * and SID is the Simulink identifier of the block without the model name.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system(':3')    - opens block with Simulink identifier 'model:3'
 */

/*-
 * Requirements for model: AppMain
 */
#endif                                 /* RTW_HEADER_AppMain_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
