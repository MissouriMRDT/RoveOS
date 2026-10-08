################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lwip/core/ipv6/dhcp6.c \
../Core/lwip/core/ipv6/ethip6.c \
../Core/lwip/core/ipv6/icmp6.c \
../Core/lwip/core/ipv6/inet6.c \
../Core/lwip/core/ipv6/ip6.c \
../Core/lwip/core/ipv6/ip6_addr.c \
../Core/lwip/core/ipv6/ip6_frag.c \
../Core/lwip/core/ipv6/mld6.c \
../Core/lwip/core/ipv6/nd6.c 

OBJS += \
./Core/lwip/core/ipv6/dhcp6.o \
./Core/lwip/core/ipv6/ethip6.o \
./Core/lwip/core/ipv6/icmp6.o \
./Core/lwip/core/ipv6/inet6.o \
./Core/lwip/core/ipv6/ip6.o \
./Core/lwip/core/ipv6/ip6_addr.o \
./Core/lwip/core/ipv6/ip6_frag.o \
./Core/lwip/core/ipv6/mld6.o \
./Core/lwip/core/ipv6/nd6.o 

C_DEPS += \
./Core/lwip/core/ipv6/dhcp6.d \
./Core/lwip/core/ipv6/ethip6.d \
./Core/lwip/core/ipv6/icmp6.d \
./Core/lwip/core/ipv6/inet6.d \
./Core/lwip/core/ipv6/ip6.d \
./Core/lwip/core/ipv6/ip6_addr.d \
./Core/lwip/core/ipv6/ip6_frag.d \
./Core/lwip/core/ipv6/mld6.d \
./Core/lwip/core/ipv6/nd6.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lwip/core/ipv6/%.o Core/lwip/core/ipv6/%.su Core/lwip/core/ipv6/%.cyclo: ../Core/lwip/core/ipv6/%.c Core/lwip/core/ipv6/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Core/lwip/include" -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Drivers/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lwip-2f-core-2f-ipv6

clean-Core-2f-lwip-2f-core-2f-ipv6:
	-$(RM) ./Core/lwip/core/ipv6/dhcp6.cyclo ./Core/lwip/core/ipv6/dhcp6.d ./Core/lwip/core/ipv6/dhcp6.o ./Core/lwip/core/ipv6/dhcp6.su ./Core/lwip/core/ipv6/ethip6.cyclo ./Core/lwip/core/ipv6/ethip6.d ./Core/lwip/core/ipv6/ethip6.o ./Core/lwip/core/ipv6/ethip6.su ./Core/lwip/core/ipv6/icmp6.cyclo ./Core/lwip/core/ipv6/icmp6.d ./Core/lwip/core/ipv6/icmp6.o ./Core/lwip/core/ipv6/icmp6.su ./Core/lwip/core/ipv6/inet6.cyclo ./Core/lwip/core/ipv6/inet6.d ./Core/lwip/core/ipv6/inet6.o ./Core/lwip/core/ipv6/inet6.su ./Core/lwip/core/ipv6/ip6.cyclo ./Core/lwip/core/ipv6/ip6.d ./Core/lwip/core/ipv6/ip6.o ./Core/lwip/core/ipv6/ip6.su ./Core/lwip/core/ipv6/ip6_addr.cyclo ./Core/lwip/core/ipv6/ip6_addr.d ./Core/lwip/core/ipv6/ip6_addr.o ./Core/lwip/core/ipv6/ip6_addr.su ./Core/lwip/core/ipv6/ip6_frag.cyclo ./Core/lwip/core/ipv6/ip6_frag.d ./Core/lwip/core/ipv6/ip6_frag.o ./Core/lwip/core/ipv6/ip6_frag.su ./Core/lwip/core/ipv6/mld6.cyclo ./Core/lwip/core/ipv6/mld6.d ./Core/lwip/core/ipv6/mld6.o ./Core/lwip/core/ipv6/mld6.su ./Core/lwip/core/ipv6/nd6.cyclo ./Core/lwip/core/ipv6/nd6.d ./Core/lwip/core/ipv6/nd6.o ./Core/lwip/core/ipv6/nd6.su

.PHONY: clean-Core-2f-lwip-2f-core-2f-ipv6

