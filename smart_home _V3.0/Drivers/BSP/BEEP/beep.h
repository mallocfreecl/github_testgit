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

#ifndef _BEEP_H
#define _BEEP_H
#include "./SYSTEM/sys/sys.h"       //sys.h�а���#include "stm32f1xx.h"                                                           

//��������������
//�����ض���
#define BEEP_GPIO_PORT GPIOB
#define BEEP_GPIO_PIN GPIO_PIN_8
#define BEEP_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOB_CLK_ENABLE();}while(0)

//�˿��������     //BEEP_GPIO_PORT�滻GPIOB�������ձ���
#define BEEP(x)   do{ x ? \
	                  HAL_GPIO_WritePin(BEEP_GPIO_PORT,BEEP_GPIO_PIN,GPIO_PIN_SET) : \
	                  HAL_GPIO_WritePin(BEEP_GPIO_PORT,BEEP_GPIO_PIN,GPIO_PIN_RESET); \
                  }while(0)
 
//�˿ڷ�ת����
#define BEEP_Toggle() do{HAL_GPIO_TogglePin(BEEP_GPIO_PORT,BEEP_GPIO_PIN);}while(0)	


//�ֶ�/Զ�̷�����
#define BEEP1_GPIO_PORT GPIOC
#define BEEP1_GPIO_PIN GPIO_PIN_1
#define BEEP1_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOC_CLK_ENABLE();}while(0)

//�˿��������     //BEEP_GPIO_PORT�滻GPIOB�������ձ���
#define BEEP1(x)   do{ x ? \
	                  HAL_GPIO_WritePin(BEEP1_GPIO_PORT,BEEP1_GPIO_PIN,GPIO_PIN_SET) : \
	                  HAL_GPIO_WritePin(BEEP1_GPIO_PORT,BEEP1_GPIO_PIN,GPIO_PIN_RESET); \
                  }while(0)
 
//�˿ڷ�ת����
#define BEEP1_Toggle() do{HAL_GPIO_TogglePin(BEEP1_GPIO_PORT,BEEP1_GPIO_PIN);}while(0)	


//�����ֶ�/Զ�̷������Ķ�ȡ����   //��ʱѡ��GPIO ��ʱ��LED1��״̬
//#define BEEP1_Status  ((uint8_t)HAL_GPIO_ReadPin(BEEP1_GPIO_PORT, BEEP1_GPIO_PIN))     /* ��ȡLED1���� */
													
//��ʼ����������
void beep_init(void);
#endif
