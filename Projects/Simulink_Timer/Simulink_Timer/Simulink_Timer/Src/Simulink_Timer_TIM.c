/*
 * File: Simulink_Timer_TIM.c
 *
 * Code generated for Simulink model :Simulink_Timer.
 *
 * Model version      : 1.4
 * Simulink Coder version    : 9.0 (R2018b) 24-May-2018
 * TLC version       : 9.0 (Aug 22 2018)
 * C/C++ source code generated on  : Fri Jan 15 16:12:16 2021
 *
 * Target selection: stm32.tlc
 * Embedded hardware selection: STM32CortexM
 * Code generation objectives: Unspecified
 * Validation result: Not run
 *
 *
 *
 * ******************************************************************************
 * * attention
 * *
 * * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * *
 * ******************************************************************************
 */

#include "Simulink_Timer.h"
#include "Simulink_Timer_TIM.h"

/* Number of configured TIMER. */
uint16_t G_TIM_Count = 0;

/* Array of TIMER information. */
TIM_ConfTypeDef* G_TIM_Conf[1];
TIM_HandleTypeDef* G_TIM_Handler[1];

/* TIM6 informations. */
TIM_ConfTypeDef TIM6_Conf;

/* TIM6 polling timeout value. Number of Solver loop. (can be changed). */
uint32_t G_TIM6_PollTimeOut = 10;

/*******************************************************************************
 * Function Name  : TIM_PeriodElapsedCustomCallback
 * Description    : Timer callback for update event
 * Input          : TIM_HandleTypeDef*   TIM IC handle
 *******************************************************************************/
void TIM_PeriodElapsedCustomCallback(TIM_HandleTypeDef *htim)
{
  TIM_ConfTypeDef * pConf = G_TIM_Conf[0];
  TIM_HandleTypeDef* pHandler = G_TIM_Handler[0];
  if (pHandler == htim) {
    if (pConf->ItUpFcn != NULL) {
      /* Call update function for TIM6. */
      pConf->ItUpFcn();
    }
  }
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  extern void TIM_PeriodElapsedCustomCallback(TIM_HandleTypeDef *htim);

  /* Handle this event from model side. */
  TIM_PeriodElapsedCustomCallback(htim);
}

/*******************************************************************************
 * Function Name  : TIM6_ItUpFcn
 * Description    : TIM6 update interrupt
 * Input          : None
 * TIM6_ItUpFcn is called from TIM_PeriodElapsedCustomCallback function
 * in Simulink_Timer_TIM.c file.
 *******************************************************************************/
void TIM6_ItUpFcn()
{
  {
    /* Output and update for function-call system: '<Root>/Function-Call Subsystem' */
    if (Simulink_Timer_DW.Output_DSTATE == 500) {
      {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
      }
    }

    Simulink_Timer_DW.Output_DSTATE++;
    if (Simulink_Timer_DW.Output_DSTATE > 500) {
      Simulink_Timer_DW.Output_DSTATE = 0U;
    }
  }
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] Simulink_Timer_TIM.c
 */
