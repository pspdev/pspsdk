/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Example of using the WLAN scanner
 * The info here was reversed from scan.prx which Sony/Namco so 
 * helpfully left in plain sight on the japanese ridge racer UMD
 * Thx boys :)
 *
 * Copyright (c) 2006 James F
 *
 */
#include <pspkernel.h>
#include <stdio.h>
#include <pspnet.h>
#include <pspwlan.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("wlanscan", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

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
	"Privacy, ",
	"Short Preamble, ",
	"PBCC, ",
	"Channel Agility, "
};

/* Print the scan data to stdout */
void print_scan(unsigned char *data, int size)
{
	int i = 1;

	while(size >= sizeof(struct ScanData))
	{
		char name[33];
		char bssid[30];
		int  loop;
		struct ScanData *pData;

		pData = (struct ScanData *) data;
		printf("==================\n");
		printf("      BSS: %d\n", i);
		printf("==================\n");
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
		i++;
		data += sizeof(struct ScanData);
		size -= sizeof(struct ScanData);
	}
}

/* Do a scan */
void do_scan(void)
{
	unsigned char type[0x4C];
	u32 size, unk;
	int i;
	int ret;

	if(InitScan("wlan") >= 0)
	{
		/* No real idea what this is doing ;) */
		memset(type, 0, sizeof(type));
		for(i = 1; i < 0xF; i++)
		{
			type[0x9+i] = i;
		}
		type[0x3C] = 1;
		*((u32*) (type + 0x44)) = 6;    /* Minimum strength */
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
			print_scan(scan_data, size);
		}
	}
	else
	{
		printf("Error, cannot initialise scan\n");
	}

	TermScan("wlan");
}

int main(int argc, char *argv[])
{
	int ret;

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

	do_scan();
error:
	sceWlanDevDetach();
	sceNetTerm();

	return 0;
}
