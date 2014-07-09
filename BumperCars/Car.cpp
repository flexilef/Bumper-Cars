#include "Car.h"

Car::Car()
{
    ///position
    posX = 0;
    posY = 0;
    angle = 0;
    velocity = 0;
    acceleration = 0;

    ///properties
    maxSpeed = 50;
    maxBackThrust = 50;
    rotateSpeed = 1;
    maxHealth = 100;
    mass = 10;

    health = maxHealth;
    currentState = 1;

    ///image properties
    currentGraphic = "greenCar.png";
    rollGraphic = "greenCar.png";
    staticGraphic = "greenCar.png";
    destroyedGraphic = "greenCar.png";
}

Car::Car(int x, int y)
{
    posX = x;
    posY = y;
    angle = 45;
    velocity = 0;
    acceleration = 0;

    ///properties
    maxSpeed = 50;
    maxBackThrust = 50;
    rotateSpeed = 1;
    maxHealth = 100;
    mass = 10;

    health = maxHealth;
    currentState = 1;

    ///image properties
    currentGraphic = "greenCar.png";
    rollGraphic = "greenCar.png";
    staticGraphic = "greenCar.png";
    destroyedGraphic = "greenCar.png";
}

int Car::draw(sf::RenderWindow* _window)
{
    sf::Texture carText;

    if(!carText.loadFromFile("assets/images/" + currentGraphic))
        return EXIT_FAILURE;

    currentSprite.setTexture(carText);

    ///sync graphic and sprite
    sync();

    _window->draw(currentSprite);

    return 0;
}

//syncs the sprite graphic with the actual object
void Car::sync()
{
    currentSprite.setPosition(posX,posY);
    currentSprite.setRotation(angle);
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
