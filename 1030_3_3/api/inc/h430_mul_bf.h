#ifndef __H430_MUL_BF_H__
#define __H430_MUL_BF_H__

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

#ifndef BASE_ADDR_H430_MUL
#define BASE_ADDR_H430_MUL 0x0100U
#endif

#define NUMBER_H430_MUL 1

typedef enum
{
  H430_MUL = (int)BASE_ADDR_H430_MUL
} h430_mul_num_t;

// Register bit field definitions

/* H430_MUL_MPY */

#define MSK_H430_MUL_MPY (0xffff) /* [15:0] */

typedef unsigned short h430_mul_mpy_t; /* [15:0] */

/* H430_MUL_MPYS */

#define MSK_H430_MUL_MPYS (0xffff) /* [15:0] */

typedef unsigned short h430_mul_mpys_t; /* [15:0] */

/* H430_MUL_MAC */

#define MSK_H430_MUL_MAC (0xffff) /* [15:0] */

typedef unsigned short h430_mul_mac_t; /* [15:0] */

/* H430_MUL_MACS */

#define MSK_H430_MUL_MACS (0xffff) /* [15:0] */

typedef unsigned short h430_mul_macs_t; /* [15:0] */

/* H430_MUL_OP2 */

#define MSK_H430_MUL_OP2 (0xffff) /* [15:0] */

typedef unsigned short h430_mul_op2_t; /* [15:0] */

/* H430_MUL_RESLO */

#define MSK_H430_MUL_RESLO (0xffff) /* [15:0] */

typedef unsigned short h430_mul_reslo_t; /* [15:0] */

/* H430_MUL_RESHI */

#define MSK_H430_MUL_RESHI (0xffff) /* [15:0] */

typedef unsigned short h430_mul_reshi_t; /* [15:0] */

/* H430_MUL_SUMEXT */

#define MSK_H430_MUL_SUMEXT (0xffff) /* [15:0] */

typedef unsigned short h430_mul_sumext_t; /* [15:0] */

/* H430_MUL_LAST_MODE */

#define MSK_H430_MUL_LAST_MODE (0x3) /* [ 1:0] */

typedef unsigned short h430_mul_last_mode_t; /* [ 1:0] */

/* H430_MUL_OP2U */

#define MSK_H430_MUL_OP2U (0xffff) /* [15:0] */

typedef unsigned short h430_mul_op2u_t; /* [15:0] */

/* H430_MUL_OP2S */

#define MSK_H430_MUL_OP2S (0xffff) /* [15:0] */

typedef unsigned short h430_mul_op2s_t; /* [15:0] */

/* H430_MUL_OP2SN */

#define MSK_H430_MUL_OP2SN (0xffff) /* [15:0] */

typedef unsigned short h430_mul_op2sn_t; /* [15:0] */

/* H430_MUL_ACCU_EXT */

#define MSK_H430_MUL_ACCU_EXT (0xff) /* [ 7:0] */

typedef unsigned short h430_mul_accu_ext_t; /* [ 7:0] */

/* H430_MUL_RESHI_TC */

#define MSK_H430_MUL_RESHI_TC (0xffff) /* [15:0] */

typedef unsigned short h430_mul_reshi_tc_t; /* [15:0] */

/* H430_MUL_RESHI_Q1_15 */

#define MSK_H430_MUL_RESHI_Q1_15 (0xffff) /* [15:0] */

typedef unsigned short h430_mul_reshi_q1_15_t; /* [15:0] */

/* H430_MUL_SHIFT_RIGHT */

#define MSK_H430_MUL_SHIFT_RIGHT (0xf) /* [ 3:0] */

typedef unsigned short h430_mul_shift_right_t; /* [ 3:0] */

/* H430_MUL_SHIFT_LEFT */

#define MSK_H430_MUL_SHIFT_LEFT (0xf) /* [ 3:0] */

typedef unsigned short h430_mul_shift_left_t; /* [ 3:0] */

/* H430_MUL */

typedef struct
{
  h430_mul_last_mode_t last_mode;     /* 0 */
  h430_mul_op2u_t op2u;               /* 2 */
  h430_mul_op2s_t op2s;               /* 4 */
  h430_mul_op2sn_t op2sn;             /* 6 */
  h430_mul_accu_ext_t accu_ext;       /* 8 */
  h430_mul_reshi_tc_t reshi_tc;       /* 10 */
  h430_mul_reshi_q1_15_t reshi_q1_15; /* 12 */
  h430_mul_shift_right_t shift_right; /* 14 */
  h430_mul_shift_left_t shift_left;   /* 16 */
  unsigned short reserved0[15];
  h430_mul_mpy_t mpy;       /* 48 */
  h430_mul_mpys_t mpys;     /* 50 */
  h430_mul_mac_t mac;       /* 52 */
  h430_mul_macs_t macs;     /* 54 */
  h430_mul_op2_t op2;       /* 56 */
  h430_mul_reslo_t reslo;   /* 58 */
  h430_mul_reshi_t reshi;   /* 60 */
  h430_mul_sumext_t sumext; /* 62 */
} _PACKED_ h430_mul_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_H430_MUL 0x0100U ... H430 Multiplier

#define ADDR_H430_MUL_LAST_MODE (0x00U)
#define A_H430_MUL_LAST_MODE(ba) ((ba) + ADDR_H430_MUL_LAST_MODE)
#define R_H430_MUL_LAST_MODE(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_LAST_MODE(ba)))
#define RES_H430_MUL_LAST_MODE (0x0U)
#define MSB_H430_MUL_LAST_MODE 1
#define LSB_H430_MUL_LAST_MODE 0
#define AADDR_H430_MUL_LAST_MODE (BASE_ADDR_H430_MUL + ADDR_H430_MUL_LAST_MODE)
#define REG_H430_MUL_LAST_MODE (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_LAST_MODE))

#define ADDR_H430_MUL_OP2U (0x02U)
#define A_H430_MUL_OP2U(ba) ((ba) + ADDR_H430_MUL_OP2U)
#define R_H430_MUL_OP2U(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_OP2U(ba)))
#define RES_H430_MUL_OP2U (0x0U)
#define MSB_H430_MUL_OP2U 15
#define LSB_H430_MUL_OP2U 0
#define AADDR_H430_MUL_OP2U (BASE_ADDR_H430_MUL + ADDR_H430_MUL_OP2U)
#define REG_H430_MUL_OP2U (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_OP2U))

#define ADDR_H430_MUL_OP2S (0x04U)
#define A_H430_MUL_OP2S(ba) ((ba) + ADDR_H430_MUL_OP2S)
#define R_H430_MUL_OP2S(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_OP2S(ba)))
#define RES_H430_MUL_OP2S (0x0U)
#define MSB_H430_MUL_OP2S 15
#define LSB_H430_MUL_OP2S 0
#define AADDR_H430_MUL_OP2S (BASE_ADDR_H430_MUL + ADDR_H430_MUL_OP2S)
#define REG_H430_MUL_OP2S (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_OP2S))

#define ADDR_H430_MUL_OP2SN (0x06U)
#define A_H430_MUL_OP2SN(ba) ((ba) + ADDR_H430_MUL_OP2SN)
#define R_H430_MUL_OP2SN(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_OP2SN(ba)))
#define RES_H430_MUL_OP2SN (0x0U)
#define MSB_H430_MUL_OP2SN 15
#define LSB_H430_MUL_OP2SN 0
#define AADDR_H430_MUL_OP2SN (BASE_ADDR_H430_MUL + ADDR_H430_MUL_OP2SN)
#define REG_H430_MUL_OP2SN (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_OP2SN))

#define ADDR_H430_MUL_ACCU_EXT (0x08U)
#define A_H430_MUL_ACCU_EXT(ba) ((ba) + ADDR_H430_MUL_ACCU_EXT)
#define R_H430_MUL_ACCU_EXT(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_ACCU_EXT(ba)))
#define RES_H430_MUL_ACCU_EXT (0x0U)
#define MSB_H430_MUL_ACCU_EXT 7
#define LSB_H430_MUL_ACCU_EXT 0
#define AADDR_H430_MUL_ACCU_EXT (BASE_ADDR_H430_MUL + ADDR_H430_MUL_ACCU_EXT)
#define REG_H430_MUL_ACCU_EXT (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_ACCU_EXT))

#define ADDR_H430_MUL_RESHI_TC (0x0AU)
#define A_H430_MUL_RESHI_TC(ba) ((ba) + ADDR_H430_MUL_RESHI_TC)
#define R_H430_MUL_RESHI_TC(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_RESHI_TC(ba)))
#define RES_H430_MUL_RESHI_TC (0x0U)
#define MSB_H430_MUL_RESHI_TC 15
#define LSB_H430_MUL_RESHI_TC 0
#define AADDR_H430_MUL_RESHI_TC (BASE_ADDR_H430_MUL + ADDR_H430_MUL_RESHI_TC)
#define REG_H430_MUL_RESHI_TC (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_RESHI_TC))

#define ADDR_H430_MUL_RESHI_Q1_15 (0x0CU)
#define A_H430_MUL_RESHI_Q1_15(ba) ((ba) + ADDR_H430_MUL_RESHI_Q1_15)
#define R_H430_MUL_RESHI_Q1_15(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_RESHI_Q1_15(ba)))
#define RES_H430_MUL_RESHI_Q1_15 (0x0U)
#define MSB_H430_MUL_RESHI_Q1_15 15
#define LSB_H430_MUL_RESHI_Q1_15 0
#define AADDR_H430_MUL_RESHI_Q1_15 (BASE_ADDR_H430_MUL + ADDR_H430_MUL_RESHI_Q1_15)
#define REG_H430_MUL_RESHI_Q1_15 (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_RESHI_Q1_15))

#define ADDR_H430_MUL_SHIFT_RIGHT (0x0EU)
#define A_H430_MUL_SHIFT_RIGHT(ba) ((ba) + ADDR_H430_MUL_SHIFT_RIGHT)
#define R_H430_MUL_SHIFT_RIGHT(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_SHIFT_RIGHT(ba)))
#define RES_H430_MUL_SHIFT_RIGHT (0x0U)
#define MSB_H430_MUL_SHIFT_RIGHT 3
#define LSB_H430_MUL_SHIFT_RIGHT 0
#define AADDR_H430_MUL_SHIFT_RIGHT (BASE_ADDR_H430_MUL + ADDR_H430_MUL_SHIFT_RIGHT)
#define REG_H430_MUL_SHIFT_RIGHT (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_SHIFT_RIGHT))

#define ADDR_H430_MUL_SHIFT_LEFT (0x10U)
#define A_H430_MUL_SHIFT_LEFT(ba) ((ba) + ADDR_H430_MUL_SHIFT_LEFT)
#define R_H430_MUL_SHIFT_LEFT(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_SHIFT_LEFT(ba)))
#define RES_H430_MUL_SHIFT_LEFT (0x0U)
#define MSB_H430_MUL_SHIFT_LEFT 3
#define LSB_H430_MUL_SHIFT_LEFT 0
#define AADDR_H430_MUL_SHIFT_LEFT (BASE_ADDR_H430_MUL + ADDR_H430_MUL_SHIFT_LEFT)
#define REG_H430_MUL_SHIFT_LEFT (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_SHIFT_LEFT))

#define ADDR_H430_MUL_MPY (0x30U)
#define A_H430_MUL_MPY(ba) ((ba) + ADDR_H430_MUL_MPY)
#define R_H430_MUL_MPY(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_MPY(ba)))
#define RES_H430_MUL_MPY (0x0U)
#define MSB_H430_MUL_MPY 15
#define LSB_H430_MUL_MPY 0
#define AADDR_H430_MUL_MPY (BASE_ADDR_H430_MUL + ADDR_H430_MUL_MPY)
#define REG_H430_MUL_MPY (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_MPY))

#define ADDR_H430_MUL_MPYS (0x32U)
#define A_H430_MUL_MPYS(ba) ((ba) + ADDR_H430_MUL_MPYS)
#define R_H430_MUL_MPYS(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_MPYS(ba)))
#define RES_H430_MUL_MPYS (0x0U)
#define MSB_H430_MUL_MPYS 15
#define LSB_H430_MUL_MPYS 0
#define AADDR_H430_MUL_MPYS (BASE_ADDR_H430_MUL + ADDR_H430_MUL_MPYS)
#define REG_H430_MUL_MPYS (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_MPYS))

#define ADDR_H430_MUL_MAC (0x34U)
#define A_H430_MUL_MAC(ba) ((ba) + ADDR_H430_MUL_MAC)
#define R_H430_MUL_MAC(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_MAC(ba)))
#define RES_H430_MUL_MAC (0x0U)
#define MSB_H430_MUL_MAC 15
#define LSB_H430_MUL_MAC 0
#define AADDR_H430_MUL_MAC (BASE_ADDR_H430_MUL + ADDR_H430_MUL_MAC)
#define REG_H430_MUL_MAC (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_MAC))

#define ADDR_H430_MUL_MACS (0x36U)
#define A_H430_MUL_MACS(ba) ((ba) + ADDR_H430_MUL_MACS)
#define R_H430_MUL_MACS(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_MACS(ba)))
#define RES_H430_MUL_MACS (0x0U)
#define MSB_H430_MUL_MACS 15
#define LSB_H430_MUL_MACS 0
#define AADDR_H430_MUL_MACS (BASE_ADDR_H430_MUL + ADDR_H430_MUL_MACS)
#define REG_H430_MUL_MACS (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_MACS))

#define ADDR_H430_MUL_OP2 (0x38U)
#define A_H430_MUL_OP2(ba) ((ba) + ADDR_H430_MUL_OP2)
#define R_H430_MUL_OP2(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_OP2(ba)))
#define RES_H430_MUL_OP2 (0x0U)
#define MSB_H430_MUL_OP2 15
#define LSB_H430_MUL_OP2 0
#define AADDR_H430_MUL_OP2 (BASE_ADDR_H430_MUL + ADDR_H430_MUL_OP2)
#define REG_H430_MUL_OP2 (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_OP2))

#define ADDR_H430_MUL_RESLO (0x3AU)
#define A_H430_MUL_RESLO(ba) ((ba) + ADDR_H430_MUL_RESLO)
#define R_H430_MUL_RESLO(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_RESLO(ba)))
#define RES_H430_MUL_RESLO (0x0U)
#define MSB_H430_MUL_RESLO 15
#define LSB_H430_MUL_RESLO 0
#define AADDR_H430_MUL_RESLO (BASE_ADDR_H430_MUL + ADDR_H430_MUL_RESLO)
#define REG_H430_MUL_RESLO (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_RESLO))

#define ADDR_H430_MUL_RESHI (0x3CU)
#define A_H430_MUL_RESHI(ba) ((ba) + ADDR_H430_MUL_RESHI)
#define R_H430_MUL_RESHI(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_RESHI(ba)))
#define RES_H430_MUL_RESHI (0x0U)
#define MSB_H430_MUL_RESHI 15
#define LSB_H430_MUL_RESHI 0
#define AADDR_H430_MUL_RESHI (BASE_ADDR_H430_MUL + ADDR_H430_MUL_RESHI)
#define REG_H430_MUL_RESHI (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_RESHI))

#define ADDR_H430_MUL_SUMEXT (0x3EU)
#define A_H430_MUL_SUMEXT(ba) ((ba) + ADDR_H430_MUL_SUMEXT)
#define R_H430_MUL_SUMEXT(ba) (*(volatile unsigned short *)((unsigned int)A_H430_MUL_SUMEXT(ba)))
#define RES_H430_MUL_SUMEXT (0x0U)
#define MSB_H430_MUL_SUMEXT 15
#define LSB_H430_MUL_SUMEXT 0
#define AADDR_H430_MUL_SUMEXT (BASE_ADDR_H430_MUL + ADDR_H430_MUL_SUMEXT)
#define REG_H430_MUL_SUMEXT (*(volatile unsigned short *)((unsigned int)AADDR_H430_MUL_SUMEXT))

#endif
