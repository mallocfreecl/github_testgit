#include "./BSP/SERVO/servo.h"

void Servo_Init(void)
{
	gtim2_init(72-1,20000-1);
}


//0     500
//180   2500
void Servo_SetAngle(float Angle)
{
	__HAL_TIM_SET_COMPARE(&g_tim2_init_handle,TIM_CHANNEL_1,Angle / 180 * 2000 + 500);
}
