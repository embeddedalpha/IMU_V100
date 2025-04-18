/*
 * BMP280.h
 *
 *  Created on: Feb 3, 2025
 *      Author: kunal
 */

#ifndef BAROMETER_BMP280_H_
#define BAROMETER_BMP280_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "I2C/I2C.h"






void BMP280_Init(void);
void BMP280_Get_Data(void);


#endif /* BAROMETER_BMP280_H_ */
