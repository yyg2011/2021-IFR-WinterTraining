typedef enum 
{
    Prepare_State,      //0.׼��
    Check_State,        //1.�Լ�
    Manual_Take_State,  //2.�ֶ�ȡ��
    Auto_Take_State,    //3.�Զ�ȡ��
    Carry_State,        //4.�����ʯ
    Auto_Lay_State,     //5.�һ���ʯ
    Back_State,         //6.���ؿ�ʯ��
    Lost_Stete,         //7.Ӳ����ʧ
    Finish_State,       //8.���
    Break_State         //9.����ֹͣ
    Wait_State          //10.�ȴ���ʯ����
}Work_State;

void SetWorkState(Work_State state);
void MainProgram(Work_State state);
