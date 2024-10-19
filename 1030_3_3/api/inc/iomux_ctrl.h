#ifndef HAVE_IOMUX_H
#define HAVE_IOMUX_H

#include "base.h"

#include "iomux_ctrl_bf.h"

/********************************/
/* port A+B constants           */
/*                              */
/* 1st function : GPIO          */
/* 2nd function : 523.01 + misc */
/* 3rd function : 523.50 + misc */
/* 4th function : misc          */
/********************************/

/* port A constants */

typedef uint16_t iomux_func_a_t;

#define IOMUX_CTRL_FUNC_A0_GPIO ((iomux_func_a_t)(0 << 0))
#define IOMUX_CTRL_FUNC_A0_SPI_0_SCK ((iomux_func_a_t)(1 << 0))
#define IOMUX_CTRL_FUNC_A0_PWMN_NALLOFF ((iomux_func_a_t)(2 << 0))
#define IOMUX_CTRL_FUNC_A0_SCI_RXD ((iomux_func_a_t)(3 << 0))

#define IOMUX_CTRL_FUNC_A1_GPIO ((iomux_func_a_t)(0 << 2))
#define IOMUX_CTRL_FUNC_A1_SPI_0_SDI ((iomux_func_a_t)(1 << 2))
#define IOMUX_CTRL_FUNC_A1_CCTIMER_0_MEAS ((iomux_func_a_t)(2 << 2))
#define IOMUX_CTRL_FUNC_A1_SCI_TXD ((iomux_func_a_t)(3 << 2))

#define IOMUX_CTRL_FUNC_A2_GPIO ((iomux_func_a_t)(0 << 4))
#define IOMUX_CTRL_FUNC_A2_SPI_0_SDO ((iomux_func_a_t)(1 << 4))
#define IOMUX_CTRL_FUNC_A2_SARADC_CTRL_MUX0 ((iomux_func_a_t)(2 << 4))
#define IOMUX_CTRL_FUNC_A2_PWMN_X_N ((iomux_func_a_t)(3 << 4))

#define IOMUX_CTRL_FUNC_A3_GPIO ((iomux_func_a_t)(0 << 6))
#define IOMUX_CTRL_FUNC_A3_SPI_0_NSS ((iomux_func_a_t)(1 << 6))
#define IOMUX_CTRL_FUNC_A3_SARADC_CTRL_MUX1 ((iomux_func_a_t)(2 << 6))
#define IOMUX_CTRL_FUNC_A3_SYS_STATE_CLK ((iomux_func_a_t)(3 << 6))

#define IOMUX_CTRL_FUNC_A4_GPIO ((iomux_func_a_t)(0 << 8))
#define IOMUX_CTRL_FUNC_A4_SYS_STATE_CLK ((iomux_func_a_t)(1 << 8))
#define IOMUX_CTRL_FUNC_A4_PWMN_U_N ((iomux_func_a_t)(2 << 8))
#define IOMUX_CTRL_FUNC_A4_PWMN_X_P ((iomux_func_a_t)(3 << 8))

#define IOMUX_CTRL_FUNC_A5_GPIO ((iomux_func_a_t)(0 << 10))
#define IOMUX_CTRL_FUNC_A5_PWMN_U_N ((iomux_func_a_t)(1 << 10))
#define IOMUX_CTRL_FUNC_A5_PWMN_V_N ((iomux_func_a_t)(2 << 10))
#define IOMUX_CTRL_FUNC_A5_CCTIMER_0_PWM ((iomux_func_a_t)(3 << 10))

#define IOMUX_CTRL_FUNC_A6_GPIO ((iomux_func_a_t)(0 << 12))
#define IOMUX_CTRL_FUNC_A6_PWMN_V_N ((iomux_func_a_t)(1 << 12))
#define IOMUX_CTRL_FUNC_A6_PWMN_W_N ((iomux_func_a_t)(2 << 12))
#define IOMUX_CTRL_FUNC_A6_CCTIMER_1_PWM ((iomux_func_a_t)(3 << 12))

#define IOMUX_CTRL_FUNC_A7_GPIO ((iomux_func_a_t)(0 << 14))
#define IOMUX_CTRL_FUNC_A7_PWMN_W_N ((iomux_func_a_t)(1 << 14))
#define IOMUX_CTRL_FUNC_A7_CCTIMER_1_MEAS ((iomux_func_a_t)(2 << 14))
#define IOMUX_CTRL_FUNC_A7_SARADC_CTRL_MUX0 ((iomux_func_a_t)(3 << 14))

/* port B constants */

typedef uint16_t iomux_func_b_t;

#define IOMUX_CTRL_FUNC_B0_GPIO ((iomux_func_b_t)(0 << 0))
#define IOMUX_CTRL_FUNC_B0_SCI_RXD ((iomux_func_b_t)(1 << 0))
#define IOMUX_CTRL_FUNC_B0_CCTIMER_2_MEAS ((iomux_func_b_t)(2 << 0))
#define IOMUX_CTRL_FUNC_B0_SARADC_CTRL_MUX1 ((iomux_func_b_t)(3 << 0))

#define IOMUX_CTRL_FUNC_B1_GPIO ((iomux_func_b_t)(0 << 2))
#define IOMUX_CTRL_FUNC_B1_SCI_TXD ((iomux_func_b_t)(1 << 2))
#define IOMUX_CTRL_FUNC_B1_PWMN_U_P ((iomux_func_b_t)(2 << 2))
#define IOMUX_CTRL_FUNC_B1_SARADC_CTRL_MUX0 ((iomux_func_b_t)(3 << 2))

#define IOMUX_CTRL_FUNC_B2_GPIO ((iomux_func_b_t)(0 << 4))
#define IOMUX_CTRL_FUNC_B2_PWMN_U_P ((iomux_func_b_t)(1 << 4))
#define IOMUX_CTRL_FUNC_B2_PWMN_V_P ((iomux_func_b_t)(2 << 4))
#define IOMUX_CTRL_FUNC_B2_SCI_RXD ((iomux_func_b_t)(3 << 4))

#define IOMUX_CTRL_FUNC_B3_GPIO ((iomux_func_b_t)(0 << 6))
#define IOMUX_CTRL_FUNC_B3_PWMN_V_P ((iomux_func_b_t)(1 << 6))
#define IOMUX_CTRL_FUNC_B3_PWMN_W_P ((iomux_func_b_t)(2 << 6))
#define IOMUX_CTRL_FUNC_B3_CCTIMER_2_PWM ((iomux_func_b_t)(3 << 6))

#define IOMUX_CTRL_FUNC_B4_GPIO ((iomux_func_b_t)(0 << 8))
#define IOMUX_CTRL_FUNC_B4_PWMN_W_P ((iomux_func_b_t)(1 << 8))
#define IOMUX_CTRL_FUNC_B4_PWMN_NALLOFF ((iomux_func_b_t)(2 << 8))
#define IOMUX_CTRL_FUNC_B4_SCI_TXD ((iomux_func_b_t)(3 << 8))

#define IOMUX_CTRL_FUNC_B5_GPIO ((iomux_func_b_t)(0 << 10))
#define IOMUX_CTRL_FUNC_B5_PWMN_NALLOFF ((iomux_func_b_t)(1 << 10))
#define IOMUX_CTRL_FUNC_B5_SARADC_DBG_SMPL ((iomux_func_b_t)(2 << 10))
#define IOMUX_CTRL_FUNC_B5_SYNC_W ((iomux_func_b_t)(3 << 10))

#define IOMUX_CTRL_FUNC_B6_GPIO ((iomux_func_b_t)(0 << 12))
#define IOMUX_CTRL_FUNC_B6_SCI_RXD ((iomux_func_b_t)(1 << 12))
#define IOMUX_CTRL_FUNC_B6_PWMN_X_N ((iomux_func_b_t)(2 << 12))
#define IOMUX_CTRL_FUNC_B6_SYNC_W ((iomux_func_b_t)(3 << 12))

#define IOMUX_CTRL_FUNC_B7_GPIO ((iomux_func_b_t)(0 << 14))
#define IOMUX_CTRL_FUNC_B7_SCI_TXD ((iomux_func_b_t)(1 << 14))
#define IOMUX_CTRL_FUNC_B7_PWMN_X_P ((iomux_func_b_t)(2 << 14))
#define IOMUX_CTRL_FUNC_B7_SARADC_DBG_SMPL ((iomux_func_b_t)(3 << 14))

/* port C constants */

typedef enum
{
  IOMUX_CTRL_PORT_NO_0 = 0,
  IOMUX_CTRL_PORT_NO_1 = 1,
  IOMUX_CTRL_PORT_NO_2 = 2,
  IOMUX_CTRL_PORT_NO_3 = 3,
  IOMUX_CTRL_PORT_NO_4 = 4,
  IOMUX_CTRL_PORT_NO_5 = 5,
  IOMUX_CTRL_PORT_NO_6 = 6,
  IOMUX_CTRL_PORT_NO_7 = 7
} iomux_port_no_c_t;

typedef enum
{
  IOMUX_CTRL_FUNC_C_GPIO = 0,

  IOMUX_CTRL_FUNC_C_SPI_1_NSS = 1,
  IOMUX_CTRL_FUNC_C_SPI_1_SCK = 2,
  IOMUX_CTRL_FUNC_C_SPI_1_SDO = 3,
  IOMUX_CTRL_FUNC_C_SPI_1_SDI = 4,

  IOMUX_CTRL_FUNC_C_CCTIMER_0_MEAS = 5,
  IOMUX_CTRL_FUNC_C_CCTIMER_0_PWM = 6,
  IOMUX_CTRL_FUNC_C_CCTIMER_1_MEAS = 7,
  IOMUX_CTRL_FUNC_C_CCTIMER_1_PWM = 8,
  IOMUX_CTRL_FUNC_C_CCTIMER_2_MEAS = 9,
  IOMUX_CTRL_FUNC_C_CCTIMER_2_PWM = 10,
  IOMUX_CTRL_FUNC_C_CCTIMER_3_MEAS = 11,
  IOMUX_CTRL_FUNC_C_CCTIMER_3_PWM = 12,

  IOMUX_CTRL_FUNC_C_SYNC_U = 13,
  IOMUX_CTRL_FUNC_C_SYNC_V = 14,
  IOMUX_CTRL_FUNC_C_SARADC_SYNC_OUT = 15
} iomux_func_c_t;

/* lock passwords */

#define IOMUX_CTRL_WPASS 0xA5
#define IOMUX_CTRL_RPASS 0x96

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void iomux_ctrl_select_a(iomux_func_a_t func);
void iomux_ctrl_select_b(iomux_func_b_t func);
void iomux_ctrl_select_c(iomux_port_no_c_t port_no, iomux_func_c_t func);

void iomux_ctrl_set_lock_a(uint8_t val);
void iomux_ctrl_set_lock_b(uint8_t val);
void iomux_ctrl_set_lock_c(uint8_t val);

uint8_t iomux_ctrl_get_lock_a(void);
uint8_t iomux_ctrl_get_lock_b(void);
uint8_t iomux_ctrl_get_lock_c(void);

#endif /* HAVE_IOMUX_H */
