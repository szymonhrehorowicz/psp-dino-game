/**
 * @file collision.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "game/config.h"
#include "library/action.h"
#include "library/coordinates.h"
namespace PS::Game
{

class Collision_Action : public Library::Action
{
  public:
    Collision_Action(Library::Rectangle &rectangle, Library::Vector_2D dimensions, Config::Sprites &sprite,
                     Config::Sprites collision_sprite);

    void execute() final {};
};

} // namespace PS::Game