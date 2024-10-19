#ifndef __SARADC_TABLES__
#define __SARADC_TABLES__

#include "commons.h"
#include "driver_generic.h"
#include "motor.h"
#include "saradc_ctrl_bf.h"
#include "types.h"

/**
 * @defgroup SARADC SARADC module
 * @ingroup OTHER
 *
 * @{
 */

// Convention
// MT =  matching PWM trigger        -> triger_type_ext=0, triger_type=0
// MI =  measure extended Immediately    -> triger_type_ext=1, triger_type=0
// AI =  coprocessor like intelligence   -> triger_type_ext=0, triger_type=1

#define MT(x) x
#define MI(x) x

// more AI commands
//    0x0000..0x03FF basephase triggersc
//    0x0400..0x257F edge based triggers
//    0xFFE1-0xFFE9 compare last value

#define AI_IMMEDIATE                                                                                                   \
  0xFFC0 // immediate sampling The minimal sampling phase is extended by CFG_SAR_TIMING.mux_sampling_extension number of
         // adc clock/2 cycles.
#define AI_CMP_IRQ0                                                                                                    \
  0xFFE0 //"CMP" Assert "out of range" irq IRQ_STATUS.oor0 when the following condition is violated: 0x02[14:0] <=
         // last_sum <= target_adr[15:0].
#define AI_CMP_IRQ1 0xFFE1 // IRQ_STATUS.oor1
#define AI_CMP_IRQ2 0xFFE2 // IRQ_STATUS.oor2
#define AI_CMP_IRQ3 0xFFE3 // IRQ_STATUS.oor3
#define AI_CMP_IRQ4 0xFFE4 // IRQ_STATUS.oor4
#define AI_CMP_IRQ5 0xFFE5 // IRQ_STATUS.oor5
#define AI_CMP_IRQ6 0xFFE6 // IRQ_STATUS.oor6
#define AI_CMP_IRQ7 0xFFE7 // IRQ_STATUS.oor7
#define AI_CMP_IRQ8 0xFFE8 // IRQ_STATUS.oor8
#define AI_CMP_IRQ9 0xFFE9 // IRQ_STATUS.oor9

#define AI_WRITE_BUS 0xFFF0           //"WRITE_BUS"     Store target_adr to 0x02[14:0] with AdrBit[15]=0
#define AI_CFG_WRITE 0xFFF1           //"CFG_WRITE"     Store target_adr to CFG register
#define AI_SYNC_OUT 0xFFF2            //"SYNC_OUT"    trigger sync out event (see SYNC_OUT_CFG)
#define AI_WAIT 0xFFF3                //"WAIT"      wait for target_adr+2 clk cycles
#define AI_ST_BP 0xFFF4               //"ST_BP"       store base_phase in place of sum
#define AI_ST_TADR 0xFFF5             //"ST_TADR"     store TADR in place of sum
#define AI_LOOP_UNTIL_BP 0xFFF6       //"LOOP_UNTIL"    (0x02[14:0] <= base_phase <= target_adr[15:0])
#define AI_LOOP_UNTIL_NOT_BP 0xFFF7   //"LOOP_UNTIL NOT"  (0x02[14:0] <= base_phase <= target_adr[15:0])
#define AI_LOOP_UNTIL_TADR 0xFFF8     //"LOOP_UNTIL"    (0x02[14:0]<= TADR <= target_adr[15:0])
#define AI_LOOP_UNTIL_NOT_TADR 0xFFF9 //"LOOP_UNTIL NOT"  (0x02[14:0]<=TADR<= target_adr[15:0])
#define AI_GOTO_SUM 0xFFFA            //"GOTO_SUM"    target_adr[15:0] WHEN last_SUM <= 0x02[14:0]
#define AI_GOTO_NOT_SUM 0xFFFB        //"GOTO_NOT_SUM"  target_adr[15:0] WHEN NOT last_SUM <= 0x02[14:0]
#define AI_GOTO_BP 0xFFFC             //"GOTO_BP"     target_adr[15:0] WHEN BP <= 0x02[14:0]
#define AI_GOTO_NOT_BP 0xFFFD         //"GOTO_NOT_BP"   target_adr[15:0] WHEN NOT BP <= 0x02[14:0]
#define AI_GOTO_TADR                                                                                                   \
  0xFFFE //"GOTO_TADR"     target_adr[15:0] WHEN TADR[14:0] = 0x02[14:0] if 0x02[14:0] = 0 �GOTO always
#define AI_GOTO_ALWAYS_1400 0xFFFE //"GOTO_TADR"     0x02[14:0] = 0 �GOTO always if 14 downto 00
#define AI_END 0xFFFF              //"END"       list completed (last list item)

/** Prepares a memory address, so that the saradc module take the next address.*/
#define ADDR_INC(x) ((u16)(((u8 *)(x)) + 1))
/** Start address of the array.*/
#define SARADC_MEM_ADDR (0x1000)
/** Maximal count of samples of a window.*/
#define SAMPLE_COUNT 198
/** Samples of a window plus first and last basephase value.*/
#define BEMF_DATA_COUNT (SAMPLE_COUNT + 2)

#define BEMF_SAMPLE_INIT ((0x50 * 300) / SENSED_MODE_INC_START)
#define BEMF_DATA_INIT (BEMF_SAMPLE_INIT + 2)

// dead time events I/U _ u,v,w phase _ rise/fall
/** Triggers after DEAD_TIME_WAIT0==I cycles if phase U was Rising.*/
#define I_u_r (0x0402)
/** Triggers after DEAD_TIME_WAIT0==I cycles if phase V was Rising.*/
#define I_v_r (0x0408)
/** Triggers after DEAD_TIME_WAIT0==I cycles if phase W was Rising.*/
#define I_w_r (0x0420)

#define I_A_r (0x042A)

/** Triggers after DEAD_TIME_WAIT0==I cycles if phase U was Falling.*/
#define I_u_f (0x0401)
/** Triggers after DEAD_TIME_WAIT0==I cycles if phase V was Falling.*/
#define I_v_f (0x0404)
/** Triggers after DEAD_TIME_WAIT0==I cycles if phase W was Falling.*/
#define I_w_f (0x0410)

#define I_A_f (0x0415)

/** Triggers after DEAD_TIME_WAIT1==U_X_r cycles if phase U was Rising.*/
#define U_u_r (0x1402)
/** Triggers after DEAD_TIME_WAIT1==U_X_r cycles if phase V was Rising.*/
#define U_v_r (0x1408)
/** Triggers after DEAD_TIME_WAIT1==U_X_r cycles if phase W was Rising.*/
#define U_w_r (0x1420)
/** Triggers after DEAD_TIME_WAIT2==U_X_f cycles if phase U was Falling.*/
#define U_u_f (0x2401)
/** Triggers after DEAD_TIME_WAIT2==U_X_f cycles if phase V was Falling.*/
#define U_v_f (0x2404)
/** Triggers after DEAD_TIME_WAIT2==U_X_f cycles if phase W was Falling.*/
#define U_w_f (0x2410)

#if 0
/** Triggers after DEAD_TIME_WAIT1==U_X_r cycles if phase U was Rising.*/
#define New_U_u_r (0x2402)
/** Triggers after DEAD_TIME_WAIT1==U_X_r cycles if phase V was Rising.*/
#define New_U_v_r (0x2408)
/** Triggers after DEAD_TIME_WAIT1==U_X_r cycles if phase W was Rising.*/
#define New_U_w_r (0x2420)
/** Triggers after DEAD_TIME_WAIT2==U_X_f cycles if phase U was Falling.*/
#define New_U_u_f (0x2401)
/** Triggers after DEAD_TIME_WAIT2==U_X_f cycles if phase V was Falling.*/
#define New_U_v_f (0x2404)
/** Triggers after DEAD_TIME_WAIT2==U_X_f cycles if phase W was Falling.*/
#define New_U_w_f (0x2410)
#endif

/** This struct should be used if trigger has a value lower than 0xFFE0 to define sampling informations.*/
typedef struct
{
  /** [] */ uint16_t sample : 4;
  /** [] */ uint16_t sum : 5;
  /** [] */ uint16_t ch : 5;
  /** [] */ uint16_t trigger_type_ext : 1;
  /** [] */ uint16_t trigger_type : 1;
} _PACKED_ saradc_no_bf;

/** This struct should be used if trigger has a value higher than 0xFFE0 to define the lower barrier.*/
typedef struct
{
  /** [30:16] */ uint16_t barrier : 15;
  /**  [31]   */ uint16_t trigger_type_iar : 1;
} _PACKED_ saradc_barrier_bf;

/** Depending on the trigger the second word of a saradc command can have a different meaning.*/
typedef union {
  /** value*/ uint16_t val;
  /** saradc_no_bf*/ saradc_no_bf no;
  /** saradc_barrier_bf*/ saradc_barrier_bf until;
} _PACKED_ saradc_elem2_t;

/** An saradc command entry of a table. See SARADC register description.*/
typedef struct
{
  /** [15:0]  */ u16 target_adr;
  /** [30:16] */ saradc_elem2_t e2;
  /** [47:32] */ u16 trigger;
} saradc_table_list_entry;

/** Memory where the saradc writes the adc  values for all sampled data of a measurement window.*/
// extern __no_init  u16 bemf_voltage[2][BEMF_DATA_COUNT] @BEMF_VOLTAGE_ADDR;

#define GPIO_SAMPLE_COUNT (32)

#define GPIO_CURRENT_SAMPLE gpio[0]
#define GPIO_ADC_VGND gpio[1]
#define GPIO_I_REFERENCE gpio[2]
#define GPIO_OV_at_BP gpio[3]
#define GPIO_ADC_VBAT gpio[4]
#define GPIO_ADC_AmbientTemperature gpio[5]
#define GPIO_ADC_LAST_ADRESS gpio[6]
#define GPIO_WINDMILL_U2 gpio[10]
#define GPIO_WINDMILL_V2 gpio[11]
#define GPIO_WINDMILL_W2 gpio[12]
#define GPIO_WINDMILL_U gpio[13]
#define GPIO_WINDMILL_V gpio[14]
#define GPIO_WINDMILL_W gpio[15]
#define GPIO_I_U_R gpio[16]
#define GPIO_I_U_F gpio[17]
#define GPIO_I_V_R gpio[18]
#define GPIO_I_V_F gpio[19]
#define GPIO_I_W_R gpio[20]
#define GPIO_I_W_F gpio[21]
#define GPIO_I_BP gpio[22]
#define ADC_AmbTemperature gpio[23]
#define GPIO_I_1_SLOW gpio[25]
#define GPIO_I_2_SLOW gpio[26]
#define GPIO_I_DC gpio[27]
#define GPIO_ADC_TEMPERATURE gpio[28]
#define GPIO_ADC_VBAT_IDLE gpio[29]
#define GPIO_TADR_ADC_VBAT_COMP gpio[30]

#define GPIO_GET_ADC_VBAT_COMP (*((u16 *)((GPIO_TADR_ADC_VBAT_COMP)-2)))

#define BEMF_VOLTAGE_START_ADRESS_0 (SARADC_MEM_ADDR + 32 * 2 + 4 * 8 * 2 + 0 * BEMF_DATA_COUNT * 2)

//+2 for set tadr and store something not needed
#define ESTIMATION_ADDRESS_0 BEMF_VOLTAGE_START_ADRESS_0 + (STARTUP_SAMPLES_1 * 4 * 2 + 2) * 0
#define ESTIMATION_ADDRESS_1 BEMF_VOLTAGE_START_ADRESS_0 + (STARTUP_SAMPLES_1 * 4 * 2 + 2) * 1
#define ESTIMATION_ADDRESS_2 BEMF_VOLTAGE_START_ADRESS_0 + (STARTUP_SAMPLES_1 * 4 * 2 + 2) * 2
#define ESTIMATION_ADDRESS_3 BEMF_VOLTAGE_START_ADRESS_0 + (STARTUP_SAMPLES_1 * 4 * 2 + 2) * 3

extern __no_init volatile u16 gpio[32];
/*

*/
extern __no_init u16 currentpulse[4][8];
extern __no_init u16 bemf_voltage[2][BEMF_DATA_COUNT];

#define SARADC_MEM_MIN (SARADC_MEM_ADDR)
#define SARADC_MEM_MAX (SARADC_MEM_ADDR + (2 * BEMF_DATA_COUNT * 2) + 32 * 2 + 4 * 8 * 2)

extern saradc_table_list_entry const list_open_loop[];
/** This saradc command table continuously samples the voltage of the terminals and supply.*/
extern saradc_table_list_entry const list_windmill[];
/** This saradc command table does the startup measurements and initializes the VBAT voltage.*/
extern saradc_table_list_entry const list_estimation_1[];
extern saradc_table_list_entry const list_estimation_2[];
extern saradc_table_list_entry const list_estimation_3[];

extern saradc_table_list_entry list_bemf_start[];
extern saradc_table_list_entry list_bemf_window_0_overflow[];
extern saradc_table_list_entry list_bemf_window_0[];
extern saradc_table_list_entry list_bemf_window_1[];
extern saradc_table_list_entry list_bemf_window_2[];
extern saradc_table_list_entry list_bemf_window_3[];
extern saradc_table_list_entry list_bemf_window_4[];
extern saradc_table_list_entry list_bemf_window_5[];

extern saradc_table_list_entry const list_estimation_1_2[];
extern saradc_table_list_entry const list_estimation_2_2[];
extern saradc_table_list_entry const list_estimation_3_2[];

extern saradc_table_list_entry const ListOpenLaodDiag[];

/** @} */
#endif /* __SARADC_TABLES__ */
