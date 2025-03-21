/*
 * Modbus.h
 *
 *  Created on: Feb 28, 2025
 *      Author: kunal
 */

#ifndef MODBUS_MODBUS_H_
#define MODBUS_MODBUS_H_

#include "main.h"
#include "USART/USART.h"
#include "DMA/DMA.h"
#include "GPIO/GPIO.h"
#include "Modbus_Defs.h"


#define MAX_RECORDS 50

typedef enum {
	Read_Coil_Registers = 0x01,
	Read_Discrete_Inputs = 0x02,
    Read_Holding_Registers = 0x03,
    Read_Input_Registers = 0x04,
	Write_Single_Coil = 0x05,
    Write_Single_Register = 0x06,
	Write_Multiple_Coils = 0x0F,
    Write_Multiple_Registers = 0x10
} Modbus_Function_Codes;

typedef enum {

	Illegal_Function = 0x01,
	Illegal_Address = 0x02,
	Illegal_Data_Value = 0x03,
	Slave_Device_Failure = 0x04,
	Accepted_but_Delayed_Processing = 0x05,
	Slave_Device_Busy = 0x06,
	NAK = 0x07,
	Memory_Parity_Error = 0x08,

}Modbus_Error_Codes;

typedef struct Modbus_Payload_Template
{
	Modbus_Function_Codes Function_Code;
	uint16_t Register_Address;
	uint8_t Payload_Length;
	uint16_t Data[250];

}Modbus_Payload_Template;


typedef struct Modbus_Register_Map_Instance
{
	Modbus_Function_Codes Function_Code;
	uint16_t Register_Address;
	uint8_t Data[10];

}Modbus_Register_Map_Instance;





typedef enum Modbus_Flag_Typedef
{
	Init_Success = 1,
	Init_Fail = -1,
	Command_Transfer_Successful = 2,
	Command_Transfer_Unsuccessful = -2,
}Modbus_Flag;


typedef struct Modbus_Config
{
	uint8_t Device_Address;
	USART_Config UART_Device;
	uint8_t Device_Type;
	uint8_t Acceptable_Functions;
	void (*Modbus_Slave_Processor)(void);
	bool Modbus_Slave_Processor_Flag;
	Modbus_Payload_Template Payload;
	uint16_t readCount;

}Modbus_Config;

Modbus_Flag Modbus_Init(Modbus_Config *device_config);



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct Modbus_Read_Coils_Request{

	uint8_t Slave_Address;
	uint16_t Starting_Address;
	uint16_t Quantity_Of_Inputs;

}Modbus_Read_Coils_Request;

typedef struct Modbus_Read_Coils_Response{

	uint8_t Byte_Count;
	uint8_t Data[250];

}Modbus_Read_Coils_Response;

Modbus_Flag Modbus_Read_Coil(Modbus_Config *device_config, Modbus_Read_Coils_Request *Request,Modbus_Read_Coils_Response *Response);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct Modbus_Read_Discrete_Inputs_Request{

	uint8_t Slave_Address;
	uint16_t Starting_Address;
	uint16_t Quantity_Of_Inputs;


}Modbus_Read_Discrete_Inputs_Request;

typedef struct Modbus_Read_Discrete_Inputs_Response{

	uint8_t Byte_Count;
	uint8_t Data[250];

}Modbus_Read_Discrete_Inputs_Response;

Modbus_Flag Modbus_Read_Discrete_Inputs(Modbus_Config *device_config, Modbus_Read_Discrete_Inputs_Request *Request,Modbus_Read_Discrete_Inputs_Response *Response);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct Modbus_Read_Holding_Registers_Request{

	uint8_t Slave_Address;
	uint8_t Function_Code;
	uint16_t Starting_Address;
	uint16_t Quantity_Of_Inputs;
	uint16_t Error_Check;

}Modbus_Read_Holding_Registers_Request;

typedef struct Modbus_Read_Holding_Registers_Response{

	uint8_t Byte_Count;
	uint8_t Data[250];

}Modbus_Read_Holding_Registers_Response;

Modbus_Flag Modbus_Read_Holding_Registers(Modbus_Config *device_config,Modbus_Read_Holding_Registers_Request *Request ,Modbus_Read_Holding_Registers_Response *Response);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Modbus_Slave_Command_Processor(Modbus_Config *device_config);

Modbus_Flag Modbus_Send_Slave_Packet(Modbus_Config *device_config, uint8_t *buffer, int length);

Modbus_Register_Map_Instance* Search_Commands(Modbus_Config *config,int Function_Code, int Register_Address, Modbus_Register_Map_Instance *table);


int Compare_Commands(Modbus_Config *config, const void* a, const void* b);
int Add_Command(Modbus_Config *config,Modbus_Register_Map_Instance* table,  Modbus_Function_Codes functionCode, int registerAddress, int *data, int length);


#endif /* MODBUS_MODBUS_H_ */
