/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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
#define BUTTON1_Pin GPIO_PIN_13
#define BUTTON1_GPIO_Port GPIOC
#define BUTTON2_Pin GPIO_PIN_14
#define BUTTON2_GPIO_Port GPIOC
#define BUTTON3_Pin GPIO_PIN_15
#define BUTTON3_GPIO_Port GPIOC
#define LED_R_A_Pin GPIO_PIN_1
#define LED_R_A_GPIO_Port GPIOA
#define LED_Y_A_Pin GPIO_PIN_2
#define LED_Y_A_GPIO_Port GPIOA
#define LED_G_A_Pin GPIO_PIN_3
#define LED_G_A_GPIO_Port GPIOA
#define LED_R_B_Pin GPIO_PIN_4
#define LED_R_B_GPIO_Port GPIOA
#define LED_BLINK_Pin GPIO_PIN_5
#define LED_BLINK_GPIO_Port GPIOA
#define LED_Y_B_Pin GPIO_PIN_6
#define LED_Y_B_GPIO_Port GPIOA
#define LED_G_B_Pin GPIO_PIN_7
#define LED_G_B_GPIO_Port GPIOA
#define A_Pin GPIO_PIN_0
#define A_GPIO_Port GPIOB
#define B_Pin GPIO_PIN_1
#define B_GPIO_Port GPIOB
#define C_Pin GPIO_PIN_2
#define C_GPIO_Port GPIOB
#define D1_Pin GPIO_PIN_10
#define D1_GPIO_Port GPIOB
#define E1_Pin GPIO_PIN_11
#define E1_GPIO_Port GPIOB
#define F1_Pin GPIO_PIN_12
#define F1_GPIO_Port GPIOB
#define G1_Pin GPIO_PIN_13
#define G1_GPIO_Port GPIOB
#define EN0_Pin GPIO_PIN_14
#define EN0_GPIO_Port GPIOB
#define EN1_Pin GPIO_PIN_15
#define EN1_GPIO_Port GPIOB
#define LED_R_C_Pin GPIO_PIN_8
#define LED_R_C_GPIO_Port GPIOA
#define LED_Y_C_Pin GPIO_PIN_9
#define LED_Y_C_GPIO_Port GPIOA
#define LED_G_C_Pin GPIO_PIN_10
#define LED_G_C_GPIO_Port GPIOA
#define LED_R_D_Pin GPIO_PIN_11
#define LED_R_D_GPIO_Port GPIOA
#define LED_Y_D_Pin GPIO_PIN_12
#define LED_Y_D_GPIO_Port GPIOA
#define LED_G_D_Pin GPIO_PIN_13
#define LED_G_D_GPIO_Port GPIOA
#define D_Pin GPIO_PIN_3
#define D_GPIO_Port GPIOB
#define E_Pin GPIO_PIN_4
#define E_GPIO_Port GPIOB
#define F_Pin GPIO_PIN_5
#define F_GPIO_Port GPIOB
#define G_Pin GPIO_PIN_6
#define G_GPIO_Port GPIOB
#define A1_Pin GPIO_PIN_7
#define A1_GPIO_Port GPIOB
#define B1_Pin GPIO_PIN_8
#define B1_GPIO_Port GPIOB
#define C1_Pin GPIO_PIN_9
#define C1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
