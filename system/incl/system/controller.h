/**
 * @file controller.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <pspctrl.h>

namespace PS::System
{

/**
 * @brief Abstraction of analog stick of the controller.
 *
 */
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
 * @brief Abstraction of user buttons.
 *
 */
class Controller
{
  public:
    Controller();

    /**
     * @brief Reads and stores the current state of controller buttons.
     *
     */
    void update();

    /**
     * @brief Checks is any button is pressed.
     *
     * @return true - any button is pressed.
     * @return false - otherwise.
     */
    bool is_any_button_pressed() const;

    /**
     * @brief Get state of a specific button.
     *
     * @param button - enumeration indicating specific button.
     * @return true - if button is pressed.
     * @return false - if button is released.
     */
    bool get_button(PspCtrlButtons button) const;

    /**
     * @brief Get position of analog stick.
     *
     * @return Analog_Stick
     */
    Analog_Stick get_stick() const;

  private:
    SceCtrlData m_data{};
};

} // namespace PS::System