	.set noreorder

#include "pspimport.s"

#ifdef F_sceMpegbase_0000
	IMPORT_START	"sceMpegbase",0x00090000
#endif
#ifdef F_sceMpegbase_0001
	IMPORT_FUNC	"sceMpegbase",0xBE45C284,sceMpegBaseYCrCbCopyVme
#endif
#ifdef F_sceMpegbase_0002
	IMPORT_FUNC	"sceMpegbase",0x492B5E4B,sceMpegBaseCscInit
#endif
#ifdef F_sceMpegbase_0003
	IMPORT_FUNC	"sceMpegbase",0xCE8EB837,sceMpegBaseCscVme
#endif
#ifdef F_sceMpegbase_0004
	IMPORT_FUNC "sceMpegbase",0x0530BE4E,sceMpegbase_0530BE4E
#endif
#ifdef F_sceMpegbase_0005
	IMPORT_FUNC "sceMpegbase",0x304882E1,sceMpegbase_304882E1
#endif
#ifdef F_sceMpegbase_0006
	IMPORT_FUNC "sceMpegbase",0x7AC0321A,sceMpegBaseYCrCbCopy
#endif
#ifdef F_sceMpegbase_0007
	IMPORT_FUNC "sceMpegbase",0x91929A21,sceMpegBaseCscAvc
#endif
#ifdef F_sceMpegbase_0008
	IMPORT_FUNC "sceMpegbase",0xAC9E717E,sceMpegbase_AC9E717E
#endif
#ifdef F_sceMpegbase_0009
	IMPORT_FUNC "sceMpegbase",0xBEA18F91,sceMpegbase_BEA18F91
#endif
