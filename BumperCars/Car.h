#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Renderable.h"

class Car : public Renderable
{
public:
    Car();
    Car(int, int);

    double getVelocity();
    double getAcceleration();
    int getDriveState();
    void calcAcceleration();

    void setAngleTravel(double);
    void setVelocity(double, double);
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

    bool collided;

private:
    const int PI = 3.14159265359;

    double rotateSpeed;
    double angleTravel;
    double velocity;
    double velocityX;
    double velocityY;
    double acceleration;

    ///properties
    double maxBackVelocity;
    int maxRotateSpeed;
    int maxHealth;

    ///car state
    int health;
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
    std::string rollGraphic;
    std::string staticGraphic;
    std::string destroyedGraphic;

    ///sound properties
    //TODO
};

#endif // CAR_H_INCLUDED
