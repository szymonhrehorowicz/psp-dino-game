#include "game/actions/jump.h"
#include "game/config.h"
#include "system/coordinates.h"

namespace PS::Game
{

Jump_Action::Jump_Action(System::Vector_2D &position) : m_position(position)
{
    float const y = m_position.y - Config::PLAYER_JUMP_HEIGHT;
    m_position = {m_position.x, y};
};

void Jump_Action::execute()
{
    if (m_position.y < Config::GROUND_LEVEL)
    {
        m_position.y += Config::GRAVITY;
    }
    else
    {
        m_is_finished = true;
    }
}

} // namespace PS::Game