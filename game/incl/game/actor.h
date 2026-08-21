#pragma once

#include "library/action.h"
#include "system/coordinates.h"
#include <memory>
#include <vector>

namespace PS::Game
{

/**
 * @brief Base class for all actors
 *
 */
class Actor
{
  public:
    explicit Actor(System::Position position) : m_position(position) {};

    virtual void animate()
    {
        if (m_actions.empty())
        {
            return;
        }

        auto const &action = m_actions.front();
        action->execute();

        if (action->is_finished())
        {
            m_actions.erase(m_actions.begin());
        }
    };

    System::Position const &get_position() const
    {
        return m_position;
    }

    System::Position &get_position()
    {
        return m_position;
    }

  protected:
    bool has_active_action() const
    {
        return !m_actions.empty();
    }

    void request_action(std::unique_ptr<Library::Action> action)
    {
        m_actions.push_back(std::move(action));
    }

  private:
    System::Position m_position;
    std::vector<std::unique_ptr<Library::Action>> m_actions{};
};

} // namespace PS::Game