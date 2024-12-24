/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pipe.c - Socket wrappers to provide similar functions to normal unix
 *
 * Copyright (c) 2006 Rafael Cabezas <rafpsp@gmail.com>
 *
 * - 20070630 Alper Akcan "anhanguera" <distchx@yahoo.com>
 *            [non]blocking read/write() fix
 *            illegal size fix for read/write()
 * 
 */
#include <stdio.h>
#include <errno.h>
#include <sys/syslimits.h>
#include <sys/types.h>

#include <psptypes.h>
#include <pspthreadman.h>
#include <pspmodulemgr.h>
#include <pspkerror.h>
#include "fdman.h"

int __set_errno(int code);

#ifdef F___pipe_peekmsgsize
/* Pipe functions */
/* Returns how many bytes are in the pipe -- waiting to be read */
size_t __pipe_peekmsgsize(int fd)
{
	SceKernelMppInfo info;
	info.size = sizeof(info);
	
	if (!__IS_FD_OF_TYPE(fd, __DESCRIPTOR_TYPE_PIPE)) {
		errno = EBADF;
		return -1;
	}
	
	if (sceKernelReferMsgPipeStatus(__descriptormap[fd]->descriptor, &info) == 0) {
		return (info.bufSize - info.freeSize);
	}
	else {
		return -1;
	}
}
#else
size_t __pipe_peekmsgsize(int fd);
#endif

#ifdef F_pipe
int pipe(int fildes[2])
{
	static int iIndex = 0;
	char name[32];
	iIndex++;

	sprintf(name, "__pipe_%02d", iIndex);

	SceUID uid = sceKernelCreateMsgPipe(name, PSP_MEMORY_PARTITION_USER, 0, (void *)PIPE_BUF, NULL);

	if (uid >= 0) {
		fildes[0] = __fdman_get_new_descriptor();
		if (fildes[0] != -1) {
			__descriptormap[fildes[0]]->descriptor = uid;
			__descriptormap[fildes[0]]->type = __DESCRIPTOR_TYPE_PIPE;
		} 
		else {
			sceKernelDeleteMsgPipe(uid);
			errno = EFAULT;
			return -1;
		}
		
		fildes[1] = __fdman_get_dup_descriptor(fildes[0]);
		if (fildes[1] != -1) {
			__descriptormap[fildes[1]]->descriptor = uid;
			return 0;
		} 
		else {
			sceKernelDeleteMsgPipe(uid);
			errno = EFAULT;
			return -1;
		}
		
	}
	else {
		errno = EFAULT;
		return -1;
	}
}
#endif

#ifdef F___pipe_close
__attribute__((weak))
int __pipe_close(int fd)
{
	int ret = 0;

	if (!__IS_FD_OF_TYPE(fd, __DESCRIPTOR_TYPE_PIPE)) {
		errno = EBADF;
		return -1;
	}
	
		
	if ( __descriptormap[fd]->ref_count == 1 ) {
			/**
			* Delete a message pipe
			*
			* @param uid - The UID of the pipe
			*
			* @return 0 on success, < 0 on error
			*/
			ret = sceKernelDeleteMsgPipe(__descriptormap[fd]->descriptor);
	}
	
	__fdman_release_descriptor(fd);
			
	if(ret < 0) {
		return __set_errno(ret);
	}
	
	return 0;
}
#endif

#ifdef F___pipe_nonblocking_read
__attribute__((weak))
int __pipe_nonblocking_read(int fd, void *buf, size_t len)
{
	int ret;
	int sceuid;
	int size;
	
	if (!__IS_FD_OF_TYPE(fd, __DESCRIPTOR_TYPE_PIPE)) {
		errno = EBADF;
		return -1;
	}
	
	sceuid = __descriptormap[fd]->descriptor;

	size = __pipe_peekmsgsize(fd);
	if (size > 0) {
		if (size < len) {
			len = size;
		}
	}
	else if (size == 0) {
		errno = EAGAIN;
		return -1;
	}
	else {
		errno = EBADF;
		return -1;
	}
 
	/**
	* Receive a message from a pipe
	*
	* @param uid - The UID of the pipe
	* @param message - Pointer to the message
	* @param size - Size of the message
	* @param unk1 - Unknown
	* @param unk2 - Unknown
	* @param timeout - Timeout for receive
	*
	* @return 0 on success, < 0 on error
	*/
	ret = sceKernelTryReceiveMsgPipe(sceuid, buf, len, 0, 0);
	
	if (ret == 0) {/* Success - Data */
		return len;
	}
	else if (ret == SCE_KERNEL_ERROR_MPP_EMPTY) {/* No data */
		errno = EAGAIN;
		return -1;
	}
	else {/* Error */
		return __set_errno(ret);
	}
}
#endif

#ifdef F___pipe_read
__attribute__((weak))
int __pipe_read(int fd, void *buf, size_t len)
{
	int ret;
	int sceuid;
	
	if (!__IS_FD_OF_TYPE(fd, __DESCRIPTOR_TYPE_PIPE)) {
		errno = EBADF;
		return -1;
	}
	
	sceuid = __descriptormap[fd]->descriptor;

#if 0
	int size;

	/* we should block until there is some data (or maybe for enough data),
	 * peeking the msg size should be only for nonblocking reads
	 */
	size = __pipe_peekmsgsize(fd);
	if (size > 0) {
		if (size < len) {
			len = size;
		}
	}
	else {
		errno = EBADF;
		return -1;
	}
#endif
	/* if len is greater than PIPE_BUF then, MsgPipe functions returns
	 * SCE_KERNEL_ERROR_ILLEGAL_SIZE, but it should read at least
	 * PIPE_BUF bytes, and return the number of bytes read.
	 */
	if (len > PIPE_BUF) {
		len = PIPE_BUF;
	}

	/**
	* Receive a message from a pipe
	*
	* @param uid - The UID of the pipe
	* @param message - Pointer to the message
	* @param size - Size of the message
	* @param unk1 - Unknown
	* @param unk2 - Unknown
	* @param timeout - Timeout for receive
	*
	* @return 0 on success, < 0 on error
	*/
	ret = sceKernelReceiveMsgPipe(sceuid, buf, len, 0, NULL, NULL);
	
	if (ret == 0) {/* Success - Data */
		return len;
	}
	else {/* Error */
		return __set_errno(ret);
	}
}
#endif

#ifdef F___pipe_write
__attribute__((weak))
int __pipe_write(int fd, const void *buf, size_t len)
{
	int ret;
	int sceuid;
	char *cbuf;
	
	if (!__IS_FD_OF_TYPE(fd, __DESCRIPTOR_TYPE_PIPE)) {
		errno = EBADF;
		return -1;
	}
	
	sceuid = __descriptormap[fd]->descriptor;

	/* if len is greater than PIPE_BUF then, MsgPipe functions returns
	 * SCE_KERNEL_ERROR_ILLEGAL_SIZE, but it should write at least
	 * PIPE_BUF bytes, and return the number of bytes written.
	 */
	if (len > PIPE_BUF) {
		len = PIPE_BUF;
	}

	/**
	* Send a message to a pipe
	*
	* @param uid - The UID of the pipe
	* @param message - Pointer to the message
	* @param size - Size of the message
	* @param unk1 - Unknown
	* @param unk2 - Unknown
	* @param timeout - Timeout for send
	*
	* @return 0 on success, < 0 on error
	*/
	cbuf = (char *)buf;
	ret = sceKernelSendMsgPipe(sceuid, cbuf, len, 0, NULL, NULL);
	if (ret == 0) {/* Success - Data */
		return len;
	}
	else {/* Error */
		return __set_errno(ret);
	}
}
#endif

#ifdef F___pipe_nonblocking_write
__attribute__((weak))
int __pipe_nonblocking_write(int fd, const void *buf, size_t len)
{
	int ret;
	int sceuid;
	char *cbuf;
	
	if (!__IS_FD_OF_TYPE(fd, __DESCRIPTOR_TYPE_PIPE)) {
		errno = EBADF;
		return -1;
	}
	
	sceuid = __descriptormap[fd]->descriptor;

	/* if len is greater than PIPE_BUF then, MsgPipe functions returns
	 * SCE_KERNEL_ERROR_ILLEGAL_SIZE, but it should write at least
	 * PIPE_BUF bytes, and return the number of bytes written.
	 */
	if (len > PIPE_BUF) {
		len = PIPE_BUF;
	}

	cbuf = (char *)buf;
	ret = sceKernelTrySendMsgPipe(sceuid, cbuf, len, 0, 0);
	
	if (ret == 0) {/* Success - Data */
		return len;
	}
	else if (ret == SCE_KERNEL_ERROR_MPP_FULL) {
		errno = EAGAIN;
		return -1;
	}
	else {/* Error */
		return __set_errno(ret);
	}
}
#endif
