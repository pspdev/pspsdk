/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * sio.c - Some basic SIO (remote port) functions.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id: sio.c 2152 2007-01-27 10:09:15Z tyranid $
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsyscon.h>

/* Define some important parameters, not really sure on names. Probably doesn't matter */
#define PSP_UART4_FIFO 0xBE500000
#define PSP_UART4_STAT 0xBE500018
#define PSP_UART4_DIV1 0xBE500024
#define PSP_UART4_DIV2 0xBE500028
#define PSP_UART4_CTRL 0xBE50002C
#define PSP_UART_CLK   96000000
#define PSP_UART_TXFULL  0x20
#define PSP_UART_RXEMPTY 0x10

static int g_enablekprintf = 0;

/* Some function prototypes we will need */
int sceHprmEnd(void);
int sceSysregUartIoEnable(int uart);
extern u32 sceKernelRemoveByDebugSection;

void pspDebugSioPutchar(int ch)
{
	while(_lw(PSP_UART4_STAT) & PSP_UART_TXFULL);
	_sw(ch, PSP_UART4_FIFO);
}

int pspDebugSioGetchar(void)
{
	if(_lw(PSP_UART4_STAT) & PSP_UART_RXEMPTY)
	{
		return -1;
	}

	return _lw(PSP_UART4_FIFO);
}

void pspDebugSioPuts(const char *str)
{
	while(*str)
	{
		pspDebugSioPutchar(*str);
		str++;
	}

	pspDebugSioPutchar('\r');
	pspDebugSioPutchar('\n');
}

int pspDebugSioPutData(const char *data, int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		pspDebugSioPutchar(data[i]);
	}

	return len;
}

/* Put data to SIO converting any line feeds as necessary */
int pspDebugSioPutText(const char *data, int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		/* If just line feed add a carriage return */
		if(data[i] == '\n')
		{
			if(((i > 0) && (data[i-1] != '\r')) || (i == 0))
			{
				pspDebugSioPutchar('\r');
			}
		}

		pspDebugSioPutchar(data[i]);

		if((i < (len - 1)) && (data[i] == '\r') && (data[i+1] != '\n'))
		{
			pspDebugSioPutchar('\n');
		}
	}

	return len;
}

void pspDebugSioSetBaud(int baud)
{
	int div1, div2;

	/* rate set using the rough formula div1 = (PSP_UART_CLK / baud) >> 6 and
	 * div2 = (PSP_UART_CLK / baud) & 0x3F
	 * The uart4 driver actually uses a slightly different formula for div 2 (it
	 * adds 32 before doing the AND, but it doesn't seem to make a difference
	 */
	div1 = PSP_UART_CLK / baud;
	div2 = div1 & 0x3F;
	div1 >>= 6;

	_sw(div1, PSP_UART4_DIV1);
	_sw(div2, PSP_UART4_DIV2);
	_sw(0x60, PSP_UART4_CTRL);
}

void pspDebugSioInit(void)
{
	/* Shut down the remote driver */
	sceHprmEnd();
	/* Enable UART 4 */
	sceSysregUartIoEnable(4);
	/* Enable remote control power */
	sceSysconCtrlHRPower(1);
	/* Delay thread for a but */
	sceKernelDelayThread(2000000);
}

static u32 *get_debug_register(void)
{
	u32 *pData;
	u32 ptr;

	pData = (u32 *) (0x80000000 | ((sceKernelRemoveByDebugSection & 0x03FFFFFF) << 2));
	ptr = ((pData[0] & 0xFFFF) << 16) + (short) (pData[2] & 0xFFFF);

	return (u32 *) ptr;
}

void pspDebugEnablePutchar(void)
{
	u32 *pData;

	pData = get_debug_register();
	*pData |= 0x1000;
}

static void PutCharDebug(unsigned short *data, unsigned int type)
{
	if(((type & 0xFF00) == 0) && (g_enablekprintf))
	{
		if(type == '\n')
		{
			pspDebugSioPutchar('\r');
		}

		pspDebugSioPutchar(type);
	}
}

void pspDebugSioInstallKprintf(void)
{
	pspDebugEnablePutchar();
	sceKernelRegisterDebugPutchar(PutCharDebug);
	g_enablekprintf = 1;
}

void pspDebugSioEnableKprintf(void)
{
	g_enablekprintf = 1;
}

void pspDebugSioDisableKprintf(void)
{
	g_enablekprintf = 0;
}
