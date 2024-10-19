#include <stdint.h>

#include "api.h"
#include "irq.h"
#include "main.h"
#include "pre_pwm_helper_addon.h"
#include "pre_pwm_module.h"
#include "pre_pwm_tables.h"
#include "pwmn.h"
#include "saradc_module.h"
#include "testmode.h"

/**
 * @addtogroup PWM PRE-PWM&PWM module
 * @ingroup OTHER
 *
 * @{
 */

s16 pre_pwm_shadow_reg_smult = 0;
s16 pre_pwm_shadow_reg_sinc = 0;

bool pre_pwm_shadow_reg_reverse_direction = false;
bool pre_pwm_shadow_reg_inverse_torque = false;

void pre_pwm_init(void)
{
  pre_pwm_handler_init();

  // used for open loop startup
  pre_pwm_handler_register(PRE_PWM_IRQ_BPS0_EVT, pre_pwm_irq_handler_bp_0);
  pre_pwm_enable_irq(PRE_PWM_IRQ_BPS0_EVT, false);
  pre_pwm_set_bp_sync0(0);
  pre_pwm_enable_sync0(2);

  // zero crossing gpio
  pre_pwm_handler_register(PRE_PWM_IRQ_BPS1_EVT, pre_pwm_irq_handler_bp_1);
  pre_pwm_enable_irq(PRE_PWM_IRQ_BPS1_EVT, true);
  pre_pwm_set_bp_sync1(0);
  pre_pwm_enable_sync1(2);
  pre_pwm_enable_float(false);
}

void pre_pwm_config_online(pre_pwm_bp_max_t bp_max, u16 wave_offset_0, u16 wave_offset_1)
{
  pre_pwm_set_scale_offset((pre_pwm_scale_offset_t)wave_offset_0, (u8)0);
  pre_pwm_set_scale_offset((pre_pwm_scale_offset_t)wave_offset_1, (u8)1);
  // 18222 is magic from the hardware designer
  pre_pwm_init_base_phase((pre_pwm_acc_t)18222, (pre_pwm_base_phase_t)0, bp_max);
}

void pre_pwm_config_online_inc(s16 inc)
{
  pre_pwm_set_sinc(inc);
  inc_controller.state.sum_error = ((s32)(inc) << SCALE_INC);
}

void pre_pwm_config_online_scale(s16 scale_mult, u8 scale_shift)
{
  pre_pwm_set_smult(scale_mult);
  mult_controller.state.sum_error = ((s32)(scale_mult) << SCALE_MULT);
}

static void pre_pwm_set_phase_internal(u16 start_phase_u, pre_pwm_bp_max_t *bp_max, bool init_bp, bool vw_swap)
{
  const pre_pwm_table_entry *table_entry_array = (pre_pwm_table_entry *)pre_pwm_get_addr_base();

  initial_values values_000, values_120, values_240;

  // calculate correct values for 120? and 240? pointers
  pre_pwm_get_offset_phase_shift(table_entry_array, start_phase_u, &values_000, &values_120, &values_240, bp_max);
  if (vw_swap)
  {
    pre_pwm_set_initial_entry_direct(table_entry_array, &values_000, &values_240, &values_120);
  }
  else
  {
    pre_pwm_set_initial_entry_direct(table_entry_array, &values_000, &values_120, &values_240);
  }

  if (init_bp)
  {
    pre_pwm_set_acc(1);
    PRE_PWM_SET_BP(start_phase_u);
  }
}

void pre_pwm_set_phase(u16 start_phase_u, bool init_bp, bool vw_swap)
{

  pre_pwm_bp_max_t bp_max;
  pre_pwm_set_phase_internal(start_phase_u, &bp_max, init_bp, vw_swap);
  pre_pwm_enable_dma(true);
}

void pre_pwm_config_offline(bool pwm_run, pre_pwm_bp_max_t *bp_max, u16 *wave_offset_0, u16 *wave_offset_1,
                            u16 deadtime, u8 table_select, pre_pwm_table_entry **table_entry_array, u16 start_phase_u,
                            bool swap_uv)
{

  pre_pwm_set_default_table(wave_offset_0, wave_offset_1, 0);
  // stop pre_pwmn dma and inc and set table base adress
  pre_pwm_enable_dma(false);
  pre_pwm_enable_inc(false);

  // command to reload right values from reload
  pre_pwm_cmd_t cmd;
  cmd.val = 0; // sync feature disabled
  cmd.bf.u_reload = 1;
  cmd.bf.v_reload = 1;
  cmd.bf.w_reload = 1;
  cmd.bf.uvw_scale = 1;
  pre_pwm_set_cmd(cmd);

  // wait if dma not already preloaded next values
  pre_pwm_irq_status_t irq_status;
  do
  {
    irq_status.val = ((unsigned short)irq_get_status(VIC_IRQ_PRE_PWM));
  } while (irq_status.bf.u_dma_rdy == 0 || irq_status.bf.v_dma_rdy == 0 || irq_status.bf.w_dma_rdy == 0);

  // skipp first table entry (is already preloaded)
  cmd.val = 0;
  cmd.bf.u_dma = 1;
  cmd.bf.v_dma = 1;
  cmd.bf.w_dma = 1;
  pre_pwm_set_cmd(cmd);

  // disable sync_in_ext input
  pre_pwm_sync_cfg_intf((unsigned short)127); // intf - external sync signal integration filter
                                              // threshold value
  pre_pwm_sync_intf_set(true, (unsigned short)0);

  pre_pwm_set_phase_internal(start_phase_u, bp_max, true, false);

  // start inc and enable reload
  pre_pwm_enable_dma(true);
  pre_pwm_enable_inc(pwm_run);
}

void pre_pwm_set_default_table(u16 *wave_offset_0, u16 *wave_offset_1, u8 table)
{
  switch (table)
  {
#ifdef WAVE_SVM
  case 0:
    REG_PRE_PWM_ADDR_BASE = (u16)table_entry_svm;
    *wave_offset_0 = (UINT16_MAX) >> 2;
    *wave_offset_1 = REG_PWMN_CNT_MAX_RELOAD >> 1;
    break;
#endif
#ifdef WAVE_FLAT
  case 1:
    REG_PRE_PWM_ADDR_BASE = (u16)table_entry_flat_bottom;
    *wave_offset_0 = 0;
    *wave_offset_1 = 0;
    break;
#endif
  default:
    break;
  }
  REG_PRE_PWM_SCALE_OFFSET0 = *wave_offset_0;
  REG_PRE_PWM_SCALE_OFFSET1 = *wave_offset_1;
}

// Enable Open-loop mode
void pre_pwm_irq_handler_bp_0_enable(bool set)
{
  pre_pwm_enable_irq(PRE_PWM_IRQ_BPS0_EVT, set);
}

void pre_pwm_irq_handler_bp_0(int irq)
{
}

// Patch current measurements
void pre_pwm_irq_handler_bp_1(int irq)
{
  pre_pwm_set_bp_sync1(Motor_BasePhaseLimit(shift_wave));
}

inline s16 pre_pwm_get_sinc(void)
{
  return pre_pwm_shadow_reg_sinc;
}

inline s16 pre_pwm_get_smult(void)
{
  return pre_pwm_shadow_reg_smult;
}

bool pre_pwm_is_reverse(void)
{
  return pre_pwm_shadow_reg_reverse_direction;
}

u16 pre_pwm_get_angle(void)
{

  int16_t modified_bp = (READ_REG_U16(AADDR_PRE_PWM_BASE_PHASE));
  modified_bp = (BP_MAX >> 1) - modified_bp;
  modified_bp = Motor_BasePhaseLimit(modified_bp);

  return modified_bp;
}

// assertion smult has to be in ragnge of +- 1024
void pre_pwm_set_sinc_smult_init(s16 sinc, s16 smult, bool init, bool set_mult)
{

  bool is_rev = (bool)((sinc < 0)); // rotation direction
  bool rev_change = (bool)(pre_pwm_shadow_reg_reverse_direction != is_rev);

  // three cases -> motcub two cases
  // both is_rev+inv   -> mirror at 180 degree
  // only is_rev     -> mirror at 90 degree
  // only is_inv     -> shift by 180 degree

  if (rev_change || init)
  {
    CLI();

    // read bp
    s16 modified_bp = (READ_REG_U16(AADDR_PRE_PWM_BASE_PHASE));

    // init with reverse or direction change jump
    if (!(init && sinc > 0))
    {
      modified_bp = (BP_MAX >> 1) - modified_bp;
    }
    modified_bp = Motor_BasePhaseLimit(modified_bp);

    saradc_swap_vw(is_rev);
    pre_pwm_enable_inc(false);
    pre_pwm_set_phase(modified_bp, true, is_rev);
    if (!init)
    {
      pre_pwm_enable_inc(true);
    }
    SEI();

    pre_pwm_shadow_reg_reverse_direction = is_rev;
  }

  pre_pwm_shadow_reg_sinc = sinc;
  pre_pwm_shadow_reg_smult = smult;
  u16 ainc = ABS(sinc);

  // adapt sampling to get no overflow for low speeds
  static u8 last_sampled_pwm_edges = UINT8_MAX;
  u8 sampled_pwm_edges = divider_udiv(600 << 1, ainc); // ACC of 17bit in MOTCUB//3values

  if (last_sampled_pwm_edges != sampled_pwm_edges)
  {
    saradc_window_control_V2_lowspeed_patch(sampled_pwm_edges);
    last_sampled_pwm_edges = sampled_pwm_edges;
  }

  REG_PRE_PWM_INC = ainc * PAR_SYS_CLK_DEVIDER;

  if (pre_pwm_shadow_reg_reverse_direction)
  {
    smult = -smult;
  }

  s16 max = (REG_PWMN_CNT_MAX_RELOAD * PAR_SYS_CLK_DEVIDER);
    smult = (s16)((s32)smult * SCIDebug.Motor.OverModulateK / 1000);
#if 0
  if(smult > +(max))
  {
    smult = +max;
  }
  else if(smult < -(max))
  {
    smult = -max;
  }
  else
  {

  }
#endif
  pre_pwm_scale_t scale;
  scale.bf.scale = smult;
  scale.bf.scale_shift = DEFAULT_MULT_SHIFT;
  REG_PRE_PWM_SCALE = scale.val;
}

void pre_pwm_set_sinc(s16 sinc)
{
  pre_pwm_set_sinc_smult_init(sinc, pre_pwm_shadow_reg_smult, false, true);
}

void pre_pwm_set_smult(s16 smult)
{
  pre_pwm_set_sinc_smult_init(pre_pwm_shadow_reg_sinc, smult, false, true);
}

void pre_pwm_enable_float(bool enable)
{
  pre_pwm_cfg_t cfg;
  cfg.val = REG_PRE_PWM_CFG;
  if (enable)
  {
    cfg.bf.on_state = 0;
  }
  else
  {
    cfg.bf.on_state = 3;
  }
  REG_PRE_PWM_CFG = cfg.val;
}

bool is_pre_pwm_floating(void)
{
  pre_pwm_cfg_t cfg;
  cfg.val = REG_PRE_PWM_CFG;
  return (!(cfg.bf.on_state));
}

/** @} */
