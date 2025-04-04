################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Startup/startup_stm32c031xx.c 

OBJS += \
./Startup/startup_stm32c031xx.o 

C_DEPS += \
./Startup/startup_stm32c031xx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o Startup/%.su Startup/%.cyclo: ../Startup/%.c Startup/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DNUCLEO_C031C6 -DSTM32C031xx -DSTM32 -DSTM32C0 -DSTM32C031C6Tx -c -I../Inc -I"/home/jordan/Embedded projects/Audio_player/3rdParty/CMSIS/Include" -I"/home/jordan/Embedded projects/Audio_player/3rdParty/nucleo-c031c6" -I"/home/jordan/qp/qp/qpc/ports/arm-cm/qk/gnu" -I"/home/jordan/qp/qp/qpc/include" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32c031xx.cyclo ./Startup/startup_stm32c031xx.d ./Startup/startup_stm32c031xx.o ./Startup/startup_stm32c031xx.su

.PHONY: clean-Startup

