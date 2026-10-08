################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lwip/netif/ppp/auth.c \
../Core/lwip/netif/ppp/ccp.c \
../Core/lwip/netif/ppp/chap-md5.c \
../Core/lwip/netif/ppp/chap-new.c \
../Core/lwip/netif/ppp/chap_ms.c \
../Core/lwip/netif/ppp/demand.c \
../Core/lwip/netif/ppp/eap.c \
../Core/lwip/netif/ppp/ecp.c \
../Core/lwip/netif/ppp/eui64.c \
../Core/lwip/netif/ppp/fsm.c \
../Core/lwip/netif/ppp/ipcp.c \
../Core/lwip/netif/ppp/ipv6cp.c \
../Core/lwip/netif/ppp/lcp.c \
../Core/lwip/netif/ppp/magic.c \
../Core/lwip/netif/ppp/mppe.c \
../Core/lwip/netif/ppp/multilink.c \
../Core/lwip/netif/ppp/ppp.c \
../Core/lwip/netif/ppp/pppapi.c \
../Core/lwip/netif/ppp/pppcrypt.c \
../Core/lwip/netif/ppp/pppoe.c \
../Core/lwip/netif/ppp/pppol2tp.c \
../Core/lwip/netif/ppp/pppos.c \
../Core/lwip/netif/ppp/upap.c \
../Core/lwip/netif/ppp/utils.c \
../Core/lwip/netif/ppp/vj.c 

OBJS += \
./Core/lwip/netif/ppp/auth.o \
./Core/lwip/netif/ppp/ccp.o \
./Core/lwip/netif/ppp/chap-md5.o \
./Core/lwip/netif/ppp/chap-new.o \
./Core/lwip/netif/ppp/chap_ms.o \
./Core/lwip/netif/ppp/demand.o \
./Core/lwip/netif/ppp/eap.o \
./Core/lwip/netif/ppp/ecp.o \
./Core/lwip/netif/ppp/eui64.o \
./Core/lwip/netif/ppp/fsm.o \
./Core/lwip/netif/ppp/ipcp.o \
./Core/lwip/netif/ppp/ipv6cp.o \
./Core/lwip/netif/ppp/lcp.o \
./Core/lwip/netif/ppp/magic.o \
./Core/lwip/netif/ppp/mppe.o \
./Core/lwip/netif/ppp/multilink.o \
./Core/lwip/netif/ppp/ppp.o \
./Core/lwip/netif/ppp/pppapi.o \
./Core/lwip/netif/ppp/pppcrypt.o \
./Core/lwip/netif/ppp/pppoe.o \
./Core/lwip/netif/ppp/pppol2tp.o \
./Core/lwip/netif/ppp/pppos.o \
./Core/lwip/netif/ppp/upap.o \
./Core/lwip/netif/ppp/utils.o \
./Core/lwip/netif/ppp/vj.o 

C_DEPS += \
./Core/lwip/netif/ppp/auth.d \
./Core/lwip/netif/ppp/ccp.d \
./Core/lwip/netif/ppp/chap-md5.d \
./Core/lwip/netif/ppp/chap-new.d \
./Core/lwip/netif/ppp/chap_ms.d \
./Core/lwip/netif/ppp/demand.d \
./Core/lwip/netif/ppp/eap.d \
./Core/lwip/netif/ppp/ecp.d \
./Core/lwip/netif/ppp/eui64.d \
./Core/lwip/netif/ppp/fsm.d \
./Core/lwip/netif/ppp/ipcp.d \
./Core/lwip/netif/ppp/ipv6cp.d \
./Core/lwip/netif/ppp/lcp.d \
./Core/lwip/netif/ppp/magic.d \
./Core/lwip/netif/ppp/mppe.d \
./Core/lwip/netif/ppp/multilink.d \
./Core/lwip/netif/ppp/ppp.d \
./Core/lwip/netif/ppp/pppapi.d \
./Core/lwip/netif/ppp/pppcrypt.d \
./Core/lwip/netif/ppp/pppoe.d \
./Core/lwip/netif/ppp/pppol2tp.d \
./Core/lwip/netif/ppp/pppos.d \
./Core/lwip/netif/ppp/upap.d \
./Core/lwip/netif/ppp/utils.d \
./Core/lwip/netif/ppp/vj.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lwip/netif/ppp/%.o Core/lwip/netif/ppp/%.su Core/lwip/netif/ppp/%.cyclo: ../Core/lwip/netif/ppp/%.c Core/lwip/netif/ppp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Core/lwip/include" -I"C:/Users/gavin/Desktop/MRDT/Nucleo_Eth_Test/Drivers/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lwip-2f-netif-2f-ppp

clean-Core-2f-lwip-2f-netif-2f-ppp:
	-$(RM) ./Core/lwip/netif/ppp/auth.cyclo ./Core/lwip/netif/ppp/auth.d ./Core/lwip/netif/ppp/auth.o ./Core/lwip/netif/ppp/auth.su ./Core/lwip/netif/ppp/ccp.cyclo ./Core/lwip/netif/ppp/ccp.d ./Core/lwip/netif/ppp/ccp.o ./Core/lwip/netif/ppp/ccp.su ./Core/lwip/netif/ppp/chap-md5.cyclo ./Core/lwip/netif/ppp/chap-md5.d ./Core/lwip/netif/ppp/chap-md5.o ./Core/lwip/netif/ppp/chap-md5.su ./Core/lwip/netif/ppp/chap-new.cyclo ./Core/lwip/netif/ppp/chap-new.d ./Core/lwip/netif/ppp/chap-new.o ./Core/lwip/netif/ppp/chap-new.su ./Core/lwip/netif/ppp/chap_ms.cyclo ./Core/lwip/netif/ppp/chap_ms.d ./Core/lwip/netif/ppp/chap_ms.o ./Core/lwip/netif/ppp/chap_ms.su ./Core/lwip/netif/ppp/demand.cyclo ./Core/lwip/netif/ppp/demand.d ./Core/lwip/netif/ppp/demand.o ./Core/lwip/netif/ppp/demand.su ./Core/lwip/netif/ppp/eap.cyclo ./Core/lwip/netif/ppp/eap.d ./Core/lwip/netif/ppp/eap.o ./Core/lwip/netif/ppp/eap.su ./Core/lwip/netif/ppp/ecp.cyclo ./Core/lwip/netif/ppp/ecp.d ./Core/lwip/netif/ppp/ecp.o ./Core/lwip/netif/ppp/ecp.su ./Core/lwip/netif/ppp/eui64.cyclo ./Core/lwip/netif/ppp/eui64.d ./Core/lwip/netif/ppp/eui64.o ./Core/lwip/netif/ppp/eui64.su ./Core/lwip/netif/ppp/fsm.cyclo ./Core/lwip/netif/ppp/fsm.d ./Core/lwip/netif/ppp/fsm.o ./Core/lwip/netif/ppp/fsm.su ./Core/lwip/netif/ppp/ipcp.cyclo ./Core/lwip/netif/ppp/ipcp.d ./Core/lwip/netif/ppp/ipcp.o ./Core/lwip/netif/ppp/ipcp.su ./Core/lwip/netif/ppp/ipv6cp.cyclo ./Core/lwip/netif/ppp/ipv6cp.d ./Core/lwip/netif/ppp/ipv6cp.o ./Core/lwip/netif/ppp/ipv6cp.su ./Core/lwip/netif/ppp/lcp.cyclo ./Core/lwip/netif/ppp/lcp.d ./Core/lwip/netif/ppp/lcp.o ./Core/lwip/netif/ppp/lcp.su ./Core/lwip/netif/ppp/magic.cyclo ./Core/lwip/netif/ppp/magic.d ./Core/lwip/netif/ppp/magic.o ./Core/lwip/netif/ppp/magic.su ./Core/lwip/netif/ppp/mppe.cyclo ./Core/lwip/netif/ppp/mppe.d ./Core/lwip/netif/ppp/mppe.o ./Core/lwip/netif/ppp/mppe.su ./Core/lwip/netif/ppp/multilink.cyclo ./Core/lwip/netif/ppp/multilink.d ./Core/lwip/netif/ppp/multilink.o ./Core/lwip/netif/ppp/multilink.su ./Core/lwip/netif/ppp/ppp.cyclo ./Core/lwip/netif/ppp/ppp.d ./Core/lwip/netif/ppp/ppp.o ./Core/lwip/netif/ppp/ppp.su ./Core/lwip/netif/ppp/pppapi.cyclo ./Core/lwip/netif/ppp/pppapi.d ./Core/lwip/netif/ppp/pppapi.o ./Core/lwip/netif/ppp/pppapi.su ./Core/lwip/netif/ppp/pppcrypt.cyclo ./Core/lwip/netif/ppp/pppcrypt.d ./Core/lwip/netif/ppp/pppcrypt.o ./Core/lwip/netif/ppp/pppcrypt.su ./Core/lwip/netif/ppp/pppoe.cyclo ./Core/lwip/netif/ppp/pppoe.d ./Core/lwip/netif/ppp/pppoe.o ./Core/lwip/netif/ppp/pppoe.su ./Core/lwip/netif/ppp/pppol2tp.cyclo ./Core/lwip/netif/ppp/pppol2tp.d ./Core/lwip/netif/ppp/pppol2tp.o ./Core/lwip/netif/ppp/pppol2tp.su ./Core/lwip/netif/ppp/pppos.cyclo ./Core/lwip/netif/ppp/pppos.d ./Core/lwip/netif/ppp/pppos.o ./Core/lwip/netif/ppp/pppos.su ./Core/lwip/netif/ppp/upap.cyclo ./Core/lwip/netif/ppp/upap.d ./Core/lwip/netif/ppp/upap.o ./Core/lwip/netif/ppp/upap.su ./Core/lwip/netif/ppp/utils.cyclo ./Core/lwip/netif/ppp/utils.d ./Core/lwip/netif/ppp/utils.o ./Core/lwip/netif/ppp/utils.su ./Core/lwip/netif/ppp/vj.cyclo ./Core/lwip/netif/ppp/vj.d ./Core/lwip/netif/ppp/vj.o ./Core/lwip/netif/ppp/vj.su

.PHONY: clean-Core-2f-lwip-2f-netif-2f-ppp

