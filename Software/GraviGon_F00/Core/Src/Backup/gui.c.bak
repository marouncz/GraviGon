/*
 * gui.c
 *
 *  Created on: Apr 16, 2024
 *      Author: marou
 */

#include "main.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "gui.h"
#include <stdio.h>
#include "cmsis_os2.h"
#include <string.h>


uint8_t loggerOn = 0;

guiStateEnum guiState = INFO;
infoSubstateEnum infoSubstate = BOARD;

uint32_t loggingTime = 0;

uint8_t isLoggerOn(void)
{
	return loggerOn;
}

void guiDrawBottomBox(char buttonText[][5])
{
	ssd1306_Line(0, 52, 127, 52, White);
	ssd1306_Line(32, 52, 32, 63, White);
	ssd1306_Line(64, 52, 64, 63, White);
	ssd1306_Line(96, 52, 96, 63, White);


	ssd1306_SetCursor(2, 54);
	ssd1306_WriteString(buttonText[0], Font_7x10, White);

	ssd1306_SetCursor(35, 54);
	ssd1306_WriteString(buttonText[1], Font_7x10, White);

	ssd1306_SetCursor(67, 54);
	ssd1306_WriteString(buttonText[2], Font_7x10, White);

	ssd1306_SetCursor(99, 54);
	ssd1306_WriteString(buttonText[3], Font_7x10, White);
}

void guiStateMachine(guiInfoStruc *guiInfo)
{
	static uint8_t buttonState[4] = {0};
	static uint8_t prevButtonState[4] = {0};
	memcpy(buttonState, guiInfo->buttons, sizeof(buttonState));
	for(uint8_t i = 0; i < sizeof(buttonState); i++)
	{
		if(buttonState[i] == 1 && prevButtonState[i] == 0)
		{
			//button pressed
			if(i == 0)
			{
				infoSubstate++;
				if(infoSubstate == LAST)
				{
					infoSubstate = 0;
				}
			}

			if(i == 1)
			{
				ssd1306_Fill(Black);
				char buttonText[4][5] =
						{ "HOME", "RECD", "STOP", "CALB" };
				guiDrawBottomBox(buttonText);

				for (uint8_t countdown = 5; countdown > 0; countdown--)
				{
					ssd1306_SetCursor(0, 0);
					char countdownString[22];
					snprintf(countdownString, 22, "Recording in %d s",
							countdown);
					ssd1306_WriteString(countdownString, Font_7x10, White);
					ssd1306_UpdateScreen();
					osDelay(1000);
				}

				loggerOn = 1;
				loggingTime = HAL_GetTick();
				guiState = RECORD;
			}

			if(i == 2)
			{
				loggerOn = 0;
				guiState = INFO;
			}
			if(i == 3)
			{
				//calibration state machine
				loggerOn = 0;
				//calibrateAccel();



			}

		}
	}
	memcpy(prevButtonState, buttonState, sizeof(buttonState));

	char buttonText[4][5] =
		{ "HOME", "RECD", "STOP", "CALB" };

	switch (guiState)
	{
	case INFO:
		//gui handler for info screen
		printInfoScreen(guiInfo);

		break;
	case RECORD:
		//gui handler for recording screen

		ssd1306_Fill( Black);
		guiDrawBottomBox(buttonText);

		float recordingTime = (HAL_GetTick()-loggingTime)/1000.0f;

		char timeString[20] = "";
		snprintf(timeString, 20, "TIME: %.2f s",
				recordingTime);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(timeString, Font_7x10, White);

		ssd1306_UpdateScreen();
		osDelay(100);
		break;
	case STOP:
		//gui handler for stop screen
		break;
	case CALIBRATION:
		//gui handler for calibration screen
		break;

	}

}

void printInfoScreen(guiInfoStruc *guiInfo)
{
	char buttonText[4][5] =
	{ "HOME", "RECD", "STOP", "CALB" };

	switch (infoSubstate)
	{
	case BOARD:
		//
		ssd1306_Fill(Black);
		strcpy(buttonText[0], "HOME");
		guiDrawBottomBox(buttonText);

		char timeString[20] = "";
		snprintf(timeString, 20, "UTC: %02d:%02d:%02d",
				guiInfo->boardStats.sTime.Hours,
				guiInfo->boardStats.sTime.Minutes,
				guiInfo->boardStats.sTime.Seconds);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(timeString, Font_7x10, White);

		char voltageString[15];
		if (guiInfo->boardStats.usbVoltage > 2.0)
		{
			//do not display battery voltage, charging
			strcpy(voltageString, "BATT: CHARGING");
			ssd1306_SetCursor(0, 10);
			ssd1306_WriteString(voltageString, Font_7x10, White);
		}
		else
		{
			snprintf(voltageString, 15, "BATT: %.2f V  ",
					guiInfo->boardStats.battVoltage);
			ssd1306_SetCursor(0, 10);
			ssd1306_WriteString(voltageString, Font_7x10, White);
		}

		char tempString[17];
		snprintf(tempString, 17, "TEMP: %.1f degC",
				guiInfo->boardStats.mcuTemp);
		ssd1306_SetCursor(0, 20);
		ssd1306_WriteString(tempString, Font_7x10, White);

		char supplyString[17];
		snprintf(supplyString, 17, "PSU: %.2f V  ",
				guiInfo->boardStats.supplyVoltage);
		ssd1306_SetCursor(0, 30);
		ssd1306_WriteString(supplyString, Font_7x10, White);

		ssd1306_UpdateScreen();
		osDelay(100);

		break;
	case MPU6050:
		//
		ssd1306_Fill(Black);
		strcpy(buttonText[0], "MPU ");
		guiDrawBottomBox(buttonText);

		char mpuAxisHeader[20] =  "[rad/s]  [m/s^2]";
		ssd1306_SetCursor(20, 0);
		ssd1306_WriteString(mpuAxisHeader, Font_6x8, White);

		char mpuAxisStringX[17];
		snprintf(mpuAxisStringX, 17, "X: %+06.2f %+06.2f", guiInfo->mpu.gyroX,
				guiInfo->mpu.accelX);
		ssd1306_SetCursor(0, 10);
		ssd1306_WriteString(mpuAxisStringX, Font_7x10, White);
		char mpuAxisStringY[17];
		snprintf(mpuAxisStringY, 17, "Y: %+06.2f %+06.2f", guiInfo->mpu.gyroY,
				guiInfo->mpu.accelY);
		ssd1306_SetCursor(0, 20);
		ssd1306_WriteString(mpuAxisStringY, Font_7x10, White);
		char mpuAxisStringZ[17];
		snprintf(mpuAxisStringZ, 17, "Z: %+06.2f %+06.2f", guiInfo->mpu.gyroZ,
				guiInfo->mpu.accelZ);
		ssd1306_SetCursor(0, 30);
		ssd1306_WriteString(mpuAxisStringZ, Font_7x10, White);

		ssd1306_UpdateScreen();
		osDelay(100);
		break;
	case ADIS:
		//
		ssd1306_Fill(Black);
		strcpy(buttonText[0], "ADIS");
		guiDrawBottomBox(buttonText);

		char AdisAxisHeader[20] = "[rad/s]  [m/s^2]";
		ssd1306_SetCursor(20, 0);
		ssd1306_WriteString(AdisAxisHeader, Font_6x8, White);

		char AdisAxisStringX[17];
		snprintf(AdisAxisStringX, 17, "X: %+06.2f %+06.2f", guiInfo->adis.gyroX,
				guiInfo->adis.accelX);
		ssd1306_SetCursor(0, 10);
		ssd1306_WriteString(AdisAxisStringX, Font_7x10, White);
		char AdisAxisStringY[17];
		snprintf(AdisAxisStringY, 17, "Y: %+06.2f %+06.2f", guiInfo->adis.gyroY,
				guiInfo->adis.accelY);
		ssd1306_SetCursor(0, 20);
		ssd1306_WriteString(AdisAxisStringY, Font_7x10, White);
		char AdisAxisStringZ[17];
		snprintf(AdisAxisStringZ, 17, "Z: %+06.2f %+06.2f", guiInfo->adis.gyroZ,
				guiInfo->adis.accelZ);
		ssd1306_SetCursor(0, 30);
		ssd1306_WriteString(AdisAxisStringZ, Font_7x10, White);

		char dataCntString[17];
		snprintf(dataCntString, 17, "dataCNT: %lu",
				guiInfo->adis.dataCNT);
		ssd1306_SetCursor(0, 42);
		ssd1306_WriteString(dataCntString, Font_6x8, White);

		ssd1306_UpdateScreen();
		osDelay(100);
		break;
	case LSM:
		//
		ssd1306_Fill(Black);
		strcpy(buttonText[0], "LSM ");
		guiDrawBottomBox(buttonText);


		char LsmAxisHeader[20] = "[uT]";
		ssd1306_SetCursor(20, 0);
		ssd1306_WriteString(LsmAxisHeader, Font_6x8, White);

		char LsmAxisStringX[17];
		snprintf(LsmAxisStringX, 17, "X: %+07.2f", guiInfo->lsm.magX);
		ssd1306_SetCursor(0, 10);
		ssd1306_WriteString(LsmAxisStringX, Font_7x10, White);

		char LsmAxisStringY[17];
		snprintf(LsmAxisStringY, 17, "Y: %+07.2f", guiInfo->lsm.magY);
		ssd1306_SetCursor(0, 20);
		ssd1306_WriteString(LsmAxisStringY, Font_7x10, White);

		char LsmAxisStringZ[17];
		snprintf(LsmAxisStringZ, 17, "Z: %+07.2f", guiInfo->lsm.magZ);
		ssd1306_SetCursor(0, 30);
		ssd1306_WriteString(LsmAxisStringZ, Font_7x10, White);


		ssd1306_UpdateScreen();
		osDelay(100);
		break;
	case GNSS:
		//
		ssd1306_Fill(Black);
		strcpy(buttonText[0], "GNSS");
		guiDrawBottomBox(buttonText);
		char fixType[6][19] =
		{ "GPS: No Fix       ", "GPS: DR only      ", "GPS: 2D-Fix       ",
				"GPS: 3D-Fix       ", "GPS: Time only fix" };
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(fixType[guiInfo->gnss.fixType], Font_7x10, White);

		char latitudeString[19];
		snprintf(latitudeString, 19, "LAT: %+02.9f", guiInfo->gnss.fLat);
		ssd1306_SetCursor(0, 10);
		ssd1306_WriteString(latitudeString, Font_7x10, White);

		char longitudeString[19];
		snprintf(longitudeString, 19, "LON: %+02.9f", guiInfo->gnss.fLon);
		ssd1306_SetCursor(0, 20);
		ssd1306_WriteString(longitudeString, Font_7x10, White);

		ssd1306_UpdateScreen();
		osDelay(100);
		break;
	case LAST:
		break;

	}

}



