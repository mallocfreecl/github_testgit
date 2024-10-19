#include "ADCSample.h"
#include "MotorAPI.h"
#include "commons.h"
#include "debug.h"
#include "saradc_tables.h"
#include "testmode.h" /* 21.07.30 by yhd */
#include <string.h>

#define USE_AMB_T 0

#define VBAT_OFFSET 8          // VBAT_OFFSET*0.1V
#define PHASE_VOLTAGE_OFFSET 3 // V_PHASE_OFFSET*0.1V

/* 添加括号 消除polyspace警告 2023.10.29 by lxs */
/* polyspace +1 MISRA-C3:10.8 */
#define CurrentADToAmp(AD) ((u16)(((u32)(AD)*962u) >> 12))
/* 增加电流采样转换 23.07.04 by lxs */
#define ShuntCurrentCovert(AD) ((s32)(AD) / 4)

/* 低通滤波相关宏定义 23.07.04 by lxs */
#define ADC_SAMPLE_CURRENT_LP_COEF (1000)
#define S16_MAX (0x7FFF)
/* 电流采样滤波范围 23.12.15 by lxs */
#define ADC_SAMPLE_CURRENT_LOW_PASS_RANGE (20)
#if USE_AMB_T == 1
#define NTC_TABLE_LEN 40u
const s16 NTCTableX[NTC_TABLE_LEN] = {20,  23,  26,  29,  32,  35,  39,  44,  49,  55,  62,  71,  80,  90,
                                      103, 116, 132, 151, 171, 195, 222, 253, 287, 324, 365, 410, 457, 506,
                                      558, 609, 660, 710, 757, 800, 839, 874, 904, 930, 951, 967};
const s16 NTCTableY[NTC_TABLE_LEN] = {150, 145, 140, 135, 130, 125, 120, 115, 110, 105, 100, 95, 90, 85,
                                      80,  75,  70,  65,  60,  55,  50,  45,  40,  35,  30,  25, 20, 15,
                                      10,  5,   0,   -5,  -10, -15, -20, -25, -30, -35, -40, -45};
#endif
/*  将所有结构体变量初始化 2023.10.29 by lxs */
ADCResults_t ADCResults = {0};
/* 电流低通滤波结构体声明 23.08.28 by lxs */
static TMat_Lp CurrentLp;
static s16 ADC_GetAmbientTemperature(void);
static s16 ADC_GetChipTemperature(void);
static u16 ADC_GetChipVBat(void);
static void BatVoltageFilter(void);
static u16 ADC_GetChipVBatAD(void);
static u16 ADC_GetPhaseVoltageU(void);
static u16 ADC_GetPhaseVoltageV(void);
static u16 ADC_GetPhaseVoltageW(void);

void ADC_VarInit(void)
{
  GPIO_ADC_AmbientTemperature = 0;
  GPIO_ADC_VBAT = (u16)(2600 * VF_CON_F);
  GPIO_WINDMILL_U = INVALID;
  GPIO_WINDMILL_V = INVALID;
  GPIO_WINDMILL_W = INVALID;
  ADC_AmbTemperature = DRIVER_CURRENT_REFERENCE;
  memset((void *)&bemf_voltage[0][0], 0, sizeof(u16) * 2 * BEMF_DATA_COUNT);
  /* 无符号类型后缀加u 2023.10.29 by lxs */
  ADCResults.Voltage.BatFiltered = 0xFFFFu;
  /* 电流低通滤波相关参数定义 23.08.28 by lxs */
  CurrentLp.CoefA = ADC_SAMPLE_CURRENT_LP_COEF;
  CurrentLp.CoefB = CurrentLp.CoefA;
  CurrentLp.Min = 0;
  CurrentLp.Max = S16_MAX;

  /* polyspace +1 MISRA-C3:10.1 */
  CurrentLp.Out = ((s32)ADCResults.Current.DC << 15);
}

void ADC_PeriodTask(void)
{
  ADCResults.Temperature.Chip = ADC_GetChipTemperature();
  ADCResults.Temperature.Ambient = ADC_GetAmbientTemperature();

  ADCResults.RawAD.Bat = ADC_GetChipVBatAD();
  ADCResults.Voltage.Bat = ADC_GetChipVBat();
  BatVoltageFilter();

  ADCResults.Voltage.PhaseU = ADC_GetPhaseVoltageU();
  ADCResults.Voltage.PhaseV = ADC_GetPhaseVoltageV();
  ADCResults.Voltage.PhaseW = ADC_GetPhaseVoltageW();

  ADCResults.Current.U0 = CurrentADToAmp((s16)ADCResults.RawAD.Current.Sector0 - (s16)ADCResults.RawAD.Current.Zero);
  ADCResults.Current.V0 = CurrentADToAmp((s16)ADCResults.RawAD.Current.Sector4 - (s16)ADCResults.RawAD.Current.Zero);
  ADCResults.Current.W0 = CurrentADToAmp((s16)ADCResults.RawAD.Current.Sector2 - (s16)ADCResults.RawAD.Current.Zero);

  ADCResults.Current.U1 = CurrentADToAmp((s16)ADCResults.RawAD.Current.Sector3 - (s16)ADCResults.RawAD.Current.Zero);
  ADCResults.Current.V1 = CurrentADToAmp((s16)ADCResults.RawAD.Current.Sector1 - (s16)ADCResults.RawAD.Current.Zero);
  ADCResults.Current.W1 = CurrentADToAmp((s16)ADCResults.RawAD.Current.Sector5 - (s16)ADCResults.RawAD.Current.Zero);

  ADCResults.Current.U = ADCResults.Current.U0;
  ADCResults.Current.V = ADCResults.Current.V0;
  ADCResults.Current.W = ADCResults.Current.W0;

  /*  fct test, 21.07.30 by yhd */
  if (testmode_BrigeOutEn != 0u)
  {
    s16 tmp = ((s16)ADCResults.RawAD.Current.Sector0 - (s16)ADCResults.RawAD.Current.Zero);
    ADCResults.Current.DC = (ADCResults.Current.DC * 9 + tmp) / 10;
  }
  else
  {
#if 1
    /* 计算母线电流 适用T4918项目 23.07.03 by lxs */
    u16 Zero = 0;
    Zero = ADCResults.RawAD.Current.Zero << 1u;
    /* 使用扇区2和扇区4求平均来计算实际电流AD值，并转化为实际值 23.08.30 by lxs */
    ADCResults.RawAD.Current.DC = (((s32)ADCResults.RawAD.Current.Sector2 + (s32)ADCResults.RawAD.Current.Sector4 -
                                    ((s32)Zero)) / 2);
    s16 ShuntCurrent = ShuntCurrentCovert(ADCResults.RawAD.Current.DC);
    if (ShuntCurrent < 0)
    {
      ShuntCurrent = 0;
    }
    ADCResults.Current.DC = ShuntCurrent;
    /* 采集的实际电流和滤波电流相差超过2A使用实际电流，2A之内使用滤波电流 23.08.30 by lxs */
    if ((ADCResults.Current.DC + ADC_SAMPLE_CURRENT_LOW_PASS_RANGE < ADCResults.Current.DCFlt) ||
        (ADCResults.Current.DCFlt + ADC_SAMPLE_CURRENT_LOW_PASS_RANGE < ADCResults.Current.DC) || (ADCResults.Current.DC == 0))
    {
      ADCResults.Current.DCFlt = ADCResults.Current.DC;
      /* polyspace +1 MISRA-C3:10.1 */
      CurrentLp.Out = ((s32)ADCResults.Current.DCFlt << 15);
    }
    else
    {
      ADCResults.Current.DCFlt = Mat_ExeLp(&CurrentLp, ADCResults.Current.DC);
    }

#endif
  }
}

static s16 ADC_GetAmbientTemperature(void)
{
  s16 AmbT;
#if USE_AMB_T == 1
  /*
  NTC High voltage is VDD = 3.3V.
  NTC table is port from other application whitch using 10 bits ADC.
  This ADC Vref = 2.5V.
  NTC_X = ADVal*(1024/4096)*(2.5V/3.3V)
  */
  u16 NTC_X;

  NTC_X = (((u32)((GPIO_ADC_AmbientTemperature) >> 4) * 194u) >> 10);
  AmbT = look1_is16ls32n10Ds32_linlags(NTC_X, ((const s16 *)&(NTCTableX[0])), ((const s16 *)&(NTCTableY[0])),
                                       NTC_TABLE_LEN - 1);

#else
  AmbT = ADCResults.Temperature.Chip;
#endif
  return AmbT;
}

static s16 ADC_GetChipTemperature(void)
{
  /*
  VT = 1.50~1.60V(Typ. 1.55V) @ T = 25 deg
  VT temperature coefficient TC_VT = -3.3 mV/K
  */
  s16 T_Degree;

  /*
    VT = AD/4096*2.5V*10000
    GPIO_ADC_TEMPERATURE is the sum of 16 samples
  */
  ADCResults.Voltage.VT = ((u32)(GPIO_ADC_TEMPERATURE)*25000) >> 16;

  if (ADCResults.Voltage.VT >= 15500)
  {
    T_Degree = 25 - ((s32)ADCResults.Voltage.VT - (s32)15500) / 33;
  }
  else
  {
    T_Degree = 25 + ((s32)15500 - (s32)ADCResults.Voltage.VT) / 33;
  }

  return T_Degree;
}

static u16 ADC_GetChipVBatAD(void)
{
  volatile u16 supply;
  /* polyspace +1 MISRA-C3:11.6 */
  void *CurrentList = (void *)READ_REG_U16(AADDR_SARADC_CTRL_SADR_CURRENT);

  if ((CurrentList == list_windmill) || (CurrentList == ListOpenLaodDiag))
  {
    supply = GPIO_ADC_VBAT_IDLE;
    GPIO_ADC_VBAT = supply;
  }
  else
  {
    supply = GPIO_ADC_VBAT;
  }

  return supply;
}

static u16 ADC_GetChipVBat(void)
{
  /*
  Voltage divider ratio for VS and high voltage divider ratio for M[1..3]
  is 28.8. Voltage(V) = AD/4096*2.5V*28.8; 1AD = 0.0176V
  */
  u16 Voltage;

  Voltage = (((u32)ADCResults.RawAD.Bat * 720u) >> 12);
  /* polyspace +1 MISRA-C3:11.6 */
  void *CurrentList = (void *)READ_REG_U16(AADDR_SARADC_CTRL_SADR_CURRENT);

  if ((CurrentList == list_windmill) || (CurrentList == ListOpenLaodDiag))
  {
    Voltage += VBAT_OFFSET;
  }

  return Voltage;
}

static void BatVoltageFilter(void)
{
  static s16 FilterDiff = 0;
  /*  与结构体变量名冲突，修改变量名  2023.10.29 by lxs */
  static u16 FilterTime = 0;
  static bool IsBatFilteredLow = true;
  /* 无符号类型后缀加u 2023.10.29 by lxs */
  if (ADCResults.Voltage.BatFiltered == 0xFFFFu)
  {
    ADCResults.Voltage.BatFiltered = ADCResults.Voltage.Bat;
  }
  else
  {
    // ADCResults.Voltage.BatFiltered = (ADCResults.Voltage.Bat*2 +
    // ADCResults.Voltage.BatFiltered * 14)>>4;
    ADCResults.Voltage.BatFiltered = (ADCResults.Voltage.Bat * 1 + ADCResults.Voltage.BatFiltered * 23) / 24;
  }

  FilterDiff = (s16)ADCResults.Voltage.Bat - (s16)ADCResults.Voltage.BatFiltered;
  if (FilterDiff <= 0)
  {
    if (!IsBatFilteredLow)
    {
      FilterTime = 0;
    }
    IsBatFilteredLow = true;
  }
  else
  {
    if (IsBatFilteredLow)
    {
      FilterTime = 0;
    }
    IsBatFilteredLow = false;
  }

  if (ABS(FilterDiff) < 5)
  {
    FilterTime = 0;
  }
  else if (ABS(FilterDiff) > 30)
  {
    FilterTime = 0;
    ADCResults.Voltage.BatFiltered = ADCResults.Voltage.Bat;
  }
  else
  {
  }

  if (FilterTime < 400)
  {
    FilterTime++;
  }
  else
  {
    FilterTime = 0;
    ADCResults.Voltage.BatFiltered += FilterDiff;
  }
}

static u16 ADC_GetPhaseVoltageU(void)
{
  u16 Voltage;

  Voltage = ((((u32)GPIO_WINDMILL_U2 >> 4) * 720u) >> 12) + PHASE_VOLTAGE_OFFSET;

  return Voltage;
}

static u16 ADC_GetPhaseVoltageV(void)
{
  u16 Voltage;

  Voltage = ((((u32)GPIO_WINDMILL_V2 >> 4) * 720u) >> 12) + PHASE_VOLTAGE_OFFSET;

  return Voltage;
}

static u16 ADC_GetPhaseVoltageW(void)
{
  u16 Voltage;

  Voltage = ((((u32)GPIO_WINDMILL_W2 >> 4) * 720u) >> 12) + PHASE_VOLTAGE_OFFSET;

  return Voltage;
}
