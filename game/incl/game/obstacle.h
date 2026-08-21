#pragma once

#include "actions/move_left.h"
#include "actor.h"
#include "game/config.h"
#include "system/coordinates.h"
#include <memory>

namespace PS::Game
{

class Obstacle : public Actor
{
  public:
    Obstacle() : Actor({Config::OBSTACLE_POSITION_X, Config::OBSTACLE_POSITION_Y}) {};

    void move_left()
    {
        if (!has_active_action())
        {
            request_action(std::make_unique<Move_Left_Action>(get_position()));
        }
    }
};

} // namespace PS::Game