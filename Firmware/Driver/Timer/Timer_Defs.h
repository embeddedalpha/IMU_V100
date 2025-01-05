/*
 * Timer_Defs.h
 *
 *  Created on: Jul 8, 2024
 *      Author: ksalvi
 */

#ifndef TIMER_DEFS_H_
#define TIMER_DEFS_H_

#include "main.h"


typedef struct __TIMER_CHANNEL__
{
	struct Timer_1{
		uint16_t	CH1_PE9;
		uint16_t	CH1_PA8;
		uint16_t	CH2_PE11;
		uint16_t	CH2_PA9;
		uint16_t	CH3_PE13;
		uint16_t	CH3_PA10;
		uint16_t	CH4_PE14;
		uint16_t	CH4_PA11;
	}Timer_1;

	struct Timer_2{
		uint16_t	CH1_PA0;
		uint16_t	CH1_PA5;
		uint16_t	CH1_PA15;
		uint16_t	CH2_PA1;
		uint16_t	CH2_PB3;
		uint16_t	CH3_PA2;
		uint16_t	CH3_PB10;
		uint16_t	CH4_PA3;
		uint16_t	CH4_PB11;
	}Timer_2;

	struct Timer_3{
		uint16_t	CH1_PA6	;
		uint16_t	CH1_PC6	;
		uint16_t	CH1_PB4	;
		uint16_t	CH2_PA7	;
		uint16_t	CH2_PC7	;
		uint16_t	CH2_PB5	;
		uint16_t	CH3_PB0	;
		uint16_t	CH3_PC8	;
		uint16_t	CH4_PB1	;
		uint16_t	CH4_PC9	;
	}Timer_3;

	struct Timer_4{
		uint16_t	CH1_PD12;
		uint16_t	CH1_PB6	;
		uint16_t	CH2_PD13;
		uint16_t	CH2_PB7;
		uint16_t	CH3_PD14;
		uint16_t	CH3_PB8;
		uint16_t	CH4_PD15;
		uint16_t	CH4_PB9;
	}Timer_4;


	struct Timer_5{
		uint16_t	CH1_PA0	;
		uint16_t	CH2_PA1	;
		uint16_t	CH3_PA2	;
		uint16_t	CH4_PA3	;
	}Timer_5;

	struct Timer_8{
		uint16_t	CH1_PC6	;
		uint16_t	CH2_PC7	;
		uint16_t	CH3_PC8	;
		uint16_t	CH4_PC9	;
	}Timer_8;

	struct Timer_9{
		uint16_t	CH1_PA2	;
		uint16_t	CH1_PE5	;
		uint16_t	CH2_PA3	;
		uint16_t	CH2_PE6	;
	}Timer_9;

	struct Timer_10{
		uint16_t	CH1_PB8	;
	}Timer_10;

	struct Timer_11{
		uint16_t	CH1_PB9	;
	}Timer_11;

	struct Timer_12{
		uint16_t	CH1_PB14	;
		uint16_t	CH2_PB15	;

	}Timer_12;

	struct Timer_13{
		uint16_t	CH1_PA6	;
	}Timer_13;

	struct Timer_14{
		uint16_t	CH1_PA7	;
	}Timer_14;

}__TIMER_CHANNEL__;



typedef struct __TIMER_MODE__
{
	uint8_t Disable;
	uint8_t Update;
	uint8_t Master;
	uint8_t Slave_Ext_Clock_Mode;
	uint8_t Slave_Reset_Mode;
	uint8_t Slave_Gated_Mode;
	uint8_t Slave_Trigger_Mode;
}__TIMER_MODE__;

typedef struct __TIMER_CLOCK_SOURCE__
{
	uint8_t Internal;
	uint8_t ETR2;
}__TIMER_CLOCK_SOURCE__;

typedef struct __TIMER_CHANNEL_MODE__
{
	uint16_t Input_Capture_Direct_Mode;
	uint16_t Output_Capture_No_Output;
	uint16_t Output_Capture_CHP;
	uint16_t Output_Capture_CHN;
	uint16_t Output_Capture_CHP_CHN;
	uint16_t PWM_Gen_No_Output;
	uint16_t PWM_Gen_CHP;
	uint16_t PWM_Gen_CHN;
	uint16_t PWM_Gen_CHP_CHN;
	uint16_t Forced_Output_No_Output;
	uint16_t Forced_Output_CHP;
	uint16_t Forced_Output_CHN;
	uint16_t Forced_Output_CHP_CHN;
	uint16_t Encoder_Mode;
	uint16_t Input_PWM;

}__TIMER_CHANNEL_MODE__;

typedef struct __TIMER_COMBINED_CHANNEL__
{
	uint8_t Disable;
	uint8_t Encoder;
	uint8_t PWM_Input_Channel_1;
	uint8_t PWM_Input_Channel_2;
	uint8_t XOR_Hall_Sensor;

}__TIMER_COMBINED_CHANNEL__;

typedef struct __TIMER_DIRECTION__
{
	uint8_t Upcounting;
	uint8_t Downcounting;
}__TIMER_DIRECTION__;



typedef struct __TIMER_EDGE__
{
	uint8_t rising_edge_non_inverted;
	uint8_t falling_edge_inverted;
	uint8_t both_edges_non_inverted;

}__TIMER_EDGE__;

typedef struct __TIMER_INTERRUPT_REQUEST__{

	uint16_t Disable;
	uint16_t Update_Interrupt;
	uint16_t Capture_Compare_Interrupt_1;
	uint16_t Capture_Compare_Interrupt_2;
	uint16_t Capture_Compare_Interrupt_3;
	uint16_t Capture_Compare_Interrupt_4;
	uint16_t COM_Interrupt;
	uint16_t Trigger_Interrupt;
	uint16_t Break_Interrupt;
}__TIMER_INTERRUPT_REQUEST__;

typedef struct __TIMER_DMA_REQUEST__
{
	uint16_t Update_DMA_Request;
	uint16_t Capture_Compare_1_DMA_Request;
	uint16_t Capture_Compare_2_DMA_Request;
	uint16_t Capture_Compare_3_DMA_Request;
	uint16_t Capture_Compare_4_DMA_Request;
	uint16_t COM_DMA_Request;
	uint16_t Trigger_DMA_Request;
}__TIMER_DMA_REQUEST__;


static const struct Timer_Configurations{

	__TIMER_MODE__ Mode;
	__TIMER_CLOCK_SOURCE__ Clock_Source;
	__TIMER_DIRECTION__ Direction;
	struct Channel{
		__TIMER_CHANNEL__ Pin;
		__TIMER_CHANNEL_MODE__ Type;
	}Channel;
	__TIMER_EDGE__ Edge;
	__TIMER_COMBINED_CHANNEL__ Combined_Channel;
	__TIMER_INTERRUPT_REQUEST__ Interrupt_Request;
	__TIMER_DMA_REQUEST__ DMA_Request;

}Timer_Configurations = {

		.Interrupt_Request = {
				.Disable = 0,
				.Update_Interrupt = 1 << 0,
				.Capture_Compare_Interrupt_1 = 1 << 1,
				.Capture_Compare_Interrupt_2 = 1 << 2,
				.Capture_Compare_Interrupt_3 = 1 << 3,
				.Capture_Compare_Interrupt_4 = 1 << 4,
				.COM_Interrupt = 1 << 5,
				.Trigger_Interrupt = 1 << 6,
				.Break_Interrupt = 1 << 7,
		},

		.DMA_Request = {
				.Update_DMA_Request = 1 << 8,
				.Capture_Compare_1_DMA_Request = 1 << 9,
				.Capture_Compare_2_DMA_Request = 1 << 10,
				.Capture_Compare_3_DMA_Request = 1 << 11,
				.Capture_Compare_4_DMA_Request = 1 << 12,
				.COM_DMA_Request = 1 << 13,
				.Trigger_DMA_Request = 1 << 14,
		},

		.Channel = {

				.Pin = {
						.Timer_1 = {
								.CH1_PE9 =	0xE9 	,
								.CH1_PA8 =	0xA8 	,
								.CH2_PE11 =	0xE11 	,
								.CH2_PA9 =	0xA9 	,
								.CH3_PE13 =	0xE13 	,
								.CH3_PA10 =	0xA10 	,
								.CH4_PE14 =	0xE14 	,
								.CH4_PA11 =	0xA11 	,
						},

						.Timer_2 = {
								.CH1_PA0 =	0xA0 	,
								.CH1_PA5 =	0xA5 	,
								.CH1_PA15 =	0xA15 	,
								.CH2_PA1 =	0xA1 	,
								.CH2_PB3 =	0xB3 	,
								.CH3_PA2 =	0xA2 	,
								.CH3_PB10 =	0xB10 	,
								.CH4_PA3 =	0xA3 	,
								.CH4_PB11 =	0xB11 	,
						},

						.Timer_3 = {
								.CH1_PA6 =	0xA6 	,
								.CH1_PC6 =	0xC6 	,
								.CH1_PB4 =	0xB4 	,
								.CH2_PA7 =	0xA7 	,
								.CH2_PC7 =	0xC7 	,
								.CH2_PB5 =	0xB5 	,
								.CH3_PB0 =	0xB0 	,
								.CH3_PC8 =	0xC8 	,
								.CH4_PB1 =	0xB1 	,
								.CH4_PC9 =	0xC9 	,
						},

						.Timer_4 = {
								.CH1_PD12 =	0xD12 	,
								.CH1_PB6 =	0xB6 	,
								.CH2_PD13 =	0xD13 	,
								.CH2_PB7 =	0xB7 	,
								.CH3_PD14 =	0xD14 	,
								.CH3_PB8 =	0xB8 	,
								.CH4_PD15 =	0xD15 	,
								.CH4_PB9 =	0xB9 	,
						},

						.Timer_5 = {
								.CH1_PA0 =	0xA0 	,
								.CH2_PA1 =	0xA1 	,
								.CH3_PA2 =	0xA2 	,
								.CH4_PA3 =	0xA3 	,
						},

						.Timer_8 = {
								.CH1_PC6 =	0xC6 	,
								.CH2_PC7 =	0xC7 	,
								.CH3_PC8 =	0xC8 	,
								.CH4_PC9 =	0xC9 	,
						},

						.Timer_9 = {
								.CH1_PA2 =	0xA2 	,
								.CH1_PE5 =	0xE5 	,
								.CH2_PA3 =	0xA3 	,
								.CH2_PE6 =	0xE6 	,
						},

						.Timer_10 = {
								.CH1_PB8 =	0xB8 	,
						},

						.Timer_11 = {
								.CH1_PB9 =	0xB9 	,
						},

						.Timer_12 = {
								.CH1_PB14 =	0xB14 	,
								.CH2_PB15 =	0xB15 	,

						},

						.Timer_13 = {
								.CH1_PA6 =	0xA6 	,

						},

						.Timer_14 = {
								.CH1_PA7 =	0xA7 	,
						},
				},

				.Type = {
						.Input_Capture_Direct_Mode = 0b0000000000000001,
						.Output_Capture_No_Output  = 0b0000000000000010,
						.Output_Capture_CHP        = 0b0000000000000100,
						.Output_Capture_CHN        = 0b0000000000001000,
						.Output_Capture_CHP_CHN    = 0b0000000000010000,
						.PWM_Gen_No_Output         = 0b0000000000100000,
						.PWM_Gen_CHP               = 0b0000000001000000,
						.PWM_Gen_CHN               = 0b0000000010000000,
						.PWM_Gen_CHP_CHN           = 0b0000000100000000,
						.Forced_Output_No_Output   = 0b0000001000000000,
						.Forced_Output_CHP         = 0b0000010000000000,
						.Forced_Output_CHN         = 0b0000100000000000,
						.Forced_Output_CHP_CHN     = 0b0001000000000000,
						.Encoder_Mode              = 0b0010000000000000,
						.Input_PWM                 = 0b0100000000000000,
				},
		},

		.Mode = {
				.Disable              = 0b000000,
				.Master               = 0b000001,
				.Slave_Ext_Clock_Mode = 0b000010,
				.Slave_Reset_Mode     = 0b000100,
				.Slave_Gated_Mode     = 0b001000,
				.Slave_Trigger_Mode   = 0b010000,
				.Update               = 0b100000,
		},

		.Clock_Source = {
				.Internal = 0,
				.ETR2 = 0,
		},



		.Combined_Channel = {
				.Disable			 = 0b0000,
				.Encoder 			 = 0b0001,
				.PWM_Input_Channel_1 = 0b0010,
				.PWM_Input_Channel_2 = 0b0100,
				.XOR_Hall_Sensor 	 = 0b1000,
		},
}
;

#endif /* TIMER_DEFS_H_ */
