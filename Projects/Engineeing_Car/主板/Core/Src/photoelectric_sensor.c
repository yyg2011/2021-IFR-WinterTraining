/*******************************************************************************
负责检测矿石，配合GY53与光电传感器
 ******************************************************************************/
#include "main.h"
#include "photoelectric_sensor.h"
#include "gy53_iic.h"

uint16_t gy53_data=0;
int photoelectric_switch1=0;
int photoelectric_switch2=0;

void photoelectric_switch()//光电接收
{
    photoelectric_switch1=HAL_GPIO_ReadPin(GPIOA,PHOTOELECTRIC_SWITCH1_Pin);
    photoelectric_switch2=HAL_GPIO_ReadPin(GPIOA,PHOTOELECTRIC_SWITCH2_Pin);
}

void gy53_rceive()//gy53接收
{
    IIC_Start();
    IIC_Send_Byte(0x47);
    IIC_Wait_Ack();
    gy53_data=((IIC_Read_Byte(4))*256 +IIC_Read_Byte(5));
}

int direct_check()//判断是否对准：0未对准，1对准但距离不够，2已对准
{
    if(photoelectric_switch1==0|photoelectric_switch2==0)
    {
        if(gy53_data>=100) return 1;
        else return 2;
    }
    else return 0;
}