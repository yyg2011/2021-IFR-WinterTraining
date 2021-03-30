/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GY53_FR_Pin GPIO_PIN_13
#define GY53_FR_GPIO_Port GPIOC
#define GY53_BL_Pin GPIO_PIN_14
#define GY53_BL_GPIO_Port GPIOC
#define GY53_BR_Pin GPIO_PIN_15
#define GY53_BR_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_0
#define LED_GPIO_Port GPIOC
#define LED0_Pin GPIO_PIN_1
#define LED0_GPIO_Port GPIOC
#define SOLENOID_VALVE_HAND_Pin GPIO_PIN_2
#define SOLENOID_VALVE_HAND_GPIO_Port GPIOC
#define SOLENOID_VALVE_ARM_Pin GPIO_PIN_3
#define SOLENOID_VALVE_ARM_GPIO_Port GPIOC
#define PHOTOELECTIC_FL_Pin GPIO_PIN_0
#define PHOTOELECTIC_FL_GPIO_Port GPIOA
#define PHOTOELECTIC_FM_Pin GPIO_PIN_1
#define PHOTOELECTIC_FM_GPIO_Port GPIOA
#define PHOTOELECTIC_BM_Pin GPIO_PIN_6
#define PHOTOELECTIC_BM_GPIO_Port GPIOA
#define PHOTOELECTIC_BR_Pin GPIO_PIN_7
#define PHOTOELECTIC_BR_GPIO_Port GPIOA
#define SOLENOID_VALVE_DOWN_Pin GPIO_PIN_4
#define SOLENOID_VALVE_DOWN_GPIO_Port GPIOC
#define KEY_Pin GPIO_PIN_0
#define KEY_GPIO_Port GPIOB
#define PHOTOELECTIC_FR_Pin GPIO_PIN_10
#define PHOTOELECTIC_FR_GPIO_Port GPIOB
#define PHOTOELECTIC_BL_Pin GPIO_PIN_11
#define PHOTOELECTIC_BL_GPIO_Port GPIOB
#define GY53_FL_Pin GPIO_PIN_15
#define GY53_FL_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
