/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Simple DNS resolver example
 *
 * Copyright (c) 2006 James F <tyranid@gmail.com>
 * Some small parts (c) 2005 PSPPet
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsdk.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pspnet.h>
#include <pspnet_inet.h>
#include <pspnet_apctl.h>
#include <pspnet_resolver.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>

#define printf pspDebugScreenPrintf

#define MODULE_NAME "Resolver"

#define RESOLVE_NAME "badgers.com"

PSP_MODULE_INFO(MODULE_NAME, 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(0);

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread,
				     0x11, 0xFA0, PSP_THREAD_ATTR_USER, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

void do_resolver(void)
{
	int rid = -1;
	char buf[1024];
	struct in_addr addr;
	char name[1024];

	do
	{
		/* Create a resolver */
		if(sceNetResolverCreate(&rid, buf, sizeof(buf)) < 0)
		{
			printf("Error creating resolver\n");
			break;
		}

		printf("Created resolver %08x\n", rid);

		/* Resolve a name to an ip address */
		if(sceNetResolverStartNtoA(rid, RESOLVE_NAME, &addr, 2, 3) < 0)
		{
			printf("Error resolving %s\n", RESOLVE_NAME);
			break;
		}

		printf("Resolved %s to %s\n", RESOLVE_NAME, inet_ntoa(addr));

		/* Resolve the ip address to a name */
		if(sceNetResolverStartAtoN(rid, &addr, name, sizeof(name), 2, 3) < 0)
		{
			printf("Error resolving ip to name\n");
			break;
		}

		printf("Resolved ip to %s\n", name);
	}
	while(0);

	if(rid >= 0)
	{
		sceNetResolverDelete(rid);
	}
}

/* Connect to an access point */
int connect_to_apctl(int config)
{
	int err;
	int stateLast = -1;

	/* Connect using the first profile */
	err = sceNetApctlConnect(config);
	if (err != 0)
	{
		printf(MODULE_NAME ": sceNetApctlConnect returns %08X\n", err);
		return 0;
	}

	printf(MODULE_NAME ": Connecting...\n");
	while (1)
	{
		int state;
		err = sceNetApctlGetState(&state);
		if (err != 0)
		{
			printf(MODULE_NAME ": sceNetApctlGetState returns $%x\n", err);
			break;
		}
		if (state > stateLast)
		{
			printf("  connection state %d of 4\n", state);
			stateLast = state;
		}
		if (state == 4)
			break;  // connected with static IP

		// wait a little before polling again
		sceKernelDelayThread(50*1000); // 50ms
	}
	printf(MODULE_NAME ": Connected!\n");

	if(err != 0)
	{
		return 0;
	}

	return 1;
}

int net_thread(SceSize args, void *argp)
{
	int err;

	do
	{
		if((err = pspSdkInetInit()))
		{
			printf(MODULE_NAME ": Error, could not initialise the network %08X\n", err);
			break;
		}

		if(connect_to_apctl(1))
		{
			// connected, get my IPADDR and run test
			union SceNetApctlInfo info;
			
			if (sceNetApctlGetInfo(8, &info) != 0)
				strcpy(info.ip, "unknown IP");
			
			do_resolver();
		}
	}
	while(0);

	return 0;
}

/* Simple thread */
int main(int argc, char **argv)
{
	SceUID thid;

	SetupCallbacks();

	pspDebugScreenInit();

	if(pspSdkLoadInetModules() < 0)
	{
		printf("Error, could not load inet modules\n");
		sceKernelSleepThread();
	}

	/* Create a user thread to do the real work */
	thid = sceKernelCreateThread("net_thread", net_thread, 0x18, 0x10000, PSP_THREAD_ATTR_USER, NULL);
	if(thid < 0)
	{
		printf("Error, could not create thread\n");
		sceKernelSleepThread();
	}

	sceKernelStartThread(thid, 0, NULL);

	sceKernelExitDeleteThread(0);

	return 0;
}
