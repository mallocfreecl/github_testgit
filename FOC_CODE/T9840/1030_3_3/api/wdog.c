
#include "wdog.h"

#define PASSWORD 0xA5

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void wdog_init(wdog_num_t wdog, uint8_t prescale_reload, uint16_t reload)
{
  WRITE_REG_16(BASE_ADDR_WDOG + ADDR_WDOG_PRESCALER, prescale_reload);
  WRITE_REG_16(BASE_ADDR_WDOG + ADDR_WDOG_RELOAD, reload);
}

void wdog_win_config(wdog_num_t wdog, uint8_t size, bool enable)
{
  wdog_window_t window;

  window.val = 0;
  window.bf.size = size;
  window.bf.enable = enable;
  WRITE_REG_16(wdog + ADDR_WDOG_WINDOW, window.val);
}

void wdog_enable(wdog_num_t wdog)
{
  wdog_control_t control;

  control.val = 0;
  control.bf.run_enable = 1;
  control.bf.password = PASSWORD;
  WRITE_REG_16(wdog + ADDR_WDOG_CONTROL, control.val);
}

void wdog_restart(wdog_num_t wdog)
{
  wdog_control_t control;

  control.val = 0;
  control.bf.restart = 1;
  control.bf.password = PASSWORD;
  WRITE_REG_16(wdog + ADDR_WDOG_CONTROL, control.val);
}

bool wdog_is_running(wdog_num_t wdog)
{
  wdog_control_t control;

  control.val = READ_REG_U16(wdog + ADDR_WDOG_CONTROL);
  return control.bf.run_enable ? true : false;
}

uint16_t wdog_get_timer_val(wdog_num_t wdog)
{
  return READ_REG_U16(wdog + ADDR_WDOG_COUNTER);
}

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

#include "vic.h"
#include "vic_irq.h"

volatile static callback_t callback[WDOG_NUM_IRQS];

void wdog_handler_init(void)
{
  irq_handler_init(VIC_IRQ_WDOG, WDOG_NUM_IRQS, (callback_t *)callback, BASE_ADDR_WDOG + ADDR_WDOG_IRQ_VENABLE);
}
