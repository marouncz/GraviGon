/*
 * lsm.h
 *
 *  Created on: Feb 13, 2024
 *      Author: marou
 */

#ifndef INC_LSM_H_
#define INC_LSM_H_

#include <stdint.h>
#include "main.h"

void lsmInit(void);

lsmDataStruc lsmRead(void);

void lsmTriggerDMA(void);

void lsmReleaseSemaphore(void);

#endif /* INC_LSM_H_ */
