#pragma once

#include "pspdebug.h"

namespace PS::Game
{

struct Position
{
    float x{};
    float y{};
};

class Player
{
    static constexpr float ground_level{200};

  public:
    void animate()
    {
        if (m_position.y < ground_level)
        {
            m_position.y += 1;
        }
    }

    void jump()
    {
        // pspDebugScreenPrintf("Jumping!");
        float const y = m_position.y - 50;
        m_position = {m_position.x, y};
    };

    void set_position(Position position)
    {
        m_position = position;
    }

    Position const &get_position() const
    {
        return m_position;
    }

  private:
    Position m_position{200, 200};
};

}; // namespace PS::Game