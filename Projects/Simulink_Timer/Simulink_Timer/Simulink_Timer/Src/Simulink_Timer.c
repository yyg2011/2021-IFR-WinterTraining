/*
 * File: Simulink_Timer.c
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
#include "Simulink_Timer_private.h"

/* Block states (default storage) */
DW_Simulink_Timer Simulink_Timer_DW;

/* Real-time model */
RT_MODEL_Simulink_Timer Simulink_Timer_M_;
RT_MODEL_Simulink_Timer *const Simulink_Timer_M = &Simulink_Timer_M_;

/* Model step function */
void Simulink_Timer_step(void)
{
  {
  }
}

/* Model initialize function */
void Simulink_Timer_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Simulink_Timer_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&Simulink_Timer_DW, 0,
                sizeof(DW_Simulink_Timer));

  {
    /* user code (Start function Header) */
    {
      /* TIM6 initialization. */
      /* Store TIM6 informations and its handler. */
      G_TIM_Conf[G_TIM_Count] = &TIM6_Conf;
      G_TIM_Handler[G_TIM_Count] = &htim6;

      /* Store TIM information. */
      TIM6_Conf.TIM_Prescaler = 83;
      TIM6_Conf.TIM_APBClock = 16000000;
      TIM6_Conf.TIM_ARR = 1 - 1;
      TIM6_Conf.TIM_Clock = 190476.19;
      TIM6_Conf.TIM_Freq = 190476.19;
      TIM6_Conf.CH1_duty = 0.0;
      TIM6_Conf.CH2_duty = 0.0;
      TIM6_Conf.CH3_duty = 0.0;
      TIM6_Conf.CH4_duty = 0.0;
      TIM6_Conf.CH1_type = UNKNOWN;
      TIM6_Conf.CH2_type = UNKNOWN;
      TIM6_Conf.CH3_type = UNKNOWN;
      TIM6_Conf.CH4_type = UNKNOWN;

      /* Interrupt handler default initialization. */
      TIM6_Conf.ItUpFcn = NULL;
      TIM6_Conf.ItTrgFcn = NULL;
      TIM6_Conf.ItComFcn = NULL;
      TIM6_Conf.ItBrkFcn = NULL;
      TIM6_Conf.ItCcFcn = NULL;

      /* Update interrupt function. */
      TIM6_Conf.ItUpFcn = TIM6_ItUpFcn;

      /* Auto-reload preload enable */
      /*****Bugzilla 63376 *****/
      /*SET_BIT((&htim6)->Instance->CR1,TIM_CR1_ARPE);*/

      /* Update register value with blockset value. */
      /* Prescaler. */
      __HAL_TIM_SET_PRESCALER(&htim6,TIM6_Conf.TIM_Prescaler);

      /* Autoreload: ARR. */
      __HAL_TIM_SET_AUTORELOAD(&htim6,1 - 1);

      /* Update registers before start operation to come. */
      HAL_TIM_GenerateEvent(&htim6,TIM_EVENTSOURCE_UPDATE);
    }

    /* user code (Start function Body) */
    {
      /* TIM6 Start. */
      /* Starts the TIM Base generation in interrupt mode. */
      HAL_TIM_Base_Start_IT(&htim6);

      /* Start interrupt for Update event*/
      HAL_TIM_Base_Start_IT(&htim6);
    }
  }
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] Simulink_Timer.c
 */
