/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "adc.h"
#include "usart.h"
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
#define oledI2C hfmpi2c1
#define hubI2C hi2c2
#define analogADC hadc1
#define gpsUART huart2
#define lsmI2C hi2c3
#define mpuI2C hi2c1
#define LED1_Pin GPIO_PIN_4
#define LED1_GPIO_Port GPIOE
#define LED2_Pin GPIO_PIN_5
#define LED2_GPIO_Port GPIOE
#define LED3_Pin GPIO_PIN_6
#define LED3_GPIO_Port GPIOE
#define BUTTON1_Pin GPIO_PIN_0
#define BUTTON1_GPIO_Port GPIOC
#define BUTTON2_Pin GPIO_PIN_1
#define BUTTON2_GPIO_Port GPIOC
#define BUTTON3_Pin GPIO_PIN_2
#define BUTTON3_GPIO_Port GPIOC
#define BUTTON4_Pin GPIO_PIN_3
#define BUTTON4_GPIO_Port GPIOC
#define USB_VOLTAGE_ADC_Pin GPIO_PIN_0
#define USB_VOLTAGE_ADC_GPIO_Port GPIOA
#define BATT_VOLTAGE_Pin GPIO_PIN_1
#define BATT_VOLTAGE_GPIO_Port GPIOA
#define GPS_RX_Pin GPIO_PIN_2
#define GPS_RX_GPIO_Port GPIOA
#define GPS_TX_Pin GPIO_PIN_3
#define GPS_TX_GPIO_Port GPIOA
#define GPS_RST_Pin GPIO_PIN_4
#define GPS_RST_GPIO_Port GPIOA
#define SD_CARDSW_Pin GPIO_PIN_1
#define SD_CARDSW_GPIO_Port GPIOB
#define ADIS_CS_Pin GPIO_PIN_8
#define ADIS_CS_GPIO_Port GPIOE
#define ADIS_SYNC_Pin GPIO_PIN_9
#define ADIS_SYNC_GPIO_Port GPIOE
#define ADIS_RESET_Pin GPIO_PIN_10
#define ADIS_RESET_GPIO_Port GPIOE
#define ADIS_DR_Pin GPIO_PIN_11
#define ADIS_DR_GPIO_Port GPIOE
#define ADIS_DR_EXTI_IRQn EXTI15_10_IRQn
#define PWR_OFF_Pin GPIO_PIN_15
#define PWR_OFF_GPIO_Port GPIOE
#define HUB_SCL_Pin GPIO_PIN_10
#define HUB_SCL_GPIO_Port GPIOB
#define HUB_RESET_Pin GPIO_PIN_12
#define HUB_RESET_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_14
#define OLED_SCL_GPIO_Port GPIOD
#define OLED_SDA_Pin GPIO_PIN_15
#define OLED_SDA_GPIO_Port GPIOD
#define LSM_INTMAG_Pin GPIO_PIN_6
#define LSM_INTMAG_GPIO_Port GPIOC
#define LSM_INTMAG_EXTI_IRQn EXTI9_5_IRQn
#define LSM_INT1ACCL_Pin GPIO_PIN_7
#define LSM_INT1ACCL_GPIO_Port GPIOC
#define HUB_SDA_Pin GPIO_PIN_12
#define HUB_SDA_GPIO_Port GPIOC
#define LSM_INT2ACCL_Pin GPIO_PIN_5
#define LSM_INT2ACCL_GPIO_Port GPIOB
#define MPU_CLKIN_Pin GPIO_PIN_7
#define MPU_CLKIN_GPIO_Port GPIOB
#define MPU_INT_Pin GPIO_PIN_0
#define MPU_INT_GPIO_Port GPIOE
#define MPU_INT_EXTI_IRQn EXTI0_IRQn
#define MPU_FSYNC_Pin GPIO_PIN_1
#define MPU_FSYNC_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */
typedef struct
{

	//struct size 54bytes/27words
	double accelX;
	double accelY;
	double accelZ;

	double gyroX;
	double gyroY;
	double gyroZ;
	float temp;
	uint32_t dataCNT;
}adisDataStruc;

typedef struct
{

	//struct size 12bytes/6words
	float magX;
	float magY;
	float magZ;

}lsmDataStruc;

typedef struct
{

	float pressure;
	float temperature;

}bmpDataStruc;

typedef struct
{

	//struct size
	float accelX;
	float accelY;
	float accelZ;

	float gyroX;
	float gyroY;
	float gyroZ;

	float temp;

} mpuDataStruc;

typedef struct
{

	//struct size

	uint32_t year;
	uint32_t month;
	uint32_t day;
	uint32_t hour;
	uint32_t min;
	uint32_t sec;
	uint32_t fixType;

	float fLon;
	float fLat;

	int32_t height;
	int32_t hMSL;

	uint32_t hAcc;
	uint32_t vAcc;

	int32_t gSpeed;
	int32_t headMot;

} gnssLoggedDataStruc;



typedef struct
{

	lsmDataStruc lsmData;
	mpuDataStruc mpuData;
	bmpDataStruc bmpData;




}loggerStruc;

typedef struct
{

	float supplyVoltage;
	float mcuTemp;
	float battVoltage;
	float usbVoltage;
	float battVoltageFilt;

	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;

} boardStatsStruc;

typedef struct
{
	adisDataStruc adis;
	lsmDataStruc lsm;
	mpuDataStruc mpu;
	gnssLoggedDataStruc gnss;
	boardStatsStruc boardStats;
	uint8_t buttons[4];




}guiInfoStruc;

typedef struct
{
	double accelGainX;
	double accelOffsetX;
	double accelGainY;
	double accelOffsetY;
	double accelGainZ;
	double accelOffsetZ;

	double gyroOffsetX;
	double gyroOffsetY;
	double gyroOffsetZ;


}adisCalibrationStruc;

typedef struct
{
	float accelGainX;
	float accelOffsetX;
	float accelGainY;
	float accelOffsetY;
	float accelGainZ;
	float accelOffsetZ;

	float gyroOffsetX;
	float gyroOffsetY;
	float gyroOffsetZ;


}mpuCalibrationStruc;


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
