/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define J1_Pin GPIO_PIN_0
#define J1_GPIO_Port GPIOC
#define J1_EXTI_IRQn EXTI0_IRQn
#define J2_Pin GPIO_PIN_1
#define J2_GPIO_Port GPIOC
#define J2_EXTI_IRQn EXTI1_IRQn
#define Iniciar_Pin GPIO_PIN_2
#define Iniciar_GPIO_Port GPIOC
#define Iniciar_EXTI_IRQn EXTI2_IRQn
#define A_Pin GPIO_PIN_0
#define A_GPIO_Port GPIOA
#define B_Pin GPIO_PIN_1
#define B_GPIO_Port GPIOA
#define L2J2_Pin GPIO_PIN_5
#define L2J2_GPIO_Port GPIOA
#define L1J2_Pin GPIO_PIN_6
#define L1J2_GPIO_Port GPIOA
#define L4J1_Pin GPIO_PIN_7
#define L4J1_GPIO_Port GPIOA
#define G_Pin GPIO_PIN_10
#define G_GPIO_Port GPIOB
#define L2J1_Pin GPIO_PIN_7
#define L2J1_GPIO_Port GPIOC
#define L1J1_Pin GPIO_PIN_9
#define L1J1_GPIO_Port GPIOA
#define C_Pin GPIO_PIN_10
#define C_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define D_Pin GPIO_PIN_3
#define D_GPIO_Port GPIOB
#define F_Pin GPIO_PIN_4
#define F_GPIO_Port GPIOB
#define E_Pin GPIO_PIN_5
#define E_GPIO_Port GPIOB
#define L3J1_Pin GPIO_PIN_6
#define L3J1_GPIO_Port GPIOB
#define L4J2_Pin GPIO_PIN_8
#define L4J2_GPIO_Port GPIOB
#define L3J2_Pin GPIO_PIN_9
#define L3J2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
