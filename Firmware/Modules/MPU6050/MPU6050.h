/*
 * MPU6050.h
 *
 *  Created on: Feb 1, 2025
 *      Author: kunal
 */

#ifndef MPU6050_MPU6050_H_
#define MPU6050_MPU6050_H_

#include "main.h"
#include "I2C/I2C.h"
#include "GPIO/GPIO.h"
#include "MPU6050_Regs.h"

typedef struct MPU6050_Config
{
	I2C_TypeDef Port;
	int Sampling_Rate;

}MPU6050_Config;


int MPU6050_Init(MPU6050_Config *mpu6050);
int MPU6050_Get_Raw(MPU6050_Config *mpu6050);


#endif /* MPU6050_MPU6050_H_ */
