/*
 * CAN_Defs.h
 *
 *  Created on: Feb 19, 2025
 *      Author: kunal
 */

#ifndef CAN_CAN_DEFS_H_
#define CAN_CAN_DEFS_H_

#include "main.h"



static const struct CAN_Configuration
{
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	struct  Instance{
		CAN_TypeDef *_CAN1;
		CAN_TypeDef *_CAN2;
	} Instance;
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	struct  Pin{
		struct _CAN1{
			struct RX{
				uint8_t PA11;
				uint8_t PD0;
				uint8_t PB8;
			}RX;
			struct TX{
				uint8_t PA12;
				uint8_t PD1;
				uint8_t PB9;
			}TX;
		}_CAN1;
		struct _CAN2{
			 struct{
				uint8_t PB12;
				uint8_t PB5;
			}RX;
			struct{
				uint8_t PB13;
				uint8_t PB6;
			}TX;
		}_CAN2;
	} Pin;
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	struct  Baudrate{
	uint32_t  _1000_KBPS ;
	uint32_t   _750_KBPS;
	uint32_t   _500_KBPS;
	uint32_t   _250_KBPS;
	uint32_t   _200_KBPS;
	uint32_t   _150_KBPS;
	uint32_t   _125_KBPS;
	uint32_t   _100_KBPS;
	uint32_t   _75_KBPS;
	uint32_t   _50_KBPS;
	uint32_t   _25_KBPS;
	uint32_t   _10_KBPS;
	uint32_t   _5_KBPS;
	}Baudrate;
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	struct  Frame{
		uint8_t Data_Frame;
		uint8_t Remote_Frame;
	} Frame;
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	struct  ID{
		uint8_t Standard;
		uint8_t Extended;
	} ID;
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	struct  Interrupt
	{
		uint16_t Transmit_Mailbox_Empty	;
		uint16_t Fifo0_Message_Pending	;
		uint16_t Fifo1_Message_Pending	;
		uint16_t Fifo0_Full				;
		uint16_t Fifo1_Full				;
		uint16_t Fifo0_Overflow			;
		uint16_t Fifo1_Overflow			;
	} Interrupt;

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

	struct Interrupt_ID
	{
		uint32_t Slave_Interrupt; 							// = 1 << 17,
		uint32_t Wake_UP_Interrupt;							// = 1 << 16,
		uint32_t Error_Interrupt;							// = 1 << 15,
		uint32_t Last_Error_Code_Interrupt;					// = 1 << 11,
		uint32_t Buss_Off_Interrupt;						// = 1 << 10,
		uint32_t Error_Passive_Interrupt;					// = 1 << 9,
		uint32_t Error_Warning_Interrupt;					// = 1 << 8,
		uint32_t FIFO1_Overrun_Interrupt;					// = 1 << 6,
		uint32_t FIFO1_Full_Interrupt;						// = 1 << 5,
		uint32_t FIFO1_Message_Pending_Interrupt;			// = 1 << 4,
		uint32_t FIFO0_Overrun_Interrupt;					// = 1 << 3,
		uint32_t FIFO0_Full_Interrupt;						// = 1 << 2,
		uint32_t FIFO0_Message_Pending_Interrupt;			// = 1 << 1,
		uint32_t Transmit_Mailbox_Empty_Interrupt;			// = 1 << 0,
	}Interrupt_ID;

}CAN_Configuration = {
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		. Instance = {
				._CAN1 = CAN1,
				._CAN2 = CAN2,
		},
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		. Pin ={
				._CAN1 = {
						.RX = {
								.PA11 = 11,
								.PD0  = 4,
								.PB8 = 9,
							  },

						.TX = {
								.PA12 = 12,
								.PD1  = 5,
								.PB9 = 10,
						      },
					     },
				._CAN2 = {
						.RX = {
								.PB12 = 13,
								.PB5  = 6,
						      },

						.TX = {
								.PB13 = 16,
								.PB6  = 7,
						      },
				        },
		           },
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	   . Baudrate = {
			   . _1000_KBPS = 	0x001a0002,
			   . _750_KBPS =    0x001a0003,
			   . _500_KBPS =    0x001a0005,
			   . _250_KBPS =    0x001a000b,
			   . _200_KBPS =    0x001b000d,
			   . _150_KBPS =    0x001a0013,
			   . _125_KBPS =    0x001c0014,
			   . _100_KBPS =    0x001b001b,
			   . _75_KBPS =     0x001c0022,
			   . _50_KBPS =     0x001b0037,
			   . _25_KBPS =     0x001c0068,
			   . _10_KBPS =     0x001b0117,
			   . _5_KBPS =      0x001c020c,
					},
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		. Frame = {
				.Data_Frame = 0,
				.Remote_Frame = 1,
		},
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		. ID = {
				.Standard = 0,
				.Extended = 1,
		},
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		. Interrupt = {

				.Transmit_Mailbox_Empty	 = (0x01 << 0), //(0x01 << 0)
				.Fifo0_Message_Pending	= (0x01 << 1), //(0x01 << 1)
				.Fifo1_Message_Pending	= (0x01 << 4), //(0x01 << 4)
				.Fifo0_Full				= (0x01 << 2),  //(0x01 << 2)
				.Fifo1_Full				= (0x01 << 5),  //(0x01 << 5)
				.Fifo0_Overflow			= (0x01 << 3), //(0x01 << 3)
				.Fifo1_Overflow			= (0x01 << 6), //(0x01 << 6)
		},

		.Interrupt_ID =
		{
			.Slave_Interrupt 							 = 1 << 17,
			.Wake_UP_Interrupt							 = 1 << 16,
			.Error_Interrupt							 = 1 << 15,
			.Last_Error_Code_Interrupt					 = 1 << 11,
			.Buss_Off_Interrupt						 	 = 1 << 10,
			.Error_Passive_Interrupt					 = 1 << 9,
			.Error_Warning_Interrupt					 = 1 << 8,
			.FIFO1_Overrun_Interrupt					 = 1 << 6,
			.FIFO1_Full_Interrupt						 = 1 << 5,
			.FIFO1_Message_Pending_Interrupt			 = 1 << 4,
			.FIFO0_Overrun_Interrupt					 = 1 << 3,
			.FIFO0_Full_Interrupt						 = 1 << 2,
			.FIFO0_Message_Pending_Interrupt			 = 1 << 1,
			.Transmit_Mailbox_Empty_Interrupt			 = 1 << 0,
		},
};



#endif /* CAN_CAN_DEFS_H_ */
