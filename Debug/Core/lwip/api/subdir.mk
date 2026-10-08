################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lwip/api/api_lib.c \
../Core/lwip/api/api_msg.c \
../Core/lwip/api/err.c \
../Core/lwip/api/if_api.c \
../Core/lwip/api/netbuf.c \
../Core/lwip/api/netdb.c \
../Core/lwip/api/netifapi.c \
../Core/lwip/api/sockets.c \
../Core/lwip/api/tcpip.c 

OBJS += \
./Core/lwip/api/api_lib.o \
./Core/lwip/api/api_msg.o \
./Core/lwip/api/err.o \
./Core/lwip/api/if_api.o \
./Core/lwip/api/netbuf.o \
./Core/lwip/api/netdb.o \
./Core/lwip/api/netifapi.o \
./Core/lwip/api/sockets.o \
./Core/lwip/api/tcpip.o 

C_DEPS += \
./Core/lwip/api/api_lib.d \
./Core/lwip/api/api_msg.d \
./Core/lwip/api/err.d \
./Core/lwip/api/if_api.d \
./Core/lwip/api/netbuf.d \
./Core/lwip/api/netdb.d \
./Core/lwip/api/netifapi.d \
./Core/lwip/api/sockets.d \
./Core/lwip/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lwip/api/%.o Core/lwip/api/%.su Core/lwip/api/%.cyclo: ../Core/lwip/api/%.c Core/lwip/api/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Core/lwip/include" -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Drivers/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lwip-2f-api

clean-Core-2f-lwip-2f-api:
	-$(RM) ./Core/lwip/api/api_lib.cyclo ./Core/lwip/api/api_lib.d ./Core/lwip/api/api_lib.o ./Core/lwip/api/api_lib.su ./Core/lwip/api/api_msg.cyclo ./Core/lwip/api/api_msg.d ./Core/lwip/api/api_msg.o ./Core/lwip/api/api_msg.su ./Core/lwip/api/err.cyclo ./Core/lwip/api/err.d ./Core/lwip/api/err.o ./Core/lwip/api/err.su ./Core/lwip/api/if_api.cyclo ./Core/lwip/api/if_api.d ./Core/lwip/api/if_api.o ./Core/lwip/api/if_api.su ./Core/lwip/api/netbuf.cyclo ./Core/lwip/api/netbuf.d ./Core/lwip/api/netbuf.o ./Core/lwip/api/netbuf.su ./Core/lwip/api/netdb.cyclo ./Core/lwip/api/netdb.d ./Core/lwip/api/netdb.o ./Core/lwip/api/netdb.su ./Core/lwip/api/netifapi.cyclo ./Core/lwip/api/netifapi.d ./Core/lwip/api/netifapi.o ./Core/lwip/api/netifapi.su ./Core/lwip/api/sockets.cyclo ./Core/lwip/api/sockets.d ./Core/lwip/api/sockets.o ./Core/lwip/api/sockets.su ./Core/lwip/api/tcpip.cyclo ./Core/lwip/api/tcpip.d ./Core/lwip/api/tcpip.o ./Core/lwip/api/tcpip.su

.PHONY: clean-Core-2f-lwip-2f-api

