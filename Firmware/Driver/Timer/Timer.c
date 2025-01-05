/*
 * Timer.c
 *
 *  Created on: Jul 8, 2024
 *      Author: ksalvi
 */


#include "Timer.h"

Timer_Config *__timer_1_config__;
Timer_Config *__timer_2_config__;
Timer_Config *__timer_3_config__;
Timer_Config *__timer_4_config__;
Timer_Config *__timer_5_config__;
Timer_Config *__timer_6_config__;
Timer_Config *__timer_7_config__;
Timer_Config *__timer_8_config__;
Timer_Config *__timer_9_config__;
Timer_Config *__timer_10_config__;
Timer_Config *__timer_11_config__;
Timer_Config *__timer_12_config__;
Timer_Config *__timer_13_config__;
Timer_Config *__timer_14_config__;



void TIM1_BRK_TIM9_IRQHandler(void) {
    if (__timer_1_config__ ->ISR_Routines.Break_ISR) {
    	__timer_1_config__ ->ISR_Routines.Break_ISR();
    	TIM1->SR &= ~TIM_SR_BIF;  // Clear the Break interrupt flag
    }

    if (__timer_9_config__ ->ISR_Routines.Capture_Compare_1_ISR){
    	__timer_9_config__ ->ISR_Routines.Capture_Compare_1_ISR();
    	TIM9->SR &= ~TIM_SR_CC1IF;  // Clear the Break interrupt flag
    }

    if (__timer_9_config__ ->ISR_Routines.Capture_Compare_2_ISR){
    	__timer_9_config__ ->ISR_Routines.Capture_Compare_2_ISR();
    	TIM9->SR &= ~TIM_SR_CC2IF;  // Clear the Break interrupt flag
    }

    if (__timer_9_config__ ->ISR_Routines.Update_ISR){
    	__timer_9_config__ ->ISR_Routines.Update_ISR();
    	TIM9->SR &= ~TIM_SR_UIF;  // Clear the Break interrupt flag
    }

    if (__timer_9_config__ ->ISR_Routines.Trigger_ISR){
    	__timer_9_config__ ->ISR_Routines.Trigger_ISR();
    	TIM9->SR &= ~TIM_SR_TIF;  // Clear the Break interrupt flag
    }

}

void TIM1_UP_TIM10_IRQHandler(void) {
    if (__timer_1_config__ ->ISR_Routines.Update_ISR) {
    	__timer_1_config__ ->ISR_Routines.Update_ISR();
    	TIM1->SR &= ~TIM_SR_UIF;  // Clear the Update interrupt flag
    }

    if (__timer_10_config__ ->ISR_Routines.Update_ISR) {
    	__timer_10_config__ ->ISR_Routines.Update_ISR();
    	TIM10->SR &= ~TIM_SR_UIF;  // Clear the Update interrupt flag
    }

    if (__timer_10_config__ ->ISR_Routines.Capture_Compare_1_ISR) {
    	__timer_10_config__ ->ISR_Routines.Capture_Compare_1_ISR();
    	TIM10->SR &= ~TIM_SR_CC1IF;  // Clear the Update interrupt flag
    }

}

void TIM1_TRG_COM_TIM11_IRQHandler(void) {
    if (__timer_1_config__ ->ISR_Routines.Trigger_ISR) {
    	__timer_1_config__ ->ISR_Routines.Trigger_ISR();

    	TIM1->SR &= ~TIM_SR_TIF;  // Clear the Trigger interrupt flag
    }

    if (__timer_1_config__ ->ISR_Routines.Commutation_ISR) {
    	__timer_1_config__ ->ISR_Routines.Commutation_ISR();

    	TIM1->SR &= ~TIM_SR_COMIF;  // Clear the Trigger interrupt flag
    }

    if (__timer_11_config__ ->ISR_Routines.Update_ISR) {
    	__timer_11_config__ ->ISR_Routines.Update_ISR();
    	TIM11->SR &= ~TIM_SR_UIF;  // Clear the Update interrupt flag
    }

    if (__timer_11_config__ ->ISR_Routines.Capture_Compare_1_ISR) {
    	__timer_11_config__ ->ISR_Routines.Capture_Compare_1_ISR();
    	TIM11->SR &= ~TIM_SR_CC1IF;  // Clear the Update interrupt flag
    }

}

void TIM1_CC_IRQHandler(void) {
    if (__timer_1_config__ ->ISR_Routines.Capture_Compare_1_ISR) {
    	__timer_1_config__ ->ISR_Routines.Capture_Compare_1_ISR();

    	TIM1->SR &= ~TIM_SR_CC1IF;  // Clear the Capture Compare interrupt flag
    }

    if (__timer_1_config__ ->ISR_Routines.Capture_Compare_2_ISR) {
    	__timer_1_config__ ->ISR_Routines.Capture_Compare_2_ISR();

    	TIM1->SR &= ~TIM_SR_CC2IF;  // Clear the Capture Compare interrupt flag
    }

    if (__timer_1_config__ ->ISR_Routines.Capture_Compare_3_ISR) {
    	__timer_1_config__ ->ISR_Routines.Capture_Compare_3_ISR();

    	TIM1->SR &= ~TIM_SR_CC3IF;  // Clear the Capture Compare interrupt flag
    }

    if (__timer_1_config__ ->ISR_Routines.Capture_Compare_4_ISR) {
    	__timer_1_config__ ->ISR_Routines.Capture_Compare_4_ISR();

    	TIM1->SR &= ~TIM_SR_CC4IF;  // Clear the Capture Compare interrupt flag
    }
}


void TIM2_IRQHandler(void)
{
    if (__timer_2_config__ ->ISR_Routines.Capture_Compare_1_ISR) {
    	__timer_2_config__ ->ISR_Routines.Capture_Compare_1_ISR();

    	TIM2->SR &= ~TIM_SR_CC1IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_2_config__ ->ISR_Routines.Capture_Compare_2_ISR) {
    	__timer_2_config__ ->ISR_Routines.Capture_Compare_2_ISR();

    	TIM2->SR &= ~TIM_SR_CC2IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_2_config__ ->ISR_Routines.Capture_Compare_3_ISR) {
    	__timer_2_config__ ->ISR_Routines.Capture_Compare_3_ISR();

    	TIM2->SR &= ~TIM_SR_CC3IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_2_config__ ->ISR_Routines.Capture_Compare_4_ISR) {
    	__timer_2_config__ ->ISR_Routines.Capture_Compare_4_ISR();

    	TIM2->SR &= ~TIM_SR_CC4IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_2_config__ ->ISR_Routines.Update_ISR) {
    	__timer_2_config__ ->ISR_Routines.Update_ISR();

    	TIM2->SR &= ~TIM_SR_UIF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_2_config__ ->ISR_Routines.Trigger_ISR) {
    	__timer_2_config__ ->ISR_Routines.Trigger_ISR();

    	TIM2->SR &= ~TIM_SR_TIF;  // Clear the Capture Compare interrupt flag
    }
}

void TIM3_IRQHandler(void)
{
    if (__timer_3_config__ ->ISR_Routines.Capture_Compare_1_ISR) {
    	__timer_3_config__ ->ISR_Routines.Capture_Compare_1_ISR();

    	TIM3->SR &= ~TIM_SR_CC1IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_3_config__ ->ISR_Routines.Capture_Compare_2_ISR) {
    	__timer_3_config__ ->ISR_Routines.Capture_Compare_2_ISR();

    	TIM3->SR &= ~TIM_SR_CC2IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_3_config__ ->ISR_Routines.Capture_Compare_3_ISR) {
    	__timer_3_config__ ->ISR_Routines.Capture_Compare_3_ISR();

    	TIM3->SR &= ~TIM_SR_CC3IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_3_config__ ->ISR_Routines.Capture_Compare_4_ISR) {
    	__timer_3_config__ ->ISR_Routines.Capture_Compare_4_ISR();

    	TIM3->SR &= ~TIM_SR_CC4IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_3_config__ ->ISR_Routines.Update_ISR) {
    	__timer_3_config__ ->ISR_Routines.Update_ISR();

    	TIM3->SR &= ~TIM_SR_UIF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_3_config__ ->ISR_Routines.Trigger_ISR) {
    	__timer_3_config__ ->ISR_Routines.Trigger_ISR();

    	TIM3->SR &= ~TIM_SR_TIF;  // Clear the Capture Compare interrupt flag
    }
}

void TIM4_IRQHandler(void)
{
    if (__timer_4_config__ ->ISR_Routines.Capture_Compare_1_ISR) {
    	__timer_4_config__ ->ISR_Routines.Capture_Compare_1_ISR();

    	TIM4->SR &= ~TIM_SR_CC1IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_4_config__ ->ISR_Routines.Capture_Compare_2_ISR) {
    	__timer_4_config__ ->ISR_Routines.Capture_Compare_2_ISR();

    	TIM4->SR &= ~TIM_SR_CC2IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_4_config__ ->ISR_Routines.Capture_Compare_3_ISR) {
    	__timer_4_config__ ->ISR_Routines.Capture_Compare_3_ISR();

    	TIM4->SR &= ~TIM_SR_CC3IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_4_config__ ->ISR_Routines.Capture_Compare_4_ISR) {
    	__timer_4_config__ ->ISR_Routines.Capture_Compare_4_ISR();

    	TIM4->SR &= ~TIM_SR_CC4IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_4_config__ ->ISR_Routines.Update_ISR) {
    	__timer_4_config__ ->ISR_Routines.Update_ISR();

    	TIM4->SR &= ~TIM_SR_UIF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_4_config__ ->ISR_Routines.Trigger_ISR) {
    	__timer_4_config__ ->ISR_Routines.Trigger_ISR();

    	TIM4->SR &= ~TIM_SR_TIF;  // Clear the Capture Compare interrupt flag
    }
}

void TIM5_IRQHandler(void)
{
    if (__timer_5_config__ ->ISR_Routines.Capture_Compare_1_ISR) {
    	__timer_5_config__ ->ISR_Routines.Capture_Compare_1_ISR();

    	TIM5->SR &= ~TIM_SR_CC1IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_5_config__ ->ISR_Routines.Capture_Compare_2_ISR) {
    	__timer_5_config__ ->ISR_Routines.Capture_Compare_2_ISR();

    	TIM5->SR &= ~TIM_SR_CC2IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_5_config__ ->ISR_Routines.Capture_Compare_3_ISR) {
    	__timer_5_config__ ->ISR_Routines.Capture_Compare_3_ISR();

    	TIM5->SR &= ~TIM_SR_CC3IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_5_config__ ->ISR_Routines.Capture_Compare_4_ISR) {
    	__timer_5_config__ ->ISR_Routines.Capture_Compare_4_ISR();

    	TIM5->SR &= ~TIM_SR_CC4IF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_5_config__ ->ISR_Routines.Update_ISR) {
    	__timer_5_config__ ->ISR_Routines.Update_ISR();

    	TIM5->SR &= ~TIM_SR_UIF;  // Clear the Capture Compare interrupt flag
    }
    if (__timer_5_config__ ->ISR_Routines.Trigger_ISR) {
    	__timer_5_config__ ->ISR_Routines.Trigger_ISR();

    	TIM5->SR &= ~TIM_SR_TIF;  // Clear the Capture Compare interrupt flag
    }
}

void TIM6_DAC_IRQHandler(void)
{
    if (__timer_6_config__->ISR_Routines.Update_ISR) {
    	__timer_6_config__->ISR_Routines.Update_ISR();
    	  TIM6->SR &= ~TIM_SR_UIF;  // Clear the Capture Compare interrupt flag

    }

}

void TIM7_IRQHandler(void)
{
    if (__timer_7_config__->ISR_Routines.Update_ISR) {
    	__timer_7_config__->ISR_Routines.Update_ISR();

    	TIM7->SR &= ~TIM_SR_UIF;  // Clear the Capture Compare interrupt flag
    }
}

//if(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Break_Interrupt)
//{
//	NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);
//}
//else if(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.COM_Interrupt)
//{
//	NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn);
//}
//else if(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
//{
//	NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
//}
//else if((config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
//		(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_2) ||
//		(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_3) ||
//		(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_4))
//{
//	NVIC_EnableIRQ(TIM8_CC_IRQn);
//}

void TIM8_BRK_TIM12_IRQHandler(void) {
    if (__timer_8_config__ ->ISR_Routines.Break_ISR) {
    	__timer_8_config__ ->ISR_Routines.Break_ISR();
    	TIM1->SR &= ~TIM_SR_BIF;  // Clear the Break interrupt flag
    }

    if (__timer_12_config__ ->ISR_Routines.Capture_Compare_1_ISR){
    	__timer_12_config__ ->ISR_Routines.Capture_Compare_1_ISR();
    	TIM9->SR &= ~TIM_SR_CC1IF;  // Clear the Break interrupt flag
    }

    if (__timer_12_config__ ->ISR_Routines.Capture_Compare_2_ISR){
    	__timer_12_config__ ->ISR_Routines.Capture_Compare_2_ISR();
    	TIM9->SR &= ~TIM_SR_CC2IF;  // Clear the Break interrupt flag
    }

    if (__timer_12_config__ ->ISR_Routines.Update_ISR){
    	__timer_12_config__ ->ISR_Routines.Update_ISR();
    	TIM9->SR &= ~TIM_SR_UIF;  // Clear the Break interrupt flag
    }

    if (__timer_12_config__ ->ISR_Routines.Trigger_ISR){
    	__timer_12_config__ ->ISR_Routines.Trigger_ISR();
    	TIM9->SR &= ~TIM_SR_TIF;  // Clear the Break interrupt flag
    }

}

void TIM8_UP_TIM13_IRQHandler(void) {
    if (__timer_1_config__ ->ISR_Routines.Update_ISR) {
    	__timer_1_config__ ->ISR_Routines.Update_ISR();
    	TIM1->SR &= ~TIM_SR_UIF;  // Clear the Update interrupt flag
    }

    if (__timer_13_config__ ->ISR_Routines.Update_ISR) {
    	__timer_13_config__ ->ISR_Routines.Update_ISR();
    	TIM13->SR &= ~TIM_SR_UIF;  // Clear the Update interrupt flag
    }

    if (__timer_13_config__ ->ISR_Routines.Capture_Compare_1_ISR) {
    	__timer_13_config__ ->ISR_Routines.Capture_Compare_1_ISR();
    	TIM13->SR &= ~TIM_SR_CC1IF;  // Clear the Update interrupt flag
    }

}

void TIM8_TRG_COM_TIM14_IRQHandler(void) {
    if (__timer_8_config__ ->ISR_Routines.Trigger_ISR) {
    	__timer_8_config__ ->ISR_Routines.Trigger_ISR();

    	TIM8->SR &= ~TIM_SR_TIF;  // Clear the Trigger interrupt flag
    }

    if (__timer_8_config__ ->ISR_Routines.Commutation_ISR) {
    	__timer_8_config__ ->ISR_Routines.Commutation_ISR();

    	TIM8->SR &= ~TIM_SR_COMIF;  // Clear the Trigger interrupt flag
    }

    if (__timer_14_config__ ->ISR_Routines.Update_ISR) {
    	__timer_14_config__ ->ISR_Routines.Update_ISR();
    	TIM14->SR &= ~TIM_SR_UIF;  // Clear the Update interrupt flag
    }

    if (__timer_14_config__ ->ISR_Routines.Capture_Compare_1_ISR) {
    	__timer_14_config__ ->ISR_Routines.Capture_Compare_1_ISR();
    	TIM14->SR &= ~TIM_SR_CC1IF;  // Clear the Update interrupt flag
    }

}

void TIM8_CC_IRQHandler(void) {
    if (__timer_8_config__ ->ISR_Routines.Capture_Compare_1_ISR) {
    	__timer_8_config__ ->ISR_Routines.Capture_Compare_1_ISR();

    	TIM8->SR &= ~TIM_SR_CC1IF;  // Clear the Capture Compare interrupt flag
    }

    if (__timer_8_config__ ->ISR_Routines.Capture_Compare_2_ISR) {
    	__timer_8_config__ ->ISR_Routines.Capture_Compare_2_ISR();

    	TIM8->SR &= ~TIM_SR_CC2IF;  // Clear the Capture Compare interrupt flag
    }

    if (__timer_8_config__ ->ISR_Routines.Capture_Compare_3_ISR) {
    	__timer_8_config__ ->ISR_Routines.Capture_Compare_3_ISR();

    	TIM8->SR &= ~TIM_SR_CC3IF;  // Clear the Capture Compare interrupt flag
    }

    if (__timer_8_config__ ->ISR_Routines.Capture_Compare_4_ISR) {
    	__timer_8_config__ ->ISR_Routines.Capture_Compare_4_ISR();

    	TIM8->SR &= ~TIM_SR_CC4IF;  // Clear the Capture Compare interrupt flag
    }
}


static void Timer_1_Pin_Init(Timer_Config *config)
{

		RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;


		if(config -> Channel_1.Enable ==  true)
		{
			if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_1.CH1_PA8)
				GPIO_Pin_Init(GPIOA, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_1);
			else if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_1.CH1_PE9)
				GPIO_Pin_Init(GPIOE, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_1);
		}

		if(config -> Channel_2.Enable ==  true)
		{
			if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_1.CH2_PA9)
				GPIO_Pin_Init(GPIOA, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_1);
			else if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_1.CH2_PE11)
				GPIO_Pin_Init(GPIOE, 11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_1);
		}

		if(config -> Channel_3.Enable ==  true)
		{
			if(config -> Channel_3.Pin == Timer_Configurations.Channel.Pin.Timer_1.CH3_PA10)
				GPIO_Pin_Init(GPIOA, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_1);
			else if(config -> Channel_3.Pin == Timer_Configurations.Channel.Pin.Timer_1.CH3_PE13)
				GPIO_Pin_Init(GPIOE, 13, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_1);
		}

		if(config -> Channel_4.Enable ==  true)
		{
			if(config -> Channel_4.Pin == Timer_Configurations.Channel.Pin.Timer_1.CH4_PA11)
				GPIO_Pin_Init(GPIOA, 11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_1);
			else if(config -> Channel_4.Pin == Timer_Configurations.Channel.Pin.Timer_1.CH4_PE14)
				GPIO_Pin_Init(GPIOE, 14, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_1);
		}


		if(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Break_Interrupt)
		{
			NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
		}
		else if(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.COM_Interrupt)
		{
			NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
		}
		else if(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
		{
			NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
		}
		else if((config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
				(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_2) ||
				(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_3) ||
				(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_4))
		{
			NVIC_EnableIRQ(TIM1_CC_IRQn);
		}
}

static void Timer_2_Pin_Init(Timer_Config *config)
{

		RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;

		__timer_2_config__ = config;

		if(config -> Channel_1.Enable ==  true)
		{
			if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_2.CH1_PA0)
				GPIO_Pin_Init(GPIOA, 0, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_2);
			else if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_2.CH1_PA15)
				GPIO_Pin_Init(GPIOA, 15, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_2);
			else if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_2.CH1_PA5)
				GPIO_Pin_Init(GPIOA, 5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_2);
		}

		if(config -> Channel_2.Enable ==  true)
		{
			if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_2.CH2_PA1)
				GPIO_Pin_Init(GPIOA, 1, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_2);
			else if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_2.CH2_PB3)
				GPIO_Pin_Init(GPIOB,3, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_2);
		}

		if(config -> Channel_3.Enable ==  true)
		{
			if(config -> Channel_3.Pin == Timer_Configurations.Channel.Pin.Timer_2.CH3_PA2)
				GPIO_Pin_Init(GPIOA, 2, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_2);
			else if(config -> Channel_3.Pin == Timer_Configurations.Channel.Pin.Timer_2.CH3_PB10)
				GPIO_Pin_Init(GPIOB, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_2);
		}

		if(config -> Channel_4.Enable ==  true)
		{
			if(config -> Channel_4.Pin == Timer_Configurations.Channel.Pin.Timer_2.CH4_PA3)
				GPIO_Pin_Init(GPIOA, 3, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_2);
			else if(config -> Channel_4.Pin == Timer_Configurations.Channel.Pin.Timer_2.CH4_PB11)
				GPIO_Pin_Init(GPIOB, 11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_2);
		}

		if(
		   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
		   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_2) ||
		   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_3) ||
		   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_4) ||
		   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Trigger_Interrupt) ||
		   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
		)
		{
			NVIC_EnableIRQ(TIM2_IRQn);
		}

}

static void Timer_3_Pin_Init(Timer_Config *config)
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;

	if(config -> Channel_1.Enable ==  true)
	{
		if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH1_PA6)
			GPIO_Pin_Init(GPIOA, 6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_3);
		else if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH1_PB4)
			GPIO_Pin_Init(GPIOB, 4, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_3);
		else if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH1_PC6)
			GPIO_Pin_Init(GPIOC, 6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_3);
	}

	if(config -> Channel_2.Enable ==  true)
	{
		if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH2_PA7)
			GPIO_Pin_Init(GPIOA, 7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_3);
		else if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH2_PB5)
			GPIO_Pin_Init(GPIOB, 5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_3);
		else if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH2_PC7)
			GPIO_Pin_Init(GPIOC, 7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_3);
	}

	if(config -> Channel_3.Enable ==  true)
	{
		if(config -> Channel_3.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH3_PB0)
			GPIO_Pin_Init(GPIOB, 0, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_3);
		else if(config -> Channel_3.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH3_PC8)
			GPIO_Pin_Init(GPIOC, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_3);
	}

	if(config -> Channel_4.Enable ==  true)
	{
		if(config -> Channel_4.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH4_PB1)
			GPIO_Pin_Init(GPIOB, 1, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_3);
		else if(config -> Channel_4.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH4_PC9)
			GPIO_Pin_Init(GPIOC, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_3);
	}

	if(
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_2) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_3) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_4) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Trigger_Interrupt) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
	)
	{
		NVIC_EnableIRQ(TIM3_IRQn);
	}
}
static void Timer_4_Pin_Init(Timer_Config *config)
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM4EN;

	if(config -> Channel_1.Enable ==  true)
	{
		if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_4.CH1_PB6)
			GPIO_Pin_Init(GPIOB, 6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_4);
		else if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_4.CH1_PD12)
			GPIO_Pin_Init(GPIOD, 12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_4);
	}

	if(config -> Channel_2.Enable ==  true)
	{
		if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_4.CH2_PB7)
			GPIO_Pin_Init(GPIOB, 7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_4);
		else if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_4.CH2_PD13)
			GPIO_Pin_Init(GPIOD, 13, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_4);
	}

	if(config -> Channel_3.Enable ==  true)
	{
		if(config -> Channel_3.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH3_PB0)
			GPIO_Pin_Init(GPIOB, 0, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_4);
		else if(config -> Channel_3.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH3_PC8)
			GPIO_Pin_Init(GPIOC, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_4);
	}

	if(config -> Channel_4.Enable ==  true)
	{
		if(config -> Channel_4.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH4_PB1)
			GPIO_Pin_Init(GPIOB, 1, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_4);
		else if(config -> Channel_4.Pin == Timer_Configurations.Channel.Pin.Timer_3.CH4_PC9)
			GPIO_Pin_Init(GPIOC, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_4);
	}

	if(
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_2) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_3) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_4) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Trigger_Interrupt) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
	)
	{
		NVIC_EnableIRQ(TIM4_IRQn);
	}
}
static void Timer_5_Pin_Init(Timer_Config *config)
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM5EN;

	if(config -> Channel_1.Enable ==  true)
	{
		if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_5.CH1_PA0)
			GPIO_Pin_Init(GPIOA, 0, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_5);
	}

	if(config -> Channel_2.Enable ==  true)
	{
		if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_5.CH2_PA1)
			GPIO_Pin_Init(GPIOA, 1, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_5);
	}

	if(config -> Channel_3.Enable ==  true)
	{
		if(config -> Channel_3.Pin == Timer_Configurations.Channel.Pin.Timer_5.CH3_PA2)
			GPIO_Pin_Init(GPIOB, 0, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_5);
	}

	if(config -> Channel_4.Enable ==  true)
	{
		if(config -> Channel_4.Pin == Timer_Configurations.Channel.Pin.Timer_5.CH4_PA3)
			GPIO_Pin_Init(GPIOB, 1, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_5);
	}

	if(
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_2) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_3) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_4) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Trigger_Interrupt) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
	)
	{
		NVIC_EnableIRQ(TIM5_IRQn);
	}
}
static void Timer_8_Pin_Init(Timer_Config *config)
{
	RCC -> APB2ENR |= RCC_APB2ENR_TIM8EN;

	if(config -> Channel_1.Enable ==  true)
	{
		if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_8.CH1_PC6)
			GPIO_Pin_Init(GPIOC, 6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_8);
	}

	if(config -> Channel_2.Enable ==  true)
	{
		if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_8.CH2_PC7)
			GPIO_Pin_Init(GPIOC, 7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_8);
	}

	if(config -> Channel_3.Enable ==  true)
	{
		if(config -> Channel_3.Pin == Timer_Configurations.Channel.Pin.Timer_8.CH3_PC8)
			GPIO_Pin_Init(GPIOC, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_8);
	}

	if(config -> Channel_4.Enable ==  true)
	{
		if(config -> Channel_4.Pin == Timer_Configurations.Channel.Pin.Timer_8.CH4_PC9)
			GPIO_Pin_Init(GPIOC, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_8);
	}


	if(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Break_Interrupt)
	{
		NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);
	}
	else if(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.COM_Interrupt)
	{
		NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn);
	}
	else if(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
	{
		NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
	}
	else if((config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
			(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_2) ||
			(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_3) ||
			(config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_4))
	{
		NVIC_EnableIRQ(TIM8_CC_IRQn);
	}


}





static void Timer_9_Pin_Init(Timer_Config *config)
{
	RCC -> APB2ENR |= RCC_APB2ENR_TIM9EN;

	__timer_9_config__ = config;

	if(config -> Channel_1.Enable ==  true)
	{
		if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_9.CH1_PA2)
			GPIO_Pin_Init(GPIOA, 2, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_9);
		if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_9.CH1_PE5)
			GPIO_Pin_Init(GPIOE, 5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_9);
	}

	if(config -> Channel_2.Enable ==  true)
	{
		if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_9.CH2_PA3)
			GPIO_Pin_Init(GPIOA, 3, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_9);
		if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_9.CH1_PE5)
			GPIO_Pin_Init(GPIOE, 5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_9);
	}

	if(
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
	)
	{
		NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
	}
}

static void Timer_10_Pin_Init(Timer_Config *config)
{
	RCC -> APB2ENR |= RCC_APB2ENR_TIM10EN;

	if(config -> Channel_1.Enable ==  true)
	{
		if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_10.CH1_PB8)
			GPIO_Pin_Init(GPIOB, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_10);
	}

	if(
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
	)
	{
		NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	}
}

static void Timer_11_Pin_Init(Timer_Config *config)
{
	RCC -> APB2ENR |= RCC_APB2ENR_TIM11EN;

	if(config -> Channel_1.Enable ==  true)
	{
		if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_11.CH1_PB9)
			GPIO_Pin_Init(GPIOB, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_11);
	}

	if(
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
	)
	{
		NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
	}
}

static void Timer_12_Pin_Init(Timer_Config *config)
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM12EN;

	if(config -> Channel_1.Enable ==  true)
	{
		if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_12.CH1_PB14)
			GPIO_Pin_Init(GPIOB, 14, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_12);
	}

	if(config -> Channel_2.Enable ==  true)
	{
		if(config -> Channel_2.Pin == Timer_Configurations.Channel.Pin.Timer_12.CH2_PB15)
			GPIO_Pin_Init(GPIOB, 15, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_12);
	}

	if(
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
	)
	{
		NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);
	}
}

static void Timer_13_Pin_Init(Timer_Config *config)
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM13EN;

	if(config -> Channel_1.Enable ==  true)
	{
		if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_13.CH1_PA6)
			GPIO_Pin_Init(GPIOA, 6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_13);
	}

	if(
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
	   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
	)
	{
		NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
	}
}

static void Timer_14_Pin_Init(Timer_Config *config)
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM14EN;

	if(config -> Channel_1.Enable ==  true)
	{
		if(config -> Channel_1.Pin == Timer_Configurations.Channel.Pin.Timer_14.CH1_PA7)
			GPIO_Pin_Init(GPIOA, 7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None, GPIO_Configuration.Alternate_Functions.TIM_14);
	}

	if(!config->Interrupt_Request)
		if(
		   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) ||
		   (config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt)
		)
		{
			NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn);
		}
}






static void Input_Capture_Mode_Setup(Timer_Config *config)
{
	if(config->Channel_1.Type == Timer_Configurations.Channel.Type.Input_Capture_Direct_Mode)
	{
		if(config->Edge == Timer_Configurations.Edge.rising_edge_non_inverted) config -> Port -> CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
		else if(config->Edge == Timer_Configurations.Edge.falling_edge_inverted) config -> Port -> CCER |= TIM_CCER_CC1NP;
		else if(config->Edge == Timer_Configurations.Edge.both_edges_non_inverted) config -> Port -> CCER |= (TIM_CCER_CC1P | TIM_CCER_CC1NP);

		if(config -> DMA_Enable == true) config -> Port -> DIER |= TIM_DIER_CC1DE;
		if(config -> Interrupt_Request & Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_1) config -> Port -> DIER |= TIM_DIER_CC1IE;

		config -> Port -> CCMR1 |= TIM_CCMR1_CC1S_0;
		config -> Port -> CCMR1 &= ~TIM_CCMR1_CC1S_1;
		config -> Port -> CCER |= TIM_CCER_CC1E;

	}
	if(config->Channel_2.Type == Timer_Configurations.Channel.Type.Input_Capture_Direct_Mode)
	{
		if(config->Edge == Timer_Configurations.Edge.rising_edge_non_inverted) config -> Port -> CCER &= ~(TIM_CCER_CC2P | TIM_CCER_CC2NP);
		else if(config->Edge == Timer_Configurations.Edge.falling_edge_inverted) config -> Port -> CCER |= TIM_CCER_CC2NP;
		else if(config->Edge == Timer_Configurations.Edge.both_edges_non_inverted) config -> Port -> CCER |= (TIM_CCER_CC2P | TIM_CCER_CC2NP);

		if(config -> DMA_Enable == true) config -> Port -> DIER |= TIM_DIER_CC2DE;
		if(config -> Interrupt_Request & Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_2) config -> Port -> DIER |= TIM_DIER_CC2IE;

		config -> Port -> CCMR1 |= TIM_CCMR1_CC2S_0;
		config -> Port -> CCMR1 &= ~TIM_CCMR1_CC2S_1;
		config -> Port -> CCER |= TIM_CCER_CC2E;
	}
	if(config->Channel_3.Type == Timer_Configurations.Channel.Type.Input_Capture_Direct_Mode)
	{
		if(config->Edge == Timer_Configurations.Edge.rising_edge_non_inverted) config -> Port -> CCER &= ~(TIM_CCER_CC3P | TIM_CCER_CC3NP);
		else if(config->Edge == Timer_Configurations.Edge.falling_edge_inverted) config -> Port -> CCER |= TIM_CCER_CC3NP;
		else if(config->Edge == Timer_Configurations.Edge.both_edges_non_inverted) config -> Port -> CCER |= (TIM_CCER_CC3P | TIM_CCER_CC3NP);

		if(config -> DMA_Enable == true) config -> Port -> DIER |= TIM_DIER_CC3DE;
		if(config -> Interrupt_Request & Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_3) config -> Port -> DIER |= TIM_DIER_CC3IE;

		config -> Port -> CCMR2 |= TIM_CCMR2_CC3S_0;
		config -> Port -> CCMR2 &= ~TIM_CCMR2_CC3S_1;
		config -> Port -> CCER |= TIM_CCER_CC3E;
	}
	if(config->Channel_4.Type == Timer_Configurations.Channel.Type.Input_Capture_Direct_Mode)
	{
		if(config->Edge == Timer_Configurations.Edge.rising_edge_non_inverted) config -> Port -> CCER &= ~(TIM_CCER_CC4P | TIM_CCER_CC4NP);
		else if(config->Edge == Timer_Configurations.Edge.falling_edge_inverted) config -> Port -> CCER |= TIM_CCER_CC4NP;
		else if(config->Edge == Timer_Configurations.Edge.both_edges_non_inverted) config -> Port -> CCER |= (TIM_CCER_CC4P | TIM_CCER_CC4NP);

		if(config -> DMA_Enable == true) config -> Port -> DIER |= TIM_DIER_CC4DE;
		if(config -> Interrupt_Request & Timer_Configurations.Interrupt_Request.Capture_Compare_Interrupt_4) config -> Port -> DIER |= TIM_DIER_CC4IE;

		config -> Port -> CCMR2 |= TIM_CCMR2_CC4S_0;
		config -> Port -> CCMR2 &= ~TIM_CCMR2_CC4S_1;
		config -> Port -> CCER |= TIM_CCER_CC4E;
	}
}

static void PWM_Input_Mode_Setup(Timer_Config *config)
{
	if(config -> Combined_Channel == Timer_Configurations.Combined_Channel.PWM_Input_Channel_1)
	{
		config -> Port -> PSC=0;
		config -> Port -> ARR=0xFFFFFFFF;
		config -> Port -> CNT=0;

		config -> Port -> CCMR1|=TIM_CCMR1_CC1S_0;

		config -> Port -> CCER&=~(TIM_CCER_CC1P|TIM_CCER_CC1NP);

		config -> Port -> CCMR1|=TIM_CCMR1_CC2S_1;

		config -> Port -> CCER|=TIM_CCER_CC2P;

		config -> Port -> CCER&=~TIM_CCER_CC2NP;

		config -> Port -> SMCR|=TIM_SMCR_TS_2|TIM_SMCR_TS_0;

		config -> Port -> SMCR|=TIM_SMCR_SMS_2;

		config -> Port -> CCER|=TIM_CCER_CC1E|TIM_CCER_CC2E;
	}
	else if(config -> Combined_Channel == Timer_Configurations.Combined_Channel.PWM_Input_Channel_2)
	{
		config -> Port -> PSC=0;
		config -> Port -> ARR=0xFFFFFFFF;
		config -> Port -> CNT=0;

		config -> Port -> CCMR2|=TIM_CCMR2_CC3S_0;

		config -> Port -> CCER&=~(TIM_CCER_CC3P|TIM_CCER_CC3NP);

		config -> Port -> CCMR2|=TIM_CCMR2_CC4S_1;

		config -> Port -> CCER|=TIM_CCER_CC4P;

		config -> Port -> CCER&=~TIM_CCER_CC4NP;

		config -> Port -> SMCR|=TIM_SMCR_TS_2|TIM_SMCR_TS_0;

		config -> Port -> SMCR|=TIM_SMCR_SMS_2;

		config -> Port -> CCER|=TIM_CCER_CC3E|TIM_CCER_CC4E;
	}
}



static void Encoder_Mode_Setup(Timer_Config *config)
{
//	config -> Port -> CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
//	config -> Port -> CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P  );
//	config -> Port -> SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1; // Set SMS bits to 011 (Encoder mode 3)
//	config -> Port -> SMCR &= ~(TIM_SMCR_SMS); // Clear SMS bits
//	config -> Port -> SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1; // Set SMS bits to 011 (Encoder mode 3)
//	config -> Port -> CCMR1 &= ~(TIM_CCMR1_IC1F | TIM_CCMR1_IC2F); // Clear IC1F and IC2F bits
////	config -> Port -> CCMR1 |= (TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC2F_3); // Set filter to 8 samples, N=8
//	config -> Port -> CCMR1 &= ~(TIM_CCMR1_IC1PSC | TIM_CCMR1_IC2PSC); // Clear IC1PSC and IC2PSC bits
//	config -> Port -> CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P); // Clear CC1P and CC2P bits (rising edge)
//
	config -> Port -> SMCR = 0x0000;
	config -> Port -> CR2 = 0x0000;
	config -> Port->CCMR1 = 0x0000;

	config -> Port->SMCR &= ~TIM_SMCR_SMS;
	config -> Port->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	config -> Port -> CCMR1 |= (TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC2F_3);
	// Set TIM2 Channels to input
	config -> Port->CCMR1 &= ~((3U << TIM_CCMR1_CC1S_Pos) | (3U << TIM_CCMR1_CC2S_Pos));
	config -> Port->CCMR1 |= (1U << TIM_CCMR1_CC1S_Pos) | (1U << TIM_CCMR1_CC2S_Pos);

	// Configure polarity (if necessary)
	config -> Port->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);
	config -> Port -> ARR = config->Encoder_Resolution - 1;
}

static void XOR_Mode_Setup(Timer_Config *config)
{
	config -> Port -> CR2 |= TIM_CR2_TI1S;
	config -> Port -> SMCR &= ~TIM_SMCR_TS;
	config -> Port -> SMCR |= TIM_SMCR_TS_2 | TIM_SMCR_TS_1 | TIM_SMCR_TS_0;
	config -> Port -> SMCR &= ~TIM_SMCR_SMS;
	config -> Port -> SMCR |= TIM_SMCR_SMS_2;
}

static void PWM_Mode_Setup(Timer_Config *config)
{

	if((config -> Channel_1.Enable == true))
	{

		if((config -> Channel_1.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHP) || (config -> Channel_1.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHP_CHN))
		{
			config -> Port -> CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos) ; // PWM mode 1 for CH1 and CH2
			config -> Port -> CCMR1 |= TIM_CCMR1_OC1PE ; // Enable preload for output compare
			config -> Port -> CCER |= TIM_CCER_CC1E ;  // Enable CH1 and CH2 outputs
			config -> Port -> BDTR |= TIM_BDTR_MOE;
		}
		if((config -> Channel_1.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHN) || (config -> Channel_1.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHP_CHN))
		{
			config -> Port -> CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos) ; // PWM mode 1 for CH1 and CH2
			config -> Port -> CCMR1 |= TIM_CCMR1_OC1PE ; // Enable preload for output compare
			config -> Port -> CCER |= TIM_CCER_CC1NE ;  // Enable CH1 and CH2 outputs
			config -> Port -> BDTR |= TIM_BDTR_MOE;
		}

	}
	if((config -> Channel_2.Enable == true))
	{
		if((config -> Channel_2.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHP) || (config -> Channel_2.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHP_CHN))
		{
			config -> Port -> CCMR1 |= (6 << TIM_CCMR1_OC2M_Pos) ; // PWM mode 1 for CH1 and CH2
			config -> Port -> CCMR1 |= TIM_CCMR1_OC2PE ; // Enable preload for output compare
			config -> Port -> CCER |= TIM_CCER_CC2E ;  // Enable CH1 and CH2 outputs
			config -> Port -> BDTR |= TIM_BDTR_MOE;
		}
		if((config -> Channel_2.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHN) || (config -> Channel_2.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHP_CHN))
		{
			config -> Port -> CCMR1 |= (6 << TIM_CCMR1_OC2M_Pos) ; // PWM mode 1 for CH1 and CH2
			config -> Port -> CCMR1 |= TIM_CCMR1_OC2PE ; // Enable preload for output compare
			config -> Port -> CCER |= TIM_CCER_CC2NE ;  // Enable CH1 and CH2 outputs
			config -> Port -> BDTR |= TIM_BDTR_MOE;
		}
	}
	if((config -> Channel_3.Enable == true))
	{
		if((config -> Channel_3.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHP) || (config -> Channel_3.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHP_CHN))
		{
			config -> Port -> CCMR2 |= (6 << TIM_CCMR2_OC3M_Pos) ; // PWM mode 1 for CH1 and CH2
			config -> Port -> CCMR2 |= TIM_CCMR2_OC3PE ; // Enable preload for output compare
			config -> Port -> CCER |= TIM_CCER_CC3E ;  // Enable CH1 and CH2 outputs
			config -> Port -> BDTR |= TIM_BDTR_MOE;
		}
		if((config -> Channel_3.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHN) || (config -> Channel_3.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHP_CHN))
		{
			config -> Port -> CCMR2 |= (6 << TIM_CCMR2_OC3M_Pos) ; // PWM mode 1 for CH1 and CH2
			config -> Port -> CCMR2 |= TIM_CCMR2_OC4PE ; // Enable preload for output compare
			config -> Port -> CCER |= TIM_CCER_CC3NE ;  // Enable CH1 and CH2 outputs
			config -> Port -> BDTR |= TIM_BDTR_MOE;
		}
	}
	if((config -> Channel_4.Enable == true))
	{
		if((config -> Channel_4.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHP) || (config -> Channel_4.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHP_CHN) || (config -> Channel_4.Type == Timer_Configurations.Channel.Type.PWM_Gen_CHN))
		{
			config -> Port -> CCMR2 |= (6 << TIM_CCMR2_OC4M_Pos) ; // PWM mode 1 for CH1 and CH2
			config -> Port -> CCMR2 |= TIM_CCMR2_OC4PE ; // Enable preload for output compare
			config -> Port -> CCER |= TIM_CCER_CC4E ;  // Enable CH1 and CH2 outputs
			config -> Port -> BDTR |= TIM_BDTR_MOE;
		}
	}

}

static void Timer_Update(Timer_Config *config)
{
	config -> Port -> ARR = config -> Autoreload_Value;
	config -> Port -> PSC = config -> Prescaler;

	config -> Port -> EGR |= TIM_EGR_UG;
	config -> Port -> CR1 |= TIM_CR1_URS;
}

void Timer_Init(Timer_Config *config)
{

	if(config -> Port == TIM1) Timer_1_Pin_Init(config);
	else if(config -> Port == TIM2) Timer_2_Pin_Init(config);
	else if(config -> Port == TIM3) Timer_3_Pin_Init(config);
	else if(config -> Port == TIM4) Timer_4_Pin_Init(config);
	else if(config -> Port == TIM5) Timer_5_Pin_Init(config);
	else if(config -> Port == TIM6)
	{
		__timer_6_config__ = config;
		RCC -> APB1ENR |= RCC_APB1ENR_TIM6EN;
		if((config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt))
		{
			NVIC_EnableIRQ(TIM6_DAC_IRQn);
		}
	}
	else if(config -> Port == TIM7)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_TIM7EN;
		__timer_7_config__ = config;
		if((config->Interrupt_Request == Timer_Configurations.Interrupt_Request.Update_Interrupt))
		{
			NVIC_EnableIRQ(TIM7_IRQn);
		}
	}
	else if(config -> Port == TIM8) Timer_8_Pin_Init(config);
	else if(config -> Port == TIM9) Timer_9_Pin_Init(config);
	else if(config -> Port == TIM10) Timer_10_Pin_Init(config);
	else if(config -> Port == TIM11) Timer_11_Pin_Init(config);
	else if(config -> Port == TIM12) Timer_12_Pin_Init(config);
	else if(config -> Port == TIM13) Timer_13_Pin_Init(config);
	else if(config -> Port == TIM14) Timer_14_Pin_Init(config);

	config -> Port -> DIER |= config -> Interrupt_Request;

	//uint16_t Input_Capture_Direct_Mode;
	Input_Capture_Mode_Setup(config);
	PWM_Mode_Setup(config);

	if(config -> Mode == Timer_Configurations.Mode.Update)
	{
		Timer_Update(config);
	}

	if(config -> Combined_Channel == Timer_Configurations.Combined_Channel.Encoder)
	{
		Encoder_Mode_Setup(config);
	}

	if(config -> Combined_Channel == Timer_Configurations.Combined_Channel.PWM_Input_Channel_1)
	{
		PWM_Input_Mode_Setup(config);
	}

	if(config -> Combined_Channel == Timer_Configurations.Combined_Channel.XOR_Hall_Sensor)
	{

		XOR_Mode_Setup(config);
	}

	if(config -> DMA_Enable) DMA_Init(&config->DMA_Timer);
}

/*********************** PWM **************************/

void PWM_Frequency_Update(Timer_Config *config)
{
	if((config -> Port == TIM2) || (config -> Port == TIM3) || (config -> Port == TIM4) || (config -> Port == TIM5) || (config -> Port == TIM6) || (config -> Port == TIM7) || (config -> Port == TIM12) || (config -> Port == TIM13) || (config -> Port == TIM14))
	{
		config -> Port -> PSC = (84000000.0)/((config->frequency)*(100)) - 1;
	}
	else if((config -> Port == TIM1) || (config -> Port == TIM8) || (config -> Port == TIM9) || (config -> Port == TIM10) || (config -> Port == TIM11))
	{
		config -> Port -> PSC = (168000000.0)/((config->frequency)*(100)) - 1;
	}
	config -> Port -> ARR = 100-1;
}

void PWM_Duty_Cycle_Update(Timer_Config *config, uint16_t duty1_percentage, uint16_t duty2_percentage, uint16_t duty3_percentage, uint8_t duty4_percentage)
{
	if(config -> Channel_1.Enable)config -> Port -> CCR1 = duty1_percentage;
	if(config -> Channel_2.Enable)config -> Port -> CCR2 = duty2_percentage;
	if(config -> Channel_3.Enable)config -> Port -> CCR3 = duty3_percentage;
	if(config -> Channel_4.Enable)config -> Port -> CCR4 = duty4_percentage;

}


/*********************** Encoder **************************/

void Encoder_Start(Timer_Config *config)
{
	config -> Port -> PSC = 0x0000;
	config -> Port -> ARR = config -> Encoder_Resolution - 1;
	Timer_Trigger(config);
}

uint16_t Encoder_Read_Counts(Timer_Config *config)
{
	return config -> Port -> CNT;
}

uint8_t Encoder_Get_Direction(Timer_Config *config)
{
	 if (config->Port->CR1 & TIM_CR1_DIR)
	 {
		 return 1;
	 }
	 else
	 {
		 return 0;
	 }
	 return -1;
}
/********************* Input PWM Channel ************************/

void Input_PWM_Channel_Set(Timer_Config *config)
{
	config -> Port -> PSC = config->Prescaler;
	config -> Port -> ARR = config -> Autoreload_Value;
	Timer_Trigger(config);
}

void Input_PWM_Get_Data(Timer_Config *config, uint32_t *t_on, uint32_t *t_total)
{
	*t_on = config->Port->CCR1;
	*t_total = config->Port->CCR2;
}
