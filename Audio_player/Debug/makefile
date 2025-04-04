################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/qs/subdir.mk
-include Src/qk/subdir.mk
-include Src/qf/subdir.mk
-include Src/QPC_PORT/subdir.mk
-include Src/AudioPlayer_nucleo-c031c6/qk/subdir.mk
-include Src/AudioPlayer_nucleo-c031c6/subdir.mk
-include 3rdParty/nucleo-c031c6/nucleo-c031c6/subdir.mk
-include 3rdParty/nucleo-c031c6/gnu/subdir.mk
-include 3rdParty/nucleo-c031c6/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := dpp_Try_2
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
dpp_Try_2.elf \

MAP_FILES += \
dpp_Try_2.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
dpp_Try_2.list \


# All Target
all: main-build

# Main-build Target
main-build: dpp_Try_2.elf secondary-outputs

# Tool invocations
dpp_Try_2.elf dpp_Try_2.map: $(OBJS) $(USER_OBJS) /home/jordan/STM32CubeIDE/workspace_1.18.0/dpp_Try_2/3rdParty/nucleo-c031c6/gnu/nucleo-c031c6.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "dpp_Try_2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"/home/jordan/STM32CubeIDE/workspace_1.18.0/dpp_Try_2/3rdParty/nucleo-c031c6/gnu/nucleo-c031c6.ld" --specs=nosys.specs -Wl,-Map="dpp_Try_2.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

dpp_Try_2.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "dpp_Try_2.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout dpp_Try_2.elf dpp_Try_2.list dpp_Try_2.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
