#include <SDL2/SDL.h>

#include "Draw.hpp"

SDL_Renderer* Draw::renderer;

void Draw::rect(const SDL_Rect* rectangle, short red, short green, short blue)
{
    SDL_SetRenderDrawColor(Draw::renderer, red, green, blue, 255);

    SDL_RenderFillRect(Draw::renderer, rectangle);
}

void Draw::setRenderer(SDL_Renderer* inputRenderer)
{
    Draw::renderer = inputRenderer;
}