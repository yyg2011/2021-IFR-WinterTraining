/*******************************************************************************
这是负责与副板通信的库。
为了便于后期编写，它可以识别与副板的robo_base.c库相似的语法格式，并发送给副板令其执行相应动作。
它亦可接收副板发来的电机角度等信息来监测电机。
这段代码通过串口DMA与副板进行通信。

通信协议：5位
一、控制副板硬件
第零位 开始校验
默认为12即可通过校验
第一位 控制类别
0 气缸 1 电机：位置环 2 电机：速度环 3 急停所有
第二位 硬件编号
与副板里面写的一致
第三位 参数设置
气缸填0、1状态，速度环填目标速度，位置环填目标状态
第四位 结束校验
默认为34即可通过校验

二、接收副板硬件
第零位 开始校验
默认为56即可通过校验
第一位 硬件类别
1 电机：位置环 2 电机：速度环 
第二位 硬件编号
与副板里面写的一致
第三位 角度信息
与副板里面写的一致
第四位 结束校验
默认为78即可通过校验
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
