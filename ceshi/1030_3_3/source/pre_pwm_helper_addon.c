#include "pre_pwm_helper_addon.h"

/**
 * @addtogroup PWM PRE-PWM&PWM module
 * @ingroup OTHER
 *
 * @{
 */

void pre_pwm_get_offset_phase_shift(const pre_pwm_table_entry table[], u16 bp_start_u, initial_values *values_000,
                                    initial_values *values_120, initial_values *values_240, pre_pwm_bp_max_t *bp_max)
{
  u16 last_segment = 0; // index
  u16 i = 0;
  u16 steps_count = 0;

  while (table[i].duration != 0)
  {
    steps_count = steps_count + table[i].duration;
    i++;
  }

  *bp_max = steps_count - 1; // maximal value to set // bp_max start is 0
  last_segment = i - 1;

  pre_pwm_get_offset_phase_shift_value(table, values_000, bp_start_u, last_segment);
  pre_pwm_get_offset_phase_shift_value(table, values_120, bp_start_u + (1 * steps_count + 1) / 3, last_segment);
  pre_pwm_get_offset_phase_shift_value(table, values_240, bp_start_u + (2 * steps_count + 1) / 3, last_segment);
}

void pre_pwm_get_offset_phase_shift_value(const pre_pwm_table_entry table[], initial_values *values_xxx, u16 steps,
                                          u16 last_segment)
{
  u16 i = 0;
  u16 offset = 0;
  u16 steps_count = 0;

  // find segment with overflow
  while (steps_count <= steps)
  {
    steps_count = steps_count + table[i].duration;
    (i == last_segment) ? i = 0 : i++;
  }

  values_xxx->reload_index = i;

  (i == 0) ? i = last_segment : i--;
  values_xxx->current_index = i;

  offset = steps_count - steps;
  values_xxx->duration = offset;
  values_xxx->slope_acc_start = table[i].slope_acc_start + (table[i].duration - offset) * table[i].slope;
}

void pre_pwm_set_initial_entry_direct(const pre_pwm_table_entry table[], const initial_values *values_000,
                                      const initial_values *values_120, const initial_values *values_240)
{

  pre_pwm_lw_rld_t lw_rld;
  pre_pwm_hw_rld_t hw_rld;
  lw_rld.val = 0;
  hw_rld.val = 0;

  // pre_pwm_enable_dma(false);
  pre_pwm_enable_inc(false);

  // 000 degree
  lw_rld.bf.duration = (values_000)->duration;
  lw_rld.bf.slope = table[(values_000)->current_index].slope;
  hw_rld.bf.slope_acc = (values_000)->slope_acc_start;
  hw_rld.bf.use_cfg_on = table[(values_000)->current_index].use_cfg_on;
  pre_pwm_set_reload(lw_rld, hw_rld, (u8)0);
  pre_pwm_set_addr((values_000)->reload_index * 4, (u8)0);

  // 120 degree
  lw_rld.bf.duration = (values_120)->duration;
  lw_rld.bf.slope = table[(values_120)->current_index].slope;
  hw_rld.bf.slope_acc = (values_120)->slope_acc_start;
  hw_rld.bf.use_cfg_on = table[(values_120)->current_index].use_cfg_on;
  pre_pwm_set_reload(lw_rld, hw_rld, (u8)1);
  pre_pwm_set_addr((values_120)->reload_index * 4, (u8)1);

  // 240 degree
  lw_rld.bf.duration = (values_240)->duration;
  lw_rld.bf.slope = table[(values_240)->current_index].slope;
  hw_rld.bf.slope_acc = (values_240)->slope_acc_start;
  hw_rld.bf.use_cfg_on = table[(values_240)->current_index].use_cfg_on;
  pre_pwm_set_reload(lw_rld, hw_rld, (u8)2);
  pre_pwm_set_addr((values_240)->reload_index * 4, (u8)2);
  // reload active values and table entries with atomic command for synchonized
  // tables
  REG_PRE_PWM_CMD = BIT_PRE_PWM_CMD_U_RELOAD | BIT_PRE_PWM_CMD_V_RELOAD | BIT_PRE_PWM_CMD_W_RELOAD |
                    BIT_PRE_PWM_CMD_U_DMA | BIT_PRE_PWM_CMD_V_DMA | BIT_PRE_PWM_CMD_W_DMA | BIT_PRE_PWM_CMD_UVW_SCALE;
}

/** @} */
