	.set noreorder

#include "pspimport.s"

#ifdef F_sceNand_driver_0000
	IMPORT_START	"sceNand_driver",0x00010011
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
	IMPORT_FUNC	"sceNand_driver",0xE05AE88D,sceNandReadPagesRawExtra
#endif
#ifdef F_sceNand_driver_0014
	IMPORT_FUNC	"sceNand_driver",0x8932166A,sceNandWritePagesRawExtra
#endif
#ifdef F_sceNand_driver_0015
	IMPORT_FUNC	"sceNand_driver",0xC478C1DE,sceNandReadPagesRawAll
#endif
#ifdef F_sceNand_driver_0016
	IMPORT_FUNC	"sceNand_driver",0xBADD5D46,sceNandWritePagesRawAll
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
	IMPORT_FUNC	"sceNand_driver",0xD897C343,sceNandDetectChip
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
	IMPORT_FUNC	"sceNand_driver",0xC29DA136,sceNandDoMarkAsBadBlock
#endif
#ifdef F_sceNand_driver_0035
	IMPORT_FUNC	"sceNand_driver",0x3F76BC21,sceNandDumpWearBBMSize
#endif
#ifdef F_sceNand_driver_0036
	IMPORT_FUNC	"sceNand_driver",0xEBA0E6C6,sceNandCountChipMakersBBM
#endif
#ifdef F_sceNand_driver_0037
	IMPORT_FUNC	"sceNand_driver",0x2FF6081B,sceNandDetectChipMakersBBM
#endif
#ifdef F_sceNand_driver_0038
	IMPORT_FUNC	"sceNand_driver",0x2674CFFE,sceNandEraseAllBlock
#endif
#ifdef F_sceNand_driver_0039
	IMPORT_FUNC	"sceNand_driver",0x9B2AC433,sceNandTestBlock
#endif
#ifdef F_sceNand_driver_0040
	IMPORT_FUNC	"sceNand_driver",0x0BEE8F36,sceNand_driver_0BEE8F36
#endif
#ifdef F_sceNand_driver_0041
	IMPORT_FUNC	"sceNand_driver",0x88CC9F72,sceNandCorrectEcc
#endif
