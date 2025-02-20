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
}CAN_Config;



#endif /* CAN_CAN_H_ */
