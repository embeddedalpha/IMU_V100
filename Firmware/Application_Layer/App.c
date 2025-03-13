/*
 * App.c
 *
 *  Created on: Mar 4, 2025
 *      Author: kunal
 */


#include "App.h"

Modbus_Config IMUv100_Modbus;

void IMUV100_Modbus_Register_Map_Setup(void)
{
	int data[10];

	data[0] = 0x0001;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Holding_Registers,Device_Version,data,1);
	data[0] = 0x0001;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Holding_Registers,Device_Address_,data,1);
	data[0] = 0x0001;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Holding_Registers,Firmware_Version,data,1);
	data[0] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Holding_Registers,Power_Health_Check,data,1);
	data[0] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Holding_Registers,Life_Time_Counter,data,1);
	data[0] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Holding_Registers,System_Up_Time,data,1);
	data[0] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Holding_Registers,Device_Health_Check,data,1);
	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Holding_Registers,Scaling_Factors_Accelerometer,data,3);
	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Holding_Registers,Scaling_Factors_Gyroscope,data,3);
	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Holding_Registers,Scaling_Factors_Magnetometer,data,3);


	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Input_Registers,Accelerometer_Data,data,3);
	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Input_Registers,Gyroscope_Data,data,3);
	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Input_Registers,Magnetometer_Data,data,3);
	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	data[3] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Input_Registers,Quaternions_Data,data,4);
	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Input_Registers,Euler_Angles_Data,data,3);
	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Input_Registers,Linear_Velocity_Data,data,3);
	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Read_Input_Registers,Angular_Velocity_Data,data,3);

	data[0] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Write_Single_Register,Reset_Device,data,1);
	data[0] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Write_Single_Register,Start_Calibration,data,1);
	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Write_Multiple_Registers,Accelerometer_Scaling_Factor,data,3);
	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Write_Multiple_Registers,Gyroscope_Scaling_Factor,data,3);
	data[0] = 0x0000;
	data[1] = 0x0000;
	data[2] = 0x0000;
	Add_Command(&IMUv100_Modbus,Register_Table,Write_Multiple_Registers,Magnetometer_Scaling_Factor,data,3);



}

//void IMUV100_Modbus_Command_Process(void){
//	uint8_t buffer[100];
//
//	if(IMUv100_Modbus.Modbus_Slave_Processor_Flag)
//	{
//		switch (IMUv100_Modbus.Payload.Function_Code) {
//			case Read_Holding_Registers:
//			{
//				switch ((int)IMUv100_Modbus.Payload.Register_Address)
//				{
//					case (Device_Version_Addr):
//					{
//						// Modbus Send Response;
//						buffer[0] = IMUv100_Modbus.Device_Address;
//						buffer[1] = Read_Holding_Registers;
//						buffer[2] = 1;
//						buffer[3] = (IMU_Register_Map.Device_Version.Data[0] & 0xFF00)>>8;
//						buffer[4] = (IMU_Register_Map.Device_Version.Data[0] & 0x00FF)>>0;
//
//						Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 5);
//
//					}
//						break;
//
//					case (Device_Address_Addr):
//					{
//						// Modbus Send Response;
//						buffer[0] = IMUv100_Modbus.Device_Address;
//						buffer[1] = Read_Holding_Registers;
//						buffer[2] = 1;
//						buffer[3] = (IMU_Register_Map.Device_Address.Data[0] & 0xFF00)>>8;
//						buffer[4] = (IMU_Register_Map.Device_Address.Data[0] & 0x00FF)>>0;
//						Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 5);
//
//					}
//						break;
//
//					case (Firmware_Version_Addr):
//					{
//						// Modbus Send Response;
//						buffer[0] = IMUv100_Modbus.Device_Address;
//						buffer[1] = Read_Holding_Registers;
//						buffer[2] = 1;
//						buffer[3] = (IMU_Register_Map.Firmware_Version.Data[0] & 0xFF00)>>8;
//						buffer[4] = (IMU_Register_Map.Firmware_Version.Data[0] & 0x00FF)>>0;
//						Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 5);
//
//					}
//						break;
//
//
//				}
//
//			}
//				break;
//
//			case Read_Input_Registers:
//			{
//
//			}
//				break;
//
//			case Write_Single_Register:
//			{
//
//			}
//				break;
//
//			case Write_Multiple_Registers:
//			{
//
//			}
//				break;
//
//			case Read_Coil_Registers:
//			{
//				buffer[0] = IMUv100_Modbus.Device_Address;
//				buffer[1] =  0x80;
//				buffer[2] = 1;
//				Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 3);
//			}
//			break;
//
//
//
//			case Write_Single_Coil:
//			{
//				buffer[0] = IMUv100_Modbus.Device_Address;
//				buffer[1] =  Write_Single_Coil| 0x80;
//				buffer[2] = 1;
//				Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 3);
//			}
//			break;
//
//			case Read_Discrete_Inputs:
//			{
//				buffer[0] = IMUv100_Modbus.Device_Address;
//				buffer[1] =  Read_Discrete_Inputs| 0x80;
//				buffer[2] = 1;
//				Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 3);
//			}
//			break;
//
//			case Write_Multiple_Coils:
//			{
//				buffer[0] = IMUv100_Modbus.Device_Address;
//				buffer[1] =  Write_Multiple_Coils| 0x80;
//				buffer[2] = 1;
//				Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 3);
//			}
//			break;
//
//
//
//
//		}
//
//	}
//}

void IMUV100_Modbus_Comm_Setup(void)
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

//    IMUv100_Modbus.Modbus_Slave_Processor = IMUV100_Modbus_Command_Process;







}
