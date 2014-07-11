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
    acceleration = 1;

    ///properties
    maxSpeed = 3;
    maxBackThrust = 50;
    rotateSpeed = 5;
    maxHealth = 100;
    mass = 10;

    health = maxHealth;
    currentState = 1;

    ///image properties
    currentGraphic = "carSS.png";

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
    acceleration = 1;

    ///properties
    maxSpeed = 3;
    maxBackThrust = 50;
    rotateSpeed = 5;
    maxHealth = 100;
    mass = 10;

    health = maxHealth;
    currentState = 1;

    ///image properties
    currentGraphic = "carSS.png";

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

    std::cout << "row: " << row << " column: " << column << "\n";

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

void Car::accelerate()
{
    if(acceleration < 3)
        acceleration++;

    if(velocity < maxSpeed)
        velocity+=acceleration;

    posX+=velocity*cos(angle*PI/180);
    posY+=velocity*sin(angle*PI/180);
}

void Car::decelerate()
{
    acceleration--;

    if(acceleration < 0)
    {
        acceleration = 0;
    }
}

void Car::turnRight()
{
    if(angle > 359)
        angle = 0;

    angle+=rotateSpeed;
}

void Car::turnLeft()
{
    if(angle < 0)
        angle = 359;

    angle-=rotateSpeed;
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
