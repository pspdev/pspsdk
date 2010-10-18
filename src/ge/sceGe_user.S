	.set noreorder

#include "pspimport.s"

#ifdef F_sceGe_user_0000
	IMPORT_START	"sceGe_user",0x40010000
#endif
#ifdef F_sceGe_user_0001
	IMPORT_FUNC	"sceGe_user",0x1F6752AD,sceGeEdramGetSize
#endif
#ifdef F_sceGe_user_0002
	IMPORT_FUNC	"sceGe_user",0xE47E40E4,sceGeEdramGetAddr
#endif
#ifdef F_sceGe_user_0003
	IMPORT_FUNC	"sceGe_user",0xB77905EA,sceGeEdramSetAddrTranslation
#endif
#ifdef F_sceGe_user_0004
	IMPORT_FUNC	"sceGe_user",0xDC93CFEF,sceGeGetCmd
#endif
#ifdef F_sceGe_user_0005
	IMPORT_FUNC	"sceGe_user",0x57C8945B,sceGeGetMtx
#endif
#ifdef F_sceGe_user_0006
	IMPORT_FUNC	"sceGe_user",0x438A385A,sceGeSaveContext
#endif
#ifdef F_sceGe_user_0007
	IMPORT_FUNC	"sceGe_user",0x0BF608FB,sceGeRestoreContext
#endif
#ifdef F_sceGe_user_0008
	IMPORT_FUNC	"sceGe_user",0xAB49E76A,sceGeListEnQueue
#endif
#ifdef F_sceGe_user_0009
	IMPORT_FUNC	"sceGe_user",0x1C0D95A6,sceGeListEnQueueHead
#endif
#ifdef F_sceGe_user_0010
	IMPORT_FUNC	"sceGe_user",0x5FB86AB0,sceGeListDeQueue
#endif
#ifdef F_sceGe_user_0011
	IMPORT_FUNC	"sceGe_user",0xE0D68148,sceGeListUpdateStallAddr
#endif
#ifdef F_sceGe_user_0012
	IMPORT_FUNC	"sceGe_user",0x03444EB4,sceGeListSync
#endif
#ifdef F_sceGe_user_0013
	IMPORT_FUNC	"sceGe_user",0xB287BD61,sceGeDrawSync
#endif
#ifdef F_sceGe_user_0014
	IMPORT_FUNC	"sceGe_user",0xB448EC0D,sceGeBreak
#endif
#ifdef F_sceGe_user_0015
	IMPORT_FUNC	"sceGe_user",0x4C06E472,sceGeContinue
#endif
#ifdef F_sceGe_user_0016
	IMPORT_FUNC	"sceGe_user",0xA4FC06A4,sceGeSetCallback
#endif
#ifdef F_sceGe_user_0017
	IMPORT_FUNC	"sceGe_user",0x05DB22CE,sceGeUnsetCallback
#endif
