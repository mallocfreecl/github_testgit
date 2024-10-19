#ifndef HAVE_SARADC_CTRL_H
#define HAVE_SARADC_CTRL_H

#include "base.h"

#include "saradc_ctrl_bf.h"
#include "saradc_ctrl_irq.h"

#include "vic.h"

typedef struct
{
  volatile uint16_t target_adr : 16;      /* [15:0]  */
  volatile uint16_t no_sample : 4;        /* [19:16] */
  volatile uint16_t no_sum : 5;           /* [24:20] */
  volatile uint16_t ch_no : 5;            /* [29:25] */
  volatile uint16_t trigger_type_ext : 1; /* [30]    */
  volatile uint16_t trigger_type : 1;     /* [31]    */
  volatile uint16_t trigger : 16;         /* [47:32] */
} saradc_ctrl_list_entry;

typedef struct
{
  volatile uint16_t no_sample : 4;        /* [19:16] */
  volatile uint16_t no_sum : 5;           /* [24:20] */
  volatile uint16_t ch_no : 5;            /* [29:25] */
  volatile uint16_t trigger_type_ext : 1; /* [30]    */
  volatile uint16_t trigger_type : 1;     /* [31]    */
} _PACKED_ saradc_ctrl_list_item_l1_bf;

typedef union {
  volatile uint16_t val;
  volatile saradc_ctrl_list_item_l1_bf bf;
} _PACKED_ saradc_ctrl_list_item_l1_t;

typedef enum
{
  SARADC_MOTOR_CHANNEL_U = 0,
  SARADC_MOTOR_CHANNEL_V = 1,
  SARADC_MOTOR_CHANNEL_W = 2
} saradc_motor_channel_t;
/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void saradc_ctrl_set_cfg(saradc_ctrl_cfg_t cfg);
saradc_ctrl_cfg_t saradc_ctrl_get_cfg(void);

void saradc_ctrl_set_cfg_sar_timing(saradc_ctrl_cfg_sar_timing_t cfg_sar_timing);
saradc_ctrl_cfg_sar_timing_t saradc_ctrl_get_cfg_sar_timing(void);

void saradc_ctrl_set_dead_time_wait0(saradc_ctrl_dead_time_wait_t dead_time_wait);
void saradc_ctrl_set_dead_time_wait1(saradc_ctrl_dead_time_wait_t dead_time_wait);
void saradc_ctrl_set_dead_time_wait2(saradc_ctrl_dead_time_wait_t dead_time_wait);
saradc_ctrl_dead_time_wait_t saradc_ctrl_get_dead_time_wait0(void);
saradc_ctrl_dead_time_wait_t saradc_ctrl_get_dead_time_wait1(void);
saradc_ctrl_dead_time_wait_t saradc_ctrl_get_dead_time_wait2(void);

void saradc_ctrl_set_dead_time_auto_ch(saradc_motor_channel_t motor_channel, uint8_t adc_channel);

void saradc_ctrl_set_dead_time_delay(saradc_ctrl_dead_time_delay_t dead_time_delay);
saradc_ctrl_dead_time_delay_t saradc_ctrl_get_dead_time_delay(void);

void saradc_ctrl_set_sync_out_cfg(saradc_ctrl_sync_out_cfg_t sync_out_cfg);
saradc_ctrl_sync_out_cfg_t saradc_ctrl_get_sync_out_cfg(void);

void saradc_ctrl_set_sync_out_trig(saradc_ctrl_sync_out_trig_t sync_out_trig);
saradc_ctrl_sync_out_trig_t saradc_ctrl_get_sync_out_trig(void);

void saradc_ctrl_set_cmd(saradc_ctrl_cmd_t cmd);

void saradc_ctrl_set_wadr_min(saradc_ctrl_wadr_min_t wadr_min);
saradc_ctrl_wadr_min_t saradc_ctrl_get_wadr_min(void);

void saradc_ctrl_set_wadr_max(saradc_ctrl_wadr_max_t wadr_max);
saradc_ctrl_wadr_max_t saradc_ctrl_get_wadr_max(void);

void saradc_ctrl_set_sadr_new(saradc_ctrl_sadr_new_t sadr_new);

saradc_ctrl_sadr_current_t saradc_ctrl_get_sadr_current(void);

saradc_ctrl_l0_current_t saradc_ctrl_get_l0_current(void);
saradc_ctrl_l1_current_t saradc_ctrl_get_l1_current(void);
saradc_ctrl_l2_current_t saradc_ctrl_get_l2_current(void);
saradc_ctrl_tadr_t saradc_ctrl_get_tadr(void);

saradc_ctrl_adr_next_t saradc_ctrl_get_adr_next(void);

saradc_ctrl_sadr_done_t saradc_ctrl_get_sadr_done(void);

saradc_ctrl_state_t saradc_ctrl_get_state(void);

void saradc_ctrl_set_irq_mask(saradc_ctrl_irq_mask_t irq_mask);
saradc_ctrl_irq_mask_t saradc_ctrl_get_irq_mask(void);

void saradc_ctrl_test_enable_all_irqs(void);
/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

void saradc_ctrl_handler_init(void);

void saradc_ctrl_handler_register(saradc_ctrl_irq_t irq, callback_t callback);

void saradc_ctrl_enable_irq(saradc_ctrl_irq_t irq, bool enable);

saradc_ctrl_irq_status_t saradc_ctrl_get_irq_status(void);

void saradc_ctrl_clear_all_irq_events(void);

#define saradc_ctrl_handler_register(irq, cb) irq_handler_register(VIC_IRQ_ADC_CTRL, irq, cb)

#define saradc_ctrl_enable_irq(irq, en)                                                                                \
  {                                                                                                                    \
    if (en)                                                                                                            \
      irq_enable(VIC_IRQ_ADC_CTRL, irq);                                                                               \
    else                                                                                                               \
      irq_disable(VIC_IRQ_ADC_CTRL, irq);                                                                              \
  }

#define saradc_ctrl_get_irq_status() ((saradc_ctrl_irq_status_t)(unsigned short)irq_get_status(VIC_IRQ_ADC_CTRL))

#define saradc_ctrl_clear_all_irq_events() irq_clear_all_events(VIC_IRQ_ADC_CTRL)

#endif /* HAVE_SARADC_CTRL_H */
