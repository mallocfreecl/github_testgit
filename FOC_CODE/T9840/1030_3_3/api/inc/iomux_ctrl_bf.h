#ifndef __IOMUX_CTRL_BF_H__
#define __IOMUX_CTRL_BF_H__

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

#ifndef BASE_ADDR_IOMUX_CTRL
#define BASE_ADDR_IOMUX_CTRL 0x0200U
#endif

#define NUMBER_IOMUX_CTRL 1

typedef enum
{
  IOMUX_CTRL = (int)BASE_ADDR_IOMUX_CTRL
} iomux_ctrl_num_t;

// Register bit field definitions

/* IOMUX_CTRL_PAB_IO_SEL */

#define MSK_IOMUX_CTRL_PAB_IO_SEL_SEL_0 (0x3) /* [ 1:0] */
#define SFT_IOMUX_CTRL_PAB_IO_SEL_SEL_0 (0)
#define LSB_IOMUX_CTRL_PAB_IO_SEL_SEL_0 (0)
#define MSB_IOMUX_CTRL_PAB_IO_SEL_SEL_0 (1)
#define MSK_IOMUX_CTRL_PAB_IO_SEL_SEL_1 (0x3) /* [ 3:2] */
#define SFT_IOMUX_CTRL_PAB_IO_SEL_SEL_1 (2)
#define LSB_IOMUX_CTRL_PAB_IO_SEL_SEL_1 (2)
#define MSB_IOMUX_CTRL_PAB_IO_SEL_SEL_1 (3)
#define MSK_IOMUX_CTRL_PAB_IO_SEL_SEL_2 (0x3) /* [ 5:4] */
#define SFT_IOMUX_CTRL_PAB_IO_SEL_SEL_2 (4)
#define LSB_IOMUX_CTRL_PAB_IO_SEL_SEL_2 (4)
#define MSB_IOMUX_CTRL_PAB_IO_SEL_SEL_2 (5)
#define MSK_IOMUX_CTRL_PAB_IO_SEL_SEL_3 (0x3) /* [ 7:6] */
#define SFT_IOMUX_CTRL_PAB_IO_SEL_SEL_3 (6)
#define LSB_IOMUX_CTRL_PAB_IO_SEL_SEL_3 (6)
#define MSB_IOMUX_CTRL_PAB_IO_SEL_SEL_3 (7)
#define MSK_IOMUX_CTRL_PAB_IO_SEL_SEL_4 (0x3) /* [ 9:8] */
#define SFT_IOMUX_CTRL_PAB_IO_SEL_SEL_4 (8)
#define LSB_IOMUX_CTRL_PAB_IO_SEL_SEL_4 (8)
#define MSB_IOMUX_CTRL_PAB_IO_SEL_SEL_4 (9)
#define MSK_IOMUX_CTRL_PAB_IO_SEL_SEL_5 (0x3) /* [11:10] */
#define SFT_IOMUX_CTRL_PAB_IO_SEL_SEL_5 (10)
#define LSB_IOMUX_CTRL_PAB_IO_SEL_SEL_5 (10)
#define MSB_IOMUX_CTRL_PAB_IO_SEL_SEL_5 (11)
#define MSK_IOMUX_CTRL_PAB_IO_SEL_SEL_6 (0x3) /* [13:12] */
#define SFT_IOMUX_CTRL_PAB_IO_SEL_SEL_6 (12)
#define LSB_IOMUX_CTRL_PAB_IO_SEL_SEL_6 (12)
#define MSB_IOMUX_CTRL_PAB_IO_SEL_SEL_6 (13)
#define MSK_IOMUX_CTRL_PAB_IO_SEL_SEL_7 (0x3) /* [15:14] */
#define SFT_IOMUX_CTRL_PAB_IO_SEL_SEL_7 (14)
#define LSB_IOMUX_CTRL_PAB_IO_SEL_SEL_7 (14)
#define MSB_IOMUX_CTRL_PAB_IO_SEL_SEL_7 (15)

typedef struct
{
  unsigned short sel_0 : 2; /* [ 1:0] */
  unsigned short sel_1 : 2; /* [ 3:2] */
  unsigned short sel_2 : 2; /* [ 5:4] */
  unsigned short sel_3 : 2; /* [ 7:6] */
  unsigned short sel_4 : 2; /* [ 9:8] */
  unsigned short sel_5 : 2; /* [11:10] */
  unsigned short sel_6 : 2; /* [13:12] */
  unsigned short sel_7 : 2; /* [15:14] */
} _PACKED_ iomux_ctrl_pab_io_sel_bf;

typedef union {
  unsigned short val;
  iomux_ctrl_pab_io_sel_bf bf;
} _PACKED_ iomux_ctrl_pab_io_sel_t;

/* IOMUX_CTRL_PC0123_IO_SEL */

#define MSK_IOMUX_CTRL_PC0123_IO_SEL_SEL_0 (0xf) /* [ 3:0] */
#define SFT_IOMUX_CTRL_PC0123_IO_SEL_SEL_0 (0)
#define LSB_IOMUX_CTRL_PC0123_IO_SEL_SEL_0 (0)
#define MSB_IOMUX_CTRL_PC0123_IO_SEL_SEL_0 (3)
#define MSK_IOMUX_CTRL_PC0123_IO_SEL_SEL_1 (0xf) /* [ 7:4] */
#define SFT_IOMUX_CTRL_PC0123_IO_SEL_SEL_1 (4)
#define LSB_IOMUX_CTRL_PC0123_IO_SEL_SEL_1 (4)
#define MSB_IOMUX_CTRL_PC0123_IO_SEL_SEL_1 (7)
#define MSK_IOMUX_CTRL_PC0123_IO_SEL_SEL_2 (0xf) /* [11:8] */
#define SFT_IOMUX_CTRL_PC0123_IO_SEL_SEL_2 (8)
#define LSB_IOMUX_CTRL_PC0123_IO_SEL_SEL_2 (8)
#define MSB_IOMUX_CTRL_PC0123_IO_SEL_SEL_2 (11)
#define MSK_IOMUX_CTRL_PC0123_IO_SEL_SEL_3 (0xf) /* [15:12] */
#define SFT_IOMUX_CTRL_PC0123_IO_SEL_SEL_3 (12)
#define LSB_IOMUX_CTRL_PC0123_IO_SEL_SEL_3 (12)
#define MSB_IOMUX_CTRL_PC0123_IO_SEL_SEL_3 (15)

typedef struct
{
  unsigned short sel_0 : 4; /* [ 3:0] */
  unsigned short sel_1 : 4; /* [ 7:4] */
  unsigned short sel_2 : 4; /* [11:8] */
  unsigned short sel_3 : 4; /* [15:12] */
} _PACKED_ iomux_ctrl_pc0123_io_sel_bf;

typedef union {
  unsigned short val;
  iomux_ctrl_pc0123_io_sel_bf bf;
} _PACKED_ iomux_ctrl_pc0123_io_sel_t;

/* IOMUX_CTRL_PC4567_IO_SEL */

#define MSK_IOMUX_CTRL_PC4567_IO_SEL_SEL_4 (0xf) /* [ 3:0] */
#define SFT_IOMUX_CTRL_PC4567_IO_SEL_SEL_4 (0)
#define LSB_IOMUX_CTRL_PC4567_IO_SEL_SEL_4 (0)
#define MSB_IOMUX_CTRL_PC4567_IO_SEL_SEL_4 (3)
#define MSK_IOMUX_CTRL_PC4567_IO_SEL_SEL_5 (0xf) /* [ 7:4] */
#define SFT_IOMUX_CTRL_PC4567_IO_SEL_SEL_5 (4)
#define LSB_IOMUX_CTRL_PC4567_IO_SEL_SEL_5 (4)
#define MSB_IOMUX_CTRL_PC4567_IO_SEL_SEL_5 (7)
#define MSK_IOMUX_CTRL_PC4567_IO_SEL_SEL_6 (0xf) /* [11:8] */
#define SFT_IOMUX_CTRL_PC4567_IO_SEL_SEL_6 (8)
#define LSB_IOMUX_CTRL_PC4567_IO_SEL_SEL_6 (8)
#define MSB_IOMUX_CTRL_PC4567_IO_SEL_SEL_6 (11)
#define MSK_IOMUX_CTRL_PC4567_IO_SEL_SEL_7 (0xf) /* [15:12] */
#define SFT_IOMUX_CTRL_PC4567_IO_SEL_SEL_7 (12)
#define LSB_IOMUX_CTRL_PC4567_IO_SEL_SEL_7 (12)
#define MSB_IOMUX_CTRL_PC4567_IO_SEL_SEL_7 (15)

typedef struct
{
  unsigned short sel_4 : 4; /* [ 3:0] */
  unsigned short sel_5 : 4; /* [ 7:4] */
  unsigned short sel_6 : 4; /* [11:8] */
  unsigned short sel_7 : 4; /* [15:12] */
} _PACKED_ iomux_ctrl_pc4567_io_sel_bf;

typedef union {
  unsigned short val;
  iomux_ctrl_pc4567_io_sel_bf bf;
} _PACKED_ iomux_ctrl_pc4567_io_sel_t;

/* IOMUX_CTRL_PX_LOCK */

#define MSK_IOMUX_CTRL_PX_LOCK_LOCK (0xff) /* [ 7:0] */
#define SFT_IOMUX_CTRL_PX_LOCK_LOCK (0)
#define LSB_IOMUX_CTRL_PX_LOCK_LOCK (0)
#define MSB_IOMUX_CTRL_PX_LOCK_LOCK (7)
#define MSK_IOMUX_CTRL_PX_LOCK_PASS (0xff) /* [15:8] */
#define SFT_IOMUX_CTRL_PX_LOCK_PASS (8)
#define LSB_IOMUX_CTRL_PX_LOCK_PASS (8)
#define MSB_IOMUX_CTRL_PX_LOCK_PASS (15)

typedef struct
{
  unsigned short lock : 8; /* [ 7:0] */
  unsigned short pass : 8; /* [15:8] */
} _PACKED_ iomux_ctrl_px_lock_bf;

typedef union {
  unsigned short val;
  iomux_ctrl_px_lock_bf bf;
} _PACKED_ iomux_ctrl_px_lock_t;

/* IOMUX_CTRL */

typedef struct
{
  iomux_ctrl_pab_io_sel_t pa_io_sel;        /* 0 */
  iomux_ctrl_pab_io_sel_t pb_io_sel;        /* 2 */
  iomux_ctrl_pc0123_io_sel_t pc0123_io_sel; /* 4 */
  iomux_ctrl_pc4567_io_sel_t pc4567_io_sel; /* 6 */
  iomux_ctrl_px_lock_t pa_lock;             /* 8 */
  iomux_ctrl_px_lock_t pb_lock;             /* 10 */
  iomux_ctrl_px_lock_t pc_lock;             /* 12 */
} _PACKED_ iomux_ctrl_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_IOMUX_CTRL 0x0200U ... IO Mux Control Module

#define ADDR_IOMUX_CTRL_PA_IO_SEL (0x00U)
#define A_IOMUX_CTRL_PA_IO_SEL(ba) ((ba) + ADDR_IOMUX_CTRL_PA_IO_SEL)
#define R_IOMUX_CTRL_PA_IO_SEL(ba) (*(volatile unsigned short *)((unsigned int)A_IOMUX_CTRL_PA_IO_SEL(ba)))
#define RES_IOMUX_CTRL_PA_IO_SEL (0x0U)
#define MSB_IOMUX_CTRL_PA_IO_SEL 15
#define LSB_IOMUX_CTRL_PA_IO_SEL 0
#define AADDR_IOMUX_CTRL_PA_IO_SEL (BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PA_IO_SEL)
#define REG_IOMUX_CTRL_PA_IO_SEL (*(volatile unsigned short *)((unsigned int)AADDR_IOMUX_CTRL_PA_IO_SEL))

#define ADDR_IOMUX_CTRL_PB_IO_SEL (0x02U)
#define A_IOMUX_CTRL_PB_IO_SEL(ba) ((ba) + ADDR_IOMUX_CTRL_PB_IO_SEL)
#define R_IOMUX_CTRL_PB_IO_SEL(ba) (*(volatile unsigned short *)((unsigned int)A_IOMUX_CTRL_PB_IO_SEL(ba)))
#define RES_IOMUX_CTRL_PB_IO_SEL (0x0U)
#define MSB_IOMUX_CTRL_PB_IO_SEL 15
#define LSB_IOMUX_CTRL_PB_IO_SEL 0
#define AADDR_IOMUX_CTRL_PB_IO_SEL (BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PB_IO_SEL)
#define REG_IOMUX_CTRL_PB_IO_SEL (*(volatile unsigned short *)((unsigned int)AADDR_IOMUX_CTRL_PB_IO_SEL))

#define ADDR_IOMUX_CTRL_PC0123_IO_SEL (0x04U)
#define A_IOMUX_CTRL_PC0123_IO_SEL(ba) ((ba) + ADDR_IOMUX_CTRL_PC0123_IO_SEL)
#define R_IOMUX_CTRL_PC0123_IO_SEL(ba) (*(volatile unsigned short *)((unsigned int)A_IOMUX_CTRL_PC0123_IO_SEL(ba)))
#define RES_IOMUX_CTRL_PC0123_IO_SEL (0x0U)
#define MSB_IOMUX_CTRL_PC0123_IO_SEL 15
#define LSB_IOMUX_CTRL_PC0123_IO_SEL 0
#define AADDR_IOMUX_CTRL_PC0123_IO_SEL (BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PC0123_IO_SEL)
#define REG_IOMUX_CTRL_PC0123_IO_SEL (*(volatile unsigned short *)((unsigned int)AADDR_IOMUX_CTRL_PC0123_IO_SEL))

#define ADDR_IOMUX_CTRL_PC4567_IO_SEL (0x06U)
#define A_IOMUX_CTRL_PC4567_IO_SEL(ba) ((ba) + ADDR_IOMUX_CTRL_PC4567_IO_SEL)
#define R_IOMUX_CTRL_PC4567_IO_SEL(ba) (*(volatile unsigned short *)((unsigned int)A_IOMUX_CTRL_PC4567_IO_SEL(ba)))
#define RES_IOMUX_CTRL_PC4567_IO_SEL (0x0U)
#define MSB_IOMUX_CTRL_PC4567_IO_SEL 15
#define LSB_IOMUX_CTRL_PC4567_IO_SEL 0
#define AADDR_IOMUX_CTRL_PC4567_IO_SEL (BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PC4567_IO_SEL)
#define REG_IOMUX_CTRL_PC4567_IO_SEL (*(volatile unsigned short *)((unsigned int)AADDR_IOMUX_CTRL_PC4567_IO_SEL))

#define ADDR_IOMUX_CTRL_PA_LOCK (0x08U)
#define A_IOMUX_CTRL_PA_LOCK(ba) ((ba) + ADDR_IOMUX_CTRL_PA_LOCK)
#define R_IOMUX_CTRL_PA_LOCK(ba) (*(volatile unsigned short *)((unsigned int)A_IOMUX_CTRL_PA_LOCK(ba)))
#define RES_IOMUX_CTRL_PA_LOCK (0x9600U)
#define MSB_IOMUX_CTRL_PA_LOCK 15
#define LSB_IOMUX_CTRL_PA_LOCK 0
#define AADDR_IOMUX_CTRL_PA_LOCK (BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PA_LOCK)
#define REG_IOMUX_CTRL_PA_LOCK (*(volatile unsigned short *)((unsigned int)AADDR_IOMUX_CTRL_PA_LOCK))

#define ADDR_IOMUX_CTRL_PB_LOCK (0x0AU)
#define A_IOMUX_CTRL_PB_LOCK(ba) ((ba) + ADDR_IOMUX_CTRL_PB_LOCK)
#define R_IOMUX_CTRL_PB_LOCK(ba) (*(volatile unsigned short *)((unsigned int)A_IOMUX_CTRL_PB_LOCK(ba)))
#define RES_IOMUX_CTRL_PB_LOCK (0x9600U)
#define MSB_IOMUX_CTRL_PB_LOCK 15
#define LSB_IOMUX_CTRL_PB_LOCK 0
#define AADDR_IOMUX_CTRL_PB_LOCK (BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PB_LOCK)
#define REG_IOMUX_CTRL_PB_LOCK (*(volatile unsigned short *)((unsigned int)AADDR_IOMUX_CTRL_PB_LOCK))

#define ADDR_IOMUX_CTRL_PC_LOCK (0x0CU)
#define A_IOMUX_CTRL_PC_LOCK(ba) ((ba) + ADDR_IOMUX_CTRL_PC_LOCK)
#define R_IOMUX_CTRL_PC_LOCK(ba) (*(volatile unsigned short *)((unsigned int)A_IOMUX_CTRL_PC_LOCK(ba)))
#define RES_IOMUX_CTRL_PC_LOCK (0x9600U)
#define MSB_IOMUX_CTRL_PC_LOCK 15
#define LSB_IOMUX_CTRL_PC_LOCK 0
#define AADDR_IOMUX_CTRL_PC_LOCK (BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PC_LOCK)
#define REG_IOMUX_CTRL_PC_LOCK (*(volatile unsigned short *)((unsigned int)AADDR_IOMUX_CTRL_PC_LOCK))

#endif
