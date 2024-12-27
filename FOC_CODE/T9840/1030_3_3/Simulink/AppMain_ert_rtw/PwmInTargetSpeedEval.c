/*
 * File: PwmInTargetSpeedEval.c
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

#include "PwmInTargetSpeedEval.h"

/* Include model header file for global data */
#include "AppMain.h"
#include "AppMain_private.h"

/* Named constants for Chart: ''FreqValidJudge' (':1737')' */
#define IN_Invalid                     ((uint8_T)1U)
#define IN_NO_ACTIVE_CHILD_a53j        ((uint8_T)0U)
#define IN_Valid                       ((uint8_T)2U)

/* Named constants for Chart: ''DelayOut' (':1398')' */
#define IN_Delay_gmd2                  ((uint8_T)1U)
#define IN_NO_ACTIVE_CHILD_h4t5        ((uint8_T)0U)
#define IN_Reset_m0se                  ((uint8_T)2U)

/* System initialize for action system: 'PwmInShort' (':1672') */
void PwmInShort_Init(void)
{
  /* InitializeConditions for UnitDelay: 'Delay Input1' (':1686:2')
   *
   * Block description for 'Delay Input1' (':1686:2'):
   *
   *  Store in Global RAM
   */
  DW.DelayInput1_DSTATE_mx1q = false;

  /* InitializeConditions for UnitDelay: 'Delay Input1' (':1687:2')
   *
   * Block description for 'Delay Input1' (':1687:2'):
   *
   *  Store in Global RAM
   */
  DW.DelayInput1_DSTATE_h0ze = false;
}

/* System reset for action system: 'PwmInShort' (':1672') */
void PwmInShort_Reset(void)
{
  /* InitializeConditions for UnitDelay: 'Delay Input1' (':1686:2')
   *
   * Block description for 'Delay Input1' (':1686:2'):
   *
   *  Store in Global RAM
   */
  DW.DelayInput1_DSTATE_mx1q = false;

  /* InitializeConditions for UnitDelay: 'Delay Input1' (':1687:2')
   *
   * Block description for 'Delay Input1' (':1687:2'):
   *
   *  Store in Global RAM
   */
  DW.DelayInput1_DSTATE_h0ze = false;
}

/* Output and update for action system: 'PwmInShort' (':1672') */
void PwmInShort(void)
{
  /* Merge: 'Merge1' (':1759') incorporates:
   *  Logic: 'Logical Operator3' (':1690')
   *  Outport: 'PwmInShortBat' (':3089')
   *  Outport: 'PwmInShortGND' (':3087')
   *  RelationalOperator: 'FixPt Relational Operator' (':1686:3')
   *  RelationalOperator: 'FixPt Relational Operator' (':1687:3')
   *  UnitDelay: 'Delay Input1' (':1686:2')
   *  UnitDelay: 'Delay Input1' (':1687:2')
   *
   * Block description for 'Delay Input1' (':1686:2'):
   *
   *  Store in Global RAM
   *
   * Block description for 'Delay Input1' (':1687:2'):
   *
   *  Store in Global RAM
   */
  B.Merge1 = (((int16_T)Y.PwmInShortGND > (int16_T)DW.DelayInput1_DSTATE_mx1q) ||
              ((int16_T)Y.PwmInShortBat > (int16_T)DW.DelayInput1_DSTATE_h0ze));

  /* Switch: 'Switch' (':1691') incorporates:
   *  Outport: 'PwmInShortBat' (':3089')
   */
  if (Y.PwmInShortBat)
  {
    /* Merge: 'Merge2' (':1760') incorporates:
     *  Constant: 'Duty100' (':1689')
     */
    B.Duty = 1000U;
  }
  else
  {
    /* Merge: 'Merge2' (':1760') incorporates:
     *  Constant: 'Duty0' (':1688')
     */
    B.Duty = 0U;
  }

  /* End of Switch: 'Switch' (':1691') */

  /* Merge: 'Merge' (':1748') incorporates:
   *  Constant: 'Constant' (':1694')
   *  SignalConversion generated from: 'PwmInErr' (':1693')
   */
  B.Err = true;

  /* Update for UnitDelay: 'Delay Input1' (':1686:2') incorporates:
   *  Outport: 'PwmInShortGND' (':3087')
   *
   * Block description for 'Delay Input1' (':1686:2'):
   *
   *  Store in Global RAM
   */
  DW.DelayInput1_DSTATE_mx1q = Y.PwmInShortGND;

  /* Update for UnitDelay: 'Delay Input1' (':1687:2') incorporates:
   *  Outport: 'PwmInShortBat' (':3089')
   *
   * Block description for 'Delay Input1' (':1687:2'):
   *
   *  Store in Global RAM
   */
  DW.DelayInput1_DSTATE_h0ze = Y.PwmInShortBat;
}

/* Output and update for atomic system: 'DutyBufUpdate' (':2280') */
void DutyBufUpdate(uint16_T rtu_data, uint16_T rty_buf[6])
{
  int16_T i;

  /*  # eml */
  /* MATLAB Function 'PwmInTargetSpeedEval/NormalState/PwmInSpeedCtrl/PwmInNotShort/DutyFilter/Enabled Subsystem/DutyFilter/DutyBufUpdate': (':2280:1') */
  /* (':2280:1:3') */
  /* (':2280:1:4') */
  for (i = 0; i < 5; i++)
  {
    /* (':2280:1:4') */
    /* (':2280:1:5') */
    rty_buf[(int16_T)(5 - i)] = rty_buf[(int16_T)(4 - i)];
  }

  /* (':2280:1:8') */
  rty_buf[0] = rtu_data;
}

/* Output and update for atomic system: 'BufDataSameFirstCnt' (':2285') */
void BufDataSameFirstCnt(const uint16_T rtu_buf[6], uint16_T rtu_tolerance,
  uint16_T *rty_samecnt)
{
  int16_T i;
  uint16_T b_max;
  uint16_T b_min;
  uint16_T qY;

  /* MATLAB Function 'PwmInTargetSpeedEval/NormalState/PwmInSpeedCtrl/PwmInNotShort/DutyFilter/Enabled Subsystem/DutyFilter/DutyValid/BufDataSameFirstCnt': (':2285:1') */
  if (rtu_buf[0] >= rtu_tolerance)
  {
    /* (':2285:1:2') */
    /* (':2285:1:3') */
    b_min = (uint16_T)(rtu_buf[0] - rtu_tolerance);
    if (b_min > rtu_buf[0])
    {
      b_min = 0U;
    }
  }
  else
  {
    /* (':2285:1:5') */
    b_min = 0U;
  }

  /* (':2285:1:8') */
  b_max = (uint16_T)(rtu_buf[0] + rtu_tolerance);
  if (b_max < rtu_buf[0])
  {
    b_max = MAX_uint16_T;
  }

  if (b_max > 1000U)
  {
    /* (':2285:1:9') */
    /* (':2285:1:10') */
    b_max = 1000U;
  }

  /* (':2285:1:13') */
  *rty_samecnt = 1U;

  /* (':2285:1:14') */
  for (i = 0; i < 5; i++)
  {
    /* (':2285:1:14') */
    qY = rtu_buf[(int16_T)(i + 1)];
    if ((qY >= b_min) && (qY <= b_max))
    {
      /* (':2285:1:15') */
      /* (':2285:1:16') */
      qY = (uint16_T)(*rty_samecnt + 1U);
      if ((uint16_T)(*rty_samecnt + 1U) < *rty_samecnt)
      {
        qY = MAX_uint16_T;
      }

      *rty_samecnt = qY;
    }
  }
}

/* System initialize for enable system: 'DutyFilter' (':1703') */
void DutyFilter_Init(B_DutyFilter_T *localB, DW_DutyFilter_T *localDW)
{
  int16_T i;

  /* InitializeConditions for Memory: 'DutyBuf' (':2275') */
  for (i = 0; i < 6; i++)
  {
    localDW->DutyBuf_PreviousInput[i] = 2000U;
  }

  /* End of InitializeConditions for Memory: 'DutyBuf' (':2275') */

  /* SystemInitialize for Enabled SubSystem: 'Enabled Subsystem' (':2269') */
  /* SystemInitialize for Merge: 'Merge1' (':2299') */
  localB->Merge1 = 0U;

  /* End of SystemInitialize for SubSystem: 'Enabled Subsystem' (':2269') */
}

/* System reset for enable system: 'DutyFilter' (':1703') */
void DutyFilter_Reset(DW_DutyFilter_T *localDW)
{
  int16_T i;

  /* InitializeConditions for Memory: 'DutyBuf' (':2275') */
  for (i = 0; i < 6; i++)
  {
    localDW->DutyBuf_PreviousInput[i] = 2000U;
  }

  /* End of InitializeConditions for Memory: 'DutyBuf' (':2275') */
}

/* Disable for enable system: 'DutyFilter' (':1703') */
void DutyFilter_Disable(DW_DutyFilter_T *localDW)
{
  localDW->DutyFilter_MODE = false;
}

/* Output and update for enable system: 'DutyFilter' (':1703') */
void DutyFilter(boolean_T rtu_Enable, uint16_T rtu_Duty, uint16_T rtu_DutyLast,
                boolean_T rtu_IsPwmDutyUpdated, uint16_T *rty_FilteredDuty,
                boolean_T *rty_Valid, B_DutyFilter_T *localB, DW_DutyFilter_T
                *localDW)
{
  int16_T i;
  uint16_T rtb_samecnt;
  boolean_T rtb_RelationalOperator1[6];
  boolean_T tmp;

  /* Outputs for Enabled SubSystem: 'DutyFilter' (':1703') incorporates:
   *  EnablePort: 'Enable' (':1706')
   */
  if (rtu_Enable)
  {
    if (!localDW->DutyFilter_MODE)
    {
      DutyFilter_Reset(localDW);
      localDW->DutyFilter_MODE = true;
    }

    /* Outputs for Enabled SubSystem: 'Enabled Subsystem' (':2269') incorporates:
     *  EnablePort: 'Enable' (':2271')
     */
    if (rtu_IsPwmDutyUpdated)
    {
      /* MATLAB Function: 'DutyBufUpdate' (':2280') incorporates:
       *  Memory: 'DutyBuf' (':2275')
       */
      for (i = 0; i < 6; i++)
      {
        localB->buf[i] = localDW->DutyBuf_PreviousInput[i];
      }

      DutyBufUpdate(rtu_Duty, localB->buf);

      /* End of MATLAB Function: 'DutyBufUpdate' (':2280') */

      /* RelationalOperator: 'Relational Operator1' (':2300') incorporates:
       *  Constant: 'DutyMax' (':2292')
       */
      for (i = 0; i < 6; i++)
      {
        rtb_RelationalOperator1[i] = (localB->buf[i] <= 1000U);
      }

      /* End of RelationalOperator: 'Relational Operator1' (':2300') */

      /* Logic: 'Logical Operator' (':2298') */
      tmp = rtb_RelationalOperator1[0];
      for (i = 0; i < 5; i++)
      {
        tmp = (tmp && rtb_RelationalOperator1[(int16_T)(i + 1)]);
      }

      *rty_Valid = tmp;

      /* End of Logic: 'Logical Operator' (':2298') */

      /* If: 'If' (':2297') */
      if (!*rty_Valid)
      {
        /* Outputs for IfAction SubSystem: 'DutyInvalid' (':2293') incorporates:
         *  ActionPort: 'Action Port' (':2295')
         */
        /* Merge: 'Merge1' (':2299') incorporates:
         *  Inport: 'DutyLast' (':2294')
         */
        localB->Merge1 = rtu_DutyLast;

        /* End of Outputs for SubSystem: 'DutyInvalid' (':2293') */
      }
      else
      {
        /* Outputs for IfAction SubSystem: 'DutyValid' (':2281') incorporates:
         *  ActionPort: 'Action Port' (':2284')
         */
        /* MATLAB Function: 'BufDataSameFirstCnt' (':2285') incorporates:
         *  Constant: 'DutyTolerance' (':2287')
         */
        BufDataSameFirstCnt(localB->buf, 20U, &rtb_samecnt);

        /* Switch: 'Switch' (':2290') incorporates:
         *  Constant: 'DutySameCntTHR' (':2286')
         *  RelationalOperator: 'Relational Operator' (':2288')
         */
        if (rtb_samecnt >= 4U)
        {
          /* Merge: 'Merge1' (':2299') incorporates:
           *  SignalConversion generated from: 'FilteredDuty' (':2291')
           */
          localB->Merge1 = localB->buf[0];
        }
        else
        {
          /* Merge: 'Merge1' (':2299') incorporates:
           *  SignalConversion generated from: 'FilteredDuty' (':2291')
           */
          localB->Merge1 = rtu_DutyLast;
        }

        /* End of Switch: 'Switch' (':2290') */
        /* End of Outputs for SubSystem: 'DutyValid' (':2281') */
      }

      /* End of If: 'If' (':2297') */
    }

    /* End of Outputs for SubSystem: 'Enabled Subsystem' (':2269') */

    /* Switch: 'Switch' (':3091') */
    if (rtu_IsPwmDutyUpdated)
    {
      *rty_FilteredDuty = localB->Merge1;
    }
    else
    {
      *rty_FilteredDuty = rtu_DutyLast;
    }

    /* End of Switch: 'Switch' (':3091') */

    /* Update for Memory: 'DutyBuf' (':2275') */
    for (i = 0; i < 6; i++)
    {
      localDW->DutyBuf_PreviousInput[i] = localB->buf[i];
    }

    /* End of Update for Memory: 'DutyBuf' (':2275') */
  }
  else if (localDW->DutyFilter_MODE)
  {
    DutyFilter_Disable(localDW);
  }

  /* End of Outputs for SubSystem: 'DutyFilter' (':1703') */
}

/* System initialize for atomic system: 'FreqValidJudge' (':1734') */
void FreqValidJudge_Init(boolean_T *rty_Valid, DW_FreqValidJudge_T *localDW)
{
  /* SystemInitialize for Chart: 'FreqValidJudge' (':1737') */
  localDW->is_active_c12_AppMain = 0U;
  localDW->is_c12_AppMain = IN_NO_ACTIVE_CHILD_a53j;
  localDW->ValidCnt = 0U;
  localDW->InvalidCnt = 0U;
  *rty_Valid = false;
}

/* System reset for atomic system: 'FreqValidJudge' (':1734') */
void FreqValidJudge_Reset(boolean_T *rty_Valid, DW_FreqValidJudge_T *localDW)
{
  /* SystemReset for Chart: 'FreqValidJudge' (':1737') */
  localDW->is_active_c12_AppMain = 0U;
  localDW->is_c12_AppMain = IN_NO_ACTIVE_CHILD_a53j;
  localDW->ValidCnt = 0U;
  localDW->InvalidCnt = 0U;
  *rty_Valid = false;
}

/* Output and update for atomic system: 'FreqValidJudge' (':1734') */
boolean_T FreqValidJudge(uint16_T rtu_Freq, DW_FreqValidJudge_T *localDW)
{
  boolean_T rty_Valid_0;
  uint16_T qY;

  /* Chart: 'FreqValidJudge' (':1737') incorporates:
   *  Constant: 'FreqMax' (':2210')
   *  Constant: 'FreqMin' (':2209')
   *  Constant: 'FreqTolerance' (':2211')
   *  Constant: 'FreqValidJudgeFilterTime' (':2212')
   */
  /* Gateway: PwmInTargetSpeedEval/NormalState/PwmInSpeedCtrl/PwmInNotShort/FreqValidJudge/FreqValidJudge */
  /* During: PwmInTargetSpeedEval/NormalState/PwmInSpeedCtrl/PwmInNotShort/FreqValidJudge/FreqValidJudge */
  if ((uint16_T)localDW->is_active_c12_AppMain == 0U)
  {
    /* Entry: PwmInTargetSpeedEval/NormalState/PwmInSpeedCtrl/PwmInNotShort/FreqValidJudge/FreqValidJudge */
    localDW->is_active_c12_AppMain = 1U;

    /* Entry Internal: PwmInTargetSpeedEval/NormalState/PwmInSpeedCtrl/PwmInNotShort/FreqValidJudge/FreqValidJudge */
    /* Transition: (':1737:7') */
    qY = (uint16_T)(rtu_Freq + 10U);
    if ((uint16_T)(rtu_Freq + 10U) < rtu_Freq)
    {
      qY = MAX_uint16_T;
    }

    if ((rtu_Freq <= 10010U) && (qY >= 500U))
    {
      /* Transition: (':1737:55') */
      localDW->is_c12_AppMain = IN_Valid;

      /* Entry 'Valid': (':1737:8') */
      rty_Valid_0 = true;
      localDW->InvalidCnt = 1U;
    }
    else
    {
      /* Transition: (':1737:57') */
      /* Transition: (':1737:58') */
      localDW->is_c12_AppMain = IN_Invalid;

      /* Entry 'Invalid': (':1737:36') */
      rty_Valid_0 = false;
      localDW->ValidCnt = 1U;
    }
  }
  else if (localDW->is_c12_AppMain == IN_Invalid)
  {
    /* During 'Invalid': (':1737:36') */
    if (localDW->ValidCnt >= 20U)
    {
      /* Transition: (':1737:29') */
      localDW->is_c12_AppMain = IN_Valid;

      /* Entry 'Valid': (':1737:8') */
      rty_Valid_0 = true;
      localDW->InvalidCnt = 1U;
    }
    else
    {
      /* Transition: (':1737:42') */
      rty_Valid_0 = false;
      if ((rtu_Freq <= 10000U) && (rtu_Freq >= 500U))
      {
        /* Transition: (':1737:43') */
        qY = (uint16_T)(localDW->ValidCnt + 1U);
        if ((uint16_T)(localDW->ValidCnt + 1U) < localDW->ValidCnt)
        {
          qY = MAX_uint16_T;
        }

        localDW->ValidCnt = qY;
      }
      else
      {
        /* Transition: (':1737:45') */
        localDW->ValidCnt = 1U;
      }
    }

    /* During 'Valid': (':1737:8') */
  }
  else if (localDW->InvalidCnt >= 20U)
  {
    /* Transition: (':1737:28') */
    localDW->is_c12_AppMain = IN_Invalid;

    /* Entry 'Invalid': (':1737:36') */
    rty_Valid_0 = false;
    localDW->ValidCnt = 1U;
  }
  else
  {
    /* Transition: (':1737:10') */
    rty_Valid_0 = true;
    qY = (uint16_T)(rtu_Freq + 10U);
    if ((uint16_T)(rtu_Freq + 10U) < rtu_Freq)
    {
      qY = MAX_uint16_T;
    }

    if ((rtu_Freq > 10010U) || (qY < 500U))
    {
      /* Transition: (':1737:12') */
      qY = (uint16_T)(localDW->InvalidCnt + 1U);
      if ((uint16_T)(localDW->InvalidCnt + 1U) < localDW->InvalidCnt)
      {
        qY = MAX_uint16_T;
      }

      localDW->InvalidCnt = qY;
    }
    else
    {
      /* Transition: (':1737:33') */
      localDW->InvalidCnt = 1U;
    }
  }

  /* End of Chart: 'FreqValidJudge' (':1737') */
  return rty_Valid_0;
}

/* System initialize for action system: 'PwmInNotShort' (':1678') */
void PwmInNotShort_Init(void)
{
  boolean_T rtb_Valid;

  /* InitializeConditions for UnitDelay: 'Delay Input1' (':2453:2')
   *
   * Block description for 'Delay Input1' (':2453:2'):
   *
   *  Store in Global RAM
   */
  DW.DelayInput1_DSTATE = false;

  /* InitializeConditions for UnitDelay: 'Delay Input1' (':3092:2')
   *
   * Block description for 'Delay Input1' (':3092:2'):
   *
   *  Store in Global RAM
   */
  DW.DelayInput1_DSTATE_gs5l = false;

  /* SystemInitialize for Atomic SubSystem: 'FreqValidJudge' (':1734') */
  FreqValidJudge_Init(&rtb_Valid, &DW.FreqValidJudge_llbg);

  /* End of SystemInitialize for SubSystem: 'FreqValidJudge' (':1734') */

  /* SystemInitialize for Enabled SubSystem: 'DutyFilter' (':1703') */
  DutyFilter_Init(&B.DutyFilter_h2ru, &DW.DutyFilter_h2ru);

  /* End of SystemInitialize for SubSystem: 'DutyFilter' (':1703') */
}

/* System reset for action system: 'PwmInNotShort' (':1678') */
void PwmInNotShort_Reset(void)
{
  boolean_T rtb_Valid;

  /* InitializeConditions for UnitDelay: 'Delay Input1' (':2453:2')
   *
   * Block description for 'Delay Input1' (':2453:2'):
   *
   *  Store in Global RAM
   */
  DW.DelayInput1_DSTATE = false;

  /* InitializeConditions for UnitDelay: 'Delay Input1' (':3092:2')
   *
   * Block description for 'Delay Input1' (':3092:2'):
   *
   *  Store in Global RAM
   */
  DW.DelayInput1_DSTATE_gs5l = false;

  /* SystemReset for Atomic SubSystem: 'FreqValidJudge' (':1734') */
  FreqValidJudge_Reset(&rtb_Valid, &DW.FreqValidJudge_llbg);

  /* End of SystemReset for SubSystem: 'FreqValidJudge' (':1734') */
}

/* Disable for action system: 'PwmInNotShort' (':1678') */
void PwmInNotShort_Disable(void)
{
  /* Disable for Enabled SubSystem: 'DutyFilter' (':1703') */
  if (DW.DutyFilter_h2ru.DutyFilter_MODE)
  {
    DutyFilter_Disable(&DW.DutyFilter_h2ru);
  }

  /* End of Disable for SubSystem: 'DutyFilter' (':1703') */
}

/* Output and update for action system: 'PwmInNotShort' (':1678') */
void PwmInNotShort(void)
{
  boolean_T rtb_Valid;

  /* Outputs for Atomic SubSystem: 'FreqValidJudge' (':1734') */
  rtb_Valid = FreqValidJudge(B.Freq, &DW.FreqValidJudge_llbg);

  /* End of Outputs for SubSystem: 'FreqValidJudge' (':1734') */

  /* Outputs for Enabled SubSystem: 'DutyFilter' (':1703') */
  /* SignalConversion generated from: 'Enable' (':1706') */
  DutyFilter(rtb_Valid, B.HighDuty, B.DutyLast, B.Compare, &B.Switch,
             &B.DutyValid, &B.DutyFilter_h2ru, &DW.DutyFilter_h2ru);

  /* End of Outputs for SubSystem: 'DutyFilter' (':1703') */

  /* SignalConversion generated from: 'DutyUpdated' (':1822') incorporates:
   *  Logic: 'Logical Operator' (':2195')
   *  RelationalOperator: 'Relational Operator' (':1821')
   *  RelationalOperator: 'FixPt Relational Operator' (':2453:3')
   *  RelationalOperator: 'FixPt Relational Operator' (':3092:3')
   *  UnitDelay: 'Delay Input1' (':2453:2')
   *  UnitDelay: 'Delay Input1' (':3092:2')
   *
   * Block description for 'Delay Input1' (':2453:2'):
   *
   *  Store in Global RAM
   *
   * Block description for 'Delay Input1' (':3092:2'):
   *
   *  Store in Global RAM
   */
  B.Merge1 = (((int16_T)rtb_Valid > (int16_T)DW.DelayInput1_DSTATE_gs5l) ||
              ((int16_T)B.DutyValid > (int16_T)DW.DelayInput1_DSTATE) ||
              (B.Switch != B.DutyLast));

  /* Switch: 'Switch' (':3181') */
  if (rtb_Valid)
  {
    B.Duty = B.Switch;
  }
  else
  {
    B.Duty = B.DutyLast;
  }

  /* End of Switch: 'Switch' (':3181') */

  /* Logic: 'Logical Operator2' (':1740') */
  B.Err = !rtb_Valid;

  /* Update for UnitDelay: 'Delay Input1' (':2453:2')
   *
   * Block description for 'Delay Input1' (':2453:2'):
   *
   *  Store in Global RAM
   */
  DW.DelayInput1_DSTATE = B.DutyValid;

  /* Update for UnitDelay: 'Delay Input1' (':3092:2')
   *
   * Block description for 'Delay Input1' (':3092:2'):
   *
   *  Store in Global RAM
   */
  DW.DelayInput1_DSTATE_gs5l = rtb_Valid;
}

/* Output and update for atomic system: 'SpeedCurve' (':1609') */
void SpeedCurve(int32_T rtu_MaxSpeed, int16_T rtu_MinSpeed, uint16_T rtu_Duty,
                uint16_T rtu_SectorLast, int16_T *rty_Speed, uint16_T *rty_Delay,
                boolean_T *rty_Reset, uint16_T *rty_SectorNew)
{
  int32_T tmp;
  uint32_T qY;
  uint32_T z;
  int16_T tmp_0;

  /*  # eml */
  /* MATLAB Function 'PwmInTargetSpeedEval/NormalState/PwmInSpeedCtrl/DutySpeedCtrl/SpeedAndOutDelayEval/SpeedCurve': (':1609:1') */
  if (rtu_Duty < 100U)
  {
    /* (':1609:1:3') */
    /* (':1609:1:4') */
    *rty_Speed = 0;
  }
  else if (rtu_Duty < 550U)
  {
    /* (':1609:1:5') */
    /* (':1609:1:6') */
    *rty_Speed = rtu_MinSpeed;
  }
  else if (rtu_Duty <= 900U)
  {
    /* (':1609:1:7') */
    /* (':1609:1:8') */
    tmp = rtu_MaxSpeed;
    if (rtu_MaxSpeed < 0L)
    {
      tmp = 0L;
    }

    tmp_0 = rtu_MinSpeed;
    if (rtu_MinSpeed < 0)
    {
      tmp_0 = 0;
    }

    qY = (uint32_T)((uint32_T)tmp - (uint32_T)tmp_0);
    if (qY > (uint32_T)tmp)
    {
      qY = 0UL;
    }

    qY = mul_u32_sat((uint32_T)(int16_T)((int16_T)rtu_Duty - 550), qY);
    z = (uint32_T)(qY / 350UL);
    qY -= (uint32_T)(z * 350UL);
    if ((qY > 0UL) && (qY >= 175UL))
    {
      z++;
    }

    tmp_0 = rtu_MinSpeed;
    if (rtu_MinSpeed < 0)
    {
      tmp_0 = 0;
    }

    qY = (uint32_T)(z + (uint32_T)tmp_0);
    if ((int32_T)qY > 32767L)
    {
      qY = 32767UL;
    }

    *rty_Speed = (int16_T)qY;
    if ((int32_T)(int16_T)qY > rtu_MaxSpeed)
    {
      /* (':1609:1:12') */
      /* (':1609:1:13') */
      tmp = rtu_MaxSpeed;
      if (rtu_MaxSpeed < -32768L)
      {
        tmp = -32768L;
      }

      *rty_Speed = (int16_T)tmp;
    }
  }
  else
  {
    /* (':1609:1:16') */
    tmp = rtu_MaxSpeed;
    if (rtu_MaxSpeed > 32767L)
    {
      tmp = 32767L;
    }
    else if (rtu_MaxSpeed < -32768L)
    {
      tmp = -32768L;
    }

    *rty_Speed = (int16_T)tmp;
  }

  /* (':1609:1:19') */
  *rty_Delay = 0U;

  /* (':1609:1:20') */
  *rty_Reset = true;

  /* (':1609:1:21') */
  *rty_SectorNew = rtu_SectorLast;
}

/* System initialize for atomic system: 'SpeedDelayOut' (':1394') */
void SpeedDelayOut_Init(int16_T *rty_Out, DW_SpeedDelayOut_T *localDW)
{
  /* SystemInitialize for Chart: 'DelayOut' (':1398') */
  localDW->is_active_c13_AppMain = 0U;
  localDW->is_c13_AppMain = IN_NO_ACTIVE_CHILD_h4t5;
  localDW->DelayCnt = 0U;
  *rty_Out = 0;
}

/* Output and update for atomic system: 'SpeedDelayOut' (':1394') */
void SpeedDelayOut(int16_T rtu_In, uint16_T rtu_DelayTime, boolean_T rtu_Rst,
                   int16_T *rty_Out, DW_SpeedDelayOut_T *localDW)
{
  uint16_T qY;

  /* Chart: 'DelayOut' (':1398') incorporates:
   *  Memory: 'OutLast' (':1399')
   */
  /* Gateway: PwmInTargetSpeedEval/NormalState/PwmInSpeedCtrl/SpeedDelayOut/DelayOut */
  /* During: PwmInTargetSpeedEval/NormalState/PwmInSpeedCtrl/SpeedDelayOut/DelayOut */
  if ((uint16_T)localDW->is_active_c13_AppMain == 0U)
  {
    /* Entry: PwmInTargetSpeedEval/NormalState/PwmInSpeedCtrl/SpeedDelayOut/DelayOut */
    localDW->is_active_c13_AppMain = 1U;

    /* Entry Internal: PwmInTargetSpeedEval/NormalState/PwmInSpeedCtrl/SpeedDelayOut/DelayOut */
    /* Transition: (':1398:27') */
    localDW->is_c13_AppMain = IN_Reset_m0se;

    /* Entry 'Reset': (':1398:38') */
    localDW->DelayCnt = 2U;
    *rty_Out = localDW->OutLast_PreviousInput;
  }
  else if (localDW->is_c13_AppMain == IN_Delay_gmd2)
  {
    /* During 'Delay': (':1398:28') */
    if (rtu_Rst)
    {
      /* Transition: (':1398:40') */
      localDW->is_c13_AppMain = IN_Reset_m0se;

      /* Entry 'Reset': (':1398:38') */
      localDW->DelayCnt = 2U;
      *rty_Out = localDW->OutLast_PreviousInput;

      /* Transition: (':1398:33') */
    }
    else if (localDW->DelayCnt < rtu_DelayTime)
    {
      /* Transition: (':1398:34') */
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
      /* Transition: (':1398:35') */
      /* Transition: (':1398:37') */
      *rty_Out = rtu_In;

      /* Transition: (':1398:36') */
    }

    /* During 'Reset': (':1398:38') */
  }
  else if (!rtu_Rst)
  {
    /* Transition: (':1398:39') */
    localDW->is_c13_AppMain = IN_Delay_gmd2;
  }

  /* End of Chart: 'DelayOut' (':1398') */

  /* Update for Memory: 'OutLast' (':1399') */
  localDW->OutLast_PreviousInput = *rty_Out;
}

/* System initialize for atomic system: 'PwmInSpeedCtrl' (':977') */
void PwmInSpeedCtrl_Init(void)
{
  /* Start for If: 'If' (':1676') */
  DW.If_ActiveSubsystem_aekd = -1;

  /* Start for If: 'If1' (':1743') */
  DW.If1_ActiveSubsystem = -1;

  /* InitializeConditions for Memory: 'DutyLast' (':1800') */
  DW.DutyLast_PreviousInput = 50U;

  /* SystemInitialize for IfAction SubSystem: 'PwmInShort' (':1672') */
  PwmInShort_Init();

  /* End of SystemInitialize for SubSystem: 'PwmInShort' (':1672') */

  /* SystemInitialize for IfAction SubSystem: 'PwmInNotShort' (':1678') */
  PwmInNotShort_Init();

  /* End of SystemInitialize for SubSystem: 'PwmInNotShort' (':1678') */

  /* SystemInitialize for IfAction SubSystem: 'DutySpeedCtrl' (':1752') */
  /* InitializeConditions for Memory: 'LastState' (':1608') */
  DW.LastState_PreviousInput = 0U;

  /* End of SystemInitialize for SubSystem: 'DutySpeedCtrl' (':1752') */

  /* SystemInitialize for Atomic SubSystem: 'SpeedDelayOut' (':1394') */
  SpeedDelayOut_Init(&B.Out, &DW.SpeedDelayOut_awf2);

  /* End of SystemInitialize for SubSystem: 'SpeedDelayOut' (':1394') */
}

/* Disable for atomic system: 'PwmInSpeedCtrl' (':977') */
void PwmInSpeedCtrl_Disable(void)
{
  /* Disable for If: 'If' (':1676') */
  if ((int16_T)DW.If_ActiveSubsystem_aekd == 1)
  {
    PwmInNotShort_Disable();
  }

  DW.If_ActiveSubsystem_aekd = -1;

  /* End of Disable for If: 'If' (':1676') */

  /* Disable for If: 'If1' (':1743') */
  DW.If1_ActiveSubsystem = -1;
}

/* Output and update for atomic system: 'PwmInSpeedCtrl' (':977') */
void PwmInSpeedCtrl(void)
{
  int16_T rtb_Speed;
  uint16_T rtb_Delay_cskn;
  int8_T rtAction;
  int8_T rtPrevAction;
  boolean_T rtb_Rst;

  /* Memory: 'DutyLast' (':1800') */
  B.DutyLast = DW.DutyLast_PreviousInput;

  /* If: 'If' (':1676') incorporates:
   *  Logic: 'Logical Operator1' (':1685')
   *  Outport: 'PwmInShortBat' (':3089')
   *  Outport: 'PwmInShortGND' (':3087')
   */
  rtPrevAction = DW.If_ActiveSubsystem_aekd;
  rtAction = (int8_T)((!Y.PwmInShortGND) && (!Y.PwmInShortBat));
  DW.If_ActiveSubsystem_aekd = rtAction;
  if (((int16_T)rtPrevAction != (int16_T)rtAction) && ((int16_T)rtPrevAction ==
       1))
  {
    PwmInNotShort_Disable();
  }

  if ((int16_T)rtAction == 0)
  {
    if ((int16_T)rtAction != (int16_T)rtPrevAction)
    {
      /* SystemReset for IfAction SubSystem: 'PwmInShort' (':1672') incorporates:
       *  ActionPort: 'Action Port' (':1674')
       */
      /* SystemReset for If: 'If' (':1676') */
      PwmInShort_Reset();

      /* End of SystemReset for SubSystem: 'PwmInShort' (':1672') */
    }

    /* Outputs for IfAction SubSystem: 'PwmInShort' (':1672') incorporates:
     *  ActionPort: 'Action Port' (':1674')
     */
    PwmInShort();

    /* End of Outputs for SubSystem: 'PwmInShort' (':1672') */
  }
  else
  {
    if ((int16_T)rtAction != (int16_T)rtPrevAction)
    {
      /* SystemReset for IfAction SubSystem: 'PwmInNotShort' (':1678') incorporates:
       *  ActionPort: 'Action Port' (':1680')
       */
      /* SystemReset for If: 'If' (':1676') */
      PwmInNotShort_Reset();

      /* End of SystemReset for SubSystem: 'PwmInNotShort' (':1678') */
    }

    /* Outputs for IfAction SubSystem: 'PwmInNotShort' (':1678') incorporates:
     *  ActionPort: 'Action Port' (':1680')
     */
    PwmInNotShort();

    /* End of Outputs for SubSystem: 'PwmInNotShort' (':1678') */
  }

  /* End of If: 'If' (':1676') */

  /* DataTypeConversion: 'Data Type Conversion1' (':1791') */
  B.PwmInErr = B.Err;

  /* If: 'If1' (':1743') incorporates:
   *  Inport: 'FilteredVoltage' (':2253')
   *  Inport: 'LastDelay' (':1788')
   *  Inport: 'LastSpeed' (':1775')
   *  Logic: 'Logical Operator' (':2263')
   *  Memory: 'FltVoltageLast' (':2261')
   *  Memory: 'LastDelay' (':1773')
   *  Memory: 'LastSpeed' (':1772')
   *  RelationalOperator: 'Relational Operator' (':2262')
   */
  rtPrevAction = DW.If1_ActiveSubsystem;
  if (B.PwmInErr)
  {
    rtAction = 0;
  }
  else if (B.Merge1 || (U.FilteredVoltage != DW.FltVoltageLast_PreviousInput))
  {
    rtAction = 1;
  }
  else
  {
    rtAction = 2;
  }

  DW.If1_ActiveSubsystem = rtAction;
  switch (rtAction)
  {
   case 0:
    /* Outputs for IfAction SubSystem: 'ErrSpeedCtrl' (':1744') incorporates:
     *  ActionPort: 'Action Port' (':1746')
     */
    /* Switch: 'Switch2' (':2598') incorporates:
     *  Constant: 'Constant1' (':2595')
     *  Constant: 'Constant6' (':2596')
     *  Outport: 'PwmInShortGND' (':3087')
     *  Switch: 'Switch3' (':2599')
     */
    if (Y.PwmInShortGND)
    {
      rtb_Delay_cskn = 0U;
    }
    else
    {
      rtb_Delay_cskn = 0U;
    }

    /* End of Switch: 'Switch2' (':2598') */

    /* Switch: 'Switch' (':2590') incorporates:
     *  Constant: 'Constant3' (':2591')
     *  Outport: 'PwmInShortBat' (':3089')
     *  Outport: 'PwmInShortGND' (':3087')
     *  Switch: 'Switch1' (':2592')
     */
    if (Y.PwmInShortGND)
    {
      rtb_Speed = 0;
    }
    else if (Y.PwmInShortBat)
    {
      /* Outputs for Atomic SubSystem: 'MaxSpeedLimtedByVoltage' (':3173') */
      /* Switch: 'Switch1' (':2592') incorporates:
       *  Constant: 'Constant4' (':3171')
       *  DataTypeConversion: 'Data Type Conversion' (':3180')
       *  Inport: 'FilteredVoltage' (':2253')
       *  Lookup_n-D: '1-D Lookup Table' (':3175')
       *  Product: 'Divide' (':3178')
       */
      rtb_Speed = (int16_T)(int32_T)asr_s32((int32_T)(625L * (int32_T)
        look1_is16lu32n16Ds32_binlcs(U.FilteredVoltage, ConstP.pooled7,
        ConstP.pooled6, 2UL)), 5U);

      /* End of Outputs for SubSystem: 'MaxSpeedLimtedByVoltage' (':3173') */
    }
    else
    {
      /* Switch: 'Switch1' (':2592') incorporates:
       *  Memory: 'LastSpeed' (':1772')
       */
      rtb_Speed = DW.LastSpeed_PreviousInput;
    }

    /* End of Switch: 'Switch' (':2590') */

    /* SignalConversion generated from: 'Rst' (':2605') incorporates:
     *  Constant: 'Constant' (':3136')
     */
    rtb_Rst = false;

    /* End of Outputs for SubSystem: 'ErrSpeedCtrl' (':1744') */
    break;

   case 1:
    if ((int16_T)rtAction != (int16_T)rtPrevAction)
    {
      /* InitializeConditions for IfAction SubSystem: 'DutySpeedCtrl' (':1752') incorporates:
       *  ActionPort: 'Action Port' (':1755')
       */
      /* InitializeConditions for If: 'If1' (':1743') incorporates:
       *  Memory: 'LastState' (':1608')
       */
      DW.LastState_PreviousInput = 0U;

      /* End of InitializeConditions for SubSystem: 'DutySpeedCtrl' (':1752') */
    }

    /* Outputs for IfAction SubSystem: 'DutySpeedCtrl' (':1752') incorporates:
     *  ActionPort: 'Action Port' (':1755')
     */
    /* Outputs for Atomic SubSystem: 'MaxSpeedLimtedByVoltage' (':2246') */
    /* Update for Memory: 'LastState' (':1608') incorporates:
     *  Constant: 'Constant' (':2264')
     *  Constant: 'Constant' (':2250')
     *  Inport: 'FilteredVoltage' (':2253')
     *  Lookup_n-D: '1-D Lookup Table' (':2249')
     *  MATLAB Function: 'SpeedCurve' (':1609')
     *  Product: 'Divide' (':2251')
     *  SignalConversion generated from: 'Delay' (':1757')
     *  SignalConversion generated from: 'Rst' (':1758')
     *  SignalConversion generated from: 'Speed' (':1756')
     */
    SpeedCurve((int32_T)asr_s32((int32_T)(625L * (int32_T)
      look1_is16lu32n16Ds32_binlcs(U.FilteredVoltage, ConstP.pooled7,
      ConstP.pooled6, 2UL)), 5U), 3100, B.Duty, DW.LastState_PreviousInput,
               &rtb_Speed, &rtb_Delay_cskn, &rtb_Rst,
               &DW.LastState_PreviousInput);

    /* End of Outputs for SubSystem: 'MaxSpeedLimtedByVoltage' (':2246') */
    /* End of Outputs for SubSystem: 'DutySpeedCtrl' (':1752') */
    break;

   default:
    /* Outputs for IfAction SubSystem: 'KeepLastState' (':1774') incorporates:
     *  ActionPort: 'Action Port' (':1776')
     */
    /* SignalConversion generated from: 'Rst' (':1787') incorporates:
     *  Constant: 'Constant' (':1789')
     */
    rtb_Rst = false;
    rtb_Speed = DW.LastSpeed_PreviousInput;
    rtb_Delay_cskn = DW.LastDelay_PreviousInput;

    /* End of Outputs for SubSystem: 'KeepLastState' (':1774') */
    break;
  }

  /* End of If: 'If1' (':1743') */

  /* Outputs for Atomic SubSystem: 'SpeedDelayOut' (':1394') */
  SpeedDelayOut(rtb_Speed, rtb_Delay_cskn, rtb_Rst, &B.Out,
                &DW.SpeedDelayOut_awf2);

  /* End of Outputs for SubSystem: 'SpeedDelayOut' (':1394') */

  /* Update for Memory: 'DutyLast' (':1800') */
  DW.DutyLast_PreviousInput = B.Duty;

  /* Update for Memory: 'FltVoltageLast' (':2261') incorporates:
   *  Inport: 'FilteredVoltage' (':2253')
   */
  DW.FltVoltageLast_PreviousInput = U.FilteredVoltage;

  /* Update for Memory: 'LastSpeed' (':1772') */
  DW.LastSpeed_PreviousInput = rtb_Speed;

  /* Update for Memory: 'LastDelay' (':1773') */
  DW.LastDelay_PreviousInput = rtb_Delay_cskn;
}

/* System initialize for atomic system: 'PwmInTargetSpeedEval' (':961') */
void PwmInTargetSpeedEval_Init(void)
{
  /* Start for If: 'If' (':1650') */
  DW.If_ActiveSubsystem = -1;

  /* SystemInitialize for IfAction SubSystem: 'NormalState' (':1656') */
  /* SystemInitialize for Atomic SubSystem: 'PwmInSpeedCtrl' (':977') */
  PwmInSpeedCtrl_Init();

  /* End of SystemInitialize for SubSystem: 'PwmInSpeedCtrl' (':977') */
  /* End of SystemInitialize for SubSystem: 'NormalState' (':1656') */
}

/* Output and update for atomic system: 'PwmInTargetSpeedEval' (':961') */
void PwmInTargetSpeedEval(void)
{
  int8_T rtAction;
  int8_T rtPrevAction;

  /* If: 'If' (':1650') incorporates:
   *  Constant: 'InitSpeed' (':1671')
   *  Constant: 'PowerOnBlankTimeThreshold' (':968')
   *  Memory: 'PowerOnBlankTimeCnt' (':967')
   *  RelationalOperator: 'Relational Operator' (':1017')
   */
  rtPrevAction = DW.If_ActiveSubsystem;
  rtAction = (int8_T)(DW.PowerOnBlankTimeCnt_PreviousInp >= 20U);
  DW.If_ActiveSubsystem = rtAction;
  if (((int16_T)rtPrevAction != (int16_T)rtAction) && ((int16_T)rtPrevAction ==
       1))
  {
    /* Disable for Atomic SubSystem: 'PwmInSpeedCtrl' (':977') */
    PwmInSpeedCtrl_Disable();

    /* End of Disable for SubSystem: 'PwmInSpeedCtrl' (':977') */
  }

  if ((int16_T)rtAction == 0)
  {
    /* Outputs for IfAction SubSystem: 'PowerOnBlankState' (':1652') incorporates:
     *  ActionPort: 'Action Port' (':1654')
     */
    /* Update for Memory: 'PowerOnBlankTimeCnt' (':967') incorporates:
     *  Constant: 'AddOne' (':973')
     *  Sum: 'Add' (':972')
     */
    DW.PowerOnBlankTimeCnt_PreviousInp++;
    B.PwmInTargetSpeed = 0;

    /* Merge: 'Merge2' (':1669') incorporates:
     *  Constant: 'InitErrSts' (':1670')
     *  Constant: 'InitSpeed' (':1671')
     */
    B.PwmInError = false;

    /* End of Outputs for SubSystem: 'PowerOnBlankState' (':1652') */
  }
  else
  {
    /* Outputs for IfAction SubSystem: 'NormalState' (':1656') incorporates:
     *  ActionPort: 'Action Port' (':1658')
     */
    /* Outputs for Atomic SubSystem: 'PwmInSpeedCtrl' (':977') */
    PwmInSpeedCtrl();

    /* End of Outputs for SubSystem: 'PwmInSpeedCtrl' (':977') */

    /* Merge: 'Merge2' (':1669') incorporates:
     *  SignalConversion generated from: 'PwmInError' (':1667')
     */
    B.PwmInError = B.PwmInErr;

    /* SignalConversion generated from: 'TargetSpeed' (':1666') */
    B.PwmInTargetSpeed = B.Out;

    /* End of Outputs for SubSystem: 'NormalState' (':1656') */
  }

  /* End of If: 'If' (':1650') */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
