/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Simple elf based network example.
 *
 * Copyright (c) 2005 James F <tyranid@gmail.com>
 * Some small parts (c) 2005 PSPPet
 *
 */
#include <arpa/inet.h>
#include <errno.h>
#include <pspkernel.h>
#include <pspnet_apctl.h>
#include <pspsdk.h>
#include <psputility.h>
#include <string.h>
#include <unistd.h>

#define printf pspDebugScreenPrintf

#define MODULE_NAME "NetSample"
#define HELLO_MSG "Hello there. Type away.\r\n"

PSP_MODULE_INFO(MODULE_NAME, 0, 1, 1);
PSP_HEAP_THRESHOLD_SIZE_KB(1024);
PSP_HEAP_SIZE_KB(-2048);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);
PSP_MAIN_THREAD_STACK_SIZE_KB(1024);

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

	thid =
			sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, PSP_THREAD_ATTR_USER, 0);
	if (thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

#define SERVER_PORT 23

int make_socket(uint16_t port)
{
	int sock;
	int ret;
	struct sockaddr_in name;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		return -1;
	}

	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(sock, (struct sockaddr *)&name, sizeof(name));
	if (ret < 0)
	{
		return -1;
	}

	return sock;
}

/* Start a simple tcp echo server */
void start_server(const char *szIpAddr)
{
	int ret;
	int sock;
	int new = -1;
	struct sockaddr_in client;
	long unsigned int size;
	int readbytes;
	char data[1024];
	fd_set set;
	fd_set setsave;

	/* Create a socket for listening */
	sock = make_socket(SERVER_PORT);
	if (sock < 0)
	{
		printf("Error creating server socket\n");
		return;
	}

	ret = listen(sock, 1);
	if (ret < 0)
	{
		printf("Error calling listen\n");
		return;
	}

	printf("Listening for connections ip %s port %d\n", szIpAddr, SERVER_PORT);

	FD_ZERO(&set);
	FD_SET(sock, &set);
	setsave = set;

	while (1)
	{
		int i;
		set = setsave;
		if (select(FD_SETSIZE, &set, NULL, NULL, NULL) < 0)
		{
			printf("select error\n");
			return;
		}

		for (i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &set))
			{
				int val = i;

				if (val == sock)
				{
					new = accept(sock, (struct sockaddr *)&client, &size);
					if (new < 0)
					{
						printf("Error in accept %s\n", strerror(errno));
						close(sock);
						return;
					}

					printf("New connection %d from %s:%d\n", val, inet_ntoa(client.sin_addr),
								 ntohs(client.sin_port));

					write(new, HELLO_MSG, strlen(HELLO_MSG));

					FD_SET(new, &setsave);
				}
				else
				{
					readbytes = read(val, data, sizeof(data));
					if (readbytes <= 0)
					{
						printf("Socket %d closed\n", val);
						FD_CLR(val, &setsave);
						close(val);
					}
					else
					{
						write(val, data, readbytes);
						printf("%.*s", readbytes, data);
					}
				}
			}
		}
	}

	close(sock);
}

/* Connect to an access point */
int connect_to_apctl(int config)
{
	int err;
	int stateLast = -1;

	/* Connect using the first profile */
	err = sceNetApctlConnect(config);
	if (err != 0)
	{
		printf(MODULE_NAME ": sceNetApctlConnect returns %08X\n", err);
		return 0;
	}

	printf(MODULE_NAME ": Connecting...\n");
	while (1)
	{
		int state;
		err = sceNetApctlGetState(&state);
		if (err != 0)
		{
			printf(MODULE_NAME ": sceNetApctlGetState returns $%x\n", err);
			break;
		}
		if (state > stateLast)
		{
			printf("  connection state %d of 4\n", state);
			stateLast = state;
		}
		if (state == 4)
			break; // connected with static IP

		// wait a little before polling again
		sceKernelDelayThread(50 * 1000); // 50ms
	}
	printf(MODULE_NAME ": Connected!\n");

	if (err != 0)
	{
		return 0;
	}

	return 1;
}

int net_thread(SceSize args, void *argp)
{
	int err;
	do
	{
		if ((err = pspSdkInetInit()))
		{
			printf(MODULE_NAME ": Error, could not initialise the network %08X\n", err);
			break;
		}

		if (connect_to_apctl(1))
		{
			// connected, get my IPADDR and run test
			union SceNetApctlInfo info;

			if (sceNetApctlGetInfo(8, &info) != 0)
				strcpy(info.ip, "unknown IP");

			start_server(info.ip);
		}
	} while (0);
}
/* Simple thread */
int main(int argc, char **argv)
{
	SceUID thid;

	SetupCallbacks();

	sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
	sceUtilityLoadNetModule(PSP_NET_MODULE_INET);

	pspDebugScreenInit();

	/* Create a user thread to do the real work */
	thid = sceKernelCreateThread("net_thread", net_thread,
															 0x11,			 // default priority
															 256 * 1024, // stack size (256KB is regular default)
															 PSP_THREAD_ATTR_USER, NULL);
	if (thid < 0)
	{
		printf("Error, could not create thread\n");
		sceKernelSleepThread();
	}

	sceKernelStartThread(thid, 0, NULL);

	sceKernelExitDeleteThread(0);

	return 0;
}
