#pragma once

#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

class AudioManager
{
public:
    AudioManager();
    void playSample(int sampleIndex);
    enum sfx {
        BLEEP = 0,
        BLOOP,
        BAD
    };
private:
    std::vector<Mix_Chunk*> samples;
    std::filesystem::path sfx_names[3] = 
    {
        "bleep.wav",
        "bloop.wav",
        "bad.wav"
    };
};