################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/qf/qep_hsm.c \
../Src/qf/qep_msm.c \
../Src/qf/qf_act.c \
../Src/qf/qf_actq.c \
../Src/qf/qf_defer.c \
../Src/qf/qf_dyn.c \
../Src/qf/qf_mem.c \
../Src/qf/qf_ps.c \
../Src/qf/qf_qact.c \
../Src/qf/qf_qeq.c \
../Src/qf/qf_qmact.c \
../Src/qf/qf_time.c 

OBJS += \
./Src/qf/qep_hsm.o \
./Src/qf/qep_msm.o \
./Src/qf/qf_act.o \
./Src/qf/qf_actq.o \
./Src/qf/qf_defer.o \
./Src/qf/qf_dyn.o \
./Src/qf/qf_mem.o \
./Src/qf/qf_ps.o \
./Src/qf/qf_qact.o \
./Src/qf/qf_qeq.o \
./Src/qf/qf_qmact.o \
./Src/qf/qf_time.o 

C_DEPS += \
./Src/qf/qep_hsm.d \
./Src/qf/qep_msm.d \
./Src/qf/qf_act.d \
./Src/qf/qf_actq.d \
./Src/qf/qf_defer.d \
./Src/qf/qf_dyn.d \
./Src/qf/qf_mem.d \
./Src/qf/qf_ps.d \
./Src/qf/qf_qact.d \
./Src/qf/qf_qeq.d \
./Src/qf/qf_qmact.d \
./Src/qf/qf_time.d 


# Each subdirectory must supply rules for building sources it contributes
Src/qf/%.o Src/qf/%.su Src/qf/%.cyclo: ../Src/qf/%.c Src/qf/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DNUCLEO_C031C6 -DSTM32 -DSTM32C031xx -DSTM32C0 -DSTM32C031C6Tx -USTM32C0 -UNUCLEO_C031C6 -USTM32 -USTM32C031C6Tx -USTM32C0 -c -I../Inc -I"/home/jordan/Embedded projects/Audio_player/3rdParty/CMSIS/Include" -I"/home/jordan/Embedded projects/Audio_player/3rdParty/nucleo-c031c6" -I"/home/jordan/qp/qp/qpc/ports/arm-cm/qk/gnu" -I"/home/jordan/qp/qp/qpc/include" -O0 -ffunction-sections -fdata-sections -Wall -fdata-sections -ffunction-sections -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-qf

clean-Src-2f-qf:
	-$(RM) ./Src/qf/qep_hsm.cyclo ./Src/qf/qep_hsm.d ./Src/qf/qep_hsm.o ./Src/qf/qep_hsm.su ./Src/qf/qep_msm.cyclo ./Src/qf/qep_msm.d ./Src/qf/qep_msm.o ./Src/qf/qep_msm.su ./Src/qf/qf_act.cyclo ./Src/qf/qf_act.d ./Src/qf/qf_act.o ./Src/qf/qf_act.su ./Src/qf/qf_actq.cyclo ./Src/qf/qf_actq.d ./Src/qf/qf_actq.o ./Src/qf/qf_actq.su ./Src/qf/qf_defer.cyclo ./Src/qf/qf_defer.d ./Src/qf/qf_defer.o ./Src/qf/qf_defer.su ./Src/qf/qf_dyn.cyclo ./Src/qf/qf_dyn.d ./Src/qf/qf_dyn.o ./Src/qf/qf_dyn.su ./Src/qf/qf_mem.cyclo ./Src/qf/qf_mem.d ./Src/qf/qf_mem.o ./Src/qf/qf_mem.su ./Src/qf/qf_ps.cyclo ./Src/qf/qf_ps.d ./Src/qf/qf_ps.o ./Src/qf/qf_ps.su ./Src/qf/qf_qact.cyclo ./Src/qf/qf_qact.d ./Src/qf/qf_qact.o ./Src/qf/qf_qact.su ./Src/qf/qf_qeq.cyclo ./Src/qf/qf_qeq.d ./Src/qf/qf_qeq.o ./Src/qf/qf_qeq.su ./Src/qf/qf_qmact.cyclo ./Src/qf/qf_qmact.d ./Src/qf/qf_qmact.o ./Src/qf/qf_qmact.su ./Src/qf/qf_time.cyclo ./Src/qf/qf_time.d ./Src/qf/qf_time.o ./Src/qf/qf_time.su

.PHONY: clean-Src-2f-qf

