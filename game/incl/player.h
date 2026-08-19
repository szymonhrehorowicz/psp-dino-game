#pragma once

#include "pspdebug.h"

namespace PS::Game
{

class Player
{
  public:
    void jump()
    {
        pspDebugScreenPrintf("Jumping!");
    };

  private:
};

}; // namespace PS::Game