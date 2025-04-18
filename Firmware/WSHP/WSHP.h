/*
 * WSHP.h
 *
 *  Created on: Nov 27, 2024
 *      Author: kunal
 */

#ifndef WSHP_H_
#define WSHP_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "DMA/DMA.h"
#include "ADC/ADC.h"
#include "Timer/Timer.h"
#include "Console/Console.h"
#include "I2C/I2C.h"

#include "Devices/Thermistor/Thermistor.h"
#include "Devices/Seven_Segement_Display/Seven_Segment_Display.h"


#include "WSHP_Defs.h"


#define TEST_FLAG 1

#define Thermostat_Port GPIOE
#define Actuator_Port	GPIOD
#define DIP_Switch_Port GPIOB

/*****************************************************************************************************/
/*****************************************************************************************************/

extern volatile System_State Current_State ;
extern volatile OP_Code Current_Code ;
extern volatile System_State Get_State(void);

/*****************************************************************************************************/
/*****************************************************************************************************/

void Thermostat_Pin_Init(void);

Flag_State Read_Y1_Call(void);
Flag_State Read_Y2_Call(void);
Flag_State Read_O_Call(void);
Flag_State Read_G_Call(void);
Flag_State Read_W1_Call(void);
Flag_State Read_W2_Call(void);

/*****************************************************************************************************/
/*****************************************************************************************************/

void Output_Relay_Signals_Init(void);
void OD_Fan_PWM_Output_Init(void);

void Compressor_Relay_ON(void);
void Compressor_Relay_OFF(void);

void RV_Relay_ON(void);
void RV_Relay_OFF(void);

void Reheat_Valve_Relay_ON(void);
void Reheat_Valve_Relay_OFF(void);

void BleedOFF_Valve_Relay_ON(void);
void BleedOFF_Valve_Relay_OFF(void);

void ID_FAN_1_Relay_ON(void);
void ID_FAN_1_Relay_OFF(void);

void ID_FAN_2_Relay_ON(void);
void ID_FAN_2_Relay_OFF(void);

void ID_FAN_3_Relay_ON(void);
void ID_FAN_3_Relay_OFF(void);

void ID_FAN_4_Relay_ON(void);
void ID_FAN_4_Relay_OFF(void);

void ID_FAN_5_Relay_ON(void);
void ID_FAN_5_Relay_OFF(void);

void OD_FAN_1_Relay_ON(void);
void OD_FAN_1_Relay_OFF(void);

void HEATER_1_Relay_ON(void);
void HEATER_1_Relay_OFF(void);

void HEATER_2_Relay_ON(void);
void HEATER_2_Relay_OFF(void);

void Compressor_ON(void);
void Compressor_OFF(void);

void Compressor_Second_Stage_OFF(void);
void Compressor_Second_Stage_ON(void);

void MRT_Timer_Init(void);
void ASCD_Timer_Init(void);

/*****************************************************************************************************/
/*****************************************************************************************************/

void Fault_Switch_Init(void);

/*****************************************************************************************************/
/*****************************************************************************************************/

void Sensor_Init(void);
float Get_Pressure(uint16_t adc_value);
bool Read_HP_Switch(void);
bool Read_LP_Switch(void);
void Sensor_Timer_Stop(void);

/*****************************************************************************************************/
/*****************************************************************************************************/

void Error_Code_Init(void);
void Diagnostic_LEDs_Init(void);
void Diagnostic_LED_Green_Normal(void);
void Diagnostic_LED_Yellow_Steady(void);

/*****************************************************************************************************/
/*****************************************************************************************************/

void DIP_Switches_and_SSD_Init(void);
void Enforce_DIP_Switch_States(void);

/*****************************************************************************************************/
/*****************************************************************************************************/

void HMI_Init(int32_t baudrate);
void HMI_Send(void);
void HMI_Receive(void);

#endif /* WSHP_H_ */
