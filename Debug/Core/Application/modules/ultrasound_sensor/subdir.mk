################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Application/modules/ultrasound_sensor/ultrasound.c 

OBJS += \
./Core/Application/modules/ultrasound_sensor/ultrasound.o 

C_DEPS += \
./Core/Application/modules/ultrasound_sensor/ultrasound.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Application/modules/ultrasound_sensor/ultrasound.o: ../Core/Application/modules/ultrasound_sensor/ultrasound.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L162xD -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Core/Application/modules/temperature_measurement -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Core/Application/modules/hall -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Core/Application/modules/bluetooth_low_energy -I../Core/Application/modules/eeprom -I../Core/Application/modules/magnetometer -I../Core/Application/utility -I../Core/Application/runtime -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/Application/modules -I../Core/Application/modules/servo -I../Core/Application/modules/H_bridge -I../Core/Application/modules/state_machine -I../Drivers/CMSIS/Include -I../Core/Inc -I../Core/Application/runtime/device_init -I../Core/Application/runtime/tasks -I../Core/Application/modules/slotted_optocoupler -I../Core/Application/modules/ultrasound_sensor -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Application/modules/ultrasound_sensor/ultrasound.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

