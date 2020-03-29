################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../StdPeriph_Driver/src/misc.c \
../StdPeriph_Driver/src/stm32l1xx_adc.c \
../StdPeriph_Driver/src/stm32l1xx_aes.c \
../StdPeriph_Driver/src/stm32l1xx_aes_util.c \
../StdPeriph_Driver/src/stm32l1xx_comp.c \
../StdPeriph_Driver/src/stm32l1xx_crc.c \
../StdPeriph_Driver/src/stm32l1xx_dac.c \
../StdPeriph_Driver/src/stm32l1xx_dbgmcu.c \
../StdPeriph_Driver/src/stm32l1xx_dma.c \
../StdPeriph_Driver/src/stm32l1xx_exti.c \
../StdPeriph_Driver/src/stm32l1xx_flash.c \
../StdPeriph_Driver/src/stm32l1xx_flash_ramfunc.c \
../StdPeriph_Driver/src/stm32l1xx_fsmc.c \
../StdPeriph_Driver/src/stm32l1xx_gpio.c \
../StdPeriph_Driver/src/stm32l1xx_i2c.c \
../StdPeriph_Driver/src/stm32l1xx_iwdg.c \
../StdPeriph_Driver/src/stm32l1xx_lcd.c \
../StdPeriph_Driver/src/stm32l1xx_opamp.c \
../StdPeriph_Driver/src/stm32l1xx_pwr.c \
../StdPeriph_Driver/src/stm32l1xx_rcc.c \
../StdPeriph_Driver/src/stm32l1xx_rtc.c \
../StdPeriph_Driver/src/stm32l1xx_sdio.c \
../StdPeriph_Driver/src/stm32l1xx_spi.c \
../StdPeriph_Driver/src/stm32l1xx_syscfg.c \
../StdPeriph_Driver/src/stm32l1xx_tim.c \
../StdPeriph_Driver/src/stm32l1xx_usart.c \
../StdPeriph_Driver/src/stm32l1xx_wwdg.c 

OBJS += \
./StdPeriph_Driver/src/misc.o \
./StdPeriph_Driver/src/stm32l1xx_adc.o \
./StdPeriph_Driver/src/stm32l1xx_aes.o \
./StdPeriph_Driver/src/stm32l1xx_aes_util.o \
./StdPeriph_Driver/src/stm32l1xx_comp.o \
./StdPeriph_Driver/src/stm32l1xx_crc.o \
./StdPeriph_Driver/src/stm32l1xx_dac.o \
./StdPeriph_Driver/src/stm32l1xx_dbgmcu.o \
./StdPeriph_Driver/src/stm32l1xx_dma.o \
./StdPeriph_Driver/src/stm32l1xx_exti.o \
./StdPeriph_Driver/src/stm32l1xx_flash.o \
./StdPeriph_Driver/src/stm32l1xx_flash_ramfunc.o \
./StdPeriph_Driver/src/stm32l1xx_fsmc.o \
./StdPeriph_Driver/src/stm32l1xx_gpio.o \
./StdPeriph_Driver/src/stm32l1xx_i2c.o \
./StdPeriph_Driver/src/stm32l1xx_iwdg.o \
./StdPeriph_Driver/src/stm32l1xx_lcd.o \
./StdPeriph_Driver/src/stm32l1xx_opamp.o \
./StdPeriph_Driver/src/stm32l1xx_pwr.o \
./StdPeriph_Driver/src/stm32l1xx_rcc.o \
./StdPeriph_Driver/src/stm32l1xx_rtc.o \
./StdPeriph_Driver/src/stm32l1xx_sdio.o \
./StdPeriph_Driver/src/stm32l1xx_spi.o \
./StdPeriph_Driver/src/stm32l1xx_syscfg.o \
./StdPeriph_Driver/src/stm32l1xx_tim.o \
./StdPeriph_Driver/src/stm32l1xx_usart.o \
./StdPeriph_Driver/src/stm32l1xx_wwdg.o 

C_DEPS += \
./StdPeriph_Driver/src/misc.d \
./StdPeriph_Driver/src/stm32l1xx_adc.d \
./StdPeriph_Driver/src/stm32l1xx_aes.d \
./StdPeriph_Driver/src/stm32l1xx_aes_util.d \
./StdPeriph_Driver/src/stm32l1xx_comp.d \
./StdPeriph_Driver/src/stm32l1xx_crc.d \
./StdPeriph_Driver/src/stm32l1xx_dac.d \
./StdPeriph_Driver/src/stm32l1xx_dbgmcu.d \
./StdPeriph_Driver/src/stm32l1xx_dma.d \
./StdPeriph_Driver/src/stm32l1xx_exti.d \
./StdPeriph_Driver/src/stm32l1xx_flash.d \
./StdPeriph_Driver/src/stm32l1xx_flash_ramfunc.d \
./StdPeriph_Driver/src/stm32l1xx_fsmc.d \
./StdPeriph_Driver/src/stm32l1xx_gpio.d \
./StdPeriph_Driver/src/stm32l1xx_i2c.d \
./StdPeriph_Driver/src/stm32l1xx_iwdg.d \
./StdPeriph_Driver/src/stm32l1xx_lcd.d \
./StdPeriph_Driver/src/stm32l1xx_opamp.d \
./StdPeriph_Driver/src/stm32l1xx_pwr.d \
./StdPeriph_Driver/src/stm32l1xx_rcc.d \
./StdPeriph_Driver/src/stm32l1xx_rtc.d \
./StdPeriph_Driver/src/stm32l1xx_sdio.d \
./StdPeriph_Driver/src/stm32l1xx_spi.d \
./StdPeriph_Driver/src/stm32l1xx_syscfg.d \
./StdPeriph_Driver/src/stm32l1xx_tim.d \
./StdPeriph_Driver/src/stm32l1xx_usart.d \
./StdPeriph_Driver/src/stm32l1xx_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
StdPeriph_Driver/src/%.o: ../StdPeriph_Driver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L1 -DSTM32L151CBTxA -DDEBUG -DSTM32L1XX_MD -DUSE_STDPERIPH_DRIVER -I"C:/MinGW/include" -I"D:/ProgramData/WorkSpace/Workspcae_AC6/S02_BC35_STM32L/StdPeriph_Driver/inc" -I"D:/ProgramData/WorkSpace/Workspcae_AC6/S02_BC35_STM32L/inc" -I"D:/ProgramData/WorkSpace/Workspcae_AC6/S02_BC35_STM32L/CMSIS/device" -I"D:/ProgramData/WorkSpace/Workspcae_AC6/S02_BC35_STM32L/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


