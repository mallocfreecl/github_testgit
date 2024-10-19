#ifndef VBAT_MONITOR_H
#define VBAT_MONITOR_H

#include "SDKTypes.h"

extern bool IsVBatBlankStage(void);
extern bool IsVBatLoss(void);
extern void PowerUpTimeCnt(void);
/* 修改形参名字，消除polyspace警告  2023.10.17 by lxs */
extern bool PowerUpBlank(u16 BlankTimeMs);
extern void BatMonitor(void);

#endif // !VBAT_MONITOR_H