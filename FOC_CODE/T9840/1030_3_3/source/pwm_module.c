#include "api.h"

#include "commons.h"
#include "main.h"
#include "pwm_module.h"

/**
 * @addtogroup PWM PRE-PWM&PWM module
 * @ingroup OTHER
 *
 * @{
 */

void activate_pre_pwm_float_control(u8 nr, bool enable)
{
  pwmn_pwm_cfg_t pwm_cfg;
  switch (nr)
  {
  case 0:
    pwm_cfg.val = REG_PWMN_PWM0_CFG;
    break;
  case 1:
    pwm_cfg.val = REG_PWMN_PWM1_CFG;
    break;
  case 02:
    pwm_cfg.val = REG_PWMN_PWM2_CFG;
    break;
  default:
    break;
  }

  pwm_cfg.bf.on_src = enable;

  switch (nr)
  {
  case 0:
    REG_PWMN_PWM0_CFG = pwm_cfg.val;
    break;
  case 1:
    REG_PWMN_PWM1_CFG = pwm_cfg.val;
    break;
  case 2:
    REG_PWMN_PWM2_CFG = pwm_cfg.val;
    break;
  default:
    break;
  }
}

void pwm_init(u8 cnt_mode, u8 deadtime_mode, u8 deadtime)
{

  // SET_PWM_CFG
  pwmn_cfg_t pwm_reg_cfg;
  pwm_reg_cfg.bf.cnt_mode = cnt_mode;
  pwm_reg_cfg.bf.middle_rl = 0; // PWM period middle channel register reload enable
  /*
  0 : only rising edge of PS is delayed
  1 : rising and falling edge of PS are delayed
  */
  pwm_reg_cfg.bf.dead_time_mode = deadtime_mode;
  pwm_reg_cfg.bf.oc_asyn_en = 0x1;     // asynchronous overcurrent PWM signal masking enable
  pwm_reg_cfg.bf.oc_syn_en = 0x0;      // synchronous overcurrent evaluation enable
  pwm_reg_cfg.bf.oc_intf = 0x0;        // synchronous overcurrent evaluation integral
                                       // filter threshold value configuration
  pwm_reg_cfg.bf.restart_en = 0x1;     // this configuration bit is not evaluated in hardware
  pwm_reg_cfg.bf.restart_cap_en = 0x1; // this configuration bit is not evaluated in hardware
  /*
  0 : generate dead time events only when PS does not have 0% or 100% duty cycle
  1 : generate dead time events independent from PS duty cycle
  */
  pwm_reg_cfg.bf.dt_evt_continue = 0x1;
  WRITE_REG_16(AADDR_PWMN_CFG, pwm_reg_cfg.val);

  // SET PWMN_DEAD_TIME & PWMN_DEAD_TIME_RELOAD
  pwmn_dead_time_t pwm_reg_dead_time;
  pwmn_dead_time_reload_t pwm_reg_dead_time_reload;
  pwm_reg_dead_time = deadtime;
  pwm_reg_dead_time_reload = deadtime;
  WRITE_REG_16(AADDR_PWMN_DEAD_TIME, pwm_reg_dead_time);
  WRITE_REG_16(AADDR_PWMN_DEAD_TIME_RELOAD, pwm_reg_dead_time_reload);

  REG_PWMN_CNT_MAX_RELOAD = C_PWM_CNT_MAX;

  pwmn_pwm_cfg_t pwm_reg_pwmx_cfg;
  pwm_reg_pwmx_cfg.val = 0;
  /*
  00 : register update by software only
  01 : PWM0_C0_RELOAD register can also be updated by PRE_PWM module
  10 : PWM0_C1_RELOAD register can also be updated by PRE_PWM module
  Note: The combination 11 is invalid
  */
  pwm_reg_pwmx_cfg.bf.c_src = 1;
  WRITE_REG_16(AADDR_PWMN_PWM0_CFG, pwm_reg_pwmx_cfg.val);
  WRITE_REG_16(AADDR_PWMN_PWM1_CFG, pwm_reg_pwmx_cfg.val);
  WRITE_REG_16(AADDR_PWMN_PWM2_CFG, pwm_reg_pwmx_cfg.val);
  WRITE_REG_16(AADDR_PWMN_PWM3_CFG, pwm_reg_pwmx_cfg.val);

  pwmn_pwm_on_reload_t pwm_reg_pwmx_on_reload;
  pwm_reg_pwmx_on_reload.val = 0;
  pwm_reg_pwmx_on_reload.bf.ls = 0x1;
  pwm_reg_pwmx_on_reload.bf.hs = 0x1;
  WRITE_REG_16(AADDR_PWMN_PWM0_ON_RELOAD, pwm_reg_pwmx_on_reload.val);
  WRITE_REG_16(AADDR_PWMN_PWM1_ON_RELOAD, pwm_reg_pwmx_on_reload.val);
  WRITE_REG_16(AADDR_PWMN_PWM2_ON_RELOAD, pwm_reg_pwmx_on_reload.val);
  WRITE_REG_16(AADDR_PWMN_PWM3_ON_RELOAD, pwm_reg_pwmx_on_reload.val);

  // START PWMN
  pwmn_cmd_t pwm_reg_cmd;
  pwm_reg_cmd.val = 0;
  pwm_reg_cmd.bf.run = 0x1;
  WRITE_REG_16(AADDR_PWMN_CMD, pwm_reg_cmd.val);
}

void pre_pwm_control_on_duty(bool on, bool duty)
{

  pwmn_pwm_cfg_t pwmn_pwm_cfg_0;
  pwmn_pwm_cfg_0.val = READ_REG_U16(AADDR_PWMN_PWM0_CFG);

  pwmn_pwm_cfg_0.bf.on_src = on;
  pwmn_pwm_cfg_0.bf.c_src = duty;
  WRITE_REG_16(AADDR_PWMN_PWM0_CFG, pwmn_pwm_cfg_0.val);
  WRITE_REG_16(AADDR_PWMN_PWM1_CFG, pwmn_pwm_cfg_0.val);
  WRITE_REG_16(AADDR_PWMN_PWM2_CFG, pwmn_pwm_cfg_0.val);
}

void pre_pwm_control(bool set)
{
  pre_pwm_control_on_duty(set, set);
}

void enable_pwm(u8 val)
{
  WRITE_REG_16(AADDR_PWMN_PWM0_ON_RELOAD, val);
  WRITE_REG_16(AADDR_PWMN_PWM1_ON_RELOAD, val);
  WRITE_REG_16(AADDR_PWMN_PWM2_ON_RELOAD, val);
}

void wait_next_cycle(void)
{
  while (!(REG_PWMN_IRQ_STATUS & (BIT_PWMN_IRQ_STATUS_START_EVT)))
  {
  };
  REG_PWMN_IRQ_STATUS = BIT_PWMN_IRQ_STATUS_START_EVT;
}

/** @} */
