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







#define Device_Version_Addr  0x100
#define Device_Address_Addr  0x101
#define Firmware_Version_Addr 0x102

 struct IMU_Register_Map{


	// Holding Registers
	Modbus_Register_Map_Instance Device_Version; 		//R 0x100
	Modbus_Register_Map_Instance Device_Address;		//R 0x101
	Modbus_Register_Map_Instance Firmware_Version;		//R 0x102
	Modbus_Register_Map_Instance Power_Health_Check;	//R 0x103
	Modbus_Register_Map_Instance Life_Time_Counter;		//R 0x104
	Modbus_Register_Map_Instance System_Up_Time;		//R 0x105
	Modbus_Register_Map_Instance Device_Health_Check;	//R 0x106

	// Write Single Holding Register
	Modbus_Register_Map_Instance Reset_Device;			//W 0x201

	// Read Input Registers
	Modbus_Register_Map_Instance Accelerometer;//R
	Modbus_Register_Map_Instance Gyroscope;//R
	Modbus_Register_Map_Instance Magnetometer;//R
	Modbus_Register_Map_Instance Quaternions;//R
	Modbus_Register_Map_Instance Euler_Angles;
	Modbus_Register_Map_Instance Linear_Velocity; //R
	Modbus_Register_Map_Instance Angular_Velocity; //R

	// Write Multiple Holding Registers
	Modbus_Register_Map_Instance Accelerometer_Scaling_Factor;
	Modbus_Register_Map_Instance Gyroscope_Scaling_Factor;
	Modbus_Register_Map_Instance Magnetometer_Scaling_Factor;



}IMU_Register_Map;

void Modbus_Register_Map_Setup(void);
void Modbus_Comm_Setup(void);

#endif /* APP_H_ */
