	.set noreorder

#include "pspimport.s"

#ifdef F_sceChnnlsv_0000
	IMPORT_START	"sceChnnlsv",0x40010000
#endif
#ifdef F_sceChnnlsv_0001
	IMPORT_FUNC	"sceChnnlsv",0xE7833020,sceSdSetIndex
#endif
#ifdef F_sceChnnlsv_0002
	IMPORT_FUNC	"sceChnnlsv",0xF21A1FCA,sceSdRemoveValue
#endif
#ifdef F_sceChnnlsv_0003
	IMPORT_FUNC	"sceChnnlsv",0xC4C494F8,sceSdGetLastIndex
#endif
#ifdef F_sceChnnlsv_0004
	IMPORT_FUNC	"sceChnnlsv",0xABFDFC8B,sceSdCreateList
#endif
#ifdef F_sceChnnlsv_0005
	IMPORT_FUNC	"sceChnnlsv",0x850A7FA1,sceSdSetMember
#endif
#ifdef F_sceChnnlsv_0006
	IMPORT_FUNC	"sceChnnlsv",0x21BE78B4,sceSdCleanList
#endif
