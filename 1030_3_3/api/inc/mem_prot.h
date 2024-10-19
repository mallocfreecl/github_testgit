#ifndef HAVE_MEM_PROT_H
#define HAVE_MEM_PROT_H

#include "base.h"

#include "mem_prot_bf.h"
#include "mem_prot_irq.h"

#include "vic.h"

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void mem_prot_set_exec_enalbe(uint8_t part, uint16_t val);
void mem_prot_set_stack_enable(uint16_t val);
void mem_prot_set_sram_wr_enable(uint16_t val);

uint16_t mem_prot_get_access_addr(void);
uint16_t mem_prot_get_access_pc(void);
uint16_t mem_prot_get_access_type_type(void);
uint16_t mem_prot_get_access_type_bus(void);

void mem_prot_access_clear(void);

/* ======================================================================= */
/* INTERRUPT HANDLING                                                      */
/* ======================================================================= */

void mem_prot_handler_init(void);

void mem_prot_handler_register(mem_prot_irq_t irq, callback_t callback);

void mem_prot_enable_irq(mem_prot_irq_t irq, bool enable);

mem_prot_irq_status_t mem_prot_get_irq_status(void);

void mem_prot_clear_all_irq_events(void);

#define mem_prot_handler_register(irq, cb) irq_handler_register(VIC_IRQ_MEM_PROT, irq, cb)

#define mem_prot_enable_irq(irq, en)                                                                                   \
  {                                                                                                                    \
    if (en)                                                                                                            \
      irq_enable(VIC_IRQ_MEM_PROT, irq);                                                                               \
    else                                                                                                               \
      irq_disable(VIC_IRQ_MEM_PROT, irq);                                                                              \
  }

#define mem_prot_get_irq_status() ((mem_prot_irq_status_t)(unsigned short)irq_get_status(VIC_IRQ_MEM_PROT))

#define mem_prot_clear_all_irq_events() irq_clear_all_events(VIC_IRQ_MEM_PROT)

#endif /* HAVE_MEM_PROT_H */
