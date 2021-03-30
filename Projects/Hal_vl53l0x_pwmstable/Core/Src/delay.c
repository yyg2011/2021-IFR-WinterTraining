#include "delay.h"
#include "main.h"
static uint8_t  Times_us=1;//1us��Ҫ�ƵĴ���
static uint16_t Times_ms=0;//1ms��Ҫ�ƵĴ���
//SYSCLK=72M,SYSCLK/8=9M
void delay_init(uint8_t SYSCLK)
{
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);	//ѡ���ⲿʱ��  HCLK/8
	Times_us=SYSCLK/8;	//Times_us=9��	    
	Times_ms=(uint16_t)Times_us*1000;//Times_ms=9000��
}
//SYSCLK=72M,SYSCLK/8=9M,����һ����Ϊ9��֮һ ΢�룬1us��Ҫ����9��
//����SysTick->LOAD=nus*SYSCLK/8=nus*9=Count
//Count<2^24��Max_Count=16777215
//���nus=Max_Count/9=16777215/9=1864135us
//�����nusΪ1864135
void delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=(nus*Times_us); //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 	
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
//	SysTick->VAL =0X00;       //��ռ�����	 
}
//SYSCLK=72M,SYSCLK/8=9M,1΢�������9�Σ���1���������9000��
//����SysTick->LOAD=nms*9000=Count
//Count<2^24��Max_Count=16777215
//���nms=Max_Count/9000=16777215/9000=1864.135ms��
//�����nms=1864
void delay_ms(uint16_t nms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD=167999;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           
	SysTick->CTRL=0x01 ;   
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));  
	SysTick->CTRL=0x00;       
	SysTick->VAL =0X00;       	    
}
void start_Time(void)
{
	  SysTick->CTRL=0x00; //�رռ�����  
    SysTick->LOAD=(Times_us*40000);//40ms��ʱ
	  SysTick->CTRL=0x01 ;  //��16λ��ʹ���ⲿʱ�ӣ����жϣ�������ʱ������
}
void Get_Time(float *time)//�õ�ʱ�䵥λΪms
{
	  SysTick->CTRL=0x00; //�رռ�����  
    time[0]=((float)(40000*Times_us-SysTick->VAL))/(Times_us*1000);//��ȡʱ��
	   	SysTick->VAL =0x00;          //������� 
}



