#include "Car.h"
#include <cmath>
#include <iostream>

Car::Car()
{
    driveState = 1;
    velocity.x = 0;
    velocity.y = 0;
    acceleration.x = 0;
    acceleration.y = 0;
    rotateSpeed = 2;

    ///properties
    maxBackVelocity = 5;
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
    driveState = 1;
    velocity.x = 0;
    velocity.y = 0;
    acceleration.x = 0;
    acceleration.y = 0;
    rotateSpeed = 2;

    ///properties
    maxBackVelocity = 5;
    maxRotateSpeed = 5;
    mass = 1000;

    ///Renderable properties
    position.x = x;
    position.y = y;
    renderAngle = 180;
    travelAngle = 180;
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
    position.x += velocity.x;
    position.y -= velocity.y;
}

void Car::decelerate()
{
    //update driveState
    driveState = 0;

    double speed = getVelocity();

    //our velocity unit vector
    sf::Vector2f unit(cos(travelAngle*PI/180.0), sin(travelAngle*PI/180.0));

    double velX = speed*unit.x;//cos(travelAngle*PI/180.0);
    double velY = speed*unit.y;//sin(travelAngle*PI/180.0);

    setVelocity(velX, velY);

    //calculating the resistance forces
    forceDrag.x = -DRAG * velocity.x * speed;
    forceRollingResistance.x = -ROLL_RESISTANCE * velocity.x;
    forceLongitudinal.x = forceDrag.x + forceRollingResistance.x;

    forceDrag.y = -DRAG * velocity.y * speed;
    forceRollingResistance.y = -ROLL_RESISTANCE * velocity.y;
    forceLongitudinal.y = forceDrag.y + forceRollingResistance.y;

    acceleration.x = forceLongitudinal.x/mass;
    acceleration.y = forceLongitudinal.y/mass;

    velocity.x+=acceleration.x;
    velocity.y+=acceleration.y;

    /*if(getVelocity() < maxBackVelocity)
    {
        velocity.x = maxBackVelocity*cos(travelAngle*PI/180);
        velocity.y = maxBackVelocity*sin(travelAngle*PI/180);
    }*/

    //always decelerate where we are heading
    //position.x += velocity*cos(travelAngle*PI/180.0);
    //po1sition.y -= velocity*sin(travelAngle*PI/180.0);
}

void Car::accelerate()
{
    //update driveState
    driveState = 1;

    //need to travel where you're facing
    travelAngle = renderAngle;

    double speed = getVelocity();

    //our velocity unit vector
    sf::Vector2f unit(cos(travelAngle*PI/180.0), sin(travelAngle*PI/180.0));

    double velX = speed*unit.x;//cos(travelAngle*PI/180.0);
    double velY = speed*unit.y;//sin(travelAngle*PI/180.0);

    setVelocity(velX, velY);

    forceTraction.x = ENGINE_FORCE*unit.x;//cos(renderAngle*PI/180.0);
    forceTraction.y = ENGINE_FORCE*unit.y;//sin(renderAngle*PI/180.0);

    //calculating the resistance forces
    forceDrag.x = -DRAG * velocity.x * speed;
    forceRollingResistance.x = -ROLL_RESISTANCE * velocity.x;
    forceLongitudinal.x = forceTraction.x + forceDrag.x + forceRollingResistance.x;

    forceDrag.y = -DRAG * velocity.y * speed;
    forceRollingResistance.y = -ROLL_RESISTANCE * velocity.y;
    forceLongitudinal.y = forceTraction.y + forceDrag.y + forceRollingResistance.y;

    acceleration.x = forceLongitudinal.x/mass;
    acceleration.y = forceLongitudinal.y/mass;

    velocity.x+=acceleration.x;
    velocity.y+=acceleration.y;

    //only accelerate at renderAngle
    //position.x += velocity*cos(renderAngle*PI/180.0);
    //position.y -= velocity*sin(renderAngle*PI/180.0);
}

void Car::applyReverse()
{
    //update driveState
    driveState = 2;

    //need to travel 180 degrees from where we're facing
    travelAngle = renderAngle+180;

    double speed = getVelocity();

    //our velocity unit vector
    sf::Vector2f unit(cos(travelAngle*PI/180.0), sin(travelAngle*PI/180.0));

    double velX = speed*unit.x;//cos(travelAngle*PI/180.0);
    double velY = speed*unit.y;//sin(travelAngle*PI/180.0);

    setVelocity(velX, velY);

    forceTraction.x = ENGINE_FORCE*unit.x;
    forceTraction.y = ENGINE_FORCE*unit.y;

    //calculating the resistance forces
    forceDrag.x = -DRAG * velocity.x * speed;
    forceRollingResistance.x = -ROLL_RESISTANCE * velocity.x;
    forceLongitudinal.x = forceTraction.x + forceDrag.x + forceRollingResistance.x;

    forceDrag.y = -DRAG * velocity.y * speed;
    forceRollingResistance.y = -ROLL_RESISTANCE * velocity.y;
    forceLongitudinal.y = forceTraction.y + forceDrag.y + forceRollingResistance.y;

    acceleration.x = forceLongitudinal.x/mass;
    acceleration.y = forceLongitudinal.y/mass;

    velocity.x+=acceleration.x;
    velocity.y+=acceleration.y;
}

void Car::applyBrakes()
{
    //update driveState
    driveState = 3;

    double speed = getVelocity();

    //going forwards
    if(speed > 0)
    {
        forceBreak.x = -BREAK;
        forceBreak.y = -BREAK;

        //calculating the resistance forces
        forceDrag.x = -DRAG * velocity.x * speed;
        forceRollingResistance.x = -ROLL_RESISTANCE * velocity.x;
        forceLongitudinal.x = forceBreak.x + forceDrag.x + forceRollingResistance.x;

        forceDrag.y = -DRAG * velocity.y * speed;
        forceRollingResistance.y = -ROLL_RESISTANCE * velocity.y;
        forceLongitudinal.y = forceBreak.y + forceDrag.y + forceRollingResistance.y;
    }
    //going reverse
    else
    {
        forceBreak.x = BREAK;
        forceBreak.y = BREAK;

        //calculating the resistance forces
        forceDrag.x = -DRAG * velocity.x * velocity.x;
        forceRollingResistance.x = -ROLL_RESISTANCE * velocity.x;
        forceLongitudinal.x = forceBreak.x + forceDrag.x + forceRollingResistance.x;

        forceDrag.y = -DRAG * velocity.y * velocity.y;
        forceRollingResistance.y = -ROLL_RESISTANCE * velocity.y;
        forceLongitudinal.y = forceBreak.y + forceDrag.y + forceRollingResistance.y;
    }

    acceleration.x = forceLongitudinal.x/mass;
    acceleration.y = forceLongitudinal.y/mass;

    if(getVelocity() > -.1 && getVelocity() < .1)
        setVelocity(0, 5);
    else
    {
        velocity.x+=acceleration.x;
        velocity.y+=acceleration.y;
    }

    //position.x += velocity*cos(renderAngle*PI/180.0);
    //position.y -= velocity*sin(renderAngle*PI/180.0);
}

//constantly driving
void Car::dump()
{
    std::cout << "angleRender: " << renderAngle << "\n";
    std::cout << "AngleTravel: " << travelAngle << "\n";
    //std::cout << "longitudinal: " << forceLongitudinal << "\n";
    //std::cout << "drag: " << forceDrag << "\n";
    //std::cout << "rollr: " << forceRollingResistance << "\n";
    //std::cout << "tract: " << forceTraction << "\n";
    std::cout << "velocity: " << getVelocity() << "\n";
    std::cout << "velocityX: " << velocity.x << "\n";
    std::cout << "velocityY: " << velocity.y << "\n";

    std::cout << "acceleration: " << getAcceleration() << "\n";
    std::cout << "driveState: " << driveState << "\n";
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
    double vel = getVelocity();

    if(renderAngle > 359)
        renderAngle = 0;

    //just felt right. Nothing to do with physics
    rotateSpeed = .5*vel;

    renderAngle-=rotateSpeed;

    //moment we turn the travel angle needs to be the same as renderAngle
    //travelAngle = renderAngle;
}

void Car::turnLeft()
{
    double vel = getVelocity();

    if(renderAngle < 0)
        renderAngle = 359;

    //just felt right. Nothing to do with physics
    rotateSpeed = .5*vel;

    renderAngle+=rotateSpeed;

    //moment we turn the travel angle needs to be the same as renderAngle
    //travelAngle = renderAngle;
}

double Car::getVelocity()
{
    return sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
}

double Car::getAcceleration()
{
    return sqrt(acceleration.x*acceleration.x + acceleration.y*acceleration.y);
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
    velocity.x = v*cos(renderAngle*PI/180);
    velocity.y = v*sin(renderAngle*PI/180);
}

void Car::setVelocity(double vx, double vy)
{
    velocity.x = vx;
    velocity.y = vy;
}

void Car::setTravelAngle(int theta)
{
    travelAngle = theta;
}

int Car::getDriveState()
{
    return driveState;
}
