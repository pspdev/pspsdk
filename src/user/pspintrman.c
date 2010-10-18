/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspintrman.c - Interface to the system interupt manager.
 *
 * Copyright (c) 2005 James F. (tyranid@gmail.com)
 * Copyright (c) 2005 Florin Sasu (...)
 *
 * $Id: pspintrman.c 1207 2005-10-23 05:50:29Z mrbrown $
 */

#include <pspintrman.h>

const char* PspInterruptNames[67] = {//67 interrupts
	0, 0, 0, 0, "GPIO", "ATA_ATAPI", "UmdMan", "MScm0",
	"Wlan", 0, "Audio", 0, "I2C", 0, "SIRCS_IrDA",
	"Systimer0", "Systimer1", "Systimer2", "Systimer3",
	"Thread0", "NAND", "DMACPLUS", "DMA0", "DMA1",
	"Memlmd", "GE", 0, 0, 0, 0, "Display", "MeCodec", 0,
	0, 0, 0, "HP_Remote", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "MScm1", "MScm2",
	0, 0, 0, "Thread1", "Interrupt"
};
