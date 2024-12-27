#ifndef HAVE_VIC_H
#define HAVE_VIC_H

#include "base.h"
#include "types.h"

#include "vic_bf.h"
#include "vic_irq.h"

typedef void (*callback_t)(int sno);

void vic_handler_init(void);

void cli(void);
void sei(void);

void irq_handler_init(vic_irq_t pno, int svnum, callback_t *svbase, uintptr_t srbase);

void irq_handler_register(vic_irq_t pno, int sno, callback_t callback);
void irq_enable(vic_irq_t pno, int sno);
void irq_disable(vic_irq_t pno, int sno);

uint32_t irq_get_status(vic_irq_t pno);

void irq_clear_all_events(vic_irq_t pno);
void irq_clear_event_no(vic_irq_t pno, int sno); // added

#endif /* HAVE_VIC_H */
