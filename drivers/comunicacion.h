#ifndef CONFIGURACION_H
#define CONFIGURACION_H


#include "fsl_debug_console.h"
#include "fsl_silicon_id.h"
#include "fsl_enet.h"
#include "fsl_phy.h"
#include "board.h"
#include "app.h"
#include "aes.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ENET_RXBD_NUM          (4)
#define ENET_TXBD_NUM          (4)
#define ENET_RXBUFF_SIZE       (ENET_FRAME_MAX_FRAMELEN)
#define ENET_TXBUFF_SIZE       (ENET_FRAME_MAX_FRAMELEN)
#define ENET_DATA_LENGTH       (1000)
#define ENET_TRANSMIT_DATA_NUM (16)
#ifndef APP_ENET_BUFF_ALIGNMENT
#define APP_ENET_BUFF_ALIGNMENT ENET_BUFF_ALIGNMENT
#endif
#ifndef PHY_AUTONEGO_TIMEOUT_COUNT
#define PHY_AUTONEGO_TIMEOUT_COUNT (300000)
#endif
#ifndef EXAMPLE_PHY_LINK_INTR_SUPPORT
#define EXAMPLE_PHY_LINK_INTR_SUPPORT (0U)
#endif
#ifndef EXAMPLE_USES_LOOPBACK_CABLE
#define EXAMPLE_USES_LOOPBACK_CABLE (1U)
#endif

#ifndef PHY_STABILITY_DELAY_US
#if EXAMPLE_USES_LOOPBACK_CABLE
#define PHY_STABILITY_DELAY_US (0U)
#else
/* If cable is not used there is no "readiness wait" caused by auto negotiation. Lets wait 100ms.*/
#define PHY_STABILITY_DELAY_US (100000U)
#endif
#endif

/* @TEST_ANCHOR */

#ifndef MAC_ADDRESS
#define MAC_ADDRESS                        \
    {                                      \
        0x54, 0x27, 0x8d, 0x00, 0x00, 0x00 \
    }
#else
#define USER_DEFINED_MAC_ADDRESS
#endif

#define MAC_DEST							\
	{                                       \
		0xb0, 0x0c, 0xd1, 0x5c, 0xc5, 0xe2  \
	}



extern uint8_t aes_key[16];

extern uint8_t aes_iv[16];


typedef struct { char *mensaje[16];} mensajes;

extern mensajes men;


extern enet_handle_t g_handle;
extern uint8_t g_frame[ENET_DATA_LENGTH + 14];

/*! @brief The MAC address for ENET device. */
extern uint8_t g_macAddr[6];
extern uint8_t g_macAddrdest[6];

/*! @brief PHY status. */
extern phy_handle_t phyHandle;

#if ((EXAMPLE_USES_LOOPBACK_CABLE) && defined(EXAMPLE_PHY_LINK_INTR_SUPPORT) && (EXAMPLE_PHY_LINK_INTR_SUPPORT))
static bool linkChange = false;
#endif

extern void ENET_BuildBroadCastFrame(uint8_t *mensajeFinal, uint32_t length, uint32_t checksum32); // función que crea la trama

extern uint32_t anadirPadding(mensajes Tabla, uint8_t *mensaje, uint8_t noMensaje); // función que añade el padding

extern void receive(void); // función que recibe la respuesta del script de python

extern void send(uint8_t noMensaje); // función que envía las tramas

extern void envioInit(bool *link); // función que inicializa la comunicación ethernet

#endif
