/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * fdman.h - File descriptor management.
 *
 * Copyright (c) 2006 Rafael Cabezas <rafpsp@gmail.com>
 */

#ifndef _FDMAN_H_

#include <sys/types.h>

#define _FDMAN_H_

#define __FILENO_MAX 1024

#define __IS_FD_VALID(FD) \
		( (FD >= 0) && (FD < __FILENO_MAX) && (__descriptormap[FD] != NULL) )

#define __IS_FD_OF_TYPE(FD, TYPE) \
		( (__IS_FD_VALID(FD)) && (__descriptormap[FD]->type == TYPE) )
		
typedef enum {
	__DESCRIPTOR_TYPE_FILE,
	__DESCRIPTOR_TYPE_FOLDER,
	__DESCRIPTOR_TYPE_PIPE,
	__DESCRIPTOR_TYPE_SOCKET,
	__DESCRIPTOR_TYPE_TTY
} __fdman_fd_types;

typedef struct {
	uint32_t descriptor;
	uint32_t flags;
	uint32_t ref_count;
	char *filename;
	uint8_t type;
} __descriptormap_type;
	
extern __descriptormap_type *__descriptormap[__FILENO_MAX];

void __fdman_init();
int  __fdman_get_new_descriptor();
int  __fdman_get_dup_descriptor(int fd);
void __fdman_release_descriptor(int fd);

#endif
