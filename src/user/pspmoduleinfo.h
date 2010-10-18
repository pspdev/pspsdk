/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmoduleinfo.h - Definitions for the .rodata.sceModuleInfo ELF section.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: pspmoduleinfo.h 2434 2008-10-15 17:37:25Z iwn $
 */
#ifndef PSPMODULEINFO_H
#define PSPMODULEINFO_H

/* Note: Some of the structures and definitions in this file were extrapolated from
   symbolic debugging information found in the Japanese version of Puzzle Bobble. */

/* Module info structure.  Used to declare a module (library or executable).  This structure
   is required in all PSP executables. */
typedef struct _scemoduleinfo {
	unsigned short		modattribute;
	unsigned char		modversion[2];
	char			modname[27];
	char			terminal;
	void *			gp_value;
	void *			ent_top;
	void *			ent_end;
	void *			stub_top;
	void *			stub_end;
} _sceModuleInfo;

typedef const _sceModuleInfo SceModuleInfo;

extern char _gp[];

enum PspModuleInfoAttr
{
	PSP_MODULE_USER			= 0,
	PSP_MODULE_NO_STOP		= 0x0001,
	PSP_MODULE_SINGLE_LOAD	= 0x0002,
	PSP_MODULE_SINGLE_START	= 0x0004,
	PSP_MODULE_KERNEL		= 0x1000,
};

#ifdef __cplusplus

/* Declare a module.  This must be specified in the source of a library or executable. */
#define PSP_MODULE_INFO(name, attributes, major_version, minor_version) \
	__asm__ (                                                       \
	"    .set push\n"                                               \
	"    .section .lib.ent.top, \"a\", @progbits\n"                 \
	"    .align 2\n"                                                \
	"    .word 0\n"                                                 \
	"__lib_ent_top:\n"                                              \
	"    .section .lib.ent.btm, \"a\", @progbits\n"                 \
	"    .align 2\n"                                                \
	"__lib_ent_bottom:\n"                                           \
	"    .word 0\n"                                                 \
	"    .section .lib.stub.top, \"a\", @progbits\n"                \
	"    .align 2\n"                                                \
	"    .word 0\n"                                                 \
	"__lib_stub_top:\n"                                             \
	"    .section .lib.stub.btm, \"a\", @progbits\n"                \
	"    .align 2\n"                                                \
	"__lib_stub_bottom:\n"                                          \
	"    .word 0\n"                                                 \
	"    .set pop\n"                                                \
	"    .text\n"													\
	);                                                              \
	extern char __lib_ent_top[], __lib_ent_bottom[];                \
	extern char __lib_stub_top[], __lib_stub_bottom[];              \
	extern SceModuleInfo module_info                                \
		__attribute__((section(".rodata.sceModuleInfo"),        \
			       aligned(16), unused)) = {                \
	  attributes, { minor_version, major_version }, #name, 0, _gp,  \
	  __lib_ent_top, __lib_ent_bottom,                              \
	  __lib_stub_top, __lib_stub_bottom                             \
	}
#else
/* Declare a module.  This must be specified in the source of a library or executable. */
#define PSP_MODULE_INFO(name, attributes, major_version, minor_version) \
	__asm__ (                                                       \
	"    .set push\n"                                               \
	"    .section .lib.ent.top, \"a\", @progbits\n"                 \
	"    .align 2\n"                                                \
	"    .word 0\n"                                                 \
	"__lib_ent_top:\n"                                              \
	"    .section .lib.ent.btm, \"a\", @progbits\n"                 \
	"    .align 2\n"                                                \
	"__lib_ent_bottom:\n"                                           \
	"    .word 0\n"                                                 \
	"    .section .lib.stub.top, \"a\", @progbits\n"                \
	"    .align 2\n"                                                \
	"    .word 0\n"                                                 \
	"__lib_stub_top:\n"                                             \
	"    .section .lib.stub.btm, \"a\", @progbits\n"                \
	"    .align 2\n"                                                \
	"__lib_stub_bottom:\n"                                          \
	"    .word 0\n"                                                 \
	"    .set pop\n"                                                \
	"    .text\n"													\
	);                                                              \
	extern char __lib_ent_top[], __lib_ent_bottom[];                \
	extern char __lib_stub_top[], __lib_stub_bottom[];              \
	SceModuleInfo module_info                                       \
		__attribute__((section(".rodata.sceModuleInfo"),        \
			       aligned(16), unused)) = {                \
	  attributes, { minor_version, major_version }, name, 0, _gp,  \
	  __lib_ent_top, __lib_ent_bottom,                              \
	  __lib_stub_top, __lib_stub_bottom                             \
	}
#endif

/* Define the main thread's initial priority. */
#define PSP_MAIN_THREAD_PRIORITY(priority) \
	unsigned int sce_newlib_priority = (priority)
/* Define the main thread's stack size (in KB). */
#define PSP_MAIN_THREAD_STACK_SIZE_KB(size_kb) \
	unsigned int sce_newlib_stack_kb_size = (size_kb)
/* Define the main thread's attributes. */
#define PSP_MAIN_THREAD_ATTR(attr) \
	unsigned int sce_newlib_attribute = (attr)
#define PSP_MAIN_THREAD_ATTRIBUTE PSP_MAIN_THREAD_ATTR

/* Define all main thread parameters. */
#define PSP_MAIN_THREAD_PARAMS(priority, size_kb, attribute) \
	PSP_MAIN_THREAD_PRIORITY(priority); \
	PSP_MAIN_THREAD_STACK_SIZE_KB(size_kb); \
	PSP_MAIN_THREAD_ATTR(attribute)

/* If declared, the runtime code won't create a main thread for the program. */
#define PSP_NO_CREATE_MAIN_THREAD() \
	int sce_newlib_nocreate_thread_in_start = 1

/* Declare the size of the heap (in KB) that the program wants to allocate from. */
#define PSP_HEAP_SIZE_KB(size_kb) \
	int sce_newlib_heap_kb_size = (size_kb)

/* Declare to allocate maximum heap area */
#define PSP_HEAP_SIZE_MAX() \
	PSP_HEAP_SIZE_KB(-1)

/* Declare the name of the main thread */
#define PSP_MAIN_THREAD_NAME(s) const char* sce_newlib_main_thread_name = (s)

#endif /* PSPMODULEINFO_H */
