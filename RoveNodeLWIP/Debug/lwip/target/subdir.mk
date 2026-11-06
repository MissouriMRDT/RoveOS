################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/target/ethernetif.c 

OBJS += \
./lwip/target/ethernetif.o 

C_DEPS += \
./lwip/target/ethernetif.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/target/%.o lwip/target/%.su lwip/target/%.cyclo: ../lwip/target/%.c lwip/target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"/Users/vexas/Documents/GitHub/RoveOS/RoveNodeLWIP/lwip" -I"/Users/vexas/Documents/GitHub/RoveOS/RoveNodeLWIP/lwip/app" -I"/Users/vexas/Documents/GitHub/RoveOS/RoveNodeLWIP/lwip/target" -I"/Users/vexas/Documents/GitHub/RoveOS/RoveNodeLWIP/src" -I"/Users/vexas/Documents/GitHub/RoveOS/RoveNodeLWIP/src/include" -I"/Users/vexas/Documents/GitHub/RoveOS/RoveNodeLWIP/system" -I"/Users/vexas/Documents/GitHub/RoveOS/RoveNodeLWIP/system/arch" -I"/Users/vexas/Documents/GitHub/RoveOS/RoveNodeLWIP/Drivers/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lwip-2f-target

clean-lwip-2f-target:
	-$(RM) ./lwip/target/ethernetif.cyclo ./lwip/target/ethernetif.d ./lwip/target/ethernetif.o ./lwip/target/ethernetif.su

.PHONY: clean-lwip-2f-target

