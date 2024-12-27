/*BEGIN_FILE_HDR
**************************************************************************
* NOTICE
* This software is the property of XiangBin Electric. Any information contained in this
* doc should not be reproduced, or used, or disclosed without the written authorization from
* XiangBin Electric.
**************************************************************************
* File Name:Main.c
********************************************************************
* Project/Product:LXT9816_PMP
* Title :
* Author:zyg
*********************************************************************
* Description:
* 1.Init hardware and software
* 2.Call simulink model step function
* 3.Schedule time base task
*
* (Requirements, pseudo code and etc.)
*********************************************************************
* Limitations:
*
* (limitations)
*********************************************************************
*********************************************************************
* Revision History：
*
* Version       Date         	  Author         Descriptions
* ----------    --------------    ------------   ----------------------------------------
*  1.0       2021-08-20        zyg            Original
*
*
********************************************************************
*END_FILE_HDR*/

/* Includes*/
/******************************************************************/
#include "Main.h"
#include "SDK.h"
#include "Common.h"
#include "TestMode.h"
#include "PwmIn.h"
#include "ADCSample.h"
#include "MotorAPI.h"
#include "DTC.h"
#include "GlobalVars.h"
#include "lin_cfg.h"
#include "lin_lld_sci.h"
#include "LINDataPro.h"

#include "AppMain.h"                   /* Model's header file */
#include "rtwtypes.h"
#include "Emo_RAM.h"

/* Defines*/
/******************************************************************/
#define STACK_OVER_FLOW_CHECK_EN 0

#define SCH_PRG_TIMER_BASE  	(10) /*主循环任务时基由5ms为10ms 24-8-26 by CL*/
#define SCH_CNT_10MS_OVER     (10/SCH_PRG_TIMER_BASE)
#define SCH_CNT_50MS_OVER     (50/SCH_PRG_TIMER_BASE)
#define SCH_CNT_100MS_OVER    (100/SCH_PRG_TIMER_BASE)


/*休眠延时，2022-6-8-by lxs*/
#define SPLEEP_DELAY (1u)

/* Variables */
/******************************************************************/
volatile u16 MsCnt1;/*  1ms count */ 
static u16 MsCnt10; /* 10ms count */
static u16 MsCnt_50;/* 50ms count */
static u16 MsCnt100;/*100ms count */

static u8 SleepDelay = SPLEEP_DELAY;
s16 DebugSpeed = 0;

#if STACK_OVER_FLOW_CHECK_EN
uint32 StackIdx = 0;
uint32 *StackTop = (uint32 *)0x18000A08;
uint32 StackSize = (0x400>>2);
#endif

/* Function declaration */
/******************************************************************/
static void Main_SoftwareInit(void);
static void Emo_calIShuntZero(void);
static void Main_AppMainInputUpdate(void);


/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:main
* Description:
* 1.Init hardware and software
* 2.Call simulink model step function
* 3.Schedule time base task
*
* Inputs:none
*
*
* Outputs:none
*
*
* Limitations:
********************************************************************
END_FUNCTION_HDR*/
int main(void)
{
#if STACK_OVER_FLOW_CHECK_EN
	for(StackIdx = 0;StackIdx < StackSize; StackIdx++)
	{
		*(StackTop - StackIdx) = 0x5A5A5A5A;
	}
#endif
	
  SDK_HardwareInit();
  Main_SoftwareInit();

  while (1u)
  {
    if(MsCnt1 >= SCH_PRG_TIMER_BASE)
    {
      MsCnt1 = 0u;
			
      if(MsCnt10 == 0u)/* polyspace DEFECT:USELESS_IF */ /* polyspace MISRA-C3:14.3 */
      {
        MsCnt10 = SCH_CNT_10MS_OVER;

				ADCSample_PeriodTask();
				SDK_EcuFaultDiag();

				if(IsInTestMode == 0u)/* 2021-07-28-by zyg  */
				{
					/*更新输入sumlink模型的参数,2021-09-03-by zyg*/
					Main_AppMainInputUpdate();
					AppMain_step();
					
					/*RAM错误、校验和错误将芯片复位标志重启*/
					if ((ECUFaults.bit.Ram != 0u) || (ECUFaults.bit.CFlash != 0u))
					{
						Y.ChipReset = 1u;
						Y.TargetSpeedLimited = 0u;
					}
					
					MotorAPIVar.RestartEn = Y.MotorRestartEnable;
					
					s16 TargetSpeed;
					if(LinRx.IsSleep!=0u)
					{
						/*增加休眠判断,2022-06-08-by lxs*/
						TargetSpeed = 0;
					}
					else
					{
					if(Y.TargetSpeedLimited < -MOTOR_MAX_SPEED)
					{
						TargetSpeed = -MOTOR_MAX_SPEED;
					}
					else if(Y.TargetSpeedLimited > MOTOR_MAX_SPEED)
					{
						TargetSpeed = MOTOR_MAX_SPEED;
					}
					else
					{
						TargetSpeed = Y.TargetSpeedLimited;
					}
					}

					
					//MotorAPI_MotorSetSpeed(DebugSpeed); 
					MotorAPI_MotorSetSpeed(TargetSpeed);
					MotorAPI_MotorPeriodTask();
					

					/*悬空4s后状态更新为全速,通讯错误持续0.121*80ms后全速,2022-03-11-by zyg*/
					if(((IDEA_TimeOut == 1)||(Lin_Error_Flag == 1))&&(LinRx.IsSleep != 1u))
					{
						LinRx.SpdSet = 250;
					}	
					else
					{
						
					}

				}
				else/*  add else - 2021-07-28-by zyg  */
				{
					
				}

      }
			else/*  add else - 2021-07-28-by zyg  */
			{
				
			}

      if(MsCnt_50 == 0u)
      {
        MsCnt_50 = SCH_CNT_50MS_OVER;

				SDK_FeedWDog();
				
        TestMode_FactoryTest();
        TestMode_UartDebugPeriodTask();
		/*添加lin收发任务,2021-08-20-by zyg*/
		LIN_Rx();
		/* 增加LIN通信反馈条件限制，23.08.10 by zjj */
		if(IsInTestMode == 0u)
		{
        	LIN_Tx();
		}
		else
		{
		
		}
      }
			else/*  add else - 2021-07-28-by zyg  */
			{
				
			}

      if(MsCnt100 == 0u)
      {
        MsCnt100 = SCH_CNT_100MS_OVER;
				/*FCT模式下需要存储零点值，故障更新不受FCT模式限制,2023-08-11-by zjj*/
				DTC_PeriodTask();
				/*FCT模式零点数据存储 24-8-26 by CL*/
				if(IsInTestMode != 0)
				{
					DTC_DataSave();
				}
				else
				{
				
				}					
				if(IsInTestMode == 0u)/* 2021-07-28-by zyg  */
				{
					/*Lin休眠,2021-09-03-by zyg*/
					if(LinRx.IsSleep != 0u)
					{
						/*将休眠模式存储故障单列，防止休眠无法存故障，24/8/26 by CL*/
						DTC_DataSave();
						
						/*LIN休眠延时,2022-06-08-by lxs*/
						if(SleepDelay > 0u)
						{
							SleepDelay--;
						}
						else
						{
							SDK_GoToSleepMode();
						}
					}
					if (Y.ChipReset != 0u)
					{
						SDK_SystemReset();
					}				
				}
				else
				{
				
				}


        GlobalVars_PowerUpTimeCount();
      }
			else/*  add else - 2021-07-28-by zyg  */
			{
				
			}
			
      MsCnt10--;
      MsCnt_50--;
      MsCnt100--;
    }
		else/*  add else - 2021-07-28-by zyg  */
		{
				
		}
  }
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:Main_SoftwareInit
* Description:
*		Init software components
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
/*消除polyspace警告,2021-09-18-by zyg*/
static void Main_SoftwareInit(void)
{

	l_bool ret_sys = 0,ret_ifc = 0;

	SDK_Mem_Check();
	DTC_Init();
  MotorAPI_MotorInit();
	Emo_calIShuntZero();
	AppMain_initialize();
	U.PwmInHighDuty = 100u;
	/*添加lin相关初始化,2021-08-20-by zyg*/
	ret_sys = l_sys_init();
	ret_sys = ret_sys;
  ret_ifc = l_ifc_init(LI0);
	ret_ifc = ret_ifc;
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:Emo_calIShuntZero
* Description:
* 1.采集母线电流采样运放零点值
* 2.如果电源电压、环境温度在设置的范围内，则进行母线电流采样运放零点标定
* 3.母线电流采样运放零点无法标定或标定错误时，使用DTC中的存储值
*
* Inputs:
*
*
* Outputs:
* 1.AdcResults.RawAD.IShuntZero：电流零点AD值
* 2.AdcResults.ErrFlags.IShuntZero：电流零点值错误标志，1：错误，0：正常
*
* Limitations:
* 1.该函数应在DTC初始化后调用
********************************************************************
END_FUNCTION_HDR*/
static void Emo_calIShuntZero(void)
{
	/* DFalsh数据有效时使用其中的零点，否则进行电流零点标定 23.07.05 by zjj */
	if (DTCVar.IShuntZero != 0u)
	{
		ADCResults.RawAD.IShuntZero = DTCVar.IShuntZero;
	}
	else
	{
		if((ADCResults.Voltage.Bat > ADC_SAMPLE_I_SHUNT_ZERO_CALIBRATE_BAT_MIN) &&
      	(ADCResults.Voltage.Bat < ADC_SAMPLE_I_SHUNT_ZERO_CALIBRATE_BAT_MAX) &&
     	 (ADCResults.Temperature.Chip > ADC_SAMPLE_I_SHUNT_ZERO_CALIBRATE_AMBT_MIN) &&
     	 (ADCResults.Temperature.Chip < ADC_SAMPLE_I_SHUNT_ZERO_CALIBRATE_AMBT_MAX))
		{
			u8 ret = 0;
			
			ret = Emo_calcIShuntZero();
			if (ret == 0u)
			{	/* 电流标定有效时存储，23.07.05 by zjj */
				DTCVar.IShuntZero = ADCResults.RawAD.IShuntZero;	
				DtcIShuntWriteEn = 1u;
			}
		}
		else
		{
			/* 不满足电流零点标定条件时使用默认值，23.07.05 by zjj */
			ADCResults.RawAD.IShuntZero = ADC_SAMPLE_ISHUNT_ZERO_DEFAULT;

			CSAZeroFault.bit.CSAZeroVoltError = ((ADCResults.Voltage.Bat < ADC_SAMPLE_I_SHUNT_ZERO_CALIBRATE_BAT_MIN) ||
																					(ADCResults.Voltage.Bat > ADC_SAMPLE_I_SHUNT_ZERO_CALIBRATE_BAT_MAX));
			CSAZeroFault.bit.CSAZeroTempError = ((ADCResults.Temperature.Chip < ADC_SAMPLE_I_SHUNT_ZERO_CALIBRATE_AMBT_MIN) ||
																					(ADCResults.Temperature.Chip > ADC_SAMPLE_I_SHUNT_ZERO_CALIBRATE_AMBT_MAX));
		}
	}
	Emo_Svm.CsaOffset = ADCResults.RawAD.IShuntZero;
}

/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:Main_AppMainInputUpdate
* Description:
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
static void Main_AppMainInputUpdate(void)
{
	#if 0
	U.PwmInFreq = PwmIn.Freq;
	U.PwmInHighDuty = (PwmIn.HighDuty/10u + (((PwmIn.HighDuty%10u) > 5u) ? 1u : 0u)) * 10u;
	U.PwmInIdleTime = PwmIn.BusIdleTime;
	U.PwmInPinSts = PwmIn.BusState;
	#else
	U.PwmInFreq = 1000;
	//U.PwmInHighDuty = 100;
	U.PwmInHighDuty = LinRx.SpdSet;
	U.PwmInIdleTime = 0;
	U.PwmInPinSts = 0;
	#endif
	
	U.SleepValid = 0u;
	
	U.AmbTemperature = ADCResults.Temperature.Chip;
	U.SupVoltage = ADCResults.Voltage.Bat;
	U.FilteredVoltage = ADCResults.Voltage.BatFiltered;

  U.ChipFault = ECUFaults.bit.ECUFault;

  U.IsMotorShort = MotorAPIVar.Faults.bit.Short;
  U.IsMotorOpenLoad = 0u;
  U.IsMotorLock = MotorAPIVar.Faults.bit.Lock;
  U.IsMotorDryRunning = MotorAPIVar.IsDryRunning;

  U.RestartComplete = MotorAPIVar.RestartComplete;
  MotorAPIVar.RestartComplete = 0u;
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:Main_FeedBackBusOutput
* Description:
*		Set PwmOut bus state.
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
#if 0
static void Main_FeedBackBusOutput(void)
{
	static u8 FeedBackBusStatusLast = 1u;
	
	if((Y.FeedBackBusStatus != 0u) && (FeedBackBusStatusLast == 0u))
	{
		/* Delay to enable pwm in cature */
		SDK_PwmOutLow();
	}
	else if((Y.FeedBackBusStatus == 0u) && (FeedBackBusStatusLast != 0u))
	{	
		PwmIn.CaptureEnable = 0u;		
		SDK_PwmOutHigh();
	}
	else
	{
		PwmIn.CaptureEnable = Y.FeedBackBusStatus;
	}
	
	FeedBackBusStatusLast = Y.FeedBackBusStatus;
}
#endif
