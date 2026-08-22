/**
 * @file color.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <cstdint>

namespace PS::System::Graphics
{

struct Color
{
    uint8_t r{};
    uint8_t g{};
    uint8_t b{};
    uint8_t a{};

    constexpr Color() = default;
    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {};
};

} // namespace PS::System::Graphics