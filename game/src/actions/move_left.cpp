#include "game/actions/move_left.h"
#include "game/config.h"
#include "system/coordinates.h"

namespace PS::Game
{

Move_Left_Action::Move_Left_Action(System::Vector_2D &position) : m_position(position)
{
    float const x = m_position.x - Config::OBSTACLE_SPEED;
    if (x >= 0)
    {
        m_position = {x, m_position.y};
    }
    m_is_finished = true;
};

} // namespace PS::Game