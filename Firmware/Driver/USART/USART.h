/*
 * USART.h
 *
 *  Created on: Oct 18, 2023
 *      Author: kunal
 */

#ifndef USART_H_
#define USART_H_


#include "main.h"
#include "GPIO/GPIO.h"
#include "USART_Defs.h"
#include "DMA/DMA.h"



typedef struct USART_Config
{
	USART_TypeDef *Port;
	uint32_t baudrate;
	uint8_t mode;
	uint8_t TX_Pin;
	uint8_t RX_Pin;
	uint8_t CLK_Pin;
	uint8_t CTS_Pin;
	uint8_t RTS_Pin;
	uint8_t interrupt;
	uint8_t hardware_flow;
	uint8_t stop_bits;
	uint8_t dma_enable;
	uint8_t parity;
	DMA_Config USART_DMA_Instance_TX;
	DMA_Config USART_DMA_Instance_RX;

	struct __USART_Interrupts__{
		void (*Parity_ISR)(void);
		void (*Transmit_Empty_ISR)(void);
		void (*Transmission_Complete_ISR)(void);
		void (*Receiver_Empty_ISR)(void);
		void (*Idle_Line_ISR)(void);
		void (*CTS_ISR)(void);
		void (*Error_ISR)(void);
		void (*LIN_Break_Detection_ISR)(void);
	}ISR_Routines;
}USART_Config;

int8_t USART_Clock_Enable(USART_Config *config);
int8_t USART_Clock_Disable(USART_Config *config);

void USART_Config_Reset(USART_Config *config);
int8_t USART_Get_Instance_Number(USART_Config *config);
int8_t USART_Init(USART_Config *config);

void USART_TX_Single_Byte(USART_Config *config, uint8_t data);
uint16_t USART_RX_Byte(USART_Config *config);
int8_t USART_TX_Buffer(USART_Config *config, uint8_t *tx_buffer, uint16_t length);
int8_t USART_RX_Buffer(USART_Config *config, uint8_t *rx_buffer, uint16_t length, bool circular_buffer_enable);
void USART_Clear_Status_Regs(USART_Config *config);


#endif /* USART_H_ */
