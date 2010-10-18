/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspnet_adhocctl.h - PSP Adhoc control networking libraries.
 *
 * Copyright (c) 2006 James F.
 * Copyright (c) 2008 InsertWittyName <tias_dp@hotmail.com>
 *
 * Based on the adhoc code in SMS Plus
 * 
 * $Id: pspnet_adhocctl.h 2433 2008-10-15 10:00:27Z iwn $
 */
#ifndef __PSPNETCTL_ADHOC_H__
#define __PSPNETCTL_ADHOC_H__

#ifdef __cplusplus
extern "C" {
#endif

/** Product structure */
struct productStruct
{
	/** Unknown, set to 0 */
	int unknown;
	/** The product ID string */
	char product[9];
} productStruct;

/** Peer info structure */
struct SceNetAdhocctlPeerInfo
{
	struct SceNetAdhocctlPeerInfo *next;
	/** Nickname */
	char nickname[128];	
	/** Mac address */
	unsigned char mac[6];
	/** Unknown */
	unsigned char unknown[6];
	/** Time stamp */
	unsigned long timestamp;
};

/** Scan info structure */
struct SceNetAdhocctlScanInfo
{
	struct SceNetAdhocctlScanInfo *next;
	/** Channel number */
	int channel;
	/** Name of the connection (alphanumeric characters only) */
	char name[8];
	/** The BSSID */
	unsigned char bssid[6];
	/** Unknown */
	unsigned char unknown[2];
	/** Unknown */
	int unknown2;
};

struct SceNetAdhocctlGameModeInfo
{
	/** Number of peers (including self) */
	int count;
	/** MAC addresses of peers (including self) */
	unsigned char macs[16][6];
};

/** Params structure */
struct SceNetAdhocctlParams
{
	/** Channel number */
	int channel;
	/** Name of the connection */
	char name[8];
	/** The BSSID */
	unsigned char bssid[6];
	/** Nickname */
	char nickname[128];
};

/**
 * Initialise the Adhoc control library
 *
 * @param stacksize - Stack size of the adhocctl thread. Set to 0x2000
 * @param priority - Priority of the adhocctl thread. Set to 0x30
 * @param product - Pass a filled in ::productStruct
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocctlInit(int stacksize, int priority, struct productStruct *product);

/**
 * Terminate the Adhoc control library
 *
 * @return 0 on success, < on error.
 */
int sceNetAdhocctlTerm(void);

/**
 * Connect to the Adhoc control
 *
 * @param name - The name of the connection (maximum 8 alphanumeric characters).
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlConnect(const char *name);

/**
 * Disconnect from the Adhoc control
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocctlDisconnect(void);

/**
 * Get the state of the Adhoc control
 *
 * @param event - Pointer to an integer to receive the status. Can continue when it becomes 1.
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocctlGetState(int *event);

/**
 * Connect to the Adhoc control (as a host)
 *
 * @param name - The name of the connection (maximum 8 alphanumeric characters).
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlCreate(const char *name);

/**
 * Connect to the Adhoc control (as a client)
 *
 * @param scaninfo - A valid ::SceNetAdhocctlScanInfo struct that has been filled by sceNetAchocctlGetScanInfo
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlJoin(struct SceNetAdhocctlScanInfo *scaninfo);

/**
 * Get the adhoc ID
 *
 * @param product - A pointer to a  ::productStruct
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlGetAdhocId(struct productStruct *product);

/**
 * Connect to the Adhoc control game mode (as a host)
 *
 * @param name - The name of the connection (maximum 8 alphanumeric characters).
 * @param unknown - Pass 1.
 * @param num - The total number of players (including the host).
 * @param macs - A pointer to a list of the participating mac addresses, host first, then clients.
 * @param timeout - Timeout in microseconds.
 * @param unknown2 - pass 0.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlCreateEnterGameMode(const char *name, int unknown, int num, unsigned char *macs, unsigned int timeout, int unknown2);

/**
 * Connect to the Adhoc control game mode (as a client)
 *
 * @param name - The name of the connection (maximum 8 alphanumeric characters).
 * @param hostmac - The mac address of the host.
 * @param timeout - Timeout in microseconds.
 * @param unknown - pass 0.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlJoinEnterGameMode(const char *name, unsigned char *hostmac, unsigned int timeout, int unknown);

/**
 * Get game mode information
 *
 * @param gamemodeinfo - Pointer to store the info.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlGetGameModeInfo(struct SceNetAdhocctlGameModeInfo *gamemodeinfo);

/**
 * Exit game mode.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlExitGameMode(void);

/**
 * Get a list of peers
 *
 * @param length - The length of the list.
 * @param buf - An allocated area of size length.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlGetPeerList(int *length, void *buf);

/**
 * Get peer information
 *
 * @param mac - The mac address of the peer.
 * @param size - Size of peerinfo.
 * @param peerinfo - Pointer to store the information.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlGetPeerInfo(unsigned char *mac, int size, struct SceNetAdhocctlPeerInfo *peerinfo);

/**
 * Scan the adhoc channels
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlScan(void);

/**
 * Get the results of a scan
 *
 * @param length - The length of the list.
 * @param buf - An allocated area of size length.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlGetScanInfo(int *length, void *buf);

typedef void (*sceNetAdhocctlHandler)(int flag, int error, void *unknown);

/**
 * Register an adhoc event handler
 *
 * @param handler - The event handler.
 * @param unknown - Pass NULL.
 *
 * @return Handler id on success, < 0 on error.
 */
int sceNetAdhocctlAddHandler(sceNetAdhocctlHandler handler, void *unknown);

/**
 * Delete an adhoc event handler
 *
 * @param id - The handler id as returned by sceNetAdhocctlAddHandler.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlDelHandler(int id);

/**
 * Get nickname from a mac address
 *
 * @param mac - The mac address.
 * @param nickname - Pointer to a char buffer where the nickname will be stored.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlGetNameByAddr(unsigned char *mac, char *nickname);

/**
 * Get mac address from nickname
 *
 * @param nickname - The nickname.
 * @param length - The length of the list.
 * @param buf - An allocated area of size length.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlGetAddrByName(char *nickname, int *length, void *buf);

/**
 * Get Adhocctl parameter
 *
 * @param params - Pointer to a ::SceNetAdhocctlParams
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlGetParameter(struct SceNetAdhocctlParams *params);

#ifdef __cplusplus
}
#endif

#endif
