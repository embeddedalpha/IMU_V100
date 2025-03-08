
#include <stdint.h>
#include "main.h"
#include "Console/Console.h"
#include "I2C/I2C.h"
#include "GPIO/GPIO.h"
#include "MPU6050/MPU6050_Regs.h"
#include "Modbus/Modbus.h"






I2C_Config mpu6050;

#define MPU6250_ADDRESS 0x68
#define who_am_i 0x75

volatile uint8_t data[12] ;
volatile float ACC[3], GYRO[3];

volatile bool mpu_data_ready_flag = 0;

void MPU6050_ISR(void)
{
	mpu_data_ready_flag = 1;
}

int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();
//	Console_Init(9600);



	mpu6050.Port = I2C1;
	mpu6050.Mode = I2C_Configuration.Mode.Master;
	mpu6050.Interrupts = I2C_Configuration.Interrupts.Disable;
	mpu6050.DMA_Control = I2C_Configuration.DMA_Control.RX_DMA_Enable;
	mpu6050.SCL_Pin = I2C_Configuration.Pin.__I2C1__.SCL.PB6;
	mpu6050.SDA_Pin = I2C_Configuration.Pin.__I2C1__.SDA.PB7;
	mpu6050.Speed_Mode = I2C_Configuration.Speed_Mode.FM_Mode;
	I2C_Init(&mpu6050);

	int temp = 0;
	temp = I2C_Read_Register(&mpu6050, MPU6250_ADDRESS, MPU6050_Registers.WHO_AM_I);
	(void)temp;


	I2C_Master_Write_Register(&mpu6050, MPU6250_ADDRESS, MPU6050_Registers.PWR_MGMT_1, 0x01);
	I2C_Master_Write_Register(&mpu6050, MPU6250_ADDRESS, MPU6050_Registers.PWR_MGMT_2, 0x00);
	I2C_Master_Write_Register(&mpu6050, MPU6250_ADDRESS, MPU6050_Registers.CONFIG, 0x03); //4G
	I2C_Master_Write_Register(&mpu6050, MPU6250_ADDRESS, MPU6050_Registers.SMPLRT_DIV, 250); //500 DPS
	I2C_Master_Write_Register(&mpu6050, MPU6250_ADDRESS, MPU6050_Registers.GYRO_CONFIG, 0x00);
	I2C_Master_Write_Register(&mpu6050, MPU6250_ADDRESS, MPU6050_Registers.ACCEL_CONFIG, 0x00);

	I2C_Master_Write_Register(&mpu6050, MPU6250_ADDRESS, MPU6050_Registers.INT_ENABLE, 0x01);
	I2C_Master_Write_Register(&mpu6050, MPU6250_ADDRESS, MPU6050_Registers.USER_CTRL, 0x00);

	GPIO_Pin_Init(GPIOB, 4,
			GPIO_Configuration.Mode.Input,
			GPIO_Configuration.Output_Type.None,
			GPIO_Configuration.Speed.None,
			GPIO_Configuration.Pull.None,
			GPIO_Configuration.Alternate_Functions.None);
	GPIO_Interrupt_Setup(GPIOB,4, GPIO_Configuration.Interrupt_Edge.RISING_EDGE, 0, MPU6050_ISR);

	GPIO_Pin_Init(GPIOB, 5,
			GPIO_Configuration.Mode.General_Purpose_Output,
			GPIO_Configuration.Output_Type.Push_Pull,
			GPIO_Configuration.Speed.Very_High_Speed,
			GPIO_Configuration.Pull.None,
			GPIO_Configuration.Alternate_Functions.None);

	for(;;)
	{
		if(mpu_data_ready_flag == 1)
		{
			I2C_Master_Read_Registers_Bulk(&mpu6050, MPU6250_ADDRESS, MPU6050_Registers.ACCEL_XOUT_H, &data, 12);
			GPIO_Pin_High(GPIOB, 5);
			ACC[0] = ((data[0] << 8) | data[1])/16384.0 ;
			ACC[1] = ((data[2] << 8) | data[3])/16384.0 ;
			ACC[2] = ((data[4] << 8) | data[5])/16384.0  ;

			GYRO[0] = ((data[6] << 8) | data[7])/131.0 ;
			GYRO[1] = ((data[8] << 8) | data[9])/131.0 ;
			GYRO[2] = ((data[10] << 8) | data[11])/131.0  ;
			GPIO_Pin_Low(GPIOB, 5);
			mpu_data_ready_flag = 0;
		}
	}
}
