/*******************************************************************************
这是负责与副板通信的库。
为了便于后期编写，它可以识别与副板的robo_base.c库相同的语法格式，并发送给副板令其执行相应动作。
它亦可接收副板发来的电机角度等信息来监测电机。
这段代码通过串口DMA与副板进行通信。
 ******************************************************************************/

#include "main.h"
#include "communicate.h"

UART_RX_BUFFER Uart1_Rx;

void Usart_Init(void)
{
	Uart1_Rx.Buffer[0]=(uint8_t*)malloc(sizeof(uint8_t)*USART1_RX_LEN_MAX);//USART1_RX_LEN_MAX==18
	Uart1_Rx.Buffer[1]=(uint8_t*)malloc(sizeof(uint8_t)*USART1_RX_LEN_MAX);//USART1_RX_LEN_MAX==18
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	Uart1_Rx.Buffer_Num = 0;
	Uart1_Rx.Length_Max=USART1_RX_LEN_MAX;
	HAL_UART_Receive_DMA(&huart1, Uart1_Rx.Buffer[0], USART1_RX_LEN_MAX);
}
