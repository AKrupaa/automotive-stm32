################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32L1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/Application/utility/subdir.mk
-include Core/Application/runtime/tasks/subdir.mk
-include Core/Application/runtime/device_init/subdir.mk
-include Core/Application/runtime/subdir.mk
-include Core/Application/modules/ultrasound_sensor/subdir.mk
-include Core/Application/modules/slotted_optocoupler/subdir.mk
-include Core/Application/modules/servo/subdir.mk
-include Core/Application/modules/magnetometer/subdir.mk
-include Core/Application/modules/hall/subdir.mk
-include Core/Application/modules/eeprom/subdir.mk
-include Core/Application/modules/bluetooth_low_energy/subdir.mk
-include Core/Application/modules/H_bridge/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Automotive.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Automotive.list \

OBJCOPY_BIN += \
Automotive.bin \


# All Target
all: Automotive.elf secondary-outputs

# Tool invocations
Automotive.elf: $(OBJS) $(USER_OBJS) E:\workplace\STM32\Automotive\STM32L162RDTX_FLASH.ld
	arm-none-eabi-gcc -o "Automotive.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\workplace\STM32\Automotive\STM32L162RDTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Automotive.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Automotive.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Automotive.list"
	@echo 'Finished building: $@'
	@echo ' '

Automotive.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Automotive.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
