#include "main.h"
#include "gpio.h"
#include "gy53_iic.h"

void delay_us(uint32_t us)
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
    while (delay--) {}
}

void IIC1_SDA_IN(void)
{	   
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = VL53L0X_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY_GPIO_Port, &GPIO_InitStruct);
}

void IIC1_SDA_OUT(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = VL53L0X_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void IIC_Start(void)
{
	IIC_SDA_OUT();     
	IIC_SDA1;	  	  
	IIC_SCL1;
	delay_us(4);
 	IIC_SDA0;
	delay_us(4);
	IIC_SCL0;
}	  

void IIC_Stop(void)
{
	IIC_SDA_OUT();
	IIC_SCL0;
	IIC_SDA0;
 	delay_us(4);
	IIC_SCL1; 
	IIC_SDA1;
	delay_us(4);							   	
}

uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	IIC_SDA_IN();      
	IIC_SDA1;delay_us(1);	   
	IIC_SCL1;delay_us(1);	 
	while(READ_IIC_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL0;  
	return 0;  
} 

void IIC_Ack(void)
{
	IIC_SCL0;
	IIC_SDA_OUT();
	IIC_SDA0;
	delay_us(2);
	IIC_SCL1;
	delay_us(2);
	IIC_SCL0;
}

//???ACK??		    
void IIC_NAck(void)
{
	IIC_SCL0;
	IIC_SDA_OUT();
	IIC_SDA1;
	delay_us(2);
	IIC_SCL1;
	delay_us(2);
	IIC_SCL0;
}	

		  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	IIC_SDA_OUT(); 	    
    IIC_SCL0;
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA1;
		else
			IIC_SDA0;
		txd<<=1; 	  
		delay_us(2);   
		IIC_SCL1;
		delay_us(2); 
		IIC_SCL0;	
		delay_us(2);
    }	 
} 	    

uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC_SDA_IN();
    for(i=0;i<8;i++ )
	{
        IIC_SCL0; 
        delay_us(2);
		IIC_SCL1;
        receive<<=1;
        if(READ_IIC_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();
    else
        IIC_Ack();   
    return receive;
}

