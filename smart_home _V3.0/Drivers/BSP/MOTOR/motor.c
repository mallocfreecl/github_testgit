#include "./BSP/MOTOR/motor.h"

//电机正转多长时间，反转多长时间

GPIO_InitTypeDef gpio_init_struct;
void motor_init(void)
{ 
	gtim5_init(36-1,100-1);

	__HAL_RCC_GPIOA_CLK_ENABLE();      //开启时钟
	
	gpio_init_struct.Mode=GPIO_MODE_OUTPUT_PP;
	gpio_init_struct.Pin=GPIO_PIN_4|GPIO_PIN_5;
	gpio_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio_init_struct);
}

void SetSpeed(int8_t Speed)
{
   if(Speed >= 0)
   {
       HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
       __HAL_TIM_SET_COMPARE(&g_tim5_init_handle,TIM_CHANNEL_3,Speed);
   }
   else
   {
	   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
       __HAL_TIM_SET_COMPARE(&g_tim5_init_handle,TIM_CHANNEL_3,-Speed); 
   }

}
