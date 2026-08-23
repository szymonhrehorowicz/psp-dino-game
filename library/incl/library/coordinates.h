/**
 * @file coordinates.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

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

struct Rectangle
{
    float x{};
    float y{};
    float w{};
    float h{};
};

} // namespace PS::Library