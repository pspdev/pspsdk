/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Sample to demonstrate proper use of the mp3 library
 *
 * Copyright (c) 2008 Alexander Berl <raphael@fx-world.org>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <stdio.h>
#include <pspaudio.h>
#include <pspmp3.h>
#include <psputility.h>


/* Define the module info section */
PSP_MODULE_INFO("Mp3Test", 0, 0, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);
PSP_HEAP_SIZE_KB(-1024);

#define MP3FILE "Test.mp3"

/* Define printf, just to make typing easier */
#define printf  pspDebugScreenPrintf

static int isrunning = 1;
/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
    isrunning = 0;

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
    thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
    if (thid >= 0)
	sceKernelStartThread(thid, 0, 0);
    return thid;
}


// Input and Output buffers
unsigned char	mp3Buf[16*1024]  __attribute__((aligned(64)));
unsigned char	pcmBuf[16*(1152/2)]  __attribute__((aligned(64)));


// Macro to allow formatted input without having to use stdargs.h
#define ERRORMSG(...) { char msg[128]; sprintf(msg,__VA_ARGS__); error(msg); }

// Print out an error message and quit after user input
void error( char* msg )
{
	SceCtrlData pad;
	pspDebugScreenClear();
	pspDebugScreenSetXY(0, 0);
	printf(msg);
	printf("Press X to quit.\n");
	while (isrunning)
	{
		sceCtrlReadBufferPositive(&pad, 1);
		if (pad.Buttons & PSP_CTRL_CROSS)
			break;
		sceDisplayWaitVblankStart();
	}
	sceKernelExitGame();
}

int fillStreamBuffer( int fd, int handle )
{
	unsigned char* dst;
	long int write;
	long int pos;
	// Get Info on the stream (where to fill to, how much to fill, where to fill from)
	int status = sceMp3GetInfoToAddStreamData( handle, &dst, &write, &pos);
	if (status<0)
	{
		ERRORMSG("ERROR: sceMp3GetInfoToAddStreamData returned 0x%08X\n", status);
	}

	// Seek file to position requested
	status = sceIoLseek32( fd, pos, SEEK_SET );
	if (status<0)
	{
		ERRORMSG("ERROR: sceIoLseek32 returned 0x%08X\n", status);
	}
	
	// Read the amount of data
	int read = sceIoRead( fd, dst, write );
	if (read < 0)
	{
		ERRORMSG("ERROR: Could not read from file - 0x%08X\n", read);
	}
	
	if (read==0)
	{
		// End of file?
		return 0;
	}
	
	// Notify mp3 library about how much we really wrote to the stream buffer
	status = sceMp3NotifyAddStreamData( handle, read );
	if (status<0)
	{
		ERRORMSG("ERROR: sceMp3NotifyAddStreamData returned 0x%08X\n", status);
	}
	
	return (pos>0);
}

/* main routine */
int main(int argc, char *argv[])
{
    SceCtrlData pad;

    //init screen and callbacks
    pspDebugScreenInit();
    pspDebugScreenClear();
    SetupCallbacks();
	
    // Setup Pad
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(0);

	// Load modules
	int status = sceUtilityLoadModule(PSP_MODULE_AV_AVCODEC);
	if (status<0)
	{
		ERRORMSG("ERROR: sceUtilityLoadModule(PSP_MODULE_AV_AVCODEC) returned 0x%08X\n", status);
	}
	
	status = sceUtilityLoadModule(PSP_MODULE_AV_MP3);
	if (status<0)
	{
		ERRORMSG("ERROR: sceUtilityLoadModule(PSP_MODULE_AV_MP3) returned 0x%08X\n", status);
	}
	
	// Open the input file
	int fd = sceIoOpen( MP3FILE, PSP_O_RDONLY, 0777 );
	if (fd<0)
	{
		ERRORMSG("ERROR: Could not open file '%s' - 0x%08X\n", MP3FILE, fd);
	}
	
	// Init mp3 resources
	status = sceMp3InitResource();
	if (status<0)
	{
		ERRORMSG("ERROR: sceMp3InitResource returned 0x%08X\n", status);
	}
	
	// Reserve a mp3 handle for our playback
	SceMp3InitArg mp3Init;
	mp3Init.mp3StreamStart = 0;
	mp3Init.mp3StreamEnd = sceIoLseek32( fd, 0, SEEK_END );
	mp3Init.mp3Buf = mp3Buf;
	mp3Init.mp3BufSize = sizeof(mp3Buf);
	mp3Init.pcmBuf = pcmBuf;
	mp3Init.pcmBufSize = sizeof(pcmBuf);
	
	int handle = sceMp3ReserveMp3Handle( &mp3Init );
	if (handle<0)
	{
		ERRORMSG("ERROR: sceMp3ReserveMp3Handle returned 0x%08X\n", handle);
	}
	
	// Fill the stream buffer with some data so that sceMp3Init has something to work with
	fillStreamBuffer( fd, handle );
	
	status = sceMp3Init( handle );
	if (status<0)
	{
		ERRORMSG("ERROR: sceMp3Init returned 0x%08X\n", status);
	}
	
	int channel = -1;
	int samplingRate = sceMp3GetSamplingRate( handle );
	int numChannels = sceMp3GetMp3ChannelNum( handle );
	int lastDecoded = 0;
	int volume = PSP_AUDIO_VOLUME_MAX;
	int numPlayed = 0;
	int paused = 0;
	int lastButtons = 0;
	int loop = 0;
	while (isrunning)
	{
		sceDisplayWaitVblankStart();
		pspDebugScreenSetXY(0, 0);
		printf("PSP Mp3 Sample v1.0 by Raphael\n\n");
		printf("Playing '%s'...\n", MP3FILE);
		printf(" %i Hz\n", samplingRate);
		printf(" %li kbit/s\n", sceMp3GetBitRate( handle ));
		printf(" %s\n", numChannels==2?"Stereo":"Mono");
		printf(" %s\n\n", loop==0?"No loop":"Loop");
		int playTime = samplingRate>0?numPlayed / samplingRate:0;
		printf(" Playtime: %02i:%02i\n", playTime/60, playTime%60 );
		printf("\n\n\nPress CIRCLE to Pause/Resume playback\nPress TRIANGLE to reset playback\nPress CROSS to switch loop mode\nPress SQUARE to stop playback and quit\n");
		
		if (!paused)
		{
			// Check if we need to fill our stream buffer
			if (sceMp3CheckStreamDataNeeded( handle )>0)
			{
				fillStreamBuffer( fd, handle );
			}

			// Decode some samples
			short* buf;
			int bytesDecoded;
			int retries = 0;
			// We retry in case it's just that we reached the end of the stream and need to loop
			for (;retries<1;retries++)
			{
				bytesDecoded = sceMp3Decode( handle, &buf );
				if (bytesDecoded>0)
					break;
				
				if (sceMp3CheckStreamDataNeeded( handle )<=0)
					break;
				
				if (!fillStreamBuffer( fd, handle ))
				{
					numPlayed = 0;
				}
			}
			if (bytesDecoded<0 && bytesDecoded!=0x80671402)
			{
				ERRORMSG("ERROR: sceMp3Decode returned 0x%08X\n", bytesDecoded);
			}
			
			// Nothing more to decode? Must have reached end of input buffer
			if (bytesDecoded==0 || bytesDecoded==0x80671402)
			{
				paused = 1;
				sceMp3ResetPlayPosition( handle );
				numPlayed = 0;
			}
			else
			{
				// Reserve the Audio channel for our output if not yet done
				if (channel<0 || lastDecoded!=bytesDecoded)
				{
					if (channel>=0)
						sceAudioSRCChRelease();
					
					channel = sceAudioSRCChReserve( bytesDecoded/(2*numChannels), samplingRate, numChannels );
				}
				// Output the decoded samples and accumulate the number of played samples to get the playtime
				numPlayed += sceAudioSRCOutputBlocking( volume, buf );
			}
		}
		
		sceCtrlPeekBufferPositive(&pad, 1);
		
		if (pad.Buttons!=lastButtons)
		{
			if (pad.Buttons & PSP_CTRL_CIRCLE)
			{
				paused ^= 1;
			}
			
			if (pad.Buttons & PSP_CTRL_TRIANGLE)
			{
				// Reset the stream and playback status
				sceMp3ResetPlayPosition( handle );
				numPlayed = 0;
			}
			
			if (pad.Buttons & PSP_CTRL_CROSS)
			{
				loop = (loop==0?-1:0);
				status = sceMp3SetLoopNum( handle, loop );
				if (status<0)
				{
					ERRORMSG("ERROR: sceMp3SetLoopNum returned 0x%08X\n", status);
				}
			}
			
			if (pad.Buttons & PSP_CTRL_SQUARE)
			{
				break;
			}
			
			lastButtons = pad.Buttons;
		}
    }
    
    // Cleanup time...
    if (channel>=0)
		sceAudioSRCChRelease();
	
	status = sceMp3ReleaseMp3Handle( handle );
	if (status<0)
	{
		ERRORMSG("ERROR: sceMp3ReleaseMp3Handle returned 0x%08X\n", status);
	}
	
	status = sceMp3TermResource();
	if (status<0)
	{
		ERRORMSG("ERROR: sceMp3TermResource returned 0x%08X\n", status);
	}
	
	status = sceIoClose( fd );
	if (status<0)
	{
		ERRORMSG("ERROR: sceIoClose returned 0x%08X\n", status);
	}
	
    sceKernelExitGame();

    return 0;
}
