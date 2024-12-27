#include "mem_prot.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void mem_prot_set_exec_enalbe(uint8_t part, uint16_t val)
{
  if (part < 4)
  {
    WRITE_REG_16(MEM_PROT + ADDR_MEM_PROT_EXEC_ENABLE_0 + 2 * part, val);
  }
}

void mem_prot_set_stack_enable(uint16_t val)
{
  WRITE_REG_16(MEM_PROT + ADDR_MEM_PROT_STACK_ENABLE, val);
}

void mem_prot_set_sram_wr_enable(uint16_t val)
{
  WRITE_REG_16(MEM_PROT + ADDR_MEM_PROT_SRAM_WR_ENABLE, val);
}

uint16_t mem_prot_get_access_addr(void)
{
  return READ_REG_U16(MEM_PROT + ADDR_MEM_PROT_ACCESS_ADDR);
}

uint16_t mem_prot_get_access_pc(void)
{
  return READ_REG_U16(MEM_PROT + ADDR_MEM_PROT_ACCESS_PC);
}

uint16_t mem_prot_get_access_type_type(void)
{
  mem_prot_access_type_t mem_prot_access_type;
  mem_prot_access_type.val = READ_REG_U16(MEM_PROT + ADDR_MEM_PROT_ACCESS_TYPE);
  return mem_prot_access_type.bf.type;
}

uint16_t mem_prot_get_access_type_bus(void)
{
  mem_prot_access_type_t mem_prot_access_type;
  mem_prot_access_type.val = READ_REG_U16(MEM_PROT + ADDR_MEM_PROT_ACCESS_TYPE);
  return mem_prot_access_type.bf.bus;
}

void mem_prot_access_clear(void)
{
  WRITE_REG_16(MEM_PROT + ADDR_MEM_PROT_ACCESS_CLEAR, 1);
}

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

#include "vic.h"
#include "vic_irq.h"

volatile static callback_t callback[MEM_PROT_NUM_IRQS];

void mem_prot_handler_init(void)
{
  irq_handler_init(VIC_IRQ_MEM_PROT, MEM_PROT_NUM_IRQS, (callback_t *)callback,
                   BASE_ADDR_MEM_PROT + ADDR_MEM_PROT_IRQ_VENABLE);
}
