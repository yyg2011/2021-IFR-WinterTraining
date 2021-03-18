typedef enum 
{
    Prepare_State,      //0.准备
    Check_State,        //1.自检
    Manual_Take_State,  //2.手动取弹
    Auto_Take_State,    //3.自动取弹
    Carry_State,        //4.运输矿石
    Auto_Lay_State,     //5.兑换矿石
    Back_State,         //6.返回矿石区
    Lost_Stete,         //7.硬件丢失
    Finish_State,       //8.完成
    Break_State         //9.遇错停止
    Wait_State          //10.等待矿石下落
}Work_State;

void SetWorkState(Work_State state);
void MainProgram(Work_State state);
