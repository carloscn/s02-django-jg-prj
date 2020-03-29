################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BC35.c \
../src/LED.c \
../src/buzzer.c \
../src/ds1302-2.c \
../src/key.c \
../src/main.c \
../src/mpu6050.c \
../src/stm32l1xx_it.c \
../src/sw180.c \
../src/syscalls.c \
../src/system_stm32l1xx.c \
../src/timer.c \
../src/usart.c 

OBJS += \
./src/BC35.o \
./src/LED.o \
./src/buzzer.o \
./src/ds1302-2.o \
./src/key.o \
./src/main.o \
./src/mpu6050.o \
./src/stm32l1xx_it.o \
./src/sw180.o \
./src/syscalls.o \
./src/system_stm32l1xx.o \
./src/timer.o \
./src/usart.o 

C_DEPS += \
./src/BC35.d \
./src/LED.d \
./src/buzzer.d \
./src/ds1302-2.d \
./src/key.d \
./src/main.d \
./src/mpu6050.d \
./src/stm32l1xx_it.d \
./src/sw180.d \
./src/syscalls.d \
./src/system_stm32l1xx.d \
./src/timer.d \
./src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L1 -DSTM32L151CBTxA -DDEBUG -DSTM32L1XX_MD -DUSE_STDPERIPH_DRIVER -I"C:/MinGW/include" -I"D:/ProgramData/WorkSpace/Workspcae_AC6/S02_BC35_STM32L/StdPeriph_Driver/inc" -I"D:/ProgramData/WorkSpace/Workspcae_AC6/S02_BC35_STM32L/inc" -I"D:/ProgramData/WorkSpace/Workspcae_AC6/S02_BC35_STM32L/CMSIS/device" -I"D:/ProgramData/WorkSpace/Workspcae_AC6/S02_BC35_STM32L/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


