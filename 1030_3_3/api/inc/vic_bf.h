#ifndef __VIC_BF_H__
#define __VIC_BF_H__

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

#ifndef BASE_ADDR_VIC
#define BASE_ADDR_VIC 0x0040U
#endif

#define NUMBER_VIC 1

typedef enum
{
  VIC = (int)BASE_ADDR_VIC
} vic_num_t;

// Register bit field definitions

/* VIC_TABLE_BASE */

#define MSK_VIC_TABLE_BASE (0xffff) /* [15:0] */

typedef unsigned short vic_table_base_t; /* [15:0] */

/* VIC_TABLE_TYPE */

#define MSK_VIC_TABLE_TYPE (0x1) /* [0] */

typedef unsigned short vic_table_type_t; /* [0] */

/* VIC_MAIN_ENABLE */

#define MSK_VIC_MAIN_ENABLE (0x1) /* [0] */

typedef unsigned short vic_main_enable_t; /* [0] */

/* VIC_IRQ_STATUS0 */

#define MSK_VIC_IRQ_STATUS0_MEM_PROT (0x1) /* [0] */
#define SFT_VIC_IRQ_STATUS0_MEM_PROT (0)
#define LSB_VIC_IRQ_STATUS0_MEM_PROT (0)
#define MSB_VIC_IRQ_STATUS0_MEM_PROT (0)
#define BIT_VIC_IRQ_STATUS0_MEM_PROT (0x1)  /* [0] */
#define MSK_VIC_IRQ_STATUS0_SYS_STATE (0x1) /* [1] */
#define SFT_VIC_IRQ_STATUS0_SYS_STATE (1)
#define LSB_VIC_IRQ_STATUS0_SYS_STATE (1)
#define MSB_VIC_IRQ_STATUS0_SYS_STATE (1)
#define BIT_VIC_IRQ_STATUS0_SYS_STATE (0x2) /* [1] */
#define MSK_VIC_IRQ_STATUS0_WDOG (0x1)      /* [2] */
#define SFT_VIC_IRQ_STATUS0_WDOG (2)
#define LSB_VIC_IRQ_STATUS0_WDOG (2)
#define MSB_VIC_IRQ_STATUS0_WDOG (2)
#define BIT_VIC_IRQ_STATUS0_WDOG (0x4)    /* [2] */
#define MSK_VIC_IRQ_STATUS0_DIVIDER (0x1) /* [3] */
#define SFT_VIC_IRQ_STATUS0_DIVIDER (3)
#define LSB_VIC_IRQ_STATUS0_DIVIDER (3)
#define MSB_VIC_IRQ_STATUS0_DIVIDER (3)
#define BIT_VIC_IRQ_STATUS0_DIVIDER (0x8)  /* [3] */
#define MSK_VIC_IRQ_STATUS0_ADC_CTRL (0x1) /* [4] */
#define SFT_VIC_IRQ_STATUS0_ADC_CTRL (4)
#define LSB_VIC_IRQ_STATUS0_ADC_CTRL (4)
#define MSB_VIC_IRQ_STATUS0_ADC_CTRL (4)
#define BIT_VIC_IRQ_STATUS0_ADC_CTRL (0x10) /* [4] */
#define MSK_VIC_IRQ_STATUS0_PWMN (0x1)      /* [5] */
#define SFT_VIC_IRQ_STATUS0_PWMN (5)
#define LSB_VIC_IRQ_STATUS0_PWMN (5)
#define MSB_VIC_IRQ_STATUS0_PWMN (5)
#define BIT_VIC_IRQ_STATUS0_PWMN (0x20)   /* [5] */
#define MSK_VIC_IRQ_STATUS0_PRE_PWM (0x1) /* [6] */
#define SFT_VIC_IRQ_STATUS0_PRE_PWM (6)
#define LSB_VIC_IRQ_STATUS0_PRE_PWM (6)
#define MSB_VIC_IRQ_STATUS0_PRE_PWM (6)
#define BIT_VIC_IRQ_STATUS0_PRE_PWM (0x40) /* [6] */
#define MSK_VIC_IRQ_STATUS0_SPI_0 (0x1)    /* [7] */
#define SFT_VIC_IRQ_STATUS0_SPI_0 (7)
#define LSB_VIC_IRQ_STATUS0_SPI_0 (7)
#define MSB_VIC_IRQ_STATUS0_SPI_0 (7)
#define BIT_VIC_IRQ_STATUS0_SPI_0 (0x80) /* [7] */
#define MSK_VIC_IRQ_STATUS0_SPI_1 (0x1)  /* [8] */
#define SFT_VIC_IRQ_STATUS0_SPI_1 (8)
#define LSB_VIC_IRQ_STATUS0_SPI_1 (8)
#define MSB_VIC_IRQ_STATUS0_SPI_1 (8)
#define BIT_VIC_IRQ_STATUS0_SPI_1 (0x100) /* [8] */
#define MSK_VIC_IRQ_STATUS0_SCI (0x1)     /* [9] */
#define SFT_VIC_IRQ_STATUS0_SCI (9)
#define LSB_VIC_IRQ_STATUS0_SCI (9)
#define MSB_VIC_IRQ_STATUS0_SCI (9)
#define BIT_VIC_IRQ_STATUS0_SCI (0x200)     /* [9] */
#define MSK_VIC_IRQ_STATUS0_CCTIMER_0 (0x1) /* [10] */
#define SFT_VIC_IRQ_STATUS0_CCTIMER_0 (10)
#define LSB_VIC_IRQ_STATUS0_CCTIMER_0 (10)
#define MSB_VIC_IRQ_STATUS0_CCTIMER_0 (10)
#define BIT_VIC_IRQ_STATUS0_CCTIMER_0 (0x400) /* [10] */
#define MSK_VIC_IRQ_STATUS0_CCTIMER_1 (0x1)   /* [11] */
#define SFT_VIC_IRQ_STATUS0_CCTIMER_1 (11)
#define LSB_VIC_IRQ_STATUS0_CCTIMER_1 (11)
#define MSB_VIC_IRQ_STATUS0_CCTIMER_1 (11)
#define BIT_VIC_IRQ_STATUS0_CCTIMER_1 (0x800) /* [11] */
#define MSK_VIC_IRQ_STATUS0_CCTIMER_2 (0x1)   /* [12] */
#define SFT_VIC_IRQ_STATUS0_CCTIMER_2 (12)
#define LSB_VIC_IRQ_STATUS0_CCTIMER_2 (12)
#define MSB_VIC_IRQ_STATUS0_CCTIMER_2 (12)
#define BIT_VIC_IRQ_STATUS0_CCTIMER_2 (0x1000) /* [12] */
#define MSK_VIC_IRQ_STATUS0_CCTIMER_3 (0x1)    /* [13] */
#define SFT_VIC_IRQ_STATUS0_CCTIMER_3 (13)
#define LSB_VIC_IRQ_STATUS0_CCTIMER_3 (13)
#define MSB_VIC_IRQ_STATUS0_CCTIMER_3 (13)
#define BIT_VIC_IRQ_STATUS0_CCTIMER_3 (0x2000) /* [13] */
#define MSK_VIC_IRQ_STATUS0_GPIO_A (0x1)       /* [14] */
#define SFT_VIC_IRQ_STATUS0_GPIO_A (14)
#define LSB_VIC_IRQ_STATUS0_GPIO_A (14)
#define MSB_VIC_IRQ_STATUS0_GPIO_A (14)
#define BIT_VIC_IRQ_STATUS0_GPIO_A (0x4000) /* [14] */
#define MSK_VIC_IRQ_STATUS0_GPIO_B (0x1)    /* [15] */
#define SFT_VIC_IRQ_STATUS0_GPIO_B (15)
#define LSB_VIC_IRQ_STATUS0_GPIO_B (15)
#define MSB_VIC_IRQ_STATUS0_GPIO_B (15)
#define BIT_VIC_IRQ_STATUS0_GPIO_B (0x8000) /* [15] */

typedef struct
{
  unsigned short mem_prot : 1;  /* [0] */
  unsigned short sys_state : 1; /* [1] */
  unsigned short wdog : 1;      /* [2] */
  unsigned short divider : 1;   /* [3] */
  unsigned short adc_ctrl : 1;  /* [4] */
  unsigned short pwmn : 1;      /* [5] */
  unsigned short pre_pwm : 1;   /* [6] */
  unsigned short spi_0 : 1;     /* [7] */
  unsigned short spi_1 : 1;     /* [8] */
  unsigned short sci : 1;       /* [9] */
  unsigned short cctimer_0 : 1; /* [10] */
  unsigned short cctimer_1 : 1; /* [11] */
  unsigned short cctimer_2 : 1; /* [12] */
  unsigned short cctimer_3 : 1; /* [13] */
  unsigned short gpio_a : 1;    /* [14] */
  unsigned short gpio_b : 1;    /* [15] */
} _PACKED_ vic_irq_status0_bf;

typedef union {
  unsigned short val;
  vic_irq_status0_bf bf;
} _PACKED_ vic_irq_status0_t;

/* VIC_IRQ_STATUS1 */

#define MSK_VIC_IRQ_STATUS1 (0x1) /* [0] */

typedef unsigned short vic_irq_status1_t; /* [0] */

/* VIC_IRQ_MASK0 */

#define MSK_VIC_IRQ_MASK0 (0xffff) /* [15:0] */

typedef unsigned short vic_irq_mask0_t; /* [15:0] */

/* VIC_IRQ_MASK1 */

#define MSK_VIC_IRQ_MASK1 (0x1) /* [0] */

typedef unsigned short vic_irq_mask1_t; /* [0] */

/* VIC_IRQ_VENABLE */

#define MSK_VIC_IRQ_VENABLE (0x1f) /* [ 4:0] */

typedef unsigned short vic_irq_venable_t; /* [ 4:0] */

/* VIC_IRQ_VDISABLE */

#define MSK_VIC_IRQ_VDISABLE (0x1f) /* [ 4:0] */

typedef unsigned short vic_irq_vdisable_t; /* [ 4:0] */

/* VIC_IRQ_VMAX */

#define MSK_VIC_IRQ_VMAX (0x1f) /* [ 4:0] */

typedef unsigned short vic_irq_vmax_t; /* [ 4:0] */

/* VIC_IRQ_VNO */

#define MSK_VIC_IRQ_VNO (0x1f) /* [ 4:0] */

typedef unsigned short vic_irq_vno_t; /* [ 4:0] */

/* VIC */

typedef struct
{
  vic_table_base_t table_base;   /* 0 */
  vic_table_type_t table_type;   /* 2 */
  vic_main_enable_t main_enable; /* 4 */
  unsigned short reserved0[21];
  vic_irq_status0_t irq_status0;   /* 48 */
  vic_irq_status1_t irq_status1;   /* 50 */
  vic_irq_mask0_t irq_mask0;       /* 52 */
  vic_irq_mask1_t irq_mask1;       /* 54 */
  vic_irq_venable_t irq_venable;   /* 56 */
  vic_irq_vdisable_t irq_vdisable; /* 58 */
  vic_irq_vmax_t irq_vmax;         /* 60 */
  vic_irq_vno_t irq_vno;           /* 62 */
} _PACKED_ vic_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_VIC 0x0040U ... Vector Interrupt Controller Module

#define ADDR_VIC_TABLE_BASE (0x00U)
#define A_VIC_TABLE_BASE(ba) ((ba) + ADDR_VIC_TABLE_BASE)
#define R_VIC_TABLE_BASE(ba) (*(volatile unsigned short *)((unsigned int)A_VIC_TABLE_BASE(ba)))
#define RES_VIC_TABLE_BASE (0x0U)
#define MSB_VIC_TABLE_BASE 15
#define LSB_VIC_TABLE_BASE 0
#define AADDR_VIC_TABLE_BASE (BASE_ADDR_VIC + ADDR_VIC_TABLE_BASE)
#define REG_VIC_TABLE_BASE (*(volatile unsigned short *)((unsigned int)AADDR_VIC_TABLE_BASE))

#define ADDR_VIC_TABLE_TYPE (0x02U)
#define A_VIC_TABLE_TYPE(ba) ((ba) + ADDR_VIC_TABLE_TYPE)
#define R_VIC_TABLE_TYPE(ba) (*(volatile unsigned short *)((unsigned int)A_VIC_TABLE_TYPE(ba)))
#define RES_VIC_TABLE_TYPE (0x0U)
#define MSB_VIC_TABLE_TYPE 0
#define LSB_VIC_TABLE_TYPE 0
#define AADDR_VIC_TABLE_TYPE (BASE_ADDR_VIC + ADDR_VIC_TABLE_TYPE)
#define REG_VIC_TABLE_TYPE (*(volatile unsigned short *)((unsigned int)AADDR_VIC_TABLE_TYPE))

#define ADDR_VIC_MAIN_ENABLE (0x04U)
#define A_VIC_MAIN_ENABLE(ba) ((ba) + ADDR_VIC_MAIN_ENABLE)
#define R_VIC_MAIN_ENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_VIC_MAIN_ENABLE(ba)))
#define RES_VIC_MAIN_ENABLE (0x1U)
#define MSB_VIC_MAIN_ENABLE 0
#define LSB_VIC_MAIN_ENABLE 0
#define AADDR_VIC_MAIN_ENABLE (BASE_ADDR_VIC + ADDR_VIC_MAIN_ENABLE)
#define REG_VIC_MAIN_ENABLE (*(volatile unsigned short *)((unsigned int)AADDR_VIC_MAIN_ENABLE))

#define ADDR_VIC_IRQ_STATUS0 (0x30U)
#define A_VIC_IRQ_STATUS0(ba) ((ba) + ADDR_VIC_IRQ_STATUS0)
#define R_VIC_IRQ_STATUS0(ba) (*(volatile unsigned short *)((unsigned int)A_VIC_IRQ_STATUS0(ba)))
#define RES_VIC_IRQ_STATUS0 (0x0U)
#define MSB_VIC_IRQ_STATUS0 15
#define LSB_VIC_IRQ_STATUS0 0
#define AADDR_VIC_IRQ_STATUS0 (BASE_ADDR_VIC + ADDR_VIC_IRQ_STATUS0)
#define REG_VIC_IRQ_STATUS0 (*(volatile unsigned short *)((unsigned int)AADDR_VIC_IRQ_STATUS0))

#define ADDR_VIC_IRQ_STATUS1 (0x32U)
#define A_VIC_IRQ_STATUS1(ba) ((ba) + ADDR_VIC_IRQ_STATUS1)
#define R_VIC_IRQ_STATUS1(ba) (*(volatile unsigned short *)((unsigned int)A_VIC_IRQ_STATUS1(ba)))
#define RES_VIC_IRQ_STATUS1 (0x0U)
#define MSB_VIC_IRQ_STATUS1 0
#define LSB_VIC_IRQ_STATUS1 0
#define AADDR_VIC_IRQ_STATUS1 (BASE_ADDR_VIC + ADDR_VIC_IRQ_STATUS1)
#define REG_VIC_IRQ_STATUS1 (*(volatile unsigned short *)((unsigned int)AADDR_VIC_IRQ_STATUS1))

#define ADDR_VIC_IRQ_MASK0 (0x34U)
#define A_VIC_IRQ_MASK0(ba) ((ba) + ADDR_VIC_IRQ_MASK0)
#define R_VIC_IRQ_MASK0(ba) (*(volatile unsigned short *)((unsigned int)A_VIC_IRQ_MASK0(ba)))
#define RES_VIC_IRQ_MASK0 (0x0U)
#define MSB_VIC_IRQ_MASK0 15
#define LSB_VIC_IRQ_MASK0 0
#define AADDR_VIC_IRQ_MASK0 (BASE_ADDR_VIC + ADDR_VIC_IRQ_MASK0)
#define REG_VIC_IRQ_MASK0 (*(volatile unsigned short *)((unsigned int)AADDR_VIC_IRQ_MASK0))

#define ADDR_VIC_IRQ_MASK1 (0x36U)
#define A_VIC_IRQ_MASK1(ba) ((ba) + ADDR_VIC_IRQ_MASK1)
#define R_VIC_IRQ_MASK1(ba) (*(volatile unsigned short *)((unsigned int)A_VIC_IRQ_MASK1(ba)))
#define RES_VIC_IRQ_MASK1 (0x0U)
#define MSB_VIC_IRQ_MASK1 0
#define LSB_VIC_IRQ_MASK1 0
#define AADDR_VIC_IRQ_MASK1 (BASE_ADDR_VIC + ADDR_VIC_IRQ_MASK1)
#define REG_VIC_IRQ_MASK1 (*(volatile unsigned short *)((unsigned int)AADDR_VIC_IRQ_MASK1))

#define ADDR_VIC_IRQ_VENABLE (0x38U)
#define A_VIC_IRQ_VENABLE(ba) ((ba) + ADDR_VIC_IRQ_VENABLE)
#define R_VIC_IRQ_VENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_VIC_IRQ_VENABLE(ba)))
#define RES_VIC_IRQ_VENABLE (0x0U)
#define MSB_VIC_IRQ_VENABLE 4
#define LSB_VIC_IRQ_VENABLE 0
#define AADDR_VIC_IRQ_VENABLE (BASE_ADDR_VIC + ADDR_VIC_IRQ_VENABLE)
#define REG_VIC_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_VIC_IRQ_VENABLE))

#define ADDR_VIC_IRQ_VDISABLE (0x3AU)
#define A_VIC_IRQ_VDISABLE(ba) ((ba) + ADDR_VIC_IRQ_VDISABLE)
#define R_VIC_IRQ_VDISABLE(ba) (*(volatile unsigned short *)((unsigned int)A_VIC_IRQ_VDISABLE(ba)))
#define RES_VIC_IRQ_VDISABLE (0x0U)
#define MSB_VIC_IRQ_VDISABLE 4
#define LSB_VIC_IRQ_VDISABLE 0
#define AADDR_VIC_IRQ_VDISABLE (BASE_ADDR_VIC + ADDR_VIC_IRQ_VDISABLE)
#define REG_VIC_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_VIC_IRQ_VDISABLE))

#define ADDR_VIC_IRQ_VMAX (0x3CU)
#define A_VIC_IRQ_VMAX(ba) ((ba) + ADDR_VIC_IRQ_VMAX)
#define R_VIC_IRQ_VMAX(ba) (*(volatile unsigned short *)((unsigned int)A_VIC_IRQ_VMAX(ba)))
#define RES_VIC_IRQ_VMAX (0x11U)
#define MSB_VIC_IRQ_VMAX 4
#define LSB_VIC_IRQ_VMAX 0
#define AADDR_VIC_IRQ_VMAX (BASE_ADDR_VIC + ADDR_VIC_IRQ_VMAX)
#define REG_VIC_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_VIC_IRQ_VMAX))

#define ADDR_VIC_IRQ_VNO (0x3EU)
#define A_VIC_IRQ_VNO(ba) ((ba) + ADDR_VIC_IRQ_VNO)
#define R_VIC_IRQ_VNO(ba) (*(volatile unsigned short *)((unsigned int)A_VIC_IRQ_VNO(ba)))
#define RES_VIC_IRQ_VNO (0x11U)
#define MSB_VIC_IRQ_VNO 4
#define LSB_VIC_IRQ_VNO 0
#define AADDR_VIC_IRQ_VNO (BASE_ADDR_VIC + ADDR_VIC_IRQ_VNO)
#define REG_VIC_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_VIC_IRQ_VNO))

#endif
