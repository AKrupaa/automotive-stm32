################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Application/runtime/tasks/task_ble.c \
../Core/Application/runtime/tasks/task_eyes.c \
../Core/Application/runtime/tasks/task_memory.c \
../Core/Application/runtime/tasks/task_sensors.c \
../Core/Application/runtime/tasks/task_state_machine.c 

OBJS += \
./Core/Application/runtime/tasks/task_ble.o \
./Core/Application/runtime/tasks/task_eyes.o \
./Core/Application/runtime/tasks/task_memory.o \
./Core/Application/runtime/tasks/task_sensors.o \
./Core/Application/runtime/tasks/task_state_machine.o 

C_DEPS += \
./Core/Application/runtime/tasks/task_ble.d \
./Core/Application/runtime/tasks/task_eyes.d \
./Core/Application/runtime/tasks/task_memory.d \
./Core/Application/runtime/tasks/task_sensors.d \
./Core/Application/runtime/tasks/task_state_machine.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Application/runtime/tasks/task_ble.o: ../Core/Application/runtime/tasks/task_ble.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L162xD -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Core/Application/modules/temperature_measurement -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Core/Application/modules/hall -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Core/Application/modules/bluetooth_low_energy -I../Core/Application/modules/eeprom -I../Core/Application/modules/magnetometer -I../Core/Application/utility -I../Core/Application/runtime -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/Application/modules -I../Core/Application/modules/servo -I../Core/Application/modules/H_bridge -I../Core/Application/modules/state_machine -I../Drivers/CMSIS/Include -I../Core/Inc -I../Core/Application/runtime/device_init -I../Core/Application/runtime/tasks -I../Core/Application/modules/slotted_optocoupler -I../Core/Application/modules/ultrasound_sensor -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Application/runtime/tasks/task_ble.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Application/runtime/tasks/task_eyes.o: ../Core/Application/runtime/tasks/task_eyes.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L162xD -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Core/Application/modules/temperature_measurement -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Core/Application/modules/hall -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Core/Application/modules/bluetooth_low_energy -I../Core/Application/modules/eeprom -I../Core/Application/modules/magnetometer -I../Core/Application/utility -I../Core/Application/runtime -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/Application/modules -I../Core/Application/modules/servo -I../Core/Application/modules/H_bridge -I../Core/Application/modules/state_machine -I../Drivers/CMSIS/Include -I../Core/Inc -I../Core/Application/runtime/device_init -I../Core/Application/runtime/tasks -I../Core/Application/modules/slotted_optocoupler -I../Core/Application/modules/ultrasound_sensor -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Application/runtime/tasks/task_eyes.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Application/runtime/tasks/task_memory.o: ../Core/Application/runtime/tasks/task_memory.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L162xD -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Core/Application/modules/temperature_measurement -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Core/Application/modules/hall -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Core/Application/modules/bluetooth_low_energy -I../Core/Application/modules/eeprom -I../Core/Application/modules/magnetometer -I../Core/Application/utility -I../Core/Application/runtime -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/Application/modules -I../Core/Application/modules/servo -I../Core/Application/modules/H_bridge -I../Core/Application/modules/state_machine -I../Drivers/CMSIS/Include -I../Core/Inc -I../Core/Application/runtime/device_init -I../Core/Application/runtime/tasks -I../Core/Application/modules/slotted_optocoupler -I../Core/Application/modules/ultrasound_sensor -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Application/runtime/tasks/task_memory.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Application/runtime/tasks/task_sensors.o: ../Core/Application/runtime/tasks/task_sensors.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L162xD -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Core/Application/modules/temperature_measurement -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Core/Application/modules/hall -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Core/Application/modules/bluetooth_low_energy -I../Core/Application/modules/eeprom -I../Core/Application/modules/magnetometer -I../Core/Application/utility -I../Core/Application/runtime -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/Application/modules -I../Core/Application/modules/servo -I../Core/Application/modules/H_bridge -I../Core/Application/modules/state_machine -I../Drivers/CMSIS/Include -I../Core/Inc -I../Core/Application/runtime/device_init -I../Core/Application/runtime/tasks -I../Core/Application/modules/slotted_optocoupler -I../Core/Application/modules/ultrasound_sensor -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Application/runtime/tasks/task_sensors.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Application/runtime/tasks/task_state_machine.o: ../Core/Application/runtime/tasks/task_state_machine.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L162xD -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Core/Application/modules/temperature_measurement -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Core/Application/modules/hall -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Core/Application/modules/bluetooth_low_energy -I../Core/Application/modules/eeprom -I../Core/Application/modules/magnetometer -I../Core/Application/utility -I../Core/Application/runtime -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/Application/modules -I../Core/Application/modules/servo -I../Core/Application/modules/H_bridge -I../Core/Application/modules/state_machine -I../Drivers/CMSIS/Include -I../Core/Inc -I../Core/Application/runtime/device_init -I../Core/Application/runtime/tasks -I../Core/Application/modules/slotted_optocoupler -I../Core/Application/modules/ultrasound_sensor -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Application/runtime/tasks/task_state_machine.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

