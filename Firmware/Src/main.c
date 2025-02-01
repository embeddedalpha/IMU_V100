
#include <stdint.h>
#include "main.h"
#include "Console/Console.h"
#include "I2C/I2C.h"
#include "GPIO/GPIO.h"
#include "MPU6050/MPU6050_Regs.h"

I2C_Config mpu6050;

#define mpu6050_address 0x68
#define who_am_i 0x75

volatile int acceleration[6], gyro[6] ;
volatile float ACC[3], GYRO[3];

volatile bool mpu_data_ready_flag = 0;

void MPU6050_ISR(void)
{
//	int temp = 0;
//
////	temp = I2C_Read_Register(&mpu6050, mpu6050_address, INT_STATUS);
//
//	if(temp & 0x01)
//	{
		mpu_data_ready_flag = 1;
//	}

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
	temp = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.WHO_AM_I);



	I2C_Master_Write_Register(&mpu6050, mpu6050_address, MPU6050_Registers.PWR_MGMT_1, 0x01);
	I2C_Master_Write_Register(&mpu6050, mpu6050_address, MPU6050_Registers.PWR_MGMT_2, 0x00);
	I2C_Master_Write_Register(&mpu6050, mpu6050_address, MPU6050_Registers.CONFIG, 0x03); //4G
	I2C_Master_Write_Register(&mpu6050, mpu6050_address, MPU6050_Registers.SMPLRT_DIV, 7); //500 DPS
	I2C_Master_Write_Register(&mpu6050, mpu6050_address, MPU6050_Registers.GYRO_CONFIG, 0x00);
	I2C_Master_Write_Register(&mpu6050, mpu6050_address, MPU6050_Registers.ACCEL_CONFIG, 0x00);

	I2C_Master_Write_Register(&mpu6050, mpu6050_address, MPU6050_Registers.INT_ENABLE, 0x01);
	I2C_Master_Write_Register(&mpu6050, mpu6050_address, MPU6050_Registers.USER_CTRL, 0x00);

	for(;;)
	{
//		if(mpu_data_ready_flag == 1)
//		{

//			I2C_Read_Registers_Bulk(&mpu6050, mpu6050_address, ACCEL_XOUT_H, &acceleration, 6);
//			I2C_Read_Registers_Bulk(&mpu6050, mpu6050_address, GYRO_XOUT_H, &gyro, 6);
			acceleration[0] = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.ACCEL_XOUT_H);
			acceleration[1] = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.ACCEL_XOUT_L);
			acceleration[2] = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.ACCEL_YOUT_H);
			acceleration[3] = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.ACCEL_YOUT_L);
			acceleration[4] = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.ACCEL_ZOUT_H);
			acceleration[5] = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.ACCEL_ZOUT_L);

			gyro[0] = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.GYRO_XOUT_H);
			gyro[1] = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.GYRO_XOUT_L);
			gyro[2] = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.GYRO_YOUT_H);
			gyro[3] = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.GYRO_YOUT_L);
			gyro[4] = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.GYRO_ZOUT_H);
			gyro[5] = I2C_Read_Register(&mpu6050, mpu6050_address, MPU6050_Registers.GYRO_ZOUT_L);

			ACC[0] = ((acceleration[0] << 8) | acceleration[1])/16384.0 ;
			ACC[1] = ((acceleration[2] << 8) | acceleration[3])/16384.0 ;
			ACC[2] = ((acceleration[4] << 8) | acceleration[5])/16384.0  ;

			GYRO[0] = ((gyro[0] << 8) | gyro[1])/250.0 ;
			GYRO[1] = ((gyro[2] << 8) | gyro[3])/250.0 ;
			GYRO[2] = ((gyro[4] << 8) | gyro[5])/250.0  ;

			mpu_data_ready_flag = 0;
//		}






	}
}
