/*
 * Seven_Segment_Display.c
 *
 *  Created on: Dec 4, 2024
 *      Author: kunal
 */

#include "Seven_Segment_Display.h"

Seven_Segment_Display_Config *temp_config;

const uint8_t SEGMENT_MAP[62] = {
    // 0-9
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
    // A-Z
    0b01110111, // A
    0b01111100, // B
    0b00111001, // C
    0b01011110, // D
    0b01111001, // E
    0b01110001, // F
    0b00111101, // G
    0b01110110, // H
    0b00000110, // I
    0b00011110, // J
    0b01110101, // K
    0b00111000, // L
    0b00010101, // M
    0b01010100, // N
    0b00111111, // O
    0b01110011, // P
    0b01101011, // Q
    0b01010000, // R
    0b01101101, // S
    0b01111000, // T
    0b00111110, // U
    0b00111110, // V
    0b01111110, // W
    0b01110110, // X
    0b01101110, // Y
    0b01011011, // Z
    // a-z
    0b01011111, // a
    0b01111100, // b
    0b01011000, // c
    0b01011110, // d
    0b01111011, // e
    0b01110001, // f
    0b01101111, // g
    0b01110100, // h
    0b00000100, // i
    0b00001110, // j
    0b01110101, // k
    0b00110000, // l
    0b00010100, // m
    0b01010100, // n
    0b01011100, // o
    0b01110011, // p
    0b01100111, // q
    0b01010000, // r
    0b01101101, // s
    0b01111000, // t
    0b00011100, // u
    0b00011100, // v
    0b01111110, // w
    0b01110110, // x
    0b01101110, // y
    0b01011011  // z
};

void Seven_Segment_Display_Init(Seven_Segment_Display_Config *config)
{
	temp_config = config;

	GPIO_Pin_Init(temp_config->A->Port, temp_config->A->Pin_numer,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Very_High_Speed,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);

	GPIO_Pin_Init(temp_config->B->Port, temp_config->B->Pin_numer,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Very_High_Speed,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);

	GPIO_Pin_Init(temp_config->C->Port, temp_config->C->Pin_numer,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Very_High_Speed,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);

	GPIO_Pin_Init(temp_config->D->Port, temp_config->D->Pin_numer,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Very_High_Speed,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);

	GPIO_Pin_Init(temp_config->E->Port, temp_config->E->Pin_numer,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Very_High_Speed,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);

	GPIO_Pin_Init(temp_config->F->Port, temp_config->F->Pin_numer,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Very_High_Speed,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);

	GPIO_Pin_Init(temp_config->G->Port, temp_config->G->Pin_numer,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Very_High_Speed,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);

	if(temp_config->DF1->Port != NULL)
	{
	GPIO_Pin_Init(temp_config->DF1->Port, temp_config->DF1->Pin_numer,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Very_High_Speed,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);
	}

	if(temp_config->DF2->Port != NULL)
	{
	GPIO_Pin_Init(temp_config->DF2->Port, temp_config->DF2->Pin_numer,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Very_High_Speed,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);
	}

	if(temp_config->DF3->Port != NULL)
	{
	GPIO_Pin_Init(temp_config->DF3->Port, temp_config->DF3->Pin_numer,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Very_High_Speed,
			GPIO_Configuration.Pull.No_Pull_Up_Down,
			GPIO_Configuration.Alternate_Functions.None);
	}
}

void Seven_Segment_Display_Select_Digit(Segment_Selection segment)
{
	switch (segment) {
		case Segment_1:
			GPIO_Pin_High(temp_config->DF1->Port, temp_config->DF1->Pin_numer);
			break;
		case Segment_2:
			GPIO_Pin_High(temp_config->DF2->Port, temp_config->DF2->Pin_numer);
			break;
		case Segment_3:
			GPIO_Pin_High(temp_config->DF3->Port, temp_config->DF3->Pin_numer);
			break;
	}
}

void Seven_Segment_Display_Update(char code)
{
	uint8_t segmentData;
    if (code >= '0' && code <= '9') {
        segmentData = SEGMENT_MAP[code - '0'];
    } else if (code >= 'A' && code <= 'Z') {
        segmentData = SEGMENT_MAP[code - 'A' + 10];
    } else if (code >= 'a' && code <= 'z') {
        segmentData = SEGMENT_MAP[code - 'a' + 36];
    } else {
        segmentData = 0; // Default to blank
    }


	if((segmentData & 0x01) == 1)GPIO_Pin_High(temp_config->A->Port, temp_config->A->Pin_numer);
	else GPIO_Pin_Low(temp_config->A->Port, temp_config->A->Pin_numer);

	if((segmentData & 0x02) == 0x02)GPIO_Pin_High(temp_config->B->Port, temp_config->B->Pin_numer);
	else GPIO_Pin_Low(temp_config->B->Port, temp_config->B->Pin_numer);

	if((segmentData & 0x04) == 0x04)GPIO_Pin_High(temp_config->C->Port, temp_config->C->Pin_numer);
	else GPIO_Pin_Low(temp_config->C->Port, temp_config->C->Pin_numer);

	if((segmentData & 0x08) == 0x08)GPIO_Pin_High(temp_config->D->Port, temp_config->D->Pin_numer);
	else GPIO_Pin_Low(temp_config->D->Port, temp_config->D->Pin_numer);

	if((segmentData & 0x10) == 0x10)GPIO_Pin_High(temp_config->E->Port, temp_config->E->Pin_numer);
	else GPIO_Pin_Low(temp_config->E->Port, temp_config->E->Pin_numer);

	if((segmentData & 0x20) == 0x20)GPIO_Pin_High(temp_config->F->Port, temp_config->F->Pin_numer);
	else GPIO_Pin_Low(temp_config->F->Port, temp_config->F->Pin_numer);

	if((segmentData & 0x40) == 0x40)GPIO_Pin_High(temp_config->G->Port, temp_config->G->Pin_numer);
	else GPIO_Pin_Low(temp_config->G->Port, temp_config->G->Pin_numer);

}

