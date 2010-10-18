	.set noreorder

#include "pspimport.s"

#ifdef F_sceNetAdhoc_0000
	IMPORT_START	"sceNetAdhoc",0x00090000
#endif
#ifdef F_sceNetAdhoc_0001
	IMPORT_FUNC	"sceNetAdhoc",0xE1D621D7,sceNetAdhocInit
#endif
#ifdef F_sceNetAdhoc_0002
	IMPORT_FUNC	"sceNetAdhoc",0xA62C6F57,sceNetAdhocTerm
#endif
#ifdef F_sceNetAdhoc_0003
	IMPORT_FUNC	"sceNetAdhoc",0x7A662D6B,sceNetAdhocPollSocket
#endif
#ifdef F_sceNetAdhoc_0004
	IMPORT_FUNC	"sceNetAdhoc",0x73BFD52D,sceNetAdhocSetSocketAlert
#endif
#ifdef F_sceNetAdhoc_0005
	IMPORT_FUNC	"sceNetAdhoc",0x4D2CE199,sceNetAdhocGetSocketAlert
#endif
#ifdef F_sceNetAdhoc_0006
	IMPORT_FUNC	"sceNetAdhoc",0x6F92741B,sceNetAdhocPdpCreate
#endif
#ifdef F_sceNetAdhoc_0007
	IMPORT_FUNC	"sceNetAdhoc",0xABED3790,sceNetAdhocPdpSend
#endif
#ifdef F_sceNetAdhoc_0008
	IMPORT_FUNC	"sceNetAdhoc",0xDFE53E03,sceNetAdhocPdpRecv
#endif
#ifdef F_sceNetAdhoc_0009
	IMPORT_FUNC	"sceNetAdhoc",0x7F27BB5E,sceNetAdhocPdpDelete
#endif
#ifdef F_sceNetAdhoc_0010
	IMPORT_FUNC	"sceNetAdhoc",0xC7C1FC57,sceNetAdhocGetPdpStat
#endif
#ifdef F_sceNetAdhoc_0011
	IMPORT_FUNC	"sceNetAdhoc",0x877F6D66,sceNetAdhocPtpOpen
#endif
#ifdef F_sceNetAdhoc_0012
	IMPORT_FUNC	"sceNetAdhoc",0xFC6FC07B,sceNetAdhocPtpConnect
#endif
#ifdef F_sceNetAdhoc_0013
	IMPORT_FUNC	"sceNetAdhoc",0xE08BDAC1,sceNetAdhocPtpListen
#endif
#ifdef F_sceNetAdhoc_0014
	IMPORT_FUNC	"sceNetAdhoc",0x9DF81198,sceNetAdhocPtpAccept
#endif
#ifdef F_sceNetAdhoc_0015
	IMPORT_FUNC	"sceNetAdhoc",0x4DA4C788,sceNetAdhocPtpSend
#endif
#ifdef F_sceNetAdhoc_0016
	IMPORT_FUNC	"sceNetAdhoc",0x8BEA2B3E,sceNetAdhocPtpRecv
#endif
#ifdef F_sceNetAdhoc_0017
	IMPORT_FUNC	"sceNetAdhoc",0x9AC2EEAC,sceNetAdhocPtpFlush
#endif
#ifdef F_sceNetAdhoc_0018
	IMPORT_FUNC	"sceNetAdhoc",0x157E6225,sceNetAdhocPtpClose
#endif
#ifdef F_sceNetAdhoc_0019
	IMPORT_FUNC	"sceNetAdhoc",0xB9685118,sceNetAdhocGetPtpStat
#endif
#ifdef F_sceNetAdhoc_0020
	IMPORT_FUNC	"sceNetAdhoc",0x7F75C338,sceNetAdhocGameModeCreateMaster
#endif
#ifdef F_sceNetAdhoc_0021
	IMPORT_FUNC	"sceNetAdhoc",0x3278AB0C,sceNetAdhocGameModeCreateReplica
#endif
#ifdef F_sceNetAdhoc_0022
	IMPORT_FUNC	"sceNetAdhoc",0x98C204C8,sceNetAdhocGameModeUpdateMaster
#endif
#ifdef F_sceNetAdhoc_0023
	IMPORT_FUNC	"sceNetAdhoc",0xFA324B4E,sceNetAdhocGameModeUpdateReplica
#endif
#ifdef F_sceNetAdhoc_0024
	IMPORT_FUNC	"sceNetAdhoc",0xA0229362,sceNetAdhocGameModeDeleteMaster
#endif
#ifdef F_sceNetAdhoc_0025
	IMPORT_FUNC	"sceNetAdhoc",0x0B2228E9,sceNetAdhocGameModeDeleteReplica
#endif
