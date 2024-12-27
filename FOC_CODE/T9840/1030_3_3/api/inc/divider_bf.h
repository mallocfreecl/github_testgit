#ifndef __DIVIDER_BF_H__
#define __DIVIDER_BF_H__

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

#ifndef BASE_ADDR_DIVIDER
#define BASE_ADDR_DIVIDER 0x0140U
#endif

#define NUMBER_DIVIDER 1

typedef enum
{
  DIVIDER = (int)BASE_ADDR_DIVIDER
} divider_num_t;

// Register bit field definitions

/* DIVIDER_OP1 */

#define MSK_DIVIDER_OP1 (0xffff) /* [15:0] */

typedef unsigned short divider_op1_t; /* [15:0] */

/* DIVIDER_OP2 */

#define MSK_DIVIDER_OP2 (0xffff) /* [15:0] */

typedef unsigned short divider_op2_t; /* [15:0] */

/* DIVIDER_OP2S */

#define MSK_DIVIDER_OP2S (0xffff) /* [15:0] */

typedef unsigned short divider_op2s_t; /* [15:0] */

/* DIVIDER_RESULT */

#define MSK_DIVIDER_RESULT (0xffff) /* [15:0] */

typedef unsigned short divider_result_t; /* [15:0] */

/* DIVIDER_REMAINDER */

#define MSK_DIVIDER_REMAINDER (0xffff) /* [15:0] */

typedef unsigned short divider_remainder_t; /* [15:0] */

/* DIVIDER_IRQ_STATUS */

#define MSK_DIVIDER_IRQ_STATUS (0x1) /* [0] */

typedef unsigned short divider_irq_status_t; /* [0] */

/* DIVIDER_IRQ_MASK */

#define MSK_DIVIDER_IRQ_MASK (0x1) /* [0] */

typedef unsigned short divider_irq_mask_t; /* [0] */

/* DIVIDER_IRQ_VENABLE */

#define MSK_DIVIDER_IRQ_VENABLE (0x1) /* [0] */

typedef unsigned short divider_irq_venable_t; /* [0] */

/* DIVIDER_IRQ_VDISABLE */

#define MSK_DIVIDER_IRQ_VDISABLE (0x1) /* [0] */

typedef unsigned short divider_irq_vdisable_t; /* [0] */

/* DIVIDER_IRQ_VMAX */

#define MSK_DIVIDER_IRQ_VMAX (0x1) /* [0] */

typedef unsigned short divider_irq_vmax_t; /* [0] */

/* DIVIDER_IRQ_VNO */

#define MSK_DIVIDER_IRQ_VNO (0x1) /* [0] */

typedef unsigned short divider_irq_vno_t; /* [0] */

/* DIVIDER */

typedef struct
{
  divider_op1_t op1lo;           /* 0 */
  divider_op1_t op1hi;           /* 2 */
  divider_op2_t op2;             /* 4 */
  divider_op2s_t op2s;           /* 6 */
  divider_result_t resultlo;     /* 8 */
  divider_result_t resulthi;     /* 10 */
  divider_remainder_t remainder; /* 12 */
  unsigned short reserved0[17];
  divider_irq_status_t irq_status; /* 48 */
  unsigned short reserved1[1];
  divider_irq_mask_t irq_mask; /* 52 */
  unsigned short reserved2[1];
  divider_irq_venable_t irq_venable;   /* 56 */
  divider_irq_vdisable_t irq_vdisable; /* 58 */
  divider_irq_vmax_t irq_vmax;         /* 60 */
  divider_irq_vno_t irq_vno;           /* 62 */
} _PACKED_ divider_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_DIVIDER 0x0140U ... Divider Module

#define ADDR_DIVIDER_OP1LO (0x00U)
#define A_DIVIDER_OP1LO(ba) ((ba) + ADDR_DIVIDER_OP1LO)
#define R_DIVIDER_OP1LO(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_OP1LO(ba)))
#define RES_DIVIDER_OP1LO (0x0U)
#define MSB_DIVIDER_OP1LO 15
#define LSB_DIVIDER_OP1LO 0
#define AADDR_DIVIDER_OP1LO (BASE_ADDR_DIVIDER + ADDR_DIVIDER_OP1LO)
#define REG_DIVIDER_OP1LO (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_OP1LO))

#define ADDR_DIVIDER_OP1HI (0x02U)
#define A_DIVIDER_OP1HI(ba) ((ba) + ADDR_DIVIDER_OP1HI)
#define R_DIVIDER_OP1HI(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_OP1HI(ba)))
#define RES_DIVIDER_OP1HI (0x0U)
#define MSB_DIVIDER_OP1HI 15
#define LSB_DIVIDER_OP1HI 0
#define AADDR_DIVIDER_OP1HI (BASE_ADDR_DIVIDER + ADDR_DIVIDER_OP1HI)
#define REG_DIVIDER_OP1HI (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_OP1HI))

#define ADDR_DIVIDER_OP2 (0x04U)
#define A_DIVIDER_OP2(ba) ((ba) + ADDR_DIVIDER_OP2)
#define R_DIVIDER_OP2(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_OP2(ba)))
#define RES_DIVIDER_OP2 (0x0U)
#define MSB_DIVIDER_OP2 15
#define LSB_DIVIDER_OP2 0
#define AADDR_DIVIDER_OP2 (BASE_ADDR_DIVIDER + ADDR_DIVIDER_OP2)
#define REG_DIVIDER_OP2 (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_OP2))

#define ADDR_DIVIDER_OP2S (0x06U)
#define A_DIVIDER_OP2S(ba) ((ba) + ADDR_DIVIDER_OP2S)
#define R_DIVIDER_OP2S(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_OP2S(ba)))
#define RES_DIVIDER_OP2S (0x0U)
#define MSB_DIVIDER_OP2S 15
#define LSB_DIVIDER_OP2S 0
#define AADDR_DIVIDER_OP2S (BASE_ADDR_DIVIDER + ADDR_DIVIDER_OP2S)
#define REG_DIVIDER_OP2S (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_OP2S))

#define ADDR_DIVIDER_RESULTLO (0x08U)
#define A_DIVIDER_RESULTLO(ba) ((ba) + ADDR_DIVIDER_RESULTLO)
#define R_DIVIDER_RESULTLO(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_RESULTLO(ba)))
#define RES_DIVIDER_RESULTLO (0x0U)
#define MSB_DIVIDER_RESULTLO 15
#define LSB_DIVIDER_RESULTLO 0
#define AADDR_DIVIDER_RESULTLO (BASE_ADDR_DIVIDER + ADDR_DIVIDER_RESULTLO)
#define REG_DIVIDER_RESULTLO (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_RESULTLO))

#define ADDR_DIVIDER_RESULTHI (0x0AU)
#define A_DIVIDER_RESULTHI(ba) ((ba) + ADDR_DIVIDER_RESULTHI)
#define R_DIVIDER_RESULTHI(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_RESULTHI(ba)))
#define RES_DIVIDER_RESULTHI (0x0U)
#define MSB_DIVIDER_RESULTHI 15
#define LSB_DIVIDER_RESULTHI 0
#define AADDR_DIVIDER_RESULTHI (BASE_ADDR_DIVIDER + ADDR_DIVIDER_RESULTHI)
#define REG_DIVIDER_RESULTHI (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_RESULTHI))

#define ADDR_DIVIDER_REMAINDER (0x0CU)
#define A_DIVIDER_REMAINDER(ba) ((ba) + ADDR_DIVIDER_REMAINDER)
#define R_DIVIDER_REMAINDER(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_REMAINDER(ba)))
#define RES_DIVIDER_REMAINDER (0x0U)
#define MSB_DIVIDER_REMAINDER 15
#define LSB_DIVIDER_REMAINDER 0
#define AADDR_DIVIDER_REMAINDER (BASE_ADDR_DIVIDER + ADDR_DIVIDER_REMAINDER)
#define REG_DIVIDER_REMAINDER (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_REMAINDER))

#define ADDR_DIVIDER_IRQ_STATUS (0x30U)
#define A_DIVIDER_IRQ_STATUS(ba) ((ba) + ADDR_DIVIDER_IRQ_STATUS)
#define R_DIVIDER_IRQ_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_IRQ_STATUS(ba)))
#define RES_DIVIDER_IRQ_STATUS (0x0U)
#define MSB_DIVIDER_IRQ_STATUS 0
#define LSB_DIVIDER_IRQ_STATUS 0
#define AADDR_DIVIDER_IRQ_STATUS (BASE_ADDR_DIVIDER + ADDR_DIVIDER_IRQ_STATUS)
#define REG_DIVIDER_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_IRQ_STATUS))

#define ADDR_DIVIDER_IRQ_MASK (0x34U)
#define A_DIVIDER_IRQ_MASK(ba) ((ba) + ADDR_DIVIDER_IRQ_MASK)
#define R_DIVIDER_IRQ_MASK(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_IRQ_MASK(ba)))
#define RES_DIVIDER_IRQ_MASK (0x0U)
#define MSB_DIVIDER_IRQ_MASK 0
#define LSB_DIVIDER_IRQ_MASK 0
#define AADDR_DIVIDER_IRQ_MASK (BASE_ADDR_DIVIDER + ADDR_DIVIDER_IRQ_MASK)
#define REG_DIVIDER_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_IRQ_MASK))

#define ADDR_DIVIDER_IRQ_VENABLE (0x38U)
#define A_DIVIDER_IRQ_VENABLE(ba) ((ba) + ADDR_DIVIDER_IRQ_VENABLE)
#define R_DIVIDER_IRQ_VENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_IRQ_VENABLE(ba)))
#define RES_DIVIDER_IRQ_VENABLE (0x0U)
#define MSB_DIVIDER_IRQ_VENABLE 0
#define LSB_DIVIDER_IRQ_VENABLE 0
#define AADDR_DIVIDER_IRQ_VENABLE (BASE_ADDR_DIVIDER + ADDR_DIVIDER_IRQ_VENABLE)
#define REG_DIVIDER_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_IRQ_VENABLE))

#define ADDR_DIVIDER_IRQ_VDISABLE (0x3AU)
#define A_DIVIDER_IRQ_VDISABLE(ba) ((ba) + ADDR_DIVIDER_IRQ_VDISABLE)
#define R_DIVIDER_IRQ_VDISABLE(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_IRQ_VDISABLE(ba)))
#define RES_DIVIDER_IRQ_VDISABLE (0x0U)
#define MSB_DIVIDER_IRQ_VDISABLE 0
#define LSB_DIVIDER_IRQ_VDISABLE 0
#define AADDR_DIVIDER_IRQ_VDISABLE (BASE_ADDR_DIVIDER + ADDR_DIVIDER_IRQ_VDISABLE)
#define REG_DIVIDER_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_IRQ_VDISABLE))

#define ADDR_DIVIDER_IRQ_VMAX (0x3CU)
#define A_DIVIDER_IRQ_VMAX(ba) ((ba) + ADDR_DIVIDER_IRQ_VMAX)
#define R_DIVIDER_IRQ_VMAX(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_IRQ_VMAX(ba)))
#define RES_DIVIDER_IRQ_VMAX (0x1U)
#define MSB_DIVIDER_IRQ_VMAX 0
#define LSB_DIVIDER_IRQ_VMAX 0
#define AADDR_DIVIDER_IRQ_VMAX (BASE_ADDR_DIVIDER + ADDR_DIVIDER_IRQ_VMAX)
#define REG_DIVIDER_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_IRQ_VMAX))

#define ADDR_DIVIDER_IRQ_VNO (0x3EU)
#define A_DIVIDER_IRQ_VNO(ba) ((ba) + ADDR_DIVIDER_IRQ_VNO)
#define R_DIVIDER_IRQ_VNO(ba) (*(volatile unsigned short *)((unsigned int)A_DIVIDER_IRQ_VNO(ba)))
#define RES_DIVIDER_IRQ_VNO (0x1U)
#define MSB_DIVIDER_IRQ_VNO 0
#define LSB_DIVIDER_IRQ_VNO 0
#define AADDR_DIVIDER_IRQ_VNO (BASE_ADDR_DIVIDER + ADDR_DIVIDER_IRQ_VNO)
#define REG_DIVIDER_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_DIVIDER_IRQ_VNO))

#endif
