#ifndef __H430_MUL_H__
#define __H430_MUL_H__

#include "base.h"
#include "types.h"

/* ========================================================================== */
/* MULTIPLY constants */
/* ========================================================================== */

typedef enum
{
  MUL, /* multiply */
  MAC  /* multiply with accumulate */
} mult_type;

/* ========================================================================== */
/* MULTIPLY serve functions */
/* ========================================================================== */

void mult_set_accu(uint32_t value);

/* 16 Bit x 16 Bit -> 32 Bit */
uint32_t multiply_u16_u16(mult_type type, uint16_t fac_a, uint16_t fac_b);
int32_t multiply_s16_s16(mult_type type, int16_t fac_a, int16_t fac_b);

/* 8 Bit x 16 Bit -> 32 Bit */
uint32_t multiply_u08_u16(mult_type type, uint8_t fac_a, uint16_t fac_b);
int32_t multiply_s08_s16(mult_type type, int8_t fac_a, int16_t fac_b);

/* 16 Bit x  8 Bit -> 32 Bit */
uint32_t multiply_u16_u08(mult_type type, uint16_t fac_a, uint8_t fac_b);
int32_t multiply_s16_s08(mult_type type, int16_t fac_a, int8_t fac_b);

/* 8 Bit x  8 Bit -> 16 Bit */
uint16_t multiply_u08_u08(mult_type type, uint8_t fac_a, uint8_t fac_b);
int16_t multiply_s08_s08(mult_type type, int8_t fac_a, int8_t fac_b);

uint16_t multiply_sumext(void);

#endif /* __H430_MUL_H__ */
