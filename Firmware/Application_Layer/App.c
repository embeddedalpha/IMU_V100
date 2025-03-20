/*
 * App.c
 *
 *  Created on: Mar 4, 2025
 *      Author: kunal
 */


#include "App.h"

Modbus_Config IMUv100_Modbus;

Modbus_Register_Map_Instance RTable[] = {

		{Read_Holding_Registers, IMU_Device_Version, {0x0001}},
		{Read_Holding_Registers, IMU_Firmware_Version, {0x0001}},
		{Read_Holding_Registers, Life_Time_Counter, {0x0000,0x0000}},
		{Read_Holding_Registers, System_Up_Time, {0x0000,0x0000}},
		{Read_Holding_Registers, Device_Health_Check, {0x0001}},
		{Read_Holding_Registers, Scaling_Factors_Accelerometer, {0x0000,0x0000,0x0000}},
		{Read_Holding_Registers, Scaling_Factors_Gyroscope, {0x0000,0x0000,0x0000}},
		{Read_Holding_Registers, Scaling_Factors_Magnetometer, {0x0000,0x0000,0x0000}},

		{Read_Input_Registers, Accelerometer_Data, {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000}},
		{Read_Input_Registers, Gyroscope_Data, {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000}},
		{Read_Input_Registers, Magnetometer_Data, {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000}},
		{Read_Input_Registers, Quaternions_Data, {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000}},
		{Read_Input_Registers, Euler_Angles_Data, {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000}},
		{Read_Input_Registers, Linear_Velocity_Data, {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000}},
		{Read_Input_Registers, Angular_Velocity_Data, {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000}},

		{Write_Single_Register, Reset_Device, {0x0000}},
		{Write_Single_Register, Start_Calibration, {0x0000}},

		{Write_Multiple_Registers, Accelerometer_Scaling_Factor, {0x0000,0x0000,0x0000}},
		{Write_Multiple_Registers, Gyroscope_Scaling_Factor, {0x0000,0x0000,0x0000}},
		{Write_Multiple_Registers, Magnetometer_Scaling_Factor, {0x0000,0x0000,0x0000}},


};



void IMUV100_Modbus_Command_Process(void){
	uint8_t buffer[100];

	if(IMUv100_Modbus.Modbus_Slave_Processor_Flag)
	{



		Modbus_Register_Map_Instance* found = Search_Commands(&IMUv100_Modbus, IMUv100_Modbus.Payload.Function_Code, IMUv100_Modbus.Payload.Register_Address, RTable);

		if(found)
		{
			switch (found->Function_Code)
			{
				case Read_Holding_Registers:
				{
					switch (found->Register_Address) {
						case IMU_Device_Version:
						{
							buffer[0] = IMUv100_Modbus.Device_Address;
							buffer[1] = Read_Holding_Registers;
							buffer[2] = 2;
							buffer[3] = found->Data[0] ;
							buffer[4] = found->Data[1] ;
							Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 5);
						}
							break;

						case IMUV100_Address:
						{
							buffer[0] = IMUv100_Modbus.Device_Address;
							buffer[1] = Read_Holding_Registers;
							buffer[2] = 2;
							buffer[3] = found->Data[0] ;
							buffer[4] = found->Data[1] ;
							Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 5);
						}
							break;

						case IMU_Firmware_Version:
						{
							buffer[0] = IMUv100_Modbus.Device_Address;
							buffer[1] = Read_Holding_Registers;
							buffer[2] = 2;
							buffer[3] = found->Data[0] ;
							buffer[4] = found->Data[1] ;
							Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 5);
						}
							break;

						case Power_Health_Check:
						{
							buffer[0] = IMUv100_Modbus.Device_Address;
							buffer[1] = Read_Holding_Registers;
							buffer[2] = 2;
							buffer[3] = found->Data[0] ;
							buffer[4] = found->Data[1] ;
							Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 5);
						}
							break;

						case Life_Time_Counter:
						{
							buffer[0] = IMUv100_Modbus.Device_Address;
							buffer[1] = Read_Holding_Registers;
							buffer[2] = 4;
							buffer[3] = found->Data[0] ;
							buffer[4] = found->Data[1] ;
							buffer[5] = found->Data[2] ;
							buffer[6] = found->Data[3] ;
							Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 7);
						}
							break;
						default:
						{

						}
							break;
					}

				}
					break;


				case Read_Input_Registers:
				{
					switch (found->Register_Address) {
						case Accelerometer_Data:
						{
							buffer[0] = IMUv100_Modbus.Device_Address;
							buffer[1] = Read_Input_Registers;
							buffer[2] = 6;
							buffer[3] = found->Data[0] ;
							buffer[4] = found->Data[1] ;
							buffer[5] = found->Data[2] ;
							buffer[6] = found->Data[3] ;
							buffer[7] = found->Data[4] ;
							buffer[8] = found->Data[5] ;
							Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 9);

						}
							break;
						case Gyroscope_Data:
							{
								buffer[0] = IMUv100_Modbus.Device_Address;
								buffer[1] = Read_Input_Registers;
								buffer[2] = 6;
								buffer[3] = found->Data[0] ;
								buffer[4] = found->Data[1] ;
								buffer[5] = found->Data[2] ;
								buffer[6] = found->Data[3] ;
								buffer[7] = found->Data[4] ;
								buffer[8] = found->Data[5] ;
								Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 9);

							}
								break;

						case Gyroscope_Data:
							{
								buffer[0] = IMUv100_Modbus.Device_Address;
								buffer[1] = Read_Input_Registers;
								buffer[2] = 6;
								buffer[3] = found->Data[0] ;
								buffer[4] = found->Data[1] ;
								buffer[5] = found->Data[2] ;
								buffer[6] = found->Data[3] ;
								buffer[7] = found->Data[4] ;
								buffer[8] = found->Data[5] ;
								Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 9);

							}
								break;

						case Magnetometer_Data:
							{
								buffer[0] = IMUv100_Modbus.Device_Address;
								buffer[1] = Read_Input_Registers;
								buffer[2] = 6;
								buffer[3] = found->Data[0] ;
								buffer[4] = found->Data[1] ;
								buffer[5] = found->Data[2] ;
								buffer[6] = found->Data[3] ;
								buffer[7] = found->Data[4] ;
								buffer[8] = found->Data[5] ;
								Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 9);

							}
								break;

						case Quaternions_Data:
							{
								buffer[0] = IMUv100_Modbus.Device_Address;
								buffer[1] = Read_Input_Registers;
								buffer[2] = 8;
								buffer[3] = found->Data[0] ;
								buffer[4] = found->Data[1] ;
								buffer[5] = found->Data[2] ;
								buffer[6] = found->Data[3] ;
								buffer[7] = found->Data[4] ;
								buffer[8] = found->Data[5] ;
								buffer[9] = found->Data[6] ;
								buffer[10] = found->Data[7] ;
								Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 11);

							}
								break;

						case Euler_Angles_Data:
							{
								buffer[0] = IMUv100_Modbus.Device_Address;
								buffer[1] = Read_Input_Registers;
								buffer[2] = 6;
								buffer[3] = found->Data[0] ;
								buffer[4] = found->Data[1] ;
								buffer[5] = found->Data[2] ;
								buffer[6] = found->Data[3] ;
								buffer[7] = found->Data[4] ;
								buffer[8] = found->Data[5] ;
								Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 9);

							}
								break;

						case Linear_Velocity_Data:
							{
								buffer[0] = IMUv100_Modbus.Device_Address;
								buffer[1] = Read_Input_Registers;
								buffer[2] = 6;
								buffer[3] = found->Data[0] ;
								buffer[4] = found->Data[1] ;
								buffer[5] = found->Data[2] ;
								buffer[6] = found->Data[3] ;
								buffer[7] = found->Data[4] ;
								buffer[8] = found->Data[5] ;
								Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 9);

							}
								break;

						case Angular_Velocity_Data:
							{
								buffer[0] = IMUv100_Modbus.Device_Address;
								buffer[1] = Read_Input_Registers;
								buffer[2] = 6;
								buffer[3] = found->Data[0] ;
								buffer[4] = found->Data[1] ;
								buffer[5] = found->Data[2] ;
								buffer[6] = found->Data[3] ;
								buffer[7] = found->Data[4] ;
								buffer[8] = found->Data[5] ;
								Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 9);

							}
								break;
						default:
						{

						}
							break;
					}

				}
				break;

				case Write_Single_Register:
				{
					switch (found->Register_Address)
					{
						case Reset_Device:
						{

						}

							break;

						case Start_Calibration:
						{

						}

							break;

						default:
						{

						}
							break;
					}

				}
				break;

				case Write_Multiple_Registers:
				{
					switch (found->Register_Address)
					{
						case Accelerometer_Scaling_Factor:
						{

						}

							break;

						case Gyroscope_Scaling_Factor:
						{

						}

							break;

						case Magnetometer_Scaling_Factor:
						{

						}

							break;

						default:
						{

						}
							break;
					}
				}
				break;

				default:
//					return -1;
					break;
			}
		}

//		switch (IMUv100_Modbus.Payload.Function_Code) {
//			case Read_Holding_Registers:
//			{
//				switch ((int)IMUv100_Modbus.Payload.Register_Address)
//				{
//					case (IMU_Device_Version):
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
////						buffer[0] = IMUv100_Modbus.Device_Address;
////						buffer[1] = Read_Holding_Registers;
////						buffer[2] = 1;
////						buffer[3] = (IMU_Register_Map.Firmware_Version.Data[0] & 0xFF00)>>8;
////						buffer[4] = (IMU_Register_Map.Firmware_Version.Data[0] & 0x00FF)>>0;
////						Modbus_Send_Slave_Packet(&IMUv100_Modbus, buffer, 5);
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

	}
}

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
