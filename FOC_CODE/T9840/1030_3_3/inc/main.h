#ifndef __DEMO__
#define __DEMO__

#include "api.h"
#include "bemf_control.h"
#include "commons.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <types.h>

#include "bemf_control.h"
#include "driver_generic.h"
#include "irq.h"
#include "motor.h"
#include "parameters.h"
#include "pre_pwm_helper_addon.h"
#include "pre_pwm_module.h"
#include "pre_pwm_tables.h"
#include "pwm_module.h"
#include "saradc_module.h"
#include "saradc_tables.h"
#include "u_f_table.h"

/** Initial PRE_PWM Increment.*/
#define DEFAULT_INC 1
/** Initial PRE_PWM Multiplier.*/
#define DEFAULT_MULT 0
/** Initial PRE_PWM Multiplier shift.*/

#if (PAR_SYS_CLK_DEVIDER == 1)
#define DEFAULT_MULT_SHIFT 5
#else
#if (PAR_SYS_CLK_DEVIDER == 2)
#define DEFAULT_MULT_SHIFT 6
#else
#define DEFAULT_MULT_SHIFT 7
#endif
#endif

/**Enable to put waveform into memory*/
#define WAVE_SVM
#define WAVE_FLAT

#define STALL_CHECK_EVERY_60X_ROTATIONS 1

#ifdef LIN
// 10A / 0.15
#define BOARD_MAXIMAL_CURRENT_ADC 67
#else
#define BOARD_MAXIMAL_CURRENT_ADC 10000
#endif

// FILTER BITS
#define INC_CONTROLLER_DISABLE_TIME_BIT 1u
#define MULT_CONTROLLER_DISABLE_TIME_BIT 2u
#define INC_CONTROLLER_MULTIPLY_TIME_BIT 4u
#define MULT_CONTROLLER_DISABLE_PERCENT 8u

#ifndef FILTER_BITS_SETTING
#define FILTER_BITS_SETTING (1)
#endif
// END FILTER BITS

extern s16 shift_wave;
extern s16 pre_pwm_shadow_reg_smult;
extern s16 pre_pwm_shadow_reg_sinc;

#endif /* __DEMO__ */
