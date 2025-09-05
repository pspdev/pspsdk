	.set noreorder

#include "pspimport.s"

#ifdef F_sceKermitPeripheral_0000
	IMPORT_START	"sceKermitPeripheral",0x40090000
#endif
#ifdef F_sceKermitPeripheral_0001
	IMPORT_FUNC	"sceKermitPeripheral",0x4A26B7C8,sceKermitPeripheral_4A26B7C8
#endif
#ifdef F_sceKermitPeripheral_0002
	IMPORT_FUNC	"sceKermitPeripheral",0xC0EBC631,sceKermitPeripheral_C0EBC631
#endif
#ifdef F_sceKermitPeripheral_0003
	IMPORT_FUNC	"sceKermitPeripheral",0xD27C5E03,sceKermitPeripheral_D27C5E03
#endif
