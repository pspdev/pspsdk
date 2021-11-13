/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * select.c - Socket wrappers to provide similar functions to normal unix
 *
 * Copyright (c) 2006 Rafael Cabezas <rafpsp@gmail.com>
 *
 * - 20070701 Alper Akcan "anhanguera" <distchx@yahoo.com>
 *            select EBADF fix
 * 
 */
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>
#include <psptypes.h>
#include <pspthreadman.h>
#include <pspnet_inet.h>

#include "fdman.h"

#define SELECT_POLLING_DELAY_IN_us	100
#define SCE_FD_SET(n, p) \
	((p)->fds_bits[((n) & 0xFF) /_NFDBITS] |= (1 << ((n) % _NFDBITS)))

#ifdef F_select
static int __poll_select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds)
{
	int fd, count;
	fd_set ready_readfds, ready_writefds, ready_exceptfds;
	fd_set scereadfds, scewritefds;
	SceKernelMppInfo info;
	struct timeval scetv;

	FD_ZERO(&ready_readfds);
	FD_ZERO(&ready_writefds);
	FD_ZERO(&ready_exceptfds);

	info.size = sizeof(info);
	scetv.tv_sec = 0;
	scetv.tv_usec = 0;
	count = 0;

	for (fd = 0; fd < n; fd++)
	{
		if (__descriptormap[fd] != NULL) {
			switch(__descriptormap[fd]->type)
			{
				case __DESCRIPTOR_TYPE_PIPE:
					if (readfds && FD_ISSET(fd, readfds)) {
						if (sceKernelReferMsgPipeStatus(__descriptormap[fd]->descriptor, &info) == 0) {
							if (info.bufSize != info.freeSize) {
								FD_SET(fd, &ready_readfds);
								count++;
							}
						}
						else {
							FD_SET(fd, &ready_exceptfds);
							count++;
						}
					}
					if (writefds && FD_ISSET(fd, writefds)) {
						if (sceKernelReferMsgPipeStatus(__descriptormap[fd]->descriptor, &info) == 0) {
							if (info.freeSize > 0) {
								FD_SET(fd, &ready_writefds);
								count++;
							}
						}
						else {
							FD_SET(fd, &ready_exceptfds);
							count++;
						}
					}
					break;
				case __DESCRIPTOR_TYPE_FILE:
					if (readfds && FD_ISSET(fd, readfds)) {
						if (readfds && FD_ISSET(fd, readfds)) {
							/** Just set it for now */
							FD_SET(fd, &ready_readfds);
							count++;
						}
					} 
					break;
				case __DESCRIPTOR_TYPE_SOCKET:
					if (readfds && FD_ISSET(fd, readfds)) {
						int sce_ret, sce_fd;
						sce_fd = __descriptormap[fd]->descriptor;
						FD_ZERO(&scereadfds);
						SCE_FD_SET(sce_fd, &scereadfds);
						errno = 0;
						sce_ret = sceNetInetSelect (sce_fd+1, &scereadfds, NULL, NULL, &scetv);
						if (sce_ret>0) {
							FD_SET(fd, &ready_readfds);
							count++;
						}
						else if (sce_ret == -1) {
							errno = sceNetInetGetErrno();
							if (exceptfds && FD_ISSET(fd, exceptfds)) {
								FD_SET(fd, &ready_exceptfds);
								count++;
							} else {
								count = -1;
							}
						}
					}
					if (writefds && FD_ISSET(fd, writefds)) {
						int sce_ret;
						FD_ZERO(&scewritefds);
						SCE_FD_SET(__descriptormap[fd]->descriptor, &scewritefds);
						sce_ret = sceNetInetSelect (__descriptormap[fd]->descriptor+1, NULL, &scewritefds, NULL, &scetv);
						if (sce_ret>0) {
							FD_SET(fd, &ready_writefds);
							count++;
						}
						else if (sce_ret == -1) {
							if (exceptfds && FD_ISSET(fd, exceptfds)) {
								FD_SET(fd, &ready_exceptfds);
								count++;
							} 
							else {
								count = -1;
							}
						}
					}
					break;
			}
		} else {
			/* anhanguera - 20070701
			 *
			 * here we know that, system has no idea about 'fd'. if caller requested
			 * information about 'fd', return '-1' and set errno to 'EBADF'. we should
			 * increse the count and set exceptfd for fd, but it is safe to obey select
			 * manual.
			 *
			 * from manual;
			 * On error, -1 is returned, and errno is set appropriately; the sets and
			 * timeout become undefined, so do not rely on their contents after an error.
			 */
			if ((readfds && FD_ISSET(fd, readfds)) ||
			    (writefds && FD_ISSET(fd, writefds)) ||
			    (exceptfds && FD_ISSET(fd, exceptfds))) {
				errno = EBADF;
				return -1;
			}
		}
	}

	if (count > 0) {
		if (readfds)
			*readfds   = ready_readfds;
		if (writefds)
			*writefds  = ready_writefds;
		if (exceptfds)
			*exceptfds = ready_exceptfds;
	}

	return count;
}

int	select(int n, fd_set *readfds, fd_set *writefds,
		   fd_set *exceptfds, struct timeval *timeout)
{
	int count;
	clock_t start_time, time;
	
	start_time = clock();

	count = 0;
	
	if (timeout) {
		time = (timeout->tv_sec * CLOCKS_PER_SEC) + (timeout->tv_usec * (1*1000*1000/CLOCKS_PER_SEC));
	} 
	else {
		time = 0; 
	}
	
	for (;;) {
		count = __poll_select(n, readfds, writefds, exceptfds);
		/* If timeout == NULL, then don't timeout! */
		if ( (count > 0) || ((timeout != NULL) && ((clock() - start_time) >= time)) ) {
			break;
		}
		if (count < 0) {
			/* anhanguera - 20070701
			 * error, lets let the caller to handle error state
			 */
			break;
		}
		else {
			/* Nothing found, and not timed-out yet; let's yield for SELECT_POLLING_DELAY_IN_us, so we're not in a busy loop */
			sceKernelDelayThread(SELECT_POLLING_DELAY_IN_us);
		} 
	}
	
	return count;
}
#endif


