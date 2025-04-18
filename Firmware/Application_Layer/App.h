/*
 * App.h
 *
 *  Created on: Mar 4, 2025
 *      Author: kunal
 */

#ifndef APP_H_
#define APP_H_



#include "main.h"
#include "Modbus/Modbus.h"


extern volatile uint32_t Life_Time_Counter_Value;

#define Modbus_Device_Address 15
#define Modbus_Baudrate 9600

#define MAX_Registers 20
#define Data_Size 10
#define NA 0






extern Modbus_Register_Map_Instance Register_Table[MAX_Registers];

#define		IMU_Device_Version					(0x101)
#define		IMUV100_Address						(0x102)
#define		IMU_Firmware_Version				(0x103)
#define		Power_Health_Check					(0x104)
#define		Life_Time_Counter					(0x105)
#define		System_Up_Time						(0x106)
#define		Device_Health_Check					(0x107)
#define		Scaling_Factors_Accelerometer		(0x108)
#define		Scaling_Factors_Gyroscope			(0x109)
#define		Scaling_Factors_Magnetometer		(0x10A)
#define		Accelerometer_Data					(0x10B)
#define		Gyroscope_Data						(0x10C)
#define		Magnetometer_Data					(0x10D)
#define		Quaternions_Data					(0x10E)
#define		Euler_Angles_Data					(0x10F)
#define		Linear_Velocity_Data				(0x110)
#define		Angular_Velocity_Data				(0x111)
#define		Reset_Device						(0x112)
#define		Start_Calibration					(0x113)
#define		Accelerometer_Scaling_Factor		(0x114)
#define		Gyroscope_Scaling_Factor			(0x115)
#define		Magnetometer_Scaling_Factor			(0x116)

extern Modbus_Register_Map_Instance RTable[MAX_Registers];


void IMUV100_Modbus_Comm_Setup(void);
void IMUV100_Modbus_Command_Process(void);

void IMUV100_CAN_Comm_Setup(void);
void IMUV100_CAN_Command_Process(void);
//void IMUV100_Modbus_Command_Process(void);

#endif /* APP_H_ */
