	.set noreorder

#include "pspimport.s"

// Build files
// LflashFatfmt_0000.o LflashFatfmt_0001.o

#ifdef F_LflashFatfmt_0000
	IMPORT_START "LflashFatfmt",0x00090000
#endif
#ifdef F_LflashFatfmt_0001
	IMPORT_FUNC  "LflashFatfmt",0xB7A424A4,sceLflashFatfmtStartFatfmt
#endif
