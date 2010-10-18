/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspexports.c - Define the default set of exports for an executable
 *
 * Copyright (c) 2005 James F. <tyranid@gmail.com>
 *
 * $Id: pspexports.c 1521 2005-12-04 20:32:16Z tyranid $
 * $HeadURL: svn://tyranid@svn.pspdev.org/psp/trunk/pspsdk/src/startup/pspexports.c $
 */
#include <pspmoduleexport.h>
#define NULL ((void *) 0)

void extern module_start;
void extern module_info;
static const unsigned int __syslib_exports[4] __attribute__((section(".rodata.sceResident"))) = {
	0xD632ACDB,
	0xF01D73A7,
	(unsigned int) &module_start,
	(unsigned int) &module_info,
};

const struct _PspLibraryEntry __library_exports[1] __attribute__((section(".lib.ent"), used)) = {
	{ NULL, 0x0000, 0x8000, 4, 1, 1, &__syslib_exports },
};
