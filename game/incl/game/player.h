#pragma once

#include "actions/jump.h"
#include "actor.h"
#include "game/config.h"
#include <memory>

namespace PS::Game
{

class Player : public Actor
{
  public:
    Player() : Actor({Config::PLAYER_POSITION_X, Config::PLAYER_POSITION_Y}) {};

    void jump()
    {
        if (!has_active_action())
        {
            request_action(std::make_unique<Jump_Action>(get_rectangle()));
        }
    }
};

}; // namespace PS::Game