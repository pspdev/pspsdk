	.set noreorder

#include "pspimport.s"

#ifdef F_StdioForKernel_0000
	IMPORT_START	"StdioForKernel",0x00010000
#endif
#ifdef F_StdioForKernel_0001
	IMPORT_FUNC	"StdioForKernel",0x2CCF071A,fdprintf
#endif
#ifdef F_StdioForKernel_0002
	IMPORT_FUNC	"StdioForKernel",0xCAB439DF,printf
#endif
#ifdef F_StdioForKernel_0003
	IMPORT_FUNC	"StdioForKernel",0x4F78930A,fdputc
#endif
#ifdef F_StdioForKernel_0004
	IMPORT_FUNC	"StdioForKernel",0xD768752A,putchar
#endif
#ifdef F_StdioForKernel_0005
	IMPORT_FUNC	"StdioForKernel",0x36B23B8B,fdputs
#endif
#ifdef F_StdioForKernel_0006
	IMPORT_FUNC	"StdioForKernel",0xD97C8CB9,puts
#endif
#ifdef F_StdioForKernel_0007
	IMPORT_FUNC	"StdioForKernel",0xD2B2A2A7,fdgetc
#endif
#ifdef F_StdioForKernel_0008
	IMPORT_FUNC	"StdioForKernel",0x7E338487,getchar
#endif
#ifdef F_StdioForKernel_0009
	IMPORT_FUNC	"StdioForKernel",0x11A5127A,fdgets
#endif
#ifdef F_StdioForKernel_0010
	IMPORT_FUNC	"StdioForKernel",0xBFF7E760,gets
#endif
#ifdef F_StdioForKernel_0011
	IMPORT_FUNC	"StdioForKernel",0x172D316E,sceKernelStdin
#endif
#ifdef F_StdioForKernel_0012
	IMPORT_FUNC	"StdioForKernel",0xA6BAB2E9,sceKernelStdout
#endif
#ifdef F_StdioForKernel_0013
	IMPORT_FUNC	"StdioForKernel",0xF78BA90A,sceKernelStderr
#endif
#ifdef F_StdioForKernel_0014
	IMPORT_FUNC	"StdioForKernel",0x98220F3E,sceKernelStdoutReopen
#endif
#ifdef F_StdioForKernel_0015
	IMPORT_FUNC	"StdioForKernel",0xFB5380C5,sceKernelStderrReopen
#endif
