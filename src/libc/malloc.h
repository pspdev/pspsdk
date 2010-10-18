/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * malloc.h
 *
 * Copyright (c) 2002-2004 PS2DEV
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: malloc.h 1095 2005-09-27 21:02:16Z jim $
 */

#ifndef _MALLOC_H
#define _MALLOC_H

#include <pspkernel.h>
#include <stddef.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* stdlib/malloc */
void *	malloc(size_t size);
void *	realloc(void *ptr, size_t size);
void *	calloc(size_t n, size_t size);
void *	memalign(size_t align, size_t size);
void	free(void * ptr);

/* Memory walkers. Used for debugging/profiling purposes. */
void * __mem_walk_begin(void);
void __mem_walk_read(void * token, u32 * size, void ** ptr, int * valid);
void * __mem_walk_inc(void * token);
int __mem_walk_end(void * token);

/* Example of use:

  void * i;
  
  for (i = __mem_walk_begin(); !__mem_walk_end(i); i = __mem_walk_inc(i)) {
      u32 block_size;
      void * block_ptr;
      int valid;

      __mem_walk_read(i, &block_size, &block_ptr, &valid);
      if (!valid) {
          fprintf(stderr, "Block at token %p is invalid.\n", i);
	  break;
      }
      printf("Block at token %p points at a memory block of %i bytes at %p.\n", i, block_size, block_ptr);
  }
  
  note that 'valid' will be always true if DEBUG_ALLOC was not defined when alloc.c got compiled.

*/

#ifdef __cplusplus
}
#endif

#endif	// _MALLOC_H

