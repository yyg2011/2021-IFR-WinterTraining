//---------ͷ�ļ����ò���---------//
#include "robo_base.h"
#include "mechanism_arm.h"
//--------------------------------//

//---------������������-----------//
ROBO_BASE Robo_Base;
CAN_HandleTypeDef hcan2;
float speed;
int Motor_num;
int pos_x;
int pos_y;
//--------------------------------//

//---------�ⲿ������������-------//
extern float speed;
extern int speedLF,speedRF,speedRB,speedLB,Robo_mode;
//--------------------------------//

/**********************************************************���pid����ϵͳ****************************************************************************************************/
//--------------------------------------------------------------------------------------------------//
//1.��ʼ������
//
//��������:
//		���̲�����ʼ��
//
//��������:
//		��ʼ���������е���Ϣ
//
//��������:
//		ROBO_BASE ָ��, ���̽ṹ���ָ��
//
//��ֲ����:
//		��ʲô״̬, ���, ���״̬���Ȱ����ݷ�װ��ROBO_BASE�ṹ����, Ȼ��ֱ�ӳ�ʼ���ͺ���
//
//--------------------------------------------------------------------------------------------------//
void ARM_BASE_Init(ROBO_BASE *Robo)       
{
  Pos_System* P_Pos=NULL;           //λ�û���Ϣ��pid
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
//2.��ȡ��ǰλ�û�λ�����ٶ����ݣ�pos��ڣ�


//��������:
//		λ�û�������ݷ����Ľӿں���

//��������:
//		��ȡRobo_Base��Ӧ��CAN�ڴ��������, ���ݵ���������ֱ�����һ�����ӵ���Ϣ, Ȼ�󴢴�������.

//��������:
//		ROBO_BASE ָ��, ���̽ṹ���ָ��
//		uint8_t* �����Ϣ������, �Ƽ�ʹ��Rx_CAN����, �������Բ���Ҫ�Լ�ȥ����.
//		uint32_t �������

//��ֲ����:
//		ֱ�Ӷ�case�����ݽ����޸�, �м���λ�û������ӾͼӼ���, Ȼ����ָ��ָ���Ӧ�����Ӿ���.

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

void Arm_num_auto_converter(ROBO_BASE* Robo,uint8_t* TxData)//�Զ�����������PID����
{
    Arm_pos_control_process(&Robo->Pos_ArmX,TxData);
    Arm_pos_control_process(&Robo->Pos_ArmY,TxData);
    Arm_pos_control_process(&Robo->Pos_ArmClip,TxData);
    Arm_pos_control_process(&Robo->Pos_ArmZ0,TxData);
    Arm_pos_control_process(&Robo->Pos_ArmZ1,TxData);
}


