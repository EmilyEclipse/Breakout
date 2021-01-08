#ifndef DRAW_HPP
#define DRAW_HPP

#include <SDL2/SDL.h>

#include "HyperBlock.hpp"

class Draw 
{
public:
    static void rect(SDL_Rect* rectangle, const Uint8 red,
        const Uint8 green, const Uint8 blue);
    static void hyperBlock(const HyperBlock* hyper);
    static void line(const Line line, const Uint8 red,
        const Uint8 green, const Uint8 blue); 
    static void setRenderer(SDL_Renderer* renderer);
private:
    static SDL_Renderer *renderer;
};

#endif //DRAW_HPP