/*
 * App.c
 *
 *  Created on: Mar 4, 2025
 *      Author: kunal
 */


#include "App.h"



void Modbus_Register_Map_Setup(void)
{
	IMU_Register_Map.Device_Address.Access_Type = Modbus_Register_Map_configuration.Access.Read;
	IMU_Register_Map.Device_Address.Register_Address = 0x0100;
	IMU_Register_Map.Device_Address.Number_Of_Registers = 1;
	IMU_Register_Map.Device_Address.Data[0] = 0x0010;

	IMU_Register_Map.Device_Version.Access_Type = Modbus_Register_Map_configuration.Access.Read;
	IMU_Register_Map.Device_Version.Register_Address = 0x0101;
	IMU_Register_Map.Device_Version.Number_Of_Registers = 1;
	IMU_Register_Map.Device_Version.Data[0] = 0x0001;

	IMU_Register_Map.Firmware_Version.Access_Type = Modbus_Register_Map_configuration.Access.Read;
	IMU_Register_Map.Firmware_Version.Register_Address = 0x0102;
	IMU_Register_Map.Firmware_Version.Number_Of_Registers = 1;
	IMU_Register_Map.Firmware_Version.Data[0] = 0x0001;

	IMU_Register_Map.Reset_Device.Access_Type = Modbus_Register_Map_configuration.Access.Write;
	IMU_Register_Map.Reset_Device.Register_Address = 0x0103;
	IMU_Register_Map.Reset_Device.Number_Of_Registers = 1;
	IMU_Register_Map.Reset_Device.Data[0] = 0x0000;

	IMU_Register_Map.System_Up_Time.Access_Type = Modbus_Register_Map_configuration.Access.Write;
	IMU_Register_Map.System_Up_Time.Register_Address = 0x0103;
	IMU_Register_Map.System_Up_Time.Number_Of_Registers = 1;
	IMU_Register_Map.System_Up_Time.Data[0] = 0x0000;


/**********************************************************************************************************/
	IMU_Register_Map.Accelerometer_Data.Access_Type = Modbus_Register_Map_configuration.Access.Read;
	IMU_Register_Map.Accelerometer_Data.Register_Address = 0x0103;
	IMU_Register_Map.Accelerometer_Data.Number_Of_Registers = 3;
	IMU_Register_Map.Accelerometer_Data.Data[0] = 0x0000;
	IMU_Register_Map.Accelerometer_Data.Data[1] = 0x0000;
	IMU_Register_Map.Accelerometer_Data.Data[2] = 0x0000;

	IMU_Register_Map.Gyroscope_Data.Access_Type = Modbus_Register_Map_configuration.Access.Read;
	IMU_Register_Map.Gyroscope_Data.Register_Address = 0x010D;
	IMU_Register_Map.Gyroscope_Data.Number_Of_Registers = 3;
	IMU_Register_Map.Gyroscope_Data.Data[0] = 0x0000;
	IMU_Register_Map.Gyroscope_Data.Data[1] = 0x0000;
	IMU_Register_Map.Gyroscope_Data.Data[2] = 0x0000;

	IMU_Register_Map.Magnetometer_Data.Access_Type = Modbus_Register_Map_configuration.Access.Read;
	IMU_Register_Map.Magnetometer_Data.Register_Address = 0x010E;
	IMU_Register_Map.Magnetometer_Data.Number_Of_Registers = 3;
	IMU_Register_Map.Magnetometer_Data.Data[0] = 0x0000;
	IMU_Register_Map.Magnetometer_Data.Data[1] = 0x0000;
	IMU_Register_Map.Magnetometer_Data.Data[2] = 0x0000;

	IMU_Register_Map.Quaternion_Data.Access_Type = Modbus_Register_Map_configuration.Access.Read;
	IMU_Register_Map.Quaternion_Data.Register_Address = 0x010F;
	IMU_Register_Map.Quaternion_Data.Number_Of_Registers = 4;
	IMU_Register_Map.Quaternion_Data.Data[0] = 0x0000;
	IMU_Register_Map.Quaternion_Data.Data[1] = 0x0000;
	IMU_Register_Map.Quaternion_Data.Data[2] = 0x0000;
	IMU_Register_Map.Quaternion_Data.Data[3] = 0x0000;
/**********************************************************************************************************/

}
