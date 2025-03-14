/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "mqtt_freertos.h"

#include "board.h"
#include "fsl_silicon_id.h"

#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/apps/mqtt.h"
#include "lwip/tcpip.h"

// FIXME cleanup

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief MQTT server host name or IP address. */
#ifndef EXAMPLE_MQTT_SERVER_HOST
#define EXAMPLE_MQTT_SERVER_HOST "broker.emqx.io"
#endif

/*! @brief MQTT server port number. */
#ifndef EXAMPLE_MQTT_SERVER_PORT
#define EXAMPLE_MQTT_SERVER_PORT 1883
#endif

/*! @brief Stack size of the temporary lwIP initialization thread. */
#define INIT_THREAD_STACKSIZE 1024

/*! @brief Priority of the temporary lwIP initialization thread. */
#define INIT_THREAD_PRIO DEFAULT_THREAD_PRIO

/*! @brief Stack size of the temporary initialization thread. */
#define APP_THREAD_STACKSIZE 1024

/*! @brief Priority of the temporary initialization thread. */
#define APP_THREAD_PRIO DEFAULT_THREAD_PRIO

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void connect_to_mqtt(void *ctx);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief MQTT client data. */
static mqtt_client_t *mqtt_client;

/*! @brief MQTT client ID string. */
static char client_id[(SILICONID_MAX_LENGTH * 2) + 5];

/*! @brief MQTT client information. */
static const struct mqtt_connect_client_info_t mqtt_client_info = {
    .client_id   = (const char *)&client_id[0],
    .client_user = NULL,
    .client_pass = NULL,
    .keep_alive  = 100,
    .will_topic  = NULL,
    .will_msg    = NULL,
    .will_qos    = 0,
    .will_retain = 0,
#if LWIP_ALTCP && LWIP_ALTCP_TLS
    .tls_config = NULL,
#endif
};

/*! @brief MQTT broker IP address. */
static ip_addr_t mqtt_addr;

/*! @brief Indicates connection to MQTT broker. */
static volatile bool connected = false;

typedef struct {
    char *_topic;
    char *_message;
} mqtt_message_t;

mqtt_message_t msg = {
	._topic = "",
	._message = ""
};

bool mqtt_flag;

bool sensorPoste1;
bool sensorPoste2;

bool semaforo1;
bool semaforo2;

bool pasoDeCebra;
bool sincronizar;

int tiempo1;
int tiempo2;

uint16_t mensaje;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Called when subscription request finishes.
 */
static void mqtt_topic_subscribed_cb(void *arg, err_t err)
{
    const char *topic = (const char *)arg;

    if (err == ERR_OK)
    {
        PRINTF("Subscribed to the topic %s \n", topic);
    }
    else
    {
        PRINTF("Failed to subscribe to the topic %s : %d \n", topic, err);
    }
}

/*!
 * @brief Called when there is a message on a subscribed topic.
 */
static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{
    LWIP_UNUSED_ARG(arg);

    msg._topic = topic;
    msg._topic[strlen(topic)] = '\0';
    PRINTF("Received %u bytes from the topic %s: ", tot_len, topic);
}

/*!
 * @brief Called when recieved incoming published message fragment.
 */
static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    int i;

    LWIP_UNUSED_ARG(arg);

    for (i = 0; i < len; i++)
    {


            PRINTF("%c", data[i]);

    }
    strcpy(data,msg._message);
    //msg._message = data;
    //msg._message[len+1] = '\0';
    //PRINTF("%s",msg._message);

    if (flags & MQTT_DATA_FLAG_LAST)
    {
        PRINTF("\n");
    }

    mqtt_flag = true;

    if(strcmp(data,"poste1")==0)
    	sensorPoste1 = true;
    if(strcmp(data,"poste2")==0)
        sensorPoste2 = true;
    if(strcmp(data,"verde")==0)
            semaforo2 = true;
    if(strcmp(data,"bloqueado")==0)
            pasoDeCebra = true;
    if(strcmp(data,"desbloqueado")==0)
                pasoDeCebra = false;
    if(strcmp(data,"detener")==0)
                sincronizar = true;
}

/*!
 * @brief Subscribe to MQTT topics.
 */
static void mqtt_subscribe_topics(mqtt_client_t *client)
{
    static const char *topics[] = {"Poste1/#", "Poste2/#", "UsuarioDis/#", "Semaforo2/#"};
    int qos[]                   = {1, 1, 1, 1};
    err_t err;
    int i;

    mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb,
                            LWIP_CONST_CAST(void *, &mqtt_client_info));

    for (i = 0; i < ARRAY_SIZE(topics); i++)
    {
        err = mqtt_subscribe(client, topics[i], qos[i], mqtt_topic_subscribed_cb, LWIP_CONST_CAST(void *, topics[i]));

        if (err == ERR_OK)
        {
            PRINTF("Subscribing to the topic %s with QoS %d... \n", topics[i], qos[i]);
        }
        else
        {
            PRINTF("Failed to subscribe to the topic %s with QoS %d: %d. \n", topics[i], qos[i], err);
        }
    }
}

/*!
 * @brief Called when connection state changes.
 */
static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t *)arg;

    connected = (status == MQTT_CONNECT_ACCEPTED);

    switch (status)
    {
        case MQTT_CONNECT_ACCEPTED:
            PRINTF("MQTT client \"%s\" connected.\r\n", client_info->client_id);
            mqtt_subscribe_topics(client);
            break;

        case MQTT_CONNECT_DISCONNECTED:
            PRINTF("MQTT client \"%s\" not connected.\r\n", client_info->client_id);
            /* Try to reconnect 1 second later */
            sys_timeout(1000, connect_to_mqtt, NULL);
            break;

        case MQTT_CONNECT_TIMEOUT:
            PRINTF("MQTT client \"%s\" connection timeout.\r\n", client_info->client_id);
            /* Try again 1 second later */
            sys_timeout(1000, connect_to_mqtt, NULL);
            break;

        case MQTT_CONNECT_REFUSED_PROTOCOL_VERSION:
        case MQTT_CONNECT_REFUSED_IDENTIFIER:
        case MQTT_CONNECT_REFUSED_SERVER:
        case MQTT_CONNECT_REFUSED_USERNAME_PASS:
        case MQTT_CONNECT_REFUSED_NOT_AUTHORIZED_:
            PRINTF("MQTT client \"%s\" connection refused: %d.\r\n", client_info->client_id, (int)status);
            /* Try again 10 seconds later */
            sys_timeout(10000, connect_to_mqtt, NULL);
            break;

        default:
            PRINTF("MQTT client \"%s\" connection status: %d.\r\n", client_info->client_id, (int)status);
            /* Try again 10 seconds later */
            sys_timeout(10000, connect_to_mqtt, NULL);
            break;
    }
}

/*!
 * @brief Starts connecting to MQTT broker. To be called on tcpip_thread.
 */
static void connect_to_mqtt(void *ctx)
{
    LWIP_UNUSED_ARG(ctx);

    PRINTF("Connecting to MQTT broker at %s...\r\n", ipaddr_ntoa(&mqtt_addr));

    mqtt_client_connect(mqtt_client, &mqtt_addr, EXAMPLE_MQTT_SERVER_PORT, mqtt_connection_cb,
                        LWIP_CONST_CAST(void *, &mqtt_client_info), &mqtt_client_info);
}

/*!
 * @brief Called when publish request finishes.
 */
static void mqtt_message_published_cb(void *arg, err_t err)
{
    //const char *topic = msg._topic;

    if (err == ERR_OK)
    {
        PRINTF("Message Published \n");
    }
    else
    {
        PRINTF("Failed to publish. \n");
    }
}

/*!
 * @brief Publishes a message. To be called on tcpip_thread.
 */
static void publish_message(void *ctx)
{
    const char *topic   = "";
    const char *message = "";

    //LWIP_UNUSED_ARG(ctx);

    switch(mensaje){

    case 1:
    	topic = "Semaforo1";
        message = "noobstruir";
    break;

    case 2:
        topic = "Semaforo1";
        message = "ya";
    break;

    case 3:
        topic = "Semaforo1";
        message = "alerta";
    break;

    case 4:
        topic = "Semaforo1";
        message = "aunno";
    break;

    case 5:
        topic = "Semaforo1";
        message = "mandardistancia";
    break;

    case 6:
        topic = "Semaforo1";
        message = "yanoenviar";
    break;

    case 7:
    	topic = "Semaforo2";
    	message = "detener";
    break;

    case 8:
        topic = "Semaforo2";
        message = "rojo";
    break;

    case 9:
        topic = "Semaforo2";
        message = "verde";
    break;

    }


    PRINTF("Going to publish to the topic %s... \n", topic);

    mqtt_publish(mqtt_client, topic, message, strlen(message), 1, 0, mqtt_message_published_cb, (void *)topic);
}

/*!
 * @brief Application thread.
 */
static void app_thread(void *arg)
{
    struct netif *netif = (struct netif *)arg;
    err_t err;
    int i;

    PRINTF("\r\nIPv4 Address     : %s\r\n", ipaddr_ntoa(&netif->ip_addr));
    PRINTF("IPv4 Subnet mask : %s\r\n", ipaddr_ntoa(&netif->netmask));
    PRINTF("IPv4 Gateway     : %s\r\n\r\n", ipaddr_ntoa(&netif->gw));

    /*
     * Check if we have an IP address or host name string configured.
     * Could just call netconn_gethostbyname() on both IP address or host name,
     * but we want to print some info if goint to resolve it.
     */
    if (ipaddr_aton(EXAMPLE_MQTT_SERVER_HOST, &mqtt_addr) && IP_IS_V4(&mqtt_addr))
    {
        /* Already an IP address */
        err = ERR_OK;
    }
    else
    {
        /* Resolve MQTT broker's host name to an IP address */
        PRINTF("Resolving \"%s\"...\r\n", EXAMPLE_MQTT_SERVER_HOST);
        err = netconn_gethostbyname(EXAMPLE_MQTT_SERVER_HOST, &mqtt_addr);
    }

    if (err == ERR_OK)
    {
        /* Start connecting to MQTT broker from tcpip_thread */
        err = tcpip_callback(connect_to_mqtt, NULL);
        if (err != ERR_OK)
        {
            PRINTF("Failed to invoke broker connection on the tcpip_thread: %d.\r\n", err);
        }
    }
    else
    {
        PRINTF("Failed to obtain IP address: %d.\r\n", err);
    }

    //Activamos los semaforos

    GPIO_PinWrite(GPIO, 0U, 12U, 0U); //verde 1
    GPIO_PinWrite(GPIO, 0U, 1U, 1U);  //rojo 1

    GPIO_PinWrite(GPIO, 0U, 7U, 1U);  //verde 2
    GPIO_PinWrite(GPIO, 0U, 12U, 0U); //rojo 2
    /* Publish some messages */

    int tiempo;

    tiempo = 10000000;
    tiempo1 = 10000000;
    tiempo2 = 10000000;
    semaforo1 = true;
    semaforo2 = true;
    sensorPoste1 = false;
    sensorPoste2 = false;

    while(1)
    {
    	if (sensorPoste1){

    		if(!semaforo1 && !semaforo2)
    		{

    			while(!sensorPoste2 || tiempo)
    			{

    				if (connected && tiempo)
    				{           mensaje = 5;
    							err = tcpip_callback(publish_message, NULL);
    					    	if (err != ERR_OK){
    					    		PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    					    	}
    					    	sys_msleep(1000U);

    							while(pasoDeCebra)
    							{   mensaje = 1;
    								err = tcpip_callback(publish_message, NULL);
    						        if (err != ERR_OK){
    								    PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    								}
    						        sys_msleep(1000U);

    							}
    							mensaje = 2;
    							err = tcpip_callback(publish_message, NULL);
    							if (err != ERR_OK){
    							    PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    							}
    							sys_msleep(1000U);

    				}

    				else if(connected && !tiempo){
    					mensaje = 3;
    					err = tcpip_callback(publish_message, NULL);
    					if (err != ERR_OK){
    					    PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    					}
    					sys_msleep(5000U);
    					tiempo = 10000001;
    					tiempo1 = 10000000;
    					tiempo2 = 10000000;
    					sensorPoste1 = false;
    					sensorPoste2 = false;

    					GPIO_PinWrite(GPIO, 0U, 1U, 1U); //rojo1
    					GPIO_PinWrite(GPIO, 0U, 6U, 0U); //rojo2

    					GPIO_PinWrite(GPIO, 0U, 12U, 0U); //verde 1
    					GPIO_PinWrite(GPIO, 0U, 7U, 1U);  //verde 2

    					semaforo1 = true;
    					semaforo2 = true;
    					sincronizar = false;

    					mensaje = 9;
    					err = tcpip_callback(publish_message, NULL);
    					if (err != ERR_OK){
    					   PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    					}
    					sys_msleep(1000U);
    				}

    				tiempo--;

    			}


    		}

    		if(semaforo1 && !semaforo2){

    			if (connected)
    			{   mensaje = 7;
    			    err = tcpip_callback(publish_message, NULL);
    			    if (err != ERR_OK){
    			    	PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    			    }
    			    sys_msleep(1000U);
    			}
    			tiempo1--;
    		}

    		if(!semaforo1 && semaforo2){
    			tiempo2--;
    		}



    	} // fin de sensorposte1

    	if (sensorPoste2){

    	    		if(!semaforo1 && !semaforo2)
    	    		{

    	    			while(!sensorPoste1 || tiempo)
    	    			{

    	    				if (connected && tiempo)
    	    				{           mensaje = 5;
    	    							err = tcpip_callback(publish_message, NULL);
    	    					    	if (err != ERR_OK){
    	    					    		PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    	    					    	}
    	    					    	sys_msleep(1000U);

    	    							while(pasoDeCebra)
    	    							{   mensaje = 1;
    	    								err = tcpip_callback(publish_message, NULL);
    	    						        if (err != ERR_OK){
    	    								    PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    	    								}
    	    						        sys_msleep(1000U);

    	    							}
    	    							mensaje = 2;
    	    							err = tcpip_callback(publish_message, NULL);
    	    							if (err != ERR_OK){
    	    							    PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    	    							}
    	    							sys_msleep(1000U);

    	    				}

    	    				else if(connected && !tiempo){
    	    					mensaje = 3;
    	    					err = tcpip_callback(publish_message, NULL);
    	    					if (err != ERR_OK){
    	    					    PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    	    					}
    	    					sys_msleep(5000U);
    	    					tiempo = 10000001;
    	    					tiempo1 = 10000000;
    	    					tiempo2 = 10000000;
    	    					sensorPoste1 = false;
    	    					sensorPoste2 = false;

    	    					GPIO_PinWrite(GPIO, 0U, 1U, 1U); //rojo1
    	    					GPIO_PinWrite(GPIO, 0U, 6U, 0U); //rojo2

    	    					GPIO_PinWrite(GPIO, 0U, 12U, 0U); //verde 1
    	    					GPIO_PinWrite(GPIO, 0U, 7U, 1U);  //verde 2

    	    					semaforo1 = true;
    	    					semaforo2 = true;
    	    					sincronizar = false;

    	    					mensaje = 9;
    	    					err = tcpip_callback(publish_message, NULL);
    	    					if (err != ERR_OK){
    	    					    PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    	    					}
    	    					sys_msleep(1000U);
    	    				}

    	    				tiempo--;

    	    			}


    	    		}

    	    		if(semaforo1 && !semaforo2){

    	    			if (connected)
    	    			{   mensaje = 7;
    	    			    err = tcpip_callback(publish_message, NULL);
    	    			    if (err != ERR_OK){
    	    			    	PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    	    			    }
    	    			    sys_msleep(1000U);
    	    			}
    	    			tiempo1--;
    	    		}

    	    		if(!semaforo1 && semaforo2){
    	    		    tiempo2--;
    	    		}



    	    	} // fin de sensorposte2

    	if(semaforo1 && (tiempo1 <= 0)){

    			semaforo1 = false;
    			tiempo1 = 10000000;
    			GPIO_PinWrite(GPIO, 0U, 12U, 1U); //verde 1
    			GPIO_PinWrite(GPIO, 0U, 1U, 0U); //rojo1


    	}

    	if(!semaforo1 && (tiempo1 <= 0)){

    	    if(sensorPoste1 || sensorPoste2){

    	    }
    	    else
    	    {
    	    	semaforo1 = true;
    	    	tiempo1 = 10000000;
    	    	GPIO_PinWrite(GPIO, 0U, 1U, 1U); //rojo1
    	    	GPIO_PinWrite(GPIO, 0U, 12U, 0U); //verde 1

    	    }

    	}

    	if(semaforo2 && (tiempo2 <= 0)){

    	    semaforo2 = false;
    	    tiempo2 = 5000000;

    	    GPIO_PinWrite(GPIO, 0U, 6U, 1U); //rojo2
            GPIO_PinWrite(GPIO, 0U, 7U, 0U);  //verde 2

            mensaje = 8;
            err = tcpip_callback(publish_message, NULL);
            if (err != ERR_OK){
               PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
            }
            sys_msleep(1000U);


    	}

    	if(!semaforo2 && (tiempo2 <= 0)){

    	   if(sincronizar){}
    	   else
    	    {
    	    semaforo2 = true;
    	    tiempo2 = 10000000;
    	    GPIO_PinWrite(GPIO, 0U, 6U, 0U); //rojo2
    	    GPIO_PinWrite(GPIO, 0U, 7U, 1U);  //verde 2

    	    mensaje = 9;
    	    err = tcpip_callback(publish_message, NULL);
    	    if (err != ERR_OK){
    	       PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
    	    }
    	    sys_msleep(1000U);

    	    }

    	 }

    	tiempo1--;
    	tiempo2--;

    	/*
        if (connected && mqtt_flag)
        {
            err = tcpip_callback(publish_message, NULL);
            if (err != ERR_OK)
            {
                PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
            }
            mqtt_flag = false;
            //GPIO_PinWrite(GPIO, 0U, 42U, 0U);
        }

        sys_msleep(1000U);*/
    }


    vTaskDelete(NULL);
}

static void generate_client_id(void)
{
    uint8_t silicon_id[SILICONID_MAX_LENGTH];
    const char *hex = "0123456789abcdef";
    status_t status;
    uint32_t id_len = sizeof(silicon_id);
    int idx         = 0;
    int i;
    bool id_is_zero = true;

    /* Get unique ID of SoC */
    status = SILICONID_GetID(&silicon_id[0], &id_len);
    assert(status == kStatus_Success);
    assert(id_len > 0U);
    (void)status;

    /* Covert unique ID to client ID string in form: nxp_hex-unique-id */

    /* Check if client_id can accomodate prefix, id and terminator */
    assert(sizeof(client_id) >= (5U + (2U * id_len)));

    /* Fill in prefix */
    client_id[idx++] = 'n';
    client_id[idx++] = 'x';
    client_id[idx++] = 'p';
    client_id[idx++] = '_';

    /* Append unique ID */
    for (i = (int)id_len - 1; i >= 0; i--)
    {
        uint8_t value    = silicon_id[i];
        client_id[idx++] = hex[value >> 4];
        client_id[idx++] = hex[value & 0xFU];

        if (value != 0)
        {
            id_is_zero = false;
        }
    }

    /* Terminate string */
    client_id[idx] = '\0';

    if (id_is_zero)
    {
        PRINTF(
            "WARNING: MQTT client id is zero. (%s)"
#ifdef OCOTP
            " This might be caused by blank OTP memory."
#endif
            "\r\n",
            client_id);
    }
}


/*!
 * @brief Create and run example thread
 *
 * @param netif  netif which example should use
 */
void mqtt_freertos_run_thread(struct netif *netif)
{
    LOCK_TCPIP_CORE();
    mqtt_client = mqtt_client_new();
    UNLOCK_TCPIP_CORE();
    if (mqtt_client == NULL)
    {
        PRINTF("mqtt_client_new() failed.\r\n");
        while (1)
        {
        }
    }

    generate_client_id();


    if (sys_thread_new("app_task", app_thread, netif, APP_THREAD_STACKSIZE, APP_THREAD_PRIO) == NULL)
    {
        LWIP_ASSERT("mqtt_freertos_start_thread(): Task creation failed.", 0);
    }
}
