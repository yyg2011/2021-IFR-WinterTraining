#include "main.h"
#include "whell_control.h"
#include "communicate.h"
#include "Remote.h"

int speedLF,speedRF,speedRB,speedLB,Robo_mode;
extern RC_Ctl_t RC_CtrlData;

void Remote_to_speed()//�����ķ�ָ����ٶȿ��ƺ���
{
    Robo_mode=0;
	if(RC_CtrlData.rc.ch2==1024)//ƽ��
	{
		speedLF=((RC_CtrlData.rc.ch1-1024)-(RC_CtrlData.rc.ch0-1024))*5;
		speedRF=(-(RC_CtrlData.rc.ch1-1024)-(RC_CtrlData.rc.ch0-1024))*5;
		speedRB=(-(RC_CtrlData.rc.ch1-1024)+(RC_CtrlData.rc.ch0-1024))*5;
		speedLB=((RC_CtrlData.rc.ch1-1024)+(RC_CtrlData.rc.ch0-1024))*5;
	}
	else//��ת
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

