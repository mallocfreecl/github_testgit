
#include "cctimer.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void cctimer_set_prescaler(cctimer_num_t dev, uint16_t prescaler)
{

  if (prescaler)
    prescaler--;
  if (prescaler > 255)
    prescaler = 255; // 8 bit saturation

  WRITE_REG_16(dev + ADDR_CCTIMER_PRESCALER, prescaler);
}

uint16_t cctimer_get_prescaler(cctimer_num_t dev)
{

  return READ_REG_U16(dev + ADDR_CCTIMER_PRESCALER);
}

void cctimer_config(cctimer_num_t dev, cctimer_subdev_t subdev, clk_sel_t clk_sel, restart_sel_t sta_sel,
                    capture_sel_t cap_sel, capcmp_mode_t mode)
{

  cctimer_config_t cctimer_config;

  cctimer_config.val = 0;
  cctimer_config.bf.mode = mode;
  cctimer_config.bf.clk_sel = clk_sel;
  cctimer_config.bf.restart_sel = sta_sel;
  cctimer_config.bf.capture_sel = cap_sel;

  switch (subdev)
  {
  case CCT_A:
    WRITE_REG_16(dev + ADDR_CCTIMER_CONFIG_A, cctimer_config.val);
    break;
  case CCT_B:
    WRITE_REG_16(dev + ADDR_CCTIMER_CONFIG_B, cctimer_config.val);
    break;
  }
}

void cctimer_enable(cctimer_num_t dev, cctimer_subdev_t subdevs, bool enable)
{

  cctimer_control_t cctimer_control;

  cctimer_control.val = READ_REG_U16(dev + ADDR_CCTIMER_CONTROL);

  if (subdevs & CCT_A)
  {
    cctimer_control.bf.enable_a = enable ? 1 : 0;
  }
  if (subdevs & CCT_B)
  {
    cctimer_control.bf.enable_b = enable ? 1 : 0;
  }
  WRITE_REG_16(dev + ADDR_CCTIMER_CONTROL, cctimer_control.val);
}

void cctimer_set_compare(cctimer_num_t dev, cctimer_subdev_t subdev, uint16_t cmp_val)
{

  if (cmp_val)
    cmp_val--;

  switch (subdev)
  {
  case CCT_A:
    WRITE_REG_16(dev + ADDR_CCTIMER_CAPCMP_A, cmp_val);
    break;
  case CCT_B:
    WRITE_REG_16(dev + ADDR_CCTIMER_CAPCMP_B, cmp_val);
    break;
  }
}

uint16_t cctimer_get_compare(cctimer_num_t dev, cctimer_subdev_t subdev)
{

  uint16_t cmp;

  cmp = 0;
  switch (subdev)
  {
  case CCT_A:
    cmp = READ_REG_U16(dev + ADDR_CCTIMER_CAPCMP_A);
    break;
  case CCT_B:
    cmp = READ_REG_U16(dev + ADDR_CCTIMER_CAPCMP_B);
    break;
  }
  if (cmp)
    cmp++;
  return cmp;
}

uint16_t cctimer_get_counter(cctimer_num_t dev, cctimer_subdev_t subdev)
{

  uint16_t cnt;

  cnt = 0;
  switch (subdev)
  {
  case CCT_A:
    cnt = READ_REG_U16(dev + ADDR_CCTIMER_COUNTER_A);
    break;
  case CCT_B:
    cnt = READ_REG_U16(dev + ADDR_CCTIMER_COUNTER_B);
    break;
  }
  return cnt;
}

uint16_t cctimer_get_capture(cctimer_num_t dev, cctimer_subdev_t subdev)
{

  uint16_t cap;

  cap = 0;
  switch (subdev)
  {
  case CCT_A:
    cap = READ_REG_U16(dev + ADDR_CCTIMER_CAPCMP_A);
    break;
  case CCT_B:
    cap = READ_REG_U16(dev + ADDR_CCTIMER_CAPCMP_B);
    break;
  }
  if (cap)
    cap++;
  return cap;
}

void cctimer_restart(cctimer_num_t dev, cctimer_cmd_t cmds)
{

  cctimer_control_t cctimer_control;

  cctimer_control.val = READ_REG_U16(dev + ADDR_CCTIMER_CONTROL);

  if (cmds & CCT_CMD_A)
  {
    cctimer_control.bf.restart_a = 1;
  }
  if (cmds & CCT_CMD_B)
  {
    cctimer_control.bf.restart_b = 1;
  }
  if (cmds & CCT_CMD_P)
  {
    cctimer_control.bf.restart_p = 1;
  }
  WRITE_REG_16(dev + ADDR_CCTIMER_CONTROL, cctimer_control.val);
}

void cctimer_set_presel(cctimer_num_t dev, cctimer_subdev_t subdev, pre_sel_t clk_sel, pre_sel_t sta_sel,
                        pre_sel_t cap_sel)
{

  cctimer_presel_t cctimer_presel;

  cctimer_presel.val = 0;
  cctimer_presel.bf.clk_sel = clk_sel;
  cctimer_presel.bf.restart_sel = sta_sel;
  cctimer_presel.bf.capture_sel = cap_sel;

  switch (subdev)
  {
  case CCT_A:
    WRITE_REG_16(dev + ADDR_CCTIMER_PRESEL_A, cctimer_presel.val);
    break;
  case CCT_B:
    WRITE_REG_16(dev + ADDR_CCTIMER_PRESEL_B, cctimer_presel.val);
    break;
  }
}

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

#include "vic.h"
#include "vic_irq.h"

/* ======================================================================= */
/* CONSTANT VALUES                                                         */
/* ======================================================================= */

const uint16_t cctimer_bases[NUMBER_CCTIMER] = {CCTIMER_0, CCTIMER_1, CCTIMER_2, CCTIMER_3};

vic_irq_t cctimer_vic_irqs[NUMBER_CCTIMER] = {VIC_IRQ_CCTIMER_0, VIC_IRQ_CCTIMER_1, VIC_IRQ_CCTIMER_2,
                                              VIC_IRQ_CCTIMER_3};

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

#include "vic.h"
#include "vic_irq.h"

uint16_t cctimer_get_index(cctimer_num_t cctimer_no)
{

  uint16_t n;

  for (n = 1; n < NUMBER_CCTIMER; n++)
  {
    if (cctimer_no == cctimer_bases[n])
      return n;
  }
  return 0;
}

volatile static callback_t callback[NUMBER_CCTIMER][CCTIMER_NUM_IRQS];

void cctimer_handler_init(cctimer_num_t cctimer_no)
{

  irq_handler_init(cctimer_vic_irqs[cctimer_get_index(cctimer_no)], CCTIMER_NUM_IRQS,
                   (callback_t *)callback[cctimer_get_index(cctimer_no)],
                   cctimer_bases[cctimer_get_index(cctimer_no)] + ADDR_CCTIMER_IRQ_VENABLE);
}

void cctimer_handler_register(cctimer_num_t cctimer_no, cctimer_irq_t irq, callback_t callback)
{

  irq_handler_register(cctimer_vic_irqs[cctimer_get_index(cctimer_no)], irq, callback);
}

void cctimer_enable_irq(cctimer_num_t cctimer_no, cctimer_irq_t irq, bool enable)
{

  if (enable)
    irq_enable(cctimer_vic_irqs[cctimer_get_index(cctimer_no)], irq);
  else
    irq_disable(cctimer_vic_irqs[cctimer_get_index(cctimer_no)], irq);
}

uint16_t cctimer_get_irq_status(cctimer_num_t cctimer_no)
{

  return irq_get_status(cctimer_vic_irqs[cctimer_get_index(cctimer_no)]);
}

void cctimer_clear_all_irq_events(cctimer_num_t cctimer_no)
{

  irq_clear_all_events(cctimer_vic_irqs[cctimer_get_index(cctimer_no)]);
}
