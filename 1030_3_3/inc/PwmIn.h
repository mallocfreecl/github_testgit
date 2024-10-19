#ifndef PWMIN_H
#define PWMIN_H

#include "SDKTypes.h"

typedef struct
{
  u16 Freq;        // 0.1Hz
  u16 LowDuty;     // 0.1%
  u16 BusIdleTime; // 1ms
  bool BusState;   // 0:Bus Low, 1:Bus High
  bool Update;
} PwmInAPI_t;

extern PwmInAPI_t PwmInAPI;

/* Isr handler */
extern void PwmIn_LowPulseHigh2LowHandler(void);
extern void PwmIn_LowPulseCaptureTimerOverFlowHandler(void);
extern void PwmIn_LowPulseLow2HighCaptureHandler(void);
extern void PwmIn_PeriodPulseCaptureTimerOverFlowHandler(void);
extern void PwmIn_PeriodPulseCaptureAndRestartHandler(void);

extern void PwmIn_PeriodTask(void);
extern u16 PwmIn_CaculateTargetSpeed(void);

#endif
