#include <iostream>

#include "Game.h"

Game::Game(int width, int height)
{
    window.create(sf::VideoMode(width, height), "Bumper Cars!!!");
}

void Game::gameLoop()
{
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();

        theCar.drive();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            theCar.turnRight();
            theCar.accelerate();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            theCar.turnLeft();
            theCar.accelerate();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            theCar.turnRight();
            theCar.decelerate();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            theCar.turnLeft();
            theCar.decelerate();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            theCar.accelerate();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            theCar.decelerate();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(theCar.getVelocity() > 1)
                theCar.turnRight();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(theCar.getVelocity() > 1)
                theCar.turnLeft();
        }
        //debugging purposes
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            std::cout << "Angle: " << theCar.getAngle() << "\n";
            std::cout << "x: " << theCar.getPosX() << "\n";
            std::cout << "y: " << theCar.getPosY() << "\n";
        }

        theCar.draw(&window);
        window.display();
    }
}