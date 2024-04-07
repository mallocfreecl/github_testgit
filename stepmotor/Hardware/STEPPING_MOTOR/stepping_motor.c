#include "stepping_motor.h"
#include "delay.h"


extern uint8_t lastmove;         //0：正转  1:反转   2：表示电机停止
extern uint32_t pulse;           //int(double)(angle/5.625)*64;

//GPIO使用PB.12、PB.13、PB.14、PB.15
//使用定时器3的更新中断   定时2ms:执行每步的时间

/*结构体初始化*/

GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM4_TimeBaseInitStructure;
void StepMotor_init(void)      //确定每个脉冲持续的时间(确定转速)
{
  /*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);			//开启GPIOB的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);			//开启TIM4的时钟
	
	/*GPIO初始化*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MOTOR_A | MOTOR_B | MOTOR_C | MOTOR_D;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						
	
	/*配置时钟源*/
	TIM_InternalClockConfig(TIM4);		//选择TIM4为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	/*时基单元初始化*/
	TIM4_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		  //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM4_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//计数器模式，选择向上计数
	TIM4_TimeBaseInitStructure.TIM_Period = 7200-1;									//计数周期，即ARR的值
	TIM4_TimeBaseInitStructure.TIM_Prescaler = 20-1;									//预分频器，即PSC的值  //定时时间：7200 * ((19+1)/72000000) = 2ms
	TIM4_TimeBaseInitStructure.TIM_RepetitionCounter = 0;						//重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM4, &TIM4_TimeBaseInitStructure);							//将结构体变量交给TIM_TimeBaseInit，配置TIM2的时基单元	
	
	/*中断输出配置*/
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);						//清除定时器更新标志位
																//TIM_TimeBaseInit函数末尾，手动产生了更新事件
																//若不清除此标志位，则开启中断后，会立刻进入一次中断
																//如果不介意此问题，则不清除此标志位也可
	
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);					//开启TIM2的更新中断
	
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure;											//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;						//选择配置NVIC的TIM4线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//指定NVIC线路的抢占优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//指定NVIC线路的响应优先级为0
	NVIC_Init(&NVIC_InitStructure);														//将结构体变量交给NVIC_Init，配置NVIC外设
	
	/*TIM使能*/
	//TIM_Cmd(TIM4, ENABLE);			//使能TIM3，定时器开始运行  //定时器一旦开启步进电机就开始旋转
   
}


//步进电机驱动函数：     dir:1表示电机正转；0表示反转
void StepMotor_Move(uint8_t dir)
{
    static uint8_t step = 0;
    if(dir == 0)
    {
        if(step == 0)
            step = 8;
        step--;
    }
    if(0 == step)
    {
        MOTOR_A_H;
        MOTOR_B_L;
        MOTOR_C_L;
        MOTOR_D_L;
    }
    else if(1 == step)
    {
        MOTOR_A_H;
        MOTOR_B_H;
        MOTOR_C_L;
        MOTOR_D_L;
    }
    else if(2 == step)
    {
        MOTOR_A_L;
        MOTOR_B_H;
        MOTOR_C_L;
        MOTOR_D_L;
    }
    else if(3 == step)
    {
        MOTOR_A_L;
        MOTOR_B_H;
        MOTOR_C_H;
        MOTOR_D_L;
    }
    else if(4 == step)
    {
        MOTOR_A_L;
        MOTOR_B_L;
        MOTOR_C_H;
        MOTOR_D_L;
    }
    else if(5 == step)
    {
        MOTOR_A_L;
        MOTOR_B_L;
        MOTOR_C_H;
        MOTOR_D_H;
    }
    else if(6 == step)
    {
        MOTOR_A_L;
        MOTOR_B_L;
        MOTOR_C_L;
        MOTOR_D_H;
    }
    else if(7 == step)
    {
        MOTOR_A_H;
        MOTOR_B_L;
        MOTOR_C_L;
        MOTOR_D_H;
    }
    if(dir == 1)
    {
        step++;
        if(step == 8)
        {
            step = 0;
        }
    }
}


void StepMotor_Stop(void)
{
    MOTOR_A_L;
    MOTOR_B_L;
    MOTOR_C_L;
    MOTOR_D_L;
}



//绝对值函数
int GFP_abs(int num)
{
	return num>=0 ? num :(-num);
}

uint16_t motor_speed(uint8_t cnt)
{
	uint16_t temp = 7200/cnt;
  if(temp <= 0)  temp = 0;
	return temp;
}


void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
    {
        static uint32_t i = 0;
        i++;
        if(lastmove == 0)
        {
            StepMotor_Move(1);
            if(i > pulse)
            {
                StepMotor_Stop();
                lastmove = 2;
                i = 0;
                //HAL_TIM_Base_Stop_IT(&g_tim_handle);
            }
        }
        else if(lastmove == 2)
        {
            i = 0;
            StepMotor_Stop();
        }
        else if(lastmove == 1)
        {
            StepMotor_Move(0);
            if(i > pulse)
            {
                StepMotor_Stop();
                lastmove = 2;
                i = 0;
                //HAL_TIM_Base_Stop_IT(&g_tim_handle);
            }
        }
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  /* 清除定时器溢出中断标志位 */
    }
}
