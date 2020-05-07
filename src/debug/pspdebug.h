/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  pspdebug.h - Prototypes for the pspDebug library
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <psptypes.h>
#include <pspmoduleinfo.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Debug Debug Utility Library */

/** @addtogroup Debug */
/*@{*/

/** 
  * Initialise the debug screen
  */
void pspDebugScreenInit(void);

/**
 * Extended debug screen init
 *
 * @param vram_base - Base address of frame buffer, if NULL then sets a default
 * @param mode - Colour mode
 * @param setup - Setup the screen if 1
 */
void pspDebugScreenInitEx(void *vram_base, int mode, int setup);

/**
  * Do a printf to the debug screen.
  *
  * @param fmt - Format string to print
  * @param ... - Arguments
  */
void pspDebugScreenPrintf(const char *fmt, ...) __attribute__((format(printf,1,2)));

/**
  * Do a printf to the debug screen.
  * @note This is for kernel mode only as it uses a kernel function
  * to perform the printf instead of using vsnprintf, use normal printf for
  * user mode.
  *
  * @param format - Format string to print
  * @param ... - Arguments
  */
void pspDebugScreenKprintf(const char *format, ...) __attribute__((format(printf,1,2)));

/**
 * Enable or disable background colour writing (defaults to enabled)
 * 
 * @param enable - Set 1 to to enable background color, 0 for disable
 */
void pspDebugScreenEnableBackColor(int enable);

/** 
  * Set the background color for the text
  * @note To reset the entire screens bg colour you need to call pspDebugScreenClear
  *
  * @param color - A 32bit RGB colour
  */
void pspDebugScreenSetBackColor(u32 color);

/**
  * Set the text color 
  *
  * @param color - A 32 bit RGB color
  */
void pspDebugScreenSetTextColor(u32 color);

/**
 * Set the color mode (you must have switched the frame buffer appropriately)
 *
 * @param mode - Color mode
 */
void pspDebugScreenSetColorMode(int mode);

/** 
  * Draw a single character to the screen.
  *
  * @param x - The x co-ordinate to draw to (pixel units)
  * @param y - The y co-ordinate to draw to (pixel units)
  * @param color - The text color to draw
  * @param ch - The character to draw
  */
void pspDebugScreenPutChar(int x, int y, u32 color, u8 ch);

/**
  * Set the current X and Y co-ordinate for the screen (in character units)
  */
void pspDebugScreenSetXY(int x, int y);

/**
  * Set the video ram offset used for the screen
  *
  * @param offset - Offset in bytes
  */
void pspDebugScreenSetOffset(int offset);

/**
 * Set the video ram base used for the screen
 *
 * @param base - Base address in bytes
 */
void pspDebugScreenSetBase(u32* base);

/** 
  * Get the current X co-ordinate (in character units)
  *
  * @return The X co-ordinate
  */
int pspDebugScreenGetX(void);

/** 
  * Get the current Y co-ordinate (in character units)
  *
  * @return The Y co-ordinate
  */
int pspDebugScreenGetY(void);

/**
  * Clear the debug screen.
  */
void pspDebugScreenClear(void);

/**
  * Print non-nul terminated strings.
  * 
  * @param buff - Buffer containing the text.
  * @param size - Size of the data
  *
  * @return The number of characters written
  */
int pspDebugScreenPrintData(const char *buff, int size);

/**
 * Print a string
 *
 * @param str - String
 *
 * @return The number of characters written
 */
int pspDebugScreenPuts(const char *str);

/**
  * Get a MIPS stack trace (might work :P)
  *
  * @param results - List of points to store the results of the trace, (up to max)
  * @param max - Maximum number of back traces
  *
  * @return The number of frames stored in results.
*/
int pspDebugGetStackTrace(unsigned int* results, int max);

/**
 * Enable the clear line function that allows debug to clear the screen
*/
void pspDebugScreenClearLineEnable(void);

/**
 * Disable the clear line function that causes flicker on constant refreshes
*/
void pspDebugScreenClearLineDisable(void);

/** Structure to hold the register data associated with an exception */
typedef struct _PspDebugRegBlock
{
	u32 frame[6];
	/** Array of the 32 GPRs */
	u32 r[32];
	/** The status register */
	u32 status;
	/** lo */
	u32 lo;
	u32 hi;
	u32 badvaddr;
	u32 cause;
	u32 epc;
	float fpr[32];
	u32 fsr;
	u32 fir;
	u32 frame_ptr;
	u32 unused;
	/* Unused on PSP */
	u32 index;
	u32 random;
	u32 entrylo0;
	u32 entrylo1;
	u32 context;
	u32 pagemask;
	u32 wired;
	u32 cop0_7;
	u32 cop0_8;
	u32 cop0_9;
	u32 entryhi;
	u32 cop0_11;
	u32 cop0_12;
	u32 cop0_13;
	u32 cop0_14;
	/* PRId should still be okay */
	u32 prid;
	u32 padding[100];
} PspDebugRegBlock;

/** Defines a debug error handler */
typedef void (*PspDebugErrorHandler)(PspDebugRegBlock *regs);

/** 
  * Install an error handler to catch unhandled exceptions.
  * 
  * @param handler - Pointer to a handler function. If set to NULL it will default
  * to resetting the screen and dumping the error.
  * @return < 0 on error
  */
int pspDebugInstallErrorHandler(PspDebugErrorHandler handler);

/**
  * Dump an exception to screen using the pspDebugScreen functions.
  * @note This function will not setup the screen for debug output, you should call sceDebugScreenInit
  * before using it if it isn't already.
  *
  * @param regs - Pointer to a register block.
  *
  */
void pspDebugDumpException(PspDebugRegBlock *regs);

/** Type for Kprintf handler */
typedef int (*PspDebugKprintfHandler)(const char *format, u32 *args);

/** 
  * Install a Kprintf handler into the system.
  *
  * @param handler - Function pointer to the handler.
  * @return < 0 on error.
  */
int pspDebugInstallKprintfHandler(PspDebugKprintfHandler handler);

/** Structure to hold a single stack trace entry */
typedef struct _PspDebugStackTrace
{
	/** The address which called the function */
	u32 call_addr;
	/** The address of the function called */
	u32 func_addr;
} PspDebugStackTrace;

/**
  * Do a stack trace from the current exception. 
  * @note This function really isn't too general purpose and it is more than likely to generate a few 
  * false positives but I consider that better then missing out calls entirely. You have to use your
  * discretion, your code and a objdump to work out if some calls are completely surprious or not ;)
  *
  * @param regs - Pointer to a register block from an exception.
  * @param trace - Pointer to an array of PspDebugStackTrace structures.
  * @param max - The maximum number of traces to make.
  *
  * @return The number of functions found.
  */
int pspDebugGetStackTrace2(PspDebugRegBlock *regs, PspDebugStackTrace *trace, int max);

/** Structure to hold the psp profiler register values */
typedef struct _PspDebugProfilerRegs
{
	volatile u32 enable;
	volatile u32 systemck;
	volatile u32 cpuck;
	volatile u32 internal;
	volatile u32 memory;
	volatile u32 copz;
	volatile u32 vfpu;
	volatile u32 sleep;
	volatile u32 bus_access;
	volatile u32 uncached_load;
	volatile u32 uncached_store;
	volatile u32 cached_load;
	volatile u32 cached_store;
	volatile u32 i_miss;
	volatile u32 d_miss;
	volatile u32 d_writeback;
	volatile u32 cop0_inst;
	volatile u32 fpu_inst;
	volatile u32 vfpu_inst;
	volatile u32 local_bus;
} PspDebugProfilerRegs;

/** Enables the profiler hardware */
void pspDebugProfilerEnable(void);

/** Disables the profiler hardware */
void pspDebugProfilerDisable(void);

/** Clear the profiler registers */
void pspDebugProfilerClear(void);

/** Get the profiler register state
  *
  * @param regs - A pointer to a PspDebugProfilerRegs structure.
  */
void pspDebugProfilerGetRegs(PspDebugProfilerRegs *regs);

/** Print the profiler registers to screen */
void pspDebugProfilerPrint(void);

/** Type for the debug print handlers */
typedef int (*PspDebugPrintHandler)(const char *data, int len);

/** Type for the debug input handler */
typedef int (*PspDebugInputHandler)(char *data, int len);

/**
  * Install a handler for stdin (so you can use normal stdio functions)
  *
  * @param handler - A pointer to input handler, NULL to disable.
  *
  * @return < 0 on error, else 0.
  */
int pspDebugInstallStdinHandler(PspDebugInputHandler handler);

/**
  * Install a print handler for stdout (so you can use normal print functions)
  *
  * @param handler - A pointer to print handler, NULL to disable.
  *
  * @return < 0 on error, else 0.
  */
int pspDebugInstallStdoutHandler(PspDebugPrintHandler handler);

/**
  * Install a print handler for stderr (so you can use normal print functions)
  *
  * @param handler - A pointer to print handler, NULL to disable.
  *
  * @return < 0 on error, else 0.
  */
int pspDebugInstallStderrHandler(PspDebugPrintHandler handler);

/**
 * Put a character to the remote sio.
 *
 * @param ch - Character to write.
 */
void pspDebugSioPutchar(int ch);

/**
 * Get a character from the remote sio
 *
 * @return The character read or -1 if no characters available.
 */
int pspDebugSioGetchar(void);

/**
 * Write a string to the sio port.
 *
 * @param str - String to write.
 */
void pspDebugSioPuts(const char *str);

/**
 * Write a set of data to the sio port
 *
 * @param data - Pointer to the data to send.
 * @param len - Length of the data.
 *
 * @return Number of characters written.
 */
int pspDebugSioPutData(const char *data, int len);

/**
 * Write a set of data to the sio port converting single
 * line feeds to CRLF and single CR to CRLF
 *
 * @param data - Pointer to the data to send.
 * @param len - Length of the data.
 *
 * @return Number of characters written.
 */
int pspDebugSioPutText(const char *data, int len);

/**
 * Initialise the remote SIO port (defaults to 4800 8N1).
 * @note will delay 2 seconds to wait for the power to come up.
 */
void pspDebugSioInit(void);

/**
 * Set the baud rate of the SIO, e.g. 4800/9600..115200.
 * @param baud - The baudrate to set.
 */
void pspDebugSioSetBaud(int baud);

/**
 * Enable debug character output. Needs to be called in order
 * for the default Kprintf handler to work.
 */
void pspDebugEnablePutchar(void);

/**
 * Install a kprintf debug putchar handler. Implicitly calls ::pspDebugEnablePutchar
 * so you do not need to call it explicitly. Sio must be initialised before calling
 * this function however.
 */
void pspDebugSioInstallKprintf(void);

/**
  * Install the gdb stub handler.
  */
void pspDebugGdbStubInit(void);

/** 
  * Generate a breakpoint exception.
  */
void pspDebugBreakpoint(void);

/**
 * Enable the kprintf handler (once installed)
 */
void pspDebugSioEnableKprintf(void);

/**
 * Disable the kprintf handler (once installed)
 */
void pspDebugSioDisableKprintf(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
