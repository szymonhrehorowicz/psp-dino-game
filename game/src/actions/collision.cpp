#include "game/actions/collision.h"

namespace PS::Game
{

Collision_Action::Collision_Action(SDL_FRect &rectangle, Library::Vector_2D dimensions, Config::Sprites &sprite,
                                   Config::Sprites collision_sprite)
{
    float const bottom = rectangle.y + rectangle.h;
    rectangle.w = dimensions.x;
    rectangle.h = dimensions.y;
    rectangle.y = bottom - rectangle.h;
    sprite = collision_sprite;
    m_is_finished = true;
}

} // namespace PS::Game