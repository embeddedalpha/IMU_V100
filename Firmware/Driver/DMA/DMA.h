/**
 * @mainpage DMA Driver Documentation
 *
 * @section intro_sec Introduction
 *
 * This documentation provides an overview and detailed explanation of the Direct Memory Access (DMA) driver.
 * The DMA driver allows for efficient, high-speed data transfers between peripherals and memory without CPU intervention,
 * making it an essential tool for performance-critical applications.
 *
 * @section features_sec Features
 *
 * - **Memory-to-Memory Transfer**: Supports direct data transfers between memory regions.
 * - **Peripheral-to-Memory / Memory-to-Peripheral Transfers**: Facilitates data exchange between peripherals and memory.
 * - **Flow Control**: Configurable flow control to use DMA or peripheral as the flow controller.
 * - **Circular Mode**: Enables continuous data transfers in a circular buffer.
 * - **Interrupt Handling**: Supports transfer complete, half transfer complete, transfer error, and FIFO error interrupts.
 * - **Priority Levels**: Configurable priority levels for managing multiple DMA streams.
 * - **Configurable Data Sizes**: Supports byte, half-word, and word data sizes for both memory and peripherals.
 *
 * @section config_sec Configuration
 *
 * The DMA driver is configured using the `DMA_Config` structure, which contains the following parameters:
 *
 * - `DMA_Request Request`: Defines the specific DMA stream and channel to use.
 * - `uint32_t flow_control`: Specifies whether DMA or peripheral controls the flow.
 * - `uint32_t transfer_direction`: Defines the direction of data transfer (e.g., memory-to-peripheral).
 * - `uint32_t priority_level`: Sets the priority of the DMA stream.
 * - `uint32_t circular_mode`: Enables or disables circular mode for the DMA stream.
 * - `uint32_t interrupts`: Specifies which DMA interrupts to enable.
 * - `uint16_t memory_pointer_increment`: Configures memory pointer increment mode.
 * - `uint16_t peripheral_pointer_increment`: Configures peripheral pointer increment mode.
 * - `uint32_t peripheral_data_size`: Sets the data size for the peripheral (byte, half-word, or word).
 * - `uint32_t memory_data_size`: Sets the data size for memory (byte, half-word, or word).
 * - `uint32_t peripheral_address`: The address of the peripheral.
 * - `uint32_t memory_address`: The address of the memory.
 * - `uint16_t buffer_length`: The number of data items to transfer.
 *
 * @section functions_sec Functions
 *
 * The DMA driver provides the following functions:
 *
 * - `void DMA_Clock_Enable(DMA_Config *config)`: Enables the clock for the specified DMA controller.
 * - `void DMA_Clock_Disable(DMA_Config *config)`: Disables the clock for the specified DMA controller.
 * - `void DMA_Reset(DMA_Config *config)`: Resets the specified DMA controller.
 * - `void DMA_Reset_Flags(DMA_Flags_Typedef flag)`: Resets all DMA flags.
 * - `int8_t DMA_Init(DMA_Config *config)`: Initializes the DMA with the specified configuration.
 * - `void DMA_Set_Target(DMA_Config *config)`: Configures the target memory and peripheral for DMA transfers.
 * - `void DMA_Set_Trigger(DMA_Config *config)`: Sets up and enables the DMA stream for data transfer.
 * - `void DMA_Memory_To_Memory_Transfer(uint32_t *source, uint8_t source_data_size, uint8_t dest_data_size, uint32_t *destination, bool source_increment, bool destination_increment, uint16_t length)`: Performs a memory-to-memory data transfer using DMA.
 *
 * @section usage_sec Usage
 *
 * To use the DMA driver in your application, follow these steps:
 *
 * 1. **Configure the DMA settings**: Initialize a `DMA_Config` structure with your desired settings.
 * 2. **Initialize the DMA**: Call `DMA_Init` with the configuration structure.
 * 3. **Set up data transfer**: Use `DMA_Set_Target` and `DMA_Set_Trigger` to configure the transfer settings.
 * 4. **Start the transfer**: If using memory-to-memory transfer, call `DMA_Memory_To_Memory_Transfer`.
 *
 * @section example_sec Example
 *
 * ```c
 * DMA_Config dma_config;
 * dma_config.Request = DMA_Configuration.Request.SPI1_RX;
 * dma_config.flow_control = DMA_Configuration.Flow_Control.DMA_Control;
 * dma_config.transfer_direction = DMA_Configuration.Transfer_Direction.Peripheral_to_memory;
 * dma_config.priority_level = DMA_Configuration.Priority_Level.High;
 * dma_config.circular_mode = DMA_Configuration.Circular_Mode.Disable;
 * dma_config.interrupts = DMA_Configuration.DMA_Interrupts.Transfer_Complete;
 * dma_config.memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;
 * dma_config.peripheral_pointer_increment = DMA_Configuration.Peripheral_Pointer_Increment.Disable;
 * dma_config.peripheral_data_size = DMA_Configuration.Peripheral_Data_Size.half_word;
 * dma_config.memory_data_size = DMA_Configuration.Memory_Data_Size.half_word;
 * dma_config.peripheral_address = (uint32_t)&(SPI1->DR);
 * dma_config.memory_address = (uint32_t)buffer;
 * dma_config.buffer_length = BUFFER_SIZE;
 *
 * DMA_Init(&dma_config);
 * DMA_Set_Target(&dma_config);
 * DMA_Set_Trigger(&dma_config);
 * ```
 *
 * @section notes_sec Notes
 * - Ensure that the appropriate DMA streams and channels are enabled before starting a transfer.
 * - Pay attention to memory alignment when configuring data sizes.
 *
 * @section license_sec License
 *
 * This software is provided "as-is," without any express or implied warranty. In no event shall the authors be held liable for any damages arising from the use of this software.
 *
 */


/**
 * @file DMA.h
 * @author Kunal Salvi
 * @brief Header file for the DMA driver.
 *
 * This file contains the function prototypes and data structures for configuring
 * and using the DMA peripheral. It supports functions for initializing the DMA,
 * setting up memory-to-memory transfers, and managing DMA flags and interrupts.
 *
 * @version 1.0
 * @date 2024-08-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef DMA_H_
#define DMA_H_

#include "main.h"
#include "DMA_Defs.h"

/** @addtogroup DMA_Flags
 * @{
 */
extern volatile  DMA_Flags_Typedef I2S2_RX_DMA_Flag;
extern volatile  DMA_Flags_Typedef I2S2_TX_DMA_Flag;
extern volatile  DMA_Flags_Typedef I2S3_RX_DMA_Flag;
extern volatile  DMA_Flags_Typedef I2S3_TX_DMA_Flag;
extern volatile  DMA_Flags_Typedef I2C1_RX_DMA_Flag;
extern volatile  DMA_Flags_Typedef I2C1_TX_DMA_Flag;
extern volatile  DMA_Flags_Typedef I2C2_RX_DMA_Flag;
extern volatile  DMA_Flags_Typedef I2C2_TX_DMA_Flag;
extern volatile  DMA_Flags_Typedef I2C3_RX_DMA_Flag;
extern volatile  DMA_Flags_Typedef I2C3_TX_DMA_Flag;
extern volatile  DMA_Flags_Typedef SPI1_RX_DMA_Flag;
extern volatile  DMA_Flags_Typedef SPI2_RX_DMA_Flag;
extern volatile  DMA_Flags_Typedef SPI3_RX_DMA_Flag;
extern volatile  DMA_Flags_Typedef SPI1_TX_DMA_Flag;
extern volatile  DMA_Flags_Typedef SPI2_TX_DMA_Flag;
extern volatile  DMA_Flags_Typedef SPI3_TX_DMA_Flag;

extern volatile  DMA_Flags_Typedef TIM1_UP_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM1_CH1_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM1_CH2_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM1_CH3_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM1_CH4_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM1_TRIG_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM1_COM_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM8_UP_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM8_CH1_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM8_CH2_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM8_CH3_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM8_CH4_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM8_TRIG_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM8_COM_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM2_UP_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM2_CH1_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM2_CH2_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM2_CH3_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM2_CH4_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM3_CH1_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM3_CH2_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM3_CH3_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM3_CH4_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM3_UP_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM3_TRIG_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM4_CH1_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM4_CH2_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM4_CH3_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM4_UP_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM5_CH1_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM5_CH2_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM5_CH3_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM5_CH4_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM5_UP_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM5_TRIG_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM6_UP_DMA_Flag;
extern volatile  DMA_Flags_Typedef TIM7_UP_DMA_Flag;
extern volatile  DMA_Flags_Typedef DAC1_DMA_Flag;
extern volatile  DMA_Flags_Typedef DAC2_DMA_Flag;
extern volatile  DMA_Flags_Typedef SDIO_RXTX_DMA_Flag;
extern volatile  DMA_Flags_Typedef DCMI_DMA_Flag;
extern volatile  DMA_Flags_Typedef ADC1_DMA_Flag;
extern volatile  DMA_Flags_Typedef ADC2_DMA_Flag;
extern volatile  DMA_Flags_Typedef ADC3_DMA_Flag;

extern volatile  DMA_Flags_Typedef DMA1_Stream0_Flag;
extern volatile  DMA_Flags_Typedef DMA1_Stream1_Flag;
extern volatile  DMA_Flags_Typedef DMA1_Stream2_Flag;
extern volatile  DMA_Flags_Typedef DMA1_Stream3_Flag;
extern volatile  DMA_Flags_Typedef DMA1_Stream4_Flag;
extern volatile  DMA_Flags_Typedef DMA1_Stream5_Flag;
extern volatile  DMA_Flags_Typedef DMA1_Stream6_Flag;
extern volatile  DMA_Flags_Typedef DMA1_Stream7_Flag;

extern volatile  DMA_Flags_Typedef DMA2_Stream0_Flag;
extern volatile  DMA_Flags_Typedef DMA2_Stream1_Flag;
extern volatile  DMA_Flags_Typedef DMA2_Stream2_Flag;
extern volatile  DMA_Flags_Typedef DMA2_Stream3_Flag;
extern volatile  DMA_Flags_Typedef DMA2_Stream4_Flag;
extern volatile  DMA_Flags_Typedef DMA2_Stream5_Flag;
extern volatile  DMA_Flags_Typedef DMA2_Stream6_Flag;
extern volatile  DMA_Flags_Typedef DMA2_Stream7_Flag;
/** @} */

/**
 * @brief DMA configuration structure.
 *
 * This structure contains the configuration parameters for the DMA peripheral,
 * including settings for flow control, transfer direction, priority level, circular mode,
 * interrupts, memory and peripheral data sizes, and addresses.
 */
typedef struct DMA_Config
{
    DMA_Request Request;                /**< DMA request settings */
    uint32_t flow_control;              /**< Flow control mode (DMA or peripheral) */
    uint32_t transfer_direction;        /**< Transfer direction (memory-to-peripheral, peripheral-to-memory, etc.) */
    uint32_t priority_level;            /**< Priority level (low, medium, high, very high) */
    uint32_t circular_mode;             /**< Circular mode enable/disable */
    uint32_t interrupts;                /**< Interrupts settings */
    uint16_t memory_pointer_increment;  /**< Memory pointer increment mode */
    uint16_t peripheral_pointer_increment; /**< Peripheral pointer increment mode */
    uint32_t peripheral_data_size;      /**< Peripheral data size (byte, half-word, word) */
    uint32_t memory_data_size;          /**< Memory data size (byte, half-word, word) */

    uint32_t peripheral_address;        /**< Peripheral base address */
    uint32_t memory_address;            /**< Memory base address */
    uint16_t buffer_length;             /**< Number of data items to transfer */
    uint32_t double_buffer_mode;		/**< Enables Double Buffer Mode> */

	struct __DMA_Interrupts__{
		void (*FIFO_Error_ISR)(void);
		void (*Direct_Mode_Error_ISR)(void);
		void (*Transfer_Error_ISR)(void);
		void (*Half_Transfer_Complete_ISR)(void);
		void (*Full_Transfer_Commplete_ISR)(void);
		void (*Double_Buffer_Mode_Target_1_ISR)(void);
		void (*Double_Buffer_Mode_Target_2_ISR)(void);
	}ISR_Routines;

} DMA_Config;

/**
 * @brief Enables the clock for the specified DMA controller.
 *
 * @param[in] config Pointer to the DMA_Config structure containing the DMA controller settings.
 */
void DMA_Clock_Enable(DMA_Config *config);

/**
 * @brief Disables the clock for the specified DMA controller.
 *
 * @param[in] config Pointer to the DMA_Config structure containing the DMA controller settings.
 */
void DMA_Clock_Disable(DMA_Config *config);

/**
 * @brief Resets the specified DMA controller.
 *
 * @param[in] config Pointer to the DMA_Config structure containing the DMA controller settings.
 */
void DMA_Reset(DMA_Config *config);

/**
 * @brief Resets all DMA flags in the provided DMA_Flags_Typedef structure.
 *
 * @param flag The DMA_Flags_Typedef structure whose flags are to be reset.
 */
void DMA_Reset_Flags(volatile DMA_Flags_Typedef *flag);

/**
 * @brief Initializes the DMA with the specified configuration.
 *
 * @param[in] config Pointer to the DMA_Config structure containing the configuration parameters.
 *
 * @return int8_t Returns 1 on successful initialization, or -1 if an error occurs.
 */
int8_t DMA_Init(DMA_Config *config);

/**
 * @brief Configures the target memory and peripheral for DMA transfers.
 *
 * @param[in] config Pointer to the DMA_Config structure containing the target configuration.
 */
void DMA_Set_Target(DMA_Config *config);

/**
 * @brief Sets up and enables the DMA stream for data transfer.
 *
 * @param[in] config Pointer to the DMA_Config structure containing the configuration settings.
 */
void DMA_Set_Trigger(DMA_Config *config);

/**
 * @brief Performs a memory-to-memory data transfer using DMA.
 *
 * @param[in] source Pointer to the source memory location.
 * @param[in] source_data_size Size of the data at the source (8, 16, or 32 bits).
 * @param[in] dest_data_size Size of the data at the destination (8, 16, or 32 bits).
 * @param[in] destination Pointer to the destination memory location.
 * @param[in] source_increment If true, the source address will be incremented after each transfer.
 * @param[in] destination_increment If true, the destination address will be incremented after each transfer.
 * @param[in] length Number of data items to transfer.
 */
void DMA_Memory_To_Memory_Transfer(uint32_t *source,
                          uint8_t source_data_size, uint8_t dest_data_size,
                          uint32_t *destination, bool source_increment,
                          bool destination_increment, uint16_t length);

#endif /* DMA_H_ */
