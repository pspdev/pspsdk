/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspnet.h - PSP networking libraries.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@0xd6.org>
 * Copyright (c) 2008 David Perry <tias_dp@hotmail.com>
 *
 * Portions based on PspPet's wifi_03 sample code.
 * 
 * $Id: pspnet.h 2439 2008-10-23 18:58:06Z iwn $
 */

#ifndef PSPNET_H
#define PSPNET_H

#ifdef __cplusplus
extern "C" {
#endif
	
typedef struct SceNetMallocStat
{
	int pool;
	int maximum;
	int free;
	
} SceNetMallocStat;

/**
 * Initialise the networking library
 *
 * @param poolsize - Memory pool size (appears to be for the whole of the networking library).
 * @param calloutprio - Priority of the SceNetCallout thread.
 * @param calloutstack - Stack size of the SceNetCallout thread (defaults to 4096 on non 1.5 firmware regardless of what value is passed).
 * @param netintrprio - Priority of the SceNetNetintr thread.
 * @param netintrstack - Stack size of the SceNetNetintr thread (defaults to 4096 on non 1.5 firmware regardless of what value is passed).
 *
 * @return 0 on success, < 0 on error
 */
int sceNetInit(int poolsize, int calloutprio, int calloutstack, int netintrprio, int netintrstack);
	
/**
 * Terminate the networking library
 *
 * @return 0 on success, < 0 on error
 */
int sceNetTerm(void);

/**
 * Free (delete) thread info/data
 *
 * @param thid - The thread id.
 *
 * @return 0 on success, < 0 on error
 */
int sceNetFreeThreadinfo(int thid);

/**
 * Abort a thread
 *
 * @param thid - The thread id.
 *
 * @return 0 on success, < 0 on error
 */
int sceNetThreadAbort(int thid);

/**
 * Convert string to a Mac address
 *
 * @param name - The string to convert.
 * @param mac - Pointer to a buffer to store the result.
 */
void sceNetEtherStrton(char *name, unsigned char *mac);

/**
 * Convert Mac address to a string
 *
 * @param mac - The Mac address to convert.
 * @param name - Pointer to a buffer to store the result.
 */
void sceNetEtherNtostr(unsigned char *mac, char *name);

/**
 * Retrieve the local Mac address
 *
 * @param mac - Pointer to a buffer to store the result.
 *
 * @return 0 on success, < 0 on error
 */
int sceNetGetLocalEtherAddr(unsigned char *mac);

/**
 * Retrieve the networking library memory usage
 *
 * @param stat - Pointer to a ::SceNetMallocStat type to store the result.
 *
 * @return 0 on success, < 0 on error
 */
int sceNetGetMallocStat(SceNetMallocStat *stat);

#ifdef __cplusplus
}
#endif

#endif /* PSPNET_H */
