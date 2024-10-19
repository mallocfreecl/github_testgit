#ifndef HAVE_DIVIDER_H
#define HAVE_DIVIDER_H

#include "base.h"

#include "divider_bf.h"
#include "divider_irq.h"

#include "vic.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

uint32_t divider_udiv(uint32_t dividend, uint16_t divisor);

/*模仿硬件除法器制作的软件除法器 2023.12.15 by lxs */
uint32_t divider_udiv_soft(uint32_t dividend, uint16_t divisor);

uint16_t divider_get_udiv_remainder(void);

int32_t divider_sdiv(int32_t dividend, int16_t divisor);

int16_t divider_get_sdiv_remainder(void);

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

void divider_handler_init(void);

void divider_handler_register(divider_irq_t irq, callback_t callback);

void divider_enable_irq(divider_irq_t irq, bool enable);

divider_irq_status_t divider_get_irq_status(void);

void divider_clear_all_irq_events(void);

#define divider_handler_register(irq, cb) irq_handler_register(VIC_IRQ_DIVIDER, irq, cb)

#define divider_enable_irq(irq, en)                                                                                    \
  {                                                                                                                    \
    if (en)                                                                                                            \
      irq_enable(VIC_IRQ_DIVIDER, irq);                                                                                \
    else                                                                                                               \
      irq_disable(VIC_IRQ_DIVIDER, irq);                                                                               \
  }

#define divider_get_irq_status() ((divider_irq_status_t)(unsigned short)irq_get_status(VIC_IRQ_DIVIDER))

#define divider_clear_all_irq_events() irq_clear_all_events(VIC_IRQ_DIVIDER)

#endif /* HAVE_DIVIDER_H */
