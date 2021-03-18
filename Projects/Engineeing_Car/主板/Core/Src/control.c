#include "main.h"
#include "control.h"
#include "whell_control.h"
#include "time_counter.h"
#include "lost_count.h"
#include "communicate.h"
#include "photoelectric_sensor.h"
#include "gy53_iic.h"

int Completed=0;
Work_State Correct_State=Check_State;

void SetWorkState(Work_State state)			//¼ÇÂ¼×´Ì¬
{
    Correct_State = state;
}

void MainProgram(Work_State state)
{
    if(state==Check_State)
    {
        
        SetWorkState(Auto_Take_State);
    }
    if(state==Manual_Take_State)
    {
        Arm_Manual_Aim();
        SetWorkState(Carry_State);
    }
    if(state==Auto_Take_State)
    {
        Arm_Auto_Aim();
        Arm_Taker();
        Arm_Rotate_1();
        Arm_Rotate_2();
        SetWorkState(Carry_State);
    }
    if(state==Carry_State)
    {
        
        SetWorkState(Auto_Lay_State);
    }
    if(state==Auto_Lay_State)
    {
        Completed++;
        SetWorkState(Back_State);
    }
    if(state==Back_State)
    {
        
        SetWorkState(Auto_Take_State);
    }
    if(state==Wait_State)
    {
        
        
    }
    if(state==Finish_State)
    {
        
        
    }
}
