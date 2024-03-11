/**
 ****************************************************************************************************
 * @file        led.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-17
 * @brief       LED ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20200417
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "./BSP/BEEP/beep.h"
void beep_init(void)
{
	GPIO_InitTypeDef gpio_init_struct;
	BEEP_GPIO_CLK_ENABLE();       //����ʱ��
         
	
	gpio_init_struct.Mode=GPIO_MODE_OUTPUT_PP;//�������
	gpio_init_struct.Pin=BEEP_GPIO_PIN;
	gpio_init_struct.Pull=GPIO_PULLUP;        //����  Ĭ�ϸߵ�ƽ
	gpio_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(BEEP_GPIO_PORT,&gpio_init_struct);
	
	BEEP(0);      //�رշ�����
	
	//�ֶ�/Զ�̿��Ʒ�����  �͵�ƽ����
	GPIO_InitTypeDef gpio_init_struct1;
	BEEP1_GPIO_CLK_ENABLE();       //����ʱ��
         
	
	gpio_init_struct1.Mode=GPIO_MODE_OUTPUT_PP;//�������
	gpio_init_struct1.Pin=BEEP1_GPIO_PIN;
	gpio_init_struct1.Pull=GPIO_PULLUP;        //����  Ĭ�ϸߵ�ƽ����
	gpio_init_struct1.Speed=GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(BEEP1_GPIO_PORT,&gpio_init_struct1);
	
	BEEP1(1);      //�رշ�����
	
}






