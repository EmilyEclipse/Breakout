#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SDL2/SDL.h>

#include "Displayed/Paddle.hpp"

class Keyboard
{
public:
    static void handleInput();
    static void setPaddle(Paddle* paddle);
    class Key{
        public:
            Key(int inputScancode){
                scancode = inputScancode;
                state_p = &keyboardState[scancode];
            }
            Uint8 getState(){
                return *state_p;
            }
        private:
            Uint8 scancode;
            const Uint8* state_p;
    };
private:
    static Paddle* paddle;
    static const Uint8* keyboardState;
    
};

#endif //KEYBOARD_HPP