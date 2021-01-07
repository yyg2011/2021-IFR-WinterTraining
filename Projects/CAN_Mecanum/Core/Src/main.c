/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "dma.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "robo_base.h"
#include "Remote.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
CAN_TxHeaderTypeDef TxMessage;
CAN_RxHeaderTypeDef RxMessage;
//uint8_t RxData[8];
//uint8_t TxData[8];
uint8_t BUF[8]={1,2,3,4,5,6,7,8};
uint32_t Txmailbox;
PID pid1;
Speed_System speed;
Pos_System pos;
RC_Ctl_t RC_Data;
extern ROBO_BASE Robo_Base;
extern	uint8_t Tx_CAN2[8];				//CAN2通信发送数据
extern	uint8_t Tx_CAN1[8];				//CAN1通信发送数据
extern	uint8_t Rx_CAN2[8];				//CAN2通信接收数据
extern	uint8_t Rx_CAN1[8];				//CAN1通信接收数据
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	Usart_Init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CAN1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_IWDG_Init();
  MX_CAN2_Init();
  /* USER CODE BEGIN 2 */
	MX_IWDG_Init();
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
	HAL_TIM_Base_Start_IT(&htim2);
	CAN_FilterConfig();
	BASE_Init(&Robo_Base);
//	PID_Init(&speed.Speed_PID,5,0,0,5000,0,5000,5000);
//	PID_Init(&pos.Pos_PID,5,0,0,5000,0,5000,5000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void Motor_Info_Handle(Motor* Motor,uint8_t* RxData) //电机数据转换函数
{
	Motor->Angle=RxData[0];Motor->Angle<<=8;Motor->Angle|=RxData[1];
	Motor->Speed=RxData[2];Motor->Speed<<=8;Motor->Speed|=RxData[3];
	Motor->Current=RxData[4];Motor->Current<<=8;Motor->Current|=RxData[5];
	Motor->Temperature=RxData[6];
  if(Motor->Speed!=0){
		Motor->Error=Motor->Angle-Motor->Last_Angle;
		Motor->Abs_Angle+=Motor->Error;
		if (Motor->Error < -4096)Motor->Abs_Angle += 8192;
    else if (Motor->Error > 4096)Motor->Abs_Angle -= 8192;
  }Motor->Last_Angle=Motor->Angle;

//	pos.Info.Angle=RxData[0];pos.Info.Angle<<=8;pos.Info.Angle|=RxData[1];
//	pos.Info.Speed=RxData[2];pos.Info.Speed<<=8;pos.Info.Speed|=RxData[3];
//	pos.Info.Current=RxData[4];pos.Info.Current<<=8;pos.Info.Current|=RxData[5];
//	pos.Info.Temperature=RxData[6];
//  if(pos.Info.Speed!=0){
//		Error=pos.Info.Angle-pos.Info.Last_Angle;
//		pos.Info.Abs_Angle+=Error;
//		if (Error < -4096)pos.Info.Abs_Angle += 8192;
//    else if (Error > 4096)pos.Info.Abs_Angle -= 8192;
//	}pos.Info.Last_Angle=pos.Info.Angle;
//		speed.Tar_Speed=33.3;
//		PID_Speed_Cal(&speed,TxData);

}

void Motor_control_process(Motor* Robo,uint8_t* RxData,uint8_t* TxData)
{
	
}

void Motor_num_converter(uint8_t Motor_num,ROBO_BASE* Robo)
{
	if (Motor_num==1) Motor_control_process(Robo->MotorLF,Rx_CAN1,Tx_CAN1);
	else if(Motor_num==2) Motor_control_process(Robo->MotorRF,Rx_CAN1,Tx_CAN1);
	else if(Motor_num==3) Motor_control_process(Robo->MotorRB,Rx_CAN2,Tx_CAN1);
	else if(Motor_num==4) Motor_control_process(Robo->MotorLB,Rx_CAN2,Tx_CAN1);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
