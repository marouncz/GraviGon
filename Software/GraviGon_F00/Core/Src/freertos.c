/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "i2c.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"
#include "w25q_mem.h"


#include "ssd1306_fonts.h"
#include "lsm.h"
#include "fatfs.h"
#include "GNSS.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include "mpu.h"
#include "usb_device.h"
#include "gui.h"
#include "rtc.h"
#include "tim.h"
#include "usbd_core.h"
#include "usbd_msc.h"


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
/* USER CODE BEGIN Variables */
guiInfoStruc guiInfo = {0};
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for keepaliveTask */
osThreadId_t keepaliveTaskHandle;
const osThreadAttr_t keepaliveTask_attributes = {
  .name = "keepaliveTask",
  .stack_size = 1280 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for hubTask */
osThreadId_t hubTaskHandle;
const osThreadAttr_t hubTask_attributes = {
  .name = "hubTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for gpsTask */
osThreadId_t gpsTaskHandle;
const osThreadAttr_t gpsTask_attributes = {
  .name = "gpsTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for oledTask */
osThreadId_t oledTaskHandle;
const osThreadAttr_t oledTask_attributes = {
  .name = "oledTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for powerTask */
osThreadId_t powerTaskHandle;
const osThreadAttr_t powerTask_attributes = {
  .name = "powerTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow2,
};
/* Definitions for adisTask */
osThreadId_t adisTaskHandle;
const osThreadAttr_t adisTask_attributes = {
  .name = "adisTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityRealtime3,
};
/* Definitions for lsmTask */
osThreadId_t lsmTaskHandle;
const osThreadAttr_t lsmTask_attributes = {
  .name = "lsmTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityRealtime2,
};
/* Definitions for loggerTask */
osThreadId_t loggerTaskHandle;
const osThreadAttr_t loggerTask_attributes = {
  .name = "loggerTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal2,
};
/* Definitions for mpuTask */
osThreadId_t mpuTaskHandle;
const osThreadAttr_t mpuTask_attributes = {
  .name = "mpuTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityRealtime1,
};
/* Definitions for adisQ */
osMessageQueueId_t adisQHandle;
const osMessageQueueAttr_t adisQ_attributes = {
  .name = "adisQ"
};
/* Definitions for lsmQ */
osMessageQueueId_t lsmQHandle;
const osMessageQueueAttr_t lsmQ_attributes = {
  .name = "lsmQ"
};
/* Definitions for loggerQ */
osMessageQueueId_t loggerQHandle;
const osMessageQueueAttr_t loggerQ_attributes = {
  .name = "loggerQ"
};
/* Definitions for mpuQ */
osMessageQueueId_t mpuQHandle;
const osMessageQueueAttr_t mpuQ_attributes = {
  .name = "mpuQ"
};
/* Definitions for gnssQ */
osMessageQueueId_t gnssQHandle;
const osMessageQueueAttr_t gnssQ_attributes = {
  .name = "gnssQ"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartKeepaliveTask(void *argument);
void StartHubTask(void *argument);
void StartGpsTask(void *argument);
void StartOledTask(void *argument);
void StartPowerTask(void *argument);
void StartAdisTask(void *argument);
void StartLsmTask(void *argument);
void StartLoggerTask(void *argument);
void StartMpuTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
	HAL_TIM_Base_Start_IT(&htim11);
}

extern volatile unsigned long ulHighFrequencyTimerTicks;
__weak unsigned long getRunTimeCounterValue(void)
{
return ulHighFrequencyTimerTicks;
}
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of adisQ */
  adisQHandle = osMessageQueueNew (4, sizeof(adisDataStruc), &adisQ_attributes);

  /* creation of lsmQ */
  lsmQHandle = osMessageQueueNew (4, sizeof(lsmDataStruc), &lsmQ_attributes);

  /* creation of loggerQ */
  loggerQHandle = osMessageQueueNew (10, sizeof(loggerStruc), &loggerQ_attributes);

  /* creation of mpuQ */
  mpuQHandle = osMessageQueueNew (4, sizeof(mpuDataStruc), &mpuQ_attributes);

  /* creation of gnssQ */
  gnssQHandle = osMessageQueueNew (16, sizeof(gnssLoggedDataStruc), &gnssQ_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of keepaliveTask */
  keepaliveTaskHandle = osThreadNew(StartKeepaliveTask, NULL, &keepaliveTask_attributes);

  /* creation of hubTask */
  hubTaskHandle = osThreadNew(StartHubTask, NULL, &hubTask_attributes);

  /* creation of gpsTask */
  gpsTaskHandle = osThreadNew(StartGpsTask, NULL, &gpsTask_attributes);

  /* creation of oledTask */
  oledTaskHandle = osThreadNew(StartOledTask, NULL, &oledTask_attributes);

  /* creation of powerTask */
  powerTaskHandle = osThreadNew(StartPowerTask, NULL, &powerTask_attributes);

  /* creation of adisTask */
  adisTaskHandle = osThreadNew(StartAdisTask, NULL, &adisTask_attributes);

  /* creation of lsmTask */
  lsmTaskHandle = osThreadNew(StartLsmTask, NULL, &lsmTask_attributes);

  /* creation of loggerTask */
  loggerTaskHandle = osThreadNew(StartLoggerTask, NULL, &loggerTask_attributes);

  /* creation of mpuTask */
  mpuTaskHandle = osThreadNew(StartMpuTask, NULL, &mpuTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
		osDelay(10);
		guiInfo.buttons[0] = !HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
		guiInfo.buttons[1] = !HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
		guiInfo.buttons[2] = !HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
		guiInfo.buttons[3] = !HAL_GPIO_ReadPin(BUTTON4_GPIO_Port, BUTTON4_Pin);

		osDelay(10);
		RTC_TimeTypeDef sTime;
		RTC_DateTypeDef sDate;
		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
		guiInfo.boardStats.sTime = sTime;
		guiInfo.boardStats.sDate = sDate;

  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartKeepaliveTask */

/**
* @brief Function implementing the keepaliveTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartKeepaliveTask */
void StartKeepaliveTask(void *argument)
{
  /* USER CODE BEGIN StartKeepaliveTask */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);


	
  /* Infinite loop */
  for(;;)
  {
		if (HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 0)
		{
			TIM1->CCR3 = 250;
			osDelay(100);
		}
		if (HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin) == 0)
		{
			TIM1->CCR3 = 1250;
			osDelay(100);
		}
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		osDelay(100);

  }
  /* USER CODE END StartKeepaliveTask */
}

/* USER CODE BEGIN Header_StartHubTask */
/**
* @brief Function implementing the hubTask thread.
* @param argument: Not used
* @retval None
*/

#define HUB_ADDRESS 0b0101100<<1
#define FFH_CMD 0b1
/* USER CODE END Header_StartHubTask */
void StartHubTask(void *argument)
{
  /* USER CODE BEGIN StartHubTask */
	HAL_GPIO_WritePin(HUB_RESET_GPIO_Port, HUB_RESET_Pin, 1);
	osDelay(10);
	static uint8_t hubTxBuffer[17] = {16, 0x24, 0x04, 0x14, 0x25, 0xB3, 0x0B, 0x00, 0x00, 0x00, 0b11100, 0b10, 0b10, 0x01, 0x32, 0x32,};
	HAL_I2C_Init(&hubI2C);


	HAL_I2C_Mem_Write(&hubI2C, HUB_ADDRESS, 0x00, 1, hubTxBuffer, 17, 10);

	hubTxBuffer[0] = 1;
	hubTxBuffer[1] = FFH_CMD;
	HAL_I2C_Mem_Write(&hubI2C, HUB_ADDRESS, 0xff, 1, hubTxBuffer, 2, 10);


  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartHubTask */
}

/* USER CODE BEGIN Header_StartGpsTask */
#define SYNC_TIME_GPS 1
/**
* @brief Function implementing the gpsTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGpsTask */
void StartGpsTask(void *argument)
{
  /* USER CODE BEGIN StartGpsTask */
	HAL_GPIO_WritePin(GPS_RST_GPIO_Port, GPS_RST_Pin, 1);
	osDelay(3000);

	GNSS_StateHandle GNSS_Handle;
	gnssLoggedDataStruc gnssLoggedData;
	GNSS_Init(&GNSS_Handle, &gpsUART);
	osDelay(1000);
	GNSS_LoadConfig(&GNSS_Handle);
	uint8_t rtcFlag = 0;




  /* Infinite loop */
  for(;;)
	{
		GNSS_GetPVTData(&GNSS_Handle);
		GNSS_ParseBuffer(&GNSS_Handle);
		osDelay(1000);


		gnssLoggedData.year = GNSS_Handle.year;
		gnssLoggedData.month = GNSS_Handle.month;
		gnssLoggedData.day = GNSS_Handle.day;
		gnssLoggedData.hour = GNSS_Handle.hour;
		gnssLoggedData.min = GNSS_Handle.min;
		gnssLoggedData.sec = GNSS_Handle.sec;
		gnssLoggedData.fixType = GNSS_Handle.fixType;
		gnssLoggedData.fLon = GNSS_Handle.fLon;
		gnssLoggedData.fLat = GNSS_Handle.fLat;
		gnssLoggedData.height = GNSS_Handle.height;
		gnssLoggedData.hMSL = GNSS_Handle.hMSL;
		gnssLoggedData.hAcc = GNSS_Handle.hAcc;
		gnssLoggedData.vAcc = GNSS_Handle.vAcc;
		gnssLoggedData.gSpeed = GNSS_Handle.gSpeed;
		gnssLoggedData.headMot = GNSS_Handle.headMot;

		osMessageQueuePut(gnssQHandle,  &gnssLoggedData, 1, osWaitForever);

		guiInfo.gnss = gnssLoggedData;

		if (rtcFlag == 0 && GNSS_Handle.fixType == 3 && SYNC_TIME_GPS)
		{
			//first gps synce after power up, set rtc
			rtcFlag = 1;
			RTC_TimeTypeDef sTime =
			{ 0 };
			RTC_DateTypeDef sDate =
			{ 0 };

			sTime.Hours = GNSS_Handle.hour;
			sTime.Minutes = GNSS_Handle.min;
			sTime.Seconds = GNSS_Handle.sec;
			sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
			sTime.StoreOperation = RTC_STOREOPERATION_RESET;

			sDate.WeekDay = RTC_WEEKDAY_MONDAY;
			sDate.Month = GNSS_Handle.month;
			sDate.Date = GNSS_Handle.day;
			sDate.Year = GNSS_Handle.year - 2000;


			if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
			{
				Error_Handler();
			}


			if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
			{
				Error_Handler();
			}


		}

	}
  /* USER CODE END StartGpsTask */
}

/* USER CODE BEGIN Header_StartOledTask */
/**
* @brief Function implementing the oledTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartOledTask */
void StartOledTask(void *argument)
{
  /* USER CODE BEGIN StartOledTask */
	ssd1306_Init();
  /* Infinite loop */
  for(;;)
  {

	  guiStateMachine(&guiInfo);


		osDelay(1);

  }
  /* USER CODE END StartOledTask */
}

/* USER CODE BEGIN Header_StartPowerTask */

#define USB_CHANNEL 0
#define BAT_CHANNEL 1
#define TMP_CHANNEL 2
#define REF_CHANNEL 3
#define ADCIIRCOEFF 0.3

/**
* @brief Function implementing the powerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartPowerTask */
void StartPowerTask(void *argument)
{
  /* USER CODE BEGIN StartPowerTask */
	HAL_ADC_Init(&analogADC);

	volatile uint16_t adcDataDMA[4];

	float supplyVoltage = 3.3;
	float mcuTemp = 24;
	float battVoltage = 3.7;
	float usbVoltage = 5;
	float battVoltageFilt = 3.7;
	//minimum temperature sensor sampling time 10us, slope 2.5mv/degC, 0.76V at 25degC


  /* Infinite loop */
  for(;;)
  {
	  HAL_ADC_Start_DMA(&analogADC, (uint32_t*) adcDataDMA, 4);
	  osDelay(100);

	  supplyVoltage = *VREFINT_CAL_ADDR * VREFINT_CAL_VREF / adcDataDMA[REF_CHANNEL]/1000.0;
	  mcuTemp = -279.0 + 400.0*(supplyVoltage*adcDataDMA[TMP_CHANNEL]/4095.0);
	  usbVoltage = (supplyVoltage*adcDataDMA[USB_CHANNEL]/4095.0)*(33.0+27.0)/33.0;
	  battVoltage = (supplyVoltage*adcDataDMA[BAT_CHANNEL]/4095.0)*(33.1+27.16)/33.0;

	  battVoltageFilt = ADCIIRCOEFF * battVoltage + (1.0-ADCIIRCOEFF)*battVoltageFilt;

	  if(battVoltageFilt < 3.5) // batttery low voltage
	  {
		  HAL_GPIO_WritePin(PWR_OFF_GPIO_Port, PWR_OFF_Pin, 1);
		  while(1)
		  {
			  //this loop should be entered only for a short while and than powered down

		  }
	  }

	  guiInfo.boardStats.battVoltage = battVoltage;
	  guiInfo.boardStats.battVoltageFilt = battVoltageFilt;
	  guiInfo.boardStats.mcuTemp = mcuTemp;
	  guiInfo.boardStats.supplyVoltage = supplyVoltage;
	  guiInfo.boardStats.usbVoltage = usbVoltage;
  }
  /* USER CODE END StartPowerTask */
}

/* USER CODE BEGIN Header_StartAdisTask */


/**
* @brief Function implementing the adisTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAdisTask */
void StartAdisTask(void *argument)
{
  /* USER CODE BEGIN StartAdisTask */


	/* Infinite loop */
  for(;;)
  {
	  osDelay(100);



  }
  /* USER CODE END StartAdisTask */
}

/* USER CODE BEGIN Header_StartLsmTask */

/**
* @brief Function implementing the lsmTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLsmTask */
void StartLsmTask(void *argument)
{
  /* USER CODE BEGIN StartLsmTask */
	lsmDataStruc lsmLog;

	osDelay(1000);
	lsmInit();
	osDelay(100);

  /* Infinite loop */
  for(;;)
  {

	  lsmLog = lsmRead();
	  osMessageQueuePut(lsmQHandle,  &lsmLog, 1, osWaitForever);
	  guiInfo.lsm = lsmLog;


  }
  /* USER CODE END StartLsmTask */
}

/* USER CODE BEGIN Header_StartLoggerTask */



/**
* @brief Function implementing the loggerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLoggerTask */
void StartLoggerTask(void *argument)
{
  /* USER CODE BEGIN StartLoggerTask */
	loggerStruc loggerStore[10];
	loggerStruc loggerStoreFS;

	FRESULT res; /* FatFs function common result code */
	uint32_t byteswritten, bytesread; /* File write/read counts */

	uint8_t loggerState = 0;
	uint8_t prevLoggerState = 0;
	uint8_t buffer[sizeof(loggerStoreFS)];


	extern USBD_HandleTypeDef hUsbDeviceFS;
	MX_USB_DEVICE_Init();


  /* Infinite loop */
  for(;;)
  {
		loggerState = isLoggerOn();

		if (loggerState && !prevLoggerState)
		{
			//logger just turned on
			//deinit usb

			USBD_LL_DeInit(&hUsbDeviceFS);


			if (f_mount(&SDFatFS, (TCHAR const*) SDPath, 0) != FR_OK)
			{
				Error_Handler();
			}
			else
			{

				//Open file for writing (Create)
				if (f_open(&SDFile, "imuData.bin", FA_CREATE_ALWAYS | FA_WRITE)
						!= FR_OK)
				{
					Error_Handler();
				}
				else
				{

				}

			}

		}
		else if (loggerState && prevLoggerState)
		{
			// logging cycle
			osMessageQueueGet(loggerQHandle, &loggerStoreFS, NULL,
					osWaitForever);
			memcpy(buffer, &loggerStoreFS, sizeof(loggerStoreFS));
			f_write(&SDFile, buffer, sizeof(loggerStoreFS),
										(void*) &byteswritten);
		}
		else if (!loggerState && prevLoggerState)
		{
			//logger just turned off
			f_close(&SDFile);
			f_mount(&SDFatFS, (TCHAR const*) NULL, 0);
			USBD_LL_Init(&hUsbDeviceFS);
			MX_USB_DEVICE_Init();
		}
		else
		{
			//turned off logger
			osDelay(1);
			osMessageQueueGet(loggerQHandle, &loggerStore[0], NULL,
			osWaitForever);
		}
		prevLoggerState = loggerState;


  }
  /* USER CODE END StartLoggerTask */
}

/* USER CODE BEGIN Header_StartMpuTask */
/**
* @brief Function implementing the mpuTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMpuTask */
void StartMpuTask(void *argument)
{
  /* USER CODE BEGIN StartMpuTask */
	osDelay(100);
	mpuInit();
	osDelay(100);

	mpuDataStruc mpuLog;
  /* Infinite loop */
  for(;;)
  {
	  mpuLog = mpuRead();
	  osMessageQueuePut(mpuQHandle,  &mpuLog, 1, osWaitForever);
	  guiInfo.mpu = mpuLog;

  }
  /* USER CODE END StartMpuTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if (GPIO_Pin == LSM_INTMAG_Pin)
	{
		lsmTriggerDMA();

	}
	if (GPIO_Pin == MPU_INT_Pin)
	{
		if (mpuReady())
		{
			mpuTriggerDMA();
		}

	}
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (hi2c == &lsmI2C)
	{
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1);
		lsmReleaseSemaphore();

	}
	if (hi2c == &mpuI2C)
	{
		mpuReleaseSemaphore();

	}

}

/* USER CODE END Application */

