/*
 * File: AppMain.c
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

#include "AppMain.h"
#include "PwmInParamEval.h"
#include "PwmInTargetSpeedEval.h"
#include "ECUFaultDiag.h"
#include "MotorTargetSpeedMux.h"
#include "MotorRestartAndFaultCnt.h"
#include "FeedBack.h"
#include "rt_sys_ECUFaultDiag_0.h"
#include "rtwtypes.h"
#include <string.h>
#include "AppMain_private.h"

/* Block signals (default storage) */
B_T B;

/* Block states (default storage) */
DW_T DW;

/* External inputs (root inport signals with default storage) */
ExtU_T U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_T Y;

/* Real-time model */
static RT_MODEL_T M_;
RT_MODEL_T *const M = &M_;
static void rate_scheduler(void);
int16_T look1_is16lu32n16Ds32_binlcs(int16_T u0, const int16_T bp0[], const
  int16_T table[], uint32_T maxIndex)
{
  uint32_T frac;
  uint32_T iLeft;
  int16_T bpLeftVar;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
     Rounding mode: 'simplest'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
     Rounding mode: 'simplest'
   */
  if (u0 <= bp0[0UL])
  {
    iLeft = 0UL;
    frac = 0UL;
  }
  else if (u0 < bp0[maxIndex])
  {
    uint32_T iRght;

    /* Binary Search */
    frac = (uint32_T)(maxIndex >> 1UL);
    iLeft = 0UL;
    iRght = maxIndex;
    while ((uint32_T)(iRght - iLeft) > 1UL)
    {
      if (u0 < bp0[frac])
      {
        iRght = frac;
      }
      else
      {
        iLeft = frac;
      }

      frac = (uint32_T)((uint32_T)(iRght + iLeft) >> 1UL);
    }

    bpLeftVar = bp0[iLeft];
    frac = (uint32_T)((uint32_T)((uint32_T)(uint16_T)((uint16_T)u0 - (uint16_T)
      bpLeftVar) << 16) / (uint32_T)(uint16_T)((uint16_T)bp0[(uint32_T)(iLeft +
      1UL)] - (uint16_T)bpLeftVar));
  }
  else
  {
    iLeft = (uint32_T)(maxIndex - 1UL);
    frac = 65536UL;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Rounding mode: 'simplest'
     Overflow mode: 'wrapping'
   */
  bpLeftVar = table[iLeft];
  return (int16_T)((int16_T)(int32_T)asr_s32((int32_T)((int32_T)((int32_T)table
    [(uint32_T)(iLeft + 1UL)] - (int32_T)bpLeftVar) * (int32_T)frac), 16U) +
                   bpLeftVar);
}

void mul_wide_u32(uint32_T in0, uint32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                  *ptrOutBitsLo)
{
  uint32_T in0Hi;
  uint32_T in0Lo;
  uint32_T in1Hi;
  uint32_T in1Lo;
  uint32_T outBitsLo;
  uint32_T productHiLo;
  uint32_T productLoHi;
  in0Hi = (uint32_T)(in0 >> 16UL);
  in0Lo = (uint32_T)(in0 & 65535UL);
  in1Hi = (uint32_T)(in1 >> 16UL);
  in1Lo = (uint32_T)(in1 & 65535UL);
  productHiLo = (uint32_T)(in0Hi * in1Lo);
  productLoHi = (uint32_T)(in0Lo * in1Hi);
  in0Lo *= in1Lo;
  in1Lo = 0UL;
  outBitsLo = (uint32_T)((uint32_T)(productLoHi << 16UL) + in0Lo);
  if (outBitsLo < in0Lo)
  {
    in1Lo = 1UL;
  }

  in0Lo = outBitsLo;
  outBitsLo += (uint32_T)(productHiLo << 16UL);
  if (outBitsLo < in0Lo)
  {
    in1Lo++;
  }

  *ptrOutBitsHi = (uint32_T)((uint32_T)((uint32_T)((uint32_T)(productLoHi >>
    16UL) + (uint32_T)(productHiLo >> 16UL)) + (uint32_T)(in0Hi * in1Hi)) +
    in1Lo);
  *ptrOutBitsLo = outBitsLo;
}

uint32_T mul_u32_sat(uint32_T a, uint32_T b)
{
  uint32_T result;
  uint32_T u32_chi;
  mul_wide_u32(a, b, &u32_chi, &result);
  if (u32_chi)
  {
    result = MAX_uint32_T;
  }

  return result;
}

int32_T asr_s32(int32_T u, uint16_T n)
{
  int32_T y;
  if (u >= 0L)
  {
    y = (int32_T)(uint32_T)((uint32_T)u >> n);
  }
  else
  {
    y = (int32_T)((int32_T)-(int32_T)(uint32_T)((uint32_T)(int32_T)(-1L - u) >>
      n) - 1L);
  }

  return y;
}

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (M->Timing.TaskCounters.TID[1])++;
  if ((M->Timing.TaskCounters.TID[1]) > 19)
  {                                    /* Sample time: [0.1s, 0.0s] */
    M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void AppMain_step(void)
{
  int16_T rtb_MotorTargetSpeed;
  boolean_T rtb_ECUFault;

  /* Outputs for Atomic SubSystem: 'PwmInParamEval' (':925') */
  PwmInParamEval();

  /* End of Outputs for SubSystem: 'PwmInParamEval' (':925') */

  /* RelationalOperator: 'Compare' (':2309:2') incorporates:
   *  Constant: 'Constant' (':2309:3')
   *  Inport: 'PwmInIdleTime' (':1629')
   */
  B.Compare = (U.PwmInIdleTime == 0U);

  /* Outputs for Atomic SubSystem: 'PwmInTargetSpeedEval' (':961') */
  PwmInTargetSpeedEval();

  /* End of Outputs for SubSystem: 'PwmInTargetSpeedEval' (':961') */

  /* Outport: 'PwmInError' (':3085') */
  Y.PwmInError = B.PwmInError;

  /* Outport: 'PwmInTargetSpeed' (':3130') */
  Y.PwmInTargetSpeed = B.PwmInTargetSpeed;

  /* Outputs for Atomic SubSystem: 'ECUFaultDiag' (':769') */
  /* Inport: 'SupVoltage' (':766') incorporates:
   *  Inport: 'AmbTemperature' (':767')
   *  Inport: 'ChipFault' (':768')
   *  Outport: 'AmbTStatus' (':2266')
   *  Outport: 'VoltageStatus' (':2265')
   */
  ECUFaultDiag(U.SupVoltage, U.AmbTemperature, U.ChipFault, &rtb_ECUFault,
               &Y.VoltageStatus, &Y.AmbTStatus, &DW.ECUFaultDiag_ima5);

  /* End of Outputs for SubSystem: 'ECUFaultDiag' (':769') */

  /* Outputs for Atomic SubSystem: 'MotorTargetSpeedMux' (':916') */
  /* Inport: 'TestModeSpeedCtrlEnable' (':2915') incorporates:
   *  Inport: 'TestModeSpeed' (':2916')
   */
  rtb_MotorTargetSpeed = MotorTargetSpeedMux(U.TestModeSpeedCtrlEnable,
    U.TestModeSpeed, B.PwmInTargetSpeed);

  /* End of Outputs for SubSystem: 'MotorTargetSpeedMux' (':916') */

  /* Outputs for Atomic SubSystem: 'MotorRestartAndFaultCnt' (':815') */
  /* Outport: 'MotorRestartEnable' (':1616') incorporates:
   *  Inport: 'IsMotorDryRunning' (':2342')
   *  Inport: 'IsMotorLock' (':1827')
   *  Inport: 'IsMotorOpenLoad' (':1828')
   *  Inport: 'IsMotorShort' (':1826')
   *  Inport: 'RestartComplete' (':1882')
   *  Outport: 'LockCnt' (':2586')
   *  Outport: 'OpenCnt' (':2585')
   *  Outport: 'ShortCnt' (':2584')
   *  Outport: 'TargetSpeed' (':3131')
   */
  MotorRestartAndFaultCnt(rtb_MotorTargetSpeed, rtb_ECUFault, U.RestartComplete,
    U.IsMotorShort, U.IsMotorLock, U.IsMotorOpenLoad, U.IsMotorDryRunning,
    B.PwmInTargetSpeed, &Y.TargetSpeed, &Y.MotorRestartEnable, &Y.ShortCnt,
    &Y.OpenCnt, &Y.LockCnt, &DW.MotorRestartAndFaultCnt_bnwn);

  /* End of Outputs for SubSystem: 'MotorRestartAndFaultCnt' (':815') */
  if (M->Timing.TaskCounters.TID[1] == 0)
  {
    /* Outputs for Atomic SubSystem: 'FeedBack' (':890') */
    FeedBack();

    /* End of Outputs for SubSystem: 'FeedBack' (':890') */

    /* Outport: 'FeedBackBusStatus' (':2164') */
    Y.FeedBackBusStatus = B.Switch_kva1;
  }

  /* Outputs for Atomic SubSystem: 'SpeedLimit' (':2196') */
  /* Chart: 'TemperatureState' (':3099') incorporates:
   *  Inport: 'AmbTemperature' (':767')
   */
  TemperatureState(U.AmbTemperature, &B.Status, 400U, 140, 138, 2000U, -40, -38,
                   &DW.sf_TemperatureState);

  /* Switch: 'Switch' (':2337') */
  if ((int16_T)B.Status > 0)
  {
    /* Switch: 'Switch1' (':2339') incorporates:
     *  Constant: 'AmbTPreOverMaxSpeed' (':2335')
     *  Outport: 'TargetSpeed' (':3131')
     *  RelationalOperator: 'Relational Operator' (':2338')
     */
    if (Y.TargetSpeed > 3277)
    {
      /* Outport: 'TargetSpeedLimited' (':2216') */
      Y.TargetSpeedLimited = 3277;
    }
    else
    {
      /* Outport: 'TargetSpeedLimited' (':2216') */
      Y.TargetSpeedLimited = Y.TargetSpeed;
    }

    /* End of Switch: 'Switch1' (':2339') */
  }
  else
  {
    /* Outport: 'TargetSpeedLimited' (':2216') incorporates:
     *  Outport: 'TargetSpeed' (':3131')
     */
    Y.TargetSpeedLimited = Y.TargetSpeed;
  }

  /* End of Switch: 'Switch' (':2337') */
  /* End of Outputs for SubSystem: 'SpeedLimit' (':2196') */
  rate_scheduler();
}

/* Model initialize function */
void AppMain_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)M, 0,
                sizeof(RT_MODEL_T));

  /* block I/O */
  (void) memset(((void *) &B), 0,
                sizeof(B_T));

  /* states (dwork) */
  (void) memset((void *)&DW, 0,
                sizeof(DW_T));

  /* external inputs */
  (void)memset(&U, 0, sizeof(ExtU_T));

  /* external outputs */
  (void)memset(&Y, 0, sizeof(ExtY_T));

  /* SystemInitialize for Atomic SubSystem: 'PwmInTargetSpeedEval' (':961') */
  PwmInTargetSpeedEval_Init();

  /* End of SystemInitialize for SubSystem: 'PwmInTargetSpeedEval' (':961') */

  /* SystemInitialize for Atomic SubSystem: 'ECUFaultDiag' (':769') */

  /* SystemInitialize for Outport: 'VoltageStatus' (':2265') incorporates:
   *  Outport: 'AmbTStatus' (':2266')
   */
  ECUFaultDiag_Init(&Y.VoltageStatus, &Y.AmbTStatus, &DW.ECUFaultDiag_ima5);

  /* End of SystemInitialize for SubSystem: 'ECUFaultDiag' (':769') */

  /* SystemInitialize for Atomic SubSystem: 'MotorRestartAndFaultCnt' (':815') */
  MotorRestartAndFaultCnt_Init(&DW.MotorRestartAndFaultCnt_bnwn);

  /* End of SystemInitialize for SubSystem: 'MotorRestartAndFaultCnt' (':815') */

  /* SystemInitialize for Atomic SubSystem: 'FeedBack' (':890') */
  FeedBack_Init();

  /* End of SystemInitialize for SubSystem: 'FeedBack' (':890') */

  /* SystemInitialize for Atomic SubSystem: 'SpeedLimit' (':2196') */

  /* SystemInitialize for Chart: 'TemperatureState' (':3099') */
  TemperatureState_Init(&B.Status, &DW.sf_TemperatureState);

  /* End of SystemInitialize for SubSystem: 'SpeedLimit' (':2196') */

  /* ConstCode for Outport: 'ChipSleep' (':1625') */
  Y.ChipSleep = false;

  /* ConstCode for Outport: 'ChipReset' (':1626') */
  Y.ChipReset = false;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */