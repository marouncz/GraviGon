################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/ssd1306/ssd1306.c \
../Core/ssd1306/ssd1306_fonts.c \
../Core/ssd1306/ssd1306_tests.c 

OBJS += \
./Core/ssd1306/ssd1306.o \
./Core/ssd1306/ssd1306_fonts.o \
./Core/ssd1306/ssd1306_tests.o 

C_DEPS += \
./Core/ssd1306/ssd1306.d \
./Core/ssd1306/ssd1306_fonts.d \
./Core/ssd1306/ssd1306_tests.d 


# Each subdirectory must supply rules for building sources it contributes
Core/ssd1306/%.o Core/ssd1306/%.su Core/ssd1306/%.cyclo: ../Core/ssd1306/%.c Core/ssd1306/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-ssd1306

clean-Core-2f-ssd1306:
	-$(RM) ./Core/ssd1306/ssd1306.cyclo ./Core/ssd1306/ssd1306.d ./Core/ssd1306/ssd1306.o ./Core/ssd1306/ssd1306.su ./Core/ssd1306/ssd1306_fonts.cyclo ./Core/ssd1306/ssd1306_fonts.d ./Core/ssd1306/ssd1306_fonts.o ./Core/ssd1306/ssd1306_fonts.su ./Core/ssd1306/ssd1306_tests.cyclo ./Core/ssd1306/ssd1306_tests.d ./Core/ssd1306/ssd1306_tests.o ./Core/ssd1306/ssd1306_tests.su

.PHONY: clean-Core-2f-ssd1306

