#ifndef __SCI_INST_H__
#define __SCI_INST_H__

#ifdef USE_TESTER_BASES
#include "tester_bases.h"
#endif

/* ========================================================================== */
/* SCI serve functions */
/* ========================================================================== */

void _sci_set_config(uintptr_t dev, sci_cfg cfg);
void _sci_reset_config(uintptr_t dev, sci_cfg cfg);

void _sci_transmit(uintptr_t dev, uint8_t data);
uint8_t _sci_receive(uintptr_t dev);

bool _sci_transmit_byte(uintptr_t dev, uint8_t data, bool blocking);
bool _sci_receive_byte(uintptr_t dev, uint8_t *data, bool blocking);

sci_status _sci_get_status(uintptr_t dev);

void _sci_set_baud_rate(uintptr_t dev, sci_baud baud_rate);
uint16_t _sci_get_baud_rate(uintptr_t dev);

void _sci_set_auto_mode(uintptr_t dev, sci_auto_mode auto_mode);
void _sci_set_meas_mode(uintptr_t dev, sci_meas_mode meas_mode);
uint16_t _sci_get_meas_value(uintptr_t dev);

void _sci_meas_enable(uintptr_t dev);
void _sci_meas_disable(uintptr_t dev);

void _sci_set_dbc_filter(uintptr_t dev, uint8_t dbc);
uint8_t _sci_get_dbc_filter(uintptr_t dev);

void _sci_set_timer_cmp(uintptr_t dev, uint16_t val);
uint16_t _sci_get_timer_cmp(uintptr_t dev);
uint16_t _sci_get_timer_cnt(uintptr_t dev);

void _sci_bus_collision_detect(uintptr_t dev, bool val);
void _sci_timer_enable(uintptr_t dev, bool val);
void _sci_timer_prepare(uintptr_t dev, sci_timer_prepare_mode timer_prepare_mode);
void _sci_set_timer_clk_base(uintptr_t dev, sci_timer_clk_base timer_clk_base);
void _sci_timeout_enable(uintptr_t dev, bool val);
void _sci_disable(uintptr_t dev, bool val);
void _sci_set_txd(uintptr_t dev, bool val);
bool _sci_get_rxd(uintptr_t dev);

/* ========================================================================== */
/* TIMER instance related serve functions */
/* ========================================================================== */

#define sci_set_config(...) _sci_set_config(SCI, __VA_ARGS__)
#define sci_reset_config(...) _sci_reset_config(SCI, __VA_ARGS__)
#define sci_transmit(...) _sci_transmit(SCI, __VA_ARGS__)
#define sci_receive() _sci_receive(SCI)
#define sci_transmit_byte(...) _sci_transmit_byte(SCI, __VA_ARGS__)
#define sci_receive_byte(...) _sci_receive_byte(SCI, __VA_ARGS__)
#define sci_get_status() _sci_get_status(SCI)
#define sci_set_baud_rate(...) _sci_set_baud_rate(SCI, __VA_ARGS__)
#define sci_get_baud_rate() _sci_get_baud_rate(SCI)
#define sci_set_auto_mode(...) _sci_set_auto_mode(SCI, __VA_ARGS__)
#define sci_set_meas_mode(...) _sci_set_meas_mode(SCI, __VA_ARGS__)
#define sci_get_meas_value() _sci_get_meas_value(SCI)
#define sci_meas_enable() _sci_meas_enable(SCI)
#define sci_meas_disable() _sci_meas_disable(SCI)
#define sci_set_dbc_filter(...) _sci_set_dbc_filter(SCI, __VA_ARGS__)
#define sci_get_dbc_filter() _sci_get_dbc_filter(SCI)
#define sci_bus_collision_detect(...) _sci_bus_collision_detect(SCI, __VA_ARGS__)
#define sci_set_timer_cmp(...) _sci_set_timer_cmp(SCI, __VA_ARGS__)
#define sci_get_timer_cmp(...) _sci_get_timer_cmp(SCI)
#define sci_get_timer_cnt(...) _sci_get_timer_cnt(SCI)
#define sci_timer_enable(...) _sci_timer_enable(SCI, __VA_ARGS__)
#define sci_timer_prepare(...) _sci_timer_prepare(SCI, __VA_ARGS__)
#define sci_set_timer_clk_base(...) _sci_set_timer_clk_base(SCI, __VA_ARGS__)
#define sci_timeout_enable(...) _sci_timeout_enable(SCI, __VA_ARGS__)
#define sci_disable(...) _sci_disable(SCI, __VA_ARGS__)
#define sci_set_txd(...) _sci_set_txd(SCI, __VA_ARGS__)
#define sci_get_rxd() _sci_get_rxd(SCI)

#ifdef BASE_ADDR_SCI_TESTER
#define trgt_sci_set_config(...) _sci_set_config(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_reset_config(...) _sci_reset_config(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_transmit(...) _sci_transmit(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_receive() _sci_receive(BASE_ADDR_SCI_TESTER)
#define trgt_sci_transmit_byte(...) _sci_transmit_byte(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_receive_byte(...) _sci_receive_byte(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_get_status() _sci_get_status(BASE_ADDR_SCI_TESTER)
#define trgt_sci_set_baud_rate(...) _sci_set_baud_rate(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_get_baud_rate() _sci_get_baud_rate(BASE_ADDR_SCI_TESTER)
#define trgt_sci_set_auto_mode(...) _sci_set_auto_mode(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_set_meas_mode(...) _sci_set_meas_mode(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_get_meas_value() _sci_get_meas_value(BASE_ADDR_SCI_TESTER)
#define trgt_sci_meas_enable() _sci_meas_enable(BASE_ADDR_SCI_TESTER)
#define trgt_sci_meas_disable() _sci_meas_disable(BASE_ADDR_SCI_TESTER)
#define trgt_sci_set_dbc_filter(...) _sci_set_dbc_filter(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_get_dbc_filter() _sci_get_dbc_filter(BASE_ADDR_SCI_TESTER)
#define trgt_sci_bus_collision_detect(...) _sci_bus_collision_detect(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_set_timer_cmp(...) _sci_set_timer_cmp(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_get_timer_cmp(...) _sci_get_timer_cmp(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_get_timer_cnt(...) _sci_get_timer_cnt(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_timer_enable(...) _sci_timer_enable(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_timer_prepare(...) _sci_timer_prepare(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_set_timer_clk_base(...) _sci_set_timer_clk_base(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_timeout_enable(...) _sci_timeout_enable(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_disable(...) _sci_disable(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_set_txd(...) _sci_set_txd(BASE_ADDR_SCI_TESTER, __VA_ARGS__)
#define trgt_sci_get_rxd() _sci_get_rxd(BASE_ADDR_SCI_TESTER)
#endif

/*RPY*/

uint16_t _sci_get_features(uintptr_t dev);
void _sci_set_data(uintptr_t dev, uint8_t byte);
uint8_t _sci_get_data(uintptr_t dev);

uint16_t _sci_get_tx_dma_len(uintptr_t dev);
uint16_t _sci_get_rx_dma_len(uintptr_t dev);

void _sci_set_timer_compare(uintptr_t dev, uint16_t cmp);
uint16_t _sci_get_timer_counter(uintptr_t dev);
uint16_t _sci_get_timer_compare(uintptr_t dev);

void _sci_disable_all_irqs(uintptr_t dev);
sci_irq_t _sci_get_pending_irq(uintptr_t dev);
void _sci_reset_pending_irq(uintptr_t dev, int num);

void _sci_enable_addon_irq(uintptr_t dev, uint16_t mask, bool en);
void _sci_reset_addon_irq(uintptr_t dev, uint16_t mask);

/*---*/

/*RPY*/
#define sci_get_features() _sci_get_features(SCI)
#define sci_set_data(...) _sci_set_data(SCI, __VA_ARGS__)
#define sci_get_data() _sci_get_data(SCI)
#define sci_get_pending_irq() _sci_get_pending_irq(SCI)
#define sci_reset_pending_irq(...) _sci_reset_pending_irq(SCI, __VA_ARGS__)
#define sci_disable_all_irqs() _sci_disable_all_irqs(SCI)
#define sci_setup_tx_dma(...) _sci_setup_tx_dma(SCI, __VA_ARGS__)
#define sci_setup_rx_dma(...) _sci_setup_rx_dma(SCI, __VA_ARGS__)
#define sci_stop_tx_dma() _sci_stop_tx_dma(SCI)
#define sci_stop_rx_dma() _sci_stop_rx_dma(SCI)
#define sci_get_tx_dma_len() _sci_get_tx_dma_len(SCI)
#define sci_get_rx_dma_len() _sci_get_rx_dma_len(SCI)

uint16_t _sci_get_features(uintptr_t dev);
void _sci_set_data(uintptr_t dev, uint8_t byte);
uint8_t _sci_get_data(uintptr_t dev);

uint16_t _sci_get_tx_dma_len(uintptr_t dev);
uint16_t _sci_get_rx_dma_len(uintptr_t dev);

void _sci_set_timer_compare(uintptr_t dev, uint16_t cmp);
uint16_t _sci_get_timer_counter(uintptr_t dev);
uint16_t _sci_get_timer_compare(uintptr_t dev);

void _sci_disable_all_irqs(uintptr_t dev);
sci_irq_t _sci_get_pending_irq(uintptr_t dev);
void _sci_reset_pending_irq(uintptr_t dev, int num);

void _sci_enable_addon_irq(uintptr_t dev, uint16_t mask, bool en);
void _sci_reset_addon_irq(uintptr_t dev, uint16_t mask);

/*---*/

#define trgt_sci_set_config(...) _sci_set_config(0x6380, __VA_ARGS__)
#define trgt_sci_reset_config(...) _sci_reset_config(0x6380, __VA_ARGS__)
#define trgt_sci_transmit(...) _sci_transmit(0x6380, __VA_ARGS__)
#define trgt_sci_receive() _sci_receive(0x6380)
#define trgt_sci_transmit_byte(...) _sci_transmit_byte(0x6380, __VA_ARGS__)
#define trgt_sci_receive_byte(...) _sci_receive_byte(0x6380, __VA_ARGS__)
#define trgt_sci_get_status() _sci_get_status(0x6380)
#define trgt_sci_set_baud_rate(...) _sci_set_baud_rate(0x6380, __VA_ARGS__)
#define trgt_sci_get_baud_rate() _sci_get_baud_rate(0x6380)
#define trgt_sci_set_auto_mode(...) _sci_set_auto_mode(0x6380, __VA_ARGS__)
#define trgt_sci_set_meas_mode(...) _sci_set_meas_mode(0x6380, __VA_ARGS__)
#define trgt_sci_get_meas_value() _sci_get_meas_value(0x6380)
#define trgt_sci_meas_enable() _sci_meas_enable(0x6380)
#define trgt_sci_meas_disable() _sci_meas_disable(0x6380)
#define trgt_sci_set_dbc_filter(...) _sci_set_dbc_filter(0x6380, __VA_ARGS__)
#define trgt_sci_get_dbc_filter() _sci_get_dbc_filter(0x6380)

#endif /* __SCI_INST_H__ */
