/*
 * File: PwmInParamEval.c
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

#include "PwmInParamEval.h"
#include "AppMain.h"
#include "rtwtypes.h"
#include "AppMain_private.h"

/* Output and update for atomic system: 'PwmInshortDetect' (':943') */
void PwmInshortDetect(void)
{
  boolean_T rtb_RelationalOperator;

  /* RelationalOperator: 'Relational Operator' (':1630') incorporates:
   *  Constant: 'PwmInBusTimeOutCntTHR' (':946')
   *  Inport: 'PwmInIdleTime' (':1629')
   */
  rtb_RelationalOperator = ((int32_T)U.PwmInIdleTime >= 1000);

  /* Outport: 'PwmInShortBat' (':3089') incorporates:
   *  Inport: 'PwmInPinSts' (':1038')
   *  Logic: 'Logical Operator' (':1633')
   */
  Y.PwmInShortBat = (rtb_RelationalOperator && U.PwmInPinSts);

  /* Outport: 'PwmInShortGND' (':3087') incorporates:
   *  Inport: 'PwmInPinSts' (':1038')
   *  Logic: 'Logical Operator1' (':1634')
   *  Logic: 'Logical Operator2' (':1635')
   */
  Y.PwmInShortGND = (rtb_RelationalOperator && (!U.PwmInPinSts));
}

/* Output and update for atomic system: 'PwmInParamEval' (':925') */
void PwmInParamEval(void)
{
  /* SignalConversion generated from: 'PwmInStatus' (':957') incorporates:
   *  Inport: 'PwmInFreq' (':1627')
   */
  B.Freq = U.PwmInFreq;

  /* SignalConversion generated from: 'PwmInStatus' (':957') incorporates:
   *  Inport: 'PwmInHighDuty' (':1628')
   */
  B.HighDuty = U.PwmInHighDuty;

  /* Outputs for Atomic SubSystem: 'PwmInshortDetect' (':943') */
  PwmInshortDetect();

  /* End of Outputs for SubSystem: 'PwmInshortDetect' (':943') */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
