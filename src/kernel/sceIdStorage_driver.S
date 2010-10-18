	.set noreorder

#include "pspimport.s"

#ifdef F_sceIdStorage_driver_0000
	IMPORT_START	"sceIdStorage_driver",0x00010000
#endif
#ifdef F_sceIdStorage_driver_0001
	IMPORT_FUNC	"sceIdStorage_driver",0xAB129D20,sceIdStorageInit
#endif
#ifdef F_sceIdStorage_driver_0002
	IMPORT_FUNC	"sceIdStorage_driver",0x2CE0BE69,sceIdStorageEnd
#endif
#ifdef F_sceIdStorage_driver_0003
	IMPORT_FUNC	"sceIdStorage_driver",0xF77565B6,sceIdStorageSuspend
#endif
#ifdef F_sceIdStorage_driver_0004
	IMPORT_FUNC	"sceIdStorage_driver",0xFE51173D,sceIdStorageResume
#endif
#ifdef F_sceIdStorage_driver_0005
	IMPORT_FUNC	"sceIdStorage_driver",0xEB830733,sceIdStorageGetLeafSize
#endif
#ifdef F_sceIdStorage_driver_0006
	IMPORT_FUNC	"sceIdStorage_driver",0xFEFA40C2,sceIdStorageIsFormatted
#endif
#ifdef F_sceIdStorage_driver_0007
	IMPORT_FUNC	"sceIdStorage_driver",0x2D633688,sceIdStorageIsReadOnly
#endif
#ifdef F_sceIdStorage_driver_0008
	IMPORT_FUNC	"sceIdStorage_driver",0xB9069BAD,sceIdStorageIsDirty
#endif
#ifdef F_sceIdStorage_driver_0009
	IMPORT_FUNC	"sceIdStorage_driver",0x958089DB,sceIdStorageFormat
#endif
#ifdef F_sceIdStorage_driver_0010
	IMPORT_FUNC	"sceIdStorage_driver",0xF4BCB3EE,sceIdStorageUnformat
#endif
#ifdef F_sceIdStorage_driver_0011
	IMPORT_FUNC	"sceIdStorage_driver",0xEB00C509,sceIdStorageReadLeaf
#endif
#ifdef F_sceIdStorage_driver_0012
	IMPORT_FUNC	"sceIdStorage_driver",0x1FA4D135,sceIdStorageWriteLeaf
#endif
#ifdef F_sceIdStorage_driver_0013
	IMPORT_FUNC	"sceIdStorage_driver",0x08A471A6,sceIdStorageCreateLeaf
#endif
#ifdef F_sceIdStorage_driver_0014
	IMPORT_FUNC	"sceIdStorage_driver",0x2C97AB36,sceIdStorageDeleteLeaf
#endif
#ifdef F_sceIdStorage_driver_0015
	IMPORT_FUNC	"sceIdStorage_driver",0x99ACCB71,sceIdStorage_driver_99ACCB71
#endif
#ifdef F_sceIdStorage_driver_0016
	IMPORT_FUNC	"sceIdStorage_driver",0x37833CB8,sceIdStorage_driver_37833CB8
#endif
#ifdef F_sceIdStorage_driver_0017
	IMPORT_FUNC	"sceIdStorage_driver",0x31E08AFB,sceIdStorageEnumId
#endif
#ifdef F_sceIdStorage_driver_0018
	IMPORT_FUNC	"sceIdStorage_driver",0x6FE062D1,sceIdStorageLookup
#endif
#ifdef F_sceIdStorage_driver_0019
	IMPORT_FUNC	"sceIdStorage_driver",0x683AAC10,sceIdStorageUpdate
#endif
#ifdef F_sceIdStorage_driver_0020
	IMPORT_FUNC	"sceIdStorage_driver",0x3AD32523,sceIdStorageFlush
#endif
