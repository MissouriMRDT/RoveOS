################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lwip/core/altcp.c \
../Core/lwip/core/altcp_alloc.c \
../Core/lwip/core/altcp_tcp.c \
../Core/lwip/core/def.c \
../Core/lwip/core/dns.c \
../Core/lwip/core/inet_chksum.c \
../Core/lwip/core/init.c \
../Core/lwip/core/ip.c \
../Core/lwip/core/mem.c \
../Core/lwip/core/memp.c \
../Core/lwip/core/netif.c \
../Core/lwip/core/pbuf.c \
../Core/lwip/core/raw.c \
../Core/lwip/core/stats.c \
../Core/lwip/core/sys.c \
../Core/lwip/core/tcp.c \
../Core/lwip/core/tcp_in.c \
../Core/lwip/core/tcp_out.c \
../Core/lwip/core/timeouts.c \
../Core/lwip/core/udp.c 

OBJS += \
./Core/lwip/core/altcp.o \
./Core/lwip/core/altcp_alloc.o \
./Core/lwip/core/altcp_tcp.o \
./Core/lwip/core/def.o \
./Core/lwip/core/dns.o \
./Core/lwip/core/inet_chksum.o \
./Core/lwip/core/init.o \
./Core/lwip/core/ip.o \
./Core/lwip/core/mem.o \
./Core/lwip/core/memp.o \
./Core/lwip/core/netif.o \
./Core/lwip/core/pbuf.o \
./Core/lwip/core/raw.o \
./Core/lwip/core/stats.o \
./Core/lwip/core/sys.o \
./Core/lwip/core/tcp.o \
./Core/lwip/core/tcp_in.o \
./Core/lwip/core/tcp_out.o \
./Core/lwip/core/timeouts.o \
./Core/lwip/core/udp.o 

C_DEPS += \
./Core/lwip/core/altcp.d \
./Core/lwip/core/altcp_alloc.d \
./Core/lwip/core/altcp_tcp.d \
./Core/lwip/core/def.d \
./Core/lwip/core/dns.d \
./Core/lwip/core/inet_chksum.d \
./Core/lwip/core/init.d \
./Core/lwip/core/ip.d \
./Core/lwip/core/mem.d \
./Core/lwip/core/memp.d \
./Core/lwip/core/netif.d \
./Core/lwip/core/pbuf.d \
./Core/lwip/core/raw.d \
./Core/lwip/core/stats.d \
./Core/lwip/core/sys.d \
./Core/lwip/core/tcp.d \
./Core/lwip/core/tcp_in.d \
./Core/lwip/core/tcp_out.d \
./Core/lwip/core/timeouts.d \
./Core/lwip/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lwip/core/%.o Core/lwip/core/%.su Core/lwip/core/%.cyclo: ../Core/lwip/core/%.c Core/lwip/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Core/lwip/include" -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Drivers/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lwip-2f-core

clean-Core-2f-lwip-2f-core:
	-$(RM) ./Core/lwip/core/altcp.cyclo ./Core/lwip/core/altcp.d ./Core/lwip/core/altcp.o ./Core/lwip/core/altcp.su ./Core/lwip/core/altcp_alloc.cyclo ./Core/lwip/core/altcp_alloc.d ./Core/lwip/core/altcp_alloc.o ./Core/lwip/core/altcp_alloc.su ./Core/lwip/core/altcp_tcp.cyclo ./Core/lwip/core/altcp_tcp.d ./Core/lwip/core/altcp_tcp.o ./Core/lwip/core/altcp_tcp.su ./Core/lwip/core/def.cyclo ./Core/lwip/core/def.d ./Core/lwip/core/def.o ./Core/lwip/core/def.su ./Core/lwip/core/dns.cyclo ./Core/lwip/core/dns.d ./Core/lwip/core/dns.o ./Core/lwip/core/dns.su ./Core/lwip/core/inet_chksum.cyclo ./Core/lwip/core/inet_chksum.d ./Core/lwip/core/inet_chksum.o ./Core/lwip/core/inet_chksum.su ./Core/lwip/core/init.cyclo ./Core/lwip/core/init.d ./Core/lwip/core/init.o ./Core/lwip/core/init.su ./Core/lwip/core/ip.cyclo ./Core/lwip/core/ip.d ./Core/lwip/core/ip.o ./Core/lwip/core/ip.su ./Core/lwip/core/mem.cyclo ./Core/lwip/core/mem.d ./Core/lwip/core/mem.o ./Core/lwip/core/mem.su ./Core/lwip/core/memp.cyclo ./Core/lwip/core/memp.d ./Core/lwip/core/memp.o ./Core/lwip/core/memp.su ./Core/lwip/core/netif.cyclo ./Core/lwip/core/netif.d ./Core/lwip/core/netif.o ./Core/lwip/core/netif.su ./Core/lwip/core/pbuf.cyclo ./Core/lwip/core/pbuf.d ./Core/lwip/core/pbuf.o ./Core/lwip/core/pbuf.su ./Core/lwip/core/raw.cyclo ./Core/lwip/core/raw.d ./Core/lwip/core/raw.o ./Core/lwip/core/raw.su ./Core/lwip/core/stats.cyclo ./Core/lwip/core/stats.d ./Core/lwip/core/stats.o ./Core/lwip/core/stats.su ./Core/lwip/core/sys.cyclo ./Core/lwip/core/sys.d ./Core/lwip/core/sys.o ./Core/lwip/core/sys.su ./Core/lwip/core/tcp.cyclo ./Core/lwip/core/tcp.d ./Core/lwip/core/tcp.o ./Core/lwip/core/tcp.su ./Core/lwip/core/tcp_in.cyclo ./Core/lwip/core/tcp_in.d ./Core/lwip/core/tcp_in.o ./Core/lwip/core/tcp_in.su ./Core/lwip/core/tcp_out.cyclo ./Core/lwip/core/tcp_out.d ./Core/lwip/core/tcp_out.o ./Core/lwip/core/tcp_out.su ./Core/lwip/core/timeouts.cyclo ./Core/lwip/core/timeouts.d ./Core/lwip/core/timeouts.o ./Core/lwip/core/timeouts.su ./Core/lwip/core/udp.cyclo ./Core/lwip/core/udp.d ./Core/lwip/core/udp.o ./Core/lwip/core/udp.su

.PHONY: clean-Core-2f-lwip-2f-core

