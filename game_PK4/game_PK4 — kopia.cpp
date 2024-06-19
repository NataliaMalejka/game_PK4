#pragma once
#include "GameEngine.h"

int main()
{
    srand(static_cast<unsigned>(time(0)));

    GameEngine gameEngine;
    gameEngine.run();
}
