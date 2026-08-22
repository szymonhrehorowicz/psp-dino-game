#pragma once

#include "actions/move_left.h"
#include "actor.h"
#include "game/config.h"
#include "library/coordinates.h"
#include <memory>

namespace PS::Game
{

class Obstacle : public Actor
{
  public:
    Obstacle() : Actor({.x = Config::OBSTACLE_POSITION_X, .y = Config::OBSTACLE_POSITION_Y}) {};

    Obstacle(Library::Vector_2D position) : Actor({.x = position.x, .y = position.y}) {};

    void move_left()
    {
        if (!has_active_action())
        {
            request_action(std::make_unique<Move_Left_Action>(get_rectangle()));
        }
    }
};

} // namespace PS::Game