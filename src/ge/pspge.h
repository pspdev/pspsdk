/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspge.h - Prototypes for the sceGe library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: pspge.h 2433 2008-10-15 10:00:27Z iwn $
 */
#ifndef __GE_H__
#define __GE_H__

#ifdef __cplusplus
extern "C" {
#endif

/** Stores the state of the GE. */
typedef struct PspGeContext {
	unsigned int context[512];
} PspGeContext;

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
	unsigned int	size;
	PspGeContext*	context;
} PspGeListArgs;

/**
 * Get the size of VRAM.
 *
 * @return The size of VRAM (in bytes).
 */
unsigned int sceGeEdramGetSize(void);

/**
  * Get the address of VRAM.
  *
  * @return A pointer to the base of VRAM.
  */
void * sceGeEdramGetAddr(void);

/**
 * Retrive the current value of a GE command.
 *
 * @param cmd - The GE command register to retrieve.
 *
 * @return The value of the GE command.
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
 * @return ???
 */
int sceGeGetMtx(int type, void *matrix);

/**
 * Save the GE's current state.
 *
 * @param context - Pointer to a ::PspGeContext.
 *
 * @return ???
 */
int sceGeSaveContext(PspGeContext *context);

/**
 * Restore a previously saved GE context.
 *
 * @param context - Pointer to a ::PspGeContext.
 *
 * @return ???
 */
int sceGeRestoreContext(const PspGeContext *context);

/** 
  * Enqueue a display list at the tail of the GE display list queue.
  *
  * @param list - The head of the list to queue.
  * @param stall - The stall address.
  * If NULL then no stall address set and the list is transferred immediately.
  * @param cbid - ID of the callback set by calling sceGeSetCallback
  * @param arg - Structure containing GE context buffer address
  *
  * @return The ID of the queue.
  */
int sceGeListEnQueue(const void *list, void *stall, int cbid, PspGeListArgs *arg);

/**
  * Enqueue a display list at the head of the GE display list queue.
  * 
  * @param list - The head of the list to queue.
  * @param stall - The stall address.
  * If NULL then no stall address set and the list is transferred immediately.
  * @param cbid - ID of the callback set by calling sceGeSetCallback
  * @param arg - Structure containing GE context buffer address
  *
  * @return The ID of the queue.
  */
int sceGeListEnQueueHead(const void *list, void *stall, int cbid, PspGeListArgs *arg);

/**
 * Cancel a queued or running list.
 *
 * @param qid - The ID of the queue.
 *
 * @return ???
 */
int sceGeListDeQueue(int qid);

/**
  * Update the stall address for the specified queue.
  * 
  * @param qid - The ID of the queue.
  * @param stall - The stall address to update
  *
  * @return Unknown. Probably 0 if successful.
  */
int sceGeListUpdateStallAddr(int qid, void *stall);


/** Wait condition for ::sceGeListSync() and ::sceGeDrawSync(). */
typedef enum PspGeSyncType {
	PSP_GE_LIST_DONE = 0,
	PSP_GE_LIST_QUEUED,
	PSP_GE_LIST_DRAWING_DONE,
	PSP_GE_LIST_STALL_REACHED,
	PSP_GE_LIST_CANCEL_DONE
} PspGeSyncType;

/**
  * Wait for syncronisation of a list.
  *
  * @param qid - The queue ID of the list to sync.
  * @param syncType - Specifies the condition to wait on.  One of ::PspGeSyncType.
  * 
  * @return ???
  */
int sceGeListSync(int qid, int syncType);

/**
  * Wait for drawing to complete.
  * 
  * @param syncType - Specifies the condition to wait on.  One of ::PspGeSyncType.
  * 
  * @return ???
  */
int sceGeDrawSync(int syncType);

/**
  * Register callback handlers for the the Ge 
  *
  * @param cb - Configured callback data structure
  * @return The callback ID, < 0 on error
  */
int sceGeSetCallback(PspGeCallbackData *cb);

/**
  * Unregister the callback handlers
  *
  * @param cbid - The ID of the callbacks from sceGeSetCallback
  * @return < 0 on error
  */
int sceGeUnsetCallback(int cbid);

#ifdef __cplusplus
}
#endif

#endif /* __GE_H__ */
