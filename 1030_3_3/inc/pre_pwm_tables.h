#ifndef __PRE_PWM_TABLES__
#define __PRE_PWM_TABLES__

#include "commons.h"
#include "motor.h"
/**
 * @defgroup PWM PRE-PWM&PWM module
 * @ingroup OTHER
 * @{
 */

/** Space vector modulation waveform*/
extern const pre_pwm_table_entry table_entry_svm[];
/** Rectangle modulation waveform*/
extern const pre_pwm_table_entry table_entry_trapez[];
/** Sinus modulation waveform*/
/** Flat bottom modulation waveform*/
extern const pre_pwm_table_entry table_entry_flat_bottom[];

/** @} */
#endif /* __PRE_PWM_TABLES__ */
