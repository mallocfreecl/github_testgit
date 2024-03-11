#include "./BSP/GTIM/gtim.h"//里面包含库函数

//PWM控制舵机:使用TIM2的通道1(CH1输出PWM波形,PA0)

//定义全局结构体变量
GPIO_InitTypeDef g_tim2_gpio_init_struct;    //GPIO初始化结构体
TIM_HandleTypeDef g_tim2_init_handle;    //定时器初始化结构体
TIM_OC_InitTypeDef g_tim2_oc_init_handle; //输出比较初始化结构体

void gtim2_init(uint32_t psc,uint32_t arr)//psc:预分频  arr:自动装载值
{ 
	
	//1.开启GPIO时钟、AFIO时钟(用于重映射)、定时器时钟。配置GPIO。引脚重映射
	PWM1_GPIO_CLK_ENABLE();//查看宏定义
	__HAL_RCC_TIM2_CLK_ENABLE();
	
	g_tim2_gpio_init_struct.Mode=GPIO_MODE_AF_PP;//复用推挽输出
	g_tim2_gpio_init_struct.Pin=PWM1_GPIO_PIN;
	g_tim2_gpio_init_struct.Pull=GPIO_PULLUP;    //上拉  默认高电平
	g_tim2_gpio_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PWM1_GPIO_PORT,&g_tim2_gpio_init_struct);
	
	//2.时基单元初始化，初始化可用HAL_TIM_PWM_Init函数(函数内部会调用HAL_TIM_PWM_MspInit函数)/HAL_TIM_Base_Init
	g_tim2_init_handle.Instance=TIM2;
	g_tim2_init_handle.Init.CounterMode=TIM_COUNTERMODE_UP;      //向上计数
	g_tim2_init_handle.Init.Period=arr;
	g_tim2_init_handle.Init.Prescaler=psc;
	HAL_TIM_PWM_Init(&g_tim2_init_handle);//或HAL_TIM_Base_Init(&g_timer_handle)
	
	//3.PWM通道配置(定时器、输出比较设置、那个通道),使能定时器和通道输出
	//函数1①:HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim,
	//TIM_OC_InitTypeDef *sConfig, uint32_t Channel);
	//函数②HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
	g_tim2_oc_init_handle.OCMode=TIM_OCMODE_PWM1;          //PWM模式1
	g_tim2_oc_init_handle.Pulse=0;                   //比较值设为trr/2
	g_tim2_oc_init_handle.OCPolarity=TIM_OCPOLARITY_HIGH;  //极性:比较极性为高   定时器计数值小于比较值输出有效电平高电平
	HAL_TIM_PWM_ConfigChannel(&g_tim2_init_handle,&g_tim2_oc_init_handle, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&g_tim2_init_handle, TIM_CHANNEL_1);
}


//PWM控制直流电机:使用TIM5的通道2(CH2输出PWM波形,PA1)

//定义全局结构体变量
GPIO_InitTypeDef g_tim5_gpio_init_struct;    //GPIO初始化结构体
TIM_HandleTypeDef g_tim5_init_handle;    //定时器初始化结构体
TIM_OC_InitTypeDef g_tim5_oc_init_handle; //输出比较初始化结构体

void gtim5_init(uint32_t psc,uint32_t arr)//psc:预分频  arr:自动装载值
{ 
	
	//1.开启GPIO时钟、AFIO时钟(用于重映射)、定时器时钟。配置GPIO。引脚重映射
	PWM2_GPIO_CLK_ENABLE();//查看宏定义
	__HAL_RCC_TIM5_CLK_ENABLE();
	
	g_tim5_gpio_init_struct.Mode=GPIO_MODE_AF_PP;//复用推挽输出
	g_tim5_gpio_init_struct.Pin=PWM2_GPIO_PIN;
	g_tim5_gpio_init_struct.Pull=GPIO_PULLUP;    //上拉  默认高电平
	g_tim5_gpio_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PWM2_GPIO_PORT,&g_tim5_gpio_init_struct);
	
	//2.时基单元初始化，初始化可用HAL_TIM_PWM_Init函数(函数内部会调用HAL_TIM_PWM_MspInit函数)/HAL_TIM_Base_Init
	g_tim5_init_handle.Instance=TIM5;
	g_tim5_init_handle.Init.CounterMode=TIM_COUNTERMODE_UP;      //向上计数
	g_tim5_init_handle.Init.Period=arr;
	g_tim5_init_handle.Init.Prescaler=psc;
	HAL_TIM_PWM_Init(&g_tim5_init_handle);//或HAL_TIM_Base_Init(&g_timer_handle)
	
	//3.PWM通道配置(定时器、输出比较设置、那个通道),使能定时器和通道输出
	//函数1①:HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim,
	//TIM_OC_InitTypeDef *sConfig, uint32_t Channel);
	//函数②HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
	g_tim5_oc_init_handle.OCMode=TIM_OCMODE_PWM1;          //PWM模式1
	g_tim5_oc_init_handle.Pulse=0;                   //比较值设为trr/2
	g_tim5_oc_init_handle.OCPolarity=TIM_OCPOLARITY_HIGH;  //极性:比较极性为高   定时器计数值小于比较值输出有效电平高电平
	HAL_TIM_PWM_ConfigChannel(&g_tim5_init_handle,&g_tim5_oc_init_handle, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&g_tim5_init_handle, TIM_CHANNEL_2);
}
