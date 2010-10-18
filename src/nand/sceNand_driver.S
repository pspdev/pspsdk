	.set noreorder

#include "pspimport.s"

#ifdef F_sceNand_driver_0000
	IMPORT_START	"sceNand_driver",0x00010000
#endif
#ifdef F_sceNand_driver_0001
	IMPORT_FUNC	"sceNand_driver",0xA513BB12,sceNandInit
#endif
#ifdef F_sceNand_driver_0002
	IMPORT_FUNC	"sceNand_driver",0xD305870E,sceNandEnd
#endif
#ifdef F_sceNand_driver_0003
	IMPORT_FUNC	"sceNand_driver",0x73A68408,sceNandSuspend
#endif
#ifdef F_sceNand_driver_0004
	IMPORT_FUNC	"sceNand_driver",0x0F9BBBBD,sceNandResume
#endif
#ifdef F_sceNand_driver_0005
	IMPORT_FUNC	"sceNand_driver",0x84EE5D76,sceNandSetWriteProtect
#endif
#ifdef F_sceNand_driver_0006
	IMPORT_FUNC	"sceNand_driver",0xAE4438C7,sceNandLock
#endif
#ifdef F_sceNand_driver_0007
	IMPORT_FUNC	"sceNand_driver",0x41FFA822,sceNandUnlock
#endif
#ifdef F_sceNand_driver_0008
	IMPORT_FUNC	"sceNand_driver",0xE41A11DE,sceNandReadStatus
#endif
#ifdef F_sceNand_driver_0009
	IMPORT_FUNC	"sceNand_driver",0x7AF7B77A,sceNandReset
#endif
#ifdef F_sceNand_driver_0010
	IMPORT_FUNC	"sceNand_driver",0xFCDF7610,sceNandReadId
#endif
#ifdef F_sceNand_driver_0011
	IMPORT_FUNC	"sceNand_driver",0x89BDCA08,sceNandReadPages
#endif
#ifdef F_sceNand_driver_0012
	IMPORT_FUNC	"sceNand_driver",0x8AF0AB9F,sceNandWritePages
#endif
#ifdef F_sceNand_driver_0013
	IMPORT_FUNC	"sceNand_driver",0xE05AE88D,sceNand_driver_E05AE88D
#endif
#ifdef F_sceNand_driver_0014
	IMPORT_FUNC	"sceNand_driver",0x8932166A,sceNand_driver_8932166A
#endif
#ifdef F_sceNand_driver_0015
	IMPORT_FUNC	"sceNand_driver",0xC478C1DE,sceNand_driver_C478C1DE
#endif
#ifdef F_sceNand_driver_0016
	IMPORT_FUNC	"sceNand_driver",0xBADD5D46,sceNand_driver_BADD5D46
#endif
#ifdef F_sceNand_driver_0017
	IMPORT_FUNC	"sceNand_driver",0x766756EF,sceNandReadAccess
#endif
#ifdef F_sceNand_driver_0018
	IMPORT_FUNC	"sceNand_driver",0x0ADC8686,sceNandWriteAccess
#endif
#ifdef F_sceNand_driver_0019
	IMPORT_FUNC	"sceNand_driver",0xEB0A0022,sceNandEraseBlock
#endif
#ifdef F_sceNand_driver_0020
	IMPORT_FUNC	"sceNand_driver",0x5182C394,sceNandReadExtraOnly
#endif
#ifdef F_sceNand_driver_0021
	IMPORT_FUNC	"sceNand_driver",0xEF55F193,sceNandCalcEcc
#endif
#ifdef F_sceNand_driver_0022
	IMPORT_FUNC	"sceNand_driver",0x18B78661,sceNandVerifyEcc
#endif
#ifdef F_sceNand_driver_0023
	IMPORT_FUNC	"sceNand_driver",0xB795D2ED,sceNandCollectEcc
#endif
#ifdef F_sceNand_driver_0024
	IMPORT_FUNC	"sceNand_driver",0xD897C343,sceNand_driver_D897C343
#endif
#ifdef F_sceNand_driver_0025
	IMPORT_FUNC	"sceNand_driver",0xCE9843E6,sceNandGetPageSize
#endif
#ifdef F_sceNand_driver_0026
	IMPORT_FUNC	"sceNand_driver",0xB07C41D4,sceNandGetPagesPerBlock
#endif
#ifdef F_sceNand_driver_0027
	IMPORT_FUNC	"sceNand_driver",0xC1376222,sceNandGetTotalBlocks
#endif
#ifdef F_sceNand_driver_0028
	IMPORT_FUNC	"sceNand_driver",0x716CD2B2,sceNandWriteBlock
#endif
#ifdef F_sceNand_driver_0029
	IMPORT_FUNC	"sceNand_driver",0xB2B021E5,sceNandWriteBlockWithVerify
#endif
#ifdef F_sceNand_driver_0030
	IMPORT_FUNC	"sceNand_driver",0xC32EA051,sceNandReadBlockWithRetry
#endif
#ifdef F_sceNand_driver_0031
	IMPORT_FUNC	"sceNand_driver",0x5AC02755,sceNandVerifyBlockWithRetry
#endif
#ifdef F_sceNand_driver_0032
	IMPORT_FUNC	"sceNand_driver",0x8933B2E0,sceNandEraseBlockWithRetry
#endif
#ifdef F_sceNand_driver_0033
	IMPORT_FUNC	"sceNand_driver",0x01F09203,sceNandIsBadBlock
#endif
#ifdef F_sceNand_driver_0034
	IMPORT_FUNC	"sceNand_driver",0xC29DA136,sceNand_driver_C29DA136
#endif
#ifdef F_sceNand_driver_0035
	IMPORT_FUNC	"sceNand_driver",0x3F76BC21,sceNand_driver_3F76BC21
#endif
#ifdef F_sceNand_driver_0036
	IMPORT_FUNC	"sceNand_driver",0xEBA0E6C6,sceNand_driver_EBA0E6C6
#endif
#ifdef F_sceNand_driver_0037
	IMPORT_FUNC	"sceNand_driver",0x2FF6081B,sceNand_driver_2FF6081B
#endif
#ifdef F_sceNand_driver_0038
	IMPORT_FUNC	"sceNand_driver",0x2674CFFE,sceNandEraseAllBlock
#endif
#ifdef F_sceNand_driver_0039
	IMPORT_FUNC	"sceNand_driver",0x9B2AC433,sceNandTestBlock
#endif
