#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "key.h" 
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"
#include "stepping_motor.h"

uint8_t lastmove;   //控制电机正反转及显示电机当时的状态  0:顺时针  1逆时针  2：电机停止
uint32_t pulse = 0; //(360/5.625)*64;   
int16_t Angle;			//定义要旋转角度的变量
uint8_t speed = 2;  //取值1~2   >2会失步
uint8_t KeyNum;
uint8_t temp;

int main(void)
{
	
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			
	/*模块初始化*/
	Key_Init();        //本按键使用轮询的方法  //也可以使用中断的方法
	OLED_Init();		   //OLED初始化
	Timer_Init();		   //定时器初始化
	Encoder_Init();		 //编码器初始化
	StepMotor_init();  //步进电机部分初始化

	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Angle:");		//1行1列显示字符串Angle:
	OLED_ShowString(2, 1, "Speed:");		//2行1列显示字符串Speed:
	OLED_ShowString(3, 1, "temp:");		//3行1列显示字符串temp:
	
	while (1)  
	{
		KeyNum = Key_GetNum();
		if(KeyNum == 1)  
		{
			speed++;
		}
		if(KeyNum == 2)           //只有这个扫描函数发挥作用       按键扫描函数/硬件的问题
		{
			temp++;
			if(Angle >= 0)  lastmove = 0;
			else            lastmove = 1;
			pulse = (GFP_abs(Angle)/5.625)*64; 
			
			TIM4_TimeBaseInitStructure.TIM_Period = motor_speed(speed)-1;		//通过减少计数值来减短每个脉冲的持续时间
			TIM_TimeBaseInit(TIM4, &TIM4_TimeBaseInitStructure);
			TIM_ClearFlag(TIM4, TIM_FLAG_Update);						//清除定时器更新标志位
			TIM_Cmd(TIM4, ENABLE);			                    //使能TIM3，定时器开始运行  在使能前面确定pulse和lastmove
			
		}
		
		OLED_ShowSignedNum(1, 7, Angle, 5);	//显示步进电机要转的角度和方向
		OLED_ShowSignedNum(2, 7, speed, 5);	//显示步进电机设定的速度		
		OLED_ShowSignedNum(3, 7, temp, 5);	
	}
}

/**
  * 函    数：TIM2中断函数
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
  *           函数名为预留的指定名称，可以从启动文件复制
  *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
  */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)		//判断是否是TIM2的更新事件触发的中断
	{
		Angle = Encoder_Get();								//每隔固定时间段读取一次编码器计数增量值，即为速度值
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);			//清除TIM2更新事件的中断标志位
															//中断标志位必须清除
															//否则中断将连续不断地触发，导致主程序卡死
	}
}
