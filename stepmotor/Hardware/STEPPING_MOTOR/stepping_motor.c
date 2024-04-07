#include "stepping_motor.h"
#include "delay.h"


extern uint8_t lastmove;         //0����ת  1:��ת   2����ʾ���ֹͣ
extern uint32_t pulse;           //int(double)(angle/5.625)*64;

//GPIOʹ��PB.12��PB.13��PB.14��PB.15
//ʹ�ö�ʱ��3�ĸ����ж�   ��ʱ2ms:ִ��ÿ����ʱ��

/*�ṹ���ʼ��*/

GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM4_TimeBaseInitStructure;
void StepMotor_init(void)      //ȷ��ÿ�����������ʱ��(ȷ��ת��)
{
  /*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);			//����GPIOB��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);			//����TIM4��ʱ��
	
	/*GPIO��ʼ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MOTOR_A | MOTOR_B | MOTOR_C | MOTOR_D;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						
	
	/*����ʱ��Դ*/
	TIM_InternalClockConfig(TIM4);		//ѡ��TIM4Ϊ�ڲ�ʱ�ӣ��������ô˺�����TIMĬ��ҲΪ�ڲ�ʱ��
	
	/*ʱ����Ԫ��ʼ��*/
	TIM4_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		  //ʱ�ӷ�Ƶ��ѡ�񲻷�Ƶ���˲������������˲���ʱ�ӣ���Ӱ��ʱ����Ԫ����
	TIM4_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//������ģʽ��ѡ�����ϼ���
	TIM4_TimeBaseInitStructure.TIM_Period = 7200-1;									//�������ڣ���ARR��ֵ
	TIM4_TimeBaseInitStructure.TIM_Prescaler = 20-1;									//Ԥ��Ƶ������PSC��ֵ  //��ʱʱ�䣺7200 * ((19+1)/72000000) = 2ms
	TIM4_TimeBaseInitStructure.TIM_RepetitionCounter = 0;						//�ظ����������߼���ʱ���Ż��õ�
	TIM_TimeBaseInit(TIM4, &TIM4_TimeBaseInitStructure);							//���ṹ���������TIM_TimeBaseInit������TIM2��ʱ����Ԫ	
	
	/*�ж��������*/
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);						//�����ʱ�����±�־λ
																//TIM_TimeBaseInit����ĩβ���ֶ������˸����¼�
																//��������˱�־λ�������жϺ󣬻����̽���һ���ж�
																//�������������⣬������˱�־λҲ��
	
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);					//����TIM2�ĸ����ж�
	
	/*NVIC����*/
	NVIC_InitTypeDef NVIC_InitStructure;											//����ṹ�����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;						//ѡ������NVIC��TIM4��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//ָ��NVIC��·ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//ָ��NVIC��·����ռ���ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//ָ��NVIC��·����Ӧ���ȼ�Ϊ0
	NVIC_Init(&NVIC_InitStructure);														//���ṹ���������NVIC_Init������NVIC����
	
	/*TIMʹ��*/
	//TIM_Cmd(TIM4, ENABLE);			//ʹ��TIM3����ʱ����ʼ����  //��ʱ��һ��������������Ϳ�ʼ��ת
   
}


//�����������������     dir:1��ʾ�����ת��0��ʾ��ת
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



//����ֵ����
int GFP_abs(int num)
{
	return num>=0 ? num :(-num);
}

uint16_t motor_speed(uint8_t cnt)
{
	uint16_t temp = 7200/cnt;
  if(temp <= 0)  temp = 0;
	return temp;
}


void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
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
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  /* �����ʱ������жϱ�־λ */
    }
}
