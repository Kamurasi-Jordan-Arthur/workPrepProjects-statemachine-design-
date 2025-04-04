################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/dpp_nucleo-c031c6/qk/bsp.c 

OBJS += \
./Src/dpp_nucleo-c031c6/qk/bsp.o 

C_DEPS += \
./Src/dpp_nucleo-c031c6/qk/bsp.d 


# Each subdirectory must supply rules for building sources it contributes
Src/dpp_nucleo-c031c6/qk/%.o Src/dpp_nucleo-c031c6/qk/%.su Src/dpp_nucleo-c031c6/qk/%.cyclo: ../Src/dpp_nucleo-c031c6/qk/%.c Src/dpp_nucleo-c031c6/qk/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DNUCLEO_C031C6 -DSTM32 -DSTM32C031xx -DSTM32C0 -DSTM32C031C6Tx -USTM32C0 -UNUCLEO_C031C6 -USTM32 -USTM32C031C6Tx -USTM32C0 -c -I../Inc -I"/home/jordan/Embedded projects/Audio_player/3rdParty/CMSIS/Include" -I"/home/jordan/Embedded projects/Audio_player/3rdParty/nucleo-c031c6" -I"/home/jordan/qp/qp/qpc/ports/arm-cm/qk/gnu" -I"/home/jordan/qp/qp/qpc/include" -O0 -ffunction-sections -fdata-sections -Wall -fdata-sections -ffunction-sections -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-dpp_nucleo-2d-c031c6-2f-qk

clean-Src-2f-dpp_nucleo-2d-c031c6-2f-qk:
	-$(RM) ./Src/dpp_nucleo-c031c6/qk/bsp.cyclo ./Src/dpp_nucleo-c031c6/qk/bsp.d ./Src/dpp_nucleo-c031c6/qk/bsp.o ./Src/dpp_nucleo-c031c6/qk/bsp.su

.PHONY: clean-Src-2f-dpp_nucleo-2d-c031c6-2f-qk

