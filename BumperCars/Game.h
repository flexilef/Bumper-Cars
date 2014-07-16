#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Car.h"

class Game
{
public:
    Game(int, int);
    void gameLoop();
    void checkCollisions();

private:
    sf::RenderWindow window;
    Car theCar;
    Car car;
};

#endif // GAME_H_INCLUDED
