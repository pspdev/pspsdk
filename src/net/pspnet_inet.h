/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspnet_inet.h - PSP networking libraries.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@0xd6.org>
 *
 * Portions based on PspPet's wifi_03 sample code.
 * 
 * $Id: pspnet_inet.h 1541 2005-12-08 05:49:20Z mrbrown $
 */

#ifndef PSPNET_INET_H
#define PSPNET_INET_H

#ifdef __cplusplus
extern "C" {
#endif

int sceNetInetInit(void);
int sceNetInetTerm(void);

/* The real sceNetInet socket prototypes are in <sys/socket.h>. */
#ifdef DOXYGEN
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
#endif /* DOXYGEN */

#ifdef __cplusplus
}
#endif

#endif /* PSPNET_INET_H */
