#pragma once

#include <cstdint>

namespace PS::Game::Config
{

// World
constexpr uint16_t GRAVITY = 5;
constexpr uint16_t GROUND_LEVEL = 200;

// Player
constexpr uint16_t JUMP_HEIGHT = 50;
constexpr uint16_t PLAYER_POSITION_X = 200;
constexpr uint16_t PLAYER_POSITION_Y = GROUND_LEVEL;

// Assertions

static_assert((JUMP_HEIGHT % GRAVITY) == 0);

} // namespace PS::Game::Config