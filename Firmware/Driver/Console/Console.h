/**
 * @file Console.h
 * @brief Console Interface for STM32F407VGT6.
 *
 * This header file provides the interface for the console module,
 * enabling UART-based input and output for debugging and communication
 * on the STM32F407VGT6 microcontroller. The console uses DMA for efficient
 * data handling and supports formatted input/output functions similar to `printf` and `scanf`.
 *
 * @version 1.0
 * @date 2023-12-19
 *
 * @author Kunal
 * @copyright Copyright (c) 2023
 *
 * @mainpage Console Module for STM32F407VGT6
 *
 * @section intro_sec Introduction
 *
 * The Console module provides an abstraction layer for UART communication
 * on the STM32F407VGT6 microcontroller. It is designed for efficient
 * data handling using DMA and provides easy-to-use functions for formatted
 * printing and reading through a serial interface.
 *
 * @section features_sec Features
 *
 * - UART initialization with custom baud rate
 * - Formatted printing using `printConsole`
 * - Formatted input using `readConsole`
 * - DMA-based UART reception for high efficiency
 * - Designed to support common debugging and communication tasks
 *
 * @section dependencies_sec Dependencies
 *
 * The Console module depends on the following components:
 * - GPIO for UART pin configuration
 * - USART for UART initialization and communication
 * - DMA for efficient UART data handling
 *
 * Include the following headers in your project to use the Console module:
 * - `Console.h`
 * - `GPIO.h` (for GPIO configuration)
 * - `USART.h` (for UART initialization and communication)
 * - `DMA.h` (for DMA configuration)
 *
 * @section usage_sec Usage
 *
 * To use the Console module, include the `Console.h` header in your application code.
 * Initialize the console with a desired baud rate using `Console_Init`.
 * Use `printConsole` for sending formatted messages and `readConsole` for receiving formatted input.
 *
 * Example:
 * @code
 * #include "Console.h"
 *
 * int main(void) {
 *     Console_Init(9600); // Initialize UART with 9600 baud rate
 *
 *     printConsole("Hello, STM32!\n"); // Send a message
 *
 *     char buffer[20];
 *     readConsole("%s", buffer); // Read user input into buffer
 *
 *     printConsole("You entered: %s\n", buffer); // Echo the input
 *
 *     while (1) {
 *         // Application code
 *     }
 * }
 * @endcode
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "USART/USART.h"
#include "DMA/DMA.h"

/**
 * @brief Initializes the console interface with a specified baud rate.
 *
 * This function configures the UART interface for communication, including
 * setting the baud rate, enabling DMA, and configuring GPIO pins for UART.
 *
 * @param baudrate Desired baud rate for UART communication.
 */
void Console_Init(int32_t baudrate);

/**
 * @brief Sends a formatted message over the console.
 *
 * This function formats a message using `vsprintf` and sends it over UART
 * using DMA. It supports the same format specifiers as `printf`.
 *
 * @param msg Format string for the message to send.
 * @param ... Variable arguments for the format string.
 */
void printConsole(char *msg, ...);

/**
 * @brief Reads a formatted input from the console.
 *
 * This function waits for user input, processes it using `vsscanf`,
 * and stores the result in the provided variables. DMA is used for
 * efficient data reception.
 *
 * @param msg Format string for the expected input.
 * @param ... Pointers to variables where the input data will be stored.
 * @return Number of items successfully read and assigned, or -1 in case of an error.
 */
int readConsole(const char *msg, ...);

#endif /* CONSOLE_H_ */

