#include "Car.h"
#include <cmath>
#include <iostream>

Car::Car()
{
    velocity = 0;
    acceleration = 0;
    rotateSpeed = 2;

    ///properties
    maxBackVelocity = -5;
    maxRotateSpeed = 5;
    mass = 1000;

    ///Renderable properties
    position.x = 200;
    position.y = 200;
    renderAngle = 45;
    travelAngle = 45;
    currentGraphic = "greenCarSS.png";
    anglePerRow = 40;
    anglePerSprite = 5;
    spriteHeight = 76;
    spriteWidth = 76;
    row = renderAngle/anglePerRow;
    column = (renderAngle-(anglePerRow*row)) / anglePerSprite;
}

Car::Car(int x, int y)
{
    velocity = 0;
    acceleration = 0;
    rotateSpeed = 2;

    ///properties
    maxBackVelocity = -5;
    maxRotateSpeed = 5;
    mass = 1000;

    ///Renderable properties
    position.x = x;
    position.y = y;
    renderAngle = 0;
    travelAngle = 0;
    currentGraphic = "greenCarSS.png";
    anglePerRow = 40;
    anglePerSprite = 5;
    spriteHeight = 76;
    spriteWidth = 76;
    row = renderAngle/anglePerRow;
    column = (renderAngle-(anglePerRow*row)) / anglePerSprite;
}

void Car::update()
{
    //if we are not accelerating/reversing/braking
    if(driveState != 4 && driveState != 0)
    {
        //move according to where we are facing
        position.x += velocity*cos(renderAngle*PI/180.0);
        position.y -= velocity*sin(renderAngle*PI/180.0);
    }
    else
    {
        position.x += velocity*cos(travelAngle*PI/180.0);
        position.y -= velocity*sin(travelAngle*PI/180.0);
    }
}

void Car::accelerate()
{
    //if(driveState != 4)
    //update driveState
    driveState = 1;

    //need to travel where you're facing
    travelAngle = renderAngle;

    forceTraction = ENGINE_FORCE;

    //calculating the resistance forces
    forceDrag = -DRAG * velocity * velocity;
    forceRollingResistance = -ROLL_RESISTANCE * velocity;
    forceLongitudinal = forceTraction + forceDrag + forceRollingResistance;

    acceleration = forceLongitudinal/mass;
    velocity+=acceleration;

    //only accelerate at renderAngle
    //position.x += velocity*cos(renderAngle*PI/180.0);
    //position.y -= velocity*sin(renderAngle*PI/180.0);
}

void Car::decelerate()
{
    //update driveState
    driveState = 0;

    forceTraction = 0;

    //calculating the resistance forces
    forceDrag = -DRAG * velocity * velocity;
    forceRollingResistance = -ROLL_RESISTANCE * velocity;
    forceLongitudinal = forceTraction + forceDrag + forceRollingResistance;

    acceleration = forceLongitudinal/mass;
    velocity+=acceleration;

    if(velocity < maxBackVelocity)
    {
        velocity = maxBackVelocity;
    }

    //always decelerate where we are heading
    //position.x += velocity*cos(travelAngle*PI/180.0);
    //po1sition.y -= velocity*sin(travelAngle*PI/180.0);
}

void Car::applyBrakes()
{
    //update driveState
    driveState = 3;

    //going forwards
    if(velocity > 0)
    {
        forceBreak = -BREAK;

        //calculating the resistance forces
        forceDrag = -DRAG * velocity * velocity;
        forceRollingResistance = -ROLL_RESISTANCE * velocity;
        forceLongitudinal = forceBreak + forceDrag + forceRollingResistance;
    }
    //going reverse
    else
    {
        forceBreak = BREAK;

        //calculating the resistance forces
        forceDrag = -DRAG * velocity * velocity;
        forceRollingResistance = -ROLL_RESISTANCE * velocity;
        forceLongitudinal = forceBreak + forceDrag + forceRollingResistance;
    }

    acceleration = forceLongitudinal/mass;

    if(velocity > -.1 && velocity < .1)
        velocity = 0;
    else
        velocity+=acceleration;

    //position.x += velocity*cos(renderAngle*PI/180.0);
    //position.y -= velocity*sin(renderAngle*PI/180.0);
}

void Car::applyReverse()
{
    //update driveState
    driveState = 2;

    //need to travel where you're facing
    travelAngle = renderAngle;

    forceTraction = -ENGINE_FORCE;

    //calculating the forces
    forceDrag = -DRAG * velocity * velocity;
    forceRollingResistance = -ROLL_RESISTANCE * velocity;
    forceLongitudinal = forceTraction + forceDrag + forceRollingResistance;

    acceleration = forceLongitudinal/mass;
    velocity+=acceleration;

    //only accelerate in the opposite direction of where we are facing
    //position.x += velocity*cos(renderAngle*PI/180.0);
    //position.y -= velocity*sin(renderAngle*PI/180.0);
}

//constantly driving
void Car::dump()
{
    //std::cout << "angleRender: " << renderAngle << "\n";
    //std::cout << "AngleTravel: " << travelAngle << "\n";
    //std::cout << "longitudinal: " << forceLongitudinal << "\n";
    //std::cout << "drag: " << forceDrag << "\n";
    //std::cout << "rollr: " << forceRollingResistance << "\n";
    //std::cout << "tract: " << forceTraction << "\n";
    //std::cout << "velocity: " << velocity << "\n";
    //std::cout << "acceleration: " << acceleration << "\n";
    //std::cout << "driveState: " << driveState << "\n";
}

void Car::setDriveState(int state)
{
    //0 = decelerate
    //1 = accelerating
    //2 = reverse
    //3 = break
    //4 = collided
    driveState = state;
}

void Car::turnRight()
{
    if(renderAngle > 359)
        renderAngle = 0;

    //just felt right. Nothing to do with physics
    rotateSpeed = .5*velocity;

    renderAngle-=rotateSpeed;

    //moment we turn the travel angle needs to be the same as renderAngle
    travelAngle = renderAngle;
}

void Car::turnLeft()
{
    if(renderAngle < 0)
        renderAngle = 359;

    //just felt right. Nothing to do with physics
    rotateSpeed = .5*velocity;

    renderAngle+=rotateSpeed;

    //moment we turn the travel angle needs to be the same as renderAngle
    travelAngle = renderAngle;
}

double Car::getVelocity()
{
    return velocity;
}

double Car::getAcceleration()
{
    return acceleration;
}

int Car::getMass()
{
    return mass;
}

int Car::getTravelAngle()
{
    return travelAngle;
}

void Car::setVelocity(double v)
{
    velocity = v;
}

void Car::setTravelAngle(int theta)
{
    travelAngle = theta;
}

int Car::getDriveState()
{
    return driveState;
}
