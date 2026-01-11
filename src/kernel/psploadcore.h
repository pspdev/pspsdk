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

#define SCE_KERNEL_MAX_MODULE_SEGMENT (4)

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

typedef struct {
	char *name;
	void *buf;
	int size;
	int unk_12;
	int attr;
	int unk_20;
	int argSize;
	int argPartId;
} SceLoadCoreBootModuleInfo;

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

typedef struct SceLoadCoreExecFileInfo {
	/** Unknown. */
	u32 unk0;
	/** The mode attribute of the executable file. One of ::SceExecFileModeAttr. */
	u32 mode_attr; //4
	/** The API type. */
	u32 api_type; //8
	/** Unknown. */
	u32 unk12;
	/** The size of the executable, including the ~PSP header. */
	SceSize exec_size; //16
	/** The maximum size needed for the decompression. */
	SceSize max_alloc_size; //20
	/** The memory ID of the decompression buffer. */
	SceUID decompression_mem_id; //24
	/** Pointer to the compressed module data. */
	void *file_base; //28
	/** Indicates the ELF type of the executable. One of ::SceExecFileElfType. */
	u32 elf_type; //32
	/** The start address of the TEXT segment of the executable in memory. */
	void *top_addr; //36
	/**
	 * The entry address of the module. It is the offset from the start of the TEXT segment to the
	 * program's entry point.
	 */
	u32 entry_addr; //40
	/** Unknown. */
	u32 unk44;
	/**
	 * The size of the largest module segment. Should normally be "textSize", but technically can
	 * be any other segment.
	 */
	SceSize largest_seg_size; //48
	/** The size of the TEXT segment. */
	SceSize text_size; //52
	/** The size of the DATA segment. */
	SceSize data_size; //56
	/** The size of the BSS segment. */
	SceSize bss_size; //60
	/** The memory partition of the executable. */
	u32 partition_id; //64
	/**
	 * Indicates whether the executable is a kernel module or not. Set to 1 for kernel module,
	 * 0 for user module.
	 */
	u32 is_kernel_mod; //68
	/**
	 * Indicates whether the executable is decrypted or not. Set to 1 if it is successfully decrypted,
	 * 0 for encrypted.
	 */
	u32 is_decrypted; //72
	/** The offset from the start address of the TEXT segment to the SceModuleInfo section. */
	u32 module_info_offset; //76
	/** The pointer to the module's SceModuleInfo section. */
	SceModuleInfo *module_info; //80
	/** Indicates whether the module is compressed or not. Set to 1 if it is compressed, otherwise 0.*/
	u32 is_compressed; //84
	/** The module's attributes. One or more of ::SceModuleAttribute and ::SceModulePrivilegeLevel. */
	u16 mod_info_attribute; //88
	/** The attributes of the executable file. One of ::SceExecFileAttr. */
	u16 exec_attribute; //90
	/** The size of the decompressed module, including its headers. */
	SceSize dec_size; //92
	/** Indicates whether the module is decompressed or not. Set to 1 for decompressed, otherwise 0. */
	u32 is_decompressed; //96
	/**
	 * Indicates whether the module was signChecked or not. Set to 1 for signChecked, otherwise 0.
	 * A signed module has a "mangled" executable header, in other words, the "~PSP" signature can't
	 * be seen.
	 */
	u32 is_sign_checked; //100
	/** Unknown. */
	u32 unk104;
	/** The size of the GZIP compression overlap. */
	SceSize overlap_size; //108
	/** Pointer to the first resident library entry table of the module. */
	void *exports_info; //112
	/** The size of all resident library entry tables of the module. */
	SceSize exports_size; //116
	/** Pointer to the first stub library entry table of the module. */
	void *imports_info; //120
	/** The size of all stub library entry tables of the module. */
	SceSize imports_size; //124
	/** Pointer to the string table section. */
	void *strtab_offset; //128
	/** The number of segments in the executable. */
	u8 num_segments; //132
	/** Reserved. */
	u8 padding[3]; //133
	/** An array containing the start address of each segment. */
	u32 segment_addr[SCE_KERNEL_MAX_MODULE_SEGMENT]; //136
	/** An array containing the size of each segment. */
	u32 segment_size[SCE_KERNEL_MAX_MODULE_SEGMENT]; //152
	/** The ID of the ELF memory block containing the TEXT, DATA and BSS segment. */
	SceUID mem_block_id; //168
	/** An array containing the alignment information of each segment. */
	u32 segment_align[SCE_KERNEL_MAX_MODULE_SEGMENT]; //172
	/** The largest value of the segment_align array. */
	u32 max_seg_align; //188
} SceLoadCoreExecFileInfo;


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

/**
 * Check an executable file. This contains scanning its ELF header and ~PSP header (if it has one)
 * and filling the execInfo structure with basic information, like the ELF type, segment information,
 * the size of the executable. The file is also uncompressed, if it was compressed before.
 *
 * @param buf Pointer to the file's contents.
 * @param execInfo Pointer to the executionInfo belonging to that executable.
 *
 * @return 0 on success.
 */
int sceKernelCheckExecFile(void *buf, SceLoadCoreExecFileInfo *execInfo);

/**
 * Probe an executable file. This contains calculating the sizes for the three segments TEXT, DATA
 * and BSS, filling the execInfo structure with information about the location and sizes of the
 * resident/stub library entry tables.
 *
 * Furthermore, it is checked whether the executable has valid API type or not.
 *
 * @param buf Pointer to the file's contents.
 * @param execInfo Pointer to the executionInfo belonging to that executable.
 *
 * @return 0 on success.
 */
int sceKernelProbeExecutableObject(void *buf, SceLoadCoreExecFileInfo *execInfo);

/**
 * Receive a list of UIDs of loaded modules.
 *
 * @param mod_id_list Pointer to a SceUID array which will receive the UIDs of the loaded modules.
 * @param size Size of mod_id_list. Specifies the number of entries that can be stored into mod_id_list.
 * @param mod_count A pointer which will receive the total number of loaded modules.
 * @param user_mods_only Set to 1 to only receive UIDs from user mode modules. Set to 0 to receive UIDs from all loaded modules.
 *
 * @return 0 on success.
 */
int sceKernelGetModuleIdListForKernel(SceUID *mod_id_list, u32 size, u32 *mod_count, u32 user_mods_only);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSPLOADCORE_H */
