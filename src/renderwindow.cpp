#include <SDL2/SDL.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* title, short width, short height)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    
    if(window == NULL)
    {
        std::cerr << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Renderer* RenderWindow::getRenderer()
{
    return RenderWindow::renderer;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}