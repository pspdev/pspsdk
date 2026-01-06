/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * prof.c - Main profiler code
 *
 * Copyright (c) 2005 urchin <c64psp@gmail.com>
 *
 */
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include <pspprof.h>

#define	GMON_PROF_ON	0
#define	GMON_PROF_BUSY	1
#define	GMON_PROF_ERROR	2
#define	GMON_PROF_OFF	3

#define GMONVERSION	0x00051879

#include <pspthreadman.h>

/** gmon.out file header */
struct gmonhdr 
{
        int lpc;        /* lowest pc address */
        int hpc;        /* highest pc address */
        int ncnt;       /* size of samples + size of header */
        int version;    /* version number */
        int profrate;   /* profiling clock rate */
        int resv[3];    /* reserved */
};

/** frompc -> selfpc graph */
struct rawarc 
{
        unsigned int frompc;
        unsigned int selfpc;
        unsigned int count;
};

/** context */
struct gmonparam 
{
        int state;
        unsigned int lowpc;         /* runtime text start (for range checks) */
        unsigned int highpc;        /* runtime text end (for range checks) */
        unsigned int lowpc_link;    /* link-time text start (for output) */
        unsigned int highpc_link;   /* link-time text end (for output) */
        unsigned int textsize;
        unsigned int hashfraction;

        int narcs;
        struct rawarc *arcs;

        int nsamples;
        unsigned int *samples;

        int timer;
        
        unsigned int pc;
};

/// holds context statistics
static struct gmonparam gp;

/// one histogram per four bytes of text space
#define	HISTFRACTION	4

/// define sample frequency - 1000 hz = 1ms
#define SAMPLE_FREQ     1000

/// have we allocated memory and registered already
static int initialized = 0;

/// defined by linker
extern int _ftext;
extern int _etext;

/* forward declarations */
__attribute__((__no_instrument_function__, __no_profile_instrument_function__))
void __gprof_cleanup(void);
__attribute__((__no_instrument_function__, __no_profile_instrument_function__))
void __mcount(unsigned int, unsigned int);
__attribute__((__no_instrument_function__, __no_profile_instrument_function__))
static SceUInt timer_handler(SceUID uid, SceKernelSysClock *c1, SceKernelSysClock *c2, void *common);

/** Initializes pg library

    After calculating the text size, initialize() allocates enough
    memory to allow fastest access to arc structures, and some more
    for sampling statistics. Note that this also installs a timer that
    runs at 1000 hert.
*/
__attribute__((__no_instrument_function__, __no_profile_instrument_function__))
static void initialize()
{
        initialized = 1;

        memset(&gp, '\0', sizeof(gp));
        gp.state = GMON_PROF_ON;

        /* For PRX modules, the code is relocated at load time.
           &_ftext and &_etext give us runtime (relocated) addresses.
           Link-time addresses start at 0 for PSP executables.

           Runtime:   &_ftext = relocated_base, &_etext = relocated_base + text_size
           Link-time: _ftext = 0, _etext = text_size

           So: lowpc_link = 0
               highpc_link = &_etext - &_ftext (which equals text_size)
        */
        gp.lowpc = (unsigned int)&_ftext;
        gp.highpc = (unsigned int)&_etext;
        gp.lowpc_link = 0;
        gp.highpc_link = (unsigned int)&_etext - (unsigned int)&_ftext;
        gp.textsize = gp.highpc - gp.lowpc;
        gp.hashfraction = HISTFRACTION;

        gp.narcs = (gp.textsize + gp.hashfraction - 1) / gp.hashfraction;
        gp.arcs = (struct rawarc *)malloc(sizeof(struct rawarc) * gp.narcs);
        if (gp.arcs == NULL)
        {
                gp.state = GMON_PROF_ERROR;
                return;
        }

        gp.nsamples = (gp.textsize + gp.hashfraction - 1) / gp.hashfraction;
        gp.samples = (unsigned int *)malloc(sizeof(unsigned int) * gp.nsamples);
        if (gp.samples == NULL)
        {
                free(gp.arcs);
                gp.arcs = 0;
                gp.state = GMON_PROF_ERROR;
                return;
        }

        memset((void *)gp.arcs, '\0', gp.narcs * (sizeof(struct rawarc)));
        memset((void *)gp.samples, '\0', gp.nsamples * (sizeof(unsigned int )));

        gp.timer = sceKernelCreateVTimer("gprof timer", NULL);
        if (gp.timer < 0)
        {
                free(gp.arcs);
                free(gp.samples);
                gp.arcs = 0;
                gp.samples = 0;
                gp.state = GMON_PROF_ERROR;
                return;
        }

        SceKernelSysClock sc;
        sc.hi = 0;
        sc.low = SAMPLE_FREQ;
        
        int thid = sceKernelGetThreadId();
        
        SceKernelThreadInfo info;
        memset(&info, 0, sizeof(info));
        info.size = sizeof(info);
        int ret = sceKernelReferThreadStatus(thid, &info);
        
        if(ret == 0)
        {
            void* timer_addr = timer_handler;
            if((info.attr & PSP_THREAD_ATTR_USER) == 0)
            {
                timer_addr += 0x80000000;
            }
        
            ret = sceKernelSetVTimerHandler(gp.timer, &sc, timer_addr, NULL);
        }
        
        if(ret == 0)
        {
            sceKernelStartVTimer(gp.timer);
        }
}

__attribute__((__no_instrument_function__, __no_profile_instrument_function__))
void gprof_start(void) {
        // There is already a profiling session running, let's stop it and ignore the result
        if (gp.state == GMON_PROF_ON) {
                gprof_stop(NULL, 0);
        }
        initialize();
}

__attribute__((__no_instrument_function__, __no_profile_instrument_function__))
void gprof_stop(const char* filename, int should_dump)
{
        FILE *fp;
        int i;
        struct gmonhdr hdr;

        if (gp.state != GMON_PROF_ON)
        {
                /* profiling was disabled anyway */
                return;
        }

        /* disable profiling before we make plenty of libc calls */
        gp.state = GMON_PROF_OFF;

        // Delete timer
        sceKernelStopVTimer(gp.timer);
        sceKernelDeleteVTimer(gp.timer);

        if (should_dump) {
                fp = fopen(filename, "wb");

                /* Header uses link-time addresses so psp-gprof can match ELF symbols */
                hdr.lpc = gp.lowpc_link;
                hdr.hpc = gp.highpc_link;
                hdr.ncnt = sizeof(hdr) + (sizeof(unsigned int) * gp.nsamples);
                hdr.version = GMONVERSION;
                hdr.profrate = SAMPLE_FREQ;
                hdr.resv[0] = 0;
                hdr.resv[1] = 0;
                hdr.resv[2] = 0;
                fwrite(&hdr, 1, sizeof(hdr), fp);
                fwrite(gp.samples, gp.nsamples, sizeof(unsigned int), fp);

                /* Arcs already store link-time addresses (converted in __mcount) */
                for (i=0; i<gp.narcs; i++)
                {
                        if (gp.arcs[i].count > 0)
                        {
                                fwrite(gp.arcs + i, sizeof(struct rawarc), 1, fp);
                        }
                }

                fclose(fp);
        }

        // Free memory
        free(gp.arcs);
        free(gp.samples);
}

/** Writes gmon.out dump file and stops profiling
    Called from atexit() handler; will dump out a gmon.out file 
    at cwd with all collected information.
*/
__attribute__((__no_instrument_function__, __no_profile_instrument_function__))
void __gprof_cleanup()
{
        gprof_stop("gmon.out", 1);
}

/** Internal C handler for _mcount()
    @param frompc    pc address of caller
    @param selfpc    pc address of current function

    Called from mcount.S to make life a bit easier. __mcount is called
    right before a function starts. GCC generates a tiny stub at the very
    beginning of each compiled routine, which eventually brings the 
    control to here. 
*/
__attribute__((__no_instrument_function__, __no_profile_instrument_function__))
void __mcount(unsigned int frompc, unsigned int selfpc)
{ 
        int e;
        struct rawarc *arc;

        if (initialized == 0)
        {
                initialize();
        }

        if (gp.state != GMON_PROF_ON)
        {
                /* returned off for some reason */
                return;
        }

        /* Mask upper bits and convert to link-time addresses.
           Link-time addresses = runtime addresses - gp.lowpc (since lowpc_link = 0) */
        frompc = (frompc & 0x0FFFFFFF) - gp.lowpc;
        selfpc = (selfpc & 0x0FFFFFFF) - gp.lowpc;

        /* Check if within text section (using link-time range) */
        if (frompc <= gp.highpc_link)
        {
                gp.pc = selfpc;
                e = frompc / gp.hashfraction;
                arc = gp.arcs + e;
                arc->frompc = frompc;
                arc->selfpc = selfpc;
                arc->count++;
        }
}

/** Internal timer handler
*/
__attribute__((__no_instrument_function__, __no_profile_instrument_function__))
static SceUInt timer_handler(SceUID uid, SceKernelSysClock *requested, SceKernelSysClock *actual, void *common)
{
        unsigned int frompc = gp.pc;  /* Already in link-time address */

        if (gp.state == GMON_PROF_ON)
        {
                /* Check if within text section (using link-time range) */
                if (frompc <= gp.highpc_link)
                {
                        int e = frompc / gp.hashfraction;
                        gp.samples[e]++;
                }
        }

        return SAMPLE_FREQ;
}
