#include "pspmoduleinfo.h"
#include "pspthreadman.h"
#include "system/controller.h"
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
    PS::System::Controller controller{};

    while (1)
    {
        pspDebugScreenSetXY(0, 2);
        pspDebugScreenPrintf("Hello World!");

        // Update pad
        controller.update();

        auto const analog_stick = controller.get_stick();
        pspDebugScreenPrintf("Analog X = %3d\n", analog_stick.x);
        pspDebugScreenPrintf("Analog Y = %3d\n", analog_stick.y);

        // Is any button pressed
        if (controller.is_any_button_pressed())
        {
            if (controller.get_button(PSP_CTRL_SQUARE))
            {
                pspDebugScreenPrintf("Square\n");
            }
            if (controller.get_button(PSP_CTRL_TRIANGLE))
            {
                pspDebugScreenPrintf("Triangle\n");
            }
            if (controller.get_button(PSP_CTRL_CIRCLE))
            {
                pspDebugScreenPrintf("Circle\n");
            }
            if (controller.get_button(PSP_CTRL_CROSS))
            {
                pspDebugScreenPrintf("Cross\n");
            }

            if (controller.get_button(PSP_CTRL_UP))
            {
                pspDebugScreenPrintf("Up direction pad pressed! \n");
            }
            if (controller.get_button(PSP_CTRL_DOWN))
            {
                pspDebugScreenPrintf("Down direction pad pressed! \n");
            }
            if (controller.get_button(PSP_CTRL_LEFT))
            {
                pspDebugScreenPrintf("Left direction pad pressed! \n");
            }
            if (controller.get_button(PSP_CTRL_RIGHT))
            {
                pspDebugScreenPrintf("Right direction pad pressed! \n");
            }
        }

        sceDisplayWaitVblankStart();
    }

    return 0;
}