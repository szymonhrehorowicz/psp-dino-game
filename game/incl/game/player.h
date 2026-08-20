#pragma once

#include "actions/jump.h"
#include "coordinates.h"
#include "game/config.h"
#include "library/action.h"
#include <memory>
#include <vector>

namespace PS::Game
{

class Player
{
    static constexpr float ground_level{200};

  public:
    Player() = default;

    void animate()
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
    }

    void jump()
    {
        m_actions.push_back(std::make_unique<Jump_Action>(m_position));
    }

    void set_position(Position position)
    {
        m_position = position;
    }

    Position const &get_position() const
    {
        return m_position;
    }

  private:
    Position m_position{
        Config::PLAYER_POSITION_X,
        Config::PLAYER_POSITION_Y,
    };

    std::vector<std::unique_ptr<Library::Action>> m_actions{};
};

}; // namespace PS::Game