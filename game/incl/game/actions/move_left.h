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
    Move_Left_Action(SDL_FRect &position);

    void execute() final {};

  private:
    SDL_FRect &m_position;
};

} // namespace Game

} // namespace PS