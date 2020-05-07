	.set noreorder

#include "pspimport.s"

#ifdef F_sceAudioRouting_driver_0000
	IMPORT_START	"sceAudioRouting_driver",0x00010000
#endif
#ifdef F_sceAudioRouting_driver_0001
	IMPORT_FUNC	"sceAudioRouting_driver",0x28235C56,sceAudioRoutingGetVolumeMode
#endif
#ifdef F_sceAudioRouting_driver_0002
	IMPORT_FUNC	"sceAudioRouting_driver",0x36FD8AA9,sceAudioRoutingSetMode
#endif
#ifdef F_sceAudioRouting_driver_0003
	IMPORT_FUNC	"sceAudioRouting_driver",0x39240E7D,sceAudioRoutingGetMode
#endif
#ifdef F_sceAudioRouting_driver_0004
	IMPORT_FUNC	"sceAudioRouting_driver",0xBB548475,sceAudioRoutingSetVolumeMode
#endif
