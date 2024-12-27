/*BEGIN_FILE_HDR
**************************************************************************
* NOTICE
* This software is the property of XiangBin Electric. Any information contained in this
* doc should not be reproduced, or used, or disclosed without the written authorization from
* XiangBin Electric.
**************************************************************************
* File Name:PwmIn.c
********************************************************************
* Project/Product:LXT9818_PMP
* Title:
* Author:yhd
*********************************************************************
* Description:
*   Detecting PwmIn frequence and duty cycles.This module is cooperated
*   with PwmOut feed back module.
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
* ----------    --------------  ------------   ----------------------------------------
*     1.0       2021-07-23      yhd            Original
*			1.0       2021-07-31      zyg            1.PwmIn_PeriodTask():  Define variables at the beginning of the function
*								
*
********************************************************************
*END_FILE_HDR*/

/* Includes*/
/******************************************************************/
#include "PwmIn.h"
#include "SDK.h"

/* Defines*/
/******************************************************************/
#define PWM_IN_CAPTURE_TIMER_FREQ (1500000u) /* Hz */
#define PWM_IN_PERIOD_TIME_BASE (10u) /* ms */

#define PWM_PULSE_BUF_LEN (3u)
#define PWM_VALID_CHECK_NUM (1u)	/* PWM_VALID_CHECK_NUM must little than PWM_PULSE_BUF_LEN */

#define PWM_FREQ_ERROR (10u) /* Unit:0.1Hz */
/*修改为占空比变化超0.5%使用新的占空比，24.03.05 by WChuang*/
#define PWM_DUTY_ERROR (5u) /* Unit:0.1% */

#define PWM_BUS_IDLE_TIME_MAX (1000u)	/* ms */
#define PWM_MIN_PEROIDCNT_VALUE (((PWM_IN_CAPTURE_TIMER_FREQ) * 10u ) >> 16)

/* Max time delay between capture and overflow */
/* #define TimerIntNestMaxTime (0.0001) */  /* s */
/* #define TimerIntNestMaxCnt (0xFFFF - (PWM_IN_CAPTURE_TIMER_FREQ * (1.0 - 0.0001))) */
#define TimerIntNestMaxCnt (0xFFFFu - 600u)

#define HIGHCNT_TEN 0x19999999uL /* 0xFFFFFFFFu/10u   ,2021-08-04-by zyg */
#define HIGHCNT_HUN 0x28F5C28uL  /* 0xFFFFFFFFu/100u  ,2021-08-04-by zyg */
#define HIGHCNT_THO 0x418937uL   /* 0xFFFFFFFFu/1000u ,2021-08-04-by zyg */
#define MAXBUSIDLETIME (0xFFFFu - (PWM_IN_PERIOD_TIME_BASE)) /* 0xFFFFu - (PWM_IN_PERIOD_TIME_BASE) ,2021-08-04-by zyg*/

typedef struct {
  u16 CaptureCnt;      //捕获的次数
  u32 OverFlowCnt;     //溢出的次数
  u8 NestFlag;         //标志位？？
}Pulse_t;

typedef struct {
    Pulse_t HighPulse;
    Pulse_t LowPluse;
    Pulse_t PeriodPluse;
		Pulse_t PeriodPlusLowPulse;
		/*存储高占空比捕获计数，24.03.02 by WChuang*/
		Pulse_t PeriodPlusHighPulse;

    u32 HighCnt;        //？？
    u32 LowCnt;         //？？
    u32 PeriodCnt;      //？？
}Pwm_t;

typedef struct{
  u32 TimerOverflowCnt;
  u8 TimerIntNestFlag;
	u8 RisingEdgeCnt;                 //从定时器启动捕获的上升沿边沿次数
	/*下降沿捕获计数，24.03.02 by WChuang*/
	u8 FallingEdgeCnt;                //从定时器启动捕获的下降沿边沿次数
	
  Pwm_t PwmBuf[PWM_PULSE_BUF_LEN];  //PWM_PULSE_BUF_LEN:3   作用？？     取均值?减少误差？ 此程序暂时没用到
  u8 PwmBufIdx;                     //索引

  u8 PwmCnt;                        //??
	
	u8 IsCaptureTriggered;            //捕捉到边沿标志位
} PwmInVar_t;

/* Variables */
/******************************************************************/
static PwmInVar_t PwmInVar;
PwmIn_t PwmIn =
{
.CaptureEnable = 1u,
};
static u16 FreqBuf[PWM_VALID_CHECK_NUM];  //PWM_VALID_CHECK_NUM:1   定义记录结果的数组
static u16 DutyBuf[PWM_VALID_CHECK_NUM];

/* Function declaration */
/******************************************************************/
static u32 PwmIn_CalulatePulseWidth(Pulse_t *p);
static u16 PwmIn_CalulatePulseFreq(Pwm_t *p);
/*高占空比计算函数，24.03.02 by WChuang*/
static u16 PwmIn_CalulatePulseHighDuty(Pwm_t *p);

/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:PwmIn_CaptureHandler
* Description:
*   PwmIn capture interrupt handler.
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
void PwmIn_CaptureHandler(void)
{	
	u32 CaptureCnt;
	CaptureCnt = SDK_PwmInGetCaptureCnt();  //SDK_PwmInGetCaptureCnt()为TIMER2捕获寄存器的值

	if(CaptureCnt == 0u)
	{
		/* Timer is Stopping */
	}
  else
  {
    u8 TimerResetFlag = 0u;
    if(PwmIn.CaptureEnable == 0u)
    {
      TimerResetFlag = 1u;        //TimerResetFlag 计数器重新计算标志位
      PwmInVar.PwmBufIdx = 0u;
      PwmInVar.PwmCnt = 0u;
    }
    else
    {
			/*修改为上升沿触发 下降沿捕获，直接计算高占空比，24.03.02 by WChuang*/
			PwmInVar.FallingEdgeCnt++;

      Pulse_t *p = (void *)0u;//NULL
      if(PwmInVar.FallingEdgeCnt == 1u)
      {
        p = &PwmInVar.PwmBuf[PwmInVar.PwmBufIdx].HighPulse;
      }
      else if(PwmInVar.FallingEdgeCnt == 2u)
      {
        TimerResetFlag = 1u;
        
        p = &PwmInVar.PwmBuf[PwmInVar.PwmBufIdx].PeriodPlusHighPulse;

        PwmInVar.PwmBufIdx++;
        if(PwmInVar.PwmBufIdx >= (PWM_PULSE_BUF_LEN))   //PWM_PULSE_BUF_LEN:3      计算3次并缓存起来    0-->1-->2-->0-->1-->...
        {                                               //每次计算要捕获到两个下降沿，进入两次中断
          PwmInVar.PwmBufIdx = 0u;
        }
        else
        {

        }

        if(PwmInVar.PwmCnt < 0xFFu)
        {
          PwmInVar.PwmCnt++;            //PWM的计算次数
        }
        else
        {

        }
      }
      else
      {
        TimerResetFlag = 1u;
        PwmInVar.PwmBufIdx = 0u;       //拓展作用
        PwmInVar.PwmCnt = 0u;          //拓展作用    此程序中FallingEdgeCnt==1   FallingEdgeCnt==2-->TimerResetFlag = 1u-->PwmInVar.FallingEdgeCnt=0   
      }                                //FallingEdgeCnt==3不能实现原因是FallingEdgeCnt==2-->TimerResetFlag=1-->FallingEdgeCnt=0, 故左侧该else也执行不到 

      if(p != (void *)0u)     //将HighPulse和PeriodPlusHighPulse分别赋值给结构体
      {
        p->CaptureCnt = CaptureCnt;
        p->OverFlowCnt = PwmInVar.TimerOverflowCnt;    //在溢出中断中赋值
        p->NestFlag = PwmInVar.TimerIntNestFlag;       //计数器运行中在每次捕捉到边沿(下降沿)后清零   在溢出中断中某条件下置1  计算周期时由该位执行相应操作
      }
      else
      {

      }
      
      PwmInVar.IsCaptureTriggered = 1u;                //捕获到边沿标志位，在PwmIn_PeriodTask函数中清零
    }

    if(TimerResetFlag != 0)
    {
      SDK_PwmInCaptureTimerReset();         //定时器停止   计数器清零
			/*下降沿捕获，24.02.02 by WChuang*/
			SDK_PwmInSetCaptureFallingEdge();     //设置捕获模式下为下降沿捕获
      
      PwmInVar.TimerOverflowCnt = 0u;       //溢出次数清零
	  /*捕获计数清零，24.03.02 by WChuang*/
			PwmInVar.FallingEdgeCnt = 0u;         //捕获到的边沿次数清零
    }
    else
    {

    }

    PwmInVar.TimerIntNestFlag = 0u;
  }
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:PwmIn_CaptureTimerOverFlowHandler
* Description:
*   PwmIn capture timer overflow handler.
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
void PwmIn_CaptureTimerOverFlowHandler(void)
{
    /*修改溢出中断处理逻辑 22.11.16 by lxs*/
	u16 CapCnt;
	if(SDK_PwmInIsCaptureTimerRunning() != 0)
	{
  if(PwmInVar.TimerOverflowCnt < 0xFFFFu)
  {
    PwmInVar.TimerOverflowCnt++;
  }
  else
 	{
  	
 	}
		if (SDK_IsPwmInCap() != 0u)   //函数SDK_IsPwmInCap()为捕获到边沿的标志位，由软件清零    在何处清零？？
		{                                        //在溢出之前已经捕获到了边沿且捕获值在某区间将其置1
			CapCnt = SDK_PwmInGetCaptureCnt();     //TimerIntNestFlag的作用？？    
			PwmInVar.TimerIntNestFlag = ((CapCnt > (TimerIntNestMaxCnt)) || (CapCnt == 0u));//TimerIntNestMaxCnt：(0xFFFFu - 600u)
		}
		else
		{
			PwmInVar.TimerIntNestFlag = 0u;
		}
	}
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:PwmIn_PeriodTask
* Description:
*   Caculate PwmIn frequency and duty.
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
void PwmIn_PeriodTask(void)    //主函数中每10ms调用此函数
{
	u8 i = 0u;
	if(PwmIn.CaptureEnable== 0u)
	{
		
	}
	else/*  add else - 2021-07-21-by zyg  */
  {
    if((PwmIn.BusIdleTime < (PWM_BUS_IDLE_TIME_MAX)) && (PwmInVar.PwmCnt >= (PWM_VALID_CHECK_NUM)))//PWM_BUS_IDLE_TIME_MAX:1000(ms)  
			{                                                                                              //PWM_VALID_CHECK_NUM:1
      u8 tmp; 
      tmp = PwmIn.CaptureEnable;
      PwmIn.CaptureEnable = 0u;

      PwmInVar.PwmCnt = 0u;

      for( i = 0u; i < (PWM_VALID_CHECK_NUM); i++)/* Define variables at the beginning of the function - 2021-07-31-by zyg  */
      {
        u8 Idx;
        if(PwmInVar.PwmBufIdx >= (i + 1u))
        {
          Idx = PwmInVar.PwmBufIdx - i - 1u;
        }
        else
        {
          Idx = PwmInVar.PwmBufIdx + (PWM_PULSE_BUF_LEN) - i - 1u;
        }

        Pwm_t *p;
        p = &PwmInVar.PwmBuf[Idx];
				
				/*获取高占空比计数和周期计数，计算频率和周期，24.03.02 by WChuang*/
				p->HighCnt = PwmIn_CalulatePulseWidth(&(p->HighPulse));
        u32 PeriodPlusHighCnt;
        PeriodPlusHighCnt = PwmIn_CalulatePulseWidth(&(p->PeriodPlusHighPulse));
        p->PeriodCnt = PeriodPlusHighCnt - p->HighCnt;

        FreqBuf[i] = PwmIn_CalulatePulseFreq(p);     //计算周期
        DutyBuf[i] = PwmIn_CalulatePulseHighDuty(p); //计算占空比
      }

      PwmIn.Freq = FreqBuf[0u];
			/*占空比变化超过0.5%使用新占空比 24.03.02 by WChuang*/
      if (((DutyBuf[0u] + PWM_DUTY_ERROR) <= PwmIn.HighDuty) ||
          (DutyBuf[0u] >= (PwmIn.HighDuty + PWM_DUTY_ERROR)))
      {
        PwmIn.HighDuty = DutyBuf[0u];
      }
			
      PwmIn.CaptureEnable = tmp;
    }
    else
    {
      if(PwmIn.BusIdleTime > (PWM_BUS_IDLE_TIME_MAX))
      {
        PwmInVar.PwmCnt = 0u;
        PwmInVar.PwmBufIdx = 0u;
        
        PwmIn.BusState = SDK_PwmInGetBusStatus();

        PwmIn.Freq = 0u;
				/*短电高占空比设置为100%，短地为0%，24.03.02 by WChuang*/
				/*消除polyspace警告,2021-09-22-by zyg*/
        PwmIn.HighDuty = (PwmIn.BusState != 0u) ? 1000u : 0u;
      }
    }

    
    if(PwmInVar.IsCaptureTriggered != 0u)
    {
      PwmInVar.IsCaptureTriggered = 0u;
      PwmIn.BusIdleTime = 0u;
    }
    else
    {
      if(PwmIn.BusIdleTime < (MAXBUSIDLETIME))/*0xFFFFu - (PWM_IN_PERIOD_TIME_BASE) */
      {
        PwmIn.BusIdleTime += (PWM_IN_PERIOD_TIME_BASE);
      }
    }  
  }
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:PwmIn_CalulatePulseWidth
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
static u32 PwmIn_CalulatePulseWidth(Pulse_t *p) //该指针p是计算过程中那个时机的p?
{
  if((p->NestFlag) != 0u)      //p->NestFlag该标志位的作用是什么？
  {
    if(p->OverFlowCnt > 1u)
    {
      p->OverFlowCnt -= 1u;
    }
    else
    {
      p->OverFlowCnt = 0u;
    }
  }
  else
  {

  }

  return (u32)((p->OverFlowCnt<<16u) + p->CaptureCnt);//溢出次数*65536 + p->CaptureCnt 计算总的脉冲数(包含溢出的次数)
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:PwmIn_CalulatePulseWidth
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
static u16 PwmIn_CalulatePulseFreq(Pwm_t *p)
{
	u16 Freq = U16_MAX;                            //U16_MAX 0xffff
	if(p->PeriodCnt > PWM_MIN_PEROIDCNT_VALUE)     //PWM_MIN_PEROIDCNT_VALUE:(((PWM_IN_CAPTURE_TIMER_FREQ) * 10u ) >> 16)  ？？
	{
		Freq = ((PWM_IN_CAPTURE_TIMER_FREQ) * 10u / p->PeriodCnt);  //周期倒数的10倍？
	}
	return Freq;
}
/* BEGIN_FUNCTION_HDR
********************************************************************
* Function Name:
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
static u16 PwmIn_CalulatePulseHighDuty(Pwm_t *p)
{
	/*计算高占空比 24.03.02 by WChuang*/
  u32 High = 0;
  u32 Period = 0;
  u32 Coef = 0;
	u32 duty = U16_MAX;   //0xffffu

  if(p->HighCnt > (HIGHCNT_TEN))       //HIGHCNT_TEN:0xFFFFFFFFu/10u     coef的效果是p->HighCnt越大，High计算时的分母就越大。
  {																		 //coef的作用：不同区间的p->HighCnt对应适合的分母，使得计算类似，误差类似
    Coef = 1000u;
  }
  else if(p->HighCnt > (HIGHCNT_HUN))  //HIGHCNT_HUN:0xFFFFFFFFu/100u
  {
    Coef = 100u;
  }
  else if(p->HighCnt > (HIGHCNT_THO))  //HIGHCNT_THO:0xFFFFFFFFu/1000u
  {
    Coef = 10u;
  }
  else
  {
    Coef = 1u;
  }

  High = p->HighCnt / Coef * 1000u;
  Period = p->PeriodCnt / Coef;           //High比Period大1000倍，小数化整数思想，duty = 0.123 --> duty = 123
	/*防止出现Period=0的情况 22.09.01 by lxs*/
  if(Period !=0)
	{
      duty = (u16)(High / Period);
	} 
	return duty;
}
