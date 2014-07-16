#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Car.h"

class Game
{
public:
    Game(int, int);
    void gameLoop();

private:
    sf::RenderWindow window;
    Car theCar;
};

#endif // GAME_H_INCLUDED
