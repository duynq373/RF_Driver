/**
  ******************************************************************************
  * File Name          : HW_Config.h
  * Description        : Hardware configuration header
  * Author             : duynq373@gmail.com
  ******************************************************************************
  */

#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/*USER CONFIGURATION AREA*/
/******************************************************************************/
#ifdef STM32L053xx
#define PTX_DEVICE
#endif
#ifdef STM32F411xE
#define PRX_DEVICE
#endif
#define DEBUG_ENABLE
#define NUMBER_OF_RX_DEV    1
#define NUMBER_OF_TX_DEV    1
/******************************************************************************/

#ifdef PTX_DEVICE
#include "stm32l0xx_hal.h"

#define SPI_Hndlr           hspi1
#define UART_Hndlr          huart1

#define SPI_CS_EN           HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,              \
                                                                 GPIO_PIN_RESET)
#define SPI_CS_DIS          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)

#define CE_LOW              HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,              \
                                                                 GPIO_PIN_RESET)
#define CE_HIGH             HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET)

//TODO: TO BE CHANGED FOR RX WHEN MERGE
#define LED_OFF             HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,              \
                                                                 GPIO_PIN_RESET)
#define LED_ON              HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET)

extern SPI_HandleTypeDef    hspi1;
extern UART_HandleTypeDef   huart1;

#endif /*PTX_DEVICE*/

#ifdef PRX_DEVICE
#include "stm32f4xx_hal.h"

#define SPI_Hndlr           hspi2
#define UART_Hndlr          huart2

#define SPI_CS_EN           HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15,              \
                                                                 GPIO_PIN_RESET)
#define SPI_CS_DIS          HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET)

#define CE_LOW              HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14,              \
                                                                 GPIO_PIN_RESET)
#define CE_HIGH             HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET)

#define LED_OFF             HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,              \
                                                                 GPIO_PIN_RESET)
#define LED_ON              HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET)

extern SPI_HandleTypeDef    hspi2;
extern UART_HandleTypeDef   huart2;

#endif /*PRX_DEVICE*/

#endif /*__HW_CONFIG_H*/
