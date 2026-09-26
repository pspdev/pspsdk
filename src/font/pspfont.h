/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspfont.h - Prototypes for the sceLibFont library.
 *
 * Copyright (c) 2026 Zuzanna Petryk <zzanp@disroot.org>
 *
 */
#ifndef __FONT_H__
#define __FONT_H__
#include <malloc.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup LibFont Fonts Library
  * This module contains the imports for fonts.
  */

/** @addtogroup LibFont Fonts Library */
/**@{*/

enum SceFontFamily {
	SCE_FONT_FAMILY_DEFAULT = 0x0,
	SCE_FONT_FAMILY_SANS_SERIF = 0x1,
	SCE_FONT_FAMILY_SERIF = 0x2,
	SCE_FONT_FAMILY_ROUNDED = 0x3,
};

enum SceFontStyles {
	SCE_FONT_STYLE_DEFAULT = 0x0,
	SCE_FONT_STYLE_REGULAR = 0x1,
	SCE_FONT_STYLE_ITALIC = 0x2,
	SCE_FONT_STYLE_THIN = 0x3,
	SCE_FONT_STYLE_ITALIC_THIN = 0x4,
	SCE_FONT_STYLE_BOLD = 0x5,
	SCE_FONT_STYLE_ITALIC_BOLD = 0x6,
	SCE_FONT_STYLE_THICK = 0x7,
	SCE_FONT_STYLE_ITALIC_THICK = 0x8,
};

enum SceFontPixelFormat {
	SCE_FONT_PIXEL_FORMAT_L4 = 0x0,
	SCE_FONT_PIXEL_FORMAT_R4 = 0x1,
	SCE_FONT_PIXEL_FORMAT_8 = 0x2,
	SCE_FONT_PIXEL_FORMAT_24 = 0x3,
	SCE_FONT_PIXEL_FORMAT_32 = 0x4,
};

enum SceFontLanguage {
	SCE_FONT_LANGUAGE_DEFAULT = 0x0,
	SCE_FONT_LANGUAGE_JAPANESE = 0x1,
	SCE_FONT_LANGUAGE_ENGLISH = 0x2,
	SCE_FONT_LANGUAGE_KOREAN = 0x3,
	SCE_FONT_LANGUAGE_CHINESE = 0x4,
	SCE_FONT_LANGUAGE_JKC = 0x5,
};

enum SceFontVendorCountry {
	SCE_FONT_VENDOR_COUNTRY_DEFAULT = 0x0,
	SCE_FONT_VENDOR_COUNTRY_JAPAN = 0x1,
	SCE_FONT_VENDOR_COUNTRY_USA = 0x2,
	SCE_FONT_VENDOR_COUNTRY_KOREA = 0x3,
};

/**
 * @brief Font style info.
 * @see ::sceFontFindOptimumFont()
 * @see ::sceFontCalcMemorySize()
 * @see ::sceFontGetFontInfoByIndexNumber()
 * @see ::sceFontFindFont()
 * @see ::sceFontGetFontList()
 *
 */
typedef struct SceFontStyle {
	/** Width in points (1/72 inch), where 0 is system standard */
	float width;
	/** Height in points (1/72 inch), where 0 is system standard */
	float height;
	/** Resolution, where 0 is system standard */
	float xResolution;
	/** Resolution, where 0 is system standard */
	float yResolution;
	float weight;
	unsigned short family;
	unsigned short style;
	unsigned short subStyle;
	/** Language code (leave 0 if not specified) */
	unsigned short language;
	/** Region code (leave 0 if not specified) */
	unsigned short region;
	/** Country code (leave 0 if not specified) */
	unsigned short country;
	unsigned char fontName[64];
	unsigned char fileName[64];
	unsigned int extra;
	/** Expiration  (leave 0 if not specified) */
	unsigned int expiration;
} SceFontStyle;

/**
 * @brief Fixed-point info about singular characters.
 * @see ::SceFontCharacterData
 * @see ::SceFontCharacterDataFloat
 * @see ::SceFontInfo
 * @see ::SceFontCharacterInfo
 */
typedef struct SceFontCharacterData {
	unsigned int width, height;
	int top, bottom;
	int shiftX, shiftY;
	int shiftVertX, shiftVertY;
	int hShift, vShift;
} SceFontCharacterData;

/**
 * @brief Floating-point info about singular characters.
 * @see ::SceFontCharacterData
 * @see ::SceFontInfo
 */
typedef struct SceFontCharacterDataFloat {
	float width, height;
	float top, bottom;
	float shiftX, shiftY;
	float shiftVertX, shiftVertY;
	float hShift, vShift;
} SceFontCharacterDataFloat;

/**
 * @brief General font info.
 * @see ::SceFontCharacterData
 * @see ::SceFontCharacterDataFloat
 * @see ::SceFontStyle
 * @see ::sceFontGetFontInfo()
 */
typedef struct SceFontInfo {
	SceFontCharacterData maxFixed;
	SceFontCharacterDataFloat maxFloat;
	unsigned short maxWidth;
	unsigned short maxHeight;
	unsigned int characters;
	unsigned int subCharacters;
	SceFontStyle fontStyle;
	unsigned char depth;
	char unknown[3];
} SceFontInfo;

/**
 * @brief Rectangular size of the font images.
 * @see ::SceFontImageBuffer
 * @see ::sceFontGetShadowImageRect()
 * @see ::sceFontGetCharImageRect()
 */
typedef struct SceFontRect {
	unsigned short width;
	unsigned short height;
} SceFontRect;

/**
 * @brief Font cache data.
 * @see SceFontLibData
 */
typedef struct SceFontCache {
	/** Another cache instance, or just null */
	void** cache;
	/** Lock the cache */
	int (*lock)(void* cache);
	/** Unlock the cache */
	int (*unlock)(void* cache);
	/**
	 * @brief Find the key in cache.
	 *
	 * @param cache - Cache instance.
	 * @param value - Generated.
	 * @param key - Key to search for.
	 * @param result - 1 on success, 0 otherwise.
	 *
	 * @returns Pointer to the slot where it was found, NULL otherwise.
	 */
	void* (*find)(void* cache, unsigned int value, int key[4], unsigned int* result);
	int (*writeKV)(void* cache, void* slot, int key[4]);
	int (*write0)(void* cache, void* slot, void* data, int size);
	int (*write1)(void* cache, void* slot, void* data, int size);
	int (*write2)(void* cache, void* slot, void* data, int size);
	int (*write3)(void* cache, void* slot, void* data, int size);
	int (*read0)(void* cache, void* slot, void* dest);
	int (*read1)(void* cache, void* slot, void* dest);
	int (*read2)(void* cache, void* slot, void* dest);
	int (*read3)(void* cache, void* slot, void* dest);
} SceFontCache;

/**
 * @brief Info about a specific font.
 * @see ::SceFontCache
 * @see ::sceFontNewLib()
 */
typedef struct SceFontLibData {
	/** Leave null when initializing */
	void* unknown;
	/** Max number of fonts open at the same time */
	unsigned int maxFonts;
	SceFontCache* cache;
	void* (*alloc)(void* data, unsigned int size);
	void (*free)(void* data, void* pointer);
	void* (*open)(void* data, char* path, int* error);
	int (*close)(void* data, void* fileHandle);
	unsigned int (*read)(void* data, void* fileHandle, void* out, unsigned int size, unsigned int num, int* error);
	int (*seek)(void* data, void* fileHandle, unsigned int offset);
	int (*onError)(void* data, int error);
	int (*onReadComplete)(void* data, int status);
} SceFontLibData;

/**
 * @brief Buffer of the image containing a font.
 * @see ::SceFontRect
 * @see ::sceFontGetShadowGlyphImage()
 * @see ::sceFontGetShadowGlyphImage_Clip()
 * @see ::sceFontGetCharGlyphImage()
 * @see ::sceFontGetCharGlyphImage_Clip()
 */
typedef struct SceFontImageBuffer {
	unsigned int pixelFormat;
	int x, y;
	SceFontRect size;
	unsigned short bytesPerLine;
	short unknown;
	unsigned char* data;
} SceFontImageBuffer;

/**
 * @brief All the information regarding a single character.
 * @see ::SceFontCharacterData
 * @see ::sceFontGetShadowInfo()
 * @see sceFontGetCharInfo()
 */
typedef struct SceFontCharacterInfo {
	unsigned int width, height;
	int x, y;
	SceFontCharacterData data;
	char unknown[4];
} SceFontCharacterInfo;

/**
 * Flush local font cache.
 *
 * @param libraryId - Font handle.
 *
 * @return 0 on success, error code otherwise.
 */
int sceFontFlush(void* libraryId);

/**
 * Find an optimum font.
 *
 * @param libraryId - Font handle.
 * @param fontStyle - Style data of a wanted font.
 * @param error - Address for an error code.
 *
 * @return Index of the optimum font, otherwise 0.
 */
int sceFontFindOptimumFont(void* libraryId, SceFontStyle* fontStyle, int* error);

/**
 * Get font info.
 *
 * @param fontHandle - Font library handle.
 * @param fontInfo - Font information output.
 *
 * @return 0 on success, error code otherwise.
 */
int sceFontGetFontInfo(void* fontHandle, SceFontInfo* fontInfo);

/**
 * Get number of all available font lists.
 *
 * @param libraryHandle - Font library handle.
 * @param error - Address for an error code.
 *
 * @return Number of available font lists.
 */
int sceFontGetNumFontList(void* libraryHandle, int* error);

/**
 * @brief Calculate required memory size for a font.
 *
 * @param libraryHandle - Font library handle.
 * @param fontStyle - Style for the requested font.
 * @param error - Address for an error code.
 *
 * @returns Required memory size.
 */
int sceFontCalcMemorySize(void* libraryHandle, SceFontStyle* fontStyle, int* error);

int sceFontIsElement(); // TODO: DOCUMENT THIS SHIT

/**
 * @brief Close the font handle.
 *
 * @param fontHandle - Font handle.
 *
 * @returns 0 on success, error code otherwise.
 */
int sceFontClose(void* fontHandle);

/**
 * @brief Convert units from points to pixels in the vertical direction.
 *
 * @param libraryHandle - Font library handle.
 * @param points - Points value to convert.
 * @param error - Address for an error code.
 *
 * @return Pixels units.
 */
float sceFontPointToPixelV(void* libraryHandle, float points, int* error);

/**
 * @brief Convert units from points to pixels in the horizontal direction.
 *
 * @param libraryHandle - Font library handle.
 * @param points - Points value to convert.
 * @param error - Address for an error code.
 *
 * @return Pixels units.
 */
float sceFontPointToPixelH(void* libraryHandle, float points, int* error);

/**
 * @brief Set font resolution.
 *
 * @param libraryHandle - Font library handle.
 * @param hres - Horizontal resolution.
 * @param vres - Vertical resolution.
 *
 * @return 0 on success, error code otherwise.
 */
int sceFontSetResolution(void* libraryHandle, float hres, float vres);

int sceFontGetShadowImageRect(void* fontHandle, unsigned short code, SceFontRect* output);

/**
 * @brief Get font style info by index number.
 * 
 * @param libraryHandle - Font library handle. 
 * @param fontStyle - Style output.
 * @param index - Font index.
 *
 * @return 0 on success, error code otherwise.
 */
int sceFontGetFontInfoByIndexNumber(void* libraryHandle, SceFontStyle* fontStyle, int index);

int sceFontGetShadowGlyphImage(void* fontHandle, unsigned short code, SceFontImageBuffer* output);

/**
 * @brief Terminate a font handle.
 *
 * @param libraryHandle - Font library handle.
 *
 * @return 0 on success, error code otherwise.
 */
int sceFontDoneLib(void* libraryHandle);

/**
 * @brief Open local font file.
 *
 * @param libraryHandle - Font library handle.
 * @param path - Full path to the font.
 * @param mode - 0 for file based stream, 1 for memory based stream.
 * @param error - Address for an error code.
 *
 * @return Font handle.
 */
void* sceFontOpenUserFile(void* libraryHandle, char* path, unsigned int mode, int* error);

/**
 * @brief Get size of the image of the character.
 *
 * @param fontHandle - Font handle.
 * @param code - Character code.
 * @param output - Pointer to output with width and size of the image.
 *
 * @return 0 on success, error code otherwise.
 */
int sceFontGetCharImageRect(void* fontHandle, unsigned short code, SceFontRect* output);

int sceFontGetShadowGlyphImage_Clip(void* fontHandle, unsigned short code, SceFontImageBuffer* output, int x, int y, unsigned int width, unsigned int height);

/**
 * @brief Initialize a font library.
 *
 * @param data - Setup for a font library.
 * @param error - Address for an error code.
 *
 * @return Font library handle.
 */
void* sceFontNewLib(SceFontLibData *data, int* error);

/**
 * @brief Find the font that exactly matches the style.
 *
 * @param libraryHandle - Font library handle.
 * @param fontStyle - Style for the font to find.
 * @param error - Address for an error code.
 *
 * @return Index value of the font, -1 if no font is found, or 0 on error.
 */
int sceFontFindFont(void* libraryHandle, SceFontStyle* fontStyle, int* error);

/**
 * @brief Convert units from pixels to points in the horizontal direction.
 *
 * @param libraryHandle - Font library handle.
 * @param pixels - Pixels value to convert.
 * @param error - Address for an error code.
 *
 * @return Points units.
 */
float sceFontPixelToPointH(void* libraryHandle, float pixels, int* error);

/**
 * @brief Get image of a character.
 *
 * @param fontHandle - Font handle.
 * @param code - Character code.
 * @param output - Output data.
 *
 * @return 0 on success, error code otherwise.
 */
int sceFontGetCharGlyphImage(void* fontHandle, unsigned short code, SceFontImageBuffer* output);

/**
 * @brief Open a new font.
 *
 * @param libraryHandle - Font library handle.
 * @param index - Font index (0 for default).
 * @param mode - 0 for file based stream, 1 for memory based stream.
 * @param error - Address for an error code.
 *
 * @return Font handle.
 */
void* sceFontOpen(void* libraryHandle, int index, unsigned int mode, int* error);

int sceFontGetShadowInfo(void* fontHandle, unsigned short code, SceFontCharacterInfo* output);

/**
 * @brief Open font from memory.
 *
 * @param libraryHandle - Font library handle.
 * @param font - Pointer to font in memory.
 * @param size - Size of the font data.
 * @param error - Address for an error code.
 *
 * @return Font handle.
 */
void* sceFontOpenUserMemory(void* libraryHandle, char* font, unsigned int size, int* error);

/**
 * @brief Get available fonts.
 *
 * @param libraryHandle - Font library handle.
 * @param output - Array of SceFontStyle.
 * @param size - Size of the output array.
 *
 * @return 0 on success, error code otherwise.
 */
int sceFontGetFontList(void* libraryHandle, SceFontStyle* output, int size);

/**
 * @brief Get clipped image of the character.
 *
 * @param fontHandle - Font handle.
 * @param code - Character code.
 * @param output - Output data.
 * @param x - X position of clipping.
 * @param y - Y position of clipping.
 * @param width - Clipping width.
 * @param height - Clipping height.
 *
 * @return 0 on success, error code otherwise.
 */
int sceFontGetCharGlyphImage_Clip(void* fontHandle, unsigned short code, SceFontImageBuffer* output, int x, int y, unsigned int width, unsigned int height);

/**
 * @brief Get info about character.
 *
 * @param fontHandle - Font handle.
 * @param code - Character code.
 * @param output - Output of character information.
 *
 * @return 0 on success, error code otherwise.
 */
int sceFontGetCharInfo(void* fontHandle, unsigned short code, SceFontCharacterInfo* output);

/**
 * @brief Set a fallback character.
 *
 * @param libraryHandle - Font library handle.
 * @param code - Character code.
 *
 * @return 0 on success, error code otherwise.
 */
int sceFontSetAltCharacterCode(void* libraryHandle, unsigned short code);

/**
 * @brief Convert units from pixels to points in the vertical direction.
 *
 * @param libraryHandle - Font library handle.
 * @param pixels - Pixels value to convert.
 * @param error - Address for an error code.
 *
 * @return Points units.
 */
float sceFontPixelToPointV(void* libraryHandle, float pixels, int* error);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif
