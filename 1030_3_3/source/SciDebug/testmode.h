#ifndef TESTMODE_H
#define TESTMODE_H

#include "SDKTypes.h"

typedef struct
{
  struct
  {
    bool UseSCISpeed;
    s16 HighDuty;

    s16 OverModulateK;
  } Motor;

} SCIDebug_t;

extern SCIDebug_t SCIDebug;

extern u8 testmode_JumpInFlag;
extern u8 fcttest_JumpInFlag;
extern u8 terminaltest_JumpInFlag;

extern u8 testmode_BrigeOutEn;
extern u8 testmode_PWMOut50HzEn;
extern u8 testmode_PWMOut100HzEn;
extern u8 testmode_GoToSleep;
extern s16 TestModeCmdSpeed;
extern bool TestMOSRunning;

extern void SelfSignalHandle(void);
extern void TestMode(void);
extern void Test_MOS(void);
extern void PwmOut50Hz_50Duty(void);
extern void PwmOut100Hz_50Duty(void);
extern void TestModePwmOutSelect(void);

#endif
