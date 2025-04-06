/*
 * Sensor.c
 *
 *  Created on: Dec 1, 2024
 *      Author: kunal
 */


#include "WSHP.h"





Timer_Config Sensor_Timer;

volatile uint16_t sensor_buffer[7];

 volatile float CO1 = 0.0;
 volatile float CO2 = 0.0;
 volatile float Inlet_Temp = 0.0;
 volatile float Outlet_Temp = 0.0;
 volatile float Cond_SW = 0.0;
 volatile float Pressure = 0.0;
 volatile float Supply_Voltage = 0.0;


 float pressure = 0.0;

 const float R_FIXED = 100000;  // Fixed resistor value in ohms (10kΩ)
 const float BETA = 3950;      // Beta parameter for the thermistor
 const float T0 = 298.15;      // Room temperature in Kelvin (25°C)
 const float R0 = 10000 ;      // Resistance of the thermistor at T0 (10kΩ)
 const float VIN = 3.3 ;       // Input voltage (e.g., 5V)
 const int MAX_PRESSURE = 50;  // PSI

 const float UNDER_VOLTAGE_LIMIT = 18.00;
 const float OVER_VOLTAGE_LIMIT = 32.00;
 const float R1 = 10000;
 const float R2 = 1000;


 ADC_Config sensor_config;


 volatile Flag_State CS_Flag = OFF;
 volatile Flag_State CO1_Flag = OFF;
 volatile Flag_State CO2_Flag = OFF;
 volatile Flag_State UV_Flag = OFF;
 volatile Flag_State OV_Flag = OFF;
 volatile Flag_State Bypass_Flag = OFF;

  volatile uint8_t Bypass_Timer_Counter = 0;
  volatile uint8_t LP_Fault_Counter = 0;
  volatile uint8_t HP_Fault_Counter= 0;
  volatile uint8_t CS_Fault_Counter= 0;
  volatile uint8_t Lockout_Counter= 0;
  volatile uint8_t CO1_Frost_Fault_Counter = 0;
  volatile uint8_t Temp_Swap_Fault_Counter = 0;
  volatile uint8_t CO2_Frost_Fault_Counter = 0;
  volatile uint8_t Water_Flow_Fault_Counter = 0;

 volatile uint32_t Sensor_ticks = 0;
 volatile uint8_t Soft_Lockout_Counter = 0;


 float Get_Voltage(float data)
 {
	 float temp = 0.0;

	 temp = ((R1+R2)/R2)*((float)(sensor_buffer[4]/4095)*3.3);

	 return (temp = 24);
 }



 void Sensor_Timer_ISR(void)
 {
	 Sensor_ticks++;

	 if(Sensor_ticks >= 4294967294) Sensor_ticks = 0;

#if TEST_FLAG == 1

	 	CO1 = 25.00;
	 	CO2 = 25.00;
	 	Cond_SW = 100000;
	 	Pressure = 3.5;
	 	Supply_Voltage = 24.0;

#else

	 	CO1 = Get_Temperature(sensor_buffer[0]);
	 	CO2 = Get_Temperature(sensor_buffer[1]);
	 	Cond_SW = Get_Temperature(sensor_buffer[2]);
	 	Pressure = Get_Temperature(sensor_buffer[3]);
	 	Supply_Voltage = Get_Voltage(sensor_buffer[4]);
	 	Inlet_Temp = Get_Temperature(sensor_buffer[5]);
	 	Outlet_Temp = Get_Temperature(sensor_buffer[6]);

#endif



 	if((CO1 == -1) || (CO2 == -1))
 	{
 		if(
 				(sensor_buffer[0] >= 4000) || (sensor_buffer[0] <= 300) ||
				(sensor_buffer[1] >= 4000) || (sensor_buffer[1] <= 300)
 		   )
 		{
 			Current_Code = TEMP_SENSOR_ERROR;
 			Current_State = HARD_LOCKOUT;
 		}
 	}

 	if(Supply_Voltage < UNDER_VOLTAGE_LIMIT)
 	{
 		UV_Flag = ON;
		Current_Code = UNDER_VOLTAGE_FAULT;
		Current_State = HARD_LOCKOUT;
 	}

 	if(Supply_Voltage > OVER_VOLTAGE_LIMIT)
 	{
 		OV_Flag = ON;
		Current_Code = OVER_VOLTAGE_FAULT;
		Current_State = HARD_LOCKOUT;
 	}

	if(CO1 <= 10.00)
	{
		CO1_Frost_Fault_Counter++;
		if(CO1_Frost_Fault_Counter >= 30)
		{
			Current_State = SOFT_LOCKOUT;
			Current_Code = CO1_FAULT;
			CO1_Frost_Fault_Counter = 0;
		}
	}
	else{
		CO1_Frost_Fault_Counter = 0;
	}

	if(CO2 <= 10.00)
	{
		CO2_Frost_Fault_Counter++;
		if(CO2_Frost_Fault_Counter >= 30)
		{
			Current_State = SOFT_LOCKOUT;
			Current_Code = CO2_FAULT;
			CO2_Frost_Fault_Counter = 0;
		}
	}
	else{
		CO2_Frost_Fault_Counter = 0;
	}

	if(HP_Flag == ON)
	{
		Compressor_Relay_OFF();
		HP_Fault_Counter++;

		if(HP_Fault_Counter >= 30)
		{
			Current_State = HARD_LOCKOUT;
			Current_Code = HP_FAULT;
			HP_Fault_Counter = 0;
		}
	}
	else
	{
		HP_Fault_Counter = 0;
	}

 	if(Bypass_Flag == ON && Compressor_State == ON)
 	{
 /***************************************************************************************************/
 		if(Current_State == HEATING_MODE_1 || Current_State == HEATING_MODE_2)
 		{

 			if((CO1 < CO2))
 			{
 				Temp_Swap_Fault_Counter++;
 				if(Temp_Swap_Fault_Counter >= 30)
 				{
 					Current_State = SOFT_LOCKOUT;
 					Current_Code = SWAPPED_THERMISTOR;
 					Temp_Swap_Fault_Counter = 0;
 				}
 	 			else{
 	 				Temp_Swap_Fault_Counter = 0;
 	 			}
 			}

 		}
 /***************************************************************************************************/
		if(Current_State == COOLING_MODE_1 || Current_State == COOLING_MODE_2)
		{
			if(CO2 < CO1)
			{
				Temp_Swap_Fault_Counter++;
				if(Temp_Swap_Fault_Counter >= 30)
				{
					Current_State = SOFT_LOCKOUT;
					Current_Code = SWAPPED_THERMISTOR;
					Temp_Swap_Fault_Counter = 0;
				}
				else{
					Temp_Swap_Fault_Counter = 0;
				}
			}
		}
 /***************************************************************************************************/
		if(LP_Flag == ON)
		{
			LP_Fault_Counter++;

			if(LP_Fault_Counter >= 30)
			{
				Current_State = SOFT_LOCKOUT;
				Current_Code = LP_FAULT;
				LP_Fault_Counter = 0;
			}
		}
		else
		{
			LP_Fault_Counter = 0;
		}
/***************************************************************************************************/
		if(Cond_SW == ON)
		{
			CS_Fault_Counter++;

			if(CS_Fault_Counter >= 30)
			{
				Current_State = SOFT_LOCKOUT;
				Current_Code = CS_OVERFLOW_FAULT;
				CS_Fault_Counter = 0;
			}
		}
		else
		{
			CS_Fault_Counter = 0;
		}

/***************************************************************************************************/
		if((Current_State == HEATING_MODE_1) || (Current_State == HEATING_MODE_2) )
		{
			if((Inlet_Temp - Outlet_Temp) < 5)
			{
				Water_Flow_Fault_Counter++;
 				if(Water_Flow_Fault_Counter >= 30)
 				{
 					Current_State = SOFT_LOCKOUT;
 					Current_Code = WATER_FLOW_FAULT;
 					Water_Flow_Fault_Counter = 0;
 				}
 	 			else{
 	 				Water_Flow_Fault_Counter = 0;
 	 			}
 			}

		}
		else if((Current_State == COOLING_MODE_1) || (Current_State == COOLING_MODE_2))
		{
			if((Outlet_Temp - Inlet_Temp) < 5)
			{
				Water_Flow_Fault_Counter++;
 				if(Water_Flow_Fault_Counter >= 30)
 				{
 					Current_State = SOFT_LOCKOUT;
 					Current_Code = WATER_FLOW_FAULT;
 					Water_Flow_Fault_Counter = 0;
 				}
 	 			else{
 	 				Water_Flow_Fault_Counter = 0;
 	 			}
 			}
		}
/***************************************************************************************************/


 	}
 }

 void Sensor_Timer_Init(void)
 {

 	Sensor_Timer.Port = TIM6;
 	Sensor_Timer.Mode = Timer_Configurations.Mode.Update;
 	Sensor_Timer.Clock_Source = Timer_Configurations.Clock_Source.Internal;
 	Sensor_Timer.DMA_Enable = false;
 	Sensor_Timer.Direction = Timer_Configurations.Direction.Upcounting;
 	Sensor_Timer.Interrupt_Request = Timer_Configurations.Interrupt_Request.Update_Interrupt;
 	Sensor_Timer.ISR_Routines.Update_ISR = Sensor_Timer_ISR;
 	Sensor_Timer.Prescaler = (uint16_t)(84000000/1000)-1;
 	Sensor_Timer.Autoreload_Value = 10000-1;
 	Timer_Init(&Sensor_Timer);
 	Timer_Trigger(&Sensor_Timer);
 }

 void Sensor_Timer_Stop(void)
 {
	 Timer_Disable(&Sensor_Timer);
 }

 void Sensor_Init(void)
 {
 	sensor_config.Channel_0.Enable = ADC_Configuration.Channel.Enable.Enable;
 	sensor_config.Channel_0.Sample_Time = ADC_Configuration.Channel.Sample_Time._3_Cycles;
 	sensor_config.Channel_0.Sequence_Number = ADC_Configuration.Channel.Sequence_Number.Sequence_1;

 	sensor_config.Channel_1.Enable = ADC_Configuration.Channel.Enable.Enable;
 	sensor_config.Channel_1.Sample_Time = ADC_Configuration.Channel.Sample_Time._3_Cycles;
 	sensor_config.Channel_1.Sequence_Number = ADC_Configuration.Channel.Sequence_Number.Sequence_2;

 	sensor_config.Channel_2.Enable = ADC_Configuration.Channel.Enable.Enable;
 	sensor_config.Channel_2.Sample_Time = ADC_Configuration.Channel.Sample_Time._3_Cycles;
 	sensor_config.Channel_2.Sequence_Number = ADC_Configuration.Channel.Sequence_Number.Sequence_3;

 	sensor_config.Channel_3.Enable = ADC_Configuration.Channel.Enable.Enable;
 	sensor_config.Channel_3.Sample_Time = ADC_Configuration.Channel.Sample_Time._3_Cycles;
 	sensor_config.Channel_3.Sequence_Number = ADC_Configuration.Channel.Sequence_Number.Sequence_4;

 	sensor_config.Channel_4.Enable = ADC_Configuration.Channel.Enable.Enable;
 	sensor_config.Channel_4.Sample_Time = ADC_Configuration.Channel.Sample_Time._3_Cycles;
 	sensor_config.Channel_4.Sequence_Number = ADC_Configuration.Channel.Sequence_Number.Sequence_5;

 	sensor_config.Port = ADC_Configuration.Port._ADC1_;
 	sensor_config.Channel_Type = ADC_Configuration.Channel_Type.Regular;
 	sensor_config.Conversion_Mode = ADC_Configuration.Conversion_Mode.Single;
 	sensor_config.Data_Alignment = ADC_Configuration.Data_Alignment.Right_Justified;
 	sensor_config.Resolution = ADC_Configuration.Resolution.Bit_12;
 	sensor_config.Watchdog_Analog.Enable = ADC_Configuration._Watchdog_Analog_.Disable;
 	sensor_config.External_Trigger.Enable = ADC_Configuration.Regular_External_Trigger_Enable.Trigger_On_Rising_Edge;
 	sensor_config.External_Trigger.Sampling_Frequency = 100;
 	sensor_config.External_Trigger.Trigger_Event = ADC_Configuration.Regular_External_Trigger_Event.Timer_2_CC2;

 	ADC_Init(&sensor_config);
 	ADC_Start_Capture(&sensor_config, (uint16_t *)&sensor_buffer[0]);

 	Sensor_Timer_Init();
 }


// float Get_Temperature(uint16_t adc_value)
// {
// 	float temp_kelvin = 0.0;
// 	float temp_celsius = 0.0;
// 	float Vout = 0.0;
// 	float R_thermistor = 0.0;
//
//
// 	Vout = (adc_value / 1024.0)*VIN;
// 	R_thermistor = R_FIXED * (VIN / Vout - 1);
//
// 	temp_kelvin = 1 / ((1/T0) + (1/BETA) * log(R_thermistor/R0));
// 	return temp_celsius = temp_kelvin - 273.15;
// }
//
// float Get_Resistance(uint16_t adc_value)
// {
// 	float Vout = 0.0;
// 	float R_resistance = 0.0;
// 	Vout = (adc_value / 1024.0)*VIN;
// 	return R_resistance = R_FIXED * (VIN / Vout - 1);
// }

 bool Read_LP_Switch(void)
 {
 	return GPIOB -> IDR & GPIO_IDR_ID0;
 }

 bool Read_HP_Switch(void)
 {
 	return GPIOB -> IDR & GPIO_IDR_ID1;
 }

 float Get_Pressure(uint16_t adc_value)
 {
 	return pressure = (adc_value / 1024.0)*MAX_PRESSURE;
 }
