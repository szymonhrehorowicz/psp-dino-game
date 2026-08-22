#pragma once

#include "SDL3/SDL_rect.h"
#include "library/action.h"

namespace PS
{

namespace Game
{

class Jump_Action : public Library::Action
{
  public:
    Jump_Action(SDL_FRect &rectangle);

    void execute() final;

  private:
    SDL_FRect &m_rectangle;
    int m_distance{0};
    bool m_is_falling{false};
};

} // namespace Game

} // namespace PS