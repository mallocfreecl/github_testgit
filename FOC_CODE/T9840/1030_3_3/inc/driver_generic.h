#ifndef __DRIVER_GENERIC__
#define __DRIVER_GENERIC__

#include "MotorAPI.h"
#include "commons.h"
#include "driver_52350.h"

#define ADC_MULT_COUNTER 5              // 2,5V
#define ADC_MULT_DENOMINATOR (2 * 4096) //*2 to use 5V instead of 2,5V
#define ADC_CONVERSION_COUNTER ((u64)ADC_MULT_COUNTER * (u64)DRIVER_DIV_DENOMINATOR * 1000)
#define ADC_CONVERSION_DIVIDER ((u64)ADC_MULT_DENOMINATOR * (u64)DRIVER_DIV_COUNTER)

#define ADC_CONVERSION_COUNTER_HIGH ((u64)ADC_MULT_COUNTER * (u64)DRIVER_DIV_DENOMINATOR_HIGH * 1000)
#define ADC_CONVERSION_DIVIDER_HIGH ((u64)ADC_MULT_DENOMINATOR * (u64)DRIVER_DIV_COUNTER_HIGH)

//#define ADC_CONVERSION_FACTOR_Q16_16  (((u64)ADC_CONVERSION_COUNTER<<16)/(u64)ADC_CONVERSION_DIVIDER)
//#define ADC_CONVERSION_DIVIDER_Q16_16 (((u64)ADC_CONVERSION_DIVIDER<<16)/(u64)ADC_CONVERSION_COUNTER)

#define ADC_CONVERSION_FACTOR_HIGH_Q16_16 (((u64)ADC_CONVERSION_COUNTER_HIGH << 16) / (u64)ADC_CONVERSION_DIVIDER_HIGH)
#define ADC_CONVERSION_DIVIDER_HIGH_Q16_16 (((u64)ADC_CONVERSION_DIVIDER_HIGH << 16) / (u64)ADC_CONVERSION_COUNTER_HIGH)

#define ADC_DIVIDER_CONVERSION_LOW_TO_HIGH_Q16

/**
 * @defgroup HAL Hardware abstraction layer for driver interfaces
 * @ingroup OTHER
 *
 * This module provides hardware abstraction layer functions.
 * The API calls to configure and operate the MOTCU and driver peripherals are abstracted.
 * The flag T52350/T52351 is used to switch the called function in driver_52350.c and driver_52301.c.
 *
 * @{
 */

#define DRIVER_ANY_SHORT_CIRCUIT_BITS                                                                                  \
  (DRIVER_LS1_SHORT_CIRCUIT | DRIVER_LS2_SHORT_CIRCUIT | DRIVER_LS3_SHORT_CIRCUIT | DRIVER_HS1_SHORT_CIRCUIT |         \
   DRIVER_HS2_SHORT_CIRCUIT | DRIVER_HS3_SHORT_CIRCUIT)
#define DRIVER_SC_OR_OC_BITS (DRIVER_ANY_SHORT_CIRCUIT_BITS | DRIVER_OVERCURRENT)
#define DRIVER_ANY_UNDERVOLTAGE_BITS (DRIVER_VCC_UNDERVOLTAGE | DRIVER_VG_UNDERVOLTAGE)
#define DRIVER_ANY_OVERVOLTAGE_BITS (DRIVER_VG_OVERVOLTAGE | DRIVER_VBAT_OVERVOLTAGE)

/**
 * An enumeration type to identify all possible driver errors.<BR>
 * When using the E523.01 high voltage gate driver, see IRQSTAT1 and IRQSTAT2 register description (chapter 6.8.5 of the
 * E523.01 datasheet) for details.<BR> When using the E523.50 high voltage gate driver, a subset of possible entries is
 * used. See ERR1 and ERR2 reporting (chapter 5.3 of the E523.50 datasheet) for details.
 */
#define DRIVER_OK 0 /**<  No error was detected, normal operation */
#define DRIVER_LS1_SHORT_CIRCUIT                                                                                       \
  0x0001 /**<  E523.01: Drain-Source voltage of the low side FET at channel 1 exceeded                                 \
          *    threshold, configured in SCTH-register, while it was switched on.                                       \
          *<BR>E523.50: not used */
#define DRIVER_LS2_SHORT_CIRCUIT                                                                                       \
  0x0002 /**<  E523.01: Drain-Source voltage of the low side FET at channel 2 exceeded                                 \
          *    threshold, configured in SCTH-register, while it was switched on.                                       \
          *<BR>E523.50: not used */
#define DRIVER_LS3_SHORT_CIRCUIT                                                                                       \
  0x0004 /**<  E523.01: Drain-Source voltage of the low side FET at channel 3 exceeded                                 \
          *    threshold, configured in SCTH-register, while it was switched on.                                       \
          *<BR>E523.50: not used */
#define DRIVER_HS1_SHORT_CIRCUIT                                                                                       \
  0x0008 /**<  E523.01: Drain-Source voltage of the high side FET at channel 1 exceeded                                \
          *    threshold, configured in SCTH-register, while it was switched on.                                       \
          *<BR>E523.50: not used */
#define DRIVER_HS2_SHORT_CIRCUIT                                                                                       \
  0x0010 /**<  E523.01: Drain-Source voltage of the high side FET at channel 2 exceeded                                \
          *    threshold, configured in SCTH-register, while it was switched on.                                       \
          *<BR>E523.50: not used */
#define DRIVER_HS3_SHORT_CIRCUIT                                                                                       \
  0x0020 /**<  E523.01: Drain-Source voltage of the high side FET at channel 3 exceeded                                \
          *    threshold, configured in SCTH-register, while it was switched on.                                       \
          *<BR>E523.50: not used */
#define DRIVER_OVERCURRENT                                                                                             \
  0x0040 /**<  Voltage at IO-comparator exceeded threshhold, configured in IOCOMPTHR-register                          \
          *<BR>E523.01: range: (((0...63)/64) * Vdd)                                                                   \
          *<BR>E523.50: 0.9 * Vdd) */
#define DRIVER_OVERTEMP                                                                                                \
  0x0080                               /**<  E523.01: Temperature exceeded 150°C                                      \
                                        *<BR>E523.50: Temperature exceeded 170°C */
#define DRIVER_VCC_UNDERVOLTAGE 0x0100 /**<  VCC dropped below 3.3/5V, depending on chosen mode */
#define DRIVER_VG_UNDERVOLTAGE                                                                                         \
  0x0200 /**<  E523.01: VG Voltage dropped below 6.4V in normal mode(5.4V in 6V mode);                                 \
          *<BR>E523.50: VG Voltage dropped below 8.75V; */
#define DRIVER_VG_OVERVOLTAGE                                                                                          \
  0x0400 /**<  E523.01: VG Voltage exceeded 14V;                                                                       \
          *<BR>E523.50: not used */
#define DRIVER_VBAT_OVERVOLTAGE                                                                                        \
  0x0800 /**<  E523.01: Supply Voltage exceeded 30V;                                                                   \
          *<BR>E523.50: not used */
#define DRIVER_PWM_DETECTION                                                                                           \
  0x1000 /**<  E523.01: new register values are available, by the PWM-Interface                                        \
          *<BR>E523.50: not used */
#define DRIVER_REG_WATCHDOG                                                                                            \
  0x2000 /**<  E523.01: watchdog is configured in register mode and has not been triggered                             \
          *<BR>E523.50: not used */
#define DRIVER_CLOCK_WATCHDOG                                                                                          \
  0x4000                      /**<  E523.01: watchdog is configured in CLK mode and has not received an CLK-signal     \
                               *<BR>E523.50: not used */
#define DRIVER_UNKNOWN 0xFFFF /**<  an unknown error occurred; should never happen */
//}driver_error_t;

typedef struct
{
  u16 ls1_sc : 1;         /* [  0] */
  u16 ls2_sc : 1;         /* [  1] */
  u16 ls3_sc : 1;         /* [  2] */
  u16 hs1_sc : 1;         /* [  3] */
  u16 hs2_sc : 1;         /* [  4] */
  u16 hs3_sc : 1;         /* [  5] */
  u16 oc : 1;             /* [  6] */
  u16 ot : 1;             /* [  7] */
  u16 vcc_uv : 1;         /* [  8] */
  u16 vg_uv : 1;          /* [  9] */
  u16 vg_ov : 1;          /* [ 10] */
  u16 vbat_ov : 1;        /* [ 11] */
  u16 pwm_detected : 1;   /* [ 12] */
  u16 reg_watchdog : 1;   /* [ 13] */
  u16 clock_watchdog : 1; /* [ 14] */
  u16 reserved : 1;       /* [ 15] */
} _PACKED_ driver_error_bf;

typedef enum
{
  ePinOutLow,
  ePinOutHigh,
  ePinOutToggle,
  ePinOutInValid
} PinOut_t;

/* Monitor chip fault, 21.07.30 by yhd */
typedef union {
  u32 reg;
  struct
  {
    u32 SysClkFail : 1;
    u32 WDogRst : 1;
    u32 CPUParityRst : 1;
    u32 SRAMParity : 1;
    u32 FlashBitErr1 : 1;
    u32 FlashBitErr2 : 1;
    u32 sram_wr_prot : 1;
    u32 stack_prot : 1;

    u32 exec_prot : 1;
    u32 bad_access : 1;
    u32 SCI_FE : 1;
    u32 SCI_OV : 1;
    u32 dma_read_err : 1;
    u32 dma_write_err : 1;
    u32 reload_error_evt : 1;
    u32 overcurrent : 1;

    u32 DrvOc : 1;
    u32 DrvOT : 1;
    u32 VCC_UV : 1;
    u32 VG_UV : 1;
  } bit;

} ChipFaults_t;

extern ChipFaults_t ChipFaults;

extern void SDK_HardWareInit(void);
extern void SDK_SCIInitLater(void);
extern void SDK_MCUDiagOut(PinOut_t Out);
extern void SDK_SCITxIntEn(bool Enable);
extern void SDK_InterruptEnable(void);
extern void SDK_InterruptDisable(void);
extern bool SDK_IsChipFault(void);
extern void SDK_ChipSleep(void);
extern void SDK_ChipReset(void);
extern void SDK_SWRst(void);

// implementation driver specific

/**
 * @brief The MOTCU peripherals are initialized, including SPI.
 */
void SDK_GPIOInit(void);

/**
 * @brief Configures the driver peripherals per SPI, but leaves the H bridge power source set to off.
 */
void SDK_MotorDrvOff(void);

/**
 * @brief The SPI the H bridge power source is set to on and the gate is controlled by the MOTCU generated PWM signals.
 */
void SDK_MotorDrvOn(void);

/**
 * @brief The SPI the H bridge power source is set to idle and the low and high gate are set to high impedance.
 */
void SDK_MotorDrvLowPower(void);

/**
 * @brief Gets and error code of the driver peripherals per SPI or GPIO signal.
 * @retval Error                        State of the driver as a bitfield.
 */
driver_error_t SDK_MotorDrvGetStatus(void);

/**
 * @brief Clears the error or errors of the driver peripherals per SPI or GPIO signal.
 */
void SDK_MotorDrvClearError(driver_error_t error);

extern void SDK_FeedWDOG(void);

/** @} */
#endif
