/**
 * @file DMA.c
 * @brief DMA Driver Implementation for STM32F407VGT6
 *
 * This file provides the implementation of the GPIO driver for the STM32F407VGT6 microcontroller.
 * It includes functions to initialize DMA, handle DMA interrupts, configure DMA streams,
 * and manage memory-to-memory transfers.
 *
 * @version 1.0
 * @date 2024-08-21
 *
 * @author Your Name
 * @copyright Copyright (c) 2024
 */

#include "DMA.h"


DMA_Config *__DMA1_Stream0_Config__;
DMA_Config *__DMA1_Stream1_Config__;
DMA_Config *__DMA1_Stream2_Config__;
DMA_Config *__DMA1_Stream3_Config__;
DMA_Config *__DMA1_Stream4_Config__;
DMA_Config *__DMA1_Stream5_Config__;
DMA_Config *__DMA1_Stream6_Config__;
DMA_Config *__DMA1_Stream7_Config__;

DMA_Config *__DMA2_Stream0_Config__;
DMA_Config *__DMA2_Stream1_Config__;
DMA_Config *__DMA2_Stream2_Config__;
DMA_Config *__DMA2_Stream3_Config__;
DMA_Config *__DMA2_Stream4_Config__;
DMA_Config *__DMA2_Stream5_Config__;
DMA_Config *__DMA2_Stream6_Config__;
DMA_Config *__DMA2_Stream7_Config__;



volatile uint32_t DMA_LISR = 0;
volatile uint32_t DMA_HISR = 0;


void DMA1_Stream0_IRQHandler(void)
{
	DMA_LISR = DMA1 -> LISR;

	if(DMA_LISR & DMA_LISR_FEIF0)
	{
	    if (__DMA1_Stream0_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA1_Stream0_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CFEIF0;
	    }
	}

	if(DMA_LISR & DMA_LISR_DMEIF0)
	{
	    if (__DMA1_Stream0_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA1_Stream0_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CDMEIF0;
	    }
	}

	if(DMA_LISR & DMA_LISR_TEIF0)
	{
	    if (__DMA1_Stream0_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA1_Stream0_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CTEIF0;
	    }
	}

	if(DMA_LISR & DMA_LISR_HTIF0)
	{
	    if (__DMA1_Stream0_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA1_Stream0_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CHTIF0;

	    	if(__DMA1_Stream0_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream0_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream0_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream0_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_LISR & DMA_LISR_TCIF0)
	{
	    if (__DMA1_Stream0_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA1_Stream0_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CTCIF0;

	    	if(__DMA1_Stream0_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream0_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream0_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream0_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}

void DMA1_Stream1_IRQHandler(void)
{
	DMA_LISR = DMA1 -> LISR;

	if(DMA_LISR & DMA_LISR_FEIF1)
	{
	    if (__DMA1_Stream1_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA1_Stream1_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CFEIF1;
	    }
	}

	if(DMA_LISR & DMA_LISR_DMEIF1)
	{
	    if (__DMA1_Stream1_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA1_Stream1_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CDMEIF1;
	    }
	}

	if(DMA_LISR & DMA_LISR_TEIF1)
	{
	    if (__DMA1_Stream1_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA1_Stream1_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CTEIF1;
	    }
	}

	if(DMA_LISR & DMA_LISR_HTIF1)
	{
	    if (__DMA1_Stream1_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA1_Stream1_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CHTIF1;

	    	if(__DMA1_Stream1_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream1_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream1_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream1_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_LISR & DMA_LISR_TCIF1)
	{
	    if (__DMA1_Stream1_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA1_Stream1_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CTCIF1;

	    	if(__DMA1_Stream1_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream1_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream1_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream1_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}


void DMA1_Stream2_IRQHandler(void)
{
	DMA_LISR = DMA1 -> LISR;

	if(DMA_LISR & DMA_LISR_FEIF2)
	{
	    if (__DMA1_Stream2_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA1_Stream2_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CFEIF2;
	    }
	}

	if(DMA_LISR & DMA_LISR_DMEIF2)
	{
	    if (__DMA1_Stream2_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA1_Stream2_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CDMEIF2;
	    }
	}

	if(DMA_LISR & DMA_LISR_TEIF2)
	{
	    if (__DMA1_Stream2_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA1_Stream2_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CTEIF2;
	    }
	}

	if(DMA_LISR & DMA_LISR_HTIF2)
	{
	    if (__DMA1_Stream2_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA1_Stream2_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CHTIF2;

	    	if(__DMA1_Stream2_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream2_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream2_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream2_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_LISR & DMA_LISR_TCIF2)
	{
	    if (__DMA1_Stream2_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA1_Stream2_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CTCIF2;

	    	if(__DMA1_Stream2_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream2_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream2_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream2_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}

void DMA1_Stream3_IRQHandler(void)
{
	DMA_LISR = DMA1 -> LISR;

	if(DMA_LISR & DMA_LISR_FEIF3)
	{
	    if (__DMA1_Stream3_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA1_Stream3_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CFEIF3;
	    }
	}

	if(DMA_LISR & DMA_LISR_DMEIF3)
	{
	    if (__DMA1_Stream3_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA1_Stream3_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CDMEIF3;
	    }
	}

	if(DMA_LISR & DMA_LISR_TEIF3)
	{
	    if (__DMA1_Stream3_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA1_Stream3_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CTEIF3;
	    }
	}

	if(DMA_LISR & DMA_LISR_HTIF3)
	{
	    if (__DMA1_Stream3_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA1_Stream3_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CHTIF3;

	    	if(__DMA1_Stream3_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream3_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream3_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream3_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_LISR & DMA_LISR_TCIF3)
	{
	    if (__DMA1_Stream3_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA1_Stream3_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> LIFCR |= DMA_LIFCR_CTCIF3;

	    	if(__DMA1_Stream3_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream3_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream3_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream3_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}

void DMA1_Stream4_IRQHandler(void)
{
	DMA_HISR = DMA1 -> HISR;

	if(DMA_HISR & DMA_HISR_FEIF4)
	{
	    if (__DMA1_Stream4_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA1_Stream4_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA1 -> LIFCR |= DMA_HIFCR_CFEIF5;
	    }
	}

	if(DMA_HISR & DMA_HISR_DMEIF4)
	{
	    if (__DMA1_Stream4_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA1_Stream4_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CDMEIF4;
	    }
	}

	if(DMA_HISR & DMA_HISR_TEIF4)
	{
	    if (__DMA1_Stream4_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA1_Stream4_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CTEIF4;
	    }
	}

	if(DMA_HISR & DMA_HISR_HTIF4)
	{
	    if (__DMA1_Stream4_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA1_Stream4_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CHTIF4;

	    	if(__DMA1_Stream4_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream4_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream4_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream4_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_HISR & DMA_HISR_TCIF4)
	{
	    if (__DMA1_Stream4_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA1_Stream4_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CTCIF4;

	    	if(__DMA1_Stream4_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream4_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream4_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream4_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}




void DMA1_Stream5_IRQHandler(void)
{
	DMA_HISR = DMA1 -> HISR;

	if(DMA_HISR & DMA_HISR_FEIF5)
	{
	    if (__DMA1_Stream5_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA1_Stream5_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CFEIF5;
	    }
	}

	if(DMA_HISR & DMA_HISR_DMEIF5)
	{
	    if (__DMA1_Stream5_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA1_Stream5_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CDMEIF5;
	    }
	}

	if(DMA_HISR & DMA_HISR_TEIF5)
	{
	    if (__DMA1_Stream5_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA1_Stream5_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CTEIF5;
	    }
	}

	if(DMA_HISR & DMA_HISR_HTIF5)
	{
	    if (__DMA1_Stream5_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA1_Stream5_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CHTIF5;

	    	if(__DMA1_Stream5_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream5_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream5_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream5_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_HISR & DMA_HISR_TCIF5)
	{
	    if (__DMA1_Stream5_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA1_Stream5_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CTCIF5;

	    	if(__DMA1_Stream5_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream5_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream5_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream5_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}



void DMA1_Stream6_IRQHandler(void)
{
	DMA_HISR = DMA1 -> HISR;

	if(DMA_HISR & DMA_HISR_FEIF6)
	{
	    if (__DMA1_Stream6_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA1_Stream6_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CFEIF6;
	    }
	}

	if(DMA_HISR & DMA_HISR_DMEIF6)
	{
	    if (__DMA1_Stream6_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA1_Stream6_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CDMEIF6;
	    }
	}

	if(DMA_HISR & DMA_HISR_TEIF6)
	{
	    if (__DMA1_Stream6_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA1_Stream6_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CTEIF6;
	    }
	}

	if(DMA_HISR & DMA_HISR_HTIF6)
	{
	    if (__DMA1_Stream6_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA1_Stream6_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CHTIF6;

	    	if(__DMA1_Stream6_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream6_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream6_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream6_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_HISR & DMA_HISR_TCIF6)
	{
	    if (__DMA1_Stream6_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA1_Stream6_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CTCIF6;

	    	if(__DMA1_Stream6_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream6_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream6_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream6_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}


void DMA1_Stream7_IRQHandler(void)
{
	DMA_HISR = DMA1 -> HISR;

	if(DMA_HISR & DMA_HISR_FEIF7)
	{
	    if (__DMA1_Stream7_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA1_Stream7_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CFEIF7;
	    }
	}

	if(DMA_HISR & DMA_HISR_DMEIF7)
	{
	    if (__DMA1_Stream7_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA1_Stream7_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CDMEIF7;
	    }
	}

	if(DMA_HISR & DMA_HISR_TEIF7)
	{
	    if (__DMA1_Stream7_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA1_Stream7_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CTEIF7;
	    }
	}

	if(DMA_HISR & DMA_HISR_HTIF7)
	{
	    if (__DMA1_Stream7_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA1_Stream7_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CHTIF7;

	    	if(__DMA1_Stream7_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream7_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream7_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream7_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_HISR & DMA_HISR_TCIF7)
	{
	    if (__DMA1_Stream7_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA1_Stream7_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA1 -> HIFCR |= DMA_HIFCR_CTCIF7;

	    	if(__DMA1_Stream7_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA1_Stream7_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA1_Stream7_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA1_Stream7_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}

void DMA2_Stream0_IRQHandler(void)
{
	DMA_LISR = DMA2 -> LISR;

	if(DMA_LISR & DMA_LISR_FEIF0)
	{
	    if (__DMA2_Stream0_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA2_Stream0_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CFEIF0;
	    }
	}

	if(DMA_LISR & DMA_LISR_DMEIF0)
	{
	    if (__DMA2_Stream0_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA2_Stream0_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CDMEIF0;
	    }
	}

	if(DMA_LISR & DMA_LISR_TEIF0)
	{
	    if (__DMA2_Stream0_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA2_Stream0_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CTEIF0;
	    }
	}

	if(DMA_LISR & DMA_LISR_HTIF0)
	{
	    if (__DMA2_Stream0_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA2_Stream0_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CHTIF0;

	    	if(__DMA2_Stream0_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream0_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream0_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream0_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_LISR & DMA_LISR_TCIF0)
	{
	    if (__DMA2_Stream0_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA2_Stream0_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CTCIF0;

	    	if(__DMA2_Stream0_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream0_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream0_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream0_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}

void DMA2_Stream1_IRQHandler(void)
{
	DMA_LISR = DMA2 -> LISR;

	if(DMA_LISR & DMA_LISR_FEIF1)
	{
	    if (__DMA2_Stream1_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA2_Stream1_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CFEIF1;
	    }
	}

	if(DMA_LISR & DMA_LISR_DMEIF1)
	{
	    if (__DMA2_Stream1_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA2_Stream1_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CDMEIF1;
	    }
	}

	if(DMA_LISR & DMA_LISR_TEIF1)
	{
	    if (__DMA2_Stream1_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA2_Stream1_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CTEIF1;
	    }
	}

	if(DMA_LISR & DMA_LISR_HTIF1)
	{
	    if (__DMA2_Stream1_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA2_Stream1_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CHTIF1;

	    	if(__DMA2_Stream1_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream1_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream1_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream1_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_LISR & DMA_LISR_TCIF1)
	{
	    if (__DMA2_Stream1_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA2_Stream1_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CTCIF1;

	    	if(__DMA2_Stream1_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream1_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream1_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream1_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}


void DMA2_Stream2_IRQHandler(void)
{
	DMA_LISR = DMA2 -> LISR;

	if(DMA_LISR & DMA_LISR_FEIF2)
	{
	    if (__DMA2_Stream2_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA2_Stream2_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CFEIF2;
	    }
	}

	if(DMA_LISR & DMA_LISR_DMEIF2)
	{
	    if (__DMA2_Stream2_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA2_Stream2_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CDMEIF2;
	    }
	}

	if(DMA_LISR & DMA_LISR_TEIF2)
	{
	    if (__DMA2_Stream2_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA2_Stream2_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CTEIF2;
	    }
	}

	if(DMA_LISR & DMA_LISR_HTIF2)
	{
	    if (__DMA2_Stream2_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA2_Stream2_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CHTIF2;

	    	if(__DMA2_Stream2_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream2_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream2_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream2_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_LISR & DMA_LISR_TCIF2)
	{
	    if (__DMA2_Stream2_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA2_Stream2_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CTCIF2;

	    	if(__DMA2_Stream2_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream2_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream2_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream2_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}

void DMA2_Stream3_IRQHandler(void)
{
	DMA_LISR = DMA2 -> LISR;

	if(DMA_LISR & DMA_LISR_FEIF3)
	{
	    if (__DMA2_Stream3_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA2_Stream3_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CFEIF3;
	    }
	}

	if(DMA_LISR & DMA_LISR_DMEIF3)
	{
	    if (__DMA2_Stream3_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA2_Stream3_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CDMEIF3;
	    }
	}

	if(DMA_LISR & DMA_LISR_TEIF3)
	{
	    if (__DMA2_Stream3_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA2_Stream3_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CTEIF3;
	    }
	}

	if(DMA_LISR & DMA_LISR_HTIF3)
	{
	    if (__DMA2_Stream3_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA2_Stream3_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CHTIF3;

	    	if(__DMA2_Stream3_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream3_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream3_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream3_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_LISR & DMA_LISR_TCIF3)
	{
	    if (__DMA2_Stream3_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA2_Stream3_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> LIFCR |= DMA_LIFCR_CTCIF3;

	    	if(__DMA2_Stream3_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream3_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream3_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream3_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}

void DMA2_Stream4_IRQHandler(void)
{
	DMA_HISR = DMA2 -> HISR;

	if(DMA_HISR & DMA_HISR_FEIF4)
	{
	    if (__DMA2_Stream4_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA2_Stream4_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA2 -> LIFCR |= DMA_HIFCR_CFEIF5;
	    }
	}

	if(DMA_HISR & DMA_HISR_DMEIF4)
	{
	    if (__DMA2_Stream4_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA2_Stream4_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CDMEIF4;
	    }
	}

	if(DMA_HISR & DMA_HISR_TEIF4)
	{
	    if (__DMA2_Stream4_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA2_Stream4_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CTEIF4;
	    }
	}

	if(DMA_HISR & DMA_HISR_HTIF4)
	{
	    if (__DMA2_Stream4_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA2_Stream4_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CHTIF4;

	    	if(__DMA2_Stream4_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream4_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream4_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream4_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_HISR & DMA_HISR_TCIF4)
	{
	    if (__DMA2_Stream4_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA2_Stream4_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CTCIF4;

	    	if(__DMA2_Stream4_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream4_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream4_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream4_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}




void DMA2_Stream5_IRQHandler(void)
{
	DMA_HISR = DMA2 -> HISR;

	if(DMA_HISR & DMA_HISR_FEIF5)
	{
	    if (__DMA2_Stream5_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA2_Stream5_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CFEIF5;
	    }
	}

	if(DMA_HISR & DMA_HISR_DMEIF5)
	{
	    if (__DMA2_Stream5_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA2_Stream5_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CDMEIF5;
	    }
	}

	if(DMA_HISR & DMA_HISR_TEIF5)
	{
	    if (__DMA2_Stream5_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA2_Stream5_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CTEIF5;
	    }
	}

	if(DMA_HISR & DMA_HISR_HTIF5)
	{
	    if (__DMA2_Stream5_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA2_Stream5_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CHTIF5;

	    	if(__DMA2_Stream5_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream5_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream5_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream5_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_HISR & DMA_HISR_TCIF5)
	{
	    if (__DMA2_Stream5_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA2_Stream5_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CTCIF5;

	    	if(__DMA2_Stream5_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream5_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream5_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream5_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}



void DMA2_Stream6_IRQHandler(void)
{
	DMA_HISR = DMA2 -> HISR;

	if(DMA_HISR & DMA_HISR_FEIF6)
	{
	    if (__DMA2_Stream6_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA2_Stream6_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CFEIF6;
	    }
	}

	if(DMA_HISR & DMA_HISR_DMEIF6)
	{
	    if (__DMA2_Stream6_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA2_Stream6_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CDMEIF6;
	    }
	}

	if(DMA_HISR & DMA_HISR_TEIF6)
	{
	    if (__DMA2_Stream6_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA2_Stream6_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CTEIF6;
	    }
	}

	if(DMA_HISR & DMA_HISR_HTIF6)
	{
	    if (__DMA2_Stream6_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA2_Stream6_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CHTIF6;

	    	if(__DMA2_Stream6_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream6_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream6_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream6_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_HISR & DMA_HISR_TCIF6)
	{
	    if (__DMA2_Stream6_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA2_Stream6_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CTCIF6;

	    	if(__DMA2_Stream6_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream6_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream6_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream6_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}


void DMA2_Stream7_IRQHandler(void)
{
	DMA_HISR = DMA2 -> HISR;

	if(DMA_HISR & DMA_HISR_FEIF7)
	{
	    if (__DMA2_Stream7_Config__ -> ISR_Routines.FIFO_Error_ISR)
	    {
	    	__DMA2_Stream7_Config__ ->ISR_Routines.FIFO_Error_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CFEIF7;
	    }
	}

	if(DMA_HISR & DMA_HISR_DMEIF7)
	{
	    if (__DMA2_Stream7_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
	    {
	    	__DMA2_Stream7_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CDMEIF7;
	    }
	}

	if(DMA_HISR & DMA_HISR_TEIF7)
	{
	    if (__DMA2_Stream7_Config__ -> ISR_Routines.Transfer_Error_ISR)
	    {
	    	__DMA2_Stream7_Config__ ->ISR_Routines.Transfer_Error_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CTEIF7;
	    }
	}

	if(DMA_HISR & DMA_HISR_HTIF7)
	{
	    if (__DMA2_Stream7_Config__ -> ISR_Routines.Half_Transfer_Complete_ISR)
	    {
	    	__DMA2_Stream7_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CHTIF7;

	    	if(__DMA2_Stream7_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream7_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream7_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream7_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}

	if(DMA_HISR & DMA_HISR_TCIF7)
	{
	    if (__DMA2_Stream7_Config__ -> ISR_Routines.Full_Transfer_Commplete_ISR)
	    {
	    	__DMA2_Stream7_Config__ ->ISR_Routines.Half_Transfer_Complete_ISR();
	    	DMA2 -> HIFCR |= DMA_HIFCR_CTCIF7;

	    	if(__DMA2_Stream7_Config__->double_buffer_mode == DMA_Configuration.Double_Buffer_Mode.Enable )
	    	{
	    		if((__DMA2_Stream7_Config__->Request.Stream->CR & DMA_SxCR_DBM_Msk) != 0)
	    		{
	    			__DMA2_Stream7_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_1_ISR();
	    		}
	    		else
	    		{
	    			__DMA2_Stream7_Config__ -> ISR_Routines.Double_Buffer_Mode_Target_2_ISR();
	    		}
	    	}
	    }
	}
}

/**
 * @brief Resets all DMA flags in the provided DMA_Flags_Typedef structure.
 *
 * This function sets all the flags in the provided `DMA_Flags_Typedef` structure
 * to `false`, effectively resetting the state of the flags that monitor DMA events
 * such as direct mode error, FIFO error, half transfer complete, transfer complete,
 * and transfer error.
 *
 * @param flag The `DMA_Flags_Typedef` structure whose flags are to be reset.
 */
void DMA_Reset_Flags(volatile DMA_Flags_Typedef *flag)
{
	flag->Direct_Mode_Error_Flag = false;
	flag->Fifo_Error_Flag = false;
	flag->Half_Transfer_Complete_Flag = false;
	flag->Transfer_Complete_Flag = false;
	flag->Transfer_Error_Flag = false;
}

/**
 * @brief Enables the clock for the specified DMA controller.
 *
 * This function enables the clock for the DMA controller specified in the
 * `DMA_Config` structure. It checks whether the controller is `DMA1` or `DMA2`
 * and then enables the corresponding clock by setting the appropriate bit in
 * the RCC AHB1 peripheral clock enable register.
 *
 * @param[in] config Pointer to the `DMA_Config` structure that contains the DMA controller configuration.
 */
void DMA_Clock_Enable(DMA_Config *config)
{
	if(config -> Request.Controller == DMA1){
		RCC -> AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	}
	if(config -> Request.Controller == DMA2)
		{
		RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
		}
}
//

/**
 * @brief Disables the clock for the specified DMA controller.
 *
 * This function disables the clock for the DMA controller specified in the
 * `DMA_Config` structure. It checks whether the controller is `DMA1` or `DMA2`
 * and then disables the corresponding clock by clearing the appropriate bit in
 * the RCC AHB1 peripheral clock enable register.
 *
 * @param[in] config Pointer to the `DMA_Config` structure that contains the DMA controller configuration.
 */
void DMA_Clock_Disable(DMA_Config *config)
{

	if(config -> Request.Controller == DMA1) RCC -> AHB1ENR &= ~RCC_AHB1ENR_DMA1EN;
	if(config -> Request.Controller == DMA2) RCC -> AHB1ENR &= ~RCC_AHB1ENR_DMA2EN;
}
//

/**
 * @brief Resets the specified DMA controller.
 *
 * This function resets the DMA controller specified in the `DMA_Config` structure.
 * It checks whether the controller is `DMA1` or `DMA2` and then triggers a reset
 * by setting the appropriate bit in the RCC AHB1 peripheral reset register.
 *
 * @param[in] config Pointer to the `DMA_Config` structure that contains the DMA controller configuration.
 */
void DMA_Reset(DMA_Config *config)
{
	if(config -> Request.Controller == DMA1) RCC -> AHB1RSTR |= RCC_AHB1RSTR_DMA1RST;
	if(config -> Request.Controller == DMA2) RCC -> AHB1RSTR |= RCC_AHB1RSTR_DMA2RST;
}

/**
 * @brief Initializes the DMA with the specified configuration.
 *
 * This function configures the DMA stream with the settings provided in the
 * `DMA_Config` structure. It enables the clock for the specified DMA controller,
 * sets up the DMA channel, circular mode, flow control, priority level, data sizes,
 * transfer direction, and interrupts. If interrupts are enabled, it also configures
 * the NVIC for the corresponding DMA stream.
 *
 * @param[in] config Pointer to the `DMA_Config` structure containing the configuration parameters.
 *
 * @return int8_t Returns 1 on successful initialization, or -1 if an error occurs.
 */
int8_t DMA_Init(DMA_Config *config)
{
//	DMA_Clock_Disable(config);
    DMA_Clock_Enable(config);  // Enable the clock for the specified DMA controller

    if (config->Request.Stream->CR & DMA_SxCR_EN)
    {
    	config->Request.Stream->CR &= ~DMA_SxCR_EN;
        while (config->Request.Stream->CR & DMA_SxCR_EN);  // Wait until disabled
    }


    config->Request.Stream->CR |= config->Request.channel << DMA_SxCR_CHSEL_Pos;  // Set the DMA channel
    config->Request.Stream->CR |= config->circular_mode;  // Configure circular mode
    config->Request.Stream->CR |= config->flow_control;  // Set flow control
    config->Request.Stream->CR |= config->priority_level;  // Set priority level
    config->Request.Stream->CR |= config->memory_data_size;  // Set memory data size
    config->Request.Stream->CR |= config->peripheral_data_size;  // Set peripheral data size
    config->Request.Stream->CR |= config->transfer_direction;  // Set transfer direction

    // Configure DMA interrupts if enabled


     if(config->interrupts != DMA_Configuration.DMA_Interrupts.Disable)
    {

        if(config->interrupts |= DMA_Configuration.DMA_Interrupts.Fifo_Error)
        {
        	config->Request.Stream->FCR |= config->interrupts;
        }

        if(config->interrupts |= DMA_Configuration.DMA_Interrupts.Transfer_Complete)
        {
        	config->Request.Stream->CR |= DMA_SxCR_TCIE;
        }

        if(config->interrupts |= DMA_Configuration.DMA_Interrupts.Half_Transfer_Complete)
        {
        	config->Request.Stream->CR |= DMA_SxCR_HTIE;
        }

        if(config->interrupts |= DMA_Configuration.DMA_Interrupts.Transfer_Error)
        {
        	config->Request.Stream->CR |= DMA_SxCR_TEIE;
        }
        if(config->interrupts |= DMA_Configuration.DMA_Interrupts.Direct_Mode_Error)
        {
        	config->Request.Stream->CR |= DMA_SxCR_DMEIE;
        }

        // Enable the corresponding NVIC interrupt for the DMA stream
        if(config->Request.Controller == DMA1)
        {
            if(config->Request.Stream == DMA1_Stream0){
            	NVIC_EnableIRQ(DMA1_Stream0_IRQn);
            }
            else if(config->Request.Stream == DMA1_Stream1){
            	NVIC_EnableIRQ(DMA1_Stream1_IRQn);
            }
            else if(config->Request.Stream == DMA1_Stream2){
            	NVIC_EnableIRQ(DMA1_Stream2_IRQn);
            }
            else if(config->Request.Stream == DMA1_Stream3){
            	NVIC_EnableIRQ(DMA1_Stream3_IRQn);
            }
            else if(config->Request.Stream == DMA1_Stream4){
            	NVIC_EnableIRQ(DMA1_Stream4_IRQn);
            }
            else if(config->Request.Stream == DMA1_Stream5){
            	NVIC_EnableIRQ(DMA1_Stream5_IRQn);
            }
            else if(config->Request.Stream == DMA1_Stream6) {
            	NVIC_EnableIRQ(DMA1_Stream6_IRQn);
            }
            else if(config->Request.Stream == DMA1_Stream7){
            	NVIC_EnableIRQ(DMA1_Stream7_IRQn);
            }
        }
        else if(config->Request.Controller == DMA2)
        {
            if(config->Request.Stream == DMA2_Stream0){
            	NVIC_EnableIRQ(DMA2_Stream0_IRQn);
            }
            else if(config->Request.Stream == DMA2_Stream1){
            	NVIC_EnableIRQ(DMA2_Stream1_IRQn);
            }
            else if(config->Request.Stream == DMA2_Stream2){
            	NVIC_EnableIRQ(DMA2_Stream2_IRQn);
            }
            else if(config->Request.Stream == DMA2_Stream3){
            	NVIC_EnableIRQ(DMA2_Stream3_IRQn);
            }
            else if(config->Request.Stream == DMA2_Stream4){
            	NVIC_EnableIRQ(DMA2_Stream4_IRQn);
            }
            else if(config->Request.Stream == DMA2_Stream5){
            	NVIC_EnableIRQ(DMA2_Stream5_IRQn);
            }
            else if(config->Request.Stream == DMA2_Stream6){
            	NVIC_EnableIRQ(DMA2_Stream6_IRQn);
            }
            else if(config->Request.Stream == DMA2_Stream7){
//            	NVIC_SetPriority(DMA2_Stream7_IRQn,0);
            	NVIC_EnableIRQ(DMA2_Stream7_IRQn);

            }
        }
    }

    // Configure memory and peripheral pointer increments
    config->Request.Stream->CR |= config->memory_pointer_increment;
    config->Request.Stream->CR |= config->peripheral_pointer_increment;

    // Configure circular mode
    if(config->circular_mode == DMA_Configuration.Circular_Mode.Enable)
    {
        config->Request.Stream->CR |= DMA_SxCR_CIRC;
    }
    else if(config->circular_mode == DMA_Configuration.Circular_Mode.Disable)
    {
        config->Request.Stream->CR &= ~DMA_SxCR_CIRC;
    }
    else
    {
        return -1;  // Return -1 if circular mode configuration is invalid
    }

    return 1;  // Return 1 on successful initialization
}


/**
 * @brief Configures the target memory and peripheral for DMA transfers.
 *
 * This function sets up the DMA stream to transfer data between the specified
 * memory and peripheral addresses. It configures the memory and peripheral data
 * sizes, the number of data items to transfer, and the memory pointer increment
 * mode. The function also clears the previous configurations for data size and
 * memory increment before applying the new settings.
 *
 * @param[in] config Pointer to the `DMA_Config` structure containing the target configuration.
 */
void DMA_Set_Target(DMA_Config *config)
{
	config -> Request.Stream -> CR &= ~DMA_SxCR_EN;



	if(config -> circular_mode == DMA_Configuration.Circular_Mode.Disable)
	{
		config -> Request.Stream -> CR &= ~DMA_SxCR_CIRC;
	}
	else if(config -> circular_mode == DMA_Configuration.Circular_Mode.Enable)
	{
		config -> Request.Stream -> CR |= DMA_SxCR_CIRC;
	}

    // Clear previous data size and memory increment settings
    config -> Request.Stream -> CR &= ~(DMA_SxCR_MSIZE | DMA_SxCR_PSIZE | DMA_SxCR_MINC);

    // Set the peripheral data size
    config -> Request.Stream -> CR |= config -> peripheral_data_size;

    // Set the memory data size
    config -> Request.Stream -> CR |= config -> memory_data_size;

    // Set the number of data items to be transferred
    config -> Request.Stream -> NDTR = config -> buffer_length;

    // Set memory pointer increment mode
    config -> Request.Stream -> CR |= DMA_SxCR_MINC;

    // Set the memory address
    config -> Request.Stream -> M0AR = (uint32_t)config->memory_address;

    // Set the peripheral address
    config -> Request.Stream -> PAR = (uint32_t)config->peripheral_address;
}



/**
 * @brief Sets up and enables the DMA stream for data transfer.
 *
 * This function configures the DMA stream trigger by clearing any pending interrupt
 * flags for the specified stream and then enables the stream for data transfer. The
 * function determines which register to modify (LIFCR or HIFCR) based on the stream
 * number and the DMA controller (DMA1 or DMA2).
 *
 * @param[in] config Pointer to the `DMA_Config` structure that contains the configuration settings.
 */
void DMA_Set_Trigger(DMA_Config *config)
{
    // Bit shift values for streams 0 to 7
    static const uint8_t LIFCR_Shifts[4] = {0, 6, 16, 22};
    static const uint8_t HIFCR_Shifts[4] = {0, 6, 16, 22};

    DMA_TypeDef *controller = config->Request.Controller;
    DMA_Stream_TypeDef *stream = config->Request.Stream;
    uint32_t shift;

    if (controller == DMA1 || controller == DMA2)
    {
        // Determine the correct shift value and clear the corresponding flags in LIFCR or HIFCR
        if (stream >= DMA1_Stream0 && stream <= DMA1_Stream3)
        {
            shift = LIFCR_Shifts[stream - DMA1_Stream0];
            controller->LIFCR |= 0x3F << shift;  // Clear interrupt flags for the stream
        }
        else if (stream >= DMA1_Stream4 && stream <= DMA1_Stream7)
        {
            shift = HIFCR_Shifts[stream - DMA1_Stream4];
            controller->HIFCR |= 0x3F << shift;  // Clear interrupt flags for the stream
        }
        else if (stream >= DMA2_Stream0 && stream <= DMA2_Stream3)
        {
            shift = LIFCR_Shifts[stream - DMA2_Stream0];
            controller->LIFCR |= 0x3F << shift;  // Clear interrupt flags for the stream
        }
        else if (stream >= DMA2_Stream4 && stream <= DMA2_Stream7)
        {
            shift = HIFCR_Shifts[stream - DMA2_Stream4];
            controller->HIFCR |= 0x3F << shift;  // Clear interrupt flags for the stream
        }

        stream->CR |= DMA_SxCR_EN;  // Enable the DMA stream
    }
}




/**
 * @brief Performs a memory-to-memory data transfer using DMA.
 *
 * This function configures and initiates a DMA transfer from a source memory
 * location to a destination memory location. It sets up the data size,
 * increment modes, and the length of the transfer. The function enables the
 * DMA stream, waits for the transfer to complete, and then disables the stream.
 *
 * @param[in] source Pointer to the source memory location.
 * @param[in] source_data_size Size of the data at the source (8, 16, or 32 bits).
 * @param[in] dest_data_size Size of the data at the destination (8, 16, or 32 bits).
 * @param[in] destination Pointer to the destination memory location.
 * @param[in] source_increment If true, the source address will be incremented after each transfer.
 * @param[in] destination_increment If true, the destination address will be incremented after each transfer.
 * @param[in] length Number of data items to transfer.
 */
void DMA_Memory_To_Memory_Transfer(uint32_t *source,
                          uint8_t source_data_size, uint8_t dest_data_size,
                          uint32_t *destination, bool source_increment,
                          bool destination_increment, uint16_t length)
{
    // Enable DMA2 clock
    RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // Clear the channel selection and set the transfer direction to memory-to-memory
    DMA2_Stream0->CR &= (DMA_SxCR_CHSEL);
    DMA2_Stream0->CR |= DMA_Configuration.Transfer_Direction.Memory_to_memory;

    // Set the transfer complete interrupt and priority level
    DMA2_Stream0->CR |= (DMA_SxCR_TCIE | DMA_SxCR_PL);

    // Set the peripheral data size based on the source data size
    if(source_data_size == 32)
    {
        DMA2_Stream0->CR |= DMA_SxCR_PSIZE;
    }
    else if(source_data_size == 16)
    {
        DMA2_Stream0->CR |= DMA_SxCR_PSIZE_0;
        DMA2_Stream0->CR &= ~DMA_SxCR_PSIZE_1;
    }
    else
    {
        DMA2_Stream0->CR &= ~DMA_SxCR_PSIZE;
    }

    // Set the memory data size based on the destination data size
    if(dest_data_size == 32)
    {
        DMA2_Stream0->CR |= DMA_SxCR_MSIZE;
    }
    else if(dest_data_size == 16)
    {
        DMA2_Stream0->CR |= DMA_SxCR_MSIZE_0;
        DMA2_Stream0->CR &= ~DMA_SxCR_MSIZE_1;
    }
    else
    {
        DMA2_Stream0->CR &= ~DMA_SxCR_MSIZE;
    }

    // Configure source address increment mode
    if(source_increment)
    {
        DMA2_Stream0->CR |= DMA_SxCR_PINC;
    }
    else
    {
        DMA2_Stream0->CR &= ~DMA_SxCR_PINC;
    }

    // Configure destination address increment mode
    if(destination_increment)
    {
        DMA2_Stream0->CR |= DMA_SxCR_MINC;
    }
    else
    {
        DMA2_Stream0->CR &= ~DMA_SxCR_MINC;
    }

    // Set the peripheral address (source)
    DMA2_Stream0->PAR = (uint32_t)(source);

    // Set the memory address (destination)
    DMA2_Stream0->M0AR = (uint32_t)(destination);

    // Set the number of data items to transfer
    DMA2_Stream0->NDTR = (uint16_t)length;

    // Enable the DMA stream
    DMA2_Stream0->CR |= DMA_SxCR_EN;

    // Wait for the transfer to complete
    while((DMA2->LISR & (DMA_LISR_TCIF0_Msk)) == 0) {}

    // Clear the transfer complete flag
    DMA2->LIFCR |= DMA_LIFCR_CTCIF0 | DMA_LIFCR_CHTIF0;

    // Disable the DMA stream

    DMA2_Stream0->CR = 0;
    DMA2_Stream0->FCR = 0;
    DMA2_Stream0->M0AR = 0;
    DMA2_Stream0->M1AR = 0;
    DMA2_Stream0->NDTR= 0;
    DMA2_Stream0->PAR = 0;

    DMA2_Stream0->CR &= ~DMA_SxCR_EN;
}
