#include "Car.h"
#include <cmath>
#include <iostream>

Car::Car()
{
    ///position
    posX = 0;
    posY = 0;
    velocity = 0;
    acceleration = 0;
    angle = 0;
    rotateSpeed = 5;

    ///properties
    maxVelocity = 10;
    maxBackVelocity = 3;
    maxRotateSpeed = 5;
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
    velocity = 0;
    acceleration = 0;
    angle = 0;
    rotateSpeed = 5;

    ///properties
    maxVelocity = 10;
    maxBackVelocity = 5;
    maxRotateSpeed = 5;
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
    double frictionFactor = .1;     //lower the less friction there is
    double velocityLoss = velocity * frictionFactor;

    velocity-=velocityLoss;         //apply friction

    //special cases are hardcoded
    if(angle == 0)
        posX+=velocity;
    else if(angle == 90)
        posY-=velocity;
    else if(angle == 180)
        posX-=velocity;
    else if(angle == 270)
        posY+=velocity;
    else
    {
        double velocityX = cos(angle*PI/180.0)*velocity;
        double velocityY = sin(angle*PI/180.0)*velocity;

        //update position
        posX+=velocityX;
        posY-=velocityY;
    }

    std::cout << "velocityLoss: " << velocityLoss << "\n";
    std::cout << "velocity: " << velocity << "\n";
    //std::cout << "velocityX: " << velocityX << "\n";
    //std::cout << "velocityY: " << velocityY << "\n";
}

void Car::accelerate()
{
    acceleration = 2;

    if(velocity < maxVelocity)
        velocity+=acceleration;
}

void Car::decelerate()
{
    acceleration = 1;

    if(velocity > -1*maxBackVelocity)
        velocity-=acceleration;
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

double Car::getPosX()
{
    return posX;
}
double Car::getPosY()
{
    return posY;
}
int Car::getAngle()
{
    return angle;
}

double Car::getVelocity()
{
    return velocity;
}

