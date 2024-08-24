/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspprof.h - Prototypes for the profiler library
 *
 * Copyright (c) 2006 Urchin
 *
 */
#ifndef __PSPPROF_H__
#define __PSPPROF_H__

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Start the profiler.
 * If the profiler is already running, this function stop previous one,
 * and ignore the result.
 * Finally, it initializes a new profiler session.
 */
__attribute__((__no_instrument_function__, __no_profile_instrument_function__))
void gprof_start(void);
/**
 * Stop the profiler.
 * If the profiler is not running, this function does nothing.
 * @param filename The name of the file to write the profiling data to.
 * @param should_dump If 1, the profiling data will be written to the file.
 * If 0, the profiling data will be discarded.
 */
__attribute__((__no_instrument_function__, __no_profile_instrument_function__))
void gprof_stop(const char* filename, int should_dump);

#ifdef __cplusplus
}
#endif

#endif	/* __PSPPROF_H__ */
