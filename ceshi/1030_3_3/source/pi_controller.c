
#include "pi_controller.h"
#include "divider.h"
#include "pre_pwm_helper_addon.h"
#include <stdio.h>

/**
 * @defgroup Controller Controller module
 * @ingroup OTHER
 * This module implements an PI controller.
 * @{
 */

void pi_controller_init(pi_ctrl_data_t *pi_controller, u16 Kp, u16 Ki, s32 min, s32 max, u16 scaling_factor,
                        u16 Ki_shift_gain)
{
  // init state
  pi_controller->state.sum_error = 0;
  pi_controller->state.lastValue = 0;
  pi_controller->state.rest = 0;
  // pi_controller->state.norm = multiplier;

  // init parameter
  pi_controller->param.Kp = Kp;
  pi_controller->param.Ki = Ki;
  pi_controller->param.scaling_factor = scaling_factor;
  // pi_controller->param.max = ((s32)max) << scaling_factor;
  // pi_controller->param.min = ((s32)min) << scaling_factor;
  pi_controller->param.max = max;
  pi_controller->param.min = min;
  pi_controller->param.Ki_shift_gain = Ki_shift_gain;
}

s32 pi_controller_call(pi_ctrl_data_t *pi, s16 error, u16 divider)
{
  s32 y_p, y_i, diff;

  if (pi->param.Ki != 0)
  {

    if (divider != 0 && divider != 0xFFFF)
    {
      divider = divider >> pi->param.Ki_shift_gain;
      if (divider == 0)
      {
        divider = 1;
      }
      diff = divider_sdiv((((s32)pi->param.Ki * (s32)error)) + (s32)pi->state.rest, divider);
      pi->state.rest = (divider_get_sdiv_remainder());
    }
    else
    {
      diff = (s32)pi->param.Ki * (s32)error;
    }
  }
  else
  {
    diff = 0;
  }

  //*************** P-term ***************//
  if (divider == 0xFFFF)
  {
    s32 ainc = (s32)PRE_PWM_GET_ABS_INC;
    y_p = ((s32)pi->param.Kp * (((s32)error * ainc) >> 6));
  }
  else
  {
    y_p = ((s32)pi->param.Kp * (s32)error);
  }

  //*************** I-term ***************//
  y_i = pi->state.sum_error + diff;

  //*************** Limitation Sum Error***************//
  if (y_i > pi->param.max)
  {
    y_i = pi->param.max;
  }
  if (y_i < pi->param.min)
  {
    y_i = pi->param.min;
  }

  // y_i and y_p copy for further limitations
  pi->state.sum_error = y_i;
  pi->state.y_p = y_p;

  // Calculate return value

  //*************** Limitation Output***************//
  y_i = y_i + y_p; // reuse

  if (y_i > pi->param.max)
  {
    y_i = pi->param.max;
  }
  if (y_i < pi->param.min)
  {
    y_i = pi->param.min;
  }
  return y_i;
}

void pi_controller_reset(pi_ctrl_data_t *pi_controller)
{
  pi_controller->state.sum_error = 0;
  pi_controller->state.lastValue = 0;
  pi_controller->state.rest = 0;
  return;
}

void pi_controller_sum_init(pi_ctrl_data_t *pi_controller, s16 new_output)
{
  pi_controller->state.sum_error = ((s32)new_output) << pi_controller->param.scaling_factor;
}

/** @} */
