#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

Game::Game(int w, int h) : theRenderer(&window)
{
    width = w;
    height = h;
    theCar.setPosition(200, 200);
    car.setPosition(400, 400);
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
            //handleUserInput();
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
    theCar.dump();

    theCar.update();
    car.update();
    handleUserInput();
    checkCollisions();
}

void Game::displayGame()
{
    theRenderer.render(theCar);
    theRenderer.render(car);
}

void Game::handleUserInput()
{
    //UP = accelerate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        theCar.accelerate();
        //theCar.setDriveState(1);
        //allow turning only when accelerating
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            theCar.turnRight();
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            theCar.turnLeft();
    }
    //reversing
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        theCar.applyReverse();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            theCar.turnRight();
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            theCar.turnLeft();
    }
    //braking
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
    {
        theCar.applyBrakes();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            theCar.turnRight();
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            theCar.turnLeft();
    }
    //no user input let the car decelerate naturally
    else
    {
        theCar.decelerate();

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

void Game::checkCollisions()
{
    if(Collision::BoundingBoxTest(theCar.getCurrentSprite(), car.getCurrentSprite()))
    {
        std::cout << "Collided!\n";
        double vel1 = theCar.getVelocity();
        double vel2 = car.getVelocity();

        int angle1 = theCar.getTravelAngle();
        int angle2 = car.getTravelAngle();

        theCar.setTravelAngle(90);
        theCar.setDriveState(4);
        theCar.setVelocity(2);
        car.setVelocity(0);
        car.setTravelAngle(270);
    }
}
