	.set noreorder

#include "pspimport.s"

#ifdef F_sceWlanDrv_lib_0000
	IMPORT_START	"sceWlanDrv_lib",0x40010000
#endif
#ifdef F_sceWlanDrv_lib_0001
	IMPORT_FUNC	"sceWlanDrv_lib",0x482CAE9A,sceWlanDevAttach
#endif
#ifdef F_sceWlanDrv_lib_0002
	IMPORT_FUNC	"sceWlanDrv_lib",0xC9A8CAB7,sceWlanDevDetach
#endif
#ifdef F_sceWlanDrv_lib_0003
	IMPORT_FUNC	"sceWlanDrv_lib",0x19E51F54,sceWlanDrv_lib_19E51F54
#endif
#ifdef F_sceWlanDrv_lib_0004
	IMPORT_FUNC	"sceWlanDrv_lib",0x5E7C8D94,sceWlanDevIsGameMode
#endif
#ifdef F_sceWlanDrv_lib_0005
	IMPORT_FUNC	"sceWlanDrv_lib",0x5ED4049A,sceWlanGPPrevEstablishActive
#endif
#ifdef F_sceWlanDrv_lib_0006
	IMPORT_FUNC	"sceWlanDrv_lib",0xB4D7CB74,sceWlanGPSend
#endif
#ifdef F_sceWlanDrv_lib_0007
	IMPORT_FUNC	"sceWlanDrv_lib",0xA447103A,sceWlanGPRecv
#endif
#ifdef F_sceWlanDrv_lib_0008
	IMPORT_FUNC	"sceWlanDrv_lib",0x9658C9F7,sceWlanGPRegisterCallback
#endif
#ifdef F_sceWlanDrv_lib_0009
	IMPORT_FUNC	"sceWlanDrv_lib",0x4C7F62E0,sceWlanGPUnRegisterCallback
#endif
#ifdef F_sceWlanDrv_lib_0010
	IMPORT_FUNC	"sceWlanDrv_lib",0x81579D36,sceWlanDrv_lib_81579D36
#endif
#ifdef F_sceWlanDrv_lib_0011
	IMPORT_FUNC	"sceWlanDrv_lib",0x5BAA1FE5,sceWlanDrv_lib_5BAA1FE5
#endif
#ifdef F_sceWlanDrv_lib_0012
	IMPORT_FUNC	"sceWlanDrv_lib",0x4C14BACA,sceWlanDrv_lib_4C14BACA
#endif
#ifdef F_sceWlanDrv_lib_0013
	IMPORT_FUNC	"sceWlanDrv_lib",0x2D0FAE4E,sceWlanDrv_lib_2D0FAE4E
#endif
#ifdef F_sceWlanDrv_lib_0014
	IMPORT_FUNC	"sceWlanDrv_lib",0x56F467CA,sceWlanDrv_lib_56F467CA
#endif
#ifdef F_sceWlanDrv_lib_0015
	IMPORT_FUNC	"sceWlanDrv_lib",0xFE8A0B46,sceWlanDrv_lib_FE8A0B46
#endif
#ifdef F_sceWlanDrv_lib_0016
	IMPORT_FUNC	"sceWlanDrv_lib",0x40B0AA4A,sceWlanDrv_lib_40B0AA4A
#endif
#ifdef F_sceWlanDrv_lib_0017
	IMPORT_FUNC	"sceWlanDrv_lib",0x7FF54BD2,sceWlanDevSetGPIO
#endif
#ifdef F_sceWlanDrv_lib_0018
	IMPORT_FUNC	"sceWlanDrv_lib",0x05FE320C,sceWlanDevGetStateGPIO
#endif
