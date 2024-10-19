#ifndef __PWMN_BF_H__
#define __PWMN_BF_H__

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

#ifndef BASE_ADDR_PWMN
#define BASE_ADDR_PWMN 0x0600U
#endif

#define NUMBER_PWMN 1

typedef enum
{
  PWMN = (int)BASE_ADDR_PWMN
} pwmn_num_t;

// Register bit field definitions

/* PWMN_CFG */

#define MSK_PWMN_CFG_CNT_MODE (0x3) /* [ 1:0] */
#define SFT_PWMN_CFG_CNT_MODE (0)
#define LSB_PWMN_CFG_CNT_MODE (0)
#define MSB_PWMN_CFG_CNT_MODE (1)
#define MSK_PWMN_CFG_MIDDLE_RL (0x1) /* [2] */
#define SFT_PWMN_CFG_MIDDLE_RL (2)
#define LSB_PWMN_CFG_MIDDLE_RL (2)
#define MSB_PWMN_CFG_MIDDLE_RL (2)
#define BIT_PWMN_CFG_MIDDLE_RL (0x4)      /* [2] */
#define MSK_PWMN_CFG_DEAD_TIME_MODE (0x1) /* [3] */
#define SFT_PWMN_CFG_DEAD_TIME_MODE (3)
#define LSB_PWMN_CFG_DEAD_TIME_MODE (3)
#define MSB_PWMN_CFG_DEAD_TIME_MODE (3)
#define BIT_PWMN_CFG_DEAD_TIME_MODE (0x8) /* [3] */
#define MSK_PWMN_CFG_OC_ASYN_EN (0x1)     /* [4] */
#define SFT_PWMN_CFG_OC_ASYN_EN (4)
#define LSB_PWMN_CFG_OC_ASYN_EN (4)
#define MSB_PWMN_CFG_OC_ASYN_EN (4)
#define BIT_PWMN_CFG_OC_ASYN_EN (0x10) /* [4] */
#define MSK_PWMN_CFG_OC_SYN_EN (0x1)   /* [5] */
#define SFT_PWMN_CFG_OC_SYN_EN (5)
#define LSB_PWMN_CFG_OC_SYN_EN (5)
#define MSB_PWMN_CFG_OC_SYN_EN (5)
#define BIT_PWMN_CFG_OC_SYN_EN (0x20) /* [5] */
#define MSK_PWMN_CFG_OC_INTF (0x7f)   /* [12:6] */
#define SFT_PWMN_CFG_OC_INTF (6)
#define LSB_PWMN_CFG_OC_INTF (6)
#define MSB_PWMN_CFG_OC_INTF (12)
#define MSK_PWMN_CFG_RESTART_EN (0x1) /* [13] */
#define SFT_PWMN_CFG_RESTART_EN (13)
#define LSB_PWMN_CFG_RESTART_EN (13)
#define MSB_PWMN_CFG_RESTART_EN (13)
#define BIT_PWMN_CFG_RESTART_EN (0x2000)  /* [13] */
#define MSK_PWMN_CFG_RESTART_CAP_EN (0x1) /* [14] */
#define SFT_PWMN_CFG_RESTART_CAP_EN (14)
#define LSB_PWMN_CFG_RESTART_CAP_EN (14)
#define MSB_PWMN_CFG_RESTART_CAP_EN (14)
#define BIT_PWMN_CFG_RESTART_CAP_EN (0x4000) /* [14] */
#define MSK_PWMN_CFG_DT_EVT_CONTINUE (0x1)   /* [15] */
#define SFT_PWMN_CFG_DT_EVT_CONTINUE (15)
#define LSB_PWMN_CFG_DT_EVT_CONTINUE (15)
#define MSB_PWMN_CFG_DT_EVT_CONTINUE (15)
#define BIT_PWMN_CFG_DT_EVT_CONTINUE (0x8000) /* [15] */

typedef struct
{
  unsigned short cnt_mode : 2;        /* [ 1:0] */
  unsigned short middle_rl : 1;       /* [2] */
  unsigned short dead_time_mode : 1;  /* [3] */
  unsigned short oc_asyn_en : 1;      /* [4] */
  unsigned short oc_syn_en : 1;       /* [5] */
  unsigned short oc_intf : 7;         /* [12:6] */
  unsigned short restart_en : 1;      /* [13] */
  unsigned short restart_cap_en : 1;  /* [14] */
  unsigned short dt_evt_continue : 1; /* [15] */
} _PACKED_ pwmn_cfg_bf;

typedef union {
  unsigned short val;
  pwmn_cfg_bf bf;
} _PACKED_ pwmn_cfg_t;

/* PWMN_CMD */

#define MSK_PWMN_CMD_RUN (0x1) /* [0] */
#define SFT_PWMN_CMD_RUN (0)
#define LSB_PWMN_CMD_RUN (0)
#define MSB_PWMN_CMD_RUN (0)
#define BIT_PWMN_CMD_RUN (0x1) /* [0] */
#define MSK_PWMN_CMD_OC (0x1)  /* [1] */
#define SFT_PWMN_CMD_OC (1)
#define LSB_PWMN_CMD_OC (1)
#define MSB_PWMN_CMD_OC (1)
#define BIT_PWMN_CMD_OC (0x2)      /* [1] */
#define MSK_PWMN_CMD_RESTART (0x1) /* [2] */
#define SFT_PWMN_CMD_RESTART (2)
#define LSB_PWMN_CMD_RESTART (2)
#define MSB_PWMN_CMD_RESTART (2)
#define BIT_PWMN_CMD_RESTART (0x4)         /* [2] */
#define MSK_PWMN_CMD_INTF_SYNC_CLEAR (0x1) /* [3] */
#define SFT_PWMN_CMD_INTF_SYNC_CLEAR (3)
#define LSB_PWMN_CMD_INTF_SYNC_CLEAR (3)
#define MSB_PWMN_CMD_INTF_SYNC_CLEAR (3)
#define BIT_PWMN_CMD_INTF_SYNC_CLEAR (0x8) /* [3] */

typedef struct
{
  unsigned short run : 1;             /* [0] */
  unsigned short oc : 1;              /* [1] */
  unsigned short restart : 1;         /* [2] */
  unsigned short intf_sync_clear : 1; /* [3] */
  unsigned short reserved : 12;
} _PACKED_ pwmn_cmd_bf;

typedef union {
  unsigned short val;
  pwmn_cmd_bf bf;
} _PACKED_ pwmn_cmd_t;

/* PWMN_STATE */

#define MSK_PWMN_STATE_RUN (0x1) /* [0] */
#define SFT_PWMN_STATE_RUN (0)
#define LSB_PWMN_STATE_RUN (0)
#define MSB_PWMN_STATE_RUN (0)
#define BIT_PWMN_STATE_RUN (0x1) /* [0] */
#define MSK_PWMN_STATE_OC (0x1)  /* [1] */
#define SFT_PWMN_STATE_OC (1)
#define LSB_PWMN_STATE_OC (1)
#define MSB_PWMN_STATE_OC (1)
#define BIT_PWMN_STATE_OC (0x2) /* [1] */

typedef struct
{
  unsigned short run : 1; /* [0] */
  unsigned short oc : 1;  /* [1] */
  unsigned short reserved : 14;
} _PACKED_ pwmn_state_bf;

typedef union {
  unsigned short val;
  pwmn_state_bf bf;
} _PACKED_ pwmn_state_t;

/* PWMN_CNT_RESTART */

#define MSK_PWMN_CNT_RESTART (0xffff) /* [15:0] */

typedef unsigned short pwmn_cnt_restart_t; /* [15:0] */

/* PWMN_CNT */

#define MSK_PWMN_CNT (0xffff) /* [15:0] */

typedef unsigned short pwmn_cnt_t; /* [15:0] */

/* PWMN_PWM_PHASE */

#define MSK_PWMN_PWM_PHASE (0xffff) /* [15:0] */

typedef unsigned short pwmn_pwm_phase_t; /* [15:0] */

/* PWMN_PRESCALER */

#define MSK_PWMN_PRESCALER (0xf) /* [ 3:0] */

typedef unsigned short pwmn_prescaler_t; /* [ 3:0] */

/* PWMN_CNT_MAX */

#define MSK_PWMN_CNT_MAX (0xffff) /* [15:0] */

typedef unsigned short pwmn_cnt_max_t; /* [15:0] */

/* PWMN_NTH_START */

#define MSK_PWMN_NTH_START (0xf) /* [ 3:0] */

typedef unsigned short pwmn_nth_start_t; /* [ 3:0] */

/* PWMN_DEAD_TIME */

#define MSK_PWMN_DEAD_TIME (0xff) /* [ 7:0] */

typedef unsigned short pwmn_dead_time_t; /* [ 7:0] */

/* PWMN_PRESCALER_RELOAD */

#define MSK_PWMN_PRESCALER_RELOAD (0xf) /* [ 3:0] */

typedef unsigned short pwmn_prescaler_reload_t; /* [ 3:0] */

/* PWMN_CNT_MAX_RELOAD */

#define MSK_PWMN_CNT_MAX_RELOAD (0xffff) /* [15:0] */

typedef unsigned short pwmn_cnt_max_reload_t; /* [15:0] */

/* PWMN_NTH_START_RELOAD */

#define MSK_PWMN_NTH_START_RELOAD (0xf) /* [ 3:0] */

typedef unsigned short pwmn_nth_start_reload_t; /* [ 3:0] */

/* PWMN_DEAD_TIME_RELOAD */

#define MSK_PWMN_DEAD_TIME_RELOAD (0xff) /* [ 7:0] */

typedef unsigned short pwmn_dead_time_reload_t; /* [ 7:0] */

/* PWMN_DEAD_TIME_RELOAD_CH */

#define MSK_PWMN_DEAD_TIME_RELOAD_CH_RELOAD (0xff) /* [ 7:0] */
#define SFT_PWMN_DEAD_TIME_RELOAD_CH_RELOAD (0)
#define LSB_PWMN_DEAD_TIME_RELOAD_CH_RELOAD (0)
#define MSB_PWMN_DEAD_TIME_RELOAD_CH_RELOAD (7)
#define MSK_PWMN_DEAD_TIME_RELOAD_CH_UP_CH0_HL (0x1) /* [8] */
#define SFT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH0_HL (8)
#define LSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH0_HL (8)
#define MSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH0_HL (8)
#define BIT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH0_HL (0x100) /* [8] */
#define MSK_PWMN_DEAD_TIME_RELOAD_CH_UP_CH0_LH (0x1)   /* [9] */
#define SFT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH0_LH (9)
#define LSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH0_LH (9)
#define MSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH0_LH (9)
#define BIT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH0_LH (0x200) /* [9] */
#define MSK_PWMN_DEAD_TIME_RELOAD_CH_UP_CH1_HL (0x1)   /* [10] */
#define SFT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH1_HL (10)
#define LSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH1_HL (10)
#define MSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH1_HL (10)
#define BIT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH1_HL (0x400) /* [10] */
#define MSK_PWMN_DEAD_TIME_RELOAD_CH_UP_CH1_LH (0x1)   /* [11] */
#define SFT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH1_LH (11)
#define LSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH1_LH (11)
#define MSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH1_LH (11)
#define BIT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH1_LH (0x800) /* [11] */
#define MSK_PWMN_DEAD_TIME_RELOAD_CH_UP_CH2_HL (0x1)   /* [12] */
#define SFT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH2_HL (12)
#define LSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH2_HL (12)
#define MSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH2_HL (12)
#define BIT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH2_HL (0x1000) /* [12] */
#define MSK_PWMN_DEAD_TIME_RELOAD_CH_UP_CH2_LH (0x1)    /* [13] */
#define SFT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH2_LH (13)
#define LSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH2_LH (13)
#define MSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH2_LH (13)
#define BIT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH2_LH (0x2000) /* [13] */
#define MSK_PWMN_DEAD_TIME_RELOAD_CH_UP_CH3_HL (0x1)    /* [14] */
#define SFT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH3_HL (14)
#define LSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH3_HL (14)
#define MSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH3_HL (14)
#define BIT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH3_HL (0x4000) /* [14] */
#define MSK_PWMN_DEAD_TIME_RELOAD_CH_UP_CH3_LH (0x1)    /* [15] */
#define SFT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH3_LH (15)
#define LSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH3_LH (15)
#define MSB_PWMN_DEAD_TIME_RELOAD_CH_UP_CH3_LH (15)
#define BIT_PWMN_DEAD_TIME_RELOAD_CH_UP_CH3_LH (0x8000) /* [15] */

typedef struct
{
  unsigned short reload : 8;    /* [ 7:0] */
  unsigned short up_ch0_hl : 1; /* [8] */
  unsigned short up_ch0_lh : 1; /* [9] */
  unsigned short up_ch1_hl : 1; /* [10] */
  unsigned short up_ch1_lh : 1; /* [11] */
  unsigned short up_ch2_hl : 1; /* [12] */
  unsigned short up_ch2_lh : 1; /* [13] */
  unsigned short up_ch3_hl : 1; /* [14] */
  unsigned short up_ch3_lh : 1; /* [15] */
} _PACKED_ pwmn_dead_time_reload_ch_bf;

typedef union {
  unsigned short val;
  pwmn_dead_time_reload_ch_bf bf;
} _PACKED_ pwmn_dead_time_reload_ch_t;

/* PWMN_PWM_CFG */

#define MSK_PWMN_PWM_CFG_CMP_MODE (0x3) /* [ 1:0] */
#define SFT_PWMN_PWM_CFG_CMP_MODE (0)
#define LSB_PWMN_PWM_CFG_CMP_MODE (0)
#define MSB_PWMN_PWM_CFG_CMP_MODE (1)
#define MSK_PWMN_PWM_CFG_C_SRC (0x3) /* [ 3:2] */
#define SFT_PWMN_PWM_CFG_C_SRC (2)
#define LSB_PWMN_PWM_CFG_C_SRC (2)
#define MSB_PWMN_PWM_CFG_C_SRC (3)
#define MSK_PWMN_PWM_CFG_ON_SRC (0x1) /* [4] */
#define SFT_PWMN_PWM_CFG_ON_SRC (4)
#define LSB_PWMN_PWM_CFG_ON_SRC (4)
#define MSB_PWMN_PWM_CFG_ON_SRC (4)
#define BIT_PWMN_PWM_CFG_ON_SRC (0x10)       /* [4] */
#define MSK_PWMN_PWM_CFG_IGN_START_EVT (0x1) /* [5] */
#define SFT_PWMN_PWM_CFG_IGN_START_EVT (5)
#define LSB_PWMN_PWM_CFG_IGN_START_EVT (5)
#define MSB_PWMN_PWM_CFG_IGN_START_EVT (5)
#define BIT_PWMN_PWM_CFG_IGN_START_EVT (0x20) /* [5] */

typedef struct
{
  unsigned short cmp_mode : 2;      /* [ 1:0] */
  unsigned short c_src : 2;         /* [ 3:2] */
  unsigned short on_src : 1;        /* [4] */
  unsigned short ign_start_evt : 1; /* [5] */
  unsigned short reserved : 10;
} _PACKED_ pwmn_pwm_cfg_bf;

typedef union {
  unsigned short val;
  pwmn_pwm_cfg_bf bf;
} _PACKED_ pwmn_pwm_cfg_t;

/* PWMN_PWM_C */

#define MSK_PWMN_PWM_C (0xffff) /* [15:0] */

typedef unsigned short pwmn_pwm_c_t; /* [15:0] */

/* PWMN_PWM_ON */

#define MSK_PWMN_PWM_ON_LS (0x1) /* [0] */
#define SFT_PWMN_PWM_ON_LS (0)
#define LSB_PWMN_PWM_ON_LS (0)
#define MSB_PWMN_PWM_ON_LS (0)
#define BIT_PWMN_PWM_ON_LS (0x1) /* [0] */
#define MSK_PWMN_PWM_ON_HS (0x1) /* [1] */
#define SFT_PWMN_PWM_ON_HS (1)
#define LSB_PWMN_PWM_ON_HS (1)
#define MSB_PWMN_PWM_ON_HS (1)
#define BIT_PWMN_PWM_ON_HS (0x2) /* [1] */

typedef struct
{
  unsigned short ls : 1; /* [0] */
  unsigned short hs : 1; /* [1] */
  unsigned short reserved : 14;
} _PACKED_ pwmn_pwm_on_bf;

typedef union {
  unsigned short val;
  pwmn_pwm_on_bf bf;
} _PACKED_ pwmn_pwm_on_t;

/* PWMN_PWM_C_RELOAD */

#define MSK_PWMN_PWM_C_RELOAD (0xffff) /* [15:0] */

typedef unsigned short pwmn_pwm_c_reload_t; /* [15:0] */

/* PWMN_PWM_ON_RELOAD */

#define MSK_PWMN_PWM_ON_RELOAD_LS (0x1) /* [0] */
#define SFT_PWMN_PWM_ON_RELOAD_LS (0)
#define LSB_PWMN_PWM_ON_RELOAD_LS (0)
#define MSB_PWMN_PWM_ON_RELOAD_LS (0)
#define BIT_PWMN_PWM_ON_RELOAD_LS (0x1) /* [0] */
#define MSK_PWMN_PWM_ON_RELOAD_HS (0x1) /* [1] */
#define SFT_PWMN_PWM_ON_RELOAD_HS (1)
#define LSB_PWMN_PWM_ON_RELOAD_HS (1)
#define MSB_PWMN_PWM_ON_RELOAD_HS (1)
#define BIT_PWMN_PWM_ON_RELOAD_HS (0x2) /* [1] */

typedef struct
{
  unsigned short ls : 1; /* [0] */
  unsigned short hs : 1; /* [1] */
  unsigned short reserved : 14;
} _PACKED_ pwmn_pwm_on_reload_bf;

typedef union {
  unsigned short val;
  pwmn_pwm_on_reload_bf bf;
} _PACKED_ pwmn_pwm_on_reload_t;

/* PWMN_PWM_DEAD_TIME */

#define MSK_PWMN_PWM_DEAD_TIME_HIGH_TO_LOW (0xff) /* [ 7:0] */
#define SFT_PWMN_PWM_DEAD_TIME_HIGH_TO_LOW (0)
#define LSB_PWMN_PWM_DEAD_TIME_HIGH_TO_LOW (0)
#define MSB_PWMN_PWM_DEAD_TIME_HIGH_TO_LOW (7)
#define MSK_PWMN_PWM_DEAD_TIME_LOW_TO_HIGH (0xff) /* [15:8] */
#define SFT_PWMN_PWM_DEAD_TIME_LOW_TO_HIGH (8)
#define LSB_PWMN_PWM_DEAD_TIME_LOW_TO_HIGH (8)
#define MSB_PWMN_PWM_DEAD_TIME_LOW_TO_HIGH (15)

typedef struct
{
  unsigned short high_to_low : 8; /* [ 7:0] */
  unsigned short low_to_high : 8; /* [15:8] */
} _PACKED_ pwmn_pwm_dead_time_bf;

typedef union {
  unsigned short val;
  pwmn_pwm_dead_time_bf bf;
} _PACKED_ pwmn_pwm_dead_time_t;

/* PWMN_IRQ_STATUS */

#define MSK_PWMN_IRQ_STATUS_OC (0x1) /* [0] */
#define SFT_PWMN_IRQ_STATUS_OC (0)
#define LSB_PWMN_IRQ_STATUS_OC (0)
#define MSB_PWMN_IRQ_STATUS_OC (0)
#define BIT_PWMN_IRQ_STATUS_OC (0x1)        /* [0] */
#define MSK_PWMN_IRQ_STATUS_START_EVT (0x1) /* [1] */
#define SFT_PWMN_IRQ_STATUS_START_EVT (1)
#define LSB_PWMN_IRQ_STATUS_START_EVT (1)
#define MSB_PWMN_IRQ_STATUS_START_EVT (1)
#define BIT_PWMN_IRQ_STATUS_START_EVT (0x2)  /* [1] */
#define MSK_PWMN_IRQ_STATUS_MIDDLE_EVT (0x1) /* [2] */
#define SFT_PWMN_IRQ_STATUS_MIDDLE_EVT (2)
#define LSB_PWMN_IRQ_STATUS_MIDDLE_EVT (2)
#define MSB_PWMN_IRQ_STATUS_MIDDLE_EVT (2)
#define BIT_PWMN_IRQ_STATUS_MIDDLE_EVT (0x4)      /* [2] */
#define MSK_PWMN_IRQ_STATUS_DEAD_TIME_EVT_0 (0x1) /* [3] */
#define SFT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_0 (3)
#define LSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_0 (3)
#define MSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_0 (3)
#define BIT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_0 (0x8) /* [3] */
#define MSK_PWMN_IRQ_STATUS_DEAD_TIME_EVT_1 (0x1) /* [4] */
#define SFT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_1 (4)
#define LSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_1 (4)
#define MSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_1 (4)
#define BIT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_1 (0x10) /* [4] */
#define MSK_PWMN_IRQ_STATUS_DEAD_TIME_EVT_2 (0x1)  /* [5] */
#define SFT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_2 (5)
#define LSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_2 (5)
#define MSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_2 (5)
#define BIT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_2 (0x20) /* [5] */
#define MSK_PWMN_IRQ_STATUS_DEAD_TIME_EVT_3 (0x1)  /* [6] */
#define SFT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_3 (6)
#define LSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_3 (6)
#define MSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_3 (6)
#define BIT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_3 (0x40) /* [6] */
#define MSK_PWMN_IRQ_STATUS_DEAD_TIME_EVT_4 (0x1)  /* [7] */
#define SFT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_4 (7)
#define LSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_4 (7)
#define MSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_4 (7)
#define BIT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_4 (0x80) /* [7] */
#define MSK_PWMN_IRQ_STATUS_DEAD_TIME_EVT_5 (0x1)  /* [8] */
#define SFT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_5 (8)
#define LSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_5 (8)
#define MSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_5 (8)
#define BIT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_5 (0x100) /* [8] */
#define MSK_PWMN_IRQ_STATUS_DEAD_TIME_EVT_6 (0x1)   /* [9] */
#define SFT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_6 (9)
#define LSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_6 (9)
#define MSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_6 (9)
#define BIT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_6 (0x200) /* [9] */
#define MSK_PWMN_IRQ_STATUS_DEAD_TIME_EVT_7 (0x1)   /* [10] */
#define SFT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_7 (10)
#define LSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_7 (10)
#define MSB_PWMN_IRQ_STATUS_DEAD_TIME_EVT_7 (10)
#define BIT_PWMN_IRQ_STATUS_DEAD_TIME_EVT_7 (0x400) /* [10] */

typedef struct
{
  unsigned short oc : 1;              /* [0] */
  unsigned short start_evt : 1;       /* [1] */
  unsigned short middle_evt : 1;      /* [2] */
  unsigned short dead_time_evt_0 : 1; /* [3] */
  unsigned short dead_time_evt_1 : 1; /* [4] */
  unsigned short dead_time_evt_2 : 1; /* [5] */
  unsigned short dead_time_evt_3 : 1; /* [6] */
  unsigned short dead_time_evt_4 : 1; /* [7] */
  unsigned short dead_time_evt_5 : 1; /* [8] */
  unsigned short dead_time_evt_6 : 1; /* [9] */
  unsigned short dead_time_evt_7 : 1; /* [10] */
  unsigned short reserved : 5;
} _PACKED_ pwmn_irq_status_bf;

typedef union {
  unsigned short val;
  pwmn_irq_status_bf bf;
} _PACKED_ pwmn_irq_status_t;

/* PWMN_IRQ_MASK */

#define MSK_PWMN_IRQ_MASK (0x7ff) /* [10:0] */

typedef unsigned short pwmn_irq_mask_t; /* [10:0] */

/* PWMN_IRQ_VENABLE */

#define MSK_PWMN_IRQ_VENABLE (0xf) /* [ 3:0] */

typedef unsigned short pwmn_irq_venable_t; /* [ 3:0] */

/* PWMN_IRQ_VDISABLE */

#define MSK_PWMN_IRQ_VDISABLE (0xf) /* [ 3:0] */

typedef unsigned short pwmn_irq_vdisable_t; /* [ 3:0] */

/* PWMN_IRQ_VMAX */

#define MSK_PWMN_IRQ_VMAX (0xf) /* [ 3:0] */

typedef unsigned short pwmn_irq_vmax_t; /* [ 3:0] */

/* PWMN_IRQ_VNO */

#define MSK_PWMN_IRQ_VNO (0xf) /* [ 3:0] */

typedef unsigned short pwmn_irq_vno_t; /* [ 3:0] */

/* PWMN */

typedef struct
{
  pwmn_cfg_t cfg;                           /* 0 */
  pwmn_cmd_t cmd;                           /* 2 */
  pwmn_state_t state;                       /* 4 */
  pwmn_cnt_t cnt;                           /* 6 */
  pwmn_pwm_phase_t pwm_phase;               /* 8 */
  pwmn_prescaler_t prescaler;               /* 10 */
  pwmn_cnt_max_t cnt_max;                   /* 12 */
  pwmn_dead_time_t dead_time;               /* 14 */
  pwmn_prescaler_reload_t prescaler_reload; /* 16 */
  pwmn_cnt_max_reload_t cnt_max_reload;     /* 18 */
  pwmn_dead_time_reload_t dead_time_reload; /* 20 */
  pwmn_cnt_restart_t cnt_restart;           /* 22 */
  pwmn_nth_start_t nth_start;               /* 24 */
  pwmn_nth_start_reload_t nth_start_reload; /* 26 */
  unsigned short reserved0[1];
  pwmn_dead_time_reload_ch_t dead_time_reload_ch; /* 30 */
  pwmn_pwm_cfg_t pwm0_cfg;                        /* 32 */
  pwmn_pwm_c_t pwm0_c0;                           /* 34 */
  pwmn_pwm_c_t pwm0_c1;                           /* 36 */
  pwmn_pwm_on_t pwm0_on;                          /* 38 */
  pwmn_pwm_c_reload_t pwm0_c0_reload;             /* 40 */
  pwmn_pwm_c_reload_t pwm0_c1_reload;             /* 42 */
  pwmn_pwm_on_reload_t pwm0_on_reload;            /* 44 */
  pwmn_pwm_dead_time_t pwm0_dead_time;            /* 46 */
  pwmn_pwm_cfg_t pwm1_cfg;                        /* 48 */
  pwmn_pwm_c_t pwm1_c0;                           /* 50 */
  pwmn_pwm_c_t pwm1_c1;                           /* 52 */
  pwmn_pwm_on_t pwm1_on;                          /* 54 */
  pwmn_pwm_c_reload_t pwm1_c0_reload;             /* 56 */
  pwmn_pwm_c_reload_t pwm1_c1_reload;             /* 58 */
  pwmn_pwm_on_reload_t pwm1_on_reload;            /* 60 */
  pwmn_pwm_dead_time_t pwm1_dead_time;            /* 62 */
  pwmn_pwm_cfg_t pwm2_cfg;                        /* 64 */
  pwmn_pwm_c_t pwm2_c0;                           /* 66 */
  pwmn_pwm_c_t pwm2_c1;                           /* 68 */
  pwmn_pwm_on_t pwm2_on;                          /* 70 */
  pwmn_pwm_c_reload_t pwm2_c0_reload;             /* 72 */
  pwmn_pwm_c_reload_t pwm2_c1_reload;             /* 74 */
  pwmn_pwm_on_reload_t pwm2_on_reload;            /* 76 */
  pwmn_pwm_dead_time_t pwm2_dead_time;            /* 78 */
  pwmn_pwm_cfg_t pwm3_cfg;                        /* 80 */
  pwmn_pwm_c_t pwm3_c0;                           /* 82 */
  pwmn_pwm_c_t pwm3_c1;                           /* 84 */
  pwmn_pwm_on_t pwm3_on;                          /* 86 */
  pwmn_pwm_c_reload_t pwm3_c0_reload;             /* 88 */
  pwmn_pwm_c_reload_t pwm3_c1_reload;             /* 90 */
  pwmn_pwm_on_reload_t pwm3_on_reload;            /* 92 */
  pwmn_pwm_dead_time_t pwm3_dead_time;            /* 94 */
  unsigned short reserved1[8];
  pwmn_irq_status_t irq_status; /* 112 */
  unsigned short reserved2[1];
  pwmn_irq_mask_t irq_mask; /* 116 */
  unsigned short reserved3[1];
  pwmn_irq_venable_t irq_venable;   /* 120 */
  pwmn_irq_vdisable_t irq_vdisable; /* 122 */
  pwmn_irq_vmax_t irq_vmax;         /* 124 */
  pwmn_irq_vno_t irq_vno;           /* 126 */
} _PACKED_ pwmn_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_PWMN 0x0600U ... PWM Module

#define ADDR_PWMN_CFG (0x00U)
#define A_PWMN_CFG(ba) ((ba) + ADDR_PWMN_CFG)
#define R_PWMN_CFG(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_CFG(ba)))
#define RES_PWMN_CFG (0x0U)
#define MSB_PWMN_CFG 15
#define LSB_PWMN_CFG 0
#define AADDR_PWMN_CFG (BASE_ADDR_PWMN + ADDR_PWMN_CFG)
#define REG_PWMN_CFG (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_CFG))

#define ADDR_PWMN_CMD (0x02U)
#define A_PWMN_CMD(ba) ((ba) + ADDR_PWMN_CMD)
#define R_PWMN_CMD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_CMD(ba)))
#define RES_PWMN_CMD (0x0U)
#define MSB_PWMN_CMD 3
#define LSB_PWMN_CMD 0
#define AADDR_PWMN_CMD (BASE_ADDR_PWMN + ADDR_PWMN_CMD)
#define REG_PWMN_CMD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_CMD))

#define ADDR_PWMN_STATE (0x04U)
#define A_PWMN_STATE(ba) ((ba) + ADDR_PWMN_STATE)
#define R_PWMN_STATE(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_STATE(ba)))
#define RES_PWMN_STATE (0x0U)
#define MSB_PWMN_STATE 1
#define LSB_PWMN_STATE 0
#define AADDR_PWMN_STATE (BASE_ADDR_PWMN + ADDR_PWMN_STATE)
#define REG_PWMN_STATE (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_STATE))

#define ADDR_PWMN_CNT (0x06U)
#define A_PWMN_CNT(ba) ((ba) + ADDR_PWMN_CNT)
#define R_PWMN_CNT(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_CNT(ba)))
#define RES_PWMN_CNT (0x0U)
#define MSB_PWMN_CNT 15
#define LSB_PWMN_CNT 0
#define AADDR_PWMN_CNT (BASE_ADDR_PWMN + ADDR_PWMN_CNT)
#define REG_PWMN_CNT (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_CNT))

#define ADDR_PWMN_PWM_PHASE (0x08U)
#define A_PWMN_PWM_PHASE(ba) ((ba) + ADDR_PWMN_PWM_PHASE)
#define R_PWMN_PWM_PHASE(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM_PHASE(ba)))
#define RES_PWMN_PWM_PHASE (0x0U)
#define MSB_PWMN_PWM_PHASE 15
#define LSB_PWMN_PWM_PHASE 0
#define AADDR_PWMN_PWM_PHASE (BASE_ADDR_PWMN + ADDR_PWMN_PWM_PHASE)
#define REG_PWMN_PWM_PHASE (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM_PHASE))

#define ADDR_PWMN_PRESCALER (0x0AU)
#define A_PWMN_PRESCALER(ba) ((ba) + ADDR_PWMN_PRESCALER)
#define R_PWMN_PRESCALER(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PRESCALER(ba)))
#define RES_PWMN_PRESCALER (0x0U)
#define MSB_PWMN_PRESCALER 3
#define LSB_PWMN_PRESCALER 0
#define AADDR_PWMN_PRESCALER (BASE_ADDR_PWMN + ADDR_PWMN_PRESCALER)
#define REG_PWMN_PRESCALER (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PRESCALER))

#define ADDR_PWMN_CNT_MAX (0x0CU)
#define A_PWMN_CNT_MAX(ba) ((ba) + ADDR_PWMN_CNT_MAX)
#define R_PWMN_CNT_MAX(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_CNT_MAX(ba)))
#define RES_PWMN_CNT_MAX (0x1U)
#define MSB_PWMN_CNT_MAX 15
#define LSB_PWMN_CNT_MAX 0
#define AADDR_PWMN_CNT_MAX (BASE_ADDR_PWMN + ADDR_PWMN_CNT_MAX)
#define REG_PWMN_CNT_MAX (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_CNT_MAX))

#define ADDR_PWMN_DEAD_TIME (0x0EU)
#define A_PWMN_DEAD_TIME(ba) ((ba) + ADDR_PWMN_DEAD_TIME)
#define R_PWMN_DEAD_TIME(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_DEAD_TIME(ba)))
#define RES_PWMN_DEAD_TIME (0x0U)
#define MSB_PWMN_DEAD_TIME 7
#define LSB_PWMN_DEAD_TIME 0
#define AADDR_PWMN_DEAD_TIME (BASE_ADDR_PWMN + ADDR_PWMN_DEAD_TIME)
#define REG_PWMN_DEAD_TIME (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_DEAD_TIME))

#define ADDR_PWMN_PRESCALER_RELOAD (0x10U)
#define A_PWMN_PRESCALER_RELOAD(ba) ((ba) + ADDR_PWMN_PRESCALER_RELOAD)
#define R_PWMN_PRESCALER_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PRESCALER_RELOAD(ba)))
#define RES_PWMN_PRESCALER_RELOAD (0x0U)
#define MSB_PWMN_PRESCALER_RELOAD 3
#define LSB_PWMN_PRESCALER_RELOAD 0
#define AADDR_PWMN_PRESCALER_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PRESCALER_RELOAD)
#define REG_PWMN_PRESCALER_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PRESCALER_RELOAD))

#define ADDR_PWMN_CNT_MAX_RELOAD (0x12U)
#define A_PWMN_CNT_MAX_RELOAD(ba) ((ba) + ADDR_PWMN_CNT_MAX_RELOAD)
#define R_PWMN_CNT_MAX_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_CNT_MAX_RELOAD(ba)))
#define RES_PWMN_CNT_MAX_RELOAD (0x0U)
#define MSB_PWMN_CNT_MAX_RELOAD 15
#define LSB_PWMN_CNT_MAX_RELOAD 0
#define AADDR_PWMN_CNT_MAX_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_CNT_MAX_RELOAD)
#define REG_PWMN_CNT_MAX_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_CNT_MAX_RELOAD))

#define ADDR_PWMN_DEAD_TIME_RELOAD (0x14U)
#define A_PWMN_DEAD_TIME_RELOAD(ba) ((ba) + ADDR_PWMN_DEAD_TIME_RELOAD)
#define R_PWMN_DEAD_TIME_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_DEAD_TIME_RELOAD(ba)))
#define RES_PWMN_DEAD_TIME_RELOAD (0x0U)
#define MSB_PWMN_DEAD_TIME_RELOAD 7
#define LSB_PWMN_DEAD_TIME_RELOAD 0
#define AADDR_PWMN_DEAD_TIME_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_DEAD_TIME_RELOAD)
#define REG_PWMN_DEAD_TIME_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_DEAD_TIME_RELOAD))

#define ADDR_PWMN_CNT_RESTART (0x16U)
#define A_PWMN_CNT_RESTART(ba) ((ba) + ADDR_PWMN_CNT_RESTART)
#define R_PWMN_CNT_RESTART(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_CNT_RESTART(ba)))
#define RES_PWMN_CNT_RESTART (0x0U)
#define MSB_PWMN_CNT_RESTART 15
#define LSB_PWMN_CNT_RESTART 0
#define AADDR_PWMN_CNT_RESTART (BASE_ADDR_PWMN + ADDR_PWMN_CNT_RESTART)
#define REG_PWMN_CNT_RESTART (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_CNT_RESTART))

#define ADDR_PWMN_NTH_START (0x18U)
#define A_PWMN_NTH_START(ba) ((ba) + ADDR_PWMN_NTH_START)
#define R_PWMN_NTH_START(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_NTH_START(ba)))
#define RES_PWMN_NTH_START (0x0U)
#define MSB_PWMN_NTH_START 3
#define LSB_PWMN_NTH_START 0
#define AADDR_PWMN_NTH_START (BASE_ADDR_PWMN + ADDR_PWMN_NTH_START)
#define REG_PWMN_NTH_START (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_NTH_START))

#define ADDR_PWMN_NTH_START_RELOAD (0x1AU)
#define A_PWMN_NTH_START_RELOAD(ba) ((ba) + ADDR_PWMN_NTH_START_RELOAD)
#define R_PWMN_NTH_START_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_NTH_START_RELOAD(ba)))
#define RES_PWMN_NTH_START_RELOAD (0x0U)
#define MSB_PWMN_NTH_START_RELOAD 3
#define LSB_PWMN_NTH_START_RELOAD 0
#define AADDR_PWMN_NTH_START_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_NTH_START_RELOAD)
#define REG_PWMN_NTH_START_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_NTH_START_RELOAD))

#define ADDR_PWMN_DEAD_TIME_RELOAD_CH (0x1EU)
#define A_PWMN_DEAD_TIME_RELOAD_CH(ba) ((ba) + ADDR_PWMN_DEAD_TIME_RELOAD_CH)
#define R_PWMN_DEAD_TIME_RELOAD_CH(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_DEAD_TIME_RELOAD_CH(ba)))
#define RES_PWMN_DEAD_TIME_RELOAD_CH (0x0U)
#define MSB_PWMN_DEAD_TIME_RELOAD_CH 15
#define LSB_PWMN_DEAD_TIME_RELOAD_CH 0
#define AADDR_PWMN_DEAD_TIME_RELOAD_CH (BASE_ADDR_PWMN + ADDR_PWMN_DEAD_TIME_RELOAD_CH)
#define REG_PWMN_DEAD_TIME_RELOAD_CH (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_DEAD_TIME_RELOAD_CH))

#define ADDR_PWMN_PWM0_CFG (0x20U)
#define A_PWMN_PWM0_CFG(ba) ((ba) + ADDR_PWMN_PWM0_CFG)
#define R_PWMN_PWM0_CFG(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM0_CFG(ba)))
#define RES_PWMN_PWM0_CFG (0x0U)
#define MSB_PWMN_PWM0_CFG 5
#define LSB_PWMN_PWM0_CFG 0
#define AADDR_PWMN_PWM0_CFG (BASE_ADDR_PWMN + ADDR_PWMN_PWM0_CFG)
#define REG_PWMN_PWM0_CFG (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM0_CFG))

#define ADDR_PWMN_PWM0_C0 (0x22U)
#define A_PWMN_PWM0_C0(ba) ((ba) + ADDR_PWMN_PWM0_C0)
#define R_PWMN_PWM0_C0(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM0_C0(ba)))
#define RES_PWMN_PWM0_C0 (0x0U)
#define MSB_PWMN_PWM0_C0 15
#define LSB_PWMN_PWM0_C0 0
#define AADDR_PWMN_PWM0_C0 (BASE_ADDR_PWMN + ADDR_PWMN_PWM0_C0)
#define REG_PWMN_PWM0_C0 (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM0_C0))

#define ADDR_PWMN_PWM0_C1 (0x24U)
#define A_PWMN_PWM0_C1(ba) ((ba) + ADDR_PWMN_PWM0_C1)
#define R_PWMN_PWM0_C1(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM0_C1(ba)))
#define RES_PWMN_PWM0_C1 (0x0U)
#define MSB_PWMN_PWM0_C1 15
#define LSB_PWMN_PWM0_C1 0
#define AADDR_PWMN_PWM0_C1 (BASE_ADDR_PWMN + ADDR_PWMN_PWM0_C1)
#define REG_PWMN_PWM0_C1 (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM0_C1))

#define ADDR_PWMN_PWM0_ON (0x26U)
#define A_PWMN_PWM0_ON(ba) ((ba) + ADDR_PWMN_PWM0_ON)
#define R_PWMN_PWM0_ON(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM0_ON(ba)))
#define RES_PWMN_PWM0_ON (0x0U)
#define MSB_PWMN_PWM0_ON 1
#define LSB_PWMN_PWM0_ON 0
#define AADDR_PWMN_PWM0_ON (BASE_ADDR_PWMN + ADDR_PWMN_PWM0_ON)
#define REG_PWMN_PWM0_ON (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM0_ON))

#define ADDR_PWMN_PWM0_C0_RELOAD (0x28U)
#define A_PWMN_PWM0_C0_RELOAD(ba) ((ba) + ADDR_PWMN_PWM0_C0_RELOAD)
#define R_PWMN_PWM0_C0_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM0_C0_RELOAD(ba)))
#define RES_PWMN_PWM0_C0_RELOAD (0x0U)
#define MSB_PWMN_PWM0_C0_RELOAD 15
#define LSB_PWMN_PWM0_C0_RELOAD 0
#define AADDR_PWMN_PWM0_C0_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PWM0_C0_RELOAD)
#define REG_PWMN_PWM0_C0_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM0_C0_RELOAD))

#define ADDR_PWMN_PWM0_C1_RELOAD (0x2AU)
#define A_PWMN_PWM0_C1_RELOAD(ba) ((ba) + ADDR_PWMN_PWM0_C1_RELOAD)
#define R_PWMN_PWM0_C1_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM0_C1_RELOAD(ba)))
#define RES_PWMN_PWM0_C1_RELOAD (0x0U)
#define MSB_PWMN_PWM0_C1_RELOAD 15
#define LSB_PWMN_PWM0_C1_RELOAD 0
#define AADDR_PWMN_PWM0_C1_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PWM0_C1_RELOAD)
#define REG_PWMN_PWM0_C1_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM0_C1_RELOAD))

#define ADDR_PWMN_PWM0_ON_RELOAD (0x2CU)
#define A_PWMN_PWM0_ON_RELOAD(ba) ((ba) + ADDR_PWMN_PWM0_ON_RELOAD)
#define R_PWMN_PWM0_ON_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM0_ON_RELOAD(ba)))
#define RES_PWMN_PWM0_ON_RELOAD (0x0U)
#define MSB_PWMN_PWM0_ON_RELOAD 1
#define LSB_PWMN_PWM0_ON_RELOAD 0
#define AADDR_PWMN_PWM0_ON_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PWM0_ON_RELOAD)
#define REG_PWMN_PWM0_ON_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM0_ON_RELOAD))

#define ADDR_PWMN_PWM0_DEAD_TIME (0x2EU)
#define A_PWMN_PWM0_DEAD_TIME(ba) ((ba) + ADDR_PWMN_PWM0_DEAD_TIME)
#define R_PWMN_PWM0_DEAD_TIME(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM0_DEAD_TIME(ba)))
#define RES_PWMN_PWM0_DEAD_TIME (0x0U)
#define MSB_PWMN_PWM0_DEAD_TIME 15
#define LSB_PWMN_PWM0_DEAD_TIME 0
#define AADDR_PWMN_PWM0_DEAD_TIME (BASE_ADDR_PWMN + ADDR_PWMN_PWM0_DEAD_TIME)
#define REG_PWMN_PWM0_DEAD_TIME (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM0_DEAD_TIME))

#define ADDR_PWMN_PWM1_CFG (0x30U)
#define A_PWMN_PWM1_CFG(ba) ((ba) + ADDR_PWMN_PWM1_CFG)
#define R_PWMN_PWM1_CFG(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM1_CFG(ba)))
#define RES_PWMN_PWM1_CFG (0x0U)
#define MSB_PWMN_PWM1_CFG 5
#define LSB_PWMN_PWM1_CFG 0
#define AADDR_PWMN_PWM1_CFG (BASE_ADDR_PWMN + ADDR_PWMN_PWM1_CFG)
#define REG_PWMN_PWM1_CFG (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM1_CFG))

#define ADDR_PWMN_PWM1_C0 (0x32U)
#define A_PWMN_PWM1_C0(ba) ((ba) + ADDR_PWMN_PWM1_C0)
#define R_PWMN_PWM1_C0(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM1_C0(ba)))
#define RES_PWMN_PWM1_C0 (0x0U)
#define MSB_PWMN_PWM1_C0 15
#define LSB_PWMN_PWM1_C0 0
#define AADDR_PWMN_PWM1_C0 (BASE_ADDR_PWMN + ADDR_PWMN_PWM1_C0)
#define REG_PWMN_PWM1_C0 (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM1_C0))

#define ADDR_PWMN_PWM1_C1 (0x34U)
#define A_PWMN_PWM1_C1(ba) ((ba) + ADDR_PWMN_PWM1_C1)
#define R_PWMN_PWM1_C1(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM1_C1(ba)))
#define RES_PWMN_PWM1_C1 (0x0U)
#define MSB_PWMN_PWM1_C1 15
#define LSB_PWMN_PWM1_C1 0
#define AADDR_PWMN_PWM1_C1 (BASE_ADDR_PWMN + ADDR_PWMN_PWM1_C1)
#define REG_PWMN_PWM1_C1 (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM1_C1))

#define ADDR_PWMN_PWM1_ON (0x36U)
#define A_PWMN_PWM1_ON(ba) ((ba) + ADDR_PWMN_PWM1_ON)
#define R_PWMN_PWM1_ON(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM1_ON(ba)))
#define RES_PWMN_PWM1_ON (0x0U)
#define MSB_PWMN_PWM1_ON 1
#define LSB_PWMN_PWM1_ON 0
#define AADDR_PWMN_PWM1_ON (BASE_ADDR_PWMN + ADDR_PWMN_PWM1_ON)
#define REG_PWMN_PWM1_ON (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM1_ON))

#define ADDR_PWMN_PWM1_C0_RELOAD (0x38U)
#define A_PWMN_PWM1_C0_RELOAD(ba) ((ba) + ADDR_PWMN_PWM1_C0_RELOAD)
#define R_PWMN_PWM1_C0_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM1_C0_RELOAD(ba)))
#define RES_PWMN_PWM1_C0_RELOAD (0x0U)
#define MSB_PWMN_PWM1_C0_RELOAD 15
#define LSB_PWMN_PWM1_C0_RELOAD 0
#define AADDR_PWMN_PWM1_C0_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PWM1_C0_RELOAD)
#define REG_PWMN_PWM1_C0_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM1_C0_RELOAD))

#define ADDR_PWMN_PWM1_C1_RELOAD (0x3AU)
#define A_PWMN_PWM1_C1_RELOAD(ba) ((ba) + ADDR_PWMN_PWM1_C1_RELOAD)
#define R_PWMN_PWM1_C1_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM1_C1_RELOAD(ba)))
#define RES_PWMN_PWM1_C1_RELOAD (0x0U)
#define MSB_PWMN_PWM1_C1_RELOAD 15
#define LSB_PWMN_PWM1_C1_RELOAD 0
#define AADDR_PWMN_PWM1_C1_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PWM1_C1_RELOAD)
#define REG_PWMN_PWM1_C1_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM1_C1_RELOAD))

#define ADDR_PWMN_PWM1_ON_RELOAD (0x3CU)
#define A_PWMN_PWM1_ON_RELOAD(ba) ((ba) + ADDR_PWMN_PWM1_ON_RELOAD)
#define R_PWMN_PWM1_ON_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM1_ON_RELOAD(ba)))
#define RES_PWMN_PWM1_ON_RELOAD (0x0U)
#define MSB_PWMN_PWM1_ON_RELOAD 1
#define LSB_PWMN_PWM1_ON_RELOAD 0
#define AADDR_PWMN_PWM1_ON_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PWM1_ON_RELOAD)
#define REG_PWMN_PWM1_ON_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM1_ON_RELOAD))

#define ADDR_PWMN_PWM1_DEAD_TIME (0x3EU)
#define A_PWMN_PWM1_DEAD_TIME(ba) ((ba) + ADDR_PWMN_PWM1_DEAD_TIME)
#define R_PWMN_PWM1_DEAD_TIME(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM1_DEAD_TIME(ba)))
#define RES_PWMN_PWM1_DEAD_TIME (0x0U)
#define MSB_PWMN_PWM1_DEAD_TIME 15
#define LSB_PWMN_PWM1_DEAD_TIME 0
#define AADDR_PWMN_PWM1_DEAD_TIME (BASE_ADDR_PWMN + ADDR_PWMN_PWM1_DEAD_TIME)
#define REG_PWMN_PWM1_DEAD_TIME (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM1_DEAD_TIME))

#define ADDR_PWMN_PWM2_CFG (0x40U)
#define A_PWMN_PWM2_CFG(ba) ((ba) + ADDR_PWMN_PWM2_CFG)
#define R_PWMN_PWM2_CFG(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM2_CFG(ba)))
#define RES_PWMN_PWM2_CFG (0x0U)
#define MSB_PWMN_PWM2_CFG 5
#define LSB_PWMN_PWM2_CFG 0
#define AADDR_PWMN_PWM2_CFG (BASE_ADDR_PWMN + ADDR_PWMN_PWM2_CFG)
#define REG_PWMN_PWM2_CFG (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM2_CFG))

#define ADDR_PWMN_PWM2_C0 (0x42U)
#define A_PWMN_PWM2_C0(ba) ((ba) + ADDR_PWMN_PWM2_C0)
#define R_PWMN_PWM2_C0(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM2_C0(ba)))
#define RES_PWMN_PWM2_C0 (0x0U)
#define MSB_PWMN_PWM2_C0 15
#define LSB_PWMN_PWM2_C0 0
#define AADDR_PWMN_PWM2_C0 (BASE_ADDR_PWMN + ADDR_PWMN_PWM2_C0)
#define REG_PWMN_PWM2_C0 (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM2_C0))

#define ADDR_PWMN_PWM2_C1 (0x44U)
#define A_PWMN_PWM2_C1(ba) ((ba) + ADDR_PWMN_PWM2_C1)
#define R_PWMN_PWM2_C1(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM2_C1(ba)))
#define RES_PWMN_PWM2_C1 (0x0U)
#define MSB_PWMN_PWM2_C1 15
#define LSB_PWMN_PWM2_C1 0
#define AADDR_PWMN_PWM2_C1 (BASE_ADDR_PWMN + ADDR_PWMN_PWM2_C1)
#define REG_PWMN_PWM2_C1 (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM2_C1))

#define ADDR_PWMN_PWM2_ON (0x46U)
#define A_PWMN_PWM2_ON(ba) ((ba) + ADDR_PWMN_PWM2_ON)
#define R_PWMN_PWM2_ON(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM2_ON(ba)))
#define RES_PWMN_PWM2_ON (0x0U)
#define MSB_PWMN_PWM2_ON 1
#define LSB_PWMN_PWM2_ON 0
#define AADDR_PWMN_PWM2_ON (BASE_ADDR_PWMN + ADDR_PWMN_PWM2_ON)
#define REG_PWMN_PWM2_ON (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM2_ON))

#define ADDR_PWMN_PWM2_C0_RELOAD (0x48U)
#define A_PWMN_PWM2_C0_RELOAD(ba) ((ba) + ADDR_PWMN_PWM2_C0_RELOAD)
#define R_PWMN_PWM2_C0_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM2_C0_RELOAD(ba)))
#define RES_PWMN_PWM2_C0_RELOAD (0x0U)
#define MSB_PWMN_PWM2_C0_RELOAD 15
#define LSB_PWMN_PWM2_C0_RELOAD 0
#define AADDR_PWMN_PWM2_C0_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PWM2_C0_RELOAD)
#define REG_PWMN_PWM2_C0_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM2_C0_RELOAD))

#define ADDR_PWMN_PWM2_C1_RELOAD (0x4AU)
#define A_PWMN_PWM2_C1_RELOAD(ba) ((ba) + ADDR_PWMN_PWM2_C1_RELOAD)
#define R_PWMN_PWM2_C1_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM2_C1_RELOAD(ba)))
#define RES_PWMN_PWM2_C1_RELOAD (0x0U)
#define MSB_PWMN_PWM2_C1_RELOAD 15
#define LSB_PWMN_PWM2_C1_RELOAD 0
#define AADDR_PWMN_PWM2_C1_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PWM2_C1_RELOAD)
#define REG_PWMN_PWM2_C1_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM2_C1_RELOAD))

#define ADDR_PWMN_PWM2_ON_RELOAD (0x4CU)
#define A_PWMN_PWM2_ON_RELOAD(ba) ((ba) + ADDR_PWMN_PWM2_ON_RELOAD)
#define R_PWMN_PWM2_ON_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM2_ON_RELOAD(ba)))
#define RES_PWMN_PWM2_ON_RELOAD (0x0U)
#define MSB_PWMN_PWM2_ON_RELOAD 1
#define LSB_PWMN_PWM2_ON_RELOAD 0
#define AADDR_PWMN_PWM2_ON_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PWM2_ON_RELOAD)
#define REG_PWMN_PWM2_ON_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM2_ON_RELOAD))

#define ADDR_PWMN_PWM2_DEAD_TIME (0x4EU)
#define A_PWMN_PWM2_DEAD_TIME(ba) ((ba) + ADDR_PWMN_PWM2_DEAD_TIME)
#define R_PWMN_PWM2_DEAD_TIME(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM2_DEAD_TIME(ba)))
#define RES_PWMN_PWM2_DEAD_TIME (0x0U)
#define MSB_PWMN_PWM2_DEAD_TIME 15
#define LSB_PWMN_PWM2_DEAD_TIME 0
#define AADDR_PWMN_PWM2_DEAD_TIME (BASE_ADDR_PWMN + ADDR_PWMN_PWM2_DEAD_TIME)
#define REG_PWMN_PWM2_DEAD_TIME (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM2_DEAD_TIME))

#define ADDR_PWMN_PWM3_CFG (0x50U)
#define A_PWMN_PWM3_CFG(ba) ((ba) + ADDR_PWMN_PWM3_CFG)
#define R_PWMN_PWM3_CFG(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM3_CFG(ba)))
#define RES_PWMN_PWM3_CFG (0x0U)
#define MSB_PWMN_PWM3_CFG 5
#define LSB_PWMN_PWM3_CFG 0
#define AADDR_PWMN_PWM3_CFG (BASE_ADDR_PWMN + ADDR_PWMN_PWM3_CFG)
#define REG_PWMN_PWM3_CFG (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM3_CFG))

#define ADDR_PWMN_PWM3_C0 (0x52U)
#define A_PWMN_PWM3_C0(ba) ((ba) + ADDR_PWMN_PWM3_C0)
#define R_PWMN_PWM3_C0(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM3_C0(ba)))
#define RES_PWMN_PWM3_C0 (0x0U)
#define MSB_PWMN_PWM3_C0 15
#define LSB_PWMN_PWM3_C0 0
#define AADDR_PWMN_PWM3_C0 (BASE_ADDR_PWMN + ADDR_PWMN_PWM3_C0)
#define REG_PWMN_PWM3_C0 (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM3_C0))

#define ADDR_PWMN_PWM3_C1 (0x54U)
#define A_PWMN_PWM3_C1(ba) ((ba) + ADDR_PWMN_PWM3_C1)
#define R_PWMN_PWM3_C1(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM3_C1(ba)))
#define RES_PWMN_PWM3_C1 (0x0U)
#define MSB_PWMN_PWM3_C1 15
#define LSB_PWMN_PWM3_C1 0
#define AADDR_PWMN_PWM3_C1 (BASE_ADDR_PWMN + ADDR_PWMN_PWM3_C1)
#define REG_PWMN_PWM3_C1 (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM3_C1))

#define ADDR_PWMN_PWM3_ON (0x56U)
#define A_PWMN_PWM3_ON(ba) ((ba) + ADDR_PWMN_PWM3_ON)
#define R_PWMN_PWM3_ON(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM3_ON(ba)))
#define RES_PWMN_PWM3_ON (0x0U)
#define MSB_PWMN_PWM3_ON 1
#define LSB_PWMN_PWM3_ON 0
#define AADDR_PWMN_PWM3_ON (BASE_ADDR_PWMN + ADDR_PWMN_PWM3_ON)
#define REG_PWMN_PWM3_ON (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM3_ON))

#define ADDR_PWMN_PWM3_C0_RELOAD (0x58U)
#define A_PWMN_PWM3_C0_RELOAD(ba) ((ba) + ADDR_PWMN_PWM3_C0_RELOAD)
#define R_PWMN_PWM3_C0_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM3_C0_RELOAD(ba)))
#define RES_PWMN_PWM3_C0_RELOAD (0x0U)
#define MSB_PWMN_PWM3_C0_RELOAD 15
#define LSB_PWMN_PWM3_C0_RELOAD 0
#define AADDR_PWMN_PWM3_C0_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PWM3_C0_RELOAD)
#define REG_PWMN_PWM3_C0_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM3_C0_RELOAD))

#define ADDR_PWMN_PWM3_C1_RELOAD (0x5AU)
#define A_PWMN_PWM3_C1_RELOAD(ba) ((ba) + ADDR_PWMN_PWM3_C1_RELOAD)
#define R_PWMN_PWM3_C1_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM3_C1_RELOAD(ba)))
#define RES_PWMN_PWM3_C1_RELOAD (0x0U)
#define MSB_PWMN_PWM3_C1_RELOAD 15
#define LSB_PWMN_PWM3_C1_RELOAD 0
#define AADDR_PWMN_PWM3_C1_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PWM3_C1_RELOAD)
#define REG_PWMN_PWM3_C1_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM3_C1_RELOAD))

#define ADDR_PWMN_PWM3_ON_RELOAD (0x5CU)
#define A_PWMN_PWM3_ON_RELOAD(ba) ((ba) + ADDR_PWMN_PWM3_ON_RELOAD)
#define R_PWMN_PWM3_ON_RELOAD(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM3_ON_RELOAD(ba)))
#define RES_PWMN_PWM3_ON_RELOAD (0x0U)
#define MSB_PWMN_PWM3_ON_RELOAD 1
#define LSB_PWMN_PWM3_ON_RELOAD 0
#define AADDR_PWMN_PWM3_ON_RELOAD (BASE_ADDR_PWMN + ADDR_PWMN_PWM3_ON_RELOAD)
#define REG_PWMN_PWM3_ON_RELOAD (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM3_ON_RELOAD))

#define ADDR_PWMN_PWM3_DEAD_TIME (0x5EU)
#define A_PWMN_PWM3_DEAD_TIME(ba) ((ba) + ADDR_PWMN_PWM3_DEAD_TIME)
#define R_PWMN_PWM3_DEAD_TIME(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_PWM3_DEAD_TIME(ba)))
#define RES_PWMN_PWM3_DEAD_TIME (0x0U)
#define MSB_PWMN_PWM3_DEAD_TIME 15
#define LSB_PWMN_PWM3_DEAD_TIME 0
#define AADDR_PWMN_PWM3_DEAD_TIME (BASE_ADDR_PWMN + ADDR_PWMN_PWM3_DEAD_TIME)
#define REG_PWMN_PWM3_DEAD_TIME (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_PWM3_DEAD_TIME))

#define ADDR_PWMN_IRQ_STATUS (0x70U)
#define A_PWMN_IRQ_STATUS(ba) ((ba) + ADDR_PWMN_IRQ_STATUS)
#define R_PWMN_IRQ_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_IRQ_STATUS(ba)))
#define RES_PWMN_IRQ_STATUS (0x0U)
#define MSB_PWMN_IRQ_STATUS 10
#define LSB_PWMN_IRQ_STATUS 0
#define AADDR_PWMN_IRQ_STATUS (BASE_ADDR_PWMN + ADDR_PWMN_IRQ_STATUS)
#define REG_PWMN_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_IRQ_STATUS))

#define ADDR_PWMN_IRQ_MASK (0x74U)
#define A_PWMN_IRQ_MASK(ba) ((ba) + ADDR_PWMN_IRQ_MASK)
#define R_PWMN_IRQ_MASK(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_IRQ_MASK(ba)))
#define RES_PWMN_IRQ_MASK (0x0U)
#define MSB_PWMN_IRQ_MASK 10
#define LSB_PWMN_IRQ_MASK 0
#define AADDR_PWMN_IRQ_MASK (BASE_ADDR_PWMN + ADDR_PWMN_IRQ_MASK)
#define REG_PWMN_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_IRQ_MASK))

#define ADDR_PWMN_IRQ_VENABLE (0x78U)
#define A_PWMN_IRQ_VENABLE(ba) ((ba) + ADDR_PWMN_IRQ_VENABLE)
#define R_PWMN_IRQ_VENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_IRQ_VENABLE(ba)))
#define RES_PWMN_IRQ_VENABLE (0x0U)
#define MSB_PWMN_IRQ_VENABLE 3
#define LSB_PWMN_IRQ_VENABLE 0
#define AADDR_PWMN_IRQ_VENABLE (BASE_ADDR_PWMN + ADDR_PWMN_IRQ_VENABLE)
#define REG_PWMN_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_IRQ_VENABLE))

#define ADDR_PWMN_IRQ_VDISABLE (0x7AU)
#define A_PWMN_IRQ_VDISABLE(ba) ((ba) + ADDR_PWMN_IRQ_VDISABLE)
#define R_PWMN_IRQ_VDISABLE(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_IRQ_VDISABLE(ba)))
#define RES_PWMN_IRQ_VDISABLE (0x0U)
#define MSB_PWMN_IRQ_VDISABLE 3
#define LSB_PWMN_IRQ_VDISABLE 0
#define AADDR_PWMN_IRQ_VDISABLE (BASE_ADDR_PWMN + ADDR_PWMN_IRQ_VDISABLE)
#define REG_PWMN_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_IRQ_VDISABLE))

#define ADDR_PWMN_IRQ_VMAX (0x7CU)
#define A_PWMN_IRQ_VMAX(ba) ((ba) + ADDR_PWMN_IRQ_VMAX)
#define R_PWMN_IRQ_VMAX(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_IRQ_VMAX(ba)))
#define RES_PWMN_IRQ_VMAX (0xbU)
#define MSB_PWMN_IRQ_VMAX 3
#define LSB_PWMN_IRQ_VMAX 0
#define AADDR_PWMN_IRQ_VMAX (BASE_ADDR_PWMN + ADDR_PWMN_IRQ_VMAX)
#define REG_PWMN_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_IRQ_VMAX))

#define ADDR_PWMN_IRQ_VNO (0x7EU)
#define A_PWMN_IRQ_VNO(ba) ((ba) + ADDR_PWMN_IRQ_VNO)
#define R_PWMN_IRQ_VNO(ba) (*(volatile unsigned short *)((unsigned int)A_PWMN_IRQ_VNO(ba)))
#define RES_PWMN_IRQ_VNO (0xbU)
#define MSB_PWMN_IRQ_VNO 3
#define LSB_PWMN_IRQ_VNO 0
#define AADDR_PWMN_IRQ_VNO (BASE_ADDR_PWMN + ADDR_PWMN_IRQ_VNO)
#define REG_PWMN_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_PWMN_IRQ_VNO))

#endif
