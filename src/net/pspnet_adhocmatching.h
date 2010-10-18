/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspnet_adhocmatching.h - PSP Adhoc matching networking libraries.
 *
 * Copyright (c) 2006 James F.
 * Copyright (c) 2008 InsertWittyName <tias_dp@hotmail.com>
 *
 * Based on the adhoc code in SMS Plus
 * 
 * $Id: pspnet_adhocmatching.h 2433 2008-10-15 10:00:27Z iwn $
 */
#ifndef __PSPNETMATCHING_ADHOC_H__
#define __PSPNETMATCHING_ADHOC_H__

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * Matching events used in pspAdhocMatchingCallback
 */
enum pspAdhocMatchingEvents
{
	/** Hello event. optdata contains data if optlen > 0. */
	PSP_ADHOC_MATCHING_EVENT_HELLO =		1,
	/** Join request. optdata contains data if optlen > 0. */
	PSP_ADHOC_MATCHING_EVENT_JOIN =			2,
	/** Target left matching. */
	PSP_ADHOC_MATCHING_EVENT_LEFT =			3,
	/** Join request rejected. */
	PSP_ADHOC_MATCHING_EVENT_REJECT =		4,
	/** Join request cancelled. */
	PSP_ADHOC_MATCHING_EVENT_CANCEL =		5,
	/** Join request accepted. optdata contains data if optlen > 0. */
	PSP_ADHOC_MATCHING_EVENT_ACCEPT =		6,
	/** Matching is complete. */
	PSP_ADHOC_MATCHING_EVENT_COMPLETE =		7,
	/** Ping timeout event. */
	PSP_ADHOC_MATCHING_EVENT_TIMEOUT =		8,
	/** Error event. */
	PSP_ADHOC_MATCHING_EVENT_ERROR =		9,
	/** Peer disconnect event. */
	PSP_ADHOC_MATCHING_EVENT_DISCONNECT =	10,
	/** Data received event. optdata contains data if optlen > 0. */
	PSP_ADHOC_MATCHING_EVENT_DATA =			11,
	/** Data acknowledged event. */
	PSP_ADHOC_MATCHING_EVENT_DATA_CONFIRM =	12,
	/** Data timeout event. */
	PSP_ADHOC_MATCHING_EVENT_DATA_TIMEOUT =	13
};

/** 
 * Matching modes used in sceNetAdhocMatchingCreate
 */
enum pspAdhocMatchingModes
{
	/** Host */
	PSP_ADHOC_MATCHING_MODE_HOST =		1,
	/** Client */
	PSP_ADHOC_MATCHING_MODE_CLIENT =	2,
	/** Peer to peer */
	PSP_ADHOC_MATCHING_MODE_PTP =		3
};

/** 
 * Linked list for sceNetAdhocMatchingGetMembers
 */
struct pspAdhocMatchingMember
{
	struct pspAdhocMatchingMember *next;
	unsigned char mac[6];
	char unknown[2];
};

/** 
 * Linked list for sceNetAdhocMatchingGetMembers
 */
struct pspAdhocPoolStat
{
	/** Size of the pool */
	int size;
	/** Maximum size of the pool */
	int maxsize;
	/** Unused memory in the pool */
	int freesize;
};

/** 
 * Initialise the Adhoc matching library
 *
 * @param memsize - Internal memory pool size. Lumines uses 0x20000
 * 
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocMatchingInit(int memsize);

/**
 * Terminate the Adhoc matching library
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocMatchingTerm(void);

/** Matching callback */
typedef void (*pspAdhocMatchingCallback)(int matchingid, int event, unsigned char *mac, int optlen, void *optdata);

/**
 * Create an Adhoc matching object
 *
 * @param mode - One of ::pspAdhocMatchingModes
 * @param maxpeers - Maximum number of peers to match (only used when mode is PSP_ADHOC_MATCHING_MODE_HOST)
 * @param port - Port. Lumines uses 0x22B
 * @param bufsize - Receiving buffer size
 * @param hellodelay - Hello message send delay in microseconds (only used when mode is PSP_ADHOC_MATCHING_MODE_HOST or PSP_ADHOC_MATCHING_MODE_PTP)
 * @param pingdelay - Ping send delay in microseconds. Lumines uses 0x5B8D80 (only used when mode is PSP_ADHOC_MATCHING_MODE_HOST or PSP_ADHOC_MATCHING_MODE_PTP)
 * @param initcount - Initial count of the of the resend counter. Lumines uses 3
 * @param msgdelay - Message send delay in microseconds
 * @param callback - Callback to be called for matching
 *
 * @return ID of object on success, < 0 on error.
 */
int sceNetAdhocMatchingCreate(int mode, int maxpeers, unsigned short port, int bufsize, unsigned int hellodelay, unsigned int pingdelay, int initcount, unsigned int msgdelay, pspAdhocMatchingCallback callback);

/**
 * Delete an Adhoc matching object
 *
 * @param matchingid - The ID returned from ::sceNetAdhocMatchingCreate
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocMatchingDelete(int matchingid);

/**
 * Start a matching object
 *
 * @param matchingid - The ID returned from ::sceNetAdhocMatchingCreate
 * @param evthpri - Priority of the event handler thread. Lumines uses 0x10
 * @param evthstack - Stack size of the event handler thread. Lumines uses 0x2000
 * @param inthpri - Priority of the input handler thread. Lumines uses 0x10
 * @param inthstack - Stack size of the input handler thread. Lumines uses 0x2000
 * @param optlen - Size of hellodata
 * @param optdata - Pointer to block of data passed to callback
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocMatchingStart(int matchingid, int evthpri, int evthstack, int inthpri, int inthstack, int optlen, void *optdata);

/** 
 * Stop a matching object
 *
 * @param matchingid - The ID returned from ::sceNetAdhocMatchingCreate
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocMatchingStop(int matchingid);

/**
 * Select a matching target
 *
 * @param matchingid - The ID returned from ::sceNetAdhocMatchingCreate
 * @param mac - MAC address to select
 * @param optlen - Optional data length
 * @param optdata - Pointer to the optional data
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocMatchingSelectTarget(int matchingid, unsigned char *mac, int optlen, void *optdata);

/**
 * Cancel a matching target
 *
 * @param matchingid - The ID returned from ::sceNetAdhocMatchingCreate
 * @param mac - The MAC address to cancel
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocMatchingCancelTarget(int matchingid, unsigned char *mac);

/**
 * Cancel a matching target (with optional data)
 *
 * @param matchingid - The ID returned from ::sceNetAdhocMatchingCreate
 * @param mac - The MAC address to cancel
 * @param optlen - Optional data length
 * @param optdata - Pointer to the optional data
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocMatchingCancelTargetWithOpt(int matchingid, unsigned char *mac, int optlen, void *optdata);

/**
 * Send data to a matching target
 *
 * @param matchingid - The ID returned from ::sceNetAdhocMatchingCreate
 * @param mac - The MAC address to send the data to
 * @param datalen - Length of the data
 * @param data - Pointer to the data
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocMatchingSendData(int matchingid, unsigned char *mac, int datalen, void *data);

/**
 * Abort a data send to a matching target
 *
 * @param matchingid - The ID returned from ::sceNetAdhocMatchingCreate
 * @param mac - The MAC address to send the data to
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocMatchingAbortSendData(int matchingid, unsigned char *mac);

/**
 * Set the optional hello message
 *
 * @param matchingid - The ID returned from ::sceNetAdhocMatchingCreate
 * @param optlen - Length of the hello data
 * @param optdata - Pointer to the hello data
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocMatchingSetHelloOpt(int matchingid, int optlen, void *optdata);

/**
 * Get the optional hello message
 *
 * @param matchingid - The ID returned from ::sceNetAdhocMatchingCreate
 * @param optlen - Length of the hello data
 * @param optdata - Pointer to the hello data
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocMatchingGetHelloOpt(int matchingid, int *optlen, void *optdata);

/**
 * Get a list of matching members
 *
 * @param matchingid - The ID returned from ::sceNetAdhocMatchingCreate
 * @param length - The length of the list.
 * @param buf - An allocated area of size length.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocMatchingGetMembers(int matchingid, int *length, void *buf);

/**
 * Get the maximum memory usage by the matching library
 *
 * @return The memory usage on success, < 0 on error.
 */
int sceNetAdhocMatchingGetPoolMaxAlloc(void);

/**
 * Get the status of the memory pool used by the matching library
 *
 * @param poolstat - A ::pspAdhocPoolStat.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocMatchingGetPoolStat(struct pspAdhocPoolStat *poolstat);

#ifdef __cplusplus
}
#endif

#endif
