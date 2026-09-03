################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/lan8742.c 

OBJS += \
./Drivers/BSP/lan8742.o 

C_DEPS += \
./Drivers/BSP/lan8742.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/%.o Drivers/BSP/%.su Drivers/BSP/%.cyclo: ../Drivers/BSP/%.c Drivers/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/fanta/OneDrive/Documents/Nucleo Test Ping/RoveNodeLWIP/RoveNodeLWIP/lwip" -I"C:/Users/fanta/OneDrive/Documents/Nucleo Test Ping/RoveNodeLWIP/RoveNodeLWIP/lwip/app" -I"C:/Users/fanta/OneDrive/Documents/Nucleo Test Ping/RoveNodeLWIP/RoveNodeLWIP/lwip/target" -I"C:/Users/fanta/OneDrive/Documents/Nucleo Test Ping/RoveNodeLWIP/RoveNodeLWIP/src" -I"C:/Users/fanta/OneDrive/Documents/Nucleo Test Ping/RoveNodeLWIP/RoveNodeLWIP/src/include" -I"C:/Users/fanta/OneDrive/Documents/Nucleo Test Ping/RoveNodeLWIP/RoveNodeLWIP/system" -I"C:/Users/fanta/OneDrive/Documents/Nucleo Test Ping/RoveNodeLWIP/RoveNodeLWIP/system/arch" -I"C:/Users/fanta/OneDrive/Documents/Nucleo Test Ping/RoveNodeLWIP/RoveNodeLWIP/Drivers/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP

clean-Drivers-2f-BSP:
	-$(RM) ./Drivers/BSP/lan8742.cyclo ./Drivers/BSP/lan8742.d ./Drivers/BSP/lan8742.o ./Drivers/BSP/lan8742.su

.PHONY: clean-Drivers-2f-BSP

