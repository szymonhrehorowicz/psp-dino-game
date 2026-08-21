#pragma once

#include <cstdint>

namespace PS::Game::Config
{

// World
constexpr uint16_t GRAVITY = 5;
constexpr uint16_t GROUND_LEVEL = 200;

// Player
constexpr uint16_t PLAYER_JUMP_HEIGHT = 50;
constexpr uint16_t PLAYER_POSITION_X = 200;
constexpr uint16_t PLAYER_POSITION_Y = GROUND_LEVEL;
constexpr char const *PLAYER_SPRITE = "idle.png";

// Obstacle
constexpr uint16_t OBSTACLE_SPEED = 1;
constexpr uint16_t OBSTACLE_POSITION_X = 400;
constexpr uint16_t OBSTACLE_POSITION_Y = GROUND_LEVEL;
constexpr char const *OBSTACLE_SPRITE = "grass.png";

// Assertions

static_assert((PLAYER_JUMP_HEIGHT % GRAVITY) == 0);
static_assert((OBSTACLE_POSITION_X % OBSTACLE_SPEED) == 0);

// Graphics
enum class Sprites
{
    PLAYER = 0,
    OBSTACLE = 1,

    LAST = 2
};

} // namespace PS::Game::Config