/*
 * parameters.h
 *
 *  Created on: 24.03.2015
 *      Author: daniel
 */

#ifndef MOTCUB_INC_PARAMETERS_H_
#define MOTCUB_INC_PARAMETERS_H_

#include "commons.h"

#define DEBUG_STARTUP_ESTIMATION

#ifdef EXTERNAL_PARAMETERS
#include "external_parameters.h"
#else

#ifdef LIN
#include "lindrv_basictypes.h"
#include "lindrv_hal_maz.h"
#endif

#define CUSTOMER_SPECIFIC_PARAMETERS

/* Settings */
#define PAR_MAX_CLK_hz 48000000u /* PLL clock and base unit [hz]*/

#ifdef T52350
/* 24MHZ */
#define PAR_SYS_CLK_DEVIDER 2u /* Devider of PLL [1, 2, 4]*/
#else
/* 48MHZ */
#define PAR_SYS_CLK_DEVIDER 1u /* Devider of PLL [1, 2, 4]*/
#endif

#define PAR_PWMFREQ_hz (16000u) /* PWM frequency [hz] */

#define PI_CONTROLLER_MAX_MULT (24000000u / PAR_PWMFREQ_hz)

// Calculations
#define C_SYS_CLK_hz (u32)((double)PAR_MAX_CLK_hz / (double)PAR_SYS_CLK_DEVIDER)
#define C_PWM_CNT_MAX (u16)((double)C_SYS_CLK_hz / (double)(PAR_PWMFREQ_hz * 2))

/**Duration of clock cycles for deadtime generation. See PWM DEAD_TIME register description.*/
//#define DRIVER_PWM_DEADTIME (48 / PAR_SYS_CLK_DEVIDER)   //1us
//#define DRIVER_PWM_DEADTIME (48 / PAR_SYS_CLK_DEVIDER * 3 / 2) //1.5us
#define DRIVER_PWM_DEADTIME 36 // 1.25us
/** Shifts the sample point in clock cycles to compensate the driver delay.*/

#if (PAR_SYS_CLK_DEVIDER == 1)
#define DRIVER_DELAY_1 48 / PAR_SYS_CLK_DEVIDER
#define DRIVER_DELAY_2 48 / PAR_SYS_CLK_DEVIDER
#else
#if (PAR_SYS_CLK_DEVIDER == 2)
#define DRIVER_DELAY_0 (8)
#define DRIVER_DELAY_1 (33)
#define DRIVER_DELAY_2 (29)
#else
#define DRIVER_DELAY_1 48 / PAR_SYS_CLK_DEVIDER
#define DRIVER_DELAY_2 48 / PAR_SYS_CLK_DEVIDER
#endif
#endif

/** MOSFET_AUIRFS4610*/
#define MOSFET_RDSON (double)0.011
/** Maximal Current.*/
#define DRIVER_SCTH_MAX_CURRENT 200

/**Maximal speed reference = 100+100/8*/
#define SPEED_REF_LIMIT_DP2 3
#define SPEED_REF_LIMIT_ALWAYS

#define DRIVER_SCTH_SETTING                                                                                            \
  ((uint16_t)(((double)MOSFET_RDSON * (double)DRIVER_SCTH_MAX_CURRENT * (double)128 / (double)3.3) + (double)0.5))
#define DRIVER_SCTH_HS DRIVER_SCTH_SETTING
#define DRIVER_SCTH_LS DRIVER_SCTH_SETTING

#define INC_CONTROLLER_DISABLE_TIME // no time for inner controller more stable

// STARTUP
#define STARTUP_DATA_START 0
#define STARTUP_EXTEND_BOOTSTRAP 1
#define STARTUP_BOOTSTRAP_LOAD 2400
#define STARTUP_DURATION 1920
#define STARTUP_DC (STARTUP_DURATION / 2)
#define STARTUP_OSZ (STARTUP_DURATION * 3 / 2)
#define STARTUP_DNS ((STARTUP_DURATION))
#define STARTUP_SAMPLES_2 15
#define STARTUP_SAMPLES_1 1

s16 get_vbat_maximal_multiplier(void);

#endif
#endif /* MOTCUB_INC_PARAMETERS_H_ */
