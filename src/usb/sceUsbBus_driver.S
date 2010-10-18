	.set noreorder

#include "pspimport.s"

#ifdef F_sceUsbBus_driver_0000
	IMPORT_START	"sceUsbBus_driver",0x00010000
#endif
#ifdef F_sceUsbBus_driver_0001
	IMPORT_FUNC	"sceUsbBus_driver",0xC21645A4,sceUsbGetState
#endif
#ifdef F_sceUsbBus_driver_0002
	IMPORT_FUNC	"sceUsbBus_driver",0xB1644BE7,sceUsbbdRegister
#endif
#ifdef F_sceUsbBus_driver_0003
	IMPORT_FUNC	"sceUsbBus_driver",0xC1E2A540,sceUsbbdUnregister
#endif
#ifdef F_sceUsbBus_driver_0004
	IMPORT_FUNC	"sceUsbBus_driver",0x951A24CC,sceUsbbdClearFIFO
#endif
#ifdef F_sceUsbBus_driver_0005
	IMPORT_FUNC	"sceUsbBus_driver",0xE65441C1,sceUsbbdStall
#endif
#ifdef F_sceUsbBus_driver_0006
	IMPORT_FUNC	"sceUsbBus_driver",0x23E51D8F,sceUsbbdReqSend
#endif
#ifdef F_sceUsbBus_driver_0007
	IMPORT_FUNC	"sceUsbBus_driver",0x913EC15D,sceUsbbdReqRecv
#endif
#ifdef F_sceUsbBus_driver_0008
	IMPORT_FUNC	"sceUsbBus_driver",0xCC57EC9D,sceUsbbdReqCancel
#endif
#ifdef F_sceUsbBus_driver_0009
	IMPORT_FUNC	"sceUsbBus_driver",0xC5E53685,sceUsbbdReqCancelAll
#endif
