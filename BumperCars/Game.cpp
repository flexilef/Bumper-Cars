#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

Game::Game(int width, int height):car(400, 400)
{
    window.create(sf::VideoMode(width, height), "Bumper Cars!!!");
}

void Game::gameLoop()
{
    sf::Clock myClock;
    const int TICKS_PER_SECOND = 50;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 10;

    sf::Int32 nextGameTick = myClock.getElapsedTime().asMilliseconds();
    int loops;

    while(window.isOpen())
    {
        loops = 0;

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        while(myClock.getElapsedTime().asMilliseconds() > nextGameTick && loops < MAX_FRAMESKIP)
        {
            ///This should all be in updateGame()
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                theCar.accelerate();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    theCar.turnRight();
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    theCar.turnLeft();
            }
            else
            {
                theCar.decelerate();
            }
            /*
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                theCar.accelerate();
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                theCar.decelerate();
            }*/

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
                std::cout << "velocity: " << theCar.getVelocity() << "\n";
                std::cout << "acceleration: " << theCar.getAcceleration() << "\n";
            }
            theCar.drive();
            //car.drive();
            checkCollisions();
            ///This above should all be in updateGame()

            //time stuff
            nextGameTick+=SKIP_TICKS;
            loops++;

            //std::cout << "loops: " << loops << "\n";
            //std::cout << "nextGameTick: " << nextGameTick << "\n";
            //std::cout << "elapsed: " << myClock.getElapsedTime().asMilliseconds() << "\n";

        }

        window.clear();
        ///This should all be in displayGame()
        theCar.draw(&window);
        car.draw(&window);

        window.display();
        ///This all above should be in displayGame()
    }
}

void Game::checkCollisions()
{
    if(Collision::BoundingBoxTest(theCar.getCurrentSprite(), car.getCurrentSprite()))
    {
        //std::cout << "Collided!\n";
        double velocity = theCar.getVelocity()/2;
        theCar.setVelocity(-20);
        car.setVelocity(velocity);
    }
    //else
    //std::cout << "NOT Collided!\n";
}
