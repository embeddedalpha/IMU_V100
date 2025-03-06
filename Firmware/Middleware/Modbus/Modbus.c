/*
 * Modbus.c
 *
 *  Created on: Feb 28, 2025
 *      Author: kunal
 */


#include "Modbus.h"

typedef struct Modbus_Flag_Struct{

	volatile bool RX_Active_Flag;
	volatile bool RX_Complete_Flag;
}Modbus_Flag_Struct;

typedef struct Modbus_Data_Packet_Struct{
	volatile uint16_t Data_Length;
	volatile uint8_t RX_Buffer[256];
}Modbus_Data_Packet_Struct;

Modbus_Config *__modbus_usart_1_device_config;
Modbus_Config *__modbus_usart_2_device_config;
Modbus_Config *__modbus_usart_3_device_config;
Modbus_Config *__modbus_uart_4_device_config;
Modbus_Config *__modbus_uart_5_device_config;
Modbus_Config *__modbus_usart_6_device_config;

Modbus_Flag_Struct Modbus1_Flag;
Modbus_Flag_Struct Modbus2_Flag;
Modbus_Flag_Struct Modbus3_Flag;
Modbus_Flag_Struct Modbus4_Flag;
Modbus_Flag_Struct Modbus5_Flag;
Modbus_Flag_Struct Modbus6_Flag;

Modbus_Data_Packet_Struct Modbus1_Data_Packet;
Modbus_Data_Packet_Struct Modbus2_Data_Packet;
Modbus_Data_Packet_Struct Modbus3_Data_Packet;
Modbus_Data_Packet_Struct Modbus4_Data_Packet;
Modbus_Data_Packet_Struct Modbus5_Data_Packet;
Modbus_Data_Packet_Struct Modbus6_Data_Packet;


// Flags to control and monitor UART reception
volatile int modbus_txget_flag = 0; // Indicates if the reception is active
volatile int modbus_txflag = 0;     // Indicates if data reception is complete

#define RX_Buffer_Length 200 // Length of the reception buffer

// Variables to track the length of received data and the reception buffer
volatile int Modbus_RX_Length = 0;
volatile char Modbus_TRX_Buffer[RX_Buffer_Length]; // Buffer for received and transmitted data


static uint16_t CRC16 ( uint8_t *nData, uint16_t wLength)
{
static const uint16_t wCRCTable[] = {
   0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
   0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
   0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
   0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
   0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
   0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
   0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
   0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
   0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
   0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
   0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
   0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
   0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
   0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
   0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
   0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
   0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
   0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
   0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
   0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
   0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
   0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
   0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
   0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
   0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
   0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
   0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
   0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
   0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
   0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
   0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
   0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

uint8_t nTemp;
uint16_t wCRCWord = 0xFFFF;

   while (wLength--)
   {
      nTemp = *nData++ ^ wCRCWord;
      wCRCWord >>= 8;
      wCRCWord  ^= wCRCTable[nTemp];
   }
   return wCRCWord;
}

bool Modbus_Packet_Validate(Modbus_Config *device_config,Modbus_Data_Packet_Struct *Packet)
{
	if(Packet->RX_Buffer[0] == device_config->Device_Address)
	{
		uint16_t calc_crc = CRC16(Packet->RX_Buffer, Packet->Data_Length-2);

		uint16_t temp_crc = (Packet->RX_Buffer[Packet->Data_Length-1] << 8) | (Packet->RX_Buffer[Packet->Data_Length-2] << 0);

		if(calc_crc == temp_crc)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

bool Modbus_Slave_Packet_Processor(Modbus_Config *device_config,Modbus_Data_Packet_Struct *Packet)
{
	if(Packet->RX_Buffer[0] == device_config->Device_Address)
	{
		uint16_t calc_crc = CRC16(Packet->RX_Buffer, Packet->Data_Length-2);

		uint16_t temp_crc = (Packet->RX_Buffer[Packet->Data_Length-1] << 8) | (Packet->RX_Buffer[Packet->Data_Length-2] << 0);

		if(calc_crc == temp_crc)
		{
			if(device_config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Read_Coils)
			{
				if(Packet->RX_Buffer[1] == Modbus_Function_Code.Read_Coils)
				{
					// Don't know how to implement this
				}
			}
			else if(device_config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Read_Discrete_Inputs)
			{
				if(Packet->RX_Buffer[1] == Modbus_Function_Code.Read_Discrete_Inputs)
				{
					// Don't know how to implement this
				}
			}
			else if(device_config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Read_Holding_Registers)
			{
				if(Packet->RX_Buffer[1] == Modbus_Function_Code.Read_Holding_Registers)
				{
					// Don't know how to implement this
				}
			}
			else if(device_config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Read_Input_Registers)
			{
				if(Packet->RX_Buffer[1] == Modbus_Function_Code.Read_Input_Registers)
				{
					// Don't know how to implement this
				}
			}
			else if(device_config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Write_Single_Coil)
			{
				if(Packet->RX_Buffer[1] == Modbus_Function_Code.Write_Single_Coil)
				{
					// Don't know how to implement this
				}
			}
			else if(device_config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Write_Single_Register)
			{
				if(Packet->RX_Buffer[1] == Modbus_Function_Code.Write_Single_Register)
				{
					// Don't know how to implement this
				}
			}
			else if(device_config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Write_Multiple_Coils)
			{
				if(Packet->RX_Buffer[1] == Modbus_Function_Code.Write_Multiple_Coils)
				{
					// Don't know how to implement this
				}
			}
			else if(device_config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Write_Multiple_Registers)
			{
				if(Packet->RX_Buffer[1] == Modbus_Function_Code.Write_Multiple_Registers)
				{
					// Don't know how to implement this
				}
			}
			else
			{
				// Need to implement this
			}



		}
		else
		{

			return 0;
		}

	}


	return 1;
}

void MODBUS_USART1_IRQ(void)
{
	if(Modbus1_Flag.RX_Active_Flag)
	{
		USART_Clear_Status_Regs(&__modbus_usart_1_device_config->UART_Device);

		 __disable_irq(); // Disable interrupts to safely update DMA configurations

		 __modbus_usart_1_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;

		 Modbus1_Data_Packet.Data_Length = RX_Buffer_Length - __modbus_usart_1_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR;

		// Prevent buffer overflow
		if ( Modbus1_Data_Packet.Data_Length > RX_Buffer_Length)
		{
			Modbus1_Data_Packet.Data_Length = 	Modbus1_Data_Packet.Data_Length;
		}

        // Reset DMA stream for the next reception
        __modbus_usart_1_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR = RX_Buffer_Length;
        __modbus_usart_1_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR |= DMA_SxCR_EN;

        Modbus1_Flag.RX_Complete_Flag = 1; // Set the flag indicating data reception is complete

        //Process the incoming packet.

        if(__modbus_usart_1_device_config->Device_Type == Modbus_Configuration.Device_Type.Slave)
        {
        	Modbus_Slave_Packet_Processor(__modbus_usart_1_device_config, &Modbus1_Data_Packet);
        }


        __enable_irq(); // Re-enable interrupts







	}

}

void MODBUS_USART2_IRQ(void)
{
	if(Modbus2_Flag.RX_Active_Flag)
	{
		USART_Clear_Status_Regs(&__modbus_usart_2_device_config->UART_Device);

		 __disable_irq(); // Disable interrupts to safely update DMA configurations

		 __modbus_usart_2_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;

		 Modbus2_Data_Packet.Data_Length = RX_Buffer_Length - __modbus_usart_2_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR;

		// Prevent buffer overflow
		if ( Modbus2_Data_Packet.Data_Length > RX_Buffer_Length)
		{
			Modbus2_Data_Packet.Data_Length = 	Modbus2_Data_Packet.Data_Length;
		}

        // Reset DMA stream for the next reception
        __modbus_usart_2_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR = RX_Buffer_Length;
        __modbus_usart_2_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR |= DMA_SxCR_EN;


        Modbus2_Flag.RX_Complete_Flag = 1; // Set the flag indicating data reception is complete

        if(__modbus_usart_2_device_config->Device_Type == Modbus_Configuration.Device_Type.Slave)
        {
        	Modbus_Slave_Packet_Processor(__modbus_usart_2_device_config, &Modbus2_Data_Packet);
        }

        __enable_irq(); // Re-enable interrupts

	}
}

void MODBUS_USART3_IRQ(void)
{
	if(Modbus3_Flag.RX_Active_Flag)
	{
		USART_Clear_Status_Regs(&__modbus_usart_3_device_config->UART_Device);

		 __disable_irq(); // Disable interrupts to safely update DMA configurations

		 __modbus_usart_3_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;

		 Modbus3_Data_Packet.Data_Length = RX_Buffer_Length - __modbus_usart_3_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR;

		// Prevent buffer overflow
		if ( Modbus3_Data_Packet.Data_Length > RX_Buffer_Length)
		{
			Modbus3_Data_Packet.Data_Length = 	Modbus3_Data_Packet.Data_Length;
		}

        // Reset DMA stream for the next reception
        __modbus_usart_3_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR = RX_Buffer_Length;
        __modbus_usart_3_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR |= DMA_SxCR_EN;

        Modbus3_Flag.RX_Complete_Flag = 1; // Set the flag indicating data reception is complete


        if(__modbus_usart_3_device_config->Device_Type == Modbus_Configuration.Device_Type.Slave)
        {
        	Modbus_Slave_Packet_Processor(__modbus_usart_3_device_config, &Modbus3_Data_Packet);
        }

        __enable_irq(); // Re-enable interrupts



	}

}

void MODBUS_UART4_IRQ(void)
{
	if(Modbus4_Flag.RX_Active_Flag)
	{
		USART_Clear_Status_Regs(&__modbus_uart_4_device_config->UART_Device);

		 __disable_irq(); // Disable interrupts to safely update DMA configurations

		 __modbus_uart_4_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;

		 Modbus4_Data_Packet.Data_Length = RX_Buffer_Length - __modbus_uart_4_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR;

		// Prevent buffer overflow
		if ( Modbus4_Data_Packet.Data_Length > RX_Buffer_Length)
		{
			Modbus4_Data_Packet.Data_Length = 	Modbus4_Data_Packet.Data_Length;
		}

        // Reset DMA stream for the next reception
        __modbus_uart_4_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR = RX_Buffer_Length;
        __modbus_uart_4_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR |= DMA_SxCR_EN;

        __enable_irq(); // Re-enable interrupts

        Modbus4_Flag.RX_Complete_Flag = 1; // Set the flag indicating data reception is complete

	}

}

void MODBUS_UART5_IRQ(void)
{
	if(Modbus5_Flag.RX_Active_Flag)
	{
		USART_Clear_Status_Regs(&__modbus_uart_5_device_config->UART_Device);

		 __disable_irq(); // Disable interrupts to safely update DMA configurations

		 __modbus_uart_5_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;

		 Modbus5_Data_Packet.Data_Length = RX_Buffer_Length - __modbus_uart_5_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR;

		// Prevent buffer overflow
		if ( Modbus5_Data_Packet.Data_Length > RX_Buffer_Length)
		{
			Modbus5_Data_Packet.Data_Length = 	Modbus5_Data_Packet.Data_Length;
		}

        // Reset DMA stream for the next reception
        __modbus_uart_5_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR = RX_Buffer_Length;
        __modbus_uart_5_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR |= DMA_SxCR_EN;

        __enable_irq(); // Re-enable interrupts

        Modbus5_Flag.RX_Complete_Flag = 1; // Set the flag indicating data reception is complete

	}

}

void MODBUS_USART6_IRQ(void)
{
	if(Modbus6_Flag.RX_Active_Flag)
	{
		USART_Clear_Status_Regs(&__modbus_usart_6_device_config->UART_Device);

		 __disable_irq(); // Disable interrupts to safely update DMA configurations

		 __modbus_usart_6_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;

		 Modbus6_Data_Packet.Data_Length = RX_Buffer_Length - __modbus_usart_6_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR;

		// Prevent buffer overflow
		if ( Modbus6_Data_Packet.Data_Length > RX_Buffer_Length)
		{
			Modbus6_Data_Packet.Data_Length = 	Modbus6_Data_Packet.Data_Length;
		}

        // Reset DMA stream for the next reception
        __modbus_usart_6_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR = RX_Buffer_Length;
        __modbus_usart_6_device_config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR |= DMA_SxCR_EN;

        __enable_irq(); // Re-enable interrupts

        Modbus6_Flag.RX_Complete_Flag = 1; // Set the flag indicating data reception is complete

	}

}





Modbus_Flag Modbus_Init(Modbus_Config *device_config)
{
	if(device_config->UART_Device.Port == USART1)
	{
		__modbus_usart_1_device_config = device_config;
		device_config->UART_Device.ISR_Routines.Idle_Line_ISR = MODBUS_USART1_IRQ;

	}
	if(device_config->UART_Device.Port == USART2)
	{
		__modbus_usart_2_device_config = device_config;
		device_config->UART_Device.ISR_Routines.Idle_Line_ISR = MODBUS_USART2_IRQ;
	}
	if(device_config->UART_Device.Port == USART3)
	{
		__modbus_usart_3_device_config = device_config;
		device_config->UART_Device.ISR_Routines.Idle_Line_ISR = MODBUS_USART3_IRQ;
	}
	if(device_config->UART_Device.Port == UART4)
	{
		__modbus_uart_4_device_config = device_config;
		device_config->UART_Device.ISR_Routines.Idle_Line_ISR = MODBUS_UART4_IRQ;
	}
	if(device_config->UART_Device.Port == UART5)
	{
		__modbus_uart_5_device_config = device_config;
		device_config->UART_Device.ISR_Routines.Idle_Line_ISR = MODBUS_UART5_IRQ;
	}
	if(device_config->UART_Device.Port == USART6)
	{
		__modbus_usart_6_device_config = device_config;
		device_config->UART_Device.ISR_Routines.Idle_Line_ISR = MODBUS_USART6_IRQ;
	}


    if (USART_Init(&device_config->UART_Device) != true) {
        return Init_Fail;
    }


	if(device_config->Device_Type == Modbus_Configuration.Device_Type.Slave)
	{

		if(device_config->UART_Device.Port == USART1)
		{
			Modbus1_Flag.RX_Active_Flag = 1;
			USART_RX_Buffer(&__modbus_usart_1_device_config->UART_Device, (uint8_t *)Modbus1_Data_Packet.RX_Buffer, RX_Buffer_Length, 0);
		}
		else if(device_config->UART_Device.Port == USART2)
		{
			Modbus2_Flag.RX_Active_Flag = 1;
			USART_RX_Buffer(&__modbus_usart_2_device_config->UART_Device, (uint8_t *)Modbus2_Data_Packet.RX_Buffer, RX_Buffer_Length, 0);
		}
		else if(device_config->UART_Device.Port == USART3)
		{
			Modbus3_Flag.RX_Active_Flag = 1;
			USART_RX_Buffer(&__modbus_usart_2_device_config->UART_Device, (uint8_t *)Modbus3_Data_Packet.RX_Buffer, RX_Buffer_Length, 0);
		}
		else if(device_config->UART_Device.Port == UART4)
		{
			Modbus4_Flag.RX_Active_Flag = 1;
			USART_RX_Buffer(&__modbus_uart_4_device_config->UART_Device, (uint8_t *)Modbus4_Data_Packet.RX_Buffer, RX_Buffer_Length, 0);
		}
		else if(device_config->UART_Device.Port == UART5)
		{
			Modbus5_Flag.RX_Active_Flag = 1;
			USART_RX_Buffer(&__modbus_uart_5_device_config->UART_Device, (uint8_t *)Modbus5_Data_Packet.RX_Buffer, RX_Buffer_Length, 0);
		}
		else if(device_config->UART_Device.Port == USART6)
		{
			Modbus6_Flag.RX_Active_Flag = 1;
			USART_RX_Buffer(&__modbus_usart_6_device_config->UART_Device, (uint8_t *)Modbus6_Data_Packet.RX_Buffer, RX_Buffer_Length, 0);
		}


	}


	return Init_Success;
}


Modbus_Flag Modbus_Read_Coil(Modbus_Config *device_config, Modbus_Read_Coils_Request *Request,Modbus_Read_Coils_Response *Response)
{

	uint16_t crc;
	uint8_t buffer[8];

	buffer[0] = Request->Slave_Address;
	buffer[1]  = Modbus_Function_Code.Read_Coils;
	buffer[2] = (Request->Starting_Address & 0xFF00) >> 8;
	buffer[3] = (Request->Starting_Address & 0x00FF) >> 0;
	buffer[4] = (Request->Quantity_Of_Inputs & 0xFF00) >> 8;
	buffer[5] = (Request->Quantity_Of_Inputs & 0x00FF) >> 0;

	crc = CRC16(buffer, 6);

	buffer[6] = (crc & 0x00FF) >> 0;
	buffer[7] = (crc & 0xFF00) >> 8;

	for(int i =0 ; i < 8; i++)
	{
		USART_TX_Byte(&device_config->UART_Device, buffer[i]);
	}

	if(device_config->UART_Device.Port == USART1)
	{
		Modbus1_Flag.RX_Active_Flag = 1;
		USART_RX_Buffer(&__modbus_usart_1_device_config->UART_Device, (uint8_t *)Modbus1_Data_Packet.RX_Buffer, RX_Buffer_Length, 0);

	    while (Modbus1_Flag.RX_Complete_Flag == 0) {
	        // Wait loop
	    }

	    // Check for valid input length
	    if (Modbus1_Data_Packet.Data_Length < 2) {
	        // Reset flags and return error
	    	Modbus1_Flag.RX_Active_Flag = 0;
	    	Modbus1_Flag.RX_Complete_Flag = 0;
	        return -1;
	    }




	    if(Modbus_Packet_Validate(device_config, Modbus1_Data_Packet) == 1)
	    {
	    	if(Modbus1_Data_Packet.RX_Buffer[1] == Modbus_Function_Code.Read_Coils)
	    	{
	    		Response->Byte_Count = Modbus1_Data_Packet.RX_Buffer[3];


	    	}

	    }





		Modbus1_Flag.RX_Active_Flag = 0;
		Modbus1_Flag.RX_Complete_Flag = 0;
	}



	return Command_Transfer_Successful;
}

Modbus_Flag Modbus_Read_Discrete_Inputs(Modbus_Config *device_config, Modbus_Read_Discrete_Inputs_Request *Request,Modbus_Read_Discrete_Inputs_Response *Response)
{
	uint16_t crc;
	uint8_t buffer[8];

	buffer[0] = Request->Slave_Address;
	buffer[1]  = Modbus_Function_Code.Read_Discrete_Inputs;
	buffer[2] = (Request->Starting_Address & 0xFF00) >> 8;
	buffer[3] = (Request->Starting_Address & 0x00FF) >> 0;
	buffer[4] = (Request->Quantity_Of_Inputs & 0xFF00) >> 8;
	buffer[5] = (Request->Quantity_Of_Inputs & 0x00FF) >> 0;

	crc = CRC16(buffer, 6);

	buffer[6] = (crc & 0x00FF) >> 0;
	buffer[7] = (crc & 0xFF00) >> 8;

	for(int i =0 ; i < 8; i++)
	{
		USART_TX_Byte(&device_config->UART_Device, buffer[i]);
	}


	return Command_Transfer_Successful;
}

Modbus_Flag Modbus_Read_Holding_Registers(Modbus_Config *device_config,Modbus_Read_Holding_Registers_Request *Request ,Modbus_Read_Holding_Registers_Response *Response)
{
	uint16_t crc;
	uint8_t buffer[8];

	buffer[0] = Request->Slave_Address;
	buffer[1]  = Modbus_Function_Code.Read_Holding_Registers;
	buffer[2] = (Request->Starting_Address & 0xFF00) >> 8;
	buffer[3] = (Request->Starting_Address & 0x00FF) >> 0;
	buffer[4] = (Request->Quantity_Of_Inputs & 0xFF00) >> 8;
	buffer[5] = (Request->Quantity_Of_Inputs & 0x00FF) >> 0;

	crc = CRC16(buffer, 6);

	buffer[6] = (crc & 0x00FF) >> 0;
	buffer[7] = (crc & 0xFF00) >> 8;

	for(int i =0 ; i < 8; i++)
	{
		USART_TX_Byte(&device_config->UART_Device, buffer[i]);
	}




	return Command_Transfer_Successful;
}

Modbus_Flag Modbus_Read_Input_Registers(Modbus_Config *device_config,Modbus_Read_Input_Registers_Request *Request ,Modbus_Read_Input_Registers_Response *Response)
{
	uint16_t crc;
	uint8_t buffer[8];

	buffer[0] = Request->Slave_Address;
	buffer[1]  = Modbus_Function_Code.Read_Input_Registers;
	buffer[2] = (Request->Starting_Address & 0xFF00) >> 8;
	buffer[3] = (Request->Starting_Address & 0x00FF) >> 0;
	buffer[4] = (Request->Quantity_Of_Inputs & 0xFF00) >> 8;
	buffer[5] = (Request->Quantity_Of_Inputs & 0x00FF) >> 0;

	crc = CRC16(buffer, 6);

	buffer[6] = (crc & 0x00FF) >> 0;
	buffer[7] = (crc & 0xFF00) >> 8;

	for(int i =0 ; i < 8; i++)
	{
		USART_TX_Byte(&device_config->UART_Device, buffer[i]);
	}


	return Command_Transfer_Successful;
}



