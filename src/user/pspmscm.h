/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmscm.h - Memory stick utility functions
 *
 * Copyright (c) 2006 Adrahil
 *
 * $Id: pspmscm.h 2005 2006-09-17 21:36:52Z tyranid $
 */
#ifndef PSPMSCM_H
#define PSPMSCM_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns whether a memory stick is current inserted
 *
 * @return 1 if memory stick inserted, 0 if not or if < 0 on error
 */
static __inline__ int MScmIsMediumInserted(void)
{
	int status, ret;

	ret = sceIoDevctl("mscmhc0:", 0x02025806, 0, 0, &status, sizeof(status));
	if(ret < 0) return ret;
	if(status != 1) return 0;

	return 1;
}

/* Event which has occurred in the memory stick ejection callback, passed in arg2 */
#define MS_CB_EVENT_INSERTED 1
#define MS_CB_EVENT_EJECTED  2

/**
 * Registers a memory stick ejection callback
 *
 * @param cbid - The uid of an allocated callback
 *
 * @return 0 on success, < 0 on error
 */
static __inline__ int MScmRegisterMSInsertEjectCallback(SceUID cbid)
{
	return sceIoDevctl("fatms0:", 0x02415821, &cbid, sizeof(cbid), 0, 0);
}

/**
 * Unregister a memory stick ejection callback
 *
 * @param cbid - The uid of an allocated callback
 *
 * @return 0 on success, < 0 on error
 */
static __inline__ int MScmUnregisterMSInsertEjectCallback(SceUID cbid)
{
	return sceIoDevctl("fatms0:", 0x02415822, &cbid, sizeof(cbid), 0, 0);
}

#ifdef __cplusplus
}
#endif

#endif /* PSPMSCM_H */
