#include "Texture.hpp"

Texture::Texture(){}

Texture::Texture(SDL_Texture* i_tex, Sint16 i_x, Sint16 i_y)
{
    this->tex = i_tex;
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    this->setRectX(i_x);
    this->setRectY(i_y);
    this->setRectW(w);
    this->setRectH(h);
}

SDL_Texture* Texture::getTextureP() const
{
    return tex;
}