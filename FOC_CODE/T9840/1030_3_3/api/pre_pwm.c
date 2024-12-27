
#include "pre_pwm.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void pre_pwm_set_cfg(pre_pwm_cfg_t cfg)
{
  WRITE_REG_16(AADDR_PRE_PWM_CFG, cfg.val);
}

pre_pwm_cfg_t pre_pwm_get_cfg(void)
{
  pre_pwm_cfg_t cfg;
  cfg.val = READ_REG_U16(AADDR_PRE_PWM_CFG);
  return cfg;
}

void pre_pwm_set_bp_max(pre_pwm_bp_max_t bp_max)
{
  WRITE_REG_16(AADDR_PRE_PWM_BP_MAX, bp_max);
}

pre_pwm_bp_max_t pre_pwm_get_bp_max(void)
{
  return (pre_pwm_bp_max_t)READ_REG_U16(AADDR_PRE_PWM_BP_MAX);
}

void pre_pwm_set_addr_base(pre_pwm_addr_base_t addr_base)
{
  WRITE_REG_16(AADDR_PRE_PWM_ADDR_BASE, addr_base);
}

pre_pwm_addr_base_t pre_pwm_get_addr_base(void)
{
  return (pre_pwm_addr_base_t)READ_REG_U16(AADDR_PRE_PWM_ADDR_BASE);
}

void pre_pwm_set_cmd(pre_pwm_cmd_t cmd)
{
  WRITE_REG_16(AADDR_PRE_PWM_CMD, cmd.val);
}

void pre_pwm_set_acc(pre_pwm_acc_t acc)
{
  WRITE_REG_16(AADDR_PRE_PWM_ACC, acc);
}

pre_pwm_acc_t pre_pwm_get_acc(void)
{
  return (pre_pwm_acc_t)READ_REG_U16(AADDR_PRE_PWM_ACC);
}

void pre_pwm_set_base_phase(pre_pwm_base_phase_t base_phase)
{
  WRITE_REG_16(AADDR_PRE_PWM_BASE_PHASE, base_phase);
}

pre_pwm_inc_t pre_pwm_get_base_phase(void)
{
  return (pre_pwm_base_phase_t)READ_REG_U16(AADDR_PRE_PWM_BASE_PHASE);
}

void pre_pwm_set_scale_offset(pre_pwm_scale_offset_t scale_offset, uint8_t nr)
{
  switch (nr)
  {
  case 0:
    WRITE_REG_16(AADDR_PRE_PWM_SCALE_OFFSET0, scale_offset);
    break;
  case 1:
    WRITE_REG_16(AADDR_PRE_PWM_SCALE_OFFSET1, scale_offset);
    break;
  }
}

pre_pwm_scale_offset_t pre_pwm_get_scale_offset(uint8_t nr)
{
  if (nr)
  {
    return (pre_pwm_scale_offset_t)READ_REG_U16(AADDR_PRE_PWM_SCALE_OFFSET1);
  }
  return (pre_pwm_scale_offset_t)READ_REG_U16(AADDR_PRE_PWM_SCALE_OFFSET0);
}

void pre_pwm_set_bp_sync0(pre_pwm_bp_sync_t bp_sync0)
{
  WRITE_REG_16(AADDR_PRE_PWM_BP_SYNC0, bp_sync0);
}

pre_pwm_bp_sync_t pre_pwm_get_bp_sync0(void)
{
  return (pre_pwm_bp_sync_t)READ_REG_U16(AADDR_PRE_PWM_BP_SYNC0);
}

void pre_pwm_set_bp_sync1(pre_pwm_bp_sync_t bp_sync1)
{
  WRITE_REG_16(AADDR_PRE_PWM_BP_SYNC1, bp_sync1);
}

pre_pwm_bp_sync_t pre_pwm_get_bp_sync1(void)
{
  return (pre_pwm_bp_sync_t)READ_REG_U16(AADDR_PRE_PWM_BP_SYNC1);
}

void pre_pwm_set_sync_en(pre_pwm_sync_en_t sync_en)
{
  WRITE_REG_16(AADDR_PRE_PWM_SYNC_EN, sync_en.val);
}

pre_pwm_sync_en_t pre_pwm_get_sync_en(void)
{
  pre_pwm_sync_en_t sync_en;
  sync_en.val = READ_REG_U16(AADDR_PRE_PWM_SYNC_EN);
  return sync_en;
}

void pre_pwm_set_sync_ext_cfg(pre_pwm_sync_ext_cfg_t sync_ext_cfg)
{
  WRITE_REG_16(AADDR_PRE_PWM_SYNC_EXT_CFG, sync_ext_cfg.val);
}

pre_pwm_sync_ext_cfg_t pre_pwm_get_sync_ext_cfg(void)
{
  pre_pwm_sync_ext_cfg_t sync_ext_cfg;
  sync_ext_cfg.val = READ_REG_U16(AADDR_PRE_PWM_SYNC_EXT_CFG);
  return sync_ext_cfg;
}

void pre_pwm_set_scale_sync(pre_pwm_scale_sync_t scale_sync)
{
  WRITE_REG_16(AADDR_PRE_PWM_SCALE_SYNC, scale_sync.val);
}

pre_pwm_scale_sync_t pre_pwm_get_scale_sync(void)
{
  pre_pwm_scale_sync_t scale_sync;
  scale_sync.val = READ_REG_U16(AADDR_PRE_PWM_SCALE_SYNC);
  return scale_sync;
}

void pre_pwm_set_inc_sync(pre_pwm_inc_sync_t inc_sync)
{
  WRITE_REG_16(AADDR_PRE_PWM_INC_SYNC, inc_sync);
}

pre_pwm_inc_sync_t pre_pwm_get_inc_sync(void)
{
  return (pre_pwm_inc_sync_t)READ_REG_U16(AADDR_PRE_PWM_INC_SYNC);
}

void pre_pwm_set_addr(pre_pwm_addr_t addr, uint8_t nr)
{
  switch (nr)
  {
  case 0:
    WRITE_REG_16(AADDR_PRE_PWM_U_ADDR, addr);
    break;
  case 1:
    WRITE_REG_16(AADDR_PRE_PWM_V_ADDR, addr);
    break;
  case 2:
    WRITE_REG_16(AADDR_PRE_PWM_W_ADDR, addr);
    break;
  }
}

void pre_pwm_set_current(pre_pwm_lw_t lw, pre_pwm_hw_t hw, uint8_t nr)
{
  switch (nr)
  {
  case 0:
    WRITE_REG_16(AADDR_PRE_PWM_U_LW, lw.val);
    WRITE_REG_16(AADDR_PRE_PWM_U_HW, hw.val);
    break;
  case 1:
    WRITE_REG_16(AADDR_PRE_PWM_V_LW, lw.val);
    WRITE_REG_16(AADDR_PRE_PWM_V_HW, hw.val);
    break;
  case 2:
    WRITE_REG_16(AADDR_PRE_PWM_W_LW, lw.val);
    WRITE_REG_16(AADDR_PRE_PWM_W_HW, hw.val);
    break;
  }
}

void pre_pwm_set_reload(pre_pwm_lw_rld_t lw_rld, pre_pwm_hw_rld_t hw_rld, uint8_t nr)
{
  switch (nr)
  {
  case 0:
    WRITE_REG_16(AADDR_PRE_PWM_U_LW_RLD, lw_rld.val);
    WRITE_REG_16(AADDR_PRE_PWM_U_HW_RLD, hw_rld.val);
    break;
  case 1:
    WRITE_REG_16(AADDR_PRE_PWM_V_LW_RLD, lw_rld.val);
    WRITE_REG_16(AADDR_PRE_PWM_V_HW_RLD, hw_rld.val);
    break;
  case 2:
    WRITE_REG_16(AADDR_PRE_PWM_W_LW_RLD, lw_rld.val);
    WRITE_REG_16(AADDR_PRE_PWM_W_HW_RLD, hw_rld.val);
    break;
  }
}

pre_pwm_addr_t pre_pwm_get_addr(uint8_t nr)
{
  switch (nr)
  {
  case 0:
    return (pre_pwm_addr_t)READ_REG_U16(AADDR_PRE_PWM_U_ADDR);
    break;
  case 1:
    return (pre_pwm_addr_t)READ_REG_U16(AADDR_PRE_PWM_V_ADDR);
    break;
  case 2:
    return (pre_pwm_addr_t)READ_REG_U16(AADDR_PRE_PWM_W_ADDR);
    break;
  }
  return 0;
}

void pre_pwm_get_current(pre_pwm_lw_t *lw, pre_pwm_hw_t *hw, uint8_t nr)
{
  switch (nr)
  {
  case 0:
    (*lw).val = READ_REG_U16(AADDR_PRE_PWM_U_LW);
    (*hw).val = READ_REG_U16(AADDR_PRE_PWM_U_HW);
    break;
  case 1:
    (*lw).val = READ_REG_U16(AADDR_PRE_PWM_V_LW);
    (*hw).val = READ_REG_U16(AADDR_PRE_PWM_V_HW);
    break;
  case 2:
    (*lw).val = READ_REG_U16(AADDR_PRE_PWM_W_LW);
    (*hw).val = READ_REG_U16(AADDR_PRE_PWM_W_HW);
    break;
  }
}

void pre_pwm_get_reload(pre_pwm_lw_rld_t *lw_rld, pre_pwm_hw_rld_t *hw_rld, uint8_t nr)
{
  switch (nr)
  {
  case 0:
    (*lw_rld).val = READ_REG_U16(AADDR_PRE_PWM_U_LW_RLD);
    (*hw_rld).val = READ_REG_U16(AADDR_PRE_PWM_U_HW_RLD);
    break;
  case 1:
    (*lw_rld).val = READ_REG_U16(AADDR_PRE_PWM_V_LW_RLD);
    (*hw_rld).val = READ_REG_U16(AADDR_PRE_PWM_V_HW_RLD);
    break;
  case 2:
    (*lw_rld).val = READ_REG_U16(AADDR_PRE_PWM_W_LW_RLD);
    (*hw_rld).val = READ_REG_U16(AADDR_PRE_PWM_W_HW_RLD);
    break;
  }
}

void pre_pwm_set_irq_mask(pre_pwm_irq_mask_t irq_mask)
{
  WRITE_REG_16(AADDR_PRE_PWM_IRQ_MASK, irq_mask);
}

pre_pwm_irq_mask_t pre_pwm_get_irq_mask(void)
{
  return (pre_pwm_irq_mask_t)READ_REG_U16(AADDR_PRE_PWM_IRQ_MASK);
}

// void pre_pwm_test_enable_all_irqs(void) {
//  pre_pwm_enable_irq(PRE_PWM_IRQ_BPS0_EVT        , true);
//  pre_pwm_enable_irq(PRE_PWM_IRQ_BPS1_EVT        , false);
//  pre_pwm_enable_irq(PRE_PWM_IRQ_U_RELOAD_EVT    , false);
//  pre_pwm_enable_irq(PRE_PWM_IRQ_V_RELOAD_EVT    , false);
//  pre_pwm_enable_irq(PRE_PWM_IRQ_W_RELOAD_EVT    , false);
//  pre_pwm_enable_irq(PRE_PWM_IRQ_RELOAD_ERROR_EVT, false);
//  pre_pwm_enable_irq(PRE_PWM_IRQ_U_DMA_RDY       , false);
//  pre_pwm_enable_irq(PRE_PWM_IRQ_V_DMA_RDY       , false);
//  pre_pwm_enable_irq(PRE_PWM_IRQ_W_DMA_RDY       , false);
//  //pre_pwm_clear_all_irq_events();
//}

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

#include "vic.h"
#include "vic_irq.h"

volatile static callback_t callback[PRE_PWM_NUM_IRQS];

void pre_pwm_handler_init(void)
{

  irq_handler_init(VIC_IRQ_PRE_PWM, PRE_PWM_NUM_IRQS, (callback_t *)callback,
                   BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_IRQ_VENABLE);
}
