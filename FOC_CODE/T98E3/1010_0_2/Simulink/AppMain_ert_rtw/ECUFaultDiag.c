/*
 * File: ECUFaultDiag.c
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

#include "rtwtypes.h"
#include "ECUFaultDiag.h"
#include "rt_sys_ECUFaultDiag_0.h"
#include "AppMain_private.h"

/* System initialize for atomic system: 'AmbTemperatureDiag' (':1039') */
void AmbTemperatureDiag_Init(int8_T *rty_AmbTStatus, DW_AmbTemperatureDiag_T
  *localDW)
{
  /* SystemInitialize for Chart: 'AmbTOverDiag' (':1621') */
  AmbTOverDiag_Init(rty_AmbTStatus, &localDW->sf_AmbTOverDiag);
}

/* Output and update for atomic system: 'AmbTemperatureDiag' (':1039') */
void AmbTemperatureDiag(int16_T rtu_AmbTemperature, int8_T *rty_AmbTStatus,
  DW_AmbTemperatureDiag_T *localDW)
{
  /* Chart: 'AmbTOverDiag' (':1621') */
  AmbTOverDiag(rtu_AmbTemperature, rty_AmbTStatus, 10, 150, 148, -40, -38,
               &localDW->sf_AmbTOverDiag);
}

/* System initialize for atomic system: 'VoltageDiag' (':797') */
void VoltageDiag_Init(int8_T *rty_VoltageStatus, DW_VoltageDiag_T *localDW)
{
  /* SystemInitialize for Chart: 'VoltageDiag' (':1620') */
  AmbTOverDiag_Init(rty_VoltageStatus, &localDW->sf_VoltageDiag);
}

/* Output and update for atomic system: 'VoltageDiag' (':797') */
void VoltageDiag(int16_T rtu_Voltage, int8_T *rty_VoltageStatus,
                 DW_VoltageDiag_T *localDW)
{
  /* Chart: 'VoltageDiag' (':1620') */
  AmbTOverDiag(rtu_Voltage, rty_VoltageStatus, 10, 180, 170, 80, 90,
               &localDW->sf_VoltageDiag);
}

/* System initialize for atomic system: 'ECUFaultDiag' (':769') */
void ECUFaultDiag_Init(int8_T *rty_VoltageStatus, int8_T *rty_AmbTStatus,
  DW_ECUFaultDiag_T *localDW)
{
  /* SystemInitialize for Atomic SubSystem: 'AmbTemperatureDiag' (':1039') */
  AmbTemperatureDiag_Init(rty_AmbTStatus, &localDW->AmbTemperatureDiag_hnpz);

  /* End of SystemInitialize for SubSystem: 'AmbTemperatureDiag' (':1039') */

  /* SystemInitialize for Atomic SubSystem: 'VoltageDiag' (':797') */
  VoltageDiag_Init(rty_VoltageStatus, &localDW->VoltageDiag_ospw);

  /* End of SystemInitialize for SubSystem: 'VoltageDiag' (':797') */
}

/* Output and update for atomic system: 'ECUFaultDiag' (':769') */
void ECUFaultDiag(int16_T rtu_SupVoltage, int16_T rtu_AmbTemperature, boolean_T
                  rtu_ChipFault, boolean_T *rty_ECUFault, int8_T
                  *rty_VoltageStatus, int8_T *rty_AmbTStatus, DW_ECUFaultDiag_T *
                  localDW)
{
  /* Outputs for Atomic SubSystem: 'AmbTemperatureDiag' (':1039') */
  AmbTemperatureDiag(rtu_AmbTemperature, rty_AmbTStatus,
                     &localDW->AmbTemperatureDiag_hnpz);

  /* End of Outputs for SubSystem: 'AmbTemperatureDiag' (':1039') */

  /* Outputs for Atomic SubSystem: 'VoltageDiag' (':797') */
  VoltageDiag(rtu_SupVoltage, rty_VoltageStatus, &localDW->VoltageDiag_ospw);

  /* End of Outputs for SubSystem: 'VoltageDiag' (':797') */

  /* Logic: 'Logical Operator' (':796') incorporates:
   *  Constant: 'Constant' (':790:3')
   *  Constant: 'Constant' (':791:3')
   *  RelationalOperator: 'Compare' (':790:2')
   *  RelationalOperator: 'Compare' (':791:2')
   */
  *rty_ECUFault = (((int32_T)*rty_VoltageStatus != 0) || ((int32_T)
    *rty_AmbTStatus != 0) || rtu_ChipFault);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
