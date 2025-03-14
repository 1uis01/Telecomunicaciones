/*
 * Copyright 2021-2022, 2024 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/*${header:start}*/
#include "fsl_enet.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "app.h"
#include "fsl_reset.h"
#include "fsl_io_mux.h"
/*${header:end}*/

/*${variable:start}*/
phy_ksz8081_resource_t g_phy_resource;
/*${variable:end}*/

/*${function:start}*/
void BOARD_InitModuleClock(void)
{
    /* Set 50MHz output clock required by PHY. */
    CLOCK_EnableClock(kCLOCK_TddrMciEnetClk);
}

static void MDIO_Init(void)
{
    uint32_t i = ENET_GetInstance(EXAMPLE_ENET);

    (void)CLOCK_EnableClock(s_enetClock[i]);
    (void)CLOCK_EnableClock(s_enetExtraClock[i]);
    ENET_SetSMI(EXAMPLE_ENET, EXAMPLE_CLOCK_FREQ, false);
}

static status_t MDIO_Write(uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    return ENET_MDIOWrite(EXAMPLE_ENET, phyAddr, regAddr, data);
}

static status_t MDIO_Read(uint8_t phyAddr, uint8_t regAddr, uint16_t *pData)
{
    return ENET_MDIORead(EXAMPLE_ENET, phyAddr, regAddr, pData);
}

void BOARD_InitHardware(void)
{

    gpio_pin_config_t gpio_config = {kGPIO_DigitalOutput, 1U};

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    BOARD_InitModuleClock();

    ENET_ResetHardware();

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

    MDIO_Init();
    g_phy_resource.read  = MDIO_Read;
    g_phy_resource.write = MDIO_Write;
}

/*${function:end}*/
