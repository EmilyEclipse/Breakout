#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>

#include "Draw.hpp"
#include "RenderWindow.hpp"
#include "Rectangle.hpp"
#include "Paddle.hpp"

void safeSleep(const std::chrono::duration<int, std::milli>& timeFrameTookToRun,
                const std::chrono::duration<int, std::milli>& interval)
{
    int timeToSkip = (interval - timeFrameTookToRun).count();
    if(timeToSkip > 0)
    {
        SDL_Delay(timeToSkip);
    }
}

short calculateSpeed(short frameCount, short maxSpeed, short acceleration)
{
    short speed = frameCount * acceleration + acceleration;
    if (speed <= maxSpeed)
        return speed;
    else return maxSpeed;
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
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    short movementSpeed = 0;
    short maxMovementSpeed = 10;
    short movementFrameCount = 0;
    bool moving = false;


    
    Paddle paddle(windowWidth / 2, 900, 300, 50);
    Draw::setRenderer(window.getRenderer());

    //MAIN GAME LOOPS
    if(variableFPS)
    {

    } else 
    {
        while(gameRunning)
        {
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                {
                    gameRunning = false;
                    break;
                }
            }

            SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
            SDL_RenderClear(window.getRenderer());

            Draw::rect(paddle.getRect(), 255, 255, 255);
            SDL_RenderPresent(window.getRenderer());

            //keyboard input
            {
                movementSpeed = calculateSpeed(movementFrameCount, maxMovementSpeed, 2);
                if(keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A])
                {
                    paddle.moveLeft(movementSpeed);
                    moving = true;
                }

                if(keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D])
                {
                    paddle.moveRight(movementSpeed);
                    moving = true;
                }

                if(!keyboardState[SDL_SCANCODE_LEFT] && !keyboardState[SDL_SCANCODE_A] && !keyboardState[SDL_SCANCODE_RIGHT] && !keyboardState[SDL_SCANCODE_D])
                    moving = false;
                if(moving)
                    ++movementFrameCount;
                else  movementFrameCount = 0;
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