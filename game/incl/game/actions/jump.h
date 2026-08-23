/**
 * @file jump.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "library/action.h"
#include "library/coordinates.h"

namespace PS
{

namespace Game
{

/**
 * @brief Action manipulating the position to jump up to a predefined height with predefined speed of raise and fall.
 *
 */
class Jump_Action : public Library::Action
{
  public:
    Jump_Action(Library::Rectangle &rectangle);

    /**
     * @brief Executes a step of an action of jumping.
     *
     */
    void execute() final;

  private:
    Library::Rectangle &m_rectangle;
    int m_distance{0};
    bool m_is_falling{false};
};

} // namespace Game

} // namespace PS