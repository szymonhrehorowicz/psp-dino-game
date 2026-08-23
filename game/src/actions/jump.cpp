#include "game/actions/jump.h"
#include "game/config.h"

namespace PS::Game
{

Jump_Action::Jump_Action(Library::Rectangle &rectangle) : m_rectangle(rectangle) {};

void Jump_Action::execute()
{
    if (m_is_finished)
    {
        return;
    }

    if (!m_is_falling)
    {
        m_rectangle.y += Config::PLAYER_JUMP_SPEED;
        m_distance += Config::PLAYER_JUMP_SPEED;
        if (m_distance <= Config::PLAYER_JUMP_HEIGHT)
        {
            m_is_falling = true;
        }
    }
    else
    {
        m_rectangle.y += Config::GRAVITY;
        m_distance += Config::GRAVITY;
        if (m_distance == 0)
        {
            m_is_finished = true;
        }
    }
}

} // namespace PS::Game