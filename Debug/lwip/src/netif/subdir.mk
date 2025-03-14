################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/netif/bridgeif.c \
../lwip/src/netif/bridgeif_fdb.c \
../lwip/src/netif/ethernet.c \
../lwip/src/netif/lowpan6.c \
../lwip/src/netif/lowpan6_ble.c \
../lwip/src/netif/lowpan6_common.c \
../lwip/src/netif/slipif.c \
../lwip/src/netif/zepif.c 

C_DEPS += \
./lwip/src/netif/bridgeif.d \
./lwip/src/netif/bridgeif_fdb.d \
./lwip/src/netif/ethernet.d \
./lwip/src/netif/lowpan6.d \
./lwip/src/netif/lowpan6_ble.d \
./lwip/src/netif/lowpan6_common.d \
./lwip/src/netif/slipif.d \
./lwip/src/netif/zepif.d 

OBJS += \
./lwip/src/netif/bridgeif.o \
./lwip/src/netif/bridgeif_fdb.o \
./lwip/src/netif/ethernet.o \
./lwip/src/netif/lowpan6.o \
./lwip/src/netif/lowpan6_ble.o \
./lwip/src/netif/lowpan6_common.o \
./lwip/src/netif/slipif.o \
./lwip/src/netif/zepif.o 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/netif/%.o: ../lwip/src/netif/%.c lwip/src/netif/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_RW612ETA2I -DCPU_RW612ETA2I_cm33_nodsp -DMCUXPRESSO_SDK -D_POSIX_SOURCE -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DUSE_RTOS=1 -DPRINTF_ADVANCED_ENABLE=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DBOOT_HEADER_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -DWIFI_BOARD_RW610 -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DLWIP_SUPPORT_CUSTOM_PBUF=1 -DCHECKSUM_GEN_UDP=1 -DCHECKSUM_GEN_TCP=1 -DCHECKSUM_GEN_ICMP=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_UDP=1 -DCHECKSUM_CHECK_TCP=1 -DCHECKSUM_CHECK_ICMP=1 -DCHECKSUM_CHECK_ICMP6=1 -DSDK_OS_FREE_RTOS -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\source" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\flash_config" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\drivers" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\CMSIS" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\CMSIS\m-profile" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\device" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\device\periph" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\utilities" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\lists" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\utilities\str" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\utilities\debug_console" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\serial_manager" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\gpio" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\uart" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClBuffer\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClBuffer\inc\internal" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClCore\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClEls\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClEls\inc\internal" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClMemory\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClMemory\inc\internal" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslMemory\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslMemory\inc\internal" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslCPreProcessor\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslDataIntegrity\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslFlowProtection\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslParamIntegrity\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslSecureCounter\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\compiler" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\platforms\rw61x" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\platforms\rw61x\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\includes\platform\rw61x" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\phy" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\silicon_id" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\lwip\port" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\lwip\src" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\lwip\src\include" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\lwip\src\include\lwip" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\lwip\port\sys_arch\dynamic" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\lwip\src\include\lwip\apps" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\freertos\freertos-kernel\include" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\freertos\freertos-kernel\portable\GCC\ARM_CM33_NTZ\non_secure" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\board" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\freertos\freertos-kernel\template" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\freertos\freertos-kernel\template\ARM_CM33_3_priority_bits" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -fno-builtin -mcpu=cortex-m33+nodsp -imacros "C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lwip-2f-src-2f-netif

clean-lwip-2f-src-2f-netif:
	-$(RM) ./lwip/src/netif/bridgeif.d ./lwip/src/netif/bridgeif.o ./lwip/src/netif/bridgeif_fdb.d ./lwip/src/netif/bridgeif_fdb.o ./lwip/src/netif/ethernet.d ./lwip/src/netif/ethernet.o ./lwip/src/netif/lowpan6.d ./lwip/src/netif/lowpan6.o ./lwip/src/netif/lowpan6_ble.d ./lwip/src/netif/lowpan6_ble.o ./lwip/src/netif/lowpan6_common.d ./lwip/src/netif/lowpan6_common.o ./lwip/src/netif/slipif.d ./lwip/src/netif/slipif.o ./lwip/src/netif/zepif.d ./lwip/src/netif/zepif.o

.PHONY: clean-lwip-2f-src-2f-netif

