#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "servo.h" 

int main(void)
{ 
	u16 Servo_90=899;    	
	u16 Servo_0=499;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	LED_Init();				//��ʼ��LED�˿�
	KEY_Init();
 	TIM2_PWM_Init(10000-1,145-1);
	TIM3_PWM_Init(10000-1,145-1);	
     				
	while(1)
	{                                                                                                                                                                                                                                                                                                                                                                                                                       
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==1){
			TIM4_Int_Init(10000-1,8400-1);//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����5000��Ϊ500ms
			while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==1){
				GPIO_SetBits(GPIOC,GPIO_Pin_0); 
				TIM_SetCompare1(TIM2,Servo_90);
			}
		GPIO_ResetBits(GPIOC,GPIO_Pin_0); 
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
		TIM_SetCompare1(TIM2,Servo_0);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetCompare1(TIM3,Servo_0);
		TIM4_Int_ShutDown();
		}
	}
}
