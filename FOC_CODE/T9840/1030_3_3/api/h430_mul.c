#include "h430_mul.h"
#include "h430_mul_reg.h"

void mult_set_accu(uint32_t value)
{

  MULTIPLY_WORD->PRODUCT = value;
}

/* 16 Bit x 16 Bit -> 32 Bit */

uint32_t multiply_u16_u16(mult_type type, uint16_t fac_a, uint16_t fac_b)
{

  if (type == MAC)
    MULTIPLY_WORD->FAC_A_MAC = fac_a;
  else
    MULTIPLY_WORD->FAC_A_MPY = fac_a;
  MULTIPLY_WORD->FAC_B = fac_b;
  return MULTIPLY_WORD->PRODUCT;
}

int32_t multiply_s16_s16(mult_type type, int16_t fac_a, int16_t fac_b)
{

  if (type == MAC)
    MULTIPLY_WORD->FAC_A_MACS = fac_a;
  else
    MULTIPLY_WORD->FAC_A_MPYS = fac_a;
  MULTIPLY_WORD->FAC_B = fac_b;
  return MULTIPLY_WORD->PRODUCT;
}

/* 8 Bit x 16 Bit -> 32 Bit */

uint32_t multiply_u08_u16(mult_type type, uint8_t fac_a, uint16_t fac_b)
{

  if (type == MAC)
    MULTIPLY_BYTE->FAC_A_MAC = fac_a;
  else
    MULTIPLY_BYTE->FAC_A_MPY = fac_a;
  MULTIPLY_WORD->FAC_B = fac_b;
  return MULTIPLY_WORD->PRODUCT;
}

int32_t multiply_s08_s16(mult_type type, int8_t fac_a, int16_t fac_b)
{

  if (type == MAC)
    MULTIPLY_BYTE->FAC_A_MACS = fac_a;
  else
    MULTIPLY_BYTE->FAC_A_MPYS = fac_a;
  MULTIPLY_WORD->FAC_B = fac_b;
  return MULTIPLY_WORD->PRODUCT;
}

/* 16 Bit x  8 Bit -> 32 Bit */

uint32_t multiply_u16_u08(mult_type type, uint16_t fac_a, uint8_t fac_b)
{

  if (type == MAC)
    MULTIPLY_WORD->FAC_A_MAC = fac_a;
  else
    MULTIPLY_WORD->FAC_A_MPY = fac_a;
  MULTIPLY_BYTE->FAC_B = fac_b;
  return MULTIPLY_WORD->PRODUCT;
}

int32_t multiply_s16_s08(mult_type type, int16_t fac_a, int8_t fac_b)
{

  if (type == MAC)
    MULTIPLY_WORD->FAC_A_MACS = fac_a;
  else
    MULTIPLY_WORD->FAC_A_MPYS = fac_a;
  MULTIPLY_BYTE->FAC_B = fac_b;
  return MULTIPLY_WORD->PRODUCT;
}

/* 8 Bit x  8 Bit -> 16 Bit */

uint16_t multiply_u08_u08(mult_type type, uint8_t fac_a, uint8_t fac_b)
{

  if (type == MAC)
    MULTIPLY_BYTE->FAC_A_MAC = fac_a;
  else
    MULTIPLY_BYTE->FAC_A_MPY = fac_a;
  MULTIPLY_BYTE->FAC_B = fac_b;
  return (uint16_t)MULTIPLY_WORD->PRODUCT;
}

int16_t multiply_s08_s08(mult_type type, int8_t fac_a, int8_t fac_b)
{

  if (type == MAC)
    MULTIPLY_BYTE->FAC_A_MACS = fac_a;
  else
    MULTIPLY_BYTE->FAC_A_MPYS = fac_a;
  MULTIPLY_BYTE->FAC_B = fac_b;
  return (int16_t)MULTIPLY_WORD->PRODUCT;
}

uint16_t multiply_sumext(void)
{
  return MULTIPLY_WORD->PRODUCT_EXT;
}
