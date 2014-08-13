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
    return position.x;
}
double Renderable::getPosY()
{
    return position.y;
}
double Renderable::getRenderAngle()
{
    return renderAngle;
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
    position.x = x;
    position.y = y;
}
void Renderable::setRenderAngle(double theta)
{
    renderAngle = theta;
}

void Renderable::sync()
{
    row = renderAngle/anglePerRow;
    column = (renderAngle-(anglePerRow*row)) / anglePerSprite;
    currentSprite.setPosition(position.x,position.y);
}
