/*
 * DIP_Switch.c
 *
 *  Created on: Jan 16, 2025
 *      Author: kunal
 */

#include "WSHP.h"

 volatile Flag_State COMPRESSOR_START_DELAY_Flag  = OFF ;
 volatile Flag_State MOTOR_TYPE_Flag   = OFF;
 volatile Flag_State BLOWER_TIME_DELAY_Flag   = OFF;
 volatile Flag_State NORM_DEHUM_CONFIGURATION_Flag   = OFF;
 volatile Flag_State BOILERLESS_OPERATION_Flag  = OFF ;
 volatile Flag_State BOILERLESS_CHANGE_OVER_TEMPERATURE_Flag  = OFF ;
 volatile Flag_State VACATED_PREMISES_TIMING_Flag  = OFF ;
 volatile Flag_State SINGLE_OR_DUAL_STAGE_MODE_Flag  = OFF;

 volatile Flag_State ACCESSORY_RELAY_1_ACTIVATION_Flag  = OFF ;
 volatile Flag_State SECOND_PRE_COMPRESSOR_60_Flag  = OFF;
 volatile Flag_State ACCESSORY_RELAY_2_ACTIVATION_SIGNAL_Flag  = OFF ;
 volatile Flag_State SECOND_POST_FAN_DELAY_30_Flag  = OFF ;


#define DIPSW_Address 0x21
#define LCD_Address   0x22

I2C_Config dip_ssd;


void DIP_Switches_and_SSD_Init(void)
{
	dip_ssd.Port = I2C2;
	dip_ssd.Mode = I2C_Configuration.Mode.Master;
	dip_ssd.Speed_Mode = I2C_Configuration.Speed_Mode.FM_Mode;
	dip_ssd.SDA_Pin = I2C_Configuration.Pin.__I2C2__.SDA.PB11;
	dip_ssd.SCL_Pin = I2C_Configuration.Pin.__I2C2__.SCL.PB10;
	dip_ssd.DMA_Control = I2C_Configuration.DMA_Control.Disable;
	I2C_Init(&dip_ssd);
}


static uint16_t Read_DIP_Switch(void)
{
	uint16_t dip1, dip2;
	dip1 = I2C_Master_Read_Register(&dip_ssd, DIPSW_Address, 0x00);
	dip2 = I2C_Master_Read_Register(&dip_ssd, DIPSW_Address, 0x01);
	return (dip1 << 8) | dip2;
}

void Enforce_DIP_Switch_States(void)
{
	uint16_t SW = Read_DIP_Switch();

	if(SW & COMPRESSOR_START_DELAY) COMPRESSOR_START_DELAY_Flag = ON;
	else COMPRESSOR_START_DELAY_Flag = OFF;

	if(SW & MOTOR_TYPE) MOTOR_TYPE_Flag = ON;
	else MOTOR_TYPE_Flag = OFF;

	if(SW & BLOWER_TIME_DELAY) BLOWER_TIME_DELAY_Flag = ON;
	else BLOWER_TIME_DELAY_Flag = OFF;

	if(SW & NORM_DEHUM_CONFIGURATION) COMPRESSOR_START_DELAY_Flag = ON;
	else COMPRESSOR_START_DELAY_Flag = OFF;

	if(SW & BOILERLESS_OPERATION) BOILERLESS_OPERATION_Flag = ON;
	else BOILERLESS_OPERATION_Flag = OFF;

	if(SW & BOILERLESS_CHANGE_OVER_TEMPERATURE) BOILERLESS_CHANGE_OVER_TEMPERATURE_Flag = ON;
	else BOILERLESS_CHANGE_OVER_TEMPERATURE_Flag = OFF;

	if(SW & VACATED_PREMISES_TIMING) VACATED_PREMISES_TIMING_Flag = ON;
	else VACATED_PREMISES_TIMING_Flag = OFF;

	if(SW & SINGLE_OR_DUAL_STAGE_MODE) SINGLE_OR_DUAL_STAGE_MODE_Flag = ON;
	else SINGLE_OR_DUAL_STAGE_MODE_Flag = OFF;

	if(SW & ACCESSORY_RELAY_1_ACTIVATION) ACCESSORY_RELAY_1_ACTIVATION_Flag = ON;
	else ACCESSORY_RELAY_1_ACTIVATION_Flag = OFF;

	if(SW & SECOND_PRE_COMPRESSOR_60) SECOND_PRE_COMPRESSOR_60_Flag = ON;
	else SECOND_PRE_COMPRESSOR_60_Flag = OFF;

	if(SW & ACCESSORY_RELAY_2_ACTIVATION_SIGNAL) ACCESSORY_RELAY_2_ACTIVATION_SIGNAL_Flag = ON;
	else ACCESSORY_RELAY_2_ACTIVATION_SIGNAL_Flag = OFF;

	if(SW & SECOND_POST_FAN_DELAY_30) SECOND_POST_FAN_DELAY_30_Flag = ON;
	else SECOND_POST_FAN_DELAY_30_Flag = OFF;


}
