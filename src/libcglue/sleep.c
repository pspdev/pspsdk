/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * sleep.c - Sleep functions needed by newlib.
 *
 * Copyright (c) 2021 Francisco Javier Trujillo Mata <fjtrujy@gmail.com>
 *
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

#include <pspthreadman.h>

/* Fuctions from errno.c */
int __set_errno(int code);

#ifdef F_nanosleep
/* note: we don't use rem as we have no signals */
int nanosleep(const struct timespec *req, struct timespec *rem)
{
	int res = 0;
    uint32_t usec = 1000000 * req->tv_sec + (req->tv_nsec / 1000);
    res = __set_errno(sceKernelDelayThread(usec));
	
    if( rem != NULL ) {
        rem->tv_sec = 0;
        rem->tv_nsec = 0;
    }

    return res;
}
#endif