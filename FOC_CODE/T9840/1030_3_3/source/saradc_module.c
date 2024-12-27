#include "saradc_module.h"
#include "ADCSample.h"
#include "MotorAPI.h"
#include "debug.h"
#include "main.h"
#include "testmode.h"
#include <string.h>

/**
 * @addtogroup SARADC SARADC module
 * @ingroup OTHER
 *
 * @{
 */
 /* 低压不学习电流零点 23.08.28 by lxs */
#define SARADC_MODULE_CURRENT_ZERO_VOLT_MIN (100)

void saradc_config(u8 dead_time_wait_0, u8 dead_time_wait_1, u8 dead_time_wait_2)
{
  saradc_ctrl_set_dead_time_wait0((saradc_ctrl_dead_time_wait_t)dead_time_wait_0);
  saradc_ctrl_set_dead_time_wait1((saradc_ctrl_dead_time_wait_t)dead_time_wait_1);
  saradc_ctrl_set_dead_time_wait2((saradc_ctrl_dead_time_wait_t)dead_time_wait_2);
}

void saradc_swap_vw_channels(bool reverse)
{
  u16 ch_w;
  u16 ch_v;

  if (reverse)
  {
    // swap them
    ch_v = BEMF_W;
    ch_w = BEMF_V;
  }
  else
  {
    // v is v w is w
    ch_v = BEMF_V;
    ch_w = BEMF_W;
  }

  list_bemf_window_1[2].e2.no.ch = ch_v;
  list_bemf_window_1[3].e2.no.ch = ch_v;
  list_bemf_window_1[5].e2.no.ch = ch_v;

  list_bemf_window_2[2].e2.no.ch = ch_w;
  list_bemf_window_2[3].e2.no.ch = ch_w;
  list_bemf_window_2[5].e2.no.ch = ch_w;

  list_bemf_window_4[2].e2.no.ch = ch_v;
  list_bemf_window_4[3].e2.no.ch = ch_v;
  list_bemf_window_4[5].e2.no.ch = ch_v;

  list_bemf_window_5[2].e2.no.ch = ch_w;
  list_bemf_window_5[3].e2.no.ch = ch_w;
  list_bemf_window_5[5].e2.no.ch = ch_w;

  list_bemf_window_2[17].e2.no.ch = ch_w;
  list_bemf_window_3[17].e2.no.ch = ch_w;
  list_bemf_window_4[17].e2.no.ch = ch_v;
  list_bemf_window_5[17].e2.no.ch = ch_v;

  list_bemf_window_2[18].e2.no.ch = ch_w;
  list_bemf_window_3[18].e2.no.ch = ch_w;
  list_bemf_window_4[18].e2.no.ch = ch_v;
  list_bemf_window_5[18].e2.no.ch = ch_v;

  list_bemf_window_0[19].e2.no.ch = ch_v;
  list_bemf_window_1[19].e2.no.ch = ch_w;

  list_bemf_window_3[19].e2.no.ch = ch_v;
  list_bemf_window_4[19].e2.no.ch = ch_w;
}

static void saradc_swap_triggers(bool reverse)
{
  u16 u_r = U_u_r;
  u16 u_f = U_u_f;

  u16 v_r;
  u16 w_r;
  u16 v_f;
  u16 w_f;

  bool floating = is_pre_pwm_floating();

  if (reverse)
  {
    // swap them
    v_r = U_w_r;
    v_f = U_w_f;
    w_r = U_v_r;
    w_f = U_v_f;
  }
  else
  {
    // v is v w is w
    v_r = U_v_r;
    v_f = U_v_f;
    w_r = U_w_r;
    w_f = U_w_f;
  }

  if (!floating)
  {
    list_bemf_window_0[2].trigger = u_r;
    list_bemf_window_0[5].trigger = u_f;

    list_bemf_window_1[2].trigger = v_r;
    list_bemf_window_1[5].trigger = v_f;

    list_bemf_window_2[2].trigger = w_r;
    list_bemf_window_2[5].trigger = w_f;

    list_bemf_window_3[2].trigger = u_r;
    list_bemf_window_3[5].trigger = u_f;

    list_bemf_window_4[2].trigger = v_r;
    list_bemf_window_4[5].trigger = v_f;

    list_bemf_window_5[2].trigger = w_r;
    list_bemf_window_5[5].trigger = w_f;
  }
  else
  {
    u16 amult = PRE_PWM_GET_ABS_MULT;
    if (amult > (REG_PWMN_CNT_MAX_RELOAD >> 1))
    {
      // measure at the middle at higher speeds
      list_bemf_window_0[2].trigger =
        (w_r | u_f) & 0x0FFF; // | u_r and u_f prevents stuck todo wait for motcub to remove
      list_bemf_window_0[5].trigger = (v_f | u_r) & 0x0FFF;

      if (bldc_mode != sinus_stallcheck) // not necessary
      {
        list_bemf_window_1[2].trigger = (w_r | v_f) & 0x0FFF;
        list_bemf_window_1[5].trigger = (u_f | v_r) & 0x0FFF;

        list_bemf_window_2[2].trigger = (v_r | w_f) & 0x0FFF;
        list_bemf_window_2[5].trigger = (u_f | w_r) & 0x0FFF;

        list_bemf_window_3[2].trigger = (v_r | u_f) & 0x0FFF;
        list_bemf_window_3[5].trigger = (w_f | u_r) & 0x0FFF;

        list_bemf_window_4[2].trigger = (u_r | v_f) & 0x0FFF;
        list_bemf_window_4[5].trigger = (w_f | v_r) & 0x0FFF;

        list_bemf_window_5[2].trigger = (u_r | w_f) & 0x0FFF;
        list_bemf_window_5[5].trigger = (v_f | w_r) & 0x0FFF;
      }

    }
    else
    {
      // measure at the top/bottom to support low speeds
      list_bemf_window_0[2].trigger =
        (v_r | u_r) & 0x0FFF; // | u_r and u_f prevents stuck todo wait for motcub to remove
      list_bemf_window_0[5].trigger = (w_f | u_f) & 0x0FFF;

      if (bldc_mode != sinus_stallcheck) // not necessary
      {
        list_bemf_window_1[2].trigger = (u_r | v_r) & 0x0FFF;
        list_bemf_window_1[5].trigger = (w_f | v_f) & 0x0FFF;

        list_bemf_window_2[2].trigger = (u_r | w_r) & 0x0FFF;
        list_bemf_window_2[5].trigger = (v_f | w_f) & 0x0FFF;

        list_bemf_window_3[2].trigger = (w_r | u_r) & 0x0FFF;
        list_bemf_window_3[5].trigger = (v_f | u_f) & 0x0FFF;

        list_bemf_window_4[2].trigger = (w_r | v_r) & 0x0FFF;
        list_bemf_window_4[5].trigger = (u_f | v_f) & 0x0FFF;

        list_bemf_window_5[2].trigger = (v_r | w_r) & 0x0FFF;
        list_bemf_window_5[5].trigger = (u_f | w_f) & 0x0FFF;
      }

    }
  }
}

#define WINDOW_0_START DEG_TO_BP(30 + 60 * 5)
#define WINDOW_1_START DEG_TO_BP(30 + 60 * 0)
#define WINDOW_2_START DEG_TO_BP(30 + 60 * 1)
#define WINDOW_3_START DEG_TO_BP(30 + 60 * 2)
#define WINDOW_4_START DEG_TO_BP(30 + 60 * 3)
#define WINDOW_5_START DEG_TO_BP(30 + 60 * 4)

#define WINDOW_0_STOP WINDOW_1_START
#define WINDOW_1_STOP WINDOW_2_START
#define WINDOW_2_STOP WINDOW_3_START
#define WINDOW_3_STOP WINDOW_4_START
#define WINDOW_4_STOP WINDOW_5_START
#define WINDOW_5_STOP WINDOW_0_START

#define FIFDEGEND 2066

static void saradc_windowsize(void)
{
  if (bldc_mode == sinus_float)
  {
    list_bemf_window_0_overflow[1].e2.until.barrier = 3886;
    list_bemf_window_1[1].e2.until.barrier = FIFDEGEND + 2 * 1323 - 3969;
    list_bemf_window_2[1].e2.until.barrier = 3886 + 1 * 1323 - 3969;
    list_bemf_window_3[1].e2.until.barrier = FIFDEGEND;
    list_bemf_window_4[1].e2.until.barrier = 3886 + 2 * 1323 - 3969;
    list_bemf_window_5[1].e2.until.barrier = FIFDEGEND + 1 * 1323;

    list_bemf_window_0[7].e2.until.barrier = 83;
    list_bemf_window_1[7].e2.until.barrier = FIFDEGEND + 2 * 1323 - 3969;
    list_bemf_window_2[7].e2.until.barrier = 83 + 1 * 1323;
    list_bemf_window_3[7].e2.until.barrier = FIFDEGEND;
    list_bemf_window_4[7].e2.until.barrier = 83 + 2 * 1323;
    list_bemf_window_5[7].e2.until.barrier = FIFDEGEND + 1 * 1323;
  }
  else
  {
    list_bemf_window_0_overflow[1].e2.until.barrier = WINDOW_0_START;
    list_bemf_window_1[1].e2.until.barrier = WINDOW_1_START;
    list_bemf_window_2[1].e2.until.barrier = WINDOW_2_START;
    list_bemf_window_3[1].e2.until.barrier = WINDOW_3_START;
    list_bemf_window_4[1].e2.until.barrier = WINDOW_4_START;
    list_bemf_window_5[1].e2.until.barrier = WINDOW_5_START;

    list_bemf_window_0[7].e2.until.barrier = WINDOW_0_STOP;
    list_bemf_window_1[7].e2.until.barrier = WINDOW_1_STOP;
    list_bemf_window_2[7].e2.until.barrier = WINDOW_2_STOP;
    list_bemf_window_3[7].e2.until.barrier = WINDOW_3_STOP;
    list_bemf_window_4[7].e2.until.barrier = WINDOW_4_STOP;
    list_bemf_window_5[7].e2.until.barrier = WINDOW_5_STOP;
  }
}

// on bldc_mode change, on pre_pwm init or rotation change, on PWM higher than
// 50%
void saradc_swap_vw(bool reverse)
{
  saradc_swap_vw_channels(reverse);
  saradc_swap_triggers(reverse);
  saradc_windowsize();
}

void saradc_apply_list(saradc_table_list_entry *table, bool skip_list)
{
  saradc_ctrl_sadr_new_t sadr_new;
  sadr_new.bf.start_adr = ((u16)(table)) >> 1;
  sadr_new.bf.list_skip = skip_list;
  REG_SARADC_CTRL_SADR_NEW = sadr_new.val;
}

void saradc_window_control_V2_lowspeed_patch(u16 x)
{
  x = (x * READ_REG_U16(AADDR_PWMN_CNT_MAX_RELOAD)) << 1;

  if (bldc_mode == trapez_float || bldc_mode == sinus_float)
  {
    saradc_swap_vw(pre_pwm_is_reverse());
  }

  // only 15 degree 4 times more samples
  if (bldc_mode == sinus_float)
  {
    x = x >> 2;
  }
  // only 15 degree 4 times more samples
  if (bldc_mode == sinus_float && is_pre_pwm_floating())
  {
    list_bemf_window_0[6].target_adr = x >> 2;
  }
  else
  {
    list_bemf_window_0[6].target_adr = x;
  }

  list_bemf_window_1[6].target_adr = x;
  list_bemf_window_2[6].target_adr = x;
  list_bemf_window_3[6].target_adr = x;
  list_bemf_window_4[6].target_adr = x;
  list_bemf_window_5[6].target_adr = x;
}

void saradc_window_control_V2_patch(u8 nr, s16 shift_opt_phase)
{
  switch (nr)
  {
  case 0:
    list_bemf_start[0].e2.until.barrier = Motor_BasePhaseLimit(DEG_TO_BP(30 + 60 * 5) + (s16)shift_opt_phase);
    list_bemf_start[2].target_adr = (u16)list_bemf_window_0;
    break;
  case 1:
    list_bemf_start[0].e2.until.barrier = Motor_BasePhaseLimit(DEG_TO_BP(30 + 60 * 0) + (s16)shift_opt_phase);
    list_bemf_start[2].target_adr = (u16)list_bemf_window_1;
    break;
  case 2:
    list_bemf_start[0].e2.until.barrier = Motor_BasePhaseLimit(DEG_TO_BP(30 + 60 * 1) + (s16)shift_opt_phase);
    list_bemf_start[2].target_adr = (u16)list_bemf_window_2;
    break;
  case 3:
    list_bemf_start[0].e2.until.barrier = Motor_BasePhaseLimit(DEG_TO_BP(30 + 60 * 2) + (s16)shift_opt_phase);
    list_bemf_start[2].target_adr = (u16)list_bemf_window_3;
    break;
  case 4:
    list_bemf_start[0].e2.until.barrier = Motor_BasePhaseLimit(DEG_TO_BP(30 + 60 * 3) + (s16)shift_opt_phase);
    list_bemf_start[2].target_adr = (u16)list_bemf_window_4;
    break;
  case 5:
    list_bemf_start[0].e2.until.barrier = Motor_BasePhaseLimit(DEG_TO_BP(30 + 60 * 4) + (s16)shift_opt_phase);
    list_bemf_start[2].target_adr = (u16)list_bemf_window_5;
    break;
  default:
    break;
  }
}

static void saradc_window_control_V2(u8 nr)
{
#define zc_shift 12
  u16 *start = (bemf_voltage[nr & 0x1]);
  u16 *end = ((u16 *)(currentpulse[0][nr]));

  s16 diff = 0;

  s16 valid = 0;
  s32 sumy = 0; // sum y for averaging

  s16 y_avg = 0;

#if 0
  for (u16 *p = (start + 1); p < end; p += 3)
  {
#ifndef DISABLE_DIRECT_SMULT
    s16 reference = GPIO_ADC_VBAT;
    sumy += ((s16)(*p + *(p + 2))) - (s16)(reference);
    /* 刘贺刘工关于解决水泵不同负载失步的临时参考代码，暂时保留 24.01.05 by lxs  */
    //sumy += ((s16)(*p + *(p + 2)));
#else
    sumy += ((s16)(*p + *(p + 2))) - (s16)(*(p + 1));
#endif
    valid++;
    y_avg = divider_sdiv(sumy, valid << 1);
  }

  diff = y_avg; // bx is not used, because the points are nearly equally
                // distributed and the slope can only be near 1
  /* 刘贺刘工关于解决水泵不同负载失步的临时参考代码，暂时保留 24.01.05 by lxs  */
  //diff = (y_avg - GPIO_ADC_VBAT/2)/GPIO_ADC_VBAT * 1365;
#else
  s16 reference = GPIO_ADC_VBAT;

  for (u16 *p = (start + 1); p < end; p += 3)
  {
    sumy += ((s16)(*p + *(p + 2)));
    valid++;
  }
  
  y_avg = divider_sdiv(sumy, valid);
  /* 通过计算偏差的百分比来表征角度的误差 24.01.11 by lxs */
  diff = (s16)((((s32)y_avg - (s32)reference) * 1000) / (s32)reference);

#endif

  if ((nr & 0x1) == 0)
  {
    diff = -diff;
  }

  if (pre_pwm_get_sinc() < 0)
  {
    diff = -diff;
  }

  if (bemf_control_get_mode() == mode_closed)
  {
    bemf_control_call(diff, nr);
  }

}

void clarke_trans(s16 u, s16 v, s16 w, s16 *alpha, s16 *beta)
{
  *alpha = (2 * u - v - w);
  *beta = divider_sdiv(((s32)(v - w)) * 13775, 7953);
}

u16 uvw_theta(int32_t u, int32_t v, int32_t w)
{
  s16 a;
  s16 b;

  s16 div_max = 0;
  div_max = MAX(div_max, ABS(u) >> 12); // 12bit like ADC measurement
  div_max = MAX(div_max, ABS(v) >> 12);
  div_max = MAX(div_max, ABS(w) >> 12);
  if (div_max != 0)
  {
    u = divider_sdiv(u, div_max);
    v = divider_sdiv(v, div_max);
    w = divider_sdiv(w, div_max);
  }

  clarke_trans(u, v, w, &a, &b);
  return atan2Lerp_BP((int16_t)a, (int16_t)b);
}

u16 ab_theta(int32_t a, int32_t b)
{
  // limit input for atan calculation
  for (u8 var = 0; var < 16; ++var)
  {
    if ((ABS(a) < (INT16_MAX)) && (ABS(b) < (INT16_MAX)))
    {
      break;
    }
    else
    {
      a = a >> 1;
      b = b >> 1;
    }
  }
  return atan2Lerp_BP((int16_t)a, (int16_t)b);
}

void ADCListDoneHandler2(void)
{
  void *done = (void *)READ_REG_U16(AADDR_SARADC_CTRL_SADR_DONE);

  u8 window = 0xFF;

  if (done == list_bemf_window_0)
  {
    window = 0;
    ADCResults.RawAD.Current.Sector0 = (GPIO_I_DC >> 4);
  }
  else if (done == list_bemf_window_1)
  {
    window = 1;
    ADCResults.RawAD.Current.Sector1 = (GPIO_I_DC >> 4);
  }
  else if (done == list_bemf_window_2)
  {
    window = 2;
    ADCResults.RawAD.Current.Sector2 = (GPIO_I_DC >> 4);
  }
  else if (done == list_bemf_window_3)
  {
    window = 3;
    ADCResults.RawAD.Current.Sector3 = (GPIO_I_DC >> 4);
  }
  else if (done == list_bemf_window_4)
  {
    window = 4;
    ADCResults.RawAD.Current.Sector4 = (GPIO_I_DC >> 4);
  }
  else if (done == list_bemf_window_0_overflow)
  {
    window = 5;
    ADCResults.RawAD.Current.Sector5 = (GPIO_I_DC >> 4);
  }
  else if (done == list_windmill)
  {
    /* fct test, 21.07.30 by yhd */
    if (!testmode_BrigeOutEn)
    {
      /* 电压小于10V时不学习电流零点 23.06.28 by lxs */
      if (ADCResults.Voltage.Bat > SARADC_MODULE_CURRENT_ZERO_VOLT_MIN)
      {
        ADCResults.RawAD.Current.Zero = (GPIO_I_DC >> 4);
      }

      ADCResults.RawAD.Current.Sector0 = ADCResults.RawAD.Current.Zero;
      ADCResults.RawAD.Current.Sector1 = ADCResults.RawAD.Current.Zero;
      ADCResults.RawAD.Current.Sector2 = ADCResults.RawAD.Current.Zero;
      ADCResults.RawAD.Current.Sector3 = ADCResults.RawAD.Current.Zero;
      ADCResults.RawAD.Current.Sector4 = ADCResults.RawAD.Current.Zero;
      ADCResults.RawAD.Current.Sector5 = ADCResults.RawAD.Current.Zero;
    }
    else
    {
      u16 tmp = (GPIO_I_DC >> 4);
      ADCResults.RawAD.Current.Sector0 = tmp;
      ADCResults.RawAD.Current.Sector1 = tmp;
      ADCResults.RawAD.Current.Sector2 = tmp;
      ADCResults.RawAD.Current.Sector3 = tmp;
      ADCResults.RawAD.Current.Sector4 = tmp;
      ADCResults.RawAD.Current.Sector5 = tmp;
    }

    Motor_CaculateWindmillPosition();
  }
  else
  {
  }

  if (window != 0xFF)
  {
    saradc_window_control_V2(window);
  }
}

/** @} */
