/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psploadcore.h - Interface to LoadCoreForKernel.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: psploadcore.h 2433 2008-10-15 10:00:27Z iwn $
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
/*@{*/

/** Describes a module.  This structure could change in future firmware revisions. */
typedef struct SceModule {
	struct SceModule	*next;
	unsigned short		attribute;
	unsigned char		version[2];
	char				modname[27];
	char				terminal;
	unsigned int		unknown1;
	unsigned int		unknown2;
	SceUID				modid;
	unsigned int		unknown3[4];
	void *				ent_top;
	unsigned int		ent_size;
	void *				stub_top;
	unsigned int		stub_size;
	unsigned int		unknown4[4];
	unsigned int		entry_addr;
	unsigned int		gp_value;
	unsigned int		text_addr;
	unsigned int		text_size;
	unsigned int		data_size;
	unsigned int		bss_size;
	unsigned int		nsegment;
	unsigned int		segmentaddr[4];
	unsigned int		segmentsize[4];
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

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSPLOADCORE_H */
