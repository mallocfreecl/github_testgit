#ifndef __PRE_PWM_HELPER_ADDON__
#define __PRE_PWM_HELPER_ADDON__

#include "commons.h"
#include "limits.h"
#include "pre_pwm.h"
#include "pre_pwm_helper.h"
#include "pwmn_bf.h"
#include "stdio.h"
#include "types.h"

/**
 * @defgroup PWM PRE-PWM&PWM module
 * @ingroup OTHER
 * @{
 */

/*********************/
/** normal 			 */
/*********************/
/** Gets the actual shift for the multiplier.*/
#ifndef PRE_PWM_GET_SHIFT
#define PRE_PWM_GET_SHIFT                                                                                              \
  ((READ_REG_U16(AADDR_PRE_PWM_SCALE) >> SFT_PRE_PWM_SCALE_SCALE_SHIFT) & MSK_PRE_PWM_SCALE_SCALE)
#endif

/** Sets the actual shift for the multiplier.*/
#ifndef PRE_PWM_SET_SHIFT
#define PRE_PWM_SET_SHIFT(X)                                                                                           \
  (WRITE_REG_16(AADDR_PRE_PWM_SCALE, (READ_REG_U16(AADDR_PRE_PWM_SCALE) &                                              \
                                      ~(MSK_PRE_PWM_SCALE_SCALE_SHIFT << SFT_PRE_PWM_SCALE_SCALE_SHIFT)) |             \
                                       (X << SFT_PRE_PWM_SCALE_SCALE_SHIFT)))
#endif

/** Gets the actual absolute of the actual increment.*/
#ifndef PRE_PWM_GET_ABS_INC
#define PRE_PWM_GET_ABS_INC ((READ_REG_U16(AADDR_PRE_PWM_INC)) / PAR_SYS_CLK_DEVIDER)
#endif

/** Gets the actual absolute of the actual multiplier.*/
#ifndef PRE_PWM_GET_ABS_MULT
#define PRE_PWM_GET_ABS_MULT (READ_REG_U16(AADDR_PRE_PWM_SCALE) & MSK_PRE_PWM_SCALE_SCALE)
#endif

/** Gets the actual basephase of the hardware.*/
#ifndef PRE_PWM_GET_BP
#define PRE_PWM_GET_BP (READ_REG_U16(AADDR_PRE_PWM_BASE_PHASE))
#endif

/** Sets the actual basephase of the hardware.*/
#ifndef PRE_PWM_SET_BP
#define PRE_PWM_SET_BP(X) WRITE_REG_16(AADDR_PRE_PWM_BASE_PHASE, X)
#endif

/** Sets the actual basephase of the hardware.*/
#ifndef PRE_PWM_GET_ACC
#define PRE_PWM_GET_ACC (READ_REG_U16(AADDR_PRE_PWM_ACC))
#endif

/** Sets the actual basephase of the hardware.*/
#ifndef PRE_PWM_SET_ACC
#define PRE_PWM_SET_ACC(X) WRITE_REG_16(AADDR_PRE_PWM_ACC, X)
#endif

/*********************/
/** Depreciated */
/*********************/
#ifndef PRE_PWM_GET_SWAP_UV
/** Swaps the output for the phases U and V to rotate the motor in the opposite direction.*/
#define PRE_PWM_GET_SWAP_UV ((READ_REG_U16(AADDR_PRE_PWM_CFG) >> SFT_PRE_PWM_CFG_SWAP_UV) & MSK_PRE_PWM_CFG_SWAP_UV)
#endif

#ifndef PRE_PWM_SET_SWAP_UV
#define PRE_PWM_SET_SWAP_UV(X)                                                                                         \
  (WRITE_REG_16(AADDR_PRE_PWM_CFG,                                                                                     \
                (READ_REG_U16(AADDR_PRE_PWM_CFG) & ~BIT_PRE_PWM_CFG_SWAP_UV) | (X << SFT_PRE_PWM_CFG_SWAP_UV)))
#endif

/** Calculates for a given pre_pwm table the maximal basephase and the initial values of the waveform pointers for the
 * pre_pwm module. The returned values_xxx represents a phase shift by 0, 120 and 240 degrees for voltage generation of
 * the U,V and W coil. Additional all phases can be shifted per the bp_start_u entry to align the waveform at the
 * initial motor position.
 * @param table				Pre_pwm table for waveform generation
 * @param bp_start_u		Aligns all phases to initial motor position
 * @retval values_000		Initial values for phase U
 * @retval values_120		Initial values for phase V
 * @retval values_240		Initial values for phase W
 * @retval bp_max			Represents 360 degrees in basephases */
void pre_pwm_get_offset_phase_shift(const pre_pwm_table_entry table[], u16 bp_start_u, initial_values *values_000,
                                    initial_values *values_120, initial_values *values_240, pre_pwm_bp_max_t *bp_max);

/**@brief Calculates for a given pre_pwm table the initial value of the waveform pointers for the pre_pwm module.
 * The returned values_xxx represents a initial value for voltage generation of a coil.
 * @param table				Pre_pwm table for waveform generation
 * @retval values_xxx		Initial values for a phase
 * @param steps				Steps in basephases to shift the pointer
 * @param last_segment		Last segment of a table*/
void pre_pwm_get_offset_phase_shift_value(const pre_pwm_table_entry table[], initial_values *values_xxx, u16 steps,
                                          u16 last_segment);

/**@brief Uses caclulated the initial values for the phases and writes them into the registers of the pre_pwm modul.
 * @param table				Pre_pwm table for waveform generation
 * @param values_000		Initial values for phase U
 * @param values_120		Initial values for phase V
 * @param values_240		Initial values for phase W*/
void pre_pwm_set_initial_entry_direct(const pre_pwm_table_entry table[], const initial_values *values_000,
                                      const initial_values *values_120, const initial_values *values_240);

/** @} */
#endif /*__PRE_PWM_HELPER_ADDON__ */
