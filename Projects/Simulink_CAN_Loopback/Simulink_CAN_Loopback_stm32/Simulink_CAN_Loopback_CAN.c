/* 
 * File: Simulink_CAN_Loopback_CAN.c
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


    

              #include "Simulink_CAN_Loopback.h"
            #include "Simulink_CAN_Loopback_CAN.h"



  


  


  


          /* Interrupt pointer callback function definition. */
        void (* Rx_ItFcn1)(void) = NULL;
        void (* Tx_ItFcn1)(void) = NULL;
        void (* Error_ItFcn1)(void) = NULL;



  


  


  


  


  


  


  


  


  


  


  


          /**
          * @brief  Rx FIFO 0 message pending callback.
          * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
          *         the configuration information for the specified CAN.
          * @retval None
          */
        void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
        {
          if(Rx_ItFcn1 != NULL) {
            Rx_ItFcn1();
          }

          else {
            Error_Handler();
          }
        }

        /**
          * @brief  Rx FIFO 1 message pending callback.
          * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
          *         the configuration information for the specified CAN.
          * @retval None
          */
        void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
        {
          if(Rx_ItFcn1 != NULL) {
            Rx_ItFcn1();
          }

          else {
            Error_Handler();
          }
        }

        /**
          * @brief  Rx FIFO 0 full callback.
          * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
          *         the configuration information for the specified CAN.
          * @retval None
          */
        void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan)
        {
          if(Rx_ItFcn1 != NULL) {
            Rx_ItFcn1();
          }

          else {
            Error_Handler();
          }
        }

        /**
          * @brief  Rx FIFO 1 full callback.
          * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
          *         the configuration information for the specified CAN.
          * @retval None
          */
        void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef *hcan)
        {
          if(Rx_ItFcn1 != NULL) {
            Rx_ItFcn1();
          }

          else {
            Error_Handler();
          }
        }
    /**
      * @brief  Transmission Mailbox 0 complete callback.
      * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
      *         the configuration information for the specified CAN.
      * @retval None
      */
     void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
     {
       /* Call CANx transmit complete function. */
       if(Tx_ItFcn1 != NULL) {
         Tx_ItFcn1();
       }

       else {
         Error_Handler();
       }
     }

    /**
      * @brief  Transmission Mailbox 1 complete callback.
      * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
      *         the configuration information for the specified CAN.
      * @retval None
      */
     void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan)
     {
       /* Call CANx transmit complete function. */
       if(Tx_ItFcn1 != NULL) {
         Tx_ItFcn1();
       }

       else {
         Error_Handler();
       }
     }

    /**
      * @brief  Transmission Mailbox 2 complete callback.
      * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
      *         the configuration information for the specified CAN.
      * @retval None
      */
     void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan)
     {
       /* Call CANx transmit complete function. */
       if(Tx_ItFcn1 != NULL) {
         Tx_ItFcn1();
       }

       else {
         Error_Handler();
       }
     }

    /**
      * @brief  Transmission Mailbox 0 Cancellation callback.
      * @param  hcan pointer to an CAN_HandleTypeDef structure that contains
      *         the configuration information for the specified CAN.
      * @retval None
      */
    void HAL_CAN_TxMailbox0AbortCallback(CAN_HandleTypeDef *hcan)
    {
        UNUSED(hcan);
    }

    /**
      * @brief  Transmission Mailbox 1 Cancellation callback.
      * @param  hcan pointer to an CAN_HandleTypeDef structure that contains
      *         the configuration information for the specified CAN.
      * @retval None
      */
    void HAL_CAN_TxMailbox1AbortCallback(CAN_HandleTypeDef *hcan)
    {
        UNUSED(hcan);
    }

    /**
      * @brief  Transmission Mailbox 2 Cancellation callback.
      * @param  hcan pointer to an CAN_HandleTypeDef structure that contains
      *         the configuration information for the specified CAN.
      * @retval None
      */
    void HAL_CAN_TxMailbox2AbortCallback(CAN_HandleTypeDef *hcan)
    {
        UNUSED(hcan);
    }
    /**
      * @brief  Sleep callback.
      * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
      *         the configuration information for the specified CAN.
      * @retval None
      */
    void HAL_CAN_SleepCallback(CAN_HandleTypeDef *hcan)
    {
      UNUSED(hcan);
    }

    /**
      * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
      *         the configuration information for the specified CAN.
      * @retval None
      */
    void HAL_CAN_WakeUpFromRxMsgCallback(CAN_HandleTypeDef *hcan)
    {
      UNUSED(hcan);
    }
    /**
      * @brief  Error CAN callback.
      * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
      *         the configuration information for the specified CAN.
      * @retval None
      */
     void HAL_CAN_ErrorCallback(CAN_HandleTypeDef* hcan)
     {
       /* Call CANx error function. */
       if(Error_ItFcn1 != NULL) {
         Error_ItFcn1();
       }

       else {
         Error_Handler();
       }
    }
        /*******************************************************************************
        * Function Name  : CAN1_Error_ItFcn
        * Description    : CAN1 Error processing function
        * Input          : None
        *******************************************************************************/
        void CAN1_Error_ItFcn()
        {


                                 {
               
      
  
  

    
      
  

      
  

                                /*@[1bb5*/          
      
        
        
                              
          /* Output and update for function-call system: '<Root>/Error_Fcn' */              
                      
      
      
      
  



                          
      
  



                        
                /*@[a23*/                


    {
      /* Reset CAN1 state. */
      __HAL_CAN_RESET_HANDLE_STATE(&hcan1);
    }
 
   
  
/*@]*/



        

      
  


        
    
      
        

                
      


    


/*@]*/




      
  

      
  

      
  

                    
  

  

         }
        }



  


  


  


  

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] Simulink_CAN_Loopback_CAN.c
 */
