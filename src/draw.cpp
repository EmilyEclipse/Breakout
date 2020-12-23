#include <SDL2/SDL.h>

#include "Draw.hpp"

SDL_Renderer* Draw::renderer;

void Draw::rect(const SDL_Rect* rectangle, short red, short green, short blue)
{
    SDL_SetRenderDrawColor(Draw::renderer, red, green, blue, 255);

    SDL_RenderFillRect(Draw::renderer, rectangle);
}

void Draw::hyperBlock(HyperBlock* hyper)
{
    for(auto row : hyper->elements)
        for(auto block : row)
            Draw::rect(block.getRect(), block.red, block.green, block.blue);
}

void Draw::setRenderer(SDL_Renderer* inputRenderer)
{
    Draw::renderer = inputRenderer;
}