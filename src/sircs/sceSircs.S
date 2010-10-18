	.set noreorder

#include "pspimport.s"

#ifdef F_sceSircs_0000
	IMPORT_START	"sceSircs",0x40010000
#endif
#ifdef F_sceSircs_0001
	IMPORT_FUNC	"sceSircs",0x71EEF62D,sceSircsSend
#endif
