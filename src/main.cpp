#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>

#include <fstream>

#include "AudioManager.hpp"
#include "Draw.hpp"
#include "DrawRegistry.hpp"
#include "RenderWindow.hpp"
#include "Rectangle.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "HyperBlock.hpp"
#include "Keyboard.hpp"
#include "Options.hpp"
#include "ScoreKeeper.hpp"
#include "Util.hpp"

int main(int argc, char *argv[])
{
    const char* title = "BREAKOUT v0.5";
    Options options;
    //expected time between frames(if computer is fast enough)
    int ratio = floor(1000.0 / options.framesPerSecond);
    const std::chrono::milliseconds interval(ratio);

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    if (TTF_Init() != 0){
        std::cout << "TTF_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	    SDL_Quit();
	    return 1;
    }

    RenderWindow window(title, options.windowWidth, options.windowHeight);

    const bool variableFPS = false;
    bool gameRunning = true;
    SDL_Event event;

    DrawRegistry drawReg;
    Draw::loadTTF("arcade-classic.ttf", 42);
    Draw::setRenderer(window.getRenderer());
    ScoreKeeper scoreKeeper(&options.windowWidth);
    AudioManager audioManager;
    
    HyperBlock hyperBlock(drawReg, options);
    Paddle paddle(options, hyperBlock);
    Ball ball(options, paddle, hyperBlock, scoreKeeper, audioManager);

    drawReg.RegisterElement(paddle.getRectangle());
    drawReg.RegisterElement(ball.getRectangle());
    
    for(auto block_iter = hyperBlock.getElements()->begin(); block_iter != hyperBlock.getElements()->end(); ++block_iter)
        drawReg.RegisterElement(&(*block_iter));


    Keyboard::setPaddle(&paddle);

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

            drawReg.DrawElements();
            scoreKeeper.handleScore();
            SDL_RenderPresent(window.getRenderer());

            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<int64_t, std::nano> timeFrameTookToRun = end - start;
            Util::safeSleep(timeFrameTookToRun, interval);
        }
    }
    window.cleanUp();

    SDL_Quit();

    return 0;
}