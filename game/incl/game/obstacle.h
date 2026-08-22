#pragma once

#include "actions/move_left.h"
#include "actor.h"
#include "game/config.h"
#include "library/coordinates.h"
#include <memory>

namespace PS::Game
{

/**
 * @brief Represents Obstacle state of Actor.
 *
 */
class Obstacle : public Actor
{
  public:
    Obstacle()
        : Actor({.x = Config::OBSTACLE_POSITION_X, .y = Config::OBSTACLE_POSITION_Y}, Config::Sprites::OBSTACLE) {};

    Obstacle(Library::Vector_2D position) : Actor({.x = position.x, .y = position.y}, Config::Sprites::OBSTACLE) {};

    /**
     * @brief Registers an Action for the Obstacle to move left.
     *
     */
    void move_left()
    {
        if (!has_active_action())
        {
            request_action(std::make_unique<Move_Left_Action>(get_rectangle()));
        }
    }
};

} // namespace PS::Game