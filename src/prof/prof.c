/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * prof.c - Main profiler code
 *
 * Copyright (c) 2005 urchin <c64psp@gmail.com>
 *
 * $Id$
 */
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

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
        unsigned int lowpc;
        unsigned int highpc;
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
void gprof_cleanup(void);
void __mcount(unsigned int, unsigned int);
static SceUInt timer_handler(SceUID uid, SceKernelSysClock *c1, SceKernelSysClock *c2, void *common);

/** Initializes pg library

    After calculating the text size, initialize() allocates enough
    memory to allow fastest access to arc structures, and some more
    for sampling statistics. Note that this also installs a timer that
    runs at 1000 hert.
*/
static void initialize()
{
        initialized = 1;

        memset(&gp, '\0', sizeof(gp));
        gp.state = GMON_PROF_ON;
        gp.lowpc = (unsigned int)&_ftext;
        gp.highpc = (unsigned int)&_etext;
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

        SceKernelSysClock sc;
        sc.hi = 0;
        sc.low = SAMPLE_FREQ;
        
        int thid = sceKernelGetThreadId();
        
        SceKernelThreadInfo info;
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

/** Writes gmon.out dump file and stops profiling

    Called from atexit() handler; will dump out a host:gmon.out file 
    with all collected information.
*/
void gprof_cleanup()
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

        sceKernelStopVTimer(gp.timer);

        fp = fopen("gmon.out", "wb");
        hdr.lpc = gp.lowpc;
        hdr.hpc = gp.highpc;
        hdr.ncnt = sizeof(hdr) + (sizeof(unsigned int) * gp.nsamples);
        hdr.version = GMONVERSION;
        hdr.profrate = SAMPLE_FREQ;
        hdr.resv[0] = 0;
        hdr.resv[1] = 0;
        hdr.resv[2] = 0;
        fwrite(&hdr, 1, sizeof(hdr), fp);
        fwrite(gp.samples, gp.nsamples, sizeof(unsigned int), fp);

        for (i=0; i<gp.narcs; i++)
        {
                if (gp.arcs[i].count > 0)
                {
                        fwrite(gp.arcs + i, sizeof(struct rawarc), 1, fp);
                }
        }

        fclose(fp);
}

/** Internal C handler for _mcount()
    @param frompc    pc address of caller
    @param selfpc    pc address of current function

    Called from mcount.S to make life a bit easier. __mcount is called
    right before a function starts. GCC generates a tiny stub at the very
    beginning of each compiled routine, which eventually brings the 
    control to here. 
*/
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

        frompc = frompc & 0x0FFFFFFF;
        selfpc = selfpc & 0x0FFFFFFF;

        /* call might come from stack */
        if (frompc >= gp.lowpc && frompc <= gp.highpc)
        {
                gp.pc = selfpc;
                e = (frompc - gp.lowpc) / gp.hashfraction;
                arc = gp.arcs + e;
                arc->frompc = frompc;
                arc->selfpc = selfpc;
                arc->count++;
        }
}

/** Internal timer handler
*/
static SceUInt timer_handler(SceUID uid, SceKernelSysClock *requested, SceKernelSysClock *actual, void *common)
{
        unsigned int frompc = gp.pc;

        if (gp.state == GMON_PROF_ON)
        {
                /* call might come from stack */
                if (frompc >= gp.lowpc && frompc <= gp.highpc)
                {
                        int e = (frompc - gp.lowpc) / gp.hashfraction;
                        gp.samples[e]++;
                }
        }

        return SAMPLE_FREQ;
}
