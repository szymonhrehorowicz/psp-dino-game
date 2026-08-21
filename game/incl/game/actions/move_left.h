#pragma once

#include "library/action.h"

namespace PS
{

namespace System
{
struct Vector_2D;
}

namespace Game
{

class Move_Left_Action : public Library::Action
{
  public:
    Move_Left_Action(struct System::Vector_2D &position);

    void execute() final {};

  private:
    System::Vector_2D &m_position;
};

} // namespace Game

} // namespace PS