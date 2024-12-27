#ifndef HAVE_CCTIMER_H
#define HAVE_CCTIMER_H

#include "base.h"

#include "cctimer_bf.h"
#include "cctimer_irq.h"

#include "vic.h"

typedef enum
{
  CCT_A = 1,
  CCT_B = 2
} cctimer_subdev_t;

typedef enum
{
  CCT_CMP_MODE = 0,
  CCT_CMP_ONCE = 1,
  CCT_CMP_LOOP = 2,
  CCT_CAP_MODE = 3
} capcmp_mode_t;

typedef enum
{
  CCT_CMD_A = 1, // counter A restart command
  CCT_CMD_B = 2, // counter B restart command
  CCT_CMD_P = 4  // prescaler restart command
} cctimer_cmd_t;

// clock, restart and capture SELECT enums

typedef enum
{
  CCT_CLK_SEL_PRESC_SYS_CLK = 0,
  CCT_CLK_SEL_MEAS_POSEDGE = 1,
  CCT_CLK_SEL_MEAS_NEGEDGE = 2,
  CCT_CLK_SEL_PRE_SELECTED = 3
} clk_sel_t;

typedef enum
{
  CCT_STA_SEL_OWN_COMPARE = 0,
  CCT_STA_SEL_OTHER_COMPARE = 1,
  CCT_STA_SEL_MEAS_POSEDGE = 2,
  CCT_STA_SEL_MEAS_NEGEDGE = 3,
  CCT_STA_SEL_PRE_SELECTED = 4
} restart_sel_t;

typedef enum
{
  CCT_CAP_SEL_OTHER_COMPARE = 0,
  CCT_CAP_SEL_MEAS_POSEDGE = 1,
  CCT_CAP_SEL_MEAS_NEGEDGE = 2,
  CCT_CAP_SEL_PRE_SELECTED = 3
} capture_sel_t;

// COMMON clock, restart and capture PRE-SELECT enum

typedef enum
{
  CCT_CLK_SEL_HALL_60_DEG = 0,
  CCT_CLK_SEL_INCR_STEP = 1,
  CCT_CLK_SEL_INCR_ZERO = 2,
  CCT_CLK_SEL_SCI_BAUD_CLK = 3,
  CCT_CLK_SEL_UNCONNECTED = 4,

  CCT_CLK_SEL_SYNC_U_POSEDGE = 8,
  CCT_CLK_SEL_SYNC_V_POSEDGE = 9,
  CCT_CLK_SEL_SYNC_W_POSEDGE = 10,
  CCT_CLK_SEL_SYNC_U_NEGEDGE = 11,
  CCT_CLK_SEL_SYNC_V_NEGEDGE = 12,
  CCT_CLK_SEL_SYNC_W_NEGEDGE = 13
} pre_sel_t;

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void cctimer_set_prescaler(cctimer_num_t dev, uint16_t prescaler);
uint16_t cctimer_get_prescaler(cctimer_num_t dev);

void cctimer_config(cctimer_num_t dev, cctimer_subdev_t subdev, clk_sel_t clk_sel, restart_sel_t sta_sel,
                    capture_sel_t cap_sel, capcmp_mode_t mode);

void cctimer_enable(cctimer_num_t dev, cctimer_subdev_t subdevs, bool enable);

void cctimer_set_compare(cctimer_num_t dev, cctimer_subdev_t subdev, uint16_t cmp_val);
uint16_t cctimer_get_compare(cctimer_num_t dev, cctimer_subdev_t subdev);
uint16_t cctimer_get_counter(cctimer_num_t dev, cctimer_subdev_t subdev);
uint16_t cctimer_get_capture(cctimer_num_t dev, cctimer_subdev_t subdev);

void cctimer_restart(cctimer_num_t dev, cctimer_cmd_t cmds);

void cctimer_set_presel(cctimer_num_t dev, cctimer_subdev_t subdev, pre_sel_t clk_sel, pre_sel_t sta_sel,
                        pre_sel_t cap_sel);

/* ======================================================================= */
/* HIGHER LEVEL DEFINES                                                    */
/* ======================================================================= */

#define cctimer_config_loop_timer(dev, subdev)                                                                         \
  cctimer_config(dev, subdev, CCT_CLK_SEL_PRESC_SYS_CLK, CCT_STA_SEL_OWN_COMPARE, (capture_sel_t)0, CCT_CMP_LOOP)

#define cctimer_config_once_timer(dev, subdev)                                                                         \
  cctimer_config(dev, subdev, CCT_CLK_SEL_PRESC_SYS_CLK, CCT_STA_SEL_OWN_COMPARE, (capture_sel_t)0, CCT_CMP_ONCE)

#define cctimer_config_capture(dev, subdev, restart, capture)                                                          \
  cctimer_config(dev, subdev, CCT_CLK_SEL_PRESC_SYS_CLK, restart, capture, CCT_CAP_MODE)

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

void cctimer_handler_init(cctimer_num_t cctimer_no);

void cctimer_handler_register(cctimer_num_t cctimer_no, cctimer_irq_t irq, callback_t callback);

void cctimer_enable_irq(cctimer_num_t cctimer_no, cctimer_irq_t irq, bool enable);

uint16_t cctimer_get_irq_status(cctimer_num_t cctimer_no);

void cctimer_clear_all_irq_events(cctimer_num_t cctimer_no);

#endif /* HAVE_CCTIMER_H */
