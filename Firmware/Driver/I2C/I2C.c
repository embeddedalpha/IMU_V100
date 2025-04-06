/*
 * I2C.c
 *
 *  Created on: Sep 25, 2024
 *      Author: kunal
 */


#include "I2C.h"


DMA_Config xI2C_TX;
DMA_Config xI2C_RX;

static void pin_setup(I2C_Config *config)
{
	if(config->Port == I2C1)
	{
		if(config->SCL_Pin == I2C_Configuration.Pin.__I2C1__.SCL.PB6) GPIO_Pin_Init(GPIOB, 6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.I2C_1);
		else if(config->SCL_Pin == I2C_Configuration.Pin.__I2C1__.SCL.PB8) GPIO_Pin_Init(GPIOB, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.I2C_1);

		if(config->SDA_Pin == I2C_Configuration.Pin.__I2C1__.SDA.PB7) GPIO_Pin_Init(GPIOB, 7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.I2C_1);
		else if(config->SDA_Pin == I2C_Configuration.Pin.__I2C1__.SDA.PB9) GPIO_Pin_Init(GPIOB, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.I2C_1);

	}
	else if(config->Port == I2C2)
	{
		if(config->SCL_Pin == I2C_Configuration.Pin.__I2C2__.SCL.PB10) GPIO_Pin_Init(GPIOB, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.I2C_2);
		if(config->SDA_Pin == I2C_Configuration.Pin.__I2C2__.SDA.PB11) GPIO_Pin_Init(GPIOB, 11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.I2C_2);
	}
	else if(config->Port == I2C3)
	{
		if(config->SCL_Pin == I2C_Configuration.Pin.__I2C3__.SCL.PA8) GPIO_Pin_Init(GPIOA, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.I2C_3);
		if(config->SDA_Pin == I2C_Configuration.Pin.__I2C3__.SDA.PC9) GPIO_Pin_Init(GPIOC, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.I2C_3);
	}
}

void I2C_Clock_Enable(I2C_Config *config)
{
	if(config->Port == I2C1)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_I2C1EN;
	}
	else if(config->Port == I2C2)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_I2C2EN;
	}
	else if(config->Port == I2C3)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_I2C3EN;
	}
}

void I2C_Clock_Disable(I2C_Config *config)
{
	if(config->Port == I2C1)
	{
		RCC -> APB1ENR &= ~RCC_APB1ENR_I2C1EN;
	}
	else if(config->Port == I2C2)
	{
		RCC -> APB1ENR &= ~RCC_APB1ENR_I2C2EN;
	}
	else if(config->Port == I2C3)
	{
		RCC -> APB1ENR &= ~RCC_APB1ENR_I2C3EN;
	}
}

void I2C_Reset(I2C_Config *config)
{
	config->Speed_Mode = I2C_Configuration.Speed_Mode.FM_Mode;
	config->Interrupts = I2C_Configuration.Interrupts.Disable;
	config->Mode = I2C_Configuration.Mode.Master;
	I2C_Clock_Disable(config);
}

void I2C_Init(I2C_Config *config)
{
	pin_setup(config);
	I2C_Clock_Enable(config);

	config->Port -> CR1 &= ~I2C_CR1_PE;
	config->Port -> CR1 |= I2C_CR1_SWRST | I2C_CR1_NOSTRETCH;
	config->Port -> CR1 &= ~I2C_CR1_SWRST;

	if(config -> Interrupts == I2C_Configuration.Interrupts.Disable)
	{
		config -> Port -> CR2 &= ~(I2C_CR2_ITBUFEN | I2C_CR2_ITERREN | I2C_CR2_ITEVTEN);
	}
	else
	{
		if(config->Interrupts == I2C_Configuration.Interrupts.Buffer)
		{
			config -> Port -> CR2 |= I2C_CR2_ITBUFEN;
		}
		if(config->Interrupts == I2C_Configuration.Interrupts.Error)
		{
			config -> Port -> CR2 |= I2C_CR2_ITERREN;
		}
		if(config->Interrupts == I2C_Configuration.Interrupts.Event)
		{
			config -> Port -> CR2 |= I2C_CR2_ITEVTEN;
		}
	}





	//CCR ==> [Tr + Tw]/(1/48000000)
	//TRISE ==> [Tr/(1/48000000)]

	if(config->Speed_Mode == I2C_Configuration.Speed_Mode.FM_Mode)
	{
		config->Port -> CR2 |= 30; //42MHz
		config->Port -> CCR = (1<<15) | (1<<14) | 5;
		config->Port -> TRISE = 30;
	}
	else
	{
		config-> Port  -> CR2 = 25;
		config->Port  -> CCR = 0x28;
		config->Port  -> TRISE = 0x8;
	}

	config -> Port -> CR1 |= I2C_CR1_NOSTRETCH;
	config -> Port -> CR1 |= I2C_CR1_PE;

}


int8_t I2C_Master_Start(I2C_Config *config)
{
	int time_out = 1000;
	config -> Port -> CR1 |= I2C_CR1_START;
	config -> Port -> CR1 |= I2C_CR1_START;
	while( !(config -> Port -> SR1 & I2C_SR1_SB))
	{
		if(time_out == 0)
		{
			return -1;
		}
		time_out--;
	}
	return 0;
}

void I2C_Master_Address(I2C_Config *config, uint8_t address, uint8_t read_write)
{
//	volatile int temp;
	config -> Port -> DR = address << 1  | read_write;
	while((config -> Port -> SR1 & 2) == 0){}
	while((config -> Port -> SR1 & 2))
	{
//		temp = config -> Port -> SR1;
//		temp = config -> Port -> SR2;
		(void)config->Port -> SR1;
		(void)config->Port -> SR2;
		if((config -> Port -> SR1 & 2) == 0)
		{
			break;
		}
	}
}


void I2C_Master_Send_Byte(I2C_Config *config, uint8_t data)
{
	while((config -> Port-> SR1 & 0x80) == 0){}
	config -> Port -> DR = data;
	while((config -> Port -> SR1 & 0x80) == 0){}
}

int I2C_Master_Receive_Byte(I2C_Config *config)
{
	volatile int temp;
	config -> Port -> CR1 |= I2C_CR1_ACK;
	while((config -> Port -> SR1 & I2C_SR1_RXNE) == 0){}
	temp = config -> Port -> DR;
	config -> Port -> CR1 &= ~I2C_CR1_ACK;
	return temp;
}



void I2C_Master_Send_Buffer(I2C_Config *config, uint8_t *data, int length)
{
	if(config->DMA_Control == I2C_Configuration.DMA_Control.TX_DMA_Enable)
	{
//		xI2C_TX.memory_address = (uint32_t)&data;
//		xI2C_TX.buffer_length = length;
//		xI2C_TX.peripheral_address = (uint32_t)&confi->DR;
//		DMA_Set_Target(&xI2C_TX);
//		DMA_Trigger(&xI2C_TX);
	}
	for(int i = 0; i < length; i++)
	{
		while((config -> Port -> SR1 & 0x80) == 0){}
		config -> Port -> DR = data[i];
		while((config -> Port -> SR1 & 0x80) == 0){}
	}
}

void I2C_Master_NACK(I2C_Config *config)
{
	config -> Port -> CR1 &= ~I2C_CR1_ACK;
}

void I2C_Master_ACK(I2C_Config *config)
{
	config -> Port -> CR1 |= I2C_CR1_ACK;
}

void I2C_Master_Stop(I2C_Config *config)
{
	config -> Port -> CR1 |= I2C_CR1_STOP;
}


void I2C_Master_Write_Register(I2C_Config *config, uint8_t device_address, uint8_t reg_address, uint8_t data)
{
	I2C_Master_Start(config);
	I2C_Master_Address(config, device_address,0);
	I2C_Master_Send_Byte(config, reg_address);
	I2C_Master_Send_Byte(config, data);
	I2C_Master_Stop(config);
}

int I2C_Master_Read_Register(I2C_Config *config, uint8_t device_address, uint8_t reg_address)
{
	volatile int temp;
	I2C_Master_Start(config);
	I2C_Master_Address(config, device_address, 0);
	I2C_Master_Send_Byte(config, reg_address);
	I2C_Master_Stop(config);
	I2C_Master_Start(config);
	I2C_Master_Address(config, device_address, 1);
	temp = I2C_Master_Receive_Byte(config);
	I2C_Master_Stop(config);
	return temp;
}

