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

#include "./BSP/BEEP/beep.h"
void beep_init(void)
{
	GPIO_InitTypeDef gpio_init_struct;
	BEEP_GPIO_CLK_ENABLE();       //开启时钟
         
	
	gpio_init_struct.Mode=GPIO_MODE_OUTPUT_PP;//推挽输出
	gpio_init_struct.Pin=BEEP_GPIO_PIN;
	gpio_init_struct.Pull=GPIO_PULLUP;        //上拉  默认高电平
	gpio_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(BEEP_GPIO_PORT,&gpio_init_struct);
	
	BEEP(0);      //关闭蜂鸣器
	
	//手动/远程控制蜂鸣器  低电平触发
	GPIO_InitTypeDef gpio_init_struct1;
	BEEP1_GPIO_CLK_ENABLE();       //开启时钟
         
	
	gpio_init_struct1.Mode=GPIO_MODE_OUTPUT_PP;//推挽输出
	gpio_init_struct1.Pin=BEEP1_GPIO_PIN;
	gpio_init_struct1.Pull=GPIO_PULLUP;        //上拉  默认高电平不响
	gpio_init_struct1.Speed=GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(BEEP1_GPIO_PORT,&gpio_init_struct1);
	
	BEEP1(1);      //关闭蜂鸣器
	
}






