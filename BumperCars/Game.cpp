#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

Game::Game(int width, int height) : theRenderer(&window), theCar(400, 400)
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
            handleUserInput();
            update();
            //checkCollisions();

            //time stuff
            nextGameTick+=SKIP_TICKS;
            loops++;
        }

        window.clear();
        displayGame();
        window.display();
    }
}

void Game::update()
{
    theCar.drive();
}

void Game::displayGame()
{
    theRenderer.render(theCar);
}

void Game::handleUserInput()
{
    //UP = accelerate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        theCar.setDriveState(1);
        //allow turning only when accelerating
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            theCar.turnRight();
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            theCar.turnLeft();
    }
    //reversing
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        theCar.setDriveState(2);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            theCar.turnRight();
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            theCar.turnLeft();
    }
    //braking
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
    {
        theCar.setDriveState(3);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            theCar.turnRight();
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            theCar.turnLeft();
    }
    //no engine force
    else
    {
        theCar.setDriveState(0);

        //still turn if the user wants to
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
    }
}

/*void Game::checkCollisions()
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
}*/
