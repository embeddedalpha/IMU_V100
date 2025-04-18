/*
 * USART.c
 *
 *  Created on: Oct 18, 2023
 *      Author: kunal
 */


#include "main.h"
#include "USART.h"

 volatile  DMA_Flags_Typedef USART1_RX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART1_TX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART2_RX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART2_TX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART3_RX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART3_TX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART4_RX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART4_TX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART5_RX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART5_TX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART6_RX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART6_TX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART7_RX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART7_TX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART8_RX_DMA_Flag;
 volatile  DMA_Flags_Typedef USART8_TX_DMA_Flag;


DMA_Config xUSART_RX[6];
DMA_Config xUSART_TX[6];

int8_t usart_dma_instance_number;


USART_Config *__usart_1_config__;
USART_Config *__usart_2_config__;
USART_Config *__usart_3_config__;
USART_Config *__usart_4_config__;
USART_Config *__usart_5_config__;
USART_Config *__usart_6_config__;

volatile uint16_t USART_SR = 0;




void UART4_IRQHandler(void)
{
	USART_SR = UART4 -> SR;
	if(USART_SR & USART_SR_CTS)
	{
	    if (__usart_4_config__ ->ISR_Routines.CTS_ISR) {
	    	__usart_4_config__ ->ISR_Routines.CTS_ISR();
	    	UART4->SR &= ~USART_SR_CTS;  // Clear the Break interrupt flag
	    }
	}

	if(USART_SR & USART_SR_LBD)
	{
	    if (__usart_4_config__ ->ISR_Routines.LIN_Break_Detection_ISR) {
	    	__usart_4_config__ ->ISR_Routines.LIN_Break_Detection_ISR();
	    	UART4->SR &= ~USART_SR_LBD;  // Clear the Break interrupt flag
	    }
	}

	if(USART_SR & USART_SR_TXE)
	{
	    if (__usart_4_config__ ->ISR_Routines.Transmit_Empty_ISR) {
	    	__usart_4_config__ ->ISR_Routines.Transmit_Empty_ISR();
	    	UART4->SR &= ~USART_SR_TXE;  // Clear the Break interrupt flag
	    }
	}


	if(USART_SR & USART_SR_TC)
	{
	    if (__usart_4_config__ ->ISR_Routines.Transmission_Complete_ISR) {
	    	__usart_4_config__ ->ISR_Routines.Transmission_Complete_ISR();
	    	UART4->SR &= ~USART_SR_TC;  // Clear the Break interrupt flag
	    }
	}

	if(USART_SR & USART_SR_RXNE)
	{
	    if (__usart_4_config__ ->ISR_Routines.Receiver_Empty_ISR) {
	    	__usart_4_config__ ->ISR_Routines.Receiver_Empty_ISR();
	    	UART4->SR &= ~USART_SR_RXNE;  // Clear the Break interrupt flag
	    }
	}


	if(USART_SR & USART_SR_IDLE)
	{
	    if (__usart_4_config__ ->ISR_Routines.Idle_Line_ISR) {
	    	__usart_4_config__ ->ISR_Routines.Idle_Line_ISR();
	    	UART4->SR &= ~USART_SR_IDLE;  // Clear the Break interrupt flag
	    }
	}

	if(USART_SR & USART_SR_PE)
	{
	    if (__usart_4_config__ ->ISR_Routines.Parity_ISR) {
	    	__usart_4_config__ ->ISR_Routines.Parity_ISR();
	    	UART4->SR &= ~USART_SR_PE;  // Clear the Break interrupt flag
	    }
	}

}


void USART1_IRQHandler(void)
{
	USART_SR = USART1 -> SR;
	if(USART_SR & USART_SR_CTS)
	{
	    if (__usart_1_config__ ->ISR_Routines.CTS_ISR) {
	    	__usart_1_config__ ->ISR_Routines.CTS_ISR();
	    	USART1->SR &= ~USART_SR_CTS;  // Clear the Break interrupt flag
	    }
	}

	if(USART_SR & USART_SR_LBD)
	{
	    if (__usart_1_config__ ->ISR_Routines.LIN_Break_Detection_ISR) {
	    	__usart_1_config__ ->ISR_Routines.LIN_Break_Detection_ISR();
	    	USART1->SR &= ~USART_SR_LBD;  // Clear the Break interrupt flag
	    }
	}

	if(USART_SR & USART_SR_TXE)
	{
	    if (__usart_1_config__ ->ISR_Routines.Transmit_Empty_ISR) {
	    	__usart_1_config__ ->ISR_Routines.Transmit_Empty_ISR();
	    	USART1->SR &= ~USART_SR_TXE;  // Clear the Break interrupt flag
	    }
	}


	if(USART_SR & USART_SR_TC)
	{
	    if (__usart_1_config__ ->ISR_Routines.Transmission_Complete_ISR) {
	    	__usart_1_config__ ->ISR_Routines.Transmission_Complete_ISR();
	    	USART1->SR &= ~USART_SR_TC;  // Clear the Break interrupt flag
	    }
	}

	if(USART_SR & USART_SR_RXNE)
	{
	    if (__usart_1_config__ ->ISR_Routines.Receiver_Empty_ISR) {
	    	__usart_1_config__ ->ISR_Routines.Receiver_Empty_ISR();
	    	USART1->SR &= ~USART_SR_RXNE;  // Clear the Break interrupt flag
	    }
	}


	if(USART_SR & USART_SR_IDLE)
	{
	    if (__usart_1_config__ ->ISR_Routines.Idle_Line_ISR) {
	    	__usart_1_config__ ->ISR_Routines.Idle_Line_ISR();
	    	USART1->SR &= ~USART_SR_IDLE;  // Clear the Break interrupt flag
	    }
	}

	if(USART_SR & USART_SR_PE)
	{
	    if (__usart_1_config__ ->ISR_Routines.Parity_ISR) {
	    	__usart_1_config__ ->ISR_Routines.Parity_ISR();
	    	USART1->SR &= ~USART_SR_PE;  // Clear the Break interrupt flag
	    }
	}

}



int8_t USART_Get_Instance_Number(USART_Config *config)
{
	if(config->Port == USART1) {return 0;}
	else if(config->Port == USART2) {return 1;}
	else if(config->Port == USART3) {return 2;}
	else if(config->Port == UART4) {return 3;}
	else if(config->Port == UART5) {return 4;}
	else if(config->Port == USART6) {return 5;}
	else {return -1;}
}

void USART_Config_Reset(USART_Config *config)
{
	config->mode = USART_Configuration.Mode.Disable;
	config->hardware_flow = USART_Configuration.Hardware_Flow.Disable;
	config->baudrate = 9600;
	config->dma_enable = USART_Configuration.DMA_Enable.RX_Disable | USART_Configuration.DMA_Enable.TX_Disable;
	config->interrupt = USART_Configuration.Interrupt_Type.Disable;
}


int8_t USART_Clock_Enable(USART_Config *config)
{
	if(config->Port == USART1)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
	}
	else if(config->Port == USART2)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
	}
	else if(config->Port == USART3)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;
	}
	else if(config->Port == UART4)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_UART4EN;
	}
	else if(config->Port == UART5)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_UART5EN;
	}
	else if(config->Port == USART6)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_USART6EN;
	}
	else
	{
		return -1;
	}
	return 1;
}


int8_t USART_Clock_Disable(USART_Config *config)
{
	if(config->Port == USART1)
	{
		RCC -> APB2ENR &= ~RCC_APB2ENR_USART1EN;
	}
	else if(config->Port == USART2)
	{
		RCC -> APB1ENR &= ~RCC_APB1ENR_USART2EN;
	}
	else if(config->Port == USART3)
	{
		RCC -> APB1ENR &= ~RCC_APB1ENR_USART3EN;
	}
	else if(config->Port == UART4)
	{
		RCC -> APB1ENR &= ~RCC_APB1ENR_UART4EN;
	}
	else if(config->Port == UART5)
	{
		RCC -> APB1ENR &= ~RCC_APB1ENR_UART5EN;
	}
	else if(config->Port == USART6)
	{
		RCC -> APB2ENR &= ~RCC_APB2ENR_USART6EN;
	}
	else
	{
		return -1;
	}
	return 1;
}

static void PIN_Setup(USART_Config *config)
{
	if(config->Port == USART1)
	{
		__usart_1_config__ = config;

		if((config->mode == USART_Configuration.Mode.Asynchronous) ||
		   (config->mode == USART_Configuration.Mode.Synchronous) ||
		   (config->mode == USART_Configuration.Mode.IrDA) ||
		   (config->mode == USART_Configuration.Mode.LIN) )
		{
			if(config->TX_Pin == USART1_TX_Pin.PA9)GPIO_Pin_Init(GPIOA, USART1_TX_Pin.PA9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_1);
			else if(config->TX_Pin == USART1_TX_Pin.PB6)GPIO_Pin_Init(GPIOB, USART1_TX_Pin.PB6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_1);

			if(config->RX_Pin == USART1_RX_Pin.PA10)GPIO_Pin_Init(GPIOA, USART1_RX_Pin.PA10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_1);
			else if(config->RX_Pin == USART1_RX_Pin.PB7)GPIO_Pin_Init(GPIOB, USART1_RX_Pin.PB7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_1);

			if((config->mode == USART_Configuration.Mode.Synchronous))if(config->CLK_Pin == USART1_CLK_Pin.PA8)GPIO_Pin_Init(GPIOA, USART1_CLK_Pin.PA8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_1);

			if(config->hardware_flow != USART_Configuration.Hardware_Flow.Disable)
			{
				if(config->hardware_flow == USART_Configuration.Hardware_Flow.CTS_Enable)GPIO_Pin_Init(GPIOA, USART1_CTS_Pin.PA11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_1);
				if(config->hardware_flow == USART_Configuration.Hardware_Flow.RTS_Enable)GPIO_Pin_Init(GPIOA, USART1_RTS_Pin.PA12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_1);
				if(config->hardware_flow == USART_Configuration.Hardware_Flow.CTS_RTS_Enable)
				{
					GPIO_Pin_Init(GPIOA, USART1_CTS_Pin.PA11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_1);
					GPIO_Pin_Init(GPIOA, USART1_RTS_Pin.PA12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_1);
				}
		    }
		}
		else if((config->mode == USART_Configuration.Mode.SmartCard) ||
		   (config->mode == USART_Configuration.Mode.SmartCard_Clock) ||
		   (config->mode == USART_Configuration.Mode.Single_Wire_Half_Duplex) )
		{
			if(config->TX_Pin == USART1_TX_Pin.PA9)GPIO_Pin_Init(GPIOA, USART1_TX_Pin.PA9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_1);
			if((config->mode == USART_Configuration.Mode.SmartCard_Clock))GPIO_Pin_Init(GPIOA, USART1_CLK_Pin.PA8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_1);

		}
	}

	else if(config->Port == USART2)
	{
		__usart_2_config__ = config;
		if((config->mode == USART_Configuration.Mode.Asynchronous) ||
		   (config->mode == USART_Configuration.Mode.Synchronous) ||
		   (config->mode == USART_Configuration.Mode.IrDA) ||
		   (config->mode == USART_Configuration.Mode.LIN) )
		{
			if(config->TX_Pin == USART2_TX_Pin.PA2)GPIO_Pin_Init(GPIOA, USART2_TX_Pin.PA2, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);
			else if(config->TX_Pin == USART2_TX_Pin.PD5)GPIO_Pin_Init(GPIOD, USART2_TX_Pin.PD5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);

			if(config->RX_Pin == USART2_RX_Pin.PA3)GPIO_Pin_Init(GPIOA, USART2_RX_Pin.PA3, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);
			else if(config->RX_Pin == USART2_RX_Pin.PD6)GPIO_Pin_Init(GPIOD, USART2_RX_Pin.PD6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);

			if((config->mode == USART_Configuration.Mode.Synchronous)){
				if(config->CLK_Pin == USART2_CLK_Pin.PA4)GPIO_Pin_Init(GPIOA, USART2_CLK_Pin.PA4, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);
				else if(config->CLK_Pin == USART2_CLK_Pin.PD7)GPIO_Pin_Init(GPIOA, USART2_CLK_Pin.PD7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);
			}


			if((config->hardware_flow != USART_Configuration.Hardware_Flow.Disable) || (config->hardware_flow == USART_Configuration.Hardware_Flow.CTS_RTS_Enable))
			{
				if(config->hardware_flow == USART_Configuration.Hardware_Flow.CTS_Enable)
				{
					if(config->CLK_Pin == USART2_CTS_Pin.PA0)
					{
						GPIO_Pin_Init(GPIOA, USART2_CTS_Pin.PA0, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);
					}
					else if(config->CLK_Pin == USART2_CTS_Pin.PD3)
					{
						GPIO_Pin_Init(GPIOD, USART2_CTS_Pin.PD3, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);
					}
				}
				if((config->hardware_flow == USART_Configuration.Hardware_Flow.RTS_Enable) || (config->hardware_flow == USART_Configuration.Hardware_Flow.CTS_RTS_Enable))
				{
					if(config->CLK_Pin == USART2_RTS_Pin.PA1)
					{
						GPIO_Pin_Init(GPIOA, USART2_RTS_Pin.PA1, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);
					}
					else if(config->CLK_Pin == USART2_RTS_Pin.PD4)
					{
						GPIO_Pin_Init(GPIOD, USART2_RTS_Pin.PD4, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);
					}
				}

		    }
		}
		else if((config->mode == USART_Configuration.Mode.SmartCard) ||
		   (config->mode == USART_Configuration.Mode.SmartCard_Clock) ||
		   (config->mode == USART_Configuration.Mode.Single_Wire_Half_Duplex))
		{
			if(config->TX_Pin == USART2_TX_Pin.PA2)
			{
				GPIO_Pin_Init(GPIOA, USART2_TX_Pin.PA2, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);
			}
			else if(config->TX_Pin == USART2_TX_Pin.PD5)
			{
				GPIO_Pin_Init(GPIOD, USART2_TX_Pin.PD5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);
			}

			if((config->mode == USART_Configuration.Mode.SmartCard_Clock))
			{
				if(config->CLK_Pin == USART2_CLK_Pin.PA4)
				{
					GPIO_Pin_Init(GPIOA, USART2_CLK_Pin.PA4, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);
				}
				else if(config->CLK_Pin == USART2_CLK_Pin.PD7)
				{
					GPIO_Pin_Init(GPIOA, USART2_CLK_Pin.PD7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_2);
				}
			}
		}
	}

	else if(config->Port == USART3)
	{
		__usart_3_config__ = config;
		if((config->mode == USART_Configuration.Mode.Asynchronous) ||
		   (config->mode == USART_Configuration.Mode.Synchronous) ||
		   (config->mode == USART_Configuration.Mode.IrDA) ||
		   (config->mode == USART_Configuration.Mode.LIN) )
		{
			if(config->TX_Pin == USART3_TX_Pin.PB11)GPIO_Pin_Init(GPIOA, USART3_TX_Pin.PB11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
			else if(config->TX_Pin == USART3_TX_Pin.PC10)GPIO_Pin_Init(GPIOB, USART3_TX_Pin.PC10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
			else if(config->TX_Pin == USART3_TX_Pin.PD8)GPIO_Pin_Init(GPIOB, USART3_TX_Pin.PD8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);

			if(config->RX_Pin == USART3_RX_Pin.PB10)GPIO_Pin_Init(GPIOA, USART3_RX_Pin.PB10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
			else if(config->RX_Pin == USART3_RX_Pin.PC11)GPIO_Pin_Init(GPIOB, USART3_RX_Pin.PC11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
			else if(config->TX_Pin == USART3_TX_Pin.PD8)GPIO_Pin_Init(GPIOB, USART3_TX_Pin.PD8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);


			if((config->mode == USART_Configuration.Mode.Synchronous))
			{
				if(config->CLK_Pin == USART3_CLK_Pin.PB12)GPIO_Pin_Init(GPIOB, USART3_CLK_Pin.PB12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
				else if(config->CLK_Pin == USART3_CLK_Pin.PD10)GPIO_Pin_Init(GPIOD, USART3_CLK_Pin.PD10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);

			}

			if(config->hardware_flow != USART_Configuration.Hardware_Flow.Disable)
			{
				if((config->hardware_flow == USART_Configuration.Hardware_Flow.CTS_Enable) || (config->hardware_flow == USART_Configuration.Hardware_Flow.CTS_RTS_Enable))
				{
					if(config->CLK_Pin == USART3_CTS_Pin.PB13)GPIO_Pin_Init(GPIOB, USART3_CTS_Pin.PB13, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
					else if(config->CLK_Pin == USART3_CTS_Pin.PD11)GPIO_Pin_Init(GPIOD, USART3_CTS_Pin.PD11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
				}
				if((config->hardware_flow == USART_Configuration.Hardware_Flow.RTS_Enable) || (config->hardware_flow == USART_Configuration.Hardware_Flow.CTS_RTS_Enable))
				{
					if(config->CLK_Pin == USART3_RTS_Pin.PB14)GPIO_Pin_Init(GPIOB, USART3_RTS_Pin.PB14, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
					else if(config->CLK_Pin == USART3_RTS_Pin.PD12)GPIO_Pin_Init(GPIOD, USART3_RTS_Pin.PD12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
				}
		    }
		}
		else if((config->mode == USART_Configuration.Mode.SmartCard) ||
		   (config->mode == USART_Configuration.Mode.SmartCard_Clock) ||
		   (config->mode == USART_Configuration.Mode.Single_Wire_Half_Duplex) )
		{
			if(config->TX_Pin == USART3_TX_Pin.PB11)GPIO_Pin_Init(GPIOA, USART3_TX_Pin.PB11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
			else if(config->TX_Pin == USART3_TX_Pin.PC10)GPIO_Pin_Init(GPIOB, USART3_TX_Pin.PC10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
			else if(config->TX_Pin == USART3_TX_Pin.PD8)GPIO_Pin_Init(GPIOB, USART3_TX_Pin.PD8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
			if(config->CLK_Pin == USART3_CLK_Pin.PB12)GPIO_Pin_Init(GPIOB, USART3_CLK_Pin.PB12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);
			else if(config->CLK_Pin == USART3_CLK_Pin.PD10)GPIO_Pin_Init(GPIOD, USART3_CLK_Pin.PD10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_3);

		}
	}
	else if(config -> Port == UART4)
	{
		__usart_4_config__ = config;
		if((config->mode == USART_Configuration.Mode.Asynchronous) ||
		   (config->mode == USART_Configuration.Mode.IrDA) ||
		   (config->mode == USART_Configuration.Mode.LIN))
		{
			if(config->TX_Pin == UART4_TX_Pin.PA0)GPIO_Pin_Init(GPIOA, UART4_TX_Pin.PA0, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_4);
			else if(config->TX_Pin == UART4_TX_Pin.PC10)GPIO_Pin_Init(GPIOC, UART4_TX_Pin.PC10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_4);

			if(config->RX_Pin == UART4_RX_Pin.PA1)GPIO_Pin_Init(GPIOA, UART4_RX_Pin.PA1, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_4);
			else if(config->RX_Pin == UART4_RX_Pin.PC11)GPIO_Pin_Init(GPIOC, UART4_RX_Pin.PC11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_4);
		}
	}
	else if(config -> Port == UART5)
	{
		__usart_5_config__ = config;
		if((config->mode == USART_Configuration.Mode.Asynchronous) ||
		   (config->mode == USART_Configuration.Mode.IrDA) ||
		   (config->mode == USART_Configuration.Mode.LIN))
		{
			if(config->TX_Pin == UART5_TX_Pin.PD2)GPIO_Pin_Init(GPIOA, UART5_TX_Pin.PD2, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.UART_5);
			if(config->RX_Pin == UART5_RX_Pin.PC12)GPIO_Pin_Init(GPIOA, UART5_RX_Pin.PC12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.UART_5);
		}
	}
	else if(config->Port == USART6)
	{
		if((config->mode == USART_Configuration.Mode.Asynchronous) ||
		   (config->mode == USART_Configuration.Mode.Synchronous) ||
		   (config->mode == USART_Configuration.Mode.IrDA) ||
		   (config->mode == USART_Configuration.Mode.LIN) )
		{
			if(config->TX_Pin == USART6_TX_Pin.PC6)GPIO_Pin_Init(GPIOC, USART6_TX_Pin.PC6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_6);
			if(config->RX_Pin == USART6_RX_Pin.PC7)GPIO_Pin_Init(GPIOC, USART6_RX_Pin.PC7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_6);
			if(config->CLK_Pin == USART6_CLK_Pin.PC8)GPIO_Pin_Init(GPIOC, USART6_CLK_Pin.PC8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_6);
		}
		else if((config->mode == USART_Configuration.Mode.SmartCard) ||
		   (config->mode == USART_Configuration.Mode.SmartCard_Clock) ||
		   (config->mode == USART_Configuration.Mode.Single_Wire_Half_Duplex) )
		{
			if(config->TX_Pin == USART6_TX_Pin.PC6)GPIO_Pin_Init(GPIOA, USART6_TX_Pin.PC6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_6);
			if((config->mode == USART_Configuration.Mode.SmartCard_Clock))GPIO_Pin_Init(GPIOA, USART6_CLK_Pin.PC8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.USART_6);

		}
	}


}


int8_t USART_Init(USART_Config *config)
{
	USART_Clock_Enable(config);
	PIN_Setup(config);

	usart_dma_instance_number = USART_Get_Instance_Number(config);
	if(usart_dma_instance_number == -1) return -1;

//	USART1 -> CR1 |= USART_CR1_UE;


	double brr;
	double div_frac, mantissa;
	int div_frac_1;
	int mantissa_1;

	if(config -> Port == USART1)
	{
		int32_t freq = SystemAPB2_Clock_Speed();
		 brr = (freq/ (16.0 * 2.0 * (double)(config->baudrate)));

		 separateFractionAndIntegral(brr, &div_frac, &mantissa);
		 div_frac_1 = (int)(ceil(div_frac*16.0));
		 mantissa_1 = (int)(ceil(mantissa));
	}
	else
	{
		int32_t freq = SystemAPB2_Clock_Speed();
		 brr = (freq/ (2 * 16.0 * 2.0 * (double)(config->baudrate)));

		 separateFractionAndIntegral(brr, &div_frac, &mantissa);
		 div_frac_1 = (int)(ceil(div_frac*16.0));
		 mantissa_1 = (int)(ceil(mantissa));

	}




	config->Port->BRR = (mantissa_1<<4)|(div_frac_1);
	config->Port->CR1 |= config->parity;

	if(config -> interrupt == USART_Configuration.Interrupt_Type.Disable)
	{
		config -> Port -> CR1 &= ~(USART_CR1_PEIE | USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR1_RXNEIE | USART_CR1_IDLEIE);
		config -> Port -> CR2 &= ~(USART_CR2_LBDIE);
		config -> Port -> CR3 &= ~(USART_CR3_CTSIE | USART_CR3_EIE);
	}
	else
	{
		if((config->interrupt & USART_Configuration.Interrupt_Type.Parity_Enable) == USART_Configuration.Interrupt_Type.Parity_Enable)
		{
			config -> Port -> CR1 |= USART_CR1_PEIE;
		}
		if((config->interrupt & USART_Configuration.Interrupt_Type.Transmit_Empty_Enable) == USART_Configuration.Interrupt_Type.Transmit_Empty_Enable)
		{
			config -> Port -> CR1 |= USART_CR1_TXEIE;
		}
		if((config->interrupt & USART_Configuration.Interrupt_Type.Transmission_Complete_Enable) == USART_Configuration.Interrupt_Type.Transmission_Complete_Enable)
		{
			config -> Port -> CR1 |= USART_CR1_TCIE;
		}
		if((config->interrupt & USART_Configuration.Interrupt_Type.Receiver_Empty_Enable) == USART_Configuration.Interrupt_Type.Receiver_Empty_Enable)
		{
			config -> Port -> CR1 |= USART_CR1_RXNEIE;
		}
		if((config->interrupt & USART_Configuration.Interrupt_Type.IDLE_Enable) == USART_Configuration.Interrupt_Type.IDLE_Enable)
		{
			config -> Port -> CR1 |= USART_CR1_IDLEIE;
		}

		if((config->interrupt & USART_Configuration.Interrupt_Type.LIN_Break_Detection_Enable) == USART_Configuration.Interrupt_Type.LIN_Break_Detection_Enable)
		{
			config -> Port -> CR2 |= USART_CR2_LBDIE;
		}

		if((config->interrupt & USART_Configuration.Interrupt_Type.CTS_Enable) == USART_Configuration.Interrupt_Type.CTS_Enable)
		{
			config -> Port -> CR3 |= USART_CR3_CTSIE;
		}
		if((config->interrupt & USART_Configuration.Interrupt_Type.Error_Enable) == USART_Configuration.Interrupt_Type.Error_Enable)
		{
			config -> Port -> CR3 |= USART_CR3_EIE;
		}

		if(config -> Port == USART1)
		{
			NVIC_SetPriority(USART1_IRQn, 0);
			NVIC_EnableIRQ(USART1_IRQn);
		}
		else if(config -> Port == USART2)
		{
			NVIC_EnableIRQ(USART2_IRQn);
		}
		else if(config -> Port == USART3)
		{
			NVIC_EnableIRQ(USART3_IRQn);
		}
		else if(config -> Port == UART4)
		{
			NVIC_EnableIRQ(UART4_IRQn);
		}
		else if(config -> Port == UART5)
		{
			NVIC_EnableIRQ(UART5_IRQn);
		}
		else if(config -> Port == USART6)
		{
			NVIC_EnableIRQ(USART6_IRQn);
		}

	}


	config->Port->CR2 |= config->stop_bits;

	if((config->dma_enable & USART_Configuration.DMA_Enable.RX_Enable) == USART_Configuration.DMA_Enable.RX_Enable)
	{
		config -> Port -> CR3 |= USART_CR3_DMAR;

		if(config->Port == USART1)
		{
			xUSART_RX[0].Request = DMA_Configuration.Request.USART1_RX;
		}
		else if(config->Port == USART2)
		{
			xUSART_RX[1].Request = DMA_Configuration.Request.USART2_RX;
		}
		else if(config->Port == USART3)
		{
			xUSART_RX[2].Request = DMA_Configuration.Request.USART3_RX;
		}
		else if(config->Port == UART4)
		{
			xUSART_RX[3].Request = DMA_Configuration.Request.UART4_RX;
		}
		else if(config->Port == UART5)
		{
			xUSART_RX[4].Request = DMA_Configuration.Request.UART5_RX;
		}
		else
		{
			xUSART_RX[5].Request = DMA_Configuration.Request.UART6_RX;
		}

		xUSART_RX[usart_dma_instance_number].circular_mode = DMA_Configuration.Circular_Mode.Disable;
		xUSART_RX[usart_dma_instance_number].flow_control = DMA_Configuration.Flow_Control.DMA_Control;
		xUSART_RX[usart_dma_instance_number].interrupts = DMA_Configuration.DMA_Interrupts.Disable;
		xUSART_RX[usart_dma_instance_number].memory_data_size = DMA_Configuration.Memory_Data_Size.byte;
		xUSART_RX[usart_dma_instance_number].peripheral_data_size = DMA_Configuration.Peripheral_Data_Size.byte;
		xUSART_RX[usart_dma_instance_number].peripheral_pointer_increment = DMA_Configuration.Peripheral_Pointer_Increment.Disable;
		xUSART_RX[usart_dma_instance_number].memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;
		xUSART_RX[usart_dma_instance_number].priority_level = DMA_Configuration.Priority_Level.High;
		xUSART_RX[usart_dma_instance_number].transfer_direction = DMA_Configuration.Transfer_Direction.Peripheral_to_memory;
		config ->USART_DMA_Instance_RX = xUSART_RX[usart_dma_instance_number];
		DMA_Init(&xUSART_RX[usart_dma_instance_number]);
	}
	else
	{
		config -> Port  -> CR3 &= ~USART_CR3_DMAR;
	}

	if((config->dma_enable & USART_Configuration.DMA_Enable.TX_Enable) == USART_Configuration.DMA_Enable.TX_Enable)
	{

		config -> Port  -> CR3 |= USART_CR3_DMAT;

		if(config->Port == USART1)
		{
			xUSART_TX[0].Request = DMA_Configuration.Request.USART1_TX;
		}
		else if(config->Port == USART2)
		{
			xUSART_TX[1].Request = DMA_Configuration.Request.USART2_TX;
		}
		else if(config->Port == USART3)
		{
			xUSART_TX[2].Request = DMA_Configuration.Request.USART3_TX;
		}
		else if(config->Port == UART4)
		{
			xUSART_TX[3].Request = DMA_Configuration.Request.UART4_TX;
		}
		else if(config->Port == UART5)
		{
			xUSART_TX[4].Request = DMA_Configuration.Request.UART5_TX;
		}
		else
		{
			xUSART_TX[5].Request = DMA_Configuration.Request.UART6_TX;
		}

		xUSART_TX[usart_dma_instance_number].circular_mode = DMA_Configuration.Circular_Mode.Disable;
		xUSART_TX[usart_dma_instance_number].flow_control = DMA_Configuration.Flow_Control.DMA_Control;
		xUSART_TX[usart_dma_instance_number].interrupts = DMA_Configuration.DMA_Interrupts.Transfer_Complete ;
		xUSART_TX[usart_dma_instance_number].memory_data_size = DMA_Configuration.Memory_Data_Size.byte;
		xUSART_TX[usart_dma_instance_number].peripheral_data_size = DMA_Configuration.Peripheral_Data_Size.byte;
		xUSART_TX[usart_dma_instance_number].peripheral_pointer_increment = DMA_Configuration.Peripheral_Pointer_Increment.Disable;
		xUSART_TX[usart_dma_instance_number].memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;
		xUSART_TX[usart_dma_instance_number].priority_level = DMA_Configuration.Priority_Level.Very_high;
		xUSART_TX[usart_dma_instance_number].transfer_direction = DMA_Configuration.Transfer_Direction.Memory_to_peripheral;
		config ->USART_DMA_Instance_TX = xUSART_TX[usart_dma_instance_number];
		DMA_Init(&xUSART_TX[usart_dma_instance_number]);
	}
	else
	{
		config -> Port -> CR3 &= ~USART_CR3_DMAT;
	}

	if(config->mode == USART_Configuration.Mode.Single_Wire_Half_Duplex) config -> Port -> CR3 |= USART_CR3_HDSEL;
	if(config->mode == USART_Configuration.Mode.LIN) config -> Port -> CR2 |= USART_CR2_LINEN;


	config->Port->CR1 |= USART_CR1_RE | USART_CR1_TE  ;
	config->Port-> CR1 |= USART_CR1_UE;

	return 1;
}

int8_t USART_TX_Buffer(USART_Config *config, uint8_t *tx_buffer, uint16_t length)
{
	if(config->dma_enable |= USART_Configuration.DMA_Enable.TX_Enable)
	{
		config -> Port -> SR &= ~USART_SR_TC;
		xUSART_TX[usart_dma_instance_number].memory_address = (uint32_t)tx_buffer;
		xUSART_TX[usart_dma_instance_number].peripheral_address = (uint32_t)&config->Port->DR;
		xUSART_TX[usart_dma_instance_number].buffer_length = length;
		DMA_Set_Target(&xUSART_TX[usart_dma_instance_number]);
		DMA_Set_Trigger(&xUSART_TX[usart_dma_instance_number]);


		if(config->Port == USART1)
		{
			if(USART1_TX_DMA_Flag.Triggered != 1)
			{
				USART1_TX_DMA_Flag.Transfer_Complete_Flag = (xUSART_TX[usart_dma_instance_number].Request.Controller -> HISR & DMA_HISR_TCIF7_Msk) >> DMA_HISR_TCIF7_Pos;
				USART1_TX_DMA_Flag.Transfer_Complete_Flag = (xUSART_TX[usart_dma_instance_number].Request.Controller -> HISR & DMA_HISR_HTIF7_Msk) >> DMA_HISR_HTIF7_Pos;
			}

			while((USART1_TX_DMA_Flag.Transfer_Complete_Flag == false))
			{
				if(USART1_TX_DMA_Flag.Transfer_Error_Flag == true) {return -1;}
			}
			USART1_TX_DMA_Flag.Transfer_Complete_Flag = false;
			DMA_Reset_Flags(&USART1_TX_DMA_Flag);
		}
		else if(config->Port == USART2)
		{
			while((USART2_TX_DMA_Flag.Transfer_Complete_Flag == false))
			{
				if(USART2_TX_DMA_Flag.Transfer_Error_Flag == true)  {return -1;}
			}
			USART2_TX_DMA_Flag.Transfer_Complete_Flag = false;
			DMA_Reset_Flags(&USART2_TX_DMA_Flag);
		}
		else if(config->Port == USART3)
		{
			while((USART3_TX_DMA_Flag.Transfer_Complete_Flag == false))
			{
				if(USART3_TX_DMA_Flag.Transfer_Error_Flag == true)  {return -1;}
			}
			USART3_TX_DMA_Flag.Transfer_Complete_Flag = false;
			DMA_Reset_Flags(&USART3_TX_DMA_Flag);
		}
		else if(config->Port == UART4)
		{
			while((USART4_TX_DMA_Flag.Transfer_Complete_Flag == false))
			{
				if(USART4_TX_DMA_Flag.Transfer_Error_Flag == true)  {return -1;}
			}
			USART4_TX_DMA_Flag.Transfer_Complete_Flag = false;
			DMA_Reset_Flags(&USART4_TX_DMA_Flag);
		}
		else if(config->Port == UART5)
		{
			while((USART5_TX_DMA_Flag.Transfer_Complete_Flag == false))
			{
				if(USART5_TX_DMA_Flag.Transfer_Error_Flag == true) {return -1;}
			}
			USART5_TX_DMA_Flag.Transfer_Complete_Flag = false;
			DMA_Reset_Flags(&USART5_TX_DMA_Flag);
		}
		else if(config->Port == USART6)
		{
			while((USART6_TX_DMA_Flag.Transfer_Complete_Flag == false))
			{
				if(USART6_TX_DMA_Flag.Transfer_Error_Flag == true) {return -1;}
			}
			USART6_TX_DMA_Flag.Transfer_Complete_Flag = false;
			DMA_Reset_Flags(&USART6_TX_DMA_Flag);
		}


	}
	else
	{ //Will Take more time
		for(int i = 0; i <= length; i++)
		{
			config->Port->DR = tx_buffer[i];
			while(!(config->Port->SR & USART_SR_TXE));
		}
	}

	return 1;

}

int8_t USART_RX_Buffer(USART_Config *config, uint8_t *rx_buffer, uint16_t length, bool circular_buffer_enable)
{
	if(config->dma_enable |= USART_Configuration.DMA_Enable.RX_Enable)
	{
		if(circular_buffer_enable == 1)
		{
			xUSART_RX[usart_dma_instance_number].circular_mode = DMA_Configuration.Circular_Mode.Disable;
		}
		else
		{
			xUSART_RX[usart_dma_instance_number].circular_mode = DMA_Configuration.Circular_Mode.Enable;
		}

		xUSART_RX[usart_dma_instance_number].memory_address = (uint32_t)rx_buffer;
		xUSART_RX[usart_dma_instance_number].peripheral_address = (uint32_t)&config->Port->DR;
		xUSART_RX[usart_dma_instance_number].buffer_length = length;
		DMA_Set_Target(&xUSART_RX[usart_dma_instance_number]);
		DMA_Set_Trigger(&xUSART_RX[usart_dma_instance_number]);


		if(circular_buffer_enable == 1)
		{

		if(config->Port == USART1)
		{
			while((USART1_RX_DMA_Flag.Transfer_Complete_Flag == false))
			{
				if(USART1_RX_DMA_Flag.Transfer_Error_Flag == true) {return -1;}
			}
			USART1_RX_DMA_Flag.Transfer_Complete_Flag = false;
		}
		else if(config->Port == USART2)
		{
			while((USART2_RX_DMA_Flag.Transfer_Complete_Flag == false))
			{
				if(USART2_RX_DMA_Flag.Transfer_Error_Flag == true)  {return -1;}
			}
			USART2_RX_DMA_Flag.Transfer_Complete_Flag = false;
		}
		else if(config->Port == USART3)
		{
			while((USART3_RX_DMA_Flag.Transfer_Complete_Flag == false))
			{
				if(USART3_RX_DMA_Flag.Transfer_Error_Flag == true)  {return -1;}
			}
			USART3_RX_DMA_Flag.Transfer_Complete_Flag = false;
		}
		else if(config->Port == UART4)
		{
			while((USART4_RX_DMA_Flag.Transfer_Complete_Flag == false))
			{
				if(USART4_RX_DMA_Flag.Transfer_Error_Flag == true)  {return -1;}
			}
			USART4_RX_DMA_Flag.Transfer_Complete_Flag = false;
		}
		else if(config->Port == UART5)
		{
			while((USART5_RX_DMA_Flag.Transfer_Complete_Flag == false))
			{
				if(USART5_RX_DMA_Flag.Transfer_Error_Flag == true) {return -1;}
			}
			USART5_RX_DMA_Flag.Transfer_Complete_Flag = false;
		}
		else if(config->Port == USART6)
		{
			while((USART6_RX_DMA_Flag.Transfer_Complete_Flag == false))
			{
				if(USART6_RX_DMA_Flag.Transfer_Error_Flag == true) {return -1;}
			}
			USART6_RX_DMA_Flag.Transfer_Complete_Flag = false;
		}

		}

	}
	else
	{ //Will Take more time
		for(int i = 0; i <= length; i++)
		{
			rx_buffer[i] = config->Port->DR ;
			while(!(config->Port->SR & USART_SR_RXNE));
		}
	}

	return 1;

}

void USART_TX_Single_Byte(USART_Config *config, uint8_t data)
{
	config->Port->DR = data;
	while(!(config->Port->SR & USART_SR_TXE));
}

uint16_t USART_RX_Single_Byte(USART_Config *config)
{
	uint8_t data;
	data = config->Port->DR ;
	while(!(config->Port->SR & USART_SR_RXNE));
	return data;
}

void USART_Clear_Status_Regs(USART_Config *config)
{
    (void)config->Port->SR; // Read the status register to clear flags
    (void)config->Port->DR; // Read the data register to clear flags
}
