/**
 * @file controller_manager.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "library/edge_detector.h"
#include "library/signal.h"
#include "pspctrl.h"
#include "system/controller.h"
#include <cassert>
#include <map>

namespace PS::Game
{

/**
 * @brief Provides access to signals indicating changes in state of controller: buttons and analog stick
 *
 */
class Controller_Manager
{
  public:
    /**
     * @brief Evaluate and raise specific signals of controller - if their conditions are met.
     *
     */
    void update()
    {
        m_controller.update();

        for (auto &button : m_buttons)
        {
            bool const state = m_controller.get_button(button.first);
            bool const has_changed = button.second.detector.update(state);

            if (has_changed)
            {
                if (button.second.detector.is_rising())
                {
                    button.second.pressed_signal.emit();
                }
                else
                {
                    button.second.released_signal.emit();
                }

                button.second.signal.emit(state);
            }
        }

        auto const stick = m_controller.get_stick();

        if (stick != m_analog_stick.stick)
        {
            if (stick.x != m_analog_stick.stick.x)
            {
                m_analog_stick.x_signal.emit(stick);
            }

            if (stick.y != m_analog_stick.stick.y)
            {
                m_analog_stick.y_signal.emit(stick);
            }

            m_analog_stick.signal.emit(stick);
        }

        m_analog_stick.stick = stick;
    }

    /**
     * @brief Get access to signal raised whenever specific button state changes.
     *
     * @param button_id - identifier of a specific button.
     * @return Library::Signal<bool>&
     */
    Library::Signal<bool> &on_button_change(PspCtrlButtons button_id)
    {
        auto const &button = m_buttons.find(button_id);
        if (button != m_buttons.end())
        {
            return button->second.signal;
        }

        assert(false && "Button ID not found");
    }

    /**
     * @brief Get access to signal raised whenever specific button is pressed.
     *
     * @param button_id - identifier of a specific button.
     * @return Library::Signal<>&
     */
    Library::Signal<> &on_button_pressed(PspCtrlButtons button_id)
    {
        auto const &button = m_buttons.find(button_id);
        if (button != m_buttons.end())
        {
            return button->second.pressed_signal;
        }

        assert(false && "Button ID not found");
    }

    /**
     * @brief Get access to signal raised whenever specific button is released.
     *
     * @param button_id - identifier of a specific button.
     * @return Library::Signal<>&
     */
    Library::Signal<> &on_button_released(PspCtrlButtons button_id)
    {
        auto const &button = m_buttons.find(button_id);
        if (button != m_buttons.end())
        {
            return button->second.released_signal;
        }

        assert(false && "Button ID not found");
    }

    /**
     * @brief Get access to signal raised whenever analog stick position changes.
     *
     * @return Library::Signal<System::Analog_Stick>&
     */
    Library::Signal<System::Analog_Stick> &on_analog_change()
    {
        return m_analog_stick.signal;
    }

    /**
     * @brief Get access to signal raised whenever X-position of analog stick changes.
     *
     * @return Library::Signal<System::Analog_Stick>&
     */
    Library::Signal<System::Analog_Stick> &on_analog_x_change()
    {
        return m_analog_stick.x_signal;
    }

    /**
     * @brief Get access to signal raised whenever Y-position of analog stick changes.
     *
     * @return Library::Signal<System::Analog_Stick>&
     */
    Library::Signal<System::Analog_Stick> &on_analog_y_change()
    {
        return m_analog_stick.y_signal;
    }

  private:
    System::Controller m_controller{};

    struct Tracked_Button
    {
        Library::Edge_Detector detector{};
        Library::Signal<bool> signal{};
        Library::Signal<> pressed_signal{};
        Library::Signal<> released_signal{};
    };

    struct Tracked_Analog_Stick
    {
        System::Analog_Stick stick{};
        Library::Signal<System::Analog_Stick> signal{};
        Library::Signal<System::Analog_Stick> x_signal{};
        Library::Signal<System::Analog_Stick> y_signal{};
    };

    Tracked_Analog_Stick m_analog_stick{};
    std::map<PspCtrlButtons, Tracked_Button> m_buttons{
        {PspCtrlButtons::PSP_CTRL_SELECT, {}},   {PspCtrlButtons::PSP_CTRL_L3, {}},
        {PspCtrlButtons::PSP_CTRL_R3, {}},       {PspCtrlButtons::PSP_CTRL_START, {}},
        {PspCtrlButtons::PSP_CTRL_UP, {}},       {PspCtrlButtons::PSP_CTRL_RIGHT, {}},
        {PspCtrlButtons::PSP_CTRL_DOWN, {}},     {PspCtrlButtons::PSP_CTRL_LEFT, {}},
        {PspCtrlButtons::PSP_CTRL_L2, {}},       {PspCtrlButtons::PSP_CTRL_R2, {}},
        {PspCtrlButtons::PSP_CTRL_L1, {}},       {PspCtrlButtons::PSP_CTRL_R1, {}},
        {PspCtrlButtons::PSP_CTRL_TRIANGLE, {}}, {PspCtrlButtons::PSP_CTRL_CIRCLE, {}},
        {PspCtrlButtons::PSP_CTRL_CROSS, {}},    {PspCtrlButtons::PSP_CTRL_SQUARE, {}},
        {PspCtrlButtons::PSP_CTRL_HOME, {}},     {PspCtrlButtons::PSP_CTRL_HOLD, {}},
        {PspCtrlButtons::PSP_CTRL_NOTE, {}},     {PspCtrlButtons::PSP_CTRL_SCREEN, {}},
        {PspCtrlButtons::PSP_CTRL_VOLUP, {}},    {PspCtrlButtons::PSP_CTRL_VOLDOWN, {}},
        {PspCtrlButtons::PSP_CTRL_WLAN_UP, {}},  {PspCtrlButtons::PSP_CTRL_REMOTE, {}},
        {PspCtrlButtons::PSP_CTRL_DISC, {}},     {PspCtrlButtons::PSP_CTRL_MS, {}},
    };
};

} // namespace PS::Game