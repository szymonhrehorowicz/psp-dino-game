/**
 * @file move_left.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "SDL3/SDL_rect.h"
#include "library/action.h"

namespace PS
{

namespace Game
{

/**
 * @brief Action manipulating the position to move left for a predefined distance, unless the object is already out of
 * the screen (past left border).
 *
 */
class Move_Left_Action : public Library::Action
{
  public:
    Move_Left_Action(SDL_FRect &rectangle);

    /**
     * @brief Executes an action of moving left by a single predefined step.
     *
     */
    void execute() final {};
};

} // namespace Game

} // namespace PS