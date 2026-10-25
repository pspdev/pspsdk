	.set noreorder

#include "pspimport.s"

#ifdef F_sceUsbAcc_0000
	IMPORT_START	"sceUsbAcc",0x40090000
#endif
#ifdef F_sceUsbAcc_0001
	IMPORT_FUNC	"sceUsbAcc",0x0CD7D4AA,sceUsbAccGetInfo
#endif
#ifdef F_sceUsbAcc_0002
	IMPORT_FUNC	"sceUsbAcc",0x79A1C743,sceUsbAccGetAuthStat
#endif
