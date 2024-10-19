/*
 * File: FeedBack.c
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
#include "FeedBack.h"
#include "AppMain.h"
#include "AppMain_private.h"

/* Named constants for Chart: ''DelayOut' (':2346:23:11')' */
#define IN_Delay                       ((uint8_T)1U)
#define IN_DirectOut                   ((uint8_T)2U)
#define IN_NO_ACTIVE_CHILD_nvry        ((uint8_T)0U)
#define IN_Reset                       ((uint8_T)3U)

/*
 * System initialize for atomic system:
 *    'DelayOut' (':2346:23')
 *    'DelayOut' (':2354:23')
 */
void DelayOut_Init(int16_T *rty_Out, DW_DelayOut_T *localDW)
{
  /* SystemInitialize for Chart: 'DelayOut' (':2346:23:11') */
  localDW->is_active_c3_lib1 = 0U;
  localDW->is_c3_lib1 = IN_NO_ACTIVE_CHILD_nvry;
  localDW->DelayCnt = 0U;
  *rty_Out = 0;
}

/*
 * Output and update for atomic system:
 *    'DelayOut' (':2346:23')
 *    'DelayOut' (':2354:23')
 */
void DelayOut(int16_T rtu_In, uint16_T rtu_DelayTime, int16_T *rty_Out,
              DW_DelayOut_T *localDW)
{
  boolean_T rtb_Rst_c5s2;

  /* Logic: 'Logical Operator' (':2346:23:14') incorporates:
   *  RelationalOperator: 'FixPt Relational Operator' (':2346:23:12:3')
   *  RelationalOperator: 'FixPt Relational Operator' (':2346:23:13:3')
   *  UnitDelay: 'Delay Input1' (':2346:23:12:2')
   *  UnitDelay: 'Delay Input1' (':2346:23:13:2')
   *
   * Block description for 'Delay Input1' (':2346:23:12:2'):
   *
   *  Store in Global RAM
   *
   * Block description for 'Delay Input1' (':2346:23:13:2'):
   *
   *  Store in Global RAM
   */
  rtb_Rst_c5s2 = ((rtu_DelayTime != localDW->DelayInput1_DSTATE_px1k) || (rtu_In
    != localDW->DelayInput1_DSTATE));

  /* Chart: 'DelayOut' (':2346:23:11') incorporates:
   *  Memory: 'OutLast' (':2346:23:15')
   */
  /* Gateway: DelayOut/DelayOut */
  /* During: DelayOut/DelayOut */
  if ((uint16_T)localDW->is_active_c3_lib1 == 0U)
  {
    /* Entry: DelayOut/DelayOut */
    localDW->is_active_c3_lib1 = 1U;

    /* Entry Internal: DelayOut/DelayOut */
    /* Transition: (':11:27') */
    if (rtu_DelayTime == 0U)
    {
      /* Transition: (':11:60') */
      localDW->is_c3_lib1 = IN_DirectOut;

      /* Entry 'DirectOut': (':11:46') */
      *rty_Out = rtu_In;
    }
    else
    {
      /* Transition: (':11:61') */
      /* Transition: (':11:57') */
      localDW->is_c3_lib1 = IN_Reset;

      /* Entry 'Reset': (':11:64') */
      localDW->DelayCnt = 2U;
      *rty_Out = localDW->OutLast_PreviousInput;
    }
  }
  else
  {
    switch (localDW->is_c3_lib1)
    {
     case IN_Delay:
      {
        /* During 'Delay': (':11:70') */
        if (rtu_DelayTime == 0U)
        {
          /* Transition: (':11:83') */
          /* Transition: (':11:82') */
          localDW->is_c3_lib1 = IN_DirectOut;

          /* Entry 'DirectOut': (':11:46') */
          *rty_Out = rtu_In;
        }
        else if (rtb_Rst_c5s2)
        {
          /* Transition: (':11:63') */
          localDW->is_c3_lib1 = IN_Reset;

          /* Entry 'Reset': (':11:64') */
          localDW->DelayCnt = 2U;
          *rty_Out = localDW->OutLast_PreviousInput;

          /* Transition: (':11:75') */
        }
        else if (localDW->DelayCnt < rtu_DelayTime)
        {
          uint16_T qY;

          /* Transition: (':11:76') */
          qY = (uint16_T)(localDW->DelayCnt + 1U);
          if ((uint16_T)(localDW->DelayCnt + 1U) < localDW->DelayCnt)
          {
            qY = MAX_uint16_T;
          }

          localDW->DelayCnt = qY;
          *rty_Out = localDW->OutLast_PreviousInput;
        }
        else
        {
          /* Transition: (':11:77') */
          /* Transition: (':11:79') */
          *rty_Out = rtu_In;

          /* Transition: (':11:78') */
        }
      }
      break;

     case IN_DirectOut:
      /* During 'DirectOut': (':11:46') */
      if (rtu_DelayTime != 0U)
      {
        /* Transition: (':11:84') */
        localDW->is_c3_lib1 = IN_Reset;

        /* Entry 'Reset': (':11:64') */
        localDW->DelayCnt = 2U;
        *rty_Out = localDW->OutLast_PreviousInput;
      }
      else
      {
        *rty_Out = rtu_In;
      }
      break;

     default:
      /* During 'Reset': (':11:64') */
      if (rtu_DelayTime == 0U)
      {
        /* Transition: (':11:48') */
        localDW->is_c3_lib1 = IN_DirectOut;

        /* Entry 'DirectOut': (':11:46') */
        *rty_Out = rtu_In;
      }
      else if (!rtb_Rst_c5s2)
      {
        /* Transition: (':11:80') */
        localDW->is_c3_lib1 = IN_Delay;
      }
      else
      {
        /* Transition: (':11:68') */
        /* Transition: (':11:69') */
      }
      break;
    }
  }

  /* End of Chart: 'DelayOut' (':2346:23:11') */

  /* Update for UnitDelay: 'Delay Input1' (':2346:23:12:2')
   *
   * Block description for 'Delay Input1' (':2346:23:12:2'):
   *
   *  Store in Global RAM
   */
  localDW->DelayInput1_DSTATE_px1k = rtu_DelayTime;

  /* Update for UnitDelay: 'Delay Input1' (':2346:23:13:2')
   *
   * Block description for 'Delay Input1' (':2346:23:13:2'):
   *
   *  Store in Global RAM
   */
  localDW->DelayInput1_DSTATE = rtu_In;

  /* Update for Memory: 'OutLast' (':2346:23:15') */
  localDW->OutLast_PreviousInput = *rty_Out;
}

/*
 * System initialize for atomic system:
 *    'FeedBackDelay4' (':2346')
 *    'FeedBackDelay5' (':2354')
 */
void FeedBackDelay_Init(B_FeedBackDelay_T *localB, DW_FeedBackDelay_T *localDW)
{
  /* SystemInitialize for Atomic SubSystem: 'DelayOut' (':2346:23') */
  DelayOut_Init(&localB->Out, &localDW->DelayOut_orxz);

  /* End of SystemInitialize for SubSystem: 'DelayOut' (':2346:23') */
}

/*
 * Output and update for atomic system:
 *    'FeedBackDelay4' (':2346')
 *    'FeedBackDelay5' (':2354')
 */
boolean_T FeedBackDelay(uint16_T rtu_FeedBackStartDelayTime, boolean_T
  rtu_IsFault, uint16_T rtu_FeedBackEndDelayTime, B_FeedBackDelay_T *localB,
  DW_FeedBackDelay_T *localDW)
{
  boolean_T rty_FeedBackBusStatus_0;
  uint16_T rtb_DelayTime;

  /* Switch: 'Switch2' (':2346:28') incorporates:
   *  Memory: 'Memory' (':2346:26')
   *  RelationalOperator: 'FixPt Relational Operator' (':2346:24:3')
   *  RelationalOperator: 'FixPt Relational Operator' (':2346:25:3')
   *  Switch: 'Switch1' (':2346:27')
   *  UnitDelay: 'Delay Input1' (':2346:24:2')
   *  UnitDelay: 'Delay Input1' (':2346:25:2')
   *
   * Block description for 'Delay Input1' (':2346:24:2'):
   *
   *  Store in Global RAM
   *
   * Block description for 'Delay Input1' (':2346:25:2'):
   *
   *  Store in Global RAM
   */
  if ((int16_T)rtu_IsFault > (int16_T)localDW->DelayInput1_DSTATE)
  {
    rtb_DelayTime = rtu_FeedBackStartDelayTime;
  }
  else if ((int16_T)rtu_IsFault < (int16_T)localDW->DelayInput1_DSTATE_aiff)
  {
    /* Switch: 'Switch1' (':2346:27') */
    rtb_DelayTime = rtu_FeedBackEndDelayTime;
  }
  else
  {
    rtb_DelayTime = localDW->Memory_PreviousInput;
  }

  /* End of Switch: 'Switch2' (':2346:28') */

  /* Outputs for Atomic SubSystem: 'DelayOut' (':2346:23') */
  /* DataTypeConversion: 'Data Type Conversion' (':2346:21') */
  DelayOut((int16_T)rtu_IsFault, rtb_DelayTime, &localB->Out,
           &localDW->DelayOut_orxz);

  /* End of Outputs for SubSystem: 'DelayOut' (':2346:23') */

  /* DataTypeConversion: 'Data Type Conversion1' (':2346:22') */
  rty_FeedBackBusStatus_0 = (localB->Out != 0);

  /* Update for UnitDelay: 'Delay Input1' (':2346:25:2')
   *
   * Block description for 'Delay Input1' (':2346:25:2'):
   *
   *  Store in Global RAM
   */
  localDW->DelayInput1_DSTATE = rtu_IsFault;

  /* Update for UnitDelay: 'Delay Input1' (':2346:24:2')
   *
   * Block description for 'Delay Input1' (':2346:24:2'):
   *
   *  Store in Global RAM
   */
  localDW->DelayInput1_DSTATE_aiff = rtu_IsFault;

  /* Update for Memory: 'Memory' (':2346:26') */
  localDW->Memory_PreviousInput = rtb_DelayTime;
  return rty_FeedBackBusStatus_0;
}

/* System initialize for atomic system: 'FeedBack' (':890') */
void FeedBack_Init(void)
{
  /* SystemInitialize for Atomic SubSystem: 'FeedBackDelay4' (':2346') */
  FeedBackDelay_Init(&B.FeedBackDelay4, &DW.FeedBackDelay4);

  /* End of SystemInitialize for SubSystem: 'FeedBackDelay4' (':2346') */

  /* SystemInitialize for Atomic SubSystem: 'FeedBackDelay5' (':2354') */
  FeedBackDelay_Init(&B.FeedBackDelay5, &DW.FeedBackDelay5);

  /* End of SystemInitialize for SubSystem: 'FeedBackDelay5' (':2354') */
}

/* Output and update for atomic system: 'FeedBack' (':890') */
void FeedBack(void)
{
  boolean_T Switch_kva1_tmp;
  boolean_T rtb_DataTypeConversion1;
  boolean_T rtb_DataTypeConversion1_iufm;
  boolean_T rtb_LogicalOperator3;
  boolean_T rtb_LogicalOperator3_ew35;
  boolean_T rtb_LogicalOperator3_j3fr;

  /* Outputs for Atomic SubSystem: 'FeedBackDelay4' (':2346') */

  /* Constant: 'Constant2' (':2351') incorporates:
   *  Constant: 'Constant1' (':2350')
   *  Constant: 'Constant' (':2347:3')
   *  Outport: 'VoltageStatus' (':2265')
   *  RelationalOperator: 'Compare' (':2347:2')
   */
  rtb_DataTypeConversion1_iufm = FeedBackDelay(0U, ((int16_T)Y.VoltageStatus !=
    0), 0U, &B.FeedBackDelay4, &DW.FeedBackDelay4);

  /* End of Outputs for SubSystem: 'FeedBackDelay4' (':2346') */

  /* Outputs for Atomic SubSystem: 'FeedBackDelay5' (':2354') */

  /* Constant: 'Constant4' (':2355') incorporates:
   *  Constant: 'Constant5' (':2356')
   *  Constant: 'Constant' (':2353:3')
   *  Outport: 'AmbTStatus' (':2266')
   *  RelationalOperator: 'Compare' (':2353:2')
   */
  rtb_DataTypeConversion1 = FeedBackDelay(0U, ((int16_T)Y.AmbTStatus > 0), 0U,
    &B.FeedBackDelay5, &DW.FeedBackDelay5);

  /* End of Outputs for SubSystem: 'FeedBackDelay5' (':2354') */

  /* Logic: 'Logical Operator3' (':3067') incorporates:
   *  Constant: 'Constant' (':3063:3')
   *  Inport: 'IsMotorShort' (':1826')
   *  Logic: 'Logical Operator1' (':3066')
   *  Memory: 'FeedBackEnLast' (':3064')
   *  Outport: 'ShortCnt' (':2584')
   *  RelationalOperator: 'Compare' (':3063:2')
   */
  rtb_LogicalOperator3 = ((U.IsMotorShort && DW.FeedBackEnLast_PreviousInput) ||
    ((int16_T)Y.ShortCnt >= 15));

  /* Logic: 'Logical Operator3' (':3077') incorporates:
   *  Constant: 'Constant' (':3073:3')
   *  Inport: 'IsMotorOpenLoad' (':1828')
   *  Logic: 'Logical Operator1' (':3076')
   *  Memory: 'FeedBackEnLast' (':3074')
   *  Outport: 'OpenCnt' (':2585')
   *  RelationalOperator: 'Compare' (':3073:2')
   */
  rtb_LogicalOperator3_ew35 = ((U.IsMotorOpenLoad &&
    DW.FeedBackEnLast_PreviousInp_nnxg) || ((int16_T)Y.OpenCnt >= 15));

  /* Logic: 'Logical Operator3' (':3046') incorporates:
   *  Constant: 'Constant' (':3042:3')
   *  Inport: 'IsMotorLock' (':1827')
   *  Logic: 'Logical Operator1' (':3045')
   *  Memory: 'FeedBackEnLast' (':3043')
   *  Outport: 'LockCnt' (':2586')
   *  RelationalOperator: 'Compare' (':3042:2')
   */
  rtb_LogicalOperator3_j3fr = ((U.IsMotorLock &&
    DW.FeedBackEnLast_PreviousInp_by2c) || ((int16_T)Y.LockCnt >= 15));

  /* Logic: 'Logical Operator' (':3065') incorporates:
   *  Constant: 'Constant' (':2906:3')
   *  Logic: 'Logical Operator' (':3098')
   *  Logic: 'Logical Operator' (':3075')
   *  Logic: 'Logical Operator' (':3044')
   *  RelationalOperator: 'Compare' (':2906:2')
   */
  Switch_kva1_tmp = (B.PwmInTargetSpeed == 0);

  /* Switch: 'Switch' (':3124') incorporates:
   *  Inport: 'IsMotorDryRunning' (':2342')
   *  Inport: 'IsMotorLock' (':1827')
   *  Inport: 'IsMotorOpenLoad' (':1828')
   *  Inport: 'IsMotorShort' (':1826')
   *  Logic: 'Logical Operator' (':3098')
   *  Logic: 'Logical Operator1' (':3123')
   *  Logic: 'Logical Operator' (':3065')
   *  Logic: 'Logical Operator' (':3075')
   *  Logic: 'Logical Operator' (':3044')
   */
  B.Switch_kva1 = ((!rtb_DataTypeConversion1_iufm) && (!rtb_DataTypeConversion1)
                   && ((!U.IsMotorShort) || (!rtb_LogicalOperator3) ||
                       Switch_kva1_tmp) && ((!U.IsMotorOpenLoad) ||
    (!rtb_LogicalOperator3_ew35) || Switch_kva1_tmp) && ((!U.IsMotorLock) ||
    (!rtb_LogicalOperator3_j3fr) || Switch_kva1_tmp) && ((!U.IsMotorDryRunning) ||
    Switch_kva1_tmp));

  /* Update for Memory: 'FeedBackEnLast' (':3064') */
  DW.FeedBackEnLast_PreviousInput = rtb_LogicalOperator3;

  /* Update for Memory: 'FeedBackEnLast' (':3074') */
  DW.FeedBackEnLast_PreviousInp_nnxg = rtb_LogicalOperator3_ew35;

  /* Update for Memory: 'FeedBackEnLast' (':3043') */
  DW.FeedBackEnLast_PreviousInp_by2c = rtb_LogicalOperator3_j3fr;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
