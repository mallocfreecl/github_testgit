#ifndef __FLASH_CTRL_BF_H__
#define __FLASH_CTRL_BF_H__

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

#ifndef BASE_ADDR_FLASH_CTRL
#define BASE_ADDR_FLASH_CTRL 0x01C0U
#endif

#define NUMBER_FLASH_CTRL 1

typedef enum
{
  FLASH_CTRL = (int)BASE_ADDR_FLASH_CTRL
} flash_ctrl_num_t;

// Register bit field definitions

/* FLASH_CTRL_AREA_MAIN_L */

#define MSK_FLASH_CTRL_AREA_MAIN_L_AREA (0xff) /* [ 7:0] */
#define SFT_FLASH_CTRL_AREA_MAIN_L_AREA (0)
#define LSB_FLASH_CTRL_AREA_MAIN_L_AREA (0)
#define MSB_FLASH_CTRL_AREA_MAIN_L_AREA (7)
#define MSK_FLASH_CTRL_AREA_MAIN_L_PASS (0xff) /* [15:8] */
#define SFT_FLASH_CTRL_AREA_MAIN_L_PASS (8)
#define LSB_FLASH_CTRL_AREA_MAIN_L_PASS (8)
#define MSB_FLASH_CTRL_AREA_MAIN_L_PASS (15)

typedef struct
{
  unsigned short area : 8; /* [ 7:0] */
  unsigned short pass : 8; /* [15:8] */
} _PACKED_ flash_ctrl_area_main_l_bf;

typedef union {
  unsigned short val;
  flash_ctrl_area_main_l_bf bf;
} _PACKED_ flash_ctrl_area_main_l_t;

/* FLASH_CTRL_AREA_MAIN_H */

#define MSK_FLASH_CTRL_AREA_MAIN_H_AREA (0xff) /* [ 7:0] */
#define SFT_FLASH_CTRL_AREA_MAIN_H_AREA (0)
#define LSB_FLASH_CTRL_AREA_MAIN_H_AREA (0)
#define MSB_FLASH_CTRL_AREA_MAIN_H_AREA (7)
#define MSK_FLASH_CTRL_AREA_MAIN_H_PASS (0xff) /* [15:8] */
#define SFT_FLASH_CTRL_AREA_MAIN_H_PASS (8)
#define LSB_FLASH_CTRL_AREA_MAIN_H_PASS (8)
#define MSB_FLASH_CTRL_AREA_MAIN_H_PASS (15)

typedef struct
{
  unsigned short area : 8; /* [ 7:0] */
  unsigned short pass : 8; /* [15:8] */
} _PACKED_ flash_ctrl_area_main_h_bf;

typedef union {
  unsigned short val;
  flash_ctrl_area_main_h_bf bf;
} _PACKED_ flash_ctrl_area_main_h_t;

/* FLASH_CTRL_MODE */

#define MSK_FLASH_CTRL_MODE_MODE (0xff) /* [ 7:0] */
#define SFT_FLASH_CTRL_MODE_MODE (0)
#define LSB_FLASH_CTRL_MODE_MODE (0)
#define MSB_FLASH_CTRL_MODE_MODE (7)
#define MSK_FLASH_CTRL_MODE_PASS (0xff) /* [15:8] */
#define SFT_FLASH_CTRL_MODE_PASS (8)
#define LSB_FLASH_CTRL_MODE_PASS (8)
#define MSB_FLASH_CTRL_MODE_PASS (15)

typedef struct
{
  unsigned short mode : 8; /* [ 7:0] */
  unsigned short pass : 8; /* [15:8] */
} _PACKED_ flash_ctrl_mode_bf;

typedef union {
  unsigned short val;
  flash_ctrl_mode_bf bf;
} _PACKED_ flash_ctrl_mode_t;

/* FLASH_CTRL_STATUS */

#define MSK_FLASH_CTRL_STATUS_BUSY (0x1) /* [0] */
#define SFT_FLASH_CTRL_STATUS_BUSY (0)
#define LSB_FLASH_CTRL_STATUS_BUSY (0)
#define MSB_FLASH_CTRL_STATUS_BUSY (0)
#define BIT_FLASH_CTRL_STATUS_BUSY (0x1)       /* [0] */
#define MSK_FLASH_CTRL_STATUS_INCOMPLETE (0x1) /* [1] */
#define SFT_FLASH_CTRL_STATUS_INCOMPLETE (1)
#define LSB_FLASH_CTRL_STATUS_INCOMPLETE (1)
#define MSB_FLASH_CTRL_STATUS_INCOMPLETE (1)
#define BIT_FLASH_CTRL_STATUS_INCOMPLETE (0x2)  /* [1] */
#define MSK_FLASH_CTRL_STATUS_WRITE_ERROR (0x1) /* [2] */
#define SFT_FLASH_CTRL_STATUS_WRITE_ERROR (2)
#define LSB_FLASH_CTRL_STATUS_WRITE_ERROR (2)
#define MSB_FLASH_CTRL_STATUS_WRITE_ERROR (2)
#define BIT_FLASH_CTRL_STATUS_WRITE_ERROR (0x4) /* [2] */
#define MSK_FLASH_CTRL_STATUS_RECALL_BUSY (0x1) /* [3] */
#define SFT_FLASH_CTRL_STATUS_RECALL_BUSY (3)
#define LSB_FLASH_CTRL_STATUS_RECALL_BUSY (3)
#define MSB_FLASH_CTRL_STATUS_RECALL_BUSY (3)
#define BIT_FLASH_CTRL_STATUS_RECALL_BUSY (0x8) /* [3] */

typedef struct
{
  unsigned short busy : 1;        /* [0] */
  unsigned short incomplete : 1;  /* [1] */
  unsigned short write_error : 1; /* [2] */
  unsigned short recall_busy : 1; /* [3] */
  unsigned short reserved : 12;
} _PACKED_ flash_ctrl_status_bf;

typedef union {
  unsigned short val;
  flash_ctrl_status_bf bf;
} _PACKED_ flash_ctrl_status_t;

/* FLASH_CTRL_AREA_INFO */

#define MSK_FLASH_CTRL_AREA_INFO_AREA (0x3) /* [ 1:0] */
#define SFT_FLASH_CTRL_AREA_INFO_AREA (0)
#define LSB_FLASH_CTRL_AREA_INFO_AREA (0)
#define MSB_FLASH_CTRL_AREA_INFO_AREA (1)
#define MSK_FLASH_CTRL_AREA_INFO_PASS (0xff) /* [15:8] */
#define SFT_FLASH_CTRL_AREA_INFO_PASS (8)
#define LSB_FLASH_CTRL_AREA_INFO_PASS (8)
#define MSB_FLASH_CTRL_AREA_INFO_PASS (15)

typedef struct
{
  unsigned short area : 2;      /* [ 1:0] */
  unsigned short reserved7 : 6; /* [ 7:2] */
  unsigned short pass : 8;      /* [15:8] */
} _PACKED_ flash_ctrl_area_info_bf;

typedef union {
  unsigned short val;
  flash_ctrl_area_info_bf bf;
} _PACKED_ flash_ctrl_area_info_t;

/* FLASH_CTRL_READ_INFO */

#define MSK_FLASH_CTRL_READ_INFO_AREA (0x3) /* [ 1:0] */
#define SFT_FLASH_CTRL_READ_INFO_AREA (0)
#define LSB_FLASH_CTRL_READ_INFO_AREA (0)
#define MSB_FLASH_CTRL_READ_INFO_AREA (1)
#define MSK_FLASH_CTRL_READ_INFO_PASS (0xff) /* [15:8] */
#define SFT_FLASH_CTRL_READ_INFO_PASS (8)
#define LSB_FLASH_CTRL_READ_INFO_PASS (8)
#define MSB_FLASH_CTRL_READ_INFO_PASS (15)

typedef struct
{
  unsigned short area : 2;      /* [ 1:0] */
  unsigned short reserved7 : 6; /* [ 7:2] */
  unsigned short pass : 8;      /* [15:8] */
} _PACKED_ flash_ctrl_read_info_bf;

typedef union {
  unsigned short val;
  flash_ctrl_read_info_bf bf;
} _PACKED_ flash_ctrl_read_info_t;

/* FLASH_CTRL_BIT_ERROR_ADDR */

#define MSK_FLASH_CTRL_BIT_ERROR_ADDR (0xffff) /* [15:0] */

typedef unsigned short flash_ctrl_bit_error_addr_t; /* [15:0] */

/* FLASH_CTRL_WORD_CONFIG */

#define MSK_FLASH_CTRL_WORD_CONFIG_CONFIG (0x3f) /* [ 5:0] */
#define SFT_FLASH_CTRL_WORD_CONFIG_CONFIG (0)
#define LSB_FLASH_CTRL_WORD_CONFIG_CONFIG (0)
#define MSB_FLASH_CTRL_WORD_CONFIG_CONFIG (5)
#define MSK_FLASH_CTRL_WORD_CONFIG_PASS (0xff) /* [15:8] */
#define SFT_FLASH_CTRL_WORD_CONFIG_PASS (8)
#define LSB_FLASH_CTRL_WORD_CONFIG_PASS (8)
#define MSB_FLASH_CTRL_WORD_CONFIG_PASS (15)

typedef struct
{
  unsigned short config : 6;    /* [ 5:0] */
  unsigned short reserved7 : 2; /* [ 7:6] */
  unsigned short pass : 8;      /* [15:8] */
} _PACKED_ flash_ctrl_word_config_bf;

typedef union {
  unsigned short val;
  flash_ctrl_word_config_bf bf;
} _PACKED_ flash_ctrl_word_config_t;

/* FLASH_CTRL_AREA_MAIN_L_LOCK */

#define MSK_FLASH_CTRL_AREA_MAIN_L_LOCK_AREA (0xff) /* [ 7:0] */
#define SFT_FLASH_CTRL_AREA_MAIN_L_LOCK_AREA (0)
#define LSB_FLASH_CTRL_AREA_MAIN_L_LOCK_AREA (0)
#define MSB_FLASH_CTRL_AREA_MAIN_L_LOCK_AREA (7)
#define MSK_FLASH_CTRL_AREA_MAIN_L_LOCK_PASS (0xff) /* [15:8] */
#define SFT_FLASH_CTRL_AREA_MAIN_L_LOCK_PASS (8)
#define LSB_FLASH_CTRL_AREA_MAIN_L_LOCK_PASS (8)
#define MSB_FLASH_CTRL_AREA_MAIN_L_LOCK_PASS (15)

typedef struct
{
  unsigned short area : 8; /* [ 7:0] */
  unsigned short pass : 8; /* [15:8] */
} _PACKED_ flash_ctrl_area_main_l_lock_bf;

typedef union {
  unsigned short val;
  flash_ctrl_area_main_l_lock_bf bf;
} _PACKED_ flash_ctrl_area_main_l_lock_t;

/* FLASH_CTRL_AREA_MAIN_H_LOCK */

#define MSK_FLASH_CTRL_AREA_MAIN_H_LOCK_AREA (0xff) /* [ 7:0] */
#define SFT_FLASH_CTRL_AREA_MAIN_H_LOCK_AREA (0)
#define LSB_FLASH_CTRL_AREA_MAIN_H_LOCK_AREA (0)
#define MSB_FLASH_CTRL_AREA_MAIN_H_LOCK_AREA (7)
#define MSK_FLASH_CTRL_AREA_MAIN_H_LOCK_PASS (0xff) /* [15:8] */
#define SFT_FLASH_CTRL_AREA_MAIN_H_LOCK_PASS (8)
#define LSB_FLASH_CTRL_AREA_MAIN_H_LOCK_PASS (8)
#define MSB_FLASH_CTRL_AREA_MAIN_H_LOCK_PASS (15)

typedef struct
{
  unsigned short area : 8; /* [ 7:0] */
  unsigned short pass : 8; /* [15:8] */
} _PACKED_ flash_ctrl_area_main_h_lock_bf;

typedef union {
  unsigned short val;
  flash_ctrl_area_main_h_lock_bf bf;
} _PACKED_ flash_ctrl_area_main_h_lock_t;

/* FLASH_CTRL */

typedef struct
{
  flash_ctrl_area_main_l_t area_main_l;       /* 0 */
  flash_ctrl_area_main_h_t area_main_h;       /* 2 */
  flash_ctrl_mode_t mode;                     /* 4 */
  flash_ctrl_status_t status;                 /* 6 */
  flash_ctrl_area_info_t area_info;           /* 8 */
  flash_ctrl_read_info_t read_info;           /* 10 */
  flash_ctrl_bit_error_addr_t bit_error_addr; /* 12 */
  flash_ctrl_word_config_t word_config;       /* 14 */
  unsigned short reserved0[8];
  flash_ctrl_area_main_l_lock_t area_main_l_lock; /* 32 */
  flash_ctrl_area_main_h_lock_t area_main_h_lock; /* 34 */
} _PACKED_ flash_ctrl_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_FLASH_CTRL 0x01C0U ... FLASH Control Module

#define ADDR_FLASH_CTRL_AREA_MAIN_L (0x00U)
#define A_FLASH_CTRL_AREA_MAIN_L(ba) ((ba) + ADDR_FLASH_CTRL_AREA_MAIN_L)
#define R_FLASH_CTRL_AREA_MAIN_L(ba) (*(volatile unsigned short *)((unsigned int)A_FLASH_CTRL_AREA_MAIN_L(ba)))
#define RES_FLASH_CTRL_AREA_MAIN_L (0x9600U)
#define MSB_FLASH_CTRL_AREA_MAIN_L 15
#define LSB_FLASH_CTRL_AREA_MAIN_L 0
#define AADDR_FLASH_CTRL_AREA_MAIN_L (BASE_ADDR_FLASH_CTRL + ADDR_FLASH_CTRL_AREA_MAIN_L)
#define REG_FLASH_CTRL_AREA_MAIN_L (*(volatile unsigned short *)((unsigned int)AADDR_FLASH_CTRL_AREA_MAIN_L))

#define ADDR_FLASH_CTRL_AREA_MAIN_H (0x02U)
#define A_FLASH_CTRL_AREA_MAIN_H(ba) ((ba) + ADDR_FLASH_CTRL_AREA_MAIN_H)
#define R_FLASH_CTRL_AREA_MAIN_H(ba) (*(volatile unsigned short *)((unsigned int)A_FLASH_CTRL_AREA_MAIN_H(ba)))
#define RES_FLASH_CTRL_AREA_MAIN_H (0x9600U)
#define MSB_FLASH_CTRL_AREA_MAIN_H 15
#define LSB_FLASH_CTRL_AREA_MAIN_H 0
#define AADDR_FLASH_CTRL_AREA_MAIN_H (BASE_ADDR_FLASH_CTRL + ADDR_FLASH_CTRL_AREA_MAIN_H)
#define REG_FLASH_CTRL_AREA_MAIN_H (*(volatile unsigned short *)((unsigned int)AADDR_FLASH_CTRL_AREA_MAIN_H))

#define ADDR_FLASH_CTRL_MODE (0x04U)
#define A_FLASH_CTRL_MODE(ba) ((ba) + ADDR_FLASH_CTRL_MODE)
#define R_FLASH_CTRL_MODE(ba) (*(volatile unsigned short *)((unsigned int)A_FLASH_CTRL_MODE(ba)))
#define RES_FLASH_CTRL_MODE (0x9601U)
#define MSB_FLASH_CTRL_MODE 15
#define LSB_FLASH_CTRL_MODE 0
#define AADDR_FLASH_CTRL_MODE (BASE_ADDR_FLASH_CTRL + ADDR_FLASH_CTRL_MODE)
#define REG_FLASH_CTRL_MODE (*(volatile unsigned short *)((unsigned int)AADDR_FLASH_CTRL_MODE))

#define ADDR_FLASH_CTRL_STATUS (0x06U)
#define A_FLASH_CTRL_STATUS(ba) ((ba) + ADDR_FLASH_CTRL_STATUS)
#define R_FLASH_CTRL_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_FLASH_CTRL_STATUS(ba)))
#define RES_FLASH_CTRL_STATUS (0x0U)
#define MSB_FLASH_CTRL_STATUS 3
#define LSB_FLASH_CTRL_STATUS 0
#define AADDR_FLASH_CTRL_STATUS (BASE_ADDR_FLASH_CTRL + ADDR_FLASH_CTRL_STATUS)
#define REG_FLASH_CTRL_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_FLASH_CTRL_STATUS))

#define ADDR_FLASH_CTRL_AREA_INFO (0x08U)
#define A_FLASH_CTRL_AREA_INFO(ba) ((ba) + ADDR_FLASH_CTRL_AREA_INFO)
#define R_FLASH_CTRL_AREA_INFO(ba) (*(volatile unsigned short *)((unsigned int)A_FLASH_CTRL_AREA_INFO(ba)))
#define RES_FLASH_CTRL_AREA_INFO (0x9600U)
#define MSB_FLASH_CTRL_AREA_INFO 15
#define LSB_FLASH_CTRL_AREA_INFO 0
#define AADDR_FLASH_CTRL_AREA_INFO (BASE_ADDR_FLASH_CTRL + ADDR_FLASH_CTRL_AREA_INFO)
#define REG_FLASH_CTRL_AREA_INFO (*(volatile unsigned short *)((unsigned int)AADDR_FLASH_CTRL_AREA_INFO))

#define ADDR_FLASH_CTRL_READ_INFO (0x0AU)
#define A_FLASH_CTRL_READ_INFO(ba) ((ba) + ADDR_FLASH_CTRL_READ_INFO)
#define R_FLASH_CTRL_READ_INFO(ba) (*(volatile unsigned short *)((unsigned int)A_FLASH_CTRL_READ_INFO(ba)))
#define RES_FLASH_CTRL_READ_INFO (0x9600U)
#define MSB_FLASH_CTRL_READ_INFO 15
#define LSB_FLASH_CTRL_READ_INFO 0
#define AADDR_FLASH_CTRL_READ_INFO (BASE_ADDR_FLASH_CTRL + ADDR_FLASH_CTRL_READ_INFO)
#define REG_FLASH_CTRL_READ_INFO (*(volatile unsigned short *)((unsigned int)AADDR_FLASH_CTRL_READ_INFO))

#define ADDR_FLASH_CTRL_BIT_ERROR_ADDR (0x0CU)
#define A_FLASH_CTRL_BIT_ERROR_ADDR(ba) ((ba) + ADDR_FLASH_CTRL_BIT_ERROR_ADDR)
#define R_FLASH_CTRL_BIT_ERROR_ADDR(ba) (*(volatile unsigned short *)((unsigned int)A_FLASH_CTRL_BIT_ERROR_ADDR(ba)))
#define RES_FLASH_CTRL_BIT_ERROR_ADDR (0x0U)
#define MSB_FLASH_CTRL_BIT_ERROR_ADDR 15
#define LSB_FLASH_CTRL_BIT_ERROR_ADDR 0
#define AADDR_FLASH_CTRL_BIT_ERROR_ADDR (BASE_ADDR_FLASH_CTRL + ADDR_FLASH_CTRL_BIT_ERROR_ADDR)
#define REG_FLASH_CTRL_BIT_ERROR_ADDR (*(volatile unsigned short *)((unsigned int)AADDR_FLASH_CTRL_BIT_ERROR_ADDR))

#define ADDR_FLASH_CTRL_WORD_CONFIG (0x0EU)
#define A_FLASH_CTRL_WORD_CONFIG(ba) ((ba) + ADDR_FLASH_CTRL_WORD_CONFIG)
#define R_FLASH_CTRL_WORD_CONFIG(ba) (*(volatile unsigned short *)((unsigned int)A_FLASH_CTRL_WORD_CONFIG(ba)))
#define RES_FLASH_CTRL_WORD_CONFIG (0x963fU)
#define MSB_FLASH_CTRL_WORD_CONFIG 15
#define LSB_FLASH_CTRL_WORD_CONFIG 0
#define AADDR_FLASH_CTRL_WORD_CONFIG (BASE_ADDR_FLASH_CTRL + ADDR_FLASH_CTRL_WORD_CONFIG)
#define REG_FLASH_CTRL_WORD_CONFIG (*(volatile unsigned short *)((unsigned int)AADDR_FLASH_CTRL_WORD_CONFIG))

#define ADDR_FLASH_CTRL_AREA_MAIN_L_LOCK (0x20U)
#define A_FLASH_CTRL_AREA_MAIN_L_LOCK(ba) ((ba) + ADDR_FLASH_CTRL_AREA_MAIN_L_LOCK)
#define R_FLASH_CTRL_AREA_MAIN_L_LOCK(ba)                                                                              \
  (*(volatile unsigned short *)((unsigned int)A_FLASH_CTRL_AREA_MAIN_L_LOCK(ba)))
#define RES_FLASH_CTRL_AREA_MAIN_L_LOCK (0x9600U)
#define MSB_FLASH_CTRL_AREA_MAIN_L_LOCK 15
#define LSB_FLASH_CTRL_AREA_MAIN_L_LOCK 0
#define AADDR_FLASH_CTRL_AREA_MAIN_L_LOCK (BASE_ADDR_FLASH_CTRL + ADDR_FLASH_CTRL_AREA_MAIN_L_LOCK)
#define REG_FLASH_CTRL_AREA_MAIN_L_LOCK (*(volatile unsigned short *)((unsigned int)AADDR_FLASH_CTRL_AREA_MAIN_L_LOCK))

#define ADDR_FLASH_CTRL_AREA_MAIN_H_LOCK (0x22U)
#define A_FLASH_CTRL_AREA_MAIN_H_LOCK(ba) ((ba) + ADDR_FLASH_CTRL_AREA_MAIN_H_LOCK)
#define R_FLASH_CTRL_AREA_MAIN_H_LOCK(ba)                                                                              \
  (*(volatile unsigned short *)((unsigned int)A_FLASH_CTRL_AREA_MAIN_H_LOCK(ba)))
#define RES_FLASH_CTRL_AREA_MAIN_H_LOCK (0x9600U)
#define MSB_FLASH_CTRL_AREA_MAIN_H_LOCK 15
#define LSB_FLASH_CTRL_AREA_MAIN_H_LOCK 0
#define AADDR_FLASH_CTRL_AREA_MAIN_H_LOCK (BASE_ADDR_FLASH_CTRL + ADDR_FLASH_CTRL_AREA_MAIN_H_LOCK)
#define REG_FLASH_CTRL_AREA_MAIN_H_LOCK (*(volatile unsigned short *)((unsigned int)AADDR_FLASH_CTRL_AREA_MAIN_H_LOCK))

#endif
