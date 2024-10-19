#ifndef __H430_MUL_BF_H__
#define __H430_MUL_BF_H__

#include "types.h"

typedef volatile struct
{
  volatile uint16_t FAC_A_MPY;
  volatile uint16_t FAC_A_MPYS;
  volatile uint16_t FAC_A_MAC;
  volatile uint16_t FAC_A_MACS;
  volatile uint16_t FAC_B;
  volatile uint32_t PRODUCT;
  volatile uint16_t PRODUCT_EXT;
} MULTIPLY_WORD_TypeDef;

typedef volatile struct
{
  volatile uint8_t FAC_A_MPY;
  volatile uint8_t reserved2;
  volatile uint8_t FAC_A_MPYS;
  volatile uint8_t reserved3;
  volatile uint8_t FAC_A_MAC;
  volatile uint8_t reserved4;
  volatile uint8_t FAC_A_MACS;
  volatile uint8_t reserved5;
  volatile uint8_t FAC_B;
  volatile uint8_t reserved6;
  volatile uint16_t PRODUCT;
} MULTIPLY_BYTE_TypeDef;

#define BASE_MULTIPLY 0x0130

#define MULTIPLY_WORD ((_PACKED_ MULTIPLY_WORD_TypeDef *)BASE_MULTIPLY)
#define MULTIPLY_BYTE ((_PACKED_ MULTIPLY_BYTE_TypeDef *)BASE_MULTIPLY)

#endif /* __H430_MUL_BF_H__ */
