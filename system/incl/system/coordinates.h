#pragma once

namespace PS::System
{

struct Position
{
    float x{};
    float y{};

    Position(float x, float y) : x{x}, y{y} {};
};

} // namespace PS::System