/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psploadcore.h - Interface to LoadCoreForKernel.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

#ifndef PSPLOADCORE_H
#define PSPLOADCORE_H

#include <pspkerneltypes.h>

/** @defgroup LoadCore Interface to the LoadCoreForKernel library.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup LoadCore Interface to the LoadCoreForKernel library. */
/**@{*/


/** Reboot preparation functions */
typedef s32 (*SceKernelRebootBeforeForKernel)(void *arg1, s32 arg2, s32 arg3, s32 arg4);
typedef s32 (*SceKernelRebootPhaseForKernel)(s32 arg1, void *arg2, s32 arg3, s32 arg4);

/** Module type attributes. */
enum SceModuleAttribute {
    /** No module attributes. */
    SCE_MODULE_ATTR_NONE             = 0x0000,
    /** Resident module - stays in memory. You cannot unload such a module. */
    SCE_MODULE_ATTR_CANT_STOP        = 0x0001,
    /**
     * Only one instance of the module (one version) can be loaded into the system. If you want to load another
     * version of that module, you have to delete the loaded version first.
     */
    SCE_MODULE_ATTR_EXCLUSIVE_LOAD   = 0x0002,
    /**
     * Only one instance of the module (one version) can be started. If you want to start another
     * version of that module, you have to stop the currently running version first.
     */
    SCE_MODULE_ATTR_EXCLUSIVE_START  = 0x0004,
};

/**
 * Module Privilege Levels - These levels define the permissions a
 * module can have.
 */
enum SceModulePrivilegeLevel {
    /** Lowest permission. */
    SCE_MODULE_USER                 = 0x0000,
    /** POPS/Demo. */
    SCE_MODULE_MS                   = 0x0200,
    /** Module Gamesharing. */
    SCE_MODULE_USB_WLAN             = 0x0400,
    /** Application module. */
    SCE_MODULE_APP                  = 0x0600,
    /** VSH module. */
    SCE_MODULE_VSH                  = 0x0800,
    /** Highest permission. */
    SCE_MODULE_KERNEL               = 0x1000,
    /** The module uses KIRK's memlmd resident library. */
    SCE_MODULE_KIRK_MEMLMD_LIB      = 0x2000,
    /** The module uses KIRK's semaphore resident library. */
    SCE_MODULE_KIRK_SEMAPHORE_LIB   = 0x4000,
};

/** Describes a loaded module in memory.  This structure could change in future firmware revisions. */
typedef struct SceModule {
	/** Pointer to the next registered module. Modules are connected via a linked list. */
	struct SceModule *next;
	/** The attributes of a module. One or more of ::SceModuleAttribute and ::SceModulePrivilegeLevel. */
	u16			attribute;
	/**
	 * The version of the module. Consists of a major and minor part. There can be several modules
	 * loaded with the same name and version.
	*/
	u8			version[2];
	/** The module's name. There can be several modules loaded with the same name. */
	char		modname[27];
	/** String terminator (always '\0'). */
	char		terminal;
	/**
	 * The status of the module. Contains information whether the module has been started, stopped,
	 * is a user module, etc.
	 */
	u16 		mod_state;
	char 		padding[2];
	/** A secondary ID for the module. */
	SceUID 		sec_id;
	/** The module's UID. */
	SceUID		modid;
	/** The thread ID of a user module. */
	SceUID 		user_mod_thid;
	/** The ID of the memory block belonging to the module. */
	SceUID 		mem_id;
	/** The ID of the TEXT segment's memory partition. */
	u32			mpid_text;
	/** The ID of the DATA segment's memory partition. */
	u32			mpid_data;
	/** Pointer to the first resident library entry table of the module. */
	void *		ent_top;
	/** The size of all resident library entry tables of the module. */
	SceSize		ent_size;
	/** Pointer to the first stub library entry table of the module. */
	void *		stub_top;
	/** The size of all stub library entry tables of the module. */
	SceSize		stub_size;
	/**
	 * A pointer to the (required) module's start entry function. This function is executed during
	 * the module's startup.
	 */
	SceKernelThreadEntry module_start;
	/**
	 * A pointer to the (required) module's stop entry function. This function is executed during
	 * the module's stopping phase.
	 */
	SceKernelThreadEntry module_stop;
	/**
	 * A pointer to a module's Bootstart entry function. This function is probably executed after
	 * a reboot.
	 */
	SceKernelThreadEntry module_bootstart;
	/**
	 * A pointer to a module's rebootBefore entry function. This function is probably executed
	 * before a reboot.
	 */
	SceKernelRebootBeforeForKernel module_reboot_before;
	/**
	 * A pointer to a module's rebootPhase entry function. This function is probably executed
	 * during a reboot.
	 */
	SceKernelRebootPhaseForKernel module_reboot_phase;
	/**
	 * The entry address of the module. It is the offset from the start of the TEXT segment to the
	 * program's entry point.
	 */
	u32		entry_addr;
	/** Contains the offset from the start of the TEXT segment of the program's GP register value. */
	u32		gp_value;
	/** The start address of the TEXT segment. */
	u32		text_addr;
	/** The size of the TEXT segment. */
	u32		text_size;
	/** The size of the DATA segment. */
	u32		data_size;
	/** The size of the BSS segment. */
	u32		bss_size;
	/** The number of segments the module consists of. */
	u8		nsegment;
	/** Reserved. */
	u8		padding2[3];
	/** An array containing the start address of each segment. */
	u32		segmentaddr[4];
	/** An array containing the size of each segment. */
	SceSize	segmentsize[4];
	/** An array containing the alignment information of each segment. */
	u32 	segmentalign[4];
	/** The priority of the module start thread. */
	s32 	module_start_thread_priority;
	/** The stack size of the module start thread. */
	SceSize module_start_thread_stacksize;
	/** The attributes of the module start thread. */
	SceUInt module_start_thread_attr;
	/** The priority of the module stop thread. */
	s32 	module_stop_thread_priority;
	/** The stack size of the module stop thread. */
	SceSize module_stop_thread_stacksize;
	/** The attributes of the module stop thread. */
	SceUInt module_stop_thread_attr;
	/** The priority of the module reboot before thread. */
	s32 	module_reboot_before_thread_priority;
	/** The stack size of the module reboot before thread. */
	SceSize module_reboot_before_thread_stacksize;
	/** The attributes of the module reboot before thread. */
	SceUInt module_reboot_before_thread_attr;
	/** The value of the coprocessor 0's count register when the module is created. */
	u32 	count_reg_val;
	/** The segment checksum of the module's segments. */
	u32 	segment_checksum;
	/** TEXT segment checksum of the module. */
	u32 	text_segment_checksum;
	/**
	 * Whether to compute the text segment checksum before starting the module (see prologue).
	 * If non-zero, the text segment checksum will be computed after the module's resident libraries
	 * have been registered, and its stub libraries have been linked.
	 */
	u32 	compute_text_segment_checksum;
} SceModule;

/** Defines a library and its exported functions and variables.  Use the len
    member to determine the real size of the table (size = len * 4). */
typedef struct SceLibraryEntryTable {
	/**The library's name. */
	const char *		libname;
	/** Library version. */
	unsigned char		version[2];
	/** Library attributes. */
	unsigned short		attribute;
	/** Length of this entry table in 32-bit WORDs. */
	unsigned char		len;
	/** The number of variables exported by the library. */
	unsigned char		vstubcount;
	/** The number of functions exported by the library. */
	unsigned short		stubcount;
	/** Pointer to the entry table; an array of NIDs followed by
	    pointers to functions and variables. */
	void *				entrytable;
} SceLibraryEntryTable;

/** Specifies a library and a set of imports from that library.  Use the len
    member to determine the real size of the table (size = len * 4). */
typedef struct SceLibraryStubTable {
	/* The name of the library we're importing from. */
	const char *		libname;
	/** Minimum required version of the library we want to import. */
	unsigned char		version[2];
	/* Import attributes. */
	unsigned short		attribute;
	/** Length of this stub table in 32-bit WORDs. */
	unsigned char		len;
	/** The number of variables imported from the library. */
	unsigned char		vstubcount;
	/** The number of functions imported from the library. */
	unsigned short		stubcount;
	/** Pointer to an array of NIDs. */
	unsigned int *		nidtable;
	/** Pointer to the imported function stubs. */
	void *				stubtable;
	/** Pointer to the imported variable stubs. */
	void *				vstubtable;
} SceLibraryStubTable;


/**
 * Find a module by it's name.
 *
 * @param modname - The name of the module.
 *
 * @return Pointer to the ::SceModule structure if found, otherwise NULL.
 */
SceModule * sceKernelFindModuleByName(const char *modname);

/**
 * Find a module from an address.
 *
 * @param addr - Address somewhere within the module.
 *
 * @return Pointer to the ::SceModule structure if found, otherwise NULL.
 */
SceModule * sceKernelFindModuleByAddress(unsigned int addr);

/**
 * Find a module by it's UID.
 *
 * @param modid - The UID of the module.
 *
 * @return Pointer to the ::SceModule structure if found, otherwise NULL.
 */
SceModule * sceKernelFindModuleByUID(SceUID modid);

/**
 * Return the count of loaded modules.
 *
 * @return The count of loaded modules.
 */
int sceKernelModuleCount(void);

/**
 * Invalidate the CPU's instruction cache.
 */
void sceKernelIcacheClearAll(void);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSPLOADCORE_H */
