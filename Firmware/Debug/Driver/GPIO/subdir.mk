################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/GPIO/GPIO.c 

OBJS += \
./Driver/GPIO/GPIO.o 

C_DEPS += \
./Driver/GPIO/GPIO.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/GPIO/%.o Driver/GPIO/%.su Driver/GPIO/%.cyclo: ../Driver/GPIO/%.c Driver/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/IMU_V100/Driver" -I"D:/STM32F407_Projects/IMU_V100/Modules" -I"D:/STM32F407_Projects/IMU_V100/Middleware" -I"D:/STM32F407_Projects/IMU_V100/Application_Layer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-GPIO

clean-Driver-2f-GPIO:
	-$(RM) ./Driver/GPIO/GPIO.cyclo ./Driver/GPIO/GPIO.d ./Driver/GPIO/GPIO.o ./Driver/GPIO/GPIO.su

.PHONY: clean-Driver-2f-GPIO

