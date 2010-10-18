/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * gdb-userlib.c - GDB support functions for user mode.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id: gdb-userlib.c 2166 2007-02-04 10:52:49Z tyranid $
 */
#include <pspkernel.h>
#include <pspdebug.h>

#include <string.h>

static int sio_fd = -1;

/* GDB Debug putchar */
void putDebugChar(char ch)
{
	sceIoWrite(sio_fd, &ch, 1);
}

/* GDB Debug getchar */
char getDebugChar(void)
{
	char ch = 0;
	int count = 0;

	while(count <= 0)
	{
		count = sceIoRead(sio_fd, &ch, 1);
	}

	return ch;
}

int g_initialised = 0;

static int io_init(PspIoDrvArg *arg)
{
	return 0;
}

static int io_exit(PspIoDrvArg *arg)
{
	return 0;
}

static int io_read(PspIoDrvFileArg *arg, char *data, int len)
{
	int ret = 0;
	int ch;

	while(ret < len)
	{
		ch = pspDebugSioGetchar();
		if(ch != -1)
		{
			data[ret++] = ch & 0xFF;
		}
		else
		{
			break;
		}
	}

	return ret;
}

static int io_write(PspIoDrvFileArg *arg, const char *data, int len)
{
	int ret = 0;

	while(ret < len)
	{
		pspDebugSioPutchar(data[ret++]);
	}

	return ret;
}

void sceKernelDcacheWBinvAll(void);
void sceKernelIcacheClearAll(void);

static int io_devctl(PspIoDrvFileArg *arg, const char *devname, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen)
{
	pspKernelSetKernelPC();
	sceKernelDcacheWBinvAll();
	sceKernelIcacheClearAll();

	return 0;
}

static PspIoDrvFuncs sio_funcs = 
{
	io_init,
	io_exit,
	NULL,
	NULL,
	io_read,
	io_write,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	io_devctl,
	NULL,
};

static PspIoDrv sio_driver = 
{
	"sio", 0x10, 0x800, "SIO", &sio_funcs
};

int _gdbSupportLibReadByte(unsigned char *address, unsigned char *dest)
{
	u32 addr;

	addr = (u32) address;
	if((addr >= 0x08400000) && (addr < 0x0a000000))
	{
		*dest = *address;
		return 1;
	}

	/*
	else if((addr >= 0x88000000) && (addr < 0x8a000000))
	{
		*dest = *address;
		return 1;
	}
	*/

	return 0;
}

int _gdbSupportLibWriteByte(char val, unsigned char *dest)
{
	u32 addr;

	addr = (u32) dest;
	if((addr >= 0x08400000) && (addr < 0x0a000000))
	{
		*dest = val;
		return 1;
	}

	/*
	else if((addr >= 0x88000000) && (addr < 0x8a000000))
	{
		*dest = val;
		return 1;
	}
	*/

	return 0;
}

void _gdbSupportLibFlushCaches(void)
{
	sceIoDevctl("sio:", 0, NULL, 0, NULL, 0);
}

int _gdbSupportLibInit(void)
{
	int ret;

	if(!g_initialised)
	{
		(void) sceIoDelDrv("sio"); /* Ignore error */
		ret = sceIoAddDrv(&sio_driver);
		if(ret < 0)
		{
			return ret;
		}

		sio_fd = sceIoOpen("sio:", PSP_O_RDWR, 0);

		g_initialised = 1;
	}

	return 0;
}
