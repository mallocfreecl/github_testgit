#ifdef T52350

#include "driver_52350.h"
#include "IsrHandler.h"
#include "api.h"
#include "commons.h"
#include "driver_generic.h"
#include "flash_ctrl.h"
#include "irq.h"
#include "parameters.h"
#include "saradc_tables.h"
#include "wdog.h"
#include <stdio.h>

#include "debug.h"

#include "testmode.h"

static void SDK_SystemStateModuleInit(void);
static void SDK_ClockInit(void);
static void SDK_SystemStateModuleInit(void);
static void SDK_GPIOInit(void);
static void SDK_GPIOAInit(void);
static void SDK_GPIOBInit(void);
static void SDK_GPIOCInit(void);
static void SDK_SCIInit(void);
static void SDK_IntInit(void);
static void SDK_GPIOIntInit(void);
static void SDK_SCIIntInit(void);
static void SDK_CCTimerInit(void);
static void SDK_CCTimerIntInit(void);
static void SDK_ADCInit(void);
static void SDK_ADCMUXTiming(u16 mux_timing, u16 mux_ex, u16 clk_div);
static void SDK_ADCIntInit(void);
static void SDK_WDOGInit(void);
static void PWMNStartEvt_Handler(int sno);

void SDK_HardWareInit(void)
{
  SDK_ClockInit();
  SDK_SystemStateModuleInit();
  SDK_GPIOInit();
#if DEBUG_USE_SCI == 1
// SDK_SCIInit();
#endif
  SDK_CCTimerInit();
  SDK_ADCInit();
  SDK_IntInit();
  SDK_WDOGInit();

  /*
  Debug
  enable pwmn start_evt
  */
  pwmn_handler_init();
  pwmn_handler_register(PWMN_IRQ_START_EVT, PWMNStartEvt_Handler);
  pwmn_enable_irq(PWMN_IRQ_START_EVT, true);
}

static void PWMNStartEvt_Handler(int sno)
{
  /* fct test , 21.07.30 by yhd*/
  Test_MOS();
}

static void SDK_ClockInit(void)
{
  sys_state_control_t sys_state_control;
  sys_state_control.val = REG_SYS_STATE_CONTROL;

#if (PAR_SYS_CLK_DEVIDER == 1)
  sys_state_control.bf.sys_clk_sel = SST_CLK_SEL_48_MHz;
  // set symmetrical 48/(2*3+2) = 48/8 = 6MHZ
  sys_state_control.bf.target_clk_l = 3;
  sys_state_control.bf.target_clk_h = 3;
#else
#if (PAR_SYS_CLK_DEVIDER == 2)
  sys_state_control.bf.sys_clk_sel = SST_CLK_SEL_24_MHz;
  // set symmetrical 24/(2*1+2) = 24/4 = 6MHZ
  sys_state_control.bf.target_clk_l = 1;
  sys_state_control.bf.target_clk_h = 1;
#else
  sys_state_control.bf.sys_clk_sel = SST_CLK_SEL_12_MHz;
  // set symmetrical 12/(2*0+2) = 6MHZ
  sys_state_control.bf.target_clk_l = 0;
  sys_state_control.bf.target_clk_h = 0;
#endif
#endif

  REG_SYS_STATE_CONTROL = sys_state_control.val;

  sys_state_set_target_clk(0, 0);
}

static void SDK_SystemStateModuleInit(void)
{
  /*
  MODULE_ENABLE
  */
  sys_state_module_enable(SST_MOD_ENABLE_WDOG, true);
  //#if DEBUG_USE_SCI == 1
  // sys_state_module_enable(SST_MOD_ENABLE_SCI,         true);
  //#else
  sys_state_module_enable(SST_MOD_ENABLE_SCI, false);
  //#endif
  sys_state_module_enable(SST_MOD_ENABLE_SPI_0, false);
  sys_state_module_enable(SST_MOD_ENABLE_SPI_1, false);
  sys_state_module_enable(SST_MOD_ENABLE_GPIO_A, true);
  sys_state_module_enable(SST_MOD_ENABLE_GPIO_B, true);
  sys_state_module_enable(SST_MOD_ENABLE_GPIO_C, true);
  sys_state_module_enable(SST_MOD_ENABLE_CCTIMER_0, true);
  sys_state_module_enable(SST_MOD_ENABLE_CCTIMER_1, true);
  sys_state_module_enable(SST_MOD_ENABLE_CCTIMER_2, true);
  sys_state_module_enable(SST_MOD_ENABLE_CCTIMER_3, false);
  sys_state_module_enable(SST_MOD_ENABLE_SARADC_CTRL, true);
  sys_state_module_enable(SST_MOD_ENABLE_PRE_PWM, true);
  sys_state_module_enable(SST_MOD_ENABLE_PWMN, true);

  /*
  Enable Reset source
  */
  /* eliminate warning, 21.07.30 by yhd */
  sys_state_reset_enable((sst_reset_enable_t)(SST_RESET_ENABLE_WATCHDOG | SST_RESET_ENABLE_SOFTWARE
                                              //| SST_RESET_ENABLE_CPU_PARITY
                                              //| SST_RESET_ENABLE_SRAM_PARITY
                                              //| SST_RESET_ENABLE_FLASH_2BIT_ERR
                                              //| SST_RESET_ENABLE_FLASH_1BIT_ERR
                                              //| SST_RESET_ENABLE_SRAM_WR_PROT
                                              //| SST_RESET_ENABLE_STACK_PROT
                                              //| SST_RESET_ENABLE_EXEC_PROT
                                              ));
}

void SDK_SWRst(void)
{
  sys_state_software_reset();
}

static void SDK_GPIOInit(void)
{
  SDK_GPIOCInit();
  SDK_GPIOAInit();
  SDK_GPIOBInit();
}

static void SDK_GPIOAInit(void)
{
  u16 port_a;

  port_a = (IOMUX_CTRL_FUNC_A0_GPIO |             // DT = GND
            IOMUX_CTRL_FUNC_A1_GPIO |             // RUN
            IOMUX_CTRL_FUNC_A2_SARADC_CTRL_MUX0 | // BEMF_MUX1
            IOMUX_CTRL_FUNC_A3_SARADC_CTRL_MUX1 | // BEMF_MUX2
            IOMUX_CTRL_FUNC_A4_PWMN_U_N |         // Low-Side Channel U
            IOMUX_CTRL_FUNC_A5_PWMN_V_N |         // Low-Side Channel V
            IOMUX_CTRL_FUNC_A6_PWMN_W_N |         // Low-Side Channel W
            IOMUX_CTRL_FUNC_A7_GPIO               // ERROR1
  );

  iomux_ctrl_select_a(port_a);

  gpio_set_output_enable(GPIO_A, GPIO_IO_0, true); // DT = output
  gpio_set_input_enable(GPIO_A, GPIO_IO_0, false);
  gpio_set_data_out(GPIO_A, GPIO_IO_0, false); // DT = GND --> no deadtime

  gpio_set_output_enable(GPIO_A, GPIO_IO_1, true); // Run = output
  gpio_set_input_enable(GPIO_A, GPIO_IO_1, true);
  gpio_set_data_out(GPIO_A, GPIO_IO_1, false); // RUN = GND --> 523.50 enters sleep until init is done

  gpio_set_output_enable(GPIO_A, GPIO_IO_7, false); // ERROR1 = input
  gpio_set_input_enable(GPIO_A, GPIO_IO_7, true);
}

static void SDK_GPIOBInit(void)
{
  u16 port_b;

  port_b = (IOMUX_CTRL_FUNC_B0_GPIO |     // ERROR2
            IOMUX_CTRL_FUNC_B1_PWMN_U_P | // High-Side Channel U
            IOMUX_CTRL_FUNC_B2_PWMN_V_P | // High-Side Channel V
            IOMUX_CTRL_FUNC_B3_PWMN_W_P | // High-Side Channel W
            IOMUX_CTRL_FUNC_B4_GPIO |     // BEMO_INPUT
            IOMUX_CTRL_FUNC_B5_GPIO |     // not used is going to be AMPO / I_MEAS
            IOMUX_CTRL_FUNC_B6_SCI_RXD |  // UART for DEBUG only
            IOMUX_CTRL_FUNC_B7_SCI_TXD    // UART for DEBUG only
  );

  iomux_ctrl_select_b(port_b);

  gpio_set_output_enable(GPIO_B, GPIO_IO_0, false); // ERROR2 = input
  gpio_set_input_enable(GPIO_B, GPIO_IO_0, true);

  gpio_set_output_enable(GPIO_B, GPIO_IO_4, false); // BEM0 = input; BUT analog input
  gpio_set_input_enable(GPIO_B, GPIO_IO_4, true);

  gpio_set_output_enable(GPIO_B, GPIO_IO_5, false); // AMPO / I_MEAS
  gpio_set_input_enable(GPIO_B, GPIO_IO_5, true);

  gpio_set_output_enable(GPIO_B, GPIO_IO_6, false); // not used
  gpio_set_input_enable(GPIO_B, GPIO_IO_6, true);

  gpio_set_output_enable(GPIO_B, GPIO_IO_7, true); // not used
  gpio_set_input_enable(GPIO_B, GPIO_IO_7, false);
}

static void SDK_GPIOCInit(void)
{
  /*
  Enable power latch first.The time from power up to there is 65.6ms
  */
  iomux_ctrl_select_c(IOMUX_CTRL_PORT_NO_6, IOMUX_CTRL_FUNC_C_GPIO);
  gpio_set_data_out(GPIO_C, GPIO_IO_6, true);
  gpio_set_output_enable(GPIO_C, GPIO_IO_6, true);
  gpio_set_input_enable(GPIO_C, GPIO_IO_6, false);

  /* PWM_IN */
  iomux_ctrl_select_c(IOMUX_CTRL_PORT_NO_2, IOMUX_CTRL_FUNC_C_CCTIMER_2_MEAS);
  gpio_set_output_enable(GPIO_C, GPIO_IO_2, false);
  gpio_set_input_enable(GPIO_C, GPIO_IO_2, true);

  /* MCU_DIAG_PWMOUT */
  iomux_ctrl_select_c(IOMUX_CTRL_PORT_NO_4, IOMUX_CTRL_FUNC_C_GPIO);
  // gpio_set_data_out(GPIO_C, GPIO_IO_4, false);
  gpio_set_output_enable(GPIO_C, GPIO_IO_4, true);
  gpio_set_input_enable(GPIO_C, GPIO_IO_4, false);
  SDK_MCUDiagOut(ePinOutLow);

  /* FO_MON */
  iomux_ctrl_select_c(IOMUX_CTRL_PORT_NO_5, IOMUX_CTRL_FUNC_C_GPIO);
  gpio_set_data_out(GPIO_C, GPIO_IO_5, false);
  gpio_set_output_enable(GPIO_C, GPIO_IO_5, false);
  gpio_set_input_enable(GPIO_C, GPIO_IO_5, true);

  /* AmbTemperaturAD */
  iomux_ctrl_select_c(IOMUX_CTRL_PORT_NO_7, IOMUX_CTRL_FUNC_C_GPIO);
  /* 使能PC7为输出口，控制LIN收发器 23.12.26 by lxs */
  gpio_set_output_enable(GPIO_C, GPIO_IO_7, true);
  gpio_set_input_enable(GPIO_C, GPIO_IO_7, false);
}

static void SDK_SCIInit(void)
{
  sci_set_config(
    (sci_cfg)(SCI_ENABLE_RECEIVER | SCI_ENABLE_TRANSMITTER | SCI_ENABLE_RECEIVE_IRQ | SCI_ENABLE_TRANSMIT_IRQ));
  sci_set_baud_rate((sci_baud)SCI_BAUD_24MHZ_9600);
}

static void SDK_IntInit(void)
{
  vic_handler_init();
  SDK_GPIOIntInit();
#if DEBUG_USE_SCI == 1
// SDK_SCIIntInit();
#endif
  SDK_CCTimerIntInit();
  SDK_ADCIntInit();
}

static void SDK_GPIOIntInit(void)
{
  gpio_handler_init(GPIO_A);
  gpio_handler_init(GPIO_B);

  gpio_handler_register(BANK_DRIVER_ERROR1, PIN_DRIVER_ERROR1_SET, MotorDrv_IO_Err_Handler);
  gpio_handler_register(BANK_DRIVER_ERROR2, PIN_DRIVER_ERROR2_SET, MotorDrv_IO_Err_Handler);
  gpio_handler_register(BANK_DRIVER_ERROR1, PIN_DRIVER_ERROR1_CLR, MotorDrv_IO_Err_Handler);
  gpio_handler_register(BANK_DRIVER_ERROR2, PIN_DRIVER_ERROR2_CLR, MotorDrv_IO_Err_Handler);

  // clear interrupts
  (WRITE_REG_16(AADDR_IRQ_DRIVER_ERROR1, MASK(PIN_DRIVER_ERROR1_SET)));
  (WRITE_REG_16(AADDR_IRQ_DRIVER_ERROR2, MASK(PIN_DRIVER_ERROR2_SET)));
  (WRITE_REG_16(AADDR_IRQ_DRIVER_ERROR1, MASK(PIN_DRIVER_ERROR1_CLR)));
  (WRITE_REG_16(AADDR_IRQ_DRIVER_ERROR2, MASK(PIN_DRIVER_ERROR2_CLR)));

  // enable interrupts
  gpio_enable_irq(BANK_DRIVER_ERROR1, PIN_DRIVER_ERROR1_SET, true); // do not clear the error automatically
  gpio_enable_irq(BANK_DRIVER_ERROR2, PIN_DRIVER_ERROR2_SET, true); // do not clear the error automatically
  gpio_enable_irq(BANK_DRIVER_ERROR1, PIN_DRIVER_ERROR1_CLR, true); // do not clear the error automatically
  gpio_enable_irq(BANK_DRIVER_ERROR1, PIN_DRIVER_ERROR2_CLR, true); // do not clear the error automatically
}

static void SDK_SCIIntInit(void)
{
  sci_handler_init(SCI);
  sci_handler_register(SCI, SCI_IRQ_RECEIVE, SCIRxHandler);
  sci_handler_register(SCI, SCI_IRQ_TRANSMIT, SCITxHandler);
  sci_enable_irq(SCI, SCI_IRQ_RECEIVE, true);
  /*
  This is Tx buf empty intterrupt!!!Enable and disable it within Tx routing.
  */
  // sci_enable_irq(SCI, SCI_IRQ_TRANSMIT, true);
}

static void SDK_CCTimerInit()
{
  /*
  timer_clk = sys_clk/p
  */

  /*
  Config CCTimer0 for scheduler time base
  */
  cctimer_config_loop_timer(CCTIMER_0, CCT_A);
  cctimer_config_loop_timer(CCTIMER_0, CCT_B);
  cctimer_set_prescaler(CCTIMER_0, 240);
  WRITE_REG_16(AADDR_CCTIMER_0_CONTROL, 0xFFFF);
  cctimer_set_compare(CCTIMER_0, CCT_A, 200 / PAR_SYS_CLK_DEVIDER);  // 1ms interrupt
  cctimer_set_compare(CCTIMER_0, CCT_B, 2000 / PAR_SYS_CLK_DEVIDER); // 10ms interrupt

  /*
    Diag_out Test
  */
  // timer1, a, count clock cycles,
  cctimer_config(CCTIMER_1, CCT_A, CCT_CLK_SEL_PRESC_SYS_CLK, CCT_STA_SEL_OWN_COMPARE, CCT_CAP_SEL_OTHER_COMPARE,
                 CCT_CMP_LOOP);
  cctimer_config(CCTIMER_1, CCT_B, CCT_CLK_SEL_PRESC_SYS_CLK, CCT_STA_SEL_OTHER_COMPARE, CCT_CAP_SEL_OTHER_COMPARE,
                 CCT_CMP_LOOP);
  cctimer_set_prescaler(CCTIMER_1, 48);
  WRITE_REG_16(AADDR_CCTIMER_1_CONTROL, 0xFFFF); // enable and restart counters
  WRITE_REG_16(AADDR_CCTIMER_1_CAPCMP_A, 162);   // period
  WRITE_REG_16(AADDR_CCTIMER_1_CAPCMP_B, 81);    // duty

  /*
  Config CCtimer2 for pwm in captrue.
  CCT_A capture low pulse.
  CCT_B capture period pulse.
  */
  cctimer_config(CCTIMER_2, CCT_A, CCT_CLK_SEL_PRESC_SYS_CLK, CCT_STA_SEL_MEAS_NEGEDGE, CCT_CAP_SEL_MEAS_POSEDGE,
                 CCT_CAP_MODE);
  cctimer_config(CCTIMER_2, CCT_B, CCT_CLK_SEL_PRESC_SYS_CLK, CCT_STA_SEL_MEAS_NEGEDGE, CCT_CAP_SEL_MEAS_NEGEDGE,
                 CCT_CAP_MODE);
  cctimer_set_prescaler(CCTIMER_2, 48);
  WRITE_REG_16(AADDR_CCTIMER_2_CONTROL, 0xFFFF); // enable a and b counter, restart a and b counter and restart
                                                 // prescaler
  WRITE_REG_16(AADDR_CCTIMER_2_CAPCMP_A, 0);     // reset result value
  WRITE_REG_16(AADDR_CCTIMER_2_CAPCMP_B, 0);     // reset result value
}

static void SDK_CCTimerIntInit(void)
{
  /*
  Config CCTimer0 for scheduler time base
  */
  cctimer_handler_init(CCTIMER_0);
  cctimer_handler_register(CCTIMER_0, CCTIMER_IRQ_RESTART_A, CCTimer0_A_RestartHandler);
  cctimer_handler_register(CCTIMER_0, CCTIMER_IRQ_RESTART_B, CCTimer0_B_RestartHandler);
  cctimer_enable_irq(CCTIMER_0, CCTIMER_IRQ_RESTART_A, true);
  cctimer_enable_irq(CCTIMER_0, CCTIMER_IRQ_RESTART_B, true);

  cctimer_handler_init(CCTIMER_1);

  /*
  Config CCtimer2 for pwm in captrue
  */
  cctimer_handler_init(CCTIMER_2);
  cctimer_handler_register(CCTIMER_2, CCTIMER_IRQ_RESTART_A, CCTimer2_A_RestartHandler);
  cctimer_handler_register(CCTIMER_2, CCTIMER_IRQ_CAPTURE_A, CCTimer2_A_CaptureHandler);
  cctimer_handler_register(CCTIMER_2, CCTIMER_IRQ_OVERFLOW_A, CCTimer2_A_OverflowHandler);
  cctimer_handler_register(CCTIMER_2, CCTIMER_IRQ_RESTART_B, CCTimer2_B_RestartHandler);
  cctimer_handler_register(CCTIMER_2, CCTIMER_IRQ_CAPTURE_B, CCTimer2_B_CaptureHandler);
  cctimer_handler_register(CCTIMER_2, CCTIMER_IRQ_OVERFLOW_B, CCTimer2_B_OverflowHandler);
  cctimer_enable_irq(CCTIMER_2, CCTIMER_IRQ_RESTART_A, true);
  cctimer_enable_irq(CCTIMER_2, CCTIMER_IRQ_CAPTURE_A, true);
  cctimer_enable_irq(CCTIMER_2, CCTIMER_IRQ_OVERFLOW_A, true);
  cctimer_enable_irq(CCTIMER_2, CCTIMER_IRQ_RESTART_B, true);
  cctimer_enable_irq(CCTIMER_2, CCTIMER_IRQ_CAPTURE_B, true);
  cctimer_enable_irq(CCTIMER_2, CCTIMER_IRQ_OVERFLOW_B, true);
}

static void SDK_ADCInit(void)
{
  saradc_ctrl_cfg_t cfg;
  cfg.bf.adc_on = 1;
  cfg.bf.adc_reset = 1;
  cfg.bf.mux_sel = DRIVER_WITH_MUXER;
  cfg.bf.ext_sel = DRIVER_MUXER_CHANNEL_NUMBER;
  saradc_ctrl_set_cfg(cfg);

  /*
  adc_clk_div = 2, adc_clk = sys_clk/(2*adc_clk_div)=24M/(2*2)=6M
  sample_extension = 10 * (adc_clk/2) cycles, 10 cycles & 3M
  mux_phase:
  Clock edge number when the multiplexer is changed.
  0 switches the muliplexer for current sampling command
  5..28 switches the muliplexer for next sampling command
  */
  SDK_ADCMUXTiming(5, 10, 2);

  // sync out
  saradc_ctrl_sync_out_cfg_t sync_cfg;
  saradc_ctrl_sync_out_trig_t sync_trig;
  sync_cfg.val = 0;
  sync_cfg.bf.length = UINT8_MAX;
  sync_cfg.bf.pol = 1; // polarity of sync_out when asserted
  sync_cfg.bf.src = 2; // 0:base_phase 1:pwm_phase 2:list_cmd 3:disable
  sync_trig = 0;
  WRITE_REG_16(AADDR_SARADC_CTRL_SYNC_OUT_CFG, sync_cfg.val);
  WRITE_REG_16(AADDR_SARADC_CTRL_SYNC_OUT_TRIG, sync_trig);

  WRITE_REG_16(AADDR_SARADC_CTRL_WADR_MIN, SARADC_MEM_MIN);
  WRITE_REG_16(AADDR_SARADC_CTRL_WADR_MAX, SARADC_MEM_MAX);

  /*
  dead_time_wait_0 :Delay to sample in a deadtime for current measurements.
  dead_time_wait_1 :Delay to sample voltage of a rising pwm edge in a deadtime.
  dead_time_wait_2 :Delay to sample voltage of a falling pwm edge in a deadtime.
  */
  saradc_ctrl_set_dead_time_wait0((saradc_ctrl_dead_time_wait_t)DRIVER_DELAY_0);
  saradc_ctrl_set_dead_time_wait1((saradc_ctrl_dead_time_wait_t)DRIVER_DELAY_1);
  saradc_ctrl_set_dead_time_wait2((saradc_ctrl_dead_time_wait_t)DRIVER_DELAY_2);
}

static void SDK_ADCMUXTiming(u16 mux_timing, u16 mux_ex, u16 clk_div)
{
  saradc_ctrl_cfg_sar_timing_t cfg_sar_timing;
  cfg_sar_timing.val = 0;
  cfg_sar_timing.bf.adc_clk_div = clk_div;
  cfg_sar_timing.bf.mux_phase = mux_timing;
  cfg_sar_timing.bf.sampling_extension = mux_ex;
  saradc_ctrl_set_cfg_sar_timing(cfg_sar_timing);
}

static void SDK_ADCIntInit(void)
{
  saradc_ctrl_handler_init();
  saradc_ctrl_handler_register(SARADC_CTRL_IRQ_LIST_DONE_EVT, ADCListDoneHandler);
  saradc_ctrl_enable_irq(SARADC_CTRL_IRQ_LIST_DONE_EVT, true);
  saradc_ctrl_handler_register(SARADC_CTRL_IRQ_DMA_WRITE_ERR, ADCDMAErrorHandler);
  saradc_ctrl_enable_irq(SARADC_CTRL_IRQ_DMA_WRITE_ERR, true);
  saradc_ctrl_handler_register(SARADC_CTRL_IRQ_DMA_READ_ERR, ADCDMAErrorHandler);
  saradc_ctrl_enable_irq(SARADC_CTRL_IRQ_DMA_READ_ERR, true);
}

static void SDK_WDOGInit(void)
{
#if (PAR_SYS_CLK_DEVIDER == 1)
  // 48M
#define WDOG_PRE_SCALER 240
#elif (PAR_SYS_CLK_DEVIDER == 2)
  // 24M
#define WDOG_PRE_SCALER 240
#else
  // 12M
#define WDOG_PRE_SCALER 60
#endif

  /*
  10us per count , Reset time is 655.35ms
  */
  wdog_init(WDOG, WDOG_PRE_SCALER, 65535);

  /* Disable window watchdog */
  wdog_win_config(WDOG, 0, false);

  wdog_enable(WDOG);
}

void SDK_FeedWDOG(void)
{
  wdog_restart(WDOG);
}

void SDK_MotorDrvOff(void)
{
  gpio_set_data_out(BANK_DRIVER_RUN, PIN_DRIVER_RUN, false); // RUN = GND --> 523.50 enters sleep
}

void SDK_MotorDrvOn(void)
{
  gpio_set_data_out(BANK_DRIVER_RUN, PIN_DRIVER_RUN, true); // RUN = VCC --> 523.50 leaves sleep
}

void SDK_MotorDrvLowPower(void)
{
  gpio_set_data_out(BANK_DRIVER_RUN, PIN_DRIVER_RUN, true); // RUN = VCC --> 523.50 leaves sleep
  // we need power for the muxer to measure windmilling
}

driver_error_t SDK_MotorDrvGetStatus(void)
{
  u8 error1_cnt = 0;
  u8 error2_cnt = 0;
  u8 run_cnt = 0;
  bool error1;
  bool error2;
  bool run;

  // filter interrupts caused by signal disturbance and report the correct status
  static const u8 samples = 11;
  for (int i = 0; i < samples; i++)
  {
    error1_cnt += gpio_get_data_in(BANK_DRIVER_ERROR1, PIN_DRIVER_ERROR1);
    error2_cnt += gpio_get_data_in(BANK_DRIVER_ERROR2, PIN_DRIVER_ERROR2);
    run_cnt += gpio_get_data_in(BANK_DRIVER_RUN, PIN_DRIVER_RUN);
  }

  error1 = (error1_cnt > (samples >> 1)) ? true : false;
  error2 = (error2_cnt > (samples >> 1)) ? true : false;
  run = (run_cnt > (samples >> 1)) ? true : false;

  u8 error = ((error2 << 1) | error1);
  driver_error_t driver_error;

  if ((run == false) && (error == 3))
  {
    error = 4;
  }

  switch (error)
  {
  case 0:
    driver_error = DRIVER_OK;
    break;
  case 1:
    driver_error = DRIVER_VG_UNDERVOLTAGE;
    break;
  case 2:
    driver_error = DRIVER_OVERTEMP;
    break;
  case 3:
    driver_error = DRIVER_OVERCURRENT;
    break;
  case 4:
    driver_error = DRIVER_VCC_UNDERVOLTAGE;
    break;
  default:
    driver_error = DRIVER_UNKNOWN;
    break;
  }

  return driver_error;
}

void SDK_MotorDrvClearError(driver_error_t error)
{
  // if ok enable driver again or disable.
  if (error != DRIVER_OK)
  {
    SDK_MotorDrvOff();
    (WRITE_REG_16(AADDR_IRQ_DRIVER_ERROR2, MASK(PIN_DRIVER_ERROR1_CLR)));
    (WRITE_REG_16(AADDR_IRQ_DRIVER_ERROR1, MASK(PIN_DRIVER_ERROR2_CLR)));
  }
  else
  {
    SDK_MotorDrvOn();
    (WRITE_REG_16(AADDR_IRQ_DRIVER_ERROR2, MASK(PIN_DRIVER_ERROR1_SET)));
    (WRITE_REG_16(AADDR_IRQ_DRIVER_ERROR1, MASK(PIN_DRIVER_ERROR2_SET)));
  }
}

void SDK_MCUDiagOut(PinOut_t Out)
{
  static u8 OverRun = 0;
  static PinOut_t LastOut = ePinOutInValid;

  if (OverRun)
  {
    return;
  }
  OverRun = 1;

  if (Out != LastOut)
  {
    if (Out == ePinOutToggle)
    {
      if (LastOut == ePinOutLow)
      {
        Out = ePinOutHigh;
      }
      else if (LastOut == ePinOutHigh)
      {
        Out = ePinOutLow;
      }
      else
      {
      }
    }

    gpio_set_data_out(GPIO_C, GPIO_IO_4, (Out == ePinOutHigh) ? true : false);

    LastOut = Out;
  }

  OverRun = 0;
}

void SDK_SCITxIntEn(bool Enable)
{
  sci_enable_irq(SCI, SCI_IRQ_TRANSMIT, Enable);
}

void SDK_InterruptEnable(void)
{
  __enable_interrupt();
}

void SDK_InterruptDisable(void)
{
  __disable_interrupt();
}

/* Chip fault monitor, 21.07.30 by yhd */
ChipFaults_t ChipFaults;

bool SDK_IsChipFault(void)
{
  static u8 Flag = 0;
  static u16 reset_status = 0;

  if (!Flag)
  {
    Flag = 1;

    reset_status = sys_state_get_reset_status();
    sys_state_clear_reset_status();
  }
  sys_state_irq_status_t sys_state_irq_status;
  sys_state_irq_status.val = REG_SYS_STATE_IRQ_STATUS;
  sys_state_clear_all_irq_events();

  ChipFaults.bit.SysClkFail = ((reset_status & SST_RESET_STATUS_SYS_CLK_FAIL) != 0);
  ChipFaults.bit.WDogRst = ((reset_status & SST_RESET_STATUS_WATCHDOG) != 0) || sys_state_irq_status.bf.watchdog;
  ChipFaults.bit.CPUParityRst =
    ((reset_status & SST_RESET_STATUS_CPU_PARITY) != 0) || sys_state_irq_status.bf.cpu_parity;
  ChipFaults.bit.SRAMParity =
    ((reset_status & SST_RESET_STATUS_SRAM_PARITY) != 0) || sys_state_irq_status.bf.sram_parity;
  ChipFaults.bit.FlashBitErr1 =
    ((reset_status & SST_RESET_STATUS_FLASH_1BIT_ERR) != 0) || sys_state_irq_status.bf.flash_1bit_err;
  ChipFaults.bit.FlashBitErr2 =
    ((reset_status & SST_RESET_STATUS_FLASH_2BIT_ERR) != 0) || sys_state_irq_status.bf.flash_2bit_err;
  ChipFaults.bit.sram_wr_prot =
    ((reset_status & SST_RESET_STATUS_SRAM_WR_PROT) != 0) || sys_state_irq_status.bf.sram_wr_prot;
  ChipFaults.bit.stack_prot = ((reset_status & SST_RESET_STATUS_STACK_PROT) != 0) || sys_state_irq_status.bf.stack_prot;
  ChipFaults.bit.exec_prot = ((reset_status & SST_RESET_STATUS_EXEC_PROT) != 0) || sys_state_irq_status.bf.exec_prot;

  ChipFaults.bit.bad_access = (mem_prot_get_access_addr() != 0) || (mem_prot_get_access_pc() != 0);
  mem_prot_access_clear();

  sci_status sci_status1 = (sci_status)REG_SCI_STATUS;
  ChipFaults.bit.SCI_FE = ((sci_status1 & SCI_FRAME_ERROR) != 0);
  ChipFaults.bit.SCI_OV = ((sci_status1 & SCI_RECEIVE_OVERRUN) != 0);

  saradc_ctrl_irq_status_t saradc_ctrl_irq_status;
  saradc_ctrl_irq_status.val = REG_SARADC_CTRL_IRQ_STATUS;
  ChipFaults.bit.dma_read_err = saradc_ctrl_irq_status.bf.dma_read_err;
  ChipFaults.bit.dma_write_err = saradc_ctrl_irq_status.bf.dma_write_err;

  // pre_pwm_irq_status_t pre_pwm_irq_status;
  // pre_pwm_irq_status.val = REG_PRE_PWM_IRQ_STATUS;
  ChipFaults.bit.reload_error_evt = 0; // pre_pwm_irq_status.bf.reload_error_evt;

  pwmn_irq_status_t pwmn_irq_status;
  pwmn_irq_status.val = REG_PWMN_IRQ_STATUS;
  ChipFaults.bit.overcurrent = pwmn_irq_status.bf.oc;
  /* 将立即数替换为宏定义  2023.12.15 by lxs */ 
  ChipFaults.bit.DrvOc = ((MotorVar.FaultRecord & (1u << MOTOR_API_FAULT_RECORD_MSK_DRV_OC_CNT)) != 0);
  ChipFaults.bit.DrvOT = ((MotorVar.FaultRecord & (1u << MOTOR_API_FAULT_RECORD_MSK_DRV_OT_CNT)) != 0);
  ChipFaults.bit.VCC_UV = ((MotorVar.FaultRecord & (1u << MOTOR_API_FAULT_RECORD_MSK_DRV_VCC_LOW_CNT)) != 0);
  ChipFaults.bit.VG_UV = ((MotorVar.FaultRecord & (1u << MOTOR_API_FAULT_RECORD_MSK_DRV_VG_LOW_CNT)) != 0);
  
  return (driver_status != DRIVER_OK);
}

void SDK_ChipSleep(void)
{
  SDK_MotorDrvOff();
  gpio_set_data_out(GPIO_C, GPIO_IO_6, false);
}

void SDK_ChipReset(void)
{
/* 复位前关闭桥区 23.12.15 by lxs */
  SDK_MotorDrvOff();
  SDK_SWRst();
}

void SDK_EEPROM_Write()
{
}

void SDK_SCIInitLater(void)
{
  sys_state_module_enable(SST_MOD_ENABLE_SCI, true);
  SDK_SCIInit();
  SDK_SCIIntInit();
}

#endif // T52350
