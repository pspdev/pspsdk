	.set noreorder

#include "pspimport.s"

#ifdef F_sceLibFont_0000
	IMPORT_START	"sceLibFont",0x40010000
#endif
#ifdef F_sceLibFont_0001
	IMPORT_FUNC	"sceLibFont",0x02D7F94B,sceFontFlush
#endif
#ifdef F_sceLibFont_0002
	IMPORT_FUNC	"sceLibFont",0x099EF33C,sceFontFindOptimumFont
#endif
#ifdef F_sceLibFont_0003
	IMPORT_FUNC	"sceLibFont",0x0DA7535E,sceFontGetFontInfo
#endif
#ifdef F_sceLibFont_0004
	IMPORT_FUNC	"sceLibFont",0x27F6E642,sceFontGetNumFontList
#endif
#ifdef F_sceLibFont_0005
	IMPORT_FUNC	"sceLibFont",0x2F67356A,sceFontCalcMemorySize
#endif
#ifdef F_sceLibFont_0006
	IMPORT_FUNC	"sceLibFont",0x33FFD07C,sceFontIsElement
#endif
#ifdef F_sceLibFont_0007
	IMPORT_FUNC	"sceLibFont",0x3AEA8CB6,sceFontClose
#endif
#ifdef F_sceLibFont_0008
	IMPORT_FUNC	"sceLibFont",0x3C4B7E82,sceFontPointToPixelV
#endif
#ifdef F_sceLibFont_0009
	IMPORT_FUNC	"sceLibFont",0x472694CD,sceFontPointToPixelH
#endif
#ifdef F_sceLibFont_0010
	IMPORT_FUNC	"sceLibFont",0x48293280,sceFontSetResolution
#endif
#ifdef F_sceLibFont_0011
	IMPORT_FUNC	"sceLibFont",0x48B06520,sceFontGetShadowImageRect
#endif
#ifdef F_sceLibFont_0012
	IMPORT_FUNC	"sceLibFont",0x5333322D,sceFontGetFontInfoByIndexNumber
#endif
#ifdef F_sceLibFont_0013
	IMPORT_FUNC	"sceLibFont",0x568BE516,sceFontGetShadowGlyphImage
#endif
#ifdef F_sceLibFont_0014
	IMPORT_FUNC	"sceLibFont",0x574B6FBC,sceFontDoneLib
#endif
#ifdef F_sceLibFont_0015
	IMPORT_FUNC	"sceLibFont",0x57FCB733,sceFontOpenUserFile
#endif
#ifdef F_sceLibFont_0016
	IMPORT_FUNC	"sceLibFont",0x5C3E4A9E,sceFontGetCharImageRect
#endif
#ifdef F_sceLibFont_0017
	IMPORT_FUNC	"sceLibFont",0x5DCF6858,sceFontGetShadowGlyphImage_Clip
#endif
#ifdef F_sceLibFont_0018
	IMPORT_FUNC	"sceLibFont",0x67F17ED7,sceFontNewLib
#endif
#ifdef F_sceLibFont_0019
	IMPORT_FUNC	"sceLibFont",0x681E61A7,sceFontFindFont
#endif
#ifdef F_sceLibFont_0020
	IMPORT_FUNC	"sceLibFont",0x74B21701,sceFontPixelToPointH
#endif
#ifdef F_sceLibFont_0021
	IMPORT_FUNC	"sceLibFont",0x980F4895,sceFontGetCharGlyphImage
#endif
#ifdef F_sceLibFont_0022
	IMPORT_FUNC	"sceLibFont",0xA834319D,sceFontOpen
#endif
#ifdef F_sceLibFont_0023
	IMPORT_FUNC	"sceLibFont",0xAA3DE7B5,sceFontGetShadowInfo
#endif
#ifdef F_sceLibFont_0024
	IMPORT_FUNC	"sceLibFont",0xBB8E7FE6,sceFontOpenUserMemory
#endif
#ifdef F_sceLibFont_0025
	IMPORT_FUNC	"sceLibFont",0xBC75D85B,sceFontGetFontList
#endif
#ifdef F_sceLibFont_0026
	IMPORT_FUNC	"sceLibFont",0xCA1E6945,sceFontGetCharGlyphImage_Clip
#endif
#ifdef F_sceLibFont_0027
	IMPORT_FUNC	"sceLibFont",0xDCC80C2F,sceFontGetCharInfo
#endif
#ifdef F_sceLibFont_0028
	IMPORT_FUNC	"sceLibFont",0xEE232411,sceFontSetAltCharacterCode
#endif
#ifdef F_sceLibFont_0029
	IMPORT_FUNC	"sceLibFont",0xF8F0752E,sceFontPixelToPointV
#endif
