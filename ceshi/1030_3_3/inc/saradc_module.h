#ifndef __SARADC_MODULE__
#define __SARADC_MODULE__
#include "bemf_control.h"
#include "commons.h"
#include "irq.h"
#include "motor.h"
#include "pre_pwm_helper_addon.h"
#include "pre_pwm_module.h"
#include "saradc_ctrl.h"
#include "saradc_ctrl_irq.h"
#include "saradc_tables.h"
#include "types.h"
#include <stdio.h>

/**
 * @defgroup SARADC SARADC module
 * @ingroup OTHER
 *
 * The SARADC module controlles the ADC and the muxer to set a channel and measure delayed to a trigger of a pwm flank.
 * This module supports DMA and can write back commanded measurement CPU independent to the memory.
 * The commands are given via the saradc_tables. The execution of maximal(SAMPLE_COUNT) measures is called measurement
 * window. The software saradc module is responsible to adapt these windows for every measurable zerocrossing. See
 * register description of SARADC module for addition informations.
 *
 * @{
 */

/**All collected data of a window*/
typedef struct adc_window_t
{
  // debug
  /** Last input of bemf_controler*/ s16 regler_value;
  /** Samples used*/ u8 samples;

  /** Debug.*/ u32 sum;
  /** Debug.*/ s16 tend;
  /** Debug.*/ s16 inc;
  /** Debug.*/ s16 mult;
  /** Debug.*/ u16 error;

} adc_window;

// extern volatile u8 swap_mem; DELETE

/** Collected data for the six zerocrossing detection windows.*/

/** Counter for overcurrent detections.*/
extern volatile u16 oor_count[]; // over current counter
/** Set to true if the zerocrossing detection is stable enough for closed-loop control.*/
extern volatile bool detection_stable;
/** Table to change the trigger event of the saradc tables to measure the shunt current.*/
extern u16 current_svm_evt[];
/** Index of the currently active current trigger event.*/
extern u8 current_index;

/**@brief Initializes the SARADC module.*/
void saradc_init(void);

/**@brief Sets the moment when the internal muxer of the adc switches to a channel and if some gpio pins are used for an
 * external muxer. See SARADC register description.
 * @param mux_timing      Moment of internal muxer switch in clock cycles
 * @param mux_ex        True if external muxer is used
 * */
void saradc_mux_timing(u16 mux_timing, u16 mux_ex, u16 clk_div);

/**@brief If the right trigger event occurs the saradc delays the sample to sample inside the deadtime.
 * Also used to compensate the driver delay.
 * @param dead_time_wait_0  Delay if trigger[35:24]==0
 * @param dead_time_wait_1  Delay if trigger[35:24]==1
 * @param dead_time_wait_2  Delay if trigger[35:24]==2
 *  */
void saradc_config(u8 dead_time_wait_0, u8 dead_time_wait_1, u8 dead_time_wait_2);

/**@brief If the rotation rate is changed via the swap_uv register in the pre_pwm module the zerocrossing occurs in a
 * different order. Therefore the order of the trigger sequence has to be adapted, which is done by a new initialization
 * of the sampling windows.
 * @param swap_uv     Swap_uv value of the pre_pwm register
 *  */
// void saradc_init_adc_windows(bool swap_uv);

/**@brief If the rotation rate is changed via the swap_uv register in the pre_pwm module the zerocrossing occurs in a
 * different order. Therefore the order of the trigger sequence has to be adapted, which is done by a new initialization
 * of the sampling windows.
 * @param table       Pointer to the saradc command table
 * @param skip_list     True if a executed saradc command table should be terminated
 *  */
void saradc_apply_list(saradc_table_list_entry *table, bool skip_list);

/**@brief Checks if the wanted list is already executed to prevent restart of the list.
 * @param table       Pointer to the saradc command table
 * @param skip_list     True if a executed saradc command table should be terminated
 *  */

/**@brief Print function to observe collected zerocrossing data and window.*/
void saradc_bemf_print_values(void);

/**@brief Called if the saradc has finished a command table.
 * @param irq     Bitfield of the irq status */
void ADCListDoneHandler2(void);

void saradc_init_windows(void);

void saradc_init_window_length(u16 inc_start);

void saradc_start_current_measurement(void);

void clarke_trans(s16 u, s16 v, s16 w, s16 *alpha, s16 *beta);
u16 uvw_theta(int32_t u, int32_t v, int32_t w);
u16 ab_theta(int32_t a, int32_t b);

void saradc_swap_vw(bool reverse);
s16 summed_tendence(void);
void saradc_window_control_V2_patch(u8 nr, s16 shift_opt_phase);
void saradc_window_control_V2_lowspeed_patch(u16 x);

/** @} */
#endif /* __SARADC_MODULE__ */
