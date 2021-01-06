#include "timer.h"
#include "led.h"
int count=0;
u16 Servo_90=899; 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�

	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��3
}

void TIM4_Int_ShutDown()
{
	TIM3->CNT=0;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannelCmd=DISABLE;
	TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM4,DISABLE);
	count=0;
}

//��ʱ��3�жϷ�����
void TIM4_IRQHandler(void)
{
if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==1){
		if (count==1){
			GPIO_SetBits(GPIOC,GPIO_Pin_1);
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==1) TIM_SetCompare1(TIM3,Servo_90);
			TIM4_Int_ShutDown();
			count=0;
		}
		else{
			count++;
		}
	}
	else TIM4_Int_ShutDown();
}
			TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //����жϱ�־λ
}
