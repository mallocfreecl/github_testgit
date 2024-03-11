#ifndef     __STEPPING_MOTOR_H
#define     __STEPPING_MOTOR_H



#include "./SYSTEM/sys/sys.h"
/******************************************************************************************/
/* MOTOR IO操作函数 定义 */





#define MOTOR_A        GPIO_PIN_3
#define MOTOR_B        GPIO_PIN_4
#define MOTOR_C        GPIO_PIN_5
#define MOTOR_D        GPIO_PIN_6


#define MOTOR_A_H      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_SET)
#define MOTOR_A_L      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_RESET)
#define MOTOR_B_H      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_SET)
#define MOTOR_B_L      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_RESET)
#define MOTOR_C_H      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_SET)
#define MOTOR_C_L      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_RESET)
#define MOTOR_D_H      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET)
#define MOTOR_D_L      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET)



/******************************************************************************************/
/* MOTOR 函数 定义 */                    

void StepMotor_init(void);
void StepMotor_Move(uint8_t dir);
void StepMotor_Stop(void);




#endif
