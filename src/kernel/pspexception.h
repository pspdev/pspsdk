/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspexception.h - Interface to the kernel side of ExceptionMan
 *
 * Copyright (c) 2006 James F.
 *
 * $Id: pspexception.h 1906 2006-05-09 18:42:57Z tyranid $
 */

#ifndef PSPEXCEPTION_H
#define PSPEXCEPTION_H

#include <pspkerneltypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Register a default exception handler.
 *
 * @param func - Pointer to the exception handler function
 * @note The exception handler function must start with a NOP
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelRegisterDefaultExceptionHandler(void *func);

/**
 * Register a exception handler
 * 
 * @param exno - The exception number
 * @param func - Pointer to the exception handler function
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelRegisterExceptionHandler(int exno, void *func);

/**
 * Register a exception handler with a priority
 * 
 * @param exno - The exception number
 * @param priority - The priority of the exception
 * @param func - Pointer to the exception handler function
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelRegisterPriorityExceptionHandler(int exno, int priority, void *func);

#ifdef __cplusplus
}
#endif

#endif /* PSPEXCEPTION_H */
