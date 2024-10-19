#include "u_f_table.h"
#include "ADCSample.h"
#include "divider.h"
#include "h430_mul.h"
#include "main.h"
#include "saradc_tables.h"

// kennlinie is done as a function
// f(inc) = a/b*x+c and = minimal d [mult]
// e is the maximal added multiplier to the basevalue of the uf_function to
// prevent overcurrents
s16 U_F_Kennlinie(s16 sinc, u16 boost, bool offset, bool divider_hw_en)
{
  s16 ret;
  u16 uinc = ABS(sinc);
  u16 adapt_offset = 0;

  if (offset)
  {
    adapt_offset += m.uf_offset;
  }
  adapt_offset += boost;
  /* 判断是使用软件除法器还是硬件除法器 23.12.15 by lxs */
  if (divider_hw_en != false)
  {
    ret = MIN(divider_udiv(((u32)m.uf_slope * (u32)uinc) + (((u32)(adapt_offset)) << MULTIPLIER_REFERENCE_SHIFT),
                           ADCResults.RawAD.Bat),
              driver_maximal_multiplier);
  }
  else
  {
    ret = MIN(divider_udiv_soft(((u32)m.uf_slope * (u32)uinc) + (((u32)(adapt_offset)) << MULTIPLIER_REFERENCE_SHIFT),
                                ADCResults.RawAD.Bat),
              driver_maximal_multiplier);
  }

  if (ret < m.uf_min)
  {
    ret = m.uf_min;
  }

  if (sinc < 0)
  {
    ret = -ret;
  }

  return ret;
}
