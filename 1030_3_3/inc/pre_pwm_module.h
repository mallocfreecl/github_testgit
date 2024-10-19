#ifndef __PRE_PWM_MODULE__
#define __PRE_PWM_MODULE__

#include "api.h"
#include "commons.h"

#define STATIC_DT_COMPENSATION

/**
 * @defgroup PWM PRE-PWM&PWM module
 * @ingroup OTHER
 *
 *
 * The PRE_PWM module is responsible to to fill the dutycycle registers of the three pwm phases with in memory defined
 * linear interpolated waveform. The position in degree in the waveform is measured in basephases (PRE_PWM_GET_BP). 360
 * degree are equivalent with bp_max. The frequency/rotation rate of the waveform is controlled online via the increment
 * (PRE_PWM_SET_INC). The amplitude rate of the waveform via the multiplier (PRE_PWM_SET_MULT).
 *
 * The three PWM modules generate the PWM pulses for the U,V and W phases.
 * The duty cycle for a pwm period can also be set via software.
 *
 *
 * See register description of PRE-PWM and PWM module for addition informations.
 * @{
 */

/** Initializes the pre_pwm modul.*/
void pre_pwm_init(void);

/**@brief The pre_pwm is configured to generate a changed waveform without interruption. See register description of
 *PRE-PWM module.
 * @param bp_max                        Represents 360 degrees in basephases
 * @param wave_offset_0         Added value before scaling (voltage offset)
 * @param wave_offset_1         Added value after scaling (voltage offset)
 * @param inc                           Rotation rate
 * @param scale_mult            Waveform amplitude factor
 * @param scale_shift           Waveform amplitude power of two
 *
 **/
void pre_pwm_config_online(pre_pwm_bp_max_t bp_max, u16 wave_offset_0, u16 wave_offset_1);

/**@brief Configures the pre_pwm module to speed up or slow down the electrical rotation rate.
 * @param inc                           Rotation rate
 **/
void pre_pwm_config_online_inc(s16 inc);

/**@brief Configures the pre_pwm module to raise or attenuate the waveform amplitude.
 * @param scale_mult            Waveform amplitude factor
 * @param scale_shift           Waveform amplitude power of two
 **/
void pre_pwm_config_online_scale(s16 scale_mult, u8 scale_shift);

/**@brief The pre_pwm is stopped and configured to generate a new waveform. See register description of PRE-PWM module.
 * @param pwm_run                                               Starts to increment the basephase after configuration
 * @retval bp_max                                               Represents 360 degrees in basephases
 * @retval wave_offset_0                                Added value before scaling (voltage offset)
 * @retval wave_offset_1                                Added value after scaling (voltage offset)
 * @param deadtime                                              Deadtime of pwm register
 * @param table_select                                  Selects the waveform by number 0:sine, 1:flat_bottom, 2:svm,
 *3:svm_dt_comp, 4:rectangle
 * @retval table_entry_array                    Pointer to the waveform data array
 * @param start_phase_u                                 Aligns all phases to initial motor position
 * @param swap_uv                                               Pre_pwm dutycycle outputs are swaped for counterwise
 *rotation
 **/
void pre_pwm_config_offline(bool pwm_run, pre_pwm_bp_max_t *bp_max, u16 *wave_offset_0, u16 *wave_offset_1,
                            u16 deadtime, u8 table_select, pre_pwm_table_entry **table_entry_array, u16 start_phase_u,
                            bool swap_uv);

void pre_pwm_set_default_table(u16 *wave_offset_0, u16 *wave_offset_1, u8 table);

/**@brief Adjusts the generated electrical waveform to the transfered basephase.
 * @param start_phase_u                 Shifts the waveform of all phases by start_phase_u basephases.
 * @param init_bp                               Initializes the actual basephase for startup positioning.
 **/
void pre_pwm_set_phase(u16 start_phase_u, bool init_bp, bool vw_swap);

/**@brief Enables or disables the interrupt if the bp_0 value matches the actual pre_pwm basephase.
 * @param set                                   True enable interrupt. False disable interrupt.
 **/
void pre_pwm_irq_handler_bp_0_enable(bool set);

/**@brief Is called if basephase matches bp_sync0. Used in Zangskommutierung.
 * @param irq                   bitfield of the irq status*/
void pre_pwm_irq_handler_bp_0(int irq);

/**@brief Is called if basephase matches bp_sync1. Used to measure current.
 * @param irq                   bitfield of the irq status*/
void pre_pwm_irq_handler_bp_1(int irq);

s16 pre_pwm_get_sinc(void);
s16 pre_pwm_get_smult(void);
bool pre_pwm_get_dq_bp(void);
u16 pre_pwm_get_bp(void);

void pre_pwm_set_sinc_smult_init(s16 sinc, s16 smult, bool init, bool set_mult);

// getter function to protect internal states
inline void pre_pwm_set_sinc(s16 sinc);
inline void pre_pwm_set_smult(s16 smult);
bool pre_pwm_is_reverse(void);

u16 pre_pwm_get_angle(void);
void pre_pwm_set_initial_direction(bool reverse);
void pre_pwm_enable_float(bool enable);
bool is_pre_pwm_floating(void);

/** @} */
#endif
