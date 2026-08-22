/**
 * @file obstacle_generator.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "coordinates.h"
#include "signal.h"
#include <random>

namespace PS::Library
{

/**
 * @brief Generates obstacle coordinates on random levels (upper or lower)
 *
 */
class Obstacle_Position_Generator
{
  public:
    Obstacle_Position_Generator() = default;

    void update()
    {
        ++m_elapsed_time;

        if (m_elapsed_time >= m_period)
        {
            // 0 - ground level, 1 - above player level
            int const level_coefficient = m_distribution(m_generator);
            Vector_2D position{};
            position.x = m_starting_x;
            position.y = level_coefficient == 0 ? m_lower_level : m_upper_level;
            m_new_obstacle_signal.emit(position);
            m_elapsed_time = 0;
        }
    }

    /**
     * @brief Get access to signal raised whenever new obstacle is generated
     *
     * @return Signal<Vector_2D>& - (X, Y) position of a newly generated obstacle
     */
    Signal<Vector_2D> &on_new_obstacle()
    {
        return m_new_obstacle_signal;
    }

    /**
     * @brief Set period in which new obstacle position will be generated
     *
     * @param period
     */
    void set_period(int period)
    {
        m_period = period;
    }

    /**
     * @brief Set levels on which new obstacle will be generated
     *
     * @param lower - ground level
     * @param upper - level above the player
     */
    void set_levels(int lower, int upper)
    {
        m_lower_level = lower;
        m_upper_level = upper;
    }

    /**
     * @brief Set the starting X coordinate of newly created obstacles
     *
     * @param x
     */
    void set_starting_x(int x)
    {
        m_starting_x = x;
    }

  private:
    std::default_random_engine m_generator{};
    std::uniform_int_distribution<int> m_distribution{0, 1};

    Signal<Vector_2D> m_new_obstacle_signal{};

    int m_period{0};
    int m_elapsed_time{0};

    int m_lower_level{0};
    int m_upper_level{0};
    int m_starting_x{0};
};

} // namespace PS::Library