
#include "gpio.h"
#include "utils.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void gpio_set_input_enable(gpio_num_t gpio_no, gpio_io_t ios, bool enable)
{

  uint16_t ie;

  ie = READ_REG_U16(gpio_no + ADDR_GPIO_DATA_IE);
  if (enable)
  {
    ie |= ios;
  }
  else
  {
    ie &= ~ios;
  }
  WRITE_REG_16(gpio_no + ADDR_GPIO_DATA_IE, ie);
}

void gpio_set_output_enable(gpio_num_t gpio_no, gpio_io_t ios, bool enable)
{

  uint16_t oe;

  oe = READ_REG_U16(gpio_no + ADDR_GPIO_DATA_OE);
  if (enable)
  {
    oe |= ios;
  }
  else
  {
    oe &= ~ios;
  }
  WRITE_REG_16(gpio_no + ADDR_GPIO_DATA_OE, oe);
}

void gpio_set_data_out(gpio_num_t gpio_no, gpio_io_t ios, bool high)
{

  uint16_t data;

  data = READ_REG_U16(gpio_no + ADDR_GPIO_DATA_OUT);
  if (high)
  {
    data |= ios;
  }
  else
  {
    data &= ~ios;
  }
  WRITE_REG_16(gpio_no + ADDR_GPIO_DATA_OUT, data);
}

void gpio_set_direction_lock(gpio_num_t gpio_no, gpio_io_t ios, bool lock)
{

  uint16_t direction_lock;

  direction_lock = READ_REG_U16(gpio_no + ADDR_GPIO_DIRECTION_LOCK);
  if (lock)
  {
    direction_lock |= ios;
  }
  else
  {
    direction_lock &= ~ios;
  }
  WRITE_REG_16(gpio_no + ADDR_GPIO_DIRECTION_LOCK, direction_lock);
}

bool gpio_get_data_in(gpio_num_t gpio_no, gpio_io_t io)
{

  return (READ_REG_U16(gpio_no + ADDR_GPIO_DATA_IN) & io) ? true : false;
}

void gpio_write_input_enable(gpio_num_t gpio_no, uint8_t ie)
{

  WRITE_REG_16(gpio_no + ADDR_GPIO_DATA_IE, (uint16_t)ie);
}

void gpio_write_output_enable(gpio_num_t gpio_no, uint8_t oe)
{

  WRITE_REG_16(gpio_no + ADDR_GPIO_DATA_OE, (uint16_t)oe);
}

void gpio_write_data_out(gpio_num_t gpio_no, uint8_t data)
{

  WRITE_REG_16(gpio_no + ADDR_GPIO_DATA_OUT, (uint16_t)data);
}

void gpio_write_direction_lock(gpio_num_t gpio_no, uint8_t data)
{

  WRITE_REG_16(gpio_no + ADDR_GPIO_DIRECTION_LOCK, (uint16_t)data);
}

uint8_t gpio_read_data_in(gpio_num_t gpio_no)
{

  return READ_REG_U16(gpio_no + ADDR_GPIO_DATA_IN);
}

/* ======================================================================= */
/* CONSTANT VALUES                                                         */
/* ======================================================================= */

const uint16_t gpio_bases[NUMBER_GPIO] = {GPIO_A, GPIO_B, GPIO_C};

vic_irq_t gpio_vic_irqs[NUMBER_GPIO] = {VIC_IRQ_GPIO_A, VIC_IRQ_GPIO_B, VIC_IRQ_GPIO_C};

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

#include "vic.h"
#include "vic_irq.h"

uint16_t gpio_get_index(gpio_num_t gpio_no)
{

  if (gpio_no == gpio_bases[2])
    return 2;
  if (gpio_no == gpio_bases[1])
    return 1;
  return 0;
}

volatile static callback_t callback[NUMBER_GPIO][GPIO_NUM_IRQS];

void gpio_handler_init(gpio_num_t gpio_no)
{

  irq_handler_init(gpio_vic_irqs[gpio_get_index(gpio_no)], GPIO_NUM_IRQS,
                   (callback_t *)callback[gpio_get_index(gpio_no)],
                   gpio_bases[gpio_get_index(gpio_no)] + ADDR_GPIO_IRQ_VENABLE);
}

void gpio_handler_register(gpio_num_t gpio_no, gpio_irq_t irq, callback_t callback)
{

  irq_handler_register(gpio_vic_irqs[gpio_get_index(gpio_no)], irq, callback);
}

void gpio_enable_irq(gpio_num_t gpio_no, gpio_irq_t irq, bool enable)
{

  if (enable)
    irq_enable(gpio_vic_irqs[gpio_get_index(gpio_no)], irq);
  else
    irq_disable(gpio_vic_irqs[gpio_get_index(gpio_no)], irq);
}

uint16_t gpio_get_irq_status(gpio_num_t gpio_no)
{

  return irq_get_status(gpio_vic_irqs[gpio_get_index(gpio_no)]);
}

void gpio_clear_all_irq_events(gpio_num_t gpio_no)
{

  irq_clear_all_events(gpio_vic_irqs[gpio_get_index(gpio_no)]);
}
