#ifndef HAVE_WDOG_H
#define HAVE_WDOG_H

#include "base.h"

#include "wdog_bf.h"
#include "wdog_irq.h"

#include "vic.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void wdog_init(wdog_num_t wdog, uint8_t prescale_reload, uint16_t reload);

void wdog_win_config(wdog_num_t wdog, uint8_t size, bool enable);

void wdog_enable(wdog_num_t wdog);

void wdog_restart(wdog_num_t wdog);

bool wdog_is_running(wdog_num_t wdog);

uint16_t wdog_get_timer_val(wdog_num_t wdog);

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

void wdog_handler_init(void);

void wdog_handler_register(wdog_irq_t irq, callback_t callback);

void wdog_enable_irq(wdog_irq_t irq, bool enable);

wdog_irq_status_t wdog_get_irq_status(void);

void wdog_clear_all_irq_events(void);

#define wdog_handler_register(irq, cb) irq_handler_register(VIC_IRQ_WDOG, irq, cb)

#define wdog_enable_irq(irq, en)                                                                                       \
  {                                                                                                                    \
    if (en)                                                                                                            \
      irq_enable(VIC_IRQ_WDOG, irq);                                                                                   \
    else                                                                                                               \
      irq_disable(VIC_IRQ_WDOG, irq);                                                                                  \
  }

#define wdog_get_irq_status() ((wdog_irq_status_t)(unsigned short)irq_get_status(VIC_IRQ_WDOG))

#define wdog_clear_all_irq_events() irq_clear_all_events(VIC_IRQ_WDOG)

#endif /* HAVE_WDOG_H */
