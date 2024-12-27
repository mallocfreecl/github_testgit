
#include "sci.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void _sci_set_config(uintptr_t dev, sci_cfg cfg)
{

  SCI(dev)->control.val |= (uint16_t)cfg;
}

void _sci_reset_config(uintptr_t dev, sci_cfg cfg)
{

  SCI(dev)->control.val &= (uint16_t)(~cfg);
}

void _sci_transmit(uintptr_t dev, uint8_t data)
{

  _sci_transmit_byte(dev, data, true);
}

uint8_t _sci_receive(uintptr_t dev)
{

  uint8_t data = 0;

  _sci_receive_byte(dev, &data, true);
  return data;
}

bool _sci_transmit_byte(uintptr_t dev, uint8_t data, bool blocking)
{

  sci_status status;

  do
  {
    status = _sci_get_status(dev);
  } while (blocking && !(status & SCI_TRANSMIT_DATAREG_EMPTY));

  if (status & SCI_TRANSMIT_DATAREG_EMPTY)
  {
    SCI(dev)->data_io = data;
    return true;
  }
  return false;
}

bool _sci_receive_byte(uintptr_t dev, uint8_t *data, bool blocking)
{

  sci_status status;

  do
  {
    status = _sci_get_status(dev);
  } while (blocking && !(status & SCI_RECEIVE_DATAREG_FULL));

  if (status & SCI_RECEIVE_DATAREG_FULL)
  {
    *data = SCI(dev)->data_io;
    return true;
  }
  return false;
}

sci_status _sci_get_status(uintptr_t dev)
{

  return (sci_status)(SCI(dev)->status.val);
}

void _sci_set_meas_mode(uintptr_t dev, sci_meas_mode meas_mode)
{

  sci_meas_control_t SCI_MEASCNTRL;

  SCI_MEASCNTRL.val = SCI(dev)->meas_control.val;
  SCI_MEASCNTRL.bf.men = 0;
  SCI_MEASCNTRL.bf.mmode = meas_mode;
  SCI(dev)->meas_control.val = SCI_MEASCNTRL.val;
}

void _sci_meas_enable(uintptr_t dev)
{

  sci_meas_control_t SCI_MEASCNTRL;

  SCI_MEASCNTRL.val = SCI(dev)->meas_control.val;
  SCI_MEASCNTRL.bf.men = 1;
  SCI(dev)->meas_control.val = SCI_MEASCNTRL.val;
}

void _sci_meas_disable(uintptr_t dev)
{

  sci_meas_control_t SCI_MEASCNTRL;

  SCI_MEASCNTRL.val = SCI(dev)->meas_control.val;
  SCI_MEASCNTRL.bf.men = 0;
  SCI(dev)->meas_control.val = SCI_MEASCNTRL.val;
}

void _sci_set_auto_mode(uintptr_t dev, sci_auto_mode auto_mode)
{

  sci_meas_control_t SCI_MEASCNTRL;

  SCI_MEASCNTRL.val = SCI(dev)->meas_control.val;
  if (auto_mode == SCI_AUTO_OFF)
  {
    SCI_MEASCNTRL.bf.auto_meas = 0;
    SCI_MEASCNTRL.bf.auto_baud = 0;
  }
  else if (auto_mode == SCI_AUTO_MEAS)
  {
    SCI_MEASCNTRL.bf.auto_meas = 1;
    SCI_MEASCNTRL.bf.auto_baud = 0;
  }
  else if (auto_mode == SCI_AUTO_BAUD)
  {
    SCI_MEASCNTRL.bf.auto_meas = 0;
    SCI_MEASCNTRL.bf.auto_baud = 1;
  }
  else if (auto_mode == SCI_AUTO_BOTH)
  {
    SCI_MEASCNTRL.bf.auto_meas = 1;
    SCI_MEASCNTRL.bf.auto_baud = 1;
  }
  SCI(dev)->meas_control.val = SCI_MEASCNTRL.val;
}

void _sci_set_dbc_filter(uintptr_t dev, uint8_t dbc)
{

  sci_meas_control_t SCI_MEASCNTRL;

  SCI_MEASCNTRL.val = SCI(dev)->meas_control.val;
  SCI_MEASCNTRL.bf.dbc = dbc;
  SCI(dev)->meas_control.val = SCI_MEASCNTRL.val;
}

uint8_t _sci_get_dbc_filter(uintptr_t dev)
{

  sci_meas_control_t SCI_MEASCNTRL;

  SCI_MEASCNTRL.val = SCI(dev)->meas_control.val;
  return SCI_MEASCNTRL.bf.dbc;
}

uint16_t _sci_get_meas_value(uintptr_t dev)
{

  return SCI(dev)->meas_counter;
}

uint16_t _sci_get_baud_rate(uintptr_t dev)
{

  return SCI(dev)->baud_rate.val;
}

void _sci_set_baud_rate(uintptr_t dev, sci_baud baud_rate)
{

  SCI(dev)->baud_rate.val = baud_rate;
}

void _sci_bus_collision_detect(uintptr_t dev, bool val)
{

  sci_meas_control_t SCI_MEASCNTRL;

  SCI_MEASCNTRL.val = SCI(dev)->meas_control.val;
  SCI_MEASCNTRL.bf.bus_collision_e = val;
  SCI(dev)->meas_control.val = SCI_MEASCNTRL.val;
}

void _sci_set_timer_cmp(uintptr_t dev, uint16_t val)
{

  SCI(dev)->timer_compare = val;
}

uint16_t _sci_get_timer_cmp(uintptr_t dev)
{

  return (uint16_t)SCI(dev)->timer_compare;
}

uint16_t _sci_get_timer_cnt(uintptr_t dev)
{

  return (uint16_t)SCI(dev)->timer_counter;
}

void _sci_timer_enable(uintptr_t dev, bool val)
{

  sci_lin_mode_t SCI_LINMODE;

  SCI_LINMODE.val = SCI(dev)->lin_mode.val;
  SCI_LINMODE.bf.timer_enable = val;
  SCI(dev)->lin_mode.val = SCI_LINMODE.val;
}

void _sci_timer_prepare(uintptr_t dev, sci_timer_prepare_mode timer_prepare_mode)
{

  sci_lin_mode_t SCI_LINMODE;

  SCI_LINMODE.val = SCI(dev)->lin_mode.val;
  SCI_LINMODE.bf.timer_prepare = timer_prepare_mode;
  SCI(dev)->lin_mode.val = SCI_LINMODE.val;
}

void _sci_set_timer_clk_base(uintptr_t dev, sci_timer_clk_base timer_clk_base)
{

  sci_lin_mode_t SCI_LINMODE;

  SCI_LINMODE.val = SCI(dev)->lin_mode.val;
  SCI_LINMODE.bf.timer_clk_base = timer_clk_base;
  SCI(dev)->lin_mode.val = SCI_LINMODE.val;
}

void _sci_timeout_enable(uintptr_t dev, bool val)
{

  sci_lin_mode_t SCI_LINMODE;

  SCI_LINMODE.val = SCI(dev)->lin_mode.val;
  SCI_LINMODE.bf.txd_timeout_enable = val;
  SCI(dev)->lin_mode.val = SCI_LINMODE.val;
}

void _sci_disable(uintptr_t dev, bool val)
{

  sci_lin_mode_t SCI_LINMODE;

  SCI_LINMODE.val = SCI(dev)->lin_mode.val;
  SCI_LINMODE.bf.sci_disable = val;
  SCI(dev)->lin_mode.val = SCI_LINMODE.val;
}

void _sci_set_txd(uintptr_t dev, bool val)
{

  sci_lin_mode_t SCI_LINMODE;

  SCI_LINMODE.val = SCI(dev)->lin_mode.val;
  SCI_LINMODE.bf.txd_val = val;
  SCI(dev)->lin_mode.val = SCI_LINMODE.val;
}

bool _sci_get_rxd(uintptr_t dev)
{

  sci_lin_mode_t SCI_LINMODE;

  SCI_LINMODE.val = SCI(dev)->lin_mode.val;
  if (SCI_LINMODE.bf.rxd)
    return true;
  else
    return false;
}

/* ======================================================================= */
/* CONSTANT VALUES                                                         */
/* ======================================================================= */

const uint16_t sci_bases[NUMBER_SCI] = {SCI};

vic_irq_t sci_vic_irqs[NUMBER_SCI] = {VIC_IRQ_SCI};

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

#include "vic.h"
#include "vic_irq.h"

uint16_t sci_get_index(sci_num_t sci_no)
{

  if (sci_no == sci_bases[1])
    return 1;
  return 0;
}

volatile static callback_t callback[NUMBER_SCI][SCI_NUM_IRQS];

void sci_handler_init(sci_num_t sci_no)
{

  irq_handler_init(sci_vic_irqs[sci_get_index(sci_no)], SCI_NUM_IRQS, (callback_t *)callback[sci_get_index(sci_no)],
                   sci_bases[sci_get_index(sci_no)] + ADDR_SCI_IRQ_VENABLE);
}

void sci_handler_register(sci_num_t sci_no, sci_irq_t irq, callback_t callback)
{

  irq_handler_register(sci_vic_irqs[sci_get_index(sci_no)], irq, callback);
}

void sci_enable_irq(sci_num_t sci_no, sci_irq_t irq, bool enable)
{

  if (enable)
    irq_enable(sci_vic_irqs[sci_get_index(sci_no)], irq);
  else
    irq_disable(sci_vic_irqs[sci_get_index(sci_no)], irq);
}

uint16_t sci_get_irq_status(sci_num_t sci_no)
{

  return irq_get_status(sci_vic_irqs[sci_get_index(sci_no)]);
}

void sci_clear_all_irq_events(sci_num_t sci_no)
{

  irq_clear_all_events(sci_vic_irqs[sci_get_index(sci_no)]);
}

/*RPY*/

sci_irq_t _sci_get_pending_irq(uintptr_t dev)
{
  //! "VNO" is not usable here, since it holds only enabled IRQs, while here all irqs
  //! have to be considered.
  // uint16_t irqs=(SCI(dev)->IRQ_STATUS);
  uint16_t irqs = REG_SCI_IRQ_STATUS;
  int num = 0;

  while (num < SCI_NUM_IRQS)
  {
    if (irqs & 0x01)
      break;
    irqs >>= 1;
    ++num;
  }

  return ((sci_irq_t)num);
}

void _sci_reset_pending_irq(uintptr_t dev, int num)
{
  //(SCI(dev)->IRQ_STATUS) = (1<<num);
  REG_SCI_IRQ_STATUS = (1 << num);
}

void _sci_disable_all_irqs(uintptr_t dev)
{
  //(SCI(dev)->IRQ_MASK) = 0;
  REG_SCI_IRQ_MASK = 0;
}

uint8_t _sci_get_data(uintptr_t dev)
{
  // return (uint8_t)((SCI(dev)->DATA)&MSK_SCI_DATA_IO);
  return (uint8_t)(REG_SCI_DATA_IO & MSK_SCI_DATA_IO);
}

void _sci_set_data(uintptr_t dev, uint8_t byte)
{
  // SCI(dev)->DATA = ((sci_data_io_t)byte);
  REG_SCI_DATA_IO = ((sci_data_io_t)byte);
}

/*---*/
