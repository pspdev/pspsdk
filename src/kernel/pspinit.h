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

#include <psptypes.h>
#include <pspkerneltypes.h>
#include <psploadexec_kernel.h>

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
 * This structure represents an Init control block. It holds information about the
 * currently booted module by Init.
 */
typedef struct SceInit {
    /** The API type of the currently loaded module. One of ::SceInitApiType. */
    s32 apitype; //0
    /** The address of a memory protection block of type ::SCE_PROTECT_INFO_TYPE_FILE_NAME. */
    void *file_mod_addr; //4
    /** The address of a memory protection block of type ::SCE_PROTECT_INFO_TYPE_DISC_IMAGE. */
    void *disc_mod_addr; //8
    /** VSH parameters. Used to reboot the kernel. */
    SceKernelLoadExecVSHParam vsh_param; //12
    /** Unknown. */
    s32 unk60;
    /** Unknown. */
    s32 unk64;
    /** Unknown. */
    s32 unk68;
    /** Unknown. */
    s32 unk72;
    /** Unknown. */
    s32 unk76;
    /** Unknown. */
    s32 unk80;
    /** Unknown. */
    s32 unk84;
    /** Unknown. */
    s32 unk88;
    /** The application type of the currently loaded module. One of ::SceApplicationType. */
    u32 application_type; //92
    /** The number of power locks used by Init. */
    s32 num_power_locks; //96
    /** The address of a memory protection block of type ::SCE_PROTECT_INFO_TYPE_PARAM_SFO. */
    void *param_sfo_base; //100
    /** The size of of the memory block pointed to by ::paramSfoBase. */
    SceSize param_sfo_size; //104
    /** Unknown. */
    s32 lpt_summary; //108
    /** Pointer to boot callbacks of modules. */
    SceBootCallback *boot_callbacks1; //112
    /** The current boot callback 1 slot used to hold the registered boot callback. */
    SceBootCallback *cur_boot_callback1; //116
    /** Pointer to boot callbacks of modules. */
    SceBootCallback *boot_callbacks2; //120
    /** The current boot callback 2 slot used to hold the registered boot callback. */
    SceBootCallback *cur_boot_callback2; //124
} SceInit;

/**
 * Gets the api type.
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
 * @return the key configuration code, one of `PSPKeyConfig` values
*/
int sceKernelApplicationType();

#define sceKernelInitKeyConfig sceKernelApplicationType

#if defined(_PSP_FW_VERSION) && _PSP_FW_VERSION >= 660

/**
 * Retrieve Init's internal control block. This control block manages execution details of an
 * executable, like its API type, its boot medium and its application type.
 *
 * @return A pointer to Init's internal control block.
 */
SceInit *sceKernelQueryInitCB(void);

#endif /* defined(_PSP_FW_VERSION) && _PSP_FW_VERSION >= 660 */

#endif /* __PSPINIT_H__ */

