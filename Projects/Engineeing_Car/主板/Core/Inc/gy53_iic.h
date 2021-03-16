#include "gpio.h"

void IIC_SDA_IN(void);
void IIC_SDA_OUT(void);

#define IIC_SCL0    HAL_GPIO_WritePin(GPIOC,VL53L0X_SCL_Pin, GPIO_PIN_RESET)
#define IIC_SDA0    HAL_GPIO_WritePin(GPIOC,VL53L0X_SDA_Pin, GPIO_PIN_RESET)
#define IIC_SCL1    HAL_GPIO_WritePin(GPIOC,VL53L0X_SCL_Pin, GPIO_PIN_SET)
#define IIC_SDA1    HAL_GPIO_WritePin(GPIOC,VL53L0X_SDA_Pin, GPIO_PIN_SET) 
#define READ_IIC_SDA   HAL_GPIO_ReadPin(GPIOC,VL53L0X_SCL_Pin) 

void IIC_Init(void);               			 
void IIC_Start(void);				
void IIC_Stop(void);	  			
void IIC_Send_Byte(u8 txd);			
uint8_t IIC_Read_Byte(unsigned char ack);
uint8_t IIC_Wait_Ack(void); 				
void IIC_Ack(void);					
void IIC_NAck(void);				

void IIC1_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC1_Read_One_Byte(u8 daddr,u8 addr);	  












