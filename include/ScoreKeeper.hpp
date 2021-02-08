#pragma once

#include <SDL2/SDL.h>

#include "Draw.hpp"
#include "Texture.hpp"

class ScoreKeeper{
public:
    ScoreKeeper(Uint16* i_winW);
    void incrementScore(Uint16 addValue);
    void handleScore();
    void rebuildTexture();

private:
    Texture scoreTex;
    Uint32 score;
    Uint32 prevScore;
    Uint16* window_Width;
};