#ifndef HAVE_SYS_STATE_H
#define HAVE_SYS_STATE_H

#include "base.h"

#include "sys_state_bf.h"
#include "sys_state_irq.h"

#include "vic.h"

typedef enum
{
  SST_MOD_ENABLE_WDOG = (1 << 0),
  SST_MOD_ENABLE_SCI = (1 << 1),
  SST_MOD_ENABLE_SPI_0 = (1 << 2),
  SST_MOD_ENABLE_SPI_1 = (1 << 3),
  SST_MOD_ENABLE_GPIO_A = (1 << 4),
  SST_MOD_ENABLE_GPIO_B = (1 << 5),
  SST_MOD_ENABLE_GPIO_C = (1 << 6),
  SST_MOD_ENABLE_CCTIMER_0 = (1 << 7),
  SST_MOD_ENABLE_CCTIMER_1 = (1 << 8),
  SST_MOD_ENABLE_CCTIMER_2 = (1 << 9),
  SST_MOD_ENABLE_CCTIMER_3 = (1 << 10),
  SST_MOD_ENABLE_SARADC_CTRL = (1 << 11),
  SST_MOD_ENABLE_PRE_PWM = (1 << 12),
  SST_MOD_ENABLE_PWMN = (1 << 13)
} sst_mod_enable_t;

typedef enum
{
  SST_RESET_STATUS_POR = (1 << SFT_SYS_STATE_RESET_STATUS_POR),
  SST_RESET_STATUS_VDDIO_OK = (1 << SFT_SYS_STATE_RESET_STATUS_VDDIO_OK),
  SST_RESET_STATUS_VDDC_OK = (1 << SFT_SYS_STATE_RESET_STATUS_VDDC_OK),
  SST_RESET_STATUS_NRSTI = (1 << SFT_SYS_STATE_RESET_STATUS_NRSTI),
  SST_RESET_STATUS_SYS_CLK_FAIL = (1 << SFT_SYS_STATE_RESET_STATUS_SYS_CLK_FAIL),
  SST_RESET_STATUS_WATCHDOG = (1 << SFT_SYS_STATE_RESET_STATUS_WATCHDOG),
  SST_RESET_STATUS_SOFTWARE = (1 << SFT_SYS_STATE_RESET_STATUS_SW_RESET),
  SST_RESET_STATUS_CPU_PARITY = (1 << SFT_SYS_STATE_RESET_STATUS_CPU_PARITY),
  SST_RESET_STATUS_SRAM_PARITY = (1 << SFT_SYS_STATE_RESET_STATUS_SRAM_PARITY),
  SST_RESET_STATUS_FLASH_2BIT_ERR = (1 << SFT_SYS_STATE_RESET_STATUS_FLASH_2BIT_ERR),
  SST_RESET_STATUS_FLASH_1BIT_ERR = (1 << SFT_SYS_STATE_RESET_STATUS_FLASH_1BIT_ERR),
  SST_RESET_STATUS_SRAM_WR_PROT = (1 << SFT_SYS_STATE_RESET_STATUS_SRAM_WR_PROT),
  SST_RESET_STATUS_STACK_PROT = (1 << SFT_SYS_STATE_RESET_STATUS_STACK_PROT),
  SST_RESET_STATUS_EXEC_PROT = (1 << SFT_SYS_STATE_RESET_STATUS_EXEC_PROT),
} sst_reset_status_t;

typedef enum
{
  SST_RESET_ENABLE_WATCHDOG = (1 << SFT_SYS_STATE_RESET_ENABLE_WATCHDOG),
  SST_RESET_ENABLE_SOFTWARE = (1 << SFT_SYS_STATE_RESET_ENABLE_SW_RESET),
  SST_RESET_ENABLE_CPU_PARITY = (1 << SFT_SYS_STATE_RESET_ENABLE_CPU_PARITY),
  SST_RESET_ENABLE_SRAM_PARITY = (1 << SFT_SYS_STATE_RESET_ENABLE_SRAM_PARITY),
  SST_RESET_ENABLE_FLASH_2BIT_ERR = (1 << SFT_SYS_STATE_RESET_ENABLE_FLASH_2BIT_ERR),
  SST_RESET_ENABLE_FLASH_1BIT_ERR = (1 << SFT_SYS_STATE_RESET_ENABLE_FLASH_1BIT_ERR),
  SST_RESET_ENABLE_SRAM_WR_PROT = (1 << SFT_SYS_STATE_RESET_ENABLE_SRAM_WR_PROT),
  SST_RESET_ENABLE_STACK_PROT = (1 << SFT_SYS_STATE_RESET_ENABLE_STACK_PROT),
  SST_RESET_ENABLE_EXEC_PROT = (1 << SFT_SYS_STATE_RESET_ENABLE_EXEC_PROT),
} sst_reset_enable_t;

typedef enum
{
  SST_CLK_SEL_4_MHz = 0,
  SST_CLK_SEL_8_MHz = 1,
  SST_CLK_SEL_12_MHz = 2,
  SST_CLK_SEL_24_MHz = 3,
  SST_CLK_SEL_48_MHz = 4
} sst_clk_sel_t;

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void sys_state_module_enable(sst_mod_enable_t modules, bool enable);

void sys_state_set_sys_clk(sst_clk_sel_t sel);
void sys_state_set_drv_strength(bool strong);
void sys_state_use_adc_clk_shifted(bool use_shifted);
void sys_state_adc_clk_delay(uint8_t delay);
void sys_state_set_target_clk(uint8_t clk_l, uint8_t clk_h);

uint16_t sys_state_get_reset_status(void);
void sys_state_clear_reset_status(void);
void sys_state_reset_enable(sst_reset_enable_t resets);

void sys_state_software_reset(void);

void sys_state_set_calibration(uint8_t vref, uint8_t bgap, uint8_t sys_osc);
void sys_state_set_calibration_lock(void);

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

void sys_state_handler_init(void);

void sys_state_handler_register(sys_state_irq_t irq, callback_t callback);

void sys_state_enable_irq(sys_state_irq_t irq, bool enable);

sys_state_irq_status_t sys_state_get_irq_status(void);

void sys_state_clear_all_irq_events(void);

#define sys_state_handler_register(irq, cb) irq_handler_register(VIC_IRQ_SYS_STATE, irq, cb)

#define sys_state_enable_irq(irq, en)                                                                                  \
  {                                                                                                                    \
    if (en)                                                                                                            \
      irq_enable(VIC_IRQ_SYS_STATE, irq);                                                                              \
    else                                                                                                               \
      irq_disable(VIC_IRQ_SYS_STATE, irq);                                                                             \
  }

#define sys_state_get_irq_status() ((sys_state_irq_status_t)(unsigned short)irq_get_status(VIC_IRQ_SYS_STATE))

#define sys_state_clear_all_irq_events() irq_clear_all_events(VIC_IRQ_SYS_STATE)

#endif /* HAVE_SYS_STATE_H */
