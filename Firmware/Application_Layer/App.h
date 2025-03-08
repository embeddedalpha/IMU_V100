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









struct IMU_Register_Map{

	Modbus_Register_Map_Instance Device_Version; //R
	Modbus_Register_Map_Instance Device_Address;//R
	Modbus_Register_Map_Instance Firmware_Version;//R

	Modbus_Register_Map_Instance Power_Health_Check;//R
	Modbus_Register_Map_Instance Life_Time_Counter;//R
	Modbus_Register_Map_Instance System_Up_Time;//R
	Modbus_Register_Map_Instance Device_Health_Check;//R
	Modbus_Register_Map_Instance Accelerometer_Health_Check;//R
	Modbus_Register_Map_Instance Gyroscope_Health_Check;//R
	Modbus_Register_Map_Instance Magnetometer_Health_Check;//R
	Modbus_Register_Map_Instance GNSS_Health_Check;//R

	Modbus_Register_Map_Instance Reset_Device;//W

	Modbus_Register_Map_Instance Accelerometer_Data;//R
	Modbus_Register_Map_Instance Gyroscope_Data;//R
	Modbus_Register_Map_Instance Magnetometer_Data;//R
	Modbus_Register_Map_Instance Quaternion_Data;//R

	Modbus_Register_Map_Instance Linear_Velocity_Data; //R
	Modbus_Register_Map_Instance Angular_Velocity_Data; //R


}IMU_Register_Map;

void Modbus_Register_Map_Setup(void);
void Modbus_Comm_Setup(void);

#endif /* APP_H_ */
