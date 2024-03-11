/**
 ****************************************************************************************************
 * @file        exti.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-20
 * @brief       �ⲿ�ж� ��������
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
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
 * V1.0 20200419
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __KEYEXTI_H
#define __KEYEXTI_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* ���� �� �жϱ�� & �жϷ����� ���� */ 

#define KEY0_INT_GPIO_PORT              GPIOE
#define KEY0_INT_GPIO_PIN               GPIO_PIN_4
#define KEY0_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */
#define KEY0_INT_IRQn                   EXTI4_IRQn
#define KEY0_INT_IRQHandler             EXTI4_IRQHandler

#define KEY1_INT_GPIO_PORT              GPIOE
#define KEY1_INT_GPIO_PIN               GPIO_PIN_3
#define KEY1_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */
#define KEY1_INT_IRQn                   EXTI3_IRQn
#define KEY1_INT_IRQHandler             EXTI3_IRQHandler

#define KEY2_INT_GPIO_PORT              GPIOE
#define KEY2_INT_GPIO_PIN               GPIO_PIN_2
#define KEY2_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */
#define KEY2_INT_IRQn                   EXTI2_IRQn
#define KEY2_INT_IRQHandler             EXTI2_IRQHandler

#define WKUP_INT_GPIO_PORT              GPIOA
#define WKUP_INT_GPIO_PIN               GPIO_PIN_0
#define WKUP_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA��ʱ��ʹ�� */
#define WKUP_INT_IRQn                   EXTI0_IRQn
#define WKUP_INT_IRQHandler             EXTI0_IRQHandler

/******************************************************************************************/

extern uint8_t alarm_flag;
extern uint8_t alarm_is_free;
void key_extix_init(void);  /* �ⲿ�жϳ�ʼ�� */

#endif
























