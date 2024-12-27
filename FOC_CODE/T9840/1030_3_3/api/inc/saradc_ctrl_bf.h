#ifndef __SARADC_CTRL_BF_H__
#define __SARADC_CTRL_BF_H__

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

#ifndef BASE_ADDR_SARADC_CTRL
#define BASE_ADDR_SARADC_CTRL 0x0500U
#endif

#define NUMBER_SARADC_CTRL 1

typedef enum
{
  SARADC_CTRL = (int)BASE_ADDR_SARADC_CTRL
} saradc_ctrl_num_t;

// Register bit field definitions

/* SARADC_CTRL_CFG */

#define MSK_SARADC_CTRL_CFG_ADC_ON (0x1) /* [0] */
#define SFT_SARADC_CTRL_CFG_ADC_ON (0)
#define LSB_SARADC_CTRL_CFG_ADC_ON (0)
#define MSB_SARADC_CTRL_CFG_ADC_ON (0)
#define BIT_SARADC_CTRL_CFG_ADC_ON (0x1)    /* [0] */
#define MSK_SARADC_CTRL_CFG_ADC_RESET (0x3) /* [ 2:1] */
#define SFT_SARADC_CTRL_CFG_ADC_RESET (1)
#define LSB_SARADC_CTRL_CFG_ADC_RESET (1)
#define MSB_SARADC_CTRL_CFG_ADC_RESET (2)
#define MSK_SARADC_CTRL_CFG_MUX_SEL (0x1) /* [3] */
#define SFT_SARADC_CTRL_CFG_MUX_SEL (3)
#define LSB_SARADC_CTRL_CFG_MUX_SEL (3)
#define MSB_SARADC_CTRL_CFG_MUX_SEL (3)
#define BIT_SARADC_CTRL_CFG_MUX_SEL (0x8)  /* [3] */
#define MSK_SARADC_CTRL_CFG_EXT_SEL (0x1f) /* [ 8:4] */
#define SFT_SARADC_CTRL_CFG_EXT_SEL (4)
#define LSB_SARADC_CTRL_CFG_EXT_SEL (4)
#define MSB_SARADC_CTRL_CFG_EXT_SEL (8)
#define MSK_SARADC_CTRL_CFG_MISSED_DT_E (0x1) /* [9] */
#define SFT_SARADC_CTRL_CFG_MISSED_DT_E (9)
#define LSB_SARADC_CTRL_CFG_MISSED_DT_E (9)
#define MSB_SARADC_CTRL_CFG_MISSED_DT_E (9)
#define BIT_SARADC_CTRL_CFG_MISSED_DT_E (0x200) /* [9] */
#define MSK_SARADC_CTRL_CFG_STORE_DT_EVT (0x1)  /* [10] */
#define SFT_SARADC_CTRL_CFG_STORE_DT_EVT (10)
#define LSB_SARADC_CTRL_CFG_STORE_DT_EVT (10)
#define MSB_SARADC_CTRL_CFG_STORE_DT_EVT (10)
#define BIT_SARADC_CTRL_CFG_STORE_DT_EVT (0x400) /* [10] */
#define MSK_SARADC_CTRL_CFG_ADCLOOP_UP (0x1)     /* [11] */
#define SFT_SARADC_CTRL_CFG_ADCLOOP_UP (11)
#define LSB_SARADC_CTRL_CFG_ADCLOOP_UP (11)
#define MSB_SARADC_CTRL_CFG_ADCLOOP_UP (11)
#define BIT_SARADC_CTRL_CFG_ADCLOOP_UP (0x800) /* [11] */

typedef struct
{
  unsigned short adc_on : 1;       /* [0] */
  unsigned short adc_reset : 2;    /* [ 2:1] */
  unsigned short mux_sel : 1;      /* [3] */
  unsigned short ext_sel : 5;      /* [ 8:4] */
  unsigned short missed_dt_e : 1;  /* [9] */
  unsigned short store_dt_evt : 1; /* [10] */
  unsigned short adcloop_up : 1;   /* [11] */
  unsigned short reserved : 4;
} _PACKED_ saradc_ctrl_cfg_bf;

typedef union {
  unsigned short val;
  saradc_ctrl_cfg_bf bf;
} _PACKED_ saradc_ctrl_cfg_t;

/* SARADC_CTRL_CFG_SAR_TIMING */

#define MSK_SARADC_CTRL_CFG_SAR_TIMING_ADC_CLK_DIV (0x7) /* [ 2:0] */
#define SFT_SARADC_CTRL_CFG_SAR_TIMING_ADC_CLK_DIV (0)
#define LSB_SARADC_CTRL_CFG_SAR_TIMING_ADC_CLK_DIV (0)
#define MSB_SARADC_CTRL_CFG_SAR_TIMING_ADC_CLK_DIV (2)
#define MSK_SARADC_CTRL_CFG_SAR_TIMING_MUX_PHASE (0x1f) /* [ 7:3] */
#define SFT_SARADC_CTRL_CFG_SAR_TIMING_MUX_PHASE (3)
#define LSB_SARADC_CTRL_CFG_SAR_TIMING_MUX_PHASE (3)
#define MSB_SARADC_CTRL_CFG_SAR_TIMING_MUX_PHASE (7)
#define MSK_SARADC_CTRL_CFG_SAR_TIMING_SAMPLING_EXTENSION (0xff) /* [15:8] */
#define SFT_SARADC_CTRL_CFG_SAR_TIMING_SAMPLING_EXTENSION (8)
#define LSB_SARADC_CTRL_CFG_SAR_TIMING_SAMPLING_EXTENSION (8)
#define MSB_SARADC_CTRL_CFG_SAR_TIMING_SAMPLING_EXTENSION (15)

typedef struct
{
  unsigned short adc_clk_div : 3;        /* [ 2:0] */
  unsigned short mux_phase : 5;          /* [ 7:3] */
  unsigned short sampling_extension : 8; /* [15:8] */
} _PACKED_ saradc_ctrl_cfg_sar_timing_bf;

typedef union {
  unsigned short val;
  saradc_ctrl_cfg_sar_timing_bf bf;
} _PACKED_ saradc_ctrl_cfg_sar_timing_t;

/* SARADC_CTRL_DEAD_TIME_DELAY */

#define MSK_SARADC_CTRL_DEAD_TIME_DELAY (0xff) /* [ 7:0] */

typedef unsigned short saradc_ctrl_dead_time_delay_t; /* [ 7:0] */

/* SARADC_CTRL_DEAD_TIME_WAIT */

#define MSK_SARADC_CTRL_DEAD_TIME_WAIT (0xff) /* [ 7:0] */

typedef unsigned short saradc_ctrl_dead_time_wait_t; /* [ 7:0] */

/* SARADC_CTRL_SYNC_OUT_CFG */

#define MSK_SARADC_CTRL_SYNC_OUT_CFG_LENGTH (0xff) /* [ 7:0] */
#define SFT_SARADC_CTRL_SYNC_OUT_CFG_LENGTH (0)
#define LSB_SARADC_CTRL_SYNC_OUT_CFG_LENGTH (0)
#define MSB_SARADC_CTRL_SYNC_OUT_CFG_LENGTH (7)
#define MSK_SARADC_CTRL_SYNC_OUT_CFG_POL (0x1) /* [8] */
#define SFT_SARADC_CTRL_SYNC_OUT_CFG_POL (8)
#define LSB_SARADC_CTRL_SYNC_OUT_CFG_POL (8)
#define MSB_SARADC_CTRL_SYNC_OUT_CFG_POL (8)
#define BIT_SARADC_CTRL_SYNC_OUT_CFG_POL (0x100) /* [8] */
#define MSK_SARADC_CTRL_SYNC_OUT_CFG_SRC (0x3)   /* [10:9] */
#define SFT_SARADC_CTRL_SYNC_OUT_CFG_SRC (9)
#define LSB_SARADC_CTRL_SYNC_OUT_CFG_SRC (9)
#define MSB_SARADC_CTRL_SYNC_OUT_CFG_SRC (10)

typedef struct
{
  unsigned short length : 8; /* [ 7:0] */
  unsigned short pol : 1;    /* [8] */
  unsigned short src : 2;    /* [10:9] */
  unsigned short reserved : 5;
} _PACKED_ saradc_ctrl_sync_out_cfg_bf;

typedef union {
  unsigned short val;
  saradc_ctrl_sync_out_cfg_bf bf;
} _PACKED_ saradc_ctrl_sync_out_cfg_t;

/* SARADC_CTRL_SYNC_OUT_TRIG */

#define MSK_SARADC_CTRL_SYNC_OUT_TRIG (0xffff) /* [15:0] */

typedef unsigned short saradc_ctrl_sync_out_trig_t; /* [15:0] */

/* SARADC_CTRL_CMD */

#define MSK_SARADC_CTRL_CMD_LIST_SKIP (0x1) /* [0] */
#define SFT_SARADC_CTRL_CMD_LIST_SKIP (0)
#define LSB_SARADC_CTRL_CMD_LIST_SKIP (0)
#define MSB_SARADC_CTRL_CMD_LIST_SKIP (0)
#define BIT_SARADC_CTRL_CMD_LIST_SKIP (0x1) /* [0] */
#define MSK_SARADC_CTRL_CMD_SEQ_SKIP (0x1)  /* [1] */
#define SFT_SARADC_CTRL_CMD_SEQ_SKIP (1)
#define LSB_SARADC_CTRL_CMD_SEQ_SKIP (1)
#define MSB_SARADC_CTRL_CMD_SEQ_SKIP (1)
#define BIT_SARADC_CTRL_CMD_SEQ_SKIP (0x2) /* [1] */

typedef struct
{
  unsigned short list_skip : 1; /* [0] */
  unsigned short seq_skip : 1;  /* [1] */
  unsigned short reserved : 14;
} _PACKED_ saradc_ctrl_cmd_bf;

typedef union {
  unsigned short val;
  saradc_ctrl_cmd_bf bf;
} _PACKED_ saradc_ctrl_cmd_t;

/* SARADC_CTRL_WADR_MIN */

#define MSK_SARADC_CTRL_WADR_MIN_WADR_MIN (0x7ff) /* [15:5] */
#define SFT_SARADC_CTRL_WADR_MIN_WADR_MIN (5)
#define LSB_SARADC_CTRL_WADR_MIN_WADR_MIN (5)
#define MSB_SARADC_CTRL_WADR_MIN_WADR_MIN (15)

typedef struct
{
  unsigned short reserved4 : 5; /* [ 4:0] */
  unsigned short wadr_min : 11; /* [15:5] */
} _PACKED_ saradc_ctrl_wadr_min_bf;

typedef union {
  unsigned short val;
  saradc_ctrl_wadr_min_bf bf;
} _PACKED_ saradc_ctrl_wadr_min_t;

/* SARADC_CTRL_WADR_MAX */

#define MSK_SARADC_CTRL_WADR_MAX_WADR_MAX (0x7ff) /* [15:5] */
#define SFT_SARADC_CTRL_WADR_MAX_WADR_MAX (5)
#define LSB_SARADC_CTRL_WADR_MAX_WADR_MAX (5)
#define MSB_SARADC_CTRL_WADR_MAX_WADR_MAX (15)

typedef struct
{
  unsigned short reserved4 : 5; /* [ 4:0] */
  unsigned short wadr_max : 11; /* [15:5] */
} _PACKED_ saradc_ctrl_wadr_max_bf;

typedef union {
  unsigned short val;
  saradc_ctrl_wadr_max_bf bf;
} _PACKED_ saradc_ctrl_wadr_max_t;

/* SARADC_CTRL_SADR_NEW */

#define MSK_SARADC_CTRL_SADR_NEW_LIST_SKIP (0x1) /* [0] */
#define SFT_SARADC_CTRL_SADR_NEW_LIST_SKIP (0)
#define LSB_SARADC_CTRL_SADR_NEW_LIST_SKIP (0)
#define MSB_SARADC_CTRL_SADR_NEW_LIST_SKIP (0)
#define BIT_SARADC_CTRL_SADR_NEW_LIST_SKIP (0x1)    /* [0] */
#define MSK_SARADC_CTRL_SADR_NEW_START_ADR (0x7fff) /* [15:1] */
#define SFT_SARADC_CTRL_SADR_NEW_START_ADR (1)
#define LSB_SARADC_CTRL_SADR_NEW_START_ADR (1)
#define MSB_SARADC_CTRL_SADR_NEW_START_ADR (15)

typedef struct
{
  unsigned short list_skip : 1;  /* [0] */
  unsigned short start_adr : 15; /* [15:1] */
} _PACKED_ saradc_ctrl_sadr_new_bf;

typedef union {
  unsigned short val;
  saradc_ctrl_sadr_new_bf bf;
} _PACKED_ saradc_ctrl_sadr_new_t;

/* SARADC_CTRL_SADR_CURRENT */

#define MSK_SARADC_CTRL_SADR_CURRENT (0xffff) /* [15:0] */

typedef unsigned short saradc_ctrl_sadr_current_t; /* [15:0] */

/* SARADC_CTRL_L0_CURRENT */

#define MSK_SARADC_CTRL_L0_CURRENT (0xffff) /* [15:0] */

typedef unsigned short saradc_ctrl_l0_current_t; /* [15:0] */

/* SARADC_CTRL_L1_CURRENT */

#define MSK_SARADC_CTRL_L1_CURRENT_NO_SAMPLE (0xf) /* [ 3:0] */
#define SFT_SARADC_CTRL_L1_CURRENT_NO_SAMPLE (0)
#define LSB_SARADC_CTRL_L1_CURRENT_NO_SAMPLE (0)
#define MSB_SARADC_CTRL_L1_CURRENT_NO_SAMPLE (3)
#define MSK_SARADC_CTRL_L1_CURRENT_NO_SUM (0x1f) /* [ 8:4] */
#define SFT_SARADC_CTRL_L1_CURRENT_NO_SUM (4)
#define LSB_SARADC_CTRL_L1_CURRENT_NO_SUM (4)
#define MSB_SARADC_CTRL_L1_CURRENT_NO_SUM (8)
#define MSK_SARADC_CTRL_L1_CURRENT_CH_NO (0x1f) /* [13:9] */
#define SFT_SARADC_CTRL_L1_CURRENT_CH_NO (9)
#define LSB_SARADC_CTRL_L1_CURRENT_CH_NO (9)
#define MSB_SARADC_CTRL_L1_CURRENT_CH_NO (13)
#define MSK_SARADC_CTRL_L1_CURRENT_TRIGGER_TYPE_EXT (0x1) /* [14] */
#define SFT_SARADC_CTRL_L1_CURRENT_TRIGGER_TYPE_EXT (14)
#define LSB_SARADC_CTRL_L1_CURRENT_TRIGGER_TYPE_EXT (14)
#define MSB_SARADC_CTRL_L1_CURRENT_TRIGGER_TYPE_EXT (14)
#define BIT_SARADC_CTRL_L1_CURRENT_TRIGGER_TYPE_EXT (0x4000) /* [14] */
#define MSK_SARADC_CTRL_L1_CURRENT_TRIGGER_TYPE (0x1)        /* [15] */
#define SFT_SARADC_CTRL_L1_CURRENT_TRIGGER_TYPE (15)
#define LSB_SARADC_CTRL_L1_CURRENT_TRIGGER_TYPE (15)
#define MSB_SARADC_CTRL_L1_CURRENT_TRIGGER_TYPE (15)
#define BIT_SARADC_CTRL_L1_CURRENT_TRIGGER_TYPE (0x8000) /* [15] */

typedef struct
{
  unsigned short no_sample : 4;        /* [ 3:0] */
  unsigned short no_sum : 5;           /* [ 8:4] */
  unsigned short ch_no : 5;            /* [13:9] */
  unsigned short trigger_type_ext : 1; /* [14] */
  unsigned short trigger_type : 1;     /* [15] */
} _PACKED_ saradc_ctrl_l1_current_bf;

typedef union {
  unsigned short val;
  saradc_ctrl_l1_current_bf bf;
} _PACKED_ saradc_ctrl_l1_current_t;

/* SARADC_CTRL_L2_CURRENT */

#define MSK_SARADC_CTRL_L2_CURRENT (0xffff) /* [15:0] */

typedef unsigned short saradc_ctrl_l2_current_t; /* [15:0] */

/* SARADC_CTRL_ADR_NEXT */

#define MSK_SARADC_CTRL_ADR_NEXT (0xffff) /* [15:0] */

typedef unsigned short saradc_ctrl_adr_next_t; /* [15:0] */

/* SARADC_CTRL_SADR_DONE */

#define MSK_SARADC_CTRL_SADR_DONE (0xffff) /* [15:0] */

typedef unsigned short saradc_ctrl_sadr_done_t; /* [15:0] */

/* SARADC_CTRL_STATE */

#define MSK_SARADC_CTRL_STATE (0x7) /* [ 2:0] */

typedef unsigned short saradc_ctrl_state_t; /* [ 2:0] */

/* SARADC_CTRL_TADR */

#define MSK_SARADC_CTRL_TADR (0xffff) /* [15:0] */

typedef unsigned short saradc_ctrl_tadr_t; /* [15:0] */

/* SARADC_CTRL_AUTOCHANNEL */

#define MSK_SARADC_CTRL_AUTOCHANNEL_AUTO_CH_U (0x1f) /* [ 4:0] */
#define SFT_SARADC_CTRL_AUTOCHANNEL_AUTO_CH_U (0)
#define LSB_SARADC_CTRL_AUTOCHANNEL_AUTO_CH_U (0)
#define MSB_SARADC_CTRL_AUTOCHANNEL_AUTO_CH_U (4)
#define MSK_SARADC_CTRL_AUTOCHANNEL_AUTO_CH_V (0x1f) /* [ 9:5] */
#define SFT_SARADC_CTRL_AUTOCHANNEL_AUTO_CH_V (5)
#define LSB_SARADC_CTRL_AUTOCHANNEL_AUTO_CH_V (5)
#define MSB_SARADC_CTRL_AUTOCHANNEL_AUTO_CH_V (9)
#define MSK_SARADC_CTRL_AUTOCHANNEL_AUTO_CH_W (0x1f) /* [14:10] */
#define SFT_SARADC_CTRL_AUTOCHANNEL_AUTO_CH_W (10)
#define LSB_SARADC_CTRL_AUTOCHANNEL_AUTO_CH_W (10)
#define MSB_SARADC_CTRL_AUTOCHANNEL_AUTO_CH_W (14)

typedef struct
{
  unsigned short auto_ch_u : 5; /* [ 4:0] */
  unsigned short auto_ch_v : 5; /* [ 9:5] */
  unsigned short auto_ch_w : 5; /* [14:10] */
  unsigned short reserved : 1;
} _PACKED_ saradc_ctrl_autochannel_bf;

typedef union {
  unsigned short val;
  saradc_ctrl_autochannel_bf bf;
} _PACKED_ saradc_ctrl_autochannel_t;

/* SARADC_CTRL_IRQ_STATUS */

#define MSK_SARADC_CTRL_IRQ_STATUS_DMA_READ_ERR (0x1) /* [0] */
#define SFT_SARADC_CTRL_IRQ_STATUS_DMA_READ_ERR (0)
#define LSB_SARADC_CTRL_IRQ_STATUS_DMA_READ_ERR (0)
#define MSB_SARADC_CTRL_IRQ_STATUS_DMA_READ_ERR (0)
#define BIT_SARADC_CTRL_IRQ_STATUS_DMA_READ_ERR (0x1)  /* [0] */
#define MSK_SARADC_CTRL_IRQ_STATUS_DMA_WRITE_ERR (0x1) /* [1] */
#define SFT_SARADC_CTRL_IRQ_STATUS_DMA_WRITE_ERR (1)
#define LSB_SARADC_CTRL_IRQ_STATUS_DMA_WRITE_ERR (1)
#define MSB_SARADC_CTRL_IRQ_STATUS_DMA_WRITE_ERR (1)
#define BIT_SARADC_CTRL_IRQ_STATUS_DMA_WRITE_ERR (0x2)   /* [1] */
#define MSK_SARADC_CTRL_IRQ_STATUS_SUM_WRITTEN_EVT (0x1) /* [2] */
#define SFT_SARADC_CTRL_IRQ_STATUS_SUM_WRITTEN_EVT (2)
#define LSB_SARADC_CTRL_IRQ_STATUS_SUM_WRITTEN_EVT (2)
#define MSB_SARADC_CTRL_IRQ_STATUS_SUM_WRITTEN_EVT (2)
#define BIT_SARADC_CTRL_IRQ_STATUS_SUM_WRITTEN_EVT (0x4) /* [2] */
#define MSK_SARADC_CTRL_IRQ_STATUS_LIST_DONE_EVT (0x1)   /* [3] */
#define SFT_SARADC_CTRL_IRQ_STATUS_LIST_DONE_EVT (3)
#define LSB_SARADC_CTRL_IRQ_STATUS_LIST_DONE_EVT (3)
#define MSB_SARADC_CTRL_IRQ_STATUS_LIST_DONE_EVT (3)
#define BIT_SARADC_CTRL_IRQ_STATUS_LIST_DONE_EVT (0x8)    /* [3] */
#define MSK_SARADC_CTRL_IRQ_STATUS_SADR_DONE_NEMPTY (0x1) /* [4] */
#define SFT_SARADC_CTRL_IRQ_STATUS_SADR_DONE_NEMPTY (4)
#define LSB_SARADC_CTRL_IRQ_STATUS_SADR_DONE_NEMPTY (4)
#define MSB_SARADC_CTRL_IRQ_STATUS_SADR_DONE_NEMPTY (4)
#define BIT_SARADC_CTRL_IRQ_STATUS_SADR_DONE_NEMPTY (0x10) /* [4] */
#define MSK_SARADC_CTRL_IRQ_STATUS_SADR_NEW_NFULL (0x1)    /* [5] */
#define SFT_SARADC_CTRL_IRQ_STATUS_SADR_NEW_NFULL (5)
#define LSB_SARADC_CTRL_IRQ_STATUS_SADR_NEW_NFULL (5)
#define MSB_SARADC_CTRL_IRQ_STATUS_SADR_NEW_NFULL (5)
#define BIT_SARADC_CTRL_IRQ_STATUS_SADR_NEW_NFULL (0x20) /* [5] */
#define MSK_SARADC_CTRL_IRQ_STATUS_OOR0 (0x1)            /* [6] */
#define SFT_SARADC_CTRL_IRQ_STATUS_OOR0 (6)
#define LSB_SARADC_CTRL_IRQ_STATUS_OOR0 (6)
#define MSB_SARADC_CTRL_IRQ_STATUS_OOR0 (6)
#define BIT_SARADC_CTRL_IRQ_STATUS_OOR0 (0x40) /* [6] */
#define MSK_SARADC_CTRL_IRQ_STATUS_OOR1 (0x1)  /* [7] */
#define SFT_SARADC_CTRL_IRQ_STATUS_OOR1 (7)
#define LSB_SARADC_CTRL_IRQ_STATUS_OOR1 (7)
#define MSB_SARADC_CTRL_IRQ_STATUS_OOR1 (7)
#define BIT_SARADC_CTRL_IRQ_STATUS_OOR1 (0x80) /* [7] */
#define MSK_SARADC_CTRL_IRQ_STATUS_OOR2 (0x1)  /* [8] */
#define SFT_SARADC_CTRL_IRQ_STATUS_OOR2 (8)
#define LSB_SARADC_CTRL_IRQ_STATUS_OOR2 (8)
#define MSB_SARADC_CTRL_IRQ_STATUS_OOR2 (8)
#define BIT_SARADC_CTRL_IRQ_STATUS_OOR2 (0x100) /* [8] */
#define MSK_SARADC_CTRL_IRQ_STATUS_OOR3 (0x1)   /* [9] */
#define SFT_SARADC_CTRL_IRQ_STATUS_OOR3 (9)
#define LSB_SARADC_CTRL_IRQ_STATUS_OOR3 (9)
#define MSB_SARADC_CTRL_IRQ_STATUS_OOR3 (9)
#define BIT_SARADC_CTRL_IRQ_STATUS_OOR3 (0x200) /* [9] */
#define MSK_SARADC_CTRL_IRQ_STATUS_OOR4 (0x1)   /* [10] */
#define SFT_SARADC_CTRL_IRQ_STATUS_OOR4 (10)
#define LSB_SARADC_CTRL_IRQ_STATUS_OOR4 (10)
#define MSB_SARADC_CTRL_IRQ_STATUS_OOR4 (10)
#define BIT_SARADC_CTRL_IRQ_STATUS_OOR4 (0x400) /* [10] */
#define MSK_SARADC_CTRL_IRQ_STATUS_OOR5 (0x1)   /* [11] */
#define SFT_SARADC_CTRL_IRQ_STATUS_OOR5 (11)
#define LSB_SARADC_CTRL_IRQ_STATUS_OOR5 (11)
#define MSB_SARADC_CTRL_IRQ_STATUS_OOR5 (11)
#define BIT_SARADC_CTRL_IRQ_STATUS_OOR5 (0x800) /* [11] */
#define MSK_SARADC_CTRL_IRQ_STATUS_OOR6 (0x1)   /* [12] */
#define SFT_SARADC_CTRL_IRQ_STATUS_OOR6 (12)
#define LSB_SARADC_CTRL_IRQ_STATUS_OOR6 (12)
#define MSB_SARADC_CTRL_IRQ_STATUS_OOR6 (12)
#define BIT_SARADC_CTRL_IRQ_STATUS_OOR6 (0x1000) /* [12] */
#define MSK_SARADC_CTRL_IRQ_STATUS_OOR7 (0x1)    /* [13] */
#define SFT_SARADC_CTRL_IRQ_STATUS_OOR7 (13)
#define LSB_SARADC_CTRL_IRQ_STATUS_OOR7 (13)
#define MSB_SARADC_CTRL_IRQ_STATUS_OOR7 (13)
#define BIT_SARADC_CTRL_IRQ_STATUS_OOR7 (0x2000) /* [13] */
#define MSK_SARADC_CTRL_IRQ_STATUS_OOR8 (0x1)    /* [14] */
#define SFT_SARADC_CTRL_IRQ_STATUS_OOR8 (14)
#define LSB_SARADC_CTRL_IRQ_STATUS_OOR8 (14)
#define MSB_SARADC_CTRL_IRQ_STATUS_OOR8 (14)
#define BIT_SARADC_CTRL_IRQ_STATUS_OOR8 (0x4000) /* [14] */
#define MSK_SARADC_CTRL_IRQ_STATUS_OOR9 (0x1)    /* [15] */
#define SFT_SARADC_CTRL_IRQ_STATUS_OOR9 (15)
#define LSB_SARADC_CTRL_IRQ_STATUS_OOR9 (15)
#define MSB_SARADC_CTRL_IRQ_STATUS_OOR9 (15)
#define BIT_SARADC_CTRL_IRQ_STATUS_OOR9 (0x8000) /* [15] */

typedef struct
{
  unsigned short dma_read_err : 1;     /* [0] */
  unsigned short dma_write_err : 1;    /* [1] */
  unsigned short sum_written_evt : 1;  /* [2] */
  unsigned short list_done_evt : 1;    /* [3] */
  unsigned short sadr_done_nempty : 1; /* [4] */
  unsigned short sadr_new_nfull : 1;   /* [5] */
  unsigned short oor0 : 1;             /* [6] */
  unsigned short oor1 : 1;             /* [7] */
  unsigned short oor2 : 1;             /* [8] */
  unsigned short oor3 : 1;             /* [9] */
  unsigned short oor4 : 1;             /* [10] */
  unsigned short oor5 : 1;             /* [11] */
  unsigned short oor6 : 1;             /* [12] */
  unsigned short oor7 : 1;             /* [13] */
  unsigned short oor8 : 1;             /* [14] */
  unsigned short oor9 : 1;             /* [15] */
} _PACKED_ saradc_ctrl_irq_status_bf;

typedef union {
  unsigned short val;
  saradc_ctrl_irq_status_bf bf;
} _PACKED_ saradc_ctrl_irq_status_t;

/* SARADC_CTRL_IRQ_MASK */

#define MSK_SARADC_CTRL_IRQ_MASK (0xffff) /* [15:0] */

typedef unsigned short saradc_ctrl_irq_mask_t; /* [15:0] */

/* SARADC_CTRL_IRQ_VENABLE */

#define MSK_SARADC_CTRL_IRQ_VENABLE (0xf) /* [ 3:0] */

typedef unsigned short saradc_ctrl_irq_venable_t; /* [ 3:0] */

/* SARADC_CTRL_IRQ_VDISABLE */

#define MSK_SARADC_CTRL_IRQ_VDISABLE (0xf) /* [ 3:0] */

typedef unsigned short saradc_ctrl_irq_vdisable_t; /* [ 3:0] */

/* SARADC_CTRL_IRQ_VMAX */

#define MSK_SARADC_CTRL_IRQ_VMAX (0x1f) /* [ 4:0] */

typedef unsigned short saradc_ctrl_irq_vmax_t; /* [ 4:0] */

/* SARADC_CTRL_IRQ_VNO */

#define MSK_SARADC_CTRL_IRQ_VNO (0x1f) /* [ 4:0] */

typedef unsigned short saradc_ctrl_irq_vno_t; /* [ 4:0] */

/* SARADC_CTRL */

typedef struct
{
  saradc_ctrl_cfg_t cfg;                         /* 0 */
  saradc_ctrl_cfg_sar_timing_t cfg_sar_timing;   /* 2 */
  saradc_ctrl_dead_time_delay_t dead_time_delay; /* 4 */
  saradc_ctrl_dead_time_wait_t dead_time_wait0;  /* 6 */
  saradc_ctrl_sync_out_cfg_t sync_out_cfg;       /* 8 */
  saradc_ctrl_sync_out_trig_t sync_out_trig;     /* 10 */
  saradc_ctrl_cmd_t cmd;                         /* 12 */
  saradc_ctrl_wadr_min_t wadr_min;               /* 14 */
  saradc_ctrl_wadr_max_t wadr_max;               /* 16 */
  saradc_ctrl_sadr_new_t sadr_new;               /* 18 */
  saradc_ctrl_sadr_current_t sadr_current;       /* 20 */
  saradc_ctrl_l0_current_t l0_current;           /* 22 */
  saradc_ctrl_l1_current_t l1_current;           /* 24 */
  saradc_ctrl_l2_current_t l2_current;           /* 26 */
  saradc_ctrl_adr_next_t adr_next;               /* 28 */
  saradc_ctrl_sadr_done_t sadr_done;             /* 30 */
  saradc_ctrl_state_t state;                     /* 32 */
  saradc_ctrl_dead_time_wait_t dead_time_wait1;  /* 34 */
  saradc_ctrl_dead_time_wait_t dead_time_wait2;  /* 36 */
  saradc_ctrl_tadr_t tadr;                       /* 38 */
  saradc_ctrl_autochannel_t autochannel;         /* 40 */
  unsigned short reserved0[35];
  saradc_ctrl_irq_status_t irq_status; /* 112 */
  unsigned short reserved1[1];
  saradc_ctrl_irq_mask_t irq_mask; /* 116 */
  unsigned short reserved2[1];
  saradc_ctrl_irq_venable_t irq_venable;   /* 120 */
  saradc_ctrl_irq_vdisable_t irq_vdisable; /* 122 */
  saradc_ctrl_irq_vmax_t irq_vmax;         /* 124 */
  saradc_ctrl_irq_vno_t irq_vno;           /* 126 */
} _PACKED_ saradc_ctrl_t;

#ifdef __IAR_SYSTEMS_ICC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_SARADC_CTRL 0x0500U ... ADC Control Module

#define ADDR_SARADC_CTRL_CFG (0x00U)
#define A_SARADC_CTRL_CFG(ba) ((ba) + ADDR_SARADC_CTRL_CFG)
#define R_SARADC_CTRL_CFG(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_CFG(ba)))
#define RES_SARADC_CTRL_CFG (0x0U)
#define MSB_SARADC_CTRL_CFG 11
#define LSB_SARADC_CTRL_CFG 0
#define AADDR_SARADC_CTRL_CFG (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_CFG)
#define REG_SARADC_CTRL_CFG (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_CFG))

#define ADDR_SARADC_CTRL_CFG_SAR_TIMING (0x02U)
#define A_SARADC_CTRL_CFG_SAR_TIMING(ba) ((ba) + ADDR_SARADC_CTRL_CFG_SAR_TIMING)
#define R_SARADC_CTRL_CFG_SAR_TIMING(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_CFG_SAR_TIMING(ba)))
#define RES_SARADC_CTRL_CFG_SAR_TIMING (0x29U)
#define MSB_SARADC_CTRL_CFG_SAR_TIMING 15
#define LSB_SARADC_CTRL_CFG_SAR_TIMING 0
#define AADDR_SARADC_CTRL_CFG_SAR_TIMING (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_CFG_SAR_TIMING)
#define REG_SARADC_CTRL_CFG_SAR_TIMING (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_CFG_SAR_TIMING))

#define ADDR_SARADC_CTRL_DEAD_TIME_DELAY (0x04U)
#define A_SARADC_CTRL_DEAD_TIME_DELAY(ba) ((ba) + ADDR_SARADC_CTRL_DEAD_TIME_DELAY)
#define R_SARADC_CTRL_DEAD_TIME_DELAY(ba)                                                                              \
  (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_DEAD_TIME_DELAY(ba)))
#define RES_SARADC_CTRL_DEAD_TIME_DELAY (0x0U)
#define MSB_SARADC_CTRL_DEAD_TIME_DELAY 7
#define LSB_SARADC_CTRL_DEAD_TIME_DELAY 0
#define AADDR_SARADC_CTRL_DEAD_TIME_DELAY (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_DEAD_TIME_DELAY)
#define REG_SARADC_CTRL_DEAD_TIME_DELAY (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_DEAD_TIME_DELAY))

#define ADDR_SARADC_CTRL_DEAD_TIME_WAIT0 (0x06U)
#define A_SARADC_CTRL_DEAD_TIME_WAIT0(ba) ((ba) + ADDR_SARADC_CTRL_DEAD_TIME_WAIT0)
#define R_SARADC_CTRL_DEAD_TIME_WAIT0(ba)                                                                              \
  (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_DEAD_TIME_WAIT0(ba)))
#define RES_SARADC_CTRL_DEAD_TIME_WAIT0 (0x0U)
#define MSB_SARADC_CTRL_DEAD_TIME_WAIT0 7
#define LSB_SARADC_CTRL_DEAD_TIME_WAIT0 0
#define AADDR_SARADC_CTRL_DEAD_TIME_WAIT0 (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_DEAD_TIME_WAIT0)
#define REG_SARADC_CTRL_DEAD_TIME_WAIT0 (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_DEAD_TIME_WAIT0))

#define ADDR_SARADC_CTRL_SYNC_OUT_CFG (0x08U)
#define A_SARADC_CTRL_SYNC_OUT_CFG(ba) ((ba) + ADDR_SARADC_CTRL_SYNC_OUT_CFG)
#define R_SARADC_CTRL_SYNC_OUT_CFG(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_SYNC_OUT_CFG(ba)))
#define RES_SARADC_CTRL_SYNC_OUT_CFG (0x100U)
#define MSB_SARADC_CTRL_SYNC_OUT_CFG 10
#define LSB_SARADC_CTRL_SYNC_OUT_CFG 0
#define AADDR_SARADC_CTRL_SYNC_OUT_CFG (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_SYNC_OUT_CFG)
#define REG_SARADC_CTRL_SYNC_OUT_CFG (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_SYNC_OUT_CFG))

#define ADDR_SARADC_CTRL_SYNC_OUT_TRIG (0x0AU)
#define A_SARADC_CTRL_SYNC_OUT_TRIG(ba) ((ba) + ADDR_SARADC_CTRL_SYNC_OUT_TRIG)
#define R_SARADC_CTRL_SYNC_OUT_TRIG(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_SYNC_OUT_TRIG(ba)))
#define RES_SARADC_CTRL_SYNC_OUT_TRIG (0x0U)
#define MSB_SARADC_CTRL_SYNC_OUT_TRIG 15
#define LSB_SARADC_CTRL_SYNC_OUT_TRIG 0
#define AADDR_SARADC_CTRL_SYNC_OUT_TRIG (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_SYNC_OUT_TRIG)
#define REG_SARADC_CTRL_SYNC_OUT_TRIG (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_SYNC_OUT_TRIG))

#define ADDR_SARADC_CTRL_CMD (0x0CU)
#define A_SARADC_CTRL_CMD(ba) ((ba) + ADDR_SARADC_CTRL_CMD)
#define R_SARADC_CTRL_CMD(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_CMD(ba)))
#define RES_SARADC_CTRL_CMD (0x0U)
#define MSB_SARADC_CTRL_CMD 1
#define LSB_SARADC_CTRL_CMD 0
#define AADDR_SARADC_CTRL_CMD (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_CMD)
#define REG_SARADC_CTRL_CMD (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_CMD))

#define ADDR_SARADC_CTRL_WADR_MIN (0x0EU)
#define A_SARADC_CTRL_WADR_MIN(ba) ((ba) + ADDR_SARADC_CTRL_WADR_MIN)
#define R_SARADC_CTRL_WADR_MIN(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_WADR_MIN(ba)))
#define RES_SARADC_CTRL_WADR_MIN (0x0U)
#define MSB_SARADC_CTRL_WADR_MIN 15
#define LSB_SARADC_CTRL_WADR_MIN 5
#define AADDR_SARADC_CTRL_WADR_MIN (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_WADR_MIN)
#define REG_SARADC_CTRL_WADR_MIN (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_WADR_MIN))

#define ADDR_SARADC_CTRL_WADR_MAX (0x10U)
#define A_SARADC_CTRL_WADR_MAX(ba) ((ba) + ADDR_SARADC_CTRL_WADR_MAX)
#define R_SARADC_CTRL_WADR_MAX(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_WADR_MAX(ba)))
#define RES_SARADC_CTRL_WADR_MAX (0x0U)
#define MSB_SARADC_CTRL_WADR_MAX 15
#define LSB_SARADC_CTRL_WADR_MAX 5
#define AADDR_SARADC_CTRL_WADR_MAX (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_WADR_MAX)
#define REG_SARADC_CTRL_WADR_MAX (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_WADR_MAX))

#define ADDR_SARADC_CTRL_SADR_NEW (0x12U)
#define A_SARADC_CTRL_SADR_NEW(ba) ((ba) + ADDR_SARADC_CTRL_SADR_NEW)
#define R_SARADC_CTRL_SADR_NEW(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_SADR_NEW(ba)))
#define RES_SARADC_CTRL_SADR_NEW (0x0U)
#define MSB_SARADC_CTRL_SADR_NEW 15
#define LSB_SARADC_CTRL_SADR_NEW 0
#define AADDR_SARADC_CTRL_SADR_NEW (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_SADR_NEW)
#define REG_SARADC_CTRL_SADR_NEW (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_SADR_NEW))

#define ADDR_SARADC_CTRL_SADR_CURRENT (0x14U)
#define A_SARADC_CTRL_SADR_CURRENT(ba) ((ba) + ADDR_SARADC_CTRL_SADR_CURRENT)
#define R_SARADC_CTRL_SADR_CURRENT(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_SADR_CURRENT(ba)))
#define RES_SARADC_CTRL_SADR_CURRENT (0x0U)
#define MSB_SARADC_CTRL_SADR_CURRENT 15
#define LSB_SARADC_CTRL_SADR_CURRENT 0
#define AADDR_SARADC_CTRL_SADR_CURRENT (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_SADR_CURRENT)
#define REG_SARADC_CTRL_SADR_CURRENT (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_SADR_CURRENT))

#define ADDR_SARADC_CTRL_L0_CURRENT (0x16U)
#define A_SARADC_CTRL_L0_CURRENT(ba) ((ba) + ADDR_SARADC_CTRL_L0_CURRENT)
#define R_SARADC_CTRL_L0_CURRENT(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_L0_CURRENT(ba)))
#define RES_SARADC_CTRL_L0_CURRENT (0x0U)
#define MSB_SARADC_CTRL_L0_CURRENT 15
#define LSB_SARADC_CTRL_L0_CURRENT 0
#define AADDR_SARADC_CTRL_L0_CURRENT (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_L0_CURRENT)
#define REG_SARADC_CTRL_L0_CURRENT (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_L0_CURRENT))

#define ADDR_SARADC_CTRL_L1_CURRENT (0x18U)
#define A_SARADC_CTRL_L1_CURRENT(ba) ((ba) + ADDR_SARADC_CTRL_L1_CURRENT)
#define R_SARADC_CTRL_L1_CURRENT(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_L1_CURRENT(ba)))
#define RES_SARADC_CTRL_L1_CURRENT (0x0U)
#define MSB_SARADC_CTRL_L1_CURRENT 15
#define LSB_SARADC_CTRL_L1_CURRENT 0
#define AADDR_SARADC_CTRL_L1_CURRENT (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_L1_CURRENT)
#define REG_SARADC_CTRL_L1_CURRENT (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_L1_CURRENT))

#define ADDR_SARADC_CTRL_L2_CURRENT (0x1AU)
#define A_SARADC_CTRL_L2_CURRENT(ba) ((ba) + ADDR_SARADC_CTRL_L2_CURRENT)
#define R_SARADC_CTRL_L2_CURRENT(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_L2_CURRENT(ba)))
#define RES_SARADC_CTRL_L2_CURRENT (0x0U)
#define MSB_SARADC_CTRL_L2_CURRENT 15
#define LSB_SARADC_CTRL_L2_CURRENT 0
#define AADDR_SARADC_CTRL_L2_CURRENT (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_L2_CURRENT)
#define REG_SARADC_CTRL_L2_CURRENT (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_L2_CURRENT))

#define ADDR_SARADC_CTRL_ADR_NEXT (0x1CU)
#define A_SARADC_CTRL_ADR_NEXT(ba) ((ba) + ADDR_SARADC_CTRL_ADR_NEXT)
#define R_SARADC_CTRL_ADR_NEXT(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_ADR_NEXT(ba)))
#define RES_SARADC_CTRL_ADR_NEXT (0x0U)
#define MSB_SARADC_CTRL_ADR_NEXT 15
#define LSB_SARADC_CTRL_ADR_NEXT 0
#define AADDR_SARADC_CTRL_ADR_NEXT (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_ADR_NEXT)
#define REG_SARADC_CTRL_ADR_NEXT (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_ADR_NEXT))

#define ADDR_SARADC_CTRL_SADR_DONE (0x1EU)
#define A_SARADC_CTRL_SADR_DONE(ba) ((ba) + ADDR_SARADC_CTRL_SADR_DONE)
#define R_SARADC_CTRL_SADR_DONE(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_SADR_DONE(ba)))
#define RES_SARADC_CTRL_SADR_DONE (0x0U)
#define MSB_SARADC_CTRL_SADR_DONE 15
#define LSB_SARADC_CTRL_SADR_DONE 0
#define AADDR_SARADC_CTRL_SADR_DONE (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_SADR_DONE)
#define REG_SARADC_CTRL_SADR_DONE (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_SADR_DONE))

#define ADDR_SARADC_CTRL_STATE (0x20U)
#define A_SARADC_CTRL_STATE(ba) ((ba) + ADDR_SARADC_CTRL_STATE)
#define R_SARADC_CTRL_STATE(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_STATE(ba)))
#define RES_SARADC_CTRL_STATE (0x0U)
#define MSB_SARADC_CTRL_STATE 2
#define LSB_SARADC_CTRL_STATE 0
#define AADDR_SARADC_CTRL_STATE (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_STATE)
#define REG_SARADC_CTRL_STATE (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_STATE))

#define ADDR_SARADC_CTRL_DEAD_TIME_WAIT1 (0x22U)
#define A_SARADC_CTRL_DEAD_TIME_WAIT1(ba) ((ba) + ADDR_SARADC_CTRL_DEAD_TIME_WAIT1)
#define R_SARADC_CTRL_DEAD_TIME_WAIT1(ba)                                                                              \
  (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_DEAD_TIME_WAIT1(ba)))
#define RES_SARADC_CTRL_DEAD_TIME_WAIT1 (0x0U)
#define MSB_SARADC_CTRL_DEAD_TIME_WAIT1 7
#define LSB_SARADC_CTRL_DEAD_TIME_WAIT1 0
#define AADDR_SARADC_CTRL_DEAD_TIME_WAIT1 (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_DEAD_TIME_WAIT1)
#define REG_SARADC_CTRL_DEAD_TIME_WAIT1 (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_DEAD_TIME_WAIT1))

#define ADDR_SARADC_CTRL_DEAD_TIME_WAIT2 (0x24U)
#define A_SARADC_CTRL_DEAD_TIME_WAIT2(ba) ((ba) + ADDR_SARADC_CTRL_DEAD_TIME_WAIT2)
#define R_SARADC_CTRL_DEAD_TIME_WAIT2(ba)                                                                              \
  (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_DEAD_TIME_WAIT2(ba)))
#define RES_SARADC_CTRL_DEAD_TIME_WAIT2 (0x0U)
#define MSB_SARADC_CTRL_DEAD_TIME_WAIT2 7
#define LSB_SARADC_CTRL_DEAD_TIME_WAIT2 0
#define AADDR_SARADC_CTRL_DEAD_TIME_WAIT2 (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_DEAD_TIME_WAIT2)
#define REG_SARADC_CTRL_DEAD_TIME_WAIT2 (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_DEAD_TIME_WAIT2))

#define ADDR_SARADC_CTRL_TADR (0x26U)
#define A_SARADC_CTRL_TADR(ba) ((ba) + ADDR_SARADC_CTRL_TADR)
#define R_SARADC_CTRL_TADR(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_TADR(ba)))
#define RES_SARADC_CTRL_TADR (0x0U)
#define MSB_SARADC_CTRL_TADR 15
#define LSB_SARADC_CTRL_TADR 0
#define AADDR_SARADC_CTRL_TADR (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_TADR)
#define REG_SARADC_CTRL_TADR (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_TADR))

#define ADDR_SARADC_CTRL_AUTOCHANNEL (0x28U)
#define A_SARADC_CTRL_AUTOCHANNEL(ba) ((ba) + ADDR_SARADC_CTRL_AUTOCHANNEL)
#define R_SARADC_CTRL_AUTOCHANNEL(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_AUTOCHANNEL(ba)))
#define RES_SARADC_CTRL_AUTOCHANNEL (0x0U)
#define MSB_SARADC_CTRL_AUTOCHANNEL 14
#define LSB_SARADC_CTRL_AUTOCHANNEL 0
#define AADDR_SARADC_CTRL_AUTOCHANNEL (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_AUTOCHANNEL)
#define REG_SARADC_CTRL_AUTOCHANNEL (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_AUTOCHANNEL))

#define ADDR_SARADC_CTRL_IRQ_STATUS (0x70U)
#define A_SARADC_CTRL_IRQ_STATUS(ba) ((ba) + ADDR_SARADC_CTRL_IRQ_STATUS)
#define R_SARADC_CTRL_IRQ_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_IRQ_STATUS(ba)))
#define RES_SARADC_CTRL_IRQ_STATUS (0x0U)
#define MSB_SARADC_CTRL_IRQ_STATUS 15
#define LSB_SARADC_CTRL_IRQ_STATUS 0
#define AADDR_SARADC_CTRL_IRQ_STATUS (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_IRQ_STATUS)
#define REG_SARADC_CTRL_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_IRQ_STATUS))

#define ADDR_SARADC_CTRL_IRQ_MASK (0x74U)
#define A_SARADC_CTRL_IRQ_MASK(ba) ((ba) + ADDR_SARADC_CTRL_IRQ_MASK)
#define R_SARADC_CTRL_IRQ_MASK(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_IRQ_MASK(ba)))
#define RES_SARADC_CTRL_IRQ_MASK (0x0U)
#define MSB_SARADC_CTRL_IRQ_MASK 15
#define LSB_SARADC_CTRL_IRQ_MASK 0
#define AADDR_SARADC_CTRL_IRQ_MASK (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_IRQ_MASK)
#define REG_SARADC_CTRL_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_IRQ_MASK))

#define ADDR_SARADC_CTRL_IRQ_VENABLE (0x78U)
#define A_SARADC_CTRL_IRQ_VENABLE(ba) ((ba) + ADDR_SARADC_CTRL_IRQ_VENABLE)
#define R_SARADC_CTRL_IRQ_VENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_IRQ_VENABLE(ba)))
#define RES_SARADC_CTRL_IRQ_VENABLE (0x0U)
#define MSB_SARADC_CTRL_IRQ_VENABLE 3
#define LSB_SARADC_CTRL_IRQ_VENABLE 0
#define AADDR_SARADC_CTRL_IRQ_VENABLE (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_IRQ_VENABLE)
#define REG_SARADC_CTRL_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_IRQ_VENABLE))

#define ADDR_SARADC_CTRL_IRQ_VDISABLE (0x7AU)
#define A_SARADC_CTRL_IRQ_VDISABLE(ba) ((ba) + ADDR_SARADC_CTRL_IRQ_VDISABLE)
#define R_SARADC_CTRL_IRQ_VDISABLE(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_IRQ_VDISABLE(ba)))
#define RES_SARADC_CTRL_IRQ_VDISABLE (0x0U)
#define MSB_SARADC_CTRL_IRQ_VDISABLE 3
#define LSB_SARADC_CTRL_IRQ_VDISABLE 0
#define AADDR_SARADC_CTRL_IRQ_VDISABLE (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_IRQ_VDISABLE)
#define REG_SARADC_CTRL_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_IRQ_VDISABLE))

#define ADDR_SARADC_CTRL_IRQ_VMAX (0x7CU)
#define A_SARADC_CTRL_IRQ_VMAX(ba) ((ba) + ADDR_SARADC_CTRL_IRQ_VMAX)
#define R_SARADC_CTRL_IRQ_VMAX(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_IRQ_VMAX(ba)))
#define RES_SARADC_CTRL_IRQ_VMAX (0x10U)
#define MSB_SARADC_CTRL_IRQ_VMAX 4
#define LSB_SARADC_CTRL_IRQ_VMAX 0
#define AADDR_SARADC_CTRL_IRQ_VMAX (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_IRQ_VMAX)
#define REG_SARADC_CTRL_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_IRQ_VMAX))

#define ADDR_SARADC_CTRL_IRQ_VNO (0x7EU)
#define A_SARADC_CTRL_IRQ_VNO(ba) ((ba) + ADDR_SARADC_CTRL_IRQ_VNO)
#define R_SARADC_CTRL_IRQ_VNO(ba) (*(volatile unsigned short *)((unsigned int)A_SARADC_CTRL_IRQ_VNO(ba)))
#define RES_SARADC_CTRL_IRQ_VNO (0x10U)
#define MSB_SARADC_CTRL_IRQ_VNO 4
#define LSB_SARADC_CTRL_IRQ_VNO 0
#define AADDR_SARADC_CTRL_IRQ_VNO (BASE_ADDR_SARADC_CTRL + ADDR_SARADC_CTRL_IRQ_VNO)
#define REG_SARADC_CTRL_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_SARADC_CTRL_IRQ_VNO))

#endif
