#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <SFML/Graphics.hpp>

class Car
{
public:
    Car();
    Car(int, int);

    double getPosX();
    double getPosY();
    int getAngle();
    double getVelocity();
    int getCurrentState();
    sf::Sprite& getCurrentSprite();

    void setPosition(double, double);
    void setAngle(int);
    void setVelocity(double);
    void setAcceleration(double);

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
    double posX;
    double posY;
    int angle;
    int rotateSpeed;
    double velocity;
    double acceleration;

    ///properties
    double maxVelocity;
    double maxBackVelocity;
    int maxRotateSpeed;
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
