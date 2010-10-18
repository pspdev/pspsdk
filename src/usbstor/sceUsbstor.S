	.set noreorder

#include "pspimport.s"

#ifdef F_sceUsbstor_0000
	IMPORT_START	"sceUsbstor",0x40090000
#endif
#ifdef F_sceUsbstor_0001
	IMPORT_FUNC	"sceUsbstor",0x60066CFE,sceUsbstorGetStatus
#endif
