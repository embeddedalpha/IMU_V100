/*
 * WSHP_Defs.h
 *
 *  Created on: Nov 27, 2024
 *      Author: kunal
 */

#ifndef WSHP_DEFS_H_
#define WSHP_DEFS_H_

#include "main.h"

typedef enum OP_Code_Typedef{

	STANDBY_CODE = 1,
	FAN_ONLY_CODE = 2,
	LOW_COOL_CODE = 3,
	HIGH_COOL_CODE = 4,
	LOW_HEAT_CODE = 5,
	HIGH_HEAT_CODE = 6,
	AUX_HEAT_CODE = 7,
	HGRH_MODE_CODE = 8,

	NO_FAULT = 11,
	HP_FAULT = 12,
	LP_FAULT = 13,
	CO1_FAULT = 14,
	CO2_FAULT = 15,
	CS_OVERFLOW_FAULT = 16,
	OVER_VOLTAGE_FAULT = 17,
	SWAPPED_THERMISTOR = 18,
	TEMP_SENSOR_ERROR = 19,
	FAULT_RENTRY = 20,
	UNDER_VOLTAGE_FAULT = 21,
	WATER_FLOW_FAULT = 22,

}OP_Code;

typedef enum System_State_Typedef  {
    STANDBY,
    HEATING_MODE_1,
	HEATING_MODE_2,
    COOLING_MODE_1,
	COOLING_MODE_2,
	FAN_ONLY,
	SOFT_LOCKOUT,
	HARD_LOCKOUT,
	TRANSITION_STATE,

} System_State;

typedef enum Flag_State_Typedef
{
	OFF,
	DONT_CARE,
	ON,
}Flag_State;

typedef enum DIP_Switches_Modes_Typedef
{
	COMPRESSOR_START_DELAY   			=	1 << 0,
	MOTOR_TYPE               			=	1 << 1,
	BLOWER_TIME_DELAY  		 			=	1 << 2,
	NORM_DEHUM_CONFIGURATION 			=	1 << 3,
	BOILERLESS_OPERATION   				=	1 << 4,
	BOILERLESS_CHANGE_OVER_TEMPERATURE  =    1 << 5,
	VACATED_PREMISES_TIMING   		 	=	1 << 6,
	SINGLE_OR_DUAL_STAGE_MODE			=	1 << 7,
	ACCESSORY_RELAY_1_ACTIVATION		=   1 << 8,
	SECOND_PRE_COMPRESSOR_60     		=   1 << 9,
	ACCESSORY_RELAY_2_ACTIVATION_SIGNAL  =   1 << 10,
	SECOND_POST_FAN_DELAY_30             =   1 << 11,
}DIP_Switches_Modes;





extern volatile System_State Current_State ;
extern volatile OP_Code Current_Code ;

/*************************************** Thermostat Flags **********************************************/
extern volatile Flag_State O_Flag ;
extern volatile Flag_State G_Flag ;
extern volatile Flag_State Y1_Flag ;
extern volatile Flag_State W1_Flag ;
extern volatile Flag_State Y2_Flag ;
extern volatile Flag_State W2_Flag ;
extern volatile Flag_State DH_Flag ;

/*************************************** Sensor Flags **********************************************/
extern volatile Flag_State HP_Flag  ;
extern volatile Flag_State LP_Flag  ;
extern volatile Flag_State CS_Flag  ;
extern volatile Flag_State CO1_Flag ;
extern volatile Flag_State CO2_Flag ;
extern volatile Flag_State UV_Flag  ;
extern volatile Flag_State OV_Flag  ;
extern volatile Flag_State DEFROST_FLAG;

/*************************************** Actuator Flags **********************************************/
extern volatile Flag_State Compressor_State ;
extern volatile Flag_State Compressor_Second_Stage_State;
extern volatile Flag_State BleedOff_Valve_State ;
extern volatile Flag_State Reheat_Valve_State ;
extern volatile Flag_State RV_State ;
extern volatile Flag_State ID_FAN1_State ;
extern volatile Flag_State ID_FAN2_State ;
extern volatile Flag_State ID_FAN3_State ;
extern volatile Flag_State ID_FAN4_State ;
extern volatile Flag_State ID_FAN5_State ;
extern volatile Flag_State OD_FAN1_State ;
extern volatile Flag_State HEATER1_State;
extern volatile Flag_State HEATER2_State;
/*************************************** Timer Flags **********************************************/
extern volatile Flag_State Antishort_Delay_Flag ;
extern volatile Flag_State Minimum_ON_Time_Delay_Flag ;
extern volatile Flag_State Compressor_Cycle_Timer_Flag ;
extern volatile Flag_State Bypass_Flag;
/************************************* Counters ***********************************************/
extern volatile uint8_t Bypass_Timer_Counter;
extern volatile uint8_t LP_Fault_Counter;
extern volatile uint8_t HP_Fault_Counter;
extern volatile uint8_t CS_Fault_Counter;
extern volatile uint8_t Lockout_Counter;
extern volatile uint8_t CO1_Frost_Fault_Counter;
extern volatile uint8_t Temp_Swap_Fault_Counter;
extern volatile uint8_t CO2_Frost_Fault_Counter;
extern volatile uint8_t Water_Flow_Fault_Counter;
/*************************************** DIP Switches Flags **********************************************/
extern volatile Flag_State COMPRESSOR_START_DELAY_Flag  ;
extern volatile Flag_State MOTOR_TYPE_Flag  ;
extern volatile Flag_State BLOWER_TIME_DELAY_Flag  ;
extern volatile Flag_State BLOWER_TIME_DELAY_Flag  ;
extern volatile Flag_State NORM_DEHUM_CONFIGURATION_Flag  ;
extern volatile Flag_State BOILERLESS_OPERATION_Flag  ;
extern volatile Flag_State BOILERLESS_CHANGE_OVER_TEMPERATURE_Flag  ;
extern volatile Flag_State VACATED_PREMISES_TIMING_Flag  ;
extern volatile Flag_State SINGLE_OR_DUAL_STAGE_MODE_Flag  ;
extern volatile Flag_State ACCESSORY_RELAY_1_ACTIVATION_Flag  ;
extern volatile Flag_State SECOND_PRE_COMPRESSOR_60_Flag  ;
extern volatile Flag_State ACCESSORY_RELAY_2_ACTIVATION_SIGNAL_Flag  ;
extern volatile Flag_State SECOND_POST_FAN_DELAY_30_Flag  ;


extern volatile float Inlet_Temp;
extern volatile float Outlet_Temp;
extern volatile float CO1 ;
extern volatile float CO2 ;
extern volatile float Cond_SW ;
extern volatile float Pressure;
extern volatile float Supply_Voltage;

extern volatile uint16_t Minimum_ON_Time_Tick ;
extern volatile uint16_t Anti_Short_Cycle_Tick;

extern volatile uint8_t Soft_Lockout_Counter;

extern volatile uint32_t Sensor_ticks;




#endif /* WSHP_DEFS_H_ */
