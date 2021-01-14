/*
 * File: Simulink_Test.h
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

#ifndef RTW_HEADER_Simulink_Test_h_
#define RTW_HEADER_Simulink_Test_h_
#include <stddef.h>
#include <string.h>
#include "STM32_Config.h"
#include "Simulink_Test_External_Functions.h"
#ifndef Simulink_Test_COMMON_INCLUDES_
# define Simulink_Test_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Simulink_Test_COMMON_INCLUDES_ */

#include "Simulink_Test_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T PulseGenerator;               /* '<Root>/Pulse Generator' */
} B_Simulink_Test;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  int32_T clockTickCounter;            /* '<Root>/Pulse Generator' */
} DW_Simulink_Test;

/* Real-time Model Data Structure */
struct tag_RTM_Simulink_Test {
  const char_T *errorStatus;
};

/* Block signals (default storage) */
extern B_Simulink_Test Simulink_Test_B;

/* Block states (default storage) */
extern DW_Simulink_Test Simulink_Test_DW;

/* Model entry point functions */
extern void Simulink_Test_initialize(void);
extern void Simulink_Test_step(void);

/* Real-time Model object */
extern RT_MODEL_Simulink_Test *const Simulink_Test_M;

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
 * '<Root>' : 'Simulink_Test'
 */
#endif                                 /* RTW_HEADER_Simulink_Test_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] Simulink_Test.h
 */
