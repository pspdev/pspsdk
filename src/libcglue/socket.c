/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * socket.c - Socket wrappers to provide similar functions to normal unix
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * 
 */

#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <psptypes.h>
#include <pspnet_inet.h>
#include "fdman.h"

// To avoid warnings
int	sceNetInetAccept(int s, struct sockaddr *addr, socklen_t *addrlen);
int	sceNetInetBind(int s, const struct sockaddr *my_addr, socklen_t addrlen);
int	sceNetInetConnect(int s, const struct sockaddr *serv_addr, socklen_t addrlen);
int	sceNetInetGetsockopt(int s, int level, int optname, void *optval, socklen_t *optlen);
int	sceNetInetListen(int s, int backlog);
size_t	sceNetInetRecv(int s, void *buf, size_t len, int flags);
size_t	sceNetInetRecvfrom(int s, void *buf, size_t flags, int, struct sockaddr *from, socklen_t *fromlen);
size_t	sceNetInetSend(int s, const void *buf, size_t len, int flags);
size_t	sceNetInetSendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
int	sceNetInetSetsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
int	sceNetInetShutdown(int s, int how);
int	sceNetInetSocket(int domain, int type, int protocol);
int sceNetInetClose(int s);
int sceNetInetGetErrno(void);
int	sceNetInetGetpeername(int s, struct sockaddr *name, socklen_t *namelen);
int	sceNetInetGetsockname(int s, struct sockaddr *name, socklen_t *namelen);
ssize_t sceNetInetSendmsg(int s, const struct msghdr *msg, int flags);
ssize_t sceNetInetRecvmsg(int s, struct msghdr *msg, int flags);

#ifdef F_socket
int	socket(int domain, int type, int protocol)
{
	int sock, scesock;

	scesock = sceNetInetSocket(domain, type, protocol);
	if(scesock < 0)	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	sock = __fdman_get_new_descriptor();
	if( sock != -1 )	{
		__descriptormap[sock]->descriptor = scesock;
		__descriptormap[sock]->type = __DESCRIPTOR_TYPE_SOCKET;
	}
	else {
		sceNetInetClose(scesock);
		errno = ENOENT;
		return -1;
	}

	return sock;
}
#endif

/* These are glue routines that are called from _close(), _read(), and
   _write().  They are here so that any program that uses socket() will pull
   them in and have expanded socket capability. */

#ifdef F___socket_close
int __socket_close(int sock)
{
	int ret = 0;

	if (__descriptormap[sock]->ref_count == 1) {
		ret = sceNetInetClose(__descriptormap[sock]->descriptor);
	}

	__fdman_release_descriptor(sock);

	if(ret < 0)
	{
		/* If close is defined likely errno is */
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_accept
int	accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
	int newscesock, newsock;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	newscesock = sceNetInetAccept(__descriptormap[s]->descriptor, addr, addrlen);
	if( (newscesock >= 0) ) {
		newsock = __fdman_get_new_descriptor();
		if ( newsock != -1 ) {
			__descriptormap[newsock]->descriptor = newscesock;
			__descriptormap[newsock]->type = __DESCRIPTOR_TYPE_SOCKET;
		}
		else {
			sceNetInetClose(newscesock);
			errno = ENOENT;
			return -1;
		}
	}
	else {
		errno = ENOENT;
		return -1;
	}

	return newsock;
}
#endif

#ifdef F_bind
int	bind(int s, const struct sockaddr *my_addr, socklen_t addrlen)
{
	int ret;
	
	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetBind(__descriptormap[s]->descriptor, my_addr, addrlen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_connect
int	connect(int s, const struct sockaddr *serv_addr, socklen_t addrlen)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetConnect(__descriptormap[s]->descriptor, serv_addr, addrlen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}
	
	return 0;
}
#endif

#ifdef F_listen
int	listen(int s, int backlog)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetListen(__descriptormap[s]->descriptor, backlog);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_recv
ssize_t	recv(int s, void *buf, size_t len, int flags)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetRecv(__descriptormap[s]->descriptor, buf, len, flags);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return ret;
}
#endif

#ifdef F_recvfrom
ssize_t	recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetRecvfrom(__descriptormap[s]->descriptor, buf, len, flags, from, fromlen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return ret;
}
#endif

#ifdef F_send
ssize_t	send(int s, const void *buf, size_t len, int flags)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetSend(__descriptormap[s]->descriptor, buf, len, flags);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return ret;
}
#endif

#ifdef F_sendto
ssize_t	sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetSendto(__descriptormap[s]->descriptor, buf, len, flags, to, tolen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return ret;
}
#endif

#ifdef F_getsockopt
int	getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetGetsockopt(__descriptormap[s]->descriptor, level, optname, optval, optlen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_setsockopt
int	setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetSetsockopt(__descriptormap[s]->descriptor, level, optname, optval, optlen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}
	else
	{
		if ( (level == SOL_SOCKET) && (optname == SO_NONBLOCK) ) {
			if (*((int*)optval) == 1) {
				__descriptormap[s]->flags |= O_NONBLOCK;
			}
			else {
				__descriptormap[s]->flags &= ~O_NONBLOCK;
			}	
		}
	}

	return 0;
}
#endif

#ifdef F_shutdown
int	shutdown(int s, int how)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetShutdown(__descriptormap[s]->descriptor, how);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_getpeername
int	getpeername(int s, struct sockaddr *name, socklen_t *namelen)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetGetpeername(__descriptormap[s]->descriptor, name, namelen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_getsockname
int	getsockname(int s, struct sockaddr *name, socklen_t *namelen)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetGetsockname(__descriptormap[s]->descriptor, name, namelen);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_inet_ntoa
char *inet_ntoa(struct in_addr in)
{
	static char ip_addr[INET_ADDRSTRLEN+1];

	if(sceNetInetInetNtop(AF_INET, &in, ip_addr, INET_ADDRSTRLEN) == NULL)
	{
		strcpy(ip_addr, "Invalid");
	}

	return ip_addr;
}
#endif

#ifdef F_sendmsg
ssize_t sendmsg(int s, const struct msghdr *msg, int flags)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetSendmsg(__descriptormap[s]->descriptor, msg, flags);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif

#ifdef F_recvmsg
ssize_t recvmsg(int s, struct msghdr *msg, int flags)
{
	int ret;

	if (!__IS_FD_OF_TYPE(s, __DESCRIPTOR_TYPE_SOCKET)) {
		errno = EBADF;
		return -1;
	}

	ret = sceNetInetRecvmsg(__descriptormap[s]->descriptor, msg, flags);
	if(ret < 0)
	{
		errno = sceNetInetGetErrno();
		return -1;
	}

	return 0;
}
#endif