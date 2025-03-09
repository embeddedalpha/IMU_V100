/*
 * Modbus_Defs.h
 *
 *  Created on: Feb 28, 2025
 *      Author: kunal
 */

#ifndef MODBUS_MODBUS_DEFS_H_
#define  MODBUS_MODBUS_DEFS_H_

#include "main.h"


static const struct Modbus_Register_Map_configuration
{
	struct Access{

		bool Read;
		bool Write;

	}Access;
}Modbus_Register_Map_configuration =
		{
				.Access = {
						.Read = 0,
						.Write = 1,
				},
		};

static const struct Modbus_Configuration
{
	struct Device_Type
	{
		bool Master;
		bool Slave;
	}Device_Type;

	struct Acceptable_Function_Codes
	{
		uint8_t Read_Coils;
		uint8_t Read_Discrete_Inputs;
		uint8_t Read_Holding_Registers;
		uint8_t Read_Input_Registers;
		uint8_t Write_Single_Coil;
		uint8_t Write_Single_Register;
		uint8_t Write_Multiple_Coils;
		uint8_t Write_Multiple_Registers;

	}Acceptable_Function_Codes;


}Modbus_Configuration = {

		.Device_Type =
		{
				.Master = 0,
				.Slave = 1,
		},

		.Acceptable_Function_Codes = {
				.Read_Coils = 1 << 0,
				.Read_Discrete_Inputs  = 1 << 1,
				.Read_Holding_Registers  = 1 << 2,
				.Read_Input_Registers  = 1 << 3,
				.Write_Single_Coil  = 1 << 4,
				.Write_Single_Register  = 1 << 5,
				.Write_Multiple_Coils  = 1 << 6,
				.Write_Multiple_Registers  = 1 << 7,
		},
};










#endif /* MODBUS_MODBUS_DEFS_H_ */
