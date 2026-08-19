#include "system/controller.h"
#include "pspctrl.h"

namespace PS::System
{

Controller::Controller()
{
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
}

void Controller::update()
{
    sceCtrlReadBufferPositive(&m_data, 1);
}

bool Controller::is_any_button_pressed() const
{
    return m_data.Buttons != 0;
}

bool Controller::get_button(PspCtrlButtons button) const
{
    return m_data.Buttons & button;
}

Analog_Stick Controller::get_stick() const
{
    return {.x = m_data.Lx, .y = m_data.Ly};
}

} // namespace PS::System