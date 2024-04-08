#include <string>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspge.h>

PSP_MODULE_INFO("PSP HELLOCPP", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int main(int argc, char *argv[]) {
    pspDebugScreenInit();
    pspDebugScreenPrintf(std::to_string(123.45).c_str());

    while(true) {
        sceDisplayWaitVblankStart();
    }
}

