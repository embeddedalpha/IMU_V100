/*
 * CAN.h
 *
 *  Created on: Feb 19, 2025
 *      Author: kunal
 */

#ifndef CAN_CAN_H_
#define CAN_CAN_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "Timer/Timer.h"

typedef struct CAN_Config
{
	CAN_TypeDef *CAN_Port;
	uint8_t RX_Pin;
	uint8_t TX_Pin;
	uint32_t Baudrate;
	int timestamp_enable;
	int interrupt;

	struct __CAN_Interrupts__{
		void (* Sleep_ISR)(void);
		void (*Wake_UP_ISR)(void);
		void (*Error_ISR)(void);
		void (*Last_Error_Code_ISR)(void);
		void (*Bus_off_ISR)(void);
		void (*Error_Passive_ISR)(void);
		void (*Error_Warning_ISR)(void);
		void (*FIFO_Overrun_ISR)(void);
		void (*FIFO_Full_ISR)(void);
		void (*FIFO_Message_Pending_ISR)(void);
		void (*Transmit_Mailbox_Empty_ISR)(void);

	}ISR_Routines;

}CAN_Config;


void CAN_Init(CAN_Config *config);




#endif /* CAN_CAN_H_ */
