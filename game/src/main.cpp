#include "controller_manager.h"
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

    controller_manager.on_button_change(PspCtrlButtons::PSP_CTRL_CROSS).connect([](bool state) {
        if (state)
        {
            pspDebugScreenPrintf("Cross button was pressed!\n");
        }
        else
        {
            pspDebugScreenPrintf("Cross button was released!\n");
        }
    });

    controller_manager.on_analog_change().connect(
        [](PS::System::Analog_Stick stick) { pspDebugScreenPrintf("X Y changed to: {%3d, %3d}\n", stick.x, stick.y); });

    controller_manager.on_analog_x_change().connect(
        [](PS::System::Analog_Stick stick) { pspDebugScreenPrintf("X changed to: %3d\n", stick.x); });

    controller_manager.on_analog_y_change().connect(
        [](PS::System::Analog_Stick stick) { pspDebugScreenPrintf("Y changed to: %3d\n", stick.y); });

    while (1)
    {
        pspDebugScreenSetXY(0, 2);
        pspDebugScreenPrintf("Hello World!\n");

        // Update pad
        controller_manager.update();

        // auto const analog_stick = controller.get_stick();
        // pspDebugScreenPrintf("Analog X = %3d\n", analog_stick.x);
        // pspDebugScreenPrintf("Analog Y = %3d\n", analog_stick.y);

        // Is any button pressed
        // if (controller.is_any_button_pressed())
        // {
        //     if (controller.get_button(PSP_CTRL_SQUARE))
        //     {
        //         pspDebugScreenPrintf("Square\n");
        //     }
        //     if (controller.get_button(PSP_CTRL_TRIANGLE))
        //     {
        //         pspDebugScreenPrintf("Triangle\n");
        //     }
        //     if (controller.get_button(PSP_CTRL_CIRCLE))
        //     {
        //         pspDebugScreenPrintf("Circle\n");
        //     }
        //     if (controller.get_button(PSP_CTRL_CROSS))
        //     {
        //         pspDebugScreenPrintf("Cross\n");
        //     }

        //     if (controller.get_button(PSP_CTRL_UP))
        //     {
        //         pspDebugScreenPrintf("Up direction pad pressed! \n");
        //     }
        //     if (controller.get_button(PSP_CTRL_DOWN))
        //     {
        //         pspDebugScreenPrintf("Down direction pad pressed! \n");
        //     }
        //     if (controller.get_button(PSP_CTRL_LEFT))
        //     {
        //         pspDebugScreenPrintf("Left direction pad pressed! \n");
        //     }
        //     if (controller.get_button(PSP_CTRL_RIGHT))
        //     {
        //         pspDebugScreenPrintf("Right direction pad pressed! \n");
        //     }
        // }

        sceDisplayWaitVblankStart();
    }

    return 0;
}