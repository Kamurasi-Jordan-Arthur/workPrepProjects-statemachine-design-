################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/qs/qstamp.c 

OBJS += \
./Core/Src/qs/qstamp.o 

C_DEPS += \
./Core/Src/qs/qstamp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/qs/%.o Core/Src/qs/%.su Core/Src/qs/%.cyclo: ../Core/Src/qs/%.c Core/Src/qs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"/home/jordan/Embedded projects/Elevator2/Core/Inc/QV_PORT" -I"/home/jordan/Embedded projects/Elevator2/Core/Inc/QPC_inc" -I"/home/jordan/Embedded projects/Elevator2/Core/Inc/appfiles/include" -O0 -ffunction-sections -fdata-sections -Wall -mcpu=cortex-m4 -mfpu=vfp -mfloat-abi=softfp -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-qs

clean-Core-2f-Src-2f-qs:
	-$(RM) ./Core/Src/qs/qstamp.cyclo ./Core/Src/qs/qstamp.d ./Core/Src/qs/qstamp.o ./Core/Src/qs/qstamp.su

.PHONY: clean-Core-2f-Src-2f-qs

