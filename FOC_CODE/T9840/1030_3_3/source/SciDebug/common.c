#include "Common.h"

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/



/*******************************************************************************
* Function Name  :
* Description    :
* Input          :
* Output         :
* Return         :
*******************************************************************************/
MInt16 look1_is16ls32n10Ds32_linlags(MInt16 u0, const MInt16 bp0[], const
  MInt16 table[], MUInt32 maxIndex)
{
  MInt32 frac;
  MInt16 y_0;
  MUInt32 bpIdx;

  /* Lookup 1-D
     Search method: 'linear'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'on'
     Rounding mode: 'simplest'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'on'
     Rounding mode: 'simplest'
   */
  /* Linear Search */
  bpIdx = maxIndex >> 1U;

  if(u0 < bp0[0])
  {
      return table[0];
  }

  while ((u0 < bp0[bpIdx]) && (bpIdx > 0U)) {
    bpIdx--;
  }

  while ((bpIdx < maxIndex) && (u0 >= bp0[bpIdx + 1U])) {
    bpIdx++;
  }

  frac = (MInt32)(((MUInt32)(MUInt16)((MUInt32)u0 - bp0[bpIdx]) << 10) /
                   (MUInt16)(bp0[bpIdx + 1U] - bp0[bpIdx]));

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'on'
     Rounding mode: 'simplest'
     Overflow mode: 'wrapping'
   */

  if (bpIdx == maxIndex) {
    y_0 = table[bpIdx];
  } else {
    y_0 = (MInt16)((MInt16)((table[bpIdx + 1U] - table[bpIdx]) * frac >> 10) +
                    table[bpIdx]);
  }

  return y_0;
}
/*******************************************************************************
* Function Name  : LookTableStepBelow_s16
* Description    : If input < table_x[i],then return table_y[i].If input >=table_x
                    [index_max],then return table_y[index_max].
* Input          :
* Output         :
* Return         :
*******************************************************************************/
sint16 LookTableStepBelow_s16(sint16 input,const sint16 table_x[],const sint16 table_y[],uint8 table_len)
{
    sint16 ret;
    uint8 i;

    for(i = 0; i < table_len; i++)
    {
        if( (input < table_x[i])
          ||(i == (table_len - 1)))
        {
            ret = table_y[i];
            break;
        }
    }

    return ret;
}
/*******************************************************************************
* Function Name  :
* Description    :
* Input          :
* Output         :
* Return         :
*******************************************************************************/
void copymemory(uint8 des[],uint8 src[],uint8 length)
{
    uint8 i;
    for(i=0;i<length ;i++)
    {
        des[i]= src[i];
  }
}


