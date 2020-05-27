/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Sample to demonstrate proper use of the systemparam functions
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <stdio.h>
#include <string.h>
#include <pspmoduleinfo.h>
#include <psputility.h>

/* Define the module info section */
PSP_MODULE_INFO("SystemParam Sample", 0, 1, 0);

//Just to leave room for expansion
#define NUM_SYSTEMPARAMS 15

/* Define printf, just to make typing easier */
#define printf  pspDebugScreenPrintf

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
    sceKernelExitGame();

	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
    int cbid;
    cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
    int thid = 0;
    thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);
    if (thid >= 0)
	sceKernelStartThread(thid, 0, 0);
    return thid;
}

void printSystemParam(int id, int iVal, char *sVal) {
	switch(id) {
		case(PSP_SYSTEMPARAM_ID_STRING_NICKNAME):
			printf("%-17s: %s\n", "Nickname", sVal);
			break;
		case(PSP_SYSTEMPARAM_ID_INT_ADHOC_CHANNEL):
			printf("%-17s: %d\n", "AdHoc Channel", iVal);
			break;
		case(PSP_SYSTEMPARAM_ID_INT_WLAN_POWERSAVE):
			printf("%-17s: %s\n", "WLAN Powersave", iVal == 0 ? "enabled   " : "disabled");
			break;
		case(PSP_SYSTEMPARAM_ID_INT_DATE_FORMAT):
			switch(iVal) {
				case(PSP_SYSTEMPARAM_DATE_FORMAT_YYYYMMDD):
					printf("%-17s: YYYYMMDD\n", "Date Format");
					break;
				case(PSP_SYSTEMPARAM_DATE_FORMAT_MMDDYYYY):
					printf("%-17s: MMDDYYYY\n", "Date Format");
					break;
				case(PSP_SYSTEMPARAM_DATE_FORMAT_DDMMYYYY):
					printf("%-17s: DDMMYYYY\n", "Date Format");
					break;
				default:
					printf("%-17s: INVALID\n", "Date Format");
			}
			break;
		case(PSP_SYSTEMPARAM_ID_INT_TIME_FORMAT):
			switch(iVal) {
				case(PSP_SYSTEMPARAM_TIME_FORMAT_24HR):
					printf("%-17s: 24HR\n", "Time Format");
					break;
				case(PSP_SYSTEMPARAM_TIME_FORMAT_12HR):
					printf("%-17s: 12HR\n", "Time Format");
					break;
				default:
					printf("%-17s: INVALID\n", "Time Format");
			}
			break;
		case(PSP_SYSTEMPARAM_ID_INT_TIMEZONE):
			printf("%-17s: %d\n", "Timezone", iVal);
			break;
		case(PSP_SYSTEMPARAM_ID_INT_DAYLIGHTSAVINGS):
			switch(iVal) {
				case(PSP_SYSTEMPARAM_DAYLIGHTSAVINGS_STD):
					printf("%-17s: standard\n", "Daylight Savings");
					break;
				case(PSP_SYSTEMPARAM_DAYLIGHTSAVINGS_SAVING):
					printf("%-17s: saving\n", "Daylight Savings");
					break;
				default:
					printf("%-17s: INVALID\n", "Daylight Savings");
			}
			break;
		case(PSP_SYSTEMPARAM_ID_INT_LANGUAGE):
			switch(iVal) {
				case(PSP_SYSTEMPARAM_LANGUAGE_JAPANESE):
					printf("%-17s: Japanese\n", "Language");
					break;
				case(PSP_SYSTEMPARAM_LANGUAGE_ENGLISH):
					printf("%-17s: English\n", "Language");
					break;
				case(PSP_SYSTEMPARAM_LANGUAGE_FRENCH):
					printf("%-17s: French\n", "Language");
					break;
				case(PSP_SYSTEMPARAM_LANGUAGE_SPANISH):
					printf("%-17s: Spanish\n", "Language");
					break;
				case(PSP_SYSTEMPARAM_LANGUAGE_GERMAN):
					printf("%-17s: German\n", "Language");
					break;
				case(PSP_SYSTEMPARAM_LANGUAGE_ITALIAN):
					printf("%-17s: Italian\n", "Language");
					break;
				case(PSP_SYSTEMPARAM_LANGUAGE_DUTCH):
					printf("%-17s: Dutch\n", "Language");
					break;
				case(PSP_SYSTEMPARAM_LANGUAGE_PORTUGUESE):
					printf("%-17s: Portuguese\n", "Language");
					break;
				case(PSP_SYSTEMPARAM_LANGUAGE_KOREAN):
					printf("%-17s: Korean\n", "Language");
					break;
				default:
					printf("%-17s: INVALID\n", "Language");
			}
			break;
		case(PSP_SYSTEMPARAM_ID_INT_UNKNOWN):
			printf("%-17s: %d (1 on NA PSPs and 0 on JAP PSPs, v1.5+ only)\n", "Unknown:", iVal);
			break;
		default:
			printf("%-17s: int 0x%08X, string '%s'\n", "Unknown", iVal, sVal);
	}
}

/* main routine */
int main(int argc, char *argv[])
{
    char sVal[256];
    int iVal;
    int i;
    
    //init screen and callbacks
    pspDebugScreenInit();
    pspDebugScreenClear();
    
    SetupCallbacks();

    //fetch and print out power and battery information
    pspDebugScreenSetXY(0, 0);
    printf("SystemParam Sample v1.0 by John_K\n\n"); 
    	
    for (i = 0; i <= NUM_SYSTEMPARAMS; i++) {
    	iVal = 0xDEADBEEF;
    	memset(sVal, 0, 256);
    	if(sceUtilityGetSystemParamInt(i, &iVal) != PSP_SYSTEMPARAM_RETVAL_FAIL)
    		printSystemParam(i, iVal, sVal);
    	if(sceUtilityGetSystemParamString(i, sVal, 256) != PSP_SYSTEMPARAM_RETVAL_FAIL)
    		printSystemParam(i, iVal, sVal);
    }

    sceKernelSleepThread();
    sceKernelExitGame();

    return 0;
}
