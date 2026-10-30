	.set noreorder

#include "pspimport.s"

#ifdef F_sceUsbGps_driver_0000
	IMPORT_START	"sceUsbGps_driver",0x00090000
#endif
#ifdef F_sceUsbGps_driver_0001
	IMPORT_FUNC	"sceUsbGps_driver",0x268F95CA,sceUsbGpsSetInitDataLocation
#endif
#ifdef F_sceUsbGps_driver_0002
	IMPORT_FUNC	"sceUsbGps_driver",0x31F95CDE,sceUsbGpsGetPowerSaveMode
#endif
#ifdef F_sceUsbGps_driver_0003
	IMPORT_FUNC	"sceUsbGps_driver",0x54D26AA4,sceUsbGpsGetInitDataLocation
#endif
#ifdef F_sceUsbGps_driver_0004
	IMPORT_FUNC	"sceUsbGps_driver",0x5881C826,sceUsbGpsGetStaticNavMode
#endif
#ifdef F_sceUsbGps_driver_0005
	IMPORT_FUNC	"sceUsbGps_driver",0x69E4AAA8,sceUsbGpsSaveInitData
#endif
#ifdef F_sceUsbGps_driver_0006
	IMPORT_FUNC	"sceUsbGps_driver",0x6EED4811,sceUsbGpsClose
#endif
#ifdef F_sceUsbGps_driver_0007
	IMPORT_FUNC	"sceUsbGps_driver",0x7C16AC3A,sceUsbGpsGetState
#endif
#ifdef F_sceUsbGps_driver_0008
	IMPORT_FUNC	"sceUsbGps_driver",0x934EC2B2,sceUsbGpsGetData
#endif
#ifdef F_sceUsbGps_driver_0009
	IMPORT_FUNC	"sceUsbGps_driver",0x9D8F99E8,sceUsbGpsSetPowerSaveMode
#endif
#ifdef F_sceUsbGps_driver_0010
	IMPORT_FUNC	"sceUsbGps_driver",0x9F267D34,sceUsbGpsOpen
#endif
#ifdef F_sceUsbGps_driver_0011
	IMPORT_FUNC	"sceUsbGps_driver",0xA259CD67,sceUsbGpsReset
#endif
#ifdef F_sceUsbGps_driver_0012
	IMPORT_FUNC	"sceUsbGps_driver",0xA8ED0BC2,sceUsbGpsSetStaticNavMode
#endif
