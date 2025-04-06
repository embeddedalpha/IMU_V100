/*
 * main.h
 *
 *  Created on: Nov 17, 2021
 *      Author: Kunal
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include <stdio.h>
#include "math.h"
#include "inttypes.h"
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include "stdbool.h"
#include "stdint.h"
#include "system_stm32f4xx.h"
//#include "Drivers/GPIO.h"


typedef struct Interrupts
{
	bool Enable;
	uint32_t Interrup_Flags;
}Interrupts;

#define __weak   __attribute__((weak))

#define SPI_Debug_Flag 0

extern uint32_t APB1CLK_SPEED;
extern uint32_t APB2CLK_SPEED;


void BSP_Init(void);

__STATIC_INLINE int32_t SystemAPB1_Clock_Speed(void)
{
	return (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1)>> RCC_CFGR_PPRE1_Pos]);
}

__STATIC_INLINE int32_t SystemAPB2_Clock_Speed(void)
{
	return (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2)>> RCC_CFGR_PPRE2_Pos]);
}

__STATIC_INLINE void MCU_Clock_Setup(void)
{
//	uint8_t pll_m = 4;
//	uint8_t pll_n = 168; //192
//	uint8_t pll_p = 0;
//	uint8_t pll_q = 7;

	SystemInit();

	uint8_t pll_m = 8;
	uint16_t pll_n = 336; //192
	uint8_t pll_p = 0;
	uint8_t pll_q = 7;

	RCC->PLLCFGR = 0x00000000;
	RCC -> CR |= RCC_CR_HSEON;
	while(!(RCC -> CR & RCC_CR_HSERDY)){}
	RCC -> APB1ENR |= RCC_APB1ENR_PWREN;
	PWR ->CR |= PWR_CR_VOS;
	FLASH -> ACR |= FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;
	RCC->PLLCFGR |= (pll_q << 24) | (pll_p << 16) | (pll_n << 6) | (pll_m << 0);
	RCC ->PLLCFGR |= 1 << 22;
	RCC -> CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC -> CFGR |= RCC_CFGR_PPRE1_DIV4;
	RCC -> CFGR |= RCC_CFGR_PPRE2_DIV2;




	RCC -> CR |= RCC_CR_PLLON;



	while(!(RCC->CR & RCC_CR_PLLRDY)){}
	RCC -> CFGR |= RCC_CFGR_SW_PLL;
	while((RCC -> CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/168);
	RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}


__STATIC_INLINE int I2S_Clock_Init()
{
//	int plli2s_m = 25; //25 25 4
//	int plli2s_n = 344; //344 192 50
//	int plli2s_r = 2; //2 5 2
//	RCC -> PLLI2SCFGR = (plli2s_m << 0) | (plli2s_n << 6) | (plli2s_r << 28);
//	RCC -> CR |= RCC_CR_PLLI2SON;
//	while(!(RCC -> CR & RCC_CR_PLLI2SRDY));

	uint32_t RCC_PLLI2SCFGR = 0;
	uint32_t plli2s_n = 384;
	uint32_t plli2s_r = 5;
	RCC_PLLI2SCFGR = plli2s_n << 6;
	RCC_PLLI2SCFGR |= plli2s_r << 28;
	RCC -> PLLI2SCFGR = RCC_PLLI2SCFGR;
	RCC -> CR |= RCC_CR_PLLI2SON;
	while(!(RCC -> CR & RCC_CR_PLLI2SRDY));
	return (0UL);
}



__STATIC_INLINE uint32_t Delay_Config(void)
{

	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	return (0UL);                                                     /* Function successful */
}

__STATIC_INLINE void Delay_DeInit(void)
{
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}


__STATIC_INLINE uint32_t Delay_us(float us)
{

	SysTick->LOAD = 168 * us;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
	return (0UL);                                                     /* Function successful */
}

__STATIC_INLINE uint32_t Delay_ms(float ms)
{
	unsigned long x =0x29040 * (ms);
	SysTick->LOAD =  x ;
	SysTick->VAL = 0;
	SysTick->CTRL |= 1;
	while((SysTick->CTRL & 0x00010000) == 0);
	return (0UL);                                                     /* Function successful */
}


__STATIC_INLINE uint32_t Delay_milli(float ms)
{
	for (; ms>0; ms--)
	{
		Delay_ms(1);
	}
	return ms;
}


__STATIC_INLINE uint32_t Delay_s(unsigned long s)
{
	s = s * 1000;
	for (; s>0; s--)
	{
		Delay_ms(1);
	}
	return (0UL);
}


__STATIC_INLINE float Time_Stamp_Start(void)
{
	float temp = 0;
	SysTick->CTRL = 0;
	SysTick->LOAD = 0xFFFFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x5;
	while(SysTick->VAL != 0);
	temp = (float)(SysTick->VAL / (SystemCoreClock));
	return temp;
}

__STATIC_INLINE float Time_Stamp_End(void)
{
	float temp = 0;
	temp = (float)(SysTick->VAL / (SystemCoreClock));
	return temp;
}

__STATIC_INLINE	void separateFractionAndIntegral(double number, double *fractionalPart, double *integralPart) {
    *integralPart = (double)((int64_t)number);
    *fractionalPart = number - *integralPart;
}


__STATIC_INLINE void Loging_Init(void)
{
	// Enable Debug Exception and Monitor Control Register (DEMCR)
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

	// Unlock and enable ITM
	ITM->LAR = 0xC5ACCE55;  // Unlock ITM
	ITM->TCR |= ITM_TCR_ITMENA_Msk;  // Enable ITM

	// Enable stimulus port 0 (ITM_STIM0) for logging
	ITM->TER |= (1 << 0);  // Enable stimulus port 0

}

__STATIC_INLINE void Log_Print(char *msg, ...)
{
	char buff[100];

	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);

	for(int i = 0; i<= strlen(buff)-1; i++)
	{
		ITM_SendChar(buff[i]);
	}
}

__STATIC_INLINE int Log_Scan(int buffer_length, char * msg, ...)
{

	char buff[100];

	va_list args;

	for(int i = 0; i < buffer_length; i++)
	{
		while(!(ITM_CheckChar())){}
        char ch = ITM_ReceiveChar();
        buff[i] = ITM_SendChar(ch);  // Echo character back
	}

	va_start(args, msg);
    // Use sscanf to parse the input from the buffer
    int result = vsscanf(buff, msg, args);
    // Clean up the variable argument list
    va_end(args);
    return result;  // Return the number of successful conversions
}




#endif /* MAIN_H_ */
