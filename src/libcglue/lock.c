/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * sleep.c - Sleep functions needed by newlib.
 *
 * Copyright (c) 2023 Francisco Javier Trujillo Mata <fjtrujy@gmail.com>
 *
 */

/**
 * @file
 * The lock API functions required by newlib.
 */

#include <stdio.h>
#include <sys/lock.h>
#include <pspthreadman.h>

// Structure representing the lock
struct __lock {
    SceLwMutexWorkarea mutex;
    int32_t thread_id;
    int32_t count;
};

#ifdef F___retarget_lock_init
void __retarget_lock_init(_LOCK_T *lock)
{
    sceKernelCreateLwMutex(&(*lock)->mutex, "lock API mutex", 0, 0, 0);
}
#endif

#ifdef F___retarget_lock_acquire
void __retarget_lock_acquire(_LOCK_T lock)
{
	sceKernelLockLwMutex(&lock->mutex, 1, 0);
}
#endif

#ifdef F___retarget_lock_release
void __retarget_lock_release(_LOCK_T lock)
{
	sceKernelUnlockLwMutex(&lock->mutex, 1);
}
#endif

#ifdef F___retarget_lock_try_acquire
int __retarget_lock_try_acquire(_LOCK_T lock)
{
	return sceKernelTryLockLwMutex(&lock->mutex, 1);
}
#endif

#ifdef F___retarget_lock_close
void __retarget_lock_close(_LOCK_T lock)
{
    sceKernelDeleteLwMutex(&lock->mutex);
}
#endif

#ifdef F___retarget_lock_init_recursive
void __retarget_lock_init_recursive(_LOCK_T *lock)
{
	sceKernelCreateLwMutex(&(*lock)->mutex, "lock API recursive mutex", 0, 0, 0);
    (*lock)->count = 0;
    (*lock)->thread_id = sceKernelGetThreadId();
}
#endif

#ifdef F___retarget_lock_acquire_recursive
void __retarget_lock_acquire_recursive(_LOCK_T lock)
{
    int32_t thread_id = sceKernelGetThreadId();
    if (lock->count == 0 || lock->thread_id != thread_id) {
        sceKernelLockLwMutex(&lock->mutex, 1, 0);
    }
    lock->count++;
}
#endif

#ifdef F___retarget_lock_release_recursive
void __retarget_lock_release_recursive(_LOCK_T lock)
{
    int32_t thread_id = sceKernelGetThreadId();
    if (lock->count == 1 || lock->thread_id != thread_id) {
        sceKernelUnlockLwMutex(&lock->mutex, 1);
    }
    lock->count--;
}
#endif

#ifdef F___retarget_lock_try_acquire_recursive
int __retarget_lock_try_acquire_recursive(_LOCK_T lock)
{
    int res = 0;
    int32_t thread_id = sceKernelGetThreadId();
    if (lock->count == 0 || lock->thread_id != thread_id) {
        res = sceKernelTryLockLwMutex(&lock->mutex, 1) != 0;
    }
    lock->count++;
    return res;
}
#endif

#ifdef F___retarget_lock_close_recursive
void __retarget_lock_close_recursive(_LOCK_T lock)
{
    sceKernelDeleteLwMutex(&lock->mutex);
}
#endif