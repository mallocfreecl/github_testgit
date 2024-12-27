#ifndef HAVE_SPI_H
#define HAVE_SPI_H

#include "base.h"

#include "spi_bf.h"
#include "spi_irq.h"

#include "vic.h"

#define SPI_FIFO_DEPTH 4

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void spi_init(spi_num_t spi_no, uint16_t divider, uint16_t timeout, uint16_t length, bool master, bool msb_first,
              bool phase, bool polarity, bool high_z, bool invert_nss, bool invert_data, bool pause_nss,
              bool sdi_irq_pol);

void spi_swap_sdi_sdo(spi_num_t spi_no, bool swap);

bool spi_transmit(spi_num_t spi_no, uint16_t data, bool keep_nss, bool blocking);

bool spi_receive(spi_num_t spi_no, uint16_t *data, bool blocking);

void spi_fifo_clear(spi_num_t spi_no, bool tfifo_clr, bool rfifo_clr, bool spi_rst);

uint16_t spi_get_rx_fifo_level(spi_num_t spi_no);

uint16_t spi_get_tx_fifo_level(spi_num_t spi_no);

uint16_t spi_get_rx_fifo_timeout(spi_num_t spi_no);

void spi_set_rx_fifo_timeout(spi_num_t spi_no, uint16_t value);

void spi_set_rx_high_water(spi_num_t spi_no, uint8_t value);

void spi_set_tx_low_water(spi_num_t spi_no, uint8_t value);

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

void spi_handler_init(spi_num_t spi_no);

void spi_handler_register(spi_num_t spi_no, spi_irq_t irq, callback_t callback);

void spi_enable_irq(spi_num_t spi_no, spi_irq_t irq, bool enable);

uint16_t spi_get_irq_status(spi_num_t spi_no);

void spi_clear_all_irq_events(spi_num_t spi_no);

#endif /* HAVE_SPI_H */
