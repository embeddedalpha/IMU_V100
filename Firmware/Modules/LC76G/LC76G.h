/*
 * LC76G.h
 *
 *  Created on: Jan 4, 2025
 *      Author: kunal
 */

#ifndef LC76G_LC76G_H_
#define LC76G_LC76G_H_

#include "main.h"
#include "stddef.h"
#include "GPIO/GPIO.h"
#include "USART/USART.h"


typedef enum LC76G_Status_Flag{

	Bad_String,
	Init_Success,
	Init_Fail,
	Process_Success,
	Checksum_Fail,
	Checksum_Pass,

}LC76G_Status_Flag;


typedef struct Meridians_Typedef
{
	uint8_t Degrees;
	float   Minutes;

}Meridians_Typedef;

typedef enum Directions_Typedef{
	North = 1,
	South,
	East,
	West,
}Directions_Typedef;

typedef enum LC76G_Command_Type_Typedef
{
	GNGGA = 1,
	GNVTG,
	GNRMC,
	GBGSV,
	GAGSV,
	GLGSV,
	GPGSV,
	GNGSA,
	GNGLL,

}LC76G_Command_Type_Typedef;

typedef struct LC76G_Data_Typedef
{
	//GNGGA Related Data
	Time_Typedef Fix_Time;
	Meridians_Typedef Latitude;
	Meridians_Typedef Longitude;
	Directions_Typedef N_or_S;
	Directions_Typedef W_or_S;
	uint8_t Number_of_Sats;
	float Altitude;

	//GNVTG
	float COGT; //Course over ground, in true north course direction.
	float SOGN; //Speed over ground in knots.
	float SOGK; //Speed over ground in kilometers per hour

	//GNGLL



}LC76G_Data_Typedef;

LC76G_Status_Flag LC76G_Init(uint32_t baudrate);
LC76G_Status_Flag LC76G_Process_Data(LC76G_Data_Typedef *data);




#endif /* LC76G_LC76G_H_ */
