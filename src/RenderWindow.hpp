#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include <SDL2/SDL.h>

class RenderWindow 
{
public:
    //CONSTRUCTORS
    RenderWindow(const char* title, short width, short height);
    void cleanUp();
    SDL_Renderer* getRenderer();
    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif //RENDERWINOW_HPP