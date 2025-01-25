
#include <stdint.h>
#include "main.h"
#include "Console/Console.h"
#include "I2C/I2C.h"


I2C_Config mpu6050;

#define mpu6050_address 0x68
#define who_am_i 0x75

int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();
	Console_Init(9600);

	mpu6050.Port = I2C1;
	mpu6050.Mode = I2C_Configuration.Mode.Master;
	mpu6050.Interrupts = I2C_Configuration.Interrupts.Disable;
	mpu6050.DMA_Control = I2C_Configuration.DMA_Control.Disable;
	mpu6050.SCL_Pin = I2C_Configuration.Pin.__I2C1__.SCL.PB6;
	mpu6050.SDA_Pin = I2C_Configuration.Pin.__I2C1__.SDA.PB7;
	mpu6050.Speed_Mode = I2C_Configuration.Speed_Mode.FM_Mode;
	I2C_Init(&mpu6050);








	for(;;)
	{
		I2C_Master_Read_Register(&mpu6050, mpu6050_address, who_am_i);
		Delay_s(1);


	}
}
