/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psputility_htmlviewer.h - html viewer utility library.
 *
 * Copyright (c) 2008 David Perry (InsertWittyName)
 * Copyright (c) 2008 moonlight
 *
 */

#ifndef __PSPUTILITY_HTMLVIEWER_H__
#define __PSPUTILITY_HTMLVIEWER_H__

#ifdef __cplusplus
extern "C" {
#endif

enum pspUtilityHtmlViewerDisconnectModes
{
	/** Enable automatic disconnect */
	PSP_UTILITY_HTMLVIEWER_DISCONNECTMODE_ENABLE = 0,
	/** Disable automatic disconnect */
	PSP_UTILITY_HTMLVIEWER_DISCONNECTMODE_DISABLE,
	/** Confirm disconnection */	
	PSP_UTILITY_HTMLVIEWER_DISCONNECTMODE_CONFIRM
};

enum pspUtilityHtmlViewerInterfaceModes
{
	/** Full user interface */
	PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_FULL = 0,
	/** Limited user interface */
	PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_LIMITED,
	/** No user interface */
	PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_NONE
};

enum pspUtilityHtmlViewerCookieModes
{
	/** Disable accepting cookies */
	PSP_UTILITY_HTMLVIEWER_COOKIEMODE_DISABLED = 0,
	/** Enable accepting cookies */
	PSP_UTILITY_HTMLVIEWER_COOKIEMODE_ENABLED,
	/** Confirm accepting a cookie every time */
	PSP_UTILITY_HTMLVIEWER_COOKIEMODE_CONFIRM,
	/** Use the system default for accepting cookies */
	PSP_UTILITY_HTMLVIEWER_COOKIEMODE_DEFAULT
};

enum pspUtilityHtmlViewerTextSizes
{
	/** Large text size */
	PSP_UTILITY_HTMLVIEWER_TEXTSIZE_LARGE = 0,
	/** Normal text size */
	PSP_UTILITY_HTMLVIEWER_TEXTSIZE_NORMAL,
	/** Small text size */
	PSP_UTILITY_HTMLVIEWER_TEXTSIZE_SMALL
};

enum pspUtilityHtmlViewerDisplayModes
{
	/** Normal display */
	PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_NORMAL = 0,
	/** Fit display */
	PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_FIT,
	/** Smart fit display */
	PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_SMART_FIT
};

enum pspUtilityHtmlViewerConnectModes
{
	/** Auto connect to last used connection */
	PSP_UTILITY_HTMLVIEWER_CONNECTMODE_LAST = 0,
	/** Manually select the connection (once) */
	PSP_UTILITY_HTMLVIEWER_CONNECTMODE_MANUAL_ONCE,
	/** Manually select the connection (every time) */
	PSP_UTILITY_HTMLVIEWER_CONNECTMODE_MANUAL_ALL
};

enum pspUtilityHtmlViewerOptions
{
	/** Open SCE net start page */
	PSP_UTILITY_HTMLVIEWER_OPEN_SCE_START_PAGE					= 0x000001,
	/** Disable startup limitations */
	PSP_UTILITY_HTMLVIEWER_DISABLE_STARTUP_LIMITS				= 0x000002,
	/** Disable exit confirmation dialog */
	PSP_UTILITY_HTMLVIEWER_DISABLE_EXIT_DIALOG					= 0x000004,
	/** Disable cursor */
	PSP_UTILITY_HTMLVIEWER_DISABLE_CURSOR						= 0x000008,
	/** Disable download completion confirmation dialog */
	PSP_UTILITY_HTMLVIEWER_DISABLE_DOWNLOAD_COMPLETE_DIALOG		= 0x000010,
	/** Disable download confirmation dialog */
	PSP_UTILITY_HTMLVIEWER_DISABLE_DOWNLOAD_START_DIALOG		= 0x000020,
	/** Disable save destination confirmation dialog */
	PSP_UTILITY_HTMLVIEWER_DISABLE_DOWNLOAD_DESTINATION_DIALOG	= 0x000040,
	/** Disable modification of the download destination */
	PSP_UTILITY_HTMLVIEWER_LOCK_DOWNLOAD_DESTINATION_DIALOG		= 0x000080,
	/** Disable tab display */
	PSP_UTILITY_HTMLVIEWER_DISABLE_TAB_DISPLAY					= 0x000100,
	/** Hold analog controller when HOLD button is down */
	PSP_UTILITY_HTMLVIEWER_ENABLE_ANALOG_HOLD					= 0x000200,
	/** Enable Flash Player */
	PSP_UTILITY_HTMLVIEWER_ENABLE_FLASH							= 0x000400,
	/** Disable L/R triggers for back/forward */
	PSP_UTILITY_HTMLVIEWER_DISABLE_LRTRIGGER					= 0x000800	
};

typedef struct pspUtilityHtmlViewerParam
{
	pspUtilityDialogCommon base;
	/** Pointer to the memory pool to be used */
	void* memaddr;
	/** Size of the memory pool */
	unsigned int memsize;
	/** Unknown. Pass 0 */
	int	unknown1;
	/** Unknown. Pass 0 */
	int	unknown2;
	/** URL to be opened initially */
	char* initialurl;
	/** Number of tabs (maximum of 3) */
	unsigned int numtabs;
	/** One of ::pspUtilityHtmlViewerInterfaceModes */
	unsigned int interfacemode;
	/** Values from ::pspUtilityHtmlViewerOptions. Bitwise OR together */
	unsigned int options;
	/** Directory to be used for downloading */
	char* dldirname;
	/** Filename to be used for downloading */
	char* dlfilename;
	/** Directory to be used for uploading */
	char* uldirname;
	/** Filename to be used for uploading */
	char* ulfilename;
	/** One of ::pspUtilityHtmlViewerCookieModes */
	unsigned int cookiemode;
	/** Unknown. Pass 0 */
	unsigned int unknown3;
	/** URL to set the home page to */
	char* homeurl;
	/** One of ::pspUtilityHtmlViewerTextSizes */
	unsigned int textsize;
	/** One of ::pspUtilityHtmlViewerDisplayModes */
	unsigned int displaymode;
	/** One of ::pspUtilityHtmlViewerConnectModes */
	unsigned int connectmode;
	/** One of ::pspUtilityHtmlViewerDisconnectModes */
	unsigned int disconnectmode;
	/** The maximum amount of memory the browser used */
	unsigned int memused;
	/** Unknown. Pass 0 */
	int unknown4[10];
	
} pspUtilityHtmlViewerParam;

/**
 * Init the html viewer
 *
 * @param params - html viewer parameters
 *
 * @return 0 on success, < 0 on error.
 */
int sceUtilityHtmlViewerInitStart(pspUtilityHtmlViewerParam *params);

/**
 * Shutdown html viewer. 
 */
int sceUtilityHtmlViewerShutdownStart(void);

/**
 * Refresh the GUI for html viewer
 *
 * @param n - unknown, pass 1
 */
int sceUtilityHtmlViewerUpdate(int n);

/**
 * Get the current status of the html viewer.
 *
 * @return 2 if the GUI is visible (you need to call sceUtilityHtmlViewerGetStatus).
 * 3 if the user cancelled the dialog, and you need to call sceUtilityHtmlViewerShutdownStart.
 * 4 if the dialog has been successfully shut down.
 */
int sceUtilityHtmlViewerGetStatus(void);

#ifdef __cplusplus
}
#endif

#endif
