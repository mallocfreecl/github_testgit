#include "./BSP/STEPPING_MOTOR/stepping_motor.h"
#include "./SYSTEM/delay/delay.h"



extern uint8_t lastmove;
TIM_HandleTypeDef g_tim_handle;
extern uint32_t pulse;//int(double)(angle/5.625)*64;
void StepMotor_init(void)
{
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_TIM2_CLK_ENABLE();
    

    GPIO_InitTypeDef gpio_struct;
    
    gpio_struct.Pin = MOTOR_A | MOTOR_B | MOTOR_C | MOTOR_D;
    gpio_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_struct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOC, &gpio_struct);
    
    g_tim_handle.Instance = TIM1;
    g_tim_handle.Init.Prescaler = 19;
    g_tim_handle.Init.Period = 7199;
    g_tim_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&g_tim_handle);
    
    HAL_NVIC_SetPriority(TIM1_UP_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
    HAL_TIM_Base_Start_IT(&g_tim_handle);
    //HAL_TIM_Base_Stop_IT(&g_tim_handle);
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


void TIM1_UP_IRQHandler(void)
{
    /* 以下代码没有使用定时器HAL库共用处理函数来处理，而是直接通过判断中断标志位的方式 */
    if(__HAL_TIM_GET_FLAG(&g_tim_handle, TIM_FLAG_UPDATE) != RESET)
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
        __HAL_TIM_CLEAR_IT(&g_tim_handle, TIM_IT_UPDATE);  /* 清除定时器溢出中断标志位 */
    }
}
