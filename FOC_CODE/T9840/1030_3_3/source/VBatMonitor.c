#include "VBatMonitor.h"
#include "ADCSample.h"
#include "MotorAPI.h"
#include "bemf_control.h"
#include "driver_generic.h"

#define POWER_UP_TIME_CNT_BASE 10 // ms

#define Power_Loss_Entry_Voltage_THR 120
#define Power_Loss_Exit_Voltage_THR 130
#define Power_Loss_Filter_Time_THR 10 // 50ms

static u16 PowerUpTime = 0;
static bool IsBatLossInMotorOff = false;

static void BatLossMonitorMotorOff(void);

bool IsVBatLoss(void)
{
  return IsBatLossInMotorOff;
}

void PowerUpTimeCnt(void)
{
  if (PowerUpTime < 0xFFFFu - POWER_UP_TIME_CNT_BASE)
  {
    PowerUpTime += POWER_UP_TIME_CNT_BASE;
  }
  else
  {
    PowerUpTime = 0xFFFFu;
  }
}

bool PowerUpBlank(u16 BlankTimeMs)
{
  return (PowerUpTime >= BlankTimeMs);
}

void BatMonitor(void)
{
  if (PowerUpTime < 2000)
  {
    return;
  }

  BatLossMonitorMotorOff();
}

static void BatLossMonitorMotorOff(void)
{
  static u16 FilterTime = 0;
  bool ret = false;

  u16 Voltage = ADCResults.Voltage.Bat;

  if (Voltage < Power_Loss_Entry_Voltage_THR)
  {
    if (FilterTime < Power_Loss_Filter_Time_THR)
    {
      FilterTime++;
    }
    else
    {
      ret = true;
    }
  }
  else if (Voltage > Power_Loss_Exit_Voltage_THR)
  {
    FilterTime = 0;
  }
  else
  {

  }

  IsBatLossInMotorOff = ret;
}