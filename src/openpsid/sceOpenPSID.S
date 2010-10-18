	.set noreorder

#include "pspimport.s"

// Build List
// sceOpenPSID_0000.o sceOpenPSID_0001.o 

#ifdef F_sceOpenPSID_0000
	IMPORT_START	"sceOpenPSID",0x40010011
#endif
#ifdef F_sceOpenPSID_0001
	IMPORT_FUNC	"sceOpenPSID",0xC69BEBCE,sceOpenPSIDGetOpenPSID
#endif
