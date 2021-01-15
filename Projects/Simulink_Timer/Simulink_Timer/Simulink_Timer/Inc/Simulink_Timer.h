/*
 * File: Simulink_Timer.h
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

#ifndef RTW_HEADER_Simulink_Timer_h_
#define RTW_HEADER_Simulink_Timer_h_
#include <stddef.h>
#include <string.h>
#include "STM32_Config.h"
#include "Simulink_Timer_External_Functions.h"
#include "Simulink_Timer_TIM.h"
#ifndef Simulink_Timer_COMMON_INCLUDES_
# define Simulink_Timer_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Simulink_Timer_COMMON_INCLUDES_ */

#include "Simulink_Timer_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint16_T Output_DSTATE;              /* '<S3>/Output' */
} DW_Simulink_Timer;

/* Real-time Model Data Structure */
struct tag_RTM_Simulink_Timer {
  const char_T *errorStatus;
};

/* Block states (default storage) */
extern DW_Simulink_Timer Simulink_Timer_DW;

/* Model entry point functions */
extern void Simulink_Timer_initialize(void);
extern void Simulink_Timer_step(void);

/* Real-time Model object */
extern RT_MODEL_Simulink_Timer *const Simulink_Timer_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/FixPt Data Type Duplicate1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Simulink_Timer'
 * '<S1>'   : 'Simulink_Timer/Function-Call Subsystem'
 * '<S2>'   : 'Simulink_Timer/Function-Call Subsystem/Compare To Constant'
 * '<S3>'   : 'Simulink_Timer/Function-Call Subsystem/Counter Limited'
 * '<S4>'   : 'Simulink_Timer/Function-Call Subsystem/Enabled Subsystem'
 * '<S5>'   : 'Simulink_Timer/Function-Call Subsystem/Counter Limited/Increment Real World'
 * '<S6>'   : 'Simulink_Timer/Function-Call Subsystem/Counter Limited/Wrap To Zero'
 */
#endif                                 /* RTW_HEADER_Simulink_Timer_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] Simulink_Timer.h
 */
