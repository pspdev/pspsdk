/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Sample to demonstrate savedata decryption using sceChnnlsv
 *
 * Copyright (c) 2005 Jim Paris <jim@jtan.com>
 * Coypright (c) 2005 psp123
 *
 */

#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <psptypes.h>
#include <psputility.h>

#include <stdio.h>
#include <string.h>

#include "decrypt.h"

PSP_MODULE_INFO("SaveDecrypt", 0, 1, 1);

#define printf pspDebugScreenPrintf

#if 0
  /* Old format save with no key, supported by 1.0+ firmware */
  const char *decrypted = "ms0:/PLAIN.BIN";
  const char *encrypted = "ms0:/PSP/SAVEDATA/DATA111110000/DATA.BIN";
  const unsigned char *gamekey = NULL;
#else
  /* New format save with a key, supported by 2.0+ firmware */
  const char *decrypted = "ms0:/PLAIN.BIN";
  const char *encrypted = "ms0:/PSP/SAVEDATA/DATA222220000/DATA.BIN";
  const unsigned char gamekey[] = { 
	  0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
	  0xFA, 0xCA, 0xDE, 0x00, 0xDE, 0xAD, 0xBE, 0xEF
  };
#endif

int waitbutton(int mask) {
	SceCtrlData paddata;
	do {
		sceDisplayWaitVblankStart();
		sceCtrlReadBufferPositive(&paddata, 1);
	} while((paddata.Buttons & mask));
	do {
		sceDisplayWaitVblankStart();
		sceCtrlReadBufferPositive(&paddata, 1);
	} while(!(paddata.Buttons & mask));
	return paddata.Buttons;
}

int main(int argc, char *argv[])
{
	int i, ret;

	pspDebugScreenInit();
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

	printf("Save Decrypt Sample\n");
	printf("by Jim Paris and psp123\n\n");

	printf("Will decrypt: %s\n", encrypted);
	printf("   Using key:");
	if(gamekey) {
		for (i = 0; i < 0x10; i++)
			printf(" %02x", gamekey[i]);
	} else {
		printf(" none");
	}
	printf("\n\n");
	printf(" Output file: %s\n\n", decrypted);
	printf("Press X to continue, or O to quit.\n\n");

	if (waitbutton(PSP_CTRL_CROSS | PSP_CTRL_CIRCLE) & PSP_CTRL_CIRCLE) 
		goto out;

	printf("Working...\n\n");

	ret = decrypt_file(decrypted, encrypted, gamekey);
	if(ret < 0) {
		printf("Error: decrypt_file() returned %d\n\n", ret);
	} else {
		printf("Successfully wrote %d bytes to\n", ret);
		printf("  %s\n\n", decrypted);
	}

	printf("Press any button to quit\n");
	waitbutton(-1);

 out:
	sceKernelExitGame();
	return 0;
}
