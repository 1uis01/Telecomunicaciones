################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_cache.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_enet.c \
../drivers/fsl_flexcomm.c \
../drivers/fsl_flexspi.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2s_bridge.c \
../drivers/fsl_inputmux.c \
../drivers/fsl_iped.c \
../drivers/fsl_ocotp.c \
../drivers/fsl_pint.c \
../drivers/fsl_power.c \
../drivers/fsl_reset.c \
../drivers/fsl_usart.c 

C_DEPS += \
./drivers/fsl_cache.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_enet.d \
./drivers/fsl_flexcomm.d \
./drivers/fsl_flexspi.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2s_bridge.d \
./drivers/fsl_inputmux.d \
./drivers/fsl_iped.d \
./drivers/fsl_ocotp.d \
./drivers/fsl_pint.d \
./drivers/fsl_power.d \
./drivers/fsl_reset.d \
./drivers/fsl_usart.d 

OBJS += \
./drivers/fsl_cache.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_enet.o \
./drivers/fsl_flexcomm.o \
./drivers/fsl_flexspi.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2s_bridge.o \
./drivers/fsl_inputmux.o \
./drivers/fsl_iped.o \
./drivers/fsl_ocotp.o \
./drivers/fsl_pint.o \
./drivers/fsl_power.o \
./drivers/fsl_reset.o \
./drivers/fsl_usart.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_RW612ETA2I -DCPU_RW612ETA2I_cm33_nodsp -DMCUXPRESSO_SDK -D_POSIX_SOURCE -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DUSE_RTOS=1 -DPRINTF_ADVANCED_ENABLE=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DBOOT_HEADER_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -DWIFI_BOARD_RW610 -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DLWIP_SUPPORT_CUSTOM_PBUF=1 -DCHECKSUM_GEN_UDP=1 -DCHECKSUM_GEN_TCP=1 -DCHECKSUM_GEN_ICMP=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_UDP=1 -DCHECKSUM_CHECK_TCP=1 -DCHECKSUM_CHECK_ICMP=1 -DCHECKSUM_CHECK_ICMP6=1 -DSDK_OS_FREE_RTOS -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\source" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\flash_config" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\drivers" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\CMSIS" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\CMSIS\m-profile" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\device" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\device\periph" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\utilities" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\lists" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\utilities\str" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\utilities\debug_console" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\serial_manager" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\gpio" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\uart" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClBuffer\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClBuffer\inc\internal" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClCore\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClEls\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClEls\inc\internal" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClMemory\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxClMemory\inc\internal" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslMemory\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslMemory\inc\internal" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslCPreProcessor\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslDataIntegrity\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslFlowProtection\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslParamIntegrity\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\comps\mcuxCsslSecureCounter\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\compiler" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\platforms\rw61x" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\src\platforms\rw61x\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\els_pkc\includes\platform\rw61x" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\phy" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component\silicon_id" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\component" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\lwip\port" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\lwip\src" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\lwip\src\include" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\lwip\src\include\lwip" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\lwip\port\sys_arch\dynamic" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\lwip\src\include\lwip\apps" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\freertos\freertos-kernel\include" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\freertos\freertos-kernel\portable\GCC\ARM_CM33_NTZ\non_secure" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\board" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\freertos\freertos-kernel\template" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\freertos\freertos-kernel\template\ARM_CM33_3_priority_bits" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -fno-builtin -mcpu=cortex-m33+nodsp -imacros "C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_lwip_mqtt_freertos\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_cache.d ./drivers/fsl_cache.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_enet.d ./drivers/fsl_enet.o ./drivers/fsl_flexcomm.d ./drivers/fsl_flexcomm.o ./drivers/fsl_flexspi.d ./drivers/fsl_flexspi.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_i2s_bridge.d ./drivers/fsl_i2s_bridge.o ./drivers/fsl_inputmux.d ./drivers/fsl_inputmux.o ./drivers/fsl_iped.d ./drivers/fsl_iped.o ./drivers/fsl_ocotp.d ./drivers/fsl_ocotp.o ./drivers/fsl_pint.d ./drivers/fsl_pint.o ./drivers/fsl_power.d ./drivers/fsl_power.o ./drivers/fsl_reset.d ./drivers/fsl_reset.o ./drivers/fsl_usart.d ./drivers/fsl_usart.o

.PHONY: clean-drivers

