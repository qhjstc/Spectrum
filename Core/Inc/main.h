/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#define LED0_Pin GPIO_PIN_9
#define LED0_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOF
#define T_MOSI_Pin GPIO_PIN_15
#define T_MOSI_GPIO_Port GPIOF
#define T_CS_Pin GPIO_PIN_0
#define T_CS_GPIO_Port GPIOG
#define T_SCLK_Pin GPIO_PIN_1
#define T_SCLK_GPIO_Port GPIOG
#define T_MISO_Pin GPIO_PIN_11
#define T_MISO_GPIO_Port GPIOD
#define T_PEN_Pin GPIO_PIN_12
#define T_PEN_GPIO_Port GPIOD
#define LCD_BL_Pin GPIO_PIN_13
#define LCD_BL_GPIO_Port GPIOD
#define ADS1256_NC_Pin GPIO_PIN_12
#define ADS1256_NC_GPIO_Port GPIOA
#define ADS1256_SYNC_Pin GPIO_PIN_6
#define ADS1256_SYNC_GPIO_Port GPIOD
#define ADS1256_SCK_Pin GPIO_PIN_7
#define ADS1256_SCK_GPIO_Port GPIOD
#define ADS1256_RST_Pin GPIO_PIN_9
#define ADS1256_RST_GPIO_Port GPIOG
#define ADS1256_MOSI_Pin GPIO_PIN_10
#define ADS1256_MOSI_GPIO_Port GPIOG
#define ADS1256_CS_Pin GPIO_PIN_11
#define ADS1256_CS_GPIO_Port GPIOG
#define ADS1256_MISO_Pin GPIO_PIN_13
#define ADS1256_MISO_GPIO_Port GPIOG
#define ADS1256_DRDY_Pin GPIO_PIN_14
#define ADS1256_DRDY_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */
//一些常用的定义
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;
typedef const int16_t sc16;
typedef const int8_t sc8;

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;
typedef __I int16_t vsc16;
typedef __I int8_t vsc8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;
typedef const uint16_t uc16;
typedef const uint8_t uc8;

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;
typedef __I uint16_t vuc16;
typedef __I uint8_t vuc8;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
