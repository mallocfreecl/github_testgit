#ifndef HAVE_GPIO_H
#define HAVE_GPIO_H

#include "base.h"

#include "gpio_bf.h"
#include "gpio_irq.h"

#include "vic.h"

typedef enum
{
  GPIO_IO_0 = 0x0001,
  GPIO_IO_1 = 0x0002,
  GPIO_IO_2 = 0x0004,
  GPIO_IO_3 = 0x0008,
  GPIO_IO_4 = 0x0010,
  GPIO_IO_5 = 0x0020,
  GPIO_IO_6 = 0x0040,
  GPIO_IO_7 = 0x0080
} gpio_io_t;

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void gpio_set_input_enable(gpio_num_t gpio_no, gpio_io_t ios, bool enable);
void gpio_set_output_enable(gpio_num_t gpio_no, gpio_io_t ios, bool enable);
void gpio_set_data_out(gpio_num_t gpio_no, gpio_io_t ios, bool high);
void gpio_set_direction_lock(gpio_num_t gpio_no, gpio_io_t ios, bool lock);
bool gpio_get_data_in(gpio_num_t gpio_no, gpio_io_t io);

void gpio_write_input_enable(gpio_num_t gpio_no, uint8_t ie);
void gpio_write_output_enable(gpio_num_t gpio_no, uint8_t oe);
void gpio_write_data_out(gpio_num_t gpio_no, uint8_t data);
void gpio_write_direction_lock(gpio_num_t gpio_no, uint8_t data);
uint8_t gpio_read_data_in(gpio_num_t gpio_no);

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

void gpio_handler_init(gpio_num_t gpio_no);

void gpio_handler_register(gpio_num_t gpio_no, gpio_irq_t irq, callback_t callback);

void gpio_enable_irq(gpio_num_t gpio_no, gpio_irq_t irq, bool enable);

uint16_t gpio_get_irq_status(gpio_num_t gpio_no);

void gpio_clear_all_irq_events(gpio_num_t gpio_no);

#endif /* HAVE_GPIO_H */
