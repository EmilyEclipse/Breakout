#ifndef DRAW_HPP
#define DRAW_HPP

#include <SDL2/SDL.h>

#include "Rectangle.hpp"
#include "Line.hpp"

class Draw
{
public:
    static void draw(const Rectangle& rectangle);

    static void draw(const SDL_Rect* rectangle, const Uint8 red,
        const Uint8 green, const Uint8 blue);
    //static void draw(const HyperBlock* hyper);
    static void draw(const Line line, const Uint8 red,
        const Uint8 green, const Uint8 blue);
    
    static void draw(const Sint16 number, const Uint8 red,
        const Uint8 green, const Uint8 blue);

    static void setRenderer(SDL_Renderer* renderer);
private:
    static SDL_Renderer *renderer;
};

#endif //DRAW_HPP