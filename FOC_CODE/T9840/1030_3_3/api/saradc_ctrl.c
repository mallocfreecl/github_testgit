#include "saradc_ctrl.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void saradc_ctrl_set_cfg(saradc_ctrl_cfg_t cfg)
{
  WRITE_REG_16(AADDR_SARADC_CTRL_CFG, cfg.val);
}

saradc_ctrl_cfg_t saradc_ctrl_get_cfg(void)
{
  saradc_ctrl_cfg_t cfg;
  cfg.val = READ_REG_U16(AADDR_SARADC_CTRL_CFG);
  return cfg;
}

void saradc_ctrl_set_cfg_sar_timing(saradc_ctrl_cfg_sar_timing_t cfg_sar_timing)
{
  WRITE_REG_16(AADDR_SARADC_CTRL_CFG_SAR_TIMING, cfg_sar_timing.val);
}

saradc_ctrl_cfg_sar_timing_t saradc_ctrl_get_cfg_sar_timing(void)
{
  saradc_ctrl_cfg_sar_timing_t cfg_sar_timing;
  cfg_sar_timing.val = READ_REG_U16(AADDR_SARADC_CTRL_CFG_SAR_TIMING);
  return cfg_sar_timing;
}

void saradc_ctrl_set_dead_time_wait0(saradc_ctrl_dead_time_wait_t dead_time_wait)
{
  WRITE_REG_16(AADDR_SARADC_CTRL_DEAD_TIME_WAIT0, dead_time_wait);
}

void saradc_ctrl_set_dead_time_wait1(saradc_ctrl_dead_time_wait_t dead_time_wait)
{
  WRITE_REG_16(AADDR_SARADC_CTRL_DEAD_TIME_WAIT1, dead_time_wait);
}

void saradc_ctrl_set_dead_time_wait2(saradc_ctrl_dead_time_wait_t dead_time_wait)
{
  WRITE_REG_16(AADDR_SARADC_CTRL_DEAD_TIME_WAIT2, dead_time_wait);
}

saradc_ctrl_dead_time_wait_t saradc_ctrl_get_dead_time_wait0(void)
{
  return (saradc_ctrl_dead_time_wait_t)READ_REG_U16(AADDR_SARADC_CTRL_DEAD_TIME_WAIT0);
}

saradc_ctrl_dead_time_wait_t saradc_ctrl_get_dead_time_wait1(void)
{
  return (saradc_ctrl_dead_time_wait_t)READ_REG_U16(AADDR_SARADC_CTRL_DEAD_TIME_WAIT1);
}

saradc_ctrl_dead_time_wait_t saradc_ctrl_get_dead_time_wait2(void)
{
  return (saradc_ctrl_dead_time_wait_t)READ_REG_U16(AADDR_SARADC_CTRL_DEAD_TIME_WAIT2);
}

void saradc_ctrl_set_sync_out_cfg(saradc_ctrl_sync_out_cfg_t sync_out_cfg)
{
  WRITE_REG_16(AADDR_SARADC_CTRL_SYNC_OUT_CFG, sync_out_cfg.val);
}

saradc_ctrl_sync_out_cfg_t saradc_ctrl_get_sync_out_cfg(void)
{
  saradc_ctrl_sync_out_cfg_t sync_out_cfg;
  sync_out_cfg.val = READ_REG_U16(AADDR_SARADC_CTRL_SYNC_OUT_CFG);
  return sync_out_cfg;
}

void saradc_ctrl_set_sync_out_trig(saradc_ctrl_sync_out_trig_t sync_out_trig)
{
  WRITE_REG_16(AADDR_SARADC_CTRL_SYNC_OUT_TRIG, sync_out_trig);
}

saradc_ctrl_sync_out_trig_t saradc_ctrl_get_sync_out_trig(void)
{
  return (saradc_ctrl_sync_out_trig_t)READ_REG_U16(AADDR_SARADC_CTRL_SYNC_OUT_TRIG);
}

void saradc_ctrl_set_cmd(saradc_ctrl_cmd_t cmd)
{
  WRITE_REG_16(AADDR_SARADC_CTRL_CMD, cmd.val);
}

void saradc_ctrl_set_wadr_min(saradc_ctrl_wadr_min_t wadr_min)
{
  WRITE_REG_16(AADDR_SARADC_CTRL_WADR_MIN, wadr_min.val);
}

saradc_ctrl_wadr_min_t saradc_ctrl_get_wadr_min(void)
{
  saradc_ctrl_wadr_min_t wadr_min;
  wadr_min.val = READ_REG_U16(AADDR_SARADC_CTRL_WADR_MIN);
  return wadr_min;
}

void saradc_ctrl_set_wadr_max(saradc_ctrl_wadr_max_t wadr_max)
{
  WRITE_REG_16(AADDR_SARADC_CTRL_WADR_MAX, wadr_max.val);
}

saradc_ctrl_wadr_max_t saradc_ctrl_get_wadr_max(void)
{
  saradc_ctrl_wadr_max_t wadr_max;
  wadr_max.val = READ_REG_U16(AADDR_SARADC_CTRL_WADR_MAX);
  return wadr_max;
}

void saradc_ctrl_set_sadr_new(saradc_ctrl_sadr_new_t sadr_new)
{
  WRITE_REG_16(AADDR_SARADC_CTRL_SADR_NEW, sadr_new.val);
}

saradc_ctrl_sadr_current_t saradc_ctrl_get_sadr_current(void)
{
  return (saradc_ctrl_sadr_current_t)READ_REG_U16(AADDR_SARADC_CTRL_SADR_CURRENT);
}

saradc_ctrl_l0_current_t saradc_ctrl_get_l0_current(void)
{
  return (saradc_ctrl_l0_current_t)READ_REG_U16(AADDR_SARADC_CTRL_L0_CURRENT);
}
saradc_ctrl_l1_current_t saradc_ctrl_get_l1_current(void)
{
  saradc_ctrl_l1_current_t l1_current;
  l1_current.val = READ_REG_U16(AADDR_SARADC_CTRL_L1_CURRENT);
  return l1_current;
}
saradc_ctrl_l2_current_t saradc_ctrl_get_l2_current(void)
{
  return (saradc_ctrl_l2_current_t)READ_REG_U16(AADDR_SARADC_CTRL_L2_CURRENT);
}

saradc_ctrl_tadr_t saradc_ctrl_get_tadr(void)
{
  return (saradc_ctrl_tadr_t)READ_REG_U16(AADDR_SARADC_CTRL_TADR);
}

saradc_ctrl_adr_next_t saradc_ctrl_get_adr_next(void)
{
  return (saradc_ctrl_adr_next_t)READ_REG_U16(AADDR_SARADC_CTRL_ADR_NEXT);
}

saradc_ctrl_sadr_done_t saradc_ctrl_get_sadr_done(void)
{
  return (saradc_ctrl_sadr_done_t)READ_REG_U16(AADDR_SARADC_CTRL_SADR_DONE);
}

saradc_ctrl_state_t saradc_ctrl_get_state(void)
{
  return (saradc_ctrl_state_t)READ_REG_U16(AADDR_SARADC_CTRL_STATE);
}

void saradc_ctrl_set_irq_mask(saradc_ctrl_irq_mask_t irq_mask)
{
  WRITE_REG_16(AADDR_SARADC_CTRL_IRQ_MASK, irq_mask);
}

saradc_ctrl_irq_mask_t saradc_ctrl_get_irq_mask(void)
{
  return (saradc_ctrl_irq_mask_t)READ_REG_U16(AADDR_SARADC_CTRL_IRQ_MASK);
}

#include "vic.h"
#include "vic_irq.h"

volatile static callback_t callback[SARADC_CTRL_NUM_IRQS];

void saradc_ctrl_handler_init(void)
{

  irq_handler_init(VIC_IRQ_ADC_CTRL, SARADC_CTRL_NUM_IRQS, (callback_t *)callback,
                   BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_IRQ_VENABLE);
}
