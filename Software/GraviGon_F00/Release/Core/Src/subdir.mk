################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/GNSS.c \
../Core/Src/adc.c \
../Core/Src/adis.c \
../Core/Src/dma.c \
../Core/Src/fmpi2c.c \
../Core/Src/freertos.c \
../Core/Src/gpio.c \
../Core/Src/gui.c \
../Core/Src/i2c.c \
../Core/Src/lsm.c \
../Core/Src/main.c \
../Core/Src/mpu.c \
../Core/Src/quadspi.c \
../Core/Src/rtc.c \
../Core/Src/sdio.c \
../Core/Src/spi.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_hal_timebase_tim.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/usart.c \
../Core/Src/w25q_mem.c 

OBJS += \
./Core/Src/GNSS.o \
./Core/Src/adc.o \
./Core/Src/adis.o \
./Core/Src/dma.o \
./Core/Src/fmpi2c.o \
./Core/Src/freertos.o \
./Core/Src/gpio.o \
./Core/Src/gui.o \
./Core/Src/i2c.o \
./Core/Src/lsm.o \
./Core/Src/main.o \
./Core/Src/mpu.o \
./Core/Src/quadspi.o \
./Core/Src/rtc.o \
./Core/Src/sdio.o \
./Core/Src/spi.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_hal_timebase_tim.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/usart.o \
./Core/Src/w25q_mem.o 

C_DEPS += \
./Core/Src/GNSS.d \
./Core/Src/adc.d \
./Core/Src/adis.d \
./Core/Src/dma.d \
./Core/Src/fmpi2c.d \
./Core/Src/freertos.d \
./Core/Src/gpio.d \
./Core/Src/gui.d \
./Core/Src/i2c.d \
./Core/Src/lsm.d \
./Core/Src/main.d \
./Core/Src/mpu.d \
./Core/Src/quadspi.d \
./Core/Src/rtc.d \
./Core/Src/sdio.d \
./Core/Src/spi.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_hal_timebase_tim.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/usart.d \
./Core/Src/w25q_mem.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/GNSS.cyclo ./Core/Src/GNSS.d ./Core/Src/GNSS.o ./Core/Src/GNSS.su ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/adis.cyclo ./Core/Src/adis.d ./Core/Src/adis.o ./Core/Src/adis.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/fmpi2c.cyclo ./Core/Src/fmpi2c.d ./Core/Src/fmpi2c.o ./Core/Src/fmpi2c.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/gui.cyclo ./Core/Src/gui.d ./Core/Src/gui.o ./Core/Src/gui.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/lsm.cyclo ./Core/Src/lsm.d ./Core/Src/lsm.o ./Core/Src/lsm.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mpu.cyclo ./Core/Src/mpu.d ./Core/Src/mpu.o ./Core/Src/mpu.su ./Core/Src/quadspi.cyclo ./Core/Src/quadspi.d ./Core/Src/quadspi.o ./Core/Src/quadspi.su ./Core/Src/rtc.cyclo ./Core/Src/rtc.d ./Core/Src/rtc.o ./Core/Src/rtc.su ./Core/Src/sdio.cyclo ./Core/Src/sdio.d ./Core/Src/sdio.o ./Core/Src/sdio.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_hal_timebase_tim.cyclo ./Core/Src/stm32f4xx_hal_timebase_tim.d ./Core/Src/stm32f4xx_hal_timebase_tim.o ./Core/Src/stm32f4xx_hal_timebase_tim.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/w25q_mem.cyclo ./Core/Src/w25q_mem.d ./Core/Src/w25q_mem.o ./Core/Src/w25q_mem.su

.PHONY: clean-Core-2f-Src

