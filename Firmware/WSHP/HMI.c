/*
 * HMI.c
 *
 *  Created on: Jan 27, 2025
 *      Author: kunal
 */


#include "WSHP.h"

// Flags to control and monitor UART reception
volatile int HMI_RX_GET_FLAG = 0; // Indicates if the reception is active
volatile int HMI_RX_FLAG = 0;     // Indicates if data reception is complete

#define RX_Buffer_Length 200 // Length of the reception buffer

// Variables to track the length of received data and the reception buffer
volatile int HMI_RX_Length = 0;
volatile char HMI_TRX_Buffer[RX_Buffer_Length]; // Buffer for received and transmitted data

// USART configuration structure
USART_Config HMI_USART;



/**
 * @brief Interrupt handler for UART4.
 *
 * This ISR handles the reception of data via DMA for UART4.
 * It calculates the length of the received data, prevents buffer overflow,
 * and resets the DMA stream for further reception.
 */
//void UART4_IRQHandler(void) {
//    if (HMI_RX_GET_FLAG == 1) { // Check if reception is active
//        (void)UART4->SR; // Read the status register to clear flags
//        (void)UART4->DR; // Read the data register to clear flags
//
//        __disable_irq(); // Disable interrupts to safely update DMA configurations
//
//        // Disable DMA stream
//        HMI_USART.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;
//
//        // Calculate the length of received data
//        HMI_RX_Length = RX_Buffer_Length - HMI_USART.USART_DMA_Instance_RX.Request.Stream->NDTR;
//
//        // Prevent buffer overflow
//        if (HMI_RX_Length > RX_Buffer_Length) {
//            HMI_RX_Length = RX_Buffer_Length;
//        }
//
//        // Reset DMA stream for the next reception
//        HMI_USART.USART_DMA_Instance_RX.Request.Stream->NDTR = RX_Buffer_Length;
//        HMI_USART.USART_DMA_Instance_RX.Request.Stream->CR |= DMA_SxCR_EN;
//
//        __enable_irq(); // Re-enable interrupts
//
//        HMI_RX_FLAG = 1; // Set the flag indicating data reception is complete
//    }
//}

void HMI_IRQ(void)
{
    if (HMI_RX_GET_FLAG == 1) { // Check if reception is active
        (void)UART4->SR; // Read the status register to clear flags
        (void)UART4->DR; // Read the data register to clear flags

        __disable_irq(); // Disable interrupts to safely update DMA configurations

        // Disable DMA stream
        HMI_USART.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;

        // Calculate the length of received data
        HMI_RX_Length = RX_Buffer_Length - HMI_USART.USART_DMA_Instance_RX.Request.Stream->NDTR;

        // Prevent buffer overflow
        if (HMI_RX_Length > RX_Buffer_Length) {
            HMI_RX_Length = RX_Buffer_Length;
        }

        // Reset DMA stream for the next reception
        HMI_USART.USART_DMA_Instance_RX.Request.Stream->NDTR = RX_Buffer_Length;
        HMI_USART.USART_DMA_Instance_RX.Request.Stream->CR |= DMA_SxCR_EN;

        __enable_irq(); // Re-enable interrupts

        HMI_RX_FLAG = 1; // Set the flag indicating data reception is complete
    }
}


/**
 * @brief Initializes the console with a specified baud rate.
 *
 * This function configures UART4 for communication, sets up DMA for
 * data handling, and prepares the GPIO pins for UART communication.
 *
 * @param baudrate Desired baud rate for UART communication.
 */
void HMI_Init(int32_t baudrate) {
    // Reset USART configuration to default values
    USART_Config_Reset(&HMI_USART);

    // Configure USART parameters
    HMI_USART.Port = UART4; // Use UART4 for console communication
    HMI_USART.baudrate = baudrate; // Set the baud rate
    HMI_USART.mode = USART_Configuration.Mode.Asynchronous; // Asynchronous mode
    HMI_USART.stop_bits = USART_Configuration.Stop_Bits.Bit_1; // 1 stop bit
    HMI_USART.TX_Pin = UART4_TX_Pin.PC10; // TX pin is PC10
    HMI_USART.RX_Pin = UART4_RX_Pin.PC11; // RX pin is PC11
    HMI_USART.interrupt = USART_Configuration.Interrupt_Type.IDLE_Enable; // Enable IDLE interrupt
    HMI_USART.dma_enable = USART_Configuration.DMA_Enable.TX_Enable | USART_Configuration.DMA_Enable.RX_Enable; // Enable DMA for TX and RX
    HMI_USART.ISR_Routines.Idle_Line_ISR = HMI_IRQ;
    // Initialize USART
    if (USART_Init(&HMI_USART) != true) {
        // Handle USART initialization failure (e.g., log error or halt execution)
    }
}


 /**
  * @brief Sends a formatted message to the console.
  *
  * This function formats a string using `vsprintf` and sends it over UART
  * using DMA. It supports formatted strings with variable arguments.
  *
  * @param msg Format string for the message to send.
  * @param ... Variable arguments for the format string.
  */
 void HMI_Send(void) {
     // Transmit the buffer using DMA
     USART_TX_Buffer(&HMI_USART, (uint8_t *)&HMI_TRX_Buffer[0], 10);
 }

//int HMI_Read_Console(const char *msg, ...)
//{
//	va_list args;
//	int result;
//	HMI_RX_GET_FLAG = 1;
//	USART_RX_Buffer(&HMI_USART, (uint8_t *)&HMI_TRX_Buffer[0], RX_Buffer_Length, 0);
//	while(HMI_RX_FLAG == 0){}
//	HMI_TRX_Buffer[HMI_RX_Length - 1] = 0;
//	HMI_TRX_Buffer[HMI_RX_Length - 2] = 0;
//	va_start(args, msg);
//	result = vsscanf((char *)HMI_TRX_Buffer,msg,args);
//	va_end(args);
//	HMI_RX_GET_FLAG = 0;
//	HMI_RX_FLAG = 0;
//	return result;
//}



 /**
  * @brief Reads a formatted input from the console.
  *
  * This function waits for user input, processes it using `vsscanf`,
  * and stores the parsed data in the provided variables.
  *
  * @param msg Format string for the expected input.
  * @param ... Pointers to variables where the input data will be stored.
  * @return Number of successfully parsed items or -1 in case of an error.
  */
 int HMI_Read_Console(const char *msg, ...) {
     va_list args;
     int result;

     HMI_RX_GET_FLAG = 1; // Enable reception

     // Start DMA reception
     USART_RX_Buffer(&HMI_USART, (uint8_t *)HMI_TRX_Buffer, RX_Buffer_Length, 0);

     // Wait until data reception is complete
     while (HMI_RX_FLAG == 0) {
         // Wait loop
     }

     // Check for valid input length
     if (HMI_RX_Length < 2) {
         // Reset flags and return error
         HMI_RX_GET_FLAG = 0;
         HMI_RX_FLAG = 0;
         return -1;
     }


     // Null-terminate the received string
     HMI_TRX_Buffer[HMI_RX_Length - 1] = '\0';

     // Parse the input using the format string
     va_start(args, msg);
     result = vsscanf((char *)HMI_TRX_Buffer, msg, args);
     va_end(args);

     // Reset reception flags
     HMI_RX_GET_FLAG = 0;
     HMI_RX_FLAG = 0;

     return result;
 }
