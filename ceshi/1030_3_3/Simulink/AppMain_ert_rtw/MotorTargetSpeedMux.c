/*
 * File: MotorTargetSpeedMux.c
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

#include "rtwtypes.h"
#include "MotorTargetSpeedMux.h"
#include "AppMain_private.h"

/* Output and update for atomic system: 'MotorTargetSpeedMux' (':916') */
int16_T MotorTargetSpeedMux(boolean_T rtu_TestModeSpeedCtrlEnable, int16_T
  rtu_TestModeSpeed, int16_T rtu_PwmInCtrlSpeed)
{
  int16_T rty_MotorTargetSpeed_0;

  /* Switch: 'Switch1' (':923') */
  if (rtu_TestModeSpeedCtrlEnable)
  {
    /* Switch: 'Switch2' (':1569') */
    rty_MotorTargetSpeed_0 = rtu_TestModeSpeed;
  }
  else
  {
    /* Switch: 'Switch2' (':1569') */
    rty_MotorTargetSpeed_0 = rtu_PwmInCtrlSpeed;
  }

  /* End of Switch: 'Switch1' (':923') */
  return rty_MotorTargetSpeed_0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
