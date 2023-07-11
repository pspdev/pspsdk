
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <psputility.h>
#include <psputility_netmodules.h>
#include <psputility_htmlviewer.h>
#include <pspnet.h>
#include <pspnet_inet.h>
#include <pspnet_apctl.h>
#include <pspnet_resolver.h>
#include <psphttp.h>
#include <pspssl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/unistd.h>

#include "graphics.h"

PSP_MODULE_INFO("HtmlViewer", PSP_MODULE_USER, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);
PSP_HEAP_THRESHOLD_SIZE_KB(0x8000);

#define BROWSER_MEMORY (10*1024*1024) 

SceUID vpl;
pspUtilityHtmlViewerParam params;

void throwError(char *fmt, ...)
{
	va_list list;
	char msg[256];	

	va_start(list, fmt);
	vsprintf(msg, fmt, list);
	va_end(list);

	pspDebugScreenInit();
	pspDebugScreenClear();
	pspDebugScreenPrintf(msg);
	
	sceKernelSleepThread();
}


void loadNetModule(int module) 
{
	int result = sceUtilityLoadNetModule(module);
	if (result < 0) {
		throwError("sceUtilityLoadNetModule error 0x%08x", result);
	}
}

void loadNetModules()
{
	loadNetModule(PSP_NET_MODULE_COMMON);
	loadNetModule(PSP_NET_MODULE_INET);
	loadNetModule(PSP_NET_MODULE_PARSEURI);
	loadNetModule(PSP_NET_MODULE_PARSEHTTP);
	loadNetModule(PSP_NET_MODULE_HTTP);
	loadNetModule(PSP_NET_MODULE_SSL);
}

void unloadNetModules()
{
	sceUtilityUnloadNetModule(PSP_NET_MODULE_SSL);
	sceUtilityUnloadNetModule(PSP_NET_MODULE_HTTP);
	sceUtilityUnloadNetModule(PSP_NET_MODULE_PARSEHTTP);
	sceUtilityUnloadNetModule(PSP_NET_MODULE_PARSEURI);
	sceUtilityUnloadNetModule(PSP_NET_MODULE_INET);
	sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON);
}

void netTerm()
{
	sceHttpSaveSystemCookie();
	sceHttpsEnd();
	sceHttpEnd();
	sceSslEnd();
	sceNetApctlTerm();
	sceNetInetTerm();
	sceNetTerm();
	
	unloadNetModules();	
}

void netInit()
{
	int res;

	loadNetModules();

	res = sceNetInit(0x20000, 0x2A, 0, 0x2A, 0);
	if (res < 0) 
	{
		throwError("Error 0x%08X in sceNetInit\n", res);		
	}

	res = sceNetInetInit();
	if (res < 0) 
	{
		netTerm();
		throwError("Error 0x%08X in sceNetInetInit\n", res);				
	}

	res = sceNetResolverInit();
	if (res < 0) 
	{
		netTerm();
		throwError("Error 0x%08X in sceNetResolverInit\n", res);		
	}

	res = sceNetApctlInit(0x1800, 0x30);
	if (res < 0) 
	{
		netTerm();
		throwError("Error 0x%08X in sceNetApctlInit\n", res);		
	}

	res = sceSslInit(0x28000);
	if (res < 0) 
	{
		netTerm();
		throwError("Error 0x%08X in sceSslInit\n", res);
	}

	res = sceHttpInit(0x25800);
	if (res < 0) 
	{
		netTerm();
		throwError("Error 0x%08X in sceHttpInit\n", res);
	}

	res = sceHttpsInit(0, 0, 0, 0);
	if (res < 0) 
	{
		netTerm();
		throwError("Error 0x%08X in sceHttpsInit\n", res);
	}

	res = sceHttpsLoadDefaultCert(0, 0);
	if (res < 0) 
	{
		netTerm();
		throwError("Error 0x%08X in sceHttpsLoadDefaultCert\n", res);
	}

	res = sceHttpLoadSystemCookie();
	if (res < 0) 
	{
		netTerm();
		throwError("Error 0x%08X in sceHttpLoadSystemCookie\n", res);
	}	
}

void htmlViewerInit(char *url)
{
	int res;
	
	vpl = sceKernelCreateVpl("BrowserVpl", PSP_MEMORY_PARTITION_USER, 0, BROWSER_MEMORY + 256, NULL);
	
	if (vpl < 0) 
		throwError("Error 0x%08X creating vpl.\n", vpl);

	memset(&params, 0, sizeof(pspUtilityHtmlViewerParam));
	
	params.base.size = sizeof(pspUtilityHtmlViewerParam);
	
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.base.language);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.base.buttonSwap);
	
	params.base.graphicsThread = 17;
	params.base.accessThread = 19;
	params.base.fontThread = 18;
	params.base.soundThread = 16;	
	params.memsize = BROWSER_MEMORY;
	params.initialurl = url;
	params.numtabs = 1;
	params.cookiemode = PSP_UTILITY_HTMLVIEWER_COOKIEMODE_DEFAULT;
	params.homeurl = url;
	params.textsize = PSP_UTILITY_HTMLVIEWER_TEXTSIZE_NORMAL;
	params.displaymode = PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_SMART_FIT;
	params.options = PSP_UTILITY_HTMLVIEWER_DISABLE_STARTUP_LIMITS;
	params.interfacemode = PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_FULL;
	params.connectmode = PSP_UTILITY_HTMLVIEWER_CONNECTMODE_LAST;
	
	// Note the lack of 'ms0:' on the paths	
	params.dldirname = "/PSP/PHOTO";
	
	res = sceKernelAllocateVpl(vpl, params.memsize, &params.memaddr, NULL);
	
	if (res < 0) 
		throwError("Error 0x%08X allocating browser memory.\n", res);

	res = sceUtilityHtmlViewerInitStart(&params);
	
	if (res < 0)
		throwError("Error 0x%08X initing browser.\n", res);
}

int updateHtmlViewer()
{
	draw();

	switch (sceUtilityHtmlViewerGetStatus())
	{	
		case PSP_UTILITY_DIALOG_VISIBLE:			
			sceUtilityHtmlViewerUpdate(1);
		break;
	
		case PSP_UTILITY_DIALOG_QUIT:		
			sceUtilityHtmlViewerShutdownStart();		
		break;
	
		case PSP_UTILITY_DIALOG_NONE:
			return 0;
		break;
		
		default:
			break;
	}

	return 1;
}

int main(int argc, char *argv[])
{
	char url[128] = "file:/";
	char cwd[128] = {0};
	getcwd(cwd, 128);
	char *path = "/index.html";
	strcat(url, strstr(cwd, "/") + 1); // strip ms0:/
	strcat(url, path);

	setupGu();
	netInit();
	htmlViewerInit(url);	

	while(updateHtmlViewer())
	{
		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}

	netTerm();
	sceKernelFreeVpl(vpl, params.memaddr);
	sceKernelDeleteVpl(vpl);
	sceKernelExitGame();

	return 0;
}
