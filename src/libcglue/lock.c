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
};

#ifdef F___lock___sfp_recursive_mutex
struct __lock __lock___sfp_recursive_mutex;
#endif

#ifdef F___lock___atexit_recursive_mutex
struct __lock __lock___atexit_recursive_mutex;
#endif

#ifdef F___lock___at_quick_exit_mutex
struct __lock __lock___at_quick_exit_mutex;
#endif

#ifdef F___lock___malloc_recursive_mutex
struct __lock __lock___malloc_recursive_mutex;
#endif

#ifdef F___lock___env_recursive_mutex
struct __lock __lock___env_recursive_mutex;
#endif

#ifdef F___lock___tz_mutex
struct __lock __lock___tz_mutex;
#endif

#ifdef F___lock___dd_hash_mutex
struct __lock __lock___dd_hash_mutex;
#endif

#ifdef F___lock___arc4random_mutex
struct __lock __lock___arc4random_mutex;
#endif

static inline void __common_lock_init(_LOCK_T lock)
{    
    sceKernelCreateLwMutex(&lock->mutex, "lock API mutex", PSP_LW_MUTEX_ATTR_THFIFO, 0, 0);
}

static inline void __common_lock_init_recursive(_LOCK_T lock)
{
    sceKernelCreateLwMutex(&lock->mutex, "lock API mutex Recursive", PSP_LW_MUTEX_ATTR_RECURSIVE, 0, 0);
}

static inline void __common_lock_close(_LOCK_T lock)
{
    sceKernelDeleteLwMutex(&lock->mutex);
}

static inline void __common_lock_close_recursive(_LOCK_T lock)
{
    sceKernelDeleteLwMutex(&lock->mutex);
}

#ifdef F___retarget_lock_init
void __retarget_lock_init(_LOCK_T *lock)
{
    _LOCK_T new_lock = (_LOCK_T)malloc(sizeof(struct __lock));
    __common_lock_init(new_lock);
    *lock = new_lock;
}
#endif

#ifdef F___retarget_lock_init_recursive
void __retarget_lock_init_recursive(_LOCK_T *lock)
{
    _LOCK_T new_lock = (_LOCK_T)malloc(sizeof(struct __lock));
    __common_lock_init_recursive(new_lock);
    *lock = new_lock;
}
#endif

#ifdef F___retarget_lock_close
void __retarget_lock_close(_LOCK_T lock)
{
	__common_lock_close(lock);
    free(lock);
}
#endif

#ifdef F___retarget_lock_close_recursive
void __retarget_lock_close_recursive(_LOCK_T lock)
{
    __common_lock_close_recursive(lock);
    free(lock);
}
#endif

#ifdef F___retarget_lock_acquire
void __retarget_lock_acquire(_LOCK_T lock)
{
	sceKernelLockLwMutex(&lock->mutex, 1, 0);
}
#endif

#ifdef F___retarget_lock_acquire_recursive
void __retarget_lock_acquire_recursive(_LOCK_T lock)
{
    sceKernelLockLwMutex(&lock->mutex, 1, 0);
}
#endif

#ifdef F___retarget_lock_try_acquire
int __retarget_lock_try_acquire(_LOCK_T lock)
{
	return sceKernelTryLockLwMutex(&lock->mutex, 1);
}
#endif

#ifdef F___retarget_lock_try_acquire_recursive
int __retarget_lock_try_acquire_recursive(_LOCK_T lock)
{
    return sceKernelTryLockLwMutex(&lock->mutex, 1);
}
#endif

#ifdef F___retarget_lock_release
void __retarget_lock_release(_LOCK_T lock)
{
	sceKernelUnlockLwMutex(&lock->mutex, 1);
}
#endif

#ifdef F___retarget_lock_release_recursive
void __retarget_lock_release_recursive(_LOCK_T lock)
{
    sceKernelUnlockLwMutex(&lock->mutex, 1);
}
#endif

#ifdef F___locks_init
extern struct __lock __lock___malloc_recursive_mutex;
extern struct __lock __lock___atexit_recursive_mutex;
extern struct __lock __lock___at_quick_exit_mutex;
extern struct __lock __lock___sfp_recursive_mutex;
extern struct __lock __lock___env_recursive_mutex;
extern struct __lock __lock___tz_mutex;
extern struct __lock __lock___dd_hash_mutex;
extern struct __lock __lock___arc4random_mutex;

void __locks_init()
{
    _LOCK_T lock_malloc = &__lock___malloc_recursive_mutex;
    _LOCK_T lock_atexit = &__lock___atexit_recursive_mutex;
    _LOCK_T lock_quick_exit = &__lock___at_quick_exit_mutex;
    _LOCK_T lock_sfp = &__lock___sfp_recursive_mutex;
    _LOCK_T lock_env = &__lock___env_recursive_mutex;
    _LOCK_T lock_tz = &__lock___tz_mutex;
    _LOCK_T lock_dd_hash = &__lock___dd_hash_mutex;
    _LOCK_T lock_arc4random = &__lock___arc4random_mutex;
    
    __common_lock_init_recursive(lock_malloc);
    __common_lock_init_recursive(lock_atexit);
    __common_lock_init(lock_quick_exit);
    __common_lock_init_recursive(lock_sfp);
    __common_lock_init_recursive(lock_env);
    __common_lock_init(lock_tz);
    __common_lock_init(lock_dd_hash);
    __common_lock_init(lock_arc4random);
}
#endif

#ifdef F___locks_deinit
extern struct __lock __lock___malloc_recursive_mutex;
extern struct __lock __lock___atexit_recursive_mutex;
extern struct __lock __lock___at_quick_exit_mutex;
extern struct __lock __lock___sfp_recursive_mutex;
extern struct __lock __lock___env_recursive_mutex;
extern struct __lock __lock___tz_mutex;
extern struct __lock __lock___dd_hash_mutex;
extern struct __lock __lock___arc4random_mutex;

void __locks_deinit()
{
    _LOCK_T lock_malloc = &__lock___malloc_recursive_mutex;
    _LOCK_T lock_atexit = &__lock___atexit_recursive_mutex;
    _LOCK_T lock_quick_exit = &__lock___at_quick_exit_mutex;
    _LOCK_T lock_sfp = &__lock___sfp_recursive_mutex;
    _LOCK_T lock_env = &__lock___env_recursive_mutex;
    _LOCK_T lock_tz = &__lock___tz_mutex;
    _LOCK_T lock_dd_hash = &__lock___dd_hash_mutex;
    _LOCK_T lock_arc4random = &__lock___arc4random_mutex;
    

    __common_lock_close_recursive(lock_malloc);
    __common_lock_close_recursive(lock_atexit);
    __common_lock_close(lock_quick_exit);
    __common_lock_close_recursive(lock_sfp);
    __common_lock_close_recursive(lock_env);
    __common_lock_close(lock_tz);
    __common_lock_close(lock_dd_hash);
    __common_lock_close(lock_arc4random);
}
#endif