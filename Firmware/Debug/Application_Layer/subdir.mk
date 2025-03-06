################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application_Layer/App.c 

OBJS += \
./Application_Layer/App.o 

C_DEPS += \
./Application_Layer/App.d 


# Each subdirectory must supply rules for building sources it contributes
Application_Layer/%.o Application_Layer/%.su Application_Layer/%.cyclo: ../Application_Layer/%.c Application_Layer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/IMU_V100/Driver" -I"D:/STM32F407_Projects/IMU_V100/Modules" -I"D:/STM32F407_Projects/IMU_V100/Middleware" -I"D:/STM32F407_Projects/IMU_V100/Application_Layer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application_Layer

clean-Application_Layer:
	-$(RM) ./Application_Layer/App.cyclo ./Application_Layer/App.d ./Application_Layer/App.o ./Application_Layer/App.su

.PHONY: clean-Application_Layer

