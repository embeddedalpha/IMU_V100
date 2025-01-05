/*
 * LC76G.c
 *
 *  Created on: Jan 4, 2025
 *      Author: kunal
 */

#include "LC76G.h"

// Taken from quectel_lc26gablc76glc86g_series_gnss_protocol_specification_v1-4.pdf page no 13/139
// pData is the data array whose checksum needs to be calculated:
static unsigned char Ql_Check_XOR(const unsigned char *pData, unsigned int Length)
{
 unsigned char result = 0;
 unsigned int i = 0;
 if((NULL == pData) || (Length < 1))
 {
 return 0;
 }
 for(i = 0; i < Length; i++)
 {
 result ^= *(pData + i);
 }
 return result;
}


LC76G_Status_Flag LC76G_Init(void);
LC76G_Status_Flag LC76G_Process_Data(LC76G_Data_Typedef *data);
