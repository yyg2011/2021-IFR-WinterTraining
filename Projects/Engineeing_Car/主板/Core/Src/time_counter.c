#include "tim.h"
#include "time_counter.h"
#include "control.h"
#include "main.h"

int one_min_count=0;
extern Work_State Correct_State;
extern int Completed;

void ResetTimer()
{
    HAL_TIM_Base_Stop(&htim3);
    __HAL_TIM_SetCounter(&htim3,0);
    one_min_count=0;
}

void StartTimer()
{
    one_min_count=0;
    __HAL_TIM_CLEAR_FLAG(&htim3,TIM_FLAG_UPDATE);
    HAL_TIM_Base_Start_IT(&htim3);
}

void CheckTimer()
{
    if (Correct_State==Back_State)
    {
        if (one_min_count==0|Completed==2) Correct_State=Wait_State;
        else if(Completed==5) Correct_State=Finish_State;
    }
    if (Correct_State==Wait_State)
    {
        if (one_min_count==1) Correct_State=Auto_Take_State;
        else Correct_State=Wait_State;
    }
}