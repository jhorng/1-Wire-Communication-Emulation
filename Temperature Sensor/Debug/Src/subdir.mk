################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/function.c \
../Src/main.c \
../Src/state_machine.c \
../Src/stm32f1xx_hal_msp.c \
../Src/stm32f1xx_it.c \
../Src/system_stm32f1xx.c \
../Src/timer.c \
../Src/uart.c 

OBJS += \
./Src/function.o \
./Src/main.o \
./Src/state_machine.o \
./Src/stm32f1xx_hal_msp.o \
./Src/stm32f1xx_it.o \
./Src/system_stm32f1xx.o \
./Src/timer.o \
./Src/uart.o 

C_DEPS += \
./Src/function.d \
./Src/main.d \
./Src/state_machine.d \
./Src/stm32f1xx_hal_msp.d \
./Src/stm32f1xx_it.d \
./Src/system_stm32f1xx.d \
./Src/timer.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/Users/TARUC/Desktop/1-Wire-Communication-Emulation/Temperature Sensor/Inc" -I"C:/Users/TARUC/Desktop/1-Wire-Communication-Emulation/Temperature Sensor/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/Users/TARUC/Desktop/1-Wire-Communication-Emulation/Temperature Sensor/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/Users/TARUC/Desktop/1-Wire-Communication-Emulation/Temperature Sensor/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/TARUC/Desktop/1-Wire-Communication-Emulation/Temperature Sensor/Drivers/CMSIS/Include" -I"C:/Users/TARUC/Desktop/1-Wire-Communication-Emulation/Temperature Sensor/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


