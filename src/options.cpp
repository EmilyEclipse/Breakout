#include "Options.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <fstream>
#include <sstream>

Options::Options()
{
    readOptions();
}

void Options::readOptions()
{
    std::fstream optionsFile("options.txt", std::ios::in);

    Uint16 count = 1;

    for(std::string inputLine; std::getline(optionsFile, inputLine); )
    {
        ++count;

        if(inputLine.empty())
            continue;

        std::istringstream lineStream(inputLine);
        std::string rowHeading;
        lineStream >> rowHeading;

        if(rowHeading[0] == '#')
            continue;

        switch(optionsMap[rowHeading])
        {
            case window_width:
                lineStream >> windowWidth;
            
            case window_height:
                lineStream >> windowHeight;

            case fps:
                lineStream >> framesPerSecond;

            default:
                std::cout << "Error reading option at line " << count;
        }
    }

    xScale = windowWidth / 1920.0;
    yScale = windowHeight / 1080.0; 
}