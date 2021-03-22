################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRoman.c \
../Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanBold.c \
../Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanItalic.c \
../Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanNormal.c 

C_DEPS += \
./Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRoman.d \
./Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanBold.d \
./Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanItalic.d \
./Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanNormal.d 

OBJS += \
./Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRoman.o \
./Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanBold.o \
./Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanItalic.o \
./Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanNormal.o 


# Each subdirectory must supply rules for building sources it contributes
Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRoman.o: ../Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRoman.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DDEBUG -c -I../Core/Inc -I../Code/Devices -I../Code -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -Os -ffunction-sections -fdata-sections -mslow-flash-data -Wall -fstack-usage -MMD -MP -MF"Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRoman.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanBold.o: ../Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanBold.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DDEBUG -c -I../Core/Inc -I../Code/Devices -I../Code -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -Os -ffunction-sections -fdata-sections -mslow-flash-data -Wall -fstack-usage -MMD -MP -MF"Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanBold.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanItalic.o: ../Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanItalic.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DDEBUG -c -I../Core/Inc -I../Code/Devices -I../Code -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -Os -ffunction-sections -fdata-sections -mslow-flash-data -Wall -fstack-usage -MMD -MP -MF"Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanItalic.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanNormal.o: ../Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanNormal.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DDEBUG -c -I../Core/Inc -I../Code/Devices -I../Code -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -Os -ffunction-sections -fdata-sections -mslow-flash-data -Wall -fstack-usage -MMD -MP -MF"Code/VA_GUI/Fonts/TimesNewRoman/TimesNewRomanNormal.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

