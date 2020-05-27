/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Sample to show registry usage
 *
 * Copyright (c) 2006 James F
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspreg.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <string.h>
#include <stdio.h>

#define printf pspDebugScreenPrintf

/* Define the module info section */
PSP_MODULE_INFO("regsample", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int get_registry_value(const char *dir, const char *name, unsigned int *val)
{
	int ret = 0;
	struct RegParam reg;
	REGHANDLE h;

	memset(&reg, 0, sizeof(reg));
	reg.regtype = 1;
	reg.namelen = strlen("/system");
	reg.unk2 = 1;
	reg.unk3 = 1;
	strcpy(reg.name, "/system");
	if(sceRegOpenRegistry(&reg, 2, &h) == 0)
	{
		REGHANDLE hd;
		if(!sceRegOpenCategory(h, dir, 2, &hd))
		{
			REGHANDLE hk;
			unsigned int type, size;

			if(!sceRegGetKeyInfo(hd, name, &hk, &type, &size))
			{
				if(!sceRegGetKeyValue(hd, hk, val, 4))
				{
					ret = 1;
					sceRegFlushCategory(hd);
				}
			}
			sceRegCloseCategory(hd);
		}
		sceRegFlushRegistry(h);
		sceRegCloseRegistry(h);
	}

	return ret;
}

int set_registry_value(const char *dir, const char *name, unsigned int val)
{
	int ret = 0;
	struct RegParam reg;
	REGHANDLE h;

	memset(&reg, 0, sizeof(reg));
	reg.regtype = 1;
	reg.namelen = strlen("/system");
	reg.unk2 = 1;
	reg.unk3 = 1;
	strcpy(reg.name, "/system");
	if(sceRegOpenRegistry(&reg, 2, &h) == 0)
	{
		REGHANDLE hd;
		if(!sceRegOpenCategory(h, dir, 2, &hd))
		{
			if(!sceRegSetKeyValue(hd, name, &val, 4))
			{
				printf("Set registry value\n");
				ret = 1;
				sceRegFlushCategory(hd);
			}
			sceRegCloseCategory(hd);
		}
		sceRegFlushRegistry(h);
		sceRegCloseRegistry(h);
	}

	return ret;
}

int main(int argc, char *argv[])
{
	unsigned int vol;
	unsigned int but;
	unsigned int lang;

	pspDebugScreenInit();
	printf("Simple Registry Sample (c) 2k6 TyRaNiD\n");
	if(get_registry_value("/CONFIG/SYSTEM/SOUND", "main_volume", &vol))
	{
		printf("Main Volume: %d\n", vol);
	}
	if(get_registry_value("/CONFIG/SYSTEM/XMB", "language", &lang))
	{
		printf("Language : %d\n", lang);
	}
	if(get_registry_value("/CONFIG/SYSTEM/XMB", "button_assign", &but))
	{
		if(but == 0)
		{
			printf("Jap button assignment (Circle is enter)\n");
		}
		else
		{
			printf("NA/EU button assignment (Cross is enter)\n");
		}
	}
	else
	{
		printf("Could not get button_assign (v1.0?). Exiting in 5 seconds\n");
		sceKernelDelayThread(5000000);
		sceKernelExitGame();
	}

	printf("* To swap buttons press Circle *\n");
	printf("* To exit press start *\n");
	while(1)
	{
		SceCtrlData pad;
		sceCtrlPeekBufferPositive(&pad, 1);
		if(pad.Buttons & PSP_CTRL_START)
		{
			sceKernelExitGame();
		}
		if(pad.Buttons & PSP_CTRL_CIRCLE)
		{
			but ^= 1;
			if(set_registry_value("/CONFIG/SYSTEM/XMB", "button_assign", but))
			{
				if(but)
				{
					printf("Set to NA/EU mode\n");
				}
				else
				{
					printf("Set to Jap mode\n");
				}
			}
			else
			{
				printf("Error setting button assignment\n");
			}
			printf("Exiting in 5 seconds\n");
			sceKernelDelayThread(5000000);
			sceKernelExitGame();
		}
		sceDisplayWaitVblankStart();
	}

	return 0;
}
