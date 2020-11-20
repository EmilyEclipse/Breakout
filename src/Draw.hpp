#ifndef DRAW_HPP
#define DRAW_HPP

#include <SDL2/SDL.h>

class Draw 
{
public:
    static void rect(const SDL_Rect* rectangle, short red, short green, short blue);
    static void setRenderer(SDL_Renderer* renderer);
private:
    static SDL_Renderer *renderer;
};

#endif //DRAW_HPP