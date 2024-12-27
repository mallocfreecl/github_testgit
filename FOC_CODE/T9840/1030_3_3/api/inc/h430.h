#ifndef __H430_H__
#define __H430_H__

#include "base.h"
#include "types.h"

/* ========================================================================== */
/* CPU serve functions */
/* ========================================================================== */

void cpu_enable_irqs(void);

void cpu_disable_irqs(void);

void set_standby_flag(void);

void set_stop_flag(void);

/* ========================================================================== */
/* CPU function defines */
/* ========================================================================== */

#ifdef DPI

#define cpu_enable_irqs()
#define cpu_disable_irqs()
#define set_standby_flag()
#define set_stop_flag()

#else

#define cpu_enable_irqs()                                                                                              \
  {                                                                                                                    \
    _NOP();                                                                                                            \
    _NOP();                                                                                                            \
    _BIS_SR(0x0008);                                                                                                   \
  }
#define cpu_disable_irqs()                                                                                             \
  {                                                                                                                    \
    _BIC_SR(0x0008);                                                                                                   \
  }

#define set_standby_flag()                                                                                             \
  {                                                                                                                    \
    _BIS_SR(0x0018);                                                                                                   \
    _NOP();                                                                                                            \
  }
#define set_stop_flag()                                                                                                \
  {                                                                                                                    \
    _BIS_SR(0x0038);                                                                                                   \
    _NOP();                                                                                                            \
  }

#endif

#endif /* __H430_H__ */
