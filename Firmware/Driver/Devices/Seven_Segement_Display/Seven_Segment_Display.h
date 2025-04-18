/*
 * Seven_Segment_Display.h
 *
 *  Created on: Dec 4, 2024
 *      Author: kunal
 */

#ifndef DEVICES_SEVEN_SEGEMENT_DISPLAY_SEVEN_SEGMENT_DISPLAY_H_
#define DEVICES_SEVEN_SEGEMENT_DISPLAY_SEVEN_SEGMENT_DISPLAY_H_

#include "main.h"
#include "GPIO/GPIO.h"

typedef struct Seven_Segment_Display_Config{

	GPIO_Pin *A;
	GPIO_Pin *B;
	GPIO_Pin *C;
	GPIO_Pin *D;
	GPIO_Pin *E;
	GPIO_Pin *F;
	GPIO_Pin *G;
	GPIO_Pin *DF1;
	GPIO_Pin *DF2;
	GPIO_Pin *DF3;

}Seven_Segment_Display_Config;

typedef enum Segment_Selection
{
	Segment_1 = 1,
	Segment_2 = 2,
	Segment_3 = 3,
}Segment_Selection;

void Seven_Segment_Display_Init(Seven_Segment_Display_Config *config);
void Seven_Segment_Display_Select_Digit(Segment_Selection segment);
void Seven_Segment_Display_Update(char code);


#endif /* DEVICES_SEVEN_SEGEMENT_DISPLAY_SEVEN_SEGMENT_DISPLAY_H_ */
