################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Application/runtime/runtime.c \
../Core/Application/runtime/runtime_conf.c 

OBJS += \
./Core/Application/runtime/runtime.o \
./Core/Application/runtime/runtime_conf.o 

C_DEPS += \
./Core/Application/runtime/runtime.d \
./Core/Application/runtime/runtime_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Application/runtime/runtime.o: ../Core/Application/runtime/runtime.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L162xD -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I"E:/workplace/STM32/Automotive/Core/Application/runtime/device_init" -I"E:/workplace/STM32/Automotive/Core/Application/modules/magnetometer" -I"E:/workplace/STM32/Automotive/Core/Application/utility" -I"E:/workplace/STM32/Automotive/Core/Application/runtime" -I../Drivers/STM32L1xx_HAL_Driver/Inc -I"E:/workplace/STM32/Automotive/Core/Application/modules/H_bridge" -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I"E:/workplace/STM32/Automotive/Core/Application/modules/slotted_optocoupler" -I"E:/workplace/STM32/Automotive/Core/Application/runtime/tasks" -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I"E:/workplace/STM32/Automotive/Core/Application/modules/eeprom" -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"E:/workplace/STM32/Automotive/Core/Application/modules/proximity_sensor" -I../Drivers/CMSIS/Include -I../Core/Inc -I"E:/workplace/STM32/Automotive/Core/Application/modules" -I"E:/workplace/STM32/Automotive/Core/Application/modules/bluetooth_low_energy" -I"E:/workplace/STM32/Automotive/Core/Application/modules/state_machine" -I"E:/workplace/STM32/Automotive/Core/Application/modules/hall" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Application/runtime/runtime.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Application/runtime/runtime_conf.o: ../Core/Application/runtime/runtime_conf.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L162xD -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I"E:/workplace/STM32/Automotive/Core/Application/runtime/device_init" -I"E:/workplace/STM32/Automotive/Core/Application/modules/magnetometer" -I"E:/workplace/STM32/Automotive/Core/Application/utility" -I"E:/workplace/STM32/Automotive/Core/Application/runtime" -I../Drivers/STM32L1xx_HAL_Driver/Inc -I"E:/workplace/STM32/Automotive/Core/Application/modules/H_bridge" -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I"E:/workplace/STM32/Automotive/Core/Application/modules/slotted_optocoupler" -I"E:/workplace/STM32/Automotive/Core/Application/runtime/tasks" -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I"E:/workplace/STM32/Automotive/Core/Application/modules/eeprom" -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"E:/workplace/STM32/Automotive/Core/Application/modules/proximity_sensor" -I../Drivers/CMSIS/Include -I../Core/Inc -I"E:/workplace/STM32/Automotive/Core/Application/modules" -I"E:/workplace/STM32/Automotive/Core/Application/modules/bluetooth_low_energy" -I"E:/workplace/STM32/Automotive/Core/Application/modules/state_machine" -I"E:/workplace/STM32/Automotive/Core/Application/modules/hall" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Application/runtime/runtime_conf.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

