#pragma once

#include <list>

#include "Draw.hpp"
#include "Rectangle.hpp"

class DrawRegistry{
public:
    DrawRegistry();

    void DrawElements() const;
    void RegisterElement(Rectangle * input);
    void UnregisterElement(const Rectangle * input);

    static bool compare(const Rectangle * r1, const Rectangle * r2);

private:
    std::list<const Rectangle *> stuffToDraw;
    Uint16 idCounter;
};