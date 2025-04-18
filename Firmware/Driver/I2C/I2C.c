/*
 * I2C.c
 *
 *  Created on: Sep 25, 2024
 *      Author: kunal
 */


#include "I2C.h"


DMA_Config xI2C1_TX;
DMA_Config xI2C2_TX;
DMA_Config xI2C3_TX;

DMA_Config xI2C1_RX;
DMA_Config xI2C2_RX;
DMA_Config xI2C3_RX;


void I2C1_DMA_Config(uint8_t *pBuffer, uint32_t len)
{
    // Enable clock for DMA1 if not already enabled
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

    // 1. Disable DMA1 Stream0 (if enabled)
    if (DMA1_Stream5->CR & DMA_SxCR_EN)
    {
    	DMA1_Stream5->CR &= ~DMA_SxCR_EN;
        while (DMA1_Stream5->CR & DMA_SxCR_EN);  // Wait until disabled
    }

    // 2. Clear all interrupt flags for Stream0
    DMA1->HIFCR |= DMA_HIFCR_CTCIF5  | DMA_HIFCR_CHTIF5 |
                     DMA_HIFCR_CTEIF5  | DMA_HIFCR_CDMEIF5 |
                     DMA_HIFCR_CFEIF5;

    // 3. Set peripheral address: I2C1 data register
    DMA1_Stream5->PAR = (uint32_t)&I2C1->DR;
    // 4. Set memory address: pointer to our receive buffer
    DMA1_Stream5->M0AR = (uint32_t)pBuffer;
    // 5. Set the number of data items to transfer
    DMA1_Stream5->NDTR = len;

    // 6. Configure DMA stream:
    //    - Select Channel 1 (bits 27:25 = 001)
    //    - Set transfer direction: Peripheral-to-Memory (DIR = 0)
    //    - Enable Memory Increment Mode (MINC)
    //    - Data size: 8-bit for both peripheral and memory (default = 00)
    //    - (Optional) Enable Transfer Complete Interrupt (TCIE) if using interrupts.
    DMA1_Stream5->CR = 0;  // Clear previous settings
    DMA1_Stream5->CR |= (1 << 25);   // Channel selection: Channel 1
    DMA1_Stream5->CR |= DMA_SxCR_MINC; // Memory increment mode
    // (Other bits such as priority and FIFO settings can be configured as needed.)

    // 7. Finally, enable the DMA stream
    DMA1_Stream5->CR |= DMA_SxCR_EN;
}



#define I2C_TIMEOUT  0xFFFF

static void pin_setup(I2C_Config *config)
{
	if(config->Port == I2C1)
	{
		if(config->SCL_Pin == I2C_Configuration.Pin.__I2C1__.SCL.PB6) GPIO_Pin_Init(GPIOB, 6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.I2C_1);
		else if(config->SCL_Pin == I2C_Configuration.Pin.__I2C1__.SCL.PB8) GPIO_Pin_Init(GPIOB, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.I2C_1);

		if(config->SDA_Pin == I2C_Configuration.Pin.__I2C1__.SDA.PB7) GPIO_Pin_Init(GPIOB, 7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.I2C_1);
		else if(config->SDA_Pin == I2C_Configuration.Pin.__I2C1__.SDA.PB9) GPIO_Pin_Init(GPIOB, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.I2C_1);

	}
	else if(config->Port == I2C2)
	{
		if(config->SCL_Pin == I2C_Configuration.Pin.__I2C2__.SCL.PB10) GPIO_Pin_Init(GPIOB, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.I2C_2);
		if(config->SDA_Pin == I2C_Configuration.Pin.__I2C2__.SDA.PB11) GPIO_Pin_Init(GPIOB, 11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.I2C_2);
	}
	else if(config->Port == I2C3)
	{
		if(config->SCL_Pin == I2C_Configuration.Pin.__I2C3__.SCL.PA8) GPIO_Pin_Init(GPIOA, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.I2C_3);
		if(config->SDA_Pin == I2C_Configuration.Pin.__I2C3__.SDA.PC9) GPIO_Pin_Init(GPIOC, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Open_Drain, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.I2C_3);
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

	config -> Port -> CR1 &= ~I2C_CR1_PE;
	config -> Port -> CR1 |= I2C_CR1_SWRST;
	config->Port -> CR1 &= ~I2C_CR1_SWRST;
	config -> Port -> CR1 &= ~I2C_CR1_NOSTRETCH;


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
		config->Port -> CR2 |= 42; //42MHz
		config->Port -> CCR = (0<<15) | (1<<14) | 52;
		config->Port -> TRISE = 13;
	}
	else
	{
		config-> Port  -> CR2 = 42;
		config->Port -> CCR = (0<<15) | (1<<14) | 210;
		config->Port  -> TRISE = 43;
	}

	if(config -> DMA_Control == I2C_Configuration.DMA_Control.RX_DMA_Enable)
	{
		config -> Port -> CR2 |= I2C_CR2_LAST;

		if(config->Port == I2C1)
		{
//			config -> Port -> CR2 |= I2C_CR2_DMAEN;
			xI2C1_RX.Request = DMA_Configuration.Request.I2C1_RX;
			xI2C1_RX.circular_mode = DMA_Configuration.Circular_Mode.Disable;
			xI2C1_RX.flow_control = DMA_Configuration.Flow_Control.DMA_Control;
			xI2C1_RX.memory_data_size = DMA_Configuration.Memory_Data_Size.byte;
			xI2C1_RX.memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;
			xI2C1_RX.peripheral_data_size = DMA_Configuration.Peripheral_Data_Size.byte;
			xI2C1_RX.transfer_direction = DMA_Configuration.Transfer_Direction.Peripheral_to_memory;
			xI2C1_RX.priority_level = DMA_Configuration.Priority_Level.Very_high;
			DMA_Init(&xI2C1_RX);

		}

		else if(config->Port == I2C2)
		{
			xI2C2_RX.Request = DMA_Configuration.Request.I2C2_RX;
			xI2C2_RX.circular_mode = DMA_Configuration.Circular_Mode.Disable;
			xI2C2_RX.flow_control = DMA_Configuration.Flow_Control.DMA_Control;
			xI2C2_RX.memory_data_size = DMA_Configuration.Memory_Data_Size.byte;
			xI2C2_RX.memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;
			xI2C2_RX.peripheral_data_size = DMA_Configuration.Peripheral_Data_Size.byte;
			xI2C2_RX.peripheral_pointer_increment = DMA_Configuration.Peripheral_Pointer_Increment.Enable;
			xI2C2_RX.transfer_direction = DMA_Configuration.Transfer_Direction.Peripheral_to_memory;
			xI2C2_RX.priority_level = DMA_Configuration.Priority_Level.Very_high;
			DMA_Init(&xI2C2_RX);
		}

		else if(config->Port == I2C3)
		{
			xI2C3_RX.Request = DMA_Configuration.Request.I2C3_RX;
			xI2C3_RX.circular_mode = DMA_Configuration.Circular_Mode.Disable;
			xI2C3_RX.flow_control = DMA_Configuration.Flow_Control.DMA_Control;
			xI2C3_RX.memory_data_size = DMA_Configuration.Memory_Data_Size.byte;
			xI2C3_RX.memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;
			xI2C3_RX.peripheral_data_size = DMA_Configuration.Peripheral_Data_Size.byte;
			xI2C3_RX.peripheral_pointer_increment = DMA_Configuration.Peripheral_Pointer_Increment.Enable;
			xI2C3_RX.transfer_direction = DMA_Configuration.Transfer_Direction.Peripheral_to_memory;
			xI2C3_RX.priority_level = DMA_Configuration.Priority_Level.Very_high;
			DMA_Init(&xI2C3_RX);
		}

	}

	config -> Port -> CR1 |= I2C_CR1_PE;

}


int8_t I2C_Master_Start(I2C_Config *config)
{
	int time_out = 1000;

	while(config -> Port -> SR2 & I2C_SR2_BUSY){
		if(time_out == 0)
		{
			return -1;
		}
		time_out--;
	}

	time_out = 1000;
	config -> Port -> CR1 |= I2C_CR1_START;
//	config -> Port -> CR1 |= I2C_CR1_START;
	while( !(config -> Port -> SR1 & I2C_SR1_SB))
	{
		if(time_out == 0)
		{
			return -1;
		}
		time_out--;
	}
	(void)config ->  Port -> SR1;
	return 0;
}

void I2C_Master_Address(I2C_Config *config, uint8_t address, uint8_t read_write)
{
	config -> Port -> DR = address << 1  | read_write;
	while((config -> Port -> SR1 & I2C_SR1_ADDR) == 0){;}
	while((config -> Port -> SR1 & 2))
	{
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
		if(config->Port == I2C1)
		{
			xI2C1_RX.memory_address = (uint32_t)&data[0];
			xI2C1_RX.peripheral_address = (uint32_t)&config->Port->DR;
			xI2C1_RX.buffer_length = length;
			DMA_Set_Target(&xI2C1_RX);
			DMA_Set_Trigger(&xI2C1_RX);
		}
		else if(config->Port == I2C2)
		{
			xI2C2_RX.memory_address = (uint32_t)&data[0];
			xI2C2_RX.peripheral_address = (uint32_t)&config->Port->DR;
			DMA_Set_Target(&xI2C2_RX);
			DMA_Set_Trigger(&xI2C2_RX);
		}
		else if(config->Port == I2C3)
		{
			xI2C3_RX.memory_address = (uint32_t)&data[0];
			xI2C3_RX.peripheral_address = (uint32_t)&config->Port->DR;
			DMA_Set_Target(&xI2C3_RX);
			DMA_Set_Trigger(&xI2C3_RX);
		}
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




int I2C_Read_Register(I2C_Config *config, uint16_t device_address, uint8_t reg_address)
{
    volatile uint32_t timeout;
    uint8_t data;

    /* 1) Wait until I2C is not busy --------------------------------------- */
    timeout = I2C_TIMEOUT;
    while ( (config -> Port -> SR2 & I2C_SR2_BUSY) != 0 )
    {
        if (--timeout == 0)
        {
            // Handle bus busy error
            return -1;
        }
    }

    config -> Port -> CR1 |= I2C_CR1_START;
    timeout = I2C_TIMEOUT;
	while ( (config -> Port -> SR1 & I2C_SR1_SB) == 0 )
	{
		if (--timeout == 0)
		{
			// START not generated in time
			return -1;
		}
	}

	config -> Port -> DR = (device_address << 1);
	timeout = I2C_TIMEOUT;
	while ( (config -> Port -> SR1 & I2C_SR1_ADDR) == 0 )
	{
		if (--timeout == 0)
		{
			// ADDR not set in time
			return -1;
		}
		// Check for error flags (NACK, bus errors, etc.)
		if (config -> Port -> SR1 & (I2C_SR1_AF | I2C_SR1_BERR | I2C_SR1_ARLO | I2C_SR1_OVR))
		{
			// Some I2C error occurred
			return -1;
		}
	}

	(void) config -> Port ->SR1;
	(void) config -> Port ->SR2;

	config -> Port ->DR = reg_address;

	timeout = I2C_TIMEOUT;
	while ( (config -> Port ->SR1 & I2C_SR1_TXE) == 0 )
	{
		if (--timeout == 0)
		{
			// TXE not set in time
			return -1;
		}
		if (config -> Port ->SR1 & (I2C_SR1_AF | I2C_SR1_BERR | I2C_SR1_ARLO | I2C_SR1_OVR))
		{
			// Some I2C error occurred
			return -1;
		}
	}

	config -> Port ->CR1 |= I2C_CR1_START;

	timeout = I2C_TIMEOUT;
	while ( (config -> Port ->SR1 & I2C_SR1_SB) == 0 )
	{
		if (--timeout == 0)
		{
			// SB not set in time
			return -1;
		}
	}

	config -> Port ->DR = (device_address << 1) | 0x01; // LSB=1 for read

	    /* 12) Wait for ADDR flag --------------------------------------------- */
	    timeout = I2C_TIMEOUT;
	    while ( (config -> Port ->SR1 & I2C_SR1_ADDR) == 0 )
	    {
	        if (--timeout == 0)
	        {
	            // ADDR not set in time
	            return -1;
	        }
	        // Check for error flags
	        if (config -> Port ->SR1 & (I2C_SR1_AF | I2C_SR1_BERR | I2C_SR1_ARLO | I2C_SR1_OVR))
	        {
	            return -1;
	        }
	    }

	    config -> Port ->CR1 &= ~I2C_CR1_ACK;       // Disable ACK for single byte read
	       (void) config -> Port ->SR1;               // Clear ADDR by reading SR1
	       (void) config -> Port ->SR2;
	       config -> Port ->CR1 |= I2C_CR1_STOP;      // Generate STOP

	       /* 13) Wait until RXNE (data received) -------------------------------- */
	       timeout = I2C_TIMEOUT;
	       while ( (config -> Port ->SR1 & I2C_SR1_RXNE) == 0 )
	       {
	           if (--timeout == 0)
	           {
	               // RXNE not set in time
	               return -1;
	           }
	           // Check for errors
	           if (config -> Port ->SR1 & (I2C_SR1_AF | I2C_SR1_BERR | I2C_SR1_ARLO | I2C_SR1_OVR))
	           {
	               return -1;
	           }
	       }

	       /* 14) Read the received byte ----------------------------------------- */
	       data = (uint8_t) config -> Port ->DR;

	       /* 15) Re-enable ACK (so next transfers can continue normally) -------- */
	       config -> Port ->CR1 |= I2C_CR1_ACK;

	       return data;

}

int I2C_Master_Read_Registers_Bulk(I2C_Config *config, uint8_t device_address, uint8_t reg_address, uint8_t *data, uint16_t length)
{

	if(config->Port == I2C1)
	{
		xI2C1_RX.memory_address = (uint32_t)&data[0];
		xI2C1_RX.peripheral_address = (uint32_t)&config->Port->DR;
		xI2C1_RX.buffer_length = length;
		DMA_Set_Target(&xI2C1_RX);
		DMA_Set_Trigger(&xI2C1_RX);
	}
	else if(config->Port == I2C2)
	{
		xI2C2_RX.memory_address = (uint32_t)&data[0];
		xI2C2_RX.peripheral_address = (uint32_t)&config->Port->DR;
		xI2C2_RX.buffer_length = length;
		DMA_Set_Target(&xI2C2_RX);
		DMA_Set_Trigger(&xI2C2_RX);
	}
	else if(config->Port == I2C3)
	{
		xI2C3_RX.memory_address = (uint32_t)&data[0];
		xI2C3_RX.peripheral_address = (uint32_t)&config->Port->DR;
		xI2C3_RX.buffer_length = length;
		DMA_Set_Target(&xI2C3_RX);
		DMA_Set_Trigger(&xI2C3_RX);
	}
	else
	{
		return -1;
	}


	config->Port->CR2 |= I2C_CR2_DMAEN;
	I2C_Master_Start(config);
	I2C_Master_Address(config, device_address, 0);
	I2C_Master_Send_Byte(config, reg_address);
	I2C_Master_Stop(config);
	I2C_Master_Start(config);
	I2C_Master_Address(config, device_address, 1);

	if(config->Port == I2C1)
	{
		while (!(xI2C1_RX.Request.Controller->HISR & DMA_HISR_TCIF5));  // Wait for transfer complete flag (Stream0)
		xI2C1_RX.Request.Controller->HIFCR |= DMA_HIFCR_CTCIF5;
	}
	else if(config->Port == I2C2)
	{
		while (!(xI2C2_RX.Request.Controller->HISR & DMA_HISR_TCIF5));  // Wait for transfer complete flag (Stream0)
		xI2C2_RX.Request.Controller->HIFCR |= DMA_HIFCR_CTCIF5;
	}
	else if(config->Port == I2C3)
	{
		while (!(xI2C3_RX.Request.Controller->HISR & DMA_HISR_TCIF5));  // Wait for transfer complete flag (Stream0)
		xI2C3_RX.Request.Controller->HIFCR |= DMA_HIFCR_CTCIF5;
	}


	config->Port->CR2 &= ~I2C_CR2_DMAEN;
	I2C_Master_Stop(config);

	return 1;
}

//void I2C_Master_Read_Registers_Bulk(I2C_Config *config, uint8_t device_address, uint8_t reg_address,volatile uint8_t *data, uint16_t length)
//{
//
//	I2C1_DMA_Config(data, length);
//
//	I2C1->CR2 |= I2C_CR2_DMAEN;
//
//	I2C_Master_Start(config);
//
//	I2C_Master_Address(config, device_address, 0);
//	I2C_Master_Send_Byte(config, reg_address);
//	I2C_Master_Stop(config);
//	I2C_Master_Start(config);
//	I2C_Master_Address(config, device_address, 1);
//	while (!(DMA1->HISR & DMA_HISR_TCIF5));  // Wait for transfer complete flag (Stream0)
//
//	    // 7. Clear the DMA transfer complete flag.
//	    DMA1->HIFCR |= DMA_HIFCR_CTCIF5;
//	    I2C1->CR2 &= ~I2C_CR2_DMAEN;
//
//	    // 9. Generate the STOP condition to end the I2C communication.
//	    I2C_Master_Stop(config);
//
//
//}
