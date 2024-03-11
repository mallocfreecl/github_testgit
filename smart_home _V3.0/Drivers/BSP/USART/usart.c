//硬件驱动
#include "./BSP/USART/usart.h"
//C库
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

/*
************************************************************
*	函数名称：	Usart1_Init
*
*	函数功能：	串口1初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：		TX-PA9		RX-PA10
************************************************************
*/

UART_HandleTypeDef usartInitStruct1;
void Usart1_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;
	
	__HAL_RCC_USART1_CLK_ENABLE(); /* USART1 时钟使能 */
	__HAL_RCC_GPIOA_CLK_ENABLE(); //USART1 TX引脚PA9、RX引脚PA10
	
	//PA9	TXD
	gpioInitStruct.Mode = GPIO_MODE_AF_PP;
	gpioInitStruct.Pin = GPIO_PIN_9;
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);    
	
	//PA10	RXD	
	gpioInitStruct.Mode = GPIO_MODE_AF_INPUT;
	gpioInitStruct.Pin = GPIO_PIN_10;
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpioInitStruct); 
	
	usartInitStruct1.Instance = USART1;
	usartInitStruct1.Init.BaudRate = baud;
	usartInitStruct1.Init.HwFlowCtl = UART_HWCONTROL_NONE; 		                    //无硬件流控
	usartInitStruct1.Init.Mode = UART_MODE_TX_RX;				                    //接收和发送
	usartInitStruct1.Init.Parity = UART_PARITY_NONE;							    //无校验
	usartInitStruct1.Init.StopBits = UART_STOPBITS_1;								//1位停止位
	usartInitStruct1.Init.WordLength = UART_WORDLENGTH_8B;							//8位数据位
	HAL_UART_Init(&usartInitStruct1);                                               //使能串口
		
		
	__HAL_UART_ENABLE_IT(&usartInitStruct1, UART_IT_RXNE);     /* 开启接收中断 */
	
	HAL_NVIC_EnableIRQ(USART1_IRQn);                           /* 使能 USART1 中断通道 */
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 2);                   /* 抢占优先级 0，子优先级 0*/

}

/*
************************************************************
*	函数名称：	Usart2_Init
*
*	函数功能：	串口2初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：		TX-PA2		RX-PA3
************************************************************
*/

UART_HandleTypeDef usartInitStruct2;
void Usart2_Init(unsigned int baud)
{
	GPIO_InitTypeDef gpioInitStruct;
	
	__HAL_RCC_USART2_CLK_ENABLE(); /* USART2 时钟使能 */
	__HAL_RCC_GPIOA_CLK_ENABLE(); //USART1 TX引脚PA9、RX引脚PA10
	
	//PA2	TXD
	gpioInitStruct.Mode = GPIO_MODE_AF_PP;
	gpioInitStruct.Pin = GPIO_PIN_2;
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);    
	
	//PA3	RXD	
	gpioInitStruct.Mode = GPIO_MODE_AF_INPUT;
	gpioInitStruct.Pin = GPIO_PIN_3;
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpioInitStruct); 
	
	usartInitStruct2.Instance = USART2;
	usartInitStruct2.Init.BaudRate = baud;
	usartInitStruct2.Init.HwFlowCtl = UART_HWCONTROL_NONE; 		                    //无硬件流控
	usartInitStruct2.Init.Mode = UART_MODE_TX_RX;				                    //接收和发送
	usartInitStruct2.Init.Parity = UART_PARITY_NONE;							    //无校验
	usartInitStruct2.Init.StopBits = UART_STOPBITS_1;								//1位停止位
	usartInitStruct2.Init.WordLength = UART_WORDLENGTH_8B;							//8位数据位
	HAL_UART_Init(&usartInitStruct2);                                               //开启串口                                
		
	__HAL_UART_ENABLE_IT(&usartInitStruct2, UART_IT_RXNE);     /* 开启接收中断 */
	
	HAL_NVIC_EnableIRQ(USART2_IRQn);                           /* 使能 USART2 中断通道 */
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);                   /* 抢占优先级 0，子优先级 0*/
	

}

/*
************************************************************
*	函数名称：	Usart_SendString
*
*	函数功能：	串口数据发送
*
*	入口参数：	USARTx：串口组
*				str：要发送的数据
*				len：数据长度
*
*	返回参数：	无
*
*	说明：		
************************************************************  //发送一个字符串   
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{
	if(USARTx == USART1)		
    {
		HAL_UART_Transmit(&usartInitStruct1,str,len,1000);
		while(__HAL_UART_GET_FLAG(&usartInitStruct1,UART_FLAG_TC)!= SET);
	}
	else if (USARTx == USART2)
	{
	    HAL_UART_Transmit(&usartInitStruct2,str,len,1000);
		while(__HAL_UART_GET_FLAG(&usartInitStruct2,UART_FLAG_TC)!= SET);//发送数据寄存器空
	}

}

/*
************************************************************
*	函数名称：	UsartPrintf
*
*	函数功能：	格式化打印
*
*	入口参数：	USARTx：串口组
*				fmt：不定长参
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void USART_SendData(USART_TypeDef *USARTx,uint8_t Byte)//传一个字节
{
	uint8_t *dat = &Byte;
	if(USARTx == USART1)
	{
		HAL_UART_Transmit(&usartInitStruct1,dat,1,1000);//最后一个参数是超时时间
		while(__HAL_UART_GET_FLAG(&usartInitStruct1,UART_FLAG_TC)!= SET);
	}
	else if(USARTx == USART2)
	{
		HAL_UART_Transmit(&usartInitStruct2,dat,1,1000);//最后一个参数是超时时间
		while(__HAL_UART_GET_FLAG(&usartInitStruct2,UART_FLAG_TC)!= SET);
	}
	
}
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//格式化
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
	}
}

/*
************************************************************
*	函数名称：	USART1_IRQHandler
*
*	函数功能：	串口1收发中断
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/


void USART1_IRQHandler(void)
{

	if(__HAL_UART_GET_FLAG(&usartInitStruct1,UART_FLAG_RXNE)==SET) //接收中断
	{
		__HAL_UART_CLEAR_FLAG(&usartInitStruct1, USART_FLAG_RXNE);
	}

}
