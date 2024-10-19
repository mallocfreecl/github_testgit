#include "commons.h"
#include "api.h"
#include "irq.h"
#include "pre_pwm_helper_addon.h"

/**
 * @addtogroup MISC Miscellaneous
 * @ingroup OTHER
 *
 * @{
 */

// Source: http://www.coranac.com/documents/arctangent/
#define OCTANTIFY(_x, _y, _o)                                                                                          \
  do                                                                                                                   \
  {                                                                                                                    \
    s16 _t;                                                                                                            \
    _o = 0;                                                                                                            \
    if (_y < 0)                                                                                                        \
    {                                                                                                                  \
      _x = -_x;                                                                                                        \
      _y = -_y;                                                                                                        \
      _o += 4;                                                                                                         \
    }                                                                                                                  \
    if (_x <= 0)                                                                                                       \
    {                                                                                                                  \
      _t = _x;                                                                                                         \
      _x = _y;                                                                                                         \
      _y = -_t;                                                                                                        \
      _o += 2;                                                                                                         \
    }                                                                                                                  \
    if (_x <= _y)                                                                                                      \
    {                                                                                                                  \
      _t = _y - _x;                                                                                                    \
      _x = _x + _y;                                                                                                    \
      _y = _t;                                                                                                         \
      _o += 1;                                                                                                         \
    }                                                                                                                  \
  } while (0);

// pi
#define BP_BRAD_PI (3969 >> 1) // This is PI
#define ATAN_FP 14             //(y/x)<<ATAN_FP //assertion: min(x,y)<<ATAN_FP < 2^32

// table
#define ATAN_FP_LUT_SHIFT (ATAN_FP - 7)         // conversion from (y/x)<<ATAN_FP --> [0...2�128entries]
#define ATAN_FP_LUT_SIZE 1 << ATAN_FP_LUT_SHIFT // size of the table
#define BP_ATAN_LUT_ENTRY_SHIFT 7               // 1<<BRAD_PI_SHIFT+ATAN_LUT_ENTRY_SHIFT is PI in table

static void printuint_generic(u16 i, bool zeros);

// Arctangens LUT. Interval: [0, 1] (one=128); PI=3969<<6
const uint16_t atanLUTBP[130] = // ALIGN(4)=
  {0x0000, 0x0278, 0x04EF, 0x0767, 0x09DE, 0x0C55, 0x0ECB, 0x1141, 0x13B7, 0x162C, 0x18A0, 0x1B14, 0x1D86,
   0x1FF8, 0x2269, 0x24D8, 0x2747, 0x29B4, 0x2C20, 0x2E8B, 0x30F4, 0x335C, 0x35C3, 0x3827, 0x3A8A, 0x3CEC,
   0x3F4B, 0x41A9, 0x4405, 0x465F, 0x48B7, 0x4B0C, 0x4D60, 0x4FB1, 0x5201, 0x544D, 0x5698, 0x58E0, 0x5B26,
   0x5D69, 0x5FAA, 0x61E8, 0x6424, 0x665D, 0x6893, 0x6AC7, 0x6CF7, 0x6F25, 0x7151, 0x7379, 0x759F, 0x77C1,
   0x79E1, 0x7BFE, 0x7E17, 0x802E, 0x8242, 0x8452, 0x8660, 0x886B, 0x8A72, 0x8C76, 0x8E78, 0x9076, 0x9271,
   0x9468, 0x965D, 0x984E, 0x9A3D, 0x9C28, 0x9E10, 0x9FF4, 0xA1D6, 0xA3B4, 0xA58F, 0xA767, 0xA93B, 0xAB0D,
   0xACDB, 0xAEA6, 0xB06E, 0xB233, 0xB3F4, 0xB5B2, 0xB76E, 0xB925, 0xBADA, 0xBC8C, 0xBE3A, 0xBFE6, 0xC18E,
   0xC333, 0xC4D5, 0xC674, 0xC810, 0xC9A9, 0xCB3F, 0xCCD2, 0xCE61, 0xCFEE, 0xD178, 0xD2FF, 0xD482, 0xD603,
   0xD781, 0xD8FC, 0xDA74, 0xDBEA, 0xDD5C, 0xDECC, 0xE038, 0xE1A2, 0xE30A, 0xE46E, 0xE5D0, 0xE72F, 0xE88B,
   0xE9E4, 0xEB3B, 0xEC8F, 0xEDE1, 0xEF30, 0xF07C, 0xF1C6, 0xF30D, 0xF451, 0xF593, 0xF6D3, 0xF810, 0xF94B};

const uint16_t sinLUTBP[] = // ALIGN(4)=
  {0x0000, 0x019F, 0x033E, 0x04DC, 0x067B, 0x081A, 0x09B8, 0x0B55, 0x0CF3, 0x0E8F, 0x102B, 0x11C7, 0x1361, 0x14FB,
   0x1694, 0x182D, 0x19C4, 0x1B5A, 0x1CEF, 0x1E82, 0x2015, 0x21A6, 0x2336, 0x24C4, 0x2651, 0x27DC, 0x2966, 0x2AEE,
   0x2C74, 0x2DF8, 0x2F7B, 0x30FB, 0x327A, 0x33F6, 0x3570, 0x36E9, 0x385E, 0x39D2, 0x3B43, 0x3CB2, 0x3E1E, 0x3F88,
   0x40EF, 0x4253, 0x43B5, 0x4513, 0x466F, 0x47C9, 0x491F, 0x4A72, 0x4BC2, 0x4D0F, 0x4E59, 0x4FA0, 0x50E3, 0x5223,
   0x5360, 0x5499, 0x55CF, 0x5701, 0x5830, 0x595B, 0x5A82, 0x5BA6, 0x5CC6, 0x5DE2, 0x5EFA, 0x600E, 0x611E, 0x622B,
   0x6333, 0x6437, 0x6538, 0x6634, 0x672B, 0x681F, 0x690E, 0x69F9, 0x6AE0, 0x6BC2, 0x6CA0, 0x6D79, 0x6E4E, 0x6F1E,
   0x6FEA, 0x70B1, 0x7174, 0x7232, 0x72EB, 0x739F, 0x744F, 0x74FA, 0x75A0, 0x7641, 0x76DE, 0x7775, 0x7808, 0x7895,
   0x791E, 0x79A2, 0x7A21, 0x7A9A, 0x7B0F, 0x7B7F, 0x7BE9, 0x7C4F, 0x7CAF, 0x7D0B, 0x7D61, 0x7DB2, 0x7DFE, 0x7E44,
   0x7E86, 0x7EC2, 0x7EF9, 0x7F2B, 0x7F57, 0x7F7F, 0x7FA1, 0x7FBE, 0x7FD5, 0x7FE8, 0x7FF5, 0x7FFD, 0x7FFF, 0x7FFD};

int16_t atan2Lerp_BP(int16_t y, int16_t x)
{
  if (y == 0)
  {
    return (x >= 0 ? 0 : BP_BRAD_PI);
  } // div zero

  uint16_t phi;
  OCTANTIFY(x, y, phi);
  phi = (phi * BP_BRAD_PI + 2) >> 2;
  phi += 1; // some correction

  uint16_t t, fa, fb, h;
  // t = QDIV(y, x, ATAN_FP);
  t = divider_sdiv(((int32_t)y) << ATAN_FP, x);

  h = t & ((1 << (ATAN_FP_LUT_SHIFT)) - 1);
  fa = atanLUTBP[t >> ATAN_FP_LUT_SHIFT];
  fb = atanLUTBP[(t >> ATAN_FP_LUT_SHIFT) + 1];
  phi += ((fa + (((fb - fa) * h) >> ATAN_FP_LUT_SHIFT)) >> (BP_ATAN_LUT_ENTRY_SHIFT));

  return phi;
}

int16_t sin_BP(s16 bp)
{

  bool neg = false;
  if (bp > BP_MAX >> 1)
  {
    bp = bp - (BP_MAX >> 1);
    neg = true;
  }
  // 0-180
  if (bp > (BP_MAX >> 2))
  {
    bp = (BP_MAX >> 1) - bp;
  }
  // 0-90 == 0-992
  //

  uint16_t fa, fb, h;

  h = bp & ((1 << (SIN_FP_LUT_SHIFT)) - 1);
  fa = sinLUTBP[(u16)bp >> SIN_FP_LUT_SHIFT];
  fb = sinLUTBP[((u16)bp >> SIN_FP_LUT_SHIFT) + 1];

  fa = (fa + (((fb - fa) * h)>> SIN_FP_LUT_SHIFT));
  if (neg)
  {
    fa = -fa;
  }
  return fa;
}

s16 take_nearest_bp(s16 phasor_one, s16 phasor_two)
{
  s16 result = phasor_one - phasor_two;
  if (result > BASE_PHASE_MAX >> 1)
  {
    result -= BASE_PHASE_MAX;
  }
  else if (result < ((-BASE_PHASE_MAX) >> 1))
  {
    result += BASE_PHASE_MAX;
  }
  return result;
}

u16 Motor_BasePhaseLimit(s16 base_phase)
{
  if (base_phase >= BASE_PHASE_MAX)
  {
    base_phase -= BASE_PHASE_MAX;
  }
  else if (base_phase < 0)
  {
    base_phase += BASE_PHASE_MAX;
  }
  else
  {
  }

  return base_phase;
}

void putu16(u16 ch)
{
  putchar((ch >> 0) & 0x00FF);
  putchar((ch >> 8) & 0x00FF);
}

/******************************************************************************
  own __write to enable printf & scanf
******************************************************************************/

size_t __write(s16 fd, const u8 *buffer, size_t len)
{
  s16 nChars = 0;

  for (/*Empty */; len > 0; --len)
  {
    putchar(*buffer++);
    nChars++;
  }
  return nChars;
}

/****************************************************************************/
/*        Limit value                                                       */
/****************************************************************************/
u16 utils_u16_limit(u16 act_value, s16 incr_value, u16 limit)
{
  s32 tmp = (s32)act_value;
  tmp += incr_value;
  if (tmp < 0)
  {
    tmp = 0;
  }
  else if (tmp > (s32)limit)
  {
    tmp = (s32)limit;
  }
  return (u16)tmp;
}

#define HEX_NIBBLES 4

void printhex(u16 val)
{
  // char WarnMe[16] = "0123456789ABCDEF";//no compiler warning
  char map[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}; // better
  char dest[HEX_NIBBLES];
  int i;

  for (i = HEX_NIBBLES - 1; i >= 0; i--)
  {
    dest[i] = map[val & 0xfU];
    val = val >> 4U;
  }

  for (i = 0; i < HEX_NIBBLES; i++)
  {
    sci_transmit(dest[i]);
  }
}

void printint(s16 i)
{
  u16 u;
  if (i < 0)
  {
    putchar('-');
    u = (u16)(-i);
  }
  else
  {
    putchar('+');
    u = (u16)i;
  }
  printuint_better(u);
}

void printuint_generic(u16 i, bool zeros)
{
  u8 digit;
  bool rest = false;

  digit = divider_udiv(i, 10000);
  if (zeros || digit != 0 || rest)
  {
    putchar((u8)(digit + '0'));
    rest = true;
  }
  i = i - (digit * 10000);

  digit = divider_udiv(i, 1000);
  if (zeros || digit != 0 || rest)
  {
    putchar((u8)(digit + '0'));
    rest = true;
  }

  i = i - (digit * 1000);

  digit = divider_udiv(i, 100);
  if (zeros || digit != 0 || rest)
  {
    putchar((u8)(digit + '0'));
    rest = true;
  }

  i = i - (digit * 100);

  digit = divider_udiv(i, 10);
  if (zeros || digit != 0 || rest)
  {
    putchar((u8)(digit + '0'));
    rest = true;
  }

  i = i - (digit * 10);

  digit = i;
  if (zeros || digit != 0 || rest)
  {
    putchar((u8)(digit + '0'));
    rest = true;
  }
}

void printuint_better(u16 rest)
{
  u8 digit;
  bool started = false;
  u16 divider;
  for (u8 pos = 0; pos < 5; pos++)
  {
    switch (pos)
    {
    case 0:
      divider = 10000;
      break;
    case 1:
      divider = 1000;
      break;
    case 2:
      divider = 100;
      break;
    case 3:
      divider = 10;
      break;
    case 4:
      putchar((u8)(rest + '0'));
      return;
      break;
    default:
      break;
    }
    CLI();
    digit = divider_udiv(rest, divider);
    rest = divider_get_udiv_remainder();
    SEI();
    if (digit || started)
    {
      putchar((u8)(digit + '0'));
      started = true;
    }
    else
    {
      putchar(' ');
    }
  }
}

void printuint(u16 i)
{
  printuint_generic(i, true);
}

void printuint_short(u16 i)
{
  printuint_generic(i, false);
}

static s16 x_avg = 0;
static s16 y_avg = 0;
static s64 sxx = 0;
static s64 sxy = 0;

void linear_regression_init(s16 xavg, s16 yavg)
{
  sxx = 0;
  sxy = 0;
  x_avg = xavg;
  y_avg = yavg;
}

void linear_regression_succ(s16 x, s16 y)
{
  x = x - x_avg;
  y = y - y_avg;
  sxx += x * x;
  sxy += x * y;
}

void linear_regression_result(s16 *a, s16 *b, s16 slope_scaler, u8 shift)
{
  if (sxx == 0)
  {
    *b = 0xFFFF;
    *a = 0xFFFF;
  }
  else
  {
    *b = ((s64)sxy * (s64)slope_scaler) / sxx;
    *a = (((s32)y_avg * (s32)slope_scaler) - (((s32)*b * x_avg))) >> shift;
  }
}

s16 look1_is16ls32n10Ds32_linlags(s16 u0, const s16 bp0[], const s16 table[], u32 maxIndex)
{
  s32 frac;
  s16 y_0;
  u32 bpIdx;

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

  if (u0 < bp0[0])
  {
    return table[0];
  }

  while ((u0 < bp0[bpIdx]) && (bpIdx > 0U))
  {
    bpIdx--;
  }

  while ((bpIdx < maxIndex) && (u0 >= bp0[bpIdx + 1U]))
  {
    bpIdx++;
  }

  frac = (s32)(((u32)(u16)((u32)u0 - bp0[bpIdx]) << 10) / (u16)(bp0[bpIdx + 1U] - bp0[bpIdx]));

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'on'
     Rounding mode: 'simplest'
     Overflow mode: 'wrapping'
   */

  if (bpIdx == maxIndex)
  {
    y_0 = table[bpIdx];
  }
  else
  {
    y_0 = (s16)((s16)(((table[bpIdx + 1U] - table[bpIdx]) * frac) >> 10) + table[bpIdx]);
  }

  return y_0;
}

u16 BCD2u16(u16 BCD)
{
  const u8 bits = 16;
  u16 tmp;
  u16 ret = 0;
  u8 i, j;

  for (i = 0; i < bits / 4; i++)
  {
    tmp = BCD & 0xFu;
    if (tmp > 9)
    {
      tmp = 9;
    }

    if (i == 0)
    {
      if (tmp > 6)
      {
        tmp = 6;
      }
    }

    for (j = i; j > 0; j--)
    {
      tmp *= 10;
    }

    ret += tmp;

    BCD >>= 4;
  }

  return ret;
}
/* 增加限幅函数 23.08.28 by lxs */
__STATIC_INLINE s32 __ssat(s32 val, u8 sat)
{
  s32 min, max;

  /* polyspace +1 DEFECT:INT_CONV_OVFL */
  max = (1L << (sat - 1)) - 1;
  min = -(max + 1);

  if (val > max)
  {
    val = max;
  }
  else if (val < min)
  {
    val = min;
  }
  else
  {
  }

  return val;
}


/** \brief Performs low-pass filter algorithm.
 *
 * \param[inout] pLp Pointer to low-pass filter status
 * \param[in] Input Input in fixed-point format
 *
 * \return Low-pass filter output in fixed-point format
 * \ingroup math_api
 */
s16 Mat_ExeLp(TMat_Lp *pLp, s16 Input)
{
  s32 Out;
  s32 Min;
  s32 Max;

  /* New output = saturate(old output + coefficient A * input - coefficient B * old output/2^15 */
  Out = pLp->Out;
  Out = __ssat((Out + ((s32)pLp->CoefA * (s32)Input)) - ((s32)pLp->CoefB * (Out >> 15u)), 31u);

  /* Limit new output */
  Min = ((s32)(pLp->Min)) << 15u;
  if (Out < Min)
  {
    Out = Min;
  }
  else
  {
    Max = ((s32)(pLp->Max)) << 15u;
    if (Out > Max)
    {
      Out = Max;
    }
  }
  /* Store new output */
  pLp->Out = Out;

  /* return upper part */
  return (s16)(Out >> 15u);

} /* End of Mat_ExeLp */

/** @} */
