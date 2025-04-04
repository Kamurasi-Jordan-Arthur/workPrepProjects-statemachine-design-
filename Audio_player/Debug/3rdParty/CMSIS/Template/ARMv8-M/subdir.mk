################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../3rdParty/CMSIS/Template/ARMv8-M/main_s.c \
../3rdParty/CMSIS/Template/ARMv8-M/tz_context.c 

OBJS += \
./3rdParty/CMSIS/Template/ARMv8-M/main_s.o \
./3rdParty/CMSIS/Template/ARMv8-M/tz_context.o 

C_DEPS += \
./3rdParty/CMSIS/Template/ARMv8-M/main_s.d \
./3rdParty/CMSIS/Template/ARMv8-M/tz_context.d 


# Each subdirectory must supply rules for building sources it contributes
3rdParty/CMSIS/Template/ARMv8-M/%.o 3rdParty/CMSIS/Template/ARMv8-M/%.su 3rdParty/CMSIS/Template/ARMv8-M/%.cyclo: ../3rdParty/CMSIS/Template/ARMv8-M/%.c 3rdParty/CMSIS/Template/ARMv8-M/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DNUCLEO_C031C6 -DSTM32 -DSTM32C031xx -DSTM32C0 -DSTM32C031C6Tx -USTM32C0 -UNUCLEO_C031C6 -USTM32 -USTM32C031C6Tx -USTM32C0 -c -I../Inc -I"/home/jordan/STM32CubeIDE/workspace_1.18.0/dpp_Try_2/3rdParty/CMSIS/Include" -I"/home/jordan/STM32CubeIDE/workspace_1.18.0/dpp_Try_2/Inc/qpc_include" -I"/home/jordan/STM32CubeIDE/workspace_1.18.0/dpp_Try_2/3rdParty/nucleo-c031c6" -I"/home/jordan/STM32CubeIDE/workspace_1.18.0/Src/QPC_PORT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-3rdParty-2f-CMSIS-2f-Template-2f-ARMv8-2d-M

clean-3rdParty-2f-CMSIS-2f-Template-2f-ARMv8-2d-M:
	-$(RM) ./3rdParty/CMSIS/Template/ARMv8-M/main_s.cyclo ./3rdParty/CMSIS/Template/ARMv8-M/main_s.d ./3rdParty/CMSIS/Template/ARMv8-M/main_s.o ./3rdParty/CMSIS/Template/ARMv8-M/main_s.su ./3rdParty/CMSIS/Template/ARMv8-M/tz_context.cyclo ./3rdParty/CMSIS/Template/ARMv8-M/tz_context.d ./3rdParty/CMSIS/Template/ARMv8-M/tz_context.o ./3rdParty/CMSIS/Template/ARMv8-M/tz_context.su

.PHONY: clean-3rdParty-2f-CMSIS-2f-Template-2f-ARMv8-2d-M

