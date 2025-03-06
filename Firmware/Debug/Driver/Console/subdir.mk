################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Console/Console.c 

OBJS += \
./Driver/Console/Console.o 

C_DEPS += \
./Driver/Console/Console.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Console/%.o Driver/Console/%.su Driver/Console/%.cyclo: ../Driver/Console/%.c Driver/Console/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/IMU_V100/Driver" -I"D:/STM32F407_Projects/IMU_V100/Modules" -I"D:/STM32F407_Projects/IMU_V100/Middleware" -I"D:/STM32F407_Projects/IMU_V100/Application_Layer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-Console

clean-Driver-2f-Console:
	-$(RM) ./Driver/Console/Console.cyclo ./Driver/Console/Console.d ./Driver/Console/Console.o ./Driver/Console/Console.su

.PHONY: clean-Driver-2f-Console

