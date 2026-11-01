	.set noreorder

#include "pspimport.s"

#ifdef F_sceUsbAcc_internal_0000
	IMPORT_START	"sceUsbAcc_internal",0x00090000
#endif
#ifdef F_sceUsbAcc_internal_0001
	IMPORT_FUNC	"sceUsbAcc_internal",0x0CD7D4AA,sceUsbAccGetInfo
#endif
#ifdef F_sceUsbAcc_internal_0002
	IMPORT_FUNC	"sceUsbAcc_internal",0x18B04C82,sceUsbAccUnregisterType
#endif
#ifdef F_sceUsbAcc_internal_0003
	IMPORT_FUNC	"sceUsbAcc_internal",0x2A100C1F,sceUsbAccIntrInReq
#endif
#ifdef F_sceUsbAcc_internal_0004
	IMPORT_FUNC	"sceUsbAcc_internal",0x2E251404,sceUsbAccRegisterType
#endif
#ifdef F_sceUsbAcc_internal_0005
	IMPORT_FUNC	"sceUsbAcc_internal",0x79A1C743,sceUsbAccGetAuthStat
#endif
