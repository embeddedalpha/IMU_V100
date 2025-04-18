/**
 * @mainpage GPIO Driver for STM32F407VGT6
 *
 * @section intro_sec Introduction
 *
 * This documentation provides an overview of the GPIO driver implementation for the STM32F407VGT6 microcontroller.
 * The GPIO driver includes functions for setting up and controlling the GPIO pins, including setting pins high or low,
 * reading pin or port states, writing to a port, and configuring GPIO interrupts.
 *
 * @section features_sec Features
 *
 * - Enable or disable GPIO clocks
 * - Initialize GPIO pins with specific configurations
 * - Set or clear individual GPIO pins
 * - Read the state of GPIO pins or the entire port
 * - Configure GPIO interrupts with edge selection and priority
 *
 * @section usage_sec Usage
 *
 * Include the `GPIO.h` and `GPIO_Defs.h` headers in your application code to access the GPIO functions and configurations.
 * Use the provided functions to initialize GPIO pins, control their states, and handle interrupts as needed.
 *
 * Example:
 * @code
 * GPIO_Pin_Init(GPIOA, 5, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, 0);
 * GPIO_Pin_High(GPIOA, 5);    // Set GPIOA pin 5 high
 * @endcode
 *
 * @section dependencies_sec Dependencies
 *
 * - `GPIO_Defs.h`: Contains the definitions and configurations for the GPIO driver.
 * - `main.h`: Include this to provide the necessary microcontroller-specific includes.
 *
 * @section author_sec Author
 *
 * Author: Your Name
 *
 * @date 2024-08-21
 * @version 1.0
 * @copyright Copyright (c) 2024
 */


#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "main.h"
#include "GPIO_Defs.h"

typedef enum {
    GPIO_SUCCESS = 0,
    GPIO_INVALID_PORT = -1,
    GPIO_INVALID_PIN = -2,
    GPIO_INVALID_MODE = -3,
    GPIO_INVALID_SPEED = -4,
} GPIO_Status;



typedef struct GPIO_Pin
{
	uint16_t Pin_numer;
	GPIO_TypeDef *Port;
}GPIO_Pin;

/**
 * @brief  Sets a specific pin low.
 * @param  Port: Pointer to GPIO port base address.
 * @param  pin: Pin number to set low (0-15).
 */
__STATIC_INLINE  void GPIO_Pin_Low(GPIO_TypeDef *Port, int pin)
{
	Port -> ODR &= ~(1 << pin);
}


__STATIC_INLINE  void GPIO_Pin_Toggle(GPIO_TypeDef *Port, int pin)
{
	Port -> ODR ^= (1 << pin);
}

/**
 * @brief  Reads the entire GPIO port.
 * @param  Port: Pointer to GPIO port base address.
 * @retval Port input data register value.
 */
__STATIC_INLINE  uint16_t GPIO_Port_Read(GPIO_TypeDef *Port)
{
	return Port -> IDR;
}



/**
 * @brief  Writes data to the GPIO port.
 * @param  Port: Pointer to GPIO port base address.
 * @param  data: Data to be written to the port output data register.
 */
__STATIC_INLINE  void GPIO_Write_Port(GPIO_TypeDef *Port, uint16_t data)
{
	Port -> ODR = data;
}

/**
 * @brief  Reads the state of a specific pin.
 * @param  Port: Pointer to GPIO port base address.
 * @param  pin: Pin number to read (0-15).
 * @retval Pin state (0 or 1).
 */
__STATIC_INLINE  uint16_t GPIO_Read_Pin(GPIO_TypeDef *Port, uint8_t pin)
{
	return (Port->IDR & (1<<pin)) >> pin;
}


/**
 * @brief  Sets a specific pin high.
 * @param  Port: Pointer to GPIO port base address.
 * @param  pin: Pin number to set high (0-15).
 */
__STATIC_INLINE  void GPIO_Pin_High(GPIO_TypeDef *Port, int pin)
{
	Port -> ODR |= 1 << pin;
}



/**
 * @brief  Disables the clock for a specific GPIO port.
 * @param  PORT: Pointer to GPIO port base address.
 * @retval 0 on success, -1 on failure.
 */
int GPIO_Clock_Disable(GPIO_TypeDef *PORT);

/**
 * @brief  Enables the clock for a specific GPIO port.
 * @param  PORT: Pointer to GPIO port base address.
 * @retval 0 on success, -1 on failure.
 */
int GPIO_Clock_Enable(GPIO_TypeDef *PORT);

/**
 * @brief  Initializes a specific pin with given parameters.
 * @param  Port: Pointer to GPIO port base address.
 * @param  pin: Pin number to initialize (0-15).
 * @param  mode: Pin mode (input, output, alternate function, analog).
 * @param  output_type: Output type (push-pull, open-drain).
 * @param  speed: Speed level (low, medium, high, very high).
 * @param  pull: Pull-up/pull-down configuration (none, pull-up, pull-down).
 * @param  alternate_function: Alternate function selection (0-15).
 */
GPIO_Status GPIO_Pin_Init(GPIO_TypeDef *Port, uint8_t pin, uint8_t mode, uint8_t output_type, uint8_t speed, uint8_t pull, uint8_t alternate_function);


/**
 * @brief  Configures the interrupt for a specific pin.
 * @param  pin: Pin number to configure (0-15).
 * @param  edge_select: Interrupt edge selection (0: rising, 1: falling, 2: both).
 * @param  priority: Interrupt priority.
 */
void GPIO_Interrupt_Setup(GPIO_TypeDef *Port,int pin, int edge_select, uint32_t priority, void (*attach_ISR));

#endif /* GPIO_GPIO_H_ */









