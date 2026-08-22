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
#include "game/config.h"
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
    Player() : Actor({Config::PLAYER_POSITION_X, Config::PLAYER_POSITION_Y}) {};

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
};

}; // namespace PS::Game