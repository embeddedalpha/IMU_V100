/*
 * Error_Faults.c
 *
 *  Created on: Dec 10, 2024
 *      Author: kunal
 */


#include "WSHP.h"


#define Diagnostic_LED_Port GPIOD
#define Diagnostic_LED_Green 2
#define Diagnostic_LED_Yellow 3



Seven_Segment_Display_Config Error_Code_Display;

Timer_Config Seven_Segment_Timer;
//Timer_Config Diagnostic_LED_Timer;


void Error_Code_Display_ISR(void)
{
    uint8_t code_unit =  Current_Code % 10;
    uint8_t code_tens =  Current_Code / 10;

    Seven_Segment_Display_Select_Digit(Segment_1);
    Seven_Segment_Display_Update(code_unit);
    Seven_Segment_Display_Select_Digit(Segment_2);
    Seven_Segment_Display_Update(code_tens);
}


void Error_Code_Init(void)
{
	Error_Code_Display.A->Port = GPIOC;
	Error_Code_Display.A->Pin_numer = 0;

	Error_Code_Display.B->Port = GPIOC;
	Error_Code_Display.B->Pin_numer = 1;

	Error_Code_Display.C->Port = GPIOC;
	Error_Code_Display.C->Pin_numer = 2;

	Error_Code_Display.D->Port = GPIOC;
	Error_Code_Display.D->Pin_numer = 3;

	Error_Code_Display.E->Port = GPIOC;
	Error_Code_Display.E->Pin_numer = 4;

	Error_Code_Display.F->Port = GPIOC;
	Error_Code_Display.F->Pin_numer = 5;

	Error_Code_Display.G->Port = GPIOC;
	Error_Code_Display.G->Pin_numer = 6;

	Error_Code_Display.DF1->Port = GPIOC;
	Error_Code_Display.DF1->Pin_numer = 7;

	Error_Code_Display.DF2->Port = GPIOC;
	Error_Code_Display.DF2->Pin_numer = 8;

	Seven_Segment_Display_Init(&Error_Code_Display);

	Seven_Segment_Timer.Port = TIM5;
	Seven_Segment_Timer.Mode = Timer_Configurations.Mode.Update;
	Seven_Segment_Timer.Clock_Source = Timer_Configurations.Clock_Source.Internal;
	Seven_Segment_Timer.DMA_Enable = false;
	Seven_Segment_Timer.Direction = Timer_Configurations.Direction.Upcounting;
	Seven_Segment_Timer.Interrupt_Request = Timer_Configurations.Interrupt_Request.Update_Interrupt;
	Seven_Segment_Timer.ISR_Routines.Update_ISR = Error_Code_Display_ISR;
	Seven_Segment_Timer.Prescaler = 8400-1;
	Seven_Segment_Timer.Autoreload_Value = 10000-1;
	Timer_Init(&Seven_Segment_Timer);
	Timer_Trigger(&Seven_Segment_Timer);


}


void Diagnostic_LEDs_Init(void)
{

	GPIO_Pin_Init(Diagnostic_LED_Port, Diagnostic_LED_Yellow, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.None);
	GPIO_Pin_Init(Diagnostic_LED_Port, Diagnostic_LED_Green, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.None);
}


void Diagnostic_LED_Green_Normal(void)
{
	GPIO_Pin_High(Diagnostic_LED_Port, Diagnostic_LED_Green);
}

void Diagnostic_LED_Yellow_Steady(void)
{
	GPIO_Pin_High(Diagnostic_LED_Port, Diagnostic_LED_Yellow);
}
