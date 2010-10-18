/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspnet_apctl.h - PSP networking libraries.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@0xd6.org>
 * Copyright (c) 2008 David Perry <tias_dp@hotmail.com>
 *
 * Portions based on PspPet's wifi_03 sample code.
 * 
 * $Id: pspnet_apctl.h 2434 2008-10-15 17:37:25Z iwn $
 */

#ifndef PSPNET_APCTL_H
#define PSPNET_APCTL_H

#ifdef __cplusplus
extern "C" {
#endif
	
#define PSP_NET_APCTL_STATE_DISCONNECTED	0
#define PSP_NET_APCTL_STATE_SCANNING		1
#define PSP_NET_APCTL_STATE_JOINING			2
#define PSP_NET_APCTL_STATE_GETTING_IP      3
#define PSP_NET_APCTL_STATE_GOT_IP			4
#define PSP_NET_APCTL_STATE_EAP_AUTH		5
#define PSP_NET_APCTL_STATE_KEY_EXCHANGE	6
	
#define PSP_NET_APCTL_EVENT_CONNECT_REQUEST		0
#define PSP_NET_APCTL_EVENT_SCAN_REQUEST		1
#define PSP_NET_APCTL_EVENT_SCAN_COMPLETE		2
#define PSP_NET_APCTL_EVENT_ESTABLISHED			3
#define PSP_NET_APCTL_EVENT_GET_IP				4
#define PSP_NET_APCTL_EVENT_DISCONNECT_REQUEST	5
#define PSP_NET_APCTL_EVENT_ERROR				6
#define PSP_NET_APCTL_EVENT_INFO				7
#define PSP_NET_APCTL_EVENT_EAP_AUTH			8
#define PSP_NET_APCTL_EVENT_KEY_EXCHANGE		9
#define PSP_NET_APCTL_EVENT_RECONNECT			10
	
#define PSP_NET_APCTL_INFO_PROFILE_NAME		0
#define PSP_NET_APCTL_INFO_BSSID			1
#define PSP_NET_APCTL_INFO_SSID				2
#define PSP_NET_APCTL_INFO_SSID_LENGTH		3
#define PSP_NET_APCTL_INFO_SECURITY_TYPE	4
#define PSP_NET_APCTL_INFO_STRENGTH			5
#define PSP_NET_APCTL_INFO_CHANNEL			6
#define PSP_NET_APCTL_INFO_POWER_SAVE		7
#define PSP_NET_APCTL_INFO_IP				8
#define PSP_NET_APCTL_INFO_SUBNETMASK		9
#define PSP_NET_APCTL_INFO_GATEWAY			10
#define PSP_NET_APCTL_INFO_PRIMDNS			11
#define PSP_NET_APCTL_INFO_SECDNS			12
#define PSP_NET_APCTL_INFO_USE_PROXY		13
#define PSP_NET_APCTL_INFO_PROXY_URL		14
#define PSP_NET_APCTL_INFO_PROXY_PORT		15
#define PSP_NET_APCTL_INFO_8021_EAP_TYPE	16
#define PSP_NET_APCTL_INFO_START_BROWSER	17
#define PSP_NET_APCTL_INFO_WIFISP			18
	
#define PSP_NET_APCTL_INFO_SECURITY_TYPE_NONE	0
#define PSP_NET_APCTL_INFO_SECURITY_TYPE_WEP	1
#define PSP_NET_APCTL_INFO_SECURITY_TYPE_WPA	2
	
union SceNetApctlInfo 
{ 
	char name[64];				/* Name of the config used */ 
	unsigned char bssid[6];		/* MAC address of the access point */ 
	unsigned char ssid[32];		/* ssid */ 			
	unsigned int ssidLength;	/* ssid string length*/ 
	unsigned int securityType;	/* 0 for none, 1 for WEP, 2 for WPA) */ 
	unsigned char strength;		/* Signal strength in % */ 
	unsigned char channel;		/* Channel */ 
	unsigned char powerSave;	/* 1 on, 0 off */ 
	char ip[16];				/* PSP's ip */ 
	char subNetMask[16];		/* Subnet mask */ 
	char gateway[16];			/* Gateway */ 
	char primaryDns[16];		/* Primary DNS */ 
	char secondaryDns[16];		/* Secondary DNS */ 
	unsigned int useProxy;		/* 1 for proxy, 0 for no proxy */ 
	char proxyUrl[128];			/* Proxy url */ 
	unsigned short proxyPort;	/* Proxy port */ 
	unsigned int eapType;		/* 0 is none, 1 is EAP-MD5 */ 
	unsigned int startBrowser;	/* Should browser be started */ 
	unsigned int wifisp;		/* 1 if connection is for Wifi service providers (WISP) */ 

};
	
typedef void (*sceNetApctlHandler)(int oldState, int newState, int event, int error, void *pArg);

/**
 * Init the apctl.
 *
 * @param stackSize - The stack size of the internal thread.
 *
 * @param initPriority - The priority of the internal thread.
 *
 * @return < 0 on error.
 */
int sceNetApctlInit(int stackSize, int initPriority);

/**
 * Terminate the apctl.
 *
 * @return < 0 on error.
 */
int sceNetApctlTerm(void);

/**
 * Get the apctl information.
 *
 * @param code - One of the PSP_NET_APCTL_INFO_* defines.
 *
 * @param pInfo - Pointer to a ::SceNetApctlInfo.
 *
 * @return < 0 on error.
 */
int sceNetApctlGetInfo(int code, union SceNetApctlInfo *pInfo);

/**
 * Add an apctl event handler.
 *
 * @param handler - Pointer to the event handler function.
 *
 * @param pArg - Value to be passed to the pArg parameter of the handler function.
 *
 * @return A handler id or < 0 on error.
 */
int sceNetApctlAddHandler(sceNetApctlHandler handler, void *pArg);
	
/**
 * Delete an apctl event handler.
 *
 * @param handlerid - A handler as created returned from sceNetApctlAddHandler.
 *
 * @return < 0 on error.
 */
int sceNetApctlDelHandler(int handlerId);

/**
 * Connect to an access point.
 *
 * @param connIndex - The index of the connection.
 *
 * @return < 0 on error.
 */
int sceNetApctlConnect(int connIndex);

/**
 * Disconnect from an access point.
 *
 * @return < 0 on error.
 */
int sceNetApctlDisconnect(void);

/**
 * Get the state of the access point connection.
 *
 * @param pState - Pointer to receive the current state (one of the PSP_NET_APCTL_STATE_* defines).
 *
 * @return < 0 on error.
 */
int sceNetApctlGetState(int *pState);

#ifdef __cplusplus
}
#endif

#endif /* PSPNET_APCTL_H */
