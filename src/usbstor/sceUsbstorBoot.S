	.set noreorder

#include "pspimport.s"

#ifdef F_sceUsbstorBoot_0000
	IMPORT_START	"sceUsbstorBoot",0x40090000
#endif
#ifdef F_sceUsbstorBoot_0001
	IMPORT_FUNC	"sceUsbstorBoot",0xE58818A8,sceUsbstorBootSetCapacity
#endif
#ifdef F_sceUsbstorBoot_0002
	IMPORT_FUNC	"sceUsbstorBoot",0x594BBF95,sceUsbstorBootSetLoadAddr
#endif
#ifdef F_sceUsbstorBoot_0003
	IMPORT_FUNC	"sceUsbstorBoot",0x6D865ECD,sceUsbstorBootGetDataSize
#endif
#ifdef F_sceUsbstorBoot_0004
	IMPORT_FUNC	"sceUsbstorBoot",0xA1119F0D,sceUsbstorBootSetStatus
#endif
#ifdef F_sceUsbstorBoot_0005
	IMPORT_FUNC	"sceUsbstorBoot",0x1F080078,sceUsbstorBootRegisterNotify
#endif
#ifdef F_sceUsbstorBoot_0006
	IMPORT_FUNC	"sceUsbstorBoot",0xA55C9E16,sceUsbstorBootUnregisterNotify
#endif
