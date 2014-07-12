#include "Car.h"
#include <cmath>
#include <iostream>

Car::Car()
{
    ///position
    posX = 0;
    posY = 0;
    angle = 0;
    velocity = 0;
    acceleration = 0;

    ///properties
    maxSpeed = 10;
    maxBackThrust = 3;
    rotateSpeed = 5;
    maxHealth = 100;
    mass = 10;

    health = maxHealth;
    currentState = 1;

    ///image properties
    currentGraphic = "greenCarSS.png";

    //for later
    rollGraphic = "greenCar.png";
    staticGraphic = "greenCar.png";
    destroyedGraphic = "greenCar.png";
}

Car::Car(int x, int y)
{
    posX = x;
    posY = y;
    angle = 0;
    velocity = 0;
    acceleration = 0;

    ///properties
    maxSpeed = 10;
    maxBackThrust = 3;
    rotateSpeed = 5;
    maxHealth = 100;
    mass = 10;

    health = maxHealth;
    currentState = 1;

    ///image properties
    currentGraphic = "greenCarSS.png";

    //for later
    rollGraphic = "greenCar.png";
    staticGraphic = "greenCar.png";
    destroyedGraphic = "greenCar.png";
}

int Car::draw(sf::RenderWindow* _window)
{
    sf::Texture carText;

    if(!carText.loadFromFile("assets/images/" + currentGraphic))
        return EXIT_FAILURE;

    //40 is the angle to the next row on the sprite sheet
    //read carSS.txt for this algorithm
    if(angle > 359)
        angle = 0;
    else if(angle < 0)
        angle = 359;

    int row = angle/40;
    int column = (angle-(40*row)) / 5;

    currentSprite.setTexture(carText);

    //std::cout << "row: " << row << " column: " << column << "\n";

    //IntRect(left,top,width,height)
    currentSprite.setTextureRect(sf::IntRect(column*76, row*76, 76,76));

    ///sync graphic and sprite
    sync();

    _window->draw(currentSprite);

    return 0;
}

//syncs the sprite graphic with the actual object
void Car::sync()
{
    currentSprite.setPosition(posX,posY);
}

//constantly driving
void Car::drive()
{
    int friction = 1;

    if(velocity > 0)
    {
        velocity-=friction;
    }
    else
    {
        velocity = 0;
    }

    double velocityX = cos(angle*PI/180.0)*velocity;
    double velocityY = sin(angle*PI/180.0)*velocity;

    std::cout << "velocityX: " << velocityX << "\n";
    std::cout << "velocityY: " << velocityY << "\n";
    posX+=velocityX;
    posY-=velocityY;
}

void Car::accelerate()
{
    if(acceleration < 3)
        acceleration++;

    //acceleration = 1;

    if(velocity < maxSpeed)
        velocity+=acceleration;

    //velocity = 1;
/*
    //slightly off but not visible enough to matter
    //the spritesheet is messed up... 0 was North so need to redo
    //spritesheet where 0 is Right and 90 is North
    //or else we will always have angle-90 to compensate
    double velocityX = cos(angle*PI/180.0)*velocity;
    double velocityY = sin(angle*PI/180.0)*velocity;

    std::cout << "velocityX: " << velocityX << "\n";
    std::cout << "velocityY: " << velocityY << "\n";
    posX+=velocityX;
    posY-=velocityY;
    */
}

void Car::decelerate()
{
    double velocityX = cos(angle*PI/180.0)*velocity;
    double velocityY = sin(angle*PI/180.0)*velocity;

    std::cout << "velocityX: " << velocityX << "\n";
    std::cout << "velocityY: " << velocityY << "\n";

    posX-=velocityX;
    posY+=velocityY;
}

void Car::turnRight()
{
    if(angle > 359)
        angle = 0;

    angle-=rotateSpeed;
}

void Car::turnLeft()
{
    if(angle < 0)
        angle = 359;

    angle+=rotateSpeed;
}

int Car::getPosX()
{
    return posX;
}
int Car::getPosY()
{
    return posY;
}
int Car::getAngle()
{
    return angle;
}
