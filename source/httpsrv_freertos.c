/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "httpsrv_freertos.h"

#include "lwip/opt.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#ifndef __REDLIB__
#include <inttypes.h>
#else
#define PRIu32 "u"
#endif

#include "lwip/netif.h"
#include "lwip/sys.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/ip.h"
#include "lwip/netifapi.h"
#include "lwip/sockets.h"
#include "netif/etharp.h"

#include "httpsrv.h"
#include "lwip/apps/mdns.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef HTTPD_DEBUG
#define HTTPD_DEBUG LWIP_DBG_ON
#endif

#ifndef DEBUG_WS
#define DEBUG_WS 0
#endif

#define CGI_DATA_LENGTH_MAX (96)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static char s_mdns_hostname[65] = "";

/*******************************************************************************
 * Code
 ******************************************************************************/


/*!
 * @brief Callback function to generate TXT mDNS record for HTTP service.
 */
static void http_srv_txt(struct mdns_service *service, void *txt_userdata)
{
    mdns_resp_add_service_txtitem(service, "path=/", 6);
}

/*!
 * @brief Configure and enable MDNS service.
 */
void http_server_enable_mdns(struct netif *netif, const char *mdns_hostname)
{
    LOCK_TCPIP_CORE();
    mdns_resp_init();
    mdns_resp_add_netif(netif, mdns_hostname);
    mdns_resp_add_service(netif, mdns_hostname, "_mqtt", DNSSD_PROTO_TCP, 1883, http_srv_txt, NULL);
    UNLOCK_TCPIP_CORE();

    (void)strncpy(s_mdns_hostname, mdns_hostname, sizeof(s_mdns_hostname) - 1);
    s_mdns_hostname[sizeof(s_mdns_hostname) - 1] = '\0'; // Make sure string will be always terminated.
}

/*!
 * @brief Initializes server.
 */

