#include "sys_state.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void sys_state_module_enable(sst_mod_enable_t modules, bool enable)
{
  uint16_t module_enable_tmp;

  module_enable_tmp = READ_REG_U16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_MODULE_ENABLE);
  if (enable)
  {
    module_enable_tmp |= modules;
  }
  else
  {
    module_enable_tmp &= ~modules;
  }
  WRITE_REG_16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_MODULE_ENABLE, module_enable_tmp);
}

void sys_state_set_sys_clk(sst_clk_sel_t sel)
{
  sys_state_control_t sys_state_control;

  sys_state_control.val = READ_REG_U16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_CONTROL);
  sys_state_control.bf.sys_clk_sel = sel;
  WRITE_REG_16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_CONTROL, sys_state_control.val);
}

void sys_state_use_adc_clk_shifted(bool use_shifted)
{
  sys_state_sys_clk_config_t sys_clk_config;

  sys_clk_config.val = READ_REG_U16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_SYS_CLK_CONFIG);
  sys_clk_config.bf.adc_clk_phase = use_shifted ? 1 : 0;
  WRITE_REG_16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_SYS_CLK_CONFIG, sys_clk_config.val);
}

void sys_state_adc_clk_delay(uint8_t delay)
{
  sys_state_sys_clk_config_t sys_clk_config;

  sys_clk_config.val = READ_REG_U16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_SYS_CLK_CONFIG);
  if (delay <= 21)
  {
    sys_clk_config.bf.sys_clk_delay = delay;
  }
  WRITE_REG_16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_SYS_CLK_CONFIG, sys_clk_config.val);
}

void sys_state_set_drv_strength(bool strong)
{
  sys_state_control_t sys_state_control;

  sys_state_control.val = READ_REG_U16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_CONTROL);
  sys_state_control.bf.drv_strength = strong ? 1 : 0;
  WRITE_REG_16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_CONTROL, sys_state_control.val);
}

void sys_state_set_target_clk(uint8_t clk_l, uint8_t clk_h)
{
  sys_state_control_t sys_state_control;

  sys_state_control.val = READ_REG_U16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_CONTROL);
  sys_state_control.bf.target_clk_l = clk_l;
  sys_state_control.bf.target_clk_h = clk_h;
  WRITE_REG_16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_CONTROL, sys_state_control.val);
}

uint16_t sys_state_get_reset_status(void)
{
  return READ_REG_U16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_RESET_STATUS);
}

void sys_state_clear_reset_status(void)
{
  WRITE_REG_16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_RESET_STATUS_CLEAR, 1);
}

void sys_state_reset_enable(sst_reset_enable_t resets)
{
  WRITE_REG_16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_RESET_ENABLE, resets);
}

void sys_state_software_reset(void)
{
  WRITE_REG_16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_SW_RESET, BIT_SYS_STATE_SW_RESET_SW_RESET);
}

void sys_state_set_calibration(uint8_t vref, uint8_t bgap, uint8_t sys_osc)
{
  sys_state_calibration_t sys_state_calibration;

  sys_state_calibration.val = 0;
  sys_state_calibration.bf.cal_vref = vref;
  sys_state_calibration.bf.cal_bgap = bgap;
  sys_state_calibration.bf.cal_sys_osc = sys_osc;
  WRITE_REG_16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_CALIBRATION, sys_state_calibration.val);
}

void sys_state_set_calibration_lock(void)
{
  WRITE_REG_16(BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_CALIBRATION_LOCK, 1);
}

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

#include "vic.h"
#include "vic_irq.h"

volatile static callback_t callback[SYS_STATE_NUM_IRQS];

void sys_state_handler_init(void)
{

  irq_handler_init(VIC_IRQ_SYS_STATE, SYS_STATE_NUM_IRQS, (callback_t *)callback,
                   BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_IRQ_VENABLE);
}
