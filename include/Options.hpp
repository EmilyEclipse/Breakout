#pragma once

#include <SDL2/SDL.h>

#include <map>
#include <string>

class Options
{
public:
    Options();
    void readOptions();

    Uint16 windowWidth;
    Uint16 windowHeight;
    Uint16 framesPerSecond;

    double xScale, yScale;

private:
    enum options {
        window_width,
        window_height,
        fps
    };

    std::map<std::string, options> optionsMap = 
    { 
        {"window_width", window_width},
        {"window_height", window_height},
        {"frames_per_second", fps}
    };
};

