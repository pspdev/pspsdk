	.set noreorder

#include "pspimport.s"

#ifdef F_UtilsForUser_0000
	IMPORT_START	"UtilsForUser",0x40010000
#endif
#ifdef F_UtilsForUser_0001
	IMPORT_FUNC	"UtilsForUser",0xBFA98062,sceKernelDcacheInvalidateRange
#endif
#ifdef F_UtilsForUser_0002
	IMPORT_FUNC	"UtilsForUser",0xC8186A58,sceKernelUtilsMd5Digest
#endif
#ifdef F_UtilsForUser_0003
	IMPORT_FUNC	"UtilsForUser",0x9E5C5086,sceKernelUtilsMd5BlockInit
#endif
#ifdef F_UtilsForUser_0004
	IMPORT_FUNC	"UtilsForUser",0x61E1E525,sceKernelUtilsMd5BlockUpdate
#endif
#ifdef F_UtilsForUser_0005
	IMPORT_FUNC	"UtilsForUser",0xB8D24E78,sceKernelUtilsMd5BlockResult
#endif
#ifdef F_UtilsForUser_0006
	IMPORT_FUNC	"UtilsForUser",0x840259F1,sceKernelUtilsSha1Digest
#endif
#ifdef F_UtilsForUser_0007
	IMPORT_FUNC	"UtilsForUser",0xF8FCD5BA,sceKernelUtilsSha1BlockInit
#endif
#ifdef F_UtilsForUser_0008
	IMPORT_FUNC	"UtilsForUser",0x346F6DA8,sceKernelUtilsSha1BlockUpdate
#endif
#ifdef F_UtilsForUser_0009
	IMPORT_FUNC	"UtilsForUser",0x585F1C09,sceKernelUtilsSha1BlockResult
#endif
#ifdef F_UtilsForUser_0010
	IMPORT_FUNC	"UtilsForUser",0xE860E75E,sceKernelUtilsMt19937Init
#endif
#ifdef F_UtilsForUser_0011
	IMPORT_FUNC	"UtilsForUser",0x06FB8A63,sceKernelUtilsMt19937UInt
#endif
#ifdef F_UtilsForUser_0012
	IMPORT_FUNC	"UtilsForUser",0x37FB5C42,sceKernelGetGPI
#endif
#ifdef F_UtilsForUser_0013
	IMPORT_FUNC	"UtilsForUser",0x6AD345D7,sceKernelSetGPO
#endif
#ifdef F_UtilsForUser_0014
	IMPORT_FUNC	"UtilsForUser",0x91E4F6A7,sceKernelLibcClock
#endif
#ifdef F_UtilsForUser_0015
	IMPORT_FUNC	"UtilsForUser",0x27CC57F0,sceKernelLibcTime
#endif
#ifdef F_UtilsForUser_0016
	IMPORT_FUNC	"UtilsForUser",0x71EC4271,sceKernelLibcGettimeofday
#endif
#ifdef F_UtilsForUser_0017
	IMPORT_FUNC	"UtilsForUser",0x79D1C3FA,sceKernelDcacheWritebackAll
#endif
#ifdef F_UtilsForUser_0018
	IMPORT_FUNC	"UtilsForUser",0xB435DEC5,sceKernelDcacheWritebackInvalidateAll
#endif
#ifdef F_UtilsForUser_0019
	IMPORT_FUNC	"UtilsForUser",0x3EE30821,sceKernelDcacheWritebackRange
#endif
#ifdef F_UtilsForUser_0020
	IMPORT_FUNC	"UtilsForUser",0x34B9FA9E,sceKernelDcacheWritebackInvalidateRange
#endif
#ifdef F_UtilsForUser_0021
	IMPORT_FUNC	"UtilsForUser",0x80001C4C,sceKernelDcacheProbe
#endif
#ifdef F_UtilsForUser_0022
	IMPORT_FUNC	"UtilsForUser",0x16641D70,sceKernelDcacheReadTag
#endif
#ifdef F_UtilsForUser_0023
	IMPORT_FUNC	"UtilsForUser",0x4FD31C9D,sceKernelIcacheProbe
#endif
#ifdef F_UtilsForUser_0024
	IMPORT_FUNC	"UtilsForUser",0xFB05FAD0,sceKernelIcacheReadTag
#endif
