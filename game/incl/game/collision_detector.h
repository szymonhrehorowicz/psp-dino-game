/**
 * @file collision_detector.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "engine_defines.h"
#include "game/config.h"
#include "library/signal.h"
#include <algorithm>
#include <array>
#include <cmath>

namespace PS::Game
{

template <int Width, int Height> class Collision_Detector
{
    using Row = std::array<int, Width>;
    using Map = std::array<Row, Height>;

  public:
    void update(Actors const &actors)
    {
        m_map = {};
        int index = 1;

        for (auto const &actor : actors)
        {
            auto const rectangle = actor.ptr->get_rectangle();

            int const left = std::max(0, static_cast<int>(std::floor(rectangle.x)));
            int const top = std::max(0, static_cast<int>(std::floor(rectangle.y)));
            int const right = std::min(Width, static_cast<int>(std::ceil(rectangle.x + rectangle.w)));
            int const bottom = std::min(Height, static_cast<int>(std::ceil(rectangle.y + rectangle.h)));

            bool has_collided{false};
            for (int y = top; y < bottom; ++y)
            {
                for (int x = left; x < right; ++x)
                {
                    if (!has_collided && (m_map[y][x] != 0))
                    {
                        auto const &other_actor = actors.at(m_map[y][x] - 1);
                        emit_collision(actor);
                        emit_collision(other_actor);
                        has_collided = true;
                    }
                    m_map[y][x] = index;
                }
            }

            ++index;
        }
    }

    Library::Signal<> &on_collision()
    {
        return m_collision_signal;
    }

    Map const &get_map() const
    {
        return m_map;
    }

  private:
    void emit_collision(Actor_Data const &actor)
    {
        auto const collision_signal = actor.signals.find(Config::Signals::COLLISION);
        if (collision_signal != actor.signals.end())
        {
            m_collision_signal.emit(collision_signal->second);
        }
    }

    Map m_map{};
    Library::Signal<> m_collision_signal{};
};

} // namespace PS::Game