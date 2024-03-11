/**
 ****************************************************************************************************
 * @file        led.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-17
 * @brief       LED 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20200417
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef _BEEP_H
#define _BEEP_H
#include "./SYSTEM/sys/sys.h"       //sys.h中包含#include "stm32f1xx.h"                                                           

//环境报警蜂鸣器
//引脚重定义
#define BEEP_GPIO_PORT GPIOB
#define BEEP_GPIO_PIN GPIO_PIN_8
#define BEEP_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOB_CLK_ENABLE();}while(0)

//端口输出定义     //BEEP_GPIO_PORT替换GPIOB更具有普遍性
#define BEEP(x)   do{ x ? \
	                  HAL_GPIO_WritePin(BEEP_GPIO_PORT,BEEP_GPIO_PIN,GPIO_PIN_SET) : \
	                  HAL_GPIO_WritePin(BEEP_GPIO_PORT,BEEP_GPIO_PIN,GPIO_PIN_RESET); \
                  }while(0)
 
//端口翻转定义
#define BEEP_Toggle() do{HAL_GPIO_TogglePin(BEEP_GPIO_PORT,BEEP_GPIO_PIN);}while(0)	


//手动/远程蜂鸣器
#define BEEP1_GPIO_PORT GPIOC
#define BEEP1_GPIO_PIN GPIO_PIN_1
#define BEEP1_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOC_CLK_ENABLE();}while(0)

//端口输出定义     //BEEP_GPIO_PORT替换GPIOB更具有普遍性
#define BEEP1(x)   do{ x ? \
	                  HAL_GPIO_WritePin(BEEP1_GPIO_PORT,BEEP1_GPIO_PIN,GPIO_PIN_SET) : \
	                  HAL_GPIO_WritePin(BEEP1_GPIO_PORT,BEEP1_GPIO_PIN,GPIO_PIN_RESET); \
                  }while(0)
 
//端口翻转定义
#define BEEP1_Toggle() do{HAL_GPIO_TogglePin(BEEP1_GPIO_PORT,BEEP1_GPIO_PIN);}while(0)	


//定义手动/远程蜂鸣器的读取引脚   //暂时选好GPIO 暂时用LED1的状态
//#define BEEP1_Status  ((uint8_t)HAL_GPIO_ReadPin(BEEP1_GPIO_PORT, BEEP1_GPIO_PIN))     /* 读取LED1引脚 */
													
//初始化函数声明
void beep_init(void);
#endif
