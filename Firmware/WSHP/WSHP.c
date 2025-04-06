/*
 * WSHP.c
 *
 *  Created on: Nov 27, 2024
 *      Author: kunal
 */


#include "WSHP.h"


volatile System_State Current_State = STANDBY;
volatile OP_Code Current_Code = NO_FAULT;


static bool isCoolingMode()
{
	return (Y1_Flag == ON) && (O_Flag == ON);
}

bool isHeatingMode() {
    return (Y1_Flag == ON) && (O_Flag == OFF);
}

System_State Get_State(void)
{


	if( ( (Y1_Flag == OFF) && (G_Flag == ON) && (Current_Code <=   NO_FAULT)))
	{
		return FAN_ONLY;
	}
	else if( (isHeatingMode() && (Current_Code <=   NO_FAULT)) && ((G_Flag == ON) || (G_Flag == OFF) || (G_Flag == DONT_CARE)))
	{
		if(((Current_Code == LOW_COOL_CODE) || (Current_Code == HIGH_COOL_CODE)) && (Compressor_State == ON) )
		{
			return  TRANSITION_STATE;
		}
		else if((Y2_Flag == ON))
		{
			Current_Code = LOW_HEAT_CODE;
			return HEATING_MODE_2;
		}
		else
		{
			Current_Code = LOW_HEAT_CODE;
		}

		return HEATING_MODE_1;
	}
	else if( (isCoolingMode() && (Current_Code <=  NO_FAULT)) && ((G_Flag == ON) || (G_Flag == OFF) || (G_Flag == DONT_CARE)))
	{
		if(((Current_Code == LOW_HEAT_CODE) || (Current_Code == HIGH_HEAT_CODE)) && (Compressor_State == ON) )
		{
			return  TRANSITION_STATE;
		}
		else if((Y2_Flag == ON))
		{
			Current_Code = HIGH_COOL_CODE;
			return COOLING_MODE_2;
		}
		else
		{
			Current_Code = LOW_COOL_CODE;
		}
		return COOLING_MODE_1;
	}
	else if( (isCoolingMode() && (Current_Code <=  NO_FAULT)) && ((G_Flag == ON) || (G_Flag == OFF) || (G_Flag == DONT_CARE)))
	{
		if(((Current_Code == LOW_HEAT_CODE) || (Current_Code == HIGH_HEAT_CODE)) && (Compressor_State == ON) )
		{
			return  TRANSITION_STATE;
		}
		else
		{
			Current_Code = HIGH_COOL_CODE;
		}
		return COOLING_MODE_2;
	}
	else if((Current_Code >  NO_FAULT))
	{

		return SOFT_LOCKOUT;
	}

	return STANDBY;
}

