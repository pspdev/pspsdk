/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspopenpsid.h - Prototypes for the OpenPSID library
 *
 * Copyright (c) 2008 InsertWittyName (David Perry) 
 *
 */
 
#ifndef __PSPOPENPSID_H__
#define __PSPOPENPSID_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PspOpenPSID
{
	unsigned char data[16];
} PspOpenPSID;

int sceOpenPSIDGetOpenPSID(PspOpenPSID *openpsid);

#ifdef __cplusplus
}
#endif

#endif	/* __PSPOPENPSID_H__ */
