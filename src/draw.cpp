#include <SDL2/SDL.h>

#include "Draw.hpp"

#include "HyperBlock.hpp"

SDL_Renderer* Draw::renderer;

void Draw::draw(const Rectangle& rectangle)
{
    draw(rectangle.getRect(), rectangle.getRed(),
    rectangle.getGreen(), rectangle.getBlue());
}

void Draw::draw(const SDL_Rect* rectangle, const Uint8 red, const Uint8 green,
    const Uint8 blue)
{
    SDL_SetRenderDrawColor(Draw::renderer, red, green, blue, 255);

    SDL_RenderFillRect(Draw::renderer, rectangle);
}

// void Draw::draw(const HyperBlock* hyper)
// {
//     for(auto row : hyper->elements)
//         for(auto block : row)
//             Draw::draw(block.getRect(),
//                         block.getRed(), block.getGreen(), block.getBlue());
// }

void Draw::draw(const Line line, const Uint8 red,
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