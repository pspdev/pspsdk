#include <pspdebug.h>
#include <pspkernel.h>
#include <pspmodulemgr.h>
#include <kubridge.h>

/* Define the module info section */
PSP_MODULE_INFO("user", PSP_MODULE_USER, 1, 0);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int done = 0;

/* Exit callback */
int exitCallback(int arg1, int arg2, void *common) {
    done = 1;
    return 0;
}

/* Callback thread */
int callbackThread(SceSize args, void *argp) {
    int cbid = 0;
    cbid = sceKernelCreateCallback("exitCallback", exitCallback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

/* Sets up the callback thread and returns its thread id */
int setupCallbacks(void) {
    int thid = sceKernelCreateThread("callbackThread", callbackThread, 0x11, 0xFA0, 0, 0);

    if (thid >= 0) {
        sceKernelStartThread(thid, 0, 0);
    }
        
    return thid;
}

/* Load our kernel module */
static SceUID loadStartModule(const char *path) {
    int ret = 0, status = 0;
    SceUID modID = 0;

    ret = modID = kuKernelLoadModule(path, 0, NULL);
    if (ret < 0) {
        pspDebugScreenPrintf("kuKernelLoadModule(%s) failed: %08x\n", path, ret);
        return ret;
    }

    ret = sceKernelStartModule(modID, 0, NULL, &status, NULL);
    if (ret < 0) {
        pspDebugScreenPrintf("sceKernelStartModule(%s) failed: %08x\n", path, ret);
        return ret;
    }
    
    return ret;
}

/* Unload our kernel module */
static void stopUnloadModules(SceUID modID) {
    sceKernelStopModule(modID, 0, NULL, NULL, NULL);
    sceKernelUnloadModule(modID);
}

/* Kernel function prototype */
u32 pspSysregGetTachyonVersion(void);

int main(int argc, char *argv[]) {
    // Initialize callbacks
    pspDebugScreenInit();
    setupCallbacks();

    // Load and start kernel module
    SceUID module = loadStartModule("kernel.prx");
    u32 version = pspSysregGetTachyonVersion();

    // Print kernel function result on screen
    pspDebugScreenPrintf("Kernel User Bridge Sample:\n");
    pspDebugScreenPrintf("sceSysregGetTachyonVersion returned %08lx\n", version);

    // Unload and return
    stopUnloadModules(module);
    return 0;
}
