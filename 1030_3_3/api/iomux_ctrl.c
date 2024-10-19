
#include "iomux_ctrl.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void iomux_ctrl_select_a(iomux_func_a_t func)
{

  WRITE_REG_16(BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PA_IO_SEL, func);
}

void iomux_ctrl_select_b(iomux_func_b_t func)
{

  WRITE_REG_16(BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PB_IO_SEL, func);
}

void iomux_ctrl_select_c(iomux_port_no_c_t port_no, iomux_func_c_t func)
{

  iomux_ctrl_pc0123_io_sel_t io_sel;

  func = (iomux_func_c_t)(0xF & (int)func);

  if (port_no < 4)
    io_sel.val = READ_REG_U16(BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PC0123_IO_SEL);
  else
    io_sel.val = READ_REG_U16(BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PC4567_IO_SEL);

  switch (port_no)
  {
  case IOMUX_CTRL_PORT_NO_0:
    io_sel.bf.sel_0 = func;
    break;
  case IOMUX_CTRL_PORT_NO_1:
    io_sel.bf.sel_1 = func;
    break;
  case IOMUX_CTRL_PORT_NO_2:
    io_sel.bf.sel_2 = func;
    break;
  case IOMUX_CTRL_PORT_NO_3:
    io_sel.bf.sel_3 = func;
    break;
  case IOMUX_CTRL_PORT_NO_4:
    io_sel.bf.sel_0 = func;
    break;
  case IOMUX_CTRL_PORT_NO_5:
    io_sel.bf.sel_1 = func;
    break;
  case IOMUX_CTRL_PORT_NO_6:
    io_sel.bf.sel_2 = func;
    break;
  case IOMUX_CTRL_PORT_NO_7:
    io_sel.bf.sel_3 = func;
    break;
  }

  if (port_no < 4)
    WRITE_REG_16(BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PC0123_IO_SEL, io_sel.val);
  else
    WRITE_REG_16(BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PC4567_IO_SEL, io_sel.val);
}

void iomux_ctrl_set_lock_a(uint8_t val)
{
  iomux_ctrl_px_lock_t px_lock;

  px_lock.val = 0;
  px_lock.bf.lock = val;
  px_lock.bf.pass = IOMUX_CTRL_WPASS;
  WRITE_REG_16(BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PA_LOCK, px_lock.val);
}

void iomux_ctrl_set_lock_b(uint8_t val)
{
  iomux_ctrl_px_lock_t px_lock;

  px_lock.val = 0;
  px_lock.bf.lock = val;
  px_lock.bf.pass = IOMUX_CTRL_WPASS;
  WRITE_REG_16(BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PB_LOCK, px_lock.val);
}

void iomux_ctrl_set_lock_c(uint8_t val)
{
  iomux_ctrl_px_lock_t px_lock;

  px_lock.val = 0;
  px_lock.bf.lock = val;
  px_lock.bf.pass = IOMUX_CTRL_WPASS;
  WRITE_REG_16(BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PC_LOCK, px_lock.val);
}

uint8_t iomux_ctrl_get_lock_a(void)
{
  iomux_ctrl_px_lock_t px_lock;

  px_lock.val = 0;
  px_lock.val = READ_REG_U16(BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PA_LOCK);
  return (uint8_t)px_lock.bf.lock;
}

uint8_t iomux_ctrl_get_lock_b(void)
{
  iomux_ctrl_px_lock_t px_lock;

  px_lock.val = 0;
  px_lock.val = READ_REG_U16(BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PB_LOCK);
  return (uint8_t)px_lock.bf.lock;
}

uint8_t iomux_ctrl_get_lock_c(void)
{
  iomux_ctrl_px_lock_t px_lock;

  px_lock.val = 0;
  px_lock.val = READ_REG_U16(BASE_ADDR_IOMUX_CTRL + ADDR_IOMUX_CTRL_PC_LOCK);
  return (uint8_t)px_lock.bf.lock;
}
