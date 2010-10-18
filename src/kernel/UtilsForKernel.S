	.set noreorder

#include "pspimport.s"

#ifdef F_UtilsForKernel_0000
	IMPORT_START	"UtilsForKernel",0x00090000
#endif
#ifdef F_UtilsForKernel_0001
	IMPORT_FUNC	"UtilsForKernel",0x80FE032E,sceUtilsKernelDcacheWBinvRange
#endif
#ifdef F_UtilsForKernel_0002
	IMPORT_FUNC	"UtilsForKernel",0xC8186A58,sceKernelUtilsMd5Digest
#endif
#ifdef F_UtilsForKernel_0003
	IMPORT_FUNC	"UtilsForKernel",0x9E5C5086,sceKernelUtilsMd5BlockInit
#endif
#ifdef F_UtilsForKernel_0004
	IMPORT_FUNC	"UtilsForKernel",0x61E1E525,sceKernelUtilsMd5BlockUpdate
#endif
#ifdef F_UtilsForKernel_0005
	IMPORT_FUNC	"UtilsForKernel",0xB8D24E78,sceKernelUtilsMd5BlockResult
#endif
#ifdef F_UtilsForKernel_0006
	IMPORT_FUNC	"UtilsForKernel",0x840259F1,sceKernelUtilsSha1Digest
#endif
#ifdef F_UtilsForKernel_0007
	IMPORT_FUNC	"UtilsForKernel",0xF8FCD5BA,sceKernelUtilsSha1BlockInit
#endif
#ifdef F_UtilsForKernel_0008
	IMPORT_FUNC	"UtilsForKernel",0x346F6DA8,sceKernelUtilsSha1BlockUpdate
#endif
#ifdef F_UtilsForKernel_0009
	IMPORT_FUNC	"UtilsForKernel",0x585F1C09,sceKernelUtilsSha1BlockResult
#endif
#ifdef F_UtilsForKernel_0010
	IMPORT_FUNC	"UtilsForKernel",0xE860E75E,sceKernelUtilsMt19937Init
#endif
#ifdef F_UtilsForKernel_0011
	IMPORT_FUNC	"UtilsForKernel",0x06FB8A63,sceKernelUtilsMt19937UInt
#endif
#ifdef F_UtilsForKernel_0012
	IMPORT_FUNC	"UtilsForKernel",0x193D4036,sceKernelSetGPIMask
#endif
#ifdef F_UtilsForKernel_0013
	IMPORT_FUNC	"UtilsForKernel",0x95035FEF,sceKernelSetGPOMask
#endif
#ifdef F_UtilsForKernel_0014
	IMPORT_FUNC	"UtilsForKernel",0x37FB5C42,sceKernelGetGPI
#endif
#ifdef F_UtilsForKernel_0015
	IMPORT_FUNC	"UtilsForKernel",0x6AD345D7,sceKernelSetGPO
#endif
#ifdef F_UtilsForKernel_0016
	IMPORT_FUNC	"UtilsForKernel",0x7B7ED3FD,sceKernelRegisterLibcRtcFunc
#endif
#ifdef F_UtilsForKernel_0017
	IMPORT_FUNC	"UtilsForKernel",0x6151A7C3,sceKernelReleaseLibcRtcFunc
#endif
#ifdef F_UtilsForKernel_0018
	IMPORT_FUNC	"UtilsForKernel",0x91E4F6A7,sceKernelLibcClock
#endif
#ifdef F_UtilsForKernel_0019
	IMPORT_FUNC	"UtilsForKernel",0x27CC57F0,sceKernelLibcTime
#endif
#ifdef F_UtilsForKernel_0020
	IMPORT_FUNC	"UtilsForKernel",0x71EC4271,sceKernelLibcGettimeofday
#endif
#ifdef F_UtilsForKernel_0021
	IMPORT_FUNC	"UtilsForKernel",0x79D1C3FA,sceKernelDcacheWritebackAll
#endif
#ifdef F_UtilsForKernel_0022
	IMPORT_FUNC	"UtilsForKernel",0xB435DEC5,sceKernelDcacheWritebackInvalidateAll
#endif
#ifdef F_UtilsForKernel_0023
	IMPORT_FUNC	"UtilsForKernel",0x864A9D72,sceKernelDcacheInvalidateAll
#endif
#ifdef F_UtilsForKernel_0024
	IMPORT_FUNC	"UtilsForKernel",0x3EE30821,sceKernelDcacheWritebackRange
#endif
#ifdef F_UtilsForKernel_0025
	IMPORT_FUNC	"UtilsForKernel",0x34B9FA9E,sceKernelDcacheWritebackInvalidateRange
#endif
#ifdef F_UtilsForKernel_0026
	IMPORT_FUNC	"UtilsForKernel",0xBFA98062,sceKernelDcacheInvalidateRange
#endif
#ifdef F_UtilsForKernel_0027
	IMPORT_FUNC	"UtilsForKernel",0x80001C4C,sceKernelDcacheProbe
#endif
#ifdef F_UtilsForKernel_0028
	IMPORT_FUNC	"UtilsForKernel",0x16641D70,sceKernelDcacheReadTag
#endif
#ifdef F_UtilsForKernel_0029
	IMPORT_FUNC	"UtilsForKernel",0x920F104A,sceKernelIcacheInvalidateAll
#endif
#ifdef F_UtilsForKernel_0030
	IMPORT_FUNC	"UtilsForKernel",0xC2DF770E,sceKernelIcacheInvalidateRange
#endif
#ifdef F_UtilsForKernel_0031
	IMPORT_FUNC	"UtilsForKernel",0x4FD31C9D,sceKernelIcacheProbe
#endif
#ifdef F_UtilsForKernel_0032
	IMPORT_FUNC	"UtilsForKernel",0xFB05FAD0,sceKernelIcacheReadTag
#endif
#ifdef F_UtilsForKernel_0033
	IMPORT_FUNC	"UtilsForKernel",0x78934841,sceKernelGzipDecompress
#endif
#ifdef F_UtilsForKernel_0034
	IMPORT_FUNC	"UtilsForKernel",0xE0CE3E29,sceKernelGzipIsValid
#endif
#ifdef F_UtilsForKernel_0035
	IMPORT_FUNC	"UtilsForKernel",0xB0E9C31F,sceKernelGzipGetInfo
#endif
#ifdef F_UtilsForKernel_0036
	IMPORT_FUNC	"UtilsForKernel",0xE0E6BA96,sceKernelGzipGetName
#endif
#ifdef F_UtilsForKernel_0037
	IMPORT_FUNC	"UtilsForKernel",0x8C1FBE04,sceKernelGzipGetComment
#endif
#ifdef F_UtilsForKernel_0038
	IMPORT_FUNC	"UtilsForKernel",0x23FFC828,sceKernelGzipGetCompressedData
#endif
#ifdef F_UtilsForKernel_0039
	IMPORT_FUNC	"UtilsForKernel",0xE8DB3CE6,sceKernelDeflateDecompress
#endif
