
#include "fsl_debug_console.h"
#include "fsl_silicon_id.h"
#include "fsl_enet.h"
#include "fsl_phy.h"
#include "board.h"
#include "app.h"
#include "aes.h"
#include "fsl_crc.h"
#include "comunicacion.h"
#include "comunicacion_cfg.h"

AT_NONCACHEABLE_SECTION_ALIGN(enet_rx_bd_struct_t g_rxBuffDescrip[ENET_RXBD_NUM], ENET_BUFF_ALIGNMENT);
AT_NONCACHEABLE_SECTION_ALIGN(enet_tx_bd_struct_t g_txBuffDescrip[ENET_TXBD_NUM], ENET_BUFF_ALIGNMENT);
/*! @brief The data buffers can be in cacheable region or in non-cacheable region.
 * If use cacheable region, the alignment size should be the maximum size of "CACHE LINE SIZE" and "ENET_BUFF_ALIGNMENT"
 * If use non-cache region, the alignment size is the "ENET_BUFF_ALIGNMENT".
*/
SDK_ALIGN(uint8_t g_rxDataBuff[ENET_RXBD_NUM][SDK_SIZEALIGN(ENET_RXBUFF_SIZE, APP_ENET_BUFF_ALIGNMENT)],
          APP_ENET_BUFF_ALIGNMENT);
SDK_ALIGN(uint8_t g_txDataBuff[ENET_TXBD_NUM][SDK_SIZEALIGN(ENET_TXBUFF_SIZE, APP_ENET_BUFF_ALIGNMENT)],
          APP_ENET_BUFF_ALIGNMENT);

enet_handle_t g_handle = {0};
uint8_t g_frame[ENET_DATA_LENGTH + 14] = {0};

phy_handle_t phyHandle = {0};

uint8_t g_macAddr[6] = MAC_ADDRESS;
uint8_t g_macAddrdest[6] = MAC_DEST;


mensajes men = {
    .mensaje = {
        "No todo lo que es oro reluce...",
        "Aun en la oscuridad...",
        "¿Que es la vida?",
        "No temas a la oscuridad...",
        "Hasta los mas pequenos...",
        "No digas que el sol se ha puesto...",
        "El coraje se encuentra...",
        "No todos los tesoros...",
        "Es peligroso...",
        "Un mago nunca llega tarde...",
        "Aun hay esperanza...",
        "El mundo esta cambiando...",
        "Las raices profundas...",
        "No se puede...",
        "Y sobre todo...",
        "De las cenizas, un fuego..."
    }
};

uint8_t aes_key[16] = AES;

uint8_t aes_iv[16] = IV;

struct AES_ctx ctx;

 void InitCrc32(CRC_Type *base, uint32_t seed)
{
    crc_config_t config;

    config.polynomial    = kCRC_Polynomial_CRC_32;
    config.reverseIn     = true;
    config.complementIn  = false;
    config.reverseOut    = true;
    config.complementOut = true;
    config.seed          = seed;

    CRC_Init(base, &config);
}

uint32_t anadirPadding(mensajes Tabla, uint8_t *mensaje, uint8_t noMensaje) {

	char *mensajeTabla = Tabla.mensaje[noMensaje];

	uint8_t longitudMensaje = strlen(mensajeTabla);

	uint8_t pad = 0;

	if(longitudMensaje % 16 != 0 )
		pad = 16 - (longitudMensaje % 16); // se verifica que el mensaje sea multiplo de 16 y si no se calcula el número de
                                           // padding

    for (uint8_t i = 0; i < longitudMensaje; i++) {
        mensaje[i] = mensajeTabla[i];                    // se toma la variable donde se llenara con el mensaje a enviar y
    }                                                    // se le copia el mensaje correspondiente

    if (longitudMensaje % 16 != 0 ){

        uint8_t padding = 16 - (longitudMensaje % 16);                                 // aquí se añade el padding con el
        for (uint8_t i = longitudMensaje; i < (longitudMensaje + padding); i++) {      // número calculado previamente
            mensaje[i] = pad;
        }
        longitudMensaje = longitudMensaje + padding;
    }

    return longitudMensaje;                              // se regresa la longitud del mensaje mas la cantidad de padding
}

void receive(void){

	uint32_t length = 0;
	enet_data_error_stats_t eErrStatic;
	status_t status;
	uint8_t macDist = 0;

	status = ENET_GetRxFrameSize(&g_handle, &length, 0);
	        /* Call ENET_ReadFrame when there is a received frame. */
	        if (length != 0)
	        {

	            /* Received valid frame. Deliver the rx buffer with the size equal to length. */
	            uint8_t *data = (uint8_t *)malloc(length);
	            status        = ENET_ReadFrame(EXAMPLE_ENET, &g_handle, data, length, 0, NULL);
	            if (status == kStatus_Success)
	            {
	            	for (uint8_t i = 0; i < 6 ; i++)           // Se verifica que la MAC recibida no sea distinta de
	            		if( data[i] != g_macAddr[i])           // la que tiene la tarjeta, si es así se activa una bandera
	            			macDist = 1;                       // y ya no se lee la trama

	            	if(macDist == 0){

	            		uint16_t longitud = (data[12] << 8) | data[13];         // se obtiene la longitud del mensaje

	            		longitud = longitud - 4;

	            		uint32_t checksum = data[longitud + 14] | data[longitud + 15] << 8 | data[longitud + 16] << 16 | data[longitud + 17] << 24 ;
                                                                               // se obtiene el checksum que se envío en la trama
						uint8_t mensaje[longitud];

	            		for (uint32_t i = 0; i < longitud ; i++)               // se obtiene el mensaje encriptado
	            			mensaje[i] = data[i + 14];


	            		CRC_Type *base = CRC_ENGINE;

	            		InitCrc32(base, 0xFFFFFFFFU);
	            		CRC_WriteData(base, mensaje, longitud);                // se calcula el crc al mensaje encriptado para saber
	            		uint32_t checksum32 = CRC_Get32bitResult(base);        // si coincide con el recibido en la trama


	            		if(checksum32 == checksum){
	            			AES_init_ctx_iv(&ctx, aes_key, aes_iv);              // si los checksum coinciden se desencripta el mensaje
	            			AES_CBC_decrypt_buffer(&ctx, mensaje, longitud);

	            			for (uint32_t i = 0; i < longitud ; i++)            // una vez desencriptado el mensaje se imprime
	            			    PRINTF("%c",mensaje[i]);

	            		PRINTF("\n");
	            		}
	            		else
	            			PRINTF("CHECKSUM NO CORRESPONDE\n");

	            	}


	            }
	            free(data);
	            macDist = 0;

	        }
	        else if (status == kStatus_ENET_RxFrameError)
	        {
	            /* Update the received buffer when error happened. */
	            /* Get the error information of the received g_frame. */
	            ENET_GetRxErrBeforeReadFrame(&g_handle, &eErrStatic, 0);
	            /* update the receive buffer. */
	            ENET_ReadFrame(EXAMPLE_ENET, &g_handle, NULL, 0, 0, NULL);
	        }

}

void send(uint8_t noMensaje){
	uint32_t length;
	uint8_t mensajeFinal[ENET_DATA_LENGTH]={0};
	CRC_Type *base = CRC_ENGINE;
	uint32_t checksum32;

	length = anadirPadding(men, mensajeFinal, noMensaje);           // se manda llamar la funcion para añadir el padding
	PRINTF("%s ", men.mensaje[noMensaje]);

	AES_init_ctx_iv(&ctx, aes_key, aes_iv);                         // se inicializa la funcion para encriptar el mensaje
	AES_CBC_encrypt_buffer(&ctx, mensajeFinal, length);             // se encripta el mensaje

	InitCrc32(base, 0xFFFFFFFFU);
	CRC_WriteData(base, mensajeFinal, length);                      // se le calcula el crc al mensaje que se quiere enviar
	checksum32 = CRC_Get32bitResult(base);


	ENET_BuildBroadCastFrame(mensajeFinal, length, checksum32);     // se manda llamar a la funcion que creará la trama

	if (kStatus_Success ==
	             ENET_SendFrame(EXAMPLE_ENET, &g_handle, &g_frame[0], ENET_DATA_LENGTH, 0, false, NULL))
	{
	             //PRINTF("The %d frame transmitted success!\r\n", noMensaje);

	}
	             else
	{
	             PRINTF(" \r\nTransmit frame failed!\r\n");
	}


}

void ENET_BuildBroadCastFrame(uint8_t mensajeFinal[], uint32_t length, uint32_t checksum32)
{
    uint32_t count  = 0;

    memcpy(&g_frame[0], &g_macAddrdest[0], 6U);      // se añade la MAC de destino a la trama
    memcpy(&g_frame[6], &g_macAddr[0], 6U);          // se añade la MAC de origen a la trama

    g_frame[12] = ((length+4) >> 8) & 0xFFU;         // se añade el tamaño del mensaje a la trama
    g_frame[13] = (length+4) & 0xFFU;


    for (count = 0; count < length; count++)
    {
        g_frame[count + 14] = mensajeFinal[count];     // se añade el mensaje encriptado a la trama
    }

    g_frame[length + 14] = checksum32 & 0xFFU;
    g_frame[length + 15] = (checksum32 >> 8) & 0xFFU;        // se añade el checksum a la trama
    g_frame[length + 16] = (checksum32 >> 16) & 0xFFU;
    g_frame[length + 17] = (checksum32 >> 24) & 0xFFU;

}

void envioInit(bool *link){                          // función de inicialización por defecto, solo se incluyo un pase por
                                                     // referencia de link para saber si la inicialización fué correcta
	 phy_config_t phyConfig = {0};                   // para cuando se enviará en el main
	    uint32_t testTxNum     = 0;
	    uint32_t length        = 0;
	    enet_data_error_stats_t eErrStatic;
	    status_t status;
	    enet_config_t config;
	#if EXAMPLE_USES_LOOPBACK_CABLE
	    volatile uint32_t count = 0;
	    phy_speed_t speed;
	    phy_duplex_t duplex;
	    bool autonego = false;
	   // bool link     = false;
	#endif
	    int espera = 1;


	    /* Hardware Initialization. */
	    BOARD_InitHardware();

	    PRINTF("\r\nENET example start.\r\n");

	    /* Prepare the buffer configuration. */
	    enet_buffer_config_t buffConfig[] = {{
	        ENET_RXBD_NUM,
	        ENET_TXBD_NUM,
	        SDK_SIZEALIGN(ENET_RXBUFF_SIZE, APP_ENET_BUFF_ALIGNMENT),
	        SDK_SIZEALIGN(ENET_TXBUFF_SIZE, APP_ENET_BUFF_ALIGNMENT),
	        &g_rxBuffDescrip[0],
	        &g_txBuffDescrip[0],
	        &g_rxDataBuff[0][0],
	        &g_txDataBuff[0][0],
	        true,
	        true,
	        NULL,
	    }};

	    /* Get default configuration. */
	    /*
	     * config.miiMode = kENET_RmiiMode;
	     * config.miiSpeed = kENET_MiiSpeed100M;
	     * config.miiDuplex = kENET_MiiFullDuplex;
	     * config.rxMaxFrameLen = ENET_FRAME_MAX_FRAMELEN;
	     */
	    ENET_GetDefaultConfig(&config);

	    /* The miiMode should be set according to the different PHY interfaces. */
	#ifdef EXAMPLE_PHY_INTERFACE_RGMII
	    config.miiMode = kENET_RgmiiMode;
	#else
	    config.miiMode = kENET_RmiiMode;
	#endif
	    phyConfig.phyAddr = EXAMPLE_PHY_ADDRESS;
	#if EXAMPLE_USES_LOOPBACK_CABLE
	    phyConfig.autoNeg = true;
	#else
	    phyConfig.autoNeg = false;
	    config.miiDuplex  = kENET_MiiFullDuplex;
	#endif
	    phyConfig.ops      = EXAMPLE_PHY_OPS;
	    phyConfig.resource = EXAMPLE_PHY_RESOURCE;
	#if (defined(EXAMPLE_PHY_LINK_INTR_SUPPORT) && (EXAMPLE_PHY_LINK_INTR_SUPPORT))
	    phyConfig.intrType = kPHY_IntrActiveLow;
	#endif

	    /* Initialize PHY and wait auto-negotiation over. */
	    PRINTF("Wait for PHY init...\r\n");
	#if EXAMPLE_USES_LOOPBACK_CABLE
	    do
	    {
	        status = PHY_Init(&phyHandle, &phyConfig);
	        if (status == kStatus_Success)
	        {
	            PRINTF("Wait for PHY link up...\r\n");
	            /* Wait for auto-negotiation success and link up */
	            count = PHY_AUTONEGO_TIMEOUT_COUNT;
	            do
	            {
	                PHY_GetLinkStatus(&phyHandle, link);
	                if (*link)
	                {
	                    PHY_GetAutoNegotiationStatus(&phyHandle, &autonego);
	                    if (autonego)
	                    {
	                        break;
	                    }
	                }
	            } while (--count);
	            if (!autonego)
	            {
	                PRINTF("PHY Auto-negotiation failed. Please check the cable connection and link partner setting.\r\n");
	            }
	        }
	    } while (!(*link && autonego));
	#else
	    while (PHY_Init(&phyHandle, &phyConfig) != kStatus_Success)
	    {
	        PRINTF("PHY_Init failed\r\n");
	    }

	    /* set PHY link speed/duplex and enable loopback. */
	    PHY_SetLinkSpeedDuplex(&phyHandle, (phy_speed_t)config.miiSpeed, (phy_duplex_t)config.miiDuplex);
	    PHY_EnableLoopback(&phyHandle, kPHY_LocalLoop, (phy_speed_t)config.miiSpeed, true);
	#endif /* EXAMPLE_USES_LOOPBACK_CABLE */

	#if PHY_STABILITY_DELAY_US
	    /* Wait a moment for PHY status to be stable. */
	    SDK_DelayAtLeastUs(PHY_STABILITY_DELAY_US, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
	#endif

	#if EXAMPLE_USES_LOOPBACK_CABLE
	    /* Get the actual PHY link speed and set in MAC. */
	    PHY_GetLinkSpeedDuplex(&phyHandle, &speed, &duplex);
	    config.miiSpeed  = (enet_mii_speed_t)speed;
	    config.miiDuplex = (enet_mii_duplex_t)duplex;
	#endif

	#ifndef USER_DEFINED_MAC_ADDRESS
	    /* Set special address for each chip. */
	    //SILICONID_ConvertToMacAddr(&g_macAddr);
	#endif

	    /* Init the ENET. */
	    ENET_Init(EXAMPLE_ENET, &g_handle, &config, &buffConfig[0], &g_macAddr[0], EXAMPLE_CLOCK_FREQ);
	    ENET_ActiveRead(EXAMPLE_ENET);

	    /* Build broadcast for sending. */
}
