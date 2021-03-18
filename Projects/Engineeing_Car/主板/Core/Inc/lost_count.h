#include "main.h"

enum Lost_Types
{
	Lost_MotorLF,			//0.左前轮
	Lost_MotorLB,			//1.左后轮
	Lost_MotorRF,			//2.右前轮
	Lost_MotorRB,			//3.右后轮
	Lost_ArmClip,			//4.机械臂夹子
	Lost_ArmZ0,			    //5.机械臂Z0
	Lost_ArmZ1,			    //6.机械臂Z1
	Lost_Lead_Screw0,		//7.左电机
	Lost_Lead_Screw1,		//8.右电机
	Lost_Type_Num,
};

#define Lost_Cycle 
{\
	34,\
	4,\
	20,\
	20,\
	20,\
	20,\
}