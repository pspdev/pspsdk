/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - ELF Based WLAN Scanner
 *
 * Copyright (c) 2005 James F <tyranid@gmail.com>
 *                    adresd
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsdk.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pspnet.h>
#include <pspwlan.h>
#include <pspctrl.h>
#include <pspdisplay.h>

#define printf pspDebugScreenPrintf

#define MODULE_NAME "WlanScanner"

PSP_MODULE_INFO(MODULE_NAME, 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(0);

/* Init the scan */
int sceNet_lib_5216CBF5(const char *name);
/* Do the scan */
int sceNet_lib_7BA3ED91(const char *name, void *type, u32 *size, void *buf, u32 *unk);
/* Terminate the scan */
int sceNet_lib_D2422E4D(const char *name);

#define InitScan sceNet_lib_5216CBF5
#define ScanAPs  sceNet_lib_7BA3ED91
#define TermScan sceNet_lib_D2422E4D

/* Global buffer to store the scan data */
unsigned char scan_data[0xA80];

/* Returned data */
struct ScanData
{
	struct ScanHead *pNext; 
	unsigned char bssid[6]; 
	char channel; 
	unsigned char namesize; 
	char name[32]; 
	unsigned int bsstype; 
	unsigned int beaconperiod; 
	unsigned int dtimperiod; 
	unsigned int timestamp; 
	unsigned int localtime; 
	unsigned short atim; 
	unsigned short capabilities; 
	unsigned char  rate[8]; 
	unsigned short rssi; 
	unsigned char  sizepad[6]; 
} __attribute__((packed));

/* Capability flags */
const char *caps[8] = {
	"ESS, ",
	"IBSS, ",
	"CF Pollable, ",
	"CF Pollreq,  ",
	"Privacy (WEP), ",
	"Short Preamble, ",
	"PBCC, ",
	"Channel Agility, "
};

/* Print the scan summary data to stdout */
void print_apsum(struct ScanData *pData)
{
	char name[33];
	int  loop;
	strncpy(name, pData->name, 32);
	name[32] = 0;
	printf("RSSI:%02d  ", pData->rssi);
	if (pData->capabilities & (1 << 4))
		printf(" WEP! ");
	else
		printf("NO WEP");
	printf("   SSID: %s\n", name);
}

/* Print the scan data to stdout */
void print_ap(struct ScanData *pData)
{
	char name[33];
	char bssid[30];
	int  loop;

	strncpy(name, pData->name, 32);
	name[32] = 0;
	sceNetEtherNtostr(pData->bssid, bssid);
	printf("BSSID: %s\n", bssid);
	printf("SSID: %s\n", name);
	printf("bsstype: ");
	if(pData->bsstype == 1)
	{
		printf("Infrastructure\n");
	}
	else if(pData->bsstype == 2)
	{
		printf("Independent\n");
	}
	else
	{
		printf("Unknown\n");
	}
	printf("Beacon Period: %d\n", pData->beaconperiod);
	printf("DTIM period: %d\n", pData->dtimperiod);
	printf("Timestamp: %d\n", pData->timestamp);
	printf("Local Time: %d\n", pData->localtime);
	printf("Channel: %d\n", pData->channel);
	printf("ATIM: %d\n", pData->atim);
	printf("Capability Information: ");
	for(loop = 0; loop < 8; loop++)
	{
		if(pData->capabilities & (1 << loop))
		{
			printf("%s", caps[loop]);
		}
	}
	printf("\n");

	printf("Rate: ");
	for(loop = 0; loop < 8; loop++)
	{
		const char *type;

		if(pData->rate[loop] & 0x80)
		{
			type = "Basic";
		}
		else
		{
			type = "Operational";
		}

		if(pData->rate[loop] & 0x7F)
		{
			printf("%s %d kbps, ", type, (pData->rate[loop] & 0x7F) * 500);
		}
	}
	printf("\n");

	printf("RSSI: %d\n", pData->rssi);

	printf("\n");
}

/* Do a scan */
struct ScanData *do_scan(int *count)
{
	unsigned char type[0x4C];
	u32 size, unk;
	int i;
	int ret;

	if((ret = InitScan("wlan")) >= 0)
	{
		memset(type, 0, sizeof(type));
		/* Set the channels we want to scan */
		for(i = 1; i < 0xF; i++)
		{
			type[0x9+i] = i;
		}
		type[0x3C] = 1;
		*((u32*) (type + 0x44)) = 1;    //6/* Minimum strength */
		*((u32*) (type + 0x48)) = 100;  /* Maximum strength */
		size = sizeof(scan_data);
		unk  = 0;
		memset(scan_data, 0, sizeof(scan_data));
		ret = ScanAPs("wlan", type, &size, scan_data, &unk);
		if(ret < 0)
		{
			printf("Error, could not perform scan err = %08X\n", ret);
		}
		else
		{
			*count = size / sizeof(struct ScanData);
			return (struct ScanData *) scan_data;
		}
	}
	else
	{
		printf("Error, cannot initialise scan %08X\n", ret);
	}

	TermScan("wlan");

	return NULL;
}

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	sceWlanDevDetach();
	sceNetTerm();
	sceKernelExitGame();
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

void start_ui(struct ScanData *pScan, int count)
{
	unsigned int last = 0;
	SceCtrlData pad;
	int ap = 0;
	int loop = 1;
	int vcount = 0;

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	while(loop)
	{
		pspDebugScreenClear();
		printf("Scan found %d access point(s)\n\n", count);

		printf("Press X to rescan, SQUARE to quit\n");

		if (count == 0) printf("\nAuto re-scan in 30 seconds\n");
		else 			printf("Press O to view/cycle through the access points\n\n");
		

		if (ap == 0)
		{
			int x;
			for (x=0;x<count;x++)
			{
				print_apsum(&pScan[x]);
			}
		}
		else
		{
			printf("\nDisplaying access point %d:\n\n", ap);
			print_ap(&pScan[ap-1]);
		}
		
		while(loop)
		{
			unsigned int mask;
	
			sceCtrlReadBufferPositive(&pad, 1);
			mask = pad.Buttons & ~last;
			last = pad.Buttons;
			if(mask & PSP_CTRL_CIRCLE)
			{
				ap = (ap + 1) % (count+1);
				break;
			}
			if(mask & PSP_CTRL_CROSS) loop = 0;
			if(mask & PSP_CTRL_SQUARE) sceKernelExitGame();
			sceDisplayWaitVblankStart();
			if (count == 0)
			{
				if ((vcount % 60) == 0) printf(".");
				vcount++;
				if (vcount > (30*60)) loop = 0; // auto-rescan
			}
		}
	}
}

int net_thread(SceSize args, void *argp)
{
	int ret;
	struct ScanData *pScan = NULL;
	int count;

	printf("Please wait, performing WLAN AP scan...\n");
	ret = sceNetInit(0x20000, 0x20, 0x1000, 0x20, 0x1000);
	if(ret < 0)
	{
		printf("Error initialising network lib %08X\n", ret);
		goto error;
	}

	ret = -1;
	while(ret < 0)
	{
		ret = sceWlanDevAttach();

		/* If returns a error which indicates it isn't ready */
		if(ret == 0x80410D0E)
		{
			sceKernelDelayThread(1000000);
		}
		else if(ret < 0)
		{
			printf("Error attaching to wlan device %08X\n", ret);
			goto error;
		}
	}

	pScan = do_scan(&count);
	while (pScan != NULL)
	{
		start_ui(pScan, count);

		printf("\n\nPlease wait, performing WLAN AP scan...\n");
		pScan = do_scan(&count);
	}

error:
	sceWlanDevDetach();
	sceNetTerm();

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
