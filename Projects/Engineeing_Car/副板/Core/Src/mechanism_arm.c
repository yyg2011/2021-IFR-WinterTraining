//---------头文件引用部分---------//
#include "robo_base.h"
#include "mechanism_arm.h"
//--------------------------------//

//---------变量声明部分-----------//
ROBO_BASE Robo_Base;
CAN_HandleTypeDef hcan2;
float speed;
int Motor_num;
int pos_x;
int pos_y;
//--------------------------------//

//---------外部变量声明部分-------//
extern float speed;
extern int speedLF,speedRF,speedRB,speedLB,Robo_mode;
//--------------------------------//

/**********************************************************电机pid控制系统****************************************************************************************************/
//--------------------------------------------------------------------------------------------------//
//1.初始化底盘
//
//函数名称:
//		底盘参数初始化
//
//函数功能:
//		初始化底盘所有的信息
//
//参数类型:
//		ROBO_BASE 指针, 底盘结构体的指针
//
//移植建议:
//		有什么状态, 电机, 电机状态都先把数据封装进ROBO_BASE结构体里, 然后直接初始化就好了
//
//--------------------------------------------------------------------------------------------------//
void ARM_BASE_Init(ROBO_BASE *Robo)       
{
  Pos_System* P_Pos=NULL;           //位置环信息和pid
  P_Pos=&Robo->Pos_ArmX; PID_Init(&P_Pos->Pos_PID,			0.3,	0,	0,	5000,	0,	0,	7000);
  P_Pos->Motor_Num=4;		PID_Init(&P_Pos->Speed_PID,			5,	0,	0,	5000,	0,	0,	7000); 
  P_Pos=&Robo->Pos_ArmY; PID_Init(&P_Pos->Pos_PID,			0,	0,	0,	0,	0,	0,	0);
  P_Pos->Motor_Num=5;		PID_Init(&P_Pos->Speed_PID,			0,	0,	0,	0,	0,	0,	0); 
  P_Pos=&Robo->Pos_ArmClip; PID_Init(&P_Pos->Pos_PID,			0,	0,	0,	0,	0,	0,	0);
  P_Pos->Motor_Num=6;		PID_Init(&P_Pos->Speed_PID,			0,	0,	0,	0,	0,	0,	0); 
  P_Pos=&Robo->Pos_ArmZ0; PID_Init(&P_Pos->Pos_PID,			0,	0,	0,	0,	0,	0,	0);
  P_Pos->Motor_Num=7;		PID_Init(&P_Pos->Speed_PID,			0,	0,	0,	0,	0,	0,	0); 
  P_Pos=&Robo->Pos_ArmZ1; PID_Init(&P_Pos->Pos_PID,			0,	0,	0,	0,	0,	0,	0);
  P_Pos->Motor_Num=8;		PID_Init(&P_Pos->Speed_PID,			0,	0,	0,	0,	0,	0,	0); 
}

//--------------------------------------------------------------------------------------------------//
//2.获取当前位置环位置与速度数据（pos入口）


//函数名称:
//		位置环电机数据分析的接口函数

//函数功能:
//		读取Robo_Base对应的CAN口储存的数据, 根据电机号码来分辨是哪一个轮子的信息, 然后储存电机数据.

//参数类型:
//		ROBO_BASE 指针, 底盘结构体的指针
//		uint8_t* 电机信息的数组, 推荐使用Rx_CAN变量, 这样可以不需要自己去声明.
//		uint32_t 电机号码

//移植建议:
//		直接对case的数据进行修改, 有几个位置环的轮子就加几个, 然后让指针指向对应的轮子就行.

//--------------------------------------------------------------------------------------------------//
void Arm_Pos_Analysis(ROBO_BASE* Robo,uint8_t* RX_Data,uint32_t Motor_Num)
{
  Pos_System* P_Motor=NULL;
  switch(Motor_Num)
  {
    case 0x204:P_Motor=&Robo->Pos_ArmX;break;
    case 0x205:P_Motor=&Robo->Pos_ArmY;break;
    case 0x206:P_Motor=&Robo->Pos_ArmClip;break;
    case 0x207:P_Motor=&Robo->Pos_ArmZ0;break;
    case 0x208:P_Motor=&Robo->Pos_ArmZ1;break;
	default:break;
  }if(P_Motor!=NULL) Motor_Info_Handle(&P_Motor->Info,RX_Data);
}

void Arm_pos_control_process(Pos_System* Motor,uint8_t* TxData)
{
    Remote_to_speed(Motor->Motor_Num);
    Motor->Tar_Pos=speed;
    PID_Speed_Cal(Motor,TxData);
}

void Arm_num_auto_converter(ROBO_BASE* Robo,uint8_t* TxData)//自动跑五个电机的PID计算
{
    Arm_pos_control_process(&Robo->Pos_ArmX,TxData);
    Arm_pos_control_process(&Robo->Pos_ArmY,TxData);
    Arm_pos_control_process(&Robo->Pos_ArmClip,TxData);
    Arm_pos_control_process(&Robo->Pos_ArmZ0,TxData);
    Arm_pos_control_process(&Robo->Pos_ArmZ1,TxData);
}


