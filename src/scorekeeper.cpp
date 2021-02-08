#include "ScoreKeeper.hpp"

ScoreKeeper::ScoreKeeper(Uint16* i_winW)
: score(0), prevScore(0), window_Width(i_winW)
{
    rebuildTexture();
}

void ScoreKeeper::incrementScore(Uint16 addValue){
    score += addValue;
}

void ScoreKeeper::handleScore(){
    if(score != prevScore)
        rebuildTexture();

    double scaleFactor = 2;

    Rectangle destRect(scoreTex.getRectX(), scoreTex.getRectY(),
            scoreTex.getRectW() * scaleFactor, scoreTex.getRectH() * scaleFactor);

    Draw::draw(&scoreTex, &destRect);
    prevScore = score;
}

void ScoreKeeper::rebuildTexture(){
    SDL_Texture* tex_p = Draw::renderText(std::to_string(score), 255, 255, 255);
    scoreTex = Texture(tex_p, *window_Width - 300, 20);
}
