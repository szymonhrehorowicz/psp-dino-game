#pragma once

namespace PS::Library
{

struct Vector_2D
{
    float x{};
    float y{};

    Vector_2D() = default;

    Vector_2D(float x, float y) : x{x}, y{y} {};

    Vector_2D(Vector_2D const &other) : x{other.x}, y{other.y} {};
};

} // namespace PS::Library