#ifndef __PI_CONTROLLER__
#define __PI_CONTROLLER__

#include "api.h"
#include "commons.h"

/**
 * @defgroup Controller Controller module
 * @ingroup OTHER
 * This module implements an PI controller.
 * @{
 */

/*******************************************************************************
 * Typedefs
 *******************************************************************************/

/** Integrated and last value*/
typedef struct
{
  /** Summarized error*/ s32 sum_error; // also y_i
  /** Last error*/ s32 lastValue;
  /** Rest of division*/ s16 rest;
  /** Proportional output*/ s32 y_p;
  ///** Multiplier before division*/u16 norm; // inside controller
} pi_ctrl_state_t;

/** PI settings*/
typedef struct
{
  /** Proportional factor*/ volatile u16 Kp;
  /** Integral     factor*/ volatile u16 Ki;
  /** Integral     factor*/ u16 Ki_shift_gain;
  /** Maximal output value*/ s32 max;
  /** Minimal output value*/ s32 min;
  /** Scaling of output value*/ u16 scaling_factor;
} pi_ctrl_parameter_t;

/** Data of an the PI controller object.*/
typedef struct
{
  /** Integrated and last value*/ pi_ctrl_state_t state;
  /** PI settings*/ pi_ctrl_parameter_t param;
} pi_ctrl_data_t;

/*******************************************************************************
 * Prototypes
 *******************************************************************************/
/**@brief Initializes the PI controller.
 *  @param pi_controller			Pointer to the controller object
 *  @param Kp						Proportional factor
 *  @param Ki						Integral     factor
 *  @param max						Maximal output value
 *  @param scaling_factor_in_bits	Adaption for the maximal output value
 *  @param multiplier				Used for integration time
 */
void pi_controller_init(pi_ctrl_data_t *pi_controller, u16 Kp, u16 Ki, s32 min, s32 max, u16 scaling_factor,
                        u16 KI_shift_gain);

/**@brief Initializes the PI controller.
 *  @param pi_controller	Pointer to the controller object
 *  @param error				Error to desired value
 *  @retval s32				Proportional, Integral and Differential value added
 *  @param teiler			Timeslice in Inc for Ki controller
 *
 */
s32 pi_controller_call(pi_ctrl_data_t *pi_controller, s16 error, u16 divider);

/**@brief Resets the PI controller.
 *  @param pi_controller			Pointer to the controller object
 */
void pi_controller_reset(pi_ctrl_data_t *pi_controller);

void pi_controller_sum_init(pi_ctrl_data_t *pi_controller, s16 new_output);

/** @} */
#endif /* __PI_CONTROLLER_H__ */
