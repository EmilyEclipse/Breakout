#pragma once

#include <SDL2/SDL.h>
#include <gtest/gtest.h>

#include <chrono>

class Util {
public:
    static void safeSleep(
        const std::chrono::duration<int, std::milli>& timeFrameTookToRun,
        const std::chrono::duration<int, std::milli>& interval)
    {
        int timeToSkip = calculateSkip(timeFrameTookToRun, interval);
        if(timeToSkip > 0)
        {
            SDL_Delay(timeToSkip);
        }
    }

    static int calculateSkip(
        const std::chrono::duration<int, std::milli>& timeFrameTookToRun,
        const std::chrono::duration<int, std::milli>& interval)
    {
        //assumes timeFrameTookToRun is not negative
        return (interval - timeFrameTookToRun).count();
    }

    static bool fltEqual(double d1, double d2)
    {
        const double epsilon = 10e-6;
        return abs(d1 - d2) < epsilon;
    }

    static bool fltLessThan(double d1, double d2)
    {
        const double epsilon = 10e-6;
        return d1 < d2 && abs(d1 - d2) > epsilon;
    }

    static bool fltGreaterThan(double d1, double d2)
    {
        const double epsilon = 10e-6;
        return d1 > d2 && abs(d1 - d2) > epsilon;
    }
};