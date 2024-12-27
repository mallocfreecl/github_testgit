#ifndef __COMMONS__
#define __COMMONS__

#include <stdio.h>

#include "api.h"
#include "assert.h"
#include "divider.h"
#include "limits.h"
#include "parameters.h"

#define ABS(x) (((x) < 0) ? -(x) : (x))

// for serial and nomenu option all printf are disabled

// NDEBUG for no assertion stop
#define NDEBUG

#if defined(SERIAL) || defined(NOMENU)
#define PRINTF(...)
#define NOPRINTF
#else
#define PRINTF(...) printf(__VA_ARGS__)
#endif

// disable text of menu for labview
#ifdef SERIAL
#define M(x) NULL
#else
#define M(x) x
#endif

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MASK(x) (1U << (x))

#define CLR "\033[2J"

/**
 * @defgroup MISC Miscellaneous
 * @ingroup OTHER
 *
 * @{
 */
/** Maximal basephases for the deposited pre_pwmn tables*/
#define BASE_PHASE_MAX (3968)
#define BP_MAX BASE_PHASE_MAX
/** Calculates the degree associated basephases */
#define DEG_TO_BP(x) (((x) * (int32_t)BASE_PHASE_MAX + 180) / 360)

// multiply with 5.54 or divide
//#define INC_TO_ERPM(x)  (((s32)(x)*(s32)362812/2)>>16)
#define INC_TO_ERPM(x) (((s32)(x) * (s32)181406) >> 16)
//#define ERPM_TO_INC(x)  (((s32)(x)*(s32)11878*2)>>16)
#define ERPM_TO_INC(x) (((s32)(x) * (s32)11878) >> 15)

#define INC_U_TO_ERPM(x) (((u32)(x) * (u32)362812 / 2) >> 16)
#define ERPM_U_TO_INC(x) (((u32)(x) * (u32)11878 * 2) >> 16)

#define INC_U_TO_ERPM_100_S(x, y) (((u32)(x) * (u32)3628 / 2) >> (16 - y))
#define ERPM_U_TO_INC_100_S(x, y) (((u32)(x) * (u32)119 * 2) >> (16 - y))

// S Setting
#define S_WINDMILL_DURATION_PWM 20
#define S_PRE_PWM_ACC 0x3FFFF

/* with REG_PRE_PWM_INC = ainc * PAR_SYS_CLK_DEVIDER; in pre_pwm_set_sinc_smult_init */
#define C_WM_BP_DUARATION_TO_INC                                                                                       \
  ((double)((double)S_PRE_PWM_ACC * (double)PAR_PWMFREQ_hz / (double)PAR_MAX_CLK_hz /                                  \
            (double)S_WINDMILL_DURATION_PWM * (double)0xFFFF))

#define C_WM_INC_TO_BP_DUARATION ((double)(1 / (double)C_WM_BP_DUARATION_TO_INC))

// OLD: 65536*16000/24000000/18*inc = 2.4272592592592593*0xFFFF*inc/0xFFFF
// NEW: 4*65536*16000/48000000/18*inc = ???*0xFFFF*inc/0xFFFF
#define DBP_PER_20PWMS_TO_INC(x) (((s32)C_WM_BP_DUARATION_TO_INC * (s32)(x)) / 0xFFFF)
#define INC_PER_20PWMS_TO_DBP(x) (((s32)C_WM_INC_TO_BP_DUARATION * (s32)(x)) / 0xFFFF)

/** Calculates the basephase to 10th of a degree*/
#define BP_TO_DEG(x) (divider_sdiv((s32)x * (s32)3600 + (s32)(BASE_PHASE_MAX >> 1), (BASE_PHASE_MAX)))

#define DEG30 331
#define DEG60 662
#define INVALID 0xFFFFU
#define INVALIDU8 0xFFU
#define VDD_EN_OFF 100

#define V100_CURSOR_SAVE                                                                                               \
  putchar('\033');                                                                                                     \
  putchar('7');
#define V100_CURSOR_RESTORE                                                                                            \
  putchar('\033');                                                                                                     \
  putchar('8');
#define V100_CURSOR_GOTO(x, y)                                                                                         \
  putchar('\033');                                                                                                     \
  putchar('[');                                                                                                        \
  printuint_short(x);                                                                                                  \
  putchar(';');                                                                                                        \
  printuint_short(y);                                                                                                  \
  putchar('H');
#define V100_CURSOR_GO_UP(x)                                                                                           \
  putchar('\033');                                                                                                     \
  putchar('[');                                                                                                        \
  printuint_short(x);                                                                                                  \
  putchar('A');
#define V100_ERASE_LINE                                                                                                \
  putchar('\033');                                                                                                     \
  putchar('[');                                                                                                        \
  putchar('2');                                                                                                        \
  putchar('K');

#define PRINT_GOTO_LINE(X, Y)                                                                                          \
  V100_CURSOR_SAVE;                                                                                                    \
  V100_CURSOR_GOTO(X, Y);

#define PRINT_GOTO_ERASE_LINE(X, Y)                                                                                    \
  V100_CURSOR_SAVE;                                                                                                    \
  V100_CURSOR_GOTO(X, Y);                                                                                              \
  V100_ERASE_LINE;

#define PRINT_RESTORE V100_CURSOR_RESTORE

enum RegressionState
{
  initial,
  feed,
  calc
};
/* 低通滤波相关参数结构体 23.08.28 by lxs */
typedef struct
{
  s16 CoefA; /**< \brief Coefficient A */
  s16 CoefB; /**< \brief Coefficient B */
  s16 Min;   /**< \brief Minimum */
  s16 Max;   /**< \brief Maximum */
  s32 Out;   /**< \brief Low pass output */
} TMat_Lp;


/**@brief If a basephase is higher than BASE_PHASE_MAX or lower than one, the value is corrected*/
u16 Motor_BasePhaseLimit(s16 base_phase);

/**@brief Returns smallest angle of two phasor.*/
s16 take_nearest_bp(s16 phasor_one, s16 phasor_two);

/**@brief Transmits a u16 per UART.*/
void putu16(u16 ch);

/**@brief Limits a value.*/
u16 utils_u16_limit(u16 act_value, s16 incr_value, u16 limit);

/**@brief Receives a char per UART.*/
void getchar_callback(s16 sno);

/**@brief */
int16_t atan2Lerp_BP(int16_t y, int16_t x);

// under development could have bugs
#define SIN_FP_LUT_SHIFT (3)  // all 8bp an entry 992/8= 124
#define SIN_BP_ENTRY_SHIFT 15 // 1 equals 0x7FFF

#define __STATIC_INLINE static inline
/* 低通滤波函数声明 23.08.28 by lxs */
extern  s16 Mat_ExeLp(TMat_Lp *pLp, s16 Input);

int16_t sin_BP(s16 bp);

/**@brief */
void printhex(u16 val);

void printint(s16 i);
void printuint(u16 i);
void printuint_short(u16 i);
void printuint_better(u16);

extern s16 look1_is16ls32n10Ds32_linlags(s16 u0, const s16 bp0[], const s16 table[], u32 maxIndex);

extern u16 BCD2u16(u16 BCD);

/* ===================================== */
/* deprecated types                      */
/* ===================================== */

#ifdef DOXYGEN

/**  uint8_t*/ typedef uint8_t u8;
/** uint16_t*/ typedef uint16_t u16;
/** uint32_t*/ typedef uint32_t u32;
/** uint64_t*/ typedef uint64_t u64;

/**  int8_t*/ typedef int8_t s8;
/** int16_t*/ typedef int16_t s16;
/** int32_t*/ typedef int32_t s32;
/** int64_t*/ typedef int64_t s64;

/** reg64*/ typedef volatile u64 reg64;
/** reg32*/ typedef volatile u32 reg32;
/** reg16*/ typedef volatile u16 reg16;
/**  reg8*/ typedef volatile u8 reg8;
#endif

/** @} */
#endif
