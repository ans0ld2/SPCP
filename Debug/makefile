################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Code/VA_Modbus/subdir.mk
-include Code/VA_GUI/Window/subdir.mk
-include Code/VA_GUI/Screens/subdir.mk
-include Code/VA_GUI/Geometric/subdir.mk
-include Code/VA_GUI/Fonts/TimesNewRoman/subdir.mk
-include Code/VA_GUI/Fonts/subdir.mk
-include Code/VA_GUI/Elements/VALabel/subdir.mk
-include Code/VA_GUI/Elements/VAKeyboard/subdir.mk
-include Code/VA_GUI/Elements/VAIndicator/subdir.mk
-include Code/VA_GUI/Elements/VADisplay/subdir.mk
-include Code/VA_GUI/Elements/VACanvas/subdir.mk
-include Code/VA_GUI/Elements/VAButton/subdir.mk
-include Code/VA_GUI/Elements/Graphics/subdir.mk
-include Code/VA_GUI/Elements/subdir.mk
-include Code/VA_GUI/Adafruit_RA8875/subdir.mk
-include Code/VA_GUI/subdir.mk
-include Code/VA_EEPROM_AT25640/subdir.mk
-include Code/Screens/subdir.mk
-include Code/Devices/subdir.mk
-include Code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

BUILD_ARTIFACT_NAME := SensorPanelPK_DebagPK
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SensorPanelPK_DebagPK.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SensorPanelPK_DebagPK.list \

OBJCOPY_BIN += \
SensorPanelPK_DebagPK.bin \


# All Target
all: main-build

# Main-build Target
main-build: SensorPanelPK_DebagPK.elf secondary-outputs

# Tool invocations
SensorPanelPK_DebagPK.elf: $(OBJS) $(USER_OBJS) D:\SensorPanelPK_DebagPK\ B130\SensorPanelPK_DebagPK\STM32F746ZETX_FLASH.ld
	arm-none-eabi-g++ -o "SensorPanelPK_DebagPK.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"D:\SensorPanelPK_DebagPK B130\SensorPanelPK_DebagPK\STM32F746ZETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SensorPanelPK_DebagPK.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SensorPanelPK_DebagPK.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SensorPanelPK_DebagPK.list"
	@echo 'Finished building: $@'
	@echo ' '

SensorPanelPK_DebagPK.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "SensorPanelPK_DebagPK.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
