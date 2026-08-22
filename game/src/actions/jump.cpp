#include "game/actions/jump.h"
#include "game/config.h"

namespace PS::Game
{

Jump_Action::Jump_Action(SDL_FRect &position) : m_position(position)
{
    m_position.y -= Config::PLAYER_JUMP_HEIGHT;
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