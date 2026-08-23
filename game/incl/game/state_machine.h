/**
 * @file state_machine.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "game/controller_manager.h"
#include "library/signal.h"
#include "state_machine_defines.h"
#include <cassert>

namespace PS::Game
{

class State_Machine
{
  public:
    State_Machine(Controller_Manager &controller_manager) : m_controller_manager(controller_manager) {};

    void update()
    {
        switch (m_state)
        {
        case States::START:
            state_start();
            break;
        case States::GAME:
            state_game();
            break;
        case States::END:
            state_end();
            break;
        default:
            assert(false);
            break;
        }

        m_transition_button_pressed = false;
        m_game_ended = false;
    }

    States get_state() const
    {
        return m_state;
    }

    Library::Signal<> &on_game_start()
    {
        return m_game_start_signal;
    }

    void set_game_ended()
    {
        m_game_ended = true;
    }

  private:
    void state_start()
    {
        static bool is_initialized{false};
        static bool is_finished{false};

        if (!is_initialized)
        {
            is_initialized = true;
            is_finished = false;
            m_transition_button_signal_id = m_controller_manager.on_button_pressed(PspCtrlButtons::PSP_CTRL_CROSS)
                                                .connect(this, &State_Machine::transition_button_pressed);
        }

        if (!is_finished && m_transition_button_pressed)
        {
            m_controller_manager.on_button_pressed(PspCtrlButtons::PSP_CTRL_CROSS)
                .disconnect(m_transition_button_signal_id);
            is_initialized = false;
            is_finished = true;
            m_state = States::GAME;
        }
    }

    void state_game()
    {
        static bool is_initialized{false};
        static bool is_finished{false};

        if (!is_initialized)
        {
            is_initialized = true;
            is_finished = false;
            m_game_start_signal.emit();
        }

        if (!is_finished && m_game_ended)
        {
            is_initialized = false;
            is_finished = true;
            m_state = States::END;
        }
    }

    void state_end()
    {
        static bool is_initialized{false};
        static bool is_finished{false};

        if (!is_initialized)
        {
            is_initialized = true;
            is_finished = false;
            m_transition_button_signal_id = m_controller_manager.on_button_pressed(PspCtrlButtons::PSP_CTRL_CROSS)
                                                .connect(this, &State_Machine::transition_button_pressed);
        }

        if (!is_finished && m_transition_button_pressed)
        {
            m_controller_manager.on_button_pressed(PspCtrlButtons::PSP_CTRL_CROSS)
                .disconnect(m_transition_button_signal_id);
            is_initialized = false;
            is_finished = true;
            m_state = States::GAME;
        }
    }

    void transition_button_pressed()
    {
        m_transition_button_pressed = true;
    }

    States m_state{States::START};
    Controller_Manager &m_controller_manager;
    Library::Signal<> m_game_start_signal{};

    int m_transition_button_signal_id{0};
    bool m_transition_button_pressed{false};
    bool m_game_ended{false};
};

} // namespace PS::Game