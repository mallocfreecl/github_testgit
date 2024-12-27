#ifndef _COMMON_H_
#define _COMMON_H_

#include "Types.h"
#include "Globalvariable.h"
#include "adc1.h"
#include "Adc2.h"

typedef sint8  MInt8;
typedef uint8  MUInt8;
typedef sint16 MInt16;
typedef uint16 MUInt16;
typedef uint32 MUInt32;
typedef sint32 MInt32;

//ADC 2
#define GAIN_CH_VBAT                            391       //0.0391
#define GAIN_CH_VS                              547       //0.0547
#define GAIN_CH_VSD                             391       //0.0391
#define GAIN_CH_VCP                             230       //0.023
#define GAIN_CH_VMON                            391       //0.0391
#define GAIN_CH_VDDP                            1640      //0.1640
#define GAIN_CH_VAREF                           2188      //0.2188
#define GAIN_CH_VBG                             7500      //0.75
#define GAIN_CH_VDDC                            7500      //0.75
#define GAIN_CH_TEMP                            1         //1
//ADC1
#define GAIN_CH_VDH                             167       //0.1670

extern MInt16 look1_is16ls32n10Ds32_linlags(MInt16 u0, const MInt16 bp0[], const
  MInt16 table[], MUInt32 maxIndex);
extern sint16 LookTableStepBelow_s16(sint16 input,const sint16 table_x[],const sint16 table_y[],uint8 table_len);
extern void copymemory(uint8 des[],uint8 src[],uint8 length);


#endif
