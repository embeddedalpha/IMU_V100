/*
 * Timer.h
 *
 *  Created on: Jul 8, 2024
 *      Author: ksalvi
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "DMA/DMA.h"
#include "Timer_Defs.h"




typedef struct Timer_Config{

	TIM_TypeDef *Port;

	uint8_t Mode;
	uint8_t Clock_Source;
	bool Direction;

	float frequency;
	uint16_t Prescaler;
	uint16_t Autoreload_Value;

	struct __Channel__{
		bool Enable;
		uint16_t Type;
		uint16_t Pin;
	}Channel_1, Channel_2, Channel_3, Channel_4;

	uint8_t Combined_Channel;
	uint8_t Interrupt_Request;
	uint8_t Edge;
	bool One_Pulse_Mode;

	bool DMA_Enable;
	DMA_Config DMA_Timer;
	uint32_t Encoder_Resolution;

	struct __Timer_Interrupts__{
		void (*Update_ISR)(void);
		void (*Capture_Compare_1_ISR)(void);
		void (*Capture_Compare_2_ISR)(void);
		void (*Capture_Compare_3_ISR)(void);
		void (*Capture_Compare_4_ISR)(void);
		void (*Commutation_ISR)(void);
		void (*Trigger_ISR)(void);
		void (*Break_ISR)(void);
	}ISR_Routines;



}Timer_Config;

void Timer_Init(Timer_Config *config);
//void Timer_Trigger(Timer_Config *config);
//void Timer_Disable(Timer_Config *config);

__STATIC_INLINE void Timer_Trigger(Timer_Config *config)
{
	config -> Port -> CR1 |= TIM_CR1_CEN;
}

__STATIC_INLINE void Timer_Disable(Timer_Config *config)
{
	config -> Port -> CR1 &= ~TIM_CR1_CEN;
}

void PWM_Frequency_Update(Timer_Config *config);
void PWM_Duty_Cycle_Update(Timer_Config *config, uint16_t duty1_percentage, uint16_t duty2_percentage, uint16_t duty3_percentage, uint8_t duty4_percentage);


void Encoder_Start(Timer_Config *config);
uint16_t Encoder_Read_Counts(Timer_Config *config);
uint8_t Encoder_Get_Direction(Timer_Config *config);

void Input_PWM_Channel_Set(Timer_Config *config);
void Input_PWM_Get_Data(Timer_Config *config, uint32_t *t_on, uint32_t *t_total);


#endif /* TIMER_H_ */
