#pragma once

#include <SDL2/SDL.h>

#include <chrono>

class Util {
public:
    static void safeSleep(
        const std::chrono::duration<int64_t, std::nano> timeFrameTookToRun,
        const std::chrono::duration<int32_t, std::milli> interval)
    {

        int32_t timeToSkip = calculateSkip(
            std::chrono::duration_cast<std::chrono::duration<int32_t, std::milli>>(timeFrameTookToRun),
            std::chrono::duration_cast<std::chrono::duration<int32_t, std::milli>>(interval));
        if(timeToSkip > 0)
        {
            SDL_Delay(timeToSkip);
        }
    }

    static int calculateSkip(
        const std::chrono::duration<int64_t, std::milli> timeFrameTookToRun,
        const std::chrono::duration<int64_t, std::milli> interval)
    {
        //assumes timeFrameTookToRun is not negative
        return (interval - timeFrameTookToRun).count();
    }

    static std::chrono::high_resolution_clock::time_point calculateTimeTo(std::chrono::milliseconds millis)
    {
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point intervalStart = now + millis;
        return intervalStart;
    }
};