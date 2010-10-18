	.set noreorder

#include "pspimport.s"

#ifdef F_sceMpegbase_driver_0000
	IMPORT_START	"sceMpegbase_driver",0x00010000
#endif
#ifdef F_sceMpegbase_driver_0001
	IMPORT_FUNC	"sceMpegbase_driver",0xBE45C284,sceMpegBaseYCrCbCopyVme
#endif
#ifdef F_sceMpegbase_driver_0002
	IMPORT_FUNC	"sceMpegbase_driver",0x492B5E4B,sceMpegBaseCscInit
#endif
#ifdef F_sceMpegbase_driver_0003
	IMPORT_FUNC	"sceMpegbase_driver",0xCE8EB837,sceMpegBaseCscVme
#endif
#ifdef F_sceMpegbase_driver_0004
	IMPORT_FUNC "sceMpegbase_driver",0x0530BE4E,sceMpegbase_driver_0530BE4E
#endif
#ifdef F_sceMpegbase_driver_0005
	IMPORT_FUNC "sceMpegbase_driver",0x304882E1,sceMpegbase_driver_304882E1
#endif
#ifdef F_sceMpegbase_driver_0006
	IMPORT_FUNC "sceMpegbase_driver",0x7AC0321A,sceMpegBaseYCrCbCopy
#endif
#ifdef F_sceMpegbase_driver_0007
	IMPORT_FUNC "sceMpegbase_driver",0x91929A21,sceMpegBaseCscAvc
#endif
#ifdef F_sceMpegbase_driver_0008
	IMPORT_FUNC "sceMpegbase_driver",0xAC9E717E,sceMpegbase_driver_AC9E717E
#endif
#ifdef F_sceMpegbase_driver_0009
	IMPORT_FUNC "sceMpegbase_driver",0xBEA18F91,sceMpegbase_BEA18F91
#endif
#ifdef F_sceMpegbase_driver_0010
	IMPORT_FUNC "sceMpegbase_driver",0x27A2982F,sceMpegBaseInit
#endif
