/**
 * @file action.h
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
 * @brief Base class for executable actions
 *
 */
class Action
{
  public:
    virtual ~Action() = default;

    /**
     * @brief Execute defined action
     *
     */
    virtual void execute() = 0;

    /**
     * @brief Informs about the state of the action
     *
     * @return true - if finished
     * @return false - otherwise
     */
    bool is_finished()
    {
        return m_is_finished;
    }

  protected:
    bool m_is_finished{false};
};

} // namespace PS::Library