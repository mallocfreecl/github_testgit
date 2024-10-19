#ifndef __PRE_PWM_BF_H__
#define __PRE_PWM_BF_H__

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

#ifndef BASE_ADDR_PRE_PWM
#define BASE_ADDR_PRE_PWM 0x0580U
#endif

#define NUMBER_PRE_PWM 1

typedef enum
{
  PRE_PWM = (int)BASE_ADDR_PRE_PWM
} pre_pwm_num_t;

// Register bit field definitions

/* PRE_PWM_CFG */

#define MSK_PRE_PWM_CFG_INC_EN (0x1) /* [0] */
#define SFT_PRE_PWM_CFG_INC_EN (0)
#define LSB_PRE_PWM_CFG_INC_EN (0)
#define MSB_PRE_PWM_CFG_INC_EN (0)
#define BIT_PRE_PWM_CFG_INC_EN (0x1) /* [0] */
#define MSK_PRE_PWM_CFG_DMA_EN (0x1) /* [1] */
#define SFT_PRE_PWM_CFG_DMA_EN (1)
#define LSB_PRE_PWM_CFG_DMA_EN (1)
#define MSB_PRE_PWM_CFG_DMA_EN (1)
#define BIT_PRE_PWM_CFG_DMA_EN (0x2)   /* [1] */
#define MSK_PRE_PWM_CFG_ON_STATE (0x3) /* [ 3:2] */
#define SFT_PRE_PWM_CFG_ON_STATE (2)
#define LSB_PRE_PWM_CFG_ON_STATE (2)
#define MSB_PRE_PWM_CFG_ON_STATE (3)
#define MSK_PRE_PWM_CFG_SWAP_UV (0x1) /* [4] */
#define SFT_PRE_PWM_CFG_SWAP_UV (4)
#define LSB_PRE_PWM_CFG_SWAP_UV (4)
#define MSB_PRE_PWM_CFG_SWAP_UV (4)
#define BIT_PRE_PWM_CFG_SWAP_UV (0x10)     /* [4] */
#define MSK_PRE_PWM_CFG_SWITCH_GD_TD (0x1) /* [5] */
#define SFT_PRE_PWM_CFG_SWITCH_GD_TD (5)
#define LSB_PRE_PWM_CFG_SWITCH_GD_TD (5)
#define MSB_PRE_PWM_CFG_SWITCH_GD_TD (5)
#define BIT_PRE_PWM_CFG_SWITCH_GD_TD (0x20) /* [5] */

typedef struct
{
  unsigned short inc_en : 1;       /* [0] */
  unsigned short dma_en : 1;       /* [1] */
  unsigned short on_state : 2;     /* [ 3:2] */
  unsigned short swap_uv : 1;      /* [4] */
  unsigned short switch_gd_td : 1; /* [5] */
  unsigned short reserved : 10;
} _PACKED_ pre_pwm_cfg_bf;

typedef union {
  unsigned short val;
  pre_pwm_cfg_bf bf;
} _PACKED_ pre_pwm_cfg_t;

/* PRE_PWM_BP_MAX */

#define MSK_PRE_PWM_BP_MAX (0xfff) /* [11:0] */

typedef unsigned short pre_pwm_bp_max_t; /* [11:0] */

/* PRE_PWM_ADDR_BASE */

#define MSK_PRE_PWM_ADDR_BASE (0xffff) /* [15:0] */

typedef unsigned short pre_pwm_addr_base_t; /* [15:0] */

/* PRE_PWM_CMD */

#define MSK_PRE_PWM_CMD_BPS0 (0x1) /* [0] */
#define SFT_PRE_PWM_CMD_BPS0 (0)
#define LSB_PRE_PWM_CMD_BPS0 (0)
#define MSB_PRE_PWM_CMD_BPS0 (0)
#define BIT_PRE_PWM_CMD_BPS0 (0x1)     /* [0] */
#define MSK_PRE_PWM_CMD_U_RELOAD (0x1) /* [1] */
#define SFT_PRE_PWM_CMD_U_RELOAD (1)
#define LSB_PRE_PWM_CMD_U_RELOAD (1)
#define MSB_PRE_PWM_CMD_U_RELOAD (1)
#define BIT_PRE_PWM_CMD_U_RELOAD (0x2) /* [1] */
#define MSK_PRE_PWM_CMD_V_RELOAD (0x1) /* [2] */
#define SFT_PRE_PWM_CMD_V_RELOAD (2)
#define LSB_PRE_PWM_CMD_V_RELOAD (2)
#define MSB_PRE_PWM_CMD_V_RELOAD (2)
#define BIT_PRE_PWM_CMD_V_RELOAD (0x4) /* [2] */
#define MSK_PRE_PWM_CMD_W_RELOAD (0x1) /* [3] */
#define SFT_PRE_PWM_CMD_W_RELOAD (3)
#define LSB_PRE_PWM_CMD_W_RELOAD (3)
#define MSB_PRE_PWM_CMD_W_RELOAD (3)
#define BIT_PRE_PWM_CMD_W_RELOAD (0x8) /* [3] */
#define MSK_PRE_PWM_CMD_U_DMA (0x1)    /* [4] */
#define SFT_PRE_PWM_CMD_U_DMA (4)
#define LSB_PRE_PWM_CMD_U_DMA (4)
#define MSB_PRE_PWM_CMD_U_DMA (4)
#define BIT_PRE_PWM_CMD_U_DMA (0x10) /* [4] */
#define MSK_PRE_PWM_CMD_V_DMA (0x1)  /* [5] */
#define SFT_PRE_PWM_CMD_V_DMA (5)
#define LSB_PRE_PWM_CMD_V_DMA (5)
#define MSB_PRE_PWM_CMD_V_DMA (5)
#define BIT_PRE_PWM_CMD_V_DMA (0x20) /* [5] */
#define MSK_PRE_PWM_CMD_W_DMA (0x1)  /* [6] */
#define SFT_PRE_PWM_CMD_W_DMA (6)
#define LSB_PRE_PWM_CMD_W_DMA (6)
#define MSB_PRE_PWM_CMD_W_DMA (6)
#define BIT_PRE_PWM_CMD_W_DMA (0x40)    /* [6] */
#define MSK_PRE_PWM_CMD_UVW_SCALE (0x1) /* [7] */
#define SFT_PRE_PWM_CMD_UVW_SCALE (7)
#define LSB_PRE_PWM_CMD_UVW_SCALE (7)
#define MSB_PRE_PWM_CMD_UVW_SCALE (7)
#define BIT_PRE_PWM_CMD_UVW_SCALE (0x80) /* [7] */

typedef struct
{
  unsigned short bps0 : 1;      /* [0] */
  unsigned short u_reload : 1;  /* [1] */
  unsigned short v_reload : 1;  /* [2] */
  unsigned short w_reload : 1;  /* [3] */
  unsigned short u_dma : 1;     /* [4] */
  unsigned short v_dma : 1;     /* [5] */
  unsigned short w_dma : 1;     /* [6] */
  unsigned short uvw_scale : 1; /* [7] */
  unsigned short reserved : 8;
} _PACKED_ pre_pwm_cmd_bf;

typedef union {
  unsigned short val;
  pre_pwm_cmd_bf bf;
} _PACKED_ pre_pwm_cmd_t;

/* PRE_PWM_INC */

#define MSK_PRE_PWM_INC (0xffff) /* [15:0] */

typedef unsigned short pre_pwm_inc_t; /* [15:0] */

/* PRE_PWM_ACC */

#define MSK_PRE_PWM_ACC (0xffff) /* [15:0] */

typedef unsigned short pre_pwm_acc_t; /* [15:0] */

/* PRE_PWM_BASE_PHASE */

#define MSK_PRE_PWM_BASE_PHASE (0xfff) /* [11:0] */

typedef unsigned short pre_pwm_base_phase_t; /* [11:0] */

/* PRE_PWM_SCALE */

#define MSK_PRE_PWM_SCALE_SCALE (0xfff) /* [11:0] */
#define SFT_PRE_PWM_SCALE_SCALE (0)
#define LSB_PRE_PWM_SCALE_SCALE (0)
#define MSB_PRE_PWM_SCALE_SCALE (11)
#define MSK_PRE_PWM_SCALE_SCALE_SHIFT (0x7) /* [14:12] */
#define SFT_PRE_PWM_SCALE_SCALE_SHIFT (12)
#define LSB_PRE_PWM_SCALE_SCALE_SHIFT (12)
#define MSB_PRE_PWM_SCALE_SCALE_SHIFT (14)

typedef struct
{
  unsigned short scale : 12;      /* [11:0] */
  unsigned short scale_shift : 3; /* [14:12] */
  unsigned short reserved : 1;
} _PACKED_ pre_pwm_scale_bf;

typedef union {
  unsigned short val;
  pre_pwm_scale_bf bf;
} _PACKED_ pre_pwm_scale_t;

/* PRE_PWM_SCALE_OFFSET */

#define MSK_PRE_PWM_SCALE_OFFSET (0x7fff) /* [14:0] */

typedef unsigned short pre_pwm_scale_offset_t; /* [14:0] */

/* PRE_PWM_LIMIT_LOW */

#define MSK_PRE_PWM_LIMIT_LOW (0xffff) /* [15:0] */

typedef unsigned short pre_pwm_limit_low_t; /* [15:0] */

/* PRE_PWM_LIMIT_LOW_SET */

#define MSK_PRE_PWM_LIMIT_LOW_SET (0xffff) /* [15:0] */

typedef unsigned short pre_pwm_limit_low_set_t; /* [15:0] */

/* PRE_PWM_LIMIT_HIGH */

#define MSK_PRE_PWM_LIMIT_HIGH (0xffff) /* [15:0] */

typedef unsigned short pre_pwm_limit_high_t; /* [15:0] */

/* PRE_PWM_LIMIT_HIGH_SET */

#define MSK_PRE_PWM_LIMIT_HIGH_SET (0xffff) /* [15:0] */

typedef unsigned short pre_pwm_limit_high_set_t; /* [15:0] */

/* PRE_PWM_BP_SYNC */

#define MSK_PRE_PWM_BP_SYNC (0xfff) /* [11:0] */

typedef unsigned short pre_pwm_bp_sync_t; /* [11:0] */

/* PRE_PWM_SYNC_EN */

#define MSK_PRE_PWM_SYNC_EN_BPS0 (0x3) /* [ 1:0] */
#define SFT_PRE_PWM_SYNC_EN_BPS0 (0)
#define LSB_PRE_PWM_SYNC_EN_BPS0 (0)
#define MSB_PRE_PWM_SYNC_EN_BPS0 (1)
#define MSK_PRE_PWM_SYNC_EN_BPS1 (0x3) /* [ 3:2] */
#define SFT_PRE_PWM_SYNC_EN_BPS1 (2)
#define LSB_PRE_PWM_SYNC_EN_BPS1 (2)
#define MSB_PRE_PWM_SYNC_EN_BPS1 (3)

typedef struct
{
  unsigned short bps0 : 2; /* [ 1:0] */
  unsigned short bps1 : 2; /* [ 3:2] */
  unsigned short reserved : 12;
} _PACKED_ pre_pwm_sync_en_bf;

typedef union {
  unsigned short val;
  pre_pwm_sync_en_bf bf;
} _PACKED_ pre_pwm_sync_en_t;

/* PRE_PWM_SYNC_EXT_CFG */

#define MSK_PRE_PWM_SYNC_EXT_CFG_SRC (0x3) /* [ 1:0] */
#define SFT_PRE_PWM_SYNC_EXT_CFG_SRC (0)
#define LSB_PRE_PWM_SYNC_EXT_CFG_SRC (0)
#define MSB_PRE_PWM_SYNC_EXT_CFG_SRC (1)
#define MSK_PRE_PWM_SYNC_EXT_CFG_INTF (0xff) /* [ 9:2] */
#define SFT_PRE_PWM_SYNC_EXT_CFG_INTF (2)
#define LSB_PRE_PWM_SYNC_EXT_CFG_INTF (2)
#define MSB_PRE_PWM_SYNC_EXT_CFG_INTF (9)
#define MSK_PRE_PWM_SYNC_EXT_CFG_INTF_SET (0x3) /* [11:10] */
#define SFT_PRE_PWM_SYNC_EXT_CFG_INTF_SET (10)
#define LSB_PRE_PWM_SYNC_EXT_CFG_INTF_SET (10)
#define MSB_PRE_PWM_SYNC_EXT_CFG_INTF_SET (11)
#define MSK_PRE_PWM_SYNC_EXT_CFG_EDGE (0x1) /* [12] */
#define SFT_PRE_PWM_SYNC_EXT_CFG_EDGE (12)
#define LSB_PRE_PWM_SYNC_EXT_CFG_EDGE (12)
#define MSB_PRE_PWM_SYNC_EXT_CFG_EDGE (12)
#define BIT_PRE_PWM_SYNC_EXT_CFG_EDGE (0x1000) /* [12] */

typedef struct
{
  unsigned short src : 2;      /* [ 1:0] */
  unsigned short intf : 8;     /* [ 9:2] */
  unsigned short intf_set : 2; /* [11:10] */
  unsigned short edge : 1;     /* [12] */
  unsigned short reserved : 3;
} _PACKED_ pre_pwm_sync_ext_cfg_bf;

typedef union {
  unsigned short val;
  pre_pwm_sync_ext_cfg_bf bf;
} _PACKED_ pre_pwm_sync_ext_cfg_t;

/* PRE_PWM_SCALE_SYNC */

#define MSK_PRE_PWM_SCALE_SYNC_SCALE (0xfff) /* [11:0] */
#define SFT_PRE_PWM_SCALE_SYNC_SCALE (0)
#define LSB_PRE_PWM_SCALE_SYNC_SCALE (0)
#define MSB_PRE_PWM_SCALE_SYNC_SCALE (11)
#define MSK_PRE_PWM_SCALE_SYNC_SCALE_SHIFT (0x7) /* [14:12] */
#define SFT_PRE_PWM_SCALE_SYNC_SCALE_SHIFT (12)
#define LSB_PRE_PWM_SCALE_SYNC_SCALE_SHIFT (12)
#define MSB_PRE_PWM_SCALE_SYNC_SCALE_SHIFT (14)

typedef struct
{
  unsigned short scale : 12;      /* [11:0] */
  unsigned short scale_shift : 3; /* [14:12] */
  unsigned short reserved : 1;
} _PACKED_ pre_pwm_scale_sync_bf;

typedef union {
  unsigned short val;
  pre_pwm_scale_sync_bf bf;
} _PACKED_ pre_pwm_scale_sync_t;

/* PRE_PWM_INC_SYNC */

#define MSK_PRE_PWM_INC_SYNC (0xffff) /* [15:0] */

typedef unsigned short pre_pwm_inc_sync_t; /* [15:0] */

/* PRE_PWM_ADDR */

#define MSK_PRE_PWM_ADDR (0x7ff) /* [10:0] */

typedef unsigned short pre_pwm_addr_t; /* [10:0] */

/* PRE_PWM_LW */

#define MSK_PRE_PWM_LW_DURATION (0x1ff) /* [ 8:0] */
#define SFT_PRE_PWM_LW_DURATION (0)
#define LSB_PRE_PWM_LW_DURATION (0)
#define MSB_PRE_PWM_LW_DURATION (8)
#define MSK_PRE_PWM_LW_SLOPE (0x7f) /* [15:9] */
#define SFT_PRE_PWM_LW_SLOPE (9)
#define LSB_PRE_PWM_LW_SLOPE (9)
#define MSB_PRE_PWM_LW_SLOPE (15)

typedef struct
{
  unsigned short duration : 9; /* [ 8:0] */
  unsigned short slope : 7;    /* [15:9] */
} _PACKED_ pre_pwm_lw_bf;

typedef union {
  unsigned short val;
  pre_pwm_lw_bf bf;
} _PACKED_ pre_pwm_lw_t;

/* PRE_PWM_HW */

#define MSK_PRE_PWM_HW_SLOPE_ACC (0x7fff) /* [14:0] */
#define SFT_PRE_PWM_HW_SLOPE_ACC (0)
#define LSB_PRE_PWM_HW_SLOPE_ACC (0)
#define MSB_PRE_PWM_HW_SLOPE_ACC (14)
#define MSK_PRE_PWM_HW_USE_CFG_ON (0x1) /* [15] */
#define SFT_PRE_PWM_HW_USE_CFG_ON (15)
#define LSB_PRE_PWM_HW_USE_CFG_ON (15)
#define MSB_PRE_PWM_HW_USE_CFG_ON (15)
#define BIT_PRE_PWM_HW_USE_CFG_ON (0x8000) /* [15] */

typedef struct
{
  unsigned short slope_acc : 15; /* [14:0] */
  unsigned short use_cfg_on : 1; /* [15] */
} _PACKED_ pre_pwm_hw_bf;

typedef union {
  unsigned short val;
  pre_pwm_hw_bf bf;
} _PACKED_ pre_pwm_hw_t;

/* PRE_PWM_LW_RLD */

#define MSK_PRE_PWM_LW_RLD_DURATION (0x1ff) /* [ 8:0] */
#define SFT_PRE_PWM_LW_RLD_DURATION (0)
#define LSB_PRE_PWM_LW_RLD_DURATION (0)
#define MSB_PRE_PWM_LW_RLD_DURATION (8)
#define MSK_PRE_PWM_LW_RLD_SLOPE (0x7f) /* [15:9] */
#define SFT_PRE_PWM_LW_RLD_SLOPE (9)
#define LSB_PRE_PWM_LW_RLD_SLOPE (9)
#define MSB_PRE_PWM_LW_RLD_SLOPE (15)

typedef struct
{
  unsigned short duration : 9; /* [ 8:0] */
  unsigned short slope : 7;    /* [15:9] */
} _PACKED_ pre_pwm_lw_rld_bf;

typedef union {
  unsigned short val;
  pre_pwm_lw_rld_bf bf;
} _PACKED_ pre_pwm_lw_rld_t;

/* PRE_PWM_HW_RLD */

#define MSK_PRE_PWM_HW_RLD_SLOPE_ACC (0x7fff) /* [14:0] */
#define SFT_PRE_PWM_HW_RLD_SLOPE_ACC (0)
#define LSB_PRE_PWM_HW_RLD_SLOPE_ACC (0)
#define MSB_PRE_PWM_HW_RLD_SLOPE_ACC (14)
#define MSK_PRE_PWM_HW_RLD_USE_CFG_ON (0x1) /* [15] */
#define SFT_PRE_PWM_HW_RLD_USE_CFG_ON (15)
#define LSB_PRE_PWM_HW_RLD_USE_CFG_ON (15)
#define MSB_PRE_PWM_HW_RLD_USE_CFG_ON (15)
#define BIT_PRE_PWM_HW_RLD_USE_CFG_ON (0x8000) /* [15] */

typedef struct
{
  unsigned short slope_acc : 15; /* [14:0] */
  unsigned short use_cfg_on : 1; /* [15] */
} _PACKED_ pre_pwm_hw_rld_bf;

typedef union {
  unsigned short val;
  pre_pwm_hw_rld_bf bf;
} _PACKED_ pre_pwm_hw_rld_t;

/* PRE_PWM_IRQ_STATUS */

#define MSK_PRE_PWM_IRQ_STATUS_BPS0_EVT (0x1) /* [0] */
#define SFT_PRE_PWM_IRQ_STATUS_BPS0_EVT (0)
#define LSB_PRE_PWM_IRQ_STATUS_BPS0_EVT (0)
#define MSB_PRE_PWM_IRQ_STATUS_BPS0_EVT (0)
#define BIT_PRE_PWM_IRQ_STATUS_BPS0_EVT (0x1) /* [0] */
#define MSK_PRE_PWM_IRQ_STATUS_BPS1_EVT (0x1) /* [1] */
#define SFT_PRE_PWM_IRQ_STATUS_BPS1_EVT (1)
#define LSB_PRE_PWM_IRQ_STATUS_BPS1_EVT (1)
#define MSB_PRE_PWM_IRQ_STATUS_BPS1_EVT (1)
#define BIT_PRE_PWM_IRQ_STATUS_BPS1_EVT (0x2)     /* [1] */
#define MSK_PRE_PWM_IRQ_STATUS_U_RELOAD_EVT (0x1) /* [2] */
#define SFT_PRE_PWM_IRQ_STATUS_U_RELOAD_EVT (2)
#define LSB_PRE_PWM_IRQ_STATUS_U_RELOAD_EVT (2)
#define MSB_PRE_PWM_IRQ_STATUS_U_RELOAD_EVT (2)
#define BIT_PRE_PWM_IRQ_STATUS_U_RELOAD_EVT (0x4) /* [2] */
#define MSK_PRE_PWM_IRQ_STATUS_V_RELOAD_EVT (0x1) /* [3] */
#define SFT_PRE_PWM_IRQ_STATUS_V_RELOAD_EVT (3)
#define LSB_PRE_PWM_IRQ_STATUS_V_RELOAD_EVT (3)
#define MSB_PRE_PWM_IRQ_STATUS_V_RELOAD_EVT (3)
#define BIT_PRE_PWM_IRQ_STATUS_V_RELOAD_EVT (0x8) /* [3] */
#define MSK_PRE_PWM_IRQ_STATUS_W_RELOAD_EVT (0x1) /* [4] */
#define SFT_PRE_PWM_IRQ_STATUS_W_RELOAD_EVT (4)
#define LSB_PRE_PWM_IRQ_STATUS_W_RELOAD_EVT (4)
#define MSB_PRE_PWM_IRQ_STATUS_W_RELOAD_EVT (4)
#define BIT_PRE_PWM_IRQ_STATUS_W_RELOAD_EVT (0x10)    /* [4] */
#define MSK_PRE_PWM_IRQ_STATUS_RELOAD_ERROR_EVT (0x1) /* [5] */
#define SFT_PRE_PWM_IRQ_STATUS_RELOAD_ERROR_EVT (5)
#define LSB_PRE_PWM_IRQ_STATUS_RELOAD_ERROR_EVT (5)
#define MSB_PRE_PWM_IRQ_STATUS_RELOAD_ERROR_EVT (5)
#define BIT_PRE_PWM_IRQ_STATUS_RELOAD_ERROR_EVT (0x20) /* [5] */
#define MSK_PRE_PWM_IRQ_STATUS_U_DMA_RDY (0x1)         /* [6] */
#define SFT_PRE_PWM_IRQ_STATUS_U_DMA_RDY (6)
#define LSB_PRE_PWM_IRQ_STATUS_U_DMA_RDY (6)
#define MSB_PRE_PWM_IRQ_STATUS_U_DMA_RDY (6)
#define BIT_PRE_PWM_IRQ_STATUS_U_DMA_RDY (0x40) /* [6] */
#define MSK_PRE_PWM_IRQ_STATUS_V_DMA_RDY (0x1)  /* [7] */
#define SFT_PRE_PWM_IRQ_STATUS_V_DMA_RDY (7)
#define LSB_PRE_PWM_IRQ_STATUS_V_DMA_RDY (7)
#define MSB_PRE_PWM_IRQ_STATUS_V_DMA_RDY (7)
#define BIT_PRE_PWM_IRQ_STATUS_V_DMA_RDY (0x80) /* [7] */
#define MSK_PRE_PWM_IRQ_STATUS_W_DMA_RDY (0x1)  /* [8] */
#define SFT_PRE_PWM_IRQ_STATUS_W_DMA_RDY (8)
#define LSB_PRE_PWM_IRQ_STATUS_W_DMA_RDY (8)
#define MSB_PRE_PWM_IRQ_STATUS_W_DMA_RDY (8)
#define BIT_PRE_PWM_IRQ_STATUS_W_DMA_RDY (0x100) /* [8] */

typedef struct
{
  unsigned short bps0_evt : 1;         /* [0] */
  unsigned short bps1_evt : 1;         /* [1] */
  unsigned short u_reload_evt : 1;     /* [2] */
  unsigned short v_reload_evt : 1;     /* [3] */
  unsigned short w_reload_evt : 1;     /* [4] */
  unsigned short reload_error_evt : 1; /* [5] */
  unsigned short u_dma_rdy : 1;        /* [6] */
  unsigned short v_dma_rdy : 1;        /* [7] */
  unsigned short w_dma_rdy : 1;        /* [8] */
  unsigned short reserved : 7;
} _PACKED_ pre_pwm_irq_status_bf;

typedef union {
  unsigned short val;
  pre_pwm_irq_status_bf bf;
} _PACKED_ pre_pwm_irq_status_t;

/* PRE_PWM_IRQ_MASK */

#define MSK_PRE_PWM_IRQ_MASK (0x1ff) /* [ 8:0] */

typedef unsigned short pre_pwm_irq_mask_t; /* [ 8:0] */

/* PRE_PWM_IRQ_VENABLE */

#define MSK_PRE_PWM_IRQ_VENABLE (0xf) /* [ 3:0] */

typedef unsigned short pre_pwm_irq_venable_t; /* [ 3:0] */

/* PRE_PWM_IRQ_VDISABLE */

#define MSK_PRE_PWM_IRQ_VDISABLE (0xf) /* [ 3:0] */

typedef unsigned short pre_pwm_irq_vdisable_t; /* [ 3:0] */

/* PRE_PWM_IRQ_VMAX */

#define MSK_PRE_PWM_IRQ_VMAX (0xf) /* [ 3:0] */

typedef unsigned short pre_pwm_irq_vmax_t; /* [ 3:0] */

/* PRE_PWM_IRQ_VNO */

#define MSK_PRE_PWM_IRQ_VNO (0xf) /* [ 3:0] */

typedef unsigned short pre_pwm_irq_vno_t; /* [ 3:0] */

/* PRE_PWM */

typedef struct
{
  pre_pwm_cfg_t cfg;                       /* 0 */
  pre_pwm_bp_max_t bp_max;                 /* 2 */
  pre_pwm_addr_base_t addr_base;           /* 4 */
  pre_pwm_cmd_t cmd;                       /* 6 */
  pre_pwm_inc_t inc;                       /* 8 */
  pre_pwm_acc_t acc;                       /* 10 */
  pre_pwm_base_phase_t base_phase;         /* 12 */
  pre_pwm_scale_t scale;                   /* 14 */
  pre_pwm_scale_offset_t scale_offset0;    /* 16 */
  pre_pwm_bp_sync_t bp_sync0;              /* 18 */
  pre_pwm_bp_sync_t bp_sync1;              /* 20 */
  pre_pwm_sync_en_t sync_en;               /* 22 */
  pre_pwm_sync_ext_cfg_t sync_ext_cfg;     /* 24 */
  pre_pwm_scale_sync_t scale_sync;         /* 26 */
  pre_pwm_inc_sync_t inc_sync;             /* 28 */
  pre_pwm_scale_offset_t scale_offset1;    /* 30 */
  pre_pwm_limit_low_t limit_low;           /* 32 */
  pre_pwm_limit_low_set_t limit_low_set;   /* 34 */
  pre_pwm_limit_high_t limit_high;         /* 36 */
  pre_pwm_limit_high_set_t limit_high_set; /* 38 */
  unsigned short reserved0[4];
  pre_pwm_addr_t u_addr;     /* 48 */
  pre_pwm_lw_t u_lw;         /* 50 */
  pre_pwm_hw_t u_hw;         /* 52 */
  pre_pwm_lw_rld_t u_lw_rld; /* 54 */
  pre_pwm_hw_rld_t u_hw_rld; /* 56 */
  unsigned short reserved1[3];
  pre_pwm_addr_t v_addr;     /* 64 */
  pre_pwm_lw_t v_lw;         /* 66 */
  pre_pwm_hw_t v_hw;         /* 68 */
  pre_pwm_lw_rld_t v_lw_rld; /* 70 */
  pre_pwm_hw_rld_t v_hw_rld; /* 72 */
  unsigned short reserved2[3];
  pre_pwm_addr_t w_addr;     /* 80 */
  pre_pwm_lw_t w_lw;         /* 82 */
  pre_pwm_hw_t w_hw;         /* 84 */
  pre_pwm_lw_rld_t w_lw_rld; /* 86 */
  pre_pwm_hw_rld_t w_hw_rld; /* 88 */
  unsigned short reserved3[11];
  pre_pwm_irq_status_t irq_status; /* 112 */
  unsigned short reserved4[1];
  pre_pwm_irq_mask_t irq_mask; /* 116 */
  unsigned short reserved5[1];
  pre_pwm_irq_venable_t irq_venable;   /* 120 */
  pre_pwm_irq_vdisable_t irq_vdisable; /* 122 */
  pre_pwm_irq_vmax_t irq_vmax;         /* 124 */
  pre_pwm_irq_vno_t irq_vno;           /* 126 */
} _PACKED_ pre_pwm_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_PRE_PWM 0x0580U ... Pre-PWM Module

#define ADDR_PRE_PWM_CFG (0x00U)
#define A_PRE_PWM_CFG(ba) ((ba) + ADDR_PRE_PWM_CFG)
#define R_PRE_PWM_CFG(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_CFG(ba)))
#define RES_PRE_PWM_CFG (0x0U)
#define MSB_PRE_PWM_CFG 5
#define LSB_PRE_PWM_CFG 0
#define AADDR_PRE_PWM_CFG (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_CFG)
#define REG_PRE_PWM_CFG (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_CFG))

#define ADDR_PRE_PWM_BP_MAX (0x02U)
#define A_PRE_PWM_BP_MAX(ba) ((ba) + ADDR_PRE_PWM_BP_MAX)
#define R_PRE_PWM_BP_MAX(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_BP_MAX(ba)))
#define RES_PRE_PWM_BP_MAX (0x0U)
#define MSB_PRE_PWM_BP_MAX 11
#define LSB_PRE_PWM_BP_MAX 0
#define AADDR_PRE_PWM_BP_MAX (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_BP_MAX)
#define REG_PRE_PWM_BP_MAX (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_BP_MAX))

#define ADDR_PRE_PWM_ADDR_BASE (0x04U)
#define A_PRE_PWM_ADDR_BASE(ba) ((ba) + ADDR_PRE_PWM_ADDR_BASE)
#define R_PRE_PWM_ADDR_BASE(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_ADDR_BASE(ba)))
#define RES_PRE_PWM_ADDR_BASE (0x0U)
#define MSB_PRE_PWM_ADDR_BASE 15
#define LSB_PRE_PWM_ADDR_BASE 0
#define AADDR_PRE_PWM_ADDR_BASE (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_ADDR_BASE)
#define REG_PRE_PWM_ADDR_BASE (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_ADDR_BASE))

#define ADDR_PRE_PWM_CMD (0x06U)
#define A_PRE_PWM_CMD(ba) ((ba) + ADDR_PRE_PWM_CMD)
#define R_PRE_PWM_CMD(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_CMD(ba)))
#define RES_PRE_PWM_CMD (0x0U)
#define MSB_PRE_PWM_CMD 7
#define LSB_PRE_PWM_CMD 0
#define AADDR_PRE_PWM_CMD (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_CMD)
#define REG_PRE_PWM_CMD (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_CMD))

#define ADDR_PRE_PWM_INC (0x08U)
#define A_PRE_PWM_INC(ba) ((ba) + ADDR_PRE_PWM_INC)
#define R_PRE_PWM_INC(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_INC(ba)))
#define RES_PRE_PWM_INC (0x0U)
#define MSB_PRE_PWM_INC 15
#define LSB_PRE_PWM_INC 0
#define AADDR_PRE_PWM_INC (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_INC)
#define REG_PRE_PWM_INC (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_INC))

#define ADDR_PRE_PWM_ACC (0x0AU)
#define A_PRE_PWM_ACC(ba) ((ba) + ADDR_PRE_PWM_ACC)
#define R_PRE_PWM_ACC(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_ACC(ba)))
#define RES_PRE_PWM_ACC (0x0U)
#define MSB_PRE_PWM_ACC 15
#define LSB_PRE_PWM_ACC 0
#define AADDR_PRE_PWM_ACC (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_ACC)
#define REG_PRE_PWM_ACC (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_ACC))

#define ADDR_PRE_PWM_BASE_PHASE (0x0CU)
#define A_PRE_PWM_BASE_PHASE(ba) ((ba) + ADDR_PRE_PWM_BASE_PHASE)
#define R_PRE_PWM_BASE_PHASE(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_BASE_PHASE(ba)))
#define RES_PRE_PWM_BASE_PHASE (0x0U)
#define MSB_PRE_PWM_BASE_PHASE 11
#define LSB_PRE_PWM_BASE_PHASE 0
#define AADDR_PRE_PWM_BASE_PHASE (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_BASE_PHASE)
#define REG_PRE_PWM_BASE_PHASE (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_BASE_PHASE))

#define ADDR_PRE_PWM_SCALE (0x0EU)
#define A_PRE_PWM_SCALE(ba) ((ba) + ADDR_PRE_PWM_SCALE)
#define R_PRE_PWM_SCALE(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_SCALE(ba)))
#define RES_PRE_PWM_SCALE (0x0U)
#define MSB_PRE_PWM_SCALE 14
#define LSB_PRE_PWM_SCALE 0
#define AADDR_PRE_PWM_SCALE (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_SCALE)
#define REG_PRE_PWM_SCALE (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_SCALE))

#define ADDR_PRE_PWM_SCALE_OFFSET0 (0x10U)
#define A_PRE_PWM_SCALE_OFFSET0(ba) ((ba) + ADDR_PRE_PWM_SCALE_OFFSET0)
#define R_PRE_PWM_SCALE_OFFSET0(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_SCALE_OFFSET0(ba)))
#define RES_PRE_PWM_SCALE_OFFSET0 (0x0U)
#define MSB_PRE_PWM_SCALE_OFFSET0 14
#define LSB_PRE_PWM_SCALE_OFFSET0 0
#define AADDR_PRE_PWM_SCALE_OFFSET0 (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_SCALE_OFFSET0)
#define REG_PRE_PWM_SCALE_OFFSET0 (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_SCALE_OFFSET0))

#define ADDR_PRE_PWM_BP_SYNC0 (0x12U)
#define A_PRE_PWM_BP_SYNC0(ba) ((ba) + ADDR_PRE_PWM_BP_SYNC0)
#define R_PRE_PWM_BP_SYNC0(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_BP_SYNC0(ba)))
#define RES_PRE_PWM_BP_SYNC0 (0x0U)
#define MSB_PRE_PWM_BP_SYNC0 11
#define LSB_PRE_PWM_BP_SYNC0 0
#define AADDR_PRE_PWM_BP_SYNC0 (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_BP_SYNC0)
#define REG_PRE_PWM_BP_SYNC0 (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_BP_SYNC0))

#define ADDR_PRE_PWM_BP_SYNC1 (0x14U)
#define A_PRE_PWM_BP_SYNC1(ba) ((ba) + ADDR_PRE_PWM_BP_SYNC1)
#define R_PRE_PWM_BP_SYNC1(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_BP_SYNC1(ba)))
#define RES_PRE_PWM_BP_SYNC1 (0x0U)
#define MSB_PRE_PWM_BP_SYNC1 11
#define LSB_PRE_PWM_BP_SYNC1 0
#define AADDR_PRE_PWM_BP_SYNC1 (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_BP_SYNC1)
#define REG_PRE_PWM_BP_SYNC1 (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_BP_SYNC1))

#define ADDR_PRE_PWM_SYNC_EN (0x16U)
#define A_PRE_PWM_SYNC_EN(ba) ((ba) + ADDR_PRE_PWM_SYNC_EN)
#define R_PRE_PWM_SYNC_EN(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_SYNC_EN(ba)))
#define RES_PRE_PWM_SYNC_EN (0x0U)
#define MSB_PRE_PWM_SYNC_EN 3
#define LSB_PRE_PWM_SYNC_EN 0
#define AADDR_PRE_PWM_SYNC_EN (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_SYNC_EN)
#define REG_PRE_PWM_SYNC_EN (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_SYNC_EN))

#define ADDR_PRE_PWM_SYNC_EXT_CFG (0x18U)
#define A_PRE_PWM_SYNC_EXT_CFG(ba) ((ba) + ADDR_PRE_PWM_SYNC_EXT_CFG)
#define R_PRE_PWM_SYNC_EXT_CFG(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_SYNC_EXT_CFG(ba)))
#define RES_PRE_PWM_SYNC_EXT_CFG (0x0U)
#define MSB_PRE_PWM_SYNC_EXT_CFG 12
#define LSB_PRE_PWM_SYNC_EXT_CFG 0
#define AADDR_PRE_PWM_SYNC_EXT_CFG (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_SYNC_EXT_CFG)
#define REG_PRE_PWM_SYNC_EXT_CFG (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_SYNC_EXT_CFG))

#define ADDR_PRE_PWM_SCALE_SYNC (0x1AU)
#define A_PRE_PWM_SCALE_SYNC(ba) ((ba) + ADDR_PRE_PWM_SCALE_SYNC)
#define R_PRE_PWM_SCALE_SYNC(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_SCALE_SYNC(ba)))
#define RES_PRE_PWM_SCALE_SYNC (0x0U)
#define MSB_PRE_PWM_SCALE_SYNC 14
#define LSB_PRE_PWM_SCALE_SYNC 0
#define AADDR_PRE_PWM_SCALE_SYNC (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_SCALE_SYNC)
#define REG_PRE_PWM_SCALE_SYNC (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_SCALE_SYNC))

#define ADDR_PRE_PWM_INC_SYNC (0x1CU)
#define A_PRE_PWM_INC_SYNC(ba) ((ba) + ADDR_PRE_PWM_INC_SYNC)
#define R_PRE_PWM_INC_SYNC(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_INC_SYNC(ba)))
#define RES_PRE_PWM_INC_SYNC (0x0U)
#define MSB_PRE_PWM_INC_SYNC 15
#define LSB_PRE_PWM_INC_SYNC 0
#define AADDR_PRE_PWM_INC_SYNC (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_INC_SYNC)
#define REG_PRE_PWM_INC_SYNC (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_INC_SYNC))

#define ADDR_PRE_PWM_SCALE_OFFSET1 (0x1EU)
#define A_PRE_PWM_SCALE_OFFSET1(ba) ((ba) + ADDR_PRE_PWM_SCALE_OFFSET1)
#define R_PRE_PWM_SCALE_OFFSET1(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_SCALE_OFFSET1(ba)))
#define RES_PRE_PWM_SCALE_OFFSET1 (0x0U)
#define MSB_PRE_PWM_SCALE_OFFSET1 14
#define LSB_PRE_PWM_SCALE_OFFSET1 0
#define AADDR_PRE_PWM_SCALE_OFFSET1 (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_SCALE_OFFSET1)
#define REG_PRE_PWM_SCALE_OFFSET1 (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_SCALE_OFFSET1))

#define ADDR_PRE_PWM_LIMIT_LOW (0x20U)
#define A_PRE_PWM_LIMIT_LOW(ba) ((ba) + ADDR_PRE_PWM_LIMIT_LOW)
#define R_PRE_PWM_LIMIT_LOW(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_LIMIT_LOW(ba)))
#define RES_PRE_PWM_LIMIT_LOW (0x0U)
#define MSB_PRE_PWM_LIMIT_LOW 15
#define LSB_PRE_PWM_LIMIT_LOW 0
#define AADDR_PRE_PWM_LIMIT_LOW (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_LIMIT_LOW)
#define REG_PRE_PWM_LIMIT_LOW (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_LIMIT_LOW))

#define ADDR_PRE_PWM_LIMIT_LOW_SET (0x22U)
#define A_PRE_PWM_LIMIT_LOW_SET(ba) ((ba) + ADDR_PRE_PWM_LIMIT_LOW_SET)
#define R_PRE_PWM_LIMIT_LOW_SET(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_LIMIT_LOW_SET(ba)))
#define RES_PRE_PWM_LIMIT_LOW_SET (0x0U)
#define MSB_PRE_PWM_LIMIT_LOW_SET 15
#define LSB_PRE_PWM_LIMIT_LOW_SET 0
#define AADDR_PRE_PWM_LIMIT_LOW_SET (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_LIMIT_LOW_SET)
#define REG_PRE_PWM_LIMIT_LOW_SET (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_LIMIT_LOW_SET))

#define ADDR_PRE_PWM_LIMIT_HIGH (0x24U)
#define A_PRE_PWM_LIMIT_HIGH(ba) ((ba) + ADDR_PRE_PWM_LIMIT_HIGH)
#define R_PRE_PWM_LIMIT_HIGH(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_LIMIT_HIGH(ba)))
#define RES_PRE_PWM_LIMIT_HIGH (0xffffU)
#define MSB_PRE_PWM_LIMIT_HIGH 15
#define LSB_PRE_PWM_LIMIT_HIGH 0
#define AADDR_PRE_PWM_LIMIT_HIGH (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_LIMIT_HIGH)
#define REG_PRE_PWM_LIMIT_HIGH (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_LIMIT_HIGH))

#define ADDR_PRE_PWM_LIMIT_HIGH_SET (0x26U)
#define A_PRE_PWM_LIMIT_HIGH_SET(ba) ((ba) + ADDR_PRE_PWM_LIMIT_HIGH_SET)
#define R_PRE_PWM_LIMIT_HIGH_SET(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_LIMIT_HIGH_SET(ba)))
#define RES_PRE_PWM_LIMIT_HIGH_SET (0xffffU)
#define MSB_PRE_PWM_LIMIT_HIGH_SET 15
#define LSB_PRE_PWM_LIMIT_HIGH_SET 0
#define AADDR_PRE_PWM_LIMIT_HIGH_SET (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_LIMIT_HIGH_SET)
#define REG_PRE_PWM_LIMIT_HIGH_SET (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_LIMIT_HIGH_SET))

#define ADDR_PRE_PWM_U_ADDR (0x30U)
#define A_PRE_PWM_U_ADDR(ba) ((ba) + ADDR_PRE_PWM_U_ADDR)
#define R_PRE_PWM_U_ADDR(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_U_ADDR(ba)))
#define RES_PRE_PWM_U_ADDR (0x0U)
#define MSB_PRE_PWM_U_ADDR 10
#define LSB_PRE_PWM_U_ADDR 0
#define AADDR_PRE_PWM_U_ADDR (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_U_ADDR)
#define REG_PRE_PWM_U_ADDR (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_U_ADDR))

#define ADDR_PRE_PWM_U_LW (0x32U)
#define A_PRE_PWM_U_LW(ba) ((ba) + ADDR_PRE_PWM_U_LW)
#define R_PRE_PWM_U_LW(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_U_LW(ba)))
#define RES_PRE_PWM_U_LW (0x0U)
#define MSB_PRE_PWM_U_LW 15
#define LSB_PRE_PWM_U_LW 0
#define AADDR_PRE_PWM_U_LW (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_U_LW)
#define REG_PRE_PWM_U_LW (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_U_LW))

#define ADDR_PRE_PWM_U_HW (0x34U)
#define A_PRE_PWM_U_HW(ba) ((ba) + ADDR_PRE_PWM_U_HW)
#define R_PRE_PWM_U_HW(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_U_HW(ba)))
#define RES_PRE_PWM_U_HW (0x0U)
#define MSB_PRE_PWM_U_HW 15
#define LSB_PRE_PWM_U_HW 0
#define AADDR_PRE_PWM_U_HW (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_U_HW)
#define REG_PRE_PWM_U_HW (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_U_HW))

#define ADDR_PRE_PWM_U_LW_RLD (0x36U)
#define A_PRE_PWM_U_LW_RLD(ba) ((ba) + ADDR_PRE_PWM_U_LW_RLD)
#define R_PRE_PWM_U_LW_RLD(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_U_LW_RLD(ba)))
#define RES_PRE_PWM_U_LW_RLD (0x0U)
#define MSB_PRE_PWM_U_LW_RLD 15
#define LSB_PRE_PWM_U_LW_RLD 0
#define AADDR_PRE_PWM_U_LW_RLD (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_U_LW_RLD)
#define REG_PRE_PWM_U_LW_RLD (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_U_LW_RLD))

#define ADDR_PRE_PWM_U_HW_RLD (0x38U)
#define A_PRE_PWM_U_HW_RLD(ba) ((ba) + ADDR_PRE_PWM_U_HW_RLD)
#define R_PRE_PWM_U_HW_RLD(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_U_HW_RLD(ba)))
#define RES_PRE_PWM_U_HW_RLD (0x0U)
#define MSB_PRE_PWM_U_HW_RLD 15
#define LSB_PRE_PWM_U_HW_RLD 0
#define AADDR_PRE_PWM_U_HW_RLD (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_U_HW_RLD)
#define REG_PRE_PWM_U_HW_RLD (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_U_HW_RLD))

#define ADDR_PRE_PWM_V_ADDR (0x40U)
#define A_PRE_PWM_V_ADDR(ba) ((ba) + ADDR_PRE_PWM_V_ADDR)
#define R_PRE_PWM_V_ADDR(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_V_ADDR(ba)))
#define RES_PRE_PWM_V_ADDR (0x0U)
#define MSB_PRE_PWM_V_ADDR 10
#define LSB_PRE_PWM_V_ADDR 0
#define AADDR_PRE_PWM_V_ADDR (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_V_ADDR)
#define REG_PRE_PWM_V_ADDR (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_V_ADDR))

#define ADDR_PRE_PWM_V_LW (0x42U)
#define A_PRE_PWM_V_LW(ba) ((ba) + ADDR_PRE_PWM_V_LW)
#define R_PRE_PWM_V_LW(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_V_LW(ba)))
#define RES_PRE_PWM_V_LW (0x0U)
#define MSB_PRE_PWM_V_LW 15
#define LSB_PRE_PWM_V_LW 0
#define AADDR_PRE_PWM_V_LW (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_V_LW)
#define REG_PRE_PWM_V_LW (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_V_LW))

#define ADDR_PRE_PWM_V_HW (0x44U)
#define A_PRE_PWM_V_HW(ba) ((ba) + ADDR_PRE_PWM_V_HW)
#define R_PRE_PWM_V_HW(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_V_HW(ba)))
#define RES_PRE_PWM_V_HW (0x0U)
#define MSB_PRE_PWM_V_HW 15
#define LSB_PRE_PWM_V_HW 0
#define AADDR_PRE_PWM_V_HW (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_V_HW)
#define REG_PRE_PWM_V_HW (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_V_HW))

#define ADDR_PRE_PWM_V_LW_RLD (0x46U)
#define A_PRE_PWM_V_LW_RLD(ba) ((ba) + ADDR_PRE_PWM_V_LW_RLD)
#define R_PRE_PWM_V_LW_RLD(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_V_LW_RLD(ba)))
#define RES_PRE_PWM_V_LW_RLD (0x0U)
#define MSB_PRE_PWM_V_LW_RLD 15
#define LSB_PRE_PWM_V_LW_RLD 0
#define AADDR_PRE_PWM_V_LW_RLD (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_V_LW_RLD)
#define REG_PRE_PWM_V_LW_RLD (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_V_LW_RLD))

#define ADDR_PRE_PWM_V_HW_RLD (0x48U)
#define A_PRE_PWM_V_HW_RLD(ba) ((ba) + ADDR_PRE_PWM_V_HW_RLD)
#define R_PRE_PWM_V_HW_RLD(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_V_HW_RLD(ba)))
#define RES_PRE_PWM_V_HW_RLD (0x0U)
#define MSB_PRE_PWM_V_HW_RLD 15
#define LSB_PRE_PWM_V_HW_RLD 0
#define AADDR_PRE_PWM_V_HW_RLD (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_V_HW_RLD)
#define REG_PRE_PWM_V_HW_RLD (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_V_HW_RLD))

#define ADDR_PRE_PWM_W_ADDR (0x50U)
#define A_PRE_PWM_W_ADDR(ba) ((ba) + ADDR_PRE_PWM_W_ADDR)
#define R_PRE_PWM_W_ADDR(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_W_ADDR(ba)))
#define RES_PRE_PWM_W_ADDR (0x0U)
#define MSB_PRE_PWM_W_ADDR 10
#define LSB_PRE_PWM_W_ADDR 0
#define AADDR_PRE_PWM_W_ADDR (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_W_ADDR)
#define REG_PRE_PWM_W_ADDR (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_W_ADDR))

#define ADDR_PRE_PWM_W_LW (0x52U)
#define A_PRE_PWM_W_LW(ba) ((ba) + ADDR_PRE_PWM_W_LW)
#define R_PRE_PWM_W_LW(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_W_LW(ba)))
#define RES_PRE_PWM_W_LW (0x0U)
#define MSB_PRE_PWM_W_LW 15
#define LSB_PRE_PWM_W_LW 0
#define AADDR_PRE_PWM_W_LW (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_W_LW)
#define REG_PRE_PWM_W_LW (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_W_LW))

#define ADDR_PRE_PWM_W_HW (0x54U)
#define A_PRE_PWM_W_HW(ba) ((ba) + ADDR_PRE_PWM_W_HW)
#define R_PRE_PWM_W_HW(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_W_HW(ba)))
#define RES_PRE_PWM_W_HW (0x0U)
#define MSB_PRE_PWM_W_HW 15
#define LSB_PRE_PWM_W_HW 0
#define AADDR_PRE_PWM_W_HW (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_W_HW)
#define REG_PRE_PWM_W_HW (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_W_HW))

#define ADDR_PRE_PWM_W_LW_RLD (0x56U)
#define A_PRE_PWM_W_LW_RLD(ba) ((ba) + ADDR_PRE_PWM_W_LW_RLD)
#define R_PRE_PWM_W_LW_RLD(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_W_LW_RLD(ba)))
#define RES_PRE_PWM_W_LW_RLD (0x0U)
#define MSB_PRE_PWM_W_LW_RLD 15
#define LSB_PRE_PWM_W_LW_RLD 0
#define AADDR_PRE_PWM_W_LW_RLD (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_W_LW_RLD)
#define REG_PRE_PWM_W_LW_RLD (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_W_LW_RLD))

#define ADDR_PRE_PWM_W_HW_RLD (0x58U)
#define A_PRE_PWM_W_HW_RLD(ba) ((ba) + ADDR_PRE_PWM_W_HW_RLD)
#define R_PRE_PWM_W_HW_RLD(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_W_HW_RLD(ba)))
#define RES_PRE_PWM_W_HW_RLD (0x0U)
#define MSB_PRE_PWM_W_HW_RLD 15
#define LSB_PRE_PWM_W_HW_RLD 0
#define AADDR_PRE_PWM_W_HW_RLD (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_W_HW_RLD)
#define REG_PRE_PWM_W_HW_RLD (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_W_HW_RLD))

#define ADDR_PRE_PWM_IRQ_STATUS (0x70U)
#define A_PRE_PWM_IRQ_STATUS(ba) ((ba) + ADDR_PRE_PWM_IRQ_STATUS)
#define R_PRE_PWM_IRQ_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_IRQ_STATUS(ba)))
#define RES_PRE_PWM_IRQ_STATUS (0x0U)
#define MSB_PRE_PWM_IRQ_STATUS 8
#define LSB_PRE_PWM_IRQ_STATUS 0
#define AADDR_PRE_PWM_IRQ_STATUS (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_IRQ_STATUS)
#define REG_PRE_PWM_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_IRQ_STATUS))

#define ADDR_PRE_PWM_IRQ_MASK (0x74U)
#define A_PRE_PWM_IRQ_MASK(ba) ((ba) + ADDR_PRE_PWM_IRQ_MASK)
#define R_PRE_PWM_IRQ_MASK(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_IRQ_MASK(ba)))
#define RES_PRE_PWM_IRQ_MASK (0x0U)
#define MSB_PRE_PWM_IRQ_MASK 8
#define LSB_PRE_PWM_IRQ_MASK 0
#define AADDR_PRE_PWM_IRQ_MASK (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_IRQ_MASK)
#define REG_PRE_PWM_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_IRQ_MASK))

#define ADDR_PRE_PWM_IRQ_VENABLE (0x78U)
#define A_PRE_PWM_IRQ_VENABLE(ba) ((ba) + ADDR_PRE_PWM_IRQ_VENABLE)
#define R_PRE_PWM_IRQ_VENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_IRQ_VENABLE(ba)))
#define RES_PRE_PWM_IRQ_VENABLE (0x0U)
#define MSB_PRE_PWM_IRQ_VENABLE 3
#define LSB_PRE_PWM_IRQ_VENABLE 0
#define AADDR_PRE_PWM_IRQ_VENABLE (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_IRQ_VENABLE)
#define REG_PRE_PWM_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_IRQ_VENABLE))

#define ADDR_PRE_PWM_IRQ_VDISABLE (0x7AU)
#define A_PRE_PWM_IRQ_VDISABLE(ba) ((ba) + ADDR_PRE_PWM_IRQ_VDISABLE)
#define R_PRE_PWM_IRQ_VDISABLE(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_IRQ_VDISABLE(ba)))
#define RES_PRE_PWM_IRQ_VDISABLE (0x0U)
#define MSB_PRE_PWM_IRQ_VDISABLE 3
#define LSB_PRE_PWM_IRQ_VDISABLE 0
#define AADDR_PRE_PWM_IRQ_VDISABLE (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_IRQ_VDISABLE)
#define REG_PRE_PWM_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_IRQ_VDISABLE))

#define ADDR_PRE_PWM_IRQ_VMAX (0x7CU)
#define A_PRE_PWM_IRQ_VMAX(ba) ((ba) + ADDR_PRE_PWM_IRQ_VMAX)
#define R_PRE_PWM_IRQ_VMAX(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_IRQ_VMAX(ba)))
#define RES_PRE_PWM_IRQ_VMAX (0x9U)
#define MSB_PRE_PWM_IRQ_VMAX 3
#define LSB_PRE_PWM_IRQ_VMAX 0
#define AADDR_PRE_PWM_IRQ_VMAX (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_IRQ_VMAX)
#define REG_PRE_PWM_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_IRQ_VMAX))

#define ADDR_PRE_PWM_IRQ_VNO (0x7EU)
#define A_PRE_PWM_IRQ_VNO(ba) ((ba) + ADDR_PRE_PWM_IRQ_VNO)
#define R_PRE_PWM_IRQ_VNO(ba) (*(volatile unsigned short *)((unsigned int)A_PRE_PWM_IRQ_VNO(ba)))
#define RES_PRE_PWM_IRQ_VNO (0x9U)
#define MSB_PRE_PWM_IRQ_VNO 3
#define LSB_PRE_PWM_IRQ_VNO 0
#define AADDR_PRE_PWM_IRQ_VNO (BASE_ADDR_PRE_PWM + ADDR_PRE_PWM_IRQ_VNO)
#define REG_PRE_PWM_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_PRE_PWM_IRQ_VNO))

#endif
