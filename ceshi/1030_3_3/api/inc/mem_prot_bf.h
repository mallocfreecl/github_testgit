#ifndef __MEM_PROT_BF_H__
#define __MEM_PROT_BF_H__

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

#ifndef BASE_ADDR_MEM_PROT
#define BASE_ADDR_MEM_PROT 0x00C0U
#endif

#define NUMBER_MEM_PROT 1

typedef enum
{
  MEM_PROT = (int)BASE_ADDR_MEM_PROT
} mem_prot_num_t;

// Register bit field definitions

/* MEM_PROT_EXEC_ENABLE */

#define MSK_MEM_PROT_EXEC_ENABLE (0xffff) /* [15:0] */

typedef unsigned short mem_prot_exec_enable_t; /* [15:0] */

/* MEM_PROT_STACK_ENABLE */

#define MSK_MEM_PROT_STACK_ENABLE (0xffff) /* [15:0] */

typedef unsigned short mem_prot_stack_enable_t; /* [15:0] */

/* MEM_PROT_SRAM_WR_ENABLE */

#define MSK_MEM_PROT_SRAM_WR_ENABLE (0xffff) /* [15:0] */

typedef unsigned short mem_prot_sram_wr_enable_t; /* [15:0] */

/* MEM_PROT_ACCESS_ADDR */

#define MSK_MEM_PROT_ACCESS_ADDR (0xffff) /* [15:0] */

typedef unsigned short mem_prot_access_addr_t; /* [15:0] */

/* MEM_PROT_ACCESS_PC */

#define MSK_MEM_PROT_ACCESS_PC (0xffff) /* [15:0] */

typedef unsigned short mem_prot_access_pc_t; /* [15:0] */

/* MEM_PROT_ACCESS_TYPE */

#define MSK_MEM_PROT_ACCESS_TYPE_TYPE (0x7) /* [ 2:0] */
#define SFT_MEM_PROT_ACCESS_TYPE_TYPE (0)
#define LSB_MEM_PROT_ACCESS_TYPE_TYPE (0)
#define MSB_MEM_PROT_ACCESS_TYPE_TYPE (2)
#define MSK_MEM_PROT_ACCESS_TYPE_BUS (0x7) /* [ 6:4] */
#define SFT_MEM_PROT_ACCESS_TYPE_BUS (4)
#define LSB_MEM_PROT_ACCESS_TYPE_BUS (4)
#define MSB_MEM_PROT_ACCESS_TYPE_BUS (6)

typedef struct
{
  unsigned short type : 3;      /* [ 2:0] */
  unsigned short reserved3 : 1; /* [3] */
  unsigned short bus : 3;       /* [ 6:4] */
  unsigned short reserved : 9;
} _PACKED_ mem_prot_access_type_bf;

typedef union {
  unsigned short val;
  mem_prot_access_type_bf bf;
} _PACKED_ mem_prot_access_type_t;

/* MEM_PROT_ACCESS_CLEAR */

#define MSK_MEM_PROT_ACCESS_CLEAR (0x1) /* [0] */

typedef unsigned short mem_prot_access_clear_t; /* [0] */

/* MEM_PROT_SYSROM_RD_ENABLE */

#define MSK_MEM_PROT_SYSROM_RD_ENABLE (0xffff) /* [15:0] */

typedef unsigned short mem_prot_sysrom_rd_enable_t; /* [15:0] */

/* MEM_PROT_IRQ_STATUS */

#define MSK_MEM_PROT_IRQ_STATUS_EVT_UNDEFINED (0x1) /* [0] */
#define SFT_MEM_PROT_IRQ_STATUS_EVT_UNDEFINED (0)
#define LSB_MEM_PROT_IRQ_STATUS_EVT_UNDEFINED (0)
#define MSB_MEM_PROT_IRQ_STATUS_EVT_UNDEFINED (0)
#define BIT_MEM_PROT_IRQ_STATUS_EVT_UNDEFINED (0x1)   /* [0] */
#define MSK_MEM_PROT_IRQ_STATUS_EVT_DMISALIGNED (0x1) /* [1] */
#define SFT_MEM_PROT_IRQ_STATUS_EVT_DMISALIGNED (1)
#define LSB_MEM_PROT_IRQ_STATUS_EVT_DMISALIGNED (1)
#define MSB_MEM_PROT_IRQ_STATUS_EVT_DMISALIGNED (1)
#define BIT_MEM_PROT_IRQ_STATUS_EVT_DMISALIGNED (0x2) /* [1] */

typedef struct
{
  unsigned short evt_undefined : 1;   /* [0] */
  unsigned short evt_dmisaligned : 1; /* [1] */
  unsigned short reserved : 14;
} _PACKED_ mem_prot_irq_status_bf;

typedef union {
  unsigned short val;
  mem_prot_irq_status_bf bf;
} _PACKED_ mem_prot_irq_status_t;

/* MEM_PROT_IRQ_MASK */

#define MSK_MEM_PROT_IRQ_MASK (0x3) /* [ 1:0] */

typedef unsigned short mem_prot_irq_mask_t; /* [ 1:0] */

/* MEM_PROT_IRQ_VENABLE */

#define MSK_MEM_PROT_IRQ_VENABLE (0x1) /* [0] */

typedef unsigned short mem_prot_irq_venable_t; /* [0] */

/* MEM_PROT_IRQ_VDISABLE */

#define MSK_MEM_PROT_IRQ_VDISABLE (0x1) /* [0] */

typedef unsigned short mem_prot_irq_vdisable_t; /* [0] */

/* MEM_PROT_IRQ_VMAX */

#define MSK_MEM_PROT_IRQ_VMAX (0x3) /* [ 1:0] */

typedef unsigned short mem_prot_irq_vmax_t; /* [ 1:0] */

/* MEM_PROT_IRQ_VNO */

#define MSK_MEM_PROT_IRQ_VNO (0x3) /* [ 1:0] */

typedef unsigned short mem_prot_irq_vno_t; /* [ 1:0] */

/* MEM_PROT */

typedef struct
{
  mem_prot_exec_enable_t exec_enable_0;     /* 0 */
  mem_prot_exec_enable_t exec_enable_1;     /* 2 */
  mem_prot_exec_enable_t exec_enable_2;     /* 4 */
  mem_prot_exec_enable_t exec_enable_3;     /* 6 */
  mem_prot_stack_enable_t stack_enable;     /* 8 */
  mem_prot_sram_wr_enable_t sram_wr_enable; /* 10 */
  unsigned short reserved0[2];
  mem_prot_access_addr_t access_addr;   /* 16 */
  mem_prot_access_pc_t access_pc;       /* 18 */
  mem_prot_access_type_t access_type;   /* 20 */
  mem_prot_access_clear_t access_clear; /* 22 */
  unsigned short reserved1[4];
  mem_prot_sysrom_rd_enable_t sysrom_rd_enable; /* 32 */
  unsigned short reserved2[7];
  mem_prot_irq_status_t irq_status; /* 48 */
  unsigned short reserved3[1];
  mem_prot_irq_mask_t irq_mask; /* 52 */
  unsigned short reserved4[1];
  mem_prot_irq_venable_t irq_venable;   /* 56 */
  mem_prot_irq_vdisable_t irq_vdisable; /* 58 */
  mem_prot_irq_vmax_t irq_vmax;         /* 60 */
  mem_prot_irq_vno_t irq_vno;           /* 62 */
} _PACKED_ mem_prot_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_MEM_PROT 0x00C0U ... Memory Protection Module

#define ADDR_MEM_PROT_EXEC_ENABLE_0 (0x00U)
#define A_MEM_PROT_EXEC_ENABLE_0(ba) ((ba) + ADDR_MEM_PROT_EXEC_ENABLE_0)
#define R_MEM_PROT_EXEC_ENABLE_0(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_EXEC_ENABLE_0(ba)))
#define RES_MEM_PROT_EXEC_ENABLE_0 (0xffffU)
#define MSB_MEM_PROT_EXEC_ENABLE_0 15
#define LSB_MEM_PROT_EXEC_ENABLE_0 0
#define AADDR_MEM_PROT_EXEC_ENABLE_0 (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_EXEC_ENABLE_0)
#define REG_MEM_PROT_EXEC_ENABLE_0 (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_EXEC_ENABLE_0))

#define ADDR_MEM_PROT_EXEC_ENABLE_1 (0x02U)
#define A_MEM_PROT_EXEC_ENABLE_1(ba) ((ba) + ADDR_MEM_PROT_EXEC_ENABLE_1)
#define R_MEM_PROT_EXEC_ENABLE_1(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_EXEC_ENABLE_1(ba)))
#define RES_MEM_PROT_EXEC_ENABLE_1 (0xffffU)
#define MSB_MEM_PROT_EXEC_ENABLE_1 15
#define LSB_MEM_PROT_EXEC_ENABLE_1 0
#define AADDR_MEM_PROT_EXEC_ENABLE_1 (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_EXEC_ENABLE_1)
#define REG_MEM_PROT_EXEC_ENABLE_1 (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_EXEC_ENABLE_1))

#define ADDR_MEM_PROT_EXEC_ENABLE_2 (0x04U)
#define A_MEM_PROT_EXEC_ENABLE_2(ba) ((ba) + ADDR_MEM_PROT_EXEC_ENABLE_2)
#define R_MEM_PROT_EXEC_ENABLE_2(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_EXEC_ENABLE_2(ba)))
#define RES_MEM_PROT_EXEC_ENABLE_2 (0xffffU)
#define MSB_MEM_PROT_EXEC_ENABLE_2 15
#define LSB_MEM_PROT_EXEC_ENABLE_2 0
#define AADDR_MEM_PROT_EXEC_ENABLE_2 (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_EXEC_ENABLE_2)
#define REG_MEM_PROT_EXEC_ENABLE_2 (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_EXEC_ENABLE_2))

#define ADDR_MEM_PROT_EXEC_ENABLE_3 (0x06U)
#define A_MEM_PROT_EXEC_ENABLE_3(ba) ((ba) + ADDR_MEM_PROT_EXEC_ENABLE_3)
#define R_MEM_PROT_EXEC_ENABLE_3(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_EXEC_ENABLE_3(ba)))
#define RES_MEM_PROT_EXEC_ENABLE_3 (0xffffU)
#define MSB_MEM_PROT_EXEC_ENABLE_3 15
#define LSB_MEM_PROT_EXEC_ENABLE_3 0
#define AADDR_MEM_PROT_EXEC_ENABLE_3 (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_EXEC_ENABLE_3)
#define REG_MEM_PROT_EXEC_ENABLE_3 (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_EXEC_ENABLE_3))

#define ADDR_MEM_PROT_STACK_ENABLE (0x08U)
#define A_MEM_PROT_STACK_ENABLE(ba) ((ba) + ADDR_MEM_PROT_STACK_ENABLE)
#define R_MEM_PROT_STACK_ENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_STACK_ENABLE(ba)))
#define RES_MEM_PROT_STACK_ENABLE (0xffffU)
#define MSB_MEM_PROT_STACK_ENABLE 15
#define LSB_MEM_PROT_STACK_ENABLE 0
#define AADDR_MEM_PROT_STACK_ENABLE (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_STACK_ENABLE)
#define REG_MEM_PROT_STACK_ENABLE (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_STACK_ENABLE))

#define ADDR_MEM_PROT_SRAM_WR_ENABLE (0x0AU)
#define A_MEM_PROT_SRAM_WR_ENABLE(ba) ((ba) + ADDR_MEM_PROT_SRAM_WR_ENABLE)
#define R_MEM_PROT_SRAM_WR_ENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_SRAM_WR_ENABLE(ba)))
#define RES_MEM_PROT_SRAM_WR_ENABLE (0xffffU)
#define MSB_MEM_PROT_SRAM_WR_ENABLE 15
#define LSB_MEM_PROT_SRAM_WR_ENABLE 0
#define AADDR_MEM_PROT_SRAM_WR_ENABLE (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_SRAM_WR_ENABLE)
#define REG_MEM_PROT_SRAM_WR_ENABLE (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_SRAM_WR_ENABLE))

#define ADDR_MEM_PROT_ACCESS_ADDR (0x10U)
#define A_MEM_PROT_ACCESS_ADDR(ba) ((ba) + ADDR_MEM_PROT_ACCESS_ADDR)
#define R_MEM_PROT_ACCESS_ADDR(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_ACCESS_ADDR(ba)))
#define RES_MEM_PROT_ACCESS_ADDR (0x0U)
#define MSB_MEM_PROT_ACCESS_ADDR 15
#define LSB_MEM_PROT_ACCESS_ADDR 0
#define AADDR_MEM_PROT_ACCESS_ADDR (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_ACCESS_ADDR)
#define REG_MEM_PROT_ACCESS_ADDR (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_ACCESS_ADDR))

#define ADDR_MEM_PROT_ACCESS_PC (0x12U)
#define A_MEM_PROT_ACCESS_PC(ba) ((ba) + ADDR_MEM_PROT_ACCESS_PC)
#define R_MEM_PROT_ACCESS_PC(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_ACCESS_PC(ba)))
#define RES_MEM_PROT_ACCESS_PC (0x0U)
#define MSB_MEM_PROT_ACCESS_PC 15
#define LSB_MEM_PROT_ACCESS_PC 0
#define AADDR_MEM_PROT_ACCESS_PC (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_ACCESS_PC)
#define REG_MEM_PROT_ACCESS_PC (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_ACCESS_PC))

#define ADDR_MEM_PROT_ACCESS_TYPE (0x14U)
#define A_MEM_PROT_ACCESS_TYPE(ba) ((ba) + ADDR_MEM_PROT_ACCESS_TYPE)
#define R_MEM_PROT_ACCESS_TYPE(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_ACCESS_TYPE(ba)))
#define RES_MEM_PROT_ACCESS_TYPE (0x77U)
#define MSB_MEM_PROT_ACCESS_TYPE 6
#define LSB_MEM_PROT_ACCESS_TYPE 0
#define AADDR_MEM_PROT_ACCESS_TYPE (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_ACCESS_TYPE)
#define REG_MEM_PROT_ACCESS_TYPE (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_ACCESS_TYPE))

#define ADDR_MEM_PROT_ACCESS_CLEAR (0x16U)
#define A_MEM_PROT_ACCESS_CLEAR(ba) ((ba) + ADDR_MEM_PROT_ACCESS_CLEAR)
#define R_MEM_PROT_ACCESS_CLEAR(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_ACCESS_CLEAR(ba)))
#define RES_MEM_PROT_ACCESS_CLEAR (0x0U)
#define MSB_MEM_PROT_ACCESS_CLEAR 0
#define LSB_MEM_PROT_ACCESS_CLEAR 0
#define AADDR_MEM_PROT_ACCESS_CLEAR (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_ACCESS_CLEAR)
#define REG_MEM_PROT_ACCESS_CLEAR (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_ACCESS_CLEAR))

#define ADDR_MEM_PROT_SYSROM_RD_ENABLE (0x20U)
#define A_MEM_PROT_SYSROM_RD_ENABLE(ba) ((ba) + ADDR_MEM_PROT_SYSROM_RD_ENABLE)
#define R_MEM_PROT_SYSROM_RD_ENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_SYSROM_RD_ENABLE(ba)))
#define RES_MEM_PROT_SYSROM_RD_ENABLE (0xffffU)
#define MSB_MEM_PROT_SYSROM_RD_ENABLE 15
#define LSB_MEM_PROT_SYSROM_RD_ENABLE 0
#define AADDR_MEM_PROT_SYSROM_RD_ENABLE (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_SYSROM_RD_ENABLE)
#define REG_MEM_PROT_SYSROM_RD_ENABLE (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_SYSROM_RD_ENABLE))

#define ADDR_MEM_PROT_IRQ_STATUS (0x30U)
#define A_MEM_PROT_IRQ_STATUS(ba) ((ba) + ADDR_MEM_PROT_IRQ_STATUS)
#define R_MEM_PROT_IRQ_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_IRQ_STATUS(ba)))
#define RES_MEM_PROT_IRQ_STATUS (0x0U)
#define MSB_MEM_PROT_IRQ_STATUS 1
#define LSB_MEM_PROT_IRQ_STATUS 0
#define AADDR_MEM_PROT_IRQ_STATUS (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_IRQ_STATUS)
#define REG_MEM_PROT_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_IRQ_STATUS))

#define ADDR_MEM_PROT_IRQ_MASK (0x34U)
#define A_MEM_PROT_IRQ_MASK(ba) ((ba) + ADDR_MEM_PROT_IRQ_MASK)
#define R_MEM_PROT_IRQ_MASK(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_IRQ_MASK(ba)))
#define RES_MEM_PROT_IRQ_MASK (0x0U)
#define MSB_MEM_PROT_IRQ_MASK 1
#define LSB_MEM_PROT_IRQ_MASK 0
#define AADDR_MEM_PROT_IRQ_MASK (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_IRQ_MASK)
#define REG_MEM_PROT_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_IRQ_MASK))

#define ADDR_MEM_PROT_IRQ_VENABLE (0x38U)
#define A_MEM_PROT_IRQ_VENABLE(ba) ((ba) + ADDR_MEM_PROT_IRQ_VENABLE)
#define R_MEM_PROT_IRQ_VENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_IRQ_VENABLE(ba)))
#define RES_MEM_PROT_IRQ_VENABLE (0x0U)
#define MSB_MEM_PROT_IRQ_VENABLE 0
#define LSB_MEM_PROT_IRQ_VENABLE 0
#define AADDR_MEM_PROT_IRQ_VENABLE (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_IRQ_VENABLE)
#define REG_MEM_PROT_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_IRQ_VENABLE))

#define ADDR_MEM_PROT_IRQ_VDISABLE (0x3AU)
#define A_MEM_PROT_IRQ_VDISABLE(ba) ((ba) + ADDR_MEM_PROT_IRQ_VDISABLE)
#define R_MEM_PROT_IRQ_VDISABLE(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_IRQ_VDISABLE(ba)))
#define RES_MEM_PROT_IRQ_VDISABLE (0x0U)
#define MSB_MEM_PROT_IRQ_VDISABLE 0
#define LSB_MEM_PROT_IRQ_VDISABLE 0
#define AADDR_MEM_PROT_IRQ_VDISABLE (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_IRQ_VDISABLE)
#define REG_MEM_PROT_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_IRQ_VDISABLE))

#define ADDR_MEM_PROT_IRQ_VMAX (0x3CU)
#define A_MEM_PROT_IRQ_VMAX(ba) ((ba) + ADDR_MEM_PROT_IRQ_VMAX)
#define R_MEM_PROT_IRQ_VMAX(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_IRQ_VMAX(ba)))
#define RES_MEM_PROT_IRQ_VMAX (0x2U)
#define MSB_MEM_PROT_IRQ_VMAX 1
#define LSB_MEM_PROT_IRQ_VMAX 0
#define AADDR_MEM_PROT_IRQ_VMAX (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_IRQ_VMAX)
#define REG_MEM_PROT_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_IRQ_VMAX))

#define ADDR_MEM_PROT_IRQ_VNO (0x3EU)
#define A_MEM_PROT_IRQ_VNO(ba) ((ba) + ADDR_MEM_PROT_IRQ_VNO)
#define R_MEM_PROT_IRQ_VNO(ba) (*(volatile unsigned short *)((unsigned int)A_MEM_PROT_IRQ_VNO(ba)))
#define RES_MEM_PROT_IRQ_VNO (0x2U)
#define MSB_MEM_PROT_IRQ_VNO 1
#define LSB_MEM_PROT_IRQ_VNO 0
#define AADDR_MEM_PROT_IRQ_VNO (BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_IRQ_VNO)
#define REG_MEM_PROT_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_MEM_PROT_IRQ_VNO))

#endif
