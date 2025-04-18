/*
 * Actuator.c
 *
 *  Created on: Nov 27, 2024
 *      Author: kunal
 */


#include "WSHP.h"


Timer_Config Compressor_Timer;
Timer_Config OD_FAN_PWM;

volatile Flag_State Compressor_State = OFF;
volatile Flag_State Compressor_Second_Stage_State = OFF;
volatile Flag_State BleedOff_Valve_State = OFF;
volatile Flag_State Reheat_Valve_State = OFF;
volatile Flag_State RV_State = OFF;


volatile Flag_State ID_FAN1_State = OFF;
volatile Flag_State ID_FAN2_State = OFF;
volatile Flag_State ID_FAN3_State = OFF;
volatile Flag_State ID_FAN4_State = OFF;
volatile Flag_State ID_FAN5_State = OFF;
volatile Flag_State OD_FAN1_State = OFF;
volatile Flag_State HEATER1_State = OFF;
volatile Flag_State HEATER2_State = OFF;

volatile Flag_State Antishort_Delay_Flag = DONT_CARE;
volatile Flag_State Minimum_ON_Time_Delay_Flag = OFF;
volatile Flag_State Compressor_Cycle_Timer_Flag = OFF;



volatile uint16_t Minimum_ON_Time_Tick = 0;
volatile uint16_t Anti_Short_Cycle_Tick = 0;


void MRT_Timer_ISR(void)
{
	if(Minimum_ON_Time_Tick > (60*5))
	{
		Minimum_ON_Time_Delay_Flag = ON;
		Timer_Disable(&Compressor_Timer);
	}
	else if(Minimum_ON_Time_Tick > (60*2))
	{
		Bypass_Flag = ON;
	}
	else
	{
		Minimum_ON_Time_Tick += 1;
		Minimum_ON_Time_Delay_Flag = OFF;
		Compressor_Cycle_Timer_Flag = OFF;
	}
//	if(Minimum_ON_Time_Tick == (60*60*4))
//	{
//		Compressor_Cycle_Timer_Flag = ON;
//		Minimum_ON_Time_Tick = 0;
//		Timer_Disable(&Compressor_Timer);
//	}

}

void ASCD_Timer_ISR(void)
{

	if(Anti_Short_Cycle_Tick > (60*5))
	{
		Antishort_Delay_Flag = OFF;
		Timer_Disable(&Compressor_Timer);
	}
	else
	{
		Anti_Short_Cycle_Tick += 1;
		Antishort_Delay_Flag = ON;
	}
}


void Output_Relay_Signals_Init(void)
{
	// COMPRESSOR RELAY
	GPIO_Pin_Init(Actuator_Port, 0,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Low_Speed,
			GPIO_Configuration.Pull.Pull_Down,
			GPIO_Configuration.Alternate_Functions.None);

	// RV RELAY
	GPIO_Pin_Init(Actuator_Port, 1,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Low_Speed,
			GPIO_Configuration.Pull.Pull_Down,
			GPIO_Configuration.Alternate_Functions.None);

	// REHEAT RELAY
	GPIO_Pin_Init(Actuator_Port, 2,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Low_Speed,
			GPIO_Configuration.Pull.Pull_Down,
			GPIO_Configuration.Alternate_Functions.None);

	// BLEED-OFF VALVE RELAY
	GPIO_Pin_Init(Actuator_Port, 3,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Low_Speed,
			GPIO_Configuration.Pull.Pull_Down,
			GPIO_Configuration.Alternate_Functions.None);

	// ID_FAN1 RELAY
	GPIO_Pin_Init(Actuator_Port, 4,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Low_Speed,
			GPIO_Configuration.Pull.Pull_Down,
			GPIO_Configuration.Alternate_Functions.None);

	// ID_FAN2 RELAY
	GPIO_Pin_Init(Actuator_Port, 5,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Low_Speed,
			GPIO_Configuration.Pull.Pull_Down,
			GPIO_Configuration.Alternate_Functions.None);


	// ID_FAN3  RELAY
	GPIO_Pin_Init(Actuator_Port, 6,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Low_Speed,
			GPIO_Configuration.Pull.Pull_Down,
			GPIO_Configuration.Alternate_Functions.None);

	// ID_FAN4  RELAY
	GPIO_Pin_Init(Actuator_Port, 7,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Low_Speed,
			GPIO_Configuration.Pull.Pull_Down,
			GPIO_Configuration.Alternate_Functions.None);

	// ID_FAN5  RELAY
	GPIO_Pin_Init(Actuator_Port, 8,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Low_Speed,
			GPIO_Configuration.Pull.Pull_Down,
			GPIO_Configuration.Alternate_Functions.None);


	// OUTPUT_FAN  RELAY
	GPIO_Pin_Init(Actuator_Port, 9,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Low_Speed,
			GPIO_Configuration.Pull.Pull_Down,
			GPIO_Configuration.Alternate_Functions.None);

	// HEATER 1  RELAY
	GPIO_Pin_Init(Actuator_Port, 10,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Low_Speed,
			GPIO_Configuration.Pull.Pull_Down,
			GPIO_Configuration.Alternate_Functions.None);

	// HEATER 2  RELAY
	GPIO_Pin_Init(Actuator_Port, 11,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Low_Speed,
			GPIO_Configuration.Pull.Pull_Down,
			GPIO_Configuration.Alternate_Functions.None);

}

void OD_Fan_PWM_Output_Init(void)
{
	OD_FAN_PWM.Port = TIM1;
	OD_FAN_PWM.Mode = Timer_Configurations.Mode.Master;
	OD_FAN_PWM.Channel_1.Enable = true;
	OD_FAN_PWM.Channel_1.Pin = Timer_Configurations.Channel.Pin.Timer_1.CH1_PA8;
	OD_FAN_PWM.Channel_1.Type = Timer_Configurations.Channel.Type.PWM_Gen_CHP;
	OD_FAN_PWM.Clock_Source = Timer_Configurations.Clock_Source.Internal;
	OD_FAN_PWM.Direction = Timer_Configurations.Direction.Upcounting;
	OD_FAN_PWM.frequency = 100;
	Timer_Init(&OD_FAN_PWM);
}

void Compressor_Relay_ON(void)
{
	Actuator_Port -> BSRR |= GPIO_BSRR_BS0;
	Compressor_State = ON;
}

void Compressor_Relay_OFF(void)
{
	Actuator_Port -> BSRR |= GPIO_BSRR_BR0;
	Compressor_State = OFF;
}
/*********************************************************************************************/
void Compressor_Second_Stage_Relay_ON(void)
{
	Actuator_Port -> BSRR |= GPIO_BSRR_BS1;
	Compressor_Second_Stage_State = ON;
}

void Compressor_Second_Stage_Relay_OFF(void)
{
	Actuator_Port -> BSRR |= GPIO_BSRR_BR1;
	Compressor_Second_Stage_State = OFF;
}
/*********************************************************************************************/
void RV_Relay_ON(void)
{
	RV_State = ON;
	Actuator_Port -> BSRR |= GPIO_BSRR_BS1;
}

void RV_Relay_OFF(void)
{
	RV_State = OFF;
	Actuator_Port -> BSRR |= GPIO_BSRR_BR1;
}
/*********************************************************************************************/
void Reheat_Valve_Relay_ON(void)
{
	Reheat_Valve_State = ON;
	Actuator_Port -> BSRR |= GPIO_BSRR_BS2;
}

void Reheat_Valve_Relay_OFF(void)
{
	Reheat_Valve_State = OFF;
	Actuator_Port -> BSRR |= GPIO_BSRR_BR2;
}
/*********************************************************************************************/
void BleedOFF_Valve_Relay_ON(void)
{
	BleedOff_Valve_State = ON;
	Actuator_Port -> BSRR |= GPIO_BSRR_BS3;
}

void BleedOFF_Valve_Relay_OFF(void)
{
	BleedOff_Valve_State = OFF;
	Actuator_Port -> BSRR |= GPIO_BSRR_BR3;
}
/*********************************************************************************************/
void ID_FAN_1_Relay_ON(void)
{
	ID_FAN1_State = ON;
	Actuator_Port -> BSRR |= GPIO_BSRR_BS4;
}

void ID_FAN_1_Relay_OFF(void)
{
	ID_FAN1_State = OFF;
	Actuator_Port -> BSRR |= GPIO_BSRR_BR4;
}
/*********************************************************************************************/
void ID_FAN_2_Relay_ON(void)
{
	ID_FAN2_State = ON;
	Actuator_Port -> BSRR |= GPIO_BSRR_BS5;
}

void ID_FAN_2_Relay_OFF(void)
{
	ID_FAN2_State = OFF;
	Actuator_Port -> BSRR |= GPIO_BSRR_BR5;
}
/*********************************************************************************************/
void ID_FAN_3_Relay_ON(void)
{
	 ID_FAN3_State = ON;

	Actuator_Port -> BSRR |= GPIO_BSRR_BS6;
}

void ID_FAN_3_Relay_OFF(void)
{
	ID_FAN3_State = OFF;
	Actuator_Port -> BSRR |= GPIO_BSRR_BR6;
}
/*********************************************************************************************/
void ID_FAN_4_Relay_ON(void)
{
	 ID_FAN4_State = ON;

	Actuator_Port -> BSRR |= GPIO_BSRR_BS7;
}

void ID_FAN_4_Relay_OFF(void)
{
	ID_FAN4_State = OFF;
	Actuator_Port -> BSRR |= GPIO_BSRR_BR7;
}
/*********************************************************************************************/
void ID_FAN_5_Relay_ON(void)
{
	 ID_FAN5_State = ON;

	Actuator_Port -> BSRR |= GPIO_BSRR_BS8;
}

void ID_FAN_5_Relay_OFF(void)
{
	ID_FAN5_State = OFF;
	Actuator_Port -> BSRR |= GPIO_BSRR_BR8;
}
/*********************************************************************************************/
void OD_FAN_1_Relay_ON(void)
{
	 OD_FAN1_State = ON;

	Actuator_Port -> BSRR |= GPIO_BSRR_BS9;
}

void OD_FAN_1_Relay_OFF(void)
{
	OD_FAN1_State = OFF;
	Actuator_Port -> BSRR |= GPIO_BSRR_BR9;
}
/*********************************************************************************************/
void HEATER_1_Relay_ON(void)
{
	 HEATER1_State = ON;

	Actuator_Port -> BSRR |= GPIO_BSRR_BS10;
}

void HEATER_1_Relay_OFF(void)
{
	HEATER1_State = OFF;
	Actuator_Port -> BSRR |= GPIO_BSRR_BR10;
}
/*********************************************************************************************/
void HEATER_2_Relay_ON(void)
{
	 HEATER2_State = ON;

	Actuator_Port -> BSRR |= GPIO_BSRR_BS11;
}

void HEATER_2_Relay_OFF(void)
{
	HEATER2_State = OFF;
	Actuator_Port -> BSRR |= GPIO_BSRR_BR11;
}



void MRT_Timer_Init(void)
{
	Compressor_Timer.Port = TIM7;
	Compressor_Timer.Mode = Timer_Configurations.Mode.Update;
	Compressor_Timer.Clock_Source = Timer_Configurations.Clock_Source.Internal;
	Compressor_Timer.DMA_Enable = false;
	Compressor_Timer.Direction = Timer_Configurations.Direction.Upcounting;
	Compressor_Timer.Interrupt_Request = Timer_Configurations.Interrupt_Request.Update_Interrupt;
	Compressor_Timer.ISR_Routines.Update_ISR = MRT_Timer_ISR;
	Compressor_Timer.Prescaler = 8400-1;
	Compressor_Timer.Autoreload_Value = 10000-1;
	Timer_Init(&Compressor_Timer);
	Timer_Trigger(&Compressor_Timer);
}

void ASCD_Timer_Init(void)
{
	Compressor_Timer.Port = TIM7;
	Compressor_Timer.Mode = Timer_Configurations.Mode.Update;
	Compressor_Timer.Clock_Source = Timer_Configurations.Clock_Source.Internal;
	Compressor_Timer.DMA_Enable = false;
	Compressor_Timer.Direction = Timer_Configurations.Direction.Upcounting;
	Compressor_Timer.Interrupt_Request = Timer_Configurations.Interrupt_Request.Update_Interrupt;
	Compressor_Timer.ISR_Routines.Update_ISR = ASCD_Timer_ISR;
	Compressor_Timer.Prescaler = 8400-1;
	Compressor_Timer.Autoreload_Value = 10000-1;
	Timer_Init(&Compressor_Timer);
	Timer_Trigger(&Compressor_Timer);
}

void Compressor_ON(void)
{
	if(Compressor_State == OFF)
	{
		if((Antishort_Delay_Flag == OFF) || (Antishort_Delay_Flag == DONT_CARE))
		{
			if(COMPRESSOR_START_DELAY_Flag == ON)
			{
				if(Compressor_State == OFF )
				{
					Delay_s(5);
				}
			}
			Compressor_Relay_ON();
			Minimum_ON_Time_Tick = 0;
			MRT_Timer_Init();
			Minimum_ON_Time_Delay_Flag = OFF;
			Compressor_State = ON;
			Bypass_Flag = OFF;
		}
	}
}

void Compressor_Second_Stage_OFF(void)
{
	if(Compressor_State == ON)
	{
		Compressor_Second_Stage_Relay_OFF();
		Compressor_Second_Stage_State = OFF;
	}
}

void Compressor_Second_Stage_ON(void)
{
	if(Compressor_State == OFF)
	{
		Compressor_Second_Stage_Relay_ON();
		Compressor_Second_Stage_State = ON;
	}
}

void Compressor_OFF(void)
{
	if(Compressor_State == ON)
	{
		if(Minimum_ON_Time_Delay_Flag == ON)
		{
			Compressor_Relay_OFF();
			Anti_Short_Cycle_Tick =0;
			ASCD_Timer_Init();
			Antishort_Delay_Flag = ON;
			Compressor_State = OFF;
		}
	}
}



