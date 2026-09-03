################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include system/OS/subdir.mk
-include src/netif/ppp/polarssl/subdir.mk
-include src/netif/ppp/subdir.mk
-include src/netif/subdir.mk
-include src/core/ipv6/subdir.mk
-include src/core/ipv4/subdir.mk
-include src/core/subdir.mk
-include src/api/subdir.mk
-include lwip/target/subdir.mk
-include lwip/app/subdir.mk
-include Drivers/STM32H5xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := RoveNodeLWIP
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
RoveNodeLWIP.elf \

MAP_FILES += \
RoveNodeLWIP.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
RoveNodeLWIP.list \


# All Target
all: main-build

# Main-build Target
main-build: RoveNodeLWIP.elf secondary-outputs

# Tool invocations
RoveNodeLWIP.elf RoveNodeLWIP.map: $(OBJS) $(USER_OBJS) C:\Users\fanta\OneDrive\Documents\Nucleo\ Test\ Ping\RoveNodeLWIP\RoveNodeLWIP\STM32H563RITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "RoveNodeLWIP.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m33 -T"C:\Users\fanta\OneDrive\Documents\Nucleo Test Ping\RoveNodeLWIP\RoveNodeLWIP\STM32H563RITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="RoveNodeLWIP.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

RoveNodeLWIP.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "RoveNodeLWIP.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) RoveNodeLWIP.elf RoveNodeLWIP.list RoveNodeLWIP.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
