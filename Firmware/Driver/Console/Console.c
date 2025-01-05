#include "Console.h"

// Flags to control and monitor UART reception
volatile int rx_get_flag = 0; // Indicates if the reception is active
volatile int rx_flag = 0;     // Indicates if data reception is complete

#define RX_Buffer_Length 200 // Length of the reception buffer

// Variables to track the length of received data and the reception buffer
volatile int RX_Length = 0;
volatile char TRX_Buffer[RX_Buffer_Length]; // Buffer for received and transmitted data

// USART configuration structure
USART_Config serial;



/**
 * @brief Interrupt handler for UART4.
 *
 * This ISR handles the reception of data via DMA for UART4.
 * It calculates the length of the received data, prevents buffer overflow,
 * and resets the DMA stream for further reception.
 */
//void UART4_IRQHandler(void) {
//    if (rx_get_flag == 1) { // Check if reception is active
//        (void)UART4->SR; // Read the status register to clear flags
//        (void)UART4->DR; // Read the data register to clear flags
//
//        __disable_irq(); // Disable interrupts to safely update DMA configurations
//
//        // Disable DMA stream
//        serial.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;
//
//        // Calculate the length of received data
//        RX_Length = RX_Buffer_Length - serial.USART_DMA_Instance_RX.Request.Stream->NDTR;
//
//        // Prevent buffer overflow
//        if (RX_Length > RX_Buffer_Length) {
//            RX_Length = RX_Buffer_Length;
//        }
//
//        // Reset DMA stream for the next reception
//        serial.USART_DMA_Instance_RX.Request.Stream->NDTR = RX_Buffer_Length;
//        serial.USART_DMA_Instance_RX.Request.Stream->CR |= DMA_SxCR_EN;
//
//        __enable_irq(); // Re-enable interrupts
//
//        rx_flag = 1; // Set the flag indicating data reception is complete
//    }
//}

void Console_IRQ(void)
{
    if (rx_get_flag == 1) { // Check if reception is active
        (void)UART4->SR; // Read the status register to clear flags
        (void)UART4->DR; // Read the data register to clear flags

        __disable_irq(); // Disable interrupts to safely update DMA configurations

        // Disable DMA stream
        serial.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;

        // Calculate the length of received data
        RX_Length = RX_Buffer_Length - serial.USART_DMA_Instance_RX.Request.Stream->NDTR;

        // Prevent buffer overflow
        if (RX_Length > RX_Buffer_Length) {
            RX_Length = RX_Buffer_Length;
        }

        // Reset DMA stream for the next reception
        serial.USART_DMA_Instance_RX.Request.Stream->NDTR = RX_Buffer_Length;
        serial.USART_DMA_Instance_RX.Request.Stream->CR |= DMA_SxCR_EN;

        __enable_irq(); // Re-enable interrupts

        rx_flag = 1; // Set the flag indicating data reception is complete
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
void Console_Init(int32_t baudrate) {
    // Reset USART configuration to default values
    USART_Config_Reset(&serial);

    // Configure USART parameters
    serial.Port = UART4; // Use UART4 for console communication
    serial.baudrate = baudrate; // Set the baud rate
    serial.mode = USART_Configuration.Mode.Asynchronous; // Asynchronous mode
    serial.stop_bits = USART_Configuration.Stop_Bits.Bit_1; // 1 stop bit
    serial.TX_Pin = UART4_TX_Pin.PC10; // TX pin is PC10
    serial.RX_Pin = UART4_RX_Pin.PC11; // RX pin is PC11
    serial.interrupt = USART_Configuration.Interrupt_Type.IDLE_Enable; // Enable IDLE interrupt
    serial.dma_enable = USART_Configuration.DMA_Enable.TX_Enable | USART_Configuration.DMA_Enable.RX_Enable; // Enable DMA for TX and RX
    serial.ISR_Routines.Idle_Line_ISR = Console_IRQ;
    // Initialize USART
    if (USART_Init(&serial) != true) {
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
 void printConsole(char *msg, ...) {
     va_list args;
     va_start(args, msg);

     // Format the message and store it in the transmission buffer
//     vsprintf((char *)TRX_Buffer, msg, args);

     vsnprintf((char *)TRX_Buffer, RX_Buffer_Length, msg, args);

     // Get the length of the formatted string
     uint16_t len = strlen((char *)TRX_Buffer);

     // Transmit the buffer using DMA
     USART_TX_Buffer(&serial, (uint8_t *)&TRX_Buffer[0], len);

     va_end(args);
 }

//int readConsole(const char *msg, ...)
//{
//	va_list args;
//	int result;
//	rx_get_flag = 1;
//	USART_RX_Buffer(&serial, (uint8_t *)&TRX_Buffer[0], RX_Buffer_Length, 0);
//	while(rx_flag == 0){}
//	TRX_Buffer[RX_Length - 1] = 0;
//	TRX_Buffer[RX_Length - 2] = 0;
//	va_start(args, msg);
//	result = vsscanf((char *)TRX_Buffer,msg,args);
//	va_end(args);
//	rx_get_flag = 0;
//	rx_flag = 0;
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
 int readConsole(const char *msg, ...) {
     va_list args;
     int result;

     rx_get_flag = 1; // Enable reception

     // Start DMA reception
     USART_RX_Buffer(&serial, (uint8_t *)TRX_Buffer, RX_Buffer_Length, 0);

     // Wait until data reception is complete
     while (rx_flag == 0) {
         // Wait loop
     }

     // Check for valid input length
     if (RX_Length < 2) {
         // Reset flags and return error
         rx_get_flag = 0;
         rx_flag = 0;
         return -1;
     }

     // Null-terminate the received string
     TRX_Buffer[RX_Length - 1] = '\0';

     // Parse the input using the format string
     va_start(args, msg);
     result = vsscanf((char *)TRX_Buffer, msg, args);
     va_end(args);

     // Reset reception flags
     rx_get_flag = 0;
     rx_flag = 0;

     return result;
 }
