/* 
 * File: Simulink_CAN_Loopback.c
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

        #include "Simulink_CAN_Loopback_private.h"




  


  


  


  


  


  


  


  


  


  


    
    

  
    
    /* Block signals (default storage) */
                


  B_Simulink_CAN_Loopback Simulink_CAN_Loopback_B;

      
  
      
    
    
    
    
    
    
    
      /* Block states (default storage) */
                


  DW_Simulink_CAN_Loopback Simulink_CAN_Loopback_DW;

      
  
        /* Real-time model */
          


  RT_MODEL_Simulink_CAN_Loopback Simulink_CAN_Loopback_M_;

        


  RT_MODEL_Simulink_CAN_Loopback *const Simulink_CAN_Loopback_M = &Simulink_CAN_Loopback_M_;




  


  


  


  


      

    

  
  
  
        

  
  
    
        
    
    
    
    /* Model step function */
    
          
    void Simulink_CAN_Loopback_step(void)   
    {
            


      
      
      
            
      
        
uint8_T rtb_FixPtSum1;

        

      

        
  



          
        
  



                                    /*@>19bc*/Simulink_CAN_Loopback_B./*@>20b8*/Output/*@>213*/ = /*@>1a04*/Simulink_CAN_Loopback_ConstP./*@>20bb*/Vector_Value/*@>196e*/[/*@>1a0e*/Simulink_CAN_Loopback_DW./*@>20be*/Output_DSTATE];
/*@[1b8a*/                    /* S-Function (scanpack): '<Root>/CAN Pack' */


    /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.ID = 100U;
    /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Length = 8U;
    /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Extended = 0U;
    /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Remote = 0;
    
        /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Data[0] = 0;
        /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Data[1] = 0;
        /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Data[2] = 0;
        /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Data[3] = 0;
        /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Data[4] = 0;
        /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Data[5] = 0;
        /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Data[6] = 0;
        /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Data[7] = 0;
    
    {




                
                
                

                /* --------------- START Packing signal 0 ------------------ 
                *  startBit                = 0
                *  length                  = 8
                *  desiredSignalByteLayout = LITTLEENDIAN 
                *  dataType                = SIGNED
                *  factor                  = 1.0 
                *  offset                  = 0.0 
                *  minimum                 = 0.0 
                *  maximum                 = 0.0 
                * -----------------------------------------------------------------------*/

                        {
                uint32_T packingValue = 0;
                    {
        uint32_T result = (uint32_T) (/*@>1d16*/Simulink_CAN_Loopback_B./*@>1d24*/Output);

      

             /* no scaling required */ 
        
        packingValue = result;
    }

                        {

                    int8_T packedValue;
                    int32_T scaledValue;
                            scaledValue = (int32_T) packingValue;
                    
                        if (scaledValue > (int32_T) (127)){
                            packedValue = 127;
                        }else if ( scaledValue < (int32_T)((-(127)-1))){
                            packedValue = (-(127)-1);
                        }else {
                            packedValue = (int8_T) (scaledValue);
                        }
                        {       
            
            uint8_T* tempValuePtr = (uint8_T*)&packedValue;
            uint8_T tempValue = *tempValuePtr;
            {

        
        
        
            
            
            
            
            
            
                /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Data[0]  =                     /*@>1d49*/Simulink_CAN_Loopback_B./*@>1d57*/outMessage.Data[0] |                     (uint8_T)(tempValue);
    }

    }

        }

    }

    }    
 
   
  
/*@]*//*@[1b8c*/                



    {
      CAN_TxHeaderTypeDef txHeader = {0};
      uint32_t txMailbox = 0;
      uint8_t txData[8] = {0};

        /* Build frame to send (CAN_MsgType set to on). */
        if(/*@>1dc3*/Simulink_CAN_Loopback_B./*@>1dd1*/outMessage.Extended == CAN_ID_STD) {
          txHeader.StdId = (uint32_t)/*@>1dc3*/Simulink_CAN_Loopback_B./*@>1dd1*/outMessage.ID;
          txHeader.ExtId = (uint32_t)0;
          txHeader.IDE = CAN_ID_STD;
        } else {
          txHeader.StdId = (uint32_t)0;
          txHeader.ExtId = (uint32_t)/*@>1dc3*/Simulink_CAN_Loopback_B./*@>1dd1*/outMessage.ID;
          txHeader.IDE = CAN_ID_EXT;
        }

        txHeader.RTR = (uint32_t)/*@>1dc3*/Simulink_CAN_Loopback_B./*@>1dd1*/outMessage.Remote;
        txHeader.DLC = (uint32_t)/*@>1dc3*/Simulink_CAN_Loopback_B./*@>1dd1*/outMessage.Length;
        txHeader.TransmitGlobalTime = DISABLE;

        memcpy(txData, /*@>1dc3*/Simulink_CAN_Loopback_B./*@>1dd1*/outMessage.Data, (size_t)/*@>1dc3*/Simulink_CAN_Loopback_B./*@>1dd1*/outMessage.Length);
        {


          /* Request transmission. */
          if(HAL_CAN_AddTxMessage(&hcan1, &txHeader, &txData[0], &txMailbox)!= HAL_OK) {
            Error_Handler();
          }
        }
        /* Wait transmission complete, on this mailbox. */
        while(HAL_CAN_IsTxMessagePending(&hcan1, txMailbox) == 1);
  }
 
   
  
/*@]*//*@>14f4*/rtb_FixPtSum1/*@>746*/ = /*@>1561*/(uint8_T)(((uint32_T)/*@>1a1a*/Simulink_CAN_Loopback_DW./*@>20c1*/Output_DSTATE)/*@>155d*/ + /*@>1569*/1U);
/*@>1259*/if (((int32_T)/*@>14ec*/rtb_FixPtSum1)/*@>6b3*/ > /*@>14fb*/7) {
    /*@>14fd*/rtb_FixPtSum1/*@>125c*/ = /*@>205e*/0U;
}
/*@[1b8d*/                




     {
       /* Polling case. */
       /* Wait for reception, at least something available in FIFO. */
       while(HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) == 0);
     }
 
   
  
/*@]*//*@[1b90*/                





    {
      CAN_RxHeaderTypeDef rxHeader = {0};
      uint8_t rxData[8] = {0};

      /* Get received frame. */
      if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rxHeader, &rxData[0])!= HAL_OK) {
        /*@>1e1e*/Simulink_CAN_Loopback_B./*@>1e2c*/inReady = (uint8_t)0;
      }
      else {


        /* Update Read_Data:output 0: ready. */
        /*@>1e1e*/Simulink_CAN_Loopback_B./*@>1e2c*/inReady = (uint8_t)1;

        {
          /*@>1e51*/Simulink_CAN_Loopback_B./*@>1e5f*/inMessage.Extended = (uint8_T)rxHeader.IDE;
          /*@>1e51*/Simulink_CAN_Loopback_B./*@>1e5f*/inMessage.Length = (uint8_T)rxHeader.DLC;
          /*@>1e51*/Simulink_CAN_Loopback_B./*@>1e5f*/inMessage.Remote = (uint8_T)rxHeader.RTR;

          memcpy(/*@>1e51*/Simulink_CAN_Loopback_B./*@>1e5f*/inMessage.Data, &rxData[0], (size_t)rxHeader.DLC);

          if(rxHeader.IDE == CAN_ID_STD){
            /*@>1e51*/Simulink_CAN_Loopback_B./*@>1e5f*/inMessage.ID =(uint32_T)rxHeader.StdId;
          } else {
            /*@>1e51*/Simulink_CAN_Loopback_B./*@>1e5f*/inMessage.ID =(uint32_T)rxHeader.ExtId;
          }
        }
      }
  }
 
   
  
/*@]*//*@[1b92*/                




    {
      /* Get CAN1 state. */
      /*@>1e98*/Simulink_CAN_Loopback_B./*@>1ea6*/deviceState = HAL_CAN_GetState(&hcan1);
    }
 
   
  
/*@]*//*@[1b96*/                





    {
      /* Get number of pending message for CAN1 CAN_RX_FIFO0 */
      /*@>1ef3*/Simulink_CAN_Loopback_B./*@>1f01*/inPendingCount = HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0);
    }
 
   
  
/*@]*//*@>1a20*/Simulink_CAN_Loopback_DW./*@>20c4*/Output_DSTATE/*@>6d4*/ = /*@>14f0*/rtb_FixPtSum1;






        
  


            
      
      
      
      
            
  
  
    
    

      
        

    


    
    
  
  

        

      
      
      


      
          
  

    } 
    
      




  







  /* Model initialize function */
  
      void Simulink_CAN_Loopback_initialize(void)
  { 
      


    
    
    
    
        
    
    
        /* Registration code */
            
      
      
  


      
  
  
  

  
  
  
      
        
        
        
        
            
  

        
            
            /* initialize error status */
            rtmSetErrorStatus(Simulink_CAN_Loopback_M, (NULL));
      
      
      
  
  

  
  
  

    /* block I/O */
    
      
        
        (void) memset(((void *) &Simulink_CAN_Loopback_B), 0,
sizeof(B_Simulink_CAN_Loopback));
        

        

      {
                    
            
              Simulink_CAN_Loopback_B.outMessage = CAN_DATATYPE_GROUND;
            
            
            
            
              Simulink_CAN_Loopback_B.inMessage = CAN_DATATYPE_GROUND;
            
            
              }
  

    
  
  
    

  







    /* states (dwork) */
    
        

    
        
                    
          
          (void) memset((void *)&Simulink_CAN_Loopback_DW,  0,
 sizeof(DW_Simulink_CAN_Loopback));
          
          
        
        

        
    
        
  
    

    


  

          

  
      
      

    
    
    
        




      
                                

    

    
 
    

    
 
/*@[1bc9*/          
      

    {

        /* Start CAN1. */
        if(HAL_CAN_Start(&hcan1) != HAL_OK) {
          Error_Handler();
        }
    }


 /*@]*//*@[1bca*/          
      


    {

    }


 /*@]*//*@[1bcc*/          
      


        /* Set Error interrupt function for CAN1 */
        Error_ItFcn1 = CAN1_Error_ItFcn;



        /* Activate CAN Error notifications. */
        {
          const uint32_t activeITs = CAN_IT_ERROR_WARNING|CAN_IT_ERROR_PASSIVE|
                                     CAN_IT_LAST_ERROR_CODE| CAN_IT_ERROR;
          if(HAL_CAN_ActivateNotification(&hcan1, activeITs) != HAL_OK) {
            Error_Handler();
          }
        }



 /*@]*//*@[1bcd*/          
      



        {
          /* HAL CAN1 filter configuration structure definition. */
          CAN_FilterTypeDef sFilterConfig = {0};
          sFilterConfig.FilterIdHigh = 0x0;
          sFilterConfig.FilterIdLow = 0x0;
          sFilterConfig.FilterMaskIdHigh = 0x0;
          sFilterConfig.FilterMaskIdLow = 0x0;
          sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
          sFilterConfig.FilterBank = 0;
          sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
          sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
          sFilterConfig.FilterActivation = ENABLE;
          sFilterConfig.SlaveStartFilterBank = 14;

          /* Configure CAN1 filter on dedicated FIFO0. */
          if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig)!= HAL_OK) {
            Error_Handler();
          }
        }


 /*@]*/    

    
 
        








      
    
    
        

  


      
  


  }    




      
  




  

  




  
  
   




  


  


  


  

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] Simulink_CAN_Loopback.c
 */
