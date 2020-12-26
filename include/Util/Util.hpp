#pragma once

#include <SDL2/SDL.h>
#include <gtest/gtest.h>

#include <chrono>

class Util {
public:
    void safeSleep(const std::chrono::duration<int, std::milli>& timeFrameTookToRun,
                const std::chrono::duration<int, std::milli>& interval)
    {
        int timeToSkip = calculateSkip(timeFrameTookToRun, interval);
        if(timeToSkip > 0)
        {
            SDL_Delay(timeToSkip);
        }
    }

    int calculateSkip(const std::chrono::duration<int, std::milli>& timeFrameTookToRun,
                const std::chrono::duration<int, std::milli>& interval)
    {
        //assumes timeFrameTookToRun is not negative
        return (interval - timeFrameTookToRun).count();
    }

  
};