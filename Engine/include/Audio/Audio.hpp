#pragma once

#include "Audio/Sound.hpp"

#include <SDL3/SDL.h>

#include <memory>
#include <string>
#include <vector>

namespace Pigtail
{

class Audio
{
public:
    static bool initialize();
    static void shutdown();

    static bool isInitialized();

    static std::shared_ptr<Sound> loadSound(
        const std::string& path);

    static void play(
        const std::shared_ptr<Sound>& sound,
        float volume = 1.0f,
        bool loop = false);

    static void stopAll();

    static void setMasterVolume(float volume);
    static float masterVolume();

    static void update();

private:
    struct Voice
    {
        SDL_AudioStream* stream = nullptr;

        std::shared_ptr<Sound> sound;

        float volume = 1.0f;
        bool loop = false;
    };

    static SDL_AudioDeviceID s_device;
    static bool s_initialized;
    static float s_masterVolume;

    static std::vector<Voice> s_voices;
};

}