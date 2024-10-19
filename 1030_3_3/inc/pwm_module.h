#ifndef __PWM_MODULE__
#define __PWM_MODULE__

#include "api.h"
#include "commons.h"

/**
 * @addtogroup PWM PRE-PWM&PWM module
 * @ingroup OTHER
 *
 * @{
 */

/**@brief Initialization of the pwm modul. The dutycycle registers PWMX_C0 has to be filled via software or pre_pwm
 *modul to generate pulses.
 *
 * The pre_pwm is configured to generate a changed waveform without interruption. See register description of PRE-PWM
 *module.
 * @param cnt_mode			Pwm counter mode
 * @param deadtime_mode		Mode of deadtime generation
 * @param deadtime			Deadtime duration in clock cycles
 *
 **/
void pwm_init(u8 cnt_mode, u8 deadtime_mode, u8 deadtime);

void pre_pwm_control_on_duty(bool on, bool duty);
void pre_pwm_control(bool set);
void enable_pwm(u8 val);

void activate_pre_pwm_float_control(u8 nr, bool enable);
void wait_next_cycle(void);
/** @} */
#endif
