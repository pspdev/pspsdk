	.set noreorder

#include "pspimport.s"

// Build List
// sceSsl_0000.o sceSsl_0001.o sceSsl_0002.o sceSsl_0003.o sceSsl_0004.o sceSsl_0005.o sceSsl_0006.o sceSsl_0007.o sceSsl_0008.o sceSsl_0009.o sceSsl_0010.o sceSsl_0011.o 

#ifdef F_sceSsl_0000
	IMPORT_START	"sceSsl",0x00090011
#endif
#ifdef F_sceSsl_0001
	IMPORT_FUNC	"sceSsl",0x058D21C0,sceSslGetNameEntryCount
#endif
#ifdef F_sceSsl_0002
	IMPORT_FUNC	"sceSsl",0x0EB43B06,sceSslGetUsedMemoryCurrent
#endif
#ifdef F_sceSsl_0003
	IMPORT_FUNC	"sceSsl",0x17A10DCC,sceSslGetNotBefore
#endif
#ifdef F_sceSsl_0004
	IMPORT_FUNC	"sceSsl",0x191CDEFF,sceSslEnd
#endif
#ifdef F_sceSsl_0005
	IMPORT_FUNC	"sceSsl",0x1B7C8191,sceSslGetIssuerName
#endif
#ifdef F_sceSsl_0006
	IMPORT_FUNC	"sceSsl",0x3DD5E023,sceSslGetSubjectName
#endif
#ifdef F_sceSsl_0007
	IMPORT_FUNC	"sceSsl",0x5BFB6B61,sceSslGetNotAfter
#endif
#ifdef F_sceSsl_0008
	IMPORT_FUNC	"sceSsl",0x957ECBE2,sceSslInit
#endif
#ifdef F_sceSsl_0009
	IMPORT_FUNC	"sceSsl",0xB99EDE6A,sceSslGetUsedMemoryMax
#endif
#ifdef F_sceSsl_0010
	IMPORT_FUNC	"sceSsl",0xCC0919B0,sceSslGetSerialNumber
#endif
#ifdef F_sceSsl_0011
	IMPORT_FUNC	"sceSsl",0xD6D097B4,sceSslGetNameEntryInfo
#endif
