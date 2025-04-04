/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * memory.c - Code to get accurate reporting of available (video) memory.
 *
 * Copyright (c) 2023 Ivy Bowling <motolegacy@proton.me>
 *
 */

#include <stdlib.h>
#include <stddef.h>
#include <pspsdk.h>
#include <psptypes.h>

static u32 _pspSdkGetMaxLineareMemorySize(void)
{
    u32 size, blocksize;
    u8 *ram;

    size = 0;
    blocksize = 1024 * 1024; // 1 kB

    while (blocksize)
    {
        /* Increase the size by the block */
        size += blocksize;
        ram = (u8*) malloc(size);

        if (!ram)
        {
            size -= blocksize;
            blocksize >>= 1;
        }
        else
        {
            free(ram);
        }
    }

    return size;
}

SceSize pspSdkTotalFreeUserMemSize(void)
{
    u8 **ram, **temp;
    u32 size, count, x;

    ram = NULL;
    size = count = 0;

    int intc = pspSdkDisableInterrupts();

    while (1) 
    {
        /* Check entry size */
        if (!(count % 10))
        {
            /* Allocate more entries if needed */
            temp = (u8**) realloc(ram, sizeof(u8*) * (count + 10));

            if (!temp)
                break;

            /* Update entries and their size */
            ram = temp;
            size += (sizeof(u8*) * 10);
        }

        x = _pspSdkGetMaxLineareMemorySize();

        if (!x)
            break;

        /* Try to do the memory allocation */
        ram[count] = (u8*) malloc(x);

        if (!ram[count])
            break;

        size += x;
        count++;
    }

    /* Free everything we've allocated */
    if (ram)
    {
        for (x = 0; x < count; x++)
        {
            free(ram[x]);
        }

        free(ram);
    }

    pspSdkEnableInterrupts(intc);

    /* Amount we were able to allocate before running out, in bytes. */
    return size;
}