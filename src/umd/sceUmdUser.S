	.set noreorder

#include "pspimport.s"

// Build List
// sceUmdUser_0000.o sceUmdUser_0001.o sceUmdUser_0002.o sceUmdUser_0003.o sceUmdUser_0004.o sceUmdUser_0005.o sceUmdUser_0006.o sceUmdUser_0007.o sceUmdUser_0008.o sceUmdUser_0009.o sceUmdUser_0010.o sceUmdUser_0011.o sceUmdUser_0012.o sceUmdUser_0013.o sceUmdUser_0014.o 

#ifdef F_sceUmdUser_0000
	IMPORT_START	"sceUmdUser",0x40010011
#endif
#ifdef F_sceUmdUser_0001
	IMPORT_FUNC	"sceUmdUser",0x20628E6F,sceUmdGetErrorStat
#endif
#ifdef F_sceUmdUser_0002
	IMPORT_FUNC	"sceUmdUser",0x340B7686,sceUmdGetDiscInfo
#endif
#ifdef F_sceUmdUser_0003
	IMPORT_FUNC	"sceUmdUser",0x46EBB729,sceUmdCheckMedium
#endif
#ifdef F_sceUmdUser_0004
	IMPORT_FUNC	"sceUmdUser",0x4A9E5E29,sceUmdWaitDriveStatCB
#endif
#ifdef F_sceUmdUser_0005
	IMPORT_FUNC	"sceUmdUser",0x56202973,sceUmdWaitDriveStatWithTimer
#endif
#ifdef F_sceUmdUser_0006
	IMPORT_FUNC	"sceUmdUser",0x6AF9B50A,sceUmdCancelWaitDriveStat
#endif
#ifdef F_sceUmdUser_0007
	IMPORT_FUNC	"sceUmdUser",0x6B4A146C,sceUmdGetDriveStat
#endif
#ifdef F_sceUmdUser_0008
	IMPORT_FUNC	"sceUmdUser",0x87533940,sceUmdReplaceProhibit
#endif
#ifdef F_sceUmdUser_0009
	IMPORT_FUNC	"sceUmdUser",0x8EF08FCE,sceUmdWaitDriveStat
#endif
#ifdef F_sceUmdUser_0010
	IMPORT_FUNC	"sceUmdUser",0xAEE7404D,sceUmdRegisterUMDCallBack
#endif
#ifdef F_sceUmdUser_0011
	IMPORT_FUNC	"sceUmdUser",0xBD2BDE07,sceUmdUnRegisterUMDCallBack
#endif
#ifdef F_sceUmdUser_0012
	IMPORT_FUNC	"sceUmdUser",0xC6183D47,sceUmdActivate
#endif
#ifdef F_sceUmdUser_0013
	IMPORT_FUNC	"sceUmdUser",0xCBE9F02A,sceUmdReplacePermit
#endif
#ifdef F_sceUmdUser_0014
	IMPORT_FUNC	"sceUmdUser",0xE83742BA,sceUmdDeactivate
#endif
