################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/AudioPlayer_nucleo-c031c6/qk/bsp.c 

OBJS += \
./Src/AudioPlayer_nucleo-c031c6/qk/bsp.o 

C_DEPS += \
./Src/AudioPlayer_nucleo-c031c6/qk/bsp.d 


# Each subdirectory must supply rules for building sources it contributes
Src/AudioPlayer_nucleo-c031c6/qk/%.o Src/AudioPlayer_nucleo-c031c6/qk/%.su Src/AudioPlayer_nucleo-c031c6/qk/%.cyclo: ../Src/AudioPlayer_nucleo-c031c6/qk/%.c Src/AudioPlayer_nucleo-c031c6/qk/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DNUCLEO_C031C6 -DSTM32C031xx -DSTM32 -DSTM32C0 -DSTM32C031C6Tx -c -I../Inc -I"/home/jordan/Embedded projects/Audio_player/3rdParty/CMSIS/Include" -I"/home/jordan/Embedded projects/Audio_player/3rdParty/nucleo-c031c6" -I"/home/jordan/qp/qp/qpc/ports/arm-cm/qk/gnu" -I"/home/jordan/qp/qp/qpc/include" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-AudioPlayer_nucleo-2d-c031c6-2f-qk

clean-Src-2f-AudioPlayer_nucleo-2d-c031c6-2f-qk:
	-$(RM) ./Src/AudioPlayer_nucleo-c031c6/qk/bsp.cyclo ./Src/AudioPlayer_nucleo-c031c6/qk/bsp.d ./Src/AudioPlayer_nucleo-c031c6/qk/bsp.o ./Src/AudioPlayer_nucleo-c031c6/qk/bsp.su

.PHONY: clean-Src-2f-AudioPlayer_nucleo-2d-c031c6-2f-qk

