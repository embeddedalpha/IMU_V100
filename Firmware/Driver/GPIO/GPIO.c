/**
 * @file GPIO.c
 * @brief GPIO Driver Implementation for STM32F407VGT6.
 *
 * This file provides the implementation of the GPIO driver for the STM32F407VGT6 microcontroller.
 * It includes functions to initialize GPIO pins, handle GPIO interrupts, and manage GPIO port configurations.
 *
 * @version 1.0
 * @date 2024-08-21
 *
 * @author Your Name
 */

#include "GPIO.h"

// Macro to map GPIO ports to their index for EXTI configuration
#define PORT_TO_INDEX(port) ((port == GPIOA) ? 0 : \
                            (port == GPIOB) ? 1 : \
                            (port == GPIOC) ? 2 : \
                            (port == GPIOD) ? 3 : \
                            (port == GPIOE) ? 4 : \
                            (port == GPIOF) ? 5 : \
                            (port == GPIOG) ? 6 : \
                            (port == GPIOH) ? 7 : \
                            (port == GPIOI) ? 8 : -1)

// Macro defining the split point between AFR[0] and AFR[1] registers
#define GPIO_AF_SPLIT_POINT 8

// Macro to calculate the bit position for a GPIO pin
#define PIN_POS(pin) ((pin) * 2)

// Array to store function pointers for EXTI ISRs (Interrupt Service Routines)
void (*EXTI_ISR[16])(void);

/**
 * @brief Interrupt handler for EXTI line 0.
 *
 * This ISR handles interrupts for pin 0, invoking the associated callback
 * function if one is registered.
 */
void EXTI0_IRQHandler(void) {
    if (EXTI_ISR[0]) EXTI_ISR[0](); // Invoke registered callback
    EXTI->PR |= EXTI_PR_PR0;        // Clear interrupt flag
}

/**
 * @brief Interrupt handler for EXTI line 1.
 */
void EXTI1_IRQHandler(void) {
    if (EXTI_ISR[1]) EXTI_ISR[1]();
    EXTI->PR |= EXTI_PR_PR1;
}

/**
 * @brief Interrupt handler for EXTI line 2.
 */
void EXTI2_IRQHandler(void) {
    if (EXTI_ISR[2]) EXTI_ISR[2]();
    EXTI->PR |= EXTI_PR_PR2;
}

/**
 * @brief Interrupt handler for EXTI line 3.
 */
void EXTI3_IRQHandler(void) {
    if (EXTI_ISR[3]) EXTI_ISR[3]();
    EXTI->PR |= EXTI_PR_PR3;
}

/**
 * @brief Interrupt handler for EXTI line 4.
 */
void EXTI4_IRQHandler(void) {
    if (EXTI_ISR[4]) EXTI_ISR[4]();
    EXTI->PR |= EXTI_PR_PR4;
}

/**
 * @brief Interrupt handler for EXTI lines 5 to 9.
 *
 * Handles interrupts for pins 5 to 9, checking each pin for active flags.
 */
void EXTI9_5_IRQHandler(void) {
    for (int i = 5; i <= 9; ++i) {
        if ((EXTI->PR & (1 << i)) && EXTI_ISR[i]) {
            EXTI_ISR[i]();        // Invoke callback for pin `i`
            EXTI->PR |= (1 << i); // Clear interrupt flag
        }
    }
}

/**
 * @brief Interrupt handler for EXTI lines 10 to 15.
 *
 * Handles interrupts for pins 10 to 15, checking each pin for active flags.
 */
void EXTI15_10_IRQHandler(void) {
    for (int i = 10; i <= 15; ++i) {
        if ((EXTI->PR & (1 << i)) && EXTI_ISR[i]) {
            EXTI_ISR[i]();        // Invoke callback for pin `i`
            EXTI->PR |= (1 << i); // Clear interrupt flag
        }
    }
}

/**
 * @brief Configures an interrupt for a specific GPIO pin.
 *
 * Sets up the EXTI line, enables interrupt handling, and registers a callback
 * for a specified GPIO pin.
 *
 * @param Port Pointer to GPIO port base address.
 * @param pin Pin number (0-15) to configure.
 * @param edge_select Interrupt edge selection (rising, falling, or both).
 * @param priority Interrupt priority level.
 * @param attach_ISR Pointer to the ISR function to invoke on interrupt.
 */
void GPIO_Interrupt_Setup(GPIO_TypeDef *Port, int pin, int edge_select, uint32_t priority, void (*attach_ISR)) {
    int port_data = PORT_TO_INDEX(Port);

    if (port_data < 0 || pin < 0 || pin > 15) return; // Validate inputs

    // Map GPIO port to EXTI line
    SYSCFG->EXTICR[pin / 4] |= port_data << ((pin % 4) * 4);

    // Enable EXTI interrupt mask
    EXTI->IMR |= (1 << pin);

    // Configure rising/falling edge triggers
    EXTI->RTSR &= ~(1 << pin); // Clear rising edge trigger
    EXTI->FTSR &= ~(1 << pin); // Clear falling edge trigger
    switch (edge_select) {
        case 0:
            EXTI->RTSR |= (1 << pin);
            break;
        case 1:
            EXTI->FTSR |= (1 << pin);
            break;
        case 2:
            EXTI->RTSR |= (1 << pin);
            EXTI->FTSR |= (1 << pin);
            break;
    }

    // Register the callback function
    EXTI_ISR[pin] = attach_ISR;

    // Configure NVIC for the EXTI line
    IRQn_Type irq = (pin <= 4) ? (IRQn_Type)(EXTI0_IRQn + pin) :
                    (pin <= 9) ? EXTI9_5_IRQn : EXTI15_10_IRQn;

    NVIC_SetPriority(irq, priority); // Set interrupt priority
    NVIC_EnableIRQ(irq);             // Enable NVIC interrupt
}

/**
 * @brief Disables the clock for a specific GPIO port.
 *
 * @param PORT Pointer to GPIO port base address.
 * @return GPIO_SUCCESS on success, GPIO_INVALID_PORT on failure.
 */
int GPIO_Clock_Disable(GPIO_TypeDef *PORT) {
    switch ((uint32_t)PORT) {
        case (uint32_t)GPIOA: RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN; break;
        case (uint32_t)GPIOB: RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN; break;
        case (uint32_t)GPIOC: RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN; break;
        case (uint32_t)GPIOD: RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN; break;
        case (uint32_t)GPIOE: RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN; break;
        case (uint32_t)GPIOF: RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOFEN; break;
        case (uint32_t)GPIOH: RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN; break;
        default: return GPIO_INVALID_PORT;
    }
    return GPIO_SUCCESS;
}

/**
 * @brief Enables the clock for a specific GPIO port.
 *
 * @param PORT Pointer to GPIO port base address.
 * @return GPIO_SUCCESS on success, GPIO_INVALID_PORT on failure.
 */
int GPIO_Clock_Enable(GPIO_TypeDef *PORT) {
    switch ((uint32_t)PORT) {
        case (uint32_t)GPIOA: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; break;
        case (uint32_t)GPIOB: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; break;
        case (uint32_t)GPIOC: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; break;
        case (uint32_t)GPIOD: RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; break;
        case (uint32_t)GPIOE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; break;
        case (uint32_t)GPIOF: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN; break;
        case (uint32_t)GPIOH: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN; break;
        default: return GPIO_INVALID_PORT;
    }
    return GPIO_SUCCESS;
}


GPIO_Status GPIO_Pin_Init(GPIO_TypeDef *Port, uint8_t pin, uint8_t mode, uint8_t output_type, uint8_t speed, uint8_t pull, uint8_t alternate_function) {
//    if (pin > 15 || mode > 3 || speed > 3 || pull > 2) return GPIO_INVALID_PIN;

    GPIO_Clock_Enable(Port);

    // Reset and set mode
    Port->MODER &= ~(3 << PIN_POS(pin));
    Port->MODER |= mode << PIN_POS(pin);

    // Reset and set output type
    Port->OTYPER &= ~(1 << pin);
    if (output_type != GPIO_Configuration.Output_Type.None) {
        Port->OTYPER |= output_type << pin;
    }

    // Reset and set speed
    Port->OSPEEDR &= ~(3 << PIN_POS(pin));
    if (speed != GPIO_Configuration.Speed.None) {
        Port->OSPEEDR |= speed << PIN_POS(pin);
    }

    // Reset and set pull-up/pull-down
    Port->PUPDR &= ~(3 << PIN_POS(pin));
    if (pull != GPIO_Configuration.Pull.None) {
        Port->PUPDR |= pull << PIN_POS(pin);
    }

    // Set alternate function
    if (mode == GPIO_Configuration.Mode.Alternate_Function) {
        if (pin < GPIO_AF_SPLIT_POINT) {
            Port->AFR[0] &= ~(0xF << (pin * 4));
            Port->AFR[0] |= alternate_function << (pin * 4);
        } else {
            Port->AFR[1] &= ~(0xF << ((pin - GPIO_AF_SPLIT_POINT) * 4));
            Port->AFR[1] |= alternate_function << ((pin - GPIO_AF_SPLIT_POINT) * 4);
        }
    }

    return GPIO_SUCCESS;
}



