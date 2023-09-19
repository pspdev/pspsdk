/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspiofilemgr_devctl.h - File attributes and directory entries.
 *
 */

#ifndef PSPIOFILEMGR_DEVCTL_H
#define PSPIOFILEMGR_DEVCTL_H

#include <psptypes.h>

/* This sceIoDevctl command gets the device capacity. */
#define SCE_PR_GETDEV 0x02425818

/* This structure stores the device capacity using SCE_PR_GETDEV in sceIoDevctl */
typedef struct SceDevInf {
    /* max logical cluster x unit */
    uint32_t maxClusters;
    /* number of empty clusters */
    uint32_t freeClusters;
    /* cluster of empty logical block */
    uint32_t maxSectors;
    /* bytes x logical sector */
    int32_t sectorSize;
    /* sector x cluster */
    int32_t sectorCount;
} SceDevInf;

typedef struct SceDevctlCmd {
    SceDevInf *dev_inf;
} SceDevctlCmd;

#endif /* PSPIOFILEMGR_DEVCTL_H */
