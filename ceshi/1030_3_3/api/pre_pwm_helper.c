#include "pre_pwm_helper.h"
#include "pre_pwm_helper_addon.h"
#include "pre_pwm_module.h"

// void pre_pwm_set_scale_mult (u16 mult)
//{
//  pre_pwm_scale_t scale;
//  scale = pre_pwm_get_scale();
//  scale.bf.scale = mult;
//  pre_pwm_set_scale(scale);
//}

// void pre_pwm_set_scale_shift (u16 shift)
//{
//  pre_pwm_scale_t scale;
//  scale = pre_pwm_get_scale();
//  scale.bf.scale_shift = shift;
//  pre_pwm_set_scale(scale);
//}

void get_phase_shift(const pre_pwm_table_entry table[], initial_values *values_120, initial_values *values_240,
                     pre_pwm_bp_max_t *bp_max)
{

  int steps_count = 0;
  int i = 0; // index
  int steps_count_third = 0;
  int segment_count;
  while (table[i].duration != 0)
  {
    steps_count = steps_count + table[i].duration;
    i = i + 1;
  }
  *bp_max = steps_count - 1;
  segment_count = i;
  steps_count_third = steps_count / 3;
  //_print_d_value("Steps_count: ",steps_count, " ; ");
  //_print_d_value("Steps_count_third: ",steps_count_third, " ; ");
  //_print_d_value("Segment_count: ",segment_count, " ;\n ");

  i = 0;
  int new_steps_count = 0;
  int offset;
  while (new_steps_count <= steps_count_third)
  {
    new_steps_count = new_steps_count + table[i].duration;
    i = i + 1;
  }
  if (i < segment_count)
  {
    (*values_120).reload_index = i;
  }
  else
  {
    (*values_120).reload_index = 0;
  }
  i = i - 1;
  (*values_120).current_index = i;
  offset = new_steps_count - steps_count_third;

  (*values_120).slope_acc_start = table[i].slope_acc_start + (table[i].duration - offset) * table[i].slope;

  (*values_120).duration = offset;
  //_print_d_value("initial slope_acc: ",(*values_120).slope_acc_start, " ; ");
  //_print_d_value("intitial duration: ",(*values_120).duration, " ; ");
  //_print_d_value("reload_index_120: ",(*values_120).reload_index, " ;\n ");

  i = 0;
  new_steps_count = 0;
  while (new_steps_count <= (2 * steps_count_third))
  {
    new_steps_count = new_steps_count + table[i].duration;
    i = i + 1;
  }
  if (i < segment_count)
  {
    (*values_240).reload_index = i;
  }
  else
  {
    (*values_240).reload_index = 0;
  }
  i = i - 1;
  (*values_240).current_index = i;
  offset = new_steps_count - (2 * steps_count_third);
  (*values_240).slope_acc_start = table[i].slope_acc_start + ((table[i].duration - offset) * table[i].slope);
  (*values_240).duration = offset;
  //_print_d_value("initial slope_acc: ", (*values_240).slope_acc_start, " ; ");
  //_print_d_value("intitial duration:: ",(*values_240).duration, " ; ");
  //_print_d_value("reload_index_240: ",(*values_240).reload_index, " ;\n ");
}

void pre_pwm_get_base_phase_state(pre_pwm_inc_t *inc, pre_pwm_acc_t *acc, pre_pwm_base_phase_t *base_phase)
{
  *inc = pre_pwm_get_sinc();
  *acc = PRE_PWM_GET_ACC;
  *base_phase = PRE_PWM_GET_BP;
}

void pre_pwm_init_base_phase(pre_pwm_acc_t acc, pre_pwm_base_phase_t base_phase, pre_pwm_bp_max_t bp_max)
{
  // is not used pre_pwm_set_inc_sync(inc_sync);
  PRE_PWM_SET_ACC(acc);
  PRE_PWM_SET_BP(base_phase);
  WRITE_REG_16(AADDR_PRE_PWM_BP_MAX, bp_max);
}

// void pre_pwm_init_scale(pre_pwm_scale_offset_t offset0, pre_pwm_scale_offset_t offset1, pre_pwm_scale_t scale){

//  pre_pwm_set_scale_offset(offset0,(uint8_t)0);
//  pre_pwm_set_scale_offset(offset1,(uint8_t)1);
//  pre_pwm_set_smult(scale.bf.scale);
//  pre_pwm_set_scale_shift(scale.bf.scale_shift);
//  //is not used pre_pwm_set_scale_sync(scale_sync);
//}

void pre_pwm_enable_inc(bool value)
{
  pre_pwm_cfg_t cfg;
  cfg = pre_pwm_get_cfg();
  if (value == true)
  {
    cfg.bf.inc_en = 1;
  }
  else
  {
    cfg.bf.inc_en = 0;
  }
  pre_pwm_set_cfg(cfg);
}

void pre_pwm_enable_dma(bool value)
{
  pre_pwm_cfg_t cfg;
  cfg = pre_pwm_get_cfg();
  if (value == true)
  {
    cfg.bf.dma_en = 1;
  }
  else
  {
    cfg.bf.dma_en = 0;
  }
  pre_pwm_set_cfg(cfg);
}

void pre_pwm_cfg_on_state(uint16_t value)
{
  pre_pwm_cfg_t cfg;
  cfg = pre_pwm_get_cfg();
  cfg.bf.on_state = value;
  pre_pwm_set_cfg(cfg);
}

void pre_pwm_swap_uv(bool value)
{
  pre_pwm_cfg_t cfg;
  cfg = pre_pwm_get_cfg();
  if (value == true)
  {
    cfg.bf.swap_uv = 1;
  }
  else
  {
    cfg.bf.swap_uv = 0;
  }
  pre_pwm_set_cfg(cfg);
}

void pre_pwm_switch_gd_td(bool value)
{
  pre_pwm_cfg_t cfg;
  cfg = pre_pwm_get_cfg();
  if (value == true)
  {
    cfg.bf.switch_gd_td = 1;
  }
  else
  {
    cfg.bf.switch_gd_td = 0;
  }
  pre_pwm_set_cfg(cfg);
}

/*
00 : BP_SYNC0 unused
01 : bps0 match event and sync reload event generation enabled
10 : bps0 match event generation enabled
*/
void pre_pwm_enable_sync0(uint8_t bps0)
{
  pre_pwm_sync_en_t sync_en;
  sync_en = pre_pwm_get_sync_en();
  sync_en.bf.bps0 = bps0;
  pre_pwm_set_sync_en(sync_en);
}

/*
00 : BP_SYNC1 unused
01 : sync capture event generation enabled
10 : bps1 match event generation enabled
*/
void pre_pwm_enable_sync1(uint8_t bps1)
{
  pre_pwm_sync_en_t sync_en;
  sync_en = pre_pwm_get_sync_en();
  sync_en.bf.bps1 = bps1;
  pre_pwm_set_sync_en(sync_en);
}

void pre_pwm_sync_cfg_src(uint16_t value)
{
  pre_pwm_sync_ext_cfg_t sync_cfg;
  sync_cfg = pre_pwm_get_sync_ext_cfg();
  sync_cfg.bf.src = value;
  pre_pwm_set_sync_ext_cfg(sync_cfg);
}

void pre_pwm_sync_cfg_intf(uint16_t value)
{
  pre_pwm_sync_ext_cfg_t sync_cfg;
  sync_cfg = pre_pwm_get_sync_ext_cfg();
  sync_cfg.bf.intf = value;
  pre_pwm_set_sync_ext_cfg(sync_cfg);
}
void pre_pwm_sync_intf_set(bool clear, uint16_t state)
{
  pre_pwm_sync_ext_cfg_t sync_cfg;
  sync_cfg = pre_pwm_get_sync_ext_cfg();
  if (clear == true)
  {
    sync_cfg.bf.intf_set = 2 + state;
  }
  else
  {
    sync_cfg.bf.intf_set = state;
  }
  pre_pwm_set_sync_ext_cfg(sync_cfg);
}
void pre_pwm_sync_edge(uint16_t value)
{
  pre_pwm_sync_ext_cfg_t sync_cfg;
  sync_cfg = pre_pwm_get_sync_ext_cfg();
  sync_cfg.bf.edge = value;
  pre_pwm_set_sync_ext_cfg(sync_cfg);
}
