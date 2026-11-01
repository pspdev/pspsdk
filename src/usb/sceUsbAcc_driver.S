	.set noreorder

#include "pspimport.s"

#ifdef F_sceUsbAcc_driver_0000
	IMPORT_START	"sceUsbAcc_driver",0x00090000
#endif
#ifdef F_sceUsbAcc_driver_0001
	IMPORT_FUNC	"sceUsbAcc_driver",0x0CD7D4AA,sceUsbAccGetInfo
#endif
#ifdef F_sceUsbAcc_driver_0002
	IMPORT_FUNC	"sceUsbAcc_driver",0x79A1C743,sceUsbAccGetAuthStat
#endif
