#include "LINDataPro.h"

#include "lin_cfg.h"
#include "lin_sw.h"
#include "lin_lld_sci.h"

#include "common.h"
#include "MotorAPI.h"
#include "ADCSample.h"
#include "AppMain.h"
#include "rtwtypes.h"
#include "DTC.h"

#define LIN_BUS_ACTIVITY_MASK (1<<4)
#define LIN_GO_TO_SLEEP_MASK  (1<<3)

#define Tx_Time_Base 50 //ms
#define Motor_Short_Feedback_Delay_Time (0*1000/Tx_Time_Base)  //s
#define Motor_Lock_Feedback_Delay_Time  (0*1000/Tx_Time_Base)  //s
#define Motor_Open_Feedback_Delay_Time  (0*1000/Tx_Time_Base)  //s

/*定义DTC存储使能标志位 24-8-26 by CL*/
u8 DTCSave_ENABLE = 0;

enum {
  eNormal = 0,
	/*过温降速*/
  ePreOverTemp = 1,
	/*过温停止*/
  eOverTemporLowTemp = 1,
  eMotorShort = 1,
  eMotorOverCurrent = 1,
  eMotorDryRunning = 1,
  eVoltageHighorLow = 1,
  eMotorBlock = 1,
};



LinRx_t LinRx;
LinTx_t LinTx;

void LIN_Rx(void)
{
  LinRx.IsSleep = (bool)(lin_lld_sci_get_state() == SLEEP_MODE);
	/*矩阵速度部分为13bit，最大值1FFF，但只使用0-255，要求255-1FFF视为全速处理，
	将原滤波阈值修改为8191。2023.10.10 by lpy*/
  LinRx.SpdSet = l_u16_rd_LI0_D_EWP_Setspeed();
}

void LIN_Tx(void)
{
  uint8 MotorShort = 0;
  uint8 MotorLock = 0;
	/*消除polyspace警告,2021-09-22-by zyg*/
  if((MotorAPIVar.Faults.bit.Short == 1) && (Y.ShortCnt >= 15))
  {
      MotorShort = 1;
  }
  else
  {
    MotorShort = 0;
  }

	/*消除polyspace警告,2021-09-22-by zyg*/
  if((MotorAPIVar.Faults.bit.Lock == 1)  && (Y.LockCnt >= 15))
  {
    MotorLock = 1;
  }
  else
  {
    MotorLock = 0;
  }

  LinTx.Sts.bit.OverCurrent = eNormal;
  LinTx.Sts.bit.Block = eNormal;


  if(MotorShort == 1u)
  {
    LinTx.Sts.bit.OverCurrent = eMotorShort;
  }
	else
	{
		
	}
	
  if(MotorLock == 1u)
  {
    if( (MotorAPIVar.DetailFaults.bit.MotorOnOverCurrent) == 1u)
    {
      LinTx.Sts.bit.OverCurrent = eMotorOverCurrent;
    }
    else
    {
      LinTx.Sts.bit.Block = eMotorBlock;
    }
  }
	else
	{
		
	}
  
    if(MotorAPIVar.DryRunningCurrentLowTime >= (2*60*1000))  //2Min
    {
      LinTx.Sts.bit.DryRunning = eMotorDryRunning;
    }
    else
    {
      LinTx.Sts.bit.DryRunning = eNormal;
    }
  
  /*电压状态 PMP2_PumpPowerSta*/
  if(Y.VoltageStatus !=0)
  {
    LinTx.Sts.bit.Voltage = eVoltageHighorLow;
  }
  else
  {
    LinTx.Sts.bit.Voltage = eNormal;
  }
	/*温度状态 PMP2_PumpTempSta*/
  if(Y.AmbTStatus != 0)
  {
    LinTx.Sts.bit.OverTemp = eOverTemporLowTemp;
  }
	else
  {
    LinTx.Sts.bit.OverTemp = eNormal;
  }
	/*区分1级过温和2级过温判断2023.09.23 by lpy */
   if ((B.Status == 1)&&(Y.AmbTStatus==0))
  {
    LinTx.Sts.bit.EmgyModSts = ePreOverTemp;
  }
  else
  {
    LinTx.Sts.bit.EmgyModSts = eNormal;
  }
	
	/*目标转速镜像2023.09.26 by lpy*/
	/*polyspace-begin  MISRA2012:10.8*/
  	LinTx.TargetSpd = (u8)(((s32)MotorAPIVar.RefSpeed)*1000/MOTOR_MAX_SPEED/4);
	/*polyspace-end  MISRA2012:10.8*/
	/*实际转速 PMP2_RealRPM*/
	if(MotorAPIVar.ActSpeed < 0)
	{
		LinTx.ActSpd = 0;
	}
	else if(MotorAPIVar.ActSpeed > MOTOR_MAX_SPEED) 
	{
		LinTx.ActSpd = 0xFA;
	}
	else
	{
		/*polyspace-begin  MISRA2012:10.8*/
		LinTx.ActSpd = (u8)(((s32)MotorAPIVar.ActSpeed)*1000/MOTOR_MAX_SPEED/4);
		/*polyspace-end  MISRA2012:10.8*/
	}
	
	/*电压值 PMP2_PumpInputVolt*/
  if(ADCResults.Voltage.Bat > 0xFFu)
  {
    LinTx.Voltage = 0xFFu;
  }
  else
  {
    LinTx.Voltage = ADCResults.Voltage.Bat;
  }
	
  if(ADCResults.Temperature.Chip < -50)
  {
    LinTx.Temperature = 0;
  }
	else if(ADCResults.Temperature.Chip > 205)
	{
		LinTx.Temperature = 0xFF;
	}
  else
  {
    LinTx.Temperature = ADCResults.Temperature.Chip + 50;
  }
	/* 电流值反馈23.09.25 by lpy */
  if(MotorAPIVar.IShunt < 0)
  {
    LinTx.Current = 0;
  }
  else if(MotorAPIVar.IShunt > 255)
  {
    LinTx.Current = 0xFF;
  }
  else
  {
    LinTx.Current = (MotorAPIVar.IShunt)/2;
  }
	/*错误位反馈23.09.25 by lpy*/
	if((MotorShort != 0u)||(Y.VoltageStatus != 0u)||(LinTx.Sts.bit.DryRunning != eNormal)\
	  ||(LinTx.Sts.bit.OverTemp != eNormal)||(LinTx.Sts.bit.OverCurrent != eNormal)\
	  ||(LinTx.Sts.bit.Block != eNormal)|| (LinTx.Sts.bit.EmgyModSts != 0u))
	{
		LinTx.Sts.bit.Errsts = 1;
	}
	else
	{
		LinTx.Sts.bit.Errsts = 0;
	}
	/*修改LDF矩阵20230926 by lpy*/
  l_u8_wr_LI0_Setspeed(LinTx.TargetSpd);//转速镜像
  l_u8_wr_LI0_Actual_speed(LinTx.ActSpd);//实际转速。
  l_u8_wr_LI0_Voltage(LinTx.Voltage);//电压精度0.1v
  l_u8_wr_LI0_Temperature(LinTx.Temperature);//温度精度1°
  l_u8_wr_LI0_Current(LinTx.Current);//电流精度0.2A
	l_u8_wr_LI0_Wakeup_status(3);//唤醒状态常返3
	l_u8_wr_LI0_Status_Emergency_mode(LinTx.Sts.bit.EmgyModSts);//过温限速
  l_u8_wr_LI0_Over_temperature(LinTx.Sts.bit.OverTemp);//过温故障
  l_u8_wr_LI0_Overcurren(LinTx.Sts.bit.OverCurrent);//过流
  l_u8_wr_LI0_Dry_run(LinTx.Sts.bit.DryRunning);//干运行
  l_u8_wr_LI0_Voltage_Error(LinTx.Sts.bit.Voltage);//电压故障
  l_u8_wr_LI0_Deblocking(LinTx.Sts.bit.Block);//堵转故障
	l_u8_wr_LI0_Electrical_error(0);//电气错误常返0
	l_u8_wr_LI0_Communication_error(LinTx.Sts.bit.Errsts);//通讯错误
}

/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name: DTC_SaveJudgments
* Description:
* 
* 
*
*
* Inputs:
*
*
* Outputs:
*
*
* Limitations:
********************************************************************
END_FUNCTION_HDR*/
/*定义DTC存储判断函数 24-8-26 by CL*/
void DTC_SaveJudgments(void)
{
	/*lin最后一位数据发送完成后进行存储 24-8-26 by CL*/
	if((l_flg_tst_LI0_Communication_error_flag() !=0))
	{
		DTCSave_ENABLE = 1;
		l_flg_clr_LI0_Communication_error_flag();
		DTC_DataSave();
		DTCSave_ENABLE = 0;		
	}
	else
	{}
}

