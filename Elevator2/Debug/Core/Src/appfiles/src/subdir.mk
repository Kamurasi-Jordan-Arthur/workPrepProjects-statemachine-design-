################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/appfiles/src/bsp.c \
../Core/Src/appfiles/src/elevator.c \
../Core/Src/appfiles/src/main.c \
../Core/Src/appfiles/src/stdfunctions.c 

OBJS += \
./Core/Src/appfiles/src/bsp.o \
./Core/Src/appfiles/src/elevator.o \
./Core/Src/appfiles/src/main.o \
./Core/Src/appfiles/src/stdfunctions.o 

C_DEPS += \
./Core/Src/appfiles/src/bsp.d \
./Core/Src/appfiles/src/elevator.d \
./Core/Src/appfiles/src/main.d \
./Core/Src/appfiles/src/stdfunctions.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/appfiles/src/%.o Core/Src/appfiles/src/%.su Core/Src/appfiles/src/%.cyclo: ../Core/Src/appfiles/src/%.c Core/Src/appfiles/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"/home/jordan/Embedded projects/Elevator2/Core/Inc/QV_PORT" -I"/home/jordan/Embedded projects/Elevator2/Core/Inc/QPC_inc" -I"/home/jordan/Embedded projects/Elevator2/Core/Inc/appfiles/include" -O0 -ffunction-sections -fdata-sections -Wall -mcpu=cortex-m4 -mfpu=vfp -mfloat-abi=softfp -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-appfiles-2f-src

clean-Core-2f-Src-2f-appfiles-2f-src:
	-$(RM) ./Core/Src/appfiles/src/bsp.cyclo ./Core/Src/appfiles/src/bsp.d ./Core/Src/appfiles/src/bsp.o ./Core/Src/appfiles/src/bsp.su ./Core/Src/appfiles/src/elevator.cyclo ./Core/Src/appfiles/src/elevator.d ./Core/Src/appfiles/src/elevator.o ./Core/Src/appfiles/src/elevator.su ./Core/Src/appfiles/src/main.cyclo ./Core/Src/appfiles/src/main.d ./Core/Src/appfiles/src/main.o ./Core/Src/appfiles/src/main.su ./Core/Src/appfiles/src/stdfunctions.cyclo ./Core/Src/appfiles/src/stdfunctions.d ./Core/Src/appfiles/src/stdfunctions.o ./Core/Src/appfiles/src/stdfunctions.su

.PHONY: clean-Core-2f-Src-2f-appfiles-2f-src

