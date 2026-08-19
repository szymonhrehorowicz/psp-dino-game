#include "system/exit.h"

#include "psploadexec.h"
#include "pspthreadman.h"

namespace PS::System
{

int running = 0;

int exit_callback(int arg1, int arg2, void *common)
{
    running = 0;

    return 0;
}

int exit_callback_thread(SceSize args, void *argp)
{
    int const callback_id = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);

    sceKernelRegisterExitCallback(callback_id);
    sceKernelSleepThreadCB();

    return 0;
}

int exit_init(void)
{
    int const thread_id = sceKernelCreateThread("update_thread", exit_callback_thread, 0x11, 0xFA0, 0, 0);

    if (thread_id >= 0)
    {
        sceKernelStartThread(thread_id, 0, 0);
    }

    running = 1;

    return thread_id;
}

} // namespace PS::System