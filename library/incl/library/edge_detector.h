/**
 * @file edge_detector.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

namespace PS::Library
{

/**
 * @brief Detect rising and falling edges of a boolean signal
 *
 */
class Edge_Detector
{
  public:
    Edge_Detector() = default;

    /**
     * @brief Update detector
     *
     * @param state
     * @return true - edge detected
     * @return false - no edge detected
     */
    bool update(bool state)
    {
        bool const changed = m_state != state;

        if (changed)
        {
            m_is_rising = state;
            m_is_falling = !state;
        }
        else
        {
            m_is_rising = false;
            m_is_falling = false;
        }

        m_state = state;
        return changed;
    }

    /**
     * @brief Get rising edge state of the detector after last update
     *
     * @return true - if rising edge detected
     * @return false - no rising edge detected
     */
    bool is_rising() const
    {
        return m_is_rising;
    };

    /**
     * @brief Get falling edge state of the detector after last update
     *
     * @return true - if falling edge detected
     * @return false - no falling edge detected
     */
    bool is_falling() const
    {
        return m_is_falling;
    };

  private:
    bool m_state{false};

    bool m_is_rising{false};
    bool m_is_falling{false};
};

}; // namespace PS::Library