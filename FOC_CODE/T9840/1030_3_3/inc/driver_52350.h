#ifdef T52350

#ifndef __DRIVER_52350__
#define __DRIVER_52350__

#include "commons.h"
#include "types.h"

/** Switch if R_DT is missing on evaluation board*/
#define DRIVER_DEADTIME_GENERATION 0
/** See SARADC CFG register description.*/
#define DRIVER_WITH_MUXER 1 // 523.50 has internal multiplexer BEMF-measurement
/** See SARADC CFG register description.*/
#define DRIVER_MUXER_CHANNEL_NUMBER (12) // PB4

/** Voltage divider*/
#define DRIVER_DIVIDER_HIGH (10 / 2882)
#define DRIVER_DIV_COUNTER_HIGH (100)
#define DRIVER_DIV_DENOMINATOR_HIGH (2880)

#define DRIVER_DIVIDER (10 / 192)
#define DRIVER_DIV_COUNTER (10)
#define DRIVER_DIV_DENOMINATOR (192)

//(100×192)÷(10×2882)=0,666204025
#define DRIVER_DIVIDER_CONV_LOW_TO_HIGH (((((u64)100 * (u64)192)) << 16) / ((u64)10 * 2882))

// writeback of calibration values
// mcu measured reference + fine tuning(5mA more)
#define DRIVER_CURRENT_REFERENCE (32400 - 131)
#define DRIVER_CURRENT_FACTOR 1225

// A0 = 0; B0 = 8; C0 = 16; 32 = Not connected
/** Channel  Shunt.*/
/* 修改母线电流采样端口为PC5，该端口采样的是外部滤波后的母线电流，23.06.28 by lxs */
//#define ADC_CH_RShunt (13) // = PB5
#define ADC_CH_RShunt (21) // = PC5
/** Channel  VBAT  */
#define SUPPLY (0) // DRIVER_MUXER_CHANNEL_NUMBER 0
/** Channel  coil U*/
#define BEMF_U (1) // DRIVER_MUXER_CHANNEL_NUMBER 1
/** Channel  coil V*/
#define BEMF_V (2) // DRIVER_MUXER_CHANNEL_NUMBER 2
/** Channel  coil W*/
#define BEMF_W (3) // DRIVER_MUXER_CHANNEL_NUMBER 3
/** Channel Speedset*/
#define ADC_CH_AmbientTemperature (23) // PC7
/** Channel TEMPERATURE*/
#define ADC_CH_Chip_TEMPERATURE (24)

#define BANK_DRIVER_RUN GPIO_A
#define PIN_DRIVER_RUN GPIO_IO_1

#define BANK_DRIVER_ERROR1 GPIO_A
#define PIN_DRIVER_ERROR1 GPIO_IO_7
#define PIN_DRIVER_ERROR1_SET GPIO_IRQ_EVT_POS_7
#define PIN_DRIVER_ERROR1_CLR GPIO_IRQ_EVT_NEG_7

#define BANK_DRIVER_ERROR2 GPIO_B
#define PIN_DRIVER_ERROR2 GPIO_IO_0
#define PIN_DRIVER_ERROR2_SET GPIO_IRQ_EVT_POS_0
#define PIN_DRIVER_ERROR2_CLR GPIO_IRQ_EVT_NEG_0

#define AADDR_IRQ_DRIVER_ERROR1 (BANK_DRIVER_ERROR1 + ADDR_GPIO_IRQ_STATUS)
#define AADDR_IRQ_DRIVER_ERROR2 (BANK_DRIVER_ERROR2 + ADDR_GPIO_IRQ_STATUS)

#endif
/** @} */
#endif
