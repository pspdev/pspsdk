	.set noreorder

#include "pspimport.s"

#ifdef F_sceNetApctl_0000
	IMPORT_START	"sceNetApctl",0x00090000
#endif
#ifdef F_sceNetApctl_0001
	IMPORT_FUNC	"sceNetApctl",0xE2F91F9B,sceNetApctlInit
#endif
#ifdef F_sceNetApctl_0002
	IMPORT_FUNC	"sceNetApctl",0xB3EDD0EC,sceNetApctlTerm
#endif
#ifdef F_sceNetApctl_0003
	IMPORT_FUNC	"sceNetApctl",0x2BEFDF23,sceNetApctlGetInfo
#endif
#ifdef F_sceNetApctl_0004
	IMPORT_FUNC	"sceNetApctl",0x8ABADD51,sceNetApctlAddHandler
#endif
#ifdef F_sceNetApctl_0005
	IMPORT_FUNC	"sceNetApctl",0x5963991B,sceNetApctlDelHandler
#endif
#ifdef F_sceNetApctl_0006
	IMPORT_FUNC	"sceNetApctl",0xCFB957C6,sceNetApctlConnect
#endif
#ifdef F_sceNetApctl_0007
	IMPORT_FUNC	"sceNetApctl",0x24FE91A1,sceNetApctlDisconnect
#endif
#ifdef F_sceNetApctl_0008
	IMPORT_FUNC	"sceNetApctl",0x5DEAC81B,sceNetApctlGetState
#endif
