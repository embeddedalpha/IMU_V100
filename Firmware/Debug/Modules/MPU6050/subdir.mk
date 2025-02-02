################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/MPU6050/MPU6050.c 

OBJS += \
./Modules/MPU6050/MPU6050.o 

C_DEPS += \
./Modules/MPU6050/MPU6050.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/MPU6050/%.o Modules/MPU6050/%.su Modules/MPU6050/%.cyclo: ../Modules/MPU6050/%.c Modules/MPU6050/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Projects/IMU_V100/Driver" -I"D:/STM32F407_Projects/IMU_V100/Modules" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-MPU6050

clean-Modules-2f-MPU6050:
	-$(RM) ./Modules/MPU6050/MPU6050.cyclo ./Modules/MPU6050/MPU6050.d ./Modules/MPU6050/MPU6050.o ./Modules/MPU6050/MPU6050.su

.PHONY: clean-Modules-2f-MPU6050

