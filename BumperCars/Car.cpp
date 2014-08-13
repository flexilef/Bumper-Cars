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

void Car::accelerate()
{
    forceTraction = ENGINE_FORCE;

    //calculating the forces
    forceDrag = -DRAG * velocity * velocity;
    forceRollingResistance = -ROLL_RESISTANCE * velocity;
    forceLongitudinal = forceTraction + forceDrag + forceRollingResistance;

    acceleration = forceLongitudinal/mass;
    velocity+=acceleration;

    position.x += velocity*cos(renderAngle*PI/180.0);
    position.y -= velocity*sin(renderAngle*PI/180.0);
}

void Car::decelerate()
{
    forceTraction = 0;

    //calculating the forces
    forceDrag = -DRAG * velocity * velocity;
    forceRollingResistance = -ROLL_RESISTANCE * velocity;
    forceLongitudinal = forceTraction + forceDrag + forceRollingResistance;

    acceleration = forceLongitudinal/mass;
    velocity+=acceleration;

    if(velocity < maxBackVelocity)
    {
        velocity = maxBackVelocity;
    }

    position.x += velocity*cos(travelAngle*PI/180.0);
    position.y -= velocity*sin(travelAngle*PI/180.0);
}

void Car::applyBrakes()
{
    //going forwards
    if(velocity > 0)
    {
        forceBreak = -BREAK;

        //calculating the forces
        forceDrag = -DRAG * velocity * velocity;
        forceRollingResistance = -ROLL_RESISTANCE * velocity;
        forceLongitudinal = forceBreak + forceDrag + forceRollingResistance;
    }
    //going reverse
    else
    {
        forceBreak = BREAK;

        //calculating the forces
        forceDrag = -DRAG * velocity * velocity;
        forceRollingResistance = -ROLL_RESISTANCE * velocity;
        forceLongitudinal = forceBreak + forceDrag + forceRollingResistance;
    }

    acceleration = forceLongitudinal/mass;

    if(velocity > -.1 && velocity < .1)
    {
        velocity = 0;
    }
    else
        velocity+=acceleration;

    position.x += velocity*cos(renderAngle*PI/180.0);
    position.y -= velocity*sin(renderAngle*PI/180.0);
}

void Car::applyReverse()
{
    forceTraction = -ENGINE_FORCE;

    //calculating the forces
    forceDrag = -DRAG * velocity * velocity;
    forceRollingResistance = -ROLL_RESISTANCE * velocity;
    forceLongitudinal = forceTraction + forceDrag + forceRollingResistance;

    acceleration = forceLongitudinal/mass;
    velocity+=acceleration;

    position.x += velocity*cos(renderAngle*PI/180.0);
    position.y -= velocity*sin(renderAngle*PI/180.0);
}

//constantly driving
void Car::dump()
{
    //std::cout << "angle: " << angle << "\n";
    //std::cout << "AngularV: " << rotateSpeed << "\n";
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
    driveState = state;
}

void Car::turnRight()
{
    if(renderAngle > 359)
        renderAngle = 0;

    //just felt right. Nothing to do with physics
    rotateSpeed = .5*velocity;

    renderAngle-=rotateSpeed;
    travelAngle = renderAngle;
}

void Car::turnLeft()
{
    if(renderAngle < 0)
        renderAngle = 359;

    //just felt right. Nothing to do with physics
    rotateSpeed = .5*velocity;

    renderAngle+=rotateSpeed;
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

void Car::setVelocity(double v)
{
    velocity = v;
}

int Car::getDriveState()
{
    return driveState;
}
