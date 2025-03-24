/*
 * adis.c
 *
 *  Created on: Feb 6, 2024
 *      Author: marou
 */

#include "adis.h"
#include "main.h"
#include "cmsis_os.h"
#include "spi.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h"
#include "calibration.h"

volatile uint16_t spiRxData[17];
volatile uint16_t spiTxData[17] =
{ };
GPIO_InitTypeDef GPIO_InitStruct =
{ 0 };
adisDataStruc adisData;

uint8_t adisInitCplt = 0;

/* Definitions for adisTransmitCplt */
osSemaphoreId_t adisTransmitCpltHandle;
const osSemaphoreAttr_t adisTransmitCplt_attributes =
{ .name = "adisTransmitCplt" };

void adisReset(void)
{
	HAL_GPIO_WritePin(ADIS_CS_GPIO_Port, ADIS_CS_Pin, 1);
	HAL_GPIO_WritePin(ADIS_RESET_GPIO_Port, ADIS_RESET_Pin, 0);
	osDelay(100);
	HAL_GPIO_WritePin(ADIS_RESET_GPIO_Port, ADIS_RESET_Pin, 1);
	osDelay(1000);

}

void adisInit(void)
{
	HAL_SPI_Init(&adisSPI);

	HAL_SPI_Transmit(&adisSPI, (uint8_t*) &spiTxData, 1, 100);
	osDelay(1);
	adisTransmitCpltHandle = osSemaphoreNew(1, 1, &adisTransmitCplt_attributes);

	//select decimation filter for output DR 400Hz
	spiTxData[0] = 1 << 15 | 0x64 << 8 | 0x04;
	HAL_GPIO_WritePin(ADIS_CS_GPIO_Port, ADIS_CS_Pin, 0);
	HAL_SPI_Transmit(&adisSPI, (uint8_t*) &spiTxData, 1, 100);
	HAL_GPIO_WritePin(ADIS_CS_GPIO_Port, ADIS_CS_Pin, 1);
	osDelay(1);
	spiTxData[0] = 1 << 15 | 0x65 << 8 | 0x00;
	HAL_GPIO_WritePin(ADIS_CS_GPIO_Port, ADIS_CS_Pin, 0);
	HAL_SPI_Transmit(&adisSPI, (uint8_t*) &spiTxData, 1, 100);
	HAL_GPIO_WritePin(ADIS_CS_GPIO_Port, ADIS_CS_Pin, 1);
	osDelay(1);

	//select MSC_CTRL to 32bit burst
	spiTxData[0] = 1 << 15 | 0x60 << 8 | 0x00;
	HAL_GPIO_WritePin(ADIS_CS_GPIO_Port, ADIS_CS_Pin, 0);
	HAL_SPI_Transmit(&adisSPI, (uint8_t*) &spiTxData, 1, 100);
	HAL_GPIO_WritePin(ADIS_CS_GPIO_Port, ADIS_CS_Pin, 1);
	osDelay(1);
	spiTxData[0] = 1 << 15 | 0x61 << 8 | 0b10;
	HAL_GPIO_WritePin(ADIS_CS_GPIO_Port, ADIS_CS_Pin, 0);
	HAL_SPI_Transmit(&adisSPI, (uint8_t*) &spiTxData, 1, 100);
	HAL_GPIO_WritePin(ADIS_CS_GPIO_Port, ADIS_CS_Pin, 1);

	adisInitCplt = 1;

}

#define GYRO_SCALE (0.00043633231 / 65536)
#define ACCEL_SCALE (0.00245 / 65536)


adisDataStruc adisRead(void)
{
	osSemaphoreAcquire(adisTransmitCpltHandle, 2000);
	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 1);
	adisData.gyroX = ((int32_t) ((spiRxData[3] << 16) | spiRxData[2]))
			* GYRO_SCALE;
	adisData.gyroY = ((int32_t) ((spiRxData[5] << 16) | spiRxData[4]))
			* GYRO_SCALE;
	adisData.gyroZ = ((int32_t) ((spiRxData[7] << 16) | spiRxData[6]))
			* GYRO_SCALE;

	adisData.accelX = ((int32_t) ((spiRxData[9] << 16) | spiRxData[8]))
			* ACCEL_SCALE;
	adisData.accelY = ((int32_t) ((spiRxData[11] << 16) | spiRxData[10]))
			* ACCEL_SCALE;
	adisData.accelZ = ((int32_t) ((spiRxData[13] << 16) | spiRxData[12]))
			* ACCEL_SCALE;

	adisData.temp = ((int16_t) (spiRxData[14])) * 0.1f;

	adisData.dataCNT = ((uint32_t) (spiRxData[15]));

	static adisCalibrationStruc adisCal;
	adisCal = adisCalibrationConst();
	adisData.gyroX += adisCal.gyroOffsetX;
	adisData.gyroY += adisCal.gyroOffsetY;
	adisData.gyroZ += adisCal.gyroOffsetZ;
	adisData.accelX = (adisData.accelX*adisCal.accelGainX) + adisCal.accelOffsetX;
	adisData.accelY = (adisData.accelY*adisCal.accelGainY) + adisCal.accelOffsetY;
	adisData.accelZ = (adisData.accelZ*adisCal.accelGainZ) + adisCal.accelOffsetZ;
	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 0);

	return adisData;

}

void adisTriggerDMA(void)
{

	spiTxData[0] = 0x6800;
	HAL_GPIO_WritePin(ADIS_CS_GPIO_Port, ADIS_CS_Pin, 0);
	HAL_SPI_TransmitReceive_DMA(&adisSPI, (uint8_t*) &spiTxData,
			(uint8_t*) &spiRxData, 17);
}

uint8_t adisReady(void)
{

	return adisInitCplt;

}
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	HAL_GPIO_WritePin(ADIS_CS_GPIO_Port, ADIS_CS_Pin, 1);
	osSemaphoreRelease(adisTransmitCpltHandle);
}

