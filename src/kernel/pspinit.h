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

#include <psploadexec_kernel.h>

/**
 * The possible boot medium types for an executable.
 */
typedef enum PSPBootFrom {
    /** The executable was booted via Flash 0 (1, 2). */
    PSP_BOOT_FLASH     = 0,
    /** The executable was booted via a Disc medium. */
    PSP_BOOT_DISC      = 0x20,
    /** The executable was booted via a Game-sharing medium. */
    PSP_BOOT_USBWLAN   = 0x30,
    /** The executable was booted via the Memory Stick medium. */
    PSP_BOOT_MS        = 0x40,
    /** The executable was booted via an unknown medium. */
    PSP_BOOT_EF        = 0x50,
    /** The executable was booted via Flash 3.*/
    PSP_BOOT_FLASH3    = 0x80,
} PSPBootFrom;
typedef PSPBootFrom SceBootMediumType;

/**
 * API types of an executable.
 *
 * `sceKernelLoadModuleWithApitype`
 */
typedef enum PSPInitApitype {
    PSP_INIT_APITYPE_KERNEL = 0, /* ModuleMgrForKernel */
    PSP_INIT_APITYPE_BUFFER_KERNEL = 0x02,
    PSP_INIT_APITYPE_KERNEL_BLOCK = 0x03,
    PSP_INIT_APITYPE_USER = 0x10, /* ModuleMgrForUser */
    PSP_INIT_APITYPE_DNAS = 0x13,
    PSP_INIT_APITYPE_NPDRM = 0x14,
    PSP_INIT_APITYPE_VSH = 0x20,
    PSP_INIT_APITYPE_BUFFER_VSH = 0x21,
    PSP_INIT_APITYPE_BUFFER_USBWLAN = 0x30,
    PSP_INIT_APITYPE_BUFFER_MS = 0x42,
    PSP_INIT_APITYPE_BUFFER_APP = 0x43,
    PSP_INIT_APITYPE_BUFFER_BOOT_INIT_BTCNF = 0x51,
    PSP_INIT_APITYPE_BUFFER_BOOT_INIT_CONFIG = 0x52,
    PSP_INIT_APITYPE_BUFFER_DECI = 0x70,

    /** GAME EBOOT. */
    PSP_INIT_APITYPE_GAME_EBOOT = 0x110,
    /** GAME BOOT. */
    PSP_INIT_APITYPE_GAME_BOOT = 0x111,
    /** Emulated EBOOT Memory-Stick. */
    PSP_INIT_APITYPE_EMU_EBOOT_MS = 0x112,
    /** Emulated BOOT Memory-Stick. */
    PSP_INIT_APITYPE_EMU_BOOT_MS = 0x113,
    /** Emulated EBOOT EF. */
    PSP_INIT_APITYPE_EMU_EBOOT_EF = 0x114,
    /** Emulated BOOT EF. */
    PSP_INIT_APITYPE_EMU_BOOT_EF = 0x115,
    /** NP-DRM Memory-Stick. */
    PSP_INIT_APITYPE_NPDRM_MS = 0x116, /* Distributed programs and data through the Playstation Store. */
    /** Unknown. */
    PSP_INIT_APITYPE_UNK117 = 0x117,
    /** NP-DRM EF. */
    PSP_INIT_APITYPE_NPDRM_EF = 0x118, /* NP-DRM: PlayStation Network Platform Digital Rights Management */
    /** Unknown. */
    PSP_INIT_APITYPE_UNK119 = 0x119,
    /** Executable on a disc. */
    PSP_INIT_APITYPE_UMD = 0x120,
    /** Updater executable on a disc. */
    PSP_INIT_APITYPE_UMD_UPDATER = 0x121,
    /** Disc debugger. */
    PSP_INIT_APITYPE_UMD_DEBUG = 0x122,
    /** NP-9660 game on Memory Stick. */
    PSP_INIT_APITYPE_UMD_EMU_MS1 = 0x123,
    /** NP-9660 game with update/DLC (`PBOOT.PBP`) on Memory Stick. */
    PSP_INIT_APITYPE_UMD_EMU_MS2 = 0x124,
    /** NP-9660 game on internal memory (`ef0:`). */
    PSP_INIT_APITYPE_UMD_EMU_EF1 = 0x125,
    /** NP-9660 game with update/DLC (`PBOOT.PBP`) on internal memory (`ef0:`). */
    PSP_INIT_APITYPE_UMD_EMU_EF2 = 0x126,
    /** Game-sharing executable. */
    PSP_INIT_APITYPE_USBWLAN = 0x130,
    /** Unknown. */
    PSP_INIT_APITYPE_USBWLAN_DEBUG = 0x131,
    /** Updater executable on a PBP in the Memory Stick. */
    PSP_INIT_APITYPE_MS1 = 0x140,
    /** PSP executable on a PBP in the Memory Stick. */
    PSP_INIT_APITYPE_MS2 = 0x141,
    /** Unknown. */
    PSP_INIT_APITYPE_MS3 = 0x142,
    /** Applications (i.e. Comic Reader) executable on a PBP in the Memory Stick. */
    PSP_INIT_APITYPE_MS4 = 0x143,
    /** Playstation One executable on a PBP in the Memory Stick. */
    PSP_INIT_APITYPE_MS5 = 0x144,
    /** Unknown. Licensed games? */
    PSP_INIT_APITYPE_MS6 = 0x145,
    /** Updater executable on a PBP in the internal memory (`ef0:`). */
    PSP_INIT_APITYPE_EF1 = 0x151,
    /** PSP executable on a PBP in the internal memory (`ef0:`). */
    PSP_INIT_APITYPE_EF2 = 0x152,
    /** Unknown. Probably the same as MS3 but loading form `ef0`. */
    PSP_INIT_APITYPE_EF3 = 0x153,
    /** Applications (i.e. Comic Reader) executable on a PBP in the internal memory (`ef0:`). */
    PSP_INIT_APITYPE_EF4 = 0x154,
    /** Playstation One executable on a PBP in the internal memory (`ef0:`). */
    PSP_INIT_APITYPE_EF5 = 0x155,
    /** Unknown. Probably the same as MS6 but loading form `ef0`. */
    PSP_INIT_APITYPE_EF6 = 0x156,
    /** Game/APP with update/DLC on a disc. */
    PSP_INIT_APITYPE_UMD2 = 0x160,
    /** Unknown. */
    PSP_INIT_APITYPE_UNK161 = 0x161,
    /** MerlinDRM Applications on Memory Stick */
    PSP_INIT_APITYPE_MLNAPP_MS = 0x170,
    /** MerlinDRM Applications on internal memory (`ef0:`). */
    PSP_INIT_APITYPE_MLNAPP_EF = 0x171,
    /** Exit VSH Kernel. */
    PSP_INIT_APITYPE_VSH_KERNEL = 0x200,
    /** Exit Game. */
    PSP_INIT_APITYPE_VSH1 = 0x210,
    /** Exit VSH. */
    PSP_INIT_APITYPE_VSH2 = 0x220,
    /** Kernel reboot. */
    PSP_INIT_APITYPE_KERNEL_REBOOT = 0x300,
    /** Debug. Doesn't start reboot. */
    PSP_INIT_APITYPE_DEBUG = 0x420,  /* doesn't start reboot */

    // Alias
    PSP_INIT_APITYPE_DISC = PSP_INIT_APITYPE_UMD,
    PSP_INIT_APITYPE_DISC2 = PSP_INIT_APITYPE_UMD2,
    PSP_INIT_APITYPE_DISC_UPDATER = PSP_INIT_APITYPE_UMD_UPDATER,
    PSP_INIT_APITYPE_DISC_DEBUG = PSP_INIT_APITYPE_UMD_DEBUG,
    PSP_INIT_APITYPE_DISC_EMU_MS1 = PSP_INIT_APITYPE_UMD_EMU_MS1,
    PSP_INIT_APITYPE_DISC_EMU_MS2 = PSP_INIT_APITYPE_UMD_EMU_MS2,
    PSP_INIT_APITYPE_DISC_EMU_EF1 = PSP_INIT_APITYPE_UMD_EMU_EF1,
    PSP_INIT_APITYPE_DISC_EMU_EF2 = PSP_INIT_APITYPE_UMD_EMU_EF2,
    PSP_INIT_APITYPE_MS_UPDATER = PSP_INIT_APITYPE_MS1,
    PSP_INIT_APITYPE_MS_GAME = PSP_INIT_APITYPE_MS2,
    PSP_INIT_APITYPE_MS_APP = PSP_INIT_APITYPE_MS4,
    PSP_INIT_APITYPE_MS_PS1 = PSP_INIT_APITYPE_MS5,
    PSP_INIT_APITYPE_EF_UPDATER = PSP_INIT_APITYPE_EF1,
    PSP_INIT_APITYPE_EF_GAME = PSP_INIT_APITYPE_EF2,
    PSP_INIT_APITYPE_EF_APP = PSP_INIT_APITYPE_EF4,
    PSP_INIT_APITYPE_EF_PS1 = PSP_INIT_APITYPE_EF5,
    PSP_INIT_APITYPE_VSH_EXITGAME = PSP_INIT_APITYPE_VSH1, /* ExitGame */
    PSP_INIT_APITYPE_VSH_EXITVSH = PSP_INIT_APITYPE_VSH2, /* ExitVSH */
} PSPInitApitype;

/**
 * Application types of an executable.
 */
typedef enum PSPKeyConfig {
    /** The application is a VSH application (i.e. VSH modules). */
    PSP_INIT_KEYCONFIG_VSH		= 0x100,
    /** The application is an updater. */
    PSP_INIT_KEYCONFIG_UPDATER	= 0x110,
    /** The application is a PSP game. */
    PSP_INIT_KEYCONFIG_GAME	= 0x200,
    /** The application is a Playstation One game. */
    PSP_INIT_KEYCONFIG_POPS	= 0x300,
    /** The application is a PSP application (i.e. Skype). */
    PSP_INIT_KEYCONFIG_APP		= 0x400,
} PSPKeyConfig;
typedef PSPKeyConfig SceApplicationType;

/**
 * This structure represents a boot callback belonging to a module.
 */
typedef struct SceBootCallback {
	/** The boot callback function. */
	void *boot_callback_func;
	/** Global pointer value of the module. */
	u32 gp;
} SceBootCallback;

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
    struct SceKernelLoadExecVSHParam vsh_param; //12
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
int sceKernelApplicationType();
#define sceKernelInitKeyConfig sceKernelApplicationType

/**
 * Retrieve Init's internal control block. This control block manages execution details of an
 * executable, like its API type, its boot medium and its application type.
 *
 * @return A pointer to Init's internal control block.
 */
SceInit *sceKernelQueryInitCB(void);

#endif

