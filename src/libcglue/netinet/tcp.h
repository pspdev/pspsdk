#ifndef __NETINET_TCP_H__
#define __NETINET_TCP_H__

#include <netinet/in.h>

#define SOL_TCP    IPPROTO_TCP

/* Socket options */
#define	TCP_NODELAY	0x01	/* don't delay send to coalesce packets */
#define	TCP_MAXSEG	0x02	/* set maximum segment size */

#endif
