#ifndef __PWMN_H__
#define __PWMN_H__

#include "base.h"

#include "pwmn_bf.h"
#include "pwmn_irq.h"

#include "types.h"
#include "vic.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

// SETTER
void pwmn_set_cfg(pwmn_cfg_t cfg);
void pwmn_set_cmd(pwmn_cmd_t cmd);
void pwmn_set_cnt(pwmn_cnt_t cnt);
void pwmn_set_prescaler(pwmn_prescaler_t prescaler);
void pwmn_set_cnt_max(pwmn_cnt_max_t cnt_max);
void pwmn_set_nth_start(pwmn_nth_start_t nth_start);
void pwmn_set_dead_time(pwmn_dead_time_t dead_time);
void pwmn_set_prescaler_reload(pwmn_prescaler_reload_t prescaler_reload);
void pwmn_set_cnt_max_reload(pwmn_cnt_max_reload_t cnt_max_reload);
void pwmn_set_nth_start_reload(pwmn_nth_start_reload_t nth_start_reload);
void pwmn_set_dead_time_reload(pwmn_dead_time_reload_t dead_time_reload);
void pwmn_set_pwm_cfg(pwmn_pwm_cfg_t cfg, u8 nr);
void pwmn_set_pwm_c0(pwmn_pwm_c_t c0, u8 nr);
void pwmn_set_pwm_c1(pwmn_pwm_c_t c1, u8 nr);
void pwmn_set_pwm_on(pwmn_pwm_on_t on, u8 nr);
void pwmn_set_pwm_c0_reload(pwmn_pwm_c_reload_t c0_reload, u8 nr);
void pwmn_set_pwm_c1_reload(pwmn_pwm_c_reload_t c1_reload, u8 nr);
void pwmn_set_pwm_on_reload(pwmn_pwm_on_reload_t on_reload, u8 nr);
void pwmn_set_pwm_on_reload_all(pwmn_pwm_on_reload_t on_reload);
void pwmn_set_irq_status_reg(pwmn_irq_status_t irq_status);
void pwmn_set_irq_mask(pwmn_irq_mask_t irq_mask);
void pwmn_set_irq_venable(pwmn_irq_venable_t irq_venable);
void pwmn_set_irq_vdisable(pwmn_irq_venable_t irq_disable);
void pwmn_set_irq_vmax(pwmn_irq_vmax_t irq_vmax);
void pwmn_set_irq_vno(pwmn_irq_vno_t irq_vno);

void pwmn_set_cfg_u16(u16 cfg);
void pwmn_set_cmd_u16(u16 cmd);
void pwmn_set_cnt_u16(u16 cnt);
void pwmn_set_prescaler_u16(u16 prescaler);
void pwmn_set_cnt_max_u16(u16 cnt_max);
void pwmn_set_nth_start_u16(u16 nth_start);
void pwmn_set_dead_time_u16(u16 dead_time);
void pwmn_set_prescaler_reload_u16(u16 prescaler_reload);
void pwmn_set_cnt_max_reload_u16(u16 cnt_max_reload);
void pwmn_set_nth_start_reload_u16(u16 nth_start_reload);
void pwmn_set_dead_time_reload_u16(u16 dead_time_reload);
void pwmn_set_pwm_cfg_u16(u16 cfg, u8 nr);
void pwmn_set_pwm_c0_u16(u16 c0, u8 nr);
void pwmn_set_pwm_c1_u16(u16 c1, u8 nr);
void pwmn_set_pwm_on_u16(u16, u8 nr);
void pwmn_set_pwm_c0_reload_u16(u16 c0_reload, u8 nr);
void pwmn_set_pwm_c1_reload_u16(u16 c1_reload, u8 nr);
void pwmn_set_pwm_on_reload_u16(u16 on_reload, u8 nr);
void pwmn_set_irq_status_u16_reg(u16 irq_status);
void pwmn_set_irq_mask_u16(u16 irq_mask);
void pwmn_set_irq_venable_u16(u16 irq_venable);
void pwmn_set_irq_vdisable_u16(u16 irq_disable);
void pwmn_set_irq_vmax_u16(u16 irq_vmax);
void pwmn_set_irq_vno_u16(u16 irq_vno);

// GETTER
pwmn_cfg_t pwmn_get_cfg(void);
pwmn_state_t pwmn_get_state(void);
pwmn_cnt_restart_t pwmn_get_cnt_restart(void);
pwmn_cnt_t pwmn_get_cnt(void);
pwmn_pwm_phase_t pwmn_get_pwm_phase(void);
pwmn_prescaler_t pwmn_get_prescaler(void);
pwmn_cnt_max_t pwmn_get_cnt_max(void);
pwmn_nth_start_t pwmn_get_nth_start(void);
pwmn_dead_time_t pwmn_get_dead_time(void);
pwmn_prescaler_reload_t pwmn_get_prescaler_reload(void);
pwmn_cnt_max_reload_t pwmn_get_cnt_max_reload(void);
pwmn_nth_start_reload_t pwmn_get_nth_start_reload(void);
pwmn_dead_time_reload_t pwmn_get_dead_time_reload(void);
pwmn_pwm_cfg_t pwmn_get_pwm_cfg(u8 nr);
pwmn_pwm_c_t pwmn_get_pwm_c0(u8 nr);
pwmn_pwm_c_t pwmn_get_pwm_c1(u8 nr);
pwmn_pwm_on_t pwmn_get_pwm_on(u8 nr);
pwmn_pwm_c_reload_t pwmn_get_pwm_c0_reload(u8 nr);
pwmn_pwm_c_reload_t pwmn_get_pwm_c1_reload(u8 nr);
pwmn_pwm_on_reload_t pwmn_get_pwm_on_reload(u8 nr);
pwmn_irq_status_t pwmn_get_irq_status_reg(void);
pwmn_irq_mask_t pwmn_get_irq_mask(void);
pwmn_irq_vmax_t pwmn_get_irq_vmax(void);
pwmn_irq_vno_t pwmn_get_irq_vno(void);

u16 pwmn_get_cfg_u16(void);
u16 pwmn_get_state_u16(void);
u16 pwmn_get_cnt_restart_u16(void);
u16 pwmn_get_cnt_u16(void);
u16 pwmn_get_pwm_phase_u16(void);
u16 pwmn_get_prescaler_u16(void);
u16 pwmn_get_cnt_max_u16(void);
u16 pwmn_get_nth_start_u16(void);
u16 pwmn_get_dead_time_u16(void);
u16 pwmn_get_prescaler_reload_u16(void);
u16 pwmn_get_cnt_max_reload_u16(void);
u16 pwmn_get_nth_start_reload_u16(void);
u16 pwmn_get_dead_time_reload_u16(void);
u16 pwmn_get_pwm_cfg_u16(u8 nr);
u16 pwmn_get_pwm_c0_u16(u8 nr);
u16 pwmn_get_pwm_c1_u16(u8 nr);
u16 pwmn_get_pwm_on_u16(u8 nr);
u16 pwmn_get_pwm_c0_reload_u16(u8 nr);
u16 pwmn_get_pwm_c1_reload_u16(u8 nr);
u16 pwmn_get_pwm_on_reload_u16(u8 nr);
u16 pwmn_get_irq_status_u16_reg(void);
u16 pwmn_get_irq_mask_u16(void);
u16 pwmn_get_irq_vmax_u16(void);
u16 pwmn_get_irq_vno_u16(void);

void pwmn_reset_to_default(void);
void pwmn_reset_to_default_irq_regs(void);

void pwmn_start();
void pwmn_stop();
void pwmn_restart(void);
void pwmn_restart_stop(void);
void pwmn_clear_oc(void);

//------------------------
// used by pre_pwm
void pwmn_enable(u8 nr);

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

void pwmn_handler_init(void);
void pwmn_handler_register(pwmn_irq_t irq, callback_t callback);
void pwmn_enable_irq(pwmn_irq_t irq, bool enable);
pwmn_irq_status_t pwmn_get_irq_status_reg(void);
void pwmn_clear_all_irq_events(void);

#define pwmn_handler_register(irq, cb) irq_handler_register(VIC_IRQ_PWMN, irq, cb);

#define pwmn_enable_irq(irq, en)                                                                                       \
  {                                                                                                                    \
    if (en)                                                                                                            \
      irq_enable(VIC_IRQ_PWMN, irq);                                                                                   \
    else                                                                                                               \
      irq_disable(VIC_IRQ_PWMN, irq);                                                                                  \
  }

#define pwmn_get_irq_status() ((pwmn_irq_status_t)(unsigned short)irq_get_status(VIC_IRQ_PWMN))

#define pwmn_clear_all_irq_events() irq_clear_all_events(VIC_IRQ_PWMN)

#endif /* __PWMN_H__ */
