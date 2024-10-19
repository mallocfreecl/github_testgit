#ifndef __CCTIMER_BF_H__
#define __CCTIMER_BF_H__

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

#ifndef BASE_ADDR_CCTIMER_0
#define BASE_ADDR_CCTIMER_0 0x03C0U
#endif
#ifndef BASE_ADDR_CCTIMER_1
#define BASE_ADDR_CCTIMER_1 0x0400U
#endif
#ifndef BASE_ADDR_CCTIMER_2
#define BASE_ADDR_CCTIMER_2 0x0440U
#endif
#ifndef BASE_ADDR_CCTIMER_3
#define BASE_ADDR_CCTIMER_3 0x0480U
#endif

#define MULTIPLE_CCTIMER
#define NUMBER_CCTIMER 4

typedef enum
{
  CCTIMER_0 = (int)BASE_ADDR_CCTIMER_0,
  CCTIMER_1 = (int)BASE_ADDR_CCTIMER_1,
  CCTIMER_2 = (int)BASE_ADDR_CCTIMER_2,
  CCTIMER_3 = (int)BASE_ADDR_CCTIMER_3
} cctimer_num_t;

// Register bit field definitions

/* CCTIMER_PRESCALER */

#define MSK_CCTIMER_PRESCALER (0xff) /* [ 7:0] */

typedef unsigned short cctimer_prescaler_t; /* [ 7:0] */

/* CCTIMER_CONTROL */

#define MSK_CCTIMER_CONTROL_ENABLE_A (0x1) /* [0] */
#define SFT_CCTIMER_CONTROL_ENABLE_A (0)
#define LSB_CCTIMER_CONTROL_ENABLE_A (0)
#define MSB_CCTIMER_CONTROL_ENABLE_A (0)
#define BIT_CCTIMER_CONTROL_ENABLE_A (0x1) /* [0] */
#define MSK_CCTIMER_CONTROL_ENABLE_B (0x1) /* [1] */
#define SFT_CCTIMER_CONTROL_ENABLE_B (1)
#define LSB_CCTIMER_CONTROL_ENABLE_B (1)
#define MSB_CCTIMER_CONTROL_ENABLE_B (1)
#define BIT_CCTIMER_CONTROL_ENABLE_B (0x2)  /* [1] */
#define MSK_CCTIMER_CONTROL_RESTART_A (0x1) /* [2] */
#define SFT_CCTIMER_CONTROL_RESTART_A (2)
#define LSB_CCTIMER_CONTROL_RESTART_A (2)
#define MSB_CCTIMER_CONTROL_RESTART_A (2)
#define BIT_CCTIMER_CONTROL_RESTART_A (0x4) /* [2] */
#define MSK_CCTIMER_CONTROL_RESTART_B (0x1) /* [3] */
#define SFT_CCTIMER_CONTROL_RESTART_B (3)
#define LSB_CCTIMER_CONTROL_RESTART_B (3)
#define MSB_CCTIMER_CONTROL_RESTART_B (3)
#define BIT_CCTIMER_CONTROL_RESTART_B (0x8) /* [3] */
#define MSK_CCTIMER_CONTROL_RESTART_P (0x1) /* [4] */
#define SFT_CCTIMER_CONTROL_RESTART_P (4)
#define LSB_CCTIMER_CONTROL_RESTART_P (4)
#define MSB_CCTIMER_CONTROL_RESTART_P (4)
#define BIT_CCTIMER_CONTROL_RESTART_P (0x10) /* [4] */

typedef struct
{
  unsigned short enable_a : 1;  /* [0] */
  unsigned short enable_b : 1;  /* [1] */
  unsigned short restart_a : 1; /* [2] */
  unsigned short restart_b : 1; /* [3] */
  unsigned short restart_p : 1; /* [4] */
  unsigned short reserved : 11;
} _PACKED_ cctimer_control_bf;

typedef union {
  unsigned short val;
  cctimer_control_bf bf;
} _PACKED_ cctimer_control_t;

/* CCTIMER_CONFIG */

#define MSK_CCTIMER_CONFIG_CLK_SEL (0x3) /* [ 1:0] */
#define SFT_CCTIMER_CONFIG_CLK_SEL (0)
#define LSB_CCTIMER_CONFIG_CLK_SEL (0)
#define MSB_CCTIMER_CONFIG_CLK_SEL (1)
#define MSK_CCTIMER_CONFIG_RESTART_SEL (0x7) /* [ 4:2] */
#define SFT_CCTIMER_CONFIG_RESTART_SEL (2)
#define LSB_CCTIMER_CONFIG_RESTART_SEL (2)
#define MSB_CCTIMER_CONFIG_RESTART_SEL (4)
#define MSK_CCTIMER_CONFIG_CAPTURE_SEL (0x3) /* [ 6:5] */
#define SFT_CCTIMER_CONFIG_CAPTURE_SEL (5)
#define LSB_CCTIMER_CONFIG_CAPTURE_SEL (5)
#define MSB_CCTIMER_CONFIG_CAPTURE_SEL (6)
#define MSK_CCTIMER_CONFIG_MODE (0x3) /* [ 9:8] */
#define SFT_CCTIMER_CONFIG_MODE (8)
#define LSB_CCTIMER_CONFIG_MODE (8)
#define MSB_CCTIMER_CONFIG_MODE (9)

typedef struct
{
  unsigned short clk_sel : 2;     /* [ 1:0] */
  unsigned short restart_sel : 3; /* [ 4:2] */
  unsigned short capture_sel : 2; /* [ 6:5] */
  unsigned short reserved7 : 1;   /* [7] */
  unsigned short mode : 2;        /* [ 9:8] */
  unsigned short reserved : 6;
} _PACKED_ cctimer_config_bf;

typedef union {
  unsigned short val;
  cctimer_config_bf bf;
} _PACKED_ cctimer_config_t;

/* CCTIMER_CAPCMP */

#define MSK_CCTIMER_CAPCMP (0xffff) /* [15:0] */

typedef unsigned short cctimer_capcmp_t; /* [15:0] */

/* CCTIMER_COUNTER */

#define MSK_CCTIMER_COUNTER (0xffff) /* [15:0] */

typedef unsigned short cctimer_counter_t; /* [15:0] */

/* CCTIMER_PRESEL */

#define MSK_CCTIMER_PRESEL_CLK_SEL (0xf) /* [ 3:0] */
#define SFT_CCTIMER_PRESEL_CLK_SEL (0)
#define LSB_CCTIMER_PRESEL_CLK_SEL (0)
#define MSB_CCTIMER_PRESEL_CLK_SEL (3)
#define MSK_CCTIMER_PRESEL_RESTART_SEL (0xf) /* [ 7:4] */
#define SFT_CCTIMER_PRESEL_RESTART_SEL (4)
#define LSB_CCTIMER_PRESEL_RESTART_SEL (4)
#define MSB_CCTIMER_PRESEL_RESTART_SEL (7)
#define MSK_CCTIMER_PRESEL_CAPTURE_SEL (0xf) /* [11:8] */
#define SFT_CCTIMER_PRESEL_CAPTURE_SEL (8)
#define LSB_CCTIMER_PRESEL_CAPTURE_SEL (8)
#define MSB_CCTIMER_PRESEL_CAPTURE_SEL (11)

typedef struct
{
  unsigned short clk_sel : 4;     /* [ 3:0] */
  unsigned short restart_sel : 4; /* [ 7:4] */
  unsigned short capture_sel : 4; /* [11:8] */
  unsigned short reserved : 4;
} _PACKED_ cctimer_presel_bf;

typedef union {
  unsigned short val;
  cctimer_presel_bf bf;
} _PACKED_ cctimer_presel_t;

/* CCTIMER_IRQ_STATUS */

#define MSK_CCTIMER_IRQ_STATUS_RESTART_P (0x1) /* [0] */
#define SFT_CCTIMER_IRQ_STATUS_RESTART_P (0)
#define LSB_CCTIMER_IRQ_STATUS_RESTART_P (0)
#define MSB_CCTIMER_IRQ_STATUS_RESTART_P (0)
#define BIT_CCTIMER_IRQ_STATUS_RESTART_P (0x1)  /* [0] */
#define MSK_CCTIMER_IRQ_STATUS_OVERFLOW_A (0x1) /* [1] */
#define SFT_CCTIMER_IRQ_STATUS_OVERFLOW_A (1)
#define LSB_CCTIMER_IRQ_STATUS_OVERFLOW_A (1)
#define MSB_CCTIMER_IRQ_STATUS_OVERFLOW_A (1)
#define BIT_CCTIMER_IRQ_STATUS_OVERFLOW_A (0x2) /* [1] */
#define MSK_CCTIMER_IRQ_STATUS_OVERFLOW_B (0x1) /* [2] */
#define SFT_CCTIMER_IRQ_STATUS_OVERFLOW_B (2)
#define LSB_CCTIMER_IRQ_STATUS_OVERFLOW_B (2)
#define MSB_CCTIMER_IRQ_STATUS_OVERFLOW_B (2)
#define BIT_CCTIMER_IRQ_STATUS_OVERFLOW_B (0x4) /* [2] */
#define MSK_CCTIMER_IRQ_STATUS_RESTART_A (0x1)  /* [3] */
#define SFT_CCTIMER_IRQ_STATUS_RESTART_A (3)
#define LSB_CCTIMER_IRQ_STATUS_RESTART_A (3)
#define MSB_CCTIMER_IRQ_STATUS_RESTART_A (3)
#define BIT_CCTIMER_IRQ_STATUS_RESTART_A (0x8) /* [3] */
#define MSK_CCTIMER_IRQ_STATUS_RESTART_B (0x1) /* [4] */
#define SFT_CCTIMER_IRQ_STATUS_RESTART_B (4)
#define LSB_CCTIMER_IRQ_STATUS_RESTART_B (4)
#define MSB_CCTIMER_IRQ_STATUS_RESTART_B (4)
#define BIT_CCTIMER_IRQ_STATUS_RESTART_B (0x10) /* [4] */
#define MSK_CCTIMER_IRQ_STATUS_CAPTURE_A (0x1)  /* [5] */
#define SFT_CCTIMER_IRQ_STATUS_CAPTURE_A (5)
#define LSB_CCTIMER_IRQ_STATUS_CAPTURE_A (5)
#define MSB_CCTIMER_IRQ_STATUS_CAPTURE_A (5)
#define BIT_CCTIMER_IRQ_STATUS_CAPTURE_A (0x20) /* [5] */
#define MSK_CCTIMER_IRQ_STATUS_CAPTURE_B (0x1)  /* [6] */
#define SFT_CCTIMER_IRQ_STATUS_CAPTURE_B (6)
#define LSB_CCTIMER_IRQ_STATUS_CAPTURE_B (6)
#define MSB_CCTIMER_IRQ_STATUS_CAPTURE_B (6)
#define BIT_CCTIMER_IRQ_STATUS_CAPTURE_B (0x40) /* [6] */
#define MSK_CCTIMER_IRQ_STATUS_COMPARE_A (0x1)  /* [7] */
#define SFT_CCTIMER_IRQ_STATUS_COMPARE_A (7)
#define LSB_CCTIMER_IRQ_STATUS_COMPARE_A (7)
#define MSB_CCTIMER_IRQ_STATUS_COMPARE_A (7)
#define BIT_CCTIMER_IRQ_STATUS_COMPARE_A (0x80) /* [7] */
#define MSK_CCTIMER_IRQ_STATUS_COMPARE_B (0x1)  /* [8] */
#define SFT_CCTIMER_IRQ_STATUS_COMPARE_B (8)
#define LSB_CCTIMER_IRQ_STATUS_COMPARE_B (8)
#define MSB_CCTIMER_IRQ_STATUS_COMPARE_B (8)
#define BIT_CCTIMER_IRQ_STATUS_COMPARE_B (0x100) /* [8] */

typedef struct
{
  unsigned short restart_p : 1;  /* [0] */
  unsigned short overflow_a : 1; /* [1] */
  unsigned short overflow_b : 1; /* [2] */
  unsigned short restart_a : 1;  /* [3] */
  unsigned short restart_b : 1;  /* [4] */
  unsigned short capture_a : 1;  /* [5] */
  unsigned short capture_b : 1;  /* [6] */
  unsigned short compare_a : 1;  /* [7] */
  unsigned short compare_b : 1;  /* [8] */
  unsigned short reserved : 7;
} _PACKED_ cctimer_irq_status_bf;

typedef union {
  unsigned short val;
  cctimer_irq_status_bf bf;
} _PACKED_ cctimer_irq_status_t;

/* CCTIMER_IRQ_MASK */

#define MSK_CCTIMER_IRQ_MASK (0x1ff) /* [ 8:0] */

typedef unsigned short cctimer_irq_mask_t; /* [ 8:0] */

/* CCTIMER_IRQ_VENABLE */

#define MSK_CCTIMER_IRQ_VENABLE (0xf) /* [ 3:0] */

typedef unsigned short cctimer_irq_venable_t; /* [ 3:0] */

/* CCTIMER_IRQ_VDISABLE */

#define MSK_CCTIMER_IRQ_VDISABLE (0xf) /* [ 3:0] */

typedef unsigned short cctimer_irq_vdisable_t; /* [ 3:0] */

/* CCTIMER_IRQ_VMAX */

#define MSK_CCTIMER_IRQ_VMAX (0xf) /* [ 3:0] */

typedef unsigned short cctimer_irq_vmax_t; /* [ 3:0] */

/* CCTIMER_IRQ_VNO */

#define MSK_CCTIMER_IRQ_VNO (0xf) /* [ 3:0] */

typedef unsigned short cctimer_irq_vno_t; /* [ 3:0] */

/* CCTIMER */

typedef struct
{
  cctimer_prescaler_t prescaler; /* 0 */
  cctimer_control_t control;     /* 2 */
  cctimer_config_t config_a;     /* 4 */
  cctimer_config_t config_b;     /* 6 */
  cctimer_capcmp_t capcmp_a;     /* 8 */
  cctimer_capcmp_t capcmp_b;     /* 10 */
  cctimer_counter_t counter_a;   /* 12 */
  cctimer_counter_t counter_b;   /* 14 */
  cctimer_presel_t presel_a;     /* 16 */
  cctimer_presel_t presel_b;     /* 18 */
  unsigned short reserved0[14];
  cctimer_irq_status_t irq_status; /* 48 */
  unsigned short reserved1[1];
  cctimer_irq_mask_t irq_mask; /* 52 */
  unsigned short reserved2[1];
  cctimer_irq_venable_t irq_venable;   /* 56 */
  cctimer_irq_vdisable_t irq_vdisable; /* 58 */
  cctimer_irq_vmax_t irq_vmax;         /* 60 */
  cctimer_irq_vno_t irq_vno;           /* 62 */
} _PACKED_ cctimer_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_CCTIMER_0 0x03C0U ... Capture Compare Timer (Instance 0)
// Instance base address BASE_ADDR_CCTIMER_1 0x0400U ... Capture Compare Timer (Instance 1)
// Instance base address BASE_ADDR_CCTIMER_2 0x0440U ... Capture Compare Timer (Instance 2)
// Instance base address BASE_ADDR_CCTIMER_3 0x0480U ... Capture Compare Timer (Instance 3)

#define ADDR_CCTIMER_PRESCALER (0x00U)
#define A_CCTIMER_PRESCALER(ba) ((ba) + ADDR_CCTIMER_PRESCALER)
#define R_CCTIMER_PRESCALER(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_PRESCALER(ba)))
#define RES_CCTIMER_PRESCALER (0x0U)
#define MSB_CCTIMER_PRESCALER 7
#define LSB_CCTIMER_PRESCALER 0
#define AADDR_CCTIMER_0_PRESCALER (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_PRESCALER)
#define AADDR_CCTIMER_1_PRESCALER (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_PRESCALER)
#define AADDR_CCTIMER_2_PRESCALER (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_PRESCALER)
#define AADDR_CCTIMER_3_PRESCALER (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_PRESCALER)
#define REG_CCTIMER_0_PRESCALER (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_PRESCALER))
#define REG_CCTIMER_1_PRESCALER (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_PRESCALER))
#define REG_CCTIMER_2_PRESCALER (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_PRESCALER))
#define REG_CCTIMER_3_PRESCALER (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_PRESCALER))

#define ADDR_CCTIMER_CONTROL (0x02U)
#define A_CCTIMER_CONTROL(ba) ((ba) + ADDR_CCTIMER_CONTROL)
#define R_CCTIMER_CONTROL(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_CONTROL(ba)))
#define RES_CCTIMER_CONTROL (0x0U)
#define MSB_CCTIMER_CONTROL 4
#define LSB_CCTIMER_CONTROL 0
#define AADDR_CCTIMER_0_CONTROL (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_CONTROL)
#define AADDR_CCTIMER_1_CONTROL (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_CONTROL)
#define AADDR_CCTIMER_2_CONTROL (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_CONTROL)
#define AADDR_CCTIMER_3_CONTROL (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_CONTROL)
#define REG_CCTIMER_0_CONTROL (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_CONTROL))
#define REG_CCTIMER_1_CONTROL (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_CONTROL))
#define REG_CCTIMER_2_CONTROL (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_CONTROL))
#define REG_CCTIMER_3_CONTROL (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_CONTROL))

#define ADDR_CCTIMER_CONFIG_A (0x04U)
#define A_CCTIMER_CONFIG_A(ba) ((ba) + ADDR_CCTIMER_CONFIG_A)
#define R_CCTIMER_CONFIG_A(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_CONFIG_A(ba)))
#define RES_CCTIMER_CONFIG_A (0x0U)
#define MSB_CCTIMER_CONFIG_A 9
#define LSB_CCTIMER_CONFIG_A 0
#define AADDR_CCTIMER_0_CONFIG_A (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_CONFIG_A)
#define AADDR_CCTIMER_1_CONFIG_A (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_CONFIG_A)
#define AADDR_CCTIMER_2_CONFIG_A (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_CONFIG_A)
#define AADDR_CCTIMER_3_CONFIG_A (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_CONFIG_A)
#define REG_CCTIMER_0_CONFIG_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_CONFIG_A))
#define REG_CCTIMER_1_CONFIG_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_CONFIG_A))
#define REG_CCTIMER_2_CONFIG_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_CONFIG_A))
#define REG_CCTIMER_3_CONFIG_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_CONFIG_A))

#define ADDR_CCTIMER_CONFIG_B (0x06U)
#define A_CCTIMER_CONFIG_B(ba) ((ba) + ADDR_CCTIMER_CONFIG_B)
#define R_CCTIMER_CONFIG_B(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_CONFIG_B(ba)))
#define RES_CCTIMER_CONFIG_B (0x0U)
#define MSB_CCTIMER_CONFIG_B 9
#define LSB_CCTIMER_CONFIG_B 0
#define AADDR_CCTIMER_0_CONFIG_B (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_CONFIG_B)
#define AADDR_CCTIMER_1_CONFIG_B (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_CONFIG_B)
#define AADDR_CCTIMER_2_CONFIG_B (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_CONFIG_B)
#define AADDR_CCTIMER_3_CONFIG_B (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_CONFIG_B)
#define REG_CCTIMER_0_CONFIG_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_CONFIG_B))
#define REG_CCTIMER_1_CONFIG_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_CONFIG_B))
#define REG_CCTIMER_2_CONFIG_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_CONFIG_B))
#define REG_CCTIMER_3_CONFIG_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_CONFIG_B))

#define ADDR_CCTIMER_CAPCMP_A (0x08U)
#define A_CCTIMER_CAPCMP_A(ba) ((ba) + ADDR_CCTIMER_CAPCMP_A)
#define R_CCTIMER_CAPCMP_A(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_CAPCMP_A(ba)))
#define RES_CCTIMER_CAPCMP_A (0x0U)
#define MSB_CCTIMER_CAPCMP_A 15
#define LSB_CCTIMER_CAPCMP_A 0
#define AADDR_CCTIMER_0_CAPCMP_A (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_CAPCMP_A)
#define AADDR_CCTIMER_1_CAPCMP_A (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_CAPCMP_A)
#define AADDR_CCTIMER_2_CAPCMP_A (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_CAPCMP_A)
#define AADDR_CCTIMER_3_CAPCMP_A (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_CAPCMP_A)
#define REG_CCTIMER_0_CAPCMP_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_CAPCMP_A))
#define REG_CCTIMER_1_CAPCMP_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_CAPCMP_A))
#define REG_CCTIMER_2_CAPCMP_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_CAPCMP_A))
#define REG_CCTIMER_3_CAPCMP_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_CAPCMP_A))

#define ADDR_CCTIMER_CAPCMP_B (0x0AU)
#define A_CCTIMER_CAPCMP_B(ba) ((ba) + ADDR_CCTIMER_CAPCMP_B)
#define R_CCTIMER_CAPCMP_B(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_CAPCMP_B(ba)))
#define RES_CCTIMER_CAPCMP_B (0x0U)
#define MSB_CCTIMER_CAPCMP_B 15
#define LSB_CCTIMER_CAPCMP_B 0
#define AADDR_CCTIMER_0_CAPCMP_B (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_CAPCMP_B)
#define AADDR_CCTIMER_1_CAPCMP_B (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_CAPCMP_B)
#define AADDR_CCTIMER_2_CAPCMP_B (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_CAPCMP_B)
#define AADDR_CCTIMER_3_CAPCMP_B (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_CAPCMP_B)
#define REG_CCTIMER_0_CAPCMP_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_CAPCMP_B))
#define REG_CCTIMER_1_CAPCMP_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_CAPCMP_B))
#define REG_CCTIMER_2_CAPCMP_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_CAPCMP_B))
#define REG_CCTIMER_3_CAPCMP_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_CAPCMP_B))

#define ADDR_CCTIMER_COUNTER_A (0x0CU)
#define A_CCTIMER_COUNTER_A(ba) ((ba) + ADDR_CCTIMER_COUNTER_A)
#define R_CCTIMER_COUNTER_A(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_COUNTER_A(ba)))
#define RES_CCTIMER_COUNTER_A (0x0U)
#define MSB_CCTIMER_COUNTER_A 15
#define LSB_CCTIMER_COUNTER_A 0
#define AADDR_CCTIMER_0_COUNTER_A (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_COUNTER_A)
#define AADDR_CCTIMER_1_COUNTER_A (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_COUNTER_A)
#define AADDR_CCTIMER_2_COUNTER_A (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_COUNTER_A)
#define AADDR_CCTIMER_3_COUNTER_A (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_COUNTER_A)
#define REG_CCTIMER_0_COUNTER_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_COUNTER_A))
#define REG_CCTIMER_1_COUNTER_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_COUNTER_A))
#define REG_CCTIMER_2_COUNTER_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_COUNTER_A))
#define REG_CCTIMER_3_COUNTER_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_COUNTER_A))

#define ADDR_CCTIMER_COUNTER_B (0x0EU)
#define A_CCTIMER_COUNTER_B(ba) ((ba) + ADDR_CCTIMER_COUNTER_B)
#define R_CCTIMER_COUNTER_B(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_COUNTER_B(ba)))
#define RES_CCTIMER_COUNTER_B (0x0U)
#define MSB_CCTIMER_COUNTER_B 15
#define LSB_CCTIMER_COUNTER_B 0
#define AADDR_CCTIMER_0_COUNTER_B (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_COUNTER_B)
#define AADDR_CCTIMER_1_COUNTER_B (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_COUNTER_B)
#define AADDR_CCTIMER_2_COUNTER_B (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_COUNTER_B)
#define AADDR_CCTIMER_3_COUNTER_B (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_COUNTER_B)
#define REG_CCTIMER_0_COUNTER_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_COUNTER_B))
#define REG_CCTIMER_1_COUNTER_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_COUNTER_B))
#define REG_CCTIMER_2_COUNTER_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_COUNTER_B))
#define REG_CCTIMER_3_COUNTER_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_COUNTER_B))

#define ADDR_CCTIMER_PRESEL_A (0x10U)
#define A_CCTIMER_PRESEL_A(ba) ((ba) + ADDR_CCTIMER_PRESEL_A)
#define R_CCTIMER_PRESEL_A(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_PRESEL_A(ba)))
#define RES_CCTIMER_PRESEL_A (0x0U)
#define MSB_CCTIMER_PRESEL_A 11
#define LSB_CCTIMER_PRESEL_A 0
#define AADDR_CCTIMER_0_PRESEL_A (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_PRESEL_A)
#define AADDR_CCTIMER_1_PRESEL_A (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_PRESEL_A)
#define AADDR_CCTIMER_2_PRESEL_A (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_PRESEL_A)
#define AADDR_CCTIMER_3_PRESEL_A (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_PRESEL_A)
#define REG_CCTIMER_0_PRESEL_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_PRESEL_A))
#define REG_CCTIMER_1_PRESEL_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_PRESEL_A))
#define REG_CCTIMER_2_PRESEL_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_PRESEL_A))
#define REG_CCTIMER_3_PRESEL_A (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_PRESEL_A))

#define ADDR_CCTIMER_PRESEL_B (0x12U)
#define A_CCTIMER_PRESEL_B(ba) ((ba) + ADDR_CCTIMER_PRESEL_B)
#define R_CCTIMER_PRESEL_B(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_PRESEL_B(ba)))
#define RES_CCTIMER_PRESEL_B (0x0U)
#define MSB_CCTIMER_PRESEL_B 11
#define LSB_CCTIMER_PRESEL_B 0
#define AADDR_CCTIMER_0_PRESEL_B (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_PRESEL_B)
#define AADDR_CCTIMER_1_PRESEL_B (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_PRESEL_B)
#define AADDR_CCTIMER_2_PRESEL_B (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_PRESEL_B)
#define AADDR_CCTIMER_3_PRESEL_B (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_PRESEL_B)
#define REG_CCTIMER_0_PRESEL_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_PRESEL_B))
#define REG_CCTIMER_1_PRESEL_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_PRESEL_B))
#define REG_CCTIMER_2_PRESEL_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_PRESEL_B))
#define REG_CCTIMER_3_PRESEL_B (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_PRESEL_B))

#define ADDR_CCTIMER_IRQ_STATUS (0x30U)
#define A_CCTIMER_IRQ_STATUS(ba) ((ba) + ADDR_CCTIMER_IRQ_STATUS)
#define R_CCTIMER_IRQ_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_IRQ_STATUS(ba)))
#define RES_CCTIMER_IRQ_STATUS (0x0U)
#define MSB_CCTIMER_IRQ_STATUS 8
#define LSB_CCTIMER_IRQ_STATUS 0
#define AADDR_CCTIMER_0_IRQ_STATUS (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_IRQ_STATUS)
#define AADDR_CCTIMER_1_IRQ_STATUS (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_IRQ_STATUS)
#define AADDR_CCTIMER_2_IRQ_STATUS (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_IRQ_STATUS)
#define AADDR_CCTIMER_3_IRQ_STATUS (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_IRQ_STATUS)
#define REG_CCTIMER_0_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_IRQ_STATUS))
#define REG_CCTIMER_1_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_IRQ_STATUS))
#define REG_CCTIMER_2_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_IRQ_STATUS))
#define REG_CCTIMER_3_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_IRQ_STATUS))

#define ADDR_CCTIMER_IRQ_MASK (0x34U)
#define A_CCTIMER_IRQ_MASK(ba) ((ba) + ADDR_CCTIMER_IRQ_MASK)
#define R_CCTIMER_IRQ_MASK(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_IRQ_MASK(ba)))
#define RES_CCTIMER_IRQ_MASK (0x0U)
#define MSB_CCTIMER_IRQ_MASK 8
#define LSB_CCTIMER_IRQ_MASK 0
#define AADDR_CCTIMER_0_IRQ_MASK (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_IRQ_MASK)
#define AADDR_CCTIMER_1_IRQ_MASK (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_IRQ_MASK)
#define AADDR_CCTIMER_2_IRQ_MASK (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_IRQ_MASK)
#define AADDR_CCTIMER_3_IRQ_MASK (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_IRQ_MASK)
#define REG_CCTIMER_0_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_IRQ_MASK))
#define REG_CCTIMER_1_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_IRQ_MASK))
#define REG_CCTIMER_2_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_IRQ_MASK))
#define REG_CCTIMER_3_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_IRQ_MASK))

#define ADDR_CCTIMER_IRQ_VENABLE (0x38U)
#define A_CCTIMER_IRQ_VENABLE(ba) ((ba) + ADDR_CCTIMER_IRQ_VENABLE)
#define R_CCTIMER_IRQ_VENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_IRQ_VENABLE(ba)))
#define RES_CCTIMER_IRQ_VENABLE (0x0U)
#define MSB_CCTIMER_IRQ_VENABLE 3
#define LSB_CCTIMER_IRQ_VENABLE 0
#define AADDR_CCTIMER_0_IRQ_VENABLE (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_IRQ_VENABLE)
#define AADDR_CCTIMER_1_IRQ_VENABLE (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_IRQ_VENABLE)
#define AADDR_CCTIMER_2_IRQ_VENABLE (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_IRQ_VENABLE)
#define AADDR_CCTIMER_3_IRQ_VENABLE (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_IRQ_VENABLE)
#define REG_CCTIMER_0_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_IRQ_VENABLE))
#define REG_CCTIMER_1_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_IRQ_VENABLE))
#define REG_CCTIMER_2_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_IRQ_VENABLE))
#define REG_CCTIMER_3_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_IRQ_VENABLE))

#define ADDR_CCTIMER_IRQ_VDISABLE (0x3AU)
#define A_CCTIMER_IRQ_VDISABLE(ba) ((ba) + ADDR_CCTIMER_IRQ_VDISABLE)
#define R_CCTIMER_IRQ_VDISABLE(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_IRQ_VDISABLE(ba)))
#define RES_CCTIMER_IRQ_VDISABLE (0x0U)
#define MSB_CCTIMER_IRQ_VDISABLE 3
#define LSB_CCTIMER_IRQ_VDISABLE 0
#define AADDR_CCTIMER_0_IRQ_VDISABLE (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_IRQ_VDISABLE)
#define AADDR_CCTIMER_1_IRQ_VDISABLE (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_IRQ_VDISABLE)
#define AADDR_CCTIMER_2_IRQ_VDISABLE (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_IRQ_VDISABLE)
#define AADDR_CCTIMER_3_IRQ_VDISABLE (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_IRQ_VDISABLE)
#define REG_CCTIMER_0_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_IRQ_VDISABLE))
#define REG_CCTIMER_1_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_IRQ_VDISABLE))
#define REG_CCTIMER_2_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_IRQ_VDISABLE))
#define REG_CCTIMER_3_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_IRQ_VDISABLE))

#define ADDR_CCTIMER_IRQ_VMAX (0x3CU)
#define A_CCTIMER_IRQ_VMAX(ba) ((ba) + ADDR_CCTIMER_IRQ_VMAX)
#define R_CCTIMER_IRQ_VMAX(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_IRQ_VMAX(ba)))
#define RES_CCTIMER_IRQ_VMAX (0x9U)
#define MSB_CCTIMER_IRQ_VMAX 3
#define LSB_CCTIMER_IRQ_VMAX 0
#define AADDR_CCTIMER_0_IRQ_VMAX (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_IRQ_VMAX)
#define AADDR_CCTIMER_1_IRQ_VMAX (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_IRQ_VMAX)
#define AADDR_CCTIMER_2_IRQ_VMAX (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_IRQ_VMAX)
#define AADDR_CCTIMER_3_IRQ_VMAX (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_IRQ_VMAX)
#define REG_CCTIMER_0_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_IRQ_VMAX))
#define REG_CCTIMER_1_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_IRQ_VMAX))
#define REG_CCTIMER_2_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_IRQ_VMAX))
#define REG_CCTIMER_3_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_IRQ_VMAX))

#define ADDR_CCTIMER_IRQ_VNO (0x3EU)
#define A_CCTIMER_IRQ_VNO(ba) ((ba) + ADDR_CCTIMER_IRQ_VNO)
#define R_CCTIMER_IRQ_VNO(ba) (*(volatile unsigned short *)((unsigned int)A_CCTIMER_IRQ_VNO(ba)))
#define RES_CCTIMER_IRQ_VNO (0x9U)
#define MSB_CCTIMER_IRQ_VNO 3
#define LSB_CCTIMER_IRQ_VNO 0
#define AADDR_CCTIMER_0_IRQ_VNO (BASE_ADDR_CCTIMER_0 + ADDR_CCTIMER_IRQ_VNO)
#define AADDR_CCTIMER_1_IRQ_VNO (BASE_ADDR_CCTIMER_1 + ADDR_CCTIMER_IRQ_VNO)
#define AADDR_CCTIMER_2_IRQ_VNO (BASE_ADDR_CCTIMER_2 + ADDR_CCTIMER_IRQ_VNO)
#define AADDR_CCTIMER_3_IRQ_VNO (BASE_ADDR_CCTIMER_3 + ADDR_CCTIMER_IRQ_VNO)
#define REG_CCTIMER_0_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_0_IRQ_VNO))
#define REG_CCTIMER_1_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_1_IRQ_VNO))
#define REG_CCTIMER_2_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_2_IRQ_VNO))
#define REG_CCTIMER_3_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_CCTIMER_3_IRQ_VNO))

#endif
