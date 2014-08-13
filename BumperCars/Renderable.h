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
    double getRenderAngle();
    void setPosition(double, double);
    void setRenderAngle(double);

    //sprite sheet info
    int getRow();
    int getColumn();
    int getSpriteWidth();
    int getSpriteHeight();
    void sync();

    //graphic info
    std::string getCurrentGraphic();
    sf::Sprite& getCurrentSprite();

protected:
    //object info
    sf::Vector2f position;
    int renderAngle;

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
