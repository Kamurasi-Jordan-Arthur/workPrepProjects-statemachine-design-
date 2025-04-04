################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/QPC_PORT/qk_port.c 

OBJS += \
./Src/QPC_PORT/qk_port.o 

C_DEPS += \
./Src/QPC_PORT/qk_port.d 


# Each subdirectory must supply rules for building sources it contributes
Src/QPC_PORT/%.o Src/QPC_PORT/%.su Src/QPC_PORT/%.cyclo: ../Src/QPC_PORT/%.c Src/QPC_PORT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DNUCLEO_C031C6 -DSTM32 -DSTM32C031xx -DSTM32C0 -DSTM32C031C6Tx -USTM32C0 -UNUCLEO_C031C6 -USTM32 -USTM32C031C6Tx -USTM32C0 -c -I../Inc -I"/home/jordan/Embedded projects/Audio_player/3rdParty/CMSIS/Include" -I"/home/jordan/Embedded projects/Audio_player/3rdParty/nucleo-c031c6" -I"/home/jordan/qp/qp/qpc/ports/arm-cm/qk/gnu" -I"/home/jordan/qp/qp/qpc/include" -O0 -ffunction-sections -fdata-sections -Wall -fdata-sections -ffunction-sections -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-QPC_PORT

clean-Src-2f-QPC_PORT:
	-$(RM) ./Src/QPC_PORT/qk_port.cyclo ./Src/QPC_PORT/qk_port.d ./Src/QPC_PORT/qk_port.o ./Src/QPC_PORT/qk_port.su

.PHONY: clean-Src-2f-QPC_PORT

