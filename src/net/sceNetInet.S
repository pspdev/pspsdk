	.set noreorder

#include "pspimport.s"

#ifdef F_sceNetInet_0000
	IMPORT_START	"sceNetInet",0x00090000
#endif
#ifdef F_sceNetInet_0001
	IMPORT_FUNC	"sceNetInet",0x17943399,sceNetInetInit
#endif
#ifdef F_sceNetInet_0002
	IMPORT_FUNC	"sceNetInet",0xA9ED66B9,sceNetInetTerm
#endif
#ifdef F_sceNetInet_0003
	IMPORT_FUNC	"sceNetInet",0xDB094E1B,sceNetInetAccept
#endif
#ifdef F_sceNetInet_0004
	IMPORT_FUNC	"sceNetInet",0x1A33F9AE,sceNetInetBind
#endif
#ifdef F_sceNetInet_0005
	IMPORT_FUNC	"sceNetInet",0x8D7284EA,sceNetInetClose
#endif
#ifdef F_sceNetInet_0006
	IMPORT_FUNC	"sceNetInet",0x805502DD,sceNetInetCloseWithRST
#endif
#ifdef F_sceNetInet_0007
	IMPORT_FUNC	"sceNetInet",0x410B34AA,sceNetInetConnect
#endif
#ifdef F_sceNetInet_0008
	IMPORT_FUNC	"sceNetInet",0xE247B6D6,sceNetInetGetpeername
#endif
#ifdef F_sceNetInet_0009
	IMPORT_FUNC	"sceNetInet",0x162E6FD5,sceNetInetGetsockname
#endif
#ifdef F_sceNetInet_0010
	IMPORT_FUNC	"sceNetInet",0x4A114C7C,sceNetInetGetsockopt
#endif
#ifdef F_sceNetInet_0011
	IMPORT_FUNC	"sceNetInet",0xD10A1A7A,sceNetInetListen
#endif
#ifdef F_sceNetInet_0012
	IMPORT_FUNC	"sceNetInet",0xFAABB1DD,sceNetInetPoll
#endif
#ifdef F_sceNetInet_0013
	IMPORT_FUNC	"sceNetInet",0xCDA85C99,sceNetInetRecv
#endif
#ifdef F_sceNetInet_0014
	IMPORT_FUNC	"sceNetInet",0xC91142E4,sceNetInetRecvfrom
#endif
#ifdef F_sceNetInet_0015
	IMPORT_FUNC	"sceNetInet",0xEECE61D2,sceNetInetRecvmsg
#endif
#ifdef F_sceNetInet_0016
	IMPORT_FUNC	"sceNetInet",0x5BE8D595,sceNetInetSelect
#endif
#ifdef F_sceNetInet_0017
	IMPORT_FUNC	"sceNetInet",0x7AA671BC,sceNetInetSend
#endif
#ifdef F_sceNetInet_0018
	IMPORT_FUNC	"sceNetInet",0x05038FC7,sceNetInetSendto
#endif
#ifdef F_sceNetInet_0019
	IMPORT_FUNC	"sceNetInet",0x774E36F4,sceNetInetSendmsg
#endif
#ifdef F_sceNetInet_0020
	IMPORT_FUNC	"sceNetInet",0x2FE71FE7,sceNetInetSetsockopt
#endif
#ifdef F_sceNetInet_0021
	IMPORT_FUNC	"sceNetInet",0x4CFE4E56,sceNetInetShutdown
#endif
#ifdef F_sceNetInet_0022
	IMPORT_FUNC	"sceNetInet",0x8B7B220F,sceNetInetSocket
#endif
#ifdef F_sceNetInet_0023
	IMPORT_FUNC	"sceNetInet",0x80A21ABD,sceNetInetSocketAbort
#endif
#ifdef F_sceNetInet_0024
	IMPORT_FUNC	"sceNetInet",0xFBABE411,sceNetInetGetErrno
#endif
#ifdef F_sceNetInet_0025
	IMPORT_FUNC	"sceNetInet",0xB3888AD4,sceNetInetGetTcpcbstat
#endif
#ifdef F_sceNetInet_0026
	IMPORT_FUNC	"sceNetInet",0x39B0C7D3,sceNetInetGetUdpcbstat
#endif
#ifdef F_sceNetInet_0027
	IMPORT_FUNC	"sceNetInet",0xB75D5B0A,sceNetInetInetAddr
#endif
#ifdef F_sceNetInet_0028
	IMPORT_FUNC	"sceNetInet",0x1BDF5D13,sceNetInetInetAton
#endif
#ifdef F_sceNetInet_0029
	IMPORT_FUNC	"sceNetInet",0xD0792666,sceNetInetInetNtop
#endif
#ifdef F_sceNetInet_0030
	IMPORT_FUNC	"sceNetInet",0xE30B8C19,sceNetInetInetPton
#endif
