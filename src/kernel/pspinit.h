/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspinit.h - Interface to InitForKernel.
 *
 * Copyright (c) 2007 moonlight
 *
 * $Id: pspinit.h 2433 2008-10-15 10:00:27Z iwn $
 */
#ifndef __PSPINIT_H__
#define __PSPINIT_H__

enum PSPBootFrom
{
	PSP_BOOT_FLASH = 0, /* ? */
	PSP_BOOT_DISC = 0x20,
	PSP_BOOT_MS = 0x40,
};

enum PSPInitApitype
{
	PSP_INIT_APITYPE_DISC = 0x120,
	PSP_INIT_APITYPE_DISC_UPDATER = 0x121,
	PSP_INIT_APITYPE_MS1 = 0x140,
	PSP_INIT_APITYPE_MS2 = 0x141,
	PSP_INIT_APITYPE_MS3 = 0x142,
	PSP_INIT_APITYPE_MS4 = 0x143,
	PSP_INIT_APITYPE_MS5 = 0x144,
	PSP_INIT_APITYPE_VSH1 = 0x210, /* ExitGame */
	PSP_INIT_APITYPE_VSH2 = 0x220, /* ExitVSH */
};

enum PSPKeyConfig
{
	PSP_INIT_KEYCONFIG_VSH = 0x100,
	PSP_INIT_KEYCONFIG_GAME = 0x200,
	PSP_INIT_KEYCONFIG_POPS = 0x300,
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

#endif

