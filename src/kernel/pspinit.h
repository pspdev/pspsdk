/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspinit.h - Interface to InitForKernel.
 *
 * Copyright (c) 2007 moonlight
 *
 */
#ifndef __PSPINIT_H__
#define __PSPINIT_H__

#define PSP_INIT_CHUNK_VSHPARAM		0
#define PSP_INIT_CHUNK_DISCIMAGE	3

typedef struct SceInitVSHParam
{
	SceSize size; // 0
	int param_size; // 4
	int unk1; // 8
	int unk2; // C
	int unk5; // 0x10
	int exitcheck; // 0x14
	int code; // 0x18
	int unk6; // 0x1C
} SceInitVSHParam;

typedef int (* SceInitCallback)(void *, int, int);

typedef struct SceInitCallbackData
{
	union
	{
		SceInitCallback callback; // 0

		struct 
		{
			u16 pos;
			u16 high;
		} Position;
	};

	int unk1; // 4	
} SceInitCallbackData;

enum PSPBootFrom
{
	PSP_BOOT_DEFAULT = 0, /* flash0? */
	PSP_BOOT_DISC = 0x20,
	PSP_BOOT_BUFFER = 0x30,
	PSP_BOOT_MS = 0x40,
	PSP_BOOT_FLASH3 = 0x80,
};

enum PSPInitApitype
{
	PSP_INIT_APITYPE_LOADEXEC_USER1 = 0x110,
	PSP_INIT_APITYPE_LOADEXEC_USER2 = 0x111,
	PSP_INIT_APITYPE_LOADEXEC_USER3 = 0x112,
	PSP_INIT_APITYPE_LOADEXEC_USER4 = 0x113,
	PSP_INIT_APITYPE_DISC = 0x120,
	PSP_INIT_APITYPE_DISC_UPDATER = 0x121,
	PSP_INIT_APITYPE_DISC_DEBUG = 0x122,
	PSP_INIT_APITYPE_DISC_IMAGE = 0x123,
	PSP_INIT_APITYPE_USBWLAN = 0x130,
	PSP_INIT_APITYPE_USBWLAN_DEBUG = 0x131,
	PSP_INIT_APITYPE_MS1 = 0x140,
	PSP_INIT_APITYPE_MS2 = 0x141,
	PSP_INIT_APITYPE_MS3 = 0x142,
	PSP_INIT_APITYPE_MS4 = 0x143,
	PSP_INIT_APITYPE_MS5 = 0x144,
	PSP_INIT_APITYPE_EXIT_VSH_KERNEL = 0x200,
	PSP_INIT_APITYPE_EXIT_GAME = 0x210, 
	PSP_INIT_APITYPE_EXIT_VSH_VSH = 0x220, 
	PSP_INIT_APITYPE_REBOOT_KERNEL = 0x300,
};

enum PSPKeyConfig
{
	PSP_INIT_KEYCONFIG_VSH = 0x100,
	PSP_INIT_KEYCONFIG_UPDATER = 0x110,
	PSP_INIT_KEYCONFIG_GAME = 0x200,
	PSP_INIT_KEYCONFIG_POPS = 0x300,
	PSP_INIT_KEYCONFIG_APP = 0x400,
};

/**
 * Gets the api type 
 *
 * @return the api type in which the system has booted
*/
int sceKernelInitApitype();

/**
 * Gets the filename of the executable to be launched after all modules of the api.
 *
 * @return filename of executable or NULL if no executable found.
*/
char *sceKernelInitFileName();

/**
 *
 * Gets the device in which the application was launched.
 *
 * @return the device code, one of PSPBootFrom values.
*/
int sceKernelBootFrom();

/**
 * Get the key configuration in which the system has booted.
 *
 * @return the key configuration code, one of PSPKeyConfig values 
*/
int InitForKernel_7233B5BC();
#define sceKernelInitKeyConfig InitForKernel_7233B5BC

int sceKernelGetChunk(int chunkid);

#endif

