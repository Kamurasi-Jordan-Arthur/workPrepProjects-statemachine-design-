################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gnu/startup_stm32c031xx.c 

OBJS += \
./Src/gnu/startup_stm32c031xx.o 

C_DEPS += \
./Src/gnu/startup_stm32c031xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/gnu/%.o Src/gnu/%.su Src/gnu/%.cyclo: ../Src/gnu/%.c Src/gnu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DNUCLEO_C031C6 -DSTM32 -DSTM32C031xx -DSTM32C0 -DSTM32C031C6Tx -USTM32C0 -UNUCLEO_C031C6 -USTM32 -USTM32C031C6Tx -USTM32C0 -c -I../Inc -I"/home/jordan/STM32CubeIDE/workspace_1.18.0/dpp_Try_2/3rdParty/CMSIS/Include" -I"/home/jordan/STM32CubeIDE/workspace_1.18.0/dpp_Try_2/Inc/qpc_include" -I"/home/jordan/STM32CubeIDE/workspace_1.18.0/dpp_Try_2/3rdParty/nucleo-c031c6" -I"/home/jordan/STM32CubeIDE/workspace_1.18.0/dpp_Try_2/Inc/QPC_PORT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-gnu

clean-Src-2f-gnu:
	-$(RM) ./Src/gnu/startup_stm32c031xx.cyclo ./Src/gnu/startup_stm32c031xx.d ./Src/gnu/startup_stm32c031xx.o ./Src/gnu/startup_stm32c031xx.su

.PHONY: clean-Src-2f-gnu

