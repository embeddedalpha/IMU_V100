
#include <stdint.h>
#include "main.h"
#include "Console/Console.h"



int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();
	Console_Init(9600);


	for(;;)
	{

	}
}
