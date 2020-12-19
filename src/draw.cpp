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
    for(Uint16 row = 0; row < hyper->elements.size(); ++row)
    {
        for(Uint16 col = 0; col < hyper->elements[row].size(); ++col)
        {
            Block *currentBlock_p = &hyper->elements[row][col];
            Draw::rect(currentBlock_p->getRect(), currentBlock_p->red, currentBlock_p->green,
                       currentBlock_p->blue);
            
        }
    }
}

void Draw::setRenderer(SDL_Renderer* inputRenderer)
{
    Draw::renderer = inputRenderer;
}