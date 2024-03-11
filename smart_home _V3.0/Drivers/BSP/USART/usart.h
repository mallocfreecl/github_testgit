#ifndef _USART_H_
#define _USART_H_
#include "stm32f1xx.h"
//#include "stm32f10x.h"


#define  USART_DEBUG		USART1		//调试打印所使用的串口组

extern UART_HandleTypeDef usartInitStruct1;
extern UART_HandleTypeDef usartInitStruct2;

void Usart1_Init(unsigned int baud);

void Usart2_Init(unsigned int baud);

void USART_SendData(USART_TypeDef *USARTx,uint8_t Byte);

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);

void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);

#endif

