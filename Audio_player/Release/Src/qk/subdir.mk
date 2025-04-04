################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/qk/qk.c 

OBJS += \
./Src/qk/qk.o 

C_DEPS += \
./Src/qk/qk.d 


# Each subdirectory must supply rules for building sources it contributes
Src/qk/%.o Src/qk/%.su Src/qk/%.cyclo: ../Src/qk/%.c Src/qk/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DNUCLEO_C031C6 -DSTM32C031xx -DSTM32 -DSTM32C0 -DSTM32C031C6Tx -c -I../Inc -I"/home/jordan/Embedded projects/Audio_player/3rdParty/CMSIS/Include" -I"/home/jordan/Embedded projects/Audio_player/3rdParty/nucleo-c031c6" -I"/home/jordan/qp/qp/qpc/ports/arm-cm/qk/gnu" -I"/home/jordan/qp/qp/qpc/include" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-qk

clean-Src-2f-qk:
	-$(RM) ./Src/qk/qk.cyclo ./Src/qk/qk.d ./Src/qk/qk.o ./Src/qk/qk.su

.PHONY: clean-Src-2f-qk

