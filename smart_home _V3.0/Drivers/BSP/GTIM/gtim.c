#include "./BSP/GTIM/gtim.h"//��������⺯��

//PWM���ƶ��:ʹ��TIM2��ͨ��1(CH1���PWM����,PA0)

//����ȫ�ֽṹ�����
GPIO_InitTypeDef g_tim2_gpio_init_struct;    //GPIO��ʼ���ṹ��
TIM_HandleTypeDef g_tim2_init_handle;    //��ʱ����ʼ���ṹ��
TIM_OC_InitTypeDef g_tim2_oc_init_handle; //����Ƚϳ�ʼ���ṹ��

void gtim2_init(uint32_t psc,uint32_t arr)//psc:Ԥ��Ƶ  arr:�Զ�װ��ֵ
{ 
	
	//1.����GPIOʱ�ӡ�AFIOʱ��(������ӳ��)����ʱ��ʱ�ӡ�����GPIO��������ӳ��
	PWM1_GPIO_CLK_ENABLE();//�鿴�궨��
	__HAL_RCC_TIM2_CLK_ENABLE();
	
	g_tim2_gpio_init_struct.Mode=GPIO_MODE_AF_PP;//�����������
	g_tim2_gpio_init_struct.Pin=PWM1_GPIO_PIN;
	g_tim2_gpio_init_struct.Pull=GPIO_PULLUP;    //����  Ĭ�ϸߵ�ƽ
	g_tim2_gpio_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PWM1_GPIO_PORT,&g_tim2_gpio_init_struct);
	
	//2.ʱ����Ԫ��ʼ������ʼ������HAL_TIM_PWM_Init����(�����ڲ������HAL_TIM_PWM_MspInit����)/HAL_TIM_Base_Init
	g_tim2_init_handle.Instance=TIM2;
	g_tim2_init_handle.Init.CounterMode=TIM_COUNTERMODE_UP;      //���ϼ���
	g_tim2_init_handle.Init.Period=arr;
	g_tim2_init_handle.Init.Prescaler=psc;
	HAL_TIM_PWM_Init(&g_tim2_init_handle);//��HAL_TIM_Base_Init(&g_timer_handle)
	
	//3.PWMͨ������(��ʱ��������Ƚ����á��Ǹ�ͨ��),ʹ�ܶ�ʱ����ͨ�����
	//����1��:HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim,
	//TIM_OC_InitTypeDef *sConfig, uint32_t Channel);
	//������HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
	g_tim2_oc_init_handle.OCMode=TIM_OCMODE_PWM1;          //PWMģʽ1
	g_tim2_oc_init_handle.Pulse=0;                   //�Ƚ�ֵ��Ϊtrr/2
	g_tim2_oc_init_handle.OCPolarity=TIM_OCPOLARITY_HIGH;  //����:�Ƚϼ���Ϊ��   ��ʱ������ֵС�ڱȽ�ֵ�����Ч��ƽ�ߵ�ƽ
	HAL_TIM_PWM_ConfigChannel(&g_tim2_init_handle,&g_tim2_oc_init_handle, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&g_tim2_init_handle, TIM_CHANNEL_1);
}


//PWM����ֱ�����:ʹ��TIM5��ͨ��2(CH2���PWM����,PA1)

//����ȫ�ֽṹ�����
GPIO_InitTypeDef g_tim5_gpio_init_struct;    //GPIO��ʼ���ṹ��
TIM_HandleTypeDef g_tim5_init_handle;    //��ʱ����ʼ���ṹ��
TIM_OC_InitTypeDef g_tim5_oc_init_handle; //����Ƚϳ�ʼ���ṹ��

void gtim5_init(uint32_t psc,uint32_t arr)//psc:Ԥ��Ƶ  arr:�Զ�װ��ֵ
{ 
	
	//1.����GPIOʱ�ӡ�AFIOʱ��(������ӳ��)����ʱ��ʱ�ӡ�����GPIO��������ӳ��
	PWM2_GPIO_CLK_ENABLE();//�鿴�궨��
	__HAL_RCC_TIM5_CLK_ENABLE();
	
	g_tim5_gpio_init_struct.Mode=GPIO_MODE_AF_PP;//�����������
	g_tim5_gpio_init_struct.Pin=PWM2_GPIO_PIN;
	g_tim5_gpio_init_struct.Pull=GPIO_PULLUP;    //����  Ĭ�ϸߵ�ƽ
	g_tim5_gpio_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PWM2_GPIO_PORT,&g_tim5_gpio_init_struct);
	
	//2.ʱ����Ԫ��ʼ������ʼ������HAL_TIM_PWM_Init����(�����ڲ������HAL_TIM_PWM_MspInit����)/HAL_TIM_Base_Init
	g_tim5_init_handle.Instance=TIM5;
	g_tim5_init_handle.Init.CounterMode=TIM_COUNTERMODE_UP;      //���ϼ���
	g_tim5_init_handle.Init.Period=arr;
	g_tim5_init_handle.Init.Prescaler=psc;
	HAL_TIM_PWM_Init(&g_tim5_init_handle);//��HAL_TIM_Base_Init(&g_timer_handle)
	
	//3.PWMͨ������(��ʱ��������Ƚ����á��Ǹ�ͨ��),ʹ�ܶ�ʱ����ͨ�����
	//����1��:HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim,
	//TIM_OC_InitTypeDef *sConfig, uint32_t Channel);
	//������HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
	g_tim5_oc_init_handle.OCMode=TIM_OCMODE_PWM1;          //PWMģʽ1
	g_tim5_oc_init_handle.Pulse=0;                   //�Ƚ�ֵ��Ϊtrr/2
	g_tim5_oc_init_handle.OCPolarity=TIM_OCPOLARITY_HIGH;  //����:�Ƚϼ���Ϊ��   ��ʱ������ֵС�ڱȽ�ֵ�����Ч��ƽ�ߵ�ƽ
	HAL_TIM_PWM_ConfigChannel(&g_tim5_init_handle,&g_tim5_oc_init_handle, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&g_tim5_init_handle, TIM_CHANNEL_2);
}
