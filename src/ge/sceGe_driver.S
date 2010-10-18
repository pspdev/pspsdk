	.set noreorder

#include "pspimport.s"

#ifdef F_sceGe_driver_0000
	IMPORT_START	"sceGe_driver",0x00010000
#endif
#ifdef F_sceGe_driver_0001
	IMPORT_FUNC	"sceGe_driver",0x71FCD1D6,sceGeInit
#endif
#ifdef F_sceGe_driver_0002
	IMPORT_FUNC	"sceGe_driver",0x9F2C2948,sceGeEnd
#endif
#ifdef F_sceGe_driver_0003
	IMPORT_FUNC	"sceGe_driver",0x8F185DF7,sceGeEdramInit
#endif
#ifdef F_sceGe_driver_0004
	IMPORT_FUNC	"sceGe_driver",0x1F6752AD,sceGeEdramGetSize
#endif
#ifdef F_sceGe_driver_0005
	IMPORT_FUNC	"sceGe_driver",0xE47E40E4,sceGeEdramGetAddr
#endif
#ifdef F_sceGe_driver_0006
	IMPORT_FUNC	"sceGe_driver",0xB77905EA,sceGeEdramSetAddrTranslation
#endif
#ifdef F_sceGe_driver_0007
	IMPORT_FUNC	"sceGe_driver",0xB415364D,sceGeGetReg
#endif
#ifdef F_sceGe_driver_0008
	IMPORT_FUNC	"sceGe_driver",0xDC93CFEF,sceGeGetCmd
#endif
#ifdef F_sceGe_driver_0009
	IMPORT_FUNC	"sceGe_driver",0x57C8945B,sceGeGetMtx
#endif
#ifdef F_sceGe_driver_0010
	IMPORT_FUNC	"sceGe_driver",0x438A385A,sceGeSaveContext
#endif
#ifdef F_sceGe_driver_0011
	IMPORT_FUNC	"sceGe_driver",0x0BF608FB,sceGeRestoreContext
#endif
#ifdef F_sceGe_driver_0012
	IMPORT_FUNC	"sceGe_driver",0xAB49E76A,sceGeListEnQueue
#endif
#ifdef F_sceGe_driver_0013
	IMPORT_FUNC	"sceGe_driver",0x1C0D95A6,sceGeListEnQueueHead
#endif
#ifdef F_sceGe_driver_0014
	IMPORT_FUNC	"sceGe_driver",0x5FB86AB0,sceGeListDeQueue
#endif
#ifdef F_sceGe_driver_0015
	IMPORT_FUNC	"sceGe_driver",0xE0D68148,sceGeListUpdateStallAddr
#endif
#ifdef F_sceGe_driver_0016
	IMPORT_FUNC	"sceGe_driver",0x03444EB4,sceGeListSync
#endif
#ifdef F_sceGe_driver_0017
	IMPORT_FUNC	"sceGe_driver",0xB287BD61,sceGeDrawSync
#endif
#ifdef F_sceGe_driver_0018
	IMPORT_FUNC	"sceGe_driver",0xB448EC0D,sceGeBreak
#endif
#ifdef F_sceGe_driver_0019
	IMPORT_FUNC	"sceGe_driver",0x4C06E472,sceGeContinue
#endif
#ifdef F_sceGe_driver_0020
	IMPORT_FUNC	"sceGe_driver",0xA4FC06A4,sceGeSetCallback
#endif
#ifdef F_sceGe_driver_0021
	IMPORT_FUNC	"sceGe_driver",0x05DB22CE,sceGeUnsetCallback
#endif
#ifdef F_sceGe_driver_0022
	IMPORT_FUNC	"sceGe_driver",0x9DA4A75F,sceGe_driver_9DA4A75F
#endif
#ifdef F_sceGe_driver_0023
	IMPORT_FUNC	"sceGe_driver",0x114E1745,sceGe_driver_114E1745
#endif
