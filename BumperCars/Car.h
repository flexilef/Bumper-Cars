#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Renderable.h"

class Car : public Renderable
{
public:
    Car();
    Car(int, int);

    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    ///accessors
    double getVelocity();
    double getAcceleration();
    int getTravelAngle();
    int getDriveState();
    int getMass();

    ///mutators
    void setVelocity(double);
    void setVelocity(double, double);
    void setAcceleration(double);
    void setDriveState(int);
    void setMass(int);
    void setTravelAngle(int);

    ///actions
    void update();
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
    //sf::Vector2f velocity;
    //sf::Vector2f acceleration;

    ///properties
    double maxBackVelocity;
    int maxRotateSpeed;

    ///car state
    int driveState;

    ///Driving forces and angles
    sf::Vector2f forceTraction;
    sf::Vector2f forceDrag;
    sf::Vector2f forceRollingResistance;
    sf::Vector2f forceBreak;
    sf::Vector2f forceLongitudinal;
    int travelAngle;
    sf::Vector2f travelDirVector;
    sf::Vector2f facingDirVector;

    const double ENGINE_FORCE = 200;
    const double BREAK = 300;
    const double ROLL_RESISTANCE = 15;
    const double DRAG = .5;
    int mass;

    ///image properties
    std::string rollGraphic;
    std::string staticGraphic;
    std::string destroyedGraphic;

    ///sound properties
    //TODO
};

#endif // CAR_H_INCLUDED
