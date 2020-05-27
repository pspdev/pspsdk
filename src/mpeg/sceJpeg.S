	.set noreorder

#include "pspimport.s"

#ifdef F_sceJpeg_0000
	IMPORT_START	"sceJpeg",0x00090000
#endif
#ifdef F_sceJpeg_0001
	IMPORT_FUNC	"sceJpeg",0x0425B986,sceJpeg_0425B986
#endif
#ifdef F_sceJpeg_0002
	IMPORT_FUNC	"sceJpeg",0x04B5AE02,sceJpegMJpegCsc
#endif
#ifdef F_sceJpeg_0003
	IMPORT_FUNC	"sceJpeg",0x04B93CEF,sceJpegDecodeMJpeg
#endif
#ifdef F_sceJpeg_0004
	IMPORT_FUNC	"sceJpeg",0x227662D7,sceJpeg_227662D7
#endif
#ifdef F_sceJpeg_0005
	IMPORT_FUNC	"sceJpeg",0x48B602B7,sceJpegDeleteMJpeg
#endif
#ifdef F_sceJpeg_0006
	IMPORT_FUNC	"sceJpeg",0x64B6F978,sceJpeg_64B6F978
#endif
#ifdef F_sceJpeg_0007
	IMPORT_FUNC	"sceJpeg",0x67F0ED84,sceJpeg_67F0ED84
#endif
#ifdef F_sceJpeg_0008
	IMPORT_FUNC	"sceJpeg",0x7D2F3D7F,sceJpegFinishMJpeg
#endif
#ifdef F_sceJpeg_0009
	IMPORT_FUNC	"sceJpeg",0x8F2BB012,sceJpegGetOutputInfo
#endif
#ifdef F_sceJpeg_0010
	IMPORT_FUNC	"sceJpeg",0x91EED83C,sceJpegDecodeMJpegYCbCr
#endif
#ifdef F_sceJpeg_0011
	IMPORT_FUNC	"sceJpeg",0x9B36444C,sceJpeg_9B36444C
#endif
#ifdef F_sceJpeg_0012
	IMPORT_FUNC	"sceJpeg",0x9D47469C,sceJpegCreateMJpeg
#endif
#ifdef F_sceJpeg_0013
	IMPORT_FUNC	"sceJpeg",0xAC9E70E6,sceJpegInitMJpeg
#endif
