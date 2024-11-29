/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * 
 * Sample program to demonstrate a minimalistic Hello World program.
 * The main scope here is to show how we can disable newlib features if we don't need them.
 */

#include <stdio.h>

// Specific psp headers
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspkernel.h>
#include <pspmoduleinfo.h>
#include <sys/socket.h>
#include <errno.h>

// We won't fully disable newlib as we are using printf
// However we can disable timezone, pthreads, pipe and socket support
PSP_DISABLE_NEWLIB_PIPE_SUPPORT()
PSP_DISABLE_NEWLIB_SOCKET_SUPPORT()
PSP_DISABLE_NEWLIB_TIMEZONE_SUPPORT()
PSP_DISABLE_NEWLIB_CWD_SUPPORT()
PSP_DISABLE_AUTOSTART_PTHREAD()
 
// configure PSP stuff
#define VERS    1
#define REVS    0
 
PSP_MODULE_INFO("Light Hello World", PSP_MODULE_USER, VERS, REVS);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

int main(int argc, char** argv)
{
    while(1) {
        printf("Hello World!\n");
    }
    
    return 0;
}