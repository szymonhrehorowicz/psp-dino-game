#pragma once

#include "library/action.h"

namespace PS::Game
{

class Jump_Action : public Library::Action
{
  public:
    Jump_Action(struct Position &position);

    void execute() final;

  private:
    Position &m_position;
};

} // namespace PS::Game