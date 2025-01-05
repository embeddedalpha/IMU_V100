################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Timer/Timer.c 

OBJS += \
./Driver/Timer/Timer.o 

C_DEPS += \
./Driver/Timer/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Timer/%.o Driver/Timer/%.su Driver/Timer/%.cyclo: ../Driver/Timer/%.c Driver/Timer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/IMU_V100/Driver" -I"D:/STM32F407_Projects/IMU_V100/Modules" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-Timer

clean-Driver-2f-Timer:
	-$(RM) ./Driver/Timer/Timer.cyclo ./Driver/Timer/Timer.d ./Driver/Timer/Timer.o ./Driver/Timer/Timer.su

.PHONY: clean-Driver-2f-Timer

