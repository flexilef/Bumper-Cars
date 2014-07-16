#include <iostream>
#include <SFML/Graphics.hpp>

#include "Car.h"
#include "Game.h"

using namespace std;

int main()
{
    Game theGame(500, 500);
    theGame.gameLoop();

    return 0;
}
