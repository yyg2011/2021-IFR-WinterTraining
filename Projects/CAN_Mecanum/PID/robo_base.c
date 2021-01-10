//文件名称:		robo_base.c
//对应头文件:	robo_base.h
//主要功能:
//		基于大疆C620的电调与M3508电机封装起来的底盘函数库.
//		能够实现底盘信息的初始化, 电机反馈信息的分析, 与PID控制
//
//时间:
//		2020/11/13
//
//版本:	1.0V

//---------头文件引用部分---------//
#include "robo_base.h"
#include "Remote.h"
//--------------------------------//

//---------变量声明部分-----------//
ROBO_BASE Robo_Base;
CAN_HandleTypeDef hcan2;
float speed;
int Motor_num;
//--------------------------------//

//---------外部变量声明部分-------//
RC_Ctl_t Remote;
extern float speed;
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
void BASE_Init(ROBO_BASE *Robo)       
{
  Speed_System* P_Speed=NULL;      //速度环信息和pid
  P_Speed=&Robo->Speed_MotorLF; PID_Init(&P_Speed->Speed_PID,5,0,0,5000,0,5000,5000); P_Speed->Motor_Num=0;
  P_Speed=&Robo->Speed_MotorRF; PID_Init(&P_Speed->Speed_PID,5,0,0,5000,0,5000,5000); P_Speed->Motor_Num=1;
  P_Speed=&Robo->Speed_MotorRB; PID_Init(&P_Speed->Speed_PID,5,0,0,5000,0,5000,5000); P_Speed->Motor_Num=2;
  P_Speed=&Robo->Speed_MotorLB; PID_Init(&P_Speed->Speed_PID,5,0,0,5000,0,5000,5000); P_Speed->Motor_Num=3;
}



//--------------------------------------------------------------------------------------------------//
//3.获取当前速度环速度数据（speed入口）
//
//函数名称:
//		速度环电机数据分析的接口函数
//
//函数功能:
//		读取Robo_Base对应的CAN口储存的数据, 根据电机号码来分辨是哪一个轮子的信息, 然后储存电机数据.
//
//参数类型:
//		ROBO_BASE 指针, 底盘结构体的指针
//		uint8_t* 电机信息的数组, 推荐使用Rx_CAN变量, 这样可以不需要自己去声明.
//		uint32_t 电机号码
//
//移植建议:
//		直接对case的数据进行修改, 有几个速度环的轮子就加几个, 然后让指针指向对应的轮子就行.
//
//--------------------------------------------------------------------------------------------------//
void Motor_Speed_Analysis(ROBO_BASE* Robo,uint8_t* RX_Data,uint16_t Motor_Num)
{
  Speed_System* S_Motor=NULL;
  switch(Motor_Num)
  {
    case 0x201:S_Motor=&Robo->Speed_MotorLF;break;
    case 0x202:S_Motor=&Robo->Speed_MotorRF;break;
    case 0x203:S_Motor=&Robo->Speed_MotorRB;break;
    case 0x204:S_Motor=&Robo->Speed_MotorLB;break;
	default:break;
	}
	if(S_Motor!=NULL) Motor_Info_Handle(&S_Motor->Info,RX_Data);
}




//--------------------------------------------------------------------------------------------------//
//函数名称:
//		PID参数初始化函数
//
//函数功能:
//		初始化系统PID参数
//
//参数类型:
//		PID* PID指针
//		float PID的Kp
//		float PID的Ki
//		float PID的Kd
//		float 误差最大值
//		float 死区
//		float 误差累积最大值
//		float 输出最大值
//
//--------------------------------------------------------------------------------------------------//
void PID_Init(PID *pid, float Kp, float Ki, float Kd, float error_max, float dead_line, float intergral_max, float output_max)           //参数赋值与初始化
{
	pid->Kp = Kp;                      
	pid->Ki = Ki;
	pid->Kd = Kd;
	pid->error_max = error_max;       //最大误差
	pid->output_max = output_max;         //最大输出
	pid->dead_line = dead_line;          //??
	
	pid->intergral_max = intergral_max;         //积分最大    
	
	pid->error = 0;                  //误差
	pid->error_last = 0;               //上一次误差
	pid->intergral = 0;                //积分
	pid->derivative = 0;              //求导
	pid->output = 0;                  //输出
}


//--------------------------------------------------------------------------------------------------//
//函数名称:
//		PID计算函数
//
//函数功能:
//		进行PID计算
//
//参数类型:
//		PID* PID指针
//		float 当前值
//		float 目标值
//		uint8_t 电机号码
//		uint8_t 发送数据的数组
//
//移植建议:
//		不管封装得怎么样, 建议保留该函数不要修改, 作为向下兼容或者检查错误的函数
//
//--------------------------------------------------------------------------------------------------//
void PID_General_Cal(PID *pid, float fdbV, float tarV,uint8_t moto_num,uint8_t *Tx_msg)
{

	pid->error =  tarV - fdbV;
	if(pid->error > pid->error_max)
		pid->error = pid->error_max;
	if(pid->error < -pid->error_max)
		pid->error = -pid->error_max;
	if(pid->error > 0 && pid->error < pid->dead_line)
		pid->error = 0;
	if(pid->error < 0 && pid->error > pid->dead_line)
		pid->error = 0;
	
	pid->intergral = pid->intergral + pid->error;
	if(pid->intergral > pid->intergral_max)
		pid->intergral = pid->intergral_max;
	if(pid->intergral < -pid->intergral_max)
		pid->intergral = -pid->intergral_max;
	
	pid->derivative = pid->error - pid->error_last;
	pid->error_last = pid->error;
	
	pid->output = pid->Kp*pid->error + pid->Ki*pid->intergral + pid->Kd*pid->derivative;
	
	if(pid->output > pid->output_max)
		pid->output = pid->output_max;
	if(pid->output < -pid->output_max)
		pid->output = -pid->output_max;
	
	Tx_msg[moto_num*2]=((int16_t)pid->output)>>8;Tx_msg[moto_num*2+1]=(int16_t)pid->output;
}



//--------------------------------------------------------------------------------------------------//
//函数名称:
//		速度环PID计算函数
//
//函数功能:
//		进行速度环PID计算
//
//参数类型:
//		Speed_System* 速度环系统指针
//		uint8_t* 发送数据的数组
//
//--------------------------------------------------------------------------------------------------//
void PID_Speed_Cal(Speed_System* Speed_Motor,uint8_t *Tx_msg)
{

	Speed_Motor->Speed_PID.error =  Speed_Motor->Tar_Speed - Speed_Motor->Info.Speed;
	if(Speed_Motor->Speed_PID.error > Speed_Motor->Speed_PID.error_max)
		Speed_Motor->Speed_PID.error = Speed_Motor->Speed_PID.error_max;
	if(Speed_Motor->Speed_PID.error < -Speed_Motor->Speed_PID.error_max)
		Speed_Motor->Speed_PID.error = -Speed_Motor->Speed_PID.error_max;
	if(Speed_Motor->Speed_PID.error > 0 && Speed_Motor->Speed_PID.error < Speed_Motor->Speed_PID.dead_line)
		Speed_Motor->Speed_PID.error = 0;
	if(Speed_Motor->Speed_PID.error < 0 && Speed_Motor->Speed_PID.error > Speed_Motor->Speed_PID.dead_line)
		Speed_Motor->Speed_PID.error = 0;
	
	Speed_Motor->Speed_PID.intergral = Speed_Motor->Speed_PID.intergral + Speed_Motor->Speed_PID.error;
	if(Speed_Motor->Speed_PID.intergral > Speed_Motor->Speed_PID.intergral_max)
		Speed_Motor->Speed_PID.intergral = Speed_Motor->Speed_PID.intergral_max;
	if(Speed_Motor->Speed_PID.intergral < -Speed_Motor->Speed_PID.intergral_max)
		Speed_Motor->Speed_PID.intergral = -Speed_Motor->Speed_PID.intergral_max;
	
	Speed_Motor->Speed_PID.derivative = Speed_Motor->Speed_PID.error - Speed_Motor->Speed_PID.error_last;
	Speed_Motor->Speed_PID.error_last = Speed_Motor->Speed_PID.error;
	
	Speed_Motor->Speed_PID.output = Speed_Motor->Speed_PID.Kp*Speed_Motor->Speed_PID.error + Speed_Motor->Speed_PID.Ki*Speed_Motor->Speed_PID.intergral + Speed_Motor->Speed_PID.Kd*Speed_Motor->Speed_PID.derivative;
	
	if(Speed_Motor->Speed_PID.output > Speed_Motor->Speed_PID.output_max)
		Speed_Motor->Speed_PID.output = Speed_Motor->Speed_PID.output_max;
	if(Speed_Motor->Speed_PID.output < -Speed_Motor->Speed_PID.output_max)
		Speed_Motor->Speed_PID.output = -Speed_Motor->Speed_PID.output_max;
	
	Tx_msg[Speed_Motor->Motor_Num*2] = ((int16_t)Speed_Motor->Speed_PID.output)>>8;
	Tx_msg[Speed_Motor->Motor_Num*2+1] = (int16_t)Speed_Motor->Speed_PID.output;
}



//--------------------------------------------------------------------------------------------------//
//函数名称:
//		//CAN通信发送函数
//
//函数功能:
//		发送数据
//
//参数类型:
//		CAN_HandleTypeDef* CAN的句柄
//		uint8_t* 发送数据的数组
//
//移植建议:
//		根据要求修改标识符就行
//--------------------------------------------------------------------------------------------------//
void Send_To_Motor(CAN_HandleTypeDef *hcan,uint8_t* Tx_Data)
{
  CAN_TxHeaderTypeDef TxHeader;
  uint32_t TxMailbox; 

  TxHeader.RTR = 0;
  TxHeader.IDE = 0;            
  TxHeader.StdId=0x200;
  TxHeader.TransmitGlobalTime = DISABLE;
  TxHeader.DLC = 8;
        
  if (HAL_CAN_AddTxMessage(hcan, &TxHeader, Tx_Data, &TxMailbox) != HAL_OK)
  {
   /* Transmission request Error */
     Error_Handler();
  }
	else
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);
	}
}

void Remote_to_speed(uint8_t Motor_num)//麦克纳姆轮各轮速度控制函数
{
	if (Motor_num==0) speed=((Remote.rc.ch1-1024)-(Remote.rc.ch0-1024))*5;
	else if(Motor_num==1) speed=(-(Remote.rc.ch1-1024)-(Remote.rc.ch0-1024))*5;
	else if(Motor_num==2) speed=(-(Remote.rc.ch1-1024)+(Remote.rc.ch0-1024))*5;
	else if(Motor_num==3) speed=((Remote.rc.ch1-1024)+(Remote.rc.ch0-1024))*5;
}

void Motor_Info_Handle(Motor* Motor,uint8_t* RxData) //电机数据转换函数
{
	Motor->Angle=RxData[0];Motor->Angle<<=8;Motor->Angle|=RxData[1];
	Motor->Speed=RxData[2];Motor->Speed<<=8;Motor->Speed|=RxData[3];
	Motor->Current=RxData[4];Motor->Current<<=8;Motor->Current|=RxData[5];
	Motor->Temperature=RxData[6];
  if(Motor->Speed!=0)
	{
		Motor->Error=Motor->Angle-Motor->Last_Angle;
		Motor->Abs_Angle+=Motor->Error;
		if (Motor->Error < -4096)Motor->Abs_Angle += 8192;
    else if (Motor->Error > 4096)Motor->Abs_Angle -= 8192;
  }
	Motor->Last_Angle=Motor->Angle;
}

void Speed_limit(float speed)//限速函数
{
	if (speed>8000) speed=8000;
	if (speed<-8000) speed=-8000;
}

void Motor_control_process(Speed_System* Motor,uint8_t* TxData)//PID计算过程整合
{
	Remote_to_speed(Motor->Motor_Num);
	Speed_limit(speed);
	Motor->Tar_Speed=speed;
	PID_Speed_Cal(Motor,TxData);
}

void Motor_num_auto_converter(ROBO_BASE* Robo,uint8_t* TxData)//自动跑四个轮子的PID计算
{
	Motor_control_process(&Robo->Speed_MotorLF,TxData);
	Motor_control_process(&Robo->Speed_MotorRF,TxData);
	Motor_control_process(&Robo->Speed_MotorRB,TxData);
	Motor_control_process(&Robo->Speed_MotorLB,TxData);
}


