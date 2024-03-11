#ifndef _MOTOR_H
#define _MOTOR_H
#include "./BSP/GTIM/gtim.h"//里面包含库函数

void motor_init(void);
void SetSpeed(int8_t Speed);
#endif
