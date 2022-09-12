/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

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
#define PIN_SENSOR_0_Pin GPIO_PIN_1
#define PIN_SENSOR_0_GPIO_Port GPIOA
#define PIN_SENSOR_1_Pin GPIO_PIN_2
#define PIN_SENSOR_1_GPIO_Port GPIOA
#define PIN_SENSOR_2_Pin GPIO_PIN_3
#define PIN_SENSOR_2_GPIO_Port GPIOA
#define PIN_SENSOR_3_Pin GPIO_PIN_4
#define PIN_SENSOR_3_GPIO_Port GPIOA
#define PIN_SENSOR_4_Pin GPIO_PIN_5
#define PIN_SENSOR_4_GPIO_Port GPIOA
#define PIN_SELECTOR_0_Pin GPIO_PIN_6
#define PIN_SELECTOR_0_GPIO_Port GPIOA
#define PIN_SELECTOR_1_Pin GPIO_PIN_7
#define PIN_SELECTOR_1_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
