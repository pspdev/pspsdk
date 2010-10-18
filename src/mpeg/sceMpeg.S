	.set noreorder

#include "pspimport.s"

#ifdef F_sceMpeg_0000
	IMPORT_START	"sceMpeg",0x00090000
#endif
#ifdef F_sceMpeg_0001
	IMPORT_FUNC	"sceMpeg",0x21FF80E4,sceMpegQueryStreamOffset
#endif
#ifdef F_sceMpeg_0002
	IMPORT_FUNC	"sceMpeg",0x611E9E11,sceMpegQueryStreamSize
#endif
#ifdef F_sceMpeg_0003
	IMPORT_FUNC	"sceMpeg",0x682A619B,sceMpegInit
#endif
#ifdef F_sceMpeg_0004
	IMPORT_FUNC	"sceMpeg",0x874624D6,sceMpegFinish
#endif
#ifdef F_sceMpeg_0005
	IMPORT_FUNC	"sceMpeg",0xC132E22F,sceMpegQueryMemSize
#endif
#ifdef F_sceMpeg_0006
	IMPORT_FUNC	"sceMpeg",0xD8C5F121,sceMpegCreate
#endif
#ifdef F_sceMpeg_0007
	IMPORT_FUNC	"sceMpeg",0x606A4649,sceMpegDelete
#endif
#ifdef F_sceMpeg_0008
	IMPORT_FUNC	"sceMpeg",0x42560F23,sceMpegRegistStream
#endif
#ifdef F_sceMpeg_0009
	IMPORT_FUNC	"sceMpeg",0x591A4AA2,sceMpegUnRegistStream
#endif
#ifdef F_sceMpeg_0010
	IMPORT_FUNC	"sceMpeg",0xA780CF7E,sceMpegMallocAvcEsBuf
#endif
#ifdef F_sceMpeg_0011
	IMPORT_FUNC	"sceMpeg",0xCEB870B1,sceMpegFreeAvcEsBuf
#endif
#ifdef F_sceMpeg_0012
	IMPORT_FUNC	"sceMpeg",0xF8DCB679,sceMpegQueryAtracEsSize
#endif
#ifdef F_sceMpeg_0013
	IMPORT_FUNC	"sceMpeg",0xC02CF6B5,sceMpegQueryPcmEsSize
#endif
#ifdef F_sceMpeg_0014
	IMPORT_FUNC	"sceMpeg",0x167AFD9E,sceMpegInitAu
#endif
#ifdef F_sceMpeg_0015
	IMPORT_FUNC	"sceMpeg",0x234586AE,sceMpegChangeGetAvcAuMode
#endif
#ifdef F_sceMpeg_0016
	IMPORT_FUNC	"sceMpeg",0x9DCFB7EA,sceMpegChangeGetAuMode
#endif
#ifdef F_sceMpeg_0017
	IMPORT_FUNC	"sceMpeg",0xFE246728,sceMpegGetAvcAu
#endif
#ifdef F_sceMpeg_0018
	IMPORT_FUNC	"sceMpeg",0x8C1E027D,sceMpegGetPcmAu
#endif
#ifdef F_sceMpeg_0019
	IMPORT_FUNC	"sceMpeg",0xE1CE83A7,sceMpegGetAtracAu
#endif
#ifdef F_sceMpeg_0020
	IMPORT_FUNC	"sceMpeg",0x500F0429,sceMpegFlushStream
#endif
#ifdef F_sceMpeg_0021
	IMPORT_FUNC	"sceMpeg",0x707B7629,sceMpegFlushAllStream
#endif
#ifdef F_sceMpeg_0022
	IMPORT_FUNC	"sceMpeg",0x0E3C2E9D,sceMpegAvcDecode
#endif
#ifdef F_sceMpeg_0023
	IMPORT_FUNC	"sceMpeg",0x0F6C18D7,sceMpegAvcDecodeDetail
#endif
#ifdef F_sceMpeg_0024
	IMPORT_FUNC	"sceMpeg",0xA11C7026,sceMpegAvcDecodeMode
#endif
#ifdef F_sceMpeg_0025
	IMPORT_FUNC	"sceMpeg",0x740FCCD1,sceMpegAvcDecodeStop
#endif
#ifdef F_sceMpeg_0026
	IMPORT_FUNC	"sceMpeg",0x800C44DF,sceMpegAtracDecode
#endif
#ifdef F_sceMpeg_0027
	IMPORT_FUNC	"sceMpeg",0xD7A29F46,sceMpegRingbufferQueryMemSize
#endif
#ifdef F_sceMpeg_0028
	IMPORT_FUNC	"sceMpeg",0x37295ED8,sceMpegRingbufferConstruct
#endif
#ifdef F_sceMpeg_0029
	IMPORT_FUNC	"sceMpeg",0x13407F13,sceMpegRingbufferDestruct
#endif
#ifdef F_sceMpeg_0030
	IMPORT_FUNC	"sceMpeg",0xB240A59E,sceMpegRingbufferPut
#endif
#ifdef F_sceMpeg_0031
	IMPORT_FUNC	"sceMpeg",0xB5F6DC87,sceMpegRingbufferAvailableSize
#endif
#ifdef F_sceMpeg_0032
	IMPORT_FUNC	"sceMpeg",0x11CAB459,sceMpeg_11CAB459
#endif
#ifdef F_sceMpeg_0033
	IMPORT_FUNC	"sceMpeg",0x3C37A7A6,sceMpeg_3C37A7A6
#endif
#ifdef F_sceMpeg_0034
	IMPORT_FUNC	"sceMpeg",0xB27711A8,sceMpeg_B27711A8
#endif
#ifdef F_sceMpeg_0035
	IMPORT_FUNC	"sceMpeg",0xD4DD6E75,sceMpeg_D4DD6E75
#endif
#ifdef F_sceMpeg_0036
	IMPORT_FUNC	"sceMpeg",0xC345DED2,sceMpeg_C345DED2
#endif
#ifdef F_sceMpeg_0037
	IMPORT_FUNC	"sceMpeg",0xCF3547A2,sceMpegAvcDecodeDetail2
#endif
#ifdef F_sceMpeg_0038
	IMPORT_FUNC	"sceMpeg",0x988E9E12,sceMpeg_988E9E12
#endif
