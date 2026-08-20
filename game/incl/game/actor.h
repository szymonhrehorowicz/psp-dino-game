#pragma once

#include "library/action.h"
#include "system/coordinates.h"
#include "system/graphics/sprite.h"
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
    explicit Actor(SDL_Renderer &renderer, const char *file, System::Position position)
        : m_position(position), m_sprite(renderer, file, m_position) {};

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

        m_sprite.set_position(m_position);
    };

    void set_position(System::Position position)
    {
        m_position = position;
        m_sprite.set_position(position);
    }

    System::Position const &get_position() const
    {
        return m_position;
    }

    System::Position &get_position()
    {
        return m_position;
    }

    System::Graphics::Sprite const &get_sprite() const
    {
        return m_sprite;
    }

    System::Graphics::Sprite &get_sprite()
    {
        return m_sprite;
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
    System::Graphics::Sprite m_sprite;

    std::vector<std::unique_ptr<Library::Action>> m_actions{};
};

} // namespace PS::Game