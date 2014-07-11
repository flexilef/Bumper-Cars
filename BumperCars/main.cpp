#include <iostream>
#include <SFML/Graphics.hpp>

#include "Car.h"

using namespace std;

int main()
{
    sf::RenderWindow _window;
    _window.create(sf::VideoMode(400, 400), "Bumper Cars!");

    Car theCar(200, 100);

    while(_window.isOpen())
    {
        sf::Event event;
        while(_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                _window.close();
            }
        }
        _window.clear();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            theCar.accelerate();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            theCar.decelerate();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            theCar.turnRight();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            theCar.turnLeft();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            cout << "Angle: " << theCar.getAngle() << "\n";
            cout << "x: " << theCar.getPosX() << "\n";
            cout << "y: " << theCar.getPosY() << "\n";
        }

        theCar.draw(&_window);
        _window.display();
    }

    return 0;
}
