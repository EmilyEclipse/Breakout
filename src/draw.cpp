#include <SDL2/SDL.h>

#include "Draw.hpp"

SDL_Renderer* Draw::renderer;

void Draw::rect(SDL_Rect* rectangle, const Uint8 red, const Uint8 green,
    const Uint8 blue)
{
    SDL_SetRenderDrawColor(Draw::renderer, red, green, blue, 255);

    SDL_RenderFillRect(Draw::renderer, rectangle);
}

void Draw::hyperBlock(const HyperBlock* hyper)
{
    for(auto row : hyper->elements)
        for(auto block : row)
            Draw::rect(block.getRect(), block.red, block.green, block.blue);
}

void Draw::line(const Line line, const Uint8 red,
        const Uint8 green, const Uint8 blue)
{
    SDL_SetRenderDrawColor(Draw::renderer, red, green, blue, 255);
    
    SDL_RenderDrawLine(Draw::renderer, line.first.x, line.first.y,
        line.second.x, line.second.y);
}

void Draw::setRenderer(SDL_Renderer* inputRenderer)
{
    Draw::renderer = inputRenderer;
}