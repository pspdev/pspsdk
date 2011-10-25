#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>

/* Define printf, just to make typing easier */
#define printf  pspDebugScreenPrintf

/* Define the module info section */
PSP_MODULE_INFO("cppException", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#include <exception>
using namespace std;

class myexception: public exception
{
	virtual const char* what() const throw()
	{
		return "My exception happened";
	}
} myex;

int main (void)
{
	pspDebugScreenInit();
	SceCtrlData pad;

	try
	{
		throw myex;
	}
	catch (exception& e)
	{
		printf("%s\n", e.what());
	}

	printf("\nPress X to quit.\n");

	for (;;)
	{
		sceCtrlReadBufferPositive(&pad, 1);
		if (pad.Buttons & PSP_CTRL_CROSS)
			break;
	}
	sceKernelExitGame();

	return 0;
}

