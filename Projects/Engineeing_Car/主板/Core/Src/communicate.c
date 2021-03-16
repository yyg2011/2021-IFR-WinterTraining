/*******************************************************************************
���Ǹ����븱��ͨ�ŵĿ⡣
Ϊ�˱��ں��ڱ�д��������ʶ���븱���robo_base.c����ͬ���﷨��ʽ�������͸���������ִ����Ӧ������
����ɽ��ո��巢���ĵ���Ƕȵ���Ϣ���������
��δ���ͨ������DMA�븱�����ͨ�š�
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
