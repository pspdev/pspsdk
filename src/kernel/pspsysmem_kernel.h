/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsysmem_kernel.h - Interface to the system memory manager (kernel).
 *
 * Copyright (c) 2005 James F.
 *
 */

/* Note: Some of the structures, types, and definitions in this file were
   extrapolated from symbolic debugging information found in the Japanese
   version of Puzzle Bobble. */

#ifndef PSPSYSMEMKERNEL_H
#define PSPSYSMEMKERNEL_H

#include <pspkerneltypes.h>
#include <psptypes.h>
#include <pspsysmem.h>

/** @defgroup SysMemKern System Memory Manager Kernel
  * This module contains routines to manage heaps of memory.
  */

/** @addtogroup SysMemKern System Memory Manager Kernel */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _PspPspSysMemPartitionInfo
{
	SceSize size;
	unsigned int startaddr;
	unsigned int memsize;
	unsigned int attr;
} PspPspSysMemPartitionInfo;

typedef struct SceGameInfo {
	u32 size; // 0
	u32 flags; // 4
	char umd_data_string[16]; // 8
	char expect_umd_data[16]; // 24
	char qtgp2[8]; // 40
	char qtgp3[16]; // 48
	u32 allow_replace_umd; // 64
	char title_id[16]; // 68
	u32 parental_level; // 84
	char vsh_version[8]; // 88
	u32 umd_cache_on; // 96
	u32 compiled_sdk_version; // 100
	u32 compiler_version; // 104
	u32 dnas; // 108
	u32 utility_location; // 112
	char vsh_bootfilename[64]; // 116
	char gamedata_id[16]; // 180
	char app_ver[8]; // 196
	char subscription_validity[8]; // 204
	int bootable; // 212
	int opnssmp_ver; // 216
} SceGameInfo;

/** Structure of a UID control block */
struct _uidControlBlock {
    struct _uidControlBlock *parent;
    struct _uidControlBlock *nextChild;
    struct _uidControlBlock *type;   //(0x8)
    u32 UID;					//(0xC)
    char *name;					//(0x10)
    unsigned char unk;
    unsigned char size;			// Size in words
    short attribute;
    struct _uidControlBlock *nextEntry;
} __attribute__((packed));
typedef struct _uidControlBlock SceUidControlBlock;
typedef struct _uidControlBlock uidControlBlock; // for compat reasons

typedef struct {
    u32 addr;
    u32 size;
} SceSysmemPartInfo;

typedef struct {
    u32 memSize;
    u32 unk4;
    u32 unk8;
    SceSysmemPartInfo other1; // 12
    SceSysmemPartInfo other2; // 20
    SceSysmemPartInfo vshell; // 28
    SceSysmemPartInfo scUser; // 36
    SceSysmemPartInfo meUser; // 44
    SceSysmemPartInfo extSc2Kernel; // 52
    SceSysmemPartInfo extScKernel; // 60
    SceSysmemPartInfo extMeKernel; // 68
    SceSysmemPartInfo extVshell; // 76
} SceSysmemPartTable;

typedef struct PspPspPartitionData {
    u32 unk[5];
    u32 size;
} PspPspPartitionData;

typedef struct PspPspSysMemPartition {
    struct PspPspSysMemPartition *next;
    u32 address;
    u32 size;
    u32 attributes;
    PspPspPartitionData *data;
} PspPspSysMemPartition;

/**
 * Query the parition information
 *
 * @param pid  - The partition id
 * @param info - Pointer to the ::PspPspSysMemPartitionInfo structure
 *
 * @return 0 on success.
 */
int sceKernelQueryMemoryPartitionInfo(int pid, PspPspSysMemPartitionInfo *info);

/**
 * Get the total amount of free memory.
 *
 * @param pid - The partition id
 *
 * @return The total amount of free memory, in bytes.
 */
SceSize sceKernelPartitionTotalFreeMemSize(int pid);

/**
 * Get the size of the largest free memory block.
 *
 * @param pid - The partition id
 *
 * @return The size of the largest free memory block, in bytes.
 */
SceSize sceKernelPartitionMaxFreeMemSize(int pid);

/**
 * Get the kernel to dump the internal memory table to Kprintf
 */
void sceKernelSysMemDump(void);

/**
 * Dump the list of memory blocks
 */
void sceKernelSysMemDumpBlock(void);

/**
 * Dump the tail blocks
 */
void sceKernelSysMemDumpTail(void);

/**
 * Set the protection of a block of ddr memory
 *
 * @param addr - Address to set protection on
 * @param size - Size of block
 * @param prot - Protection bitmask
 *
 * @return < 0 on error
 */
int sceKernelSetDdrMemoryProtection(void *addr, int size, int prot);

/**
 * Create a heap.
 *
 * @param partitionid - The UID of the partition where allocate the heap.
 * @param size - The size in bytes of the heap.
 * @param unk - Unknown, probably some flag or type, pass 1.
 * @param name - Name assigned to the new heap.
 *
 * @return The UID of the new heap, or if less than 0 an error. 
*/
SceUID sceKernelCreateHeap(SceUID partitionid, SceSize size, int unk, const char *name);

/**
 * Allocate a memory block from a heap.
 *
 * @param heapid - The UID of the heap to allocate from.
 * @param size - The number of bytes to allocate.
 *
 * @return The address of the allocated memory block, or NULL on error.
*/
void *sceKernelAllocHeapMemory(SceUID heapid, SceSize size);

/**
 * Free a memory block allocated from a heap.
 *
 * @param heapid - The UID of the heap where block belongs.
 * @param block - The block of memory to free from the heap.
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelFreeHeapMemory(SceUID heapid, void *block);

/**
 * Delete a heap.
 *
 * @param heapid - The UID of the heap to delete.
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelDeleteHeap(SceUID heapid);

/**
 * Get the amount of free size of a heap, in bytes.
 *
 * @param heapid - The UID of the heap
 *
 * @return the free size of the heap, in bytes. < 0 on error.
*/
SceSize sceKernelHeapTotalFreeSize(SceUID heapid);

/**
 * Get a UID control block
 *
 * @param uid - The UID to find
 * @param block - Pointer to hold the pointer to the block
 *
 * @return 0 on success
 */
int sceKernelGetSceUidControlBlock(SceUID uid, SceUidControlBlock** block);

/**
 * Get a UID control block on a particular type
 *
 * @param uid - The UID to find
 * @param type - Pointer to the type UID block
 * @param block - Pointer to hold the pointer to the block
 *
 * @return 0 on success
 */
int sceKernelGetSceUidControlBlockWithType(SceUID uid, SceUidControlBlock* type, SceUidControlBlock** block);

/**
 * Get the root of the UID tree (1.5+ only)
 *
 * @return Pointer to the UID tree root
 */
SceUidControlBlock* SysMemForKernel_536AD5E1(void);

/**
 * Delete a UID
 *
 * @param uid - The UID to delete
 *
 * @return 0 on success
 */
int sceKernelDeleteUID(SceUID uid);

/**
 * Get the model of PSP
 *
 * @return <= 0 original, 1 slim
 */
int sceKernelGetModel(void);

/**
 * Set the version of the SDK with which the caller was compiled.
 * Version numbers are as for sceKernelDevkitVersion().
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelSetCompiledSdkVersion(int version);

/**
 * Get the SDK version set with sceKernelSetCompiledSdkVersion().
 *
 * @return Version number, or 0 if unset.
 */
int sceKernelGetCompiledSdkVersion(void);

/**
 * Gets the information of the game. (2.00+ ?)
 *
 * @returns Pointer to the game information on success. NULL otherwise.
 *
 * @attention Needs to link to `pspsysmem_kernel` stub.
 */
SceGameInfo *sceKernelGetGameInfo();

/**
 * Gets the current status of the system.
 *
 * @returns The status of the system.
 *
 * @attention Needs to link to `pspsysmem_kernel` stub.
 */
int sceKernelGetSystemStatus();

/**
 * Get a UID control block
 *
 * @param uid - The UID to find
 * @param block - Pointer to hold the pointer to the block
 *
 * @return 0 on success
 *
 * @attention Needs to link to `pspsysmem_kernel` stub.
 */
int sceKernelGetUIDcontrolBlock(SceUID uid, SceUidControlBlock** block);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* PSPSYSMEMKERNEL_H */
