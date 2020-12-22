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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ML_A_Pin GPIO_PIN_0
#define ML_A_GPIO_Port GPIOA
#define ML_B_Pin GPIO_PIN_1
#define ML_B_GPIO_Port GPIOA
#define ML_Speed_Pin GPIO_PIN_7
#define ML_Speed_GPIO_Port GPIOA
#define MR_FWD_Pin GPIO_PIN_4
#define MR_FWD_GPIO_Port GPIOC
#define ML_FWD_Pin GPIO_PIN_5
#define ML_FWD_GPIO_Port GPIOC
#define MR_BWD_Pin GPIO_PIN_0
#define MR_BWD_GPIO_Port GPIOB
#define ML_BWD_Pin GPIO_PIN_1
#define ML_BWD_GPIO_Port GPIOB
#define Left_Pin GPIO_PIN_2
#define Left_GPIO_Port GPIOB
#define CLeft_Pin GPIO_PIN_7
#define CLeft_GPIO_Port GPIOE
#define CRight_Pin GPIO_PIN_8
#define CRight_GPIO_Port GPIOE
#define Right_Pin GPIO_PIN_9
#define Right_GPIO_Port GPIOE
#define Centre_Pin GPIO_PIN_10
#define Centre_GPIO_Port GPIOE
#define XLeft_Pin GPIO_PIN_11
#define XLeft_GPIO_Port GPIOE
#define XRight_Pin GPIO_PIN_12
#define XRight_GPIO_Port GPIOE
#define MR_Speed_Pin GPIO_PIN_13
#define MR_Speed_GPIO_Port GPIOD
#define MR_A_Pin GPIO_PIN_15
#define MR_A_GPIO_Port GPIOA
#define MR_B_Pin GPIO_PIN_3
#define MR_B_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
