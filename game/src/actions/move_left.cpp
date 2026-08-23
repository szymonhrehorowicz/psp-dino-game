#include "game/actions/move_left.h"
#include "game/config.h"

namespace PS::Game
{

Move_Left_Action::Move_Left_Action(Library::Rectangle &rectangle)
{
    float const x = rectangle.x - Config::OBSTACLE_SPEED;
    if (x >= -rectangle.w)
    {
        rectangle.x = x;
    }
    m_is_finished = true;
};

} // namespace PS::Game