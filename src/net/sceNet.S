	.set noreorder

#include "pspimport.s"

#ifdef F_sceNet_0000
	IMPORT_START	"sceNet",0x00090000
#endif
#ifdef F_sceNet_0001
	IMPORT_FUNC	"sceNet",0x39AF39A6,sceNetInit
#endif
#ifdef F_sceNet_0002
	IMPORT_FUNC	"sceNet",0x281928A9,sceNetTerm
#endif
#ifdef F_sceNet_0003
	IMPORT_FUNC	"sceNet",0x50647530,sceNetFreeThreadinfo
#endif
#ifdef F_sceNet_0004
	IMPORT_FUNC	"sceNet",0xAD6844C6,sceNetThreadAbort
#endif
#ifdef F_sceNet_0005
	IMPORT_FUNC	"sceNet",0x89360950,sceNetEtherNtostr
#endif
#ifdef F_sceNet_0006
	IMPORT_FUNC	"sceNet",0xD27961C9,sceNetEtherStrton
#endif
#ifdef F_sceNet_0007
	IMPORT_FUNC	"sceNet",0x0BF0A3AE,sceNetGetLocalEtherAddr
#endif
#ifdef F_sceNet_0008
	IMPORT_FUNC	"sceNet",0xCC393E48,sceNetGetMallocStat
#endif
