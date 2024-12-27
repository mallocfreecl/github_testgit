#ifndef __WDOG_BF_H__
#define __WDOG_BF_H__

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

#ifndef BASE_ADDR_WDOG
#define BASE_ADDR_WDOG 0x0080U
#endif

#define NUMBER_WDOG 1

typedef enum
{
  WDOG = (int)BASE_ADDR_WDOG
} wdog_num_t;

// Register bit field definitions

/* WDOG_CONTROL */

#define MSK_WDOG_CONTROL_RUN_ENABLE (0x1) /* [0] */
#define SFT_WDOG_CONTROL_RUN_ENABLE (0)
#define LSB_WDOG_CONTROL_RUN_ENABLE (0)
#define MSB_WDOG_CONTROL_RUN_ENABLE (0)
#define BIT_WDOG_CONTROL_RUN_ENABLE (0x1) /* [0] */
#define MSK_WDOG_CONTROL_RESTART (0x1)    /* [1] */
#define SFT_WDOG_CONTROL_RESTART (1)
#define LSB_WDOG_CONTROL_RESTART (1)
#define MSB_WDOG_CONTROL_RESTART (1)
#define BIT_WDOG_CONTROL_RESTART (0x2)   /* [1] */
#define MSK_WDOG_CONTROL_PASSWORD (0xff) /* [15:8] */
#define SFT_WDOG_CONTROL_PASSWORD (8)
#define LSB_WDOG_CONTROL_PASSWORD (8)
#define MSB_WDOG_CONTROL_PASSWORD (15)

typedef struct
{
  unsigned short run_enable : 1; /* [0] */
  unsigned short restart : 1;    /* [1] */
  unsigned short reserved7 : 6;  /* [ 7:2] */
  unsigned short password : 8;   /* [15:8] */
} _PACKED_ wdog_control_bf;

typedef union {
  unsigned short val;
  wdog_control_bf bf;
} _PACKED_ wdog_control_t;

/* WDOG_WINDOW */

#define MSK_WDOG_WINDOW_SIZE (0xf) /* [ 3:0] */
#define SFT_WDOG_WINDOW_SIZE (0)
#define LSB_WDOG_WINDOW_SIZE (0)
#define MSB_WDOG_WINDOW_SIZE (3)
#define MSK_WDOG_WINDOW_ENABLE (0x1) /* [4] */
#define SFT_WDOG_WINDOW_ENABLE (4)
#define LSB_WDOG_WINDOW_ENABLE (4)
#define MSB_WDOG_WINDOW_ENABLE (4)
#define BIT_WDOG_WINDOW_ENABLE (0x10) /* [4] */

typedef struct
{
  unsigned short size : 4;   /* [ 3:0] */
  unsigned short enable : 1; /* [4] */
  unsigned short reserved : 11;
} _PACKED_ wdog_window_bf;

typedef union {
  unsigned short val;
  wdog_window_bf bf;
} _PACKED_ wdog_window_t;

/* WDOG_PRESCALER */

#define MSK_WDOG_PRESCALER (0xff) /* [ 7:0] */

typedef unsigned short wdog_prescaler_t; /* [ 7:0] */

/* WDOG_RELOAD */

#define MSK_WDOG_RELOAD (0xffff) /* [15:0] */

typedef unsigned short wdog_reload_t; /* [15:0] */

/* WDOG_COUNTER */

#define MSK_WDOG_COUNTER (0xffff) /* [15:0] */

typedef unsigned short wdog_counter_t; /* [15:0] */

/* WDOG_IRQ_STATUS */

#define MSK_WDOG_IRQ_STATUS (0x1) /* [0] */

typedef unsigned short wdog_irq_status_t; /* [0] */

/* WDOG_IRQ_MASK */

#define MSK_WDOG_IRQ_MASK (0x1) /* [0] */

typedef unsigned short wdog_irq_mask_t; /* [0] */

/* WDOG_IRQ_VENABLE */

#define MSK_WDOG_IRQ_VENABLE (0x1) /* [0] */

typedef unsigned short wdog_irq_venable_t; /* [0] */

/* WDOG_IRQ_VDISABLE */

#define MSK_WDOG_IRQ_VDISABLE (0x1) /* [0] */

typedef unsigned short wdog_irq_vdisable_t; /* [0] */

/* WDOG_IRQ_VMAX */

#define MSK_WDOG_IRQ_VMAX (0x1) /* [0] */

typedef unsigned short wdog_irq_vmax_t; /* [0] */

/* WDOG_IRQ_VNO */

#define MSK_WDOG_IRQ_VNO (0x1) /* [0] */

typedef unsigned short wdog_irq_vno_t; /* [0] */

/* WDOG */

typedef struct
{
  wdog_control_t control;     /* 0 */
  wdog_window_t window;       /* 2 */
  wdog_prescaler_t prescaler; /* 4 */
  wdog_reload_t reload;       /* 6 */
  wdog_counter_t counter;     /* 8 */
  unsigned short reserved0[19];
  wdog_irq_status_t irq_status; /* 48 */
  unsigned short reserved1[1];
  wdog_irq_mask_t irq_mask; /* 52 */
  unsigned short reserved2[1];
  wdog_irq_venable_t irq_venable;   /* 56 */
  wdog_irq_vdisable_t irq_vdisable; /* 58 */
  wdog_irq_vmax_t irq_vmax;         /* 60 */
  wdog_irq_vno_t irq_vno;           /* 62 */
} _PACKED_ wdog_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_WDOG 0x0080U ... Watchdog Module

#define ADDR_WDOG_CONTROL (0x00U)
#define A_WDOG_CONTROL(ba) ((ba) + ADDR_WDOG_CONTROL)
#define R_WDOG_CONTROL(ba) (*(volatile unsigned short *)((unsigned int)A_WDOG_CONTROL(ba)))
#define RES_WDOG_CONTROL (0x9600U)
#define MSB_WDOG_CONTROL 15
#define LSB_WDOG_CONTROL 0
#define AADDR_WDOG_CONTROL (BASE_ADDR_WDOG + ADDR_WDOG_CONTROL)
#define REG_WDOG_CONTROL (*(volatile unsigned short *)((unsigned int)AADDR_WDOG_CONTROL))

#define ADDR_WDOG_WINDOW (0x02U)
#define A_WDOG_WINDOW(ba) ((ba) + ADDR_WDOG_WINDOW)
#define R_WDOG_WINDOW(ba) (*(volatile unsigned short *)((unsigned int)A_WDOG_WINDOW(ba)))
#define RES_WDOG_WINDOW (0xfU)
#define MSB_WDOG_WINDOW 4
#define LSB_WDOG_WINDOW 0
#define AADDR_WDOG_WINDOW (BASE_ADDR_WDOG + ADDR_WDOG_WINDOW)
#define REG_WDOG_WINDOW (*(volatile unsigned short *)((unsigned int)AADDR_WDOG_WINDOW))

#define ADDR_WDOG_PRESCALER (0x04U)
#define A_WDOG_PRESCALER(ba) ((ba) + ADDR_WDOG_PRESCALER)
#define R_WDOG_PRESCALER(ba) (*(volatile unsigned short *)((unsigned int)A_WDOG_PRESCALER(ba)))
#define RES_WDOG_PRESCALER (0xffU)
#define MSB_WDOG_PRESCALER 7
#define LSB_WDOG_PRESCALER 0
#define AADDR_WDOG_PRESCALER (BASE_ADDR_WDOG + ADDR_WDOG_PRESCALER)
#define REG_WDOG_PRESCALER (*(volatile unsigned short *)((unsigned int)AADDR_WDOG_PRESCALER))

#define ADDR_WDOG_RELOAD (0x06U)
#define A_WDOG_RELOAD(ba) ((ba) + ADDR_WDOG_RELOAD)
#define R_WDOG_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_WDOG_RELOAD(ba)))
#define RES_WDOG_RELOAD (0xffffU)
#define MSB_WDOG_RELOAD 15
#define LSB_WDOG_RELOAD 0
#define AADDR_WDOG_RELOAD (BASE_ADDR_WDOG + ADDR_WDOG_RELOAD)
#define REG_WDOG_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_WDOG_RELOAD))

#define ADDR_WDOG_COUNTER (0x08U)
#define A_WDOG_COUNTER(ba) ((ba) + ADDR_WDOG_COUNTER)
#define R_WDOG_COUNTER(ba) (*(volatile unsigned short *)((unsigned int)A_WDOG_COUNTER(ba)))
#define RES_WDOG_COUNTER (0x0U)
#define MSB_WDOG_COUNTER 15
#define LSB_WDOG_COUNTER 0
#define AADDR_WDOG_COUNTER (BASE_ADDR_WDOG + ADDR_WDOG_COUNTER)
#define REG_WDOG_COUNTER (*(volatile unsigned short *)((unsigned int)AADDR_WDOG_COUNTER))

#define ADDR_WDOG_IRQ_STATUS (0x30U)
#define A_WDOG_IRQ_STATUS(ba) ((ba) + ADDR_WDOG_IRQ_STATUS)
#define R_WDOG_IRQ_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_WDOG_IRQ_STATUS(ba)))
#define RES_WDOG_IRQ_STATUS (0x0U)
#define MSB_WDOG_IRQ_STATUS 0
#define LSB_WDOG_IRQ_STATUS 0
#define AADDR_WDOG_IRQ_STATUS (BASE_ADDR_WDOG + ADDR_WDOG_IRQ_STATUS)
#define REG_WDOG_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_WDOG_IRQ_STATUS))

#define ADDR_WDOG_IRQ_MASK (0x34U)
#define A_WDOG_IRQ_MASK(ba) ((ba) + ADDR_WDOG_IRQ_MASK)
#define R_WDOG_IRQ_MASK(ba) (*(volatile unsigned short *)((unsigned int)A_WDOG_IRQ_MASK(ba)))
#define RES_WDOG_IRQ_MASK (0x0U)
#define MSB_WDOG_IRQ_MASK 0
#define LSB_WDOG_IRQ_MASK 0
#define AADDR_WDOG_IRQ_MASK (BASE_ADDR_WDOG + ADDR_WDOG_IRQ_MASK)
#define REG_WDOG_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_WDOG_IRQ_MASK))

#define ADDR_WDOG_IRQ_VENABLE (0x38U)
#define A_WDOG_IRQ_VENABLE(ba) ((ba) + ADDR_WDOG_IRQ_VENABLE)
#define R_WDOG_IRQ_VENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_WDOG_IRQ_VENABLE(ba)))
#define RES_WDOG_IRQ_VENABLE (0x0U)
#define MSB_WDOG_IRQ_VENABLE 0
#define LSB_WDOG_IRQ_VENABLE 0
#define AADDR_WDOG_IRQ_VENABLE (BASE_ADDR_WDOG + ADDR_WDOG_IRQ_VENABLE)
#define REG_WDOG_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_WDOG_IRQ_VENABLE))

#define ADDR_WDOG_IRQ_VDISABLE (0x3AU)
#define A_WDOG_IRQ_VDISABLE(ba) ((ba) + ADDR_WDOG_IRQ_VDISABLE)
#define R_WDOG_IRQ_VDISABLE(ba) (*(volatile unsigned short *)((unsigned int)A_WDOG_IRQ_VDISABLE(ba)))
#define RES_WDOG_IRQ_VDISABLE (0x0U)
#define MSB_WDOG_IRQ_VDISABLE 0
#define LSB_WDOG_IRQ_VDISABLE 0
#define AADDR_WDOG_IRQ_VDISABLE (BASE_ADDR_WDOG + ADDR_WDOG_IRQ_VDISABLE)
#define REG_WDOG_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_WDOG_IRQ_VDISABLE))

#define ADDR_WDOG_IRQ_VMAX (0x3CU)
#define A_WDOG_IRQ_VMAX(ba) ((ba) + ADDR_WDOG_IRQ_VMAX)
#define R_WDOG_IRQ_VMAX(ba) (*(volatile unsigned short *)((unsigned int)A_WDOG_IRQ_VMAX(ba)))
#define RES_WDOG_IRQ_VMAX (0x1U)
#define MSB_WDOG_IRQ_VMAX 0
#define LSB_WDOG_IRQ_VMAX 0
#define AADDR_WDOG_IRQ_VMAX (BASE_ADDR_WDOG + ADDR_WDOG_IRQ_VMAX)
#define REG_WDOG_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_WDOG_IRQ_VMAX))

#define ADDR_WDOG_IRQ_VNO (0x3EU)
#define A_WDOG_IRQ_VNO(ba) ((ba) + ADDR_WDOG_IRQ_VNO)
#define R_WDOG_IRQ_VNO(ba) (*(volatile unsigned short *)((unsigned int)A_WDOG_IRQ_VNO(ba)))
#define RES_WDOG_IRQ_VNO (0x1U)
#define MSB_WDOG_IRQ_VNO 0
#define LSB_WDOG_IRQ_VNO 0
#define AADDR_WDOG_IRQ_VNO (BASE_ADDR_WDOG + ADDR_WDOG_IRQ_VNO)
#define REG_WDOG_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_WDOG_IRQ_VNO))

#endif
