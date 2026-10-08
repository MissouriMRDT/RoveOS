################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lwip/netif/ppp/polarssl/arc4.c \
../Core/lwip/netif/ppp/polarssl/des.c \
../Core/lwip/netif/ppp/polarssl/md4.c \
../Core/lwip/netif/ppp/polarssl/md5.c \
../Core/lwip/netif/ppp/polarssl/sha1.c 

OBJS += \
./Core/lwip/netif/ppp/polarssl/arc4.o \
./Core/lwip/netif/ppp/polarssl/des.o \
./Core/lwip/netif/ppp/polarssl/md4.o \
./Core/lwip/netif/ppp/polarssl/md5.o \
./Core/lwip/netif/ppp/polarssl/sha1.o 

C_DEPS += \
./Core/lwip/netif/ppp/polarssl/arc4.d \
./Core/lwip/netif/ppp/polarssl/des.d \
./Core/lwip/netif/ppp/polarssl/md4.d \
./Core/lwip/netif/ppp/polarssl/md5.d \
./Core/lwip/netif/ppp/polarssl/sha1.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lwip/netif/ppp/polarssl/%.o Core/lwip/netif/ppp/polarssl/%.su Core/lwip/netif/ppp/polarssl/%.cyclo: ../Core/lwip/netif/ppp/polarssl/%.c Core/lwip/netif/ppp/polarssl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Core/lwip/include" -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Drivers/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lwip-2f-netif-2f-ppp-2f-polarssl

clean-Core-2f-lwip-2f-netif-2f-ppp-2f-polarssl:
	-$(RM) ./Core/lwip/netif/ppp/polarssl/arc4.cyclo ./Core/lwip/netif/ppp/polarssl/arc4.d ./Core/lwip/netif/ppp/polarssl/arc4.o ./Core/lwip/netif/ppp/polarssl/arc4.su ./Core/lwip/netif/ppp/polarssl/des.cyclo ./Core/lwip/netif/ppp/polarssl/des.d ./Core/lwip/netif/ppp/polarssl/des.o ./Core/lwip/netif/ppp/polarssl/des.su ./Core/lwip/netif/ppp/polarssl/md4.cyclo ./Core/lwip/netif/ppp/polarssl/md4.d ./Core/lwip/netif/ppp/polarssl/md4.o ./Core/lwip/netif/ppp/polarssl/md4.su ./Core/lwip/netif/ppp/polarssl/md5.cyclo ./Core/lwip/netif/ppp/polarssl/md5.d ./Core/lwip/netif/ppp/polarssl/md5.o ./Core/lwip/netif/ppp/polarssl/md5.su ./Core/lwip/netif/ppp/polarssl/sha1.cyclo ./Core/lwip/netif/ppp/polarssl/sha1.d ./Core/lwip/netif/ppp/polarssl/sha1.o ./Core/lwip/netif/ppp/polarssl/sha1.su

.PHONY: clean-Core-2f-lwip-2f-netif-2f-ppp-2f-polarssl

