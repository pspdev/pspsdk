	.set noreorder

#include "pspimport.s"

#ifdef F_scePaf_0000
	IMPORT_START	"scePaf",0x00010011
#endif
#ifdef F_scePaf_0001
	IMPORT_FUNC	"scePaf",0x967A56EF,paf_strlen
#endif
#ifdef F_scePaf_0002
	IMPORT_FUNC	"scePaf",0x6439FDBC,paf_memset
#endif
#ifdef F_scePaf_0003
	IMPORT_FUNC	"scePaf",0xB6ADE52D,paf_memcmp
#endif
#ifdef F_scePaf_0004
	IMPORT_FUNC	"scePaf",0x11EFC5FD,paf_sprintf
#endif
#ifdef F_scePaf_0005
	IMPORT_FUNC	"scePaf",0xC6883C73,paf_strncpy
#endif
#ifdef F_scePaf_0006
	IMPORT_FUNC	"scePaf",0x15AFC8D3,paf_snprintf
#endif
#ifdef F_scePaf_0007
	IMPORT_FUNC	"scePaf",0x6BD7452C,paf_memcpy
#endif
#ifdef F_scePaf_0008
	IMPORT_FUNC	"scePaf",0x98DE3BA6,paf_strcpy
#endif

