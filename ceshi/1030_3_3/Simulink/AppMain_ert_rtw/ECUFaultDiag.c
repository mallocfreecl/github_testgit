/*
 * File: ECUFaultDiag.c
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
#include "ECUFaultDiag.h"
#include "rt_sys_ECUFaultDiag_0.h"
#include "AppMain_private.h"

/* Named constants for Chart: ''VoltageDiag' (':1620')' */
#define IN_DefaultStatus_d3yv          ((uint8_T)1U)
#define IN_High_iqat                   ((uint8_T)2U)
#define IN_Low_gidk                    ((uint8_T)3U)
#define IN_NO_ACTIVE_CHILD_feub        ((uint8_T)0U)
#define IN_Normal_f43b                 ((uint8_T)4U)

/* Forward declaration for local functions */
static void UpdateStateCnt_ofed(int16_T lowTHR, int16_T highTHR, int16_T
  rtu_Voltage, DW_VoltageDiag_T *localDW);

/* System initialize for atomic system: 'AmbTemperatureDiag' (':1039') */
void AmbTemperatureDiag_Init(int8_T *rty_AmbTStatus, DW_AmbTemperatureDiag_T
  *localDW)
{
  /* SystemInitialize for Chart: 'TemperatureState' (':3100') */
  TemperatureState_Init(rty_AmbTStatus, &localDW->sf_TemperatureState);
}

/* Output and update for atomic system: 'AmbTemperatureDiag' (':1039') */
void AmbTemperatureDiag(int16_T rtu_AmbTemperature, int8_T *rty_AmbTStatus,
  DW_AmbTemperatureDiag_T *localDW)
{
  /* Chart: 'TemperatureState' (':3100') */
  TemperatureState(rtu_AmbTemperature, rty_AmbTStatus, 400U, 145, 143, 2000U,
                   -40, -38, &localDW->sf_TemperatureState);
}

/* Function for Chart: ''VoltageDiag' (':1620')' */
static void UpdateStateCnt_ofed(int16_T lowTHR, int16_T highTHR, int16_T
  rtu_Voltage, DW_VoltageDiag_T *localDW)
{
  /* Chart: 'VoltageDiag' (':1620') */
  /* MATLAB Function 'UpdateStateCnt': (':6:39') */
  /* Graphical Function 'UpdateStateCnt': (':6:39') */
  /* Transition: (':6:41') */
  /* (':6:44:2') */
  if (rtu_Voltage < lowTHR)
  {
    uint16_T qY;

    /* Transition: (':6:44') */
    /* (':6:44:3') */
    qY = (uint16_T)(localDW->LowCnt + 1U);
    if ((uint16_T)(localDW->LowCnt + 1U) < localDW->LowCnt)
    {
      qY = MAX_uint16_T;
    }

    localDW->LowCnt = qY;

    /* (':6:44:4') */
    localDW->HighCnt = 0U;

    /* (':6:44:5') */
    localDW->NormalCnt = 0U;

    /* Transition: (':6:46') */
    /* (':6:48:2') */
  }
  else if (rtu_Voltage > highTHR)
  {
    uint16_T qY;

    /* Transition: (':6:48') */
    /* (':6:48:3') */
    localDW->LowCnt = 0U;

    /* (':6:48:4') */
    qY = (uint16_T)(localDW->HighCnt + 1U);
    if ((uint16_T)(localDW->HighCnt + 1U) < localDW->HighCnt)
    {
      qY = MAX_uint16_T;
    }

    localDW->HighCnt = qY;

    /* (':6:48:5') */
    localDW->NormalCnt = 0U;
  }
  else
  {
    uint16_T qY;

    /* Transition: (':6:50') */
    /* Transition: (':6:52') */
    /* (':6:52:2') */
    localDW->LowCnt = 0U;

    /* (':6:52:3') */
    localDW->HighCnt = 0U;

    /* (':6:52:4') */
    qY = (uint16_T)(localDW->NormalCnt + 1U);
    if ((uint16_T)(localDW->NormalCnt + 1U) < localDW->NormalCnt)
    {
      qY = MAX_uint16_T;
    }

    localDW->NormalCnt = qY;

    /* Transition: (':6:57') */

    /* Transition: (':6:58') */
  }

  /* End of Chart: 'VoltageDiag' (':1620') */
  /* Transition: (':6:56') */
}

/* System initialize for atomic system: 'VoltageDiag' (':797') */
void VoltageDiag_Init(int8_T *rty_VoltageStatus, DW_VoltageDiag_T *localDW)
{
  /* SystemInitialize for Chart: 'VoltageDiag' (':1620') */
  localDW->is_active_c2_lib1 = 0U;
  localDW->is_c2_lib1 = IN_NO_ACTIVE_CHILD_feub;
  localDW->LowCnt = 0U;
  localDW->HighCnt = 0U;
  localDW->NormalCnt = 0U;
  localDW->DefaultStatus = 0;
  localDW->IsInited = false;
  *rty_VoltageStatus = 0;
}

/* Output and update for atomic system: 'VoltageDiag' (':797') */
void VoltageDiag(int16_T rtu_Voltage, int8_T *rty_VoltageStatus,
                 DW_VoltageDiag_T *localDW)
{
  /* Chart: 'VoltageDiag' (':1620') */
  /* Gateway: HysteresisState */
  /* During: HysteresisState */
  if ((uint16_T)localDW->is_active_c2_lib1 == 0U)
  {
    /* Entry: HysteresisState */
    localDW->is_active_c2_lib1 = 1U;

    /* Entry Internal: HysteresisState */
    /* Transition: (':6:17') */
    localDW->is_c2_lib1 = IN_DefaultStatus_d3yv;

    /* Entry 'DefaultStatus': (':6:65') */
    localDW->IsInited = false;
  }
  else
  {
    switch (localDW->is_c2_lib1)
    {
     case IN_DefaultStatus_d3yv:
      /* During 'DefaultStatus': (':6:65') */
      if (localDW->IsInited)
      {
        /* Transition: (':6:90') */
        switch ((int16_T)localDW->DefaultStatus)
        {
         case 0:
          /* Transition: (':6:66') */
          localDW->is_c2_lib1 = IN_Normal_f43b;

          /* Entry 'Normal': (':6:16') */
          *rty_VoltageStatus = 0;
          break;

         case -1:
          /* Transition: (':6:68') */
          /* Transition: (':6:69') */
          localDW->is_c2_lib1 = IN_Low_gidk;

          /* Entry 'Low': (':6:20') */
          *rty_VoltageStatus = -1;
          break;

         default:
          /* Transition: (':6:71') */
          /* Transition: (':6:74') */
          /* Transition: (':6:73') */
          localDW->is_c2_lib1 = IN_High_iqat;

          /* Entry 'High': (':6:23') */
          *rty_VoltageStatus = 1;
          break;
        }
      }
      else
      {
        /* Transition: (':6:79') */
        if (rtu_Voltage > 362)
        {
          /* Transition: (':6:77') */
          localDW->DefaultStatus = 1;

          /* Transition: (':6:81') */
        }
        else if (rtu_Voltage < 150)
        {
          /* Transition: (':6:83') */
          localDW->DefaultStatus = -1;
        }
        else
        {
          /* Transition: (':6:85') */
          /* Transition: (':6:87') */
          localDW->DefaultStatus = 0;

          /* Transition: (':6:92') */

          /* Transition: (':6:93') */
        }

        /* Transition: (':6:94') */
        *rty_VoltageStatus = localDW->DefaultStatus;
        localDW->IsInited = true;
      }
      break;

     case IN_High_iqat:
      /* During 'High': (':6:23') */
      if ((rtu_Voltage < 150) && (localDW->LowCnt >= 200U))
      {
        /* Transition: (':6:30') */
        /* Transition: (':6:31') */
        localDW->is_c2_lib1 = IN_Low_gidk;

        /* Entry 'Low': (':6:20') */
        *rty_VoltageStatus = -1;
      }
      else if ((rtu_Voltage < 320) && (localDW->NormalCnt >= 200U))
      {
        /* Transition: (':6:25') */
        localDW->is_c2_lib1 = IN_Normal_f43b;

        /* Entry 'Normal': (':6:16') */
        *rty_VoltageStatus = 0;
      }
      else
      {
        UpdateStateCnt_ofed(150, 319, rtu_Voltage, localDW);
      }
      break;

     case IN_Low_gidk:
      /* During 'Low': (':6:20') */
      if ((rtu_Voltage > 362) && (localDW->HighCnt >= 200U))
      {
        /* Transition: (':6:27') */
        /* Transition: (':6:28') */
        localDW->is_c2_lib1 = IN_High_iqat;

        /* Entry 'High': (':6:23') */
        *rty_VoltageStatus = 1;
      }
      else if ((rtu_Voltage > 157) && (localDW->NormalCnt >= 200U))
      {
        /* Transition: (':6:21') */
        localDW->is_c2_lib1 = IN_Normal_f43b;

        /* Entry 'Normal': (':6:16') */
        *rty_VoltageStatus = 0;
      }
      else
      {
        UpdateStateCnt_ofed(158, 362, rtu_Voltage, localDW);
      }
      break;

     default:
      /* During 'Normal': (':6:16') */
      if ((rtu_Voltage < 150) && (localDW->LowCnt >= 200U))
      {
        /* Transition: (':6:22') */
        localDW->is_c2_lib1 = IN_Low_gidk;

        /* Entry 'Low': (':6:20') */
        *rty_VoltageStatus = -1;
      }
      else if ((rtu_Voltage > 362) && (localDW->HighCnt >= 200U))
      {
        /* Transition: (':6:24') */
        localDW->is_c2_lib1 = IN_High_iqat;

        /* Entry 'High': (':6:23') */
        *rty_VoltageStatus = 1;
      }
      else
      {
        UpdateStateCnt_ofed(150, 362, rtu_Voltage, localDW);
      }
      break;
    }
  }

  /* End of Chart: 'VoltageDiag' (':1620') */
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
  *rty_ECUFault = (((int16_T)*rty_VoltageStatus != 0) || ((int16_T)
    *rty_AmbTStatus != 0) || rtu_ChipFault);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
