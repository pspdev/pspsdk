	.set noreorder

#include "pspimport.s"

#ifdef F_sceKermit_driver_0000
	IMPORT_START "sceKermit_driver",0x00010000
#endif
#ifdef F_sceKermit_driver_0001
	IMPORT_FUNC	"sceKermit_driver",0x36666181,sceKermitSendRequest
#endif
#ifdef F_sceKermit_driver_0002
	IMPORT_FUNC	"sceKermit_driver",0x4C3A362D,sceKermit_driver_4C3A362D
#endif
#ifdef F_sceKermit_driver_0003
	IMPORT_FUNC	"sceKermit_driver",0x5280B410,sceKermitRegisterVirtualIntrHandler
#endif
#ifdef F_sceKermit_driver_0004
	IMPORT_FUNC	"sceKermit_driver",0x9DDD7DCA,sceKermit_driver_9DDD7DCA
#endif
#ifdef F_sceKermit_driver_0005
	IMPORT_FUNC	"sceKermit_driver",0xD69C50BB,sceKermit_driver_D69C50BB
#endif
