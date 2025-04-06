################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/DMA/DMA.c 

OBJS += \
./Driver/DMA/DMA.o 

C_DEPS += \
./Driver/DMA/DMA.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/DMA/%.o Driver/DMA/%.su Driver/DMA/%.cyclo: ../Driver/DMA/%.c Driver/DMA/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/Water_Source_Heat_Pump_V100/Driver" -I"D:/STM32F407_Projects/Water_Source_Heat_Pump_V100/WSHP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-DMA

clean-Driver-2f-DMA:
	-$(RM) ./Driver/DMA/DMA.cyclo ./Driver/DMA/DMA.d ./Driver/DMA/DMA.o ./Driver/DMA/DMA.su

.PHONY: clean-Driver-2f-DMA

