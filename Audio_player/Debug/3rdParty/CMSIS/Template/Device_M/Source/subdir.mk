################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../3rdParty/CMSIS/Template/Device_M/Source/startup_Device.c \
../3rdParty/CMSIS/Template/Device_M/Source/system_Device.c 

OBJS += \
./3rdParty/CMSIS/Template/Device_M/Source/startup_Device.o \
./3rdParty/CMSIS/Template/Device_M/Source/system_Device.o 

C_DEPS += \
./3rdParty/CMSIS/Template/Device_M/Source/startup_Device.d \
./3rdParty/CMSIS/Template/Device_M/Source/system_Device.d 


# Each subdirectory must supply rules for building sources it contributes
3rdParty/CMSIS/Template/Device_M/Source/%.o 3rdParty/CMSIS/Template/Device_M/Source/%.su 3rdParty/CMSIS/Template/Device_M/Source/%.cyclo: ../3rdParty/CMSIS/Template/Device_M/Source/%.c 3rdParty/CMSIS/Template/Device_M/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DNUCLEO_C031C6 -DSTM32 -DSTM32C031xx -DSTM32C0 -DSTM32C031C6Tx -USTM32C0 -UNUCLEO_C031C6 -USTM32 -USTM32C031C6Tx -USTM32C0 -c -I../Inc -I"/home/jordan/STM32CubeIDE/workspace_1.18.0/dpp_Try_2/3rdParty/CMSIS/Include" -I"/home/jordan/STM32CubeIDE/workspace_1.18.0/dpp_Try_2/Inc/qpc_include" -I"/home/jordan/STM32CubeIDE/workspace_1.18.0/dpp_Try_2/3rdParty/nucleo-c031c6" -I"/home/jordan/STM32CubeIDE/workspace_1.18.0/Src/QPC_PORT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-3rdParty-2f-CMSIS-2f-Template-2f-Device_M-2f-Source

clean-3rdParty-2f-CMSIS-2f-Template-2f-Device_M-2f-Source:
	-$(RM) ./3rdParty/CMSIS/Template/Device_M/Source/startup_Device.cyclo ./3rdParty/CMSIS/Template/Device_M/Source/startup_Device.d ./3rdParty/CMSIS/Template/Device_M/Source/startup_Device.o ./3rdParty/CMSIS/Template/Device_M/Source/startup_Device.su ./3rdParty/CMSIS/Template/Device_M/Source/system_Device.cyclo ./3rdParty/CMSIS/Template/Device_M/Source/system_Device.d ./3rdParty/CMSIS/Template/Device_M/Source/system_Device.o ./3rdParty/CMSIS/Template/Device_M/Source/system_Device.su

.PHONY: clean-3rdParty-2f-CMSIS-2f-Template-2f-Device_M-2f-Source

