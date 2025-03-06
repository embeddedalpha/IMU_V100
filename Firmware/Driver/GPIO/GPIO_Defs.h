/**
 * @file GPIO_DEFS.h
 * @brief GPIO Configuration Definitions for STM32F407VGT6
 *
 * This file contains the definitions and structures required for configuring
 * the GPIO (General-Purpose Input/Output) pins on the STM32F407VGT6 microcontroller.
 * It includes various configurations such as mode types, output types, speed settings,
 * pull-up/pull-down settings, alternate functions, and interrupt edge configurations.
 *
 * @version 1.0
 * @date 2024-08-21
 *
 * @author Your Name
 * @copyright Copyright (c) 2024
 */


#ifndef GPIO_DEFS_H_
#define GPIO_DEFS_H_

#include "main.h"



/**
 * @brief GPIO Mode Types.
 *
 * This structure defines the various modes that a GPIO pin can be configured into.
 */
typedef struct {
    uint8_t Input;                  /**< GPIO pin configured as input */
    uint8_t General_Purpose_Output; /**< GPIO pin configured as general-purpose output */
    uint8_t Alternate_Function;     /**< GPIO pin configured for alternate functions (e.g., peripheral control) */
    uint8_t Analog;                 /**< GPIO pin configured as an analog input or output */
} GPIO_Mode_Type;

/**
 * @brief GPIO Output Types.
 *
 * This structure defines the types of output that a GPIO pin can use.
 */
typedef struct {
    uint8_t Push_Pull;  /**< GPIO pin configured as push-pull output */
    uint8_t Open_Drain; /**< GPIO pin configured as open-drain output */
    uint8_t None;       /**< No output type configured */
} GPIO_Output_Type;

/**
 * @brief GPIO Speed Types.
 *
 * This structure defines the speed options for a GPIO pin.
 */
typedef struct {
    uint8_t Low_Speed;       /**< GPIO pin configured for low-speed operation */
    uint8_t Medium_Speed;    /**< GPIO pin configured for medium-speed operation */
    uint8_t High_Speed;      /**< GPIO pin configured for high-speed operation */
    uint8_t Very_High_Speed; /**< GPIO pin configured for very high-speed operation */
    uint8_t None;            /**< No speed configured */
} GPIO_Speed;

/**
 * @brief GPIO Pull-Up/Pull-Down Types.
 *
 * This structure defines the pull-up and pull-down resistor configurations for a GPIO pin.
 */
typedef struct {
    uint8_t No_Pull_Up_Down; /**< No pull-up or pull-down resistor configured */
    uint8_t Pull_Up;         /**< GPIO pin configured with a pull-up resistor */
    uint8_t Pull_Down;       /**< GPIO pin configured with a pull-down resistor */
    uint8_t None;            /**< No pull resistor configured */
} GPIO_Pull;

/**
 * @brief GPIO Alternate Functions.
 *
 * This structure defines the alternate functions that can be assigned to a GPIO pin.
 */
typedef struct {
    uint8_t None;              /**< No alternate function configured */
    uint8_t Analog;            /**< GPIO pin configured as analog */
    uint8_t SYS;               /**< GPIO pin configured for system functions */
    uint8_t MCO1;              /**< GPIO pin configured as MCO1 */
    uint8_t MCO2;              /**< GPIO pin configured as MCO2 */
    uint8_t RTC_REFIN;         /**< GPIO pin configured for RTC_REFIN */
    uint8_t TIM_1;             /**< GPIO pin configured for TIM1 */
    uint8_t TIM_2;             /**< GPIO pin configured for TIM2 */
    uint8_t TIM_3;             /**< GPIO pin configured for TIM3 */
    uint8_t TIM_4;             /**< GPIO pin configured for TIM4 */
    uint8_t TIM_5;             /**< GPIO pin configured for TIM5 */
    uint8_t TIM_8;             /**< GPIO pin configured for TIM8 */
    uint8_t TIM_9;             /**< GPIO pin configured for TIM9 */
    uint8_t TIM_10;            /**< GPIO pin configured for TIM10 */
    uint8_t TIM_11;            /**< GPIO pin configured for TIM11 */
    uint8_t I2C_1;             /**< GPIO pin configured for I2C1 */
    uint8_t I2C_2;             /**< GPIO pin configured for I2C2 */
    uint8_t I2C_3;             /**< GPIO pin configured for I2C3 */
    uint8_t SPI_1;             /**< GPIO pin configured for SPI1 */
    uint8_t SPI_2;             /**< GPIO pin configured for SPI2 */
    uint8_t I2S_2;             /**< GPIO pin configured for I2S2 */
    uint8_t I2S_2EXT;          /**< GPIO pin configured for I2S2EXT */
    uint8_t SPI_3;             /**< GPIO pin configured for SPI3 */
    uint8_t I2S_EXT;           /**< GPIO pin configured for I2S_EXT */
    uint8_t I2S_3;             /**< GPIO pin configured for I2S3 */
    uint8_t USART_1;           /**< GPIO pin configured for USART1 */
    uint8_t USART_2;           /**< GPIO pin configured for USART2 */
    uint8_t USART_3;           /**< GPIO pin configured for USART3 */
    uint8_t I2S_3EXT;          /**< GPIO pin configured for I2S3EXT */
    uint8_t USART_4;           /**< GPIO pin configured for USART4 */
    uint8_t UART_5;            /**< GPIO pin configured for UART5 */
    uint8_t USART_6;           /**< GPIO pin configured for USART6 */
    uint8_t CAN_1;             /**< GPIO pin configured for CAN1 */
    uint8_t CAN_2;             /**< GPIO pin configured for CAN2 */
    uint8_t TIM_12;            /**< GPIO pin configured for TIM12 */
    uint8_t TIM_13;            /**< GPIO pin configured for TIM13 */
    uint8_t TIM_14;            /**< GPIO pin configured for TIM14 */
    uint8_t OTG_FS_1;          /**< GPIO pin configured for OTG_FS1 */
    uint8_t OYG_HS_1;          /**< GPIO pin configured for OYG_HS1 */
    uint8_t ETH_1;             /**< GPIO pin configured for Ethernet */
    uint8_t FSMC_1;            /**< GPIO pin configured for FSMC */
    uint8_t SDIO_1;            /**< GPIO pin configured for SDIO */
    uint8_t OTG_FS_2;          /**< GPIO pin configured for OTG_FS2 */
    uint8_t DCMI_1;            /**< GPIO pin configured for DCMI */
    uint8_t EVENTOUT;          /**< GPIO pin configured for EVENTOUT */
} GPIO_Alternate_Function;

/**
 * @brief GPIO Interrupt Edge Types.
 *
 * This structure defines the edge types for GPIO interrupts.
 */
typedef struct {
    uint8_t RISING_EDGE;         /**< Interrupt triggered on rising edge */
    uint8_t FALLING_EDGE;        /**< Interrupt triggered on falling edge */
    uint8_t RISING_FALLING_EDGE; /**< Interrupt triggered on both rising and falling edges */
} GPIO_Interrupt_Edge;

/**
 * @brief GPIO Configuration Structure.
 *
 * This structure encapsulates all the possible configurations for a GPIO pin, including mode, output type, speed, pull-up/pull-down settings, alternate functions, and interrupt edge.
 */
static const struct GPIO_Configuration {

    GPIO_Mode_Type Mode;                      /**< GPIO Mode configuration */
    GPIO_Output_Type Output_Type;             /**< GPIO Output Type configuration */
    GPIO_Speed Speed;                         /**< GPIO Speed configuration */
    GPIO_Pull Pull;                           /**< GPIO Pull-Up/Pull-Down configuration */
    GPIO_Alternate_Function Alternate_Functions; /**< GPIO Alternate Functions configuration */
    GPIO_Interrupt_Edge Interrupt_Edge;       /**< GPIO Interrupt Edge configuration */

} GPIO_Configuration = {
    .Mode = {
        .Input = 0,
        .General_Purpose_Output = 1,
        .Alternate_Function = 2,
        .Analog = 3,
    },
    .Output_Type = {
        .Push_Pull = 0,
        .Open_Drain = 1,
        .None = 2,
    },
    .Speed = {
        .Low_Speed = 0,
        .Medium_Speed = 1,
        .High_Speed = 2,
        .Very_High_Speed = 3,
        .None = 4,
    },
    .Pull = {
        .No_Pull_Up_Down = 0,
        .Pull_Up = 1,
        .Pull_Down = 2,
        .None = 4,
    },
    .Alternate_Functions = {
        .None = 0,
        .Analog = 0,
        .SYS = 0,
        .MCO1 = 0,
        .MCO2 = 0,
        .RTC_REFIN = 1,
        .TIM_1 = 1,
        .TIM_2 = 1,
        .TIM_3 = 2,
        .TIM_4 = 2,
        .TIM_5 = 2,
        .TIM_8 = 3,
        .TIM_9 = 3,
        .TIM_10 = 3,
        .TIM_11 = 3,
        .I2C_1 = 4,
        .I2C_2 = 4,
        .I2C_3 = 4,
        .SPI_1 = 5,
        .SPI_2 = 5,
        .I2S_2 = 5,
        .I2S_2EXT = 5,
        .SPI_3 = 6,
        .I2S_EXT = 6,
        .I2S_3 = 6,
        .USART_1 = 7,
        .USART_2 = 7,
        .USART_3 = 7,
        .I2S_3EXT = 7,
        .USART_4 = 8,
        .UART_5 = 8,
        .USART_6 = 8,
        .CAN_1 = 9,
        .CAN_2 = 9,
        .TIM_12 = 9,
        .TIM_13 = 9,
        .TIM_14 = 9,
        .OTG_FS_1 = 10,
        .OYG_HS_1 = 10,
        .ETH_1 = 11,
        .FSMC_1 = 12,
        .SDIO_1 = 12,
        .OTG_FS_2 = 12,
        .DCMI_1 = 13,
        .EVENTOUT = 15,
    },
    .Interrupt_Edge = {
        .RISING_EDGE = 0,
        .FALLING_EDGE = 1,
        .RISING_FALLING_EDGE = 2,
    },
};

#endif /* GPIO_DEFS_H_ */
