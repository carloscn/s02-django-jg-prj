################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"C:/MinGW/include" -I"D:/ProgramData/WorkSpace/Workspcae_AC6/S02_BC35_STM32L/StdPeriph_Driver/inc" -I"D:/ProgramData/WorkSpace/Workspcae_AC6/S02_BC35_STM32L/inc" -I"D:/ProgramData/WorkSpace/Workspcae_AC6/S02_BC35_STM32L/CMSIS/device" -I"D:/ProgramData/WorkSpace/Workspcae_AC6/S02_BC35_STM32L/CMSIS/core" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


