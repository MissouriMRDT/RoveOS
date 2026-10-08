################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lwip/netif/bridgeif.c \
../Core/lwip/netif/bridgeif_fdb.c \
../Core/lwip/netif/ethernet.c \
../Core/lwip/netif/lowpan6.c \
../Core/lwip/netif/lowpan6_ble.c \
../Core/lwip/netif/lowpan6_common.c \
../Core/lwip/netif/slipif.c \
../Core/lwip/netif/zepif.c 

OBJS += \
./Core/lwip/netif/bridgeif.o \
./Core/lwip/netif/bridgeif_fdb.o \
./Core/lwip/netif/ethernet.o \
./Core/lwip/netif/lowpan6.o \
./Core/lwip/netif/lowpan6_ble.o \
./Core/lwip/netif/lowpan6_common.o \
./Core/lwip/netif/slipif.o \
./Core/lwip/netif/zepif.o 

C_DEPS += \
./Core/lwip/netif/bridgeif.d \
./Core/lwip/netif/bridgeif_fdb.d \
./Core/lwip/netif/ethernet.d \
./Core/lwip/netif/lowpan6.d \
./Core/lwip/netif/lowpan6_ble.d \
./Core/lwip/netif/lowpan6_common.d \
./Core/lwip/netif/slipif.d \
./Core/lwip/netif/zepif.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lwip/netif/%.o Core/lwip/netif/%.su Core/lwip/netif/%.cyclo: ../Core/lwip/netif/%.c Core/lwip/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Core/lwip/include" -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Drivers/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lwip-2f-netif

clean-Core-2f-lwip-2f-netif:
	-$(RM) ./Core/lwip/netif/bridgeif.cyclo ./Core/lwip/netif/bridgeif.d ./Core/lwip/netif/bridgeif.o ./Core/lwip/netif/bridgeif.su ./Core/lwip/netif/bridgeif_fdb.cyclo ./Core/lwip/netif/bridgeif_fdb.d ./Core/lwip/netif/bridgeif_fdb.o ./Core/lwip/netif/bridgeif_fdb.su ./Core/lwip/netif/ethernet.cyclo ./Core/lwip/netif/ethernet.d ./Core/lwip/netif/ethernet.o ./Core/lwip/netif/ethernet.su ./Core/lwip/netif/lowpan6.cyclo ./Core/lwip/netif/lowpan6.d ./Core/lwip/netif/lowpan6.o ./Core/lwip/netif/lowpan6.su ./Core/lwip/netif/lowpan6_ble.cyclo ./Core/lwip/netif/lowpan6_ble.d ./Core/lwip/netif/lowpan6_ble.o ./Core/lwip/netif/lowpan6_ble.su ./Core/lwip/netif/lowpan6_common.cyclo ./Core/lwip/netif/lowpan6_common.d ./Core/lwip/netif/lowpan6_common.o ./Core/lwip/netif/lowpan6_common.su ./Core/lwip/netif/slipif.cyclo ./Core/lwip/netif/slipif.d ./Core/lwip/netif/slipif.o ./Core/lwip/netif/slipif.su ./Core/lwip/netif/zepif.cyclo ./Core/lwip/netif/zepif.d ./Core/lwip/netif/zepif.o ./Core/lwip/netif/zepif.su

.PHONY: clean-Core-2f-lwip-2f-netif

