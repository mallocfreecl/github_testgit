#ifndef __IRQ__
#define __IRQ__

#include "commons.h"
#include <intrinsics.h>

/**
 * @defgroup MISC Miscellaneous
 * @ingroup OTHER
 *
 * @{
 */

// Save & Disable interrupts
#define CLI() __istate_t irqstate = SaveAndDisableIRQ()
// Restore & Enable interrupts
#define SEI() RestoreIRQ(irqstate)

/**@brief Restores IRQs.
 * @param state			state of interrupts*/
static inline void RestoreIRQ(__istate_t state)
{
  __set_interrupt_state(state);
}

/**@brief Saves and disables IRQs.
 * @retval state			state of interrupts*/
static inline __istate_t SaveAndDisableIRQ(void)
{
  __istate_t ret = __get_interrupt_state();
  __disable_interrupt();
  return ret;
}

/** @} */
#endif /* __IRQ__ */
