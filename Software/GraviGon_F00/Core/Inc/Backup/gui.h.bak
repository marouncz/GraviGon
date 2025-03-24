/*
 * gui.h
 *
 *  Created on: Apr 16, 2024
 *      Author: marou
 */

#ifndef INC_GUI_H_
#define INC_GUI_H_

typedef enum
{
	INFO,
	RECORD,
	STOP,
	CALIBRATION

}guiStateEnum;

typedef enum
{
	BOARD,
	MPU6050,
	ADIS,
	LSM,
	GNSS,
	LAST
}infoSubstateEnum;


uint8_t isLoggerOn(void);


void guiDrawBottomBox(char buttonText[][5]);

void guiStateMachine(guiInfoStruc* guiInfo);

void printInfoScreen(guiInfoStruc* guiInfo);


#endif /* INC_GUI_H_ */
