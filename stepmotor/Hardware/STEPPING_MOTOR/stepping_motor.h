#ifndef     __STEPPING_MOTOR_H
#define     __STEPPING_MOTOR_H

//#include "sys.h"
#include "stm32f10x.h"  
/******************************************************************************************/
/* MOTOR IO操作函数 定义 */


#define MOTOR_A        GPIO_Pin_12  
#define MOTOR_B        GPIO_Pin_13
#define MOTOR_C        GPIO_Pin_14
#define MOTOR_D        GPIO_Pin_15


#define MOTOR_A_H      GPIO_SetBits(GPIOB, GPIO_Pin_12);
#define MOTOR_A_L      GPIO_ResetBits(GPIOB, GPIO_Pin_12);
#define MOTOR_B_H      GPIO_SetBits(GPIOB, GPIO_Pin_13);
#define MOTOR_B_L      GPIO_ResetBits(GPIOB, GPIO_Pin_13);
#define MOTOR_C_H      GPIO_SetBits(GPIOB, GPIO_Pin_14);
#define MOTOR_C_L      GPIO_ResetBits(GPIOB, GPIO_Pin_14);
#define MOTOR_D_H      GPIO_SetBits(GPIOB, GPIO_Pin_15);
#define MOTOR_D_L      GPIO_ResetBits(GPIOB, GPIO_Pin_15);



/******************************************************************************************/


extern TIM_TimeBaseInitTypeDef TIM4_TimeBaseInitStructure;
/* MOTOR 函数 定义 */                    

void StepMotor_init(void);
void StepMotor_Move(uint8_t dir);
void StepMotor_Stop(void);
int GFP_abs(int num);
uint16_t motor_speed(uint8_t cnt);
#endif
