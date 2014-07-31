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
    rotateSpeed = 2;

    ///properties
    maxBackVelocity = -5;
    maxRotateSpeed = 5;
    maxHealth = 100;
    mass = 500;

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
    rotateSpeed = 2;

    ///properties
    maxBackVelocity = -5;
    maxRotateSpeed = 5;
    maxHealth = 100;
    mass = 1500;

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

//calculates the forces and shit
void Car::calcAcceleration()
{
    if(driveState == 0)             //not accelerating
    {
        forceTraction = 0;

        //calculating the forces
        forceDrag = -DRAG * velocity * velocity;
        forceRollingResistance = -ROLL_RESISTANCE * velocity;
        forceLongitudinal = forceTraction + forceDrag + forceRollingResistance;
    }
    else if(driveState == 1)         //accelerating
    {
        forceTraction = ENGINE_FORCE;

        //calculating the forces
        forceDrag = -DRAG * velocity * velocity;
        forceRollingResistance = -ROLL_RESISTANCE * velocity;
        forceLongitudinal = forceTraction + forceDrag + forceRollingResistance;
    }
    else if(driveState == 2)    //reverse
    {
        forceTraction = -ENGINE_FORCE;

        //calculating the forces
        forceDrag = -DRAG * velocity * velocity;
        forceRollingResistance = -ROLL_RESISTANCE * velocity;
        forceLongitudinal = forceTraction + forceDrag + forceRollingResistance;
    }
    else if(driveState == 3)    //break
    {
        forceBreak = -BREAK;

        //calculating the forces
        forceDrag = -DRAG * velocity * velocity;
        forceRollingResistance = -ROLL_RESISTANCE * velocity;
        forceLongitudinal = forceBreak + forceDrag + forceRollingResistance;
    }

    acceleration = forceLongitudinal/mass;
}

//constantly driving
void Car::drive()
{
    calcAcceleration();

    //TODO: fix break when going backwards, forwards works
    //      fix angle turning and sprite
    if(driveState == 2 && velocity < maxBackVelocity)
    {
        velocity = maxBackVelocity;
    }
    else if(driveState == 3 && velocity < 0)
    {
        velocity = 0;
    }
    else
    {
        velocity+=acceleration;
    }

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

    std::cout << "longitudinal: " << forceLongitudinal << "\n";
    std::cout << "drag: " << forceDrag << "\n";
    std::cout << "rollr: " << forceRollingResistance << "\n";
    std::cout << "tract: " << forceTraction << "\n";
    std::cout << "velocity: " << velocity << "\n";
    std::cout << "acceleration: " << acceleration << "\n";
    std::cout << "driveState: " << driveState << "\n";
}

void Car::setDriveState(int state)
{
    //0 = decelerate
    //1 = accelerating
    //2 = reverse
    //3 = break
    driveState = state;
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

double Car::getAcceleration()
{
    return acceleration;
}

void Car::setVelocity(double v)
{
    velocity = v;
}

int Car::getDriveState()
{
    return driveState;
}

sf::Sprite& Car::getCurrentSprite()
{
    return currentSprite;
}

