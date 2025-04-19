
#include <stdint.h>
#include "main.h"
#include "Console/Console.h"
#include "I2C/I2C.h"
#include "GPIO/GPIO.h"
#include "MPU6050/MPU6050_Regs.h"
#include "Modbus/Modbus.h"
#include "App.h"

volatile uint16_t commSwitch = 0;
volatile bool commSelection = 0;


typedef enum IMUV100_States
{
	Compute_Data = 0,
	Process_Command,
	Send_Diagnostic_Data,

}IMUV100_States;

IMUV100_States State;

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
	mpu6050.Interrupts_Enable = I2C_Configuration.Interrupts_Enable.Disable;
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


	commSwitch = GPIO_Read_Pin(GPIOA, 7);

	if(commSwitch)
	{
		commSelection = 1; //CAN
	}
	else
	{
		commSelection = 0; //MODBUS
		IMUV100_Modbus_Comm_Setup();
	}

	for(;;)
	{
		switch (State) {
			case Compute_Data:
			{
				// Get Accelerometer Data



				// Get Gyroscope Data

				// Get Magnetometer Data

				// Get Barometer Data

				// Get GNSS Data

				// Compute Quaternions

				// Compute Euler Angles

				// Compute Linear Velocity

				// Compute Angular Velocity


				State = Process_Command;

			}
				break;

			case Process_Command:
			{

				if(commSelection)
				{
					IMUV100_CAN_Command_Process();
				}
				else
				{
					IMUV100_Modbus_Command_Process();
				}



			}
			break;

			case Send_Diagnostic_Data:
			{

			}
			break;
		}
	}
}
