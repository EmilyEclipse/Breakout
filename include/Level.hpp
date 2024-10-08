#pragma once

#include <SDL2/SDL.h>

#include "AudioManager.hpp"
#include "Displayed/Ball.hpp"
#include "Displayed/Paddle.hpp"
#include "Displayed/Blocks/HyperBlock.hpp"
#include "DrawRegistry.hpp"
#include "Keyboard.hpp"
#include "Options.hpp"
#include "ScoreKeeper.hpp"


class LevelManager 
{
public:
    LevelManager(AudioManager& i_AM, Options& i_OP, ScoreKeeper& i_SK);
    void makeLevel();
    void destroyLevel();

    AudioManager* audioMan;
    HyperBlock* hyperBlock;
    Options* options;
    ScoreKeeper* scoreKeeper;
    Ball* ball;
    Paddle* paddle;
    DrawRegistry* drawReg;

private:
    
};

LevelManager::LevelManager(AudioManager& i_AM, Options& i_OP, ScoreKeeper& i_SK)
: audioMan(&i_AM), options(&i_OP), scoreKeeper(&i_SK)
{}

void LevelManager::makeLevel()
{
    this->drawReg = new DrawRegistry();

    this->hyperBlock = new HyperBlock(*drawReg, *options);
    this->paddle = new Paddle(*options, *hyperBlock);
    this->ball = new Ball(*options, *paddle, *hyperBlock, *scoreKeeper, *audioMan);

    Keyboard::setPaddle(paddle);

    drawReg->RegisterElement(paddle);
    drawReg->RegisterElement(ball);

    for(auto block_iter = hyperBlock->getElements()->begin(); block_iter != hyperBlock->getElements()->end(); ++block_iter)
        drawReg->RegisterElement(&(*block_iter));
}

void LevelManager::destroyLevel()
{
    delete ball;
    delete paddle;
    delete hyperBlock;
    delete drawReg;
    Keyboard::setPaddle(nullptr);
}