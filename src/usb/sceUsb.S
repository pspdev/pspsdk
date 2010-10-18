	.set noreorder

#include "pspimport.s"

#ifdef F_sceUsb_0000
	IMPORT_START	"sceUsb",0x40010000
#endif
#ifdef F_sceUsb_0001
	IMPORT_FUNC	"sceUsb",0xAE5DE6AF,sceUsbStart
#endif
#ifdef F_sceUsb_0002
	IMPORT_FUNC	"sceUsb",0xC2464FA0,sceUsbStop
#endif
#ifdef F_sceUsb_0003
	IMPORT_FUNC	"sceUsb",0xC21645A4,sceUsbGetState
#endif
#ifdef F_sceUsb_0004
	IMPORT_FUNC	"sceUsb",0x4E537366,sceUsbGetDrvList
#endif
#ifdef F_sceUsb_0005
	IMPORT_FUNC	"sceUsb",0x112CC951,sceUsbGetDrvState
#endif
#ifdef F_sceUsb_0006
	IMPORT_FUNC	"sceUsb",0x586DB82C,sceUsbActivate
#endif
#ifdef F_sceUsb_0007
	IMPORT_FUNC	"sceUsb",0xC572A9C8,sceUsbDeactivate
#endif
#ifdef F_sceUsb_0008
	IMPORT_FUNC	"sceUsb",0x5BE0E002,sceUsbWaitState
#endif
#ifdef F_sceUsb_0009
	IMPORT_FUNC	"sceUsb",0x1C360735,sceUsbWaitCancel
#endif
