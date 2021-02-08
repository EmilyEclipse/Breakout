#pragma once

#include "Rectangle.hpp"

class Texture: public Rectangle{
public:
    Texture();
    Texture(SDL_Texture* i_tex, Sint16 i_x, Sint16 i_y);

    SDL_Texture* getTextureP() const;

private:
    SDL_Texture* tex;
};