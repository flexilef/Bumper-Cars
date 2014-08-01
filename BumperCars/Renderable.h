#ifndef RENDERABLE_H_INCLUDED
#define RENDERABLE_H_INCLUDED

#include <SFML/Graphics.hpp>

class Renderable
{
public:
    Renderable();

    //object info
    double getPosX();
    double getPosY();
    double getAngle();
    void setPosition(double, double);
    void setAngle(double);

    //sprite sheet info
    int getRow();
    int getColumn();
    int getSpriteWidth();
    int getSpriteHeight();

    //graphic info
    std::string getCurrentGraphic();
    sf::Sprite& getCurrentSprite();

protected:
    //object info
    double posX;
    double posY;
    double angle;

    //sprite sheet info
    int row;
    int column;
    double anglePerRow;
    double anglePerSprite;
    double spriteWidth;
    double spriteHeight;

    //graphics
    std::string currentGraphic;
    sf::Sprite currentSprite;

};
#endif // RENDERABLE_H_INCLUDED
