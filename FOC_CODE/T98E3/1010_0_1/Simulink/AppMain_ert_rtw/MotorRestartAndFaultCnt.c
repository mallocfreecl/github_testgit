/*
 * File: MotorRestartAndFaultCnt.c
 *
 * Code generated for Simulink model 'AppMain'.
 *
 * Model version                  : 5.101
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Mon Aug 26 16:49:11 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
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
 */
void Short(uint8_T rtu_FaultCnt, uint16_T *rty_Interval)
{
  /* Switch: 'Switch5' (':2469') incorporates:
   *  Constant: 'Constant1' (':2466')
   *  Constant: 'Constant2' (':2467')
   *  RelationalOperator: 'Relational Operator' (':2468')
   */
  if ((int32_T)rtu_FaultCnt < 15)
  {
    *rty_Interval = 200U;
  }
  else
  {
    *rty_Interval = MAX_uint16_T;
  }

  /* End of Switch: 'Switch5' (':2469') */
}

/* System initialize for atomic system: 'MotorRestartAndFaultCnt' (':815') */
void MotorRestartAndFaultCnt_Init(DW_MotorRestartAndFaultCnt_T *localDW)
{
  /* Start for If: 'If' (':1833') */
  localDW->If_ActiveSubsystem = -1;

  /* SystemInitialize for IfAction SubSystem: 'MotorFalutHandle' (':1838') */
  /* Start for If: 'If' (':2851') */
  localDW->If_ActiveSubsystem_ghbp = -1;

  /* InitializeConditions for Memory: 'RestartIntervalLast' (':2133') */
  localDW->RestartIntervalLast_PreviousInp = 0U;

  /* SystemInitialize for Atomic SubSystem: 'MotorFaultRecoverTimer' (':835') */
  /* SystemInitialize for Chart: 'MotorRestartFSM' (':871') */
  localDW->is_active_c1_AppMain = 0U;
  localDW->is_c1_AppMain = IN_NO_ACTIVE_CHILD_fjpc;
  localDW->TimeCnt = 0U;

  /* End of SystemInitialize for SubSystem: 'MotorFaultRecoverTimer' (':835') */

  /* SystemInitialize for IfAction SubSystem: 'If Action Subsystem1' (':2841') */
  /* InitializeConditions for Memory: 'Memory' (':2852') */
  localDW->Memory_PreviousInput = 0U;

  /* InitializeConditions for UnitDelay: 'Delay Input1' (':2849:2')
   *
   * Block description for 'Delay Input1' (':2849:2'):
   *
   *  Store in Global RAM
   */
  localDW->DelayInput1_DSTATE_jdnj = false;

  /* End of SystemInitialize for SubSystem: 'If Action Subsystem1' (':2841') */
  /* End of SystemInitialize for SubSystem: 'MotorFalutHandle' (':1838') */
}

/* Output and update for atomic system: 'MotorRestartAndFaultCnt' (':815') */
void MotorRestartAndFaultCnt(int16_T rtu_TargetSpeed, boolean_T rtu_ECUFault,
  boolean_T rtu_RestartComplete, boolean_T rtu_IsMotorShort, boolean_T
  rtu_IsMotorLock, boolean_T rtu_IsMotorOpenLoad, boolean_T
  rtu_IsMotorDryRunning, int16_T *rty_FaultSpeed, boolean_T *rty_FaultRestartEn,
  uint8_T *rty_ShortCnt, uint8_T *rty_OpenCnt, uint8_T *rty_LockCnt,
  DW_MotorRestartAndFaultCnt_T *localDW)
{
  int32_T tmp_0;
  uint32_T tmp;
  int16_T rtb_Merge_ctka;
  uint16_T rtb_RestartInterval;
  uint16_T rtb_Switch_p2x0;
  int8_T rtAction;
  int8_T rtPrevAction;
  uint8_T rtb_FaultDetectedLast_Lock;
  uint8_T rtb_FaultDetectedLast_Open;
  uint8_T rtb_FaultDetectedLast_Short;
  uint8_T rtb_Short_melb;
  uint8_T rtb_Switch3_fx3j;
  uint8_T rtb_Switch4_kyq4;
  boolean_T rtb_RecoverEn;

  /* If: 'If' (':1833') incorporates:
   *  Logic: 'Logical Operator4' (':1832')
   */
  rtPrevAction = localDW->If_ActiveSubsystem;
  if (rtu_ECUFault)
  {
    rtAction = 0;
  }
  else if (rtu_IsMotorShort || rtu_IsMotorLock || rtu_IsMotorOpenLoad)
  {
    rtAction = 1;
  }
  else
  {
    rtAction = 2;
  }

  localDW->If_ActiveSubsystem = rtAction;
  if (((int32_T)rtPrevAction != (int32_T)rtAction) && ((int32_T)rtPrevAction ==
       1))
  {
    /* Disable for If: 'If' (':2851') */
    localDW->If_ActiveSubsystem_ghbp = -1;
  }

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
    if ((int32_T)rtAction != (int32_T)rtPrevAction)
    {
      /* InitializeConditions for IfAction SubSystem: 'MotorFalutHandle' (':1838') incorporates:
       *  ActionPort: 'Action Port' (':1840')
       */
      /* InitializeConditions for If: 'If' (':1833') incorporates:
       *  Memory: 'RestartIntervalLast' (':2133')
       */
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
     *  Logic: 'Logical Operator' (':2867')
     *  RelationalOperator: 'Compare' (':2866:2')
     */
    if (((int32_T)rtu_TargetSpeed != 0) && rtu_RestartComplete)
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
        tmp_0 = (int32_T)(uint32_T)((uint32_T)
          localDW->ShortCntLast_PreviousInput + 1U);
        if ((uint32_T)((uint32_T)localDW->ShortCntLast_PreviousInput + 1U) >
            255U)
        {
          tmp_0 = 255;
        }

        rtb_Short_melb = (uint8_T)tmp_0;
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
          tmp_0 = (int32_T)(uint32_T)((uint32_T)
            localDW->OpenCntLast_PreviousInput + 1U);
          if ((uint32_T)((uint32_T)localDW->OpenCntLast_PreviousInput + 1U) >
              255U)
          {
            tmp_0 = 255;
          }

          rtb_Switch3_fx3j = (uint8_T)tmp_0;
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
          rtb_Switch4_kyq4 = localDW->LockCntLast_PreviousInput;
        }
        else
        {
          /* Sum: 'Add4' (':2887') incorporates:
           *  Constant: 'Constant4' (':2888')
           *  Memory: 'LockCntLast' (':2086')
           */
          tmp_0 = (int32_T)(uint32_T)((uint32_T)
            localDW->LockCntLast_PreviousInput + 1U);
          if ((uint32_T)((uint32_T)localDW->LockCntLast_PreviousInput + 1U) >
              255U)
          {
            tmp_0 = 255;
          }

          rtb_Switch4_kyq4 = (uint8_T)tmp_0;
        }

        /* End of Switch: 'Switch2' (':2902') */
      }
      else
      {
        rtb_Switch4_kyq4 = 0U;
      }

      /* End of Switch: 'Switch4' (':2894') */

      /* SignalConversion generated from: 'FaultCnt' (':2023') incorporates:
       *  BusCreator: 'Bus Creator' (':2123')
       *  Merge: 'Merge1' (':3007')
       */
      rtb_FaultDetectedLast_Short = rtb_Short_melb;
      rtb_FaultDetectedLast_Open = rtb_Switch3_fx3j;
      rtb_FaultDetectedLast_Lock = rtb_Switch4_kyq4;

      /* If: 'If' (':2464') incorporates:
       *  BusCreator: 'Bus Creator' (':2123')
       *  RelationalOperator: 'Relational Operator' (':2485')
       *  Switch: 'Switch5' (':2486')
       */
      if ((int32_T)rtb_Short_melb > 0)
      {
        /* Outputs for IfAction SubSystem: 'Short' (':2460') incorporates:
         *  ActionPort: 'Action Port' (':2462')
         */
        /* SignalConversion generated from: 'RestartInterval' (':2131') */
        Short(rtb_Short_melb, &rtb_RestartInterval);

        /* End of Outputs for SubSystem: 'Short' (':2460') */
      }
      else if ((int32_T)rtb_Switch3_fx3j > 0)
      {
        /* Outputs for IfAction SubSystem: 'Open' (':2470') incorporates:
         *  ActionPort: 'Action Port' (':2472')
         */
        /* SignalConversion generated from: 'RestartInterval' (':2131') */
        Short(rtb_Switch3_fx3j, &rtb_RestartInterval);

        /* End of Outputs for SubSystem: 'Open' (':2470') */

        /* Outputs for IfAction SubSystem: 'Lock' (':2479') incorporates:
         *  ActionPort: 'Action Port' (':2481')
         */
      }
      else if ((int32_T)rtb_Switch4_kyq4 < 15)
      {
        /* Switch: 'Switch5' (':2486') incorporates:
         *  Constant: 'Constant1' (':2483')
         *  Merge: 'Merge' (':2488')
         *  SignalConversion generated from: 'RestartInterval' (':2131')
         */
        rtb_RestartInterval = 50U;
      }
      else
      {
        /* SignalConversion generated from: 'RestartInterval' (':2131') incorporates:
         *  Constant: 'Constant2' (':2484')
         *  Merge: 'Merge' (':2488')
         *  Switch: 'Switch5' (':2486')
         */
        rtb_RestartInterval = MAX_uint16_T;

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

    /* Outputs for Atomic SubSystem: 'MotorFaultRecoverTimer' (':835') */
    /* Chart: 'MotorRestartFSM' (':871') */
    /* Gateway: MotorRestartAndFaultCnt/MotorFalutHandle/MotorFaultRecoverTimer/MotorRestartFSM */
    /* During: MotorRestartAndFaultCnt/MotorFalutHandle/MotorFaultRecoverTimer/MotorRestartFSM */
    if ((uint32_T)localDW->is_active_c1_AppMain == 0U)
    {
      /* Entry: MotorRestartAndFaultCnt/MotorFalutHandle/MotorFaultRecoverTimer/MotorRestartFSM */
      localDW->is_active_c1_AppMain = 1U;

      /* Entry Internal: MotorRestartAndFaultCnt/MotorFalutHandle/MotorFaultRecoverTimer/MotorRestartFSM */
      /* Transition: (':871:19') */
      localDW->is_c1_AppMain = IN_TimeCnt;

      /* Entry 'TimeCnt': (':871:16') */
      localDW->TimeCnt = 1U;
      rtb_RecoverEn = false;
    }
    else if (localDW->is_c1_AppMain == IN_ReStart)
    {
      rtb_RecoverEn = true;

      /* During 'ReStart': (':871:4') */
      if (rtu_RestartComplete)
      {
        /* Transition: (':871:18') */
        localDW->is_c1_AppMain = IN_TimeCnt;

        /* Entry 'TimeCnt': (':871:16') */
        localDW->TimeCnt = 1U;
        rtb_RecoverEn = false;
      }
    }
    else
    {
      rtb_RecoverEn = false;

      /* During 'TimeCnt': (':871:16') */
      if ((localDW->TimeCnt >= rtb_RestartInterval) && ((int32_T)
           rtb_RestartInterval != 65535))
      {
        /* Transition: (':871:17') */
        localDW->is_c1_AppMain = IN_ReStart;

        /* Entry 'ReStart': (':871:4') */
        rtb_RecoverEn = true;
      }
      else
      {
        tmp = (uint32_T)((uint32_T)localDW->TimeCnt + 1U);
        if ((uint32_T)((uint32_T)localDW->TimeCnt + 1U) > 65535U)
        {
          tmp = 65535U;
        }

        localDW->TimeCnt = (uint16_T)tmp;
      }
    }

    /* End of Chart: 'MotorRestartFSM' (':871') */
    /* End of Outputs for SubSystem: 'MotorFaultRecoverTimer' (':835') */

    /* If: 'If' (':2851') incorporates:
     *  Logic: 'Logical Operator' (':2836')
     */
    rtPrevAction = localDW->If_ActiveSubsystem_ghbp;
    rtAction = (int8_T)((!rtu_IsMotorShort) && (!rtu_IsMotorOpenLoad));
    localDW->If_ActiveSubsystem_ghbp = rtAction;
    if ((int32_T)rtAction == 0)
    {
      /* Outputs for IfAction SubSystem: 'If Action Subsystem' (':2837') incorporates:
       *  ActionPort: 'Action Port' (':2839')
       */
      /* SignalConversion generated from: 'Speed' (':1854') incorporates:
       *  Merge: 'Merge' (':2860')
       *  SignalConversion generated from: 'SpeedIn' (':2838')
       */
      rtb_Merge_ctka = rtu_TargetSpeed;

      /* End of Outputs for SubSystem: 'If Action Subsystem' (':2837') */
    }
    else
    {
      if ((int32_T)rtPrevAction != 1)
      {
        /* InitializeConditions for IfAction SubSystem: 'If Action Subsystem1' (':2841') incorporates:
         *  ActionPort: 'Action Port' (':2843')
         */
        /* InitializeConditions for If: 'If' (':2851') incorporates:
         *  Memory: 'Memory' (':2852')
         *  UnitDelay: 'Delay Input1' (':2849:2')
         *
         * Block description for 'Delay Input1' (':2849:2'):
         *
         *  Store in Global RAM
         */
        localDW->Memory_PreviousInput = 0U;
        localDW->DelayInput1_DSTATE_jdnj = false;

        /* End of InitializeConditions for SubSystem: 'If Action Subsystem1' (':2841') */
      }

      /* Outputs for IfAction SubSystem: 'If Action Subsystem1' (':2841') incorporates:
       *  ActionPort: 'Action Port' (':2843')
       */
      /* Switch: 'Switch' (':2853') incorporates:
       *  Constant: 'Constant' (':2854')
       *  RelationalOperator: 'FixPt Relational Operator' (':2849:3')
       *  Sum: 'Add' (':2855')
       *  UnitDelay: 'Delay Input1' (':2849:2')
       *
       * Block description for 'Delay Input1' (':2849:2'):
       *
       *  Store in Global RAM
       */
      if ((int32_T)rtb_RecoverEn > (int32_T)localDW->DelayInput1_DSTATE_jdnj)
      {
        rtb_Switch_p2x0 = 0U;
      }
      else
      {
        /* Sum: 'Add' (':2855') incorporates:
         *  Constant: 'Constant1' (':2856')
         *  Memory: 'Memory' (':2852')
         */
        tmp = (uint32_T)((uint32_T)localDW->Memory_PreviousInput + 1U);
        if ((uint32_T)((uint32_T)localDW->Memory_PreviousInput + 1U) > 65535U)
        {
          tmp = 65535U;
        }

        rtb_Switch_p2x0 = (uint16_T)tmp;
      }

      /* End of Switch: 'Switch' (':2853') */

      /* Switch: 'Switch1' (':2857') incorporates:
       *  Constant: 'Constant' (':2858:3')
       *  RelationalOperator: 'Compare' (':2858:2')
       */
      if ((int32_T)rtb_Switch_p2x0 <= 400)
      {
        /* Switch: 'Switch2' (':3114') */
        if ((int32_T)rtu_TargetSpeed > 0)
        {
          /* SignalConversion generated from: 'Speed' (':1854') incorporates:
           *  Constant: 'Constant2' (':2859')
           */
          rtb_Merge_ctka = -1000;
        }
        else
        {
          /* SignalConversion generated from: 'Speed' (':1854') */
          rtb_Merge_ctka = rtu_TargetSpeed;
        }

        /* End of Switch: 'Switch2' (':3114') */
      }
      else
      {
        /* SignalConversion generated from: 'Speed' (':1854') */
        rtb_Merge_ctka = rtu_TargetSpeed;
      }

      /* End of Switch: 'Switch1' (':2857') */

      /* Update for Memory: 'Memory' (':2852') */
      localDW->Memory_PreviousInput = rtb_Switch_p2x0;

      /* Update for UnitDelay: 'Delay Input1' (':2849:2')
       *
       * Block description for 'Delay Input1' (':2849:2'):
       *
       *  Store in Global RAM
       */
      localDW->DelayInput1_DSTATE_jdnj = rtb_RecoverEn;

      /* End of Outputs for SubSystem: 'If Action Subsystem1' (':2841') */
    }

    /* End of If: 'If' (':2851') */

    /* SignalConversion generated from: 'FaultRestartEn' (':1872') */
    *rty_FaultRestartEn = rtb_RecoverEn;

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
