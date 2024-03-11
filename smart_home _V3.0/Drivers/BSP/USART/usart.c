//Ӳ������
#include "./BSP/USART/usart.h"
//C��
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

/*
************************************************************
*	�������ƣ�	Usart1_Init
*
*	�������ܣ�	����1��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PA9		RX-PA10
************************************************************
*/

UART_HandleTypeDef usartInitStruct1;
void Usart1_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;
	
	__HAL_RCC_USART1_CLK_ENABLE(); /* USART1 ʱ��ʹ�� */
	__HAL_RCC_GPIOA_CLK_ENABLE(); //USART1 TX����PA9��RX����PA10
	
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
	usartInitStruct1.Init.HwFlowCtl = UART_HWCONTROL_NONE; 		                    //��Ӳ������
	usartInitStruct1.Init.Mode = UART_MODE_TX_RX;				                    //���պͷ���
	usartInitStruct1.Init.Parity = UART_PARITY_NONE;							    //��У��
	usartInitStruct1.Init.StopBits = UART_STOPBITS_1;								//1λֹͣλ
	usartInitStruct1.Init.WordLength = UART_WORDLENGTH_8B;							//8λ����λ
	HAL_UART_Init(&usartInitStruct1);                                               //ʹ�ܴ���
		
		
	__HAL_UART_ENABLE_IT(&usartInitStruct1, UART_IT_RXNE);     /* ���������ж� */
	
	HAL_NVIC_EnableIRQ(USART1_IRQn);                           /* ʹ�� USART1 �ж�ͨ�� */
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 2);                   /* ��ռ���ȼ� 0�������ȼ� 0*/

}

/*
************************************************************
*	�������ƣ�	Usart2_Init
*
*	�������ܣ�	����2��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PA2		RX-PA3
************************************************************
*/

UART_HandleTypeDef usartInitStruct2;
void Usart2_Init(unsigned int baud)
{
	GPIO_InitTypeDef gpioInitStruct;
	
	__HAL_RCC_USART2_CLK_ENABLE(); /* USART2 ʱ��ʹ�� */
	__HAL_RCC_GPIOA_CLK_ENABLE(); //USART1 TX����PA9��RX����PA10
	
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
	usartInitStruct2.Init.HwFlowCtl = UART_HWCONTROL_NONE; 		                    //��Ӳ������
	usartInitStruct2.Init.Mode = UART_MODE_TX_RX;				                    //���պͷ���
	usartInitStruct2.Init.Parity = UART_PARITY_NONE;							    //��У��
	usartInitStruct2.Init.StopBits = UART_STOPBITS_1;								//1λֹͣλ
	usartInitStruct2.Init.WordLength = UART_WORDLENGTH_8B;							//8λ����λ
	HAL_UART_Init(&usartInitStruct2);                                               //��������                                
		
	__HAL_UART_ENABLE_IT(&usartInitStruct2, UART_IT_RXNE);     /* ���������ж� */
	
	HAL_NVIC_EnableIRQ(USART2_IRQn);                           /* ʹ�� USART2 �ж�ͨ�� */
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);                   /* ��ռ���ȼ� 0�������ȼ� 0*/
	

}

/*
************************************************************
*	�������ƣ�	Usart_SendString
*
*	�������ܣ�	�������ݷ���
*
*	��ڲ�����	USARTx��������
*				str��Ҫ���͵�����
*				len�����ݳ���
*
*	���ز�����	��
*
*	˵����		
************************************************************  //����һ���ַ���   
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
		while(__HAL_UART_GET_FLAG(&usartInitStruct2,UART_FLAG_TC)!= SET);//�������ݼĴ�����
	}

}

/*
************************************************************
*	�������ƣ�	UsartPrintf
*
*	�������ܣ�	��ʽ����ӡ
*
*	��ڲ�����	USARTx��������
*				fmt����������
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void USART_SendData(USART_TypeDef *USARTx,uint8_t Byte)//��һ���ֽ�
{
	uint8_t *dat = &Byte;
	if(USARTx == USART1)
	{
		HAL_UART_Transmit(&usartInitStruct1,dat,1,1000);//���һ�������ǳ�ʱʱ��
		while(__HAL_UART_GET_FLAG(&usartInitStruct1,UART_FLAG_TC)!= SET);
	}
	else if(USARTx == USART2)
	{
		HAL_UART_Transmit(&usartInitStruct2,dat,1,1000);//���һ�������ǳ�ʱʱ��
		while(__HAL_UART_GET_FLAG(&usartInitStruct2,UART_FLAG_TC)!= SET);
	}
	
}
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//��ʽ��
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
	}
}

/*
************************************************************
*	�������ƣ�	USART1_IRQHandler
*
*	�������ܣ�	����1�շ��ж�
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/


void USART1_IRQHandler(void)
{

	if(__HAL_UART_GET_FLAG(&usartInitStruct1,UART_FLAG_RXNE)==SET) //�����ж�
	{
		__HAL_UART_CLEAR_FLAG(&usartInitStruct1, USART_FLAG_RXNE);
	}

}
