################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lwip/core/ipv4/acd.c \
../Core/lwip/core/ipv4/autoip.c \
../Core/lwip/core/ipv4/dhcp.c \
../Core/lwip/core/ipv4/etharp.c \
../Core/lwip/core/ipv4/icmp.c \
../Core/lwip/core/ipv4/igmp.c \
../Core/lwip/core/ipv4/ip4.c \
../Core/lwip/core/ipv4/ip4_addr.c \
../Core/lwip/core/ipv4/ip4_frag.c 

OBJS += \
./Core/lwip/core/ipv4/acd.o \
./Core/lwip/core/ipv4/autoip.o \
./Core/lwip/core/ipv4/dhcp.o \
./Core/lwip/core/ipv4/etharp.o \
./Core/lwip/core/ipv4/icmp.o \
./Core/lwip/core/ipv4/igmp.o \
./Core/lwip/core/ipv4/ip4.o \
./Core/lwip/core/ipv4/ip4_addr.o \
./Core/lwip/core/ipv4/ip4_frag.o 

C_DEPS += \
./Core/lwip/core/ipv4/acd.d \
./Core/lwip/core/ipv4/autoip.d \
./Core/lwip/core/ipv4/dhcp.d \
./Core/lwip/core/ipv4/etharp.d \
./Core/lwip/core/ipv4/icmp.d \
./Core/lwip/core/ipv4/igmp.d \
./Core/lwip/core/ipv4/ip4.d \
./Core/lwip/core/ipv4/ip4_addr.d \
./Core/lwip/core/ipv4/ip4_frag.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lwip/core/ipv4/%.o Core/lwip/core/ipv4/%.su Core/lwip/core/ipv4/%.cyclo: ../Core/lwip/core/ipv4/%.c Core/lwip/core/ipv4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Core/lwip/include" -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Drivers/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lwip-2f-core-2f-ipv4

clean-Core-2f-lwip-2f-core-2f-ipv4:
	-$(RM) ./Core/lwip/core/ipv4/acd.cyclo ./Core/lwip/core/ipv4/acd.d ./Core/lwip/core/ipv4/acd.o ./Core/lwip/core/ipv4/acd.su ./Core/lwip/core/ipv4/autoip.cyclo ./Core/lwip/core/ipv4/autoip.d ./Core/lwip/core/ipv4/autoip.o ./Core/lwip/core/ipv4/autoip.su ./Core/lwip/core/ipv4/dhcp.cyclo ./Core/lwip/core/ipv4/dhcp.d ./Core/lwip/core/ipv4/dhcp.o ./Core/lwip/core/ipv4/dhcp.su ./Core/lwip/core/ipv4/etharp.cyclo ./Core/lwip/core/ipv4/etharp.d ./Core/lwip/core/ipv4/etharp.o ./Core/lwip/core/ipv4/etharp.su ./Core/lwip/core/ipv4/icmp.cyclo ./Core/lwip/core/ipv4/icmp.d ./Core/lwip/core/ipv4/icmp.o ./Core/lwip/core/ipv4/icmp.su ./Core/lwip/core/ipv4/igmp.cyclo ./Core/lwip/core/ipv4/igmp.d ./Core/lwip/core/ipv4/igmp.o ./Core/lwip/core/ipv4/igmp.su ./Core/lwip/core/ipv4/ip4.cyclo ./Core/lwip/core/ipv4/ip4.d ./Core/lwip/core/ipv4/ip4.o ./Core/lwip/core/ipv4/ip4.su ./Core/lwip/core/ipv4/ip4_addr.cyclo ./Core/lwip/core/ipv4/ip4_addr.d ./Core/lwip/core/ipv4/ip4_addr.o ./Core/lwip/core/ipv4/ip4_addr.su ./Core/lwip/core/ipv4/ip4_frag.cyclo ./Core/lwip/core/ipv4/ip4_frag.d ./Core/lwip/core/ipv4/ip4_frag.o ./Core/lwip/core/ipv4/ip4_frag.su

.PHONY: clean-Core-2f-lwip-2f-core-2f-ipv4

