################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/QV_PORT/qv_port.c 

OBJS += \
./Core/Inc/QV_PORT/qv_port.o 

C_DEPS += \
./Core/Inc/QV_PORT/qv_port.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/QV_PORT/%.o Core/Inc/QV_PORT/%.su Core/Inc/QV_PORT/%.cyclo: ../Core/Inc/QV_PORT/%.c Core/Inc/QV_PORT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"/home/jordan/Embedded projects/Elevator2/Core/Inc/appfiles/include" -I"/home/jordan/Embedded projects/Elevator2/Core/Inc/QPC_inc" -I"/home/jordan/Embedded projects/Elevator2/Core/Inc/QV_PORT" -Os -ffunction-sections -fdata-sections -Wall -mcpu=cortex-m4 -mfpu=vfp -mfloat-abi=softfp -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-QV_PORT

clean-Core-2f-Inc-2f-QV_PORT:
	-$(RM) ./Core/Inc/QV_PORT/qv_port.cyclo ./Core/Inc/QV_PORT/qv_port.d ./Core/Inc/QV_PORT/qv_port.o ./Core/Inc/QV_PORT/qv_port.su

.PHONY: clean-Core-2f-Inc-2f-QV_PORT

