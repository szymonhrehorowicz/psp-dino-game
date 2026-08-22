/**
 * @file engine_defines.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "game/actor.h"
#include "game/config.h"
#include <map>

namespace PS::Game
{

struct Actor_Data
{
    std::unique_ptr<Actor> ptr;
    Config::Sprites sprite;
    std::map<Config::Signals, int> signals;
};

using Actors = std::vector<Actor_Data>;

} // namespace PS::Game