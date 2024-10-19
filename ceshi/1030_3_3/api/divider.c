
#include "divider.h"
#include "utils.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

uint32_t divider_udiv(uint32_t dividend, uint16_t divisor)
{
  uint32_t ret;

  WRITE_REG_32(BASE_ADDR_DIVIDER + ADDR_DIVIDER_OP1LO, dividend);
  WRITE_REG_16(BASE_ADDR_DIVIDER + ADDR_DIVIDER_OP2, divisor);
  ret = READ_REG_U32(BASE_ADDR_DIVIDER + ADDR_DIVIDER_RESULTLO);

  return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:divider_udiv_soft
* Description:
* 软件除法器，用于平替硬件除法器
*
* Inputs:
*
*
*
*
* Outputs:
*
*
* Limitations:
********************************************************************
END_FUNCTION_HDR*/
uint32_t divider_udiv_soft(uint32_t dividend, uint16_t divisor)
{
  uint32_t ret;
  if (divisor != 0)
  {
    ret = dividend / divisor;
  }
  else
  {
    ret = UINT32_MAX;
  }
  return ret;
}

uint16_t divider_get_udiv_remainder(void)
{

  return READ_REG_U16(BASE_ADDR_DIVIDER + ADDR_DIVIDER_REMAINDER);
}

int32_t divider_sdiv(int32_t dividend, int16_t divisor)
{

  WRITE_REG_32(BASE_ADDR_DIVIDER + ADDR_DIVIDER_OP1LO, dividend);
  WRITE_REG_16(BASE_ADDR_DIVIDER + ADDR_DIVIDER_OP2S, divisor);

  return READ_REG_S32(BASE_ADDR_DIVIDER + ADDR_DIVIDER_RESULTLO);
}

int16_t divider_get_sdiv_remainder(void)
{

  return READ_REG_S16(BASE_ADDR_DIVIDER + ADDR_DIVIDER_REMAINDER);
}

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

#include "vic.h"
#include "vic_irq.h"

volatile static callback_t callback[DIVIDER_NUM_IRQS];

void divider_handler_init(void)
{

  irq_handler_init(VIC_IRQ_DIVIDER, DIVIDER_NUM_IRQS, (callback_t *)callback,
                   BASE_ADDR_DIVIDER + ADDR_DIVIDER_IRQ_VENABLE);
}
