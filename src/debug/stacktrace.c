/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * callstack.c - Return stack generation for MIPS processors.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id: stacktrace.c 1095 2005-09-27 21:02:16Z jim $
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <string.h>

#define CALL		 0x0C000000
#define CALL_MASK 	 0xFC000000
#define IS_CALL(x)   (((x) & CALL_MASK) == CALL)
#define CALL_ADDR(x) (((x) & ~CALL_MASK) << 2)

extern u32 _ftext;
extern u32 _etext;

/* Ideally should be something which is automatic */
#define ELF_START    (&_ftext)
#define ELF_END		 (&_etext)

/* This is a blatently wrong way of doing a stack trace, but I felt as long as you use some intelligence you 
   could easily work out if some calls in the trace were invalid :P */
static int _pspDebugDoStackTrace(u32 *sp, u32 *sp_end, u32 *ra, PspDebugStackTrace *trace, int max)
{
	int count = 0;
	int recurse = 0;

	if((ra >= (ELF_START + 2)) && (ra < ELF_END) && (IS_CALL(ra[-2])))
	{
		trace[count].func_addr = CALL_ADDR(ra[-2]);
		trace[count].call_addr = (u32) (&ra[-2]);
		count++;
	}

	while((count < max) && (sp < sp_end))
	{
		u32 *addr;
		/* Try and find all the pointers on the stack, then see if they are within range 
		   and point to a valid return address. There is possible false positives with this
		   but tbh it is better than nothing */
		addr = (u32*) *sp;

		/* Check that the address could possibly be a valid ra address */
		if((addr >= (ELF_START + 2)) && (addr < ELF_END))
		{
			if(IS_CALL(addr[-2]))
			{
				if((count == 1) && (addr == ra) && (!recurse))
				{
					/* Set recurse to 1 so any further calls from ra will be caught */
					/* This is not ideal, but it is to try and prevent the more likely case
					   of the first ra being found on the stack when first parsing */
					recurse = 1;
				}
				else
				{
					trace[count].func_addr = CALL_ADDR(addr[-2]);
					trace[count].call_addr = (u32) (&addr[-2]);
					count++;
				}
			}
		}

		sp++;
	}

	return count;
}

int pspDebugGetStackTrace2(PspDebugRegBlock *regs, PspDebugStackTrace *trace, int max)
{
	u32 *curr_sp;
	u32 *sp_end;
	u32 *curr_ra;
	int curr_thid;
	int count = 0;
	SceKernelThreadInfo th_stat;

	/* This is a real simple (and dirty way) of getting a stack trace, none of this code following shitz */
	/* Relies on the system not being totally vaporised on an exception */

	if((trace == NULL) || (max < 1))
	{
		return 0;
	}

	curr_thid = sceKernelGetThreadId();
	if(curr_thid >= 0)
	{
		memset(&th_stat, 0, sizeof(th_stat));
		th_stat.size = sizeof(th_stat);
		if(sceKernelReferThreadStatus(curr_thid, &th_stat) >= 0)
		{
			sp_end = (u32*) ((u8*) th_stat.stack + th_stat.stackSize);
			curr_sp = (u32*) (regs->r[29] & ~3);
			curr_ra = (u32*) (regs->r[31]);

			count = _pspDebugDoStackTrace(curr_sp, sp_end, curr_ra, trace, max);
		}
	}

	return count;
}
