#pragma once

#include "SDL3/SDL_rect.h"
#include "library/action.h"

namespace PS
{

namespace Game
{

class Move_Left_Action : public Library::Action
{
  public:
    Move_Left_Action(SDL_FRect &rectangle);

    void execute() final {};
};

} // namespace Game

} // namespace PS