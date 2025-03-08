/*
 * App.c
 *
 *  Created on: Mar 4, 2025
 *      Author: kunal
 */


#include "App.h"

Modbus_Config IMUv100_Modbus;

void Modbus_Register_Map_Setup(void)
{
	IMU_Register_Map.Device_Address.Access_Type = Modbus_Register_Map_configuration.Access.Read;
	IMU_Register_Map.Device_Address.Registered_Function_Code = Modbus_Configuration.Acceptable_Function_Codes.Read_Holding_Registers;
	IMU_Register_Map.Device_Address.Register_Address = 0x0100;
	IMU_Register_Map.Device_Address.Number_Of_Registers = 1;
	IMU_Register_Map.Device_Address.Data[0] = 0x0010;

	IMU_Register_Map.Device_Version.Access_Type = Modbus_Register_Map_configuration.Access.Read;
	IMU_Register_Map.Device_Version.Registered_Function_Code = Modbus_Configuration.Acceptable_Function_Codes.Read_Holding_Registers;
	IMU_Register_Map.Device_Version.Register_Address = 0x0101;
	IMU_Register_Map.Device_Version.Number_Of_Registers = 1;
	IMU_Register_Map.Device_Version.Data[0] = 0x0001;

	IMU_Register_Map.Firmware_Version.Access_Type = Modbus_Register_Map_configuration.Access.Read;
	IMU_Register_Map.Device_Version.Registered_Function_Code = Modbus_Configuration.Acceptable_Function_Codes.Read_Holding_Registers;
	IMU_Register_Map.Firmware_Version.Register_Address = 0x0102;
	IMU_Register_Map.Firmware_Version.Number_Of_Registers = 1;
	IMU_Register_Map.Firmware_Version.Data[0] = 0x0001;

	IMU_Register_Map.Reset_Device.Access_Type = Modbus_Register_Map_configuration.Access.Write;
	IMU_Register_Map.Device_Version.Registered_Function_Code = Modbus_Configuration.Acceptable_Function_Codes.Read_Holding_Registers;
	IMU_Register_Map.Reset_Device.Register_Address = 0x0103;
	IMU_Register_Map.Reset_Device.Number_Of_Registers = 1;
	IMU_Register_Map.Reset_Device.Data[0] = 0x0000;

	IMU_Register_Map.System_Up_Time.Access_Type = Modbus_Register_Map_configuration.Access.Write;
	IMU_Register_Map.Device_Version.Registered_Function_Code = Modbus_Configuration.Acceptable_Function_Codes.Read_Holding_Registers;
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

void Modbus_Comm_Setup(void)
{
	IMUv100_Modbus.Acceptable_Functions = Modbus_Configuration.Acceptable_Function_Codes.Read_Holding_Registers | Modbus_Configuration.Acceptable_Function_Codes.Read_Input_Registers |
			                              Modbus_Configuration.Acceptable_Function_Codes.Write_Single_Register | Modbus_Configuration.Acceptable_Function_Codes.Write_Multiple_Registers;

	IMUv100_Modbus.Device_Address = Modbus_Device_Address;
	IMUv100_Modbus.Device_Type = Modbus_Configuration.Device_Type.Slave;

    IMUv100_Modbus.UART_Device.Port = USART1;
    IMUv100_Modbus.UART_Device.baudrate = Modbus_Baudrate;
    IMUv100_Modbus.UART_Device.mode = USART_Configuration.Mode.Asynchronous;
    IMUv100_Modbus.UART_Device.stop_bits = USART_Configuration.Stop_Bits.Bit_1;
    IMUv100_Modbus.UART_Device.TX_Pin = USART1_TX_Pin.PA9;
    IMUv100_Modbus.UART_Device.RX_Pin = USART1_RX_Pin.PA10;
    IMUv100_Modbus.UART_Device.interrupt = USART_Configuration.Interrupt_Type.IDLE_Enable;
    IMUv100_Modbus.UART_Device.dma_enable = USART_Configuration.DMA_Enable.TX_Enable | USART_Configuration.DMA_Enable.RX_Enable;

    Modbus_Init(&IMUv100_Modbus);



}
