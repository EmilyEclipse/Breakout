#ifndef DRAW_HPP
#define DRAW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <filesystem>
#include <string>

#include "Texture.hpp"
#include "Rectangle.hpp"
#include "Line.hpp"

class Draw
{
public:
    static void draw(const Rectangle& rectangle);

    static void draw(const SDL_Rect* rectangle, const Uint8 red,
        const Uint8 green, const Uint8 blue);
    //static void draw(const HyperBlock* hyper);
    static void draw(const Line line, const Uint8 red,
        const Uint8 green, const Uint8 blue);
    
    static void draw(const Sint16 number, const Uint8 red,
        const Uint8 green, const Uint8 blue);

    static void draw(const Texture* tex);
    static void draw(const Texture* tex, const Rectangle* rect);

    static SDL_Texture* renderText(std::string text,
        const Uint8 red, const Uint8 green, const Uint8 blue);

    static void setRenderer(SDL_Renderer* renderer);
    static void loadTTF(std::filesystem::path relativePath, Uint16 size);
private:
    static SDL_Renderer *renderer;
    static TTF_Font* score_font;
};

#endif //DRAW_HPP