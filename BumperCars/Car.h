#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Renderable.h"

class Car : public Renderable
{
public:
    Car();
    Car(int, int);

    ///accessors
    double getVelocity();
    double getAcceleration();
    int getDriveState();

    ///mutators
    void setVelocity(double);
    void setAcceleration(double);
    void setDriveState(int);

    ///actions
    void accelerate();
    void decelerate();
    void applyBrakes();
    void applyReverse();
    void turnRight();
    void turnLeft();

    ///rendering
    int draw(sf::RenderWindow*);
    void sync();

    ///debugging
    void dump();

private:

    const int PI = 3.14159265359;

    double rotateSpeed;
    double velocity;
    double acceleration;

    ///properties
    double maxBackVelocity;
    int maxRotateSpeed;

    ///car state
    int driveState;

    ///Driving forces and angles
    double forceTraction;
    double forceDrag;
    double forceRollingResistance;
    double forceBreak;
    double forceLongitudinal;
    int travelAngle;
    sf::Vector2f travelDirVector;
    sf::Vector2f facingDirVector;

    const double ENGINE_FORCE = 150;
    const double BREAK = 300;
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
