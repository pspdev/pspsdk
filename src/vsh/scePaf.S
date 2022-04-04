	.set noreorder

#include "pspimport.s"

#ifdef F_scePaf_0000
	IMPORT_START	"scePaf",0x00010011
#endif
#ifdef F_scePaf_0001
	IMPORT_FUNC	"scePaf",0xD7DCB972,paf_strlen
#endif
#ifdef F_scePaf_0002
	IMPORT_FUNC	"scePaf",0xBB89C9EA,paf_memset // or 0xD9E2D6E1
#endif
#ifdef F_scePaf_0003
	IMPORT_FUNC	"scePaf",0xB05D9677,paf_memcmp
#endif
#ifdef F_scePaf_0004
	IMPORT_FUNC	"scePaf",0xA138A376,paf_sprintf
#endif
#ifdef F_scePaf_0005
	IMPORT_FUNC	"scePaf",0x7B7133D5,paf_snprintf
#endif
#ifdef F_scePaf_0006
	IMPORT_FUNC	"scePaf",0xF7C46E37,paf_memcpy // or 0xB4652CFE
#endif
#ifdef F_scePaf_0007
	IMPORT_FUNC	"scePaf",0x726DFBA9,paf_strcpy
#endif
#ifdef F_scePaf_0008
	IMPORT_FUNC	"scePaf",0x7E600551,paf_strtok_r
#endif
#ifdef F_scePaf_0009
	IMPORT_FUNC	"scePaf",0x5E909060,paf_malloc
#endif
#ifdef F_scePaf_0010
	IMPORT_FUNC	"scePaf",0xDB1612F1,paf_free
#endif
#ifdef F_scePaf_0011
	IMPORT_FUNC	"scePaf",0xAF067FA2,paf_wcslen
#endif
#ifdef F_scePaf_0012
	IMPORT_FUNC	"scePaf",0x706ABBFF,paf_strncpy
#endif
#ifdef F_scePaf_0013
	IMPORT_FUNC	"scePaf",0x4CF09BA2,paf_strcmp
#endif
#ifdef F_scePaf_0014
	IMPORT_FUNC	"scePaf",0xE0B32AE8,paf_strncmp
#endif
#ifdef F_scePaf_0015
	IMPORT_FUNC	"scePaf",0xC3B2D310,paf_strchr
#endif
#ifdef F_scePaf_0016
	IMPORT_FUNC	"scePaf",0x22420CC7,paf_strrchr
#endif
#ifdef F_scePaf_0017
	IMPORT_FUNC	"scePaf",0x4CE9C8D7,paf_strpbrk
#endif
#ifdef F_scePaf_0018
	IMPORT_FUNC	"scePaf",0xA4B8A4E3,paf_strtoul
#endif
#ifdef F_scePaf_0019
	IMPORT_FUNC	"scePaf",0x3874A5F8,scePafGetText
#endif
#ifdef F_scePaf_0020
	IMPORT_FUNC	"scePaf",0x50DCB767,PAF_Resource_GetPageNodeByID
#endif
#ifdef F_scePaf_0021
	IMPORT_FUNC	"scePaf",0x64A31513,PAF_Resource_ResolveRefWString
#endif
