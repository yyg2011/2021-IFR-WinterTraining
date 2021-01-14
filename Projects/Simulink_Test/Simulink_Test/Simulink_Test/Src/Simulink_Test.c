/*
 * File: Simulink_Test.c
 *
 * Code generated for Simulink model :Simulink_Test.
 *
 * Model version      : 1.2
 * Simulink Coder version    : 9.0 (R2018b) 24-May-2018
 * TLC version       : 9.0 (Aug 22 2018)
 * C/C++ source code generated on  : Thu Jan 14 21:14:32 2021
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

#include "Simulink_Test.h"
#include "Simulink_Test_private.h"

/* Block signals (default storage) */
B_Simulink_Test Simulink_Test_B;

/* Block states (default storage) */
DW_Simulink_Test Simulink_Test_DW;

/* Real-time model */
RT_MODEL_Simulink_Test Simulink_Test_M_;
RT_MODEL_Simulink_Test *const Simulink_Test_M = &Simulink_Test_M_;

/* Model step function */
void Simulink_Test_step(void)
{
  Simulink_Test_B.PulseGenerator = ((Simulink_Test_DW.clockTickCounter < 500) &&
    (Simulink_Test_DW.clockTickCounter >= 0));
  if (Simulink_Test_DW.clockTickCounter >= 999) {
    Simulink_Test_DW.clockTickCounter = 0;
  } else {
    Simulink_Test_DW.clockTickCounter++;
  }

  {
    if (Simulink_Test_B.PulseGenerator == 0)
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
    else
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
  }
}

/* Model initialize function */
void Simulink_Test_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Simulink_Test_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Simulink_Test_B), 0,
                sizeof(B_Simulink_Test));

  /* states (dwork) */
  (void) memset((void *)&Simulink_Test_DW, 0,
                sizeof(DW_Simulink_Test));
  Simulink_Test_DW.clockTickCounter = 0;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] Simulink_Test.c
 */
