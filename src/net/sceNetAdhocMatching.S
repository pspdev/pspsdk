	.set noreorder

#include "pspimport.s"

#ifdef F_sceNetAdhocMatching_0000
	IMPORT_START	"sceNetAdhocMatching",0x00090000
#endif
#ifdef F_sceNetAdhocMatching_0001
	IMPORT_FUNC	"sceNetAdhocMatching",0x2A2A1E07,sceNetAdhocMatchingInit
#endif
#ifdef F_sceNetAdhocMatching_0002
	IMPORT_FUNC	"sceNetAdhocMatching",0x7945ECDA,sceNetAdhocMatchingTerm
#endif
#ifdef F_sceNetAdhocMatching_0003
	IMPORT_FUNC	"sceNetAdhocMatching",0xCA5EDA6F,sceNetAdhocMatchingCreate
#endif
#ifdef F_sceNetAdhocMatching_0004
	IMPORT_FUNC	"sceNetAdhocMatching",0x93EF3843,sceNetAdhocMatchingStart
#endif
#ifdef F_sceNetAdhocMatching_0005
	IMPORT_FUNC	"sceNetAdhocMatching",0x32B156B3,sceNetAdhocMatchingStop
#endif
#ifdef F_sceNetAdhocMatching_0006
	IMPORT_FUNC	"sceNetAdhocMatching",0xF16EAF4F,sceNetAdhocMatchingDelete
#endif
#ifdef F_sceNetAdhocMatching_0007
	IMPORT_FUNC	"sceNetAdhocMatching",0x5E3D4B79,sceNetAdhocMatchingSelectTarget
#endif
#ifdef F_sceNetAdhocMatching_0008
	IMPORT_FUNC	"sceNetAdhocMatching",0xEA3C6108,sceNetAdhocMatchingCancelTarget
#endif
#ifdef F_sceNetAdhocMatching_0009
	IMPORT_FUNC	"sceNetAdhocMatching",0xB58E61B7,sceNetAdhocMatchingSetHelloOpt
#endif
#ifdef F_sceNetAdhocMatching_0010
	IMPORT_FUNC	"sceNetAdhocMatching",0xB5D96C2A,sceNetAdhocMatchingGetHelloOpt
#endif
#ifdef F_sceNetAdhocMatching_0011
	IMPORT_FUNC	"sceNetAdhocMatching",0xC58BCD9E,sceNetAdhocMatchingGetMembers
#endif
#ifdef F_sceNetAdhocMatching_0012
	IMPORT_FUNC	"sceNetAdhocMatching",0x40F8F435,sceNetAdhocMatchingGetPoolMaxAlloc
#endif
#ifdef F_sceNetAdhocMatching_0013
	IMPORT_FUNC	"sceNetAdhocMatching",0x8F58BEDF,sceNetAdhocMatchingCancelTargetWithOpt
#endif
#ifdef F_sceNetAdhocMatching_0014
	IMPORT_FUNC	"sceNetAdhocMatching",0x9C5CFB7D,sceNetAdhocMatchingGetPoolStat
#endif
#ifdef F_sceNetAdhocMatching_0015
	IMPORT_FUNC	"sceNetAdhocMatching",0xF79472D7,sceNetAdhocMatchingSendData
#endif
#ifdef F_sceNetAdhocMatching_0016
	IMPORT_FUNC	"sceNetAdhocMatching",0xEC19337D,sceNetAdhocMatchingAbortSendData
#endif
