#ifndef HAVE_PRE_PWM_H
#define HAVE_PRE_PWM_H

#include "base.h"

#include "pre_pwm_bf.h"
#include "pre_pwm_irq.h"
#include "types.h"

#include "vic.h"

typedef struct
{
  uint16_t duration : 9;         /* [ 8:0] */
  int16_t slope : 7;             /* [15:9] */
  uint16_t slope_acc_start : 15; /* [30:16] */
  uint16_t use_cfg_on : 1;       /* [31] */
} _PACKED_ pre_pwm_table_entry;

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void pre_pwm_set_cfg(pre_pwm_cfg_t cfg);

pre_pwm_cfg_t pre_pwm_get_cfg(void);

void pre_pwm_set_bp_max(pre_pwm_bp_max_t bp_max);

pre_pwm_bp_max_t pre_pwm_get_bp_max(void);

void pre_pwm_set_addr_base(pre_pwm_addr_base_t addr_base);

pre_pwm_addr_base_t pre_pwm_get_addr_base(void);

void pre_pwm_set_cmd(pre_pwm_cmd_t cmd);

void pre_pwm_set_acc(pre_pwm_acc_t acc);

void pre_pwm_set_scale_offset(pre_pwm_scale_offset_t scale_offset0, uint8_t nr);

pre_pwm_scale_offset_t pre_pwm_get_scale_offset(uint8_t nr);

void pre_pwm_set_bp_sync0(pre_pwm_bp_sync_t bp_sync0);

pre_pwm_bp_sync_t pre_pwm_get_bp_sync0(void);

void pre_pwm_set_bp_sync1(pre_pwm_bp_sync_t bp_sync1);

pre_pwm_bp_sync_t pre_pwm_get_bp_sync1(void);

void pre_pwm_set_sync_en(pre_pwm_sync_en_t sync_en);

pre_pwm_sync_en_t pre_pwm_get_sync_en(void);

void pre_pwm_set_sync_ext_cfg(pre_pwm_sync_ext_cfg_t sync_ext_cfg);

pre_pwm_sync_ext_cfg_t pre_pwm_get_sync_ext_cfg(void);

void pre_pwm_set_scale_sync(pre_pwm_scale_sync_t scale_sync);

pre_pwm_scale_sync_t pre_pwm_get_scale_sync(void);

void pre_pwm_set_inc_sync(pre_pwm_inc_sync_t inc_sync);

pre_pwm_inc_sync_t pre_pwm_get_inc_sync(void);

void pre_pwm_set_addr(pre_pwm_addr_t addr, uint8_t nr);
void pre_pwm_set_current(pre_pwm_lw_t lw, pre_pwm_hw_t hw, uint8_t nr);
void pre_pwm_set_reload(pre_pwm_lw_rld_t lw_rld, pre_pwm_hw_rld_t hw_rld, uint8_t nr);
pre_pwm_addr_t pre_pwm_get_addr(uint8_t nr);
void pre_pwm_get_current(pre_pwm_lw_t *lw, pre_pwm_hw_t *hw, uint8_t nr);
void pre_pwm_get_reload(pre_pwm_lw_rld_t *lw_rld, pre_pwm_hw_rld_t *hw_rld, uint8_t nr);

void pre_pwm_set_irq_mask(pre_pwm_irq_mask_t irq_mask);
pre_pwm_irq_mask_t pre_pwm_get_irq_mask(void);

void pre_pwm_test_enable_all_irqs(void);
/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

void pre_pwm_handler_init(void);

void pre_pwm_handler_register(pre_pwm_irq_t irq, callback_t callback);

void pre_pwm_enable_irq(pre_pwm_irq_t irq, bool enable);

pre_pwm_irq_status_t pre_pwm_get_irq_status(void);

void pre_pwm_clear_all_irq_events(void);

#define pre_pwm_handler_register(irq, cb) irq_handler_register(VIC_IRQ_PRE_PWM, irq, cb)

#define pre_pwm_enable_irq(irq, en)                                                                                    \
  {                                                                                                                    \
    if (en)                                                                                                            \
      irq_enable(VIC_IRQ_PRE_PWM, irq);                                                                                \
    else                                                                                                               \
      irq_disable(VIC_IRQ_PRE_PWM, irq);                                                                               \
  }

#define pre_pwm_get_irq_status() ((pre_pwm_irq_status_t)(unsigned short)irq_get_status(VIC_IRQ_PRE_PWM))

#define pre_pwm_clear_all_irq_events() irq_clear_all_events(VIC_IRQ_PRE_PWM)

#endif /* HAVE_PRE_PWM_H */
