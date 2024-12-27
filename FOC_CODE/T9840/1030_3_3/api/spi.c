
#include "spi.h"
#include "utils.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

volatile bool spi_msb_first = false;

void spi_init(spi_num_t spi_no, uint16_t divider, uint16_t timeout, uint16_t length, bool master, bool msb_first,
              bool phase, bool polarity, bool high_z, bool invert_nss, bool invert_data, bool pause_nss,
              bool sdi_irq_pol)
{

  spi_config_t spi_config;

  spi_msb_first = msb_first;

  if (length == 0)
    length = 1;
  if (length > 16)
    length = 16;

  spi_config.val = READ_REG_U16(spi_no + ADDR_SPI_CONFIG);
  spi_config.bf.length = length - 1;
  spi_config.bf.slave = master ? 0 : 1;
  spi_config.bf.order = msb_first ? 1 : 0;
  spi_config.bf.phase = phase ? 0 : 1;
  spi_config.bf.polarity = polarity ? 1 : 0;
  spi_config.bf.slave_high_z = high_z ? 1 : 0;
  spi_config.bf.invert_nss = invert_nss ? 1 : 0;
  spi_config.bf.invert_data = invert_data ? 1 : 0;
  spi_config.bf.pause_nss = pause_nss ? 1 : 0;
  spi_config.bf.sdi_irq_pol = sdi_irq_pol ? 1 : 0;
  spi_config.bf.enable = 1;
  WRITE_REG_16(spi_no + ADDR_SPI_CONFIG, spi_config.val);
  WRITE_REG_16(spi_no + ADDR_SPI_BAUD_CONFIG, divider);
  WRITE_REG_16(spi_no + ADDR_SPI_TIMEOUT_CONFIG, timeout);
}

void spi_swap_sdi_sdo(spi_num_t spi_no, bool swap)
{
  spi_config_t spi_config;

  spi_config.val = READ_REG_U16(spi_no + ADDR_SPI_CONFIG);
  spi_config.bf.swap_sdi_sdo = swap ? 1 : 0;
  WRITE_REG_16(spi_no + ADDR_SPI_CONFIG, spi_config.val);
}

bool spi_transmit(spi_num_t spi_no, uint16_t data, bool keep_nss, bool blocking)
{
  spi_fifo_levels_t spi_fifo_levels;

  do
  {
    spi_fifo_levels.val = READ_REG_U16(spi_no + ADDR_SPI_FIFO_LEVELS);
  } while (blocking && (spi_fifo_levels.bf.tx_fifo_level >= SPI_FIFO_DEPTH));

  if (spi_fifo_levels.bf.tx_fifo_level < SPI_FIFO_DEPTH)
  {
    if (keep_nss)
    {
      WRITE_REG_16(spi_no + ADDR_SPI_DATA_KEEP_NSS, data);
    }
    else
    {
      WRITE_REG_16(spi_no + ADDR_SPI_DATA, data);
    }
    return true;
  }
  return false;
}

bool spi_receive(spi_num_t spi_no, uint16_t *data, bool blocking)
{

  spi_fifo_levels_t spi_fifo_levels;

  do
  {
    spi_fifo_levels.val = READ_REG_U16(spi_no + ADDR_SPI_FIFO_LEVELS);
  } while (blocking && (spi_fifo_levels.bf.rx_fifo_level < 1));

  if (spi_fifo_levels.bf.rx_fifo_level >= 1)
  {
    *data = READ_REG_U16(spi_no + ADDR_SPI_DATA);
    return true;
  }
  return false;
}

void spi_fifo_clear(spi_num_t spi_no, bool tfifo_clr, bool rfifo_clr, bool spi_rst)
{

  spi_fifo_clear_t spi_fifo_clear;

  spi_fifo_clear.val = 0;
  spi_fifo_clear.bf.tx_fifo_clear = tfifo_clr ? 1 : 0;
  spi_fifo_clear.bf.rx_fifo_clear = rfifo_clr ? 1 : 0;
  spi_fifo_clear.bf.reset = spi_rst ? 1 : 0;
  WRITE_REG_16(spi_no + ADDR_SPI_FIFO_CLEAR, spi_fifo_clear.val);
}

uint16_t spi_get_rx_fifo_level(spi_num_t spi_no)
{

  spi_fifo_levels_t rx_level;

  rx_level.val = READ_REG_U16(spi_no + ADDR_SPI_FIFO_LEVELS);
  return rx_level.bf.rx_fifo_level;
}

uint16_t spi_get_tx_fifo_level(spi_num_t spi_no)
{

  spi_fifo_levels_t tx_level;

  tx_level.val = READ_REG_U16(spi_no + ADDR_SPI_FIFO_LEVELS);
  return tx_level.bf.tx_fifo_level;
}

uint16_t spi_get_rx_fifo_timeout(spi_num_t spi_no)
{

  return READ_REG_U16(spi_no + ADDR_SPI_RX_FIFO_TIMEOUT);
}

void spi_set_rx_fifo_timeout(spi_num_t spi_no, uint16_t value)
{

  WRITE_REG_16(spi_no + ADDR_SPI_RX_FIFO_TIMEOUT, value);
}

void spi_set_rx_high_water(spi_num_t spi_no, uint8_t value)
{
  spi_fifo_levels_t spi_fifo_levels;

  spi_fifo_levels.val = READ_REG_U16(spi_no + ADDR_SPI_FIFO_LEVELS);
  spi_fifo_levels.bf.rx_fifo_high_water = value;
  WRITE_REG_16(spi_no + ADDR_SPI_FIFO_LEVELS, spi_fifo_levels.val);
}

void spi_set_tx_low_water(spi_num_t spi_no, uint8_t value)
{
  spi_fifo_levels_t spi_fifo_levels;

  spi_fifo_levels.val = READ_REG_U16(spi_no + ADDR_SPI_FIFO_LEVELS);
  spi_fifo_levels.bf.tx_fifo_low_water = value;
  WRITE_REG_16(spi_no + ADDR_SPI_FIFO_LEVELS, spi_fifo_levels.val);
}

/* ======================================================================= */
/* CONSTANT VALUES                                                         */
/* ======================================================================= */

const uint16_t spi_bases[NUMBER_SPI] = {SPI_0, SPI_1};

vic_irq_t spi_vic_irqs[NUMBER_SPI] = {VIC_IRQ_SPI_0, VIC_IRQ_SPI_1};

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

#include "vic.h"
#include "vic_irq.h"

uint16_t spi_get_index(spi_num_t spi_no)
{

  if (spi_no == spi_bases[1])
    return 1;
  return 0;
}

volatile static callback_t callback[NUMBER_SPI][SPI_NUM_IRQS];

void spi_handler_init(spi_num_t spi_no)
{

  irq_handler_init(spi_vic_irqs[spi_get_index(spi_no)], SPI_NUM_IRQS, (callback_t *)callback[spi_get_index(spi_no)],
                   spi_bases[spi_get_index(spi_no)] + ADDR_SPI_IRQ_VENABLE);
}

void spi_handler_register(spi_num_t spi_no, spi_irq_t irq, callback_t callback)
{

  irq_handler_register(spi_vic_irqs[spi_get_index(spi_no)], irq, callback);
}

void spi_enable_irq(spi_num_t spi_no, spi_irq_t irq, bool enable)
{

  if (enable)
    irq_enable(spi_vic_irqs[spi_get_index(spi_no)], irq);
  else
    irq_disable(spi_vic_irqs[spi_get_index(spi_no)], irq);
}

uint16_t spi_get_irq_status(spi_num_t spi_no)
{

  return irq_get_status(spi_vic_irqs[spi_get_index(spi_no)]);
}

void spi_clear_all_irq_events(spi_num_t spi_no)
{

  irq_clear_all_events(spi_vic_irqs[spi_get_index(spi_no)]);
}
