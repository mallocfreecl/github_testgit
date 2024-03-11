#ifndef _GTIM_H
#define _GTIM_H
#include "./SYSTEM/sys/sys.h"       //sys.h中包含#include "stm32f1xx.h"                                                                                                                      

#define PWM1_GPIO_PORT GPIOA         
#define PWM1_GPIO_PIN GPIO_PIN_0
#define PWM1_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOA_CLK_ENABLE();}while(0)

#define PWM2_GPIO_PORT GPIOA         
#define PWM2_GPIO_PIN GPIO_PIN_1
#define PWM2_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOA_CLK_ENABLE();}while(0)

//外部要使用的变量声明
extern TIM_HandleTypeDef g_tim2_init_handle;
extern TIM_HandleTypeDef g_tim5_init_handle;

//初始化函数声明
void gtim2_init(uint32_t psc,uint32_t arr);
void gtim5_init(uint32_t psc,uint32_t arr);

#endif
