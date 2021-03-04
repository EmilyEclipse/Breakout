#include "AudioManager.hpp"

AudioManager::AudioManager()
{
    Mix_OpenAudio(44100, AUDIO_S16SYS, 1, 512);

    for(auto name : sfx_names)
    {
        Mix_Chunk* mc_p = Mix_LoadWAV(("sfx" / name).c_str());
        if(mc_p != nullptr)
        {
            samples.push_back(mc_p);
            //mc_p->volume = 128;
        }
        else {
            std::cout << "SDL_Mix failed to load sample file \"" << name <<"\".\n"
                      << "SDL_Error: " << SDL_GetError();     
        }
    }
}

void AudioManager::playSample(int sampleIndex)
{
    Mix_PlayChannel(-1, samples[sampleIndex], 0);
}