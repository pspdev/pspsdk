/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * cxx.cpp - Simple C++ memory allocation operators.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: cxx.cpp 339 2005-06-27 02:24:25Z warren $
 */
#include <stdlib.h>
#include <malloc.h>

__attribute__((weak))
void operator delete(void *ptr) 
{
	if (ptr)
	{
		free(ptr);
	}
}

__attribute__((weak))
void* operator new(size_t len) 
{
	return malloc(len);
}

__attribute__((weak))
void operator delete[](void *ptr) 
{
	::operator delete(ptr);
}

__attribute__((weak))
void* operator new[](size_t len) 
{
	return ::operator new(len);
}

extern "C" 
__attribute__((weak))
void __cxa_pure_virtual() 
{
	/* perror("Pure virtual method called"); */
	abort();
}
