#include <SDL2/SDL.h>

#include "Keyboard.hpp"
#include "Displayed/Paddle.hpp"

Paddle* Keyboard::paddle;
const Uint8* Keyboard::keyboardState = SDL_GetKeyboardState(NULL);
Keyboard::Key LEFT(SDL_SCANCODE_LEFT);
Keyboard::Key RIGHT(SDL_SCANCODE_RIGHT);
Keyboard::Key A(SDL_SCANCODE_A);
Keyboard::Key D(SDL_SCANCODE_D);

void Keyboard::handleInput(){
    if(paddle->canMoveLeft()){
        if(LEFT.getState() || A.getState())
        {
            paddle->moveLeft();
            paddle->setMoving(true);
        }
    }
    if(paddle->canMoveRight()){
        if(RIGHT.getState() || D.getState())
        {
            paddle->moveRight();
            paddle->setMoving(true);
        }
    }

    if(!(LEFT.getState() || A.getState() || RIGHT.getState() || D.getState()))
        paddle->setMoving(false);
}

void Keyboard::setPaddle(Paddle* inputPaddle){
    paddle = inputPaddle;
}