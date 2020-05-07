/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspge.h - Prototypes for the sceGe library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#ifndef __GE_H__
#define __GE_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Stores the state of the GE. */
typedef struct PspGeContext {
	unsigned int context[512];
} PspGeContext;

/** Structure storing a stack (for CALL/RET) */
typedef struct
{
	/** The stack buffer */
	unsigned int stack[8];
} SceGeStack;

/** Typedef for a GE callback */
typedef void (*PspGeCallback)(int id, void *arg);

/** Structure to hold the callback data */
typedef struct PspGeCallbackData
{
	/** GE callback for the signal interrupt */
	PspGeCallback signal_func;
	/** GE callback argument for signal interrupt */
	void *signal_arg;
	/** GE callback for the finish interrupt */
	PspGeCallback finish_func;
	/** GE callback argument for finish interrupt */
	void *finish_arg;
} PspGeCallbackData;

typedef struct PspGeListArgs
{
	/** Size of the structure (16) */
	unsigned int	size;
	/** Pointer to a context */
	PspGeContext*	context;
	/** Number of stacks to use */
	u32 numStacks;
	/** Pointer to the stacks (unused) */
	SceGeStack *stacks;
} PspGeListArgs;

/**
 * Drawing queue interruption parameter
 */
typedef struct PspGeBreakParam {
	unsigned int	buf[4];
} PspGeBreakParam;

/**
 * Get the size of VRAM.
 *
 * @return The size of VRAM (in bytes).
 */
unsigned int sceGeEdramGetSize(void);

/**
  * Get the eDRAM address.
  *
  * @return A pointer to the base of the eDRAM.
  */
void * sceGeEdramGetAddr(void);

/**
 * Retrieve the current value of a GE command.
 *
 * @param cmd - The GE command register to retrieve (0 to 0xFF, both included).
 *
 * @return The value of the GE command, < 0 on error.
 */
unsigned int sceGeGetCmd(int cmd);

/** GE matrix types. */
typedef enum PspGeMatrixTypes {
	/** Bone matrices. */
	PSP_GE_MATRIX_BONE0 = 0,
	PSP_GE_MATRIX_BONE1,
	PSP_GE_MATRIX_BONE2,
	PSP_GE_MATRIX_BONE3,
	PSP_GE_MATRIX_BONE4,
	PSP_GE_MATRIX_BONE5,
	PSP_GE_MATRIX_BONE6,
	PSP_GE_MATRIX_BONE7,
	/** World matrix. */
	PSP_GE_MATRIX_WORLD,
	/** View matrix. */
	PSP_GE_MATRIX_VIEW,
	/** Projection matrix. */
	PSP_GE_MATRIX_PROJECTION,
	PSP_GE_MATRIX_TEXGEN
} PspGeMatrixTypes;

/**
 * Retrieve a matrix of the given type.
 *
 * @param type - One of ::PspGeMatrixTypes.
 * @param matrix - Pointer to a variable to store the matrix.
 *
 * @return < 0 on error.
 */
int sceGeGetMtx(int type, void *matrix);

/** Structure storing a stack (for CALL/RET). */
typedef struct
{
    /** The stack buffer. */
    unsigned int stack[8];
} PspGeStack;

/**
 * Retrieve the stack of the display list currently being executed.
 *
 * @param stackId - The ID of the stack to retrieve.
 * @param stack - Pointer to a structure to store the stack, or NULL to not store it.
 *
 * @return The number of stacks of the current display list, < 0 on error.
 */
int sceGeGetStack(int stackId, PspGeStack *stack);

/**
 * Save the GE's current state.
 *
 * @param context - Pointer to a ::PspGeContext.
 *
 * @return < 0 on error.
 */
int sceGeSaveContext(PspGeContext *context);

/**
 * Restore a previously saved GE context.
 *
 * @param context - Pointer to a ::PspGeContext.
 *
 * @return < 0 on error.
 */
int sceGeRestoreContext(const PspGeContext *context);

/**
  * Enqueue a display list at the tail of the GE display list queue.
  *
  * @param list - The head of the list to queue.
  * @param stall - The stall address.
  * If NULL then no stall address is set and the list is transferred immediately.
  * @param cbid - ID of the callback set by calling sceGeSetCallback
  * @param arg - Structure containing GE context buffer address
  *
  * @return The ID of the queue, < 0 on error.
  */
int sceGeListEnQueue(const void *list, void *stall, int cbid, PspGeListArgs *arg);

/**
  * Enqueue a display list at the head of the GE display list queue.
  *
  * @param list - The head of the list to queue.
  * @param stall - The stall address.
  * If NULL then no stall address is set and the list is transferred immediately.
  * @param cbid - ID of the callback set by calling sceGeSetCallback
  * @param arg - Structure containing GE context buffer address
  *
  * @return The ID of the queue, < 0 on error.
  */
int sceGeListEnQueueHead(const void *list, void *stall, int cbid, PspGeListArgs *arg);

/**
 * Cancel a queued or running list.
 *
 * @param qid - The ID of the queue.
 *
 * @return < 0 on error.
 */
int sceGeListDeQueue(int qid);

/**
  * Update the stall address for the specified queue.
  *
  * @param qid - The ID of the queue.
  * @param stall - The new stall address.
  *
  * @return < 0 on error
  */
int sceGeListUpdateStallAddr(int qid, void *stall);


/** List status for ::sceGeListSync() and ::sceGeDrawSync(). */
typedef enum PspGeListState {
	PSP_GE_LIST_DONE = 0,
	PSP_GE_LIST_QUEUED,
	PSP_GE_LIST_DRAWING_DONE,
	PSP_GE_LIST_STALL_REACHED,
	PSP_GE_LIST_CANCEL_DONE
} PspGeListState;

/**
  * Wait for syncronisation of a list.
  *
  * @param qid - The queue ID of the list to sync.
  * @param syncType - 0 if you want to wait for the list to be completed, or 1 if you just want to peek the actual state.
  *
  * @return The specified queue status, one of ::PspGeListState.
  */
int sceGeListSync(int qid, int syncType);

/**
  * Wait for drawing to complete.
  *
  * @param syncType - 0 if you want to wait for the drawing to be completed, or 1 if you just want to peek the state of the display list currently being executed.
  *
  * @return The current queue status, one of ::PspGeListState.
  */
int sceGeDrawSync(int syncType);

/**
  * Register callback handlers for the the GE.
  *
  * @param cb - Configured callback data structure.
  *
  * @return The callback ID, < 0 on error.
  */
int sceGeSetCallback(PspGeCallbackData *cb);

/**
  * Unregister the callback handlers.
  *
  * @param cbid - The ID of the callbacks, returned by sceGeSetCallback().
  *
  * @return < 0 on error
  */
int sceGeUnsetCallback(int cbid);

/**
 * Interrupt drawing queue.
 *
 * @param mode - If set to 1, reset all the queues.
 * @param pParam - Unused (just K1-checked).
 *
 * @return The stopped queue ID if mode isn't set to 0, otherwise 0, and < 0 on error.
 */
int sceGeBreak(int mode, PspGeBreakParam *pParam);

/**
 * Restart drawing queue.
 *
 * @return < 0 on error.
 */
int sceGeContinue(void);

/**
 * Set the eDRAM address translation mode.
 *
 * @param width - 0 to not set the translation width, otherwise 512, 1024, 2048 or 4096.
 *
 * @return The previous width if it was set, otherwise 0, < 0 on error.
 */
int sceGeEdramSetAddrTranslation(int width);

#ifdef __cplusplus
}
#endif

#endif /* __GE_H__ */
