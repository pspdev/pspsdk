/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic sample to demonstrate some fileio functionality.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspumd.h>

#include <string.h>

PSP_MODULE_INFO("Dumper", 0, 1, 1);

#define printf pspDebugScreenPrintf


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

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

/* Build a path, append a directory slash if requested */
void build_path(char *output, const char *root, const char *path, int append)
{
	while(*root != 0)
	{
		*output++ = *root++;
	}

	if(*(root-1) != '/')
	{
		*output++ = '/';
	}

	while(*path != 0)
	{
		*output++ = *path++;
	}
	if(append)
		*output++ = '/';

	*output++ = 0;
}

/* Define a write buffer */
char write_buffer[128*1024];

void write_file(const char *read_loc, const char *write_loc, const char *name)
{
	int fdin;
	int fdout;
	char readpath[256];
	char writepath[256];

	build_path(readpath, read_loc, name, 0);
	build_path(writepath, write_loc, name, 0);
	printf("Writing %s\n", writepath);

	fdin = sceIoOpen(readpath, PSP_O_RDONLY, 0777);
	if(fdin >= 0)
	{
		int bytesRead = 1;
		fdout = sceIoOpen(writepath, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
		if(fdout < 0)
		{
			printf("Couldn't open %s\n", writepath);
		}

		bytesRead = sceIoRead(fdin, write_buffer, sizeof(write_buffer));
		while((bytesRead > 0) && (fdout >= 0))
		{
			sceIoWrite(fdout, write_buffer, bytesRead);
			bytesRead = sceIoRead(fdin, write_buffer, sizeof(write_buffer));
		}

		if(fdout >= 0)
		{
			sceIoClose(fdout);
		}

		if(fdin >= 0)
		{
			sceIoClose(fdin);
		}
	}
	else
	{
		printf("Couldn't open %s\n", readpath);
	}
}

void DumpBootBin(void)
{
	int i;
	int fd;

	i = sceUmdCheckMedium();
	if(i == 0)
	{
		printf("Insert UMD\n");
		i = sceUmdWaitDriveStat(PSP_UMD_PRESENT);
	}

	i = sceUmdActivate(1, "disc0:");
	printf("Mounted disc\n");

	i = sceUmdWaitDriveStat(PSP_UMD_READY);

	/* Open the UMD_DATA.BIN */
	fd = sceIoOpen("disc0:/UMD_DATA.BIN", PSP_O_RDONLY, 0777);
	if(fd >= 0)
	{
		char game_id[11];
		char path[256];

		sceIoRead(fd, game_id, 10);
		sceIoClose(fd);
		game_id[10] = 0;
		build_path(path, "ms0:/", game_id, 0);
		sceIoMkdir(path, 0777);

		printf("Found game %s\n", game_id);

		write_file("disc0:/PSP_GAME/SYSDIR", path, "BOOT.BIN");
	}
}

/* Dump a filing system */
void dump_filesystem(const char *root, const char *write_loc)
{
	int dfd;
	char next_root[256];
	char next_write[256];

	sceIoMkdir(write_loc, 0777);

	dfd = sceIoDopen(root);
	if(dfd > 0)
	{
		SceIoDirent dir;

		while(sceIoDread(dfd, &dir) > 0)
		{
			if(dir.d_stat.st_attr & FIO_SO_IFDIR)
			{
				if(dir.d_name[0] != '.')
				{
					build_path(next_write, write_loc, dir.d_name, 0);
					build_path(next_root, root, dir.d_name, 1);
					dump_filesystem(next_root, next_write);
				}
			}
			else
			{
				write_file(root, write_loc, dir.d_name);
			}
		}
		sceIoDclose(dfd);
	}
}

/* Dump memory */
void dump_memory(void)
{
	int fd;

	printf("Dumping 28Megs from 0x8400000\n");
	fd = sceIoOpen("ms0:/MEMORY.BIN", PSP_O_CREAT | PSP_O_TRUNC | PSP_O_WRONLY, 0777);
	if(fd >= 0)
	{
		sceIoWrite(fd, (void *) 0x8400000, 28*1024*1024);
		sceIoClose(fd);
	}
}

/* Dumps flash rom in bits */
void dump_flashrom(int lower)
{
	int fdin;
	int fdout;

	fdin = sceIoOpen("lflash:", PSP_O_RDONLY, 0777);
	if(fdin > 0)
	{
		int i;
		int bytes_read;

		if(lower)
		{
			fdout = sceIoOpen("ms0:/flash_lower.bin", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
		}
		else
		{
			fdout = sceIoOpen("ms0:/flash_upper.bin", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
		}

		if(fdout > 0)
		{
			for(i = 0; i < ((16 * 1024 * 1024) / sizeof(write_buffer)); i++)
			{
				bytes_read = sceIoRead(fdin, write_buffer, sizeof(write_buffer));
				if(lower)
				{
					sceIoWrite(fdout, write_buffer, bytes_read);
				}
			}

			if(!lower)
			{
				for(i = 0; i < ((16 * 1024 * 1024) / sizeof(write_buffer)); i++)
				{
					bytes_read = sceIoRead(fdin, write_buffer, sizeof(write_buffer));
					sceIoWrite(fdout, write_buffer, bytes_read);
				}
			}

			sceIoClose(fdout);
		}

		sceIoClose(fdin);
	}
	else
	{
		printf("Cannot open lflash: device\n");
		sceKernelSleepThread();
	}
}

void show_menu(void)
{
	printf("PSP Dumping Tool - TyRaNiD 2k5. (github.com/pspdev)\n");
	printf("Press triangle to dump umd boot.bin\n");
	printf("Press circle to dump flash0\n");
	printf("Press square to dump flash1\n");
	printf("Press cross to dump memory\n");
	printf("Press L trigger to dump lower 16Mb of flash rom\n");
	printf("Press R trigger to dump lower 16Mb of flash rom\n");
}

int main(void)
{
	SceCtrlData pad_data;

	pspDebugScreenSetBackColor(0xFFFFFFFF);
	pspDebugScreenSetTextColor(0);
	pspDebugScreenInit();
	SetupCallbacks();
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(1);
	show_menu();

	for(;;)
	{
		sceCtrlReadBufferPositive(&pad_data, 1);
		if(pad_data.Buttons & PSP_CTRL_TRIANGLE)
		{
			DumpBootBin();
			pspDebugScreenClear();
			printf("!!!!!!!! DONE !!!!!!!!!!\n");
			show_menu();
		}

		if(pad_data.Buttons & PSP_CTRL_CIRCLE)
		{
			dump_filesystem("flash0:/", "ms0:/flash0");
			pspDebugScreenClear();
			printf("!!!!!!!! DONE !!!!!!!!!!\n");
			show_menu();
		}

		if(pad_data.Buttons & PSP_CTRL_SQUARE)
		{
			dump_filesystem("flash1:/", "ms0:/flash1");
			pspDebugScreenClear();
			printf("!!!!!!!! DONE !!!!!!!!!!\n");
			show_menu();
		}

		if(pad_data.Buttons & PSP_CTRL_CROSS)
		{
			dump_memory();
			pspDebugScreenClear();
			printf("!!!!!!!! DONE !!!!!!!!!!\n");
			show_menu();
		}

		if(pad_data.Buttons & PSP_CTRL_LTRIGGER)
		{
			dump_flashrom(1);
			pspDebugScreenClear();
			printf("!!!!!!!! DONE !!!!!!!!!!\n");
			show_menu();
		}

		if(pad_data.Buttons & PSP_CTRL_RTRIGGER)
		{
			dump_flashrom(0);
			pspDebugScreenClear();
			printf("!!!!!!!! DONE !!!!!!!!!!\n");
			show_menu();
		}

		sceDisplayWaitVblankStart();
	}

	return 0;
}
