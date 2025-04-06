/*
 * Thermostat_Inputs.c
 *
 *  Created on: Nov 27, 2024
 *      Author: kunal
 */


#include "WSHP.h"

 volatile Flag_State O_Flag = OFF;
 volatile Flag_State G_Flag = OFF;
 volatile Flag_State Y1_Flag = OFF;
 volatile Flag_State W1_Flag = OFF;
 volatile Flag_State Y2_Flag = OFF;
 volatile Flag_State W2_Flag = OFF;
 volatile Flag_State DH_Flag = OFF;


 void Y1_Call_ISR(void)
 {
 	if((Thermostat_Port -> IDR & GPIO_IDR_ID0)) Y1_Flag = ON;
 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID0)) Y1_Flag = OFF;
 }

 Flag_State Read_Y1_Call(void)
 {
	 	if((Thermostat_Port -> IDR & GPIO_IDR_ID0))return Y1_Flag = ON;
	 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID0))return  Y1_Flag = OFF;
	 	return DONT_CARE;
 }

 void Y2_Call_ISR(void)
 {
 	if((Thermostat_Port -> IDR & GPIO_IDR_ID1)) Y2_Flag = ON;
 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID1)) Y2_Flag = OFF;
 }

 Flag_State Read_Y2_Call(void)
 {
	 	if((Thermostat_Port -> IDR & GPIO_IDR_ID1))return  Y2_Flag = ON;
	 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID1))return  Y2_Flag = OFF;
	 	return DONT_CARE;
 }

 void O_Call_ISR(void)
 {
 	if((Thermostat_Port -> IDR & GPIO_IDR_ID2))O_Flag = ON;
 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID2)) O_Flag = OFF;
 }

 Flag_State Read_O_Call(void)
 {
	 	if((Thermostat_Port -> IDR & GPIO_IDR_ID2))return  O_Flag = ON;
	 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID2))return  O_Flag = OFF;
	 	return DONT_CARE;
 }

 void G_Call_ISR(void)
 {
 	if((Thermostat_Port -> IDR & GPIO_IDR_ID3)) G_Flag = ON;
 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID3)) G_Flag = OFF;

 }

 Flag_State Read_G_Call(void)
 {
	 	if((Thermostat_Port -> IDR & GPIO_IDR_ID3))return  G_Flag = ON;
	 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID3))return  G_Flag = OFF;
	 	return DONT_CARE;
 }

 void W1_Call_ISR(void)
 {
 	if((Thermostat_Port -> IDR & GPIO_IDR_ID4)) W1_Flag = ON;
 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID4)) W1_Flag = OFF;
 }

 Flag_State Read_W1_Call(void)
 {
	 	if((Thermostat_Port -> IDR & GPIO_IDR_ID4))return  W1_Flag = ON;
	 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID4))return  W1_Flag = OFF;
	 	return DONT_CARE;
 }

 void W2_Call_ISR(void)
 {
 	if((Thermostat_Port -> IDR & GPIO_IDR_ID5)) W2_Flag = ON;
 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID5)) W2_Flag = OFF;
 }

 Flag_State Read_W2_Call(void)
 {
	 	if((Thermostat_Port -> IDR & GPIO_IDR_ID5))return  W2_Flag = ON;
	 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID5))return  W2_Flag = OFF;
	 	return DONT_CARE;
 }

 void DH_Call_ISR(void)
 {
 	if((Thermostat_Port -> IDR & GPIO_IDR_ID6)) Y2_Flag = ON;
 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID6)) Y2_Flag = OFF;
 }

 Flag_State Read_DH_Call(void)
 {
	 	if((Thermostat_Port -> IDR & GPIO_IDR_ID5))return  DH_Flag = ON;
	 	if(!(Thermostat_Port -> IDR & GPIO_IDR_ID5))return  DH_Flag = OFF;
	 	return DONT_CARE;
 }

void Thermostat_Pin_Init(void)
 {
 	/************************************************************** Y1 Call ***************************************************************/
 		GPIO_Pin_Init(Thermostat_Port, 0,
 				GPIO_Configuration.Mode.Input,
 				GPIO_Configuration.Output_Type.None,
 				GPIO_Configuration.Speed.None,
 				GPIO_Configuration.Pull.None,
 				GPIO_Configuration.Alternate_Functions.None);

 		GPIO_Interrupt_Setup(Thermostat_Port,0, GPIO_Configuration.Interrupt_Edge.RISING_FALLING_EDGE, 0, Y1_Call_ISR);
 	/**************************************************************************************************************************************/

 	/************************************************************** Y2 Call ***************************************************************/
 		GPIO_Pin_Init(Thermostat_Port, 1,
 				GPIO_Configuration.Mode.Input,
 				GPIO_Configuration.Output_Type.None,
 				GPIO_Configuration.Speed.None,
 				GPIO_Configuration.Pull.None,
 				GPIO_Configuration.Alternate_Functions.None);

 		GPIO_Interrupt_Setup(Thermostat_Port,1, GPIO_Configuration.Interrupt_Edge.RISING_FALLING_EDGE, 0, Y2_Call_ISR);
 	/**************************************************************************************************************************************/

 	/************************************************************** O Call ***************************************************************/
 		GPIO_Pin_Init(Thermostat_Port, 2,
 				GPIO_Configuration.Mode.Input,
 				GPIO_Configuration.Output_Type.None,
 				GPIO_Configuration.Speed.None,
 				GPIO_Configuration.Pull.No_Pull_Up_Down,
 				GPIO_Configuration.Alternate_Functions.None);

 		GPIO_Interrupt_Setup(Thermostat_Port,2, GPIO_Configuration.Interrupt_Edge.RISING_FALLING_EDGE, 0, O_Call_ISR);
 	/*************************************************************************************************************************************/

 //	/************************************************************** G Call ***************************************************************/
 		GPIO_Pin_Init(Thermostat_Port, 3,
 				GPIO_Configuration.Mode.Input,
 				GPIO_Configuration.Output_Type.None,
 				GPIO_Configuration.Speed.None,
 				GPIO_Configuration.Pull.No_Pull_Up_Down,
 				GPIO_Configuration.Alternate_Functions.None);

 		GPIO_Interrupt_Setup(Thermostat_Port,3, GPIO_Configuration.Interrupt_Edge.RISING_FALLING_EDGE, 0, G_Call_ISR);
 //	/*************************************************************************************************************************************/
 //
 //	/************************************************************** W1 Call ***************************************************************/
 		GPIO_Pin_Init(Thermostat_Port, 4,
 				GPIO_Configuration.Mode.Input,
 				GPIO_Configuration.Output_Type.None,
 				GPIO_Configuration.Speed.None,
 				GPIO_Configuration.Pull.No_Pull_Up_Down,
 				GPIO_Configuration.Alternate_Functions.None);

 		GPIO_Interrupt_Setup(Thermostat_Port, 4, GPIO_Configuration.Interrupt_Edge.RISING_FALLING_EDGE, 0, W1_Call_ISR);
 //	/*************************************************************************************************************************************/

 //	/************************************************************** W2 Call ***************************************************************/
		GPIO_Pin_Init(Thermostat_Port, 5,
				GPIO_Configuration.Mode.Input,
				GPIO_Configuration.Output_Type.None,
				GPIO_Configuration.Speed.None,
				GPIO_Configuration.Pull.No_Pull_Up_Down,
				GPIO_Configuration.Alternate_Functions.None);

		GPIO_Interrupt_Setup(Thermostat_Port,5 , GPIO_Configuration.Interrupt_Edge.RISING_FALLING_EDGE, 0, W2_Call_ISR);
 //	/*************************************************************************************************************************************/

 //	/************************************************************** W2 Call ***************************************************************/
		GPIO_Pin_Init(Thermostat_Port, 6,
				GPIO_Configuration.Mode.Input,
				GPIO_Configuration.Output_Type.None,
				GPIO_Configuration.Speed.None,
				GPIO_Configuration.Pull.No_Pull_Up_Down,
				GPIO_Configuration.Alternate_Functions.None);

		GPIO_Interrupt_Setup(Thermostat_Port,6 , GPIO_Configuration.Interrupt_Edge.RISING_FALLING_EDGE, 0, DH_Call_ISR);
 //	/*************************************************************************************************************************************/

 }
