################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lwip/include/ethernetif.c 

OBJS += \
./Core/lwip/include/ethernetif.o 

C_DEPS += \
./Core/lwip/include/ethernetif.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lwip/include/ethernetif.o: ../Core/lwip/include/ethernetif.c Core/lwip/include/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Core/lwip/include" -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Drivers/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lwip-2f-include

clean-Core-2f-lwip-2f-include:
	-$(RM) ./Core/lwip/include/ethernetif.cyclo ./Core/lwip/include/ethernetif.d ./Core/lwip/include/ethernetif.o ./Core/lwip/include/ethernetif.su

.PHONY: clean-Core-2f-lwip-2f-include

