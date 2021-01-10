//�ļ�����:		robo_base.c
//��Ӧͷ�ļ�:	robo_base.h
//��Ҫ����:
//		���ڴ�C620�ĵ����M3508�����װ�����ĵ��̺�����.
//		�ܹ�ʵ�ֵ�����Ϣ�ĳ�ʼ��, ���������Ϣ�ķ���, ��PID����
//
//ʱ��:
//		2020/11/13
//
//�汾:	1.0V

//---------ͷ�ļ����ò���---------//
#include "robo_base.h"
#include "Remote.h"
//--------------------------------//

//---------������������-----------//
ROBO_BASE Robo_Base;
CAN_HandleTypeDef hcan2;
float speed;
int Motor_num;
//--------------------------------//

//---------�ⲿ������������-------//
RC_Ctl_t Remote;
extern float speed;
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
void BASE_Init(ROBO_BASE *Robo)       
{
  Speed_System* P_Speed=NULL;      //�ٶȻ���Ϣ��pid
  P_Speed=&Robo->Speed_MotorLF; PID_Init(&P_Speed->Speed_PID,5,0,0,5000,0,5000,5000); P_Speed->Motor_Num=0;
  P_Speed=&Robo->Speed_MotorRF; PID_Init(&P_Speed->Speed_PID,5,0,0,5000,0,5000,5000); P_Speed->Motor_Num=1;
  P_Speed=&Robo->Speed_MotorRB; PID_Init(&P_Speed->Speed_PID,5,0,0,5000,0,5000,5000); P_Speed->Motor_Num=2;
  P_Speed=&Robo->Speed_MotorLB; PID_Init(&P_Speed->Speed_PID,5,0,0,5000,0,5000,5000); P_Speed->Motor_Num=3;
}



//--------------------------------------------------------------------------------------------------//
//3.��ȡ��ǰ�ٶȻ��ٶ����ݣ�speed��ڣ�
//
//��������:
//		�ٶȻ�������ݷ����Ľӿں���
//
//��������:
//		��ȡRobo_Base��Ӧ��CAN�ڴ��������, ���ݵ���������ֱ�����һ�����ӵ���Ϣ, Ȼ�󴢴�������.
//
//��������:
//		ROBO_BASE ָ��, ���̽ṹ���ָ��
//		uint8_t* �����Ϣ������, �Ƽ�ʹ��Rx_CAN����, �������Բ���Ҫ�Լ�ȥ����.
//		uint32_t �������
//
//��ֲ����:
//		ֱ�Ӷ�case�����ݽ����޸�, �м����ٶȻ������ӾͼӼ���, Ȼ����ָ��ָ���Ӧ�����Ӿ���.
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
//��������:
//		PID������ʼ������
//
//��������:
//		��ʼ��ϵͳPID����
//
//��������:
//		PID* PIDָ��
//		float PID��Kp
//		float PID��Ki
//		float PID��Kd
//		float ������ֵ
//		float ����
//		float ����ۻ����ֵ
//		float ������ֵ
//
//--------------------------------------------------------------------------------------------------//
void PID_Init(PID *pid, float Kp, float Ki, float Kd, float error_max, float dead_line, float intergral_max, float output_max)           //������ֵ���ʼ��
{
	pid->Kp = Kp;                      
	pid->Ki = Ki;
	pid->Kd = Kd;
	pid->error_max = error_max;       //������
	pid->output_max = output_max;         //������
	pid->dead_line = dead_line;          //??
	
	pid->intergral_max = intergral_max;         //�������    
	
	pid->error = 0;                  //���
	pid->error_last = 0;               //��һ�����
	pid->intergral = 0;                //����
	pid->derivative = 0;              //��
	pid->output = 0;                  //���
}


//--------------------------------------------------------------------------------------------------//
//��������:
//		PID���㺯��
//
//��������:
//		����PID����
//
//��������:
//		PID* PIDָ��
//		float ��ǰֵ
//		float Ŀ��ֵ
//		uint8_t �������
//		uint8_t �������ݵ�����
//
//��ֲ����:
//		���ܷ�װ����ô��, ���鱣���ú�����Ҫ�޸�, ��Ϊ���¼��ݻ��߼�����ĺ���
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
//��������:
//		�ٶȻ�PID���㺯��
//
//��������:
//		�����ٶȻ�PID����
//
//��������:
//		Speed_System* �ٶȻ�ϵͳָ��
//		uint8_t* �������ݵ�����
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
//��������:
//		//CANͨ�ŷ��ͺ���
//
//��������:
//		��������
//
//��������:
//		CAN_HandleTypeDef* CAN�ľ��
//		uint8_t* �������ݵ�����
//
//��ֲ����:
//		����Ҫ���޸ı�ʶ������
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

void Remote_to_speed(uint8_t Motor_num)//�����ķ�ָ����ٶȿ��ƺ���
{
	if (Motor_num==0) speed=((Remote.rc.ch1-1024)-(Remote.rc.ch0-1024))*5;
	else if(Motor_num==1) speed=(-(Remote.rc.ch1-1024)-(Remote.rc.ch0-1024))*5;
	else if(Motor_num==2) speed=(-(Remote.rc.ch1-1024)+(Remote.rc.ch0-1024))*5;
	else if(Motor_num==3) speed=((Remote.rc.ch1-1024)+(Remote.rc.ch0-1024))*5;
}

void Motor_Info_Handle(Motor* Motor,uint8_t* RxData) //�������ת������
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

void Speed_limit(float speed)//���ٺ���
{
	if (speed>8000) speed=8000;
	if (speed<-8000) speed=-8000;
}

void Motor_control_process(Speed_System* Motor,uint8_t* TxData)//PID�����������
{
	Remote_to_speed(Motor->Motor_Num);
	Speed_limit(speed);
	Motor->Tar_Speed=speed;
	PID_Speed_Cal(Motor,TxData);
}

void Motor_num_auto_converter(ROBO_BASE* Robo,uint8_t* TxData)//�Զ����ĸ����ӵ�PID����
{
	Motor_control_process(&Robo->Speed_MotorLF,TxData);
	Motor_control_process(&Robo->Speed_MotorRF,TxData);
	Motor_control_process(&Robo->Speed_MotorRB,TxData);
	Motor_control_process(&Robo->Speed_MotorLB,TxData);
}


