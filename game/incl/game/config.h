#pragma once

#include <cstdint>

namespace PS::Game::Config
{

// Screen
constexpr int SCREEN_WIDTH = 480;
constexpr int SCREEN_HEIGHT = 272;

// World
constexpr uint16_t GRAVITY = 5;
constexpr uint16_t GROUND_LEVEL = 200;
constexpr uint8_t SKY_COLOR_R = 140;
constexpr uint8_t SKY_COLOR_G = 195;
constexpr uint8_t SKY_COLOR_B = 255;
constexpr uint8_t SKY_COLOR_A = 204;
constexpr uint8_t GROUND_COLOR_R = 0;
constexpr uint8_t GROUND_COLOR_G = 160;
constexpr uint8_t GROUND_COLOR_B = 0;
constexpr uint8_t GROUND_COLOR_A = 255;

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