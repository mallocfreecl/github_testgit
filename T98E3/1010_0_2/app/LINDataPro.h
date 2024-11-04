#ifndef LIN_DATA_PRO_H
#define LIN_DATA_PRO_H

#include "AppTypes.h"

/*水泵运行最大转速 23.09.24 by lpy*/
#define MOTOR_MAX_SPEED (5100)
typedef struct{
  u16 SpdSet;
  u8 Enable;
  u8 IsSleep;
	
}LinRx_t;
/*消除polyspace警告,2021-09-22-by zyg*/
/*polyspace-begin  MISRA2012:6.1*/
typedef struct{
  u8 TargetSpd;
  u8 ActSpd;
  u8 Voltage;
  u8 Temperature;
  u8 Current;

  union{
    u16 reg;

    struct{
      u16 OverTemp:2;
      u16 OverCurrent:2;
      u16 DryRunning:2;
      u16 Voltage:2;
      u16 Block:2;
	  u16 Errsts:2;
      u16 EmgyModSts:2;
    }bit;
  }Sts;
}LinTx_t;
/*polyspace-end  MISRA2012:6.1*/
extern LinRx_t LinRx;
extern LinTx_t LinTx;

extern void LIN_Rx(void);
extern void LIN_Tx(void);

/*DTC存储判断函数声明 24-8-26 by CL*/
extern void DTC_SaveJudgments(void);
/*DTC存储使能标志位声明 24-8-26 by CL*/
extern u8 DTCSave_ENABLE; 

#endif
