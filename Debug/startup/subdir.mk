################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_rw612.c 

C_DEPS += \
./startup/startup_rw612.d 

OBJS += \
./startup/startup_rw612.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_RW612ETA2I -DCPU_RW612ETA2I_cm33_nodsp -DMCUXPRESSO_SDK -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DPRINTF_ADVANCED_ENABLE=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DBOOT_HEADER_ENABLE=1 -DWIFI_BOARD_RW610 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\source" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\flash_config" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\drivers" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\CMSIS" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\CMSIS\m-profile" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\device" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\device\periph" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\utilities" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\utilities\str" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\utilities\debug_console_lite" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\uart" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxClBuffer\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxClBuffer\inc\internal" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxClCore\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxClEls\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxClEls\inc\internal" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxClMemory\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxClMemory\inc\internal" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxCsslMemory\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxCsslMemory\inc\internal" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxCsslCPreProcessor\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxCsslDataIntegrity\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxCsslFlowProtection\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxCsslParamIntegrity\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\comps\mcuxCsslSecureCounter\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\compiler" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\platforms\rw61x" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\src\platforms\rw61x\inc" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\els_pkc\includes\platform\rw61x" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\phy" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component\silicon_id" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\component" -I"C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\board" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -fno-builtin -mcpu=cortex-m33+nodsp -imacros "C:\Users\Aloncho\Documents\MCUXpressoIDE_24.12.148\workspace\frdmrw612_enet_txrx_transfer\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-startup

clean-startup:
	-$(RM) ./startup/startup_rw612.d ./startup/startup_rw612.o

.PHONY: clean-startup

