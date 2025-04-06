/**
 * @file ADC.h
 * @author Kunal Salvi (kunalsalvius@gmail.com)
 * @brief  This is the driver file to be added the the application code.
 *         Functions in this driver are implemented in @ref ADC.c
 *         
 * @version 0.1
 * @date 2024-08-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/**
 * @mainpage ADC Driver Documentation
 *
 * @section intro_sec Introduction
 *
 * Welcome to the ADC (Analog-to-Digital Converter) driver documentation. This documentation covers the
 * initialization, configuration, and usage of the ADC peripheral for the STM32F407VGT6 microcontroller.
 * The driver allows for flexible setup of ADC channels, including configuration of data alignment,
 * conversion modes, and external triggers.
 *
 * @section features_sec Features
 *
 * - Support for configuring up to 16 ADC channels.
 * - Customizable data alignment (Left/Right).
 * - Single and continuous conversion modes.
 * - External trigger support for starting ADC conversions.
 * - Analog watchdog feature for monitoring ADC channels.
 * - Integrated DMA support for efficient data transfer.
 *
 * @section usage_sec Usage
 *
 * To use the ADC driver in your application:
 *
 * 1. **Include the Header**: Make sure to include `ADC.h` in your project.
 * 2. **Configure ADC Settings**: Use the `ADC_Config` structure to set up the ADC, including channels,
 *    data alignment, conversion mode, and triggers.
 * 3. **Initialize the ADC**: Call `ADC_Init()` with the configuration structure to initialize the ADC.
 * 4. **Enable the ADC**: Use `ADC_Enable()` to power on the ADC and introduce a stabilization delay.
 * 5. **Start Conversion**: Use `ADC_Start()` or `ADC_Start_Capture()` to begin the ADC conversion process.
 *
 * @section examples_sec Example Code
 *
 * Here is a simple example of configuring and starting an ADC conversion:
 *
 * @code
 * ADC_Config adcConfig;
 * adcConfig.Port = ADC1;
 * adcConfig.Data_Alignment = ADC_Configuration.Data_Alignment.Right_Justified;
 * adcConfig.Conversion_Mode = ADC_Configuration.Conversion_Mode.Continuous;
 * adcConfig.Channel_0.Enable = true;
 * adcConfig.Channel_0.Sequence_Number = 1;
 * adcConfig.Channel_0.Sample_Time = ADC_Configuration.Channel.Sample_Time._15_Cycles;
 *
 * if (ADC_Init(&adcConfig) == 1) {
 *     ADC_Enable(&adcConfig);
 *     ADC_Start(&adcConfig);
 * }
 * @endcode
 *
 * @section files_sec Files
 *
 * - **ADC.h**: This file contains the declarations for the ADC driver, including the `ADC_Config` structure
 *   and various functions for initializing and controlling the ADC.
 * - **ADC.c**: This file contains the implementation of the functions declared in `ADC.h`.
 * - **ADC_Defs.h**: Contains additional definitions and structures used by the ADC driver.
 *
 * @section author_sec Author
 *
 * This driver was developed by Kunal Salvi. For any questions or issues, please contact kunalsalvius@gmail.com.
 */


#ifndef ADC_H_
#define ADC_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "DMA/DMA.h"
#include "ADC_Defs.h"


typedef struct ADC_Pin{
	bool Enable;
	uint8_t Sequence_Number;
	uint8_t Sample_Time;
}ADC_Pin;


/** @struct ADC_Config
 *  @brief  This is the configuration structure to be used to make an instance of ADC.
 */

typedef struct ADC_Config{

/**
 * @brief 	Sets up the ADC hardware block to be used. 
 *        	STM32F407VGT6 has 3 ADC blocks and can be set using
 * 			@ref ADC_Configuration.Port
 * 
 */
	ADC_TypeDef *Port; 


/**
 * @brief 	Used to setup Data Alignment of the converted data. 
 *        	Data can be converted into Right or Left Alignment 
 * 			@ref ADC_Configuration.Data_Alignment
 * 
 */
	uint8_t Data_Alignment;

/**
 * @brief 	Used to setup Conversion Mode of the ADC. 
 *        	ADC conversions can Single or Continuous.
 * 			When External Trigger is enabled, make sure conversion mode
 * 			is set to Single  
 *          @ref ADC_Configuration.Conversion_Mode
 * 
 */
	uint8_t Conversion_Mode;


/**
 * @brief Used to setup Channel Type of the ADC.
 * 
 */
	uint8_t Channel_Type;

	struct External_Trigger
	{
		bool Enable;
		uint8_t Trigger_Event;
		uint8_t Sampling_Frequency;
	}External_Trigger;

	ADC_Pin Channel_0;
	ADC_Pin Channel_1;
	ADC_Pin Channel_2;
	ADC_Pin Channel_3;
	ADC_Pin Channel_4;
	ADC_Pin Channel_5;
	ADC_Pin Channel_6;
	ADC_Pin Channel_7;
	ADC_Pin Channel_8;
	ADC_Pin Channel_9;
	ADC_Pin Channel_10;
	ADC_Pin Channel_11;
	ADC_Pin Channel_12;
	ADC_Pin Channel_13;
	ADC_Pin Channel_14;
	ADC_Pin Channel_15;

	uint8_t Resolution;

	struct Watchdog_Analog
	{
		bool Enable;
		uint8_t Channel_Type;
		bool Channel_Scan;
		uint8_t Channel;
		uint16_t Higher_Threshold;
		uint16_t Lower_Threshold;
	}Watchdog_Analog;
}ADC_Config;

/**
 * @brief Initializes the ADC with the provided configuration.
 *
 * This function initializes the ADC peripheral based on the settings provided
 * in the `ADC_Config` structure. It configures the ADC port, resolution,
 * conversion mode, data alignment, and external trigger if enabled. It also
 * sets up the DMA for ADC data transfer.
 *
 * @param[in] config Pointer to the ADC configuration structure.
 *
 * @return int8_t Returns 1 on successful initialization, or -1 if an error occurs.
 */
int8_t ADC_Init(ADC_Config *config);

/**
 * @brief Enables the ADC and introduces a delay.
 *
 * This function enables the ADC by setting the ADON bit in the control register.
 * After enabling the ADC, it introduces a delay to allow the ADC to stabilize.
 *
 * @param[in] config Pointer to the ADC configuration structure.
 *
 * @return int8_t Returns 1 on successful enabling of the ADC.
 */
int8_t ADC_Enable(ADC_Config *config);

/**
 * @brief Starts the ADC conversion based on the specified channel type.
 *
 * This function starts the ADC conversion process for either regular or injected channels.
 * It clears the status register, then initiates the conversion by setting the appropriate
 * start bit in the control register. If the channel type is invalid, it returns an error code.
 *
 * @param[in] config Pointer to the ADC configuration structure.
 *
 * @return int8_t Returns 1 on successful start of the ADC conversion, or -1 if the channel type is invalid.
 */
int8_t ADC_Start(ADC_Config *config);

/**
 * @brief Starts ADC capture and initializes DMA.
 *
 * This function initiates the ADC capture process. If an overrun condition is detected,
 * it reinitializes the ADC by toggling the ADON bit. It then sets up the DMA to transfer
 * the ADC data to a specified buffer.
 *
 * @param[in] config Pointer to the ADC configuration structure.
 * @param[out] buffer Pointer to the buffer where ADC data will be stored.
 *
 * @return int8_t Returns 1 on successful start of ADC capture.
 */
int8_t ADC_Start_Capture(ADC_Config *config, uint16_t *buffer);

#endif /* ADC_H_ */
