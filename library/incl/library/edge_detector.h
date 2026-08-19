#pragma once

namespace PS::Library
{

class Edge_Detector
{
  public:
    Edge_Detector() = default;

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

    bool is_rising() const
    {
        return m_is_rising;
    };

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