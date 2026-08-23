/**
 * @file config.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "system/graphics/color.h"
#include <cstdint>

namespace PS::Game::Config
{

// Screen
constexpr int SCREEN_WIDTH = 480;
constexpr int SCREEN_HEIGHT = 272;

// World
constexpr int GRAVITY = 5;
constexpr int GROUND_LEVEL = 200;
constexpr System::Graphics::Color SKY_COLOR{140, 195, 255, 204};
constexpr System::Graphics::Color GROUND_COLOR{0, 160, 0, 255};

// Player
constexpr int PLAYER_JUMP_HEIGHT = -50;
constexpr int PLAYER_JUMP_SPEED = -GRAVITY;
constexpr int PLAYER_POSITION_X = 200;
constexpr int PLAYER_POSITION_Y = GROUND_LEVEL;
#ifdef PSP_DEBUG_PRX
constexpr char const *PLAYER_SPRITE = "host0:/idle.png";
constexpr char const *PLAYER_DEAD_SPRITE = "host0:/dead.png";
#else
constexpr char const *PLAYER_SPRITE = "idle.png";
constexpr char const *PLAYER_DEAD_SPRITE = "dead.png";
#endif

// Obstacle
constexpr int OBSTACLE_SPEED = 4;
constexpr int OBSTACLE_POSITION_X = 400;
constexpr int OBSTACLE_POSITION_Y = GROUND_LEVEL;
#ifdef PSP_DEBUG_PRX
constexpr char const *OBSTACLE_SPRITE = "host0:/grass.png";
#else
constexpr char const *OBSTACLE_SPRITE = "grass.png";
#endif

// Assertions

static_assert((PLAYER_JUMP_HEIGHT % GRAVITY) == 0);
static_assert((PLAYER_JUMP_SPEED % GRAVITY) == 0);
static_assert((OBSTACLE_POSITION_X % OBSTACLE_SPEED) == 0);

// Graphics
enum class Sprites
{
    PLAYER = 0,
    PLAYER_DEAD = 1,
    OBSTACLE = 2,

    LAST = 3
};

enum class Signals
{
    GAME_TICK = 0,
    COLLISION = 1,
    BUTTON_CROSS = 2,
};

} // namespace PS::Game::Config