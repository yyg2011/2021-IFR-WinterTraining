/*******************************************************************************
控制一切机械结构的动作
 ******************************************************************************/

#include "main.h"
#include "whell_control.h"
#include "communicate.h"
#include "Remote.h"

int speedLF,speedRF,speedRB,speedLB,Robo_mode;
extern RC_Ctl_t RC_CtrlData;

void Remote_to_speed()//麦克纳姆轮各轮速度控制函数
{
    Robo_mode=0;
	if(RC_CtrlData.rc.ch2==1024)//平移
	{
		speedLF=((RC_CtrlData.rc.ch1-1024)-(RC_CtrlData.rc.ch0-1024))*5;
		speedRF=(-(RC_CtrlData.rc.ch1-1024)-(RC_CtrlData.rc.ch0-1024))*5;
		speedRB=(-(RC_CtrlData.rc.ch1-1024)+(RC_CtrlData.rc.ch0-1024))*5;
		speedLB=((RC_CtrlData.rc.ch1-1024)+(RC_CtrlData.rc.ch0-1024))*5;
	}
	else//旋转
    {
		speedLF=(RC_CtrlData.rc.ch2-1024)*5;
		speedRF=(RC_CtrlData.rc.ch2-1024)*5;
		speedRB=(RC_CtrlData.rc.ch2-1024)*5;
		speedLB=(RC_CtrlData.rc.ch2-1024)*5;
	}
}

void Pos_to_speed(int x,int y)//
{
    Robo_mode=1;
    speedLF=x-y;
	speedRF=-x-y;
	speedRB=-x+y;
	speedLB=x+y;
}

void Arm_Auto_Aim()//机械臂自动对准
{

}

void Arm_Manual_Aim()//机械臂手动对准
{

}

void Arm_Taker()//机械臂夹子
{

}

void Arm_Rotate_1()//机械臂轴旋转
{

}

void Arm_Rotate_2()//机械臂夹子旋转矿石
{

}

void Platfrom_Rise()//平台上升
{

}

void Platfrom_Decline()//平台下降
{

}

void Pusher()//推矿石
{

}

void Car_Carry()//运送矿石到兑换站
{

}

void Car_Back()//返回至矿石处
{

}

