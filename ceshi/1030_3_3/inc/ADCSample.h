#ifndef ADC_SAMPLE_H
#define ADC_SAMPLE_H

#include "SDKTypes.h"

typedef struct
{
  struct
  {
    u16 Bat;
    u16 BatFiltered;
    u16 BatFast;
    u16 PhaseU;
    u16 PhaseV;
    u16 PhaseW;
    u16 VT;
  } Voltage; // 0.1V

  struct
  {
    s16 U;
    s16 V;
    s16 W;

    s16 U0;
    s16 V0;
    s16 W0;
    s16 U1;
    s16 V1;
    s16 W1;

    s16 DC;
	/* 滤波后的电流AD值 23.07.04 by lxs */
    s16 DCFlt;
  } Current;

  struct
  {
    s16 Ambient;
    s16 Chip;
  } Temperature; // degree centigrade

  struct
  {
    u16 Bat;

    struct
    {
      u16 Sector0;
      u16 Sector1;
      u16 Sector2;
      u16 Sector3;
      u16 Sector4;
      u16 Sector5;
      u16 Zero;
	  /* 电流AD值 23.07.04 by lxs*/
      s16 DC;
    } Current;
  } RawAD;
} ADCResults_t;

extern ADCResults_t ADCResults;

extern void ADC_VarInit(void);
extern void ADC_PeriodTask(void);
#endif
