#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>

#include "Draw.hpp"
#include "RenderWindow.hpp"
#include "Rectangle.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "HyperBlock.hpp"
#include "Keyboard.hpp"
#include "Util.hpp"

int main(int argc, char *argv[])
{
    const char* title = "BREAKOUT v0.2";
    Uint16 windowWidth = 1920;
    Uint16 windowHeight = 1080;
    const Uint8 FPS = 60;
    //expected time between frames(if computer is fast enough)
    const std::chrono::milliseconds interval = static_cast<std::chrono::milliseconds>(1000 / FPS);

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        std::cerr << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    RenderWindow window(title, windowWidth, windowHeight);

    const bool variableFPS = false;
    bool gameRunning = true;
    SDL_Event event;

    
    Paddle paddle(windowWidth);
    HyperBlock hyperBlock(100, 150, &windowWidth);
    Ball ball(&windowWidth, &windowHeight, &paddle, &hyperBlock);

    Keyboard::setPaddle(&paddle);
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

            Keyboard::handleInput();
            ball.move();


            SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
            SDL_RenderClear(window.getRenderer());

            Draw::hyperBlock(&hyperBlock);
            Draw::rect(paddle.getRect(), 255, 255, 255);
            Draw::rect(ball.getRect(), 255, 244, 79);
            SDL_RenderPresent(window.getRenderer());
            //SDL_Delay(1000);

            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<int, std::milli> timeFrameTookToRun = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(end - start);
            Util::safeSleep(timeFrameTookToRun, interval);
        }
    }
    window.cleanUp();

    SDL_Quit();

    return 0;
}