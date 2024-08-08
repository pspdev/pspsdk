/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#ifndef __pspgu_h__
#define __pspgu_h__

#include <psptypes.h>
#include <pspge.h>
#include <pspdisplay.h>
#include <math.h>

/** @defgroup GU Graphics Utility Library
 *
 */

#if defined(__cplusplus)
extern "C" {
#endif

/* PI, float-sized */
#define GU_PI			(3.141593f)

/* Boolean values for convenience */
#define GU_FALSE		(0)
#define GU_TRUE			(1)

/* Primitive types */
#define GU_POINTS		(0)
#define GU_LINES		(1)
#define GU_LINE_STRIP		(2)
#define GU_TRIANGLES		(3)
#define GU_TRIANGLE_STRIP	(4)
#define GU_TRIANGLE_FAN		(5)
#define GU_SPRITES		(6)

/* States */
#define GU_ALPHA_TEST		(0)
#define GU_DEPTH_TEST		(1)
#define GU_SCISSOR_TEST		(2)
#define GU_STENCIL_TEST		(3)
#define GU_BLEND		(4)
#define GU_CULL_FACE		(5)
#define GU_DITHER		(6)
#define GU_FOG			(7)
#define GU_CLIP_PLANES		(8)
#define GU_TEXTURE_2D		(9)
#define GU_LIGHTING		(10)
#define GU_LIGHT0		(11)
#define GU_LIGHT1		(12)
#define GU_LIGHT2		(13)
#define GU_LIGHT3		(14)
#define GU_LINE_SMOOTH		(15)
#define GU_PATCH_CULL_FACE	(16)
#define GU_COLOR_TEST		(17)
#define GU_COLOR_LOGIC_OP	(18)
#define GU_FACE_NORMAL_REVERSE	(19)
#define GU_PATCH_FACE		(20)
#define GU_FRAGMENT_2X		(21)

/* Matrix modes */
#define GU_PROJECTION		(0)
#define GU_VIEW			(1)
#define GU_MODEL		(2)
#define GU_TEXTURE		(3)

/* Vertex Declarations Begin */
#define GU_TEXTURE_SHIFT(n)	((n)<<0)
#define GU_TEXTURE_8BIT		GU_TEXTURE_SHIFT(1)
#define GU_TEXTURE_16BIT	GU_TEXTURE_SHIFT(2)
#define GU_TEXTURE_32BITF	GU_TEXTURE_SHIFT(3)
#define GU_TEXTURE_BITS		GU_TEXTURE_SHIFT(3)

#define GU_COLOR_SHIFT(n)	((n)<<2)
#define GU_COLOR_5650		GU_COLOR_SHIFT(4)
#define GU_COLOR_5551		GU_COLOR_SHIFT(5)
#define GU_COLOR_4444		GU_COLOR_SHIFT(6)
#define GU_COLOR_8888		GU_COLOR_SHIFT(7)
#define GU_COLOR_BITS		GU_COLOR_SHIFT(7)

#define GU_NORMAL_SHIFT(n)	((n)<<5)
#define GU_NORMAL_8BIT		GU_NORMAL_SHIFT(1)
#define GU_NORMAL_16BIT		GU_NORMAL_SHIFT(2)
#define GU_NORMAL_32BITF	GU_NORMAL_SHIFT(3)
#define GU_NORMAL_BITS		GU_NORMAL_SHIFT(3)

#define GU_VERTEX_SHIFT(n)	((n)<<7)
#define GU_VERTEX_8BIT		GU_VERTEX_SHIFT(1)
#define GU_VERTEX_16BIT		GU_VERTEX_SHIFT(2)
#define GU_VERTEX_32BITF	GU_VERTEX_SHIFT(3)
#define GU_VERTEX_BITS		GU_VERTEX_SHIFT(3)

#define GU_WEIGHT_SHIFT(n)	((n)<<9)
#define GU_WEIGHT_8BIT		GU_WEIGHT_SHIFT(1)
#define GU_WEIGHT_16BIT		GU_WEIGHT_SHIFT(2)
#define GU_WEIGHT_32BITF	GU_WEIGHT_SHIFT(3)
#define GU_WEIGHT_BITS		GU_WEIGHT_SHIFT(3)

#define GU_INDEX_SHIFT(n)	((n)<<11)
#define GU_INDEX_8BIT		GU_INDEX_SHIFT(1)
#define GU_INDEX_16BIT		GU_INDEX_SHIFT(2)
#define GU_INDEX_BITS		GU_INDEX_SHIFT(3)

#define GU_WEIGHTS(n)		((((n)-1)&7)<<14)
#define GU_WEIGHTS_BITS		GU_WEIGHTS(8)
#define GU_VERTICES(n)		((((n)-1)&7)<<18)
#define GU_VERTICES_BITS	GU_VERTICES(8)

#define GU_TRANSFORM_SHIFT(n)	((n)<<23)
#define GU_TRANSFORM_3D		GU_TRANSFORM_SHIFT(0)
#define GU_TRANSFORM_2D		GU_TRANSFORM_SHIFT(1)
#define GU_TRANSFORM_BITS	GU_TRANSFORM_SHIFT(1)
/* Vertex Declarations End */

/* Pixel Formats */
#define GU_PSM_5650		(0) /* Display, Texture, Palette */
#define GU_PSM_5551		(1) /* Display, Texture, Palette */
#define GU_PSM_4444		(2) /* Display, Texture, Palette */
#define GU_PSM_8888		(3) /* Display, Texture, Palette */
#define GU_PSM_T4		(4) /* Texture */
#define GU_PSM_T8		(5) /* Texture */
#define GU_PSM_T16		(6) /* Texture */
#define GU_PSM_T32		(7) /* Texture */
#define GU_PSM_DXT1		(8) /* Texture */
#define GU_PSM_DXT3		(9) /* Texture */
#define GU_PSM_DXT5		(10) /* Texture */

/* Spline Mode */
#define GU_FILL_FILL	(0)
#define GU_OPEN_FILL	(1)
#define GU_FILL_OPEN	(2)
#define GU_OPEN_OPEN	(3)

/* Shading Model */
#define GU_FLAT			(0)
#define GU_SMOOTH		(1)

/* Logical operation */
#define GU_CLEAR		(0)
#define GU_AND			(1)
#define GU_AND_REVERSE		(2)
#define GU_COPY			(3)
#define GU_AND_INVERTED		(4)
#define GU_NOOP			(5)
#define GU_XOR			(6)
#define GU_OR			(7)
#define GU_NOR			(8)
#define GU_EQUIV		(9)
#define GU_INVERTED		(10)
#define GU_OR_REVERSE		(11)
#define GU_COPY_INVERTED	(12)
#define GU_OR_INVERTED		(13)
#define GU_NAND			(14)
#define GU_SET			(15)

/* Texture Filter */
#define GU_NEAREST		(0)
#define GU_LINEAR		(1)
#define GU_NEAREST_MIPMAP_NEAREST (4)
#define GU_LINEAR_MIPMAP_NEAREST (5)
#define GU_NEAREST_MIPMAP_LINEAR (6)
#define GU_LINEAR_MIPMAP_LINEAR	(7)

/* Texture Map Mode */
#define GU_TEXTURE_COORDS	(0)
#define GU_TEXTURE_MATRIX	(1)
#define GU_ENVIRONMENT_MAP	(2)

/* Texture Level Mode */
#define GU_TEXTURE_AUTO		(0)
#define GU_TEXTURE_CONST	(1)
#define GU_TEXTURE_SLOPE	(2)

/* Texture Projection Map Mode */
#define GU_POSITION		(0)
#define GU_UV			(1)
#define GU_NORMALIZED_NORMAL	(2)
#define GU_NORMAL		(3)

/* Wrap Mode */
#define GU_REPEAT		(0)
#define GU_CLAMP		(1)

/* Front Face Direction */
#define GU_CW			(0)
#define GU_CCW			(1)

/* Test Function */
#define GU_NEVER		(0)
#define GU_ALWAYS		(1)
#define GU_EQUAL		(2)
#define GU_NOTEQUAL		(3)
#define GU_LESS			(4)
#define GU_LEQUAL		(5)
#define GU_GREATER		(6)
#define GU_GEQUAL		(7)

/* Clear Buffer Mask */
#define GU_COLOR_BUFFER_BIT	(1)
#define GU_STENCIL_BUFFER_BIT	(2)
#define GU_DEPTH_BUFFER_BIT	(4)
#define GU_FAST_CLEAR_BIT	(16)

/* Texture Effect */
#define GU_TFX_MODULATE		(0)
#define GU_TFX_DECAL		(1)
#define GU_TFX_BLEND		(2)
#define GU_TFX_REPLACE		(3)
#define GU_TFX_ADD		(4)

/* Texture Color Component */
#define GU_TCC_RGB		(0)
#define GU_TCC_RGBA		(1)

/* Blending Op */
#define GU_ADD			(0)
#define GU_SUBTRACT		(1)
#define GU_REVERSE_SUBTRACT	(2)
#define GU_MIN			(3)
#define GU_MAX			(4)
#define GU_ABS			(5)

/* Blending Factor */
#define GU_SRC_COLOR		(0)
#define GU_ONE_MINUS_SRC_COLOR	(1)
#define GU_SRC_ALPHA		(2)
#define GU_ONE_MINUS_SRC_ALPHA	(3)
#define GU_DST_COLOR		(0)
#define GU_ONE_MINUS_DST_COLOR	(1)
#define GU_DST_ALPHA		(4)
#define GU_ONE_MINUS_DST_ALPHA	(5)
#define GU_FIX			(10)

/* Stencil Operations */
#define GU_KEEP			(0)
#define GU_ZERO			(1)
#define GU_REPLACE		(2)
#define GU_INVERT		(3)
#define GU_INCR			(4)
#define GU_DECR			(5)

/* Light Components */
#define GU_AMBIENT		(1)
#define GU_DIFFUSE		(2)
#define GU_SPECULAR		(4)
#define GU_AMBIENT_AND_DIFFUSE	(GU_AMBIENT|GU_DIFFUSE)
#define GU_DIFFUSE_AND_SPECULAR	(GU_DIFFUSE|GU_SPECULAR)
#define GU_UNKNOWN_LIGHT_COMPONENT (8)

/* Light modes */
#define GU_SINGLE_COLOR		(0)
#define GU_SEPARATE_SPECULAR_COLOR (1)

/* Light Type */
#define GU_DIRECTIONAL		(0)
#define GU_POINTLIGHT		(1)
#define GU_SPOTLIGHT		(2)

/* Contexts */
#define GU_DIRECT		(0)
#define GU_CALL			(1)
#define GU_SEND			(2)

/* List Queue */
#define GU_TAIL			(0)
#define GU_HEAD			(1)

/* Sync behavior (mode) */
#define GU_SYNC_FINISH	(0)
#define GU_SYNC_SIGNAL	(1)
#define GU_SYNC_DONE	(2)
#define GU_SYNC_LIST	(3)
#define GU_SYNC_SEND	(4)

/* behavior (what) */
#define GU_SYNC_WAIT	(0)
#define GU_SYNC_NOWAIT	(1)

/* Sync behavior (what) [see pspge.h] */
#define GU_SYNC_WHAT_DONE (0)
#define GU_SYNC_WHAT_QUEUED (1)
#define GU_SYNC_WHAT_DRAW (2)
#define GU_SYNC_WHAT_STALL (3)
#define GU_SYNC_WHAT_CANCEL (4)

/* Signals */
#define GU_CALLBACK_SIGNAL	(1)
#define GU_CALLBACK_FINISH	(4)

/* Signal behavior */
#define GU_BEHAVIOR_SUSPEND (1)
#define GU_BEHAVIOR_CONTINUE (2)

/* Color Macros, maps 8 bit unsigned channels into one 32-bit value */
#define GU_ABGR(a,b,g,r)	(((a) << 24)|((b) << 16)|((g) << 8)|(r))
#define GU_ARGB(a,r,g,b)	GU_ABGR((a),(b),(g),(r))
#define GU_RGBA(r,g,b,a)	GU_ARGB((a),(r),(g),(b))

/* Color Macro, maps floating point channels (0..1) into one 32-bit value */
#define GU_COLOR(r,g,b,a)	GU_RGBA((u32)((r) * 255.0f),(u32)((g) * 255.0f),(u32)((b) * 255.0f),(u32)((a) * 255.0f))

typedef void (*GuSwapBuffersCallback)(void** display,void** render);

/** @addtogroup GU */
/**@{*/

/**
  * Set depth buffer parameters
  *
  * @param zbp - VRAM pointer where the depthbuffer should start
  * @param zbw - The width of the depth-buffer (block-aligned)
  *
**/
static inline void sceGuDepthBuffer(void *zbp, int zbw);

/**
  * Set display buffer parameters
  *
  * @par Example: Setup a standard 16-bit display buffer
  * @code
  * sceGuDispBuffer(480,272,(void*)512*272*2,512); // 480*272, skipping the draw buffer located at address 0
  * @endcode
  *
  * @param width - Width of the display buffer in pixels
  * @param height - Width of the display buffer in pixels
  * @param dispbp - VRAM pointer to where the display-buffer starts
  * @param dispbw - Display buffer width (block aligned)
  *
**/
static inline void sceGuDispBuffer(int width, int height, void *dispbp, int dispbw);

/**
  * Set draw buffer parameters (and store in context for buffer-swap)
  *
  * Available pixel formats are:
  *   - GU_PSM_5650
  *   - GU_PSM_5551
  *   - GU_PSM_4444
  *   - GU_PSM_8888
  *
  * @par Example: Setup a standard 16-bit draw buffer
  * @code
  * sceGuDrawBuffer(GU_PSM_5551,(void*)0,512);
  * @endcode
  *
  * @param psm - Pixel format to use for rendering (and display)
  * @param fbp - VRAM pointer to where the draw buffer starts
  * @param fbw - Frame buffer width (block aligned)
**/
static inline void sceGuDrawBuffer(int psm, void *fbp, int fbw);

/**
  * Set draw buffer directly, not storing parameters in the context
  *
  * @param psm - Pixel format to use for rendering
  * @param fbp - VRAM pointer to where the draw buffer starts
  * @param fbw - Frame buffer width (block aligned)
**/
static inline void sceGuDrawBufferList(int psm, void *fbp, int fbw);

/**
  * Turn display on or off
  *
  * Available states are:
  *   - GU_TRUE (1) - Turns display on
  *   - GU_FALSE (0) - Turns display off
  *
  * @param state - Turn display on or off
  * @return State of the display prior to this call
**/
static inline int sceGuDisplay(int state);

/**
  * Select which depth-test function to use
  *
  * Valid choices for the depth-test are:
  *   - GU_NEVER - No pixels pass the depth-test
  *   - GU_ALWAYS - All pixels pass the depth-test
  *   - GU_EQUAL - Pixels that match the depth-test pass
  *   - GU_NOTEQUAL - Pixels that doesn't match the depth-test pass
  *   - GU_LESS - Pixels that are less in depth passes
  *   - GU_LEQUAL - Pixels that are less or equal in depth passes
  *   - GU_GREATER - Pixels that are greater in depth passes
  *   - GU_GEQUAL - Pixels that are greater or equal passes
  *
  * @param function - Depth test function to use
**/
static inline void sceGuDepthFunc(int function);

/**
  * Mask depth buffer writes
  *
  * @param mask - GU_TRUE(1) to disable Z writes, GU_FALSE(0) to enable
**/
static inline void sceGuDepthMask(int mask);

static inline void sceGuDepthOffset(unsigned int offset);

/**
  * Set which range to use for depth calculations.
  *
  * @note The depth buffer is inversed, and takes values from 65535 to 0.
  *
  * Example: Use the entire depth-range for calculations:
  * @code
  * sceGuDepthRange(65535,0);
  * @endcode
  *
  * @param near - Value to use for the near plane
  * @param far - Value to use for the far plane
**/
static inline void sceGuDepthRange(int near, int far);

static inline void sceGuFog(float near, float far, unsigned int color);

/**
  * Initalize the GU system
  *
  * This function MUST be called as the first function, otherwise state is undetermined.
**/
void sceGuInit(void);

/**
  * Shutdown the GU system
  *
  * Called when GU is no longer needed
**/
void sceGuTerm(void);

static inline void sceGuBreak(int a0);
static inline void sceGuContinue(void);

typedef void (*GuCallback)(int);
/**
  * Setup signal handler
  *
  * Available signals are:
  *   - GU_CALLBACK_SIGNAL - Called when sceGuSignal is used
  *   - GU_CALLBACK_FINISH - Called when display list is finished
  *
  * @param signal - Signal index to install a handler for
  * @param callback - Callback to call when signal index is triggered
  * @return The old callback handler
**/
static inline GuCallback sceGuSetCallback(int signal, void (*callback)(int));

/**
  * Trigger signal to call code from the command stream
  *
  * Available behaviors are:
  *   - GU_BEHAVIOR_SUSPEND - Stops display list execution until callback function finished
  *   - GU_BEHAVIOR_CONTINUE - Do not stop display list execution during callback
  *
  * @param signal - Signal to trigger
  * @param behavior - Behavior type
**/
static inline void sceGuSignal(int signal, int behavior);

/**
  * Send raw float-command to the GE
  *
  * The argument is converted into a 24-bit float before transfer.
  *
  * @param cmd - Which command to send
  * @param argument - Argument to pass along
**/
static inline void sceGuSendCommandf(int cmd, float argument);

/**
  * Send raw command to the GE
  *
  * Only the 24 lower bits of the argument is passed along.
  *
  * @param cmd - Which command to send
  * @param argument - Argument to pass along
**/
static inline void sceGuSendCommandi(int cmd, int argument);

/**
  * Allocate memory on the current display list for temporary storage
  *
  * @note This function is NOT for permanent memory allocation, the
  * memory will be invalid as soon as you start filling the same display
  * list again.
  *
  * @param size - How much memory to allocate
  * @return Memory-block ready for use
**/
void *sceGuGetMemory(int size);

/**
  * Start filling a new display-context
  *
  * Contexts available are:
  *   - GU_DIRECT - Rendering is performed as list is filled
  *   - GU_CALL - List is setup to be called from the main list
  *   - GU_SEND - List is buffered for a later call to sceGuSendList()
  *
  * The previous context-type is stored so that it can be restored at sceGuFinish().
  *
  * @param cid - Context Type
  * @param list - Pointer to display-list (16 byte aligned)
**/
void sceGuStart(int cid, void *list);

/**
  * Finish current display list and go back to the parent context
  *
  * If the context is GU_DIRECT, the stall-address is updated so that the entire list will
  * execute. Otherwise, only the terminating action is written to the list, depending on
  * context-type.
  *
  * The finish-callback will get a zero as argument when using this function.
  *
  * This also restores control back to whatever context that was active prior to this call.
  *
  * @return Size of finished display list
**/
static inline int sceGuFinish(void);

/**
  * Finish current display list and go back to the parent context, sending argument id for
  * the finish callback.
  *
  * If the context is GU_DIRECT, the stall-address is updated so that the entire list will
  * execute. Otherwise, only the terminating action is written to the list, depending on
  * context-type.
  *
  * @param id - Finish callback id (16-bit)
  * @return Size of finished display list
**/
static inline int sceGuFinishId(unsigned int id);

/**
  * Call previously generated display-list
  *
  * @param list - Display list to call
**/
static inline void sceGuCallList(const void *list);

/**
  * Set wether to use stack-based calls or signals to handle execution of called lists.
  *
  * @param mode - GU_TRUE(1) to enable signals, GU_FALSE(0) to disable signals and use
  * normal calls instead.
**/
static inline void sceGuCallMode(int mode);

/**
  * Check how large the current display-list is
  *
  * @return The size of the current display list
**/
static inline int sceGuCheckList(void);

/**
  * Send a list to the GE directly
  *
  * Available modes are:
  *   - GU_TAIL - Place list last in the queue, so it executes in-order
  *   - GU_HEAD - Place list first in queue so that it executes as soon as possible
  *
  * @param mode - Whether to place the list first or last in queue
  * @param list - List to send
  * @param context - Temporary storage for the GE context
  * @return 0 for success, < 0 for failure
**/
static inline int sceGuSendList(int mode, const void *list, PspGeContext *context);

/**
  * Swap display and draw buffer
  *
  * @return Pointer to the new drawbuffer
**/
static inline void *sceGuSwapBuffers(void);

/**
  * Wait until display list has finished executing
  *
  * @par Example: Wait for the currently executing display list
  * @code
  * sceGuSync(0,0);
  * @endcode
  *
  * Available what are:
  *   - GU_SYNC_WHAT_DONE
  *   - GU_SYNC_WHAT_QUEUED
  *   - GU_SYNC_WHAT_DRAW
  *   - GU_SYNC_WHAT_STALL
  *   - GU_SYNC_WHAT_CANCEL
  *
  * Available mode are:
  *   - GU_SYNC_FINISH - Wait until the last sceGuFinish command is reached
  *   - GU_SYNC_SIGNAL - Wait until the last (?) signal is executed
  *   - GU_SYNC_DONE - Wait until all commands currently in list are executed
  *   - GU_SYNC_LIST - Wait for the currently executed display list (GU_DIRECT)
  *   - GU_SYNC_SEND - Wait for the last send list
  *
  * @param mode - What to wait for
  * @param what - What to sync to
  * @return Unknown at this time
**/
static inline int sceGuSync(int mode, int what);

/**
  * Draw array of vertices forming primitives
  *
  * Available primitive-types are:
  *   - GU_POINTS - Single pixel points (1 vertex per primitive)
  *   - GU_LINES - Single pixel lines (2 vertices per primitive)
  *   - GU_LINE_STRIP - Single pixel line-strip (2 vertices for the first primitive, 1 for every following)
  *   - GU_TRIANGLES - Filled triangles (3 vertices per primitive)
  *   - GU_TRIANGLE_STRIP - Filled triangles-strip (3 vertices for the first primitive, 1 for every following)
  *   - GU_TRIANGLE_FAN - Filled triangle-fan (3 vertices for the first primitive, 1 for every following)
  *   - GU_SPRITES - Filled blocks (2 vertices per primitive)
  *
  * The vertex-type decides how the vertices align and what kind of information they contain.\n
  * The following flags are ORed together to compose the final vertex format:
  *   - GU_TEXTURE_8BIT - 8-bit texture coordinates
  *   - GU_TEXTURE_16BIT - 16-bit texture coordinates
  *   - GU_TEXTURE_32BITF - 32-bit texture coordinates (float)
  *
  *   - GU_COLOR_5650 - 16-bit color (R5G6B5A0)
  *   - GU_COLOR_5551 - 16-bit color (R5G5B5A1)
  *   - GU_COLOR_4444 - 16-bit color (R4G4B4A4)
  *   - GU_COLOR_8888 - 32-bit color (R8G8B8A8)
  *
  *   - GU_NORMAL_8BIT - 8-bit normals
  *   - GU_NORMAL_16BIT - 16-bit normals
  *   - GU_NORMAL_32BITF - 32-bit normals (float)
  *
  *   - GU_VERTEX_8BIT - 8-bit vertex position
  *   - GU_VERTEX_16BIT - 16-bit vertex position
  *   - GU_VERTEX_32BITF - 32-bit vertex position (float)
  *
  *   - GU_WEIGHT_8BIT - 8-bit weights
  *   - GU_WEIGHT_16BIT - 16-bit weights
  *   - GU_WEIGHT_32BITF - 32-bit weights (float)
  *
  *   - GU_INDEX_8BIT - 8-bit vertex index
  *   - GU_INDEX_16BIT - 16-bit vertex index
  *
  *   - GU_WEIGHTS(n) - Number of weights (1-8)
  *   - GU_VERTICES(n) - Number of vertices (1-8)
  *
  *   - GU_TRANSFORM_2D - Coordinate is passed directly to the rasterizer
  *   - GU_TRANSFORM_3D - Coordinate is transformed before passed to rasterizer
  *
  * Data members inside a vertex are laid out in the following order:
  * - Weights - if GU_WEIGHTS(n) is used N weights are present
  * - Texture Coordinates
  * - Color
  * - Normal
  * - Position
  *
  * If GU_VERTICES(n) is used the entire vertex structure is repeated N-times.\n
  * A member is only present if related type flag has been used (look at examples below).
  *
  * @note Every member making up a vertex must be aligned to 16 bits.
  *
  * @par Notes on 16 bit vertex/texture/normal formats:
  *   - Values are stored as 16-bit signed integers, with a range of -32768 to 32767
  *   - In the floating point coordinate space this is mapped as -1.0 to 1.0
  *   - To scale this to be such that the value 1 in 16 bit space is 1 unit in floating point space, use sceGumScale() for vertices; (see pspgum.h)
  *      - You can technically use this to create whatever fixed-point space you want (a common one is 5 bits for the decimals)
  *      - Caveat: you need to use the sceGumDrawArray method to apply the affine transform to the vertices.
  *      - sceGuDrawArray() will not apply the affine transform to the vertices.
  *   - To scale this for texture coordinates use sceGuTexOffset() and sceGuTexScale() (see below)
  *   - You can't scale the normals with any functions, which is expected since normals by definition are unit vectors.
  *
  * @code
  * sceGumScale(32768.0f, 32768.0f, 32768.0f); // This is an identity mapping -- 1 unit in floating point space is 1 unit in 16-bit space
  * sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_16BIT, 3, 0, vertices);
  * @endcode
  *
  * @par Notes on 8 bit vertex/texture/normal formats:
  *   - Values are stored as 8-bit signed integers with a range of -128 to 127
  *   - In the floating point coordinate space this is mapped as -1.0 to 1.0
  *   - To scale this to be such that the value 1 in 8 bit space is 1 unit in floating point space, use sceGumScale() for vertices; (see above).
  *   - The scaling factor as demonstrated will be 128.0f.
  *   - See above for notes on texture and normals.
  *
  * @par Example: Render 400 triangles, with floating-point texture coordinates, and floating-point position, no indices
  * @code
  * sceGuDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_VERTEX_32BITF,400*3,0,vertices);
  * @endcode
  *
  * @param prim - What kind of primitives to render
  * @param vtype - Vertex type to process
  * @param count - How many vertices to process
  * @param indices - Optional pointer to an index-list
  * @param vertices - Pointer to a vertex-list
**/
static inline void sceGuDrawArray(int prim, int vtype, int count, const void *indices, const void *vertices);

/**
  * Begin conditional rendering of object
  *
  * If no vertices passed into this function are inside the scissor region, it will skip rendering
  * the object. There can be up to 32 levels of conditional testing, and all levels HAVE to
  * be terminated by sceGuEndObject().
  *
  * @par Example: test a boundingbox against the frustum, and if visible, render object
  * @code
  * sceGuBeginObject(GU_VERTEX_32BITF,8,0,boundingBox);
  *   sceGuDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_VERTEX_32BITF,vertexCount,0,vertices);
  * sceGuEndObject();
  * @endcode
  *
  * @param vtype - Vertex type to process
  * @param count - Number of vertices to test
  * @param indices - Optional list to an index-list
  * @param vertices - Pointer to a vertex-list
**/
static inline void sceGuBeginObject(int vtype, int count, const void *indices, const void *vertices);

/**
  * End conditional rendering of object
**/
static inline void sceGuEndObject(void);

/**
  * Enable or disable GE state
  *
  * Look at sceGuEnable() for a list of states
  *
  * @param state - Which state to change
  * @param status - Wether to enable or disable the state
**/
static inline void sceGuSetStatus(int state, int status);

/**
  * Get if state is currently enabled or disabled
  *
  * Look at sceGuEnable() for a list of states
  *
  * @param state - Which state to query about
  * @return Wether state is enabled or not
**/
static inline int sceGuGetStatus(int state);

/**
  * Set the status on all 22 available states
  *
  * Look at sceGuEnable() for a list of states
  *
  * @param status - Bit-mask (0-21) containing the status of all 22 states
**/
static inline void sceGuSetAllStatus(int status);

/**
  * Query status on all 22 available states
  *
  * Look at sceGuEnable() for a list of states
  *
  * @return Status of all 22 states as a bitmask (0-21)
**/
static inline int sceGuGetAllStatus(void);

/**
  * Enable GE state
  *
  * The currently available states are:
  *   - GU_ALPHA_TEST
  *   - GU_DEPTH_TEST
  *   - GU_SCISSOR_TEST
  *   - GU_BLEND
  *   - GU_CULL_FACE
  *   - GU_DITHER
  *   - GU_CLIP_PLANES
  *   - GU_TEXTURE_2D
  *   - GU_LIGHTING
  *   - GU_LIGHT0
  *   - GU_LIGHT1
  *   - GU_LIGHT2
  *   - GU_LIGHT3
  *   - GU_COLOR_LOGIC_OP
  *
  * @param state - Which state to enable
**/
static inline void sceGuEnable(int state);

/**
  * Disable GE state
  *
  * Look at sceGuEnable() for a list of states
  *
  * @param state - Which state to disable
**/
static inline void sceGuDisable(int state);

/**
  * Set light parameters
  *
  * Available light types are:
  *   - GU_DIRECTIONAL - Directional light
  *   - GU_POINTLIGHT - Single point of light
  *   - GU_SPOTLIGHT - Point-light with a cone
  *
  * Available light components are:
  *   - GU_AMBIENT_AND_DIFFUSE
  *   - GU_DIFFUSE_AND_SPECULAR
  *   - GU_UNKNOWN_LIGHT_COMPONENT
  *
  * @param light - Light index
  * @param type - Light type
  * @param components - Light components
  * @param position - Light position
**/
static inline void sceGuLight(int light, int type, int components, const ScePspFVector3 *position);

/**
  * Set light attenuation
  *
  * @param light - Light index
  * @param atten0 - Constant attenuation factor
  * @param atten1 - Linear attenuation factor
  * @param atten2 - Quadratic attenuation factor
**/
static inline void sceGuLightAtt(int light, float atten0, float atten1, float atten2);

/**
  * Set light color
  *
  * Available light components are:
  *   - GU_AMBIENT
  *   - GU_DIFFUSE
  *   - GU_SPECULAR
  *   - GU_AMBIENT_AND_DIFFUSE
  *   - GU_DIFFUSE_AND_SPECULAR
  *
  * @param light - Light index
  * @param component - Which component to set
  * @param color - Which color to use
**/
static inline void sceGuLightColor(int light, int component, unsigned int color);

/**
  * Set light mode
  *
  * Available light modes are:
  *   - GU_SINGLE_COLOR
  *   - GU_SEPARATE_SPECULAR_COLOR
  *
  * Separate specular colors are used to interpolate the specular component
  * independently, so that it can be added to the fragment after the texture color.
  *
  * @param mode - Light mode to use
**/
static inline void sceGuLightMode(int mode);

/**
  * Set spotlight parameters
  *
  * @param light - Light index
  * @param direction - Spotlight direction
  * @param exponent - Spotlight exponent
  * @param cutoff - Spotlight cutoff angle (in radians)
**/
static inline void sceGuLightSpot(int light, const ScePspFVector3 *direction, float exponent, float cutoff);

/**
  * Clear current drawbuffer
  *
  * Available clear-flags are (OR them together to get final clear-mode):
  *   - GU_COLOR_BUFFER_BIT - Clears the color-buffer
  *   - GU_STENCIL_BUFFER_BIT - Clears the stencil-buffer
  *   - GU_DEPTH_BUFFER_BIT - Clears the depth-buffer
  *
  * @param flags - Which part of the buffer to clear
**/
static inline void sceGuClear(int flags);

/**
  * Set the current clear-color
  *
  * @param color - Color to clear with
**/
static inline void sceGuClearColor(unsigned int color);

/**
  * Set the current clear-depth
  *
  * @param depth - Set which depth to clear with (0x0000-0xffff)
**/
static inline void sceGuClearDepth(unsigned int depth);

/**
  * Set the current stencil clear value
  *
  * @param stencil - Set which stencil value to clear with (0-255)
  *
**/
static inline void sceGuClearStencil(unsigned int stencil);

/**
  * Set mask for which bits of the pixels to write
  *
  * @param mask - Which bits to filter against writes
  *
**/
static inline void sceGuPixelMask(unsigned int mask);

/**
  * Set current primitive color
  *
  * @param color - Which color to use (overriden by vertex-colors)
**/
static inline void sceGuColor(unsigned int color);

/**
  * Set the color test function
  *
  * The color test is only performed while GU_COLOR_TEST is enabled.
  *
  * Available functions are:
  *   - GU_NEVER
  *   - GU_ALWAYS
  *   - GU_EQUAL
  *   - GU_NOTEQUAL
  *
  * @par Example: Reject any pixel that does not have 0 as the blue channel
  * @code
  * sceGuColorFunc(GU_EQUAL,0,0xff0000);
  * @endcode
  *
  * @param func - Color test function
  * @param color - Color to test against
  * @param mask - Mask ANDed against both source and destination when testing
**/
static inline void sceGuColorFunc(int func, unsigned int color, unsigned int mask);

/**
  * Set which color components that the material will receive
  *
  * The components are ORed together from the following values:
  *   - GU_AMBIENT
  *   - GU_DIFFUSE
  *   - GU_SPECULAR
  *
  * @param components - Which components to receive
**/
static inline void sceGuColorMaterial(int components);

/**
  * Set the alpha test parameters
  *
  * Available comparison functions are:
  *   - GU_NEVER
  *   - GU_ALWAYS
  *   - GU_EQUAL
  *   - GU_NOTEQUAL
  *   - GU_LESS
  *   - GU_LEQUAL
  *   - GU_GREATER
  *   - GU_GEQUAL
  *
  * @param func - Specifies the alpha comparison function.
  * @param value - Specifies the reference value that incoming alpha values are compared to.
  * @param mask - Specifies the mask that both values are ANDed with before comparison.
**/
static inline void sceGuAlphaFunc(int func, int value, int mask);

static inline void sceGuAmbient(unsigned int color);
static inline void sceGuAmbientColor(unsigned int color);

/**
  * Set the blending-mode
  *
  * Keys for the blending operations:
  *   - Cs - Source color
  *   - Cd - Destination color
  *   - Bs - Blend function for source fragment
  *   - Bd - Blend function for destination fragment
  *
  * Available blending-operations are:
  *   - GU_ADD - (Cs*Bs) + (Cd*Bd)
  *   - GU_SUBTRACT - (Cs*Bs) - (Cd*Bd)
  *   - GU_REVERSE_SUBTRACT - (Cd*Bd) - (Cs*Bs)
  *   - GU_MIN - Cs < Cd ? Cs : Cd
  *   - GU_MAX - Cs < Cd ? Cd : Cs
  *   - GU_ABS - |Cs-Cd|
  *
  * Available blending-functions are:
  *   - GU_SRC_COLOR
  *   - GU_ONE_MINUS_SRC_COLOR
  *   - GU_SRC_ALPHA
  *   - GU_ONE_MINUS_SRC_ALPHA
  *   - GU_DST_ALPHA
  *   - GU_ONE_MINUS_DST_ALPHA
  *   - GU_DST_COLOR
  *   - GU_ONE_MINUS_DST_COLOR
  *   - GU_FIX
  *
  * @param op - Blending Operation
  * @param src - Blending function for source operand
  * @param dest - Blending function for dest operand
  * @param srcfix - Fix value for GU_FIX (source operand)
  * @param destfix - Fix value for GU_FIX (dest operand)
**/
static inline void sceGuBlendFunc(int op, int src, int dest, unsigned int srcfix, unsigned int destfix);

static inline void sceGuMaterial(int mode, int color);

/**
  *
**/
static inline void sceGuModelColor(unsigned int emissive, unsigned int ambient, unsigned int diffuse, unsigned int specular);

/**
  * Set stencil function and reference value for stencil testing
  *
  * Available functions are:
  *   - GU_NEVER
  *   - GU_ALWAYS
  *   - GU_EQUAL
  *   - GU_NOTEQUAL
  *   - GU_LESS
  *   - GU_LEQUAL
  *   - GU_GREATER
  *   - GU_GEQUAL
  *
  * @param func - Test function
  * @param ref - The reference value for the stencil test
  * @param mask - Mask that is ANDed with both the reference value and stored stencil value when the test is done
**/
static inline void sceGuStencilFunc(int func, int ref, int mask);

/**
  * Set the stencil test actions
  *
  * Available actions are:
  *   - GU_KEEP - Keeps the current value
  *   - GU_ZERO - Sets the stencil buffer value to zero
  *   - GU_REPLACE - Sets the stencil buffer value to ref, as specified by sceGuStencilFunc()
  *   - GU_INCR - Increments the current stencil buffer value
  *   - GU_DECR - Decrease the current stencil buffer value
  *   - GU_INVERT - Bitwise invert the current stencil buffer value
  *
  * As stencil buffer shares memory with framebuffer alpha, resolution of the buffer
  * is directly in relation.
  *
  * @param fail - The action to take when the stencil test fails
  * @param zfail - The action to take when stencil test passes, but the depth test fails
  * @param zpass - The action to take when both stencil test and depth test passes
**/
static inline void sceGuStencilOp(int fail, int zfail, int zpass);

/**
  * Set the specular power for the material
  *
  * @param power - Specular power
  *
**/
static inline void sceGuSpecular(float power);

/**
  * Set the current face-order (for culling)
  *
  * This only has effect when culling is enabled (GU_CULL_FACE)
  *
  * Culling order can be:
  *   - GU_CW - Clockwise primitives are not culled
  *   - GU_CCW - Counter-clockwise are not culled
  *
  * @param order - Which order to use
**/
static inline void sceGuFrontFace(int order);

/**
  * Set color logical operation
  *
  * Available operations are:
  *   - GU_CLEAR
  *   - GU_AND
  *   - GU_AND_REVERSE
  *   - GU_COPY
  *   - GU_AND_INVERTED
  *   - GU_NOOP
  *   - GU_XOR
  *   - GU_OR
  *   - GU_NOR
  *   - GU_EQUIV
  *   - GU_INVERTED
  *   - GU_OR_REVERSE
  *   - GU_COPY_INVERTED
  *   - GU_OR_INVERTED
  *   - GU_NAND
  *   - GU_SET
  *
  * This operation only has effect if GU_COLOR_LOGIC_OP is enabled.
  *
  * @param op - Operation to execute
**/
static inline void sceGuLogicalOp(int op);

/**
  * Set ordered pixel dither matrix
  *
  * This dither matrix is only applied if GU_DITHER is enabled.
  *
  * @param matrix - Dither matrix
**/
static inline void sceGuSetDither(const ScePspIMatrix4 *matrix);

/**
  * Set how primitives are shaded
  *
  * The available shading-methods are:
  *   - GU_FLAT - Primitives are flatshaded, the last vertex-color takes effet
  *   - GU_SMOOTH - Primtives are gouraud-shaded, all vertex-colors take effect
  *
  * @param mode - Which mode to use
**/
static inline void sceGuShadeModel(int mode);

/**
  * Image transfer using the GE
  *
  * @note Data must be aligned to 1 quad word (16 bytes)
  *
  * @par Example: Copy a fullscreen 32-bit image from RAM to VRAM
  * @code
  * sceGuCopyImage(GU_PSM_8888,0,0,480,272,512,pixels,0,0,512,(void*)(((unsigned int)framebuffer)+0x4000000));
  * @endcode
  *
  * @param psm - Pixel format for buffer
  * @param sx - Source X
  * @param sy - Source Y
  * @param width - Image width
  * @param height - Image height
  * @param srcw - Source buffer width (block aligned)
  * @param src - Source pointer
  * @param dx - Destination X
  * @param dy - Destination Y
  * @param destw - Destination buffer width (block aligned)
  * @param dest - Destination pointer
**/
static inline void sceGuCopyImage(int psm, int sx, int sy, int width, int height, int srcw, void *src, int dx, int dy, int destw, void *dest);

/**
  * Specify the texture environment color
  *
  * This is used in the texture function when a constant color is needed.
  *
  * See sceGuTexFunc() for more information.
  *
  * @param color - Constant color (0x00BBGGRR)
**/
static inline void sceGuTexEnvColor(unsigned int color);

/**
  * Set how the texture is filtered
  *
  * Available filters are:
  *   - GU_NEAREST
  *   - GU_LINEAR
  *   - GU_NEAREST_MIPMAP_NEAREST
  *   - GU_LINEAR_MIPMAP_NEAREST
  *   - GU_NEAREST_MIPMAP_LINEAR
  *   - GU_LINEAR_MIPMAP_LINEAR
  *
  * @param min - Minimizing filter
  * @param mag - Magnifying filter
**/
static inline void sceGuTexFilter(int min, int mag);

/**
  * Flush texture page-cache
  *
  * Do this if you have copied/rendered into an area currently in the texture-cache
  *
**/
static inline void sceGuTexFlush(void);

/**
  * Set how textures are applied
  *
  * Key for the apply-modes:
  *   - Cv - Color value result
  *   - Ct - Texture color
  *   - Cf - Fragment color
  *   - Cc - Constant color (specified by sceGuTexEnvColor())
  *
  * Available apply-modes are: (TFX)
  *   - GU_TFX_MODULATE - Cv=Ct*Cf TCC_RGB: Av=Af TCC_RGBA: Av=At*Af
  *   - GU_TFX_DECAL - TCC_RGB: Cv=Ct,Av=Af TCC_RGBA: Cv=Cf*(1-At)+Ct*At Av=Af
  *   - GU_TFX_BLEND - Cv=(Cf*(1-Ct))+(Cc*Ct) TCC_RGB: Av=Af TCC_RGBA: Av=At*Af
  *   - GU_TFX_REPLACE - Cv=Ct TCC_RGB: Av=Af TCC_RGBA: Av=At
  *   - GU_TFX_ADD - Cv=Cf+Ct TCC_RGB: Av=Af TCC_RGBA: Av=At*Af
  *
  * The fields TCC_RGB and TCC_RGBA specify components that differ between
  * the two different component modes.
  *
  *   - GU_TFX_MODULATE - The texture is multiplied with the current diffuse fragment
  *   - GU_TFX_REPLACE - The texture replaces the fragment
  *   - GU_TFX_ADD - The texture is added on-top of the diffuse fragment
  *
  * Available component-modes are: (TCC)
  *   - GU_TCC_RGB - The texture alpha does not have any effect
  *   - GU_TCC_RGBA - The texture alpha is taken into account
  *
  * @param tfx - Which apply-mode to use
  * @param tcc - Which component-mode to use
**/
static inline void sceGuTexFunc(int tfx, int tcc);

/**
  * Set current texturemap
  *
  * Textures may reside in main RAM, but it has a huge speed-penalty. Swizzle textures
  * to get maximum speed.
  *
  * @note Data must be aligned to 1 quad word (16 bytes)
  *
  * @param mipmap - Mipmap level
  * @param width - Width of texture (must be a power of 2)
  * @param height - Height of texture (must be a power of 2)
  * @param tbw - Texture Buffer Width (block-aligned)
  * @param tbp - Texture buffer pointer (16 byte aligned)
**/
static inline void sceGuTexImage(int mipmap, int width, int height, int tbw, const void *tbp);

/**
  * Set texture-level mode (mipmapping)
  *
  * Available modes are:
  *   - GU_TEXTURE_AUTO
  *   - GU_TEXTURE_CONST
  *   - GU_TEXTURE_SLOPE
  *
  * @param mode - Which mode to use
  * @param bias - Which mipmap bias to use
**/
static inline void sceGuTexLevelMode(unsigned int mode, float bias);

/**
  * Set the texture-mapping mode
  *
  * Available modes are:
  *   - GU_TEXTURE_COORDS
  *   - GU_TEXTURE_MATRIX
  *   - GU_ENVIRONMENT_MAP
  *
  * @param mode - Which mode to use
  * @param a1 - Unknown
  * @param a2 - Unknown
**/
static inline void sceGuTexMapMode(int mode, unsigned int a1, unsigned int a2);

/**
  * Set texture-mode parameters
  *
  * Available texture-formats are:
  *   - GU_PSM_5650 - Hicolor, 16-bit
  *   - GU_PSM_5551 - Hicolor, 16-bit
  *   - GU_PSM_4444 - Hicolor, 16-bit
  *   - GU_PSM_8888 - Truecolor, 32-bit
  *   - GU_PSM_T4 - Indexed, 4-bit (2 pixels per byte)
  *   - GU_PSM_T8 - Indexed, 8-bit
  *
  * @param tpsm - Which texture format to use
  * @param maxmips - Number of mipmaps to use (0-8)
  * @param a2 - Unknown, set to 0
  * @param swizzle - GU_TRUE(1) to swizzle texture-reads
**/
static inline void sceGuTexMode(int tpsm, int maxmips, int a2, int swizzle);

/**
  * Set texture offset
  *
  * @note Only used by the 3D T&L pipe, renders done with GU_TRANSFORM_2D are
  * not affected by this.
  *
  * @param u - Offset to add to the U coordinate
  * @param v - Offset to add to the V coordinate
**/
static inline void sceGuTexOffset(float u, float v);

/**
  * Set texture projection-map mode
  *
  * Available modes are:
  *   - GU_POSITION
  *   - GU_UV
  *   - GU_NORMALIZED_NORMAL
  *   - GU_NORMAL
  *
  * @param mode - Which mode to use
**/
static inline void sceGuTexProjMapMode(int mode);

/**
  * Set texture scale
  *
  * @note Only used by the 3D T&L pipe, renders ton with GU_TRANSFORM_2D are
  * not affected by this.
  *
  * @param u - Scalar to multiply U coordinate with
  * @param v - Scalar to multiply V coordinate with
**/
static inline void sceGuTexScale(float u, float v);
static inline void sceGuTexSlope(float slope);

/**
  * Synchronize rendering pipeline with image upload.
  *
  * This will stall the rendering pipeline until the current image upload initiated by
  * sceGuCopyImage() has completed.
**/
static inline void sceGuTexSync();

/**
  * Set if the texture should repeat or clamp
  *
  * Available modes are:
  *   - GU_REPEAT - The texture repeats after crossing the border
  *   - GU_CLAMP - Texture clamps at the border
  *
  * @param u - Wrap-mode for the U direction
  * @param v - Wrap-mode for the V direction
**/
static inline void sceGuTexWrap(int u, int v);

/**
  * Upload CLUT (Color Lookup Table)
  *
  * @note Data must be aligned to 1 quad word (16 bytes)
  *
  * @param num_blocks - How many blocks of 8 entries to upload (32*8 is 256 colors)
  * @param cbp - Pointer to palette (16 byte aligned)
**/
static inline void sceGuClutLoad(int num_blocks, const void *cbp);

/**
  * Set current CLUT mode
  *
  * Available pixel formats for palettes are:
  *   - GU_PSM_5650
  *   - GU_PSM_5551
  *   - GU_PSM_4444
  *   - GU_PSM_8888
  *
  * @param cpsm - Which pixel format to use for the palette
  * @param shift - Shifts color index by that many bits to the right
  * @param mask - Masks the color index with this bitmask after the shift (0-0xFF)
  * @param a3 - Unknown, set to 0
**/
static inline void sceGuClutMode(unsigned int cpsm, unsigned int shift, unsigned int mask, unsigned int a3);

/**
  * Set virtual coordinate offset
  *
  * The PSP has a virtual coordinate-space of 4096x4096, this controls where rendering is performed
  *
  * @par Example: Center the virtual coordinate range
  * @code
  * sceGuOffset(2048-(480/2),2048-(480/2));
  * @endcode
  *
  * @param x - Offset (0-4095)
  * @param y - Offset (0-4095)
**/
static inline void sceGuOffset(unsigned int x, unsigned int y);

/**
  * Set what to scissor within the current viewport
  *
  * Note that scissoring is only performed if the custom scissoring is enabled (GU_SCISSOR_TEST)
  *
  * @param x - Left of scissor region
  * @param y - Top of scissor region
  * @param w - Width of scissor region
  * @param h - Height of scissor region
**/
static inline void sceGuScissor(int x, int y, int w, int h);

/**
  * Set current viewport
  *
  * @par Example: Setup a viewport of size (480,272) with origo at (2048,2048)
  * @code
  * sceGuViewport(2048,2048,480,272);
  * @endcode
  *
  * @param cx - Center for horizontal viewport
  * @param cy - Center for vertical viewport
  * @param width - Width of viewport
  * @param height - Height of viewport
**/
static inline void sceGuViewport(int cx, int cy, int width, int height);

/**
  * Draw bezier surface
  *
  * @param vtype - Vertex type, look at sceGuDrawArray() for vertex definition
  * @param ucount - Number of vertices used in the U direction
  * @param vcount - Number of vertices used in the V direction
  * @param indices - Pointer to index buffer
  * @param vertices - Pointer to vertex buffer
**/
static inline void sceGuDrawBezier(int vtype, int ucount, int vcount, const void *indices, const void *vertices);

/**
  * Set dividing for patches (beziers and splines)
  *
  * @param ulevel - Number of division on u direction
  * @param vlevel - Number of division on v direction
**/
static inline void sceGuPatchDivide(unsigned int ulevel, unsigned int vlevel);

static inline void sceGuPatchFrontFace(unsigned int a0);

/**
  * Set primitive for patches (beziers and splines)
  *
  * @param prim - Desired primitive type (GU_POINTS | GU_LINE_STRIP | GU_TRIANGLE_STRIP)
**/
static inline void sceGuPatchPrim(int prim);

static inline void sceGuDrawSpline(int vtype, int ucount, int vcount, int uedge, int vedge, const void *indices, const void *vertices);

/**
  * Set transform matrices
  *
  * Available matrices are:
  *   - GU_PROJECTION - View->Projection matrix
  *   - GU_VIEW - World->View matrix
  *   - GU_MODEL - Model->World matrix
  *   - GU_TEXTURE - Texture matrix
  *
  * @param type - Which matrix-type to set
  * @param matrix - Matrix to load
**/
static inline void sceGuSetMatrix(int type, const ScePspFMatrix4 *matrix);

/**
  * Specify skinning matrix entry
  *
  * To enable vertex skinning, pass GU_WEIGHTS(n), where n is between
  * 1-8, and pass available GU_WEIGHT_??? declaration. This will change
  * the amount of weights passed in the vertex araay, and by setting the skinning,
  * matrices, you will multiply each vertex every weight and vertex passed.
  *
  * Please see sceGuDrawArray() for vertex format information.
  *
  * @param index - Skinning matrix index (0-7)
  * @param matrix - Matrix to set
**/
static inline void sceGuBoneMatrix(unsigned int index, const ScePspFMatrix4 *matrix);

/**
  * Specify morph weight entry
  *
  * To enable vertex morphing, pass GU_VERTICES(n), where n is between
  * 1-8. This will change the amount of vertices passed in the vertex array,
  * and by setting the morph weights for every vertex entry in the array,
  * you can blend between them.
  *
  * Please see sceGuDrawArray() for vertex format information.
  *
  * @param index - Morph weight index (0-7)
  * @param weight - Weight to set
**/
static inline void sceGuMorphWeight(int index, float weight);

static inline void sceGuDrawArrayN(int primitive_type, int vertex_type, int count, int a3, const void *indices, const void *vertices);

/**
  * Set how the display should be set
  *
  * Available behaviours are:
  *   - PSP_DISPLAY_SETBUF_IMMEDIATE - Display is swapped immediately
  *   - PSP_DISPLAY_SETBUF_NEXTFRAME - Display is swapped on the next frame
  *
  * Do remember that this swaps the pointers internally, regardless of setting, so be careful to wait until the next
  * vertical blank or use another buffering algorithm (see guSwapBuffersCallback()).
**/
static inline void guSwapBuffersBehaviour(int behaviour);

/**
  * Set a buffer swap callback to allow for more advanced buffer methods without hacking the library.
  *
  * The GuSwapBuffersCallback is defined like this:
  * @code
  * void swapBuffersCallback(void** display, void** render);
  * @endcode
  * and on entry they contain the variables that are to be set. To change the pointers that will be used, just
  * write the new pointers. Example of a triple-buffering algorithm:
  * @code
  * void* doneBuffer;
  * void swapBuffersCallback(void** display, void** render)
  * {
  *  void* active = doneBuffer;
  *  doneBuffer = *display;
     *display = active;
  * }
  * @endcode
  *
  * @param callback - Callback to access when buffers are swapped. Pass 0 to disable.
**/
static inline void guSwapBuffersCallback(GuSwapBuffersCallback callback);

/**
  * Allocate a draw buffer in vram
  *
  * Available pixel formats are:
  *   - GU_PSM_5650 - Hicolor, 16-bit
  *   - GU_PSM_5551 - Hicolor, 16-bit
  *   - GU_PSM_4444 - Hicolor, 16-bit
  *   - GU_PSM_8888 - Truecolor, 32-bit
  *
  * @param width - Width of the buffer, usually 512 (must be a power of 2)
  * @param height - Height of the buffer, normally the height of the screen 272
  * @param psm - Which pixel format to use
  * 
  * @return A pointer to the buffer's relative to vram start (as required by sceGuDispBuffer, sceGuDrawBuffer, sceGuDepthBuffer and sceGuDrawBufferList)
**/
void* guGetStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm);

/**
  * Allocate a texture in vram
  *
  * Available texture-formats are:
  *   - GU_PSM_5650 - Hicolor, 16-bit
  *   - GU_PSM_5551 - Hicolor, 16-bit
  *   - GU_PSM_4444 - Hicolor, 16-bit
  *   - GU_PSM_8888 - Truecolor, 32-bit
  *   - GU_PSM_T4 - Indexed, 4-bit (2 pixels per byte)
  *   - GU_PSM_T8 - Indexed, 8-bit
  *
  * @param width - Width of the texture (must be a power of 2)
  * @param height - Height of the texture (must be a power of 2)
  * @param psm - Which pixel format to use
  * 
  * @return A pointer to the texture
**/
void* guGetStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm);

/**
  * Get state of display
  *
  * Available states are:
  *   - GU_TRUE (1) - Display is turned on
  *   - GU_FALSE (0) - Display is turned off
  *
  * @return State of the display
**/
static inline int guGetDisplayState();

//////////////////////// ALL THE INTERNALS & INLINE IMPLEMENTATIONS ////////////////////////

typedef struct
{
  GuCallback sig;
  GuCallback fin;
  short signal_history[16];
  int signal_offset;
  int kernel_event_flag;
  int ge_callback_id;

  GuSwapBuffersCallback swapBuffersCallback;
  int swapBuffersBehaviour;
} GuSettings;

typedef struct
{
  unsigned int *start;
  unsigned int *current;
  int parent_context;
} GuDisplayList;

typedef struct
{
  GuDisplayList list;
  int scissor_enable;
  int scissor_start[2];
  int scissor_end[2];
  int near_plane;
  int far_plane;
  int depth_offset;
  int fragment_2x;
  int texture_function;
  int texture_proj_map_mode;
  int texture_map_mode;
  int sprite_mode[4];
  unsigned int clear_color;
  unsigned int clear_stencil;
  unsigned int clear_depth;
  int texture_mode;
} GuContext;

typedef struct
{
  int pixel_size;
  int frame_width;
  void *frame_buffer;
  void *disp_buffer;
  void *depth_buffer;
  int depth_width;
  int width;
  int height;
} GuDrawBuffer;

typedef struct
{
  /* row 0 */

  unsigned char enable; // Light enable
  unsigned char type;   // Light type
  unsigned char xpos;   // X position
  unsigned char ypos;   // Y position

  /* row 1 */

  unsigned char zpos; // Z position
  unsigned char xdir; // X direction
  unsigned char ydir; // Y direction
  unsigned char zdir; // Z direction

  /* row 2 */

  unsigned char ambient;  // Ambient color
  unsigned char diffuse;  // Diffuse color
  unsigned char specular; // Specular color
  unsigned char constant; // Constant attenuation

  /* row 3 */

  unsigned char linear;    // Linear attenuation
  unsigned char quadratic; // Quadratic attenuation
  unsigned char exponent;  // Light exponent
  unsigned char cutoff;    // Light cutoff
} GuLightSettings;

extern unsigned int gu_current_frame;
extern GuContext gu_contexts[3];
extern int ge_list_executed[2];
extern void *ge_edram_address;
extern GuSettings gu_settings;
extern GuDisplayList *gu_list;
extern int gu_curr_context;
extern int gu_init;
extern int gu_display_on;
extern int gu_call_mode;
extern int gu_states;
extern GuDrawBuffer gu_draw_buffer;

extern unsigned int *gu_object_stack[];
extern int gu_object_stack_depth;

extern GuLightSettings light_settings[4];

typedef enum GECommand
{
  /* No operation */
  NOP = 0x0,
  /* Vertex data */
  VADDR = 0x1,
  /* Index data */
  IADDR = 0x2,
  /* Draw Primitive */
  PRIM = 0x4,
  /* Draw Bezier surface */
  BEZIER = 0x5,
  /* Draw Spline surface */
  SPLINE = 0x6,
  /* Bounding Box */
  BOUNDING_BOX = 0x7,
  /* Jump */
  JUMP = 0x8,
  /* Conditional Jump */
  BJUMP = 0x9,
  /* List Call */
  CALL = 0xa,
  /* List Return */
  RET = 0xb,
  /* End reading */
  END = 0xc,
  /* Signal interrupt */
  SIGNAL = 0xe,
  /* Finish drawing */
  FINISH = 0xf,
  /* Address base */
  BASE = 0x10,
  /* Vertex type */
  VERTEX_TYPE = 0x12,
  /* Offset address */
  OFFSET_ADDR = 0x13,
  /* Origin address */
  ORIGIN = 0x14,
  /* Drawing region 1, origin */
  REGION1 = 0x15,
  /* Drawing region 2, end */
  REGION2 = 0x16,

  /* Lighting enable */
  LIGHTING_ENABLE = 0x17,
  /* Light 0 enable */
  LIGHT_ENABLE0 = 0x18,
  /* Light 1 enable */
  LIGHT_ENABLE1 = 0x19,
  /* Light 2 enable */
  LIGHT_ENABLE2 = 0x1a,
  /* Light 3 enable */
  LIGHT_ENABLE3 = 0x1b,
  /* Clipping enable */
  DEPTH_CLIP_ENABLE = 0x1c,
  /* Culling enable */
  CULL_FACE_ENABLE = 0x1d,
  /* Texture mapping enable */
  TEXTURE_ENABLE = 0x1e,
  /* Fog enable */
  FOG_ENABLE = 0x1f,
  /* Dithering enable */
  DITHER_ENABLE = 0x20,
  /* Alpha blending enable */
  ALPHA_BLEND_ENABLE = 0x21,
  /* Alpha testing enable */
  ALPHA_TEST_ENABLE = 0x22,
  /* Z testing enable */
  Z_TEST_ENABLE = 0x23,
  /* Stencil testing enable */
  STENCIL_TEST_ENABLE = 0x24,
  /* Anti-aliasing enable */
  ANTI_ALIAS_ENABLE = 0x25,
  /* Patch culling enable */
  PATCH_CULL_ENABLE = 0x26,
  /* Color testing enable */
  COLOR_TEST_ENABLE = 0x27,
  /* Logical operation enable */
  LOGIC_OP_ENABLE = 0x28,

  /* Bone matrix number */
  BONE_MATRIX_NUMBER = 0x2a,
  /* Bone matrix data */
  BONE_MATRIX_DATA = 0x2b,
  /* Morph weight 0 */
  MORPH_WEIGHT0 = 0x2c,
  /* Morph weight 1 */
  MORPH_WEIGHT1 = 0x2d,
  /* Morph weight 2 */
  MORPH_WEIGHT2 = 0x2e,
  /* Morph weight 3 */
  MORPH_WEIGHT3 = 0x2f,
  /* Morph weight 4 */
  MORPH_WEIGHT4 = 0x30,
  /* Morph weight 5 */
  MORPH_WEIGHT5 = 0x31,
  /* Morph weight 6 */
  MORPH_WEIGHT6 = 0x32,
  /* Morph weight 7 */
  MORPH_WEIGHT7 = 0x33,

  /* Patch division count */
  PATCH_DIVISION = 0x36,
  /* Patch primitive type */
  PATCH_PRIMITIVE = 0x37,
  /* Patch facing */
  PATCH_FACING = 0x38,
  /* World matrix number */
  WORLD_MATRIX_NUMBER = 0x3a,
  /* World matrix data */
  WORLD_MATRIX_DATA = 0x3b,
  /* View matrix number */
  VIEW_MATRIX_NUMBER = 0x3c,
  /* View matrix data */
  VIEW_MATRIX_DATA = 0x3d,
  /* Projection matrix number */
  PROJ_MATRIX_NUMBER = 0x3e,
  /* Projection matrix data */
  PROJ_MATRIX_DATA = 0x3f,
  /* Texture generation matrix number */
  TGEN_MATRIX_NUMBER = 0x40,
  /* Texture generation matrix data */
  TGEN_MATRIX_DATA = 0x41,

  /* Viewport X scale */
  VIEWPORT_X_SCALE = 0x42,
  /* Viewport Y scale */
  VIEWPORT_Y_SCALE = 0x43,
  /* Viewport Z scale */
  VIEWPORT_Z_SCALE = 0x44,
  /* Viewport X center */
  VIEWPORT_X_CENTER = 0x45,
  /* Viewport Y center */
  VIEWPORT_Y_CENTER = 0x46,
  /* Viewport Z center */
  VIEWPORT_Z_CENTER = 0x47,
  /* Texture scale U */
  TEX_SCALE_U = 0x48,
  /* Texture scale V */
  TEX_SCALE_V = 0x49,
  /* Texture offset U */
  TEX_OFFSET_U = 0x4a,
  /* Texture offset V */
  TEX_OFFSET_V = 0x4b,
  /* Screen Offset X */
  OFFSET_X = 0x4c,
  /* Screen Offset Y */
  OFFSET_Y = 0x4d,

  /* Shade mode */
  SHADE_MODE = 0x50,
  /* Normal reverse */
  NORMAL_REVERSE = 0x51,
  /* Material color */
  MATERIAL_COLOR = 0x53,
  /* Material emissive */
  MATERIAL_EMISSIVE = 0x54,
  /* Ambient color */
  AMBIENT_COLOR = 0x55,
  /* Material diffuse */
  MATERIAL_DIFFUSE = 0x56,
  /* Material specular */
  MATERIAL_SPECULAR = 0x57,
  /* Ambient alpha */
  AMBIENT_ALPHA = 0x58,
  /* Material specular coefficient */
  MATERIAL_SPECULAR_COEF = 0x5b,
  /* Ambient light color */
  AMBIENT_LIGHT_COLOR = 0x5c,
  /* Ambient light alpha */
  AMBIENT_LIGHT_ALPHA = 0x5d,
  /* Light mode */
  LIGHT_MODE = 0x5e,

  /* Light type 0 */
  LIGHT_TYPE0 = 0x5f,
  /* Light type 1 */
  LIGHT_TYPE1 = 0x60,
  /* Light type 2 */
  LIGHT_TYPE2 = 0x61,
  /* Light type 3 */
  LIGHT_TYPE3 = 0x62,
  /* Light 0 X */
  LIGHT0_X = 0x63,
  /* Light 0 Y */
  LIGHT0_Y = 0x64,
  /* Light 0 Z */
  LIGHT0_Z = 0x65,
  /* Light 1 X */
  LIGHT1_X = 0x66,
  /* Light 1 Y */
  LIGHT1_Y = 0x67,
  /* Light 1 Z */
  LIGHT1_Z = 0x68,
  /* Light 2 X */
  LIGHT2_X = 0x69,
  /* Light 2 Y */
  LIGHT2_Y = 0x6a,
  /* Light 2 Z */
  LIGHT2_Z = 0x6b,
  /* Light 3 X */
  LIGHT3_X = 0x6c,
  /* Light 3 Y */
  LIGHT3_Y = 0x6d,
  /* Light 3 Z */
  LIGHT3_Z = 0x6e,

  /* Light 0 direction X */
  LIGHT0_DIRECTION_X = 0x6f,
  /* Light 0 direction Y */
  LIGHT0_DIRECTION_Y = 0x70,
  /* Light 0 direction Z */
  LIGHT0_DIRECTION_Z = 0x71,
  /* Light 1 direction X */
  LIGHT1_DIRECTION_X = 0x72,
  /* Light 1 direction Y */
  LIGHT1_DIRECTION_Y = 0x73,
  /* Light 1 direction Z */
  LIGHT1_DIRECTION_Z = 0x74,
  /* Light 2 direction X */
  LIGHT2_DIRECTION_X = 0x75,
  /* Light 2 direction Y */
  LIGHT2_DIRECTION_Y = 0x76,
  /* Light 2 direction Z */
  LIGHT2_DIRECTION_Z = 0x77,
  /* Light 3 direction X */
  LIGHT3_DIRECTION_X = 0x78,
  /* Light 3 direction Y */
  LIGHT3_DIRECTION_Y = 0x79,
  /* Light 3 direction Z */
  LIGHT3_DIRECTION_Z = 0x7a,

  /* Light 0 constant attenuation */
  LIGHT0_CONSTANT_ATTEN = 0x7b,
  /* Light 0 linear attenuation */
  LIGHT0_LINEAR_ATTEN = 0x7c,
  /* Light 0 quadratic attenuation */
  LIGHT0_QUADRATIC_ATTEN = 0x7d,
  /* Light 1 constant attenuation */
  LIGHT1_CONSTANT_ATTEN = 0x7e,
  /* Light 1 linear attenuation */
  LIGHT1_LINEAR_ATTEN = 0x7f,
  /* Light 1 quadratic attenuation */
  LIGHT1_QUADRATIC_ATTEN = 0x80,
  /* Light 2 constant attenuation */
  LIGHT2_CONSTANT_ATTEN = 0x81,
  /* Light 2 linear attenuation */
  LIGHT2_LINEAR_ATTEN = 0x82,
  /* Light 2 quadratic attenuation */
  LIGHT2_QUADRATIC_ATTEN = 0x83,
  /* Light 3 constant attenuation */
  LIGHT3_CONSTANT_ATTEN = 0x84,
  /* Light 3 linear attenuation */
  LIGHT3_LINEAR_ATTEN = 0x85,
  /* Light 3 quadratic attenuation */
  LIGHT3_QUADRATIC_ATTEN = 0x86,

  /* Light 0 exponent attenuation */
  LIGHT0_EXPONENT_ATTEN = 0x87,
  /* Light 1 exponent attenuation */
  LIGHT1_EXPONENT_ATTEN = 0x88,
  /* Light 2 exponent attenuation */
  LIGHT2_EXPONENT_ATTEN = 0x89,
  /* Light 3 exponent attenuation */
  LIGHT3_EXPONENT_ATTEN = 0x8a,

  /* Light 0 cutoff attenuation */
  LIGHT0_CUTOFF_ATTEN = 0x8b,
  /* Light 1 cutoff attenuation */
  LIGHT1_CUTOFF_ATTEN = 0x8c,
  /* Light 2 cutoff attenuation */
  LIGHT2_CUTOFF_ATTEN = 0x8d,
  /* Light 3 cutoff attenuation */
  LIGHT3_CUTOFF_ATTEN = 0x8e,

  /* Light 0 ambient */
  LIGHT0_AMBIENT = 0x8f,
  /* Light 0 diffuse */
  LIGHT0_DIFFUSE = 0x90,
  /* Light 0 specular */
  LIGHT0_SPECULAR = 0x91,
  /* Light 1 ambient */
  LIGHT1_AMBIENT = 0x92,
  /* Light 1 diffuse */
  LIGHT1_DIFFUSE = 0x93,
  /* Light 1 specular */
  LIGHT1_SPECULAR = 0x94,
  /* Light 2 ambient */
  LIGHT2_AMBIENT = 0x95,
  /* Light 2 diffuse */
  LIGHT2_DIFFUSE = 0x96,
  /* Light 2 specular */
  LIGHT2_SPECULAR = 0x97,
  /* Light 3 ambient */
  LIGHT3_AMBIENT = 0x98,
  /* Light 3 diffuse */
  LIGHT3_DIFFUSE = 0x99,
  /* Light 3 specular */
  LIGHT3_SPECULAR = 0x9a,

  /* Culling */
  CULL = 0x9b,

  /* Frame buffer pointer */
  FRAME_BUF_PTR = 0x9c,
  /* Frame buffer width */
  FRAME_BUF_WIDTH = 0x9d,
  /* Z buffer pointer */
  Z_BUF_PTR = 0x9e,
  /* Z buffer width */
  Z_BUF_WIDTH = 0x9f,

  /* Texture address 0 */
  TEX_ADDR0 = 0xa0,
  /* Texture address 1 */
  TEX_ADDR1 = 0xa1,
  /* Texture address 2 */
  TEX_ADDR2 = 0xa2,
  /* Texture address 3 */
  TEX_ADDR3 = 0xa3,
  /* Texture address 4 */
  TEX_ADDR4 = 0xa4,
  /* Texture address 5 */
  TEX_ADDR5 = 0xa5,
  /* Texture address 6 */
  TEX_ADDR6 = 0xa6,
  /* Texture address 7 */
  TEX_ADDR7 = 0xa7,
  /* Texture buffer width 0 */
  TEX_BUF_WIDTH0 = 0xa8,
  /* Texture buffer width 1 */
  TEX_BUF_WIDTH1 = 0xa9,
  /* Texture buffer width 2 */
  TEX_BUF_WIDTH2 = 0xaa,
  /* Texture buffer width 3 */
  TEX_BUF_WIDTH3 = 0xab,
  /* Texture buffer width 4 */
  TEX_BUF_WIDTH4 = 0xac,
  /* Texture buffer width 5 */
  TEX_BUF_WIDTH5 = 0xad,
  /* Texture buffer width 6 */
  TEX_BUF_WIDTH6 = 0xae,
  /* Texture buffer width 7 */
  TEX_BUF_WIDTH7 = 0xaf,

  /* CLUT buffer pointer */
  CLUT_BUF_PTR = 0xb0,
  /* CLUT buffer width */
  CLUT_BUF_WIDTH = 0xb1,

  /* Transfer source */
  TRANSFER_SRC = 0xb2,
  /* Transfer source width */
  TRANSFER_SRC_W = 0xb3,
  /* Transfer destination */
  TRANSFER_DST = 0xb4,
  /* Transfer destination width */
  TRANSFER_DST_W = 0xb5,

  /* Texture size 0 */
  TEX_SIZE0 = 0xb8,
  /* Texture size 1 */
  TEX_SIZE1 = 0xb9,
  /* Texture size 2 */
  TEX_SIZE2 = 0xba,
  /* Texture size 3 */
  TEX_SIZE3 = 0xbb,
  /* Texture size 4 */
  TEX_SIZE4 = 0xbc,
  /* Texture size 5 */
  TEX_SIZE5 = 0xbd,
  /* Texture size 6 */
  TEX_SIZE6 = 0xbe,
  /* Texture size 7 */
  TEX_SIZE7 = 0xbf,

  /* Texture map mode */
  TEX_MAP_MODE = 0xc0,
  /* Texture shade mapping */
  TEX_SHADE_MAPPING = 0xc1,
  /* Texture mode */
  TEX_MODE = 0xc2,
  /* Texture format */
  TEX_FORMAT = 0xc3,
  /* Load CLUT */
  CLUT_LOAD = 0xc4,
  /* CLUT format */
  CLUT_FORMAT = 0xc5,
  /* Texture filter */
  TEX_FILTER = 0xc6,
  /* Texture wrap */
  TEX_WRAP = 0xc7,
  /* Texture level */
  TEX_LEVEL = 0xc8,
  /* Texture function */
  TEX_FUNC = 0xc9,
  /* Texture environment color */
  TEX_ENV_COLOR = 0xca,
  /* Texture flush */
  TEX_FLUSH = 0xcb,
  /* Texture sync */
  TEX_SYNC = 0xcc,

  /* Fog 1 */
  FOG1 = 0xcd,
  /* Fog 2 */
  FOG2 = 0xce,
  /* Fog color */
  FOG_COLOR = 0xcf,
  /* Texture LOD slope */
  TEX_LOD_SLOPE = 0xd0,

  /* Frame buffer pixel format */
  FRAMEBUF_PIX_FORMAT = 0xd2,
  /* Clear mode */
  CLEAR_MODE = 0xd3,
  /* Scissor 1 */
  SCISSOR1 = 0xd4,
  /* Scissor 2 */
  SCISSOR2 = 0xd5,

  /* Minimum Z */
  MIN_Z = 0xd6,
  /* Maximum Z */
  MAX_Z = 0xd7,
  /* Color test */
  COLOR_TEST = 0xd8,
  /* Color reference */
  COLOR_REF = 0xd9,
  /* Color test mask */
  COLOR_TESTMASK = 0xda,
  /* Alpha test */
  ALPHA_TEST = 0xdb,
  /* Stencil test */
  STENCIL_TEST = 0xdc,
  /* Stencil operation */
  STENCIL_OP = 0xdd,
  /* Z test */
  Z_TEST = 0xde,
  /* Blend mode */
  BLEND_MODE = 0xdf,
  /* Blend fixed A */
  BLEND_FIXED_A = 0xe0,
  /* Blend fixed B */
  BLEND_FIXED_B = 0xe1,
  /* Dither 0 */
  DITH0 = 0xe2,
  /* Dither 1 */
  DITH1 = 0xe3,
  /* Dither 2 */
  DITH2 = 0xe4,
  /* Dither 3 */
  DITH3 = 0xe5,

  /* Logical operation */
  LOGIC_OP = 0xe6,
  /* Z mask */
  Z_MASK = 0xe7,
  /* Mask color */
  MASK_COLOR = 0xe8,
  /* Mask alpha */
  MASK_ALPHA = 0xe9,

  /* Transfer start */
  TRANSFER_START = 0xea,
  /* Transfer source offset */
  TRANSFER_SRC_OFFSET = 0xeb,
  /* Transfer destination offset */
  TRANSFER_DST_OFFSET = 0xec,
  /* Transfer format */
  TRANSFER_FORMAT = 0xed,
  /* Transfer size */
  TRANSFER_SIZE = 0xee,

  /* Transfer flip */
  TRANSFER_FLIP = 0xef,
  /* Transfer out size */
  TRANSFER_OUT_SIZE = 0xf0,
  /* Transfer out format */
  TRANSFER_OUT_FORMAT = 0xf1,
  /* Vertex weight */
  VERTEX_WEIGHT = 0xf2,
  /* Vertex weight address */
  VERTEX_WEIGHT_ADDR = 0xf3,
  /* Vertex weight size */
  VERTEX_WEIGHT_SIZE = 0xf4,
  /* Vertex weight type */
  VERTEX_WEIGHT_TYPE = 0xf5,
  /* Vertex weight model */
  VERTEX_WEIGHT_MODEL = 0xf6,
  /* Vertex weight normalize */
  VERTEX_WEIGHT_NORMALIZE = 0xf7,
  /* Vertex weight offset */
  VERTEX_WEIGHT_OFFSET = 0xf8,
  /* Vertex weight scale */
  VERTEX_WEIGHT_SCALE = 0xf9,
  /* Vertex weight matrix */
  VERTEX_WEIGHT_MATRIX = 0xfa,
  /* Vertex weight matrix address */
  VERTEX_WEIGHT_MATRIX_ADDR = 0xfb,
  /* Vertex weight matrix size */
  VERTEX_WEIGHT_MATRIX_SIZE = 0xfc,
  /* Vertex weight matrix type */
  VERTEX_WEIGHT_MATRIX_TYPE = 0xfd,
  /* Vertex weight matrix model */
  VERTEX_WEIGHT_MATRIX_MODEL = 0xfe,
  /* Vertex weight matrix normalize */
  VERTEX_WEIGHT_MATRIX_NORMALIZE = 0xff,
} GECommand;

static inline void sceGuSendCommandi(int cmd, int argument)
{
  *(gu_list->current++) = (cmd << 24) | (argument & 0xffffff);
}

static inline void sceGuSendCommandf(int cmd, float argument)
{
  union
  {
    float f;
    unsigned int i;
  } t;
  t.f = argument;

  sceGuSendCommandi(cmd, t.i >> 8);
}

static inline void sendCommandiStall(GECommand cmd, int argument)
{
  sceGuSendCommandi(cmd, argument);

  if (!gu_object_stack_depth && !gu_curr_context)
    sceGeListUpdateStallAddr(ge_list_executed[0], gu_list->current);
}

static inline void sceGuDepthBuffer(void *zbp, int zbw)
{
  gu_draw_buffer.depth_buffer = zbp;

  if (!gu_draw_buffer.depth_width || (gu_draw_buffer.depth_width != zbw))
    gu_draw_buffer.depth_width = zbw;

  sceGuSendCommandi(Z_BUF_PTR, ((unsigned int)zbp) & 0xffffff);
  sceGuSendCommandi(Z_BUF_WIDTH, ((((unsigned int)zbp) & 0xff000000) >> 8) | zbw);
}

static inline void sceGuDispBuffer(int width, int height, void *dispbp, int dispbw)
{
  int x = 0;
  int y = 0;

  gu_draw_buffer.width = width;
  gu_draw_buffer.height = height;
  gu_draw_buffer.disp_buffer = dispbp;

  if (!gu_draw_buffer.frame_width || (gu_draw_buffer.frame_width != dispbw))
    gu_draw_buffer.frame_width = dispbw;

  sceGuSendCommandi(REGION1, (y << 10) | x);
  sceGuSendCommandi(REGION2, (((x + gu_draw_buffer.height) - 1) << 10) | ((y + gu_draw_buffer.width) - 1));
  sceDisplaySetMode(0, gu_draw_buffer.width, gu_draw_buffer.height);

  if (gu_display_on)
    sceDisplaySetFrameBuf((void *)(((unsigned int)ge_edram_address) + ((unsigned int)gu_draw_buffer.disp_buffer)), dispbw, gu_draw_buffer.pixel_size, PSP_DISPLAY_SETBUF_NEXTFRAME);
}

static inline void sceGuDrawBuffer(int psm, void *fbp, int frame_width)
{
  gu_draw_buffer.pixel_size = psm;
  gu_draw_buffer.frame_width = frame_width;
  gu_draw_buffer.frame_buffer = fbp;

  if (!gu_draw_buffer.depth_buffer && gu_draw_buffer.height)
    gu_draw_buffer.depth_buffer = (void *)(((unsigned int)fbp) + (unsigned int)((gu_draw_buffer.height * frame_width) << 2));

  if (!gu_draw_buffer.depth_width)
    gu_draw_buffer.depth_width = frame_width;

  sceGuSendCommandi(FRAMEBUF_PIX_FORMAT, psm);
  sceGuSendCommandi(FRAME_BUF_PTR, ((unsigned int)gu_draw_buffer.frame_buffer) & 0xffffff);
  sceGuSendCommandi(FRAME_BUF_WIDTH, ((((unsigned int)gu_draw_buffer.frame_buffer) & 0xff000000) >> 8) | gu_draw_buffer.frame_width);
  sceGuSendCommandi(Z_BUF_PTR, ((unsigned int)gu_draw_buffer.depth_buffer) & 0xffffff);
  sceGuSendCommandi(Z_BUF_WIDTH, ((((unsigned int)gu_draw_buffer.depth_buffer) & 0xff000000) >> 8) | gu_draw_buffer.depth_width);
}

static inline void sceGuDrawBufferList(int psm, void *fbp, int fbw)
{
  sceGuSendCommandi(FRAMEBUF_PIX_FORMAT, psm);
  sceGuSendCommandi(FRAME_BUF_PTR, ((unsigned int)fbp) & 0xffffff);
  sceGuSendCommandi(FRAME_BUF_WIDTH, ((((unsigned int)fbp) & 0xff000000) >> 8) | fbw);
}

static inline int sceGuDisplay(int state)
{
  if (state)
    sceDisplaySetFrameBuf((void *)((unsigned int)ge_edram_address + (unsigned int)gu_draw_buffer.disp_buffer), gu_draw_buffer.frame_width, gu_draw_buffer.pixel_size, PSP_DISPLAY_SETBUF_NEXTFRAME);
  else
    sceDisplaySetFrameBuf(0, 0, 0, PSP_DISPLAY_SETBUF_NEXTFRAME);

  gu_display_on = state;
  return state;
}

static inline void sceGuDepthFunc(int function)
{
  sceGuSendCommandi(Z_TEST, function);
}

static inline void sceGuDepthMask(int mask)
{
  sceGuSendCommandi(Z_MASK, mask);
}

static inline void sceGuDepthRange(int near, int far)
{
  GuContext *context = &gu_contexts[gu_curr_context];

  unsigned int max = (unsigned int)near + (unsigned int)far;
  int val = (int)((max >> 31) + max);
  float z = (float)(val >> 1);

  context->near_plane = near;
  context->far_plane = far;

  sceGuSendCommandf(VIEWPORT_Z_SCALE, z - ((float)near));
  sceGuSendCommandf(VIEWPORT_Z_CENTER, z + ((float)context->depth_offset));

  if (near > far)
  {
    int temp = near;
    near = far;
    far = temp;
  }

  sceGuSendCommandi(MIN_Z, near);
  sceGuSendCommandi(MAX_Z, far);
}

static inline void sceGuDepthOffset(unsigned int offset)
{
  GuContext *context = &gu_contexts[gu_curr_context];
  context->depth_offset = offset;

  sceGuDepthRange(context->near_plane, context->far_plane);
}

static inline void sceGuFog(float near, float far, unsigned int color)
{
  float distance = far - near;

  if (distance)
    distance = 1.0f / distance;

  sceGuSendCommandi(FOG_COLOR, color & 0xffffff);
  sceGuSendCommandf(FOG1, far);
  sceGuSendCommandf(FOG2, distance);
}

static inline void sceGuBreak(int a0)
{
  // FIXME
  // sceGeBreak(a0,0x527a68);
}

static inline void sceGuContinue(void)
{
  // FIXME
  // sceGeContinue();
}

static inline GuCallback sceGuSetCallback(int signal, GuCallback callback)
{
  GuCallback old_callback = 0;

  switch (signal)
  {
  case GU_CALLBACK_SIGNAL:
  {
    old_callback = gu_settings.sig;
    gu_settings.sig = callback;
  }
  break;

  case GU_CALLBACK_FINISH:
  {
    old_callback = gu_settings.fin;
    gu_settings.fin = callback;
  }
  break;
  }

  return old_callback;
}

static inline void sceGuSignal(int signal, int argument)
{
  sceGuSendCommandi(SIGNAL, ((signal & 0xff) << 16) | (argument & 0xffff));
  sceGuSendCommandi(END, 0);

  if (signal == 3)
  {
    sceGuSendCommandi(FINISH, 0);
    sceGuSendCommandi(END, 0);
  }

  sendCommandiStall(NOP, 0);
}

static inline int sceGuFinish(void)
{
  switch (gu_curr_context)
  {
  case GU_DIRECT:
  case GU_SEND:
  {
    sceGuSendCommandi(FINISH, 0);
    sendCommandiStall(END, 0);
  }
  break;

  case GU_CALL:
  {
    if (gu_call_mode == 1)
    {
      sceGuSendCommandi(SIGNAL, 0x120000);
      sceGuSendCommandi(END, 0);
      sendCommandiStall(NOP, 0);
    }
    else
    {
      sceGuSendCommandi(RET, 0);
    }
  }
  break;
  }

  unsigned int size = ((unsigned int)gu_list->current) - ((unsigned int)gu_list->start);

  // go to parent list
  gu_curr_context = gu_list->parent_context;
  gu_list = &gu_contexts[gu_curr_context].list;
  return size;
}

static inline int sceGuFinishId(unsigned int id)
{
  switch (gu_curr_context)
  {
  case GU_DIRECT:
  case GU_SEND:
  {
    sceGuSendCommandi(FINISH, id & 0xffff);
    sendCommandiStall(END, 0);
  }
  break;

  case GU_CALL:
  {
    if (gu_call_mode == 1)
    {
      sceGuSendCommandi(SIGNAL, 0x120000);
      sceGuSendCommandi(END, 0);
      sendCommandiStall(NOP, 0);
    }
    else
    {
      sceGuSendCommandi(RET, 0);
    }
  }
  break;
  }

  unsigned int size = ((unsigned int)gu_list->current) - ((unsigned int)gu_list->start);

  // go to parent list
  gu_curr_context = gu_list->parent_context;
  gu_list = &gu_contexts[gu_curr_context].list;
  return size;
}

static inline void sceGuCallList(const void *list)
{
  unsigned int list_addr = (unsigned int)list;

  if (gu_call_mode == 1)
  {
    sceGuSendCommandi(SIGNAL, (list_addr >> 16) | 0x110000);
    sceGuSendCommandi(END, list_addr & 0xffff);
    sendCommandiStall(NOP, 0);
  }
  else
  {
    sceGuSendCommandi(BASE, (list_addr >> 8) & 0xf0000);
    sendCommandiStall(CALL, list_addr & 0xffffff);
  }
}

static inline void sceGuCallMode(int mode)
{
  gu_call_mode = mode;
}

static inline int sceGuCheckList(void)
{
  return ((int)gu_list->current) - ((int)gu_list->start);
}

static inline int sceGuSendList(int mode, const void *list, PspGeContext *context)
{
	gu_settings.signal_offset = 0;

	// TODO: figure out this structure
	PspGeListArgs args;
	args.size = 8; // Size of structure?
	args.context = context;

	int list_id = 0;
	int callback = gu_settings.ge_callback_id;

	switch (mode)
	{
	case GU_HEAD:
		list_id = sceGeListEnQueueHead(list, NULL, callback, &args);
		break;
	case GU_TAIL:
		list_id = sceGeListEnQueue(list, NULL, callback, &args);
		break;
	}

	if (list_id < 0)
	{
		return list_id;
	}

	ge_list_executed[1] = list_id;
	return 0;
}

static inline void *sceGuSwapBuffers(void)
{
  if (gu_settings.swapBuffersCallback)
  {
    gu_settings.swapBuffersCallback(&gu_draw_buffer.disp_buffer, &gu_draw_buffer.frame_buffer);
  }
  else
  {
    void *temp = gu_draw_buffer.disp_buffer;
    gu_draw_buffer.disp_buffer = gu_draw_buffer.frame_buffer;
    gu_draw_buffer.frame_buffer = temp;
  }

  if (gu_display_on)
    sceDisplaySetFrameBuf((void *)((unsigned int)ge_edram_address + (unsigned int)gu_draw_buffer.disp_buffer), gu_draw_buffer.frame_width, gu_draw_buffer.pixel_size, gu_settings.swapBuffersBehaviour);

  // TODO: remove this? it serves no real purpose
  gu_current_frame ^= 1;

  //	return (void*)gu_settings.swapBuffersBehaviour;
  return gu_draw_buffer.frame_buffer;
}

static inline int sceGuSync(int mode, int what)
{
  switch (mode)
  {
  case 0:
    return sceGeDrawSync(what);
  case 3:
    return sceGeListSync(ge_list_executed[0], what);
  case 4:
    return sceGeListSync(ge_list_executed[1], what);
  default:
  case 1:
  case 2:
    return 0;
  }
}

static inline void sceGuDrawArray(int prim, int vtype, int count, const void *indices, const void *vertices)
{
  if (vtype)
    sceGuSendCommandi(VERTEX_TYPE, vtype);

  if (indices)
  {
    sceGuSendCommandi(BASE, (((unsigned int)indices) >> 8) & 0xf0000);
    sceGuSendCommandi(IADDR, ((unsigned int)indices) & 0xffffff);
  }

  if (vertices)
  {
    sceGuSendCommandi(BASE, (((unsigned int)vertices) >> 8) & 0xf0000);
    sceGuSendCommandi(VADDR, ((unsigned int)vertices) & 0xffffff);
  }

  sendCommandiStall(PRIM, (prim << 16) | count);
}

static inline void sceGuBeginObject(int vertex_type, int a1, const void *indices, const void *vertices)
{
  if (vertex_type)
    sceGuSendCommandi(VERTEX_TYPE, vertex_type);

  if (indices)
  {
    sceGuSendCommandi(BASE, (((unsigned int)indices) >> 8) & 0xf0000);
    sceGuSendCommandi(IADDR, ((unsigned int)indices) & 0xffffff);
  }

  if (vertices)
  {
    sceGuSendCommandi(BASE, (((unsigned int)vertices) >> 8) & 0x0f0000);
    sceGuSendCommandi(VADDR, ((unsigned int)vertices) & 0xffffff);
  }

  sceGuSendCommandi(BOUNDING_BOX, a1);

  // store start to new object

  gu_object_stack[gu_object_stack_depth++] = gu_list->current;

  // dummy commands, overwritten in sceGuEndObject()
  sceGuSendCommandi(BASE, 0);
  sceGuSendCommandi(BJUMP, 0);
}

static inline void sceGuEndObject(void)
{
  // rewrite commands from sceGuBeginObject()

  unsigned int *current = gu_list->current;
  gu_list->current = gu_object_stack[gu_object_stack_depth - 1];

  sceGuSendCommandi(BASE, (((unsigned int)current) >> 8) & 0xf0000);
  sceGuSendCommandi(BJUMP, ((unsigned int)current) & 0xffffff);
  gu_list->current = current;

  gu_object_stack_depth--;
}

static inline void sceGuSetStatus(int state, int status)
{
  if (status)
    sceGuEnable(state);
  else
    sceGuDisable(state);
}

static inline int sceGuGetStatus(int state)
{
  if (state < 22)
    return (gu_states >> state) & 1;
  return 0;
}

static inline void sceGuSetAllStatus(int status)
{
  unsigned int i;
  for (i = 0; i < 22; ++i)
  {
    if ((status >> i) & 1)
      sceGuEnable(i);
    else
      sceGuDisable(i);
  }
}

static inline int sceGuGetAllStatus(void)
{
  return gu_states;
}

static inline void sceGuEnable(int state)
{
  switch (state)
  {
  case GU_ALPHA_TEST:
    sceGuSendCommandi(ALPHA_TEST_ENABLE, 1);
    break;
  case GU_DEPTH_TEST:
    sceGuSendCommandi(Z_TEST_ENABLE, 1);
    break;
  case GU_SCISSOR_TEST:
  {
    GuContext *context = &gu_contexts[gu_curr_context];
    context->scissor_enable = 1;
    sceGuSendCommandi(SCISSOR1, (context->scissor_start[1] << 10) | context->scissor_start[0]);
    sceGuSendCommandi(SCISSOR2, (context->scissor_end[1] << 10) | context->scissor_end[0]);
  }
  break;
  case GU_STENCIL_TEST:
    sceGuSendCommandi(STENCIL_TEST_ENABLE, 1);
    break;
  case GU_BLEND:
    sceGuSendCommandi(ALPHA_BLEND_ENABLE, 1);
    break;
  case GU_CULL_FACE:
    sceGuSendCommandi(CULL_FACE_ENABLE, 1);
    break;
  case GU_DITHER:
    sceGuSendCommandi(DITHER_ENABLE, 1);
    break;
  case GU_FOG:
    sceGuSendCommandi(FOG_ENABLE, 1);
    break;
  case GU_CLIP_PLANES:
    sceGuSendCommandi(DEPTH_CLIP_ENABLE, 1);
    break;
  case GU_TEXTURE_2D:
    sceGuSendCommandi(TEXTURE_ENABLE, 1);
    break;
  case GU_LIGHTING:
    sceGuSendCommandi(LIGHTING_ENABLE, 1);
    break;
  case GU_LIGHT0:
    sceGuSendCommandi(LIGHT_ENABLE0, 1);
    break;
  case GU_LIGHT1:
    sceGuSendCommandi(LIGHT_ENABLE1, 1);
    break;
  case GU_LIGHT2:
    sceGuSendCommandi(LIGHT_ENABLE2, 1);
    break;
  case GU_LIGHT3:
    sceGuSendCommandi(LIGHT_ENABLE3, 1);
    break;
  case GU_LINE_SMOOTH:
    sceGuSendCommandi(ANTI_ALIAS_ENABLE, 1);
    break;
  case GU_PATCH_CULL_FACE:
    sceGuSendCommandi(PATCH_CULL_ENABLE, 1);
    break;
  case GU_COLOR_TEST:
    sceGuSendCommandi(COLOR_TEST_ENABLE, 1);
    break;
  case GU_COLOR_LOGIC_OP:
    sceGuSendCommandi(LOGIC_OP_ENABLE, 1);
    break;
  case GU_FACE_NORMAL_REVERSE:
    sceGuSendCommandi(NORMAL_REVERSE, 1);
    break;
  case GU_PATCH_FACE:
    sceGuSendCommandi(PATCH_FACING, 1);
    break;
  case GU_FRAGMENT_2X:
  {
    GuContext *context = &gu_contexts[gu_curr_context];
    context->fragment_2x = 0x10000;
    sceGuSendCommandi(TEX_FUNC, 0x10000 | context->texture_function);
  }
  break;
  }

  if (state < 22)
    gu_states |= (1 << state);
}

static inline void sceGuDisable(int state)
{
  switch (state)
  {
  case GU_ALPHA_TEST:
    sceGuSendCommandi(ALPHA_TEST_ENABLE, 0);
    break;
  case GU_DEPTH_TEST:
    sceGuSendCommandi(Z_TEST_ENABLE, 0);
    break;
  case GU_SCISSOR_TEST:
  {
    GuContext *context = &gu_contexts[gu_curr_context];
    context->scissor_enable = 0;
    sceGuSendCommandi(SCISSOR1, 0);
    sceGuSendCommandi(SCISSOR2, ((gu_draw_buffer.height - 1) << 10) | (gu_draw_buffer.width - 1));
  }
  break;
  case GU_STENCIL_TEST:
    sceGuSendCommandi(STENCIL_TEST_ENABLE, 0);
    break;
  case GU_BLEND:
    sceGuSendCommandi(ALPHA_BLEND_ENABLE, 0);
    break;
  case GU_CULL_FACE:
    sceGuSendCommandi(CULL_FACE_ENABLE, 0);
    break;
  case GU_DITHER:
    sceGuSendCommandi(DITHER_ENABLE, 0);
    break;
  case GU_FOG:
    sceGuSendCommandi(FOG_ENABLE, 0);
    break;
  case GU_CLIP_PLANES:
    sceGuSendCommandi(DEPTH_CLIP_ENABLE, 0);
    break;
  case GU_TEXTURE_2D:
    sceGuSendCommandi(TEXTURE_ENABLE, 0);
    break;
  case GU_LIGHTING:
    sceGuSendCommandi(LIGHTING_ENABLE, 0);
    break;
  case GU_LIGHT0:
    sceGuSendCommandi(LIGHT_ENABLE0, 0);
    break;
  case GU_LIGHT1:
    sceGuSendCommandi(LIGHT_ENABLE1, 0);
    break;
  case GU_LIGHT2:
    sceGuSendCommandi(LIGHT_ENABLE2, 0);
    break;
  case GU_LIGHT3:
    sceGuSendCommandi(LIGHT_ENABLE3, 0);
    break;
  case GU_LINE_SMOOTH:
    sceGuSendCommandi(ANTI_ALIAS_ENABLE, 0);
    break;
  case GU_PATCH_CULL_FACE:
    sceGuSendCommandi(PATCH_CULL_ENABLE, 0);
    break;
  case GU_COLOR_TEST:
    sceGuSendCommandi(COLOR_TEST_ENABLE, 0);
    break;
  case GU_COLOR_LOGIC_OP:
    sceGuSendCommandi(LOGIC_OP_ENABLE, 0);
    break;
  case GU_FACE_NORMAL_REVERSE:
    sceGuSendCommandi(NORMAL_REVERSE, 0);
    break;
  case GU_PATCH_FACE:
    sceGuSendCommandi(PATCH_FACING, 0);
    break;
  case GU_FRAGMENT_2X:
  {
    GuContext *context = &gu_contexts[gu_curr_context];
    context->fragment_2x = 0;
    sceGuSendCommandi(TEX_FUNC, context->texture_function);
  }
  break;
  }

  if (state < 22)
    gu_states &= ~(1 << state);
}

static inline void sceGuLight(int light, int type, int components, const ScePspFVector3 *position)
{
  GuLightSettings *settings = &light_settings[light];

  sceGuSendCommandf(settings->xpos, position->x);
  sceGuSendCommandf(settings->ypos, position->y);
  sceGuSendCommandf(settings->zpos, position->z);

  int kind = 2;
  if (components != 8)
    kind = (components ^ 6) < 1 ? 1 : 0;

  sceGuSendCommandi(settings->type, ((type & 0x03) << 8) | kind);
}

static inline void sceGuLightAtt(int light, float atten0, float atten1, float atten2)
{
  GuLightSettings *settings = &light_settings[light];

  sceGuSendCommandf(settings->constant, atten0);
  sceGuSendCommandf(settings->linear, atten1);
  sceGuSendCommandf(settings->quadratic, atten2);
}

static inline void sceGuLightColor(int light, int component, unsigned int color)
{
  GuLightSettings *settings = &light_settings[light];

  switch (component)
  {
  case GU_AMBIENT:
    sceGuSendCommandi(settings->ambient, color & 0xffffff);
    break;
  case GU_DIFFUSE:
    sceGuSendCommandi(settings->diffuse, color & 0xffffff);
    break;
  case GU_AMBIENT_AND_DIFFUSE:
  {
    sceGuSendCommandi(settings->ambient, color & 0xffffff);
    break;
    sceGuSendCommandi(settings->diffuse, color & 0xffffff);
    break;
  }
  break;

  case GU_SPECULAR:
    sceGuSendCommandi(settings->specular, color & 0xffffff);
    break;
  case GU_DIFFUSE_AND_SPECULAR:
  {
    sceGuSendCommandi(settings->diffuse, color & 0xffffff);
    break;
    sceGuSendCommandi(settings->specular, color & 0xffffff);
    break;
  }
  break;
  }
}

static inline void sceGuLightMode(int mode)
{
  sceGuSendCommandi(LIGHT_MODE, mode);
}

static inline void sceGuLightSpot(int light, const ScePspFVector3 *direction, float exponent, float cutoff)
{
  GuLightSettings *settings = &light_settings[light];

  sceGuSendCommandf(settings->exponent, exponent);
  sceGuSendCommandf(settings->cutoff, cutoff);

  sceGuSendCommandf(settings->xdir, direction->x);
  sceGuSendCommandf(settings->ydir, direction->y);
  sceGuSendCommandf(settings->zdir, direction->z);
}

static inline void sceGuClear(int flags)
{
  GuContext *context = &gu_contexts[gu_curr_context];
  unsigned int filter;
  struct Vertex
  {
    u32 color;
    u16 x, y, z;
    u16 pad;
  };

  switch (gu_draw_buffer.pixel_size)
  {
  case 0:
    filter = context->clear_color & 0xffffff;
    break;
  case 1:
    filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 31);
    break;
  case 2:
    filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 28);
    break;
  case 3:
    filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 24);
    break;
  default:
    filter = 0;
    break;
  }

  struct Vertex *vertices;
  int count;

  if (!(flags & GU_FAST_CLEAR_BIT))
  {
    vertices = (struct Vertex *)sceGuGetMemory(2 * sizeof(struct Vertex));
    count = 2;

    vertices[0].color = 0;
    vertices[0].x = 0;
    vertices[0].y = 0;
    vertices[0].z = context->clear_depth;

    vertices[1].color = filter;
    vertices[1].x = gu_draw_buffer.width;
    vertices[1].y = gu_draw_buffer.height;
    vertices[1].z = context->clear_depth;
  }
  else
  {
    struct Vertex *curr;
    unsigned int i;
    count = ((gu_draw_buffer.width + 63) / 64) * 2;
    vertices = (struct Vertex *)sceGuGetMemory(count * sizeof(struct Vertex));
    curr = vertices;

    for (i = 0; i < count; ++i, ++curr)
    {
      unsigned int j, k;

      j = i >> 1;
      k = (i & 1);

      curr->color = filter;
      curr->x = (j + k) * 64;
      curr->y = k * gu_draw_buffer.height;
      curr->z = context->clear_depth;
    }
  }

  sceGuSendCommandi(CLEAR_MODE, ((flags & (GU_COLOR_BUFFER_BIT | GU_STENCIL_BUFFER_BIT | GU_DEPTH_BUFFER_BIT)) << 8) | 0x01);
  sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_VERTEX_16BIT | GU_TRANSFORM_2D, count, 0, vertices);
  sceGuSendCommandi(CLEAR_MODE, 0);
}

static inline void sceGuClearColor(unsigned int color)
{
  GuContext *context = &gu_contexts[gu_curr_context];
  context->clear_color = color;
}

static inline void sceGuClearDepth(unsigned int depth)
{
  GuContext *context = &gu_contexts[gu_curr_context];
  context->clear_depth = depth;
}

static inline void sceGuClearStencil(unsigned int stencil)
{
  GuContext *context = &gu_contexts[gu_curr_context];
  context->clear_stencil = stencil;
}

static inline void sceGuPixelMask(unsigned int mask)
{
  sceGuSendCommandi(MASK_COLOR, mask & 0xffffff);
  sceGuSendCommandi(MASK_ALPHA, mask >> 24);
}

static inline void sceGuColor(unsigned int color)
{
  sceGuMaterial(7, color);
}

static inline void sceGuColorFunc(int func, unsigned int color, unsigned int mask)
{
  sceGuSendCommandi(COLOR_TEST, func & 0x03);
  sceGuSendCommandi(COLOR_REF, color & 0xffffff);
  sceGuSendCommandi(COLOR_TESTMASK, mask);
}

static inline void sceGuMaterial(int mode, int color)
{
  if (mode & 0x01)
  {
    sceGuSendCommandi(AMBIENT_COLOR, color & 0xffffff);
    sceGuSendCommandi(AMBIENT_ALPHA, color >> 24);
  }

  if (mode & 0x02)
    sceGuSendCommandi(MATERIAL_DIFFUSE, color & 0xffffff);

  if (mode & 0x04)
    sceGuSendCommandi(MATERIAL_SPECULAR, color & 0xffffff);
}

static inline void sceGuColorMaterial(int components)
{
  sceGuSendCommandi(MATERIAL_COLOR, components);
}

static inline void sceGuAlphaFunc(int a0, int a1, int a2)
{
  int arg = a0 | ((a1 & 0xff) << 8) | ((a2 & 0xff) << 16);
  sceGuSendCommandi(ALPHA_TEST, arg);
}

static inline void sceGuAmbient(unsigned int color)
{
  sceGuSendCommandi(AMBIENT_LIGHT_COLOR, (color & 0xffffff));
  sceGuSendCommandi(AMBIENT_LIGHT_ALPHA, (color >> 24));
}

static inline void sceGuAmbientColor(unsigned int color)
{
  sceGuSendCommandi(AMBIENT_COLOR, color & 0xffffff);
  sceGuSendCommandi(AMBIENT_ALPHA, color >> 24);
}

static void sceGuBlendFunc(int op, int src, int dest, unsigned int srcfix, unsigned int destfix)
{
  sceGuSendCommandi(BLEND_MODE, src | (dest << 4) | (op << 8));
  sceGuSendCommandi(BLEND_FIXED_A, srcfix & 0xffffff);
  sceGuSendCommandi(BLEND_FIXED_B, destfix & 0xffffff);
}

static inline void sceGuModelColor(unsigned int emissive, unsigned int ambient, unsigned int diffuse, unsigned int specular)
{
  sceGuSendCommandi(MATERIAL_EMISSIVE, emissive & 0xffffff);
  sceGuSendCommandi(MATERIAL_DIFFUSE, diffuse & 0xffffff);
  sceGuSendCommandi(AMBIENT_COLOR, ambient & 0xffffff);
  sceGuSendCommandi(MATERIAL_SPECULAR, specular & 0xffffff);
}

static inline void sceGuStencilFunc(int func, int ref, int mask)
{
  sceGuSendCommandi(STENCIL_TEST, func | ((ref & 0xff) << 8) | ((mask & 0xff) << 16));
}

static inline void sceGuStencilOp(int fail, int zfail, int zpass)
{
  sceGuSendCommandi(STENCIL_OP, fail | (zfail << 8) | (zpass << 16));
}

static inline void sceGuSpecular(float power) // specular power
{
  sceGuSendCommandf(MATERIAL_SPECULAR_COEF, power);
}

static inline void sceGuFrontFace(int order)
{
  sceGuSendCommandi(CULL, order ? 0 : 1);
}

static inline void sceGuLogicalOp(int op)
{
  sceGuSendCommandi(LOGIC_OP, op & 0x0f);
}

static inline void sceGuSetDither(const ScePspIMatrix4 *matrix)
{
  sceGuSendCommandi(DITH0, (matrix->x.x & 0x0f) | ((matrix->x.y & 0x0f) << 4) | ((matrix->x.z & 0x0f) << 8) | ((matrix->x.w & 0x0f) << 12));
  sceGuSendCommandi(DITH1, (matrix->y.x & 0x0f) | ((matrix->y.y & 0x0f) << 4) | ((matrix->y.z & 0x0f) << 8) | ((matrix->y.w & 0x0f) << 12));
  sceGuSendCommandi(DITH2, (matrix->z.x & 0x0f) | ((matrix->z.y & 0x0f) << 4) | ((matrix->z.z & 0x0f) << 8) | ((matrix->z.w & 0x0f) << 12));
  sceGuSendCommandi(DITH3, (matrix->w.x & 0x0f) | ((matrix->w.y & 0x0f) << 4) | ((matrix->w.z & 0x0f) << 8) | ((matrix->w.w & 0x0f) << 12));
}

static inline void sceGuShadeModel(int mode)
{
  sceGuSendCommandi(SHADE_MODE, mode ? 1 : 0);
}

static inline void sceGuCopyImage(int psm, int sx, int sy, int width, int height, int srcw, void *src, int dx, int dy, int destw, void *dest)
{
  sceGuSendCommandi(TRANSFER_SRC, ((unsigned int)src) & 0xffffff);
  sceGuSendCommandi(TRANSFER_SRC_W, ((((unsigned int)src) & 0xff000000) >> 8) | srcw);
  sceGuSendCommandi(TRANSFER_SRC_OFFSET, (sy << 10) | sx);
  sceGuSendCommandi(TRANSFER_DST, ((unsigned int)dest) & 0xffffff);
  sceGuSendCommandi(TRANSFER_DST_W, ((((unsigned int)dest) & 0xff000000) >> 8) | destw);
  sceGuSendCommandi(TRANSFER_DST_OFFSET, (dy << 10) | dx);
  sceGuSendCommandi(TRANSFER_SIZE, ((height - 1) << 10) | (width - 1));
  sceGuSendCommandi(TRANSFER_START, (psm ^ 0x03) ? 0 : 1);
}

static inline void sceGuTexEnvColor(unsigned int color)
{
  sceGuSendCommandi(TEX_ENV_COLOR, color & 0xffffff);
}

static inline void sceGuTexFilter(int min, int mag)
{
  sceGuSendCommandi(TEX_FILTER, (mag << 8) | min);
}

static inline void sceGuTexFlush(void)
{
  sceGuSendCommandi(TEX_FLUSH, 0);
}

static void sceGuTexFunc(int tfx, int tcc)
{
  GuContext *context = &gu_contexts[gu_curr_context];
  context->texture_function = (tcc << 8) | tfx;

  sceGuSendCommandi(TEX_FUNC, ((tcc << 8) | tfx) | context->fragment_2x);
}

static inline void sceGuTexImage(int mipmap, int width, int height, int tbw, const void *tbp)
{
  #define GET_EXP(val) (31 - __builtin_clz(val & 0x3FF))

  GECommand texAddr = (GECommand)(TEX_ADDR0 + mipmap);
  GECommand texBufWidth = (GECommand)(TEX_BUF_WIDTH0 + mipmap);
  GECommand texSize = (GECommand)(TEX_SIZE0 + mipmap);
  sceGuSendCommandi(texAddr, ((unsigned int)tbp) & 0xffffff);
  sceGuSendCommandi(texBufWidth, ((((unsigned int)tbp) >> 8) & 0x0f0000) | tbw);
  sceGuSendCommandi(texSize, (GET_EXP(height) << 8) | (GET_EXP(width)));
  sceGuTexFlush();
}

static inline void sceGuTexLevelMode(unsigned int mode, float bias)
{
  int offset = (int)truncf(bias * 16.0f);

  // mip map bias?
  if (offset >= 128)
    offset = 128;
  else if (offset < -128)
    offset = -128;

  sceGuSendCommandi(TEX_LEVEL, (((unsigned int)(offset)) << 16) | mode);
}

static inline void sceGuTexMapMode(int mode, unsigned int a1, unsigned int a2)
{
  GuContext *context = &gu_contexts[gu_curr_context];

  context->texture_map_mode = mode & 0x03;

  sceGuSendCommandi(TEX_MAP_MODE, context->texture_proj_map_mode | (mode & 0x03));
  sceGuSendCommandi(TEX_SHADE_MAPPING, (a2 << 8) | (a1 & 0x03));
}

static inline void sceGuTexMode(int tpsm, int maxmips, int a2, int swizzle)
{
  GuContext *context = &gu_contexts[gu_curr_context];
  context->texture_mode = tpsm;

  sceGuSendCommandi(TEX_MODE, (maxmips << 16) | (a2 << 8) | (swizzle));
  sceGuSendCommandi(TEX_FORMAT, tpsm);

  sceGuTexFlush();
}

static inline void sceGuTexOffset(float u, float v)
{
  sceGuSendCommandf(TEX_OFFSET_U, u);
  sceGuSendCommandf(TEX_OFFSET_V, v);
}

static inline void sceGuTexProjMapMode(int mode)
{
  GuContext *context = &gu_contexts[gu_curr_context];

  context->texture_proj_map_mode = ((mode & 0x03) << 8);
  sceGuSendCommandi(TEX_MAP_MODE, ((mode & 0x03) << 8) | context->texture_map_mode);
}

static inline void sceGuTexScale(float u, float v)
{
  sceGuSendCommandf(TEX_SCALE_U, u);
  sceGuSendCommandf(TEX_SCALE_V, v);
}

static inline void sceGuTexSlope(float slope)
{
  sceGuSendCommandf(TEX_LOD_SLOPE, slope);
}

static inline void sceGuTexSync()
{
  sceGuSendCommandi(TEX_SYNC, 0);
}

static inline void sceGuTexWrap(int u, int v)
{
  sceGuSendCommandi(TEX_WRAP, (v << 8) | (u));
}

static inline void sceGuClutLoad(int num_blocks, const void *cbp)
{
  sceGuSendCommandi(CLUT_BUF_PTR, ((unsigned int)cbp) & 0xffffff);
  sceGuSendCommandi(CLUT_BUF_WIDTH, (((unsigned int)cbp) >> 8) & 0xf0000);
  sceGuSendCommandi(CLUT_LOAD, num_blocks);
}

static inline void sceGuClutMode(unsigned int cpsm, unsigned int shift, unsigned int mask, unsigned int a3)
{
  unsigned int argument = (cpsm) | (shift << 2) | (mask << 8) | (a3 << 16);
  sceGuSendCommandi(CLUT_FORMAT, argument);
}

static void sceGuOffset(unsigned int x, unsigned int y)
{
  sceGuSendCommandi(OFFSET_X, x << 4);
  sceGuSendCommandi(OFFSET_Y, y << 4);
}

static inline void sceGuScissor(int x, int y, int w, int h)
{
  GuContext *context = &gu_contexts[gu_curr_context];

  context->scissor_start[0] = x;
  context->scissor_start[1] = y;
  context->scissor_end[0] = w - 1;
  context->scissor_end[1] = h - 1;

  if (context->scissor_enable)
  {
    sceGuSendCommandi(SCISSOR1, (context->scissor_start[1] << 10) | context->scissor_start[0]);
    sceGuSendCommandi(SCISSOR2, (context->scissor_end[1] << 10) | context->scissor_end[0]);
  }
}

static inline void sceGuViewport(int cx, int cy, int width, int height)
{
  sceGuSendCommandf(VIEWPORT_X_SCALE, (float)(width >> 1));
  sceGuSendCommandf(VIEWPORT_Y_SCALE, (float)((-height) >> 1));
  sceGuSendCommandf(VIEWPORT_X_CENTER, (float)cx);
  sceGuSendCommandf(VIEWPORT_Y_CENTER, (float)cy);
}

static inline void sceGuDrawBezier(int vertex_type, int ucount, int vcount, const void *indices, const void *vertices)
{
  if (vertex_type)
    sceGuSendCommandi(VERTEX_TYPE, vertex_type);

  if (indices)
  {
    sceGuSendCommandi(BASE, (((unsigned int)indices) >> 8) & 0xf0000);
    sceGuSendCommandi(IADDR, ((unsigned int)indices) & 0xffffff);
  }

  if (vertices)
  {
    sceGuSendCommandi(BASE, (((unsigned int)vertices) >> 8) & 0xf0000);
    sceGuSendCommandi(VADDR, ((unsigned int)vertices) & 0xffffff);
  }

  sceGuSendCommandi(BEZIER, (vcount << 8) | ucount);
}

static inline void sceGuPatchDivide(unsigned int a0, unsigned int a1)
{
  sceGuSendCommandi(PATCH_DIVISION, (a1 << 8) | a0);
}

static inline void sceGuPatchFrontFace(unsigned int a0)
{
  sceGuSendCommandi(PATCH_FACING, a0);
}

static inline void sceGuPatchPrim(int prim)
{
  switch (prim)
  {
  case GU_POINTS:
    sceGuSendCommandi(PATCH_PRIMITIVE, 2);
    break;
  case GU_LINE_STRIP:
    sceGuSendCommandi(PATCH_PRIMITIVE, 1);
    break;
  case GU_TRIANGLE_STRIP:
    sceGuSendCommandi(PATCH_PRIMITIVE, 0);
    break;
  }
}

static inline void sceGuDrawSpline(int vertex_type, int ucount, int vcount, int uedge, int vedge, const void *indices, const void *vertices)
{
  if (vertex_type)
    sceGuSendCommandi(VERTEX_TYPE, vertex_type);

  if (indices)
  {
    sceGuSendCommandi(BASE, (((unsigned int)indices) >> 8) & 0xf0000);
    sceGuSendCommandi(IADDR, ((unsigned int)indices) & 0xffffff);
  }

  if (vertices)
  {
    sceGuSendCommandi(BASE, (((unsigned int)vertices) >> 8) & 0xf0000);
    sceGuSendCommandi(VADDR, ((unsigned int)vertices) & 0xffffff);
  }

  sceGuSendCommandi(SPLINE, (vedge << 18) | (uedge << 16) | (vcount << 8) | ucount);
}

static inline void sceGuSetMatrix(int type, const ScePspFMatrix4 *matrix)
{
  unsigned int i, j;
  const float *fmatrix = (const float *)matrix;

  switch (type)
  {
  case 0:
  {
    sceGuSendCommandf(PROJ_MATRIX_NUMBER, 0);

    // 4*4 - most probably projection
    for (i = 0; i < 16; ++i)
      sceGuSendCommandf(PROJ_MATRIX_DATA, fmatrix[i]);
  }
  break;

  case 1:
  {
    sceGuSendCommandf(VIEW_MATRIX_NUMBER, 0);

    // 4*4 -> 3*4 - view matrix?
    for (i = 0; i < 4; ++i)
    {
      for (j = 0; j < 3; ++j)
        sceGuSendCommandf(VIEW_MATRIX_DATA, fmatrix[j + i * 4]);
    }
  }
  break;

  case 2:
  {
    sceGuSendCommandf(WORLD_MATRIX_NUMBER, 0);

    // 4*4 -> 3*4 - ???
    for (i = 0; i < 4; ++i)
    {
      for (j = 0; j < 3; ++j)
        sceGuSendCommandf(WORLD_MATRIX_DATA, fmatrix[j + i * 4]);
    }
  }
  break;

  case 3:
  {
    sceGuSendCommandf(TGEN_MATRIX_NUMBER, 0);

    // 4*4 -> 3*4 - ???
    for (i = 0; i < 4; ++i)
    {
      for (j = 0; j < 3; ++j)
        sceGuSendCommandf(TGEN_MATRIX_DATA, fmatrix[j + i * 4]);
    }
  }
  break;
  }
}

static inline void sceGuBoneMatrix(unsigned int index, const ScePspFMatrix4 *matrix)
{
  unsigned int offset = ((index << 1) + index) << 2; // 3*4 matrix
  unsigned int i, j;
  const float *fmatrix = (const float *)matrix;

  sceGuSendCommandi(BONE_MATRIX_NUMBER, offset);
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 3; ++j)
    {
      sceGuSendCommandf(BONE_MATRIX_DATA, fmatrix[j + (i << 2)]);
    }
  }
}

static inline void sceGuMorphWeight(int index, float weight)
{
  sceGuSendCommandf(44 + index, weight);
}

static inline void sceGuDrawArrayN(int primitive_type, int vertex_type, int count, int a3, const void *indices, const void *vertices)
{
  if (vertex_type)
    sceGuSendCommandi(VERTEX_TYPE, vertex_type);

  if (indices)
  {
    sceGuSendCommandi(BASE, (((unsigned int)indices) >> 8) & 0xf0000);
    sceGuSendCommandi(IADDR, ((unsigned int)indices) & 0xffffff);
  }

  if (vertices)
  {
    sceGuSendCommandi(BASE, (((unsigned int)vertices) >> 8) & 0xf0000);
    sceGuSendCommandi(VADDR, ((unsigned int)vertices) & 0xffffff);
  }

  if (a3 > 0)
  {
    // TODO: not sure about this loop, might be off. review
    int i;
    for (i = a3 - 1; i > 0; --i)
      sceGuSendCommandi(PRIM, (primitive_type << 16) | count);
    sendCommandiStall(PRIM, (primitive_type << 16) | count);
  }
}

static inline void guSwapBuffersBehaviour(int behaviour)
{
  gu_settings.swapBuffersBehaviour = behaviour;
}

static inline void guSwapBuffersCallback(GuSwapBuffersCallback callback)
{
  gu_settings.swapBuffersCallback = callback;
}

static inline int guGetDisplayState()
{
  return gu_display_on;
}

/**@}*/

#if defined(__cplusplus)
};
#endif

#endif
