#ifndef __SCI_BF_H__
#define __SCI_BF_H__

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

#ifndef BASE_ADDR_SCI
#define BASE_ADDR_SCI 0x02C0U
#endif

#define NUMBER_SCI 1

typedef enum
{
  SCI = (int)BASE_ADDR_SCI
} sci_num_t;

// Register bit field definitions

/* SCI_BAUD_RATE */

#define MSK_SCI_BAUD_RATE_BDFA (0x1f) /* [ 4:0] */
#define SFT_SCI_BAUD_RATE_BDFA (0)
#define LSB_SCI_BAUD_RATE_BDFA (0)
#define MSB_SCI_BAUD_RATE_BDFA (4)
#define MSK_SCI_BAUD_RATE_BD (0x7ff) /* [15:5] */
#define SFT_SCI_BAUD_RATE_BD (5)
#define LSB_SCI_BAUD_RATE_BD (5)
#define MSB_SCI_BAUD_RATE_BD (15)

typedef struct
{
  volatile unsigned short bdfa : 5; /* [ 4:0] */
  volatile unsigned short bd : 11;  /* [15:5] */
} _PACKED_ sci_baud_rate_bf;

typedef union {
  volatile unsigned short val;
  volatile sci_baud_rate_bf bf;
} _PACKED_ sci_baud_rate_t;

/* SCI_CONTROL */

#define MSK_SCI_CONTROL_SBK (0x1) /* [0] */
#define SFT_SCI_CONTROL_SBK (0)
#define LSB_SCI_CONTROL_SBK (0)
#define MSB_SCI_CONTROL_SBK (0)
#define BIT_SCI_CONTROL_SBK (0x1)  /* [0] */
#define MSK_SCI_CONTROL_MFIE (0x1) /* [1] */
#define SFT_SCI_CONTROL_MFIE (1)
#define LSB_SCI_CONTROL_MFIE (1)
#define MSB_SCI_CONTROL_MFIE (1)
#define BIT_SCI_CONTROL_MFIE (0x2) /* [1] */
#define MSK_SCI_CONTROL_RE (0x1)   /* [2] */
#define SFT_SCI_CONTROL_RE (2)
#define LSB_SCI_CONTROL_RE (2)
#define MSB_SCI_CONTROL_RE (2)
#define BIT_SCI_CONTROL_RE (0x4) /* [2] */
#define MSK_SCI_CONTROL_TE (0x1) /* [3] */
#define SFT_SCI_CONTROL_TE (3)
#define LSB_SCI_CONTROL_TE (3)
#define MSB_SCI_CONTROL_TE (3)
#define BIT_SCI_CONTROL_TE (0x8)  /* [3] */
#define MSK_SCI_CONTROL_BIE (0x1) /* [4] */
#define SFT_SCI_CONTROL_BIE (4)
#define LSB_SCI_CONTROL_BIE (4)
#define MSB_SCI_CONTROL_BIE (4)
#define BIT_SCI_CONTROL_BIE (0x10) /* [4] */
#define MSK_SCI_CONTROL_RIE (0x1)  /* [5] */
#define SFT_SCI_CONTROL_RIE (5)
#define LSB_SCI_CONTROL_RIE (5)
#define MSB_SCI_CONTROL_RIE (5)
#define BIT_SCI_CONTROL_RIE (0x20) /* [5] */
#define MSK_SCI_CONTROL_LIN (0x1)  /* [6] */
#define SFT_SCI_CONTROL_LIN (6)
#define LSB_SCI_CONTROL_LIN (6)
#define MSB_SCI_CONTROL_LIN (6)
#define BIT_SCI_CONTROL_LIN (0x40) /* [6] */
#define MSK_SCI_CONTROL_TIE (0x1)  /* [7] */
#define SFT_SCI_CONTROL_TIE (7)
#define LSB_SCI_CONTROL_TIE (7)
#define MSB_SCI_CONTROL_TIE (7)
#define BIT_SCI_CONTROL_TIE (0x80) /* [7] */

typedef struct
{
  volatile unsigned short sbk : 1;  /* [0] */
  volatile unsigned short mfie : 1; /* [1] */
  volatile unsigned short re : 1;   /* [2] */
  volatile unsigned short te : 1;   /* [3] */
  volatile unsigned short bie : 1;  /* [4] */
  volatile unsigned short rie : 1;  /* [5] */
  volatile unsigned short lin : 1;  /* [6] */
  volatile unsigned short tie : 1;  /* [7] */
  volatile unsigned short reserved : 8;
} _PACKED_ sci_control_bf;

typedef union {
  volatile unsigned short val;
  volatile sci_control_bf bf;
} _PACKED_ sci_control_t;

/* SCI_STATUS */

#define MSK_SCI_STATUS_FE (0x1) /* [0] */
#define SFT_SCI_STATUS_FE (0)
#define LSB_SCI_STATUS_FE (0)
#define MSB_SCI_STATUS_FE (0)
#define BIT_SCI_STATUS_FE (0x1) /* [0] */
#define MSK_SCI_STATUS_MF (0x1) /* [1] */
#define SFT_SCI_STATUS_MF (1)
#define LSB_SCI_STATUS_MF (1)
#define MSB_SCI_STATUS_MF (1)
#define BIT_SCI_STATUS_MF (0x2)   /* [1] */
#define MSK_SCI_STATUS_MRUN (0x1) /* [2] */
#define SFT_SCI_STATUS_MRUN (2)
#define LSB_SCI_STATUS_MRUN (2)
#define MSB_SCI_STATUS_MRUN (2)
#define BIT_SCI_STATUS_MRUN (0x4) /* [2] */
#define MSK_SCI_STATUS_OV (0x1)   /* [3] */
#define SFT_SCI_STATUS_OV (3)
#define LSB_SCI_STATUS_OV (3)
#define MSB_SCI_STATUS_OV (3)
#define BIT_SCI_STATUS_OV (0x8)  /* [3] */
#define MSK_SCI_STATUS_BRF (0x1) /* [4] */
#define SFT_SCI_STATUS_BRF (4)
#define LSB_SCI_STATUS_BRF (4)
#define MSB_SCI_STATUS_BRF (4)
#define BIT_SCI_STATUS_BRF (0x10) /* [4] */
#define MSK_SCI_STATUS_RDRF (0x1) /* [5] */
#define SFT_SCI_STATUS_RDRF (5)
#define LSB_SCI_STATUS_RDRF (5)
#define MSB_SCI_STATUS_RDRF (5)
#define BIT_SCI_STATUS_RDRF (0x20) /* [5] */
#define MSK_SCI_STATUS_TC (0x1)    /* [6] */
#define SFT_SCI_STATUS_TC (6)
#define LSB_SCI_STATUS_TC (6)
#define MSB_SCI_STATUS_TC (6)
#define BIT_SCI_STATUS_TC (0x40)  /* [6] */
#define MSK_SCI_STATUS_TDRE (0x1) /* [7] */
#define SFT_SCI_STATUS_TDRE (7)
#define LSB_SCI_STATUS_TDRE (7)
#define MSB_SCI_STATUS_TDRE (7)
#define BIT_SCI_STATUS_TDRE (0x80) /* [7] */
#define MSK_SCI_STATUS_AMT (0x1)   /* [8] */
#define SFT_SCI_STATUS_AMT (8)
#define LSB_SCI_STATUS_AMT (8)
#define MSB_SCI_STATUS_AMT (8)
#define BIT_SCI_STATUS_AMT (0x100) /* [8] */
#define MSK_SCI_STATUS_ABT (0x1)   /* [9] */
#define SFT_SCI_STATUS_ABT (9)
#define LSB_SCI_STATUS_ABT (9)
#define MSB_SCI_STATUS_ABT (9)
#define BIT_SCI_STATUS_ABT (0x200) /* [9] */

typedef struct
{
  volatile unsigned short fe : 1;   /* [0] */
  volatile unsigned short mf : 1;   /* [1] */
  volatile unsigned short mrun : 1; /* [2] */
  volatile unsigned short ov : 1;   /* [3] */
  volatile unsigned short brf : 1;  /* [4] */
  volatile unsigned short rdrf : 1; /* [5] */
  volatile unsigned short tc : 1;   /* [6] */
  volatile unsigned short tdre : 1; /* [7] */
  volatile unsigned short amt : 1;  /* [8] */
  volatile unsigned short abt : 1;  /* [9] */
  volatile unsigned short reserved : 6;
} _PACKED_ sci_status_bf;

typedef union {
  volatile unsigned short val;
  volatile sci_status_bf bf;
} _PACKED_ sci_status_t;

/* SCI_DATA_IO */

#define MSK_SCI_DATA_IO (0xff) /* [ 7:0] */

typedef unsigned short sci_data_io_t; /* [ 7:0] */

/* SCI_MEAS_CONTROL */

#define MSK_SCI_MEAS_CONTROL_MEN (0x1) /* [0] */
#define SFT_SCI_MEAS_CONTROL_MEN (0)
#define LSB_SCI_MEAS_CONTROL_MEN (0)
#define MSB_SCI_MEAS_CONTROL_MEN (0)
#define BIT_SCI_MEAS_CONTROL_MEN (0x1)   /* [0] */
#define MSK_SCI_MEAS_CONTROL_MMODE (0x1) /* [1] */
#define SFT_SCI_MEAS_CONTROL_MMODE (1)
#define LSB_SCI_MEAS_CONTROL_MMODE (1)
#define MSB_SCI_MEAS_CONTROL_MMODE (1)
#define BIT_SCI_MEAS_CONTROL_MMODE (0x2)     /* [1] */
#define MSK_SCI_MEAS_CONTROL_AUTO_MEAS (0x1) /* [2] */
#define SFT_SCI_MEAS_CONTROL_AUTO_MEAS (2)
#define LSB_SCI_MEAS_CONTROL_AUTO_MEAS (2)
#define MSB_SCI_MEAS_CONTROL_AUTO_MEAS (2)
#define BIT_SCI_MEAS_CONTROL_AUTO_MEAS (0x4) /* [2] */
#define MSK_SCI_MEAS_CONTROL_AUTO_BAUD (0x1) /* [3] */
#define SFT_SCI_MEAS_CONTROL_AUTO_BAUD (3)
#define LSB_SCI_MEAS_CONTROL_AUTO_BAUD (3)
#define MSB_SCI_MEAS_CONTROL_AUTO_BAUD (3)
#define BIT_SCI_MEAS_CONTROL_AUTO_BAUD (0x8)       /* [3] */
#define MSK_SCI_MEAS_CONTROL_BUS_COLLISION_E (0x1) /* [4] */
#define SFT_SCI_MEAS_CONTROL_BUS_COLLISION_E (4)
#define LSB_SCI_MEAS_CONTROL_BUS_COLLISION_E (4)
#define MSB_SCI_MEAS_CONTROL_BUS_COLLISION_E (4)
#define BIT_SCI_MEAS_CONTROL_BUS_COLLISION_E (0x10) /* [4] */
#define MSK_SCI_MEAS_CONTROL_DBC (0x3f)             /* [13:8] */
#define SFT_SCI_MEAS_CONTROL_DBC (8)
#define LSB_SCI_MEAS_CONTROL_DBC (8)
#define MSB_SCI_MEAS_CONTROL_DBC (13)

typedef struct
{
  volatile unsigned short men : 1;             /* [0] */
  volatile unsigned short mmode : 1;           /* [1] */
  volatile unsigned short auto_meas : 1;       /* [2] */
  volatile unsigned short auto_baud : 1;       /* [3] */
  volatile unsigned short bus_collision_e : 1; /* [4] */
  volatile unsigned short reserved7 : 3;       /* [ 7:5] */
  volatile unsigned short dbc : 6;             /* [13:8] */
  volatile unsigned short reserved : 2;
} _PACKED_ sci_meas_control_bf;

typedef union {
  volatile unsigned short val;
  volatile sci_meas_control_bf bf;
} _PACKED_ sci_meas_control_t;

/* SCI_MEAS_COUNTER */

#define MSK_SCI_MEAS_COUNTER (0xffff) /* [15:0] */

typedef unsigned short sci_meas_counter_t; /* [15:0] */

/* SCI_LIN_CONFIGURATION */

#define MSK_SCI_LIN_CONFIGURATION_CBM (0x1) /* [0] */
#define SFT_SCI_LIN_CONFIGURATION_CBM (0)
#define LSB_SCI_LIN_CONFIGURATION_CBM (0)
#define MSB_SCI_LIN_CONFIGURATION_CBM (0)
#define BIT_SCI_LIN_CONFIGURATION_CBM (0x1)             /* [0] */
#define MSK_SCI_LIN_CONFIGURATION_TXD_TIMEOUT_REG (0x1) /* [1] */
#define SFT_SCI_LIN_CONFIGURATION_TXD_TIMEOUT_REG (1)
#define LSB_SCI_LIN_CONFIGURATION_TXD_TIMEOUT_REG (1)
#define MSB_SCI_LIN_CONFIGURATION_TXD_TIMEOUT_REG (1)
#define BIT_SCI_LIN_CONFIGURATION_TXD_TIMEOUT_REG (0x2) /* [1] */
#define MSK_SCI_LIN_CONFIGURATION_TIMER (0x1)           /* [2] */
#define SFT_SCI_LIN_CONFIGURATION_TIMER (2)
#define LSB_SCI_LIN_CONFIGURATION_TIMER (2)
#define MSB_SCI_LIN_CONFIGURATION_TIMER (2)
#define BIT_SCI_LIN_CONFIGURATION_TIMER (0x4) /* [2] */
#define MSK_SCI_LIN_CONFIGURATION_DMA (0x1)   /* [3] */
#define SFT_SCI_LIN_CONFIGURATION_DMA (3)
#define LSB_SCI_LIN_CONFIGURATION_DMA (3)
#define MSB_SCI_LIN_CONFIGURATION_DMA (3)
#define BIT_SCI_LIN_CONFIGURATION_DMA (0x8)     /* [3] */
#define MSK_SCI_LIN_CONFIGURATION_VERSION (0xf) /* [ 7:4] */
#define SFT_SCI_LIN_CONFIGURATION_VERSION (4)
#define LSB_SCI_LIN_CONFIGURATION_VERSION (4)
#define MSB_SCI_LIN_CONFIGURATION_VERSION (7)

typedef struct
{
  volatile unsigned short cbm : 1;             /* [0] */
  volatile unsigned short txd_timeout_reg : 1; /* [1] */
  volatile unsigned short timer : 1;           /* [2] */
  volatile unsigned short dma : 1;             /* [3] */
  volatile unsigned short version : 4;         /* [ 7:4] */
  volatile unsigned short reserved : 8;
} _PACKED_ sci_lin_configuration_bf;

typedef union {
  volatile unsigned short val;
  volatile sci_lin_configuration_bf bf;
} _PACKED_ sci_lin_configuration_t;

/* SCI_LIN_MODE */

#define MSK_SCI_LIN_MODE_RXD (0x1) /* [0] */
#define SFT_SCI_LIN_MODE_RXD (0)
#define LSB_SCI_LIN_MODE_RXD (0)
#define MSB_SCI_LIN_MODE_RXD (0)
#define BIT_SCI_LIN_MODE_RXD (0x1)     /* [0] */
#define MSK_SCI_LIN_MODE_TXD_VAL (0x1) /* [1] */
#define SFT_SCI_LIN_MODE_TXD_VAL (1)
#define LSB_SCI_LIN_MODE_TXD_VAL (1)
#define MSB_SCI_LIN_MODE_TXD_VAL (1)
#define BIT_SCI_LIN_MODE_TXD_VAL (0x2)     /* [1] */
#define MSK_SCI_LIN_MODE_SCI_DISABLE (0x1) /* [2] */
#define SFT_SCI_LIN_MODE_SCI_DISABLE (2)
#define LSB_SCI_LIN_MODE_SCI_DISABLE (2)
#define MSB_SCI_LIN_MODE_SCI_DISABLE (2)
#define BIT_SCI_LIN_MODE_SCI_DISABLE (0x4) /* [2] */
#define MSK_SCI_LIN_MODE_HIGH_SPEED (0x1)  /* [3] */
#define SFT_SCI_LIN_MODE_HIGH_SPEED (3)
#define LSB_SCI_LIN_MODE_HIGH_SPEED (3)
#define MSB_SCI_LIN_MODE_HIGH_SPEED (3)
#define BIT_SCI_LIN_MODE_HIGH_SPEED (0x8)   /* [3] */
#define MSK_SCI_LIN_MODE_TIMER_ENABLE (0x1) /* [4] */
#define SFT_SCI_LIN_MODE_TIMER_ENABLE (4)
#define LSB_SCI_LIN_MODE_TIMER_ENABLE (4)
#define MSB_SCI_LIN_MODE_TIMER_ENABLE (4)
#define BIT_SCI_LIN_MODE_TIMER_ENABLE (0x10) /* [4] */
#define MSK_SCI_LIN_MODE_TIMER_PREPARE (0x3) /* [ 6:5] */
#define SFT_SCI_LIN_MODE_TIMER_PREPARE (5)
#define LSB_SCI_LIN_MODE_TIMER_PREPARE (5)
#define MSB_SCI_LIN_MODE_TIMER_PREPARE (6)
#define MSK_SCI_LIN_MODE_TIMER_CLK_BASE (0x1) /* [7] */
#define SFT_SCI_LIN_MODE_TIMER_CLK_BASE (7)
#define LSB_SCI_LIN_MODE_TIMER_CLK_BASE (7)
#define MSB_SCI_LIN_MODE_TIMER_CLK_BASE (7)
#define BIT_SCI_LIN_MODE_TIMER_CLK_BASE (0x80)    /* [7] */
#define MSK_SCI_LIN_MODE_TXD_TIMEOUT_ENABLE (0x1) /* [8] */
#define SFT_SCI_LIN_MODE_TXD_TIMEOUT_ENABLE (8)
#define LSB_SCI_LIN_MODE_TXD_TIMEOUT_ENABLE (8)
#define MSB_SCI_LIN_MODE_TXD_TIMEOUT_ENABLE (8)
#define BIT_SCI_LIN_MODE_TXD_TIMEOUT_ENABLE (0x100) /* [8] */

typedef struct
{
  volatile unsigned short rxd : 1;                /* [0] */
  volatile unsigned short txd_val : 1;            /* [1] */
  volatile unsigned short sci_disable : 1;        /* [2] */
  volatile unsigned short high_speed : 1;         /* [3] */
  volatile unsigned short timer_enable : 1;       /* [4] */
  volatile unsigned short timer_prepare : 2;      /* [ 6:5] */
  volatile unsigned short timer_clk_base : 1;     /* [7] */
  volatile unsigned short txd_timeout_enable : 1; /* [8] */
  volatile unsigned short reserved : 7;
} _PACKED_ sci_lin_mode_bf;

typedef union {
  volatile unsigned short val;
  volatile sci_lin_mode_bf bf;
} _PACKED_ sci_lin_mode_t;

/* SCI_ADDON_INTERRUPT_ENABLE */

#define MSK_SCI_ADDON_INTERRUPT_ENABLE_RXD_FALLING_IRQ_E (0x1) /* [0] */
#define SFT_SCI_ADDON_INTERRUPT_ENABLE_RXD_FALLING_IRQ_E (0)
#define LSB_SCI_ADDON_INTERRUPT_ENABLE_RXD_FALLING_IRQ_E (0)
#define MSB_SCI_ADDON_INTERRUPT_ENABLE_RXD_FALLING_IRQ_E (0)
#define BIT_SCI_ADDON_INTERRUPT_ENABLE_RXD_FALLING_IRQ_E (0x1) /* [0] */
#define MSK_SCI_ADDON_INTERRUPT_ENABLE_RXD_RISING_IRQ_E (0x1)  /* [1] */
#define SFT_SCI_ADDON_INTERRUPT_ENABLE_RXD_RISING_IRQ_E (1)
#define LSB_SCI_ADDON_INTERRUPT_ENABLE_RXD_RISING_IRQ_E (1)
#define MSB_SCI_ADDON_INTERRUPT_ENABLE_RXD_RISING_IRQ_E (1)
#define BIT_SCI_ADDON_INTERRUPT_ENABLE_RXD_RISING_IRQ_E (0x2)  /* [1] */
#define MSK_SCI_ADDON_INTERRUPT_ENABLE_TXD_TIMEOUT_IRQ_E (0x1) /* [2] */
#define SFT_SCI_ADDON_INTERRUPT_ENABLE_TXD_TIMEOUT_IRQ_E (2)
#define LSB_SCI_ADDON_INTERRUPT_ENABLE_TXD_TIMEOUT_IRQ_E (2)
#define MSB_SCI_ADDON_INTERRUPT_ENABLE_TXD_TIMEOUT_IRQ_E (2)
#define BIT_SCI_ADDON_INTERRUPT_ENABLE_TXD_TIMEOUT_IRQ_E (0x4)   /* [2] */
#define MSK_SCI_ADDON_INTERRUPT_ENABLE_SCI_TIMER_CMP_IRQ_E (0x1) /* [3] */
#define SFT_SCI_ADDON_INTERRUPT_ENABLE_SCI_TIMER_CMP_IRQ_E (3)
#define LSB_SCI_ADDON_INTERRUPT_ENABLE_SCI_TIMER_CMP_IRQ_E (3)
#define MSB_SCI_ADDON_INTERRUPT_ENABLE_SCI_TIMER_CMP_IRQ_E (3)
#define BIT_SCI_ADDON_INTERRUPT_ENABLE_SCI_TIMER_CMP_IRQ_E (0x8) /* [3] */
#define MSK_SCI_ADDON_INTERRUPT_ENABLE_SCI_TIMER_OV_IRQ_E (0x1)  /* [4] */
#define SFT_SCI_ADDON_INTERRUPT_ENABLE_SCI_TIMER_OV_IRQ_E (4)
#define LSB_SCI_ADDON_INTERRUPT_ENABLE_SCI_TIMER_OV_IRQ_E (4)
#define MSB_SCI_ADDON_INTERRUPT_ENABLE_SCI_TIMER_OV_IRQ_E (4)
#define BIT_SCI_ADDON_INTERRUPT_ENABLE_SCI_TIMER_OV_IRQ_E (0x10)   /* [4] */
#define MSK_SCI_ADDON_INTERRUPT_ENABLE_TX_DMA_FINISHED_IRQ_E (0x1) /* [5] */
#define SFT_SCI_ADDON_INTERRUPT_ENABLE_TX_DMA_FINISHED_IRQ_E (5)
#define LSB_SCI_ADDON_INTERRUPT_ENABLE_TX_DMA_FINISHED_IRQ_E (5)
#define MSB_SCI_ADDON_INTERRUPT_ENABLE_TX_DMA_FINISHED_IRQ_E (5)
#define BIT_SCI_ADDON_INTERRUPT_ENABLE_TX_DMA_FINISHED_IRQ_E (0x20) /* [5] */
#define MSK_SCI_ADDON_INTERRUPT_ENABLE_RX_DMA_FINISHED_IRQ_E (0x1)  /* [6] */
#define SFT_SCI_ADDON_INTERRUPT_ENABLE_RX_DMA_FINISHED_IRQ_E (6)
#define LSB_SCI_ADDON_INTERRUPT_ENABLE_RX_DMA_FINISHED_IRQ_E (6)
#define MSB_SCI_ADDON_INTERRUPT_ENABLE_RX_DMA_FINISHED_IRQ_E (6)
#define BIT_SCI_ADDON_INTERRUPT_ENABLE_RX_DMA_FINISHED_IRQ_E (0x40)  /* [6] */
#define MSK_SCI_ADDON_INTERRUPT_ENABLE_LIN_BUS_COLLISION_IRQ_E (0x1) /* [7] */
#define SFT_SCI_ADDON_INTERRUPT_ENABLE_LIN_BUS_COLLISION_IRQ_E (7)
#define LSB_SCI_ADDON_INTERRUPT_ENABLE_LIN_BUS_COLLISION_IRQ_E (7)
#define MSB_SCI_ADDON_INTERRUPT_ENABLE_LIN_BUS_COLLISION_IRQ_E (7)
#define BIT_SCI_ADDON_INTERRUPT_ENABLE_LIN_BUS_COLLISION_IRQ_E (0x80) /* [7] */

typedef struct
{
  volatile unsigned short rxd_falling_irq_e : 1;       /* [0] */
  volatile unsigned short rxd_rising_irq_e : 1;        /* [1] */
  volatile unsigned short txd_timeout_irq_e : 1;       /* [2] */
  volatile unsigned short sci_timer_cmp_irq_e : 1;     /* [3] */
  volatile unsigned short sci_timer_ov_irq_e : 1;      /* [4] */
  volatile unsigned short tx_dma_finished_irq_e : 1;   /* [5] */
  volatile unsigned short rx_dma_finished_irq_e : 1;   /* [6] */
  volatile unsigned short lin_bus_collision_irq_e : 1; /* [7] */
  volatile unsigned short reserved : 8;
} _PACKED_ sci_addon_interrupt_enable_bf;

typedef union {
  volatile unsigned short val;
  volatile sci_addon_interrupt_enable_bf bf;
} _PACKED_ sci_addon_interrupt_enable_t;

/* SCI_ADDON_INTERRUPT_STATUS */

#define MSK_SCI_ADDON_INTERRUPT_STATUS_RXD_FALLING (0x1) /* [0] */
#define SFT_SCI_ADDON_INTERRUPT_STATUS_RXD_FALLING (0)
#define LSB_SCI_ADDON_INTERRUPT_STATUS_RXD_FALLING (0)
#define MSB_SCI_ADDON_INTERRUPT_STATUS_RXD_FALLING (0)
#define BIT_SCI_ADDON_INTERRUPT_STATUS_RXD_FALLING (0x1) /* [0] */
#define MSK_SCI_ADDON_INTERRUPT_STATUS_RXD_RISING (0x1)  /* [1] */
#define SFT_SCI_ADDON_INTERRUPT_STATUS_RXD_RISING (1)
#define LSB_SCI_ADDON_INTERRUPT_STATUS_RXD_RISING (1)
#define MSB_SCI_ADDON_INTERRUPT_STATUS_RXD_RISING (1)
#define BIT_SCI_ADDON_INTERRUPT_STATUS_RXD_RISING (0x2)  /* [1] */
#define MSK_SCI_ADDON_INTERRUPT_STATUS_TXD_TIMEOUT (0x1) /* [2] */
#define SFT_SCI_ADDON_INTERRUPT_STATUS_TXD_TIMEOUT (2)
#define LSB_SCI_ADDON_INTERRUPT_STATUS_TXD_TIMEOUT (2)
#define MSB_SCI_ADDON_INTERRUPT_STATUS_TXD_TIMEOUT (2)
#define BIT_SCI_ADDON_INTERRUPT_STATUS_TXD_TIMEOUT (0x4)   /* [2] */
#define MSK_SCI_ADDON_INTERRUPT_STATUS_SCI_TIMER_CMP (0x1) /* [3] */
#define SFT_SCI_ADDON_INTERRUPT_STATUS_SCI_TIMER_CMP (3)
#define LSB_SCI_ADDON_INTERRUPT_STATUS_SCI_TIMER_CMP (3)
#define MSB_SCI_ADDON_INTERRUPT_STATUS_SCI_TIMER_CMP (3)
#define BIT_SCI_ADDON_INTERRUPT_STATUS_SCI_TIMER_CMP (0x8) /* [3] */
#define MSK_SCI_ADDON_INTERRUPT_STATUS_SCI_TIMER_OV (0x1)  /* [4] */
#define SFT_SCI_ADDON_INTERRUPT_STATUS_SCI_TIMER_OV (4)
#define LSB_SCI_ADDON_INTERRUPT_STATUS_SCI_TIMER_OV (4)
#define MSB_SCI_ADDON_INTERRUPT_STATUS_SCI_TIMER_OV (4)
#define BIT_SCI_ADDON_INTERRUPT_STATUS_SCI_TIMER_OV (0x10)   /* [4] */
#define MSK_SCI_ADDON_INTERRUPT_STATUS_TX_DMA_FINISHED (0x1) /* [5] */
#define SFT_SCI_ADDON_INTERRUPT_STATUS_TX_DMA_FINISHED (5)
#define LSB_SCI_ADDON_INTERRUPT_STATUS_TX_DMA_FINISHED (5)
#define MSB_SCI_ADDON_INTERRUPT_STATUS_TX_DMA_FINISHED (5)
#define BIT_SCI_ADDON_INTERRUPT_STATUS_TX_DMA_FINISHED (0x20) /* [5] */
#define MSK_SCI_ADDON_INTERRUPT_STATUS_RX_DMA_FINISHED (0x1)  /* [6] */
#define SFT_SCI_ADDON_INTERRUPT_STATUS_RX_DMA_FINISHED (6)
#define LSB_SCI_ADDON_INTERRUPT_STATUS_RX_DMA_FINISHED (6)
#define MSB_SCI_ADDON_INTERRUPT_STATUS_RX_DMA_FINISHED (6)
#define BIT_SCI_ADDON_INTERRUPT_STATUS_RX_DMA_FINISHED (0x40)  /* [6] */
#define MSK_SCI_ADDON_INTERRUPT_STATUS_LIN_BUS_COLLISION (0x1) /* [7] */
#define SFT_SCI_ADDON_INTERRUPT_STATUS_LIN_BUS_COLLISION (7)
#define LSB_SCI_ADDON_INTERRUPT_STATUS_LIN_BUS_COLLISION (7)
#define MSB_SCI_ADDON_INTERRUPT_STATUS_LIN_BUS_COLLISION (7)
#define BIT_SCI_ADDON_INTERRUPT_STATUS_LIN_BUS_COLLISION (0x80) /* [7] */

typedef struct
{
  volatile unsigned short rxd_falling : 1;       /* [0] */
  volatile unsigned short rxd_rising : 1;        /* [1] */
  volatile unsigned short txd_timeout : 1;       /* [2] */
  volatile unsigned short sci_timer_cmp : 1;     /* [3] */
  volatile unsigned short sci_timer_ov : 1;      /* [4] */
  volatile unsigned short tx_dma_finished : 1;   /* [5] */
  volatile unsigned short rx_dma_finished : 1;   /* [6] */
  volatile unsigned short lin_bus_collision : 1; /* [7] */
  volatile unsigned short reserved : 8;
} _PACKED_ sci_addon_interrupt_status_bf;

typedef union {
  volatile unsigned short val;
  volatile sci_addon_interrupt_status_bf bf;
} _PACKED_ sci_addon_interrupt_status_t;

/* SCI_TIMER_COUNTER */

#define MSK_SCI_TIMER_COUNTER (0xffff) /* [15:0] */

typedef unsigned short sci_timer_counter_t; /* [15:0] */

/* SCI_TIMER_COMPARE */

#define MSK_SCI_TIMER_COMPARE (0xffff) /* [15:0] */

typedef unsigned short sci_timer_compare_t; /* [15:0] */

/* SCI_DMA_TX_ADDRESS */

#define MSK_SCI_DMA_TX_ADDRESS (0xffff) /* [15:0] */

typedef unsigned short sci_dma_tx_address_t; /* [15:0] */

/* SCI_DMA_TX_LENGTH */

#define MSK_SCI_DMA_TX_LENGTH (0xff) /* [ 7:0] */

typedef unsigned short sci_dma_tx_length_t; /* [ 7:0] */

/* SCI_DMA_RX_ADDRESS */

#define MSK_SCI_DMA_RX_ADDRESS (0xffff) /* [15:0] */

typedef unsigned short sci_dma_rx_address_t; /* [15:0] */

/* SCI_DMA_RX_LENGTH */

#define MSK_SCI_DMA_RX_LENGTH (0xff) /* [ 7:0] */

typedef unsigned short sci_dma_rx_length_t; /* [ 7:0] */

/* SCI_IRQ_STATUS */

#define MSK_SCI_IRQ_STATUS_EVT_BREAK (0x1) /* [0] */
#define SFT_SCI_IRQ_STATUS_EVT_BREAK (0)
#define LSB_SCI_IRQ_STATUS_EVT_BREAK (0)
#define MSB_SCI_IRQ_STATUS_EVT_BREAK (0)
#define BIT_SCI_IRQ_STATUS_EVT_BREAK (0x1) /* [0] */
#define MSK_SCI_IRQ_STATUS_EVT_MEAS (0x1)  /* [1] */
#define SFT_SCI_IRQ_STATUS_EVT_MEAS (1)
#define LSB_SCI_IRQ_STATUS_EVT_MEAS (1)
#define MSB_SCI_IRQ_STATUS_EVT_MEAS (1)
#define BIT_SCI_IRQ_STATUS_EVT_MEAS (0x2) /* [1] */
#define MSK_SCI_IRQ_STATUS_RECEIVE (0x1)  /* [2] */
#define SFT_SCI_IRQ_STATUS_RECEIVE (2)
#define LSB_SCI_IRQ_STATUS_RECEIVE (2)
#define MSB_SCI_IRQ_STATUS_RECEIVE (2)
#define BIT_SCI_IRQ_STATUS_RECEIVE (0x4)  /* [2] */
#define MSK_SCI_IRQ_STATUS_TRANSMIT (0x1) /* [3] */
#define SFT_SCI_IRQ_STATUS_TRANSMIT (3)
#define LSB_SCI_IRQ_STATUS_TRANSMIT (3)
#define MSB_SCI_IRQ_STATUS_TRANSMIT (3)
#define BIT_SCI_IRQ_STATUS_TRANSMIT (0x8)    /* [3] */
#define MSK_SCI_IRQ_STATUS_RXD_FALLING (0x1) /* [4] */
#define SFT_SCI_IRQ_STATUS_RXD_FALLING (4)
#define LSB_SCI_IRQ_STATUS_RXD_FALLING (4)
#define MSB_SCI_IRQ_STATUS_RXD_FALLING (4)
#define BIT_SCI_IRQ_STATUS_RXD_FALLING (0x10) /* [4] */
#define MSK_SCI_IRQ_STATUS_RXD_RISING (0x1)   /* [5] */
#define SFT_SCI_IRQ_STATUS_RXD_RISING (5)
#define LSB_SCI_IRQ_STATUS_RXD_RISING (5)
#define MSB_SCI_IRQ_STATUS_RXD_RISING (5)
#define BIT_SCI_IRQ_STATUS_RXD_RISING (0x20) /* [5] */
#define MSK_SCI_IRQ_STATUS_TXD_TIMEOUT (0x1) /* [6] */
#define SFT_SCI_IRQ_STATUS_TXD_TIMEOUT (6)
#define LSB_SCI_IRQ_STATUS_TXD_TIMEOUT (6)
#define MSB_SCI_IRQ_STATUS_TXD_TIMEOUT (6)
#define BIT_SCI_IRQ_STATUS_TXD_TIMEOUT (0x40)  /* [6] */
#define MSK_SCI_IRQ_STATUS_SCI_TIMER_CMP (0x1) /* [7] */
#define SFT_SCI_IRQ_STATUS_SCI_TIMER_CMP (7)
#define LSB_SCI_IRQ_STATUS_SCI_TIMER_CMP (7)
#define MSB_SCI_IRQ_STATUS_SCI_TIMER_CMP (7)
#define BIT_SCI_IRQ_STATUS_SCI_TIMER_CMP (0x80) /* [7] */
#define MSK_SCI_IRQ_STATUS_SCI_TIMER_OV (0x1)   /* [8] */
#define SFT_SCI_IRQ_STATUS_SCI_TIMER_OV (8)
#define LSB_SCI_IRQ_STATUS_SCI_TIMER_OV (8)
#define MSB_SCI_IRQ_STATUS_SCI_TIMER_OV (8)
#define BIT_SCI_IRQ_STATUS_SCI_TIMER_OV (0x100)  /* [8] */
#define MSK_SCI_IRQ_STATUS_TX_DMA_FINISHED (0x1) /* [9] */
#define SFT_SCI_IRQ_STATUS_TX_DMA_FINISHED (9)
#define LSB_SCI_IRQ_STATUS_TX_DMA_FINISHED (9)
#define MSB_SCI_IRQ_STATUS_TX_DMA_FINISHED (9)
#define BIT_SCI_IRQ_STATUS_TX_DMA_FINISHED (0x200) /* [9] */
#define MSK_SCI_IRQ_STATUS_RX_DMA_FINISHED (0x1)   /* [10] */
#define SFT_SCI_IRQ_STATUS_RX_DMA_FINISHED (10)
#define LSB_SCI_IRQ_STATUS_RX_DMA_FINISHED (10)
#define MSB_SCI_IRQ_STATUS_RX_DMA_FINISHED (10)
#define BIT_SCI_IRQ_STATUS_RX_DMA_FINISHED (0x400) /* [10] */
#define MSK_SCI_IRQ_STATUS_BUS_COLLISION (0x1)     /* [11] */
#define SFT_SCI_IRQ_STATUS_BUS_COLLISION (11)
#define LSB_SCI_IRQ_STATUS_BUS_COLLISION (11)
#define MSB_SCI_IRQ_STATUS_BUS_COLLISION (11)
#define BIT_SCI_IRQ_STATUS_BUS_COLLISION (0x800) /* [11] */

typedef struct
{
  volatile unsigned short evt_break : 1;       /* [0] */
  volatile unsigned short evt_meas : 1;        /* [1] */
  volatile unsigned short receive : 1;         /* [2] */
  volatile unsigned short transmit : 1;        /* [3] */
  volatile unsigned short rxd_falling : 1;     /* [4] */
  volatile unsigned short rxd_rising : 1;      /* [5] */
  volatile unsigned short txd_timeout : 1;     /* [6] */
  volatile unsigned short sci_timer_cmp : 1;   /* [7] */
  volatile unsigned short sci_timer_ov : 1;    /* [8] */
  volatile unsigned short tx_dma_finished : 1; /* [9] */
  volatile unsigned short rx_dma_finished : 1; /* [10] */
  volatile unsigned short bus_collision : 1;   /* [11] */
  volatile unsigned short reserved : 4;
} _PACKED_ sci_irq_status_bf;

typedef union {
  volatile unsigned short val;
  volatile sci_irq_status_bf bf;
} _PACKED_ sci_irq_status_t;

/* SCI_IRQ_MASK */

#define MSK_SCI_IRQ_MASK (0xfff) /* [11:0] */

typedef unsigned short sci_irq_mask_t; /* [11:0] */

/* SCI_IRQ_VENABLE */

#define MSK_SCI_IRQ_VENABLE (0xf) /* [ 3:0] */

typedef unsigned short sci_irq_venable_t; /* [ 3:0] */

/* SCI_IRQ_VDISABLE */

#define MSK_SCI_IRQ_VDISABLE (0xf) /* [ 3:0] */

typedef unsigned short sci_irq_vdisable_t; /* [ 3:0] */

/* SCI_IRQ_VMAX */

#define MSK_SCI_IRQ_VMAX (0xf) /* [ 3:0] */

typedef unsigned short sci_irq_vmax_t; /* [ 3:0] */

/* SCI_IRQ_VNO */

#define MSK_SCI_IRQ_VNO (0xf) /* [ 3:0] */

typedef unsigned short sci_irq_vno_t; /* [ 3:0] */

/* SCI */

typedef struct
{
  volatile sci_baud_rate_t baud_rate;                           /* 0 */
  volatile sci_control_t control;                               /* 2 */
  volatile sci_status_t status;                                 /* 4 */
  volatile sci_data_io_t data_io;                               /* 6 */
  volatile sci_meas_control_t meas_control;                     /* 8 */
  volatile sci_meas_counter_t meas_counter;                     /* 10 */
  volatile sci_lin_configuration_t lin_configuration;           /* 12 */
  volatile sci_lin_mode_t lin_mode;                             /* 14 */
  volatile sci_addon_interrupt_enable_t addon_interrupt_enable; /* 16 */
  volatile sci_addon_interrupt_status_t addon_interrupt_status; /* 18 */
  volatile sci_timer_counter_t timer_counter;                   /* 20 */
  volatile sci_timer_compare_t timer_compare;                   /* 22 */
  volatile sci_dma_tx_address_t dma_tx_address;                 /* 24 */
  volatile sci_dma_tx_length_t dma_tx_length;                   /* 26 */
  volatile sci_dma_rx_address_t dma_rx_address;                 /* 28 */
  volatile sci_dma_rx_length_t dma_rx_length;                   /* 30 */
  unsigned short reserved0[8];
  volatile sci_irq_status_t irq_status; /* 48 */
  unsigned short reserved1[1];
  volatile sci_irq_mask_t irq_mask; /* 52 */
  unsigned short reserved2[1];
  volatile sci_irq_venable_t irq_venable;   /* 56 */
  volatile sci_irq_vdisable_t irq_vdisable; /* 58 */
  volatile sci_irq_vmax_t irq_vmax;         /* 60 */
  volatile sci_irq_vno_t irq_vno;           /* 62 */
} _PACKED_ sci_t;

#ifdef __IAR_SYSTEMS_ICC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_SCI 0x02C0U ... LIN SCI (UART) Module

#define ADDR_SCI_BAUD_RATE (0x00U)
#define A_SCI_BAUD_RATE(ba) ((ba) + ADDR_SCI_BAUD_RATE)
#define R_SCI_BAUD_RATE(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_BAUD_RATE(ba)))
#define RES_SCI_BAUD_RATE (0x0U)
#define MSB_SCI_BAUD_RATE 15
#define LSB_SCI_BAUD_RATE 0
#define AADDR_SCI_BAUD_RATE (BASE_ADDR_SCI + ADDR_SCI_BAUD_RATE)
#define REG_SCI_BAUD_RATE (*(volatile unsigned short *)((unsigned int)AADDR_SCI_BAUD_RATE))

#define ADDR_SCI_CONTROL (0x02U)
#define A_SCI_CONTROL(ba) ((ba) + ADDR_SCI_CONTROL)
#define R_SCI_CONTROL(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_CONTROL(ba)))
#define RES_SCI_CONTROL (0x0U)
#define MSB_SCI_CONTROL 7
#define LSB_SCI_CONTROL 0
#define AADDR_SCI_CONTROL (BASE_ADDR_SCI + ADDR_SCI_CONTROL)
#define REG_SCI_CONTROL (*(volatile unsigned short *)((unsigned int)AADDR_SCI_CONTROL))

#define ADDR_SCI_STATUS (0x04U)
#define A_SCI_STATUS(ba) ((ba) + ADDR_SCI_STATUS)
#define R_SCI_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_STATUS(ba)))
#define RES_SCI_STATUS (0x0U)
#define MSB_SCI_STATUS 9
#define LSB_SCI_STATUS 0
#define AADDR_SCI_STATUS (BASE_ADDR_SCI + ADDR_SCI_STATUS)
#define REG_SCI_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_SCI_STATUS))

#define ADDR_SCI_DATA_IO (0x06U)
#define A_SCI_DATA_IO(ba) ((ba) + ADDR_SCI_DATA_IO)
#define R_SCI_DATA_IO(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_DATA_IO(ba)))
#define RES_SCI_DATA_IO (0x0U)
#define MSB_SCI_DATA_IO 7
#define LSB_SCI_DATA_IO 0
#define AADDR_SCI_DATA_IO (BASE_ADDR_SCI + ADDR_SCI_DATA_IO)
#define REG_SCI_DATA_IO (*(volatile unsigned short *)((unsigned int)AADDR_SCI_DATA_IO))

#define ADDR_SCI_MEAS_CONTROL (0x08U)
#define A_SCI_MEAS_CONTROL(ba) ((ba) + ADDR_SCI_MEAS_CONTROL)
#define R_SCI_MEAS_CONTROL(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_MEAS_CONTROL(ba)))
#define RES_SCI_MEAS_CONTROL (0x2800U)
#define MSB_SCI_MEAS_CONTROL 13
#define LSB_SCI_MEAS_CONTROL 0
#define AADDR_SCI_MEAS_CONTROL (BASE_ADDR_SCI + ADDR_SCI_MEAS_CONTROL)
#define REG_SCI_MEAS_CONTROL (*(volatile unsigned short *)((unsigned int)AADDR_SCI_MEAS_CONTROL))

#define ADDR_SCI_MEAS_COUNTER (0x0AU)
#define A_SCI_MEAS_COUNTER(ba) ((ba) + ADDR_SCI_MEAS_COUNTER)
#define R_SCI_MEAS_COUNTER(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_MEAS_COUNTER(ba)))
#define RES_SCI_MEAS_COUNTER (0x0U)
#define MSB_SCI_MEAS_COUNTER 15
#define LSB_SCI_MEAS_COUNTER 0
#define AADDR_SCI_MEAS_COUNTER (BASE_ADDR_SCI + ADDR_SCI_MEAS_COUNTER)
#define REG_SCI_MEAS_COUNTER (*(volatile unsigned short *)((unsigned int)AADDR_SCI_MEAS_COUNTER))

#define ADDR_SCI_LIN_CONFIGURATION (0x0CU)
#define A_SCI_LIN_CONFIGURATION(ba) ((ba) + ADDR_SCI_LIN_CONFIGURATION)
#define R_SCI_LIN_CONFIGURATION(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_LIN_CONFIGURATION(ba)))
#define RES_SCI_LIN_CONFIGURATION (0x3fU)
#define MSB_SCI_LIN_CONFIGURATION 7
#define LSB_SCI_LIN_CONFIGURATION 0
#define AADDR_SCI_LIN_CONFIGURATION (BASE_ADDR_SCI + ADDR_SCI_LIN_CONFIGURATION)
#define REG_SCI_LIN_CONFIGURATION (*(volatile unsigned short *)((unsigned int)AADDR_SCI_LIN_CONFIGURATION))

#define ADDR_SCI_LIN_MODE (0x0EU)
#define A_SCI_LIN_MODE(ba) ((ba) + ADDR_SCI_LIN_MODE)
#define R_SCI_LIN_MODE(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_LIN_MODE(ba)))
#define RES_SCI_LIN_MODE (0x3U)
#define MSB_SCI_LIN_MODE 8
#define LSB_SCI_LIN_MODE 0
#define AADDR_SCI_LIN_MODE (BASE_ADDR_SCI + ADDR_SCI_LIN_MODE)
#define REG_SCI_LIN_MODE (*(volatile unsigned short *)((unsigned int)AADDR_SCI_LIN_MODE))

#define ADDR_SCI_ADDON_INTERRUPT_ENABLE (0x10U)
#define A_SCI_ADDON_INTERRUPT_ENABLE(ba) ((ba) + ADDR_SCI_ADDON_INTERRUPT_ENABLE)
#define R_SCI_ADDON_INTERRUPT_ENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_ADDON_INTERRUPT_ENABLE(ba)))
#define RES_SCI_ADDON_INTERRUPT_ENABLE (0x0U)
#define MSB_SCI_ADDON_INTERRUPT_ENABLE 7
#define LSB_SCI_ADDON_INTERRUPT_ENABLE 0
#define AADDR_SCI_ADDON_INTERRUPT_ENABLE (BASE_ADDR_SCI + ADDR_SCI_ADDON_INTERRUPT_ENABLE)
#define REG_SCI_ADDON_INTERRUPT_ENABLE (*(volatile unsigned short *)((unsigned int)AADDR_SCI_ADDON_INTERRUPT_ENABLE))

#define ADDR_SCI_ADDON_INTERRUPT_STATUS (0x12U)
#define A_SCI_ADDON_INTERRUPT_STATUS(ba) ((ba) + ADDR_SCI_ADDON_INTERRUPT_STATUS)
#define R_SCI_ADDON_INTERRUPT_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_ADDON_INTERRUPT_STATUS(ba)))
#define RES_SCI_ADDON_INTERRUPT_STATUS (0x0U)
#define MSB_SCI_ADDON_INTERRUPT_STATUS 7
#define LSB_SCI_ADDON_INTERRUPT_STATUS 0
#define AADDR_SCI_ADDON_INTERRUPT_STATUS (BASE_ADDR_SCI + ADDR_SCI_ADDON_INTERRUPT_STATUS)
#define REG_SCI_ADDON_INTERRUPT_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_SCI_ADDON_INTERRUPT_STATUS))

#define ADDR_SCI_TIMER_COUNTER (0x14U)
#define A_SCI_TIMER_COUNTER(ba) ((ba) + ADDR_SCI_TIMER_COUNTER)
#define R_SCI_TIMER_COUNTER(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_TIMER_COUNTER(ba)))
#define RES_SCI_TIMER_COUNTER (0x0U)
#define MSB_SCI_TIMER_COUNTER 15
#define LSB_SCI_TIMER_COUNTER 0
#define AADDR_SCI_TIMER_COUNTER (BASE_ADDR_SCI + ADDR_SCI_TIMER_COUNTER)
#define REG_SCI_TIMER_COUNTER (*(volatile unsigned short *)((unsigned int)AADDR_SCI_TIMER_COUNTER))

#define ADDR_SCI_TIMER_COMPARE (0x16U)
#define A_SCI_TIMER_COMPARE(ba) ((ba) + ADDR_SCI_TIMER_COMPARE)
#define R_SCI_TIMER_COMPARE(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_TIMER_COMPARE(ba)))
#define RES_SCI_TIMER_COMPARE (0x0U)
#define MSB_SCI_TIMER_COMPARE 15
#define LSB_SCI_TIMER_COMPARE 0
#define AADDR_SCI_TIMER_COMPARE (BASE_ADDR_SCI + ADDR_SCI_TIMER_COMPARE)
#define REG_SCI_TIMER_COMPARE (*(volatile unsigned short *)((unsigned int)AADDR_SCI_TIMER_COMPARE))

#define ADDR_SCI_DMA_TX_ADDRESS (0x18U)
#define A_SCI_DMA_TX_ADDRESS(ba) ((ba) + ADDR_SCI_DMA_TX_ADDRESS)
#define R_SCI_DMA_TX_ADDRESS(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_DMA_TX_ADDRESS(ba)))
#define RES_SCI_DMA_TX_ADDRESS (0x0U)
#define MSB_SCI_DMA_TX_ADDRESS 15
#define LSB_SCI_DMA_TX_ADDRESS 0
#define AADDR_SCI_DMA_TX_ADDRESS (BASE_ADDR_SCI + ADDR_SCI_DMA_TX_ADDRESS)
#define REG_SCI_DMA_TX_ADDRESS (*(volatile unsigned short *)((unsigned int)AADDR_SCI_DMA_TX_ADDRESS))

#define ADDR_SCI_DMA_TX_LENGTH (0x1AU)
#define A_SCI_DMA_TX_LENGTH(ba) ((ba) + ADDR_SCI_DMA_TX_LENGTH)
#define R_SCI_DMA_TX_LENGTH(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_DMA_TX_LENGTH(ba)))
#define RES_SCI_DMA_TX_LENGTH (0x0U)
#define MSB_SCI_DMA_TX_LENGTH 7
#define LSB_SCI_DMA_TX_LENGTH 0
#define AADDR_SCI_DMA_TX_LENGTH (BASE_ADDR_SCI + ADDR_SCI_DMA_TX_LENGTH)
#define REG_SCI_DMA_TX_LENGTH (*(volatile unsigned short *)((unsigned int)AADDR_SCI_DMA_TX_LENGTH))

#define ADDR_SCI_DMA_RX_ADDRESS (0x1CU)
#define A_SCI_DMA_RX_ADDRESS(ba) ((ba) + ADDR_SCI_DMA_RX_ADDRESS)
#define R_SCI_DMA_RX_ADDRESS(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_DMA_RX_ADDRESS(ba)))
#define RES_SCI_DMA_RX_ADDRESS (0x0U)
#define MSB_SCI_DMA_RX_ADDRESS 15
#define LSB_SCI_DMA_RX_ADDRESS 0
#define AADDR_SCI_DMA_RX_ADDRESS (BASE_ADDR_SCI + ADDR_SCI_DMA_RX_ADDRESS)
#define REG_SCI_DMA_RX_ADDRESS (*(volatile unsigned short *)((unsigned int)AADDR_SCI_DMA_RX_ADDRESS))

#define ADDR_SCI_DMA_RX_LENGTH (0x1EU)
#define A_SCI_DMA_RX_LENGTH(ba) ((ba) + ADDR_SCI_DMA_RX_LENGTH)
#define R_SCI_DMA_RX_LENGTH(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_DMA_RX_LENGTH(ba)))
#define RES_SCI_DMA_RX_LENGTH (0x0U)
#define MSB_SCI_DMA_RX_LENGTH 7
#define LSB_SCI_DMA_RX_LENGTH 0
#define AADDR_SCI_DMA_RX_LENGTH (BASE_ADDR_SCI + ADDR_SCI_DMA_RX_LENGTH)
#define REG_SCI_DMA_RX_LENGTH (*(volatile unsigned short *)((unsigned int)AADDR_SCI_DMA_RX_LENGTH))

#define ADDR_SCI_IRQ_STATUS (0x30U)
#define A_SCI_IRQ_STATUS(ba) ((ba) + ADDR_SCI_IRQ_STATUS)
#define R_SCI_IRQ_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_IRQ_STATUS(ba)))
#define RES_SCI_IRQ_STATUS (0x0U)
#define MSB_SCI_IRQ_STATUS 11
#define LSB_SCI_IRQ_STATUS 0
#define AADDR_SCI_IRQ_STATUS (BASE_ADDR_SCI + ADDR_SCI_IRQ_STATUS)
#define REG_SCI_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_SCI_IRQ_STATUS))

#define ADDR_SCI_IRQ_MASK (0x34U)
#define A_SCI_IRQ_MASK(ba) ((ba) + ADDR_SCI_IRQ_MASK)
#define R_SCI_IRQ_MASK(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_IRQ_MASK(ba)))
#define RES_SCI_IRQ_MASK (0x0U)
#define MSB_SCI_IRQ_MASK 11
#define LSB_SCI_IRQ_MASK 0
#define AADDR_SCI_IRQ_MASK (BASE_ADDR_SCI + ADDR_SCI_IRQ_MASK)
#define REG_SCI_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_SCI_IRQ_MASK))

#define ADDR_SCI_IRQ_VENABLE (0x38U)
#define A_SCI_IRQ_VENABLE(ba) ((ba) + ADDR_SCI_IRQ_VENABLE)
#define R_SCI_IRQ_VENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_IRQ_VENABLE(ba)))
#define RES_SCI_IRQ_VENABLE (0x0U)
#define MSB_SCI_IRQ_VENABLE 3
#define LSB_SCI_IRQ_VENABLE 0
#define AADDR_SCI_IRQ_VENABLE (BASE_ADDR_SCI + ADDR_SCI_IRQ_VENABLE)
#define REG_SCI_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_SCI_IRQ_VENABLE))

#define ADDR_SCI_IRQ_VDISABLE (0x3AU)
#define A_SCI_IRQ_VDISABLE(ba) ((ba) + ADDR_SCI_IRQ_VDISABLE)
#define R_SCI_IRQ_VDISABLE(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_IRQ_VDISABLE(ba)))
#define RES_SCI_IRQ_VDISABLE (0x0U)
#define MSB_SCI_IRQ_VDISABLE 3
#define LSB_SCI_IRQ_VDISABLE 0
#define AADDR_SCI_IRQ_VDISABLE (BASE_ADDR_SCI + ADDR_SCI_IRQ_VDISABLE)
#define REG_SCI_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_SCI_IRQ_VDISABLE))

#define ADDR_SCI_IRQ_VMAX (0x3CU)
#define A_SCI_IRQ_VMAX(ba) ((ba) + ADDR_SCI_IRQ_VMAX)
#define R_SCI_IRQ_VMAX(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_IRQ_VMAX(ba)))
#define RES_SCI_IRQ_VMAX (0xcU)
#define MSB_SCI_IRQ_VMAX 3
#define LSB_SCI_IRQ_VMAX 0
#define AADDR_SCI_IRQ_VMAX (BASE_ADDR_SCI + ADDR_SCI_IRQ_VMAX)
#define REG_SCI_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_SCI_IRQ_VMAX))

#define ADDR_SCI_IRQ_VNO (0x3EU)
#define A_SCI_IRQ_VNO(ba) ((ba) + ADDR_SCI_IRQ_VNO)
#define R_SCI_IRQ_VNO(ba) (*(volatile unsigned short *)((unsigned int)A_SCI_IRQ_VNO(ba)))
#define RES_SCI_IRQ_VNO (0xcU)
#define MSB_SCI_IRQ_VNO 3
#define LSB_SCI_IRQ_VNO 0
#define AADDR_SCI_IRQ_VNO (BASE_ADDR_SCI + ADDR_SCI_IRQ_VNO)
#define REG_SCI_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_SCI_IRQ_VNO))

#endif
