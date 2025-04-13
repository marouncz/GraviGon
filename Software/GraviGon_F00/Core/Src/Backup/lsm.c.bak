/*
 * lsm.c
 *
 *  Created on: Feb 13, 2024
 *      Author: marou
 */

#include "main.h"
#include "cmsis_os.h"
#include "i2c.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h"

#define LSM_MAG_ADDRESS 0b0011110<<1

volatile uint8_t lsmRxData[7];
volatile lsmDataStruc lsmData;

/* Definitions for lsmTransmitCplt */
osSemaphoreId_t lsmTransmitCpltHandle;
const osSemaphoreAttr_t lsmTransmitCplt_attributes =
{ .name = "lsmTransmitCplt" };

void lsmInit(void)
{
	lsmTransmitCpltHandle = osSemaphoreNew(1, 1, &lsmTransmitCplt_attributes);
	uint8_t configData[4] = {0b10001100, 0b00000000, 0b00000001, 0b00000000};
	HAL_I2C_Init(&lsmI2C);
	HAL_I2C_Mem_Write(&lsmI2C, LSM_MAG_ADDRESS, 0xE0, 1, configData, 4, 100);
	HAL_I2C_Mem_Read(&lsmI2C, LSM_MAG_ADDRESS, 0xE7, 1, &lsmRxData, 7, 100);
}

#define MAG_SCALE 0.15
lsmDataStruc lsmRead(void)
{
	//osSemaphoreAcquire(lsmTransmitCpltHandle, 2000);
	//in microTesla
	HAL_I2C_Mem_Read(&lsmI2C, LSM_MAG_ADDRESS, 0xE7, 1, &lsmRxData, 7,100);
	lsmData.magX = ((int16_t) ((lsmRxData[2] << 8) | lsmRxData[1]))
					* MAG_SCALE;
	lsmData.magY = ((int16_t) ((lsmRxData[4] << 8) | lsmRxData[3]))
						* (-1)*MAG_SCALE;
	lsmData.magZ = ((int16_t) ((lsmRxData[6] << 8) | lsmRxData[5]))
						* MAG_SCALE;

	return lsmData;
}

void lsmTriggerDMA(void)
{
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 0);
	HAL_I2C_Mem_Read_DMA(&lsmI2C, LSM_MAG_ADDRESS, 0xE7, 1, &lsmRxData, 7);
	//osSemaphoreRelease(lsmTransmitCpltHandle);


}

void lsmReleaseSemaphore(void)
{
	osSemaphoreRelease(lsmTransmitCpltHandle);
}


