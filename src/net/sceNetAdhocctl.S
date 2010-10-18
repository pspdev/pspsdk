	.set noreorder

#include "pspimport.s"

#ifdef F_sceNetAdhocctl_0000
	IMPORT_START	"sceNetAdhocctl",0x00090000
#endif
#ifdef F_sceNetAdhocctl_0001
	IMPORT_FUNC	"sceNetAdhocctl",0xE26F226E,sceNetAdhocctlInit
#endif
#ifdef F_sceNetAdhocctl_0002
	IMPORT_FUNC	"sceNetAdhocctl",0x9D689E13,sceNetAdhocctlTerm
#endif
#ifdef F_sceNetAdhocctl_0003
	IMPORT_FUNC	"sceNetAdhocctl",0x0AD043ED,sceNetAdhocctlConnect
#endif
#ifdef F_sceNetAdhocctl_0004
	IMPORT_FUNC	"sceNetAdhocctl",0xEC0635C1,sceNetAdhocctlCreate
#endif
#ifdef F_sceNetAdhocctl_0005
	IMPORT_FUNC	"sceNetAdhocctl",0x5E7F79C9,sceNetAdhocctlJoin
#endif
#ifdef F_sceNetAdhocctl_0006
	IMPORT_FUNC	"sceNetAdhocctl",0x08FFF7A0,sceNetAdhocctlScan
#endif
#ifdef F_sceNetAdhocctl_0007
	IMPORT_FUNC	"sceNetAdhocctl",0x34401D65,sceNetAdhocctlDisconnect
#endif
#ifdef F_sceNetAdhocctl_0008
	IMPORT_FUNC	"sceNetAdhocctl",0x20B317A0,sceNetAdhocctlAddHandler
#endif
#ifdef F_sceNetAdhocctl_0009
	IMPORT_FUNC	"sceNetAdhocctl",0x6402490B,sceNetAdhocctlDelHandler
#endif
#ifdef F_sceNetAdhocctl_0010
	IMPORT_FUNC	"sceNetAdhocctl",0x75ECD386,sceNetAdhocctlGetState
#endif
#ifdef F_sceNetAdhocctl_0011
	IMPORT_FUNC	"sceNetAdhocctl",0x362CBE8F,sceNetAdhocctlGetAdhocId
#endif
#ifdef F_sceNetAdhocctl_0012
	IMPORT_FUNC	"sceNetAdhocctl",0xE162CB14,sceNetAdhocctlGetPeerList
#endif
#ifdef F_sceNetAdhocctl_0013
	IMPORT_FUNC	"sceNetAdhocctl",0x99560ABE,sceNetAdhocctlGetAddrByName
#endif
#ifdef F_sceNetAdhocctl_0014
	IMPORT_FUNC	"sceNetAdhocctl",0x8916C003,sceNetAdhocctlGetNameByAddr
#endif
#ifdef F_sceNetAdhocctl_0015
	IMPORT_FUNC	"sceNetAdhocctl",0xDED9D28E,sceNetAdhocctlGetParameter
#endif
#ifdef F_sceNetAdhocctl_0016
	IMPORT_FUNC	"sceNetAdhocctl",0x81AEE1BE,sceNetAdhocctlGetScanInfo
#endif
#ifdef F_sceNetAdhocctl_0017
	IMPORT_FUNC	"sceNetAdhocctl",0xA5C055CE,sceNetAdhocctlCreateEnterGameMode
#endif
#ifdef F_sceNetAdhocctl_0018
	IMPORT_FUNC	"sceNetAdhocctl",0x1FF89745,sceNetAdhocctlJoinEnterGameMode
#endif
#ifdef F_sceNetAdhocctl_0019
	IMPORT_FUNC	"sceNetAdhocctl",0xCF8E084D,sceNetAdhocctlExitGameMode
#endif
#ifdef F_sceNetAdhocctl_0020
	IMPORT_FUNC	"sceNetAdhocctl",0x5A014CE0,sceNetAdhocctlGetGameModeInfo
#endif
#ifdef F_sceNetAdhocctl_0021
	IMPORT_FUNC	"sceNetAdhocctl",0x8DB83FDC,sceNetAdhocctlGetPeerInfo
#endif
