#include "main.h"

enum Lost_Types
{
	Lost_MotorLF,			//0.��ǰ��
	Lost_MotorLB,			//1.�����
	Lost_MotorRF,			//2.��ǰ��
	Lost_MotorRB,			//3.�Һ���
	Lost_ArmClip,			//4.��е�ۼ���
	Lost_ArmZ0,			    //5.��е��Z0
	Lost_ArmZ1,			    //6.��е��Z1
	Lost_Lead_Screw0,		//7.����
	Lost_Lead_Screw1,		//8.�ҵ��
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