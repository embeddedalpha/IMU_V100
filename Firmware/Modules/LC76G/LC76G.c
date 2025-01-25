/*
 * LC76G.c
 *
 *  Created on: Jan 4, 2025
 *      Author: kunal
 */

#include "LC76G.h"

// Flags to control and monitor UART reception
volatile int gps_rx_get_flag = 0; // Indicates if the reception is active
volatile int gps_rx_flag = 0;     // Indicates if data reception is complete

#define GPS_RX_Buffer_Length 200 // Length of the reception buffer

// Variables to track the length of received data and the reception buffer
volatile int GPS_RX_Length = 0;
volatile char GPS_Buffer[GPS_RX_Buffer_Length]; // Buffer for received and transmitted data

USART_Config GPS_Serial;

// Taken from quectel_lc26gablc76glc86g_series_gnss_protocol_specification_v1-4.pdf page no 13/139
// pData is the data array whose checksum needs to be calculated:
static unsigned char Ql_Check_XOR(const unsigned char *pData, unsigned int Length)
{
 unsigned char result = 0;
 unsigned int i = 0;
 if((NULL == pData) || (Length < 1))
 {
 return 0;
 }
 for(i = 0; i < Length; i++)
 {
 result ^= *(pData + i);
 }
 return result;
}


void GPS_PPS_ISR(void)
{
	 gps_rx_get_flag = 1; // Enable reception

	 USART_RX_Buffer(&GPS_Serial, (uint8_t *)GPS_Buffer, GPS_RX_Buffer_Length, 0);
}

void Get_GPS_Data_ISR(void)
{
    if (gps_rx_get_flag == 1) { // Check if reception is active
        (void)UART4->SR; // Read the status register to clear flags
        (void)UART4->DR; // Read the data register to clear flags

        __disable_irq(); // Disable interrupts to safely update DMA configurations

        // Disable DMA stream
        GPS_Serial.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;

        // Calculate the length of received data
        GPS_RX_Length = GPS_RX_Buffer_Length - GPS_Serial.USART_DMA_Instance_RX.Request.Stream->NDTR;

        // Prevent buffer overflow
        if (GPS_RX_Length > GPS_RX_Buffer_Length) {
        	GPS_RX_Length = GPS_RX_Buffer_Length;
        }

        // Reset DMA stream for the next reception
        GPS_Serial.USART_DMA_Instance_RX.Request.Stream->NDTR = GPS_RX_Buffer_Length;
        GPS_Serial.USART_DMA_Instance_RX.Request.Stream->CR |= DMA_SxCR_EN;

        __enable_irq(); // Re-enable interrupts

        gps_rx_flag = 1; // Set the flag indicating data reception is complete
    }
}


LC76G_Status_Flag LC76G_Init(uint32_t baudrate)
{

    // Configure USART parameters
	GPS_Serial.Port = USART1; // Use UART4 for console communication
	GPS_Serial.baudrate = baudrate; // Set the baud rate
	GPS_Serial.mode = USART_Configuration.Mode.Asynchronous; // Asynchronous mode
	GPS_Serial.stop_bits = USART_Configuration.Stop_Bits.Bit_1; // 1 stop bit
	GPS_Serial.TX_Pin = USART1_TX_Pin.PA9; // TX pin is PA9
	GPS_Serial.RX_Pin = USART1_RX_Pin.PA10; // RX pin is PA10
	GPS_Serial.interrupt = USART_Configuration.Interrupt_Type.IDLE_Enable; // Enable IDLE interrupt
	GPS_Serial.dma_enable = USART_Configuration.DMA_Enable.TX_Enable | USART_Configuration.DMA_Enable.RX_Enable; // Enable DMA for TX and RX
	GPS_Serial.ISR_Routines.Idle_Line_ISR = Get_GPS_Data_ISR;
    // Initialize USART
    if (USART_Init(&GPS_Serial) != true) {
    	return Init_Fail;
    }

    return Init_Success;

}
LC76G_Status_Flag LC76G_Process_Data(LC76G_Data_Typedef *data)
{
	const char GNGGA[] = "$GNGGA";
	const char GNVTG[] = "$GNVTG";
	const char GNRMC[] = "$GNRMC";
	const char GBGSV[] = "$GBGSV";
	const char GAGSV[] = "$GAGSV";
	const char GLGSV[] = "$GLGSV";
	const char GPGSV[] = "$GPGSV";
	const char GNGSA[] = "$GNGSA";

	if(gps_rx_flag == 1)
	{


		char* token = strtok((char *)GPS_Buffer, ",");
		if(token == NULL) return Bad_String;

		if(strcmp(token, GNGGA)){
//			Ql_Check_XOR()
		}
		if(strcmp(token, GNVTG)){}
		if(strcmp(token, GNRMC)){}
		if(strcmp(token, GBGSV)){}
		if(strcmp(token, GAGSV)){}
		if(strcmp(token, GLGSV)){}
		if(strcmp(token, GPGSV)){}
		if(strcmp(token, GNGSA)){}



	}

	 return Process_Success;
}
