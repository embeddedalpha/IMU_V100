/*
 * Modbus.c
 *
 *  Created on: Feb 28, 2025
 *      Author: kunal
 */


#include "Modbus.h"

#define Modbus_RX_Buffer_Length 256 // Length of the reception buffer

typedef struct {

	volatile bool RX_Active_Flag;
	volatile bool RX_Complete_Flag;
}Modbus_Flag_Struct;

typedef struct {
	volatile uint16_t Data_Length;
	volatile uint8_t RX_Buffer[Modbus_RX_Buffer_Length];
}Modbus_Data_Packet_Struct;


typedef struct {
    Modbus_Config *config;
    Modbus_Flag_Struct flag;
    Modbus_Data_Packet_Struct data_packet;
} Modbus_Instance;


volatile Modbus_Instance modbus_Instance[6];

static uint16_t CRC16 (volatile uint8_t *nData, volatile uint16_t wLength)
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

bool Modbus_Slave_Packet_Processor(volatile Modbus_Instance *instance)
{
	if(instance->data_packet.RX_Buffer[0] == instance->config->Device_Address)
	{
		uint16_t received_crc = instance->data_packet.RX_Buffer[instance->data_packet.Data_Length - 2] |
		                        (instance->data_packet.RX_Buffer[instance->data_packet.Data_Length - 1] << 8);

		uint16_t calculated_crc = CRC16(instance->data_packet.RX_Buffer, instance->data_packet.Data_Length - 2);

		if(received_crc == calculated_crc)
		{
			if(instance->config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Read_Coils)
			{
				if(instance->data_packet.RX_Buffer[1] == Read_Coil_Registers)
				{
					// Don't know how to implement this
				}
			}
			else if(instance->config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Read_Discrete_Inputs)
			{
				if(instance->data_packet.RX_Buffer[1] == Read_Discrete_Inputs)
				{
					// Don't know how to implement this
				}
			}
			else if(instance->config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Read_Holding_Registers)
			{
				if(instance->data_packet.RX_Buffer[1] == Read_Holding_Registers)
				{
					// Don't know how to implement this
				}
			}
			else if(instance->config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Read_Input_Registers)
			{
				if(instance->data_packet.RX_Buffer[1] == Read_Input_Registers)
				{
					// Don't know how to implement this
				}
			}
			else if(instance->config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Write_Single_Coil)
			{
				if(instance->data_packet.RX_Buffer[1] == Write_Single_Coil)
				{
					// Don't know how to implement this
				}
			}
			else if(instance->config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Write_Single_Register)
			{
				if(instance->data_packet.RX_Buffer[1] == Write_Single_Register)
				{
					// Don't know how to implement this
				}
			}
			else if(instance->config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Write_Multiple_Coils)
			{
				if(instance->data_packet.RX_Buffer[1] == Write_Multiple_Coils)
				{
					// Don't know how to implement this
				}
			}
			else if(instance->config->Acceptable_Functions == Modbus_Configuration.Acceptable_Function_Codes.Write_Multiple_Registers)
			{
				if(instance->data_packet.RX_Buffer[1] == Write_Multiple_Registers)
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

void Modbus_USART_IRQ_Handler(volatile Modbus_Instance *instance)
{
	if(instance->flag.RX_Active_Flag)
	{
		USART_Clear_Status_Regs(&instance->config->UART_Device);

		 __disable_irq(); // Disable interrupts to safely update DMA configurations

		 instance->config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;

		 instance->data_packet.Data_Length = Modbus_RX_Buffer_Length - instance->config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR;

		// Prevent buffer overflow
		if ( instance->data_packet.Data_Length > Modbus_RX_Buffer_Length)
		{
			instance->data_packet.Data_Length = 	Modbus_RX_Buffer_Length;
		}

        // Reset DMA stream for the next reception
		instance->config->UART_Device.USART_DMA_Instance_RX.Request.Stream->NDTR = Modbus_RX_Buffer_Length;
		instance->config->UART_Device.USART_DMA_Instance_RX.Request.Stream->CR |= DMA_SxCR_EN;

		instance->flag.RX_Complete_Flag = 1; // Set the flag indicating data reception is complete

        //Process the incoming packet.

        if(instance->config->Device_Type == Modbus_Configuration.Device_Type.Slave)
        {
        	instance->config->Modbus_Slave_Processor_Flag = true;
        	Modbus_Slave_Packet_Processor(instance);
        }


        __enable_irq(); // Re-enable interrupts

	}
}



bool Modbus_Packet_Validate(volatile Modbus_Instance *instance)
{
	if(instance->data_packet.RX_Buffer[0] == instance->config->Device_Address)
	{
		uint16_t received_crc = instance->data_packet.RX_Buffer[instance->data_packet.Data_Length - 2] |
		                        (instance->data_packet.RX_Buffer[instance->data_packet.Data_Length - 1] << 8);

		uint16_t calculated_crc = CRC16(instance->data_packet.RX_Buffer, instance->data_packet.Data_Length - 2);

		if (calculated_crc != received_crc) {
		    return false;  // Invalid CRC
		}

		return true;
	}

	return 0;
}



void MODBUS_USART1_IRQ(void){ Modbus_USART_IRQ_Handler(&modbus_Instance[0]); }
void MODBUS_USART2_IRQ(void){ Modbus_USART_IRQ_Handler(&modbus_Instance[1]); }
void MODBUS_USART3_IRQ(void){ Modbus_USART_IRQ_Handler(&modbus_Instance[2]); }
void MODBUS_UART4_IRQ(void) { Modbus_USART_IRQ_Handler(&modbus_Instance[3]); }
void MODBUS_UART5_IRQ(void) { Modbus_USART_IRQ_Handler(&modbus_Instance[4]); }
void MODBUS_USART6_IRQ(void){ Modbus_USART_IRQ_Handler(&modbus_Instance[5]); }





Modbus_Flag Modbus_Init(Modbus_Config *device_config)
{

	int usart_index = USART_Get_Instance_Number(&device_config->UART_Device);
	if (usart_index < 0 || usart_index > 5) return Init_Fail;  // Invalid USART instance

	modbus_Instance[usart_index].config = device_config;

    switch (usart_index)
    {
        case 0: device_config->UART_Device.ISR_Routines.Idle_Line_ISR = MODBUS_USART1_IRQ; break;
        case 1: device_config->UART_Device.ISR_Routines.Idle_Line_ISR = MODBUS_USART2_IRQ; break;
        case 2: device_config->UART_Device.ISR_Routines.Idle_Line_ISR = MODBUS_USART3_IRQ; break;
        case 3:  device_config->UART_Device.ISR_Routines.Idle_Line_ISR = MODBUS_UART4_IRQ; break;
        case 4:  device_config->UART_Device.ISR_Routines.Idle_Line_ISR = MODBUS_UART5_IRQ; break;
        case 5: device_config->UART_Device.ISR_Routines.Idle_Line_ISR = MODBUS_USART6_IRQ; break;
    }


    if (USART_Init(&device_config->UART_Device) != true) {
        return Init_Fail;
    }


	if(device_config->Device_Type == Modbus_Configuration.Device_Type.Slave)
	{
		modbus_Instance[usart_index].flag.RX_Active_Flag = 1;
		USART_RX_Buffer(&modbus_Instance[usart_index].config->UART_Device, (uint8_t *)modbus_Instance[usart_index].data_packet.RX_Buffer, Modbus_RX_Buffer_Length, 0);
	}

	return Init_Success;
}

void Modbus_Slave_Command_Processor(Modbus_Config *device_config)
{
	device_config->Modbus_Slave_Processor();
}

Modbus_Flag Modbus_Send_Slave_Packet(Modbus_Config *device_config, uint8_t *buffer, int length)
{
    uint16_t crc;

    int usart_index = USART_Get_Instance_Number(&device_config->UART_Device);
    if (usart_index < 0 || usart_index > 5) return Init_Fail;  // Invalid USART instance

    // Correct CRC Byte Order
    crc = CRC16(buffer, length);

    // Transmit Modbus Request
    for(int i = 0; i < length; i++)
    {
    	USART_TX_Single_Byte(&device_config->UART_Device, buffer[i]);
    }
    USART_TX_Single_Byte(&device_config->UART_Device, crc & 0xFF);
    USART_TX_Single_Byte(&device_config->UART_Device, (crc >> 8) & 0xFF);

    return Command_Transfer_Successful;
}

Modbus_Flag Modbus_Read_Coil(Modbus_Config *device_config, Modbus_Read_Coils_Request *Request, Modbus_Read_Coils_Response *Response)
{
    uint16_t crc;
    uint8_t buffer[8];

    int usart_index = USART_Get_Instance_Number(&device_config->UART_Device);
    if (usart_index < 0 || usart_index > 5) return Init_Fail;  // Invalid USART instance

    // Build Modbus Request Packet
    buffer[0] = Request->Slave_Address;
    buffer[1] = Read_Coil_Registers;
    buffer[2] = (Request->Starting_Address >> 8) & 0xFF;
    buffer[3] = Request->Starting_Address & 0xFF;
    buffer[4] = (Request->Quantity_Of_Inputs >> 8) & 0xFF;
    buffer[5] = Request->Quantity_Of_Inputs & 0xFF;

    // Correct CRC Byte Order
    crc = CRC16(buffer, 6);
    buffer[6] = crc & 0xFF;  // LSB First
    buffer[7] = (crc >> 8) & 0xFF;  // MSB Second

    // Transmit Modbus Request
    for(int i = 0; i < 8; i++)
    {
        USART_TX_Single_Byte(&device_config->UART_Device, buffer[i]);
    }

    // Start RX Process
    modbus_Instance[usart_index].flag.RX_Active_Flag = 1;
    USART_RX_Buffer(&modbus_Instance[usart_index].config->UART_Device,
                    (uint8_t *)modbus_Instance[usart_index].data_packet.RX_Buffer,
                    Modbus_RX_Buffer_Length, 0);

    uint32_t timeout = 5000;  // 5ms timeout
    while (modbus_Instance[usart_index].flag.RX_Complete_Flag == 0 && timeout > 0) {
        timeout--;
        Delay_us(1);  // Wait 1 microsecond
    }
    if (timeout == 0) return Command_Transfer_Unsuccessful;

    // Validate Response Length
    uint16_t expected_length = 5 + (Request->Quantity_Of_Inputs / 8) + ((Request->Quantity_Of_Inputs % 8) ? 1 : 0);
    if (modbus_Instance[usart_index].data_packet.Data_Length < expected_length) {
        modbus_Instance[usart_index].flag.RX_Active_Flag = 0;
        modbus_Instance[usart_index].flag.RX_Complete_Flag = 0;
        return Command_Transfer_Unsuccessful;
    }

    // Validate CRC
    if (!Modbus_Packet_Validate(&modbus_Instance[usart_index])) return Command_Transfer_Unsuccessful;

    // Parse Response
    if (modbus_Instance[usart_index].data_packet.RX_Buffer[1] == Read_Coil_Registers)
    {
        Response->Byte_Count = modbus_Instance[usart_index].data_packet.RX_Buffer[2];

        int total_coils = Request->Quantity_Of_Inputs;
        for (int i = 0; i < total_coils; i++)
        {
            int byte_index = i / 8;
            int bit_index = i % 8;
            Response->Data[i] = (modbus_Instance[usart_index].data_packet.RX_Buffer[3 + byte_index] >> bit_index) & 0x01;
        }
    }

    modbus_Instance[usart_index].flag.RX_Active_Flag = 0;
    modbus_Instance[usart_index].flag.RX_Complete_Flag = 0;

    return Command_Transfer_Successful;
}


Modbus_Flag Modbus_Read_Discrete_Inputs(Modbus_Config *device_config, Modbus_Read_Discrete_Inputs_Request *Request,Modbus_Read_Discrete_Inputs_Response *Response)
{
    uint16_t crc;
    uint8_t buffer[8];

    int usart_index = USART_Get_Instance_Number(&device_config->UART_Device);
    if (usart_index < 0 || usart_index > 5) return Init_Fail;  // Invalid USART instance

    buffer[0] = Request->Slave_Address;
    buffer[1] = Read_Discrete_Inputs;
    buffer[2] = (Request->Starting_Address >> 8) & 0xFF;
    buffer[3] = Request->Starting_Address & 0xFF;
    buffer[4] = (Request->Quantity_Of_Inputs >> 8) & 0xFF;
    buffer[5] = Request->Quantity_Of_Inputs & 0xFF;

    crc = CRC16(buffer, 6);
    buffer[6] = crc & 0xFF;  // LSB First
    buffer[7] = (crc >> 8) & 0xFF;  // MSB Second

    // Transmit Modbus Request
    for(int i = 0; i < 8; i++)
    {
        USART_TX_Single_Byte(&device_config->UART_Device, buffer[i]);
    }

    // Start RX Process
    modbus_Instance[usart_index].flag.RX_Active_Flag = 1;
    USART_RX_Buffer(&modbus_Instance[usart_index].config->UART_Device,
                    (uint8_t *)modbus_Instance[usart_index].data_packet.RX_Buffer,
                    Modbus_RX_Buffer_Length, 0);

    uint32_t timeout = 5000;  // 5ms timeout
    while (modbus_Instance[usart_index].flag.RX_Complete_Flag == 0 && timeout > 0) {
        timeout--;
        Delay_us(1);  // Wait 1 microsecond
    }
    if (timeout == 0) return Command_Transfer_Unsuccessful;

    // Validate CRC
    if (!Modbus_Packet_Validate(&modbus_Instance[usart_index])) return Command_Transfer_Unsuccessful;

    // Parse Response
    if (modbus_Instance[usart_index].data_packet.RX_Buffer[1] == Read_Coil_Registers)
    {
        Response->Byte_Count = modbus_Instance[usart_index].data_packet.RX_Buffer[2];

        int total_coils = Request->Quantity_Of_Inputs;
        for (int i = 0; i < total_coils; i++)
        {
            int byte_index = i / 8;
            int bit_index = i % 8;
            Response->Data[i] = (modbus_Instance[usart_index].data_packet.RX_Buffer[3 + byte_index] >> bit_index) & 0x01;
        }
    }

    modbus_Instance[usart_index].flag.RX_Active_Flag = 0;
    modbus_Instance[usart_index].flag.RX_Complete_Flag = 0;

    return Command_Transfer_Successful;
}

Modbus_Flag Modbus_Read_Holding_Registers(Modbus_Config *device_config,Modbus_Read_Holding_Registers_Request *Request ,Modbus_Read_Holding_Registers_Response *Response)
{
    uint16_t crc;
    uint8_t buffer[8];

    int usart_index = USART_Get_Instance_Number(&device_config->UART_Device);
    if (usart_index < 0 || usart_index > 5) return Init_Fail;  // Invalid USART instance

    buffer[0] = Request->Slave_Address;
    buffer[1] = Read_Holding_Registers;
    buffer[2] = (Request->Starting_Address >> 8) & 0xFF;
    buffer[3] = Request->Starting_Address & 0xFF;
    buffer[4] = (Request->Quantity_Of_Inputs >> 8) & 0xFF;
    buffer[5] = Request->Quantity_Of_Inputs & 0xFF;

    crc = CRC16(buffer, 6);
    buffer[6] = crc & 0xFF;  // LSB First
    buffer[7] = (crc >> 8) & 0xFF;  // MSB Second

    // Transmit Modbus Request
    for(int i = 0; i < 8; i++)
    {
        USART_TX_Single_Byte(&device_config->UART_Device, buffer[i]);
    }

    // Start RX Process
    modbus_Instance[usart_index].flag.RX_Active_Flag = 1;
    USART_RX_Buffer(&modbus_Instance[usart_index].config->UART_Device,
                    (uint8_t *)modbus_Instance[usart_index].data_packet.RX_Buffer,
                    Modbus_RX_Buffer_Length, 0);

    uint32_t timeout = 5000;  // 5ms timeout
    while (modbus_Instance[usart_index].flag.RX_Complete_Flag == 0 && timeout > 0) {
        timeout--;
        Delay_us(1);  // Wait 1 microsecond
    }
    if (timeout == 0) return Command_Transfer_Unsuccessful;

    // Validate CRC
    if (!Modbus_Packet_Validate(&modbus_Instance[usart_index])) return Command_Transfer_Unsuccessful;

    // Parse Response
    if (modbus_Instance[usart_index].data_packet.RX_Buffer[1] == Read_Coil_Registers)
    {
        Response->Byte_Count = modbus_Instance[usart_index].data_packet.RX_Buffer[2];

        for (int i = 0; i < Response->Byte_Count; i++)
        {
            Response->Data[i] = (modbus_Instance[usart_index].data_packet.RX_Buffer[3 + i]);
        }

    }



    return Command_Transfer_Successful;
}


//
//Modbus_Flag Modbus_Read_Discrete_Inputs(Modbus_Config *device_config, Modbus_Read_Discrete_Inputs_Request *Request,Modbus_Read_Discrete_Inputs_Response *Response)
//{
//	uint16_t crc;
//	uint8_t buffer[8];
//
//	buffer[0] = Request->Slave_Address;
//	buffer[1]  = Read_Discrete_Inputs;
//	buffer[2] = (Request->Starting_Address & 0xFF00) >> 8;
//	buffer[3] = (Request->Starting_Address & 0x00FF) >> 0;
//	buffer[4] = (Request->Quantity_Of_Inputs & 0xFF00) >> 8;
//	buffer[5] = (Request->Quantity_Of_Inputs & 0x00FF) >> 0;
//
//	crc = CRC16(buffer, 6);
//
//	buffer[6] = (crc & 0x00FF) >> 0;
//	buffer[7] = (crc & 0xFF00) >> 8;
//
//	for(int i =0 ; i < 8; i++)
//	{
//		USART_TX_Single_Byte(&device_config->UART_Device, buffer[i]);
//	}
//
//
//	return Command_Transfer_Successful;
//}
//
//Modbus_Flag Modbus_Read_Holding_Registers(Modbus_Config *device_config,Modbus_Read_Holding_Registers_Request *Request ,Modbus_Read_Holding_Registers_Response *Response)
//{
//	uint16_t crc;
//	uint8_t buffer[8];
//
//	buffer[0] = Request->Slave_Address;
//	buffer[1]  = Read_Holding_Registers;
//	buffer[2] = (Request->Starting_Address & 0xFF00) >> 8;
//	buffer[3] = (Request->Starting_Address & 0x00FF) >> 0;
//	buffer[4] = (Request->Quantity_Of_Inputs & 0xFF00) >> 8;
//	buffer[5] = (Request->Quantity_Of_Inputs & 0x00FF) >> 0;
//
//	crc = CRC16(buffer, 6);
//
//	buffer[6] = (crc & 0x00FF) >> 0;
//	buffer[7] = (crc & 0xFF00) >> 8;
//
//	for(int i =0 ; i < 8; i++)
//	{
//		USART_TX_Single_Byte(&device_config->UART_Device, buffer[i]);
//	}
//
//
//
//
//	return Command_Transfer_Successful;
//}
//
//Modbus_Flag Modbus_Read_Input_Registers(Modbus_Config *device_config,Modbus_Read_Input_Registers_Request *Request ,Modbus_Read_Input_Registers_Response *Response)
//{
//	uint16_t crc;
//	uint8_t buffer[8];
//
//	buffer[0] = Request->Slave_Address;
//	buffer[1]  = Read_Input_Registers;
//	buffer[2] = (Request->Starting_Address & 0xFF00) >> 8;
//	buffer[3] = (Request->Starting_Address & 0x00FF) >> 0;
//	buffer[4] = (Request->Quantity_Of_Inputs & 0xFF00) >> 8;
//	buffer[5] = (Request->Quantity_Of_Inputs & 0x00FF) >> 0;
//
//	crc = CRC16(buffer, 6);
//
//	buffer[6] = (crc & 0x00FF) >> 0;
//	buffer[7] = (crc & 0xFF00) >> 8;
//
//	for(int i =0 ; i < 8; i++)
//	{
//		USART_TX_Single_Byte(&device_config->UART_Device, buffer[i]);
//	}
//
//
//	return Command_Transfer_Successful;
//}
//
//
//


int Compare_Commands(Modbus_Config *config, const void* a, const void* b)
{
	Modbus_Register_Map_Instance* recA = (Modbus_Register_Map_Instance*)a;
	Modbus_Register_Map_Instance* recB  = (Modbus_Register_Map_Instance*)b;

    if (recA->Function_Code != recB->Function_Code)
        return recA->Function_Code - recB->Function_Code;
    return recA->Register_Address - recB->Register_Address;
}

Modbus_Register_Map_Instance* Search_Commands(Modbus_Config *config,int Function_Code, int Register_Address, Modbus_Register_Map_Instance *table) {
	Modbus_Register_Map_Instance key = {Function_Code, Register_Address, {0}};  // Search key
    return (Modbus_Register_Map_Instance*)bsearch(&key, table, config->readCount, sizeof(Modbus_Register_Map_Instance), Compare_Commands);
}

int Add_Command(Modbus_Config *config,Modbus_Register_Map_Instance* table,  Modbus_Function_Codes functionCode, int registerAddress, int *data, int length)
{
    if (config->readCount >= MAX_RECORDS)
    {
        return -1;
    }

    table[config->readCount].Function_Code = functionCode;
    table[config->readCount].Register_Address = registerAddress;

    for (int i = 0; i < length; i++)
        table[config->readCount].Data[i] = data[i];  // Default all to NA


    return  config->readCount++;


}

Modbus_Register_Map_Instance* searchRecord(Modbus_Config *config, Modbus_Register_Map_Instance *table,int commandType, int registerAddress) {
	Modbus_Register_Map_Instance key = {commandType, registerAddress, {0}};  // Search key
    return (Modbus_Register_Map_Instance*)bsearch(&key, table, config->readCount, sizeof(Modbus_Register_Map_Instance), Compare_Commands);
}


//void sortTable() {
//    qsort(table, recordCount, sizeof(Modbus_Register_Map_Instance), compareRecords);
//}
