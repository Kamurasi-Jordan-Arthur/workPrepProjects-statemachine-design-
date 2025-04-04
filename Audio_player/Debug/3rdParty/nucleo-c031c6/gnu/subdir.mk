################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../3rdParty/nucleo-c031c6/gnu/startup_stm32c031xx.c 

OBJS += \
./3rdParty/nucleo-c031c6/gnu/startup_stm32c031xx.o 

C_DEPS += \
./3rdParty/nucleo-c031c6/gnu/startup_stm32c031xx.d 


# Each subdirectory must supply rules for building sources it contributes
3rdParty/nucleo-c031c6/gnu/%.o 3rdParty/nucleo-c031c6/gnu/%.su 3rdParty/nucleo-c031c6/gnu/%.cyclo: ../3rdParty/nucleo-c031c6/gnu/%.c 3rdParty/nucleo-c031c6/gnu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DNUCLEO_C031C6 -DSTM32 -DSTM32C031xx -DSTM32C0 -DSTM32C031C6Tx -USTM32C031C6Tx -c -I../Inc -I"/home/jordan/Embedded projects/Audio_player/3rdParty/CMSIS/Include" -I"/home/jordan/Embedded projects/Audio_player/3rdParty/nucleo-c031c6" -I"/home/jordan/qp/qp/qpc/ports/arm-cm/qk/gnu" -I"/home/jordan/qp/qp/qpc/include" -O0 -ffunction-sections -fdata-sections -Wall -fdata-sections -ffunction-sections -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-3rdParty-2f-nucleo-2d-c031c6-2f-gnu

clean-3rdParty-2f-nucleo-2d-c031c6-2f-gnu:
	-$(RM) ./3rdParty/nucleo-c031c6/gnu/startup_stm32c031xx.cyclo ./3rdParty/nucleo-c031c6/gnu/startup_stm32c031xx.d ./3rdParty/nucleo-c031c6/gnu/startup_stm32c031xx.o ./3rdParty/nucleo-c031c6/gnu/startup_stm32c031xx.su

.PHONY: clean-3rdParty-2f-nucleo-2d-c031c6-2f-gnu

