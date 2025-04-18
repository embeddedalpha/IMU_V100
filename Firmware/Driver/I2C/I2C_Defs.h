/*
 * I2C_Defs.h
 *
 *  Created on: Sep 25, 2024
 *      Author: kunal
 */

#ifndef I2C_I2C_DEFS_H_
#define I2C_I2C_DEFS_H_

#include "main.h"

/***************************************************************************************************************/
typedef struct __I2C_Mode__{
	uint8_t Master;
	uint8_t Slave;
}__I2C_Mode__;
/***************************************************************************************************************/
typedef struct __I2C1_SDA_Pin__{
	uint16_t PB7;
	uint16_t PB9;
}__I2C1_SDA_Pin__;

typedef struct __I2C1_SCL_Pin__{
	uint16_t PB6;
	uint16_t PB8;
}__I2C1_SCL_Pin__;
/***************************************************************************************************************/
typedef struct __I2C2_SDA_Pin__{
	uint16_t PB11;
}__I2C2_SDA_Pin__;

typedef struct __I2C2_SCL_Pin__{
	uint16_t PB10;
}__I2C2_SCL_Pin__;
/***************************************************************************************************************/
typedef struct __I2C3_SDA_Pin__{
	uint16_t PC9;
}__I2C3_SDA_Pin__;

typedef struct __I2C3_SCL_Pin__{
	uint16_t PA8;
}__I2C3_SCL_Pin__;
/***************************************************************************************************************/
typedef struct __I2C_Pin__{

	struct __I2C1__{

		__I2C1_SCL_Pin__ SCL;
		__I2C1_SDA_Pin__ SDA;
	}__I2C1__;

	struct __I2C2__{

		__I2C2_SCL_Pin__ SCL;
		__I2C2_SDA_Pin__ SDA;
	}__I2C2__;

	struct __I2C3__{

		__I2C3_SCL_Pin__ SCL;
		__I2C3_SDA_Pin__ SDA;
	}__I2C3__;

}__I2C_Pin__;


/***************************************************************************************************************/
typedef struct __I2C_Interrupts__{
	uint16_t Disable;
	uint16_t Error;
	uint16_t Event;
	uint16_t Buffer;
}__I2C_Interrupts__;
/***************************************************************************************************************/
typedef struct __I2C_Speed_Mode__{
	uint8_t SM_Mode;
	uint8_t FM_Mode;
}__I2C_Speed_Mode__;
/***************************************************************************************************************/
typedef struct __I2C_DMA_Control__{
	uint8_t Disable;
	uint8_t TX_DMA_Enable;
	uint8_t RX_DMA_Enable;
}__I2C_DMA_Control__;


static const struct I2C_Configuration
{
	__I2C_Mode__ Mode;

	__I2C_Pin__ Pin;

	__I2C_Interrupts__ Interrupts;

	__I2C_Speed_Mode__ Speed_Mode;

	__I2C_DMA_Control__ DMA_Control;

}I2C_Configuration = {

		.DMA_Control =
		{
				.Disable = 0,
				.TX_DMA_Enable = 1,
				.RX_DMA_Enable = 2,
		},

		.Speed_Mode = {
				.SM_Mode = 0,
				.FM_Mode = 1,
		},

		.Interrupts =
		{
				.Disable = 0,
				.Error = 1,
				.Event = 2,
				.Buffer = 3,
		},

		.Mode = {

				.Master = 1,
				.Slave = 2,
		},

		.Pin = {
				.__I2C1__ =
				{
						.SCL = {
								.PB6 = 206,
								.PB8 = 208,
						},

						.SDA = {
								.PB7 = 207,
								.PB9 = 209,
						},
				},

				.__I2C2__ =
				{

						.SCL = {
								.PB10 = 211,
						},

						.SDA = {
								.PB11 = 210,
						},
				},

				.__I2C3__ =
				{
						.SCL = {
								.PA8 = 108,
						},

						.SDA = {
								.PC9 = 309,
						},
				},

		      },



};


#endif /* I2C_I2C_DEFS_H_ */
