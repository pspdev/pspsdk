	.set noreorder

#include "pspimport.s"

#ifdef F_sceKermitMemory_driver_0000
	IMPORT_START "sceKermitMemory_driver",0x00010000
#endif
#ifdef F_sceKermitMemory_driver_0001
	IMPORT_FUNC	"sceKermitMemory_driver",0x80E1240A,sceKermitMemory_driver_80E1240A
#endif
#ifdef F_sceKermitMemory_driver_0002
	IMPORT_FUNC	"sceKermitMemory_driver",0x90B662D0,sceKermitMemory_driver_90B662D0
#endif
#ifdef F_sceKermitMemory_driver_0003
	IMPORT_FUNC	"sceKermitMemory_driver",0xAAF047AC,sceKermitMemorySetArgument
#endif
