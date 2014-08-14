#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Car.h"
#include "Renderer.h"

class Game
{
public:
    Game(int, int);
    void gameLoop();
    void handleUserInput();
    void displayGame();       //renders gameObjects
    void update();          //updates gameObjects
    void checkCollisions();

private:
    int width;
    int height;
    sf::RenderWindow window;
    Renderer theRenderer;
    std::vector<Car> theCars;
    Car theCar;
    Car car;
};

#endif // GAME_H_INCLUDED
