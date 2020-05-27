/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic sample to erm do something.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("PRXDecryptor", 0x1000, 1, 0);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(0);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

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
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

/* ptr is a pointer to the file to decrypt, check is undocumented, look at decrypt_file to see how to use */
int sceKernelCheckExecFile(void *ptr, void *check);

char g_data[0x400000] __attribute__((aligned(64)));
char g_decrypt_buf[0x400000] __attribute__((aligned(64)));

/* Decrypt a single PRX file */
int extract_file(const char* name, const char* dstname)
{
	int fd;
	int ret = 0;

	fd = sceIoOpen(name, PSP_O_RDONLY, 0777);
	if(fd >= 0)
	{
		int bytes_read;
		bytes_read = sceIoRead(fd, g_data, 4*1024*1024);
		sceIoClose(fd);
		if(bytes_read > 0)
		{
			u8 check[0x100];
			u32 size;
			char *output;

			memset(check, 0, sizeof(check));
			sceKernelCheckExecFile(g_data, check);
			/* Get size of data block */
			size = *(unsigned int *) (check+0x5C);

			/* Check if we managed to decrypt the file */
			if(*(unsigned short *)(check+0x5a) & 1)
			{
				/* Set decrypt buffer pointer */
				*(unsigned int*)(check+0x24) = (unsigned int) g_decrypt_buf;
				sceKernelCheckExecFile(g_data, check);
				output = g_decrypt_buf;
			}
			else
			{
				output = g_data;
			}

			if(size >= 0)
			{
				printf("Extracted file - size %d\n", size);
				fd = sceIoOpen(dstname, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
				if(fd >= 0)
				{
					sceIoWrite(fd, output, size);
					sceIoClose(fd);
					ret = 1;
				}
			}
			else
			{
				printf("Extract failed %s\n", name);
			}
		}
		else
		{
			printf("Couldn't read file\n");
		}
	}
	else
	{
		printf("Couldn't open file\n");
	}

	return ret;
}

SceIoDirent g_dir;
char g_infile[256];
char g_outfile[256];

void decrypt_files(const char *basedir, const char *destdir)
{
	int fd;

	printf("%s\n", basedir);
	fd = sceIoDopen(basedir);
	if(fd >= 0)
	{
		while(sceIoDread(fd, &g_dir) > 0)
		{
			if((g_dir.d_stat.st_attr & FIO_SO_IFDIR) == 0)
			{
				strcpy(g_infile, basedir);
				strcat(g_infile, g_dir.d_name);
				strcpy(g_outfile, destdir);
				strcat(g_outfile, g_dir.d_name);
				printf("Decrypting %s to %s\n", g_infile, g_outfile);
				extract_file(g_infile, g_outfile);
			}
		}

		sceIoDclose(fd);
	}
}

int main(void)
{
	pspDebugScreenInit();
	SetupCallbacks();

	/* Decrypt kernel modules */
	sceIoMkdir("ms0:/kd", 0777);
	decrypt_files("flash0:/kd/", "ms0:/kd/");
	/* Decrypt VShell modules */
	sceIoMkdir("ms0:/vsh", 0777);
	decrypt_files("flash0:/vsh/module/", "ms0:/vsh/");

	printf("Done\n");
	sceKernelExitDeleteThread(0);

	return 0;
}
