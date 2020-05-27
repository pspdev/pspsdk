/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Simple shell to look at the registry
 *
 * Copyright (c) 2006 James F
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspreg.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Define the module info section */
PSP_MODULE_INFO("regsh", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define ROOT_DIR "/root"

/* Cant seem to work out how to enumerate the roots */
const char *root_dirs[] = {
	"SYSPROFILE",
	"DATA",
	"SYSTEM",
	"CONFIG",
	"REGISTRY"
};

void print_key_root(void)
{
	int i;
	for(i = 0; i < (sizeof(root_dirs)/sizeof(char *)); i++)
	{
		printf("DIR - %-27s\n", root_dirs[i]);
	}
}

/* Print info about a specific key */
void print_key_info(REGHANDLE hd, const char *name)
{
	unsigned int type;
	SceSize size;
	unsigned char data[1024];
	REGHANDLE hk;

	if(!sceRegGetKeyInfo(hd, name, &hk, &type, &size))
	{
		if(type == REG_TYPE_DIR)
		{
			printf("DIR - %-27s\n", name);
		}
		else
		{
			if(!sceRegGetKeyValue(hd, hk, data, size))
			{
				switch(type)
				{
					case REG_TYPE_INT: printf("INT - %-27s - %4d : %d\n", name, size, *((int*) data));
									   break;
					case REG_TYPE_STR: printf("STR - %-27s - %4d : %s\n", name, size, (char *)data);
									   break;
					case REG_TYPE_BIN: {
										   int i;
										   printf("BIN - %-27s - %4d : ", name, size);
										   for(i = 0; i < size-1; i++)
										   {
											   printf("%02X-", data[i]);
										   }
										   printf("%02X\n", data[i]);
									   }
									   break;
				};
			}
		}
	}
	else
	{
		printf("Could not get info for key %s\n", name);
	}
}

/* Print out a directory key */
void print_key(const char *dir)
{
	struct RegParam reg;
	REGHANDLE h;

	if(strcmp(dir, ROOT_DIR) == 0)
	{
		print_key_root();
		return;
	}

	dir = strchr(&dir[1], '/');
	if(dir == NULL)
	{
		return;
	}

	memset(&reg, 0, sizeof(reg));
	reg.regtype = 1;
	reg.namelen = strlen("/system");
	reg.unk2 = 1;
	reg.unk3 = 1;
	strcpy(reg.name, "/system");
	if(sceRegOpenRegistry(&reg, 2, &h) == 0)
	{
		REGHANDLE hd;
		if(!sceRegOpenCategory(h, dir, 2, &hd))
		{
			int num;

			if(!sceRegGetKeysNum(hd, &num))
			{
				char *data;
				printf("Key Entries: %d\n", num);
				data = malloc(num*27);
				if(data)
				{
					if(!sceRegGetKeys(hd, data, num))
					{
						int i;
						for(i = 0; i < num; i++)
						{
							print_key_info(hd, &data[i*27]);
						}
						free(data);
					}
					else
					{
						printf("Could not get key values\n");
					}
				}
				else
				{
					printf("Could not allocate key data\n");
				}
			}
			else
			{
				printf("Could not get number of keys\n");
			}
			sceRegCloseCategory(hd);
		}
		else
		{
			printf("Could not open directory\n");
		}

		sceRegCloseRegistry(h);
	}
	else
	{
		printf("Could not open registry\n");
	}
}

int check_dir(const char *dir)
{
	struct RegParam reg;
	REGHANDLE h;
	int ret = 0;

	dir = strchr(&dir[1], '/');
	if(dir == NULL)
	{
		return 0;
	}

	memset(&reg, 0, sizeof(reg));
	reg.regtype = 1;
	reg.namelen = strlen("/system");
	reg.unk2 = 1;
	reg.unk3 = 1;
	strcpy(reg.name, "/system");
	if(sceRegOpenRegistry(&reg, 2, &h) == 0)
	{
		REGHANDLE hd;
		if(!sceRegOpenCategory(h, dir, 2, &hd))
		{
			sceRegCloseCategory(hd);
			ret = 1;
		}
		sceRegCloseRegistry(h);
	}
	else
	{
		printf("ERROR: Could not open registry\n");
	}

	return ret;
}

int exitCallback(int arg1, int arg2, void *common)
{
	sceKernelExitGame();
	return 0;
}

int callbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exitCallback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}

int setupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

void up_dir(char *currdir)
{
	char *lastsl;

	lastsl = strrchr(currdir, '/');

	if((lastsl) && (&lastsl[0] != currdir))
	{
		*lastsl = 0;
	}
}

void change_dir(char *currdir, const char *dir)
{
	char tempdir[1024];

	if(dir == NULL)
	{
		printf("ERROR: Must supply a directory argument\n");
		return;
	}

	if(strcmp(dir, "..") == 0)
	{
		up_dir(currdir);
		return;
	}

	(void) snprintf(tempdir, sizeof(tempdir), "%s/%s", currdir, dir);
	if(check_dir(tempdir))
	{
		strcpy(currdir, tempdir);
	}
	else
	{
		printf("ERROR: Invalid directory '%s'\n", tempdir);
	}
}

int main(int argc, char *argv[])
{
	char buf[1024];
	char currdir[1024];

	setupCallbacks();
	pspDebugScreenInit();
	pspDebugScreenPrintf("Registry Shell (c) 2k6 TyRaNiD\n");
	pspDebugScreenPrintf("You must access it through a stdin app such as psplink\n");

	strcpy(currdir, ROOT_DIR);

	printf("\n");
	printf("%s> ", currdir);
	while(fgets(buf, sizeof(buf), stdin))
	{
		char *cmd;
		char *arg;

		cmd = strtok(buf, " \t\n\r");
		arg = strtok(NULL, "\t\n\r");

		if(cmd)
		{
			if(strcasecmp(cmd, "ls") == 0)
			{
				print_key(currdir);
			}
			else if(strcasecmp(cmd, "cd") == 0)
			{
				change_dir(currdir, arg);
			}
			else if(strcasecmp(cmd, "exit") == 0)
			{
				break;
			}
			else
			{
				printf("ERROR: Unknown command '%s'\n", cmd);
			}
		}

		printf("%s> ", currdir);
	}

	sceKernelExitGame();

	return 0;
}
