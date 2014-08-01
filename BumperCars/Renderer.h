#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Renderable.h"

class Renderer
{
public:
    Renderer(sf::RenderWindow*);
    void loadAssets();
    void render(Renderable&);
    int loadImage(const std::string&);
    void loadObject(Renderable&);
    bool alreadyLoaded(Renderable&);

private:
    std::map<std::string, sf::Texture> imageToTexture;
    sf::RenderWindow* windowPtr;
};
#endif // RENDERER_H_INCLUDED
