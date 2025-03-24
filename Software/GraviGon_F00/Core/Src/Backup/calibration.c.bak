/*
 * calibration.c
 *
 *  Created on: Apr 21, 2024
 *      Author: marou
 */

#include "main.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "gui.h"
#include <stdio.h>
#include "cmsis_os2.h"
#include <string.h>
#include "calibration.h"
#include "adis.h"
#include "mpu.h"

#include "AccelCalSolver.h"
#include "AccelCalSolver_terminate.h"
#include "rt_nonfinite.h"

adisCalibrationStruc adisCal =
{ .accelGainX = 1.0, .accelGainY = 1.0, .accelGainZ = 1.0, .accelOffsetX = 0.0,
		.accelOffsetY = 0.0, .accelOffsetZ = 0.0, .gyroOffsetX = 0.0,
		.gyroOffsetY = 0.0, .gyroOffsetZ = 0.0 };

mpuCalibrationStruc mpuCal =
{ .accelGainX = 1.0, .accelGainY = 1.0, .accelGainZ = 1.0, .accelOffsetX = 0.0,
		.accelOffsetY = 0.0, .accelOffsetZ = 0.0, .gyroOffsetX = 0.0,
		.gyroOffsetY = 0.0, .gyroOffsetZ = 0.0 };

void calibrateAccel(void)
{

	extern osThreadId_t adisTaskHandle;
	extern osThreadId_t mpuTaskHandle;

	osThreadSuspend(adisTaskHandle);
	osThreadSuspend(mpuTaskHandle);

	char buttonText[4][5] =
	{ "    ", "    ", "    ", "NEXT" };
	ssd1306_Fill(Black);
	guiDrawBottomBox(buttonText);

	char calibrationMessage[12][22] =
	{ "You will be asked to", "lay the IMU on a ", "flat surface on all ",
			"of its 6 faces ", "sequentially. After", "each \"NEXT\" button ",
			"press, you will have", "5 seconds to", "position the unit.",
			"The IMU cannot be", "touched or moved", "during measurement",

	};

	for (int i = 0; i < 6; i++)
	{
		ssd1306_SetCursor(0, i * 8);
		ssd1306_WriteString(calibrationMessage[i], Font_6x8, White);
	}
	ssd1306_UpdateScreen();
	osDelay(2000);

	while (HAL_GPIO_ReadPin(BUTTON4_GPIO_Port, BUTTON4_Pin))
	{
		osDelay(10);
	}
	ssd1306_Fill(Black);
	guiDrawBottomBox(buttonText);
	for (int i = 6; i < 12; i++)
	{
		ssd1306_SetCursor(0, (i - 6) * 8);
		ssd1306_WriteString(calibrationMessage[i], Font_6x8, White);
	}
	ssd1306_UpdateScreen();

	osDelay(2000);
	while (HAL_GPIO_ReadPin(BUTTON4_GPIO_Port, BUTTON4_Pin))
	{
		osDelay(10);
	}
	double adisGravity[18];
	double mpuGravity[18];
	double adisGyroOffset[3] = {0};
	double mpuGyroOffset[3] = {0};


	for (uint8_t edgeNumber = 1; edgeNumber < 7; edgeNumber++)
	{
		ssd1306_Fill(Black);
		guiDrawBottomBox(buttonText);
		ssd1306_SetCursor(0, 0);
		char edgeNumberString[22];
		snprintf(edgeNumberString, 22, "CALIBRATING EDGE %d/6", edgeNumber);
		ssd1306_WriteString(edgeNumberString, Font_7x10, White);
		ssd1306_UpdateScreen();

		for (uint8_t countdown = 5; countdown > 0; countdown--)
		{
			ssd1306_SetCursor(0, 20);
			char countdownString[22];
			snprintf(countdownString, 22, "Measuring in %d s", countdown);
			ssd1306_WriteString(countdownString, Font_7x10, White);
			ssd1306_UpdateScreen();
			osDelay(1000);
		}

		//start data acquisition
		adisDataStruc adisData =
		{ 0 };
		mpuDataStruc mpuData =
		{ 0 };
		adisDataStruc adisSum =
		{ 0 };
		mpuDataStruc mpuSum =
		{ 0 };
		for (uint8_t i = 0; i < 50; i++)
		{

			adisData = adisRead();
			mpuData = mpuRead();
			adisSum.accelX += adisData.accelX;
			adisSum.accelY += adisData.accelY;
			adisSum.accelZ += adisData.accelZ;
			adisSum.gyroX += adisData.gyroX;
			adisSum.gyroY += adisData.gyroY;
			adisSum.gyroZ += adisData.gyroZ;
			mpuSum.accelX += mpuData.accelX;
			mpuSum.accelY += mpuData.accelY;
			mpuSum.accelZ += mpuData.accelZ;
			mpuSum.gyroX += mpuData.gyroX;
			mpuSum.gyroY += mpuData.gyroY;
			mpuSum.gyroZ += mpuData.gyroZ;
		}

		adisGyroOffset[0] += adisSum.gyroX/50.0;
		adisGyroOffset[1] += adisSum.gyroY/50.0;
		adisGyroOffset[2] += adisSum.gyroZ / 50.0;
		mpuGyroOffset[0] += mpuSum.gyroX / 50.0;
		mpuGyroOffset[1] += mpuSum.gyroY / 50.0;
		mpuGyroOffset[2] += mpuSum.gyroZ / 50.0;

		adisGravity[0 + edgeNumber - 1] = adisSum.accelX / 50.0;
		adisGravity[6 + edgeNumber - 1] = adisSum.accelY / 50.0;
		adisGravity[12 + edgeNumber - 1] = adisSum.accelZ / 50.0;
		mpuGravity[0 + edgeNumber - 1] = mpuSum.accelX / 50.0;
		mpuGravity[6 + edgeNumber - 1] = mpuSum.accelY / 50.0;
		mpuGravity[12 + edgeNumber - 1] = mpuSum.accelZ / 50.0;

		ssd1306_SetCursor(0, 40);
		char completeString[22] = "Measurement complete";
		ssd1306_WriteString(completeString, Font_7x10, White);
		ssd1306_UpdateScreen();

		while (HAL_GPIO_ReadPin(BUTTON4_GPIO_Port, BUTTON4_Pin))
		{
			osDelay(10);
		}
	}

	double mpuFval[6];
	double mpuX[6];
	double adisFval[6];
	double adisX[6];
	double gravityScalar = 9.81275;

	AccelCalSolver(adisGravity, gravityScalar, adisX, adisFval);
	AccelCalSolver(mpuGravity, gravityScalar, mpuX, mpuFval);
	adisCal.accelGainX = adisX[0];
	adisCal.accelOffsetX = adisX[1];
	adisCal.accelGainY = adisX[2];
	adisCal.accelOffsetY = adisX[3];
	adisCal.accelGainZ = adisX[4];
	adisCal.accelOffsetZ = adisX[5];

	adisCal.gyroOffsetX = -adisGyroOffset[0]/6.0;
	adisCal.gyroOffsetY = -adisGyroOffset[1]/6.0;
	adisCal.gyroOffsetZ = -adisGyroOffset[2]/6.0;

	mpuCal.accelGainX = mpuX[0];
	mpuCal.accelOffsetX = mpuX[1];
	mpuCal.accelGainY = mpuX[2];
	mpuCal.accelOffsetY = mpuX[3];
	mpuCal.accelGainZ = mpuX[4];
	mpuCal.accelOffsetZ = mpuX[5];

	mpuCal.gyroOffsetX = -mpuGyroOffset[0]/6.0;
	mpuCal.gyroOffsetY = -mpuGyroOffset[1]/6.0;
	mpuCal.gyroOffsetZ = -mpuGyroOffset[2]/6.0;

	ssd1306_Fill(Black);
	guiDrawBottomBox(buttonText);
	ssd1306_SetCursor(0, 0);
	char completeCalString[22] = "Calibration complete";
	ssd1306_WriteString(completeCalString, Font_7x10, White);
	ssd1306_UpdateScreen();

	osDelay(1000);

	osThreadResume(adisTaskHandle);
	osThreadResume(mpuTaskHandle);

}

adisCalibrationStruc adisCalibrationConst(void)
{
	return adisCal;
}

mpuCalibrationStruc mpuCalibrationConst(void)
{
	return mpuCal;
}
