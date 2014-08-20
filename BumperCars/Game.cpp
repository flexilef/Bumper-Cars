#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

Game::Game(int w, int h) : theRenderer(&window)
{
    width = w;
    height = h;
    theCar.setPosition(200, 300);
    car.setPosition(0, 0);
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
        /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(theCar.getVelocity() > 1)
                theCar.turnRight();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(theCar.getVelocity() > 1)
                theCar.turnLeft();
        }*/
    }
}

void Game::checkCollisions()
{
    if(Collision::BoundingBoxTest(theCar.getCurrentSprite(), car.getCurrentSprite()))
    {
        std::cout << "Collided!\n";

        applyCollision(theCar, car);
        //double vel1 = theCar.getVelocity();
        //double vel2 = car.getVelocity();

        //int angle1 = theCar.getTravelAngle();
        //int angle2 = car.getTravelAngle();

        //theCar.setTravelAngle(90);
        //theCar.setDriveState(4);
        //theCar.setVelocity(2);
        //car.setVelocity(0);
        //car.setTravelAngle(270);
    }
}

void Game::applyCollision(Car& car1, Car& car2)
{
    int angle1 = car1.getTravelAngle();
    int angle2 = car2.getTravelAngle();

    sf::Vector2f unitVector1(cos(angle1*PI/180), sin(angle1*PI/180));
    sf::Vector2f unitVector2(cos(angle1*PI/180), sin(angle1*PI/180));

    int mass1 = car1.getMass();
    int mass2 = car2.getMass();
    int massTotal = mass1 + mass2;

    double posX1 = car1.getPosX();
    double posY1 = car1.getPosY();
    double posX2 = car2.getPosX();
    double posY2 = car2.getPosY();

    double vel1 = car1.getVelocity();
    double vel2 = car2.getVelocity();

    double momentumInit1X = mass1 * vel1 * unitVector1.x;
    double momentumInit2X = mass2 * vel2 * unitVector2.x;

    double momentumInit1Y = mass1 * vel1 * unitVector1.y;
    double momentumInit2Y = mass2 * vel2 * unitVector2.y;

    double momentumTotalInitX = momentumInit1X + momentumInit2X;
    double momentumTotalInitY = momentumInit1Y + momentumInit2Y;

    double velFinalX = momentumTotalInitX/massTotal;
    double velFinalY = momentumTotalInitY/massTotal;

    double velFinal = sqrt(velFinalX * velFinalX + velFinalY * velFinalY)*2;
    double angleFinal = tan(velFinalY/velFinalX)*10;

    car1.setDriveState(4);
    car2.setDriveState(4);

    //NEED to separate (minimum distance) before setting cars off on their ways
    car1.setTravelAngle(angle2);
    car2.setTravelAngle(angle1);

    car1.setVelocity(vel2);
    car2.setVelocity(vel1);

    std::cout << "car1: " << theCar.getTravelAngle() << "\n";
    std::cout << "car2: " << car.getTravelAngle() << "\n";
}
