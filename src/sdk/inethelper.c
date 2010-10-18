/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * inethelper.c - Helper functions for internet related modules.
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 *
 * $Id: inethelper.c 2432 2008-09-17 19:44:47Z jim $
 */

#include <pspkernel.h>
#include <pspsdk.h>
#include <pspnet.h>
#include <pspnet_inet.h>
#include <pspnet_resolver.h>
#include <pspnet_apctl.h>
//#include <pspNetApDialogDummy.h>

#ifdef F_pspSdkLoadInetModules
int pspSdkLoadInetModules()
{
	int modID;

	modID = pspSdkLoadStartModule("flash0:/kd/ifhandle.prx", PSP_MEMORY_PARTITION_KERNEL);
	if (modID < 0)
		return modID;

	modID = pspSdkLoadStartModule("flash0:/kd/pspnet.prx", PSP_MEMORY_PARTITION_USER); 
	if (modID < 0)
		return modID;
	else
		pspSdkFixupImports(modID);

	modID = pspSdkLoadStartModule("flash0:/kd/pspnet_inet.prx", PSP_MEMORY_PARTITION_USER); 
	if (modID < 0)
		return modID;
	else
		pspSdkFixupImports(modID);

	modID = pspSdkLoadStartModule("flash0:/kd/pspnet_apctl.prx", PSP_MEMORY_PARTITION_USER); 
	if (modID < 0)
		return modID;
	else
		pspSdkFixupImports(modID);
/*
	modID = loadModule("flash0:/kd/pspnet_ap_dialog_dummy.prx", PSP_MEMORY_PARTITION_USER); 
	if (modID < 0)
		return modID;
	else
		fixupImports(modID);
*/
	modID = pspSdkLoadStartModule("flash0:/kd/pspnet_resolver.prx", PSP_MEMORY_PARTITION_USER); 
	if (modID < 0)
		return modID;
	else
		pspSdkFixupImports(modID);

	return 0;
}
#endif

#ifdef F_pspSdkInetInit
int pspSdkInetInit()
{
	u32 retVal;

	retVal = sceNetInit(0x20000, 0x20, 0x1000, 0x20, 0x1000);
	if (retVal != 0)
		return retVal;

	retVal = sceNetInetInit();
	if (retVal != 0)
		return retVal;

	retVal = sceNetResolverInit();
	if (retVal != 0)
		return retVal;
	
	retVal = sceNetApctlInit(0x1600, 0x42);
	if (retVal != 0)
		return retVal;

/*
	retVal = sceNetApDialogDummyInit();
	if(retVal != 0)
		return retVal;
*/
	return 0;
}
#endif

#ifdef F_pspSdkInetTerm
void pspSdkInetTerm()
{
	//sceNetApDialogDummyTerm();
	sceNetApctlTerm();
	sceNetResolverTerm();
	sceNetInetTerm();
	sceNetTerm();
}
#endif
