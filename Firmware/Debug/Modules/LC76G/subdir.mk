################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/LC76G/LC76G.c 

OBJS += \
./Modules/LC76G/LC76G.o 

C_DEPS += \
./Modules/LC76G/LC76G.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/LC76G/%.o Modules/LC76G/%.su Modules/LC76G/%.cyclo: ../Modules/LC76G/%.c Modules/LC76G/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/IMU_V100/Driver" -I"D:/STM32F407_Projects/IMU_V100/Modules" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-LC76G

clean-Modules-2f-LC76G:
	-$(RM) ./Modules/LC76G/LC76G.cyclo ./Modules/LC76G/LC76G.d ./Modules/LC76G/LC76G.o ./Modules/LC76G/LC76G.su

.PHONY: clean-Modules-2f-LC76G

