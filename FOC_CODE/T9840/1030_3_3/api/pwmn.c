
#ifndef DPI

#include "pwmn.h"
#include "types.h"

// from "mac.c" uint16_t for WRITE_REG_16
// typedef unsigned long long uint64_t;
// typedef unsigned long      uint32_t;
// typedef unsigned short     uint16_t;

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

// SETTER

void pwmn_set_cfg(pwmn_cfg_t cfg)
{
  WRITE_REG_16(AADDR_PWMN_CFG, cfg.val);
}

void pwmn_set_cmd(pwmn_cmd_t cmd)
{
  WRITE_REG_16(AADDR_PWMN_CMD, cmd.val);
}

void pwmn_set_cnt(pwmn_cnt_t cnt)
{
  WRITE_REG_16(AADDR_PWMN_CNT, cnt);
}

void pwmn_set_prescaler(pwmn_prescaler_t prescaler)
{
  WRITE_REG_16(AADDR_PWMN_PRESCALER, prescaler);
}

void pwmn_set_cnt_max(pwmn_cnt_max_t cnt_max)
{
  WRITE_REG_16(AADDR_PWMN_CNT_MAX, cnt_max);
}

void pwmn_set_nth_start(pwmn_nth_start_t nth_start)
{
  WRITE_REG_16(AADDR_PWMN_NTH_START, nth_start);
}

void pwmn_set_dead_time(pwmn_dead_time_t dead_time)
{
  WRITE_REG_16(AADDR_PWMN_DEAD_TIME, dead_time);
}

void pwmn_set_prescaler_reload(pwmn_prescaler_reload_t prescaler_reload)
{
  WRITE_REG_16(AADDR_PWMN_PRESCALER_RELOAD, prescaler_reload);
}

void pwmn_set_cnt_max_reload(pwmn_cnt_max_reload_t cnt_max_reload)
{
  WRITE_REG_16(AADDR_PWMN_CNT_MAX_RELOAD, cnt_max_reload);
}

void pwmn_set_nth_start_reload(pwmn_nth_start_reload_t nth_start_reload)
{
  WRITE_REG_16(AADDR_PWMN_NTH_START_RELOAD, nth_start_reload);
}

void pwmn_set_dead_time_reload(pwmn_dead_time_reload_t dead_time_reload)
{
  WRITE_REG_16(AADDR_PWMN_DEAD_TIME_RELOAD, dead_time_reload);
}

void pwmn_set_pwm_cfg(pwmn_pwm_cfg_t cfg, u8 nr)
{
  switch (nr)
  {
  case 0:
    WRITE_REG_16(AADDR_PWMN_PWM0_CFG, cfg.val);
    break;
  case 1:
    WRITE_REG_16(AADDR_PWMN_PWM1_CFG, cfg.val);
    break;
  case 2:
    WRITE_REG_16(AADDR_PWMN_PWM2_CFG, cfg.val);
    break;
  case 3:
    WRITE_REG_16(AADDR_PWMN_PWM3_CFG, cfg.val);
    break;
  }
}

void pwmn_set_pwm_c0(pwmn_pwm_c_t c0, u8 nr)
{
  switch (nr)
  {
  case 0:
    WRITE_REG_16(AADDR_PWMN_PWM0_C0, c0);
    break;
  case 1:
    WRITE_REG_16(AADDR_PWMN_PWM1_C0, c0);
    break;
  case 2:
    WRITE_REG_16(AADDR_PWMN_PWM2_C0, c0);
    break;
  case 3:
    WRITE_REG_16(AADDR_PWMN_PWM3_C0, c0);
    break;
  }
}

void pwmn_set_pwm_c1(pwmn_pwm_c_t c1, u8 nr)
{
  switch (nr)
  {
  case 0:
    WRITE_REG_16(AADDR_PWMN_PWM0_C1, c1);
    break;
  case 1:
    WRITE_REG_16(AADDR_PWMN_PWM1_C1, c1);
    break;
  case 2:
    WRITE_REG_16(AADDR_PWMN_PWM2_C1, c1);
    break;
  case 3:
    WRITE_REG_16(AADDR_PWMN_PWM3_C1, c1);
    break;
  }
}

void pwmn_set_pwm_on(pwmn_pwm_on_t on, u8 nr)
{
  switch (nr)
  {
  case 0:
    WRITE_REG_16(AADDR_PWMN_PWM0_ON, on.val);
    break;
  case 1:
    WRITE_REG_16(AADDR_PWMN_PWM1_ON, on.val);
    break;
  case 2:
    WRITE_REG_16(AADDR_PWMN_PWM2_ON, on.val);
    break;
  case 3:
    WRITE_REG_16(AADDR_PWMN_PWM3_ON, on.val);
    break;
  }
}

void pwmn_set_pwm_c0_reload(pwmn_pwm_c_reload_t c0_reload, u8 nr)
{
  switch (nr)
  {
  case 0:
    WRITE_REG_16(AADDR_PWMN_PWM0_C0_RELOAD, c0_reload);
    break;
  case 1:
    WRITE_REG_16(AADDR_PWMN_PWM1_C0_RELOAD, c0_reload);
    break;
  case 2:
    WRITE_REG_16(AADDR_PWMN_PWM2_C0_RELOAD, c0_reload);
    break;
  case 3:
    WRITE_REG_16(AADDR_PWMN_PWM3_C0_RELOAD, c0_reload);
    break;
  }
}

void pwmn_set_pwm_c1_reload(pwmn_pwm_c_reload_t c1_reload, u8 nr)
{
  switch (nr)
  {
  case 0:
    WRITE_REG_16(AADDR_PWMN_PWM0_C1_RELOAD, c1_reload);
    break;
  case 1:
    WRITE_REG_16(AADDR_PWMN_PWM1_C1_RELOAD, c1_reload);
    break;
  case 2:
    WRITE_REG_16(AADDR_PWMN_PWM2_C1_RELOAD, c1_reload);
    break;
  case 3:
    WRITE_REG_16(AADDR_PWMN_PWM3_C1_RELOAD, c1_reload);
    break;
  }
}

void pwmn_set_pwm_on_reload(pwmn_pwm_on_reload_t on_reload, u8 nr)
{
  switch (nr)
  {
  case 0:
    WRITE_REG_16(AADDR_PWMN_PWM0_ON_RELOAD, on_reload.val);
    break;
  case 1:
    WRITE_REG_16(AADDR_PWMN_PWM1_ON_RELOAD, on_reload.val);
    break;
  case 2:
    WRITE_REG_16(AADDR_PWMN_PWM2_ON_RELOAD, on_reload.val);
    break;
  case 3:
    WRITE_REG_16(AADDR_PWMN_PWM3_ON_RELOAD, on_reload.val);
    break;
  }
}

void pwmn_set_pwm_on_reload_all(pwmn_pwm_on_reload_t on_reload)
{
  WRITE_REG_16(AADDR_PWMN_PWM0_ON_RELOAD, on_reload.val);
  WRITE_REG_16(AADDR_PWMN_PWM1_ON_RELOAD, on_reload.val);
  WRITE_REG_16(AADDR_PWMN_PWM2_ON_RELOAD, on_reload.val);
  WRITE_REG_16(AADDR_PWMN_PWM3_ON_RELOAD, on_reload.val);
}

void pwmn_set_irq_status_reg(pwmn_irq_status_t irq_status)
{
  WRITE_REG_16(AADDR_PWMN_IRQ_STATUS, irq_status.val);
}

void pwmn_set_irq_mask(pwmn_irq_mask_t irq_mask)
{
  WRITE_REG_16(AADDR_PWMN_IRQ_MASK, irq_mask);
}

void pwmn_set_irq_venable(pwmn_irq_venable_t irq_venable)
{
  WRITE_REG_16(AADDR_PWMN_IRQ_VENABLE, irq_venable);
}

void pwmn_set_irq_vdisable(pwmn_irq_vdisable_t irq_disable)
{
  WRITE_REG_16(AADDR_PWMN_IRQ_VENABLE, irq_disable);
}

void pwmn_set_irq_vmax(pwmn_irq_vmax_t irq_vmax)
{
  WRITE_REG_16(AADDR_PWMN_IRQ_VMAX, irq_vmax);
}

void pwmn_set_irq_vno(pwmn_irq_vno_t irq_vno)
{
  WRITE_REG_16(AADDR_PWMN_IRQ_VNO, irq_vno);
}

// GETTER

pwmn_cfg_t pwmn_get_cfg(void)
{
  pwmn_cfg_t cfg;
  cfg.val = READ_REG_U16(AADDR_PWMN_CFG);
  return cfg;
}

pwmn_state_t pwmn_get_state(void)
{
  pwmn_state_t state;
  state.val = READ_REG_U16(AADDR_PWMN_STATE);
  return state;
}

pwmn_cnt_restart_t pwmn_get_cnt_restart(void)
{
  return (pwmn_cnt_restart_t)READ_REG_U16(AADDR_PWMN_CNT_RESTART);
}

pwmn_cnt_t pwmn_get_cnt(void)
{
  return (pwmn_cnt_t)READ_REG_U16(AADDR_PWMN_CNT);
}

pwmn_pwm_phase_t pwmn_get_pwm_phase(void)
{
  return (pwmn_pwm_phase_t)READ_REG_U16(AADDR_PWMN_PWM_PHASE);
}

pwmn_prescaler_t pwmn_get_prescaler(void)
{
  return (pwmn_prescaler_t)READ_REG_U16(AADDR_PWMN_PRESCALER);
}

pwmn_cnt_max_t pwmn_get_cnt_max(void)
{
  return (pwmn_cnt_max_t)READ_REG_U16(AADDR_PWMN_CNT_MAX);
}

pwmn_nth_start_t pwmn_get_nth_start(void)
{
  return (pwmn_nth_start_t)READ_REG_U16(AADDR_PWMN_NTH_START);
}

pwmn_dead_time_t pwmn_get_dead_time(void)
{
  return (pwmn_dead_time_t)READ_REG_U16(AADDR_PWMN_DEAD_TIME);
}

pwmn_prescaler_reload_t pwmn_get_prescaler_reload(void)
{
  return (pwmn_prescaler_reload_t)READ_REG_U16(AADDR_PWMN_PRESCALER_RELOAD);
}

pwmn_cnt_max_reload_t pwmn_get_cnt_max_reload(void)
{
  return (pwmn_cnt_max_reload_t)READ_REG_U16(AADDR_PWMN_CNT_MAX_RELOAD);
}

pwmn_nth_start_reload_t pwmn_get_nth_start_reload(void)
{
  return (pwmn_nth_start_reload_t)READ_REG_U16(AADDR_PWMN_NTH_START_RELOAD);
}

pwmn_dead_time_reload_t pwmn_get_dead_time_reload(void)
{
  return (pwmn_dead_time_reload_t)READ_REG_U16(AADDR_PWMN_DEAD_TIME_RELOAD);
}

pwmn_pwm_cfg_t pwmn_get_pwm_cfg(u8 nr)
{
  pwmn_pwm_cfg_t cfg;
  cfg.val = (u16)0;
  switch (nr)
  {
  case 0:
    cfg.val = READ_REG_U16(AADDR_PWMN_PWM0_CFG);
    break;
  case 1:
    cfg.val = READ_REG_U16(AADDR_PWMN_PWM1_CFG);
    break;
  case 2:
    cfg.val = READ_REG_U16(AADDR_PWMN_PWM2_CFG);
    break;
  case 3:
    cfg.val = READ_REG_U16(AADDR_PWMN_PWM3_CFG);
    break;
  }
  return cfg;
}

pwmn_pwm_c_t pwmn_get_pwm_c0(u8 nr)
{
  pwmn_pwm_c_t pwm_c = (u16)0;
  switch (nr)
  {
  case 0:
    pwm_c = (pwmn_pwm_c_t)READ_REG_U16(AADDR_PWMN_PWM0_C0);
    break;
  case 1:
    pwm_c = (pwmn_pwm_c_t)READ_REG_U16(AADDR_PWMN_PWM1_C0);
    break;
  case 2:
    pwm_c = (pwmn_pwm_c_t)READ_REG_U16(AADDR_PWMN_PWM2_C0);
    break;
  case 3:
    pwm_c = (pwmn_pwm_c_t)READ_REG_U16(AADDR_PWMN_PWM3_C0);
    break;
  }
  return pwm_c;
}

pwmn_pwm_c_t pwmn_get_pwm_c1(u8 nr)
{
  pwmn_pwm_c_t pwm_c = (u16)0;
  switch (nr)
  {
  case 0:
    pwm_c = (pwmn_pwm_c_t)READ_REG_U16(AADDR_PWMN_PWM0_C1);
    break;
  case 1:
    pwm_c = (pwmn_pwm_c_t)READ_REG_U16(AADDR_PWMN_PWM1_C1);
    break;
  case 2:
    pwm_c = (pwmn_pwm_c_t)READ_REG_U16(AADDR_PWMN_PWM2_C1);
    break;
  case 3:
    pwm_c = (pwmn_pwm_c_t)READ_REG_U16(AADDR_PWMN_PWM3_C1);
    break;
  }
  return pwm_c;
}

pwmn_pwm_on_t pwmn_get_pwm_on(u8 nr)
{
  pwmn_pwm_on_t pwm_on;
  pwm_on.val = (u16)0;
  switch (nr)
  {
  case 0:
    pwm_on.val = READ_REG_U16(AADDR_PWMN_PWM0_ON);
    break;
  case 1:
    pwm_on.val = READ_REG_U16(AADDR_PWMN_PWM1_ON);
    break;
  case 2:
    pwm_on.val = READ_REG_U16(AADDR_PWMN_PWM2_ON);
    break;
  case 3:
    pwm_on.val = READ_REG_U16(AADDR_PWMN_PWM3_ON);
    break;
  }
  return pwm_on;
}

pwmn_pwm_c_reload_t pwmn_get_pwm_c0_reload(u8 nr)
{
  pwmn_pwm_c_reload_t pwmn_c_reload = (u16)0;
  switch (nr)
  {
  case 0:
    pwmn_c_reload = (pwmn_pwm_c_reload_t)READ_REG_U16(AADDR_PWMN_PWM0_C0_RELOAD);
    break;
  case 1:
    pwmn_c_reload = (pwmn_pwm_c_reload_t)READ_REG_U16(AADDR_PWMN_PWM1_C0_RELOAD);
    break;
  case 2:
    pwmn_c_reload = (pwmn_pwm_c_reload_t)READ_REG_U16(AADDR_PWMN_PWM2_C0_RELOAD);
    break;
  case 3:
    pwmn_c_reload = (pwmn_pwm_c_reload_t)READ_REG_U16(AADDR_PWMN_PWM3_C0_RELOAD);
    break;
  }
  return pwmn_c_reload;
}

pwmn_pwm_c_reload_t pwmn_get_pwm_c1_reload(u8 nr)
{
  pwmn_pwm_c_reload_t pwm_c_reload = (u16)0;
  switch (nr)
  {
  case 0:
    pwm_c_reload = READ_REG_U16(AADDR_PWMN_PWM0_C1_RELOAD);
    break;
  case 1:
    pwm_c_reload = READ_REG_U16(AADDR_PWMN_PWM1_C1_RELOAD);
    break;
  case 2:
    pwm_c_reload = READ_REG_U16(AADDR_PWMN_PWM2_C1_RELOAD);
    break;
  case 3:
    pwm_c_reload = READ_REG_U16(AADDR_PWMN_PWM3_C1_RELOAD);
    break;
  }
  return pwm_c_reload;
}

pwmn_pwm_on_reload_t pwmn_get_pwm_on_reload(u8 nr)
{
  pwmn_pwm_on_reload_t pwm_on_reload;
  pwm_on_reload.val = (u16)0;
  switch (nr)
  {
  case 0:
    pwm_on_reload.val = READ_REG_U16(AADDR_PWMN_PWM0_ON_RELOAD);
    break;
  case 1:
    pwm_on_reload.val = READ_REG_U16(AADDR_PWMN_PWM1_ON_RELOAD);
    break;
  case 2:
    pwm_on_reload.val = READ_REG_U16(AADDR_PWMN_PWM2_ON_RELOAD);
    break;
  case 3:
    pwm_on_reload.val = READ_REG_U16(AADDR_PWMN_PWM3_ON_RELOAD);
    break;
  }
  return pwm_on_reload;
}

pwmn_irq_status_t pwmn_get_irq_status_reg(void)
{
  pwmn_irq_status_t irq_status;
  irq_status.val = READ_REG_U16(AADDR_PWMN_IRQ_MASK);
  return irq_status;
}

pwmn_irq_mask_t pwmn_get_irq_mask(void)
{
  return (pwmn_irq_mask_t)READ_REG_U16(AADDR_PWMN_IRQ_MASK);
}

pwmn_irq_vmax_t pwmn_get_irq_vmax(void)
{
  return (pwmn_irq_vmax_t)READ_REG_U16(AADDR_PWMN_IRQ_VMAX);
}

pwmn_irq_vno_t pwmn_get_irq_vno(void)
{
  return (pwmn_irq_vno_t)READ_REG_U16(AADDR_PWMN_IRQ_VNO);
}

// used by pre_pwm
void pwmn_enable(u8 nr)
{
  switch (nr)
  {
  case 0:
    WRITE_REG_16(AADDR_PWMN_PWM0_ON, 1);
    break;
  case 1:
    WRITE_REG_16(AADDR_PWMN_PWM1_ON, 1);
    break;
  case 2:
    WRITE_REG_16(AADDR_PWMN_PWM2_ON, 1);
    break;
  case 3:
    WRITE_REG_16(AADDR_PWMN_PWM3_ON, 1);
    break;
  }
}

// cast for u16 SETTER

void pwmn_set_cfg_u16(u16 cfg)
{
  pwmn_cfg_t tmp_cfg;
  tmp_cfg.val = cfg;
  pwmn_set_cfg(tmp_cfg);
}
void pwmn_set_cmd_u16(u16 cmd)
{
  pwmn_cmd_t tmp_cmd;
  tmp_cmd.val = cmd;
  pwmn_set_cmd(tmp_cmd);
}
void pwmn_set_cnt_u16(u16 cnt)
{
  pwmn_set_cnt((pwmn_cnt_t)cnt);
}
void pwmn_set_prescaler_u16(u16 prescaler)
{
  pwmn_set_prescaler((pwmn_prescaler_t)prescaler);
}
void pwmn_set_cnt_max_u16(u16 cnt_max)
{
  pwmn_set_cnt_max((pwmn_cnt_max_t)cnt_max);
}
void pwmn_set_nth_start_u16(u16 nth_start)
{
  pwmn_set_nth_start((pwmn_nth_start_t)nth_start);
}
void pwmn_set_dead_time_u16(u16 dead_time)
{
  pwmn_set_dead_time((pwmn_dead_time_t)dead_time);
}
void pwmn_set_prescaler_reload_u16(u16 prescaler_reload)
{
  pwmn_set_prescaler_reload((pwmn_prescaler_reload_t)prescaler_reload);
}
void pwmn_set_cnt_max_reload_u16(u16 cnt_max_reload)
{
  pwmn_set_cnt_max_reload((pwmn_cnt_max_reload_t)cnt_max_reload);
}
void pwmn_set_nth_start_reload_u16(u16 nth_start_reload)
{
  pwmn_set_nth_start_reload((pwmn_nth_start_reload_t)nth_start_reload);
}
void pwmn_set_dead_time_reload_u16(u16 dead_time_reload)
{
  pwmn_set_dead_time_reload((pwmn_dead_time_reload_t)dead_time_reload);
}
void pwmn_set_pwm_cfg_u16(u16 cfg, u8 nr)
{
  pwmn_pwm_cfg_t tmp_cfg;
  tmp_cfg.val = cfg;
  pwmn_set_pwm_cfg(tmp_cfg, nr);
}
void pwmn_set_pwm_c0_u16(u16 c0, u8 nr)
{
  pwmn_set_pwm_c0((pwmn_pwm_c_t)c0, nr);
}
void pwmn_set_pwm_c1_u16(u16 c1, u8 nr)
{
  pwmn_set_pwm_c1((pwmn_pwm_c_t)c1, nr);
}
void pwmn_set_pwm_on_u16(u16 on, u8 nr)
{
  pwmn_pwm_on_t tmp_on;
  tmp_on.val = on;
  pwmn_set_pwm_on(tmp_on, nr);
}
void pwmn_set_pwm_c0_reload_u16(u16 c0_reload, u8 nr)
{
  pwmn_set_pwm_c0_reload((pwmn_pwm_c_reload_t)c0_reload, nr);
}
void pwmn_set_pwm_c1_reload_u16(u16 c1_reload, u8 nr)
{
  pwmn_set_pwm_c1_reload((pwmn_pwm_c_reload_t)c1_reload, nr);
}
void pwmn_set_pwm_on_reload_u16(u16 on_reload, u8 nr)
{
  pwmn_pwm_on_reload_t tmp_on_reload;
  tmp_on_reload.val = on_reload;
  pwmn_set_pwm_on_reload(tmp_on_reload, nr);
}
void pwmn_set_irq_status_u16_reg(u16 irq_status)
{
  pwmn_irq_status_t tmp_irq_status;
  tmp_irq_status.val = irq_status;
  pwmn_set_irq_status_reg(tmp_irq_status);
}
void pwmn_set_irq_mask_u16(u16 irq_mask)
{
  pwmn_set_irq_mask((pwmn_irq_mask_t)irq_mask);
}
void pwmn_set_irq_venable_u16(u16 irq_venable)
{
  pwmn_set_irq_venable((pwmn_irq_venable_t)irq_venable);
}
void pwmn_set_irq_vdisable_u16(u16 irq_vdisable)
{
  pwmn_set_irq_vdisable((pwmn_irq_venable_t)irq_vdisable);
}
void pwmn_set_irq_vmax_u16(u16 irq_vmax)
{
  pwmn_set_irq_vmax((pwmn_irq_vmax_t)irq_vmax);
}
void pwmn_set_irq_vno_u16(u16 irq_vno)
{
  pwmn_set_irq_vno((pwmn_irq_vno_t)irq_vno);
}

// cast for u16 GETTER

u16 pwmn_get_cfg_u16(void)
{
  return (u16)pwmn_get_cfg().val;
}
u16 pwmn_get_state_u16(void)
{
  return (u16)pwmn_get_state().val;
}
u16 pwmn_get_cnt_restart_u16(void)
{
  return pwmn_get_cnt_restart();
}
u16 pwmn_get_cnt_u16(void)
{
  return pwmn_get_cnt();
}
u16 pwmn_get_pwm_phase_u16(void)
{
  return (u16)pwmn_get_pwm_phase();
}
u16 pwmn_get_prescaler_u16(void)
{
  return (u16)pwmn_get_prescaler();
}
u16 pwmn_get_cnt_max_u16(void)
{
  return (u16)pwmn_get_cnt_max();
}
u16 pwmn_get_nth_start_u16(void)
{
  return (u16)pwmn_get_nth_start();
}
u16 pwmn_get_dead_time_u16(void)
{
  return (u16)pwmn_get_dead_time();
}
u16 pwmn_get_prescaler_reload_u16(void)
{
  return (u16)pwmn_get_prescaler_reload();
}
u16 pwmn_get_cnt_max_reload_u16(void)
{
  return (u16)pwmn_get_prescaler_reload();
}
u16 pwmn_get_nth_start_reload_u16(void)
{
  return (u16)pwmn_get_nth_start_reload();
}
u16 pwmn_get_dead_time_reload_u16(void)
{
  return (u16)pwmn_get_nth_start_reload();
}

u16 pwmn_get_pwm_cfg_u16(u8 nr)
{
  return (u16)pwmn_get_pwm_cfg(nr).val;
}
u16 pwmn_get_pwm_c0_u16(u8 nr)
{
  return (u16)pwmn_get_pwm_c0(nr);
}
u16 pwmn_get_pwm_c1_u16(u8 nr)
{
  return (u16)pwmn_get_pwm_c1(nr);
}
u16 pwmn_get_pwm_on_u16(u8 nr)
{
  return (u16)pwmn_get_pwm_on(nr).val;
}
u16 pwmn_get_pwm_c0_reload_u16(u8 nr)
{
  return (u16)pwmn_get_pwm_c0_reload(nr);
}
u16 pwmn_get_pwm_c1_reload_u16(u8 nr)
{
  return (u16)pwmn_get_pwm_c1_reload(nr);
}
u16 pwmn_get_pwm_on_reload_u16(u8 nr)
{
  return (u16)pwmn_get_pwm_on_reload(nr).val;
}
u16 pwmn_get_irq_status_u16_reg(void)
{
  return (u16)pwmn_get_irq_status_reg().val;
}

u16 pwmn_get_irq_mask_u16(void)
{
  return (u16)pwmn_get_irq_mask();
}
u16 pwmn_get_irq_vmax_u16(void)
{
  return (u16)pwmn_get_irq_vmax();
}
u16 pwmn_get_irq_vno_u16(void)
{
  return (u16)pwmn_get_irq_vno();
}

void pwmn_reset_to_default(void)
{

  // not default to skip warnings
  pwmn_set_cnt_max_u16(333);
  pwmn_set_cnt_max_reload_u16(333);

  pwmn_set_cfg_u16(RES_PWMN_CFG);
  pwmn_set_cmd_u16(RES_PWMN_CMD);
  pwmn_set_cnt_u16(RES_PWMN_CNT);
  pwmn_set_prescaler_u16(RES_PWMN_PRESCALER);
  pwmn_set_nth_start_u16(RES_PWMN_NTH_START);
  pwmn_set_dead_time_u16(RES_PWMN_DEAD_TIME);
  pwmn_set_prescaler_reload_u16(RES_PWMN_PRESCALER_RELOAD);
  pwmn_set_nth_start_reload_u16(RES_PWMN_NTH_START_RELOAD);
  pwmn_set_dead_time_reload_u16(RES_PWMN_DEAD_TIME_RELOAD);

  int nr = 0;
  pwmn_set_pwm_cfg_u16(RES_PWMN_PWM0_CFG, nr);
  pwmn_set_pwm_c0_u16(RES_PWMN_PWM0_C0, nr);
  pwmn_set_pwm_c1_u16(RES_PWMN_PWM0_C1, nr);
  pwmn_set_pwm_on_u16(RES_PWMN_PWM0_ON, nr);
  pwmn_set_pwm_c0_reload_u16(RES_PWMN_PWM0_C0_RELOAD, nr);
  pwmn_set_pwm_c1_reload_u16(RES_PWMN_PWM0_C1_RELOAD, nr);
  pwmn_set_pwm_on_reload_u16(RES_PWMN_PWM0_ON_RELOAD, nr);
  nr = 1;
  pwmn_set_pwm_cfg_u16(RES_PWMN_PWM1_CFG, nr);
  pwmn_set_pwm_c0_u16(RES_PWMN_PWM1_C0, nr);
  pwmn_set_pwm_c1_u16(RES_PWMN_PWM1_C1, nr);
  pwmn_set_pwm_on_u16(RES_PWMN_PWM1_ON, nr);
  pwmn_set_pwm_c0_reload_u16(RES_PWMN_PWM1_C0_RELOAD, nr);
  pwmn_set_pwm_c1_reload_u16(RES_PWMN_PWM1_C1_RELOAD, nr);
  pwmn_set_pwm_on_reload_u16(RES_PWMN_PWM1_ON_RELOAD, nr);
  nr = 2;
  pwmn_set_pwm_cfg_u16(RES_PWMN_PWM2_CFG, nr);
  pwmn_set_pwm_c0_u16(RES_PWMN_PWM2_C0, nr);
  pwmn_set_pwm_c1_u16(RES_PWMN_PWM2_C1, nr);
  pwmn_set_pwm_on_u16(RES_PWMN_PWM2_ON, nr);
  pwmn_set_pwm_c0_reload_u16(RES_PWMN_PWM2_C0_RELOAD, nr);
  pwmn_set_pwm_c1_reload_u16(RES_PWMN_PWM2_C1_RELOAD, nr);
  pwmn_set_pwm_on_reload_u16(RES_PWMN_PWM2_ON_RELOAD, nr);
  nr = 3;
  pwmn_set_pwm_cfg_u16(RES_PWMN_PWM3_CFG, nr);
  pwmn_set_pwm_c0_u16(RES_PWMN_PWM3_C0, nr);
  pwmn_set_pwm_c1_u16(RES_PWMN_PWM3_C1, nr);
  pwmn_set_pwm_on_u16(RES_PWMN_PWM3_ON, nr);
  pwmn_set_pwm_c0_reload_u16(RES_PWMN_PWM3_C0_RELOAD, nr);
  pwmn_set_pwm_c1_reload_u16(RES_PWMN_PWM3_C1_RELOAD, nr);
  pwmn_set_pwm_on_reload_u16(RES_PWMN_PWM3_ON_RELOAD, nr);
}

void pwmn_reset_to_default_irq_regs(void)
{

  pwmn_set_irq_status_u16_reg(RES_PWMN_IRQ_STATUS);
  pwmn_set_irq_mask_u16(RES_PWMN_IRQ_MASK);
  pwmn_set_irq_venable_u16(RES_PWMN_IRQ_VENABLE);
  pwmn_set_irq_vdisable_u16(RES_PWMN_IRQ_VDISABLE);
  pwmn_set_irq_vmax_u16(RES_PWMN_IRQ_VMAX);
  // pwmn_set_irq_vno_u16(RES_PWMN_IRQ_VNO);
}

// cmd

void pwmn_start()
{
  WRITE_REG_16(AADDR_PWMN_CMD, 1);
}
void pwmn_stop()
{
  WRITE_REG_16(AADDR_PWMN_CMD, 0);
}
void pwmn_restart()
{
  WRITE_REG_16(AADDR_PWMN_CMD, 5);
}
void pwmn_restart_stop()
{
  WRITE_REG_16(AADDR_PWMN_CMD, 4);
}
void pwmn_clear_oc()
{
  WRITE_REG_16(AADDR_PWMN_CMD, 2);
}

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

#include "vic.h"
#include "vic_irq.h"

volatile static callback_t callback[PWMN_NUM_IRQS];

void pwmn_handler_init(void)
{

  irq_handler_init(VIC_IRQ_PWMN, PWMN_NUM_IRQS, (callback_t *)callback, BASE_ADDR_PWMN + ADDR_PWMN_IRQ_VENABLE);
}

#endif /* !DPI */
