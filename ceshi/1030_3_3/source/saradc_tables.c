// these commands ignore channel select
// 0xFFFB}, //store base phase
// 0xFFFE}};//goto list
// DONT PUT A LOOP UNTIL STATEMENT AS FIRST ENTRY IN A LIST

/**
 * @addtogroup SARADC SARADC module
 * @ingroup OTHER
 *
 * This module controlles the ADC with the help of the SARADC controller to
 * detect a zerocrossing.
 *
 * @{
 */

#include "saradc_tables.h"

__no_init volatile u16 gpio[32] @(SARADC_MEM_ADDR);
__no_init u16 currentpulse[4][8] @(SARADC_MEM_ADDR + sizeof(gpio));
__no_init u16 bemf_voltage[2][BEMF_DATA_COUNT] @(SARADC_MEM_ADDR + sizeof(gpio) + sizeof(currentpulse));

#define ADDFLUX 0

//  //?* are the in runtime patched entries
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
saradc_table_list_entry list_bemf_start[] = {
  // prepare the next 60 deg window table and start this table.
  /*
  Wait until  330deg <= basephase <= 360deg
  */
  {BP_MAX, {.until = {DEG_TO_BP(ADDFLUX + 30 + 60 * 5), 1}}, AI_LOOP_UNTIL_BP}, // 0*
  /*
  1.Store base_phase in place of sum
  2.Set and use TADR
  */
  {ADDR_INC(&bemf_voltage[0][0]), {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},
  /*
  Always goto list_bemf_window_0
  */
  {(u16)list_bemf_window_0, {.no = {0, 0, 0, 0, 1}}, AI_GOTO_ALWAYS_1400} // 2*
};
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------

saradc_table_list_entry list_bemf_window_0_overflow[] = {
  {0, {.no = {0, 0, BEMF_U, 0, 1}}, AI_WAIT},
  //{BP_MAX,                      {.until = {0, 1}}, AI_LOOP_UNTIL_BP},
  {(u16)list_bemf_window_0, {.no = {0, 0, 0, 0, 1}}, AI_GOTO_ALWAYS_1400}};

// Changelog
// Battery voltage is measured at the end for the phase with the highes
// dutycycle to support BLDC Measurement of DC Battery Current instead of AC
// phase current is done 16times for precision

#define VBAT_AT_CENTER                                                                                                 \
  0                                                                                                                    \
  }                                                                                                                    \
  }                                                                                                                    \
  , MT(0)                                                                                                              \
  }                                                                                                                    \
  ,
#define VBAT_AT_IMMIDIATE                                                                                              \
  1                                                                                                                    \
  }                                                                                                                    \
  }                                                                                                                    \
  , AI_IMMEDIATE                                                                                                       \
  }                                                                                                                    \
  ,

#define VBAT_TABLE_MEAS VBAT_AT_CENTER

//-----------------------------------------------------------------------------------------------------------
saradc_table_list_entry list_bemf_window_0[] = {
  // loop for 60 deg: Measure rising edge, Supply at the middle and falling
  // edge (wait is used to reduce the data)
  /*
   only set multiplexer for BEMF_U after 0+2 clk
  */
  {0, {.no = {0, 0, BEMF_U, 0, 1}}, AI_WAIT},
  /*
  Loop until 0 deg <= basephase <= 360 deg
  */
  {BP_MAX, {.until = {0, 1}}, AI_LOOP_UNTIL_BP},
  /*
  0x1400..14FF: when any of the dead_time_evt[7:0] occurs and the
  corresponding bit [7:0] is set and
  */
  {3, {.no = {0, 1, BEMF_U, 0, 1}}, U_u_r}, // 2*
  {3, {.no = {0,
              1,
              BEMF_U,
              0,
              VBAT_TABLE_MEAS{(u16) & (GPIO_TADR_ADC_VBAT_COMP), {.no = {0, 0, 0, 0, 1}}, AI_ST_TADR},
              {3, {.no = {0, 1, BEMF_U, 0, 1}}, U_u_f},                                               // 5*
              {0, {.no = {0, 0, BEMF_U, 0, 1}}, AI_WAIT},                                             // 6*
              {(DEG_TO_BP(180)), {.until = {DEG_TO_BP(ADDFLUX + 30 + 60 * 0), 1}}, AI_LOOP_UNTIL_BP}, // 7*
              {3, {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},

              // after the 60° window: save the last angle and measure the analog
              // signal
              {0, {.no = {0, 0, ADC_CH_AmbientTemperature, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_AmbientTemperature), {.no = {15, 1, ADC_CH_AmbientTemperature, 0, 1}}, AI_IMMEDIATE},

              // do a DC measurement
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
              {(u16) & (GPIO_I_DC), {.no = {15, 1, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},

              // measure the temperature immediately
              {0, {.no = {0, 0, ADC_CH_Chip_TEMPERATURE, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_TEMPERATURE), {.no = {15, 1, ADC_CH_Chip_TEMPERATURE, 0, 1}}, AI_IMMEDIATE},

              {0, {.no = {0, 0, BEMF_U, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_VBAT), {.no = {0, 1, BEMF_U, 0, 0}}, MT(0)},
              {0, {.no = {0, 0, BEMF_V, 0, 1}}, AI_IMMEDIATE},

              {(u16) & (currentpulse[0][0]), {.no = {0, 0, 0, 0, 1}}, AI_ST_TADR},

              // prepare the next 60° window table and start this table.
              {ADDR_INC(&bemf_voltage[1][0]), {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},
              {(u16)list_bemf_window_1, {.no = {0, 0, 0, 0, 1}}, AI_GOTO_ALWAYS_1400}};
//-----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------
saradc_table_list_entry list_bemf_window_1[] = {
  // 60° window
  {0, {.no = {0, 0, BEMF_V, 0, 1}}, AI_WAIT}, {BP_MAX, {.until = {0, 1}}, AI_LOOP_UNTIL_BP},
  {3, {.no = {0, 1, BEMF_V, 0, 1}}, U_v_r},
  {3, {.no = {0,
              1,
              BEMF_V,
              0,
              VBAT_TABLE_MEAS{(u16) & (GPIO_TADR_ADC_VBAT_COMP), {.no = {0, 0, 0, 0, 1}}, AI_ST_TADR},
              {3, {.no = {0, 1, BEMF_V, 0, 1}}, U_v_f},
              {0, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
              {(DEG_TO_BP(180)), {.until = {DEG_TO_BP(ADDFLUX + 30 + 60 * 1), 1}}, AI_LOOP_UNTIL_BP},
              {3, {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},

              // speed
              {0, {.no = {0, 0, ADC_CH_AmbientTemperature, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_AmbientTemperature), {.no = {15, 1, ADC_CH_AmbientTemperature, 0, 1}}, AI_IMMEDIATE},

              // current
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
              {(u16) & (GPIO_I_DC), {.no = {15, 1, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},

              // temperature
              {0, {.no = {0, 0, ADC_CH_Chip_TEMPERATURE, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_TEMPERATURE), {.no = {15, 1, ADC_CH_Chip_TEMPERATURE, 0, 1}}, AI_IMMEDIATE},

              {0, {.no = {0, 0, BEMF_U, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_VBAT), {.no = {0, 1, BEMF_U, 0, 0}}, MT(0)},
              {0, {.no = {0, 0, BEMF_W, 0, 1}}, AI_IMMEDIATE}, // 14*

              {(u16) & (currentpulse[0][1]), {.no = {0, 0, 0, 0, 1}}, AI_ST_TADR},

              // prepare
              {ADDR_INC(&bemf_voltage[0][0]), {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},
              {(u16)list_bemf_window_2, {.no = {0, 0, 0, 0, 1}}, AI_GOTO_ALWAYS_1400}};
//-----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------
saradc_table_list_entry list_bemf_window_2[] = {
  // 60° window
  {0, {.no = {0, 0, BEMF_W, 0, 1}}, AI_WAIT}, {BP_MAX, {.until = {0, 1}}, AI_LOOP_UNTIL_BP},
  {3, {.no = {0, 1, BEMF_W, 0, 1}}, U_w_r},
  {3, {.no = {0,
              1,
              BEMF_W,
              0,
              VBAT_TABLE_MEAS{(u16) & (GPIO_TADR_ADC_VBAT_COMP), {.no = {0, 0, 0, 0, 1}}, AI_ST_TADR},
              {3, {.no = {0, 1, BEMF_W, 0, 1}}, U_w_f},
              {0, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
              {BP_MAX, {.until = {DEG_TO_BP(ADDFLUX + 30 + 60 * 2), 1}}, AI_LOOP_UNTIL_BP},
              {3, {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},

              // speed
              {0, {.no = {0, 0, ADC_CH_AmbientTemperature, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_AmbientTemperature), {.no = {15, 1, ADC_CH_AmbientTemperature, 0, 1}}, AI_IMMEDIATE},

              // current
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
              {(u16) & (GPIO_I_DC), {.no = {15, 1, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},

              // temperature
              {0, {.no = {0, 0, ADC_CH_Chip_TEMPERATURE, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_TEMPERATURE), {.no = {15, 1, ADC_CH_Chip_TEMPERATURE, 0, 1}}, AI_IMMEDIATE},

              {0, {.no = {0, 0, BEMF_W, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_VBAT), {.no = {0, 1, BEMF_W, 0, 0}}, MT(0)},
              {0, {.no = {0, 0, BEMF_U, 0, 1}}, AI_IMMEDIATE},

              {(u16) & (currentpulse[0][2]), {.no = {0, 0, 0, 0, 1}}, AI_ST_TADR},

              // prepare
              {ADDR_INC(&bemf_voltage[1][0]), {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},
              {(u16)list_bemf_window_3, {.no = {0, 0, 0, 0, 1}}, AI_GOTO_ALWAYS_1400}};
//-----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------
saradc_table_list_entry list_bemf_window_3[] = {
  // 60° window
  {0, {.no = {0, 0, BEMF_U, 0, 1}}, AI_WAIT}, {BP_MAX, {.until = {0, 1}}, AI_LOOP_UNTIL_BP},
  {3, {.no = {0, 1, BEMF_U, 0, 1}}, U_u_r},
  {3, {.no = {0,
              1,
              BEMF_U,
              0,
              VBAT_TABLE_MEAS{(u16) & (GPIO_TADR_ADC_VBAT_COMP), {.no = {0, 0, 0, 0, 1}}, AI_ST_TADR},
              {3, {.no = {0, 1, BEMF_U, 0, 1}}, U_u_f},
              {0, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
              {BP_MAX, {.until = {DEG_TO_BP(ADDFLUX + 30 + 60 * 3), 1}}, AI_LOOP_UNTIL_BP},
              {3, {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},

              // speed
              {0, {.no = {0, 0, ADC_CH_AmbientTemperature, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_AmbientTemperature), {.no = {15, 1, ADC_CH_AmbientTemperature, 0, 1}}, AI_IMMEDIATE},

              // current
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
              {(u16) & (GPIO_I_DC), {.no = {15, 1, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},

              // temperature
              {0, {.no = {0, 0, ADC_CH_Chip_TEMPERATURE, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_TEMPERATURE), {.no = {15, 1, ADC_CH_Chip_TEMPERATURE, 0, 1}}, AI_IMMEDIATE},

              {0, {.no = {0, 0, BEMF_W, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_VBAT), {.no = {0, 1, BEMF_W, 0, 0}}, MT(0)},
              {0, {.no = {0, 0, BEMF_V, 0, 1}}, AI_IMMEDIATE},

              {(u16) & (currentpulse[0][3]), {.no = {0, 0, 0, 0, 1}}, AI_ST_TADR},

              // prepare
              {ADDR_INC(&bemf_voltage[0][0]), {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},
              {(u16)list_bemf_window_4, {.no = {0, 0, 0, 0, 1}}, AI_GOTO_ALWAYS_1400}};
//-----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------
saradc_table_list_entry list_bemf_window_4[] = {
  // 60° window
  {0, {.no = {0, 0, BEMF_V, 0, 1}}, AI_WAIT}, {BP_MAX, {.until = {0, 1}}, AI_LOOP_UNTIL_BP},
  {3, {.no = {0, 1, BEMF_V, 0, 1}}, U_v_r},
  {3, {.no = {0,
              1,
              BEMF_V,
              0,
              VBAT_TABLE_MEAS{(u16) & (GPIO_TADR_ADC_VBAT_COMP), {.no = {0, 0, 0, 0, 1}}, AI_ST_TADR},
              {3, {.no = {0, 1, BEMF_V, 0, 1}}, U_v_f},
              {0, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
              {BP_MAX, {.until = {DEG_TO_BP(ADDFLUX + 30 + 60 * 4), 1}}, AI_LOOP_UNTIL_BP},
              {3, {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},

              // speed
              {0, {.no = {0, 0, ADC_CH_AmbientTemperature, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_AmbientTemperature), {.no = {15, 1, ADC_CH_AmbientTemperature, 0, 1}}, AI_IMMEDIATE},

              // current
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
              {(u16) & (GPIO_I_DC), {.no = {15, 1, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},

              // temperature
              {0, {.no = {0, 0, ADC_CH_Chip_TEMPERATURE, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_TEMPERATURE), {.no = {15, 1, ADC_CH_Chip_TEMPERATURE, 0, 1}}, AI_IMMEDIATE},

              {0, {.no = {0, 0, BEMF_V, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_VBAT), {.no = {0, 1, BEMF_V, 0, 0}}, MT(0)},
              {0, {.no = {0, 0, BEMF_W, 0, 1}}, AI_IMMEDIATE},

              {(u16) & (currentpulse[0][4]), {.no = {0, 0, 0, 0, 1}}, AI_ST_TADR},

              // prepare
              {ADDR_INC(&bemf_voltage[1][0]), {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},
              {(u16)list_bemf_window_5, {.no = {0, 0, 0, 0, 1}}, AI_GOTO_ALWAYS_1400}};
//-----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------
saradc_table_list_entry list_bemf_window_5[] = {
  // 60° window
  {0, {.no = {0, 0, BEMF_W, 0, 1}}, AI_WAIT}, {BP_MAX, {.until = {0, 1}}, AI_LOOP_UNTIL_BP},
  {3, {.no = {0, 1, BEMF_W, 0, 1}}, U_w_r},
  {3, {.no = {0,
              1,
              BEMF_W,
              0,
              VBAT_TABLE_MEAS{(u16) & (GPIO_TADR_ADC_VBAT_COMP), {.no = {0, 0, 0, 0, 1}}, AI_ST_TADR},
              {3, {.no = {0, 1, BEMF_W, 0, 1}}, U_w_f},
              {0, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
              {BP_MAX, {.until = {DEG_TO_BP(ADDFLUX + 30 + 60 * 5), 1}}, AI_LOOP_UNTIL_BP},
              {3, {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},

              // speed
              {0, {.no = {0, 0, ADC_CH_AmbientTemperature, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_AmbientTemperature), {.no = {15, 1, ADC_CH_AmbientTemperature, 0, 1}}, AI_IMMEDIATE},

              // current
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
              {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
              {(u16) & (GPIO_I_DC), {.no = {15, 1, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},

              // temperature
              {0, {.no = {0, 0, ADC_CH_Chip_TEMPERATURE, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_TEMPERATURE), {.no = {15, 1, ADC_CH_Chip_TEMPERATURE, 0, 1}}, AI_IMMEDIATE},

              {0, {.no = {0, 0, BEMF_V, 0, 1}}, AI_IMMEDIATE},
              {(u16) & (GPIO_ADC_VBAT), {.no = {0, 1, BEMF_V, 0, 0}}, MT(0)},
              {0, {.no = {0, 0, BEMF_U, 0, 1}}, AI_IMMEDIATE},

              {(u16) & (currentpulse[0][5]), {.no = {0, 0, 0, 0, 1}}, AI_ST_TADR},

              // prepare
              {ADDR_INC(&bemf_voltage[0][0]), {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},
              {(u16)list_bemf_window_0_overflow, {.no = {0, 0, 0, 0, 1}}, AI_GOTO_ALWAYS_1400}};
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------

// this table is executed in idle. All 18 stacks = 36 pwm cycles a measurement
// is done and the position calculated 1.31ms @ PAR_PWMFREQ_hz = 16K
saradc_table_list_entry const list_windmill[] = {
  {0, {.no = {0, 0, BEMF_V, 0, 0}}, MT(0)},
  {(u16) & (GPIO_WINDMILL_U), {.no = {1, 1, BEMF_U, 0, 0}}, MT(0)},

  {0, {.no = {0, 0, BEMF_U, 0, 0}}, MT(0)},
  {(u16) & (GPIO_WINDMILL_U), {.no = {15, 1, BEMF_U, 0, 0}}, MT(0)},

  {0, {.no = {0, 0, BEMF_V, 0, 0}}, MT(0)},
  {(u16) & (GPIO_WINDMILL_V), {.no = {15, 1, BEMF_V, 0, 0}}, MT(0)},

  {0, {.no = {0, 0, BEMF_W, 0, 0}}, MT(0)},
  {(u16) & (GPIO_WINDMILL_W), {.no = {15, 1, BEMF_W, 0, 0}}, MT(0)},

  {0, {.no = {0, 0, BEMF_U, 0, 0}}, MT(0)},
  {(u16) & (GPIO_WINDMILL_U2), {.no = {15, 1, BEMF_U, 0, 0}}, MT(0)},

  {0, {.no = {0, 0, BEMF_V, 0, 0}}, MT(0)},
  {(u16) & (GPIO_WINDMILL_V2), {.no = {15, 1, BEMF_V, 0, 0}}, MT(0)},

  {0, {.no = {0, 0, BEMF_W, 0, 0}}, MT(0)},
  {(u16) & (GPIO_WINDMILL_W2), {.no = {15, 1, BEMF_W, 0, 0}}, MT(0)},

  {0, {.no = {0, 0, ADC_CH_AmbientTemperature, 0, 0}}, MT(0)},
  {(u16) & (GPIO_ADC_AmbientTemperature), {.no = {15, 1, ADC_CH_AmbientTemperature, 0, 0}}, MT(0)},

  {0, {.no = {0, 0, ADC_CH_Chip_TEMPERATURE, 0, 0}}, MT(0)},
  {(u16) & (GPIO_ADC_TEMPERATURE), {.no = {15, 1, ADC_CH_Chip_TEMPERATURE, 0, 0}}, MT(0)},

  {0, {.no = {0, 0, SUPPLY, 0, 0}}, MT(0)},
  {(u16) & (GPIO_ADC_VBAT_IDLE), {.no = {0, 1, SUPPLY, 0, 0}}, MT(0)},

  {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_IMMEDIATE},
  {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
  {0, {.no = {0, 0, ADC_CH_RShunt, 0, 1}}, AI_WAIT},
  //{(u16)&(GPIO_I_DC),           {.no = { 15, 1, ADC_CH_RShunt, 0, 1}},
  // AI_IMMEDIATE},
  {(u16) & (GPIO_I_DC), {.no = {15, 1, ADC_CH_RShunt, 0, 1}}, MT(1200)}, /* fct test, 21.07.30 by yhd */

  {(u16)NULL, {.no = {0, 0, 0, 0, 1}}, AI_END}};

// TODO legacy remove
saradc_table_list_entry const list_estimation_1[] = {

  {0, {.no = {0, 0, BEMF_W, 0, 1}}, U_u_r},
  {0, {.no = {0, 0, BEMF_W, 0, 1}}, U_u_r},
  {STARTUP_DC, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16) & (currentpulse[0][0]), {.no = {0, 0, BEMF_W, 0, 1}}, AI_IMMEDIATE},
  {0, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16) & (currentpulse[0][1]), {.no = {0, 0, BEMF_W, 0, 1}}, AI_IMMEDIATE},
  {ESTIMATION_ADDRESS_0 + 1, {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},
  {(u16)list_estimation_1_2, {.no = {0, 0, 0, 0, 1}}, AI_GOTO_ALWAYS_1400}};

saradc_table_list_entry const list_estimation_1_2[] = {
  {0, {.no = {0, 0, BEMF_W, 0, 1}}, U_u_f},
  {STARTUP_OSZ, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16)3, {.no = {STARTUP_SAMPLES_2, 1, BEMF_W, 0, 1}}, AI_IMMEDIATE},

  {STARTUP_DNS, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16)3, {.no = {STARTUP_SAMPLES_2, 1, BEMF_W, 0, 1}}, AI_IMMEDIATE},

  {0, {.no = {0, 0, BEMF_W, 0, 1}}, U_u_r},
  {STARTUP_OSZ, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16)3, {.no = {STARTUP_SAMPLES_2, 1, BEMF_W, 0, 1}}, AI_IMMEDIATE},
  {STARTUP_DNS, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16)3, {.no = {STARTUP_SAMPLES_2, 1, BEMF_W, 0, 1}}, AI_IMMEDIATE},

  {0xFFFF, {.until = {ESTIMATION_ADDRESS_1, 1}}, AI_LOOP_UNTIL_TADR},
  {(u16)NULL, {.no = {0, 0, 0, 0, 1}}, AI_END}};

saradc_table_list_entry const list_estimation_2[] = {
  // BC

  {0, {.no = {0, 0, BEMF_U, 0, 1}}, U_v_r},
  {0, {.no = {0, 0, BEMF_U, 0, 1}}, U_v_r},
  {STARTUP_DC, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16) & (currentpulse[1][0]), {.no = {0, 0, BEMF_U, 0, 1}}, AI_IMMEDIATE},
  {0, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16) & (currentpulse[1][1]), {.no = {0, 0, BEMF_U, 0, 1}}, AI_IMMEDIATE},
  {ESTIMATION_ADDRESS_1 + 1, {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},
  {(u16)list_estimation_2_2, {.no = {0, 0, 0, 0, 1}}, AI_GOTO_ALWAYS_1400}};

saradc_table_list_entry const list_estimation_2_2[] = {
  {0, {.no = {0, 0, BEMF_U, 0, 1}}, U_v_f},
  {STARTUP_OSZ, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16)3, {.no = {STARTUP_SAMPLES_2, 1, BEMF_U, 0, 1}}, AI_IMMEDIATE},

  {STARTUP_DNS, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16)3, {.no = {STARTUP_SAMPLES_2, 1, BEMF_U, 0, 1}}, AI_IMMEDIATE},

  {0, {.no = {0, 0, BEMF_U, 0, 1}}, U_v_r},
  {STARTUP_OSZ, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16)3, {.no = {STARTUP_SAMPLES_2, 1, BEMF_U, 0, 1}}, AI_IMMEDIATE},
  {STARTUP_DNS, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16)3, {.no = {STARTUP_SAMPLES_2, 1, BEMF_U, 0, 1}}, AI_IMMEDIATE},

  {0xFFFF, {.until = {ESTIMATION_ADDRESS_2, 1}}, AI_LOOP_UNTIL_TADR},
  {(u16)NULL, {.no = {0, 0, 0, 0, 1}}, AI_END}};

saradc_table_list_entry const list_estimation_3[] = {
  // CA
  {0, {.no = {0, 0, BEMF_V, 0, 1}}, U_w_r},
  {0, {.no = {0, 0, BEMF_V, 0, 1}}, U_w_r},
  {STARTUP_DC, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16) & (currentpulse[2][0]), {.no = {0, 0, BEMF_V, 0, 1}}, AI_IMMEDIATE},
  {0, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16) & (currentpulse[2][1]), {.no = {0, 0, BEMF_V, 0, 1}}, AI_IMMEDIATE},
  {ESTIMATION_ADDRESS_2 + 1, {.no = {0, 0, 0, 0, 1}}, AI_ST_BP},
  {(u16)list_estimation_3_2, {.no = {0, 0, 0, 0, 1}}, AI_GOTO_ALWAYS_1400}};

saradc_table_list_entry const list_estimation_3_2[] = {
  {0, {.no = {0, 0, BEMF_V, 0, 1}}, U_w_f},
  {STARTUP_OSZ, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16)3, {.no = {STARTUP_SAMPLES_2, 1, BEMF_V, 0, 1}}, AI_IMMEDIATE},

  {STARTUP_DNS, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16)3, {.no = {STARTUP_SAMPLES_2, 1, BEMF_V, 0, 1}}, AI_IMMEDIATE},

  {0, {.no = {0, 0, BEMF_V, 0, 1}}, U_w_r},
  {STARTUP_OSZ, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16)3, {.no = {STARTUP_SAMPLES_2, 1, BEMF_V, 0, 1}}, AI_IMMEDIATE},
  {STARTUP_DNS, {.no = {0, 0, 0, 0, 1}}, AI_WAIT},
  {(u16)3, {.no = {STARTUP_SAMPLES_2, 1, BEMF_V, 0, 1}}, AI_IMMEDIATE},

  {0xFFFF, {.until = {ESTIMATION_ADDRESS_3, 1}}, AI_LOOP_UNTIL_TADR},
  {(u16)NULL, {.no = {0, 0, 0, 0, 1}}, AI_END}};

saradc_table_list_entry const ListOpenLaodDiag[] = {
  {0, {.no = {0, 0, SUPPLY, 0, 0}}, MT(0)},
  //{0,                           {.no = {  0, 0, SUPPLY, 0, 1}},
  // AI_IMMEDIATE},
  {0, {.no = {0, 0, SUPPLY, 0, 1}}, AI_WAIT},
  {0, {.no = {0, 0, SUPPLY, 0, 1}}, AI_WAIT},
  {(u16) & (GPIO_ADC_VBAT_IDLE), {.no = {0, 1, SUPPLY, 0, 1}}, AI_IMMEDIATE},

  {0, {.no = {0, 0, SUPPLY, 0, 0}}, MT(0)},
  //{0,                           {.no = {  0, 0, SUPPLY, 0, 1}},
  // AI_IMMEDIATE},
  {0, {.no = {0, 0, SUPPLY, 0, 1}}, AI_WAIT},
  {0, {.no = {0, 0, SUPPLY, 0, 1}}, AI_WAIT},
  {(u16) & (GPIO_ADC_VBAT_IDLE), {.no = {0, 1, SUPPLY, 0, 1}}, AI_IMMEDIATE},

  {0, {.no = {0, 0, BEMF_U, 0, 0}}, MT(C_PWM_CNT_MAX)},
  //{0,                           {.no = {  0, 0, BEMF_U, 0, 1}},
  // AI_IMMEDIATE},
  {0, {.no = {0, 0, BEMF_U, 0, 1}}, AI_WAIT},
  {0, {.no = {0, 0, BEMF_U, 0, 1}}, AI_WAIT},
  {(u16) & (GPIO_WINDMILL_U2), {.no = {0, 1, BEMF_U, 0, 1}}, AI_IMMEDIATE},

  {0, {.no = {0, 0, BEMF_U, 0, 0}}, MT(0)},
  //{0,                           {.no = {  0, 0, BEMF_U, 0, 1}},
  // AI_IMMEDIATE},
  {0, {.no = {0, 0, BEMF_U, 0, 1}}, AI_WAIT},
  {0, {.no = {0, 0, BEMF_U, 0, 1}}, AI_WAIT},
  {(u16) & (GPIO_WINDMILL_U), {.no = {0, 1, BEMF_U, 0, 1}}, AI_IMMEDIATE},

  {0, {.no = {0, 0, BEMF_V, 0, 0}}, MT(0)},
  //{0,                           {.no = {  0, 0, BEMF_V, 0, 1}},
  // AI_IMMEDIATE},
  {0, {.no = {0, 0, BEMF_V, 0, 1}}, AI_WAIT},
  {0, {.no = {0, 0, BEMF_V, 0, 1}}, AI_WAIT},
  {(u16) & (GPIO_WINDMILL_V), {.no = {0, 1, BEMF_V, 0, 1}}, AI_IMMEDIATE},

  {0, {.no = {0, 0, BEMF_W, 0, 0}}, MT(0)},
  //{0,                           {.no = {  0, 0, BEMF_W, 0, 1}},
  // AI_IMMEDIATE},
  {0, {.no = {0, 0, BEMF_W, 0, 1}}, AI_WAIT},
  {0, {.no = {0, 0, BEMF_W, 0, 1}}, AI_WAIT},
  {(u16) & (GPIO_WINDMILL_W), {.no = {0, 1, BEMF_W, 0, 1}}, AI_IMMEDIATE},

  {(u16)NULL, {.no = {0, 0, 0, 0, 1}}, AI_END}};

/** @} */
