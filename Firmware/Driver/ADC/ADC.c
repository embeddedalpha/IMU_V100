/**
 * @file ADC.c
 * @author Kunal Salvi (kunalsalvius@gmail.com)
 * @brief This is the part driver file that has the implementation of funcitons
 *        in the ADC.h file. 
 *        
 * @version 0.1
 * @date 2024-08-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "ADC.h"

/**
 * @brief Global DMA configuration structure for ADC
 */
DMA_Config xADC;

/**
 * @brief Temporary variable to store pin value
 */
int8_t pin_temp = 0;

//void ADC_IRQHandler(void)
//{
//	if(ADC1 -> SR & ADC_SR_OVR)
//	{
//		ADC1 -> SR &= ~(ADC_SR_OVR | ADC_SR_EOC);
//		ADC1 -> CR2 |= ADC_CR2_ADON ;
//		ADC1 -> CR2 |= ADC_CR2_SWSTART;
//		DMA_Set_Target(&xADC);
//		DMA_Set_Trigger(&xADC);
//	}
//}

/**
 * @brief Initializes the external timer trigger for the ADC.
 *
 * This function sets up the external timer trigger for the ADC based on the
 * provided configuration. It enables the corresponding timer and configures
 * its registers to trigger the ADC conversion. The function supports multiple
 * trigger events, including various channels and timers.
 *
 * @param[in] config Pointer to the ADC configuration structure.
 */
static void ADC_Timer_External_Trigger_Init(ADC_Config *config)
{
	if(config->External_Trigger.Trigger_Event == ADC_Configuration.Regular_External_Trigger_Event.Timer_1_CC1)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;
		TIM1 -> CCR1 = 100/2 -1;
		TIM1->PSC = 16800;
		TIM1->ARR = 100-1;
		TIM1 -> CR2 |= TIM_CR2_MMS_1 | TIM_CR2_MMS_0;
		TIM1 -> CCER |= TIM_CCER_CC1E;
		TIM1->CR1 |= TIM_CR1_CEN ;
	}
	else if(config->External_Trigger.Trigger_Event == ADC_Configuration.Regular_External_Trigger_Event.Timer_1_CC2)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;
		TIM1 -> EGR |= TIM_EGR_CC2G;
		TIM1->DIER |=  TIM_DIER_CC2IE;
		//	NVIC_EnableIRQ(TIM1_CC_IRQn);
		//	NVIC_SetPriority(TIM1_CC_IRQn,1);
		TIM1->PSC = 10000-1;
		TIM1->ARR = 8400-1;
		TIM1->CR1 |= TIM_CR1_CEN;
	}
	else if(config->External_Trigger.Trigger_Event == ADC_Configuration.Regular_External_Trigger_Event.Timer_1_CC3)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;
		TIM1 -> EGR |= TIM_EGR_CC3G;
		TIM1->DIER |=  TIM_DIER_CC3IE;
		//	NVIC_EnableIRQ(TIM1_CC_IRQn);
		//	NVIC_SetPriority(TIM1_CC_IRQn,1);
		TIM1->PSC = 10000-1;
		TIM1->ARR = 8400-1;
		TIM1->CR1 |= TIM_CR1_CEN;
	}
	else if(config->External_Trigger.Trigger_Event == ADC_Configuration.Injected_External_Trigger_Event.Timer_1_CC4)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;
		TIM1 -> EGR |= TIM_EGR_CC4G;
		TIM1->DIER |=  TIM_DIER_CC4IE;
		//	NVIC_EnableIRQ(TIM1_CC_IRQn);
		//	NVIC_SetPriority(TIM1_CC_IRQn,1);
		TIM1->PSC = 10000-1;
		TIM1->ARR = 8400-1;
		TIM1->CR1 |= TIM_CR1_CEN;
	}
	/***************************************************************************************************************/
	else if(config->External_Trigger.Trigger_Event == ADC_Configuration.Injected_External_Trigger_Event.Timer_2_CC1)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
		TIM2 -> EGR |= TIM_EGR_CC1G;
		TIM2->DIER |=  TIM_DIER_CC1IE;
		//	NVIC_EnableIRQ(TIM1_CC_IRQn);
		//	NVIC_SetPriority(TIM1_CC_IRQn,1);
		TIM2->PSC = 10000-1;
		TIM2->ARR = 8400-1;
		TIM2->CR1 |= TIM_CR1_CEN;
	}
	else if(config->External_Trigger.Trigger_Event == ADC_Configuration.Regular_External_Trigger_Event.Timer_2_CC2)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
		TIM2 -> EGR |= TIM_EGR_CC2G | TIM_EGR_UG;
		TIM2 -> CCR1 = 1000/2 -1;
		TIM2->PSC = 8400;
		TIM2->ARR = 1000-1;
		TIM2 -> CR2 |=  TIM_CR2_MMS_1;
		TIM2 -> CCER |= TIM_CCER_CC2E;
		TIM2->CR1 |= TIM_CR1_CEN ;
	}
	else if(config->External_Trigger.Trigger_Event == ADC_Configuration.Regular_External_Trigger_Event.Timer_2_CC3)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
		TIM2 -> EGR |= TIM_EGR_CC3G;
		TIM2->DIER |=  TIM_DIER_CC3IE;
		// NVIC_EnableIRQ(TIM1_CC_IRQn);
		//	NVIC_SetPriority(TIM1_CC_IRQn,1);
		TIM2->PSC = 10000-1;
		TIM2->ARR = 8400-1;
		TIM2->CR1 |= TIM_CR1_CEN;
	}
	else if(config->External_Trigger.Trigger_Event == ADC_Configuration.Regular_External_Trigger_Event.Timer_2_CC4)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
		TIM2 -> EGR |= TIM_EGR_CC3G;
		TIM2->DIER |=  TIM_DIER_CC3IE;
		// NVIC_EnableIRQ(TIM1_CC_IRQn);
		//	NVIC_SetPriority(TIM1_CC_IRQn,1);
		TIM2->PSC = 10000-1;
		TIM2->ARR = 8400-1;
		TIM2->CR1 |= TIM_CR1_CEN;
	}
	else if(config->External_Trigger.Trigger_Event == ADC_Configuration.Regular_External_Trigger_Event.Timer_2_TRGO)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;

		TIM2->DIER |=  TIM_DIER_UIE;
		// NVIC_EnableIRQ(TIM1_CC_IRQn);
		//	NVIC_SetPriority(TIM1_CC_IRQn,1);
		TIM2 -> CR2 |=  TIM_CR2_MMS_1;
		TIM2->PSC = 1000-1;
		TIM2->ARR = 16800-1;
		TIM2->CR1 |= TIM_CR1_CEN;
		TIM2 -> EGR |= TIM_EGR_UG;
	}
	/***************************************************************************************************************/
	else if(config->External_Trigger.Trigger_Event == ADC_Configuration.Regular_External_Trigger_Event.Timer_3_CC1)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
		TIM3 -> EGR |= TIM_EGR_CC1G;
		TIM3->DIER |=  TIM_DIER_CC1IE;
		//	NVIC_EnableIRQ(TIM1_CC_IRQn);
		//	NVIC_SetPriority(TIM1_CC_IRQn,1);
		TIM3->PSC = 10000-1;
		TIM3->ARR = 8400-1;
		TIM3->CR1 |= TIM_CR1_CEN;
	}
	else if(config->External_Trigger.Trigger_Event == ADC_Configuration.Injected_External_Trigger_Event.Timer_3_CC2)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
		TIM3 -> EGR |= TIM_EGR_CC2G;
		TIM3->DIER |=  TIM_DIER_CC2IE;
		//	NVIC_EnableIRQ(TIM1_CC_IRQn);
		//	NVIC_SetPriority(TIM1_CC_IRQn,1);
		TIM3->PSC = 10000-1;
		TIM3->ARR = 8400-1;
		TIM3->CR1 |= TIM_CR1_CEN;
	}
	else if(config->External_Trigger.Trigger_Event == ADC_Configuration.Injected_External_Trigger_Event.Timer_3_CC4)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
		TIM3 -> EGR |= TIM_EGR_CC3G;
		TIM3->DIER |=  TIM_DIER_CC3IE;
		// NVIC_EnableIRQ(TIM1_CC_IRQn);
		//	NVIC_SetPriority(TIM1_CC_IRQn,1);
		TIM3->PSC = 10000-1;
		TIM3->ARR = 8400-1;
		TIM3->CR1 |= TIM_CR1_CEN;
	}
	/***************************************************************************************************************/
}

/**
 * @brief Configures the sampling time for each enabled ADC channel.
 *
 * This function sets the sampling time for each ADC channel that is enabled in the
 * provided `ADC_Config` structure. The sampling time is configured in the
 * corresponding sample time register (SMPR1 or SMPR2). The function also counts
 * the number of channels that are enabled and returns this count.
 *
 * @param[in] config Pointer to the ADC configuration structure.
 *
 * @return int8_t Returns the number of enabled channels after configuration.
 */
static int8_t ADC_Sampling_Config(ADC_Config *config)
{
    uint8_t conversion_Counter = 0;

    // Configure sampling time for Channel 0 if enabled
    if(config->Channel_0.Enable == ENABLE)
    {
        config->Port->SMPR2 |= config->Channel_0.Sample_Time << ADC_SMPR2_SMP0_Pos;
        conversion_Counter += 1;
    }

    // Configure sampling time for Channel 1 if enabled
    if(config->Channel_1.Enable == ENABLE)
    {
        config->Port->SMPR2 |= config->Channel_1.Sample_Time << ADC_SMPR2_SMP1_Pos;
        conversion_Counter += 1;
    }

    // Configure sampling time for Channel 2 if enabled
    if(config->Channel_2.Enable == ENABLE)
    {
        config->Port->SMPR2 |= config->Channel_2.Sample_Time << ADC_SMPR2_SMP2_Pos;
        conversion_Counter += 1;
    }

    // Configure sampling time for Channel 3 if enabled
    if(config->Channel_3.Enable == ENABLE)
    {
        config->Port->SMPR2 |= config->Channel_3.Sample_Time << ADC_SMPR2_SMP3_Pos;
        conversion_Counter += 1;
    }

    // Configure sampling time for Channel 4 if enabled
    if(config->Channel_4.Enable == ENABLE)
    {
        config->Port->SMPR2 |= config->Channel_4.Sample_Time << ADC_SMPR2_SMP4_Pos;
        conversion_Counter += 1;
    }

    // Configure sampling time for Channel 5 if enabled
    if(config->Channel_5.Enable == ENABLE)
    {
        config->Port->SMPR2 |= config->Channel_5.Sample_Time << ADC_SMPR2_SMP5_Pos;
        conversion_Counter += 1;
    }

    // Configure sampling time for Channel 6 if enabled
    if(config->Channel_6.Enable == ENABLE)
    {
        config->Port->SMPR2 |= config->Channel_6.Sample_Time << ADC_SMPR2_SMP6_Pos;
        conversion_Counter += 1;
    }

    // Configure sampling time for Channel 7 if enabled
    if(config->Channel_7.Enable == ENABLE)
    {
        config->Port->SMPR2 |= config->Channel_7.Sample_Time << ADC_SMPR2_SMP7_Pos;
        conversion_Counter += 1;
    }

    // Configure sampling time for Channel 8 if enabled
    if(config->Channel_8.Enable == ENABLE)
    {
        config->Port->SMPR2 |= config->Channel_8.Sample_Time << ADC_SMPR2_SMP8_Pos;
        conversion_Counter += 1;
    }

    // Configure sampling time for Channel 9 if enabled
    if(config->Channel_9.Enable == ENABLE)
    {
        config->Port->SMPR1 |= config->Channel_9.Sample_Time << ADC_SMPR2_SMP9_Pos;
        conversion_Counter += 1;
    }

    // Configure sampling time for Channel 10 if enabled
    if(config->Channel_10.Enable == ENABLE)
    {
        config->Port->SMPR1 |= config->Channel_10.Sample_Time << ADC_SMPR1_SMP10_Pos;
        conversion_Counter += 1;
    }

    // Configure sampling time for Channel 11 if enabled
    if(config->Channel_11.Enable == ENABLE)
    {
        config->Port->SMPR1 |= config->Channel_11.Sample_Time << ADC_SMPR1_SMP11_Pos;
        conversion_Counter += 1;
    }

    /**************************************************************************************************************/

    // Configure sampling time for Channel 12 if enabled
    if(config->Channel_12.Enable == ENABLE)
    {
        config->Port->SMPR1 |= config->Channel_12.Sample_Time << ADC_SMPR1_SMP12_Pos;
        conversion_Counter += 1;
    }

    /**************************************************************************************************************/

    // Configure sampling time for Channel 13 if enabled
    if(config->Channel_13.Enable == ENABLE)
    {
        config->Port->SMPR1 |= config->Channel_13.Sample_Time << ADC_SMPR1_SMP13_Pos;
        conversion_Counter += 1;
    }

    /**************************************************************************************************************/

    // Configure sampling time for Channel 14 if enabled
    if(config->Channel_14.Enable == ENABLE)
    {
        config->Port->SMPR1 |= config->Channel_14.Sample_Time << ADC_SMPR1_SMP14_Pos;
        conversion_Counter += 1;
    }

    /**************************************************************************************************************/

    // Configure sampling time for Channel 15 if enabled
    if(config->Channel_15.Enable == ENABLE)
    {
        config->Port->SMPR1 |= config->Channel_15.Sample_Time << ADC_SMPR1_SMP15_Pos;
        conversion_Counter += 1;
    }

    // Return the number of configured channels
    return conversion_Counter;
}


/**
 * @brief Initializes the GPIO pins for ADC channels.
 *
 * This function configures the GPIO pins associated with the ADC channels
 * to operate in analog mode. It checks each channel in the `ADC_Config` structure
 * and, if enabled, initializes the corresponding GPIO pin with the appropriate
 * settings.
 *
 * @param[in] config Pointer to the ADC configuration structure.
 *
 * @return int8_t Returns 1 on successful initialization of all enabled channels.
 */
static int8_t ADC_Pin_Init(ADC_Config *config)
{
    // Initialize GPIO pin for Channel 0 if enabled
    if (config->Channel_0.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOA, 0, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    // Initialize GPIO pin for Channel 1 if enabled
    if (config->Channel_1.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOA, 1, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    // Initialize GPIO pin for Channel 2 if enabled
    if (config->Channel_2.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOA, 2, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    // Initialize GPIO pin for Channel 3 if enabled
    if (config->Channel_3.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOA, 3, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    // Initialize GPIO pin for Channel 4 if enabled
    if (config->Channel_4.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOA, 4, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    // Initialize GPIO pin for Channel 5 if enabled
    if (config->Channel_5.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOA, 5, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    // Initialize GPIO pin for Channel 6 if enabled
    if (config->Channel_6.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOA, 6, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    // Initialize GPIO pin for Channel 7 if enabled
    if (config->Channel_7.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOA, 7, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    // Initialize GPIO pin for Channel 8 if enabled
    if (config->Channel_8.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOB, 0, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    // Initialize GPIO pin for Channel 9 if enabled
    if (config->Channel_9.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOB, 1, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    // Initialize GPIO pin for Channel 10 if enabled
    if (config->Channel_10.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOC, 0, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    // Initialize GPIO pin for Channel 11 if enabled
    if (config->Channel_11.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOC, 1, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    /**************************************************************************************************************/

    // Initialize GPIO pin for Channel 12 if enabled
    if (config->Channel_12.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOC, 2, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    /**************************************************************************************************************/

    // Initialize GPIO pin for Channel 13 if enabled
    if (config->Channel_13.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOC, 3, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    /**************************************************************************************************************/

    // Initialize GPIO pin for Channel 14 if enabled
    if (config->Channel_14.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOC, 4, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    /**************************************************************************************************************/

    // Initialize GPIO pin for Channel 15 if enabled
    if (config->Channel_15.Enable == ENABLE)
    {
        GPIO_Pin_Init(GPIOC, 5, GPIO_Configuration.Mode.Analog,
                      GPIO_Configuration.Output_Type.None,
                      GPIO_Configuration.Speed.None,
                      GPIO_Configuration.Pull.None,
                      GPIO_Configuration.Alternate_Functions.Analog);
    }

    // Return success
    return 1;
}



/**
 * @brief Configures the ADC conversion sequence based on enabled channels.
 *
 * This function sets up the ADC conversion sequence by configuring the sequence
 * registers (SQR1, SQR2, SQR3) based on the channels that are enabled in the
 * provided `ADC_Config` structure. Each channel is assigned a specific sequence
 * number within the ADC conversion sequence.
 *
 * @param[in] config Pointer to the ADC configuration structure.
 *
 * @return int8_t Returns 1 on successful configuration of the sequence.
 */
static int8_t ADC_Sequence_Config(ADC_Config *config)
{
    // Configure sequence for Channel 0
    if(config->Channel_0.Enable == ENABLE)
    {
        config->Port->SQR3 |= config->Channel_0.Sequence_Number << ADC_SQR3_SQ1_Pos;
    }

    // Configure sequence for Channel 1
    if(config->Channel_1.Enable == ENABLE)
    {
        config->Port->SQR3 |= config->Channel_1.Sequence_Number << ADC_SQR3_SQ2_Pos;
    }

    // Configure sequence for Channel 2
    if(config->Channel_2.Enable == ENABLE)
    {
        config->Port->SQR3 |= config->Channel_2.Sequence_Number << ADC_SQR3_SQ3_Pos;
    }

    // Configure sequence for Channel 3
    if(config->Channel_3.Enable == ENABLE)
    {
        config->Port->SQR3 |= config->Channel_3.Sequence_Number << ADC_SQR3_SQ4_Pos;
    }

    // Configure sequence for Channel 4
    if(config->Channel_4.Enable == ENABLE)
    {
        config->Port->SQR3 |= config->Channel_4.Sequence_Number << ADC_SQR3_SQ5_Pos;
    }

    // Configure sequence for Channel 5
    if(config->Channel_5.Enable == ENABLE)
    {
        config->Port->SQR3 |= config->Channel_5.Sequence_Number << ADC_SQR3_SQ6_Pos;
    }

    // Configure sequence for Channel 6
    if(config->Channel_6.Enable == ENABLE)
    {
        config->Port->SQR2 |= config->Channel_6.Sequence_Number << ADC_SQR2_SQ7_Pos;
    }

    // Configure sequence for Channel 7
    if(config->Channel_7.Enable == ENABLE)
    {
        config->Port->SQR2 |= config->Channel_7.Sequence_Number << ADC_SQR2_SQ8_Pos;
    }

    // Configure sequence for Channel 8
    if(config->Channel_8.Enable == ENABLE)
    {
        config->Port->SQR2 |= config->Channel_8.Sequence_Number << ADC_SQR2_SQ9_Pos;
    }

    // Configure sequence for Channel 9
    if(config->Channel_9.Enable == ENABLE)
    {
        config->Port->SQR2 |= config->Channel_9.Sequence_Number << ADC_SQR2_SQ10_Pos;
    }

    // Configure sequence for Channel 10
    if(config->Channel_10.Enable == ENABLE)
    {
        config->Port->SQR2 |= config->Channel_10.Sequence_Number << ADC_SQR2_SQ11_Pos;
    }

    // Configure sequence for Channel 11
    if(config->Channel_11.Enable == ENABLE)
    {
        config->Port->SQR2 |= config->Channel_11.Sequence_Number << ADC_SQR2_SQ12_Pos;
    }

    /**************************************************************************************************************/

    // Configure sequence for Channel 12
    if(config->Channel_12.Enable == ENABLE)
    {
        config->Port->SQR1 |= config->Channel_12.Sequence_Number << ADC_SQR1_SQ13_Pos;
    }

    /**************************************************************************************************************/

    // Configure sequence for Channel 13
    if(config->Channel_13.Enable == ENABLE)
    {
        config->Port->SQR1 |= config->Channel_13.Sequence_Number << ADC_SQR1_SQ14_Pos;
    }

    /**************************************************************************************************************/

    // Configure sequence for Channel 14
    if(config->Channel_14.Enable == ENABLE)
    {
        config->Port->SQR1 |= config->Channel_14.Sequence_Number << ADC_SQR1_SQ15_Pos;
    }

    /**************************************************************************************************************/

    // Configure sequence for Channel 15
    if(config->Channel_15.Enable == ENABLE)
    {
        config->Port->SQR1 |= config->Channel_15.Sequence_Number << ADC_SQR1_SQ16_Pos;
    }

    // Return success
    return 1;
}



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
int8_t ADC_Init(ADC_Config *config)
{
    // Enable the clock for the selected ADC port
    if (config->Port == ADC_Configuration.Port._ADC1_)
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    else if (config->Port == ADC_Configuration.Port._ADC2_)
        RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
    else if (config->Port == ADC_Configuration.Port._ADC3_)
        RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;
    else
        return -1;

    // Configure the ADC scan mode
    config->Port->CR1 |= ADC_CR1_SCAN;

    // Set the ADC resolution
    if (config->Resolution == ADC_Configuration.Resolution.Bit_12)
        config->Port->CR1 &= ~ADC_CR1_RES;
    else if (config->Resolution == ADC_Configuration.Resolution.Bit_10)
        config->Port->CR1 |=  1 << ADC_CR1_RES_Pos;
    else if (config->Resolution == ADC_Configuration.Resolution.Bit_8)
        config->Port->CR1 |=  2 << ADC_CR1_RES_Pos;
    else if (config->Resolution == ADC_Configuration.Resolution.Bit_6)
        config->Port->CR1 |=  3 << ADC_CR1_RES_Pos;
    else
        return -1;

    // Configure the conversion mode
    if (config->Conversion_Mode == ADC_Configuration.Conversion_Mode.Single) {
        config->Port->CR2 &= ~ADC_CR2_CONT;
    } else if (config->Conversion_Mode == ADC_Configuration.Conversion_Mode.Continuous) {
        config->Port->CR2 |= ADC_CR2_CONT;
    } else {
        return -1;
    }

    // Enable end-of-conversion selection
    config->Port->CR2 |= ADC_CR2_EOCS;

    // Set the data alignment
    if (config->Data_Alignment == ADC_Configuration.Data_Alignment.Right_Justified) {
        config->Port->CR2 &= ~ADC_CR2_ALIGN;
    } else if (config->Data_Alignment == ADC_Configuration.Data_Alignment.Left_Justified) {
        config->Port->CR2 |= ADC_CR2_ALIGN;
    } else {
        return -1;
    }

    // Configure sampling settings and initialize ADC pins
    pin_temp = ADC_Sampling_Config(config);
    config->Port->SQR1 |= (pin_temp - 1) << ADC_SQR1_L_Pos;
    ADC_Pin_Init(config);

    // Configure external trigger for regular or injected channels
    if (config->Channel_Type == ADC_Configuration.Channel_Type.Regular) {
        config->Port->CR2 &= ~ADC_CR2_EXTSEL;

        if (config->External_Trigger.Enable == ENABLE) {
            // config->Port->CR2 |= config->External_Trigger.Trigger_Event << ADC_CR2_EXTSEL_Pos;
            config->Port->CR2 |= ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1;
            config->Port->CR2 |= ADC_CR2_EXTEN_0;
            ADC_Timer_External_Trigger_Init(config);
        }
    } else if (config->Channel_Type == ADC_Configuration.Channel_Type.Injected) {
        config->Port->CR2 &= ~ADC_CR2_JEXTSEL;
        config->Port->CR2 |= config->External_Trigger.Enable << ADC_CR2_JEXTEN_Pos;
        config->Port->CR2 |= config->External_Trigger.Trigger_Event << ADC_CR2_JEXTSEL_Pos;
        ADC_Timer_External_Trigger_Init(config);
    } else {
        return -1;
    }

    // Enable DMA and set DDS for continuous requests
    config->Port->CR2 |= ADC_CR2_DMA;
    config->Port->CR2 |= ADC_CR2_DDS;

    // Configure ADC sequence
    ADC_Sequence_Config(config);

    // Enable the ADC
    ADC_Enable(config);

    // Initialize the DMA with the provided settings
    xADC.Request = DMA_Configuration.Request._ADC1;
    xADC.transfer_direction = DMA_Configuration.Transfer_Direction.Peripheral_to_memory;
    xADC.circular_mode = DMA_Configuration.Circular_Mode.Enable;
    xADC.flow_control = DMA_Configuration.Flow_Control.DMA_Control;
    xADC.memory_data_size = DMA_Configuration.Memory_Data_Size.half_word;
    xADC.peripheral_data_size = DMA_Configuration.Peripheral_Data_Size.half_word;
    xADC.memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;
    xADC.interrupts = DMA_Configuration.DMA_Interrupts.Transfer_Complete | DMA_Configuration.DMA_Interrupts.Half_Transfer_Complete;
    xADC.peripheral_pointer_increment = DMA_Configuration.Peripheral_Pointer_Increment.Disable;
    DMA_Init(&xADC);

    // Return success
    return 1;
}



/********************************************************************************************************************/

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
int8_t ADC_Enable(ADC_Config *config)
{
    // Enable the ADC by setting the ADON bit
    config->Port->CR2 |= ADC_CR2_ADON;

    // Introduce a delay for ADC stabilization
    Delay_milli(1000);

    // Return success
    return 1;
}


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
int8_t ADC_Start(ADC_Config *config)
{
    // Clear the ADC status register
    config->Port->SR = 0;

    // Start the conversion based on the channel type
    if (config->Channel_Type == ADC_Configuration.Channel_Type.Regular) {
        config->Port->CR2 |= ADC_CR2_SWSTART;  // Start regular conversion
    }
    else if (config->Channel_Type == ADC_Configuration.Channel_Type.Injected) {
        config->Port->CR2 |= ADC_CR2_JSWSTART; // Start injected conversion
    }
    else {
        return -1; // Return error if channel type is invalid
    }

    // Return success
    return 1;
}


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
int8_t ADC_Start_Capture(ADC_Config *config, uint16_t *buffer)
{
    // Check for overrun and reset ADC if necessary
    if ((config->Port->SR) & (ADC_SR_OVR))
    {
        config->Port->CR2 &= ~ADC_CR2_ADON; // Turn off the ADC
        config->Port->CR2 |= ADC_CR2_ADON;  // Turn on the ADC
    }

    // Configure DMA settings for the ADC capture
    xADC.buffer_length = pin_temp;
    xADC.peripheral_address = (uint32_t)&(config->Port->DR);
    xADC.memory_address = (uint32_t)buffer;

    // Initialize DMA with the target settings
    DMA_Set_Target(&xADC);
    DMA_Set_Trigger(&xADC);

    // Clear the ADC status register
    config->Port->SR = 0;

    // Start the ADC conversion
    ADC_Start(config);

    // Return success
    return 1;
}
