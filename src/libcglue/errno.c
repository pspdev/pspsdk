/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * errno.c - The global init/deinit code for our crt0.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

#include <stdio.h>
#include <errno.h>

#ifdef F___set_errno
int __set_errno(int code)
{
	if ((code & 0x80010000) == 0x80010000) {
		errno = code & 0xFFFF;
		return -1;
	}
	return code;
}
#endif