/*
 * Fault_Switch.c
 *
 *  Created on: Nov 27, 2024
 *      Author: kunal
 */


#include "WSHP.h"

 volatile Flag_State HP_Flag = OFF;
 volatile Flag_State LP_Flag = OFF;
 volatile Flag_State DEFROST_FLAG = OFF;

void HP_Call_ISR(void)
{
	if((GPIOA -> IDR & GPIO_IDR_ID3)){
		HP_Flag = ON;
	}
	if(!(GPIOA -> IDR & GPIO_IDR_ID3)){
		HP_Flag = OFF;
		Current_Code = NO_FAULT;
	}
}

void LP_Call_ISR(void)
{
	if((GPIOA -> IDR & GPIO_IDR_ID4)){
		LP_Flag = ON;
	}
	if(!(GPIOA -> IDR & GPIO_IDR_ID4)){
		LP_Flag = OFF;
		Current_Code = NO_FAULT;
	}

}

void DEFROST_Call_ISR(void)
{
	if((GPIOA -> IDR & GPIO_IDR_ID5)){
		DEFROST_FLAG = ON;
	}
	if(!(GPIOA -> IDR & GPIO_IDR_ID5)){
		DEFROST_FLAG = OFF;
		Current_Code = NO_FAULT;
	}

}


void Fault_Switch_Init(void)
{
	GPIO_Pin_Init(GPIOA, 3,
			GPIO_Configuration.Mode.Input,
			GPIO_Configuration.Output_Type.None,
			GPIO_Configuration.Speed.None,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);

	GPIO_Interrupt_Setup(GPIOA,3 , GPIO_Configuration.Interrupt_Edge.RISING_FALLING_EDGE, 0, LP_Call_ISR);

	GPIO_Pin_Init(GPIOA, 4,
			GPIO_Configuration.Mode.Input,
			GPIO_Configuration.Output_Type.None,
			GPIO_Configuration.Speed.None,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);

	GPIO_Interrupt_Setup(GPIOA,4 , GPIO_Configuration.Interrupt_Edge.RISING_FALLING_EDGE, 0, HP_Call_ISR);

	GPIO_Pin_Init(GPIOA, 5,
			GPIO_Configuration.Mode.Input,
			GPIO_Configuration.Output_Type.None,
			GPIO_Configuration.Speed.None,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);

	GPIO_Interrupt_Setup(GPIOA,5 , GPIO_Configuration.Interrupt_Edge.RISING_FALLING_EDGE, 0, DEFROST_Call_ISR);

}



