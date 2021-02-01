#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "Draw.hpp"

#include "HyperBlock.hpp"
#include "Texture.hpp"

SDL_Renderer* Draw::renderer;
TTF_Font* Draw::score_font;

void Draw::draw(const Rectangle& rectangle)
{
    draw(rectangle.getRect(), rectangle.getRed(),
    rectangle.getGreen(), rectangle.getBlue());
}

void Draw::draw(const SDL_Rect* rectangle, const Uint8 red, const Uint8 green,
    const Uint8 blue)
{
    SDL_SetRenderDrawColor(Draw::renderer, red, green, blue, 255);

    SDL_RenderFillRect(Draw::renderer, rectangle);
}

// void Draw::draw(const HyperBlock* hyper)
// {
//     for(auto row : hyper->elements)
//         for(auto block : row)
//             Draw::draw(block.getRect(),
//                         block.getRed(), block.getGreen(), block.getBlue());
// }

void Draw::draw(const Line line, const Uint8 red,
        const Uint8 green, const Uint8 blue)
{
    SDL_SetRenderDrawColor(Draw::renderer, red, green, blue, 255);
    
    SDL_RenderDrawLine(Draw::renderer, line.first.x, line.first.y,
        line.second.x, line.second.y);
}

void Draw::draw(const Texture* tex)
{
    SDL_RenderCopy(renderer, tex->getTextureP(), NULL, tex->getRect());
}

void Draw::draw(const Texture* tex, const Rectangle* destRect)
{
    SDL_RenderCopy(renderer, tex->getTextureP(), NULL, destRect->getRect());
}


SDL_Texture* Draw::renderText(std::string text,
        const Uint8 red, const Uint8 green, const Uint8 blue)
{
    SDL_Color color = {red, green, blue, 255};
    SDL_Surface* textSurf = TTF_RenderText_Solid(score_font, text.c_str(), color);

    SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, textSurf);

    return textTex;
}

void Draw::setRenderer(SDL_Renderer* inputRenderer)
{
    Draw::renderer = inputRenderer;
}

void Draw::loadTTF(std::filesystem::path relativePath, Uint16 size)
{
    auto fontPath = std::filesystem::current_path() / relativePath;
    score_font = TTF_OpenFont(fontPath.string().c_str(), size);
    if(score_font == nullptr)
        std::cout << "TTF_OpenFont failed. SDL error: " << SDL_GetError() << std::endl;
}