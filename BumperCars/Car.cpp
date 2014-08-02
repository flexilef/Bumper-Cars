#include "Car.h"
#include <cmath>
#include <iostream>

Car::Car()
{
    collided = false;
    velocity = 0;
    velocityX = 0;
    velocityY = 0;
    acceleration = 0;
    rotateSpeed = 2;

    ///properties
    maxBackVelocity = -10;
    maxRotateSpeed = 5;
    maxHealth = 100;
    mass = 1500;

    health = maxHealth;

    ///Renderable properties
    posX = 200;
    posY = 200;
    angleTravel = 45;
    angle = 45;
    currentGraphic = "greenCarSS.png";
    anglePerRow = 40;
    anglePerSprite = 5;
    spriteHeight = 76;
    spriteWidth = 76;
    row = angle/anglePerRow;
    column = (angle-(anglePerRow*row)) / anglePerSprite;
}

Car::Car(int x, int y)
{
    velocity = 0;
    velocityX = 0;
    velocityY = 0;
    acceleration = 0;
    rotateSpeed = 2;

    ///properties
    maxBackVelocity = -10;
    maxRotateSpeed = 5;
    maxHealth = 100;
    mass = 1500;

    health = maxHealth;

    ///Renderable properties
    posX = x;
    posY = y;
    angleTravel = 45;
    angle = 60;
    currentGraphic = "greenCarSS.png";
    anglePerRow = 40;
    anglePerSprite = 5;
    spriteHeight = 76;
    spriteWidth = 76;
    row = angle/anglePerRow;
    column = (angle-(anglePerRow*row)) / anglePerSprite;
}

/*
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

    //currentSprite.setTexture(carText);

    //std::cout << "row: " << row << " column: " << column << "\n";

    //IntRect(left,top,width,height)
    currentSprite.setTextureRect(sf::IntRect(column*76, row*76, 76,76));

    ///sync graphic and sprite
    sync();

    _window->draw(currentSprite);

    return 0;
}
*/

//calculates the acceleration based on forces and the current driveState
void Car::calcAcceleration()
{
    //not accelerating
    if(driveState == 0)
    {
        forceTraction = 0;

        //calculating the forces
        forceDrag = -DRAG * velocity * velocity;
        forceRollingResistance = -ROLL_RESISTANCE * velocity;
        forceLongitudinal = forceTraction + forceDrag + forceRollingResistance;
    }
    //accelerating
    else if(driveState == 1)
    {
        forceTraction = ENGINE_FORCE;

        //calculating the forces
        forceDrag = -DRAG * velocity * velocity;
        forceRollingResistance = -ROLL_RESISTANCE * velocity;
        forceLongitudinal = forceTraction + forceDrag + forceRollingResistance;
    }
    //reversing
    else if(driveState == 2)
    {
        forceTraction = -ENGINE_FORCE;

        //calculating the forces
        forceDrag = -DRAG * velocity * velocity;
        forceRollingResistance = -ROLL_RESISTANCE * velocity;
        forceLongitudinal = forceTraction + forceDrag + forceRollingResistance;
    }
    //breaking
    else if(driveState == 3)
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
    }

    acceleration = forceLongitudinal/mass;
}

//constantly driving
void Car::drive()
{
    calcAcceleration();

    //special conditions must be handled here
    //need to limit the velocity when reversing (not auto like forward)
    if(driveState == 2  && velocity < maxBackVelocity)//&& //(acceleration > -.1 && acceleration < 0) )
    {
        velocity = maxBackVelocity;
    }
    //breaking
    else if(driveState == 3)
    {
        if(velocity > -.1 && velocity < .1)
        {
            velocity = 0;
        }
        else
            velocity+=acceleration;

        posX+=cos(angle*PI/180.0)*velocity;
        posY-=sin(angle*PI/180.0)*velocity;
    }
    //no other special case? then deal with velocity normally
    else
    {
        angleTravel = angle;

        std::cout << "DriveState: " << driveState << "\n";
        velocity+=acceleration;
        //}

        //special cases due to angle round off errors are hard-coded instead
        /*if(angle == 0)
            posX+=velocity;
        else if(angle == 90)
            posY-=velocity;
        else if(angle == 180)
            posX-=velocity;
        else if(angle == 270)
            posY+=velocity;
        else
        {*/
        velocityX = cos(angle*PI/180.0)*velocity;
        velocityY = sin(angle*PI/180.0)*velocity;
        //update position
        posX+=velocityX;
        posY-=velocityY;
        //}
    }

    std::cout << "angle: " << angle << "\n";
    std::cout << "x: " << posX << "\n";
    std::cout << "y: " << posY << "\n";
    //std::cout << "angleTravel: " << angleTravel << "\n";
    //std::cout << "AngularV: " << rotateSpeed << "\n";
    //std::cout << "longitudinal: " << forceLongitudinal << "\n";
    //std::cout << "drag: " << forceDrag << "\n";
    //std::cout << "rollr: " << forceRollingResistance << "\n";
    //std::cout << "tract: " << forceTraction << "\n";
    std::cout << "velocity: " << velocity << "\n";
    std::cout << "acceleration: " << acceleration << "\n";
    //std::cout << "driveState: " << driveState << "\n";
}

void Car::setDriveState(int state)
{
    //0 = decelerate
    //1 = accelerating
    //2 = reverse
    //3 = break
    //4 = crash
    driveState = state;
}

void Car::turnRight()
{
    if(angle > 359)
        angle = 0;

    //just felt right. Nothing to do with physics
    rotateSpeed = .5*velocity;

    angle-=rotateSpeed;
    angleTravel = angle;
}

void Car::turnLeft()
{
    if(angle < 0)
        angle = 359;

    //just felt right. Nothing to do with physics
    rotateSpeed = .5*velocity;

    angle+=rotateSpeed;
    angleTravel = angle;
}

double Car::getVelocity()
{
    return velocity;
}

double Car::getAcceleration()
{
    return acceleration;
}

void Car::setAngleTravel(double theta)
{
    angleTravel = theta;
}

void Car::setVelocity(double v)
{
    velocity = v;
}

void Car::setVelocity(double vx, double vy)
{
    velocityX = vx;
    velocityY = vy;
}

int Car::getDriveState()
{
    return driveState;
}
