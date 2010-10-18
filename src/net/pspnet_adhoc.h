/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspnet_adhoc.h - PSP Adhoc networking libraries.
 *
 * Copyright (c) 2006 James F.
 * Copyright (c) 2008 InsertWittyName <tias_dp@hotmail.com>
 *
 * Based on the adhoc code in SMS Plus
 * 
 * $Id: pspnet_adhoc.h 2400 2008-07-06 22:46:56Z iwn $
 */
#ifndef __PSPNET_ADHOC_H__
#define __PSPNET_ADHOC_H__

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * Initialise the adhoc library.
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocInit(void);

/**
 * Terminate the adhoc library
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocTerm(void);

/**
 * Create a PDP object.
 *
 * @param mac - Your MAC address (from sceWlanGetEtherAddr)
 * @param port - Port to use, lumines uses 0x309
 * @param bufsize - Socket buffer size, lumines sets to 0x400
 * @param unk1 - Unknown, lumines sets to 0
 *
 * @return The ID of the PDP object (< 0 on error)
 */
int sceNetAdhocPdpCreate(unsigned char *mac, unsigned short port, unsigned int bufsize, int unk1);

/**
 * Delete a PDP object.
 *
 * @param id - The ID returned from ::sceNetAdhocPdpCreate
 * @param unk1 - Unknown, set to 0
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocPdpDelete(int id, int unk1); 

/**
 * Set a PDP packet to a destination
 *
 * @param id - The ID as returned by ::sceNetAdhocPdpCreate
 * @param destMacAddr - The destination MAC address, can be set to all 0xFF for broadcast
 * @param port - The port to send to
 * @param data - The data to send
 * @param len - The length of the data.
 * @param timeout - Timeout in microseconds.
 * @param nonblock - Set to 0 to block, 1 for non-blocking.
 *
 * @return Bytes sent, < 0 on error
 */
int sceNetAdhocPdpSend(int id, unsigned char *destMacAddr, unsigned short port, void *data, unsigned int len, unsigned int timeout, int nonblock); 

/**
 * Receive a PDP packet
 *
 * @param id - The ID of the PDP object, as returned by ::sceNetAdhocPdpCreate
 * @param srcMacAddr - Buffer to hold the source mac address of the sender
 * @param port - Buffer to hold the port number of he received data
 * @param data - Data buffer
 * @param dataLength - The length of the data buffer
 * @param timeout - Timeout in microseconds.
 * @param nonblock - Set to 0 to block, 1 for non-blocking.
 *
 * @return Number of bytes received, < 0 on error.
 */
int sceNetAdhocPdpRecv(int id, unsigned char *srcMacAddr, unsigned short *port, void *data, void *dataLength, unsigned int timeout, int nonblock);

/**
 * PDP status structure
 */
typedef struct pdpStatStruct
{
	/** Pointer to next PDP structure in list */
	struct pdpStatStruct *next;
	/** pdp ID */
	int pdpId;
	/** MAC address */
	unsigned char mac[6];
	/** Port */
	unsigned short port;
	/** Bytes received */
	unsigned int rcvdData;
} pdpStatStruct;

/**
 * Get the status of all PDP objects
 *
 * @param size - Pointer to the size of the stat array (e.g 20 for one structure)
 * @param stat - Pointer to a list of ::pspStatStruct structures.
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocGetPdpStat(int *size, pdpStatStruct *stat);

/**
 * Create own game object type data.
 *
 * @param data - A pointer to the game object data.
 * @param size - Size of the game data.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocGameModeCreateMaster(void *data, int size);

/**
 * Create peer game object type data.
 *
 * @param mac - The mac address of the peer.
 * @param data - A pointer to the game object data.
 * @param size - Size of the game data.
 *
 * @return The id of the replica on success, < 0 on error.
 */
int sceNetAdhocGameModeCreateReplica(unsigned char *mac, void *data, int size);

/**
 * Update own game object type data.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocGameModeUpdateMaster(void);

/**
 * Update peer game object type data.
 *
 * @param id - The id of the replica returned by sceNetAdhocGameModeCreateReplica.
 * @param unk1 - Pass 0.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocGameModeUpdateReplica(int id, int unk1);

/**
 * Delete own game object type data.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocGameModeDeleteMaster(void);

/**
 * Delete peer game object type data.
 *
 * @param id - The id of the replica.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocGameModeDeleteReplica(int id);

/**
 * Open a PTP connection
 *
 * @param srcmac - Local mac address.
 * @param srcport - Local port.
 * @param destmac - Destination mac.
 * @param destport - Destination port
 * @param bufsize - Socket buffer size
 * @param delay - Interval between retrying (microseconds).
 * @param count - Number of retries.
 * @param unk1 - Pass 0.
 *
 * @return A socket ID on success, < 0 on error.
 */
int sceNetAdhocPtpOpen(unsigned char *srcmac, unsigned short srcport, unsigned char *destmac, unsigned short destport, unsigned int bufsize, unsigned int delay, int count, int unk1);

/**
 * Wait for connection created by sceNetAdhocPtpOpen()
 *
 * @param id - A socket ID.
 * @param timeout - Timeout in microseconds.
 * @param nonblock - Set to 0 to block, 1 for non-blocking.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocPtpConnect(int id, unsigned int timeout, int nonblock);

/**
 * Wait for an incoming PTP connection
 *
 * @param srcmac - Local mac address.
 * @param srcport - Local port.
 * @param bufsize - Socket buffer size
 * @param delay - Interval between retrying (microseconds).
 * @param count - Number of retries.
 * @param queue - Connection queue length.
 * @param unk1 - Pass 0.
 *
 * @return A socket ID on success, < 0 on error.
 */
int sceNetAdhocPtpListen(unsigned char *srcmac, unsigned short srcport, unsigned int bufsize, unsigned int delay, int count, int queue, int unk1);

/**
 * Accept an incoming PTP connection
 *
 * @param id - A socket ID.
 * @param mac - Connecting peers mac.
 * @param port - Connecting peers port.
 * @param timeout - Timeout in microseconds.
 * @param nonblock - Set to 0 to block, 1 for non-blocking.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocPtpAccept(int id, unsigned char *mac, unsigned short *port, unsigned int timeout, int nonblock);

/**
 * Send data
 *
 * @param id - A socket ID.
 * @param data - Data to send.
 * @param datasize - Size of the data.
 * @param timeout - Timeout in microseconds.
 * @param nonblock - Set to 0 to block, 1 for non-blocking.
 *
 * @return 0 success, < 0 on error.
 */
int sceNetAdhocPtpSend(int id, void *data, int *datasize, unsigned int timeout, int nonblock);

/**
 * Receive data
 *
 * @param id - A socket ID.
 * @param data - Buffer for the received data.
 * @param datasize - Size of the data received.
 * @param timeout - Timeout in microseconds.
 * @param nonblock - Set to 0 to block, 1 for non-blocking.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocPtpRecv(int id, void *data, int *datasize, unsigned int timeout, int nonblock);

/**
 * Wait for data in the buffer to be sent
 *
 * @param id - A socket ID.
 * @param timeout - Timeout in microseconds.
 * @param nonblock - Set to 0 to block, 1 for non-blocking.
 *
 * @return A socket ID on success, < 0 on error.
 */
int sceNetAdhocPtpFlush(int id, unsigned int timeout, int nonblock);

/**
 * Close a socket
 *
 * @param id - A socket ID.
 * @param unk1 - Pass 0.
 *
 * @return A socket ID on success, < 0 on error.
 */
int sceNetAdhocPtpClose(int id, int unk1);

/**
 * PTP status structure
 */
typedef struct ptpStatStruct
{
	/** Pointer to next PTP structure in list */
	struct ptpStatStruct *next;
	/** ptp ID */
	int ptpId;
	/** MAC address */
	unsigned char mac[6];
	/** Peer MAC address */
	unsigned char peermac[6];
	/** Port */
	unsigned short port;
	/** Peer Port */
	unsigned short peerport;
	/** Bytes sent */
	unsigned int sentData;
	/** Bytes received */
	unsigned int rcvdData;
	/** Unknown */
	int unk1;
} ptpStatStruct;

/**
 * Get the status of all PTP objects
 *
 * @param size - Pointer to the size of the stat array (e.g 20 for one structure)
 * @param stat - Pointer to a list of ::ptpStatStruct structures.
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocGetPtpStat(int *size, ptpStatStruct *stat);

#ifdef __cplusplus
}
#endif

#endif
