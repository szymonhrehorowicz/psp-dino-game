#include "exit.h"
#include "pspmoduleinfo.h"
#include "pspthreadman.h"
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspuser.h>

// Required PSP_MODULE_INFO
PSP_MODULE_INFO("Hello World", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

int main(void)
{
    PS::System::exit_init();

    pspDebugScreenInit();
    while (1)
    {
        pspDebugScreenSetXY(0, 0);
        pspDebugScreenPrintf("Hello World!");
        // Wait for vertical blank start
        sceDisplayWaitVblankStart();
    }

    return 0;
}