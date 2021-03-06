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
int pos_x;
int pos_y;
//--------------------------------//

//---------外部变量声明部分-------//
extern RC_Ctl_t RC_CtrlData;
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
  Pos_System* P_Pos=NULL;           //位置环信息和pid
  P_Pos=&Robo->Pos_MotorLF; PID_Init(&P_Pos->Pos_PID,			0.3,	0,	0,	5000,	0,	0,	7000);
  P_Pos->Motor_Num=0;		PID_Init(&P_Pos->Speed_PID,			5,	0,	0,	5000,	0,	0,	7000); 
  P_Pos=&Robo->Pos_MotorRF; PID_Init(&P_Pos->Pos_PID,			0,	0,	0,	0,	0,	0,	0);
  P_Pos->Motor_Num=1;		PID_Init(&P_Pos->Speed_PID,			0,	0,	0,	0,	0,	0,	0); 
  P_Pos=&Robo->Pos_MotorRB; PID_Init(&P_Pos->Pos_PID,			0,	0,	0,	0,	0,	0,	0);
  P_Pos->Motor_Num=2;		PID_Init(&P_Pos->Speed_PID,			0,	0,	0,	0,	0,	0,	0); 
  P_Pos=&Robo->Pos_MotorLB; PID_Init(&P_Pos->Pos_PID,			0,	0,	0,	0,	0,	0,	0);
  P_Pos->Motor_Num=3;		PID_Init(&P_Pos->Speed_PID,			0,	0,	0,	0,	0,	0,	0); 

  Speed_System* P_Speed=NULL;      //速度环信息和pid
  P_Speed=&Robo->Speed_MotorLF; PID_Init(&P_Speed->Speed_PID,5,0,0,5000,0,5000,5000); P_Speed->Motor_Num=0;
  P_Speed=&Robo->Speed_MotorRF; PID_Init(&P_Speed->Speed_PID,5,0,0,5000,0,5000,5000); P_Speed->Motor_Num=1;
  P_Speed=&Robo->Speed_MotorRB; PID_Init(&P_Speed->Speed_PID,5,0,0,5000,0,5000,5000); P_Speed->Motor_Num=2;
  P_Speed=&Robo->Speed_MotorLB; PID_Init(&P_Speed->Speed_PID,5,0,0,5000,0,5000,5000); P_Speed->Motor_Num=3;
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
void Motor_Pos_Analysis(ROBO_BASE* Robo,uint8_t* RX_Data,uint32_t Motor_Num)
{
  Pos_System* P_Motor=NULL;
  switch(Motor_Num)
  {
    case 0x201:P_Motor=&Robo->Pos_MotorLF;break;
    case 0x202:P_Motor=&Robo->Pos_MotorRF;break;
    case 0x203:P_Motor=&Robo->Pos_MotorRB;break;
    case 0x204:P_Motor=&Robo->Pos_MotorLB;break;
	default:break;
  }if(P_Motor!=NULL) Motor_Info_Handle(&P_Motor->Info,RX_Data);
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
//		位置环电机数据分析的操作函数
//
//函数功能:
//		根据数据传进来的数据进行解析, 并且计算出绝对角度和相对角度.
//		默认通信协议内容:  	Data[0]----电机速度高8位
//							Data[1]----电机速度低8位
//							Data[2]----转子角度高8位
//							Data[3]----转子角度低8位
//							Data[4]----电流大小高8位
//							Data[5]----电流大小低8位
//							Data[6]----温度
//							Data[7]----NULL
//
//参数类型:
//		Motor_Pos_Info* 位置环电机信息指针
//		uint8_t* 电机信息的数组
//
//移植建议:
//		大框架不需要改, 要改的话, 信息解析的地方根据通信协议来改就行.
//--------------------------------------------------------------------------------------------------//
void Pos_Info_Analysis(Motor_Pos_Info* Motor,uint8_t* RX_Data)
{
  //数据解析
  Motor->Angle=(uint16_t)RX_Data[0]<<8|RX_Data[1];
  Motor->Speed=(uint16_t)RX_Data[2]<<8|RX_Data[3];
  Motor->Electric=(uint16_t)RX_Data[4]<<8|RX_Data[5];
  Motor->Temperature=RX_Data[6];

  //绝对角度计算
  if (Motor->Speed!=0)
  {
    int16_t Error=Motor->Angle-Motor->Last_Angle;
    Motor->Abs_Angle += Error;
    if (Error < -4096)Motor->Abs_Angle += 8192;
    else if (Error > 4096)  Motor->Abs_Angle -= 8192;
  }Motor->Last_Angle=Motor->Angle;

  //相对角度计算, 默认范围0-360
  if(Motor->Abs_Angle>=0) Motor->Relative_Angle=(Motor->Abs_Angle%ONE_CIRCLE)*360.0/ONE_CIRCLE;
  else Motor->Relative_Angle=360-((-Motor->Abs_Angle)%ONE_CIRCLE)*360.0/ONE_CIRCLE;
}


//--------------------------------------------------------------------------------------------------//
//函数名称:
//		速度环电机数据分析的操作函数
//
//函数功能:
//		根据数据传进来的数据进行解析.
//		默认通信协议内容:  	Data[0]----电机速度高8位
//							Data[1]----电机速度低8位
//							Data[2]----转子角度高8位
//							Data[3]----转子角度低8位
//							Data[4]----电流大小高8位
//							Data[5]----电流大小低8位
//							Data[6]----温度
//							Data[7]----NULL
//
//参数类型:
//		Motor_Speed_Info* 速度环电机信息指针
//		uint8_t* 电机信息的数组
//
//移植建议:
//		大框架不需要改, 要改的话, 信息解析的地方根据通信协议来改就行.
//--------------------------------------------------------------------------------------------------//
void Speed_Info_Analysis(Motor_Speed_Info* Motor,uint8_t* RX_Data)
{
  Motor->Speed=(uint16_t)RX_Data[2]<<8|RX_Data[3];
  Motor->Electric=(uint16_t)RX_Data[4]<<8|RX_Data[5];
  Motor->Temperature=RX_Data[6];
}

//--------------------------------------------------------------------------------------------------//
//函数名称:
//		位置环PID计算函数
//
//函数功能:
//		进行位置环PID计算
//
//参数类型:
//		Pos_System* 位置环系统指针
//		uint8_t* 发送数据的数组
//
//--------------------------------------------------------------------------------------------------//
void PID_Pos_Cal(Pos_System* Pos_Motor,uint8_t *Tx_msg)       
{
	Pos_Motor->Pos_PID.error =  Pos_Motor->Tar_Pos - Pos_Motor->Info.Abs_Angle;
	if(Pos_Motor->Pos_PID.error > Pos_Motor->Pos_PID.error_max)
		Pos_Motor->Pos_PID.error = Pos_Motor->Pos_PID.error_max;
	if(Pos_Motor->Pos_PID.error < -Pos_Motor->Pos_PID.error_max)
		Pos_Motor->Pos_PID.error = -Pos_Motor->Pos_PID.error_max;
	if(Pos_Motor->Pos_PID.error > 0 && Pos_Motor->Pos_PID.error < Pos_Motor->Pos_PID.dead_line)
		Pos_Motor->Pos_PID.error = 0;
	if(Pos_Motor->Pos_PID.error < 0 && Pos_Motor->Pos_PID.error > Pos_Motor->Pos_PID.dead_line)
		Pos_Motor->Pos_PID.error = 0;
	
	Pos_Motor->Pos_PID.intergral = Pos_Motor->Pos_PID.intergral + Pos_Motor->Pos_PID.error;
	if(Pos_Motor->Pos_PID.intergral > Pos_Motor->Pos_PID.intergral_max)
		Pos_Motor->Pos_PID.intergral = Pos_Motor->Pos_PID.intergral_max;
	if(Pos_Motor->Pos_PID.intergral < -Pos_Motor->Pos_PID.intergral_max)
		Pos_Motor->Pos_PID.intergral = -Pos_Motor->Pos_PID.intergral_max;
	
	Pos_Motor->Pos_PID.derivative = Pos_Motor->Pos_PID.error - Pos_Motor->Pos_PID.error_last;
	Pos_Motor->Pos_PID.error_last = Pos_Motor->Pos_PID.error;
	
	Pos_Motor->Pos_PID.output = Pos_Motor->Pos_PID.Kp*Pos_Motor->Pos_PID.error + Pos_Motor->Pos_PID.Ki*Pos_Motor->Pos_PID.intergral + Pos_Motor->Pos_PID.Kd*Pos_Motor->Pos_PID.derivative;
	
	if(Pos_Motor->Pos_PID.output > Pos_Motor->Pos_PID.output_max)
		Pos_Motor->Pos_PID.output = Pos_Motor->Pos_PID.output_max;
	if(Pos_Motor->Pos_PID.output < -Pos_Motor->Pos_PID.output_max)
		Pos_Motor->Pos_PID.output = -Pos_Motor->Pos_PID.output_max;
	
		Pos_Motor->Speed_PID.error =  Pos_Motor->Pos_PID.output - Pos_Motor->Info.Speed;
	if(Pos_Motor->Speed_PID.error > Pos_Motor->Speed_PID.error_max)
		Pos_Motor->Speed_PID.error = Pos_Motor->Speed_PID.error_max;
	if(Pos_Motor->Speed_PID.error < -Pos_Motor->Speed_PID.error_max)
		Pos_Motor->Speed_PID.error = -Pos_Motor->Speed_PID.error_max;
	if(Pos_Motor->Speed_PID.error > 0 && Pos_Motor->Speed_PID.error < Pos_Motor->Speed_PID.dead_line)
		Pos_Motor->Speed_PID.error = 0;
	if(Pos_Motor->Speed_PID.error < 0 && Pos_Motor->Speed_PID.error > Pos_Motor->Speed_PID.dead_line)
		Pos_Motor->Speed_PID.error = 0;
	
	Pos_Motor->Speed_PID.intergral = Pos_Motor->Speed_PID.intergral + Pos_Motor->Speed_PID.error;
	if(Pos_Motor->Speed_PID.intergral > Pos_Motor->Speed_PID.intergral_max)
		Pos_Motor->Speed_PID.intergral = Pos_Motor->Speed_PID.intergral_max;
	if(Pos_Motor->Speed_PID.intergral < -Pos_Motor->Speed_PID.intergral_max)
		Pos_Motor->Speed_PID.intergral = -Pos_Motor->Speed_PID.intergral_max;
	
	Pos_Motor->Speed_PID.derivative = Pos_Motor->Speed_PID.error - Pos_Motor->Speed_PID.error_last;
	Pos_Motor->Speed_PID.error_last = Pos_Motor->Speed_PID.error;
	
	Pos_Motor->Speed_PID.output = Pos_Motor->Speed_PID.Kp*Pos_Motor->Speed_PID.error + Pos_Motor->Speed_PID.Ki*Pos_Motor->Speed_PID.intergral + Pos_Motor->Speed_PID.Kd*Pos_Motor->Speed_PID.derivative;
	
	if(Pos_Motor->Speed_PID.output > Pos_Motor->Speed_PID.output_max)
		Pos_Motor->Speed_PID.output = Pos_Motor->Speed_PID.output_max;
	if(Pos_Motor->Speed_PID.output < -Pos_Motor->Speed_PID.output_max)
		Pos_Motor->Speed_PID.output = -Pos_Motor->Speed_PID.output_max;
	
	Pos_Motor->Motor_Num=2;

	
	Tx_msg[Pos_Motor->Motor_Num*2]=((int16_t)Pos_Motor->Speed_PID.output)>>8;Tx_msg[Pos_Motor->Motor_Num*2+1]=(int16_t)Pos_Motor->Speed_PID.output;
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

void Motor_speed_control_process(Speed_System* Motor,uint8_t* TxData)//PID计算过程整合
{
	Remote_to_speed(Motor->Motor_Num);
	Speed_limit(speed);
	Motor->Tar_Speed=speed;
	PID_Speed_Cal(Motor,TxData);
}

void Motor_pos_control_process(Pos_System* Motor,uint8_t* TxData)
{
    Pos_to_speed(Motor->Motor_Num,pos_x,pos_y);
    Motor->Tar_Pos=speed;
    PID_Pos_Cal(Motor,TxData);
}

void Motor_num_auto_converter(ROBO_BASE* Robo,uint8_t* TxData,int mode)//自动跑四个轮子的PID计算
{
    if (mode==0)
    {
        Motor_speed_control_process(&Robo->Speed_MotorLF,TxData);
        Motor_speed_control_process(&Robo->Speed_MotorRF,TxData);
        Motor_speed_control_process(&Robo->Speed_MotorRB,TxData);
        Motor_speed_control_process(&Robo->Speed_MotorLB,TxData);
    }
    else if (mode==1)
    {
        Motor_pos_control_process(&Robo->Pos_MotorLF,TxData);
        Motor_pos_control_process(&Robo->Pos_MotorRF,TxData);
        Motor_pos_control_process(&Robo->Pos_MotorRB,TxData);
        Motor_pos_control_process(&Robo->Pos_MotorLB,TxData);
    }
}


