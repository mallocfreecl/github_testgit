#ifndef HAVE_PRE_PWM_HELPER_H
#define HAVE_PRE_PWM_HELPER_H

#include "pre_pwm.h"

typedef struct
{
  volatile uint16_t duration : 16;        // 9;
  volatile uint16_t slope_acc_start : 16; // 15;
  volatile uint16_t current_index : 16;   // 8;
  volatile uint16_t reload_index : 16;    // 8;
} _PACKED_ initial_values;

void get_phase_shift(const pre_pwm_table_entry table[], initial_values *values_120, initial_values *values_240,
                     pre_pwm_bp_max_t *bp_max);

void pre_pwm_get_base_phase_state(pre_pwm_inc_t *inc, pre_pwm_acc_t *acc, pre_pwm_base_phase_t *base_phase);

void pre_pwm_init_base_phase(pre_pwm_acc_t acc, pre_pwm_base_phase_t base_phase, pre_pwm_bp_max_t bp_max);

// void pre_pwm_init_scale(pre_pwm_scale_offset_t offset0, pre_pwm_scale_offset_t offset1, pre_pwm_scale_t scale);

void pre_pwm_enable_inc(bool value);
void pre_pwm_enable_dma(bool value);
void pre_pwm_cfg_off(uint16_t value);
void pre_pwm_swap_uv(bool value);

void pre_pwm_switch_gd_td(bool value);

void pre_pwm_enable_sync0(uint8_t bps0);
void pre_pwm_enable_sync1(uint8_t bps1);
void pre_pwm_sync_cfg_src(uint16_t value);
void pre_pwm_sync_cfg_intf(uint16_t value);
void pre_pwm_sync_intf_set(bool clear, uint16_t state);
void pre_pwm_sync_edge(uint16_t value);
// void pre_pwm_set_scale_mult (u16 mult);
// void pre_pwm_set_scale_shift (u16 shift);

void pre_pwm_cfg_on_state(uint16_t value);

#endif /* HAVE_PRE_PWM_HELPER_H */
