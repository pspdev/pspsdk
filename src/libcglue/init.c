/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * init.c - The global init/deinit code for our crt0.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/param.h>

void __init_cwd(char *argv_0);
void __timezone_update();
void __fdman_init();
void __init_mutex();

#ifdef F___libcglue_init
/* Note: This function is being called from crt0.c/crt0_prx.c.
* It is a weak function because can be override by user program, 
* saving a lot of space in your binary, however you will loose
  all the basic libc operation
*/
__attribute__((weak))
void __libcglue_init(int argc, char *argv[])
{
    (void) argc;

    /* Initialize mutex used in malloc and fdman */
    __init_mutex();

	/* Initialize filedescriptor management */
	__fdman_init();

	/* Initialize cwd from this program's path */
	__init_cwd(argv[0]);

	/* Initialize timezone */
	__timezone_update();
}
#endif