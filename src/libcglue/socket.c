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
#include <pspnet.h>
#include <pspnet_inet.h>
#include <pspnet_apctl.h>

#include <pspgu.h>
#include <pspdisplay.h>
#include <psputility.h>
#include "fdman.h"

#define GU_LIST_SIZE (32 * 1024)
#define NET_BUFFER_SIZE (128 * 1024)
#define NET_APCTL_BUFFER_SIZE (32 * 1024)
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define BUFFER_WIDTH 512
#define BUFFER_SIZE (BUFFER_WIDTH * SCREEN_HEIGHT)
#define PIXEL_SIZE 4

int _netInit()
{
	int done = 0;
	int gu_was_active = guGetInit();
	uint32_t __attribute__((aligned(16))) list[GU_LIST_SIZE];  // Needed for sceGuStart to work

	// Initialize the required networking libraries
	sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
	sceUtilityLoadNetModule(PSP_NET_MODULE_INET);
	sceNetInit(NET_BUFFER_SIZE, 42, 4096, 42, 4096);
	sceNetInetInit();
	sceNetApctlInit(NET_APCTL_BUFFER_SIZE, 48);

	// If libgu was not yet active, temporarily activate it so the network selection dialog can work
	if (!gu_was_active) {
		sceGuInit();
		sceGuStart(GU_DIRECT, list);
		sceGuDrawBuffer(GU_PSM_8888, (void*)0, BUFFER_WIDTH);
		sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, (void*)(BUFFER_SIZE*PIXEL_SIZE), BUFFER_WIDTH);

		//Set up viewport
		sceGuOffset(2048 - (SCREEN_WIDTH / 2), 2048 - (SCREEN_WIDTH / 2));
		sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);

		sceGuDisable(GU_DEPTH_TEST);

		sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		sceGuEnable(GU_SCISSOR_TEST);
		sceGuDisable(GU_ALPHA_TEST);

		sceGuFinish();
		sceGuDisplay(GU_TRUE);
	}

	// Initialize the network selection dialog
	pspUtilityNetconfData params;

	memset(&params, 0, sizeof(params));
	params.base.size = sizeof(params);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.base.language);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_BUTTON_SWAP, &params.base.buttonSwap);
	params.base.graphicsThread = 17;
	params.base.accessThread = 19;
	params.base.fontThread = 18;
	params.base.soundThread = 16;
	params.action = PSP_NETCONF_ACTION_CONNECTAP;
	memset(&params.adhocparam, 0, sizeof(params.adhocparam));

	// Show the network selection dialog
	sceUtilityNetconfInitStart(&params);
	while(!done)
	{
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0);
		sceGuClear(GU_COLOR_BUFFER_BIT);
		if (sceGuGetStatus(GU_DEPTH_TEST))
			sceGuClear(GU_DEPTH_BUFFER_BIT);
		sceGuFinish();
		sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

		switch(sceUtilityNetconfGetStatus())
		{
			case PSP_UTILITY_DIALOG_VISIBLE:
				sceUtilityNetconfUpdate(1);
				break;
			case PSP_UTILITY_DIALOG_FINISHED:
				sceUtilityNetconfShutdownStart();
				break;
			case PSP_UTILITY_DIALOG_QUIT:
				sceUtilityNetconfShutdownStart();
				break;
			case PSP_UTILITY_DIALOG_NONE:
				done = 1;
				break;
			default :
				break;
		}
		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}

	// Clean up libgu
	if (!gu_was_active) {
		sceGuDisplay(GU_FALSE);
		sceGuTerm();
	}

	// Returns 1 if connecting to the network was successful
	return params.base.result == 0;
	return 1;
}

#ifdef F_socket
int	socket(int domain, int type, int protocol)
{
	int sock, scesock;
	int connection_state = PSP_NET_APCTL_STATE_DISCONNECTED;

	sceNetApctlGetState(&connection_state);
	if (connection_state == PSP_NET_APCTL_STATE_DISCONNECTED) {
		int net_connected = _netInit();
		if (!net_connected) {
			errno = EIO;
			return -1;
		}
	}

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
__attribute__((weak))
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
__attribute__((weak))
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
__attribute__((weak))
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
__attribute__((weak))
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