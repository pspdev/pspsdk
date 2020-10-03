#include "pspimport.s"

#ifdef F_sceDmac_0000
    IMPORT_START "sceDmac", 0x40010011
#endif
#ifdef F_sceDmac_0001
    IMPORT_FUNC "sceDmac", 0x617F3FE6, sceDmacMemcpy
#endif
#ifdef F_sceDmac_0002
    IMPORT_FUNC "sceDmac", 0xD97F94D8, sceDmacTryMemcpy
#endif
