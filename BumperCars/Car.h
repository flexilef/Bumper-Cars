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
    double getAcceleration();
    int getCurrentState();
    int getDriveState();
    void calcAcceleration();

    //
    sf::Sprite& getCurrentSprite();

    void setPosition(double, double);
    void setAngle(int);
    void setVelocity(double);
    void setAcceleration(double);
    void setHealth(int);
    void setDriveState(int);

    ///actions
    void drive();
    void turnRight();
    void turnLeft();
    int draw(sf::RenderWindow*);
    void sync();

private:

    const int PI = 3.14159265359;

    ///positional
    double posX;
    double posY;
    int angle;
    double rotateSpeed;
    double velocity;
    double acceleration;

    ///properties
    double maxBackVelocity;
    int maxRotateSpeed;
    int maxHealth;

    ///car state
    int health;
    int currentState;   //standing still, rolling, dead... etc
    int driveState;

    ///Driving forces and stuff
    double forceTraction;
    double forceDrag;
    double forceRollingResistance;
    double forceBreak;
    double forceLongitudinal;

    const double ENGINE_FORCE = 150;
    const double BREAK = 80;
    const double ROLL_RESISTANCE = 12.8;
    const double DRAG = 0.4257;
    int mass;

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
