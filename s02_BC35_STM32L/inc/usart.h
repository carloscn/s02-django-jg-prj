#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include <stm32l1xx.h>
#define u8 int8_t
#define u16 int16_t
#define u32 int32_t

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
#define	UART2_REC_MAX_LEN	30
char RxCounter,RxBuffer[100];     //接收缓冲,最大USART_REC_LEN个字节.
char RxCounter1,RxBuffer1[100];     //接收缓冲,最大USART_REC_LEN个字节.
char RxCounter2,RxBuffer2[UART2_REC_MAX_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

void uart_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
void Uart1_SendStr(char*SendBuf);
#endif


