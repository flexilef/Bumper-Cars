#include "Renderable.h"

Renderable::Renderable()
{

}

std::string Renderable::getCurrentGraphic()
{
    return currentGraphic;
}

sf::Sprite& Renderable::getCurrentSprite()
{
    return currentSprite;
}

double Renderable::getPosX()
{
    return posX;
}
double Renderable::getPosY()
{
    return posY;
}
double Renderable::getAngle()
{
    return angle;
}
int Renderable::getRow()
{
    return row;
}
int Renderable::getColumn()
{
    return column;
}
int Renderable::getSpriteHeight()
{
    return spriteHeight;
}
int Renderable::getSpriteWidth()
{
    return spriteWidth;
}

void Renderable::setPosition(double x, double y)
{
    posX = x;
    posY = y;
}
void Renderable::setAngle(double theta)
{
    angle = theta;
}
