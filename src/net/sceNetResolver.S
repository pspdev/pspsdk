	.set noreorder

#include "pspimport.s"

#ifdef F_sceNetResolver_0000
	IMPORT_START	"sceNetResolver",0x00090000
#endif
#ifdef F_sceNetResolver_0001
	IMPORT_FUNC	"sceNetResolver",0xF3370E61,sceNetResolverInit
#endif
#ifdef F_sceNetResolver_0002
	IMPORT_FUNC	"sceNetResolver",0x6138194A,sceNetResolverTerm
#endif
#ifdef F_sceNetResolver_0003
	IMPORT_FUNC	"sceNetResolver",0x244172AF,sceNetResolverCreate
#endif
#ifdef F_sceNetResolver_0004
	IMPORT_FUNC	"sceNetResolver",0x94523E09,sceNetResolverDelete
#endif
#ifdef F_sceNetResolver_0005
	IMPORT_FUNC	"sceNetResolver",0x224C5F44,sceNetResolverStartNtoA
#endif
#ifdef F_sceNetResolver_0006
	IMPORT_FUNC	"sceNetResolver",0x629E2FB7,sceNetResolverStartAtoN
#endif
#ifdef F_sceNetResolver_0007
	IMPORT_FUNC	"sceNetResolver",0x808F6063,sceNetResolverStop
#endif
