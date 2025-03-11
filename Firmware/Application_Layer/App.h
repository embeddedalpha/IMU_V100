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

#define Modbus_Device_Address 15
#define Modbus_Baudrate 9600

#define MAX_Registers 20
#define Data_Size 10
#define NA 0



extern Modbus_Register_Map_Instance Register_Table[MAX_Registers];




#define Device_Version_Addr  0x100
#define Device_Address_Addr  0x101
#define Firmware_Version_Addr 0x102

// struct IMU_Register_Map{
//
//
//	// Holding Registers
//	Modbus_Register_Map_Instance Device_Version; 		//R 0x100
//	Modbus_Register_Map_Instance Device_Address;		//R 0x101
//	Modbus_Register_Map_Instance Firmware_Version;		//R 0x102
//	Modbus_Register_Map_Instance Power_Health_Check;	//R 0x103
//	Modbus_Register_Map_Instance Life_Time_Counter;		//R 0x104
//	Modbus_Register_Map_Instance System_Up_Time;		//R 0x105
//	Modbus_Register_Map_Instance Device_Health_Check;	//R 0x106
//
//	// Write Single Holding Register
//	Modbus_Register_Map_Instance Reset_Device;			//W 0x201
//
//	// Read Input Registers
//	Modbus_Register_Map_Instance Accelerometer_Data;//R
//	Modbus_Register_Map_Instance Gyroscope_Data;//R
//	Modbus_Register_Map_Instance Magnetometer_Data;//R
//	Modbus_Register_Map_Instance Quaternions_Data;//R
//	Modbus_Register_Map_Instance Euler_Angles_Data;
//	Modbus_Register_Map_Instance Linear_Velocity_Data; //R
//	Modbus_Register_Map_Instance Angular_Velocity_Data; //R
//
//	// Write Multiple Holding Registers
//	Modbus_Register_Map_Instance Accelerometer_Scaling_Factor;
//	Modbus_Register_Map_Instance Gyroscope_Scaling_Factor;
//	Modbus_Register_Map_Instance Magnetometer_Scaling_Factor;
//
//
//
//}IMU_Register_Map;

void IMUV100_Modbus_Register_Map_Setup(void);
void IMUV100_Modbus_Comm_Setup(void);
void IMUV100_Modbus_Command_Process(void);

#endif /* APP_H_ */
