#ifndef __MEM_PROT_IRQ_H__
#define __MEM_PROT_IRQ_H__

#define MEM_PROT_NUM_IRQS 2

typedef enum
{
  MEM_PROT_IRQ_EVT_UNDEFINED = 0,
  MEM_PROT_IRQ_EVT_DMISALIGNED = 1
} mem_prot_irq_t;

#endif
