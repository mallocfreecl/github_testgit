#ifndef _GTIM_H
#define _GTIM_H
#include "./SYSTEM/sys/sys.h"       //sys.h�а���#include "stm32f1xx.h"                                                                                                                      

#define PWM1_GPIO_PORT GPIOA         
#define PWM1_GPIO_PIN GPIO_PIN_0
#define PWM1_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOA_CLK_ENABLE();}while(0)

#define PWM2_GPIO_PORT GPIOA         
#define PWM2_GPIO_PIN GPIO_PIN_1
#define PWM2_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOA_CLK_ENABLE();}while(0)

//�ⲿҪʹ�õı�������
extern TIM_HandleTypeDef g_tim2_init_handle;
extern TIM_HandleTypeDef g_tim5_init_handle;

//��ʼ����������
void gtim2_init(uint32_t psc,uint32_t arr);
void gtim5_init(uint32_t psc,uint32_t arr);

#endif
