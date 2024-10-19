/*
 * File: MotorRestartAndFaultCnt.c
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
#include "MotorRestartAndFaultCnt.h"
#include "AppMain_private.h"

/* Named constants for Chart: ''MotorRestartFSM' (':871')' */
#define IN_NO_ACTIVE_CHILD_fjpc        ((uint8_T)0U)
#define IN_ReStart                     ((uint8_T)1U)
#define IN_TimeCnt                     ((uint8_T)2U)

/*
 * Output and update for action system:
 *    'Short' (':2460')
 *    'Open' (':2470')
 *    'Lock' (':2479')
 */
void Short(uint16_T *rty_Interval)
{
  /* Switch: 'Switch5' (':2469') incorporates:
   *  Constant: 'Constant1' (':2466')
   */
  *rty_Interval = 200U;
}

/* System initialize for atomic system: 'MotorRestartAndFaultCnt' (':815') */
void MotorRestartAndFaultCnt_Init(DW_MotorRestartAndFaultCnt_T *localDW)
{
  /* Start for If: 'If' (':1833') */
  localDW->If_ActiveSubsystem = -1;

  /* SystemInitialize for IfAction SubSystem: 'MotorFalutHandle' (':1838') */
  /* InitializeConditions for Memory: 'Memory' (':3185') */
  localDW->Memory_PreviousInput = 0U;

  /* InitializeConditions for Memory: 'RestartIntervalLast' (':2133') */
  localDW->RestartIntervalLast_PreviousInp = 0U;

  /* SystemInitialize for Atomic SubSystem: 'MotorFaultRecoverTimer' (':835') */
  /* SystemInitialize for Chart: 'MotorRestartFSM' (':871') */
  localDW->is_active_c1_AppMain = 0U;
  localDW->is_c1_AppMain = IN_NO_ACTIVE_CHILD_fjpc;
  localDW->TimeCnt = 0U;

  /* End of SystemInitialize for SubSystem: 'MotorFaultRecoverTimer' (':835') */
  /* End of SystemInitialize for SubSystem: 'MotorFalutHandle' (':1838') */
}

/* Output and update for atomic system: 'MotorRestartAndFaultCnt' (':815') */
void MotorRestartAndFaultCnt(int16_T rtu_TargetSpeed, boolean_T rtu_ECUFault,
  boolean_T rtu_RestartComplete, boolean_T rtu_IsMotorShort, boolean_T
  rtu_IsMotorLock, boolean_T rtu_IsMotorOpenLoad, boolean_T
  rtu_IsMotorDryRunning, int16_T rtu_PwmInCtrlSpeed, int16_T *rty_FaultSpeed,
  boolean_T *rty_FaultRestartEn, uint8_T *rty_ShortCnt, uint8_T *rty_OpenCnt,
  uint8_T *rty_LockCnt, DW_MotorRestartAndFaultCnt_T *localDW)
{
  int16_T rtb_Merge_ctka;
  uint16_T qY;
  uint16_T rtb_RestartInterval;
  int8_T rtAction;
  int8_T rtPrevAction;
  uint8_T rtb_FaultDetectedLast_Lock;
  uint8_T rtb_FaultDetectedLast_Open;
  uint8_T rtb_FaultDetectedLast_Short;
  uint8_T rtb_Short_melb;
  uint8_T rtb_Switch3_fx3j;
  uint8_T rtb_Switch4;

  /* SignalConversion generated from: 'LockCnt' (':2583') incorporates:
   *  Memory: 'LockCntLast' (':2086')
   */
  *rty_LockCnt = localDW->LockCntLast_PreviousInput;

  /* SignalConversion generated from: 'OpenCnt' (':2582') incorporates:
   *  Memory: 'OpenCntLast' (':2085')
   */
  *rty_OpenCnt = localDW->OpenCntLast_PreviousInput;

  /* SignalConversion generated from: 'ShortCnt' (':2581') incorporates:
   *  Memory: 'ShortCntLast' (':834')
   */
  *rty_ShortCnt = localDW->ShortCntLast_PreviousInput;

  /* If: 'If' (':1833') incorporates:
   *  Constant: 'Constant' (':2950:3')
   *  Logic: 'Logical Operator1' (':3058')
   *  Logic: 'Logical Operator4' (':1832')
   *  RelationalOperator: 'Compare' (':2950:2')
   */
  rtPrevAction = localDW->If_ActiveSubsystem;
  if (rtu_ECUFault)
  {
    rtAction = 0;
  }
  else if ((rtu_IsMotorShort || rtu_IsMotorLock || rtu_IsMotorOpenLoad) &&
           (rtu_PwmInCtrlSpeed != 0))
  {
    rtAction = 1;
  }
  else
  {
    rtAction = 2;
  }

  localDW->If_ActiveSubsystem = rtAction;
  switch (rtAction)
  {
   case 0:
    /* Outputs for IfAction SubSystem: 'ECUFalutHandle' (':1834') incorporates:
     *  ActionPort: 'Action Port' (':1836')
     */
    /* SignalConversion generated from: 'Speed' (':1851') incorporates:
     *  Constant: 'Constant' (':1860')
     */
    rtb_Merge_ctka = 0;

    /* SignalConversion generated from: 'FaultRestartEn' (':1867') incorporates:
     *  Constant: 'Constant2' (':1868')
     */
    *rty_FaultRestartEn = false;

    /* SignalConversion generated from: 'FalutCntLast' (':1835') incorporates:
     *  Memory: 'LockCntLast' (':2086')
     *  Memory: 'OpenCntLast' (':2085')
     *  Memory: 'ShortCntLast' (':834')
     *  Merge: 'Merge1' (':3007')
     */
    rtb_FaultDetectedLast_Short = localDW->ShortCntLast_PreviousInput;
    rtb_FaultDetectedLast_Open = localDW->OpenCntLast_PreviousInput;
    rtb_FaultDetectedLast_Lock = localDW->LockCntLast_PreviousInput;

    /* End of Outputs for SubSystem: 'ECUFalutHandle' (':1834') */
    break;

   case 1:
    if ((int16_T)rtAction != (int16_T)rtPrevAction)
    {
      /* InitializeConditions for IfAction SubSystem: 'MotorFalutHandle' (':1838') incorporates:
       *  ActionPort: 'Action Port' (':1840')
       */
      /* InitializeConditions for If: 'If' (':1833') incorporates:
       *  Memory: 'Memory' (':3185')
       *  Memory: 'RestartIntervalLast' (':2133')
       */
      localDW->Memory_PreviousInput = 0U;
      localDW->RestartIntervalLast_PreviousInp = 0U;

      /* End of InitializeConditions for SubSystem: 'MotorFalutHandle' (':1838') */

      /* SystemReset for IfAction SubSystem: 'MotorFalutHandle' (':1838') incorporates:
       *  ActionPort: 'Action Port' (':1840')
       */
      /* SystemReset for Atomic SubSystem: 'MotorFaultRecoverTimer' (':835') */
      /* SystemReset for If: 'If' (':1833') incorporates:
       *  Chart: 'MotorRestartFSM' (':871')
       */
      localDW->is_active_c1_AppMain = 0U;
      localDW->is_c1_AppMain = IN_NO_ACTIVE_CHILD_fjpc;
      localDW->TimeCnt = 0U;

      /* End of SystemReset for SubSystem: 'MotorFaultRecoverTimer' (':835') */
      /* End of SystemReset for SubSystem: 'MotorFalutHandle' (':1838') */
    }

    /* Outputs for IfAction SubSystem: 'MotorFalutHandle' (':1838') incorporates:
     *  ActionPort: 'Action Port' (':1840')
     */
    /* If: 'If' (':2019') incorporates:
     *  Constant: 'Constant' (':2866:3')
     *  Constant: 'Constant' (':3186:3')
     *  Logic: 'Logical Operator' (':2867')
     *  Logic: 'Logical Operator1' (':3184')
     *  Memory: 'Memory' (':3185')
     *  RelationalOperator: 'Compare' (':2866:2')
     *  RelationalOperator: 'Compare' (':3186:2')
     *  SignalConversion generated from: 'TargetSpeed' (':2193')
     */
    if (((int16_T)localDW->Memory_PreviousInput == 0) || ((rtu_TargetSpeed != 0)
         && rtu_RestartComplete))
    {
      /* Outputs for IfAction SubSystem: 'If Action Subsystem' (':2020') incorporates:
       *  ActionPort: 'Action Port' (':2022')
       */
      /* Switch: 'Switch' (':2127') incorporates:
       *  Constant: 'Constant1' (':2126')
       *  Sum: 'Add' (':2120')
       */
      if (rtu_IsMotorShort)
      {
        /* Sum: 'Add' (':2120') incorporates:
         *  Constant: 'Constant' (':2125')
         *  Memory: 'ShortCntLast' (':834')
         */
        qY = (uint16_T)((uint16_T)localDW->ShortCntLast_PreviousInput + 1U);
        if ((uint16_T)((uint16_T)localDW->ShortCntLast_PreviousInput + 1U) >
            255U)
        {
          qY = 255U;
        }

        rtb_Short_melb = (uint8_T)qY;
      }
      else
      {
        rtb_Short_melb = 0U;
      }

      /* End of Switch: 'Switch' (':2127') */

      /* Switch: 'Switch3' (':2883') incorporates:
       *  Constant: 'Constant3' (':2880')
       */
      if (rtu_IsMotorOpenLoad)
      {
        /* Switch: 'Switch1' (':2900') incorporates:
         *  Memory: 'OpenCntLast' (':2085')
         *  Sum: 'Add3' (':2878')
         */
        if (rtu_IsMotorShort)
        {
          rtb_Switch3_fx3j = localDW->OpenCntLast_PreviousInput;
        }
        else
        {
          /* Sum: 'Add3' (':2878') incorporates:
           *  Constant: 'Constant2' (':2879')
           *  Memory: 'OpenCntLast' (':2085')
           */
          qY = (uint16_T)((uint16_T)localDW->OpenCntLast_PreviousInput + 1U);
          if ((uint16_T)((uint16_T)localDW->OpenCntLast_PreviousInput + 1U) >
              255U)
          {
            qY = 255U;
          }

          rtb_Switch3_fx3j = (uint8_T)qY;
        }

        /* End of Switch: 'Switch1' (':2900') */
      }
      else
      {
        rtb_Switch3_fx3j = 0U;
      }

      /* End of Switch: 'Switch3' (':2883') */

      /* Switch: 'Switch4' (':2894') incorporates:
       *  Constant: 'Constant5' (':2889')
       */
      if (rtu_IsMotorLock)
      {
        /* Switch: 'Switch2' (':2902') incorporates:
         *  Logic: 'Logical Operator4' (':2893')
         *  Memory: 'LockCntLast' (':2086')
         *  Sum: 'Add4' (':2887')
         */
        if (rtu_IsMotorShort || rtu_IsMotorOpenLoad)
        {
          rtb_Switch4 = localDW->LockCntLast_PreviousInput;
        }
        else
        {
          /* Sum: 'Add4' (':2887') incorporates:
           *  Constant: 'Constant4' (':2888')
           *  Memory: 'LockCntLast' (':2086')
           */
          qY = (uint16_T)((uint16_T)localDW->LockCntLast_PreviousInput + 1U);
          if ((uint16_T)((uint16_T)localDW->LockCntLast_PreviousInput + 1U) >
              255U)
          {
            qY = 255U;
          }

          rtb_Switch4 = (uint8_T)qY;
        }

        /* End of Switch: 'Switch2' (':2902') */
      }
      else
      {
        rtb_Switch4 = 0U;
      }

      /* End of Switch: 'Switch4' (':2894') */

      /* SignalConversion generated from: 'FaultCnt' (':2023') incorporates:
       *  BusCreator: 'Bus Creator' (':2123')
       *  Merge: 'Merge1' (':3007')
       */
      rtb_FaultDetectedLast_Short = rtb_Short_melb;
      rtb_FaultDetectedLast_Open = rtb_Switch3_fx3j;
      rtb_FaultDetectedLast_Lock = rtb_Switch4;

      /* If: 'If' (':2464') incorporates:
       *  BusCreator: 'Bus Creator' (':2123')
       */
      if ((int16_T)rtb_Short_melb > 0)
      {
        /* Outputs for IfAction SubSystem: 'Short' (':2460') incorporates:
         *  ActionPort: 'Action Port' (':2462')
         */
        /* SignalConversion generated from: 'RestartInterval' (':2131') */
        Short(&rtb_RestartInterval);

        /* End of Outputs for SubSystem: 'Short' (':2460') */
      }
      else if ((int16_T)rtb_Switch3_fx3j > 0)
      {
        /* Outputs for IfAction SubSystem: 'Open' (':2470') incorporates:
         *  ActionPort: 'Action Port' (':2472')
         */
        /* SignalConversion generated from: 'RestartInterval' (':2131') */
        Short(&rtb_RestartInterval);

        /* End of Outputs for SubSystem: 'Open' (':2470') */
      }
      else
      {
        /* Outputs for IfAction SubSystem: 'Lock' (':2479') incorporates:
         *  ActionPort: 'Action Port' (':2481')
         */
        /* SignalConversion generated from: 'RestartInterval' (':2131') */
        Short(&rtb_RestartInterval);

        /* End of Outputs for SubSystem: 'Lock' (':2479') */
      }

      /* End of If: 'If' (':2464') */
      /* End of Outputs for SubSystem: 'If Action Subsystem' (':2020') */
    }
    else
    {
      /* Outputs for IfAction SubSystem: 'If Action Subsystem1' (':2024') incorporates:
       *  ActionPort: 'Action Port' (':2026')
       */
      /* BusCreator: 'Bus Creator' (':2095') incorporates:
       *  Memory: 'LockCntLast' (':2086')
       *  Memory: 'OpenCntLast' (':2085')
       *  Memory: 'ShortCntLast' (':834')
       *  Merge: 'Merge1' (':3007')
       */
      rtb_FaultDetectedLast_Short = localDW->ShortCntLast_PreviousInput;
      rtb_FaultDetectedLast_Open = localDW->OpenCntLast_PreviousInput;
      rtb_FaultDetectedLast_Lock = localDW->LockCntLast_PreviousInput;

      /* SignalConversion generated from: 'RestartIntervalLast' (':2135') incorporates:
       *  Memory: 'RestartIntervalLast' (':2133')
       */
      rtb_RestartInterval = localDW->RestartIntervalLast_PreviousInp;

      /* End of Outputs for SubSystem: 'If Action Subsystem1' (':2024') */
    }

    /* End of If: 'If' (':2019') */

    /* SignalConversion generated from: 'Speed' (':1854') incorporates:
     *  SignalConversion generated from: 'TargetSpeed' (':2193')
     */
    rtb_Merge_ctka = rtu_TargetSpeed;

    /* Outputs for Atomic SubSystem: 'MotorFaultRecoverTimer' (':835') */
    /* Chart: 'MotorRestartFSM' (':871') */
    /* Gateway: MotorRestartAndFaultCnt/MotorFalutHandle/MotorFaultRecoverTimer/MotorRestartFSM */
    /* During: MotorRestartAndFaultCnt/MotorFalutHandle/MotorFaultRecoverTimer/MotorRestartFSM */
    if ((uint16_T)localDW->is_active_c1_AppMain == 0U)
    {
      /* Entry: MotorRestartAndFaultCnt/MotorFalutHandle/MotorFaultRecoverTimer/MotorRestartFSM */
      localDW->is_active_c1_AppMain = 1U;

      /* Entry Internal: MotorRestartAndFaultCnt/MotorFalutHandle/MotorFaultRecoverTimer/MotorRestartFSM */
      /* Transition: (':871:19') */
      localDW->is_c1_AppMain = IN_TimeCnt;

      /* Entry 'TimeCnt': (':871:16') */
      localDW->TimeCnt = 1U;

      /* SignalConversion generated from: 'FaultRestartEn' (':1872') */
      *rty_FaultRestartEn = false;
    }
    else if (localDW->is_c1_AppMain == IN_ReStart)
    {
      /* SignalConversion generated from: 'FaultRestartEn' (':1872') */
      *rty_FaultRestartEn = true;

      /* During 'ReStart': (':871:4') */
      if (rtu_RestartComplete)
      {
        /* Transition: (':871:18') */
        localDW->is_c1_AppMain = IN_TimeCnt;

        /* Entry 'TimeCnt': (':871:16') */
        localDW->TimeCnt = 1U;

        /* SignalConversion generated from: 'FaultRestartEn' (':1872') */
        *rty_FaultRestartEn = false;
      }
    }
    else
    {
      /* SignalConversion generated from: 'FaultRestartEn' (':1872') */
      *rty_FaultRestartEn = false;

      /* During 'TimeCnt': (':871:16') */
      if ((localDW->TimeCnt >= rtb_RestartInterval) && (rtb_RestartInterval !=
           MAX_uint16_T))
      {
        /* Transition: (':871:17') */
        localDW->is_c1_AppMain = IN_ReStart;

        /* SignalConversion generated from: 'FaultRestartEn' (':1872') */
        /* Entry 'ReStart': (':871:4') */
        *rty_FaultRestartEn = true;
      }
      else
      {
        qY = (uint16_T)(localDW->TimeCnt + 1U);
        if ((uint16_T)(localDW->TimeCnt + 1U) < localDW->TimeCnt)
        {
          qY = MAX_uint16_T;
        }

        localDW->TimeCnt = qY;
      }
    }

    /* End of Chart: 'MotorRestartFSM' (':871') */
    /* End of Outputs for SubSystem: 'MotorFaultRecoverTimer' (':835') */

    /* Update for Memory: 'Memory' (':3185') incorporates:
     *  Constant: 'Constant' (':3183')
     */
    localDW->Memory_PreviousInput = 1U;

    /* Update for Memory: 'RestartIntervalLast' (':2133') */
    localDW->RestartIntervalLast_PreviousInp = rtb_RestartInterval;

    /* End of Outputs for SubSystem: 'MotorFalutHandle' (':1838') */
    break;

   default:
    /* Outputs for IfAction SubSystem: 'Normal' (':1845') incorporates:
     *  ActionPort: 'Action Port' (':1849')
     */
    /* SignalConversion generated from: 'FaultRestartEn' (':1870') incorporates:
     *  Constant: 'Constant2' (':1869')
     */
    *rty_FaultRestartEn = false;

    /* BusCreator: 'Bus Creator' (':2088') incorporates:
     *  Constant: 'Constant' (':2092')
     *  Constant: 'Constant3' (':2093')
     *  Constant: 'Constant4' (':2094')
     *  Merge: 'Merge1' (':3007')
     */
    rtb_FaultDetectedLast_Short = 0U;
    rtb_FaultDetectedLast_Open = 0U;
    rtb_FaultDetectedLast_Lock = 0U;

    /* SignalConversion generated from: 'TargetSpeed' (':2000') */
    rtb_Merge_ctka = rtu_TargetSpeed;

    /* End of Outputs for SubSystem: 'Normal' (':1845') */
    break;
  }

  /* End of If: 'If' (':1833') */

  /* Switch: 'Switch' (':2864') incorporates:
   *  Constant: 'Constant' (':2865')
   */
  if (rtu_IsMotorDryRunning)
  {
    *rty_FaultSpeed = 0;
  }
  else
  {
    *rty_FaultSpeed = rtb_Merge_ctka;
  }

  /* End of Switch: 'Switch' (':2864') */

  /* Update for Memory: 'ShortCntLast' (':834') incorporates:
   *  Merge: 'Merge1' (':3007')
   */
  localDW->ShortCntLast_PreviousInput = rtb_FaultDetectedLast_Short;

  /* Update for Memory: 'OpenCntLast' (':2085') incorporates:
   *  Merge: 'Merge1' (':3007')
   */
  localDW->OpenCntLast_PreviousInput = rtb_FaultDetectedLast_Open;

  /* Update for Memory: 'LockCntLast' (':2086') incorporates:
   *  Merge: 'Merge1' (':3007')
   */
  localDW->LockCntLast_PreviousInput = rtb_FaultDetectedLast_Lock;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
