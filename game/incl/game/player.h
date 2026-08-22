/**
 * @file player.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "actions/jump.h"
#include "actor.h"
#include "game/actions/collision.h"
#include "game/config.h"
#include "library/coordinates.h"
#include <memory>

namespace PS::Game
{

/**
 * @brief Represents Player state as an Actor.
 *
 */
class Player : public Actor
{
  public:
    explicit Player(Library::Vector_2D dead_dimensions)
        : Actor({Config::PLAYER_POSITION_X, Config::PLAYER_POSITION_Y}, Config::Sprites::PLAYER),
          m_dead_dimensions(dead_dimensions)
    {
    }

    /**
     * @brief Registers and Action for the Player to jump.
     *
     */
    void jump()
    {
        if (!has_active_action())
        {
            request_action(std::make_unique<Jump_Action>(get_rectangle()));
        }
    }

    void die()
    {
        request_action(std::make_unique<Collision_Action>(get_rectangle(), m_dead_dimensions, get_sprite(),
                                                          Config::Sprites::PLAYER_DEAD));
    }

  private:
    Library::Vector_2D m_dead_dimensions;
};

}; // namespace PS::Game