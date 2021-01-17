/* 
 * File: Simulink_CAN_Loopback.h
 *  
 * Code generated for Simulink model :Simulink_CAN_Loopback.
 * 
 * Model version      : 1.161
 * Simulink Coder version    : 9.0 (R2018b) 24-May-2018
 * TLC version       : 9.0 (Aug 22 2018)
 * C/C++ source code generated on  : Sun Jan 17 15:35:46 2021
 * 
 * Target selection: stm32.tlc
 * Embedded hardware selection: STMicroelectronics->STM32 32-bit Cortex-M
 * Code generation objectives: 
 *    1. Execution efficiency
 *    2. RAM efficiency
 *    3. MISRA C:2012 guidelines
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



  #ifndef RTW_HEADER_Simulink_CAN_Loopback_h_
  #define RTW_HEADER_Simulink_CAN_Loopback_h_
    

  
#include <stddef.h>

#include <string.h>
            #include "Simulink_CAN_Loopback_CAN.h"
                #include "STM32_Config.h"
                #include "Simulink_CAN_Loopback_External_Functions.h"
    #ifndef Simulink_CAN_Loopback_COMMON_INCLUDES_
  # define Simulink_CAN_Loopback_COMMON_INCLUDES_
    #include <string.h>
    #include "rtwtypes.h"
    #include "can_message.h"
  #endif /* Simulink_CAN_Loopback_COMMON_INCLUDES_ */
  

    #include "Simulink_CAN_Loopback_types.h"    



  


  


  


  
    /* Macros for accessing real-time model data structure */
    

    #ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm) ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val) ((rtm)->errorStatus = (val))
#endif


  
   
    
    
      



  


  


  


          
    /* user code (top of export header file) */
            #include "can_message.h"



              /* Block signals (default storage) */
                  
          
  
     typedef struct   {
  

      /*@[20c5*/      



        
          
          
		
            
          
            

              /*@[20c6*/
                          
            
                   CAN_DATATYPE outMessage; /* '<Root>/CAN Pack' */
 
            
              
            /*@]*/ 

          
          
	  
		



        
          
          
		
            
          
            

              /*@[20c7*/
                          
            
                   CAN_DATATYPE inMessage; /* '<Root>/CAN_Read_Data1' */
 
            
              
            /*@]*/ 

          
          
	  
		



        
          
          
		
            
          
            

              /*@[20c8*/
                          
            
                   uint16_T inPendingCount; /* '<Root>/CAN_NbPendingMsg' */
 
            
              
            /*@]*/ 

          
          
	  
		



        
          
          
		
            
          
            

              /*@[20c9*/
                          
            
                   uint8_T Output; /* '<S2>/Output' */
 
            
              
            /*@]*/ 

          
          
	  
		



        
          
          
		
            
          
            

              /*@[20ca*/
                          
            
                   uint8_T inReady; /* '<Root>/CAN_Read_Data1' */
 
            
              
            /*@]*/ 

          
          
	  
		



        
          
          
		
            
          
            

              /*@[20cb*/
                          
            
                   uint8_T deviceState; /* '<Root>/CAN_Get_State1' */
 
            
              
            /*@]*/ 

          
          
	  
		
      /*@]*/            
      



  }    B_Simulink_CAN_Loopback;
  

        
              
          /* Block states (default storage) for system '<Root>' */
              
        
  
     typedef struct   {
  

      /*@[20cc*/      



        
          
          
		
            
          
            

              /*@[20cd*/
                          
            
                   int_T CANPack_ModeSignalID; /* '<Root>/CAN Pack' */
 
            
              
            /*@]*/ 

          
          
	  
		



        
          
          
		
            
          
            

              /*@[20ce*/
                          
            
                   uint8_T Output_DSTATE; /* '<S3>/Output' */
 
            
              
            /*@]*/ 

          
          
	  
		
      /*@]*/            
      



  }    DW_Simulink_CAN_Loopback;
  

      
        
  
    /* Constant parameters (default storage) */
                typedef struct {
                                  /* Computed Parameter: Vector_Value
  * Referenced by: '<S2>/Vector'
   */
          
        /*@[20cf*/  uint8_T Vector_Value[8]; /*@]*/
        
        
        } ConstP_Simulink_CAN_Loopback;
    
    


      /* Real-time Model Data Structure */
      
  struct tag_RTM_Simulink_CAN_Loopback {
            const char_T *errorStatus;



  };
      
        
          



  


  


          
      
      /* Block signals (default storage) */
      


  extern         B_Simulink_CAN_Loopback Simulink_CAN_Loopback_B;



      
        /* Block states (default storage) */
      


  extern         DW_Simulink_CAN_Loopback Simulink_CAN_Loopback_DW;



                /* Constant parameters (default storage) */
      


  extern         const  ConstP_Simulink_CAN_Loopback Simulink_CAN_Loopback_ConstP;



      


  
      /* Model entry point functions */
              extern void Simulink_CAN_Loopback_initialize(void);
            
        
                          extern void Simulink_CAN_Loopback_step(void);
                
    
    



  


            
          /* Real-time Model object */
          
          


  extern             RT_MODEL_Simulink_CAN_Loopback *const Simulink_CAN_Loopback_M;



          



  


  


  


        
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
    * '<Root>' : 'Simulink_CAN_Loopback'
      * '<S1>'   : 'Simulink_CAN_Loopback/Error_Fcn'
      * '<S2>'   : 'Simulink_CAN_Loopback/Repeating Sequence Stair'
      * '<S3>'   : 'Simulink_CAN_Loopback/Repeating Sequence Stair/LimitedCounter'
      * '<S4>'   : 'Simulink_CAN_Loopback/Repeating Sequence Stair/LimitedCounter/Increment Real World'
      * '<S5>'   : 'Simulink_CAN_Loopback/Repeating Sequence Stair/LimitedCounter/Wrap To Zero'
   */



  


  #endif /* RTW_HEADER_Simulink_CAN_Loopback_h_ */
/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] Simulink_CAN_Loopback.h
 */
