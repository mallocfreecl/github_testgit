#ifndef __GPIO_BF_H__
#define __GPIO_BF_H__

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

#ifndef BASE_ADDR_GPIO_A
#define BASE_ADDR_GPIO_A 0x0300U
#endif
#ifndef BASE_ADDR_GPIO_B
#define BASE_ADDR_GPIO_B 0x0340U
#endif
#ifndef BASE_ADDR_GPIO_C
#define BASE_ADDR_GPIO_C 0x0380U
#endif

#define MULTIPLE_GPIO
#define NUMBER_GPIO 3

typedef enum
{
  GPIO_A = (int)BASE_ADDR_GPIO_A,
  GPIO_B = (int)BASE_ADDR_GPIO_B,
  GPIO_C = (int)BASE_ADDR_GPIO_C
} gpio_num_t;

// Register bit field definitions

/* GPIO_DATA_OUT */

#define MSK_GPIO_DATA_OUT (0xff) /* [ 7:0] */

typedef unsigned short gpio_data_out_t; /* [ 7:0] */

/* GPIO_DATA_OE */

#define MSK_GPIO_DATA_OE (0xff) /* [ 7:0] */

typedef unsigned short gpio_data_oe_t; /* [ 7:0] */

/* GPIO_DATA_IN */

#define MSK_GPIO_DATA_IN (0xff) /* [ 7:0] */

typedef unsigned short gpio_data_in_t; /* [ 7:0] */

/* GPIO_DATA_IE */

#define MSK_GPIO_DATA_IE (0xff) /* [ 7:0] */

typedef unsigned short gpio_data_ie_t; /* [ 7:0] */

/* GPIO_DIRECTION_LOCK */

#define MSK_GPIO_DIRECTION_LOCK (0xff) /* [ 7:0] */

typedef unsigned short gpio_direction_lock_t; /* [ 7:0] */

/* GPIO_IRQ_STATUS */

#define MSK_GPIO_IRQ_STATUS_EVT_POS_0 (0x1) /* [0] */
#define SFT_GPIO_IRQ_STATUS_EVT_POS_0 (0)
#define LSB_GPIO_IRQ_STATUS_EVT_POS_0 (0)
#define MSB_GPIO_IRQ_STATUS_EVT_POS_0 (0)
#define BIT_GPIO_IRQ_STATUS_EVT_POS_0 (0x1) /* [0] */
#define MSK_GPIO_IRQ_STATUS_EVT_NEG_0 (0x1) /* [1] */
#define SFT_GPIO_IRQ_STATUS_EVT_NEG_0 (1)
#define LSB_GPIO_IRQ_STATUS_EVT_NEG_0 (1)
#define MSB_GPIO_IRQ_STATUS_EVT_NEG_0 (1)
#define BIT_GPIO_IRQ_STATUS_EVT_NEG_0 (0x2) /* [1] */
#define MSK_GPIO_IRQ_STATUS_EVT_POS_1 (0x1) /* [2] */
#define SFT_GPIO_IRQ_STATUS_EVT_POS_1 (2)
#define LSB_GPIO_IRQ_STATUS_EVT_POS_1 (2)
#define MSB_GPIO_IRQ_STATUS_EVT_POS_1 (2)
#define BIT_GPIO_IRQ_STATUS_EVT_POS_1 (0x4) /* [2] */
#define MSK_GPIO_IRQ_STATUS_EVT_NEG_1 (0x1) /* [3] */
#define SFT_GPIO_IRQ_STATUS_EVT_NEG_1 (3)
#define LSB_GPIO_IRQ_STATUS_EVT_NEG_1 (3)
#define MSB_GPIO_IRQ_STATUS_EVT_NEG_1 (3)
#define BIT_GPIO_IRQ_STATUS_EVT_NEG_1 (0x8) /* [3] */
#define MSK_GPIO_IRQ_STATUS_EVT_POS_2 (0x1) /* [4] */
#define SFT_GPIO_IRQ_STATUS_EVT_POS_2 (4)
#define LSB_GPIO_IRQ_STATUS_EVT_POS_2 (4)
#define MSB_GPIO_IRQ_STATUS_EVT_POS_2 (4)
#define BIT_GPIO_IRQ_STATUS_EVT_POS_2 (0x10) /* [4] */
#define MSK_GPIO_IRQ_STATUS_EVT_NEG_2 (0x1)  /* [5] */
#define SFT_GPIO_IRQ_STATUS_EVT_NEG_2 (5)
#define LSB_GPIO_IRQ_STATUS_EVT_NEG_2 (5)
#define MSB_GPIO_IRQ_STATUS_EVT_NEG_2 (5)
#define BIT_GPIO_IRQ_STATUS_EVT_NEG_2 (0x20) /* [5] */
#define MSK_GPIO_IRQ_STATUS_EVT_POS_3 (0x1)  /* [6] */
#define SFT_GPIO_IRQ_STATUS_EVT_POS_3 (6)
#define LSB_GPIO_IRQ_STATUS_EVT_POS_3 (6)
#define MSB_GPIO_IRQ_STATUS_EVT_POS_3 (6)
#define BIT_GPIO_IRQ_STATUS_EVT_POS_3 (0x40) /* [6] */
#define MSK_GPIO_IRQ_STATUS_EVT_NEG_3 (0x1)  /* [7] */
#define SFT_GPIO_IRQ_STATUS_EVT_NEG_3 (7)
#define LSB_GPIO_IRQ_STATUS_EVT_NEG_3 (7)
#define MSB_GPIO_IRQ_STATUS_EVT_NEG_3 (7)
#define BIT_GPIO_IRQ_STATUS_EVT_NEG_3 (0x80) /* [7] */
#define MSK_GPIO_IRQ_STATUS_EVT_POS_4 (0x1)  /* [8] */
#define SFT_GPIO_IRQ_STATUS_EVT_POS_4 (8)
#define LSB_GPIO_IRQ_STATUS_EVT_POS_4 (8)
#define MSB_GPIO_IRQ_STATUS_EVT_POS_4 (8)
#define BIT_GPIO_IRQ_STATUS_EVT_POS_4 (0x100) /* [8] */
#define MSK_GPIO_IRQ_STATUS_EVT_NEG_4 (0x1)   /* [9] */
#define SFT_GPIO_IRQ_STATUS_EVT_NEG_4 (9)
#define LSB_GPIO_IRQ_STATUS_EVT_NEG_4 (9)
#define MSB_GPIO_IRQ_STATUS_EVT_NEG_4 (9)
#define BIT_GPIO_IRQ_STATUS_EVT_NEG_4 (0x200) /* [9] */
#define MSK_GPIO_IRQ_STATUS_EVT_POS_5 (0x1)   /* [10] */
#define SFT_GPIO_IRQ_STATUS_EVT_POS_5 (10)
#define LSB_GPIO_IRQ_STATUS_EVT_POS_5 (10)
#define MSB_GPIO_IRQ_STATUS_EVT_POS_5 (10)
#define BIT_GPIO_IRQ_STATUS_EVT_POS_5 (0x400) /* [10] */
#define MSK_GPIO_IRQ_STATUS_EVT_NEG_5 (0x1)   /* [11] */
#define SFT_GPIO_IRQ_STATUS_EVT_NEG_5 (11)
#define LSB_GPIO_IRQ_STATUS_EVT_NEG_5 (11)
#define MSB_GPIO_IRQ_STATUS_EVT_NEG_5 (11)
#define BIT_GPIO_IRQ_STATUS_EVT_NEG_5 (0x800) /* [11] */
#define MSK_GPIO_IRQ_STATUS_EVT_POS_6 (0x1)   /* [12] */
#define SFT_GPIO_IRQ_STATUS_EVT_POS_6 (12)
#define LSB_GPIO_IRQ_STATUS_EVT_POS_6 (12)
#define MSB_GPIO_IRQ_STATUS_EVT_POS_6 (12)
#define BIT_GPIO_IRQ_STATUS_EVT_POS_6 (0x1000) /* [12] */
#define MSK_GPIO_IRQ_STATUS_EVT_NEG_6 (0x1)    /* [13] */
#define SFT_GPIO_IRQ_STATUS_EVT_NEG_6 (13)
#define LSB_GPIO_IRQ_STATUS_EVT_NEG_6 (13)
#define MSB_GPIO_IRQ_STATUS_EVT_NEG_6 (13)
#define BIT_GPIO_IRQ_STATUS_EVT_NEG_6 (0x2000) /* [13] */
#define MSK_GPIO_IRQ_STATUS_EVT_POS_7 (0x1)    /* [14] */
#define SFT_GPIO_IRQ_STATUS_EVT_POS_7 (14)
#define LSB_GPIO_IRQ_STATUS_EVT_POS_7 (14)
#define MSB_GPIO_IRQ_STATUS_EVT_POS_7 (14)
#define BIT_GPIO_IRQ_STATUS_EVT_POS_7 (0x4000) /* [14] */
#define MSK_GPIO_IRQ_STATUS_EVT_NEG_7 (0x1)    /* [15] */
#define SFT_GPIO_IRQ_STATUS_EVT_NEG_7 (15)
#define LSB_GPIO_IRQ_STATUS_EVT_NEG_7 (15)
#define MSB_GPIO_IRQ_STATUS_EVT_NEG_7 (15)
#define BIT_GPIO_IRQ_STATUS_EVT_NEG_7 (0x8000) /* [15] */

typedef struct
{
  unsigned short evt_pos_0 : 1; /* [0] */
  unsigned short evt_neg_0 : 1; /* [1] */
  unsigned short evt_pos_1 : 1; /* [2] */
  unsigned short evt_neg_1 : 1; /* [3] */
  unsigned short evt_pos_2 : 1; /* [4] */
  unsigned short evt_neg_2 : 1; /* [5] */
  unsigned short evt_pos_3 : 1; /* [6] */
  unsigned short evt_neg_3 : 1; /* [7] */
  unsigned short evt_pos_4 : 1; /* [8] */
  unsigned short evt_neg_4 : 1; /* [9] */
  unsigned short evt_pos_5 : 1; /* [10] */
  unsigned short evt_neg_5 : 1; /* [11] */
  unsigned short evt_pos_6 : 1; /* [12] */
  unsigned short evt_neg_6 : 1; /* [13] */
  unsigned short evt_pos_7 : 1; /* [14] */
  unsigned short evt_neg_7 : 1; /* [15] */
} _PACKED_ gpio_irq_status_bf;

typedef union {
  unsigned short val;
  gpio_irq_status_bf bf;
} _PACKED_ gpio_irq_status_t;

/* GPIO_IRQ_MASK */

#define MSK_GPIO_IRQ_MASK (0xffff) /* [15:0] */

typedef unsigned short gpio_irq_mask_t; /* [15:0] */

/* GPIO_IRQ_VENABLE */

#define MSK_GPIO_IRQ_VENABLE (0xf) /* [ 3:0] */

typedef unsigned short gpio_irq_venable_t; /* [ 3:0] */

/* GPIO_IRQ_VDISABLE */

#define MSK_GPIO_IRQ_VDISABLE (0xf) /* [ 3:0] */

typedef unsigned short gpio_irq_vdisable_t; /* [ 3:0] */

/* GPIO_IRQ_VMAX */

#define MSK_GPIO_IRQ_VMAX (0x1f) /* [ 4:0] */

typedef unsigned short gpio_irq_vmax_t; /* [ 4:0] */

/* GPIO_IRQ_VNO */

#define MSK_GPIO_IRQ_VNO (0x1f) /* [ 4:0] */

typedef unsigned short gpio_irq_vno_t; /* [ 4:0] */

/* GPIO */

typedef struct
{
  gpio_data_out_t data_out;             /* 0 */
  gpio_data_oe_t data_oe;               /* 2 */
  gpio_data_in_t data_in;               /* 4 */
  gpio_data_ie_t data_ie;               /* 6 */
  gpio_direction_lock_t direction_lock; /* 8 */
  unsigned short reserved0[19];
  gpio_irq_status_t irq_status; /* 48 */
  unsigned short reserved1[1];
  gpio_irq_mask_t irq_mask; /* 52 */
  unsigned short reserved2[1];
  gpio_irq_venable_t irq_venable;   /* 56 */
  gpio_irq_vdisable_t irq_vdisable; /* 58 */
  gpio_irq_vmax_t irq_vmax;         /* 60 */
  gpio_irq_vno_t irq_vno;           /* 62 */
} _PACKED_ gpio_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_GPIO_A 0x0300U ... GPIO Module (Port A)
// Instance base address BASE_ADDR_GPIO_B 0x0340U ... GPIO Module (Port B)
// Instance base address BASE_ADDR_GPIO_C 0x0380U ... GPIO Module (Port C)

#define ADDR_GPIO_DATA_OUT (0x00U)
#define A_GPIO_DATA_OUT(ba) ((ba) + ADDR_GPIO_DATA_OUT)
#define R_GPIO_DATA_OUT(ba) (*(volatile unsigned short *)((unsigned int)A_GPIO_DATA_OUT(ba)))
#define RES_GPIO_DATA_OUT (0x0U)
#define MSB_GPIO_DATA_OUT 7
#define LSB_GPIO_DATA_OUT 0
#define AADDR_GPIO_A_DATA_OUT (BASE_ADDR_GPIO_A + ADDR_GPIO_DATA_OUT)
#define AADDR_GPIO_B_DATA_OUT (BASE_ADDR_GPIO_B + ADDR_GPIO_DATA_OUT)
#define AADDR_GPIO_C_DATA_OUT (BASE_ADDR_GPIO_C + ADDR_GPIO_DATA_OUT)
#define REG_GPIO_A_DATA_OUT (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_A_DATA_OUT))
#define REG_GPIO_B_DATA_OUT (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_B_DATA_OUT))
#define REG_GPIO_C_DATA_OUT (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_C_DATA_OUT))

#define ADDR_GPIO_DATA_OE (0x02U)
#define A_GPIO_DATA_OE(ba) ((ba) + ADDR_GPIO_DATA_OE)
#define R_GPIO_DATA_OE(ba) (*(volatile unsigned short *)((unsigned int)A_GPIO_DATA_OE(ba)))
#define RES_GPIO_DATA_OE (0x0U)
#define MSB_GPIO_DATA_OE 7
#define LSB_GPIO_DATA_OE 0
#define AADDR_GPIO_A_DATA_OE (BASE_ADDR_GPIO_A + ADDR_GPIO_DATA_OE)
#define AADDR_GPIO_B_DATA_OE (BASE_ADDR_GPIO_B + ADDR_GPIO_DATA_OE)
#define AADDR_GPIO_C_DATA_OE (BASE_ADDR_GPIO_C + ADDR_GPIO_DATA_OE)
#define REG_GPIO_A_DATA_OE (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_A_DATA_OE))
#define REG_GPIO_B_DATA_OE (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_B_DATA_OE))
#define REG_GPIO_C_DATA_OE (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_C_DATA_OE))

#define ADDR_GPIO_DATA_IN (0x04U)
#define A_GPIO_DATA_IN(ba) ((ba) + ADDR_GPIO_DATA_IN)
#define R_GPIO_DATA_IN(ba) (*(volatile unsigned short *)((unsigned int)A_GPIO_DATA_IN(ba)))
#define RES_GPIO_DATA_IN (0x0U)
#define MSB_GPIO_DATA_IN 7
#define LSB_GPIO_DATA_IN 0
#define AADDR_GPIO_A_DATA_IN (BASE_ADDR_GPIO_A + ADDR_GPIO_DATA_IN)
#define AADDR_GPIO_B_DATA_IN (BASE_ADDR_GPIO_B + ADDR_GPIO_DATA_IN)
#define AADDR_GPIO_C_DATA_IN (BASE_ADDR_GPIO_C + ADDR_GPIO_DATA_IN)
#define REG_GPIO_A_DATA_IN (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_A_DATA_IN))
#define REG_GPIO_B_DATA_IN (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_B_DATA_IN))
#define REG_GPIO_C_DATA_IN (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_C_DATA_IN))

#define ADDR_GPIO_DATA_IE (0x06U)
#define A_GPIO_DATA_IE(ba) ((ba) + ADDR_GPIO_DATA_IE)
#define R_GPIO_DATA_IE(ba) (*(volatile unsigned short *)((unsigned int)A_GPIO_DATA_IE(ba)))
#define RES_GPIO_DATA_IE (0x0U)
#define MSB_GPIO_DATA_IE 7
#define LSB_GPIO_DATA_IE 0
#define AADDR_GPIO_A_DATA_IE (BASE_ADDR_GPIO_A + ADDR_GPIO_DATA_IE)
#define AADDR_GPIO_B_DATA_IE (BASE_ADDR_GPIO_B + ADDR_GPIO_DATA_IE)
#define AADDR_GPIO_C_DATA_IE (BASE_ADDR_GPIO_C + ADDR_GPIO_DATA_IE)
#define REG_GPIO_A_DATA_IE (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_A_DATA_IE))
#define REG_GPIO_B_DATA_IE (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_B_DATA_IE))
#define REG_GPIO_C_DATA_IE (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_C_DATA_IE))

#define ADDR_GPIO_DIRECTION_LOCK (0x08U)
#define A_GPIO_DIRECTION_LOCK(ba) ((ba) + ADDR_GPIO_DIRECTION_LOCK)
#define R_GPIO_DIRECTION_LOCK(ba) (*(volatile unsigned short *)((unsigned int)A_GPIO_DIRECTION_LOCK(ba)))
#define RES_GPIO_DIRECTION_LOCK (0x0U)
#define MSB_GPIO_DIRECTION_LOCK 7
#define LSB_GPIO_DIRECTION_LOCK 0
#define AADDR_GPIO_A_DIRECTION_LOCK (BASE_ADDR_GPIO_A + ADDR_GPIO_DIRECTION_LOCK)
#define AADDR_GPIO_B_DIRECTION_LOCK (BASE_ADDR_GPIO_B + ADDR_GPIO_DIRECTION_LOCK)
#define AADDR_GPIO_C_DIRECTION_LOCK (BASE_ADDR_GPIO_C + ADDR_GPIO_DIRECTION_LOCK)
#define REG_GPIO_A_DIRECTION_LOCK (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_A_DIRECTION_LOCK))
#define REG_GPIO_B_DIRECTION_LOCK (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_B_DIRECTION_LOCK))
#define REG_GPIO_C_DIRECTION_LOCK (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_C_DIRECTION_LOCK))

#define ADDR_GPIO_IRQ_STATUS (0x30U)
#define A_GPIO_IRQ_STATUS(ba) ((ba) + ADDR_GPIO_IRQ_STATUS)
#define R_GPIO_IRQ_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_GPIO_IRQ_STATUS(ba)))
#define RES_GPIO_IRQ_STATUS (0x0U)
#define MSB_GPIO_IRQ_STATUS 15
#define LSB_GPIO_IRQ_STATUS 0
#define AADDR_GPIO_A_IRQ_STATUS (BASE_ADDR_GPIO_A + ADDR_GPIO_IRQ_STATUS)
#define AADDR_GPIO_B_IRQ_STATUS (BASE_ADDR_GPIO_B + ADDR_GPIO_IRQ_STATUS)
#define AADDR_GPIO_C_IRQ_STATUS (BASE_ADDR_GPIO_C + ADDR_GPIO_IRQ_STATUS)
#define REG_GPIO_A_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_A_IRQ_STATUS))
#define REG_GPIO_B_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_B_IRQ_STATUS))
#define REG_GPIO_C_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_C_IRQ_STATUS))

#define ADDR_GPIO_IRQ_MASK (0x34U)
#define A_GPIO_IRQ_MASK(ba) ((ba) + ADDR_GPIO_IRQ_MASK)
#define R_GPIO_IRQ_MASK(ba) (*(volatile unsigned short *)((unsigned int)A_GPIO_IRQ_MASK(ba)))
#define RES_GPIO_IRQ_MASK (0x0U)
#define MSB_GPIO_IRQ_MASK 15
#define LSB_GPIO_IRQ_MASK 0
#define AADDR_GPIO_A_IRQ_MASK (BASE_ADDR_GPIO_A + ADDR_GPIO_IRQ_MASK)
#define AADDR_GPIO_B_IRQ_MASK (BASE_ADDR_GPIO_B + ADDR_GPIO_IRQ_MASK)
#define AADDR_GPIO_C_IRQ_MASK (BASE_ADDR_GPIO_C + ADDR_GPIO_IRQ_MASK)
#define REG_GPIO_A_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_A_IRQ_MASK))
#define REG_GPIO_B_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_B_IRQ_MASK))
#define REG_GPIO_C_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_C_IRQ_MASK))

#define ADDR_GPIO_IRQ_VENABLE (0x38U)
#define A_GPIO_IRQ_VENABLE(ba) ((ba) + ADDR_GPIO_IRQ_VENABLE)
#define R_GPIO_IRQ_VENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_GPIO_IRQ_VENABLE(ba)))
#define RES_GPIO_IRQ_VENABLE (0x0U)
#define MSB_GPIO_IRQ_VENABLE 3
#define LSB_GPIO_IRQ_VENABLE 0
#define AADDR_GPIO_A_IRQ_VENABLE (BASE_ADDR_GPIO_A + ADDR_GPIO_IRQ_VENABLE)
#define AADDR_GPIO_B_IRQ_VENABLE (BASE_ADDR_GPIO_B + ADDR_GPIO_IRQ_VENABLE)
#define AADDR_GPIO_C_IRQ_VENABLE (BASE_ADDR_GPIO_C + ADDR_GPIO_IRQ_VENABLE)
#define REG_GPIO_A_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_A_IRQ_VENABLE))
#define REG_GPIO_B_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_B_IRQ_VENABLE))
#define REG_GPIO_C_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_C_IRQ_VENABLE))

#define ADDR_GPIO_IRQ_VDISABLE (0x3AU)
#define A_GPIO_IRQ_VDISABLE(ba) ((ba) + ADDR_GPIO_IRQ_VDISABLE)
#define R_GPIO_IRQ_VDISABLE(ba) (*(volatile unsigned short *)((unsigned int)A_GPIO_IRQ_VDISABLE(ba)))
#define RES_GPIO_IRQ_VDISABLE (0x0U)
#define MSB_GPIO_IRQ_VDISABLE 3
#define LSB_GPIO_IRQ_VDISABLE 0
#define AADDR_GPIO_A_IRQ_VDISABLE (BASE_ADDR_GPIO_A + ADDR_GPIO_IRQ_VDISABLE)
#define AADDR_GPIO_B_IRQ_VDISABLE (BASE_ADDR_GPIO_B + ADDR_GPIO_IRQ_VDISABLE)
#define AADDR_GPIO_C_IRQ_VDISABLE (BASE_ADDR_GPIO_C + ADDR_GPIO_IRQ_VDISABLE)
#define REG_GPIO_A_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_A_IRQ_VDISABLE))
#define REG_GPIO_B_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_B_IRQ_VDISABLE))
#define REG_GPIO_C_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_C_IRQ_VDISABLE))

#define ADDR_GPIO_IRQ_VMAX (0x3CU)
#define A_GPIO_IRQ_VMAX(ba) ((ba) + ADDR_GPIO_IRQ_VMAX)
#define R_GPIO_IRQ_VMAX(ba) (*(volatile unsigned short *)((unsigned int)A_GPIO_IRQ_VMAX(ba)))
#define RES_GPIO_IRQ_VMAX (0x10U)
#define MSB_GPIO_IRQ_VMAX 4
#define LSB_GPIO_IRQ_VMAX 0
#define AADDR_GPIO_A_IRQ_VMAX (BASE_ADDR_GPIO_A + ADDR_GPIO_IRQ_VMAX)
#define AADDR_GPIO_B_IRQ_VMAX (BASE_ADDR_GPIO_B + ADDR_GPIO_IRQ_VMAX)
#define AADDR_GPIO_C_IRQ_VMAX (BASE_ADDR_GPIO_C + ADDR_GPIO_IRQ_VMAX)
#define REG_GPIO_A_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_A_IRQ_VMAX))
#define REG_GPIO_B_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_B_IRQ_VMAX))
#define REG_GPIO_C_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_C_IRQ_VMAX))

#define ADDR_GPIO_IRQ_VNO (0x3EU)
#define A_GPIO_IRQ_VNO(ba) ((ba) + ADDR_GPIO_IRQ_VNO)
#define R_GPIO_IRQ_VNO(ba) (*(volatile unsigned short *)((unsigned int)A_GPIO_IRQ_VNO(ba)))
#define RES_GPIO_IRQ_VNO (0x10U)
#define MSB_GPIO_IRQ_VNO 4
#define LSB_GPIO_IRQ_VNO 0
#define AADDR_GPIO_A_IRQ_VNO (BASE_ADDR_GPIO_A + ADDR_GPIO_IRQ_VNO)
#define AADDR_GPIO_B_IRQ_VNO (BASE_ADDR_GPIO_B + ADDR_GPIO_IRQ_VNO)
#define AADDR_GPIO_C_IRQ_VNO (BASE_ADDR_GPIO_C + ADDR_GPIO_IRQ_VNO)
#define REG_GPIO_A_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_A_IRQ_VNO))
#define REG_GPIO_B_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_B_IRQ_VNO))
#define REG_GPIO_C_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_GPIO_C_IRQ_VNO))

#endif
