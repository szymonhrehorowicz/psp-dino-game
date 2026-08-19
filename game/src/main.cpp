#include "controller_manager.h"
#include "player.h"
#include "pspmoduleinfo.h"
#include "pspthreadman.h"
#include "system/exit.h"
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspuser.h>

// Required PSP_MODULE_INFO
PSP_MODULE_INFO("Hello World", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);

int main(void)
{
    PS::System::exit_init();
    pspDebugScreenInit();

    // Controls
    PS::Game::Controller_Manager controller_manager{};

    // Actors
    PS::Game::Player player{};

    // Scene

    // Signals
    controller_manager.on_button_pressed(PspCtrlButtons::PSP_CTRL_CROSS).connect(&player, &PS::Game::Player::jump);

    while (1)
    {
        pspDebugScreenSetXY(0, 2);
        pspDebugScreenPrintf("Hello World!\n");

        // Update pad
        controller_manager.update();

        sceDisplayWaitVblankStart();
    }

    return 0;
}