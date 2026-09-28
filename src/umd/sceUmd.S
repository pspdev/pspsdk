	.set noreorder

#include "pspimport.s"

#ifdef F_sceUmd_0000
	IMPORT_START	"sceUmd",0x00090000
#endif
#ifdef F_sceUmd_0001
	IMPORT_FUNC	"sceUmd",0x075F1E0B,sceUmdSetDetectUMDCallBackId
#endif
#ifdef F_sceUmd_0002
	IMPORT_FUNC	"sceUmd",0x086DDC0D,sceUmdRegisterActivateCallBack
#endif
#ifdef F_sceUmd_0003
	IMPORT_FUNC	"sceUmd",0x230666E3,sceUmdSetDriveStatus
#endif
#ifdef F_sceUmd_0004
	IMPORT_FUNC	"sceUmd",0x27A764A1,sceUmdUnRegisterGetUMDInfoCallBack
#endif
#ifdef F_sceUmd_0005
	IMPORT_FUNC	"sceUmd",0x2D81508D,sceUmdRegisterDeactivateCallBack
#endif
#ifdef F_sceUmd_0006
	IMPORT_FUNC	"sceUmd",0x319ED97C,sceUmdUnRegisterActivateCallBack
#endif
#ifdef F_sceUmd_0007
	IMPORT_FUNC	"sceUmd",0x340B7686,sceUmdGetDiscInfo
#endif
#ifdef F_sceUmd_0008
	IMPORT_FUNC	"sceUmd",0x3925CBD8,sceUmdSetAssignedFlag
#endif
#ifdef F_sceUmd_0009
	IMPORT_FUNC	"sceUmd",0x3D0DECD5,sceUmdGetUserEventFlagId
#endif
#ifdef F_sceUmd_0010
	IMPORT_FUNC	"sceUmd",0x46EBB729,sceUmdCheckMedium
#endif
#ifdef F_sceUmd_0011
	IMPORT_FUNC	"sceUmd",0x4832ABF3,sceUmdRegisterReplaceCallBack
#endif
#ifdef F_sceUmd_0012
	IMPORT_FUNC	"sceUmd",0x4A9E5E29,sceUmdWaitDriveStatCB
#endif
#ifdef F_sceUmd_0013
	IMPORT_FUNC	"sceUmd",0x4BA25F4A,sceUmdUnRegisterReplaceCallBack
#endif
#ifdef F_sceUmd_0014
	IMPORT_FUNC	"sceUmd",0x4C952ACF,sceUmdSetSuspendResumeMode
#endif
#ifdef F_sceUmd_0015
	IMPORT_FUNC	"sceUmd",0x5469DC37,sceUmdUnRegisterMediaPresentCallBack
#endif
#ifdef F_sceUmd_0016
	IMPORT_FUNC	"sceUmd",0x56202973,sceUmdWaitDriveStatWithTimer
#endif
#ifdef F_sceUmd_0017
	IMPORT_FUNC	"sceUmd",0x659587F7,sceUmd_659587F7
#endif
#ifdef F_sceUmd_0018
	IMPORT_FUNC	"sceUmd",0x6A41ED25,sceUmdGetSuspendResumeMode
#endif
#ifdef F_sceUmd_0019
	IMPORT_FUNC	"sceUmd",0x6AF9B50A,sceUmd_6AF9B50A
#endif
#ifdef F_sceUmd_0020
	IMPORT_FUNC	"sceUmd",0x71F81482,sceUmdGetErrorStatus
#endif
#ifdef F_sceUmd_0021
	IMPORT_FUNC	"sceUmd",0x7850F057,sceUmdRegisterGetUMDInfoCallBack
#endif
#ifdef F_sceUmd_0022
	IMPORT_FUNC	"sceUmd",0x87533940,sceUmdReplaceProhibit
#endif
#ifdef F_sceUmd_0023
	IMPORT_FUNC	"sceUmd",0x8EF08FCE,sceUmdWaitDriveStat
#endif
#ifdef F_sceUmd_0024
	IMPORT_FUNC	"sceUmd",0x9B22AED7,sceUmdSetErrorStatus
#endif
#ifdef F_sceUmd_0025
	IMPORT_FUNC	"sceUmd",0xAE53DC2D,sceUmdClearDriveStatus
#endif
#ifdef F_sceUmd_0026
	IMPORT_FUNC	"sceUmd",0xAEE7404D,sceUmdRegisterUMDCallBack
#endif
#ifdef F_sceUmd_0027
	IMPORT_FUNC	"sceUmd",0xBBB5F05C,sceUmdUnRegisterDeactivateCallBack
#endif
#ifdef F_sceUmd_0028
	IMPORT_FUNC	"sceUmd",0xBD2BDE07,sceUmdUnRegisterUMDCallBack
#endif
#ifdef F_sceUmd_0029
	IMPORT_FUNC	"sceUmd",0xC6183D47,sceUmdActivate
#endif
#ifdef F_sceUmd_0030
	IMPORT_FUNC	"sceUmd",0xCBE9F02A,sceUmdReplacePermit
#endif
#ifdef F_sceUmd_0031
	IMPORT_FUNC	"sceUmd",0xD01B2DC6,sceUmdGetAssignedFlag
#endif
#ifdef F_sceUmd_0032
	IMPORT_FUNC	"sceUmd",0xD45D1FE6,sceUmdGetDriveStatus
#endif
#ifdef F_sceUmd_0033
	IMPORT_FUNC	"sceUmd",0xE83742BA,sceUmdDeactivate
#endif
#ifdef F_sceUmd_0034
	IMPORT_FUNC	"sceUmd",0xEB56097E,sceUmdGetDetectUMDCallBackId
#endif
#ifdef F_sceUmd_0035
	IMPORT_FUNC	"sceUmd",0xF8352373,sceUmdRegisterMediaPresentCallBack
#endif
