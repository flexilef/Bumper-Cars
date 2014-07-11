#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <SFML/Graphics.hpp>

class Car
{
public:
    Car();
    Car(int, int);

    int getPosX();
    int getPosY();
    int getAngle();
    int getCurrentState();

    void setPosition(int, int);
    void setAngle(int);
    void setVelocity(int);
    void setAcceleration(int);

    void setHealth(int);

    ///actions
    void drive();
    void accelerate();
    void turnRight();
    void turnLeft();
    void decelerate();
    int draw(sf::RenderWindow*);
    void sync();

private:

    const int PI = 3.14159265359;
    ///positional
    int posX;
    int posY;
    int angle;
    int velocity;
    int acceleration;

    ///properties
    int maxSpeed;
    int maxBackThrust;
    int rotateSpeed;
    int maxHealth;
    int mass;

    ///car state
    int health;
    int currentState;   //standing still, rolling, dead... etc

    ///image properties
    std::string currentGraphic;
    std::string rollGraphic;
    std::string staticGraphic;
    std::string destroyedGraphic;

    sf::Sprite currentSprite;

    ///sound properties
    //TODO
};

#endif // CAR_H_INCLUDED
