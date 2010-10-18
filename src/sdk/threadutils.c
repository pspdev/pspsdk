/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * threadutils.c - Thread manager extensions.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 *
 * $Id: threadutils.c 1658 2006-01-07 15:27:56Z tyranid $
 */

#include <string.h>

#include "pspthreadman.h"
#include "pspsdk.h"

#define MAX_UIDS 256

/* TODO: Generalize this for all thread primatives that have names. */

struct _ThreadInfoSkel
{
	SceSize size;
	char name[32];
};

typedef int (*ReferFunc)(SceUID, struct _ThreadInfoSkel*);

static int _pspSdkReferInternal(const char *name, enum SceKernelIdListType type, 
		struct _ThreadInfoSkel *pInfo, int size, ReferFunc pRefer)
{
	int uid_count = 0;

	/* First determine the number of threads we have. */
	int res = sceKernelGetThreadmanIdList(type, NULL, 0, &uid_count);
	if (res < 0) {
		return res;
	}
	if (uid_count == 0) {
		return -1;  /* XXX: Should we return a kernel errorcode here? */
	}

	/* Grab UIDs for all of the threads. */
	SceUID uid_buf[uid_count];
	res = sceKernelGetThreadmanIdList(type, uid_buf, uid_count, NULL);
	if (res < 0) {
		return res;
	}

	int i;
	for (i = 0; i < uid_count; i++) {
		memset(pInfo, 0, size);
		pInfo->size = size;

		res = pRefer(uid_buf[i], pInfo);
		if (res < 0) {
			/* If we got an error than we probably don't have enough privileges
			   to access the thread's info. */
			continue;
		}

		if (pInfo->name[0] != '\0' && strcmp(pInfo->name, name) == 0) {
			/* Found it. */
			return uid_buf[i];
		}
	}

	/* Unable to find the thread (or insufficient access to retrieve it's info). */
	return -1;  /* XXX: Should we return a kernel errorcode here? */
}

int pspSdkReferSemaStatusByName(const char *name, SceUID *pUID, SceKernelSemaInfo *pInfo)
{
	SceKernelSemaInfo intSema;
	SceUID uid;

	uid = _pspSdkReferInternal(name, SCE_KERNEL_TMID_Semaphore, (struct _ThreadInfoSkel *) &intSema, 
			sizeof(intSema), (ReferFunc) sceKernelReferSemaStatus);
	if(uid > 0)
	{
		if(pUID != NULL)
		{
			*pUID = uid;
		}

		if(pInfo != NULL)
		{
			memcpy(pInfo, &intSema, sizeof(intSema));
		}
	}
	else
	{
		return -1;
	}

	return 0;
}

int pspSdkReferEventFlagStatusByName(const char *name, SceUID *pUID, SceKernelEventFlagInfo *pInfo)
{
	SceKernelEventFlagInfo intEvent;
	SceUID uid;

	uid = _pspSdkReferInternal(name, SCE_KERNEL_TMID_EventFlag, (struct _ThreadInfoSkel *) &intEvent, 
			sizeof(intEvent), (ReferFunc) sceKernelReferEventFlagStatus);
	if(uid > 0)
	{
		if(pUID != NULL)
		{
			*pUID = uid;
		}

		if(pInfo != NULL)
		{
			memcpy(pInfo, &intEvent, sizeof(intEvent));
		}
	}
	else
	{
		return -1;
	}

	return 0;
}

int pspSdkReferThreadStatusByName(const char *name, SceUID *pUID, SceKernelThreadInfo *pInfo)
{
	SceKernelThreadInfo intThread;
	SceUID uid;

	uid = _pspSdkReferInternal(name, SCE_KERNEL_TMID_Thread, (struct _ThreadInfoSkel *) &intThread, 
			sizeof(intThread), (ReferFunc) sceKernelReferThreadStatus);
	if(uid > 0)
	{
		if(pUID != NULL)
		{
			*pUID = uid;
		}

		if(pInfo != NULL)
		{
			memcpy(pInfo, &intThread, sizeof(intThread));
		}
	}
	else
	{
		return -1;
	}

	return 0;
}

int pspSdkReferMboxStatusByName(const char *name, SceUID *pUID, SceKernelMbxInfo *pInfo)
{
	SceKernelMbxInfo intMbx;
	SceUID uid;

	uid = _pspSdkReferInternal(name, SCE_KERNEL_TMID_Mbox, (struct _ThreadInfoSkel *) &intMbx, 
			sizeof(intMbx), (ReferFunc) sceKernelReferMbxStatus);
	if(uid > 0)
	{
		if(pUID != NULL)
		{
			*pUID = uid;
		}

		if(pInfo != NULL)
		{
			memcpy(pInfo, &intMbx, sizeof(intMbx));
		}
	}
	else
	{
		return -1;
	}

	return 0;
}


int pspSdkReferVplStatusByName(const char *name, SceUID *pUID, SceKernelVplInfo *pInfo)
{
	SceKernelVplInfo intVpl;
	SceUID uid;

	uid = _pspSdkReferInternal(name, SCE_KERNEL_TMID_Vpl, (struct _ThreadInfoSkel *) &intVpl, 
			sizeof(intVpl), (ReferFunc) sceKernelReferVplStatus);
	if(uid > 0)
	{
		if(pUID != NULL)
		{
			*pUID = uid;
		}

		if(pInfo != NULL)
		{
			memcpy(pInfo, &intVpl, sizeof(intVpl));
		}
	}
	else
	{
		return -1;
	}

	return 0;
}

int pspSdkReferFplStatusByName(const char *name, SceUID *pUID, SceKernelFplInfo *pInfo)
{
	SceKernelVplInfo intFpl;
	SceUID uid;

	uid = _pspSdkReferInternal(name, SCE_KERNEL_TMID_Fpl, (struct _ThreadInfoSkel *) &intFpl, 
			sizeof(intFpl), (ReferFunc) sceKernelReferFplStatus);
	if(uid > 0)
	{
		if(pUID != NULL)
		{
			*pUID = uid;
		}

		if(pInfo != NULL)
		{
			memcpy(pInfo, &intFpl, sizeof(intFpl));
		}
	}
	else
	{
		return -1;
	}

	return 0;
}


int pspSdkReferMppStatusByName(const char *name, SceUID *pUID, SceKernelMppInfo *pInfo)
{
	SceKernelMppInfo intMpp;
	SceUID uid;

	uid = _pspSdkReferInternal(name, SCE_KERNEL_TMID_Mpipe, (struct _ThreadInfoSkel *) &intMpp, 
			sizeof(intMpp), (ReferFunc) sceKernelReferMsgPipeStatus);
	if(uid > 0)
	{
		if(pUID != NULL)
		{
			*pUID = uid;
		}

		if(pInfo != NULL)
		{
			memcpy(pInfo, &intMpp, sizeof(intMpp));
		}
	}
	else
	{
		return -1;
	}

	return 0;
}

int pspSdkReferCallbackStatusByName(const char *name, SceUID *pUID, SceKernelCallbackInfo *pInfo)
{
	SceKernelCallbackInfo intCB;
	SceUID uid;

	uid = _pspSdkReferInternal(name, SCE_KERNEL_TMID_Callback, (struct _ThreadInfoSkel *) &intCB, 
			sizeof(intCB), (ReferFunc) sceKernelReferCallbackStatus);
	if(uid > 0)
	{
		if(pUID != NULL)
		{
			*pUID = uid;
		}

		if(pInfo != NULL)
		{
			memcpy(pInfo, &intCB, sizeof(intCB));
		}
	}
	else
	{
		return -1;
	}

	return 0;
}

int pspSdkReferVTimerStatusByName(const char *name, SceUID *pUID, SceKernelVTimerInfo *pInfo)
{
	SceKernelVTimerInfo intVT;
	SceUID uid;

	uid = _pspSdkReferInternal(name, SCE_KERNEL_TMID_VTimer, (struct _ThreadInfoSkel *) &intVT, 
			sizeof(intVT), (ReferFunc) sceKernelReferVTimerStatus);
	if(uid > 0)
	{
		if(pUID != NULL)
		{
			*pUID = uid;
		}

		if(pInfo != NULL)
		{
			memcpy(pInfo, &intVT, sizeof(intVT));
		}
	}
	else
	{
		return -1;
	}

	return 0;
}

int pspSdkReferThreadEventHandlerStatusByName(const char *name, SceUID *pUID, SceKernelThreadEventHandlerInfo *pInfo)
{
	SceKernelThreadEventHandlerInfo intEH;
	SceUID uid;

	uid = _pspSdkReferInternal(name, SCE_KERNEL_TMID_ThreadEventHandler, (struct _ThreadInfoSkel *) &intEH, 
			sizeof(intEH), (ReferFunc) sceKernelReferThreadEventHandlerStatus);
	if(uid > 0)
	{
		if(pUID != NULL)
		{
			*pUID = uid;
		}

		if(pInfo != NULL)
		{
			memcpy(pInfo, &intEH, sizeof(intEH));
		}
	}
	else
	{
		return -1;
	}

	return 0;
}
