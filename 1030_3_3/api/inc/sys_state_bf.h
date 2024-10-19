#ifndef __SYS_STATE_BF_H__
#define __SYS_STATE_BF_H__

#ifdef __CC_ARM
#ifndef _PACKED_
#define _PACKED_ __packed
#endif
#endif

#ifdef __ARMCC_VERSION
#ifndef _PACKED_
#define _PACKED_ __packed
#endif
#endif

#ifdef __GNUC__
#ifndef _PACKED_
#define _PACKED_ __attribute__((packed))
#endif
#endif

#ifdef __IARC__
#pragma pack(1)
#ifndef _PACKED_
#define _PACKED_
#endif
#endif

#ifdef __IAR_SYSTEMS_ICC__
#pragma pack(1)
#ifndef _PACKED_
#define _PACKED_
#endif
#endif

#ifdef _MSC_VER
#ifndef _PACKED_
#define _PACKED_
#endif
#endif

#ifndef _PACKED_
#error "UNKNOWN COMPILER"
#endif

// Instance base addresses

#ifndef BASE_ADDR_SYS_STATE
#define BASE_ADDR_SYS_STATE 0x0180U
#endif

#define NUMBER_SYS_STATE 1

typedef enum
{
  SYS_STATE = (int)BASE_ADDR_SYS_STATE
} sys_state_num_t;

// Register bit field definitions

/* SYS_STATE_MODULE_ENABLE */

#define MSK_SYS_STATE_MODULE_ENABLE_SCI (0x1) /* [1] */
#define SFT_SYS_STATE_MODULE_ENABLE_SCI (1)
#define LSB_SYS_STATE_MODULE_ENABLE_SCI (1)
#define MSB_SYS_STATE_MODULE_ENABLE_SCI (1)
#define BIT_SYS_STATE_MODULE_ENABLE_SCI (0x2)   /* [1] */
#define MSK_SYS_STATE_MODULE_ENABLE_SPI_0 (0x1) /* [2] */
#define SFT_SYS_STATE_MODULE_ENABLE_SPI_0 (2)
#define LSB_SYS_STATE_MODULE_ENABLE_SPI_0 (2)
#define MSB_SYS_STATE_MODULE_ENABLE_SPI_0 (2)
#define BIT_SYS_STATE_MODULE_ENABLE_SPI_0 (0x4) /* [2] */
#define MSK_SYS_STATE_MODULE_ENABLE_SPI_1 (0x1) /* [3] */
#define SFT_SYS_STATE_MODULE_ENABLE_SPI_1 (3)
#define LSB_SYS_STATE_MODULE_ENABLE_SPI_1 (3)
#define MSB_SYS_STATE_MODULE_ENABLE_SPI_1 (3)
#define BIT_SYS_STATE_MODULE_ENABLE_SPI_1 (0x8)  /* [3] */
#define MSK_SYS_STATE_MODULE_ENABLE_GPIO_A (0x1) /* [4] */
#define SFT_SYS_STATE_MODULE_ENABLE_GPIO_A (4)
#define LSB_SYS_STATE_MODULE_ENABLE_GPIO_A (4)
#define MSB_SYS_STATE_MODULE_ENABLE_GPIO_A (4)
#define BIT_SYS_STATE_MODULE_ENABLE_GPIO_A (0x10) /* [4] */
#define MSK_SYS_STATE_MODULE_ENABLE_GPIO_B (0x1)  /* [5] */
#define SFT_SYS_STATE_MODULE_ENABLE_GPIO_B (5)
#define LSB_SYS_STATE_MODULE_ENABLE_GPIO_B (5)
#define MSB_SYS_STATE_MODULE_ENABLE_GPIO_B (5)
#define BIT_SYS_STATE_MODULE_ENABLE_GPIO_B (0x20) /* [5] */
#define MSK_SYS_STATE_MODULE_ENABLE_GPIO_C (0x1)  /* [6] */
#define SFT_SYS_STATE_MODULE_ENABLE_GPIO_C (6)
#define LSB_SYS_STATE_MODULE_ENABLE_GPIO_C (6)
#define MSB_SYS_STATE_MODULE_ENABLE_GPIO_C (6)
#define BIT_SYS_STATE_MODULE_ENABLE_GPIO_C (0x40)   /* [6] */
#define MSK_SYS_STATE_MODULE_ENABLE_CCTIMER_0 (0x1) /* [7] */
#define SFT_SYS_STATE_MODULE_ENABLE_CCTIMER_0 (7)
#define LSB_SYS_STATE_MODULE_ENABLE_CCTIMER_0 (7)
#define MSB_SYS_STATE_MODULE_ENABLE_CCTIMER_0 (7)
#define BIT_SYS_STATE_MODULE_ENABLE_CCTIMER_0 (0x80) /* [7] */
#define MSK_SYS_STATE_MODULE_ENABLE_CCTIMER_1 (0x1)  /* [8] */
#define SFT_SYS_STATE_MODULE_ENABLE_CCTIMER_1 (8)
#define LSB_SYS_STATE_MODULE_ENABLE_CCTIMER_1 (8)
#define MSB_SYS_STATE_MODULE_ENABLE_CCTIMER_1 (8)
#define BIT_SYS_STATE_MODULE_ENABLE_CCTIMER_1 (0x100) /* [8] */
#define MSK_SYS_STATE_MODULE_ENABLE_CCTIMER_2 (0x1)   /* [9] */
#define SFT_SYS_STATE_MODULE_ENABLE_CCTIMER_2 (9)
#define LSB_SYS_STATE_MODULE_ENABLE_CCTIMER_2 (9)
#define MSB_SYS_STATE_MODULE_ENABLE_CCTIMER_2 (9)
#define BIT_SYS_STATE_MODULE_ENABLE_CCTIMER_2 (0x200) /* [9] */
#define MSK_SYS_STATE_MODULE_ENABLE_CCTIMER_3 (0x1)   /* [10] */
#define SFT_SYS_STATE_MODULE_ENABLE_CCTIMER_3 (10)
#define LSB_SYS_STATE_MODULE_ENABLE_CCTIMER_3 (10)
#define MSB_SYS_STATE_MODULE_ENABLE_CCTIMER_3 (10)
#define BIT_SYS_STATE_MODULE_ENABLE_CCTIMER_3 (0x400) /* [10] */
#define MSK_SYS_STATE_MODULE_ENABLE_SARADC_CTRL (0x1) /* [11] */
#define SFT_SYS_STATE_MODULE_ENABLE_SARADC_CTRL (11)
#define LSB_SYS_STATE_MODULE_ENABLE_SARADC_CTRL (11)
#define MSB_SYS_STATE_MODULE_ENABLE_SARADC_CTRL (11)
#define BIT_SYS_STATE_MODULE_ENABLE_SARADC_CTRL (0x800) /* [11] */
#define MSK_SYS_STATE_MODULE_ENABLE_PRE_PWM (0x1)       /* [12] */
#define SFT_SYS_STATE_MODULE_ENABLE_PRE_PWM (12)
#define LSB_SYS_STATE_MODULE_ENABLE_PRE_PWM (12)
#define MSB_SYS_STATE_MODULE_ENABLE_PRE_PWM (12)
#define BIT_SYS_STATE_MODULE_ENABLE_PRE_PWM (0x1000) /* [12] */
#define MSK_SYS_STATE_MODULE_ENABLE_PWMN (0x1)       /* [13] */
#define SFT_SYS_STATE_MODULE_ENABLE_PWMN (13)
#define LSB_SYS_STATE_MODULE_ENABLE_PWMN (13)
#define MSB_SYS_STATE_MODULE_ENABLE_PWMN (13)
#define BIT_SYS_STATE_MODULE_ENABLE_PWMN (0x2000) /* [13] */

typedef struct
{
  unsigned short reserved0 : 1;   /* [0] */
  unsigned short sci : 1;         /* [1] */
  unsigned short spi_0 : 1;       /* [2] */
  unsigned short spi_1 : 1;       /* [3] */
  unsigned short gpio_a : 1;      /* [4] */
  unsigned short gpio_b : 1;      /* [5] */
  unsigned short gpio_c : 1;      /* [6] */
  unsigned short cctimer_0 : 1;   /* [7] */
  unsigned short cctimer_1 : 1;   /* [8] */
  unsigned short cctimer_2 : 1;   /* [9] */
  unsigned short cctimer_3 : 1;   /* [10] */
  unsigned short saradc_ctrl : 1; /* [11] */
  unsigned short pre_pwm : 1;     /* [12] */
  unsigned short pwmn : 1;        /* [13] */
  unsigned short reserved : 2;
} _PACKED_ sys_state_module_enable_bf;

typedef union {
  unsigned short val;
  sys_state_module_enable_bf bf;
} _PACKED_ sys_state_module_enable_t;

/* SYS_STATE_CONTROL */

#define MSK_SYS_STATE_CONTROL_SYS_CLK_SEL (0x7) /* [ 2:0] */
#define SFT_SYS_STATE_CONTROL_SYS_CLK_SEL (0)
#define LSB_SYS_STATE_CONTROL_SYS_CLK_SEL (0)
#define MSB_SYS_STATE_CONTROL_SYS_CLK_SEL (2)
#define MSK_SYS_STATE_CONTROL_DRV_STRENGTH (0x1) /* [3] */
#define SFT_SYS_STATE_CONTROL_DRV_STRENGTH (3)
#define LSB_SYS_STATE_CONTROL_DRV_STRENGTH (3)
#define MSB_SYS_STATE_CONTROL_DRV_STRENGTH (3)
#define BIT_SYS_STATE_CONTROL_DRV_STRENGTH (0x8) /* [3] */
#define MSK_SYS_STATE_CONTROL_TARGET_CLK_L (0x7) /* [ 6:4] */
#define SFT_SYS_STATE_CONTROL_TARGET_CLK_L (4)
#define LSB_SYS_STATE_CONTROL_TARGET_CLK_L (4)
#define MSB_SYS_STATE_CONTROL_TARGET_CLK_L (6)
#define MSK_SYS_STATE_CONTROL_TARGET_CLK_H (0x7) /* [ 9:7] */
#define SFT_SYS_STATE_CONTROL_TARGET_CLK_H (7)
#define LSB_SYS_STATE_CONTROL_TARGET_CLK_H (7)
#define MSB_SYS_STATE_CONTROL_TARGET_CLK_H (9)
#define MSK_SYS_STATE_CONTROL_SYS_CLK_ADJUST (0x3f) /* [15:10] */
#define SFT_SYS_STATE_CONTROL_SYS_CLK_ADJUST (10)
#define LSB_SYS_STATE_CONTROL_SYS_CLK_ADJUST (10)
#define MSB_SYS_STATE_CONTROL_SYS_CLK_ADJUST (15)

typedef struct
{
  unsigned short sys_clk_sel : 3;    /* [ 2:0] */
  unsigned short drv_strength : 1;   /* [3] */
  unsigned short target_clk_l : 3;   /* [ 6:4] */
  unsigned short target_clk_h : 3;   /* [ 9:7] */
  unsigned short sys_clk_adjust : 6; /* [15:10] */
} _PACKED_ sys_state_control_bf;

typedef union {
  unsigned short val;
  sys_state_control_bf bf;
} _PACKED_ sys_state_control_t;

/* SYS_STATE_RESET_STATUS */

#define MSK_SYS_STATE_RESET_STATUS_POR (0x1) /* [0] */
#define SFT_SYS_STATE_RESET_STATUS_POR (0)
#define LSB_SYS_STATE_RESET_STATUS_POR (0)
#define MSB_SYS_STATE_RESET_STATUS_POR (0)
#define BIT_SYS_STATE_RESET_STATUS_POR (0x1)      /* [0] */
#define MSK_SYS_STATE_RESET_STATUS_VDDIO_OK (0x1) /* [1] */
#define SFT_SYS_STATE_RESET_STATUS_VDDIO_OK (1)
#define LSB_SYS_STATE_RESET_STATUS_VDDIO_OK (1)
#define MSB_SYS_STATE_RESET_STATUS_VDDIO_OK (1)
#define BIT_SYS_STATE_RESET_STATUS_VDDIO_OK (0x2) /* [1] */
#define MSK_SYS_STATE_RESET_STATUS_VDDC_OK (0x1)  /* [2] */
#define SFT_SYS_STATE_RESET_STATUS_VDDC_OK (2)
#define LSB_SYS_STATE_RESET_STATUS_VDDC_OK (2)
#define MSB_SYS_STATE_RESET_STATUS_VDDC_OK (2)
#define BIT_SYS_STATE_RESET_STATUS_VDDC_OK (0x4) /* [2] */
#define MSK_SYS_STATE_RESET_STATUS_NRSTI (0x1)   /* [3] */
#define SFT_SYS_STATE_RESET_STATUS_NRSTI (3)
#define LSB_SYS_STATE_RESET_STATUS_NRSTI (3)
#define MSB_SYS_STATE_RESET_STATUS_NRSTI (3)
#define BIT_SYS_STATE_RESET_STATUS_NRSTI (0x8)        /* [3] */
#define MSK_SYS_STATE_RESET_STATUS_SYS_CLK_FAIL (0x1) /* [4] */
#define SFT_SYS_STATE_RESET_STATUS_SYS_CLK_FAIL (4)
#define LSB_SYS_STATE_RESET_STATUS_SYS_CLK_FAIL (4)
#define MSB_SYS_STATE_RESET_STATUS_SYS_CLK_FAIL (4)
#define BIT_SYS_STATE_RESET_STATUS_SYS_CLK_FAIL (0x10) /* [4] */
#define MSK_SYS_STATE_RESET_STATUS_WATCHDOG (0x1)      /* [5] */
#define SFT_SYS_STATE_RESET_STATUS_WATCHDOG (5)
#define LSB_SYS_STATE_RESET_STATUS_WATCHDOG (5)
#define MSB_SYS_STATE_RESET_STATUS_WATCHDOG (5)
#define BIT_SYS_STATE_RESET_STATUS_WATCHDOG (0x20) /* [5] */
#define MSK_SYS_STATE_RESET_STATUS_SW_RESET (0x1)  /* [6] */
#define SFT_SYS_STATE_RESET_STATUS_SW_RESET (6)
#define LSB_SYS_STATE_RESET_STATUS_SW_RESET (6)
#define MSB_SYS_STATE_RESET_STATUS_SW_RESET (6)
#define BIT_SYS_STATE_RESET_STATUS_SW_RESET (0x40)  /* [6] */
#define MSK_SYS_STATE_RESET_STATUS_CPU_PARITY (0x1) /* [7] */
#define SFT_SYS_STATE_RESET_STATUS_CPU_PARITY (7)
#define LSB_SYS_STATE_RESET_STATUS_CPU_PARITY (7)
#define MSB_SYS_STATE_RESET_STATUS_CPU_PARITY (7)
#define BIT_SYS_STATE_RESET_STATUS_CPU_PARITY (0x80) /* [7] */
#define MSK_SYS_STATE_RESET_STATUS_SRAM_PARITY (0x1) /* [8] */
#define SFT_SYS_STATE_RESET_STATUS_SRAM_PARITY (8)
#define LSB_SYS_STATE_RESET_STATUS_SRAM_PARITY (8)
#define MSB_SYS_STATE_RESET_STATUS_SRAM_PARITY (8)
#define BIT_SYS_STATE_RESET_STATUS_SRAM_PARITY (0x100)  /* [8] */
#define MSK_SYS_STATE_RESET_STATUS_FLASH_2BIT_ERR (0x1) /* [9] */
#define SFT_SYS_STATE_RESET_STATUS_FLASH_2BIT_ERR (9)
#define LSB_SYS_STATE_RESET_STATUS_FLASH_2BIT_ERR (9)
#define MSB_SYS_STATE_RESET_STATUS_FLASH_2BIT_ERR (9)
#define BIT_SYS_STATE_RESET_STATUS_FLASH_2BIT_ERR (0x200) /* [9] */
#define MSK_SYS_STATE_RESET_STATUS_FLASH_1BIT_ERR (0x1)   /* [10] */
#define SFT_SYS_STATE_RESET_STATUS_FLASH_1BIT_ERR (10)
#define LSB_SYS_STATE_RESET_STATUS_FLASH_1BIT_ERR (10)
#define MSB_SYS_STATE_RESET_STATUS_FLASH_1BIT_ERR (10)
#define BIT_SYS_STATE_RESET_STATUS_FLASH_1BIT_ERR (0x400) /* [10] */
#define MSK_SYS_STATE_RESET_STATUS_SRAM_WR_PROT (0x1)     /* [11] */
#define SFT_SYS_STATE_RESET_STATUS_SRAM_WR_PROT (11)
#define LSB_SYS_STATE_RESET_STATUS_SRAM_WR_PROT (11)
#define MSB_SYS_STATE_RESET_STATUS_SRAM_WR_PROT (11)
#define BIT_SYS_STATE_RESET_STATUS_SRAM_WR_PROT (0x800) /* [11] */
#define MSK_SYS_STATE_RESET_STATUS_STACK_PROT (0x1)     /* [12] */
#define SFT_SYS_STATE_RESET_STATUS_STACK_PROT (12)
#define LSB_SYS_STATE_RESET_STATUS_STACK_PROT (12)
#define MSB_SYS_STATE_RESET_STATUS_STACK_PROT (12)
#define BIT_SYS_STATE_RESET_STATUS_STACK_PROT (0x1000) /* [12] */
#define MSK_SYS_STATE_RESET_STATUS_EXEC_PROT (0x1)     /* [13] */
#define SFT_SYS_STATE_RESET_STATUS_EXEC_PROT (13)
#define LSB_SYS_STATE_RESET_STATUS_EXEC_PROT (13)
#define MSB_SYS_STATE_RESET_STATUS_EXEC_PROT (13)
#define BIT_SYS_STATE_RESET_STATUS_EXEC_PROT (0x2000) /* [13] */

typedef struct
{
  unsigned short por : 1;            /* [0] */
  unsigned short vddio_ok : 1;       /* [1] */
  unsigned short vddc_ok : 1;        /* [2] */
  unsigned short nrsti : 1;          /* [3] */
  unsigned short sys_clk_fail : 1;   /* [4] */
  unsigned short watchdog : 1;       /* [5] */
  unsigned short sw_reset : 1;       /* [6] */
  unsigned short cpu_parity : 1;     /* [7] */
  unsigned short sram_parity : 1;    /* [8] */
  unsigned short flash_2bit_err : 1; /* [9] */
  unsigned short flash_1bit_err : 1; /* [10] */
  unsigned short sram_wr_prot : 1;   /* [11] */
  unsigned short stack_prot : 1;     /* [12] */
  unsigned short exec_prot : 1;      /* [13] */
  unsigned short reserved : 2;
} _PACKED_ sys_state_reset_status_bf;

typedef union {
  unsigned short val;
  sys_state_reset_status_bf bf;
} _PACKED_ sys_state_reset_status_t;

/* SYS_STATE__RESET_STATUS_CLEAR */

#define MSK_SYS_STATE__RESET_STATUS_CLEAR (0x1) /* [0] */

typedef unsigned short sys_state__reset_status_clear_t; /* [0] */

/* SYS_STATE_RESET_ENABLE */

#define MSK_SYS_STATE_RESET_ENABLE_WATCHDOG (0x1) /* [0] */
#define SFT_SYS_STATE_RESET_ENABLE_WATCHDOG (0)
#define LSB_SYS_STATE_RESET_ENABLE_WATCHDOG (0)
#define MSB_SYS_STATE_RESET_ENABLE_WATCHDOG (0)
#define BIT_SYS_STATE_RESET_ENABLE_WATCHDOG (0x1) /* [0] */
#define MSK_SYS_STATE_RESET_ENABLE_SW_RESET (0x1) /* [1] */
#define SFT_SYS_STATE_RESET_ENABLE_SW_RESET (1)
#define LSB_SYS_STATE_RESET_ENABLE_SW_RESET (1)
#define MSB_SYS_STATE_RESET_ENABLE_SW_RESET (1)
#define BIT_SYS_STATE_RESET_ENABLE_SW_RESET (0x2)   /* [1] */
#define MSK_SYS_STATE_RESET_ENABLE_CPU_PARITY (0x1) /* [2] */
#define SFT_SYS_STATE_RESET_ENABLE_CPU_PARITY (2)
#define LSB_SYS_STATE_RESET_ENABLE_CPU_PARITY (2)
#define MSB_SYS_STATE_RESET_ENABLE_CPU_PARITY (2)
#define BIT_SYS_STATE_RESET_ENABLE_CPU_PARITY (0x4)  /* [2] */
#define MSK_SYS_STATE_RESET_ENABLE_SRAM_PARITY (0x1) /* [3] */
#define SFT_SYS_STATE_RESET_ENABLE_SRAM_PARITY (3)
#define LSB_SYS_STATE_RESET_ENABLE_SRAM_PARITY (3)
#define MSB_SYS_STATE_RESET_ENABLE_SRAM_PARITY (3)
#define BIT_SYS_STATE_RESET_ENABLE_SRAM_PARITY (0x8)    /* [3] */
#define MSK_SYS_STATE_RESET_ENABLE_FLASH_2BIT_ERR (0x1) /* [4] */
#define SFT_SYS_STATE_RESET_ENABLE_FLASH_2BIT_ERR (4)
#define LSB_SYS_STATE_RESET_ENABLE_FLASH_2BIT_ERR (4)
#define MSB_SYS_STATE_RESET_ENABLE_FLASH_2BIT_ERR (4)
#define BIT_SYS_STATE_RESET_ENABLE_FLASH_2BIT_ERR (0x10) /* [4] */
#define MSK_SYS_STATE_RESET_ENABLE_FLASH_1BIT_ERR (0x1)  /* [5] */
#define SFT_SYS_STATE_RESET_ENABLE_FLASH_1BIT_ERR (5)
#define LSB_SYS_STATE_RESET_ENABLE_FLASH_1BIT_ERR (5)
#define MSB_SYS_STATE_RESET_ENABLE_FLASH_1BIT_ERR (5)
#define BIT_SYS_STATE_RESET_ENABLE_FLASH_1BIT_ERR (0x20) /* [5] */
#define MSK_SYS_STATE_RESET_ENABLE_SRAM_WR_PROT (0x1)    /* [6] */
#define SFT_SYS_STATE_RESET_ENABLE_SRAM_WR_PROT (6)
#define LSB_SYS_STATE_RESET_ENABLE_SRAM_WR_PROT (6)
#define MSB_SYS_STATE_RESET_ENABLE_SRAM_WR_PROT (6)
#define BIT_SYS_STATE_RESET_ENABLE_SRAM_WR_PROT (0x40) /* [6] */
#define MSK_SYS_STATE_RESET_ENABLE_STACK_PROT (0x1)    /* [7] */
#define SFT_SYS_STATE_RESET_ENABLE_STACK_PROT (7)
#define LSB_SYS_STATE_RESET_ENABLE_STACK_PROT (7)
#define MSB_SYS_STATE_RESET_ENABLE_STACK_PROT (7)
#define BIT_SYS_STATE_RESET_ENABLE_STACK_PROT (0x80) /* [7] */
#define MSK_SYS_STATE_RESET_ENABLE_EXEC_PROT (0x1)   /* [8] */
#define SFT_SYS_STATE_RESET_ENABLE_EXEC_PROT (8)
#define LSB_SYS_STATE_RESET_ENABLE_EXEC_PROT (8)
#define MSB_SYS_STATE_RESET_ENABLE_EXEC_PROT (8)
#define BIT_SYS_STATE_RESET_ENABLE_EXEC_PROT (0x100) /* [8] */

typedef struct
{
  unsigned short watchdog : 1;       /* [0] */
  unsigned short sw_reset : 1;       /* [1] */
  unsigned short cpu_parity : 1;     /* [2] */
  unsigned short sram_parity : 1;    /* [3] */
  unsigned short flash_2bit_err : 1; /* [4] */
  unsigned short flash_1bit_err : 1; /* [5] */
  unsigned short sram_wr_prot : 1;   /* [6] */
  unsigned short stack_prot : 1;     /* [7] */
  unsigned short exec_prot : 1;      /* [8] */
  unsigned short reserved : 7;
} _PACKED_ sys_state_reset_enable_bf;

typedef union {
  unsigned short val;
  sys_state_reset_enable_bf bf;
} _PACKED_ sys_state_reset_enable_t;

/* SYS_STATE_SW_RESET */

#define MSK_SYS_STATE_SW_RESET_POR_FLAG (0x1) /* [0] */
#define SFT_SYS_STATE_SW_RESET_POR_FLAG (0)
#define LSB_SYS_STATE_SW_RESET_POR_FLAG (0)
#define MSB_SYS_STATE_SW_RESET_POR_FLAG (0)
#define BIT_SYS_STATE_SW_RESET_POR_FLAG (0x1) /* [0] */
#define MSK_SYS_STATE_SW_RESET_SW_RESET (0x1) /* [1] */
#define SFT_SYS_STATE_SW_RESET_SW_RESET (1)
#define LSB_SYS_STATE_SW_RESET_SW_RESET (1)
#define MSB_SYS_STATE_SW_RESET_SW_RESET (1)
#define BIT_SYS_STATE_SW_RESET_SW_RESET (0x2) /* [1] */

typedef struct
{
  unsigned short por_flag : 1; /* [0] */
  unsigned short sw_reset : 1; /* [1] */
  unsigned short reserved : 14;
} _PACKED_ sys_state_sw_reset_bf;

typedef union {
  unsigned short val;
  sys_state_sw_reset_bf bf;
} _PACKED_ sys_state_sw_reset_t;

/* SYS_STATE_CALIBRATION_LOCK */

#define MSK_SYS_STATE_CALIBRATION_LOCK (0x1) /* [0] */

typedef unsigned short sys_state_calibration_lock_t; /* [0] */

/* SYS_STATE_CALIBRATION */

#define MSK_SYS_STATE_CALIBRATION_CAL_VREF (0x7) /* [ 2:0] */
#define SFT_SYS_STATE_CALIBRATION_CAL_VREF (0)
#define LSB_SYS_STATE_CALIBRATION_CAL_VREF (0)
#define MSB_SYS_STATE_CALIBRATION_CAL_VREF (2)
#define MSK_SYS_STATE_CALIBRATION_CAL_BGAP (0xf) /* [ 7:4] */
#define SFT_SYS_STATE_CALIBRATION_CAL_BGAP (4)
#define LSB_SYS_STATE_CALIBRATION_CAL_BGAP (4)
#define MSB_SYS_STATE_CALIBRATION_CAL_BGAP (7)
#define MSK_SYS_STATE_CALIBRATION_CAL_SYS_OSC (0xff) /* [15:8] */
#define SFT_SYS_STATE_CALIBRATION_CAL_SYS_OSC (8)
#define LSB_SYS_STATE_CALIBRATION_CAL_SYS_OSC (8)
#define MSB_SYS_STATE_CALIBRATION_CAL_SYS_OSC (15)

typedef struct
{
  unsigned short cal_vref : 3;    /* [ 2:0] */
  unsigned short reserved3 : 1;   /* [3] */
  unsigned short cal_bgap : 4;    /* [ 7:4] */
  unsigned short cal_sys_osc : 8; /* [15:8] */
} _PACKED_ sys_state_calibration_bf;

typedef union {
  unsigned short val;
  sys_state_calibration_bf bf;
} _PACKED_ sys_state_calibration_t;

/* SYS_STATE_IC_VERSION_0 */

#define MSK_SYS_STATE_IC_VERSION_0_LOW_BYTE (0xff) /* [ 7:0] */
#define SFT_SYS_STATE_IC_VERSION_0_LOW_BYTE (0)
#define LSB_SYS_STATE_IC_VERSION_0_LOW_BYTE (0)
#define MSB_SYS_STATE_IC_VERSION_0_LOW_BYTE (7)
#define MSK_SYS_STATE_IC_VERSION_0_HIGH_BYTE (0xff) /* [15:8] */
#define SFT_SYS_STATE_IC_VERSION_0_HIGH_BYTE (8)
#define LSB_SYS_STATE_IC_VERSION_0_HIGH_BYTE (8)
#define MSB_SYS_STATE_IC_VERSION_0_HIGH_BYTE (15)

typedef struct
{
  unsigned short low_byte : 8;  /* [ 7:0] */
  unsigned short high_byte : 8; /* [15:8] */
} _PACKED_ sys_state_ic_version_0_bf;

typedef union {
  unsigned short val;
  sys_state_ic_version_0_bf bf;
} _PACKED_ sys_state_ic_version_0_t;

/* SYS_STATE_IC_VERSION_1 */

#define MSK_SYS_STATE_IC_VERSION_1_LOW_BYTE (0xff) /* [ 7:0] */
#define SFT_SYS_STATE_IC_VERSION_1_LOW_BYTE (0)
#define LSB_SYS_STATE_IC_VERSION_1_LOW_BYTE (0)
#define MSB_SYS_STATE_IC_VERSION_1_LOW_BYTE (7)
#define MSK_SYS_STATE_IC_VERSION_1_HIGH_BYTE (0xff) /* [15:8] */
#define SFT_SYS_STATE_IC_VERSION_1_HIGH_BYTE (8)
#define LSB_SYS_STATE_IC_VERSION_1_HIGH_BYTE (8)
#define MSB_SYS_STATE_IC_VERSION_1_HIGH_BYTE (15)

typedef struct
{
  unsigned short low_byte : 8;  /* [ 7:0] */
  unsigned short high_byte : 8; /* [15:8] */
} _PACKED_ sys_state_ic_version_1_bf;

typedef union {
  unsigned short val;
  sys_state_ic_version_1_bf bf;
} _PACKED_ sys_state_ic_version_1_t;

/* SYS_STATE_IC_VERSION_2 */

#define MSK_SYS_STATE_IC_VERSION_2_LOW_BYTE (0xff) /* [ 7:0] */
#define SFT_SYS_STATE_IC_VERSION_2_LOW_BYTE (0)
#define LSB_SYS_STATE_IC_VERSION_2_LOW_BYTE (0)
#define MSB_SYS_STATE_IC_VERSION_2_LOW_BYTE (7)
#define MSK_SYS_STATE_IC_VERSION_2_HIGH_BYTE (0xff) /* [15:8] */
#define SFT_SYS_STATE_IC_VERSION_2_HIGH_BYTE (8)
#define LSB_SYS_STATE_IC_VERSION_2_HIGH_BYTE (8)
#define MSB_SYS_STATE_IC_VERSION_2_HIGH_BYTE (15)

typedef struct
{
  unsigned short low_byte : 8;  /* [ 7:0] */
  unsigned short high_byte : 8; /* [15:8] */
} _PACKED_ sys_state_ic_version_2_bf;

typedef union {
  unsigned short val;
  sys_state_ic_version_2_bf bf;
} _PACKED_ sys_state_ic_version_2_t;

/* SYS_STATE_IC_VERSION_3 */

#define MSK_SYS_STATE_IC_VERSION_3_LOW_BYTE (0xff) /* [ 7:0] */
#define SFT_SYS_STATE_IC_VERSION_3_LOW_BYTE (0)
#define LSB_SYS_STATE_IC_VERSION_3_LOW_BYTE (0)
#define MSB_SYS_STATE_IC_VERSION_3_LOW_BYTE (7)
#define MSK_SYS_STATE_IC_VERSION_3_HIGH_BYTE (0xff) /* [15:8] */
#define SFT_SYS_STATE_IC_VERSION_3_HIGH_BYTE (8)
#define LSB_SYS_STATE_IC_VERSION_3_HIGH_BYTE (8)
#define MSB_SYS_STATE_IC_VERSION_3_HIGH_BYTE (15)

typedef struct
{
  unsigned short low_byte : 8;  /* [ 7:0] */
  unsigned short high_byte : 8; /* [15:8] */
} _PACKED_ sys_state_ic_version_3_bf;

typedef union {
  unsigned short val;
  sys_state_ic_version_3_bf bf;
} _PACKED_ sys_state_ic_version_3_t;

/* SYS_STATE_CUSTOMER_ID */

#define MSK_SYS_STATE_CUSTOMER_ID (0xff) /* [ 7:0] */

typedef unsigned short sys_state_customer_id_t; /* [ 7:0] */

/* SYS_STATE_DEVICE_ID */

#define MSK_SYS_STATE_DEVICE_ID (0xff) /* [ 7:0] */

typedef unsigned short sys_state_device_id_t; /* [ 7:0] */

/* SYS_STATE_SIGNATURE */

#define MSK_SYS_STATE_SIGNATURE (0xffff) /* [15:0] */

typedef unsigned short sys_state_signature_t; /* [15:0] */

/* SYS_STATE_SYS_CLK_CONFIG */

#define MSK_SYS_STATE_SYS_CLK_CONFIG_SYS_CLK_DELAY (0x1f) /* [ 4:0] */
#define SFT_SYS_STATE_SYS_CLK_CONFIG_SYS_CLK_DELAY (0)
#define LSB_SYS_STATE_SYS_CLK_CONFIG_SYS_CLK_DELAY (0)
#define MSB_SYS_STATE_SYS_CLK_CONFIG_SYS_CLK_DELAY (4)
#define MSK_SYS_STATE_SYS_CLK_CONFIG_ADC_CLK_PHASE (0x1) /* [5] */
#define SFT_SYS_STATE_SYS_CLK_CONFIG_ADC_CLK_PHASE (5)
#define LSB_SYS_STATE_SYS_CLK_CONFIG_ADC_CLK_PHASE (5)
#define MSB_SYS_STATE_SYS_CLK_CONFIG_ADC_CLK_PHASE (5)
#define BIT_SYS_STATE_SYS_CLK_CONFIG_ADC_CLK_PHASE (0x20) /* [5] */

typedef struct
{
  unsigned short sys_clk_delay : 5; /* [ 4:0] */
  unsigned short adc_clk_phase : 1; /* [5] */
  unsigned short reserved : 10;
} _PACKED_ sys_state_sys_clk_config_bf;

typedef union {
  unsigned short val;
  sys_state_sys_clk_config_bf bf;
} _PACKED_ sys_state_sys_clk_config_t;

/* SYS_STATE_ADC_CALIBRATION */

#define MSK_SYS_STATE_ADC_CALIBRATION (0xf) /* [ 3:0] */

typedef unsigned short sys_state_adc_calibration_t; /* [ 3:0] */

/* SYS_STATE_ENABLE_JTAG */

#define MSK_SYS_STATE_ENABLE_JTAG (0x1) /* [0] */

typedef unsigned short sys_state_enable_jtag_t; /* [0] */

/* SYS_STATE_IRQ_STATUS */

#define MSK_SYS_STATE_IRQ_STATUS_WATCHDOG (0x1) /* [0] */
#define SFT_SYS_STATE_IRQ_STATUS_WATCHDOG (0)
#define LSB_SYS_STATE_IRQ_STATUS_WATCHDOG (0)
#define MSB_SYS_STATE_IRQ_STATUS_WATCHDOG (0)
#define BIT_SYS_STATE_IRQ_STATUS_WATCHDOG (0x1) /* [0] */
#define MSK_SYS_STATE_IRQ_STATUS_SW_RESET (0x1) /* [1] */
#define SFT_SYS_STATE_IRQ_STATUS_SW_RESET (1)
#define LSB_SYS_STATE_IRQ_STATUS_SW_RESET (1)
#define MSB_SYS_STATE_IRQ_STATUS_SW_RESET (1)
#define BIT_SYS_STATE_IRQ_STATUS_SW_RESET (0x2)   /* [1] */
#define MSK_SYS_STATE_IRQ_STATUS_CPU_PARITY (0x1) /* [2] */
#define SFT_SYS_STATE_IRQ_STATUS_CPU_PARITY (2)
#define LSB_SYS_STATE_IRQ_STATUS_CPU_PARITY (2)
#define MSB_SYS_STATE_IRQ_STATUS_CPU_PARITY (2)
#define BIT_SYS_STATE_IRQ_STATUS_CPU_PARITY (0x4)  /* [2] */
#define MSK_SYS_STATE_IRQ_STATUS_SRAM_PARITY (0x1) /* [3] */
#define SFT_SYS_STATE_IRQ_STATUS_SRAM_PARITY (3)
#define LSB_SYS_STATE_IRQ_STATUS_SRAM_PARITY (3)
#define MSB_SYS_STATE_IRQ_STATUS_SRAM_PARITY (3)
#define BIT_SYS_STATE_IRQ_STATUS_SRAM_PARITY (0x8)    /* [3] */
#define MSK_SYS_STATE_IRQ_STATUS_FLASH_2BIT_ERR (0x1) /* [4] */
#define SFT_SYS_STATE_IRQ_STATUS_FLASH_2BIT_ERR (4)
#define LSB_SYS_STATE_IRQ_STATUS_FLASH_2BIT_ERR (4)
#define MSB_SYS_STATE_IRQ_STATUS_FLASH_2BIT_ERR (4)
#define BIT_SYS_STATE_IRQ_STATUS_FLASH_2BIT_ERR (0x10) /* [4] */
#define MSK_SYS_STATE_IRQ_STATUS_FLASH_1BIT_ERR (0x1)  /* [5] */
#define SFT_SYS_STATE_IRQ_STATUS_FLASH_1BIT_ERR (5)
#define LSB_SYS_STATE_IRQ_STATUS_FLASH_1BIT_ERR (5)
#define MSB_SYS_STATE_IRQ_STATUS_FLASH_1BIT_ERR (5)
#define BIT_SYS_STATE_IRQ_STATUS_FLASH_1BIT_ERR (0x20) /* [5] */
#define MSK_SYS_STATE_IRQ_STATUS_SRAM_WR_PROT (0x1)    /* [6] */
#define SFT_SYS_STATE_IRQ_STATUS_SRAM_WR_PROT (6)
#define LSB_SYS_STATE_IRQ_STATUS_SRAM_WR_PROT (6)
#define MSB_SYS_STATE_IRQ_STATUS_SRAM_WR_PROT (6)
#define BIT_SYS_STATE_IRQ_STATUS_SRAM_WR_PROT (0x40) /* [6] */
#define MSK_SYS_STATE_IRQ_STATUS_STACK_PROT (0x1)    /* [7] */
#define SFT_SYS_STATE_IRQ_STATUS_STACK_PROT (7)
#define LSB_SYS_STATE_IRQ_STATUS_STACK_PROT (7)
#define MSB_SYS_STATE_IRQ_STATUS_STACK_PROT (7)
#define BIT_SYS_STATE_IRQ_STATUS_STACK_PROT (0x80) /* [7] */
#define MSK_SYS_STATE_IRQ_STATUS_EXEC_PROT (0x1)   /* [8] */
#define SFT_SYS_STATE_IRQ_STATUS_EXEC_PROT (8)
#define LSB_SYS_STATE_IRQ_STATUS_EXEC_PROT (8)
#define MSB_SYS_STATE_IRQ_STATUS_EXEC_PROT (8)
#define BIT_SYS_STATE_IRQ_STATUS_EXEC_PROT (0x100) /* [8] */

typedef struct
{
  unsigned short watchdog : 1;       /* [0] */
  unsigned short sw_reset : 1;       /* [1] */
  unsigned short cpu_parity : 1;     /* [2] */
  unsigned short sram_parity : 1;    /* [3] */
  unsigned short flash_2bit_err : 1; /* [4] */
  unsigned short flash_1bit_err : 1; /* [5] */
  unsigned short sram_wr_prot : 1;   /* [6] */
  unsigned short stack_prot : 1;     /* [7] */
  unsigned short exec_prot : 1;      /* [8] */
  unsigned short reserved : 7;
} _PACKED_ sys_state_irq_status_bf;

typedef union {
  unsigned short val;
  sys_state_irq_status_bf bf;
} _PACKED_ sys_state_irq_status_t;

/* SYS_STATE_IRQ_MASK */

#define MSK_SYS_STATE_IRQ_MASK (0x1ff) /* [ 8:0] */

typedef unsigned short sys_state_irq_mask_t; /* [ 8:0] */

/* SYS_STATE_IRQ_VENABLE */

#define MSK_SYS_STATE_IRQ_VENABLE (0xf) /* [ 3:0] */

typedef unsigned short sys_state_irq_venable_t; /* [ 3:0] */

/* SYS_STATE_IRQ_VDISABLE */

#define MSK_SYS_STATE_IRQ_VDISABLE (0xf) /* [ 3:0] */

typedef unsigned short sys_state_irq_vdisable_t; /* [ 3:0] */

/* SYS_STATE_IRQ_VMAX */

#define MSK_SYS_STATE_IRQ_VMAX (0xf) /* [ 3:0] */

typedef unsigned short sys_state_irq_vmax_t; /* [ 3:0] */

/* SYS_STATE_IRQ_VNO */

#define MSK_SYS_STATE_IRQ_VNO (0xf) /* [ 3:0] */

typedef unsigned short sys_state_irq_vno_t; /* [ 3:0] */

/* SYS_STATE */

typedef struct
{
  sys_state_module_enable_t module_enable;            /* 0 */
  sys_state_control_t control;                        /* 2 */
  sys_state_reset_status_t reset_status;              /* 4 */
  sys_state__reset_status_clear_t reset_status_clear; /* 6 */
  sys_state_reset_enable_t reset_enable;              /* 8 */
  sys_state_sw_reset_t sw_reset;                      /* 10 */
  sys_state_calibration_lock_t calibration_lock;      /* 12 */
  sys_state_calibration_t calibration;                /* 14 */
  sys_state_ic_version_0_t ic_version_0;              /* 16 */
  sys_state_ic_version_1_t ic_version_1;              /* 18 */
  sys_state_ic_version_2_t ic_version_2;              /* 20 */
  sys_state_ic_version_3_t ic_version_3;              /* 22 */
  sys_state_customer_id_t customer_id;                /* 24 */
  sys_state_device_id_t device_id;                    /* 26 */
  unsigned short reserved0[2];
  sys_state_signature_t signature_0;           /* 32 */
  sys_state_signature_t signature_1;           /* 34 */
  sys_state_signature_t signature_2;           /* 36 */
  sys_state_signature_t signature_3;           /* 38 */
  sys_state_sys_clk_config_t sys_clk_config;   /* 40 */
  sys_state_adc_calibration_t adc_calibration; /* 42 */
  sys_state_enable_jtag_t enable_jtag;         /* 44 */
  unsigned short reserved1[1];
  sys_state_irq_status_t irq_status; /* 48 */
  unsigned short reserved2[1];
  sys_state_irq_mask_t irq_mask; /* 52 */
  unsigned short reserved3[1];
  sys_state_irq_venable_t irq_venable;   /* 56 */
  sys_state_irq_vdisable_t irq_vdisable; /* 58 */
  sys_state_irq_vmax_t irq_vmax;         /* 60 */
  sys_state_irq_vno_t irq_vno;           /* 62 */
} _PACKED_ sys_state_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_SYS_STATE 0x0180U ... System State Module

#define ADDR_SYS_STATE_MODULE_ENABLE (0x00U)
#define A_SYS_STATE_MODULE_ENABLE(ba) ((ba) + ADDR_SYS_STATE_MODULE_ENABLE)
#define R_SYS_STATE_MODULE_ENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_MODULE_ENABLE(ba)))
#define RES_SYS_STATE_MODULE_ENABLE (0x0U)
#define MSB_SYS_STATE_MODULE_ENABLE 13
#define LSB_SYS_STATE_MODULE_ENABLE 0
#define AADDR_SYS_STATE_MODULE_ENABLE (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_MODULE_ENABLE)
#define REG_SYS_STATE_MODULE_ENABLE (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_MODULE_ENABLE))

#define ADDR_SYS_STATE_CONTROL (0x02U)
#define A_SYS_STATE_CONTROL(ba) ((ba) + ADDR_SYS_STATE_CONTROL)
#define R_SYS_STATE_CONTROL(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_CONTROL(ba)))
#define RES_SYS_STATE_CONTROL (0x1b0U)
#define MSB_SYS_STATE_CONTROL 15
#define LSB_SYS_STATE_CONTROL 0
#define AADDR_SYS_STATE_CONTROL (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_CONTROL)
#define REG_SYS_STATE_CONTROL (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_CONTROL))

#define ADDR_SYS_STATE_RESET_STATUS (0x04U)
#define A_SYS_STATE_RESET_STATUS(ba) ((ba) + ADDR_SYS_STATE_RESET_STATUS)
#define R_SYS_STATE_RESET_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_RESET_STATUS(ba)))
#define RES_SYS_STATE_RESET_STATUS (0x1U)
#define MSB_SYS_STATE_RESET_STATUS 13
#define LSB_SYS_STATE_RESET_STATUS 0
#define AADDR_SYS_STATE_RESET_STATUS (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_RESET_STATUS)
#define REG_SYS_STATE_RESET_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_RESET_STATUS))

#define ADDR_SYS_STATE_RESET_STATUS_CLEAR (0x06U)
#define A_SYS_STATE_RESET_STATUS_CLEAR(ba) ((ba) + ADDR_SYS_STATE_RESET_STATUS_CLEAR)
#define R_SYS_STATE_RESET_STATUS_CLEAR(ba)                                                                             \
  (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_RESET_STATUS_CLEAR(ba)))
#define RES_SYS_STATE_RESET_STATUS_CLEAR (0x0U)
#define MSB_SYS_STATE_RESET_STATUS_CLEAR 0
#define LSB_SYS_STATE_RESET_STATUS_CLEAR 0
#define AADDR_SYS_STATE_RESET_STATUS_CLEAR (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_RESET_STATUS_CLEAR)
#define REG_SYS_STATE_RESET_STATUS_CLEAR                                                                               \
  (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_RESET_STATUS_CLEAR))

#define ADDR_SYS_STATE_RESET_ENABLE (0x08U)
#define A_SYS_STATE_RESET_ENABLE(ba) ((ba) + ADDR_SYS_STATE_RESET_ENABLE)
#define R_SYS_STATE_RESET_ENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_RESET_ENABLE(ba)))
#define RES_SYS_STATE_RESET_ENABLE (0x0U)
#define MSB_SYS_STATE_RESET_ENABLE 8
#define LSB_SYS_STATE_RESET_ENABLE 0
#define AADDR_SYS_STATE_RESET_ENABLE (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_RESET_ENABLE)
#define REG_SYS_STATE_RESET_ENABLE (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_RESET_ENABLE))

#define ADDR_SYS_STATE_SW_RESET (0x0AU)
#define A_SYS_STATE_SW_RESET(ba) ((ba) + ADDR_SYS_STATE_SW_RESET)
#define R_SYS_STATE_SW_RESET(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_SW_RESET(ba)))
#define RES_SYS_STATE_SW_RESET (0x1U)
#define MSB_SYS_STATE_SW_RESET 1
#define LSB_SYS_STATE_SW_RESET 0
#define AADDR_SYS_STATE_SW_RESET (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_SW_RESET)
#define REG_SYS_STATE_SW_RESET (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_SW_RESET))

#define ADDR_SYS_STATE_CALIBRATION_LOCK (0x0CU)
#define A_SYS_STATE_CALIBRATION_LOCK(ba) ((ba) + ADDR_SYS_STATE_CALIBRATION_LOCK)
#define R_SYS_STATE_CALIBRATION_LOCK(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_CALIBRATION_LOCK(ba)))
#define RES_SYS_STATE_CALIBRATION_LOCK (0x0U)
#define MSB_SYS_STATE_CALIBRATION_LOCK 0
#define LSB_SYS_STATE_CALIBRATION_LOCK 0
#define AADDR_SYS_STATE_CALIBRATION_LOCK (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_CALIBRATION_LOCK)
#define REG_SYS_STATE_CALIBRATION_LOCK (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_CALIBRATION_LOCK))

#define ADDR_SYS_STATE_CALIBRATION (0x0EU)
#define A_SYS_STATE_CALIBRATION(ba) ((ba) + ADDR_SYS_STATE_CALIBRATION)
#define R_SYS_STATE_CALIBRATION(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_CALIBRATION(ba)))
#define RES_SYS_STATE_CALIBRATION (0x84U)
#define MSB_SYS_STATE_CALIBRATION 15
#define LSB_SYS_STATE_CALIBRATION 0
#define AADDR_SYS_STATE_CALIBRATION (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_CALIBRATION)
#define REG_SYS_STATE_CALIBRATION (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_CALIBRATION))

#define ADDR_SYS_STATE_IC_VERSION_0 (0x10U)
#define A_SYS_STATE_IC_VERSION_0(ba) ((ba) + ADDR_SYS_STATE_IC_VERSION_0)
#define R_SYS_STATE_IC_VERSION_0(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_IC_VERSION_0(ba)))
#define RES_SYS_STATE_IC_VERSION_0 (0x354dU)
#define MSB_SYS_STATE_IC_VERSION_0 15
#define LSB_SYS_STATE_IC_VERSION_0 0
#define AADDR_SYS_STATE_IC_VERSION_0 (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_IC_VERSION_0)
#define REG_SYS_STATE_IC_VERSION_0 (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_IC_VERSION_0))

#define ADDR_SYS_STATE_IC_VERSION_1 (0x12U)
#define A_SYS_STATE_IC_VERSION_1(ba) ((ba) + ADDR_SYS_STATE_IC_VERSION_1)
#define R_SYS_STATE_IC_VERSION_1(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_IC_VERSION_1(ba)))
#define RES_SYS_STATE_IC_VERSION_1 (0x3332U)
#define MSB_SYS_STATE_IC_VERSION_1 15
#define LSB_SYS_STATE_IC_VERSION_1 0
#define AADDR_SYS_STATE_IC_VERSION_1 (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_IC_VERSION_1)
#define REG_SYS_STATE_IC_VERSION_1 (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_IC_VERSION_1))

#define ADDR_SYS_STATE_IC_VERSION_2 (0x14U)
#define A_SYS_STATE_IC_VERSION_2(ba) ((ba) + ADDR_SYS_STATE_IC_VERSION_2)
#define R_SYS_STATE_IC_VERSION_2(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_IC_VERSION_2(ba)))
#define RES_SYS_STATE_IC_VERSION_2 (0x3939U)
#define MSB_SYS_STATE_IC_VERSION_2 15
#define LSB_SYS_STATE_IC_VERSION_2 0
#define AADDR_SYS_STATE_IC_VERSION_2 (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_IC_VERSION_2)
#define REG_SYS_STATE_IC_VERSION_2 (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_IC_VERSION_2))

#define ADDR_SYS_STATE_IC_VERSION_3 (0x16U)
#define A_SYS_STATE_IC_VERSION_3(ba) ((ba) + ADDR_SYS_STATE_IC_VERSION_3)
#define R_SYS_STATE_IC_VERSION_3(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_IC_VERSION_3(ba)))
#define RES_SYS_STATE_IC_VERSION_3 (0x42U)
#define MSB_SYS_STATE_IC_VERSION_3 15
#define LSB_SYS_STATE_IC_VERSION_3 0
#define AADDR_SYS_STATE_IC_VERSION_3 (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_IC_VERSION_3)
#define REG_SYS_STATE_IC_VERSION_3 (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_IC_VERSION_3))

#define ADDR_SYS_STATE_CUSTOMER_ID (0x18U)
#define A_SYS_STATE_CUSTOMER_ID(ba) ((ba) + ADDR_SYS_STATE_CUSTOMER_ID)
#define R_SYS_STATE_CUSTOMER_ID(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_CUSTOMER_ID(ba)))
#define RES_SYS_STATE_CUSTOMER_ID (0xffU)
#define MSB_SYS_STATE_CUSTOMER_ID 7
#define LSB_SYS_STATE_CUSTOMER_ID 0
#define AADDR_SYS_STATE_CUSTOMER_ID (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_CUSTOMER_ID)
#define REG_SYS_STATE_CUSTOMER_ID (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_CUSTOMER_ID))

#define ADDR_SYS_STATE_DEVICE_ID (0x1AU)
#define A_SYS_STATE_DEVICE_ID(ba) ((ba) + ADDR_SYS_STATE_DEVICE_ID)
#define R_SYS_STATE_DEVICE_ID(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_DEVICE_ID(ba)))
#define RES_SYS_STATE_DEVICE_ID (0x0U)
#define MSB_SYS_STATE_DEVICE_ID 7
#define LSB_SYS_STATE_DEVICE_ID 0
#define AADDR_SYS_STATE_DEVICE_ID (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_DEVICE_ID)
#define REG_SYS_STATE_DEVICE_ID (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_DEVICE_ID))

#define ADDR_SYS_STATE_SIGNATURE_0 (0x20U)
#define A_SYS_STATE_SIGNATURE_0(ba) ((ba) + ADDR_SYS_STATE_SIGNATURE_0)
#define R_SYS_STATE_SIGNATURE_0(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_SIGNATURE_0(ba)))
#define RES_SYS_STATE_SIGNATURE_0 (0x0U)
#define MSB_SYS_STATE_SIGNATURE_0 15
#define LSB_SYS_STATE_SIGNATURE_0 0
#define AADDR_SYS_STATE_SIGNATURE_0 (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_SIGNATURE_0)
#define REG_SYS_STATE_SIGNATURE_0 (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_SIGNATURE_0))

#define ADDR_SYS_STATE_SIGNATURE_1 (0x22U)
#define A_SYS_STATE_SIGNATURE_1(ba) ((ba) + ADDR_SYS_STATE_SIGNATURE_1)
#define R_SYS_STATE_SIGNATURE_1(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_SIGNATURE_1(ba)))
#define RES_SYS_STATE_SIGNATURE_1 (0x0U)
#define MSB_SYS_STATE_SIGNATURE_1 15
#define LSB_SYS_STATE_SIGNATURE_1 0
#define AADDR_SYS_STATE_SIGNATURE_1 (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_SIGNATURE_1)
#define REG_SYS_STATE_SIGNATURE_1 (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_SIGNATURE_1))

#define ADDR_SYS_STATE_SIGNATURE_2 (0x24U)
#define A_SYS_STATE_SIGNATURE_2(ba) ((ba) + ADDR_SYS_STATE_SIGNATURE_2)
#define R_SYS_STATE_SIGNATURE_2(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_SIGNATURE_2(ba)))
#define RES_SYS_STATE_SIGNATURE_2 (0x0U)
#define MSB_SYS_STATE_SIGNATURE_2 15
#define LSB_SYS_STATE_SIGNATURE_2 0
#define AADDR_SYS_STATE_SIGNATURE_2 (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_SIGNATURE_2)
#define REG_SYS_STATE_SIGNATURE_2 (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_SIGNATURE_2))

#define ADDR_SYS_STATE_SIGNATURE_3 (0x26U)
#define A_SYS_STATE_SIGNATURE_3(ba) ((ba) + ADDR_SYS_STATE_SIGNATURE_3)
#define R_SYS_STATE_SIGNATURE_3(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_SIGNATURE_3(ba)))
#define RES_SYS_STATE_SIGNATURE_3 (0x0U)
#define MSB_SYS_STATE_SIGNATURE_3 15
#define LSB_SYS_STATE_SIGNATURE_3 0
#define AADDR_SYS_STATE_SIGNATURE_3 (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_SIGNATURE_3)
#define REG_SYS_STATE_SIGNATURE_3 (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_SIGNATURE_3))

#define ADDR_SYS_STATE_SYS_CLK_CONFIG (0x28U)
#define A_SYS_STATE_SYS_CLK_CONFIG(ba) ((ba) + ADDR_SYS_STATE_SYS_CLK_CONFIG)
#define R_SYS_STATE_SYS_CLK_CONFIG(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_SYS_CLK_CONFIG(ba)))
#define RES_SYS_STATE_SYS_CLK_CONFIG (0x0U)
#define MSB_SYS_STATE_SYS_CLK_CONFIG 5
#define LSB_SYS_STATE_SYS_CLK_CONFIG 0
#define AADDR_SYS_STATE_SYS_CLK_CONFIG (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_SYS_CLK_CONFIG)
#define REG_SYS_STATE_SYS_CLK_CONFIG (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_SYS_CLK_CONFIG))

#define ADDR_SYS_STATE_ADC_CALIBRATION (0x2AU)
#define A_SYS_STATE_ADC_CALIBRATION(ba) ((ba) + ADDR_SYS_STATE_ADC_CALIBRATION)
#define R_SYS_STATE_ADC_CALIBRATION(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_ADC_CALIBRATION(ba)))
#define RES_SYS_STATE_ADC_CALIBRATION (0x0U)
#define MSB_SYS_STATE_ADC_CALIBRATION 3
#define LSB_SYS_STATE_ADC_CALIBRATION 0
#define AADDR_SYS_STATE_ADC_CALIBRATION (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_ADC_CALIBRATION)
#define REG_SYS_STATE_ADC_CALIBRATION (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_ADC_CALIBRATION))

#define ADDR_SYS_STATE_ENABLE_JTAG (0x2CU)
#define A_SYS_STATE_ENABLE_JTAG(ba) ((ba) + ADDR_SYS_STATE_ENABLE_JTAG)
#define R_SYS_STATE_ENABLE_JTAG(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_ENABLE_JTAG(ba)))
#define RES_SYS_STATE_ENABLE_JTAG (0x0U)
#define MSB_SYS_STATE_ENABLE_JTAG 0
#define LSB_SYS_STATE_ENABLE_JTAG 0
#define AADDR_SYS_STATE_ENABLE_JTAG (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_ENABLE_JTAG)
#define REG_SYS_STATE_ENABLE_JTAG (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_ENABLE_JTAG))

#define ADDR_SYS_STATE_IRQ_STATUS (0x30U)
#define A_SYS_STATE_IRQ_STATUS(ba) ((ba) + ADDR_SYS_STATE_IRQ_STATUS)
#define R_SYS_STATE_IRQ_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_IRQ_STATUS(ba)))
#define RES_SYS_STATE_IRQ_STATUS (0x0U)
#define MSB_SYS_STATE_IRQ_STATUS 8
#define LSB_SYS_STATE_IRQ_STATUS 0
#define AADDR_SYS_STATE_IRQ_STATUS (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_IRQ_STATUS)
#define REG_SYS_STATE_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_IRQ_STATUS))

#define ADDR_SYS_STATE_IRQ_MASK (0x34U)
#define A_SYS_STATE_IRQ_MASK(ba) ((ba) + ADDR_SYS_STATE_IRQ_MASK)
#define R_SYS_STATE_IRQ_MASK(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_IRQ_MASK(ba)))
#define RES_SYS_STATE_IRQ_MASK (0x0U)
#define MSB_SYS_STATE_IRQ_MASK 8
#define LSB_SYS_STATE_IRQ_MASK 0
#define AADDR_SYS_STATE_IRQ_MASK (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_IRQ_MASK)
#define REG_SYS_STATE_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_IRQ_MASK))

#define ADDR_SYS_STATE_IRQ_VENABLE (0x38U)
#define A_SYS_STATE_IRQ_VENABLE(ba) ((ba) + ADDR_SYS_STATE_IRQ_VENABLE)
#define R_SYS_STATE_IRQ_VENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_IRQ_VENABLE(ba)))
#define RES_SYS_STATE_IRQ_VENABLE (0x0U)
#define MSB_SYS_STATE_IRQ_VENABLE 3
#define LSB_SYS_STATE_IRQ_VENABLE 0
#define AADDR_SYS_STATE_IRQ_VENABLE (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_IRQ_VENABLE)
#define REG_SYS_STATE_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_IRQ_VENABLE))

#define ADDR_SYS_STATE_IRQ_VDISABLE (0x3AU)
#define A_SYS_STATE_IRQ_VDISABLE(ba) ((ba) + ADDR_SYS_STATE_IRQ_VDISABLE)
#define R_SYS_STATE_IRQ_VDISABLE(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_IRQ_VDISABLE(ba)))
#define RES_SYS_STATE_IRQ_VDISABLE (0x0U)
#define MSB_SYS_STATE_IRQ_VDISABLE 3
#define LSB_SYS_STATE_IRQ_VDISABLE 0
#define AADDR_SYS_STATE_IRQ_VDISABLE (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_IRQ_VDISABLE)
#define REG_SYS_STATE_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_IRQ_VDISABLE))

#define ADDR_SYS_STATE_IRQ_VMAX (0x3CU)
#define A_SYS_STATE_IRQ_VMAX(ba) ((ba) + ADDR_SYS_STATE_IRQ_VMAX)
#define R_SYS_STATE_IRQ_VMAX(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_IRQ_VMAX(ba)))
#define RES_SYS_STATE_IRQ_VMAX (0x9U)
#define MSB_SYS_STATE_IRQ_VMAX 3
#define LSB_SYS_STATE_IRQ_VMAX 0
#define AADDR_SYS_STATE_IRQ_VMAX (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_IRQ_VMAX)
#define REG_SYS_STATE_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_IRQ_VMAX))

#define ADDR_SYS_STATE_IRQ_VNO (0x3EU)
#define A_SYS_STATE_IRQ_VNO(ba) ((ba) + ADDR_SYS_STATE_IRQ_VNO)
#define R_SYS_STATE_IRQ_VNO(ba) (*(volatile unsigned short *)((unsigned int)A_SYS_STATE_IRQ_VNO(ba)))
#define RES_SYS_STATE_IRQ_VNO (0x9U)
#define MSB_SYS_STATE_IRQ_VNO 3
#define LSB_SYS_STATE_IRQ_VNO 0
#define AADDR_SYS_STATE_IRQ_VNO (BASE_ADDR_SYS_STATE + ADDR_SYS_STATE_IRQ_VNO)
#define REG_SYS_STATE_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_SYS_STATE_IRQ_VNO))

#endif
