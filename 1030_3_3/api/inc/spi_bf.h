#ifndef __SPI_BF_H__
#define __SPI_BF_H__

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

#ifndef BASE_ADDR_SPI_0
#define BASE_ADDR_SPI_0 0x0240U
#endif
#ifndef BASE_ADDR_SPI_1
#define BASE_ADDR_SPI_1 0x0280U
#endif

#define MULTIPLE_SPI
#define NUMBER_SPI 2

typedef enum
{
  SPI_0 = (int)BASE_ADDR_SPI_0,
  SPI_1 = (int)BASE_ADDR_SPI_1
} spi_num_t;

// Register bit field definitions

/* SPI_DATA */

#define MSK_SPI_DATA (0xffff) /* [15:0] */

typedef unsigned short spi_data_t; /* [15:0] */

/* SPI_DATA_KEEP_NSS */

#define MSK_SPI_DATA_KEEP_NSS (0xffff) /* [15:0] */

typedef unsigned short spi_data_keep_nss_t; /* [15:0] */

/* SPI_CONFIG */

#define MSK_SPI_CONFIG_ORDER (0x1) /* [0] */
#define SFT_SPI_CONFIG_ORDER (0)
#define LSB_SPI_CONFIG_ORDER (0)
#define MSB_SPI_CONFIG_ORDER (0)
#define BIT_SPI_CONFIG_ORDER (0x1) /* [0] */
#define MSK_SPI_CONFIG_PHASE (0x1) /* [1] */
#define SFT_SPI_CONFIG_PHASE (1)
#define LSB_SPI_CONFIG_PHASE (1)
#define MSB_SPI_CONFIG_PHASE (1)
#define BIT_SPI_CONFIG_PHASE (0x2)    /* [1] */
#define MSK_SPI_CONFIG_POLARITY (0x1) /* [2] */
#define SFT_SPI_CONFIG_POLARITY (2)
#define LSB_SPI_CONFIG_POLARITY (2)
#define MSB_SPI_CONFIG_POLARITY (2)
#define BIT_SPI_CONFIG_POLARITY (0x4) /* [2] */
#define MSK_SPI_CONFIG_SLAVE (0x1)    /* [3] */
#define SFT_SPI_CONFIG_SLAVE (3)
#define LSB_SPI_CONFIG_SLAVE (3)
#define MSB_SPI_CONFIG_SLAVE (3)
#define BIT_SPI_CONFIG_SLAVE (0x8)  /* [3] */
#define MSK_SPI_CONFIG_LENGTH (0xf) /* [ 7:4] */
#define SFT_SPI_CONFIG_LENGTH (4)
#define LSB_SPI_CONFIG_LENGTH (4)
#define MSB_SPI_CONFIG_LENGTH (7)
#define MSK_SPI_CONFIG_SLAVE_HIGH_Z (0x1) /* [8] */
#define SFT_SPI_CONFIG_SLAVE_HIGH_Z (8)
#define LSB_SPI_CONFIG_SLAVE_HIGH_Z (8)
#define MSB_SPI_CONFIG_SLAVE_HIGH_Z (8)
#define BIT_SPI_CONFIG_SLAVE_HIGH_Z (0x100) /* [8] */
#define MSK_SPI_CONFIG_INVERT_NSS (0x1)     /* [9] */
#define SFT_SPI_CONFIG_INVERT_NSS (9)
#define LSB_SPI_CONFIG_INVERT_NSS (9)
#define MSB_SPI_CONFIG_INVERT_NSS (9)
#define BIT_SPI_CONFIG_INVERT_NSS (0x200) /* [9] */
#define MSK_SPI_CONFIG_INVERT_DATA (0x1)  /* [10] */
#define SFT_SPI_CONFIG_INVERT_DATA (10)
#define LSB_SPI_CONFIG_INVERT_DATA (10)
#define MSB_SPI_CONFIG_INVERT_DATA (10)
#define BIT_SPI_CONFIG_INVERT_DATA (0x400) /* [10] */
#define MSK_SPI_CONFIG_PAUSE_NSS (0x1)     /* [11] */
#define SFT_SPI_CONFIG_PAUSE_NSS (11)
#define LSB_SPI_CONFIG_PAUSE_NSS (11)
#define MSB_SPI_CONFIG_PAUSE_NSS (11)
#define BIT_SPI_CONFIG_PAUSE_NSS (0x800) /* [11] */
#define MSK_SPI_CONFIG_SDI_IRQ_POL (0x1) /* [12] */
#define SFT_SPI_CONFIG_SDI_IRQ_POL (12)
#define LSB_SPI_CONFIG_SDI_IRQ_POL (12)
#define MSB_SPI_CONFIG_SDI_IRQ_POL (12)
#define BIT_SPI_CONFIG_SDI_IRQ_POL (0x1000) /* [12] */
#define MSK_SPI_CONFIG_SWAP_SDI_SDO (0x1)   /* [13] */
#define SFT_SPI_CONFIG_SWAP_SDI_SDO (13)
#define LSB_SPI_CONFIG_SWAP_SDI_SDO (13)
#define MSB_SPI_CONFIG_SWAP_SDI_SDO (13)
#define BIT_SPI_CONFIG_SWAP_SDI_SDO (0x2000) /* [13] */
#define MSK_SPI_CONFIG_ENABLE (0x1)          /* [15] */
#define SFT_SPI_CONFIG_ENABLE (15)
#define LSB_SPI_CONFIG_ENABLE (15)
#define MSB_SPI_CONFIG_ENABLE (15)
#define BIT_SPI_CONFIG_ENABLE (0x8000) /* [15] */

typedef struct
{
  unsigned short order : 1;        /* [0] */
  unsigned short phase : 1;        /* [1] */
  unsigned short polarity : 1;     /* [2] */
  unsigned short slave : 1;        /* [3] */
  unsigned short length : 4;       /* [ 7:4] */
  unsigned short slave_high_z : 1; /* [8] */
  unsigned short invert_nss : 1;   /* [9] */
  unsigned short invert_data : 1;  /* [10] */
  unsigned short pause_nss : 1;    /* [11] */
  unsigned short sdi_irq_pol : 1;  /* [12] */
  unsigned short swap_sdi_sdo : 1; /* [13] */
  unsigned short reserved14 : 1;   /* [14] */
  unsigned short enable : 1;       /* [15] */
} _PACKED_ spi_config_bf;

typedef union {
  unsigned short val;
  spi_config_bf bf;
} _PACKED_ spi_config_t;

/* SPI_BAUD_CONFIG */

#define MSK_SPI_BAUD_CONFIG (0xffff) /* [15:0] */

typedef unsigned short spi_baud_config_t; /* [15:0] */

/* SPI_TIMEOUT_CONFIG */

#define MSK_SPI_TIMEOUT_CONFIG (0xffff) /* [15:0] */

typedef unsigned short spi_timeout_config_t; /* [15:0] */

/* SPI_RX_FIFO_TIMEOUT */

#define MSK_SPI_RX_FIFO_TIMEOUT (0xffff) /* [15:0] */

typedef unsigned short spi_rx_fifo_timeout_t; /* [15:0] */

/* SPI_FIFO_CLEAR */

#define MSK_SPI_FIFO_CLEAR_RX_FIFO_CLEAR (0x1) /* [0] */
#define SFT_SPI_FIFO_CLEAR_RX_FIFO_CLEAR (0)
#define LSB_SPI_FIFO_CLEAR_RX_FIFO_CLEAR (0)
#define MSB_SPI_FIFO_CLEAR_RX_FIFO_CLEAR (0)
#define BIT_SPI_FIFO_CLEAR_RX_FIFO_CLEAR (0x1) /* [0] */
#define MSK_SPI_FIFO_CLEAR_TX_FIFO_CLEAR (0x1) /* [1] */
#define SFT_SPI_FIFO_CLEAR_TX_FIFO_CLEAR (1)
#define LSB_SPI_FIFO_CLEAR_TX_FIFO_CLEAR (1)
#define MSB_SPI_FIFO_CLEAR_TX_FIFO_CLEAR (1)
#define BIT_SPI_FIFO_CLEAR_TX_FIFO_CLEAR (0x2) /* [1] */
#define MSK_SPI_FIFO_CLEAR_RESET (0x1)         /* [2] */
#define SFT_SPI_FIFO_CLEAR_RESET (2)
#define LSB_SPI_FIFO_CLEAR_RESET (2)
#define MSB_SPI_FIFO_CLEAR_RESET (2)
#define BIT_SPI_FIFO_CLEAR_RESET (0x4) /* [2] */

typedef struct
{
  unsigned short rx_fifo_clear : 1; /* [0] */
  unsigned short tx_fifo_clear : 1; /* [1] */
  unsigned short reset : 1;         /* [2] */
  unsigned short reserved : 13;
} _PACKED_ spi_fifo_clear_bf;

typedef union {
  unsigned short val;
  spi_fifo_clear_bf bf;
} _PACKED_ spi_fifo_clear_t;

/* SPI_FIFO_LEVELS */

#define MSK_SPI_FIFO_LEVELS_RX_FIFO_LEVEL (0x7) /* [ 2:0] */
#define SFT_SPI_FIFO_LEVELS_RX_FIFO_LEVEL (0)
#define LSB_SPI_FIFO_LEVELS_RX_FIFO_LEVEL (0)
#define MSB_SPI_FIFO_LEVELS_RX_FIFO_LEVEL (2)
#define MSK_SPI_FIFO_LEVELS_TX_FIFO_LEVEL (0x7) /* [ 6:4] */
#define SFT_SPI_FIFO_LEVELS_TX_FIFO_LEVEL (4)
#define LSB_SPI_FIFO_LEVELS_TX_FIFO_LEVEL (4)
#define MSB_SPI_FIFO_LEVELS_TX_FIFO_LEVEL (6)
#define MSK_SPI_FIFO_LEVELS_RX_FIFO_HIGH_WATER (0x7) /* [10:8] */
#define SFT_SPI_FIFO_LEVELS_RX_FIFO_HIGH_WATER (8)
#define LSB_SPI_FIFO_LEVELS_RX_FIFO_HIGH_WATER (8)
#define MSB_SPI_FIFO_LEVELS_RX_FIFO_HIGH_WATER (10)
#define MSK_SPI_FIFO_LEVELS_TX_FIFO_LOW_WATER (0x7) /* [14:12] */
#define SFT_SPI_FIFO_LEVELS_TX_FIFO_LOW_WATER (12)
#define LSB_SPI_FIFO_LEVELS_TX_FIFO_LOW_WATER (12)
#define MSB_SPI_FIFO_LEVELS_TX_FIFO_LOW_WATER (14)

typedef struct
{
  unsigned short rx_fifo_level : 3;      /* [ 2:0] */
  unsigned short reserved3 : 1;          /* [3] */
  unsigned short tx_fifo_level : 3;      /* [ 6:4] */
  unsigned short reserved7 : 1;          /* [7] */
  unsigned short rx_fifo_high_water : 3; /* [10:8] */
  unsigned short reserved11 : 1;         /* [11] */
  unsigned short tx_fifo_low_water : 3;  /* [14:12] */
  unsigned short reserved : 1;
} _PACKED_ spi_fifo_levels_bf;

typedef union {
  unsigned short val;
  spi_fifo_levels_bf bf;
} _PACKED_ spi_fifo_levels_t;

/* SPI_IRQ_STATUS */

#define MSK_SPI_IRQ_STATUS_EVT_RX_FIFO_OV_ERR (0x1) /* [0] */
#define SFT_SPI_IRQ_STATUS_EVT_RX_FIFO_OV_ERR (0)
#define LSB_SPI_IRQ_STATUS_EVT_RX_FIFO_OV_ERR (0)
#define MSB_SPI_IRQ_STATUS_EVT_RX_FIFO_OV_ERR (0)
#define BIT_SPI_IRQ_STATUS_EVT_RX_FIFO_OV_ERR (0x1) /* [0] */
#define MSK_SPI_IRQ_STATUS_EVT_RX_FIFO_UR_ERR (0x1) /* [1] */
#define SFT_SPI_IRQ_STATUS_EVT_RX_FIFO_UR_ERR (1)
#define LSB_SPI_IRQ_STATUS_EVT_RX_FIFO_UR_ERR (1)
#define MSB_SPI_IRQ_STATUS_EVT_RX_FIFO_UR_ERR (1)
#define BIT_SPI_IRQ_STATUS_EVT_RX_FIFO_UR_ERR (0x2) /* [1] */
#define MSK_SPI_IRQ_STATUS_EVT_TX_FIFO_OV_ERR (0x1) /* [2] */
#define SFT_SPI_IRQ_STATUS_EVT_TX_FIFO_OV_ERR (2)
#define LSB_SPI_IRQ_STATUS_EVT_TX_FIFO_OV_ERR (2)
#define MSB_SPI_IRQ_STATUS_EVT_TX_FIFO_OV_ERR (2)
#define BIT_SPI_IRQ_STATUS_EVT_TX_FIFO_OV_ERR (0x4) /* [2] */
#define MSK_SPI_IRQ_STATUS_EVT_TX_FIFO_UR_ERR (0x1) /* [3] */
#define SFT_SPI_IRQ_STATUS_EVT_TX_FIFO_UR_ERR (3)
#define LSB_SPI_IRQ_STATUS_EVT_TX_FIFO_UR_ERR (3)
#define MSB_SPI_IRQ_STATUS_EVT_TX_FIFO_UR_ERR (3)
#define BIT_SPI_IRQ_STATUS_EVT_TX_FIFO_UR_ERR (0x8) /* [3] */
#define MSK_SPI_IRQ_STATUS_EVT_SOT (0x1)            /* [4] */
#define SFT_SPI_IRQ_STATUS_EVT_SOT (4)
#define LSB_SPI_IRQ_STATUS_EVT_SOT (4)
#define MSB_SPI_IRQ_STATUS_EVT_SOT (4)
#define BIT_SPI_IRQ_STATUS_EVT_SOT (0x10) /* [4] */
#define MSK_SPI_IRQ_STATUS_EVT_EOT (0x1)  /* [5] */
#define SFT_SPI_IRQ_STATUS_EVT_EOT (5)
#define LSB_SPI_IRQ_STATUS_EVT_EOT (5)
#define MSB_SPI_IRQ_STATUS_EVT_EOT (5)
#define BIT_SPI_IRQ_STATUS_EVT_EOT (0x20) /* [5] */
#define MSK_SPI_IRQ_STATUS_EVT_SDI (0x1)  /* [6] */
#define SFT_SPI_IRQ_STATUS_EVT_SDI (6)
#define LSB_SPI_IRQ_STATUS_EVT_SDI (6)
#define MSB_SPI_IRQ_STATUS_EVT_SDI (6)
#define BIT_SPI_IRQ_STATUS_EVT_SDI (0x40)         /* [6] */
#define MSK_SPI_IRQ_STATUS_EVT_SCLK_TIMEOUT (0x1) /* [7] */
#define SFT_SPI_IRQ_STATUS_EVT_SCLK_TIMEOUT (7)
#define LSB_SPI_IRQ_STATUS_EVT_SCLK_TIMEOUT (7)
#define MSB_SPI_IRQ_STATUS_EVT_SCLK_TIMEOUT (7)
#define BIT_SPI_IRQ_STATUS_EVT_SCLK_TIMEOUT (0x80) /* [7] */
#define MSK_SPI_IRQ_STATUS_EVT_SHIFT_DONE (0x1)    /* [8] */
#define SFT_SPI_IRQ_STATUS_EVT_SHIFT_DONE (8)
#define LSB_SPI_IRQ_STATUS_EVT_SHIFT_DONE (8)
#define MSB_SPI_IRQ_STATUS_EVT_SHIFT_DONE (8)
#define BIT_SPI_IRQ_STATUS_EVT_SHIFT_DONE (0x100) /* [8] */
#define MSK_SPI_IRQ_STATUS_RX_FIFO_NEMPTY (0x1)   /* [9] */
#define SFT_SPI_IRQ_STATUS_RX_FIFO_NEMPTY (9)
#define LSB_SPI_IRQ_STATUS_RX_FIFO_NEMPTY (9)
#define MSB_SPI_IRQ_STATUS_RX_FIFO_NEMPTY (9)
#define BIT_SPI_IRQ_STATUS_RX_FIFO_NEMPTY (0x200) /* [9] */
#define MSK_SPI_IRQ_STATUS_RX_FIFO_TIMEOUT (0x1)  /* [10] */
#define SFT_SPI_IRQ_STATUS_RX_FIFO_TIMEOUT (10)
#define LSB_SPI_IRQ_STATUS_RX_FIFO_TIMEOUT (10)
#define MSB_SPI_IRQ_STATUS_RX_FIFO_TIMEOUT (10)
#define BIT_SPI_IRQ_STATUS_RX_FIFO_TIMEOUT (0x400)  /* [10] */
#define MSK_SPI_IRQ_STATUS_RX_FIFO_HIGH_WATER (0x1) /* [11] */
#define SFT_SPI_IRQ_STATUS_RX_FIFO_HIGH_WATER (11)
#define LSB_SPI_IRQ_STATUS_RX_FIFO_HIGH_WATER (11)
#define MSB_SPI_IRQ_STATUS_RX_FIFO_HIGH_WATER (11)
#define BIT_SPI_IRQ_STATUS_RX_FIFO_HIGH_WATER (0x800) /* [11] */
#define MSK_SPI_IRQ_STATUS_RX_FIFO_FULL (0x1)         /* [12] */
#define SFT_SPI_IRQ_STATUS_RX_FIFO_FULL (12)
#define LSB_SPI_IRQ_STATUS_RX_FIFO_FULL (12)
#define MSB_SPI_IRQ_STATUS_RX_FIFO_FULL (12)
#define BIT_SPI_IRQ_STATUS_RX_FIFO_FULL (0x1000) /* [12] */
#define MSK_SPI_IRQ_STATUS_TX_FIFO_EMPTY (0x1)   /* [13] */
#define SFT_SPI_IRQ_STATUS_TX_FIFO_EMPTY (13)
#define LSB_SPI_IRQ_STATUS_TX_FIFO_EMPTY (13)
#define MSB_SPI_IRQ_STATUS_TX_FIFO_EMPTY (13)
#define BIT_SPI_IRQ_STATUS_TX_FIFO_EMPTY (0x2000)  /* [13] */
#define MSK_SPI_IRQ_STATUS_TX_FIFO_LOW_WATER (0x1) /* [14] */
#define SFT_SPI_IRQ_STATUS_TX_FIFO_LOW_WATER (14)
#define LSB_SPI_IRQ_STATUS_TX_FIFO_LOW_WATER (14)
#define MSB_SPI_IRQ_STATUS_TX_FIFO_LOW_WATER (14)
#define BIT_SPI_IRQ_STATUS_TX_FIFO_LOW_WATER (0x4000) /* [14] */
#define MSK_SPI_IRQ_STATUS_TX_FIFO_NFULL (0x1)        /* [15] */
#define SFT_SPI_IRQ_STATUS_TX_FIFO_NFULL (15)
#define LSB_SPI_IRQ_STATUS_TX_FIFO_NFULL (15)
#define MSB_SPI_IRQ_STATUS_TX_FIFO_NFULL (15)
#define BIT_SPI_IRQ_STATUS_TX_FIFO_NFULL (0x8000) /* [15] */

typedef struct
{
  unsigned short evt_rx_fifo_ov_err : 1; /* [0] */
  unsigned short evt_rx_fifo_ur_err : 1; /* [1] */
  unsigned short evt_tx_fifo_ov_err : 1; /* [2] */
  unsigned short evt_tx_fifo_ur_err : 1; /* [3] */
  unsigned short evt_sot : 1;            /* [4] */
  unsigned short evt_eot : 1;            /* [5] */
  unsigned short evt_sdi : 1;            /* [6] */
  unsigned short evt_sclk_timeout : 1;   /* [7] */
  unsigned short evt_shift_done : 1;     /* [8] */
  unsigned short rx_fifo_nempty : 1;     /* [9] */
  unsigned short rx_fifo_timeout : 1;    /* [10] */
  unsigned short rx_fifo_high_water : 1; /* [11] */
  unsigned short rx_fifo_full : 1;       /* [12] */
  unsigned short tx_fifo_empty : 1;      /* [13] */
  unsigned short tx_fifo_low_water : 1;  /* [14] */
  unsigned short tx_fifo_nfull : 1;      /* [15] */
} _PACKED_ spi_irq_status_bf;

typedef union {
  unsigned short val;
  spi_irq_status_bf bf;
} _PACKED_ spi_irq_status_t;

/* SPI_IRQ_MASK */

#define MSK_SPI_IRQ_MASK (0xffff) /* [15:0] */

typedef unsigned short spi_irq_mask_t; /* [15:0] */

/* SPI_IRQ_VENABLE */

#define MSK_SPI_IRQ_VENABLE (0xf) /* [ 3:0] */

typedef unsigned short spi_irq_venable_t; /* [ 3:0] */

/* SPI_IRQ_VDISABLE */

#define MSK_SPI_IRQ_VDISABLE (0xf) /* [ 3:0] */

typedef unsigned short spi_irq_vdisable_t; /* [ 3:0] */

/* SPI_IRQ_VMAX */

#define MSK_SPI_IRQ_VMAX (0x1f) /* [ 4:0] */

typedef unsigned short spi_irq_vmax_t; /* [ 4:0] */

/* SPI_IRQ_VNO */

#define MSK_SPI_IRQ_VNO (0x1f) /* [ 4:0] */

typedef unsigned short spi_irq_vno_t; /* [ 4:0] */

/* SPI */

typedef struct
{
  spi_data_t data;                       /* 0 */
  spi_data_keep_nss_t data_keep_nss;     /* 2 */
  spi_config_t config;                   /* 4 */
  spi_baud_config_t baud_config;         /* 6 */
  spi_timeout_config_t timeout_config;   /* 8 */
  spi_rx_fifo_timeout_t rx_fifo_timeout; /* 10 */
  spi_fifo_clear_t fifo_clear;           /* 12 */
  spi_fifo_levels_t fifo_levels;         /* 14 */
  unsigned short reserved0[8];
  spi_irq_status_t irq_status; /* 32 */
  unsigned short reserved1[1];
  spi_irq_mask_t irq_mask; /* 36 */
  unsigned short reserved2[1];
  spi_irq_venable_t irq_venable;   /* 40 */
  spi_irq_vdisable_t irq_vdisable; /* 42 */
  spi_irq_vmax_t irq_vmax;         /* 44 */
  spi_irq_vno_t irq_vno;           /* 46 */
} _PACKED_ spi_t;

#ifdef __IARC__
#pragma pack()
#endif

// Register definitions for module
// Instance base address BASE_ADDR_SPI_0 0x0240U ... SPI Master and Slave Module 0
// Instance base address BASE_ADDR_SPI_1 0x0280U ... SPI Master and Slave Module 1

#define ADDR_SPI_DATA (0x00U)
#define A_SPI_DATA(ba) ((ba) + ADDR_SPI_DATA)
#define R_SPI_DATA(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_DATA(ba)))
#define RES_SPI_DATA (0x0U)
#define MSB_SPI_DATA 15
#define LSB_SPI_DATA 0
#define AADDR_SPI_0_DATA (BASE_ADDR_SPI_0 + ADDR_SPI_DATA)
#define AADDR_SPI_1_DATA (BASE_ADDR_SPI_1 + ADDR_SPI_DATA)
#define REG_SPI_0_DATA (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_DATA))
#define REG_SPI_1_DATA (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_DATA))

#define ADDR_SPI_DATA_KEEP_NSS (0x02U)
#define A_SPI_DATA_KEEP_NSS(ba) ((ba) + ADDR_SPI_DATA_KEEP_NSS)
#define R_SPI_DATA_KEEP_NSS(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_DATA_KEEP_NSS(ba)))
#define RES_SPI_DATA_KEEP_NSS (0x0U)
#define MSB_SPI_DATA_KEEP_NSS 15
#define LSB_SPI_DATA_KEEP_NSS 0
#define AADDR_SPI_0_DATA_KEEP_NSS (BASE_ADDR_SPI_0 + ADDR_SPI_DATA_KEEP_NSS)
#define AADDR_SPI_1_DATA_KEEP_NSS (BASE_ADDR_SPI_1 + ADDR_SPI_DATA_KEEP_NSS)
#define REG_SPI_0_DATA_KEEP_NSS (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_DATA_KEEP_NSS))
#define REG_SPI_1_DATA_KEEP_NSS (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_DATA_KEEP_NSS))

#define ADDR_SPI_CONFIG (0x04U)
#define A_SPI_CONFIG(ba) ((ba) + ADDR_SPI_CONFIG)
#define R_SPI_CONFIG(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_CONFIG(ba)))
#define RES_SPI_CONFIG (0x79U)
#define MSB_SPI_CONFIG 15
#define LSB_SPI_CONFIG 0
#define AADDR_SPI_0_CONFIG (BASE_ADDR_SPI_0 + ADDR_SPI_CONFIG)
#define AADDR_SPI_1_CONFIG (BASE_ADDR_SPI_1 + ADDR_SPI_CONFIG)
#define REG_SPI_0_CONFIG (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_CONFIG))
#define REG_SPI_1_CONFIG (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_CONFIG))

#define ADDR_SPI_BAUD_CONFIG (0x06U)
#define A_SPI_BAUD_CONFIG(ba) ((ba) + ADDR_SPI_BAUD_CONFIG)
#define R_SPI_BAUD_CONFIG(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_BAUD_CONFIG(ba)))
#define RES_SPI_BAUD_CONFIG (0x0U)
#define MSB_SPI_BAUD_CONFIG 15
#define LSB_SPI_BAUD_CONFIG 0
#define AADDR_SPI_0_BAUD_CONFIG (BASE_ADDR_SPI_0 + ADDR_SPI_BAUD_CONFIG)
#define AADDR_SPI_1_BAUD_CONFIG (BASE_ADDR_SPI_1 + ADDR_SPI_BAUD_CONFIG)
#define REG_SPI_0_BAUD_CONFIG (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_BAUD_CONFIG))
#define REG_SPI_1_BAUD_CONFIG (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_BAUD_CONFIG))

#define ADDR_SPI_TIMEOUT_CONFIG (0x08U)
#define A_SPI_TIMEOUT_CONFIG(ba) ((ba) + ADDR_SPI_TIMEOUT_CONFIG)
#define R_SPI_TIMEOUT_CONFIG(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_TIMEOUT_CONFIG(ba)))
#define RES_SPI_TIMEOUT_CONFIG (0xffffU)
#define MSB_SPI_TIMEOUT_CONFIG 15
#define LSB_SPI_TIMEOUT_CONFIG 0
#define AADDR_SPI_0_TIMEOUT_CONFIG (BASE_ADDR_SPI_0 + ADDR_SPI_TIMEOUT_CONFIG)
#define AADDR_SPI_1_TIMEOUT_CONFIG (BASE_ADDR_SPI_1 + ADDR_SPI_TIMEOUT_CONFIG)
#define REG_SPI_0_TIMEOUT_CONFIG (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_TIMEOUT_CONFIG))
#define REG_SPI_1_TIMEOUT_CONFIG (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_TIMEOUT_CONFIG))

#define ADDR_SPI_RX_FIFO_TIMEOUT (0x0AU)
#define A_SPI_RX_FIFO_TIMEOUT(ba) ((ba) + ADDR_SPI_RX_FIFO_TIMEOUT)
#define R_SPI_RX_FIFO_TIMEOUT(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_RX_FIFO_TIMEOUT(ba)))
#define RES_SPI_RX_FIFO_TIMEOUT (0x0U)
#define MSB_SPI_RX_FIFO_TIMEOUT 15
#define LSB_SPI_RX_FIFO_TIMEOUT 0
#define AADDR_SPI_0_RX_FIFO_TIMEOUT (BASE_ADDR_SPI_0 + ADDR_SPI_RX_FIFO_TIMEOUT)
#define AADDR_SPI_1_RX_FIFO_TIMEOUT (BASE_ADDR_SPI_1 + ADDR_SPI_RX_FIFO_TIMEOUT)
#define REG_SPI_0_RX_FIFO_TIMEOUT (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_RX_FIFO_TIMEOUT))
#define REG_SPI_1_RX_FIFO_TIMEOUT (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_RX_FIFO_TIMEOUT))

#define ADDR_SPI_FIFO_CLEAR (0x0CU)
#define A_SPI_FIFO_CLEAR(ba) ((ba) + ADDR_SPI_FIFO_CLEAR)
#define R_SPI_FIFO_CLEAR(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_FIFO_CLEAR(ba)))
#define RES_SPI_FIFO_CLEAR (0x0U)
#define MSB_SPI_FIFO_CLEAR 2
#define LSB_SPI_FIFO_CLEAR 0
#define AADDR_SPI_0_FIFO_CLEAR (BASE_ADDR_SPI_0 + ADDR_SPI_FIFO_CLEAR)
#define AADDR_SPI_1_FIFO_CLEAR (BASE_ADDR_SPI_1 + ADDR_SPI_FIFO_CLEAR)
#define REG_SPI_0_FIFO_CLEAR (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_FIFO_CLEAR))
#define REG_SPI_1_FIFO_CLEAR (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_FIFO_CLEAR))

#define ADDR_SPI_FIFO_LEVELS (0x0EU)
#define A_SPI_FIFO_LEVELS(ba) ((ba) + ADDR_SPI_FIFO_LEVELS)
#define R_SPI_FIFO_LEVELS(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_FIFO_LEVELS(ba)))
#define RES_SPI_FIFO_LEVELS (0x200U)
#define MSB_SPI_FIFO_LEVELS 14
#define LSB_SPI_FIFO_LEVELS 0
#define AADDR_SPI_0_FIFO_LEVELS (BASE_ADDR_SPI_0 + ADDR_SPI_FIFO_LEVELS)
#define AADDR_SPI_1_FIFO_LEVELS (BASE_ADDR_SPI_1 + ADDR_SPI_FIFO_LEVELS)
#define REG_SPI_0_FIFO_LEVELS (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_FIFO_LEVELS))
#define REG_SPI_1_FIFO_LEVELS (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_FIFO_LEVELS))

#define ADDR_SPI_IRQ_STATUS (0x20U)
#define A_SPI_IRQ_STATUS(ba) ((ba) + ADDR_SPI_IRQ_STATUS)
#define R_SPI_IRQ_STATUS(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_IRQ_STATUS(ba)))
#define RES_SPI_IRQ_STATUS (0x0U)
#define MSB_SPI_IRQ_STATUS 15
#define LSB_SPI_IRQ_STATUS 0
#define AADDR_SPI_0_IRQ_STATUS (BASE_ADDR_SPI_0 + ADDR_SPI_IRQ_STATUS)
#define AADDR_SPI_1_IRQ_STATUS (BASE_ADDR_SPI_1 + ADDR_SPI_IRQ_STATUS)
#define REG_SPI_0_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_IRQ_STATUS))
#define REG_SPI_1_IRQ_STATUS (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_IRQ_STATUS))

#define ADDR_SPI_IRQ_MASK (0x24U)
#define A_SPI_IRQ_MASK(ba) ((ba) + ADDR_SPI_IRQ_MASK)
#define R_SPI_IRQ_MASK(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_IRQ_MASK(ba)))
#define RES_SPI_IRQ_MASK (0x0U)
#define MSB_SPI_IRQ_MASK 15
#define LSB_SPI_IRQ_MASK 0
#define AADDR_SPI_0_IRQ_MASK (BASE_ADDR_SPI_0 + ADDR_SPI_IRQ_MASK)
#define AADDR_SPI_1_IRQ_MASK (BASE_ADDR_SPI_1 + ADDR_SPI_IRQ_MASK)
#define REG_SPI_0_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_IRQ_MASK))
#define REG_SPI_1_IRQ_MASK (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_IRQ_MASK))

#define ADDR_SPI_IRQ_VENABLE (0x28U)
#define A_SPI_IRQ_VENABLE(ba) ((ba) + ADDR_SPI_IRQ_VENABLE)
#define R_SPI_IRQ_VENABLE(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_IRQ_VENABLE(ba)))
#define RES_SPI_IRQ_VENABLE (0x0U)
#define MSB_SPI_IRQ_VENABLE 3
#define LSB_SPI_IRQ_VENABLE 0
#define AADDR_SPI_0_IRQ_VENABLE (BASE_ADDR_SPI_0 + ADDR_SPI_IRQ_VENABLE)
#define AADDR_SPI_1_IRQ_VENABLE (BASE_ADDR_SPI_1 + ADDR_SPI_IRQ_VENABLE)
#define REG_SPI_0_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_IRQ_VENABLE))
#define REG_SPI_1_IRQ_VENABLE (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_IRQ_VENABLE))

#define ADDR_SPI_IRQ_VDISABLE (0x2AU)
#define A_SPI_IRQ_VDISABLE(ba) ((ba) + ADDR_SPI_IRQ_VDISABLE)
#define R_SPI_IRQ_VDISABLE(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_IRQ_VDISABLE(ba)))
#define RES_SPI_IRQ_VDISABLE (0x0U)
#define MSB_SPI_IRQ_VDISABLE 3
#define LSB_SPI_IRQ_VDISABLE 0
#define AADDR_SPI_0_IRQ_VDISABLE (BASE_ADDR_SPI_0 + ADDR_SPI_IRQ_VDISABLE)
#define AADDR_SPI_1_IRQ_VDISABLE (BASE_ADDR_SPI_1 + ADDR_SPI_IRQ_VDISABLE)
#define REG_SPI_0_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_IRQ_VDISABLE))
#define REG_SPI_1_IRQ_VDISABLE (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_IRQ_VDISABLE))

#define ADDR_SPI_IRQ_VMAX (0x2CU)
#define A_SPI_IRQ_VMAX(ba) ((ba) + ADDR_SPI_IRQ_VMAX)
#define R_SPI_IRQ_VMAX(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_IRQ_VMAX(ba)))
#define RES_SPI_IRQ_VMAX (0x10U)
#define MSB_SPI_IRQ_VMAX 4
#define LSB_SPI_IRQ_VMAX 0
#define AADDR_SPI_0_IRQ_VMAX (BASE_ADDR_SPI_0 + ADDR_SPI_IRQ_VMAX)
#define AADDR_SPI_1_IRQ_VMAX (BASE_ADDR_SPI_1 + ADDR_SPI_IRQ_VMAX)
#define REG_SPI_0_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_IRQ_VMAX))
#define REG_SPI_1_IRQ_VMAX (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_IRQ_VMAX))

#define ADDR_SPI_IRQ_VNO (0x2EU)
#define A_SPI_IRQ_VNO(ba) ((ba) + ADDR_SPI_IRQ_VNO)
#define R_SPI_IRQ_VNO(ba) (*(volatile unsigned short *)((unsigned int)A_SPI_IRQ_VNO(ba)))
#define RES_SPI_IRQ_VNO (0x10U)
#define MSB_SPI_IRQ_VNO 4
#define LSB_SPI_IRQ_VNO 0
#define AADDR_SPI_0_IRQ_VNO (BASE_ADDR_SPI_0 + ADDR_SPI_IRQ_VNO)
#define AADDR_SPI_1_IRQ_VNO (BASE_ADDR_SPI_1 + ADDR_SPI_IRQ_VNO)
#define REG_SPI_0_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_SPI_0_IRQ_VNO))
#define REG_SPI_1_IRQ_VNO (*(volatile unsigned short *)((unsigned int)AADDR_SPI_1_IRQ_VNO))

#endif
