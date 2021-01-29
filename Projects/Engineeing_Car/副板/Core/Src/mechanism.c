#include "robo_base.h"
#include "mechanism.h"
#include "main.h"

ROBO_BASE Robo_Base;
CAN_HandleTypeDef hcan2;
float speed;
int Motor_num;

void cylinder(int mode)//气缸
{
    if(mode==0)
    {
        
        
    }
    else if(mode==1)
    {
        
        
    }
}


void LEAD_SCREW_BASE_Init(ROBO_BASE *Robo)//丝杠电机初始化
{
  Pos_System* P_Pos=NULL;           //位置环信息和pid
  P_Pos=&Robo->Pos_Lead_Screw; PID_Init(&P_Pos->Pos_PID,			0,	0,	0,	0,	0,	0,	0);
  P_Pos->Motor_Num=9;		PID_Init(&P_Pos->Speed_PID,			0,	0,	0,	0,	0,	0,	0); 
}


void Arm_Pos_Analysis(ROBO_BASE* Robo,uint8_t* RX_Data,uint32_t Motor_Num)
{
  Pos_System* P_Motor=NULL;
  switch(Motor_Num)
  {
    case 0x209:P_Motor=&Robo->Pos_Lead_Screw;break;
	default:break;
  }if(P_Motor!=NULL) Motor_Info_Handle(&P_Motor->Info,RX_Data);
}

void conveyor_motor_begin(int num)
{

}

void conveyor_motor_stop(int num)
{

}

void conveyor_belt(int num,int mode)//同步轮传送带
{
    if(mode==0)
    {
        conveyor_motor_begin(num*2);
        conveyor_motor_begin(num*2+1);
    }
    else if(mode==1)
    {
        conveyor_motor_stop(num*2);
        conveyor_motor_stop(num*2+1);
    }
}

