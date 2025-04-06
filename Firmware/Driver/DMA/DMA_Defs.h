/**
 * @file DMA_DEFS.h
 * @brief DMA Configuration Definitions for STM32F407VGT6
 *
 * This file contains the definitions and structures required for configuring
 * the DMA (Direct Memory Access) controller on the STM32F407VGT6 microcontroller.
 * It includes various configurations such as request channels, flow control,
 * transfer direction, priority levels, and interrupt settings.
 *
 * @version 1.0
 * @date 2024-08-21
 *
 * @author Your Name
 * @copyright Copyright (c) 2024
 */

#ifndef DMA_DEFS_H_
#define DMA_DEFS_H_

#include "main.h"

/**
 * @brief DMA Flags Structure
 *
 * This structure contains flags that indicate the status of a DMA transfer.
 * These flags are used to monitor and handle various states of the DMA transfer process.
 */
typedef struct DMA_Flags_Typedef
{
	bool Triggered;
    bool Transfer_Complete_Flag;       /**< Indicates if the transfer is complete */
    bool Half_Transfer_Complete_Flag;  /**< Indicates if half of the transfer is complete */
    bool Transfer_Error_Flag;          /**< Indicates if there was a transfer error */
    bool Direct_Mode_Error_Flag;       /**< Indicates if there was a direct mode error */
    bool Fifo_Error_Flag;              /**< Indicates if there was a FIFO error */

}DMA_Flags_Typedef;

/**
 * @brief DMA Request Structure
 *
 * This structure contains the configuration for a specific DMA request,
 * including the DMA controller, stream, and channel associated with the request.
 */
typedef struct DMA_Request {
    DMA_TypeDef *Controller;           /**< Pointer to the DMA controller */
    DMA_Stream_TypeDef *Stream;        /**< Pointer to the DMA stream */
    uint8_t channel;                   /**< DMA channel number */
} DMA_Request;


/**
 * @brief DMA Configuration Structure
 *
 * This structure contains all the necessary configurations for setting up the DMA controller.
 * It includes substructures for request channels, flow control, transfer direction,
 * priority levels, data size, circular mode, interrupts, and pointer increments.
 */
static const struct DMA_Configuration {

    /**
     * @brief DMA Request Channels
     *
     * This structure contains predefined DMA requests for various peripherals
     * such as SPI, I2C, USART, TIM, DAC, SDIO, and ADC.
     */
	struct Request{

	DMA_Request SPI3_RX;  /**< DMA request for SPI3 RX */
    DMA_Request SPI3_TX;  /**< DMA request for SPI3 TX */
    DMA_Request SPI2_RX;  /**< DMA request for SPI2 RX */
    DMA_Request SPI2_TX;  /**< DMA request for SPI2 TX */
    DMA_Request SPI1_RX;  /**< DMA request for SPI1 RX */
    DMA_Request SPI1_TX;  /**< DMA request for SPI1 TX */
    DMA_Request I2S2_RX;  /**< DMA request for I2S2 RX */
    DMA_Request I2S2_TX;  /**< DMA request for I2S2 TX */
    DMA_Request I2S3_RX;  /**< DMA request for I2S3 RX */
    DMA_Request I2S3_TX;  /**< DMA request for I2S3 TX */
    DMA_Request I2C1_RX;  /**< DMA request for I2C1 RX */
    DMA_Request I2C1_TX;  /**< DMA request for I2C1 TX */
    DMA_Request I2C2_RX;  /**< DMA request for I2C2 RX */
    DMA_Request I2C2_TX;  /**< DMA request for I2C2 TX */
    DMA_Request I2C3_RX;  /**< DMA request for I2C3 RX */
    DMA_Request I2C3_TX;  /**< DMA request for I2C3 TX */
    DMA_Request USART1_RX;  /**< DMA request for USART1 RX */
    DMA_Request USART1_TX;  /**< DMA request for USART1 TX */
    DMA_Request USART2_RX;  /**< DMA request for USART2 RX */
    DMA_Request USART2_TX;  /**< DMA request for USART2 TX */
    DMA_Request USART3_RX;  /**< DMA request for USART3 RX */
    DMA_Request USART3_TX;  /**< DMA request for USART3 TX */
    DMA_Request UART4_RX;   /**< DMA request for UART4 RX */
    DMA_Request UART4_TX;   /**< DMA request for UART4 TX */
    DMA_Request UART5_RX;   /**< DMA request for UART5 RX */
    DMA_Request UART5_TX;   /**< DMA request for UART5 TX */
    DMA_Request UART6_RX;   /**< DMA request for UART6 RX */
    DMA_Request UART6_TX;   /**< DMA request for UART6 TX */
    DMA_Request UART7_RX;   /**< DMA request for UART7 RX */
    DMA_Request UART7_TX;   /**< DMA request for UART7 TX */
    DMA_Request UART8_RX;   /**< DMA request for UART8 RX */
    DMA_Request UART8_TX;   /**< DMA request for UART8 TX */
    DMA_Request TIM1_UP;    /**< DMA request for TIM1 update */
    DMA_Request TIM1_CH1;   /**< DMA request for TIM1 channel 1 */
    DMA_Request TIM1_CH2;   /**< DMA request for TIM1 channel 2 */
    DMA_Request TIM1_CH3;   /**< DMA request for TIM1 channel 3 */
    DMA_Request TIM1_CH4;   /**< DMA request for TIM1 channel 4 */
    DMA_Request TIM1_TRIG;  /**< DMA request for TIM1 trigger */
    DMA_Request TIM1_COM;   /**< DMA request for TIM1 commutation */
    DMA_Request TIM8_UP;    /**< DMA request for TIM8 update */
    DMA_Request TIM8_CH1;   /**< DMA request for TIM8 channel 1 */
    DMA_Request TIM8_CH2;   /**< DMA request for TIM8 channel 2 */
    DMA_Request TIM8_CH3;   /**< DMA request for TIM8 channel 3 */
    DMA_Request TIM8_CH4;   /**< DMA request for TIM8 channel 4 */
    DMA_Request TIM8_TRIG;  /**< DMA request for TIM8 trigger */
    DMA_Request TIM8_COM;   /**< DMA request for TIM8 commutation */
    DMA_Request TIM2_UP;    /**< DMA request for TIM2 update */
    DMA_Request TIM2_CH1;   /**< DMA request for TIM2 channel 1 */
    DMA_Request TIM2_CH2;   /**< DMA request for TIM2 channel 2 */
    DMA_Request TIM2_CH3;   /**< DMA request for TIM2 channel 3 */
    DMA_Request TIM2_CH4;   /**< DMA request for TIM2 channel 4 */
    DMA_Request TIM3_CH1;   /**< DMA request for TIM3 channel 1 */
    DMA_Request TIM3_CH2;   /**< DMA request for TIM3 channel 2 */
    DMA_Request TIM3_CH3;   /**< DMA request for TIM3 channel 3 */
    DMA_Request TIM3_CH4;   /**< DMA request for TIM3 channel 4 */
    DMA_Request TIM3_UP;    /**< DMA request for TIM3 update */
    DMA_Request TIM3_TRIG;  /**< DMA request for TIM3 trigger */
    DMA_Request TIM4_CH1;   /**< DMA request for TIM4 channel 1 */
    DMA_Request TIM4_CH2;   /**< DMA request for TIM4 channel 2 */
    DMA_Request TIM4_CH3;   /**< DMA request for TIM4 channel 3 */
    DMA_Request TIM4_UP;    /**< DMA request for TIM4 update */
    DMA_Request TIM5_CH1;   /**< DMA request for TIM5 channel 1 */
    DMA_Request TIM5_CH2;   /**< DMA request for TIM5 channel 2 */
    DMA_Request TIM5_CH3;   /**< DMA request for TIM5 channel 3 */
    DMA_Request TIM5_CH4;   /**< DMA request for TIM5 channel 4 */
    DMA_Request TIM5_UP;    /**< DMA request for TIM5 update */
    DMA_Request TIM5_TRIG;  /**< DMA request for TIM5 trigger */
    DMA_Request TIM6_UP;    /**< DMA request for TIM6 update */
    DMA_Request TIM7_UP;    /**< DMA request for TIM7 update */
    DMA_Request _DAC1;      /**< DMA request for DAC1 */
    DMA_Request _DAC2;      /**< DMA request for DAC2 */
    DMA_Request SDIO_RXTX;  /**< DMA request for SDIO RX/TX */
    DMA_Request _DCMI;      /**< DMA request for DCMI */
    DMA_Request _ADC1;      /**< DMA request for ADC1 */
    DMA_Request _ADC2;      /**< DMA request for ADC2 */
    DMA_Request _ADC3;      /**< DMA request for ADC3 */
	}Request;

    /**
     * @brief Flow Control Configuration
     *
     * This structure contains settings for DMA flow control, allowing
     * either the DMA or the peripheral to control the data flow.
     */
	struct Flow_Control
	{
        uint32_t DMA_Control;         /**< DMA controls the data flow */
        uint32_t Peripheral_Control;  /**< Peripheral controls the data flow */
	}Flow_Control;

	/**
	 * @brief Transfer Direction Configuration
	 *
	 * This structure defines the direction of data transfer for DMA,
	 * including Peripheral-to-Memory, Memory-to-Peripheral, and Memory-to-Memory transfers.
	 */
	struct Transfer_Direction {
		uint32_t Peripheral_to_memory;  /**< Transfer data from peripheral to memory */
		uint32_t Memory_to_peripheral;  /**< Transfer data from memory to peripheral */
		uint32_t Memory_to_memory;      /**< Transfer data from memory to memory */
	} Transfer_Direction;

    /**
     * @brief Priority Level Configuration
     *
     * This structure defines the priority levels for DMA transfers,
     * ranging from low to very high priority.
     */
    struct Priority_Level {
        uint32_t Low;       /**< Low priority level */
        uint32_t Medium;    /**< Medium priority level */
        uint32_t High;      /**< High priority level */
        uint32_t Very_high; /**< Very high priority level */
    } Priority_Level;

    /**
     * @brief Peripheral Data Size Configuration
     *
     * This structure defines the data size for the peripheral in DMA transfers,
     * including byte, half-word, and word sizes.
     */
	struct Peripheral_Data_Size
	{
        uint32_t byte;       /**< Peripheral data size: byte */
        uint32_t half_word;  /**< Peripheral data size: half-word */
        uint32_t word;       /**< Peripheral data size: word */
	}Peripheral_Data_Size;

    /**
     * @brief Memory Data Size Configuration
     *
     * This structure defines the data size for the memory in DMA transfers,
     * including byte, half-word, and word sizes.
     */
	struct Memory_Data_Size
	{
        uint32_t byte;       /**< Memory data size: byte */
        uint32_t half_word;  /**< Memory data size: half-word */
        uint32_t word;       /**< Memory data size: word */
	}Memory_Data_Size;

    /**
     * @brief Circular Mode Configuration
     *
     * This structure defines the settings for circular mode in DMA transfers,
     * allowing the DMA to repeatedly transfer data from a peripheral to memory.
     */
	struct Circular_Mode
	{
        uint32_t Enable;  /**< Enable circular mode */
        uint32_t Disable; /**< Disable circular mode */
	}Circular_Mode;

    /**
     * @brief DMA Interrupt Configuration
     *
     * This structure defines the interrupt settings for DMA transfers,
     * including transfer complete, half transfer complete, transfer error,
     * direct mode error, FIFO error, and disable options.
     */
	struct DMA_Interrupts
	{
        uint32_t Transfer_Complete;       /**< Interrupt on transfer complete */
        uint32_t Half_Transfer_Complete;  /**< Interrupt on half transfer complete */
        uint32_t Transfer_Error;          /**< Interrupt on transfer error */
        uint32_t Direct_Mode_Error;       /**< Interrupt on direct mode error */
        uint32_t Fifo_Error;              /**< Interrupt on FIFO error */
        uint32_t Disable;                 /**< Disable all DMA interrupts */
	}DMA_Interrupts;

    /**
     * @brief Memory Pointer Increment Configuration
     *
     * This structure defines the settings for memory pointer increment in DMA transfers.
     * It allows the memory address to be incremented after each data transfer.
     */
	struct Memory_Pointer_Increment
	{
        uint32_t Enable;  /**< Enable memory pointer increment */
        uint32_t Disable; /**< Disable memory pointer increment */
	}Memory_Pointer_Increment;

    /**
     * @brief Peripheral Pointer Increment Configuration
     *
     * This structure defines the settings for peripheral pointer increment in DMA transfers.
     * It allows the peripheral address to be incremented after each data transfer.
     */
    struct Peripheral_Pointer_Increment {
        uint32_t Enable;  /**< Enable peripheral pointer increment */
        uint32_t Disable; /**< Disable peripheral pointer increment */
    } Peripheral_Pointer_Increment;


} DMA_Configuration = {

		.Circular_Mode = {

				.Enable = 1 << DMA_SxCR_CIRC_Pos,
				.Disable = 0 << DMA_SxCR_CIRC_Pos,
			},

		.Memory_Pointer_Increment = {
				.Enable = 1 << 10,
				.Disable = 0 << 10,
		},

		.Peripheral_Pointer_Increment = {
				.Enable = 1 << 9,
				.Disable = 0 << 9,
		},

		.DMA_Interrupts = {
				.Transfer_Complete = 1 << 4,
				.Half_Transfer_Complete = 1 << 3,
				.Transfer_Error = 1 << 2,
				.Direct_Mode_Error = 1 << 1,
				.Fifo_Error = 1 << 7,
				.Disable = 0 << 1,
		},

		.Flow_Control = {
				.DMA_Control = 0 << 5,
				.Peripheral_Control = 1 << 5,
		},

		.Transfer_Direction =
		{
			.Peripheral_to_memory = 0 << 6,
			.Memory_to_peripheral = 1 << 6,
			.Memory_to_memory = 2 << 6,
		},

		.Priority_Level =
		{
			.Low = 0 << 16,
			.Medium = 1 << 16,
			.High = 2 << 16,
			.Very_high = 3 << 16,
		},

		.Memory_Data_Size = {

				.byte = 0 << 13,
				.half_word = 1 << 13,
				.word = 2 << 13,

		},

		.Peripheral_Data_Size = {
				.byte = 0 << 11,
				.half_word = 1 << 11,
				.word = 2 << 11,
		},

		.Request = {

				.SPI3_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream0, // DMA1_Stream2
						.channel = 0,
				},

				.SPI3_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream5, // DMA1_Stream7
						.channel = 0,
				},

				.SPI2_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream3,
						.channel = 0,
				},

				.SPI2_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream4,
						.channel = 0,
				},

				.SPI1_RX = {
						.Controller = DMA2,
						.Stream = DMA2_Stream0, // DMA2_Stream2
						.channel = 3,
				},

				.SPI1_TX = {
						.Controller = DMA2,
						.Stream = DMA2_Stream3, // DMA2_Stream5
						.channel = 3,
				},

				.I2S2_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream3,
						.channel = 3,
				},

				.I2S2_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream4,
						.channel = 3,
				},

				.I2S3_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream2,
						.channel = 2,
				},

				.I2S3_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream7,
						.channel = 0,
				},

				.I2C1_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream0, // DMA1_Stream5
						.channel = 1,
				},

				.I2C1_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6, // DMA1_Stream7
						.channel = 1,
				},

				.I2C2_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream2,
						.channel = 7,
				},

				.I2C2_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream7,
						.channel = 7,
				},

				.I2C3_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream2,
						.channel = 3,
				},

				.I2C3_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream4,
						.channel = 3,
				},

				.USART1_RX = {
						.Controller = DMA2,
						.Stream = DMA2_Stream2,
						.channel = 4,
				},

				.USART1_TX = {
						.Controller = DMA2,
						.Stream = DMA2_Stream7,
						.channel = 4,
				},

				.USART2_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream5,
						.channel = 4,
				},

				.USART2_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6,
						.channel = 4,
				},

				.USART3_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream1,
						.channel = 4,
				},

				.USART3_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream3,
						.channel = 4,
				},

				.UART4_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream2,
						.channel = 4,
				},

				.UART4_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream4,
						.channel = 4,
				},

				.UART5_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream0,
						.channel = 4,
				},

				.UART5_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream7,
						.channel = 4,
				},

				.UART6_RX = {
						.Controller = DMA2,
						.Stream = DMA2_Stream1,
						.channel = 5,
				},

				.UART6_TX = {
						.Controller = DMA2,
						.Stream = DMA2_Stream6,
						.channel = 5,
				},

				.UART7_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream3,
						.channel = 5,
				},

				.UART7_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream1,
						.channel = 5,
				},

				.UART8_RX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6,
						.channel = 5,
				},

				.UART8_TX = {
						.Controller = DMA1,
						.Stream = DMA1_Stream0,
						.channel = 5,
				},

				.TIM1_UP = {
						.Controller = DMA2,
						.Stream = DMA2_Stream5,
						.channel = 6,
				},

				.TIM2_UP = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6,
						.channel = 3,
				},

				.TIM3_CH1 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream4,
						.channel = 5,
				},

				.TIM3_CH2 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream5,
						.channel = 5,
				},

				.TIM3_CH3 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6,
						.channel = 5,
				},

				.TIM3_CH4 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream2,
						.channel = 5,
				},

				.TIM4_CH1 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream0,
						.channel = 2,
				},

				.TIM4_CH2 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream3,
						.channel = 2,
				},

				.TIM4_CH3 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream7,
						.channel = 2,
				},

				.TIM4_UP = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6,
						.channel = 2,
				},

				.TIM5_CH1 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream2,
						.channel = 6,
				},

				.TIM5_CH2 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream4,
						.channel = 6,
				},

				.TIM5_CH3 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream0,
						.channel = 6,
				},

				.TIM5_UP = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6,
						.channel = 6,
				},

				.TIM6_UP = {
						.Controller = DMA1,
						.Stream = DMA1_Stream1,
						.channel = 7,
				},

				.TIM7_UP = {
						.Controller = DMA1,
						.Stream = DMA1_Stream2,
						.channel = 1,
				},

				._DAC2 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream5,
						.channel = 7,
				},

				._DAC2 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6,
						.channel = 7,
				},

				.SDIO_RXTX = {
						.Controller = DMA2,
						.Stream = DMA2_Stream3,
						.channel = 4,
				},

				._DCMI = {
						.Controller = DMA2,
						.Stream = DMA2_Stream1,
						.channel = 1,
				},

				._ADC1 = {
						.Controller = DMA2,
						.Stream = DMA2_Stream0,
						.channel = 0,
				},

				._ADC2 = {
						.Controller = DMA2,
						.Stream = DMA2_Stream2,
						.channel = 1,
				},

				._ADC3 = {
						.Controller = DMA2,
						.Stream = DMA2_Stream1,
						.channel = 2,
				},

				.TIM1_UP = {
						.Controller = DMA2,
						.Stream = DMA2_Stream5,
						.channel = 6,
				},

				.TIM1_CH1 = {
						.Controller = DMA2,
						.Stream = DMA2_Stream1,
						.channel = 6,
				},

				.TIM1_CH2 = {
						.Controller = DMA2,
						.Stream = DMA2_Stream6,
						.channel = 6,
				},

				.TIM1_CH3 = {
						.Controller = DMA2,
						.Stream = DMA2_Stream6,
						.channel = 6,
				},

				.TIM1_CH4 = {
						.Controller = DMA2,
						.Stream = DMA2_Stream4,
						.channel = 6,
				},

				.TIM1_TRIG = {
						.Controller = DMA2,
						.Stream = DMA2_Stream0,
						.channel = 6,
				},

				.TIM1_COM = {
						.Controller = DMA2,
						.Stream = DMA2_Stream0,
						.channel = 6,
				},

				.TIM8_UP = {
						.Controller = DMA2,
						.Stream = DMA2_Stream1,
						.channel = 7,
				},

				.TIM8_CH1 = {
						.Controller = DMA2,
						.Stream = DMA2_Stream2,
						.channel = 7,
				},

				.TIM8_CH2 = {
						.Controller = DMA2,
						.Stream = DMA2_Stream4,
						.channel = 7,
				},

				.TIM8_CH3 = {
						.Controller = DMA2,
						.Stream = DMA2_Stream6,
						.channel = 7,
				},

				.TIM8_CH4 = {
						.Controller = DMA2,
						.Stream = DMA2_Stream7,
						.channel = 7,
				},

				.TIM8_TRIG = {
						.Controller = DMA2,
						.Stream = DMA2_Stream1,
						.channel = 7,
				},

				.TIM8_COM = {
						.Controller = DMA2,
						.Stream = DMA2_Stream1,
						.channel = 7,
				},

				.TIM2_UP = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6,
						.channel = 3,
				},

				.TIM2_CH1 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream5,
						.channel = 3,
				},

				.TIM2_CH2 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream7,
						.channel = 3,
				},

				.TIM2_CH3 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream1,
						.channel = 3,
				},

				.TIM2_CH4 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream7,
						.channel = 3,
				},

				.TIM3_CH1 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream4,
						.channel = 5,
				},

				.TIM3_CH2 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream5,
						.channel = 5,
				},

				.TIM3_CH3 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6,
						.channel = 5,
				},

				.TIM3_CH4 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream2,
						.channel = 5,
				},

				.TIM3_UP = {
						.Controller = DMA1,
						.Stream = DMA1_Stream2,
						.channel = 5,
				},

				.TIM3_TRIG = {
						.Controller = DMA1,
						.Stream = DMA1_Stream5,
						.channel = 5,
				},

				.TIM4_CH1 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream0,
						.channel = 2,
				},

				.TIM4_CH2 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream3,
						.channel = 2,
				},

				.TIM4_CH3 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream7,
						.channel = 2,
				},

				.TIM4_UP = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6,
						.channel = 2,
				},

				.TIM5_CH1 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream2,
						.channel = 6,
				},

				.TIM5_CH2 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream4,
						.channel = 6,
				},

				.TIM5_CH3 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream0,
						.channel = 6,
				},

				.TIM5_CH4 = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6,
						.channel = 6,
				},

				.TIM5_UP = {
						.Controller = DMA1,
						.Stream = DMA1_Stream6,
						.channel = 6,
				},

				.TIM5_TRIG = {
						.Controller = DMA1,
						.Stream = DMA1_Stream3,
						.channel = 6,
				},


		},


};


#endif /* DMA_DEFS_H_ */
