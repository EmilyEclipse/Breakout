#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>

#include "Draw.hpp"
#include "RenderWindow.hpp"
#include "Rectangle.hpp"

void safeSleep(const std::chrono::duration<int, std::milli>& timeFrameTookToRun,
                const std::chrono::duration<int, std::milli>& interval)
{
    int timeToSkip = (interval - timeFrameTookToRun).count();
    if(timeToSkip > 0)
    {
        SDL_Delay(timeToSkip);
    }
}

int main(int argc, char const *argv[])
{
    const char* title = "BREAKOUT v0.1";
    short windowWidth = 1920;
    short windowHeight = 1080;
    const unsigned short FPS = 60;
    //expected time between frames(if computer is fast enough)
    const std::chrono::milliseconds interval = static_cast<std::chrono::milliseconds>(1000 / FPS);

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        std::cerr << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    RenderWindow window(title, windowWidth, windowHeight);

    const bool variableFPS = false;
    bool gameRunning = true;
    SDL_Event event;


    
    Rectangle ball(windowWidth / 2, windowHeight / 2, 300, 300);
    Draw::setRenderer(window.getRenderer());

    //MAIN GAME LOOPS
    if(variableFPS)
    {

    } else 
    {
        while(gameRunning)
        {
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

            SDL_SetRenderDrawColor(window.getRenderer(), 100, 100, 100, 255);
            SDL_RenderClear(window.getRenderer());

            Draw::rect(ball.getRect(), 255, 255, 255);
            SDL_RenderPresent(window.getRenderer());
            
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                case SDL_QUIT:
                    gameRunning = false;
                    break;
            
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_UP:
                    case SDLK_w: 
                        ball.moveY(-5);
                        break;
                    
                    case SDLK_s:
                    case SDLK_DOWN:
                        ball.moveY(5);
                        break;

                    case SDLK_a:
                    case SDLK_LEFT:
                        ball.moveX(-5);
                        break;

                    case SDLK_d:
                    case SDLK_RIGHT:
                        ball.moveX(5);
                    }
                    break; 
                }
            }


            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<int, std::milli> timeFrameTookToRun = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(end - start);
            safeSleep(timeFrameTookToRun, interval);
        }
    }
    window.cleanUp();

    SDL_Quit();

    return 0;
}