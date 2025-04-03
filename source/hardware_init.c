/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*${header:start}*/
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_power.h"
#include "fsl_io_mux.h"
/*${header:end}*/

/*${function:start}*/
void BOARD_InitHardware(void)
{
	gpio_pin_config_t gpio_config = {kGPIO_DigitalOutput, 1U};
    BOARD_InitBootPins();
    if (BOARD_IS_XIP())
    {
        BOARD_BootClockLPR();
        CLOCK_EnableClock(kCLOCK_Otp);
        CLOCK_EnableClock(kCLOCK_Els);
        CLOCK_EnableClock(kCLOCK_ElsApb);
        RESET_PeripheralReset(kOTP_RST_SHIFT_RSTn);
        RESET_PeripheralReset(kELS_APB_RST_SHIFT_RSTn);
    }
    else
    {
        BOARD_InitBootClocks();
    }
    BOARD_InitDebugConsole();
    /* Reset GMDA */
    RESET_PeripheralReset(kGDMA_RST_SHIFT_RSTn);
    /* Keep CAU sleep clock here. */
    /* CPU1 uses Internal clock when in low power mode. */
    POWER_ConfigCauInSleep(false);
    BOARD_InitSleepPinConfig();

    GPIO_PortInit(GPIO, 0U);
            GPIO_PortInit(GPIO, 1U);
            GPIO_PinInit(GPIO, 0U, 21U, &gpio_config); /* ENET_RST */
            gpio_config.pinDirection = kGPIO_DigitalInput;
            gpio_config.outputLogic  = 0U;
            GPIO_PinInit(GPIO, 1U, 23U, &gpio_config); /* ENET_INT */

            gpio_config.pinDirection = kGPIO_DigitalOutput;
            gpio_config.outputLogic  = 0U;

            GPIO_PinInit(GPIO, 0U, 1U, &gpio_config); //rojo1
            IO_MUX_SetPinMux(IO_MUX_GPIO1);
            GPIO_PinWrite(GPIO, 0U, 1U, 1U);

            GPIO_PinInit(GPIO, 0U, 12U, &gpio_config); //verde1
            IO_MUX_SetPinMux(IO_MUX_GPIO12);
            GPIO_PinWrite(GPIO, 0U, 12U, 1U);

            gpio_config.pinDirection = kGPIO_DigitalOutput;
            gpio_config.outputLogic  = 1U;

            GPIO_PinInit(GPIO, 0U, 6U, &gpio_config); //rojo2
            IO_MUX_SetPinMux(IO_MUX_GPIO6);
            GPIO_PinWrite(GPIO, 0U, 6U, 0U);

            GPIO_PinInit(GPIO, 0U, 7U, &gpio_config); //verde2
            IO_MUX_SetPinMux(IO_MUX_GPIO7);
            GPIO_PinWrite(GPIO, 0U, 7U, 0U);

            GPIO_PinWrite(GPIO, 0U, 21U, 0U);
            SDK_DelayAtLeastUs(1000000, CLOCK_GetCoreSysClkFreq());
            GPIO_PinWrite(GPIO, 0U, 21U, 1U);
}
/*${function:end}*/
