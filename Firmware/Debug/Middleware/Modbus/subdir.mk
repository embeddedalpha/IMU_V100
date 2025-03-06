################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/Modbus/Modbus.c 

OBJS += \
./Middleware/Modbus/Modbus.o 

C_DEPS += \
./Middleware/Modbus/Modbus.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/Modbus/%.o Middleware/Modbus/%.su Middleware/Modbus/%.cyclo: ../Middleware/Modbus/%.c Middleware/Modbus/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/IMU_V100/Driver" -I"D:/STM32F407_Projects/IMU_V100/Modules" -I"D:/STM32F407_Projects/IMU_V100/Middleware" -I"D:/STM32F407_Projects/IMU_V100/Application_Layer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware-2f-Modbus

clean-Middleware-2f-Modbus:
	-$(RM) ./Middleware/Modbus/Modbus.cyclo ./Middleware/Modbus/Modbus.d ./Middleware/Modbus/Modbus.o ./Middleware/Modbus/Modbus.su

.PHONY: clean-Middleware-2f-Modbus

