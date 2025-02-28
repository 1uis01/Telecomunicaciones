/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_silicon_id.h"
#include "fsl_enet.h"
#include "fsl_phy.h"
#include "board.h"
#include "app.h"
#include "aes.h"
#include "fsl_crc.h"
#include "comunicacion.h"

/*!
 * @brief Main function
 */
int main(void)
{
	bool link = false;
	bool tempLink = false;

	envioInit(&link);

	uint32_t testTxNum     = 0;
	int espera = 200000;

	while (1)
    {



#if EXAMPLE_USES_LOOPBACK_CABLE
        /* PHY link status update. */
#if (defined(EXAMPLE_PHY_LINK_INTR_SUPPORT) && (EXAMPLE_PHY_LINK_INTR_SUPPORT))
        if (linkChange)
        {
            linkChange = false;
            PHY_ClearInterrupt(&phyHandle);
            PHY_GetLinkStatus(&phyHandle, &link);
            GPIO_EnableLinkIntr();
        }
#else
        PHY_GetLinkStatus(&phyHandle, &link);
#endif
        if (tempLink != link)
        {
            PRINTF("PHY link changed, link status = %u\r\n", link);
            tempLink = link;
        }
#endif /*EXAMPLE_USES_LOOPBACK_CABLE*/
        /* Get the Frame size */

        if (testTxNum <= ENET_TRANSMIT_DATA_NUM){

        if(espera == 0)
        {
            /* Send a multicast frame when the PHY is link up. */
#if EXAMPLE_USES_LOOPBACK_CABLE
            if (link)
#endif
            {
            	espera = 100000; // se reestablece la variable de espera para hacer tiempo y que lleguen las respuestas
                send(testTxNum); // envío de la trama.
                testTxNum++;

            }
        }
        espera--;
        receive(); // Llamada a la función de recepción para verificar si se recibe la respuesta
    }
    }
}
