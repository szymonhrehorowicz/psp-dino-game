#pragma once

#include <pspctrl.h>

namespace PS::System
{

struct Analog_Stick
{
    unsigned char x{};
    unsigned char y{};

    bool operator==(const Analog_Stick &other) const
    {
        return (x == other.x) && (y == other.y);
    }

    bool operator!=(const Analog_Stick &other) const
    {
        return (x != other.x) || (y != other.y);
    }
};

/**
 * @brief Abstraction of user buttons
 *
 */
class Controller
{
  public:
    Controller();

    void update();

    bool is_any_button_pressed() const;

    bool get_button(PspCtrlButtons button) const;

    Analog_Stick get_stick() const;

  private:
    SceCtrlData m_data{};
};

} // namespace PS::System