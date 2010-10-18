	.set noreorder

#include "pspimport.s"

#ifdef F_StdioForUser_0000
	IMPORT_START	"StdioForUser",0x40010000
#endif
#ifdef F_StdioForUser_0001
	IMPORT_FUNC	"StdioForUser",0x3054D478,sceKernelStdioRead
#endif
#ifdef F_StdioForUser_0002
	IMPORT_FUNC	"StdioForUser",0x0CBB0571,sceKernelStdioLseek
#endif
#ifdef F_StdioForUser_0003
	IMPORT_FUNC	"StdioForUser",0xA46785C9,sceKernelStdioSendChar
#endif
#ifdef F_StdioForUser_0004
	IMPORT_FUNC	"StdioForUser",0xA3B931DB,sceKernelStdioWrite
#endif
#ifdef F_StdioForUser_0005
	IMPORT_FUNC	"StdioForUser",0x9D061C19,sceKernelStdioClose
#endif
#ifdef F_StdioForUser_0006
	IMPORT_FUNC	"StdioForUser",0x924ABA61,sceKernelStdioOpen
#endif
#ifdef F_StdioForUser_0007
	IMPORT_FUNC	"StdioForUser",0x172D316E,sceKernelStdin
#endif
#ifdef F_StdioForUser_0008
	IMPORT_FUNC	"StdioForUser",0xA6BAB2E9,sceKernelStdout
#endif
#ifdef F_StdioForUser_0009
	IMPORT_FUNC	"StdioForUser",0xF78BA90A,sceKernelStderr
#endif
