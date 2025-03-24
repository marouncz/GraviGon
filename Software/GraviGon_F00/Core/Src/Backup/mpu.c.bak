/*
 * mpu.c
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


#define MPU_ADDRESS 0b1101000<<1

volatile uint8_t mpuRxData[14];
volatile mpuDataStruc mpuData;

/* Definitions for mpuReceiveCplt */
osSemaphoreId_t mpuReceiveCpltHandle;
const osSemaphoreAttr_t mpuReceiveCplt_attributes =
{ .name = "mpuReceiveCplt" };

uint8_t mpuInitCplt = 0;

void mpuInit(void)
{
	HAL_GPIO_WritePin(MPU_FSYNC_GPIO_Port, MPU_FSYNC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MPU_CLKIN_GPIO_Port, MPU_CLKIN_Pin, GPIO_PIN_RESET);

	HAL_I2C_Init(&mpuI2C);

	mpuReceiveCpltHandle = osSemaphoreNew(1, 1, &mpuReceiveCplt_attributes);

	//wake up MPU6050
	uint8_t configData[4] =
	{ 0,0,0,0};
	HAL_I2C_Mem_Write(&mpuI2C, MPU_ADDRESS, 0x6B, 1, configData, 1, 100);
	osDelay(100);

	//reset MPU6050
	configData[0] = 0b10000000;
	HAL_I2C_Mem_Write(&mpuI2C, MPU_ADDRESS, 0x6B, 1, configData, 1, 100);
	osDelay(100);

	//wake up MPU6050
	configData[0] = 0b00000000;
	HAL_I2C_Mem_Write(&mpuI2C, MPU_ADDRESS, 0x6B, 1, configData, 1, 100);
	osDelay(100);

	//configure MPU6050 sample rate and gyro/acc scale
	configData[0] = 19;
	configData[1] = 0b00000000;
	configData[2] = 0b00001000;
	configData[3] = 0b00010000;
	HAL_I2C_Mem_Write(&mpuI2C, MPU_ADDRESS, 0x19, 1, configData, 4, 100);
	//configure interrupt pin
	configData[0] = 0b00000001;
	HAL_I2C_Mem_Write(&mpuI2C, MPU_ADDRESS, 0x38, 1, configData, 1, 100);
	osDelay(10);
	mpuInitCplt = 1;

}

#define ACCEL_SCALE (78.4/32768.0)
#define GYRO_SCALE (8.72665 / 32768.0)


mpuDataStruc mpuRead(void)
{
	osSemaphoreAcquire(mpuReceiveCpltHandle, 2000);
	//in ms-2
	mpuData.accelX = ((int16_t) ((mpuRxData[0] << 8) | mpuRxData[1]))
					* ACCEL_SCALE;
	mpuData.accelY = ((int16_t) ((mpuRxData[2] << 8) | mpuRxData[3]))
						* ACCEL_SCALE;
	mpuData.accelZ = ((int16_t) ((mpuRxData[4] << 8) | mpuRxData[5]))
						* ACCEL_SCALE;

	mpuData.temp = ((int16_t) ((mpuRxData[6] << 8) | mpuRxData[7]))
								/340.0 + 36.53;

	//in rads-1
	mpuData.gyroX = ((int16_t) ((mpuRxData[8] << 8) | mpuRxData[9]))
			* GYRO_SCALE;
	mpuData.gyroY = ((int16_t) ((mpuRxData[10] << 8) | mpuRxData[11]))
			* GYRO_SCALE;
	mpuData.gyroZ = ((int16_t) ((mpuRxData[12] << 8) | mpuRxData[13]))
			* GYRO_SCALE;

	/*static mpuCalibrationStruc mpuCal;
	mpuCal = mpuCalibrationConst();
	mpuData.gyroX += mpuCal.gyroOffsetX;
	mpuData.gyroY += mpuCal.gyroOffsetY;
	mpuData.gyroZ += mpuCal.gyroOffsetZ;
	mpuData.accelX = (mpuData.accelX*mpuCal.accelGainX) + mpuCal.accelOffsetX;
	mpuData.accelY = (mpuData.accelY*mpuCal.accelGainY) + mpuCal.accelOffsetY;
	mpuData.accelZ = (mpuData.accelZ*mpuCal.accelGainZ) + mpuCal.accelOffsetZ;*/

	return mpuData;
}

void mpuTriggerDMA(void)
{
	//HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 0);
	HAL_I2C_Mem_Read_DMA(&mpuI2C, MPU_ADDRESS, 0x3B, 1, &mpuRxData, 14);


}

uint8_t mpuReady(void)
{

	return mpuInitCplt;

}

void mpuReleaseSemaphore(void)
{
	osSemaphoreRelease(mpuReceiveCpltHandle);
}
