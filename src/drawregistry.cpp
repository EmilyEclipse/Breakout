#include <list>
#include <algorithm>

#include "DrawRegistry.hpp"

DrawRegistry::DrawRegistry(){
    this->stuffToDraw.clear();
}

void DrawRegistry::DrawElements() const
{
    for(auto element : stuffToDraw)
    {
        Draw::draw(*element);
    }
}

void DrawRegistry::RegisterElement(const Rectangle* input)
{
    if(!stuffToDraw.empty())
    {
    stuffToDraw.insert(std::lower_bound(stuffToDraw.begin(), stuffToDraw.end(),
        input, DrawRegistry::compare), input);
    } else {
        stuffToDraw.push_back(input);
    }
}

void DrawRegistry::UnregisterElement(const Rectangle * input)
{
    for(auto pointer_iter = stuffToDraw.begin(); pointer_iter != stuffToDraw.end(); ++pointer_iter)
        if(*pointer_iter == input)
        {
            stuffToDraw.erase(pointer_iter);
            break;
        }
}

bool DrawRegistry::compare(const Rectangle * r1, const Rectangle * r2)
{
    return r1->getLayer() < r2->getLayer();
}