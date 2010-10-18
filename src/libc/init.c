/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * init.c - The global init/deinit code for our crt0.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: init.c 540 2005-07-08 19:35:10Z warren $
 */
void _pspsdk_alloc_init();
void _pspsdk_alloc_deinit();
void _pspsdk_stdio_init();
void _pspsdk_stdio_deinit();
void _pspsdk_stdlib_init();
void _pspsdk_stdlib_deinit();

__attribute__((weak, constructor))
void _pspsdk_libc_init()
{
    _pspsdk_alloc_init();
    _pspsdk_stdio_init();
    _pspsdk_stdlib_init();
}

__attribute__((weak, destructor))
void _pspsdk_libc_deinit()
{
    _pspsdk_stdlib_deinit();
    _pspsdk_stdio_deinit();
    _pspsdk_alloc_deinit();
}
