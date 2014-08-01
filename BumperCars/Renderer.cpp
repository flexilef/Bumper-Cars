#include "Renderer.h"
#include <iostream>

Renderer::Renderer(sf::RenderWindow* window)
{
    windowPtr = window;
}

//loads a sprite and puts it into the texture to filename map
//returns -1 when imageToTexture contains a duplicate and
//when failed to load texture from file
int Renderer::loadImage(const std::string& filename)
{
    bool duplicate = false;

    //check for if empty first
    if(!imageToTexture.empty())
    {
        for(int i=0; i<imageToTexture.size(); i++)
        {
            //check for duplicate filename key. If duplicate don't load
            if(imageToTexture.count(filename))
            {
                duplicate = true;
                return -1;      //not loaded because already loaded
            }
        }
    }

    if(duplicate == false)
    {
        sf::Texture texture;
        //load the file
        if(!texture.loadFromFile("assets/images/" + filename))
            return 1;   //loaded

        //add to the map
        imageToTexture.insert(std::pair<std::string, sf::Texture>(filename, texture));
    }

    //not loaded unknown reason
    return 0;
}

void Renderer::render(Renderable& obj)
{
    std::string filename = obj.getCurrentGraphic();
    double posX = obj.getPosX();
    double posY = obj.getPosY();

    //sets the row and column of sprite sheet AND sets the sprite to the obj's position
    obj.sync();

    int row = obj.getRow();
    int column = obj.getColumn();
    double angle = obj.getAngle();
    int spriteWidth = obj.getSpriteWidth();
    int spriteHeight = obj.getSpriteHeight();

    std::cout << "row: " << row << "\n";
    std::cout << "column: " << column << "\n";

    if(!alreadyLoaded(obj))
        loadImage(filename);

    if(angle > 359)
        obj.setAngle(0);
    else if(angle < 0)
        obj.setAngle(359);

    obj.getCurrentSprite().setTexture(imageToTexture[filename]);
    obj.getCurrentSprite().setTextureRect(sf::IntRect(column*spriteWidth, row*spriteHeight, spriteWidth,spriteHeight));

    //draw it
    windowPtr->draw(obj.getCurrentSprite());
}

bool Renderer::alreadyLoaded(Renderable& obj)
{
    std::string filename = obj.getCurrentGraphic();
    if(imageToTexture.count(filename))
    {
        return true;
    }

    return false;
}
