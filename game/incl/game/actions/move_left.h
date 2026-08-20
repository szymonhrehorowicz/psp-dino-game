#pragma once

#include "library/action.h"

namespace PS
{

namespace System
{
struct Position;
}

namespace Game
{

class Move_Left_Action : public Library::Action
{
  public:
    Move_Left_Action(struct System::Position &position);

    void execute() final {};

  private:
    System::Position &m_position;
};

} // namespace Game

} // namespace PS